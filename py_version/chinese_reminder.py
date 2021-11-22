from miller_rabin import miller_rabin
import sys, math, json, random

def gcd(p, q):      
    if q == 0: return p
    return gcd(q, p % q)


def lcm(p, q):
    return (p * q) / gcd(p, q)
  


def egcd(e, phi):
    if e == 0:
        return (phi, 0, 1)
    else:
        g, y, x = egcd(phi % e, e)
        return (g, x - (phi // e) * y, y)
  


def modinv(e, phi):      
    g, x, y = egcd(e, phi)
    return int(x % phi)
  


def chineseremaindertheorem(dq, dp, p, q, c):
    m1 = pow(c, dp, p)
    m2 = pow(c, dq, q)
    qinv = modinv(q, p)

    h = (qinv * (m1 - m2)) % p
    m = m2 + h * q
    return m


# def create_privat_key(e, phi_n):
#     d = 0
#     while True:
#         if (e * d) % phi_n == 1:
#             return d
#         d += 1


def create_public_key(num):
    e = random.randint(3, num) 
    while(gcd(e, num) != 1):
        e = random.randint(3, num)
    return e 



def generate_prime(keylen):
    min_val = 2 ** (keylen - 1)
    max_val = 2 ** keylen - 1
    num = random.randint(min_val, max_val)
    while (miller_rabin(num) != True):
        num = random.randint(min_val, max_val)
    return num




def write_keys(keys):
    with open('keys.json', 'w+') as file:
        obj = json.dumps(keys)
        file.write(obj)



def encrypt(plaintext):
    p = generate_prime(1024)
    print("[LOG] p generated.", p)
    q = generate_prime(1024)
    print("[LOG] q generated.", q)

    n = p * q
    
    phi_n = (p - 1) * (q - 1)
    print("[LOG] phi_n calculated.", phi_n)

    e = create_public_key(phi_n - 1)
    print("[LOG] public key generated.", e)

    d = modinv(e, lcm(p - 1, q - 1))
    print("[LOG] privat key generated.", d)

    keys = {
        'p' : p,
        'q' : q,
        'phi_n' : phi_n,
        'e' : e,
        'd' : d}
    write_keys(keys)
    print("[LOG] keys wrote.")
    print([str(pow(ord(letter), e, phi_n)) for letter in plaintext])
    chiphertext = "\n".join([str(pow(ord(letter), e, phi_n)) for letter in plaintext])
    print("[LOG] text encrypted.")
    with open('chiphertext', 'w+') as chipher:
        chipher.write(chiphertext)


def decrypt():
    with open('keys.json', 'r+') as f:
        keys = json.load(f)
    
    with open('chiphertext', 'r+') as chipher:
        ciphertext = chipher.read().split()
    
    dq = int(pow(keys['d'], 1, keys['q'] - 1))
    dp = int(pow(keys['d'], 1, keys['p'] - 1))
    
    decrypt = ''

    for c in ciphertext:
        decrypt += chr(chineseremaindertheorem(dq, dp, keys['p'], keys['q'], int(c)))
    with open('decrypted', 'w+') as chipher:
        chipher.write(decrypt)


def main():
    # if len(sys.argv) < 2:
    #     print("Error! Invalid number of arguments, 3 required.")

    # with open(sys.argv[1], 'r+') as f:
    #     plaintext = f.read()
    encrypt("HELLO THERE!")
    decrypt()

if __name__ == '__main__':
    main()