from random import randint, seed


def miller_rabin(n):
    for i in range(k):
        if n == 1: return False
        if n == 2: return True
        if n % 2 == 0: return False

        m = n - 1
        r = 0
        while m % 2 == 0:
            m //= 2
            r += 1
        seed(1)
    
        a = randint(2, n - 1)
        x = pow(a, m, n)
        if x == 1 or x == n - 1:
            return True
        while r > 1:
            x = pow(x, 2, n)
            if x == 1: return False
            if x == n - 1: return True
            r -= 1
        return False
    return True