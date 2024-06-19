import random
import subprocess

def generate(n, m):
    file = file = open('test5.in', 'w')
    file.write("%d %d %d %d\n" % (n, m, 0, n - 1))
    matrix = [[0 for i in range(n)] for i in range(n)]
    while m > 0:
        src = random.randint(0, n - 1)
        dest = random.randint(0, n - 1)
        if src == dest:
            continue
        if matrix[src][dest] == 0:
            cap = random.randint(1, 10000)
            file.write("%d %d %d\n" % (src, dest, cap))
            matrix[src][dest] = 1
            m -= 1



def runTests(trials):
    for i in range(trials):
        generate(100, 1000)
        com = subprocess.run(["g++", "maximumflow.cpp"])
        result = subprocess.run(["a.exe"], stdin=open("test5.in", "r"), capture_output=True, text=True)
        out1 = result.stdout
        actual = subprocess.run(["test.exe"], stdin=open("test5.in", "r"), capture_output=True, text=True)
        out2 = actual.stdout
        #print("%s %s" % (out1, out2))
        if (int(out1) != int(out2)):
            print("%s %s" % (out1, out2))

        

runTests(10)
    