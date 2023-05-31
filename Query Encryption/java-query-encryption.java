import java.security.MessageDigest;
import java.util.Base64;

public class EncryptData {

    private static final String AES_ALGORITHM = "AES/CBC/PKCS5Padding";

    public static String encrypt(String data, String password) throws Exception {
        MessageDigest md = MessageDigest.getInstance("SHA-256");
        byte[] key = md.digest(password.getBytes());

        Cipher cipher = Cipher.getInstance(AES_ALGORITHM);
        cipher.init(Cipher.ENCRYPT_MODE, new SecretKeySpec(key, "AES"));

        byte[] iv = cipher.getIV();
        byte[] ciphertext = cipher.doFinal(pad(data.getBytes(), cipher.getBlockSize()));

        return Base64.getEncoder().encodeToString(iv) + Base64.getEncoder().encodeToString(ciphertext);
    }

    private static byte[] pad(byte[] data, int blockSize) {
        int padding = blockSize - data.length % blockSize;
        byte[] padBytes = new byte[padding];
        Arrays.fill(padBytes, (byte) padding);

        return concat(data, padBytes);
    }

    private static byte[] unpad(byte[] data, int blockSize) {
        int padding = data[data.length - 1];
        if (padding > blockSize) {
            throw new IllegalArgumentException("Invalid padding");
        }

        return Arrays.copyOfRange(data, 0, data.length - padding);
    }

    private static byte[] concat(byte[] a, byte[] b) {
        byte[] c = new byte[a.length + b.length];
        System.arraycopy(a, 0, c, 0, a.length);
        System.arraycopy(b, 0, c, a.length, b.length);

        return c;
    }

    public static void main(String[] args) throws Exception {
        String data = "select * from `test`";
        String password = "PhpMyAdmin_Password";

        String encryptedData = encrypt(data, password);
        System.out.println("Encrypted data: " + encryptedData);
    }
}
