// Currently under development, but you can use this code and modify it according to your requirements.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/aes.h>
#include <openssl/rand.h>
#include <openssl/sha.h>
#include <openssl/bio.h>
#include <openssl/buffer.h>

#define AES_BLOCK_SIZE 16

void sha256(const char *data, size_t data_len, unsigned char *digest) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, data, data_len);
    SHA256_Final(digest, &sha256);
}

void base64_encode(const unsigned char *data, size_t data_len, char **encoded_data) {
    BIO *bio, *b64;
    BUF_MEM *buffer_ptr;

    b64 = BIO_new(BIO_f_base64());
    bio = BIO_new(BIO_s_mem());
    bio = BIO_push(b64, bio);
    BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL);
    BIO_write(bio, data, data_len);
    BIO_flush(bio);
    BIO_get_mem_ptr(bio, &buffer_ptr);

    *encoded_data = (char *)malloc(buffer_ptr->length);
    memcpy(*encoded_data, buffer_ptr->data, buffer_ptr->length - 1);
    (*encoded_data)[buffer_ptr->length - 1] = "\0";

    BIO_free_all(bio);
}

void encrypt(const char *data, size_t data_len, const char *password, size_t password_len, char **encrypted_data) {
    unsigned char key[SHA256_DIGEST_LENGTH];
    unsigned char iv[AES_BLOCK_SIZE];
    unsigned char ciphertext[data_len + AES_BLOCK_SIZE];

    sha256(password, password_len, key);
    RAND_bytes(iv, AES_BLOCK_SIZE);

    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv);
    EVP_EncryptUpdate(ctx, ciphertext, (int *)&data_len, (const unsigned char *)data, data_len);
    EVP_EncryptFinal_ex(ctx, ciphertext + data_len, (int *)&data_len);

    size_t iv_b64_len;
    char *iv_b64;
    base64_encode(iv, AES_BLOCK_SIZE, &iv_b64);

    size_t ciphertext_b64_len;
    char *ciphertext_b64;
    base64_encode(ciphertext, data_len + AES_BLOCK_SIZE, &ciphertext_b64);

    size_t encrypted_data_len = iv_b64_len + ciphertext_b64_len;
    *encrypted_data = (char *)malloc(encrypted_data_len);
    strcpy(*encrypted_data, iv_b64);
    strcat(*encrypted_data, ciphertext_b64);

    free(iv_b64);
    free(ciphertext_b64);
    EVP_CIPHER_CTX_free(ctx);
}

int main() {
    const char *data = "select * from `test`";
    size_t data_len = strlen(data);
    const char *password = "PhpMyAdmin_Password";
    size_t password_len = strlen(password);

    char *encrypted_data;
    encrypt(data, data_len, password, password_len, &encrypted_data);
    printf("Encrypted data: %s\n", encrypted_data);

    free(encrypted_data);

    return 0;
}
