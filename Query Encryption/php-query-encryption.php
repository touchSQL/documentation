<?php
function encryptData($data, $password) {
    $algorithm = "AES-256-CBC";
    $key = generateKey($password);
    $ivLength = openssl_cipher_iv_length($algorithm);
    $iv = openssl_random_pseudo_bytes($ivLength);
    
    $encrypted = openssl_encrypt($data, $algorithm, $key, OPENSSL_RAW_DATA, $iv);
    $combined = $iv . $encrypted;
    $encoded = base64_encode($combined);
    
    return $encoded;
}

function generateKey($password) {
    $keySize = 256;
    $digest = openssl_digest($password, "SHA256", true);
    $key = substr($digest, 0, $keySize / 8);
    
    return $key;
}

$data = "select * from `test`";
$password = "PhpMyAdmin_Password";

$encrypted = encryptData($data, $password);
echo "Encrypted data: " . $encrypted . "\n";

?>
