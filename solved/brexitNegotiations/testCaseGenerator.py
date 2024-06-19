import random
import subprocess
import sys

def generate(n):
    file = open('test2.in', 'w')
    file.write('%d\n' % (n))
    for i in range(1, n + 1):
        duration = random.randint(1, 100)
        file.write('%d ' % (duration))
        childs = []
        for j in range(i + 1, n + 1):
            if random.randint(0, 1) == 1:
                childs.append(j)
        file.write('%d ' % (len(childs)))
        for i in range(len(childs)):
            file.write('%d ' % (childs[i]))
        file.write('\n')



def findError(trials):
    for i in range(trials):
        generate(5)
        result = subprocess.run(["a.exe"], stdin=open("test2.in", "r"), capture_output=True, text=True)
        output = result.stdout
        sys.stdout.flush()

        result2 = subprocess.run(["test.exe"], stdin=open("test2.in", "r"), capture_output=True, text=True)
        output2 = result2.stdout
        sys.stdout.flush()
        
        if output != output2:
            print(output)
            print(output2)
            print("Error at trial %d" % (i))
            break

findError(1000)


