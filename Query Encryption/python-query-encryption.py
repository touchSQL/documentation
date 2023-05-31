import base64
from Crypto.Cipher import AES
from Crypto.Util.Padding import pad, unpad
import hashlib

ALGORITHM = "AES"
CIPHER_MODE = "AES/CBC/PKCS5Padding"
KEY_SIZE = 256

def encryptData(data, password):
    key = generateKey(password)
    cipher = AES.new(key, AES.MODE_CBC)
    iv = cipher.iv
    encryptedBytes = cipher.encrypt(pad(data.encode('utf-8'), AES.block_size))
    combined = iv + encryptedBytes
    encryptedBase64 = base64.b64encode(combined)
    return encryptedBase64.decode()

def generateKey(password):
    digest = hashlib.sha256()
    digest.update(password.encode('utf-8'))
    key = digest.digest()
    return key[:KEY_SIZE // 8]

data = "select * from `test`"
password = "PhpMyAdmin_Password"

encrypted = encryptData(data, password)
print("Encrypted data:", encrypted)
