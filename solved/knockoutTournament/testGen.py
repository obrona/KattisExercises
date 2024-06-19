import random
import subprocess
import sys


def generate(n):
    file = open('test4.in', 'w')
    file.write('%d\n' % (n))
    for i in range(n):
        file.write('%d\n' % (random.randint(1, 10)))



def test(n):
    for i in range(n):
        generate(4000)
        res1 = subprocess.run(['a.exe'], stdin=open('test4.in', 'r'), capture_output=True, text=True)
        ans1 = float(res1.stdout)
        print(ans1)

        res2 = subprocess.run(['test.exe'], stdin=open('test4.in', 'r'), capture_output=True, text=True)
        ans2 = float(res2.stdout)

        

        if abs(ans2 - ans1) > 0.0000001:
            print('failed')
            break

#test(5)
generate(4000)