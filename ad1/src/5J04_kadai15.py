def kadai15(n, y):
    a = 0
    b = 0
    c = 0
    if y >= 10000:
        a = int(y/10000)
        y -= 10000 * int(y/10000)
    if y >= 5000:
        b = int(y/5000)
        y -= 5000 * int(y/5000)
    if y >= 1000:
        c = int(y/1000)
        y -= 1000 * int(y/1000)
    if y > 0 or (a+b+c) > n:
        return -1, -1, -1
    elif y == 0:
        return a, b, c


if __name__ == '__main__':
    while True:
        n, y = input().split()
        print(kadai15(int(n), int(y)))
