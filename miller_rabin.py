from random import randint, seed


def miller_rabin(n, k=40):
    if n == 1: return False
    if n == 2: return True
    if n % 2 == 0: return False

    m = n - 1
    r = 0
    while m % 2 == 0:
        m //= 2
        r += 1
    for _ in range(k):
        a = randint(2, n - 1)
        x = pow(a, m, n)
        if x != 1 and x != n - 1:
            while r > 1:
                x = pow(x, 2, n)
                if x == 1: return False
                if x == n - 1: return True
                r -= 1
            if x != n - 1: return False
    return True