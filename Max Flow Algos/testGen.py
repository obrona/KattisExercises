import random



# generates a complete graph 
def generate(n):
    file = open('test4.in', 'w')
    file.write('%d %d %d %d\n' % (n, 0, n - 1, n * (n - 1) / 2))
    for i in range(n):
        for j in range(i + 1, n):
            file.write('%d %d %d\n' % (i, j, random.randint(1, 10)))


def generate2(n):
    file = open('test5.in', 'w')
    file.write('%d %d %d %d\n' % (n, 0, n - 1, n - 1))
    for i in range(n - 1):
        file.write('%d %d %d\n' % (i, i + 1, random.randint(1, 10)))

generate(300)
#generate2(50000)