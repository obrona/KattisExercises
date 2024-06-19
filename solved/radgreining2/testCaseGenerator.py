import random
import subprocess



def createString(n):
    lst = ['G', 'A', 'T', 'C']
    arr = []
    for i in range(n):
        arr.append(lst[random.randint(0, 3)])
    return ''.join(arr)

def generate(s, n, k):
    file = open('test5.in', 'w')
    file.write("%d %d\n" % (len(s), len(s) - k + 1))
    for i in range(len(s) - k + 1):
        substring = s[i:i + k]
        if random.randint(0, 1) == 1:
            substring = substring[::-1]
        file.write("%d %s\n" % (i + 1, substring))
    file.write("%s\n" % s)



s = createString(10)
generate(s, 10, 2)

result = subprocess.run(["a.exe"], stdin=open("test5.in", "r"), capture_output=True, text=True)
output = result.stdout
#print(output)
print(output == s)

    








