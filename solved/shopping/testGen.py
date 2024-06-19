
def generate(n):
    file = open('test5.in', 'w')
    file.write('%d %d\n' % (n, n))
    for i in range(n):
        file.write('%d %d %d\n' % (i, (i + 1) % n, 1000000))
    file.write('2\n')
    file.write('%d\n' % (n // 4))
    file.write('%d\n' % (3 * (n // 4)))


generate(100000)
