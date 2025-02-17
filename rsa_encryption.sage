# RSA Encryption Implementation in SageMath

# Step 1: Generate two large primes (512-bit primes here for demonstration)
p = random_prime(2^512, lbound=2^511)
q = random_prime(2^512, lbound=2^511)

# Step 2: Compute the RSA modulus and Euler's totient
n = p * q
phi = (p - 1) * (q - 1)

# Step 3: Choose the public exponent e (65537 is common) and ensure it's coprime with phi.
e = 65537
if gcd(e, phi) != 1:
    while gcd(e, phi) != 1:
        e = next_prime(e)

# Step 4: Compute the private exponent d
d = inverse_mod(e, phi)

# Encryption function: encrypts an integer message m < n
def encrypt(m):
    return power_mod(m, e, n)

# Decryption function: decrypts the ciphertext back to the original message integer
def decrypt(c):
    return power_mod(c, d, n)

# Helper: Convert a string to an integer
def string_to_int(s):
    # Convert the string to its hexadecimal representation then to an integer.
    return Integer(int(s.encode('utf-8').hex(), 16))

# Helper: Convert an integer back to a string
def int_to_string(m_int):
    hex_str = hex(m_int)[2:]
    if len(hex_str) % 2:
        hex_str = '0' + hex_str  # pad with a zero if needed
    return bytes.fromhex(hex_str).decode('utf-8')

# Example usage:
message = "Hello, RSA!"
print("Original message:", message)

# Convert the message to an integer
m_int = string_to_int(message)

# Encrypt the integer message
ciphertext = encrypt(m_int)
print("Encrypted ciphertext (integer):", ciphertext)

# Decrypt the ciphertext back to integer
decrypted_int = decrypt(ciphertext)

# Convert the integer back to a string
decrypted_message = int_to_string(decrypted_int)
print("Decrypted message:", decrypted_message)
