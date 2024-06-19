def matrixMult(m1, m2):
   row = len(m1)
   col = len(m2[0])
   out = [[0 for i in range(col)] for i in range(row)]
   for i in range(row):
      for j in range(col):
         count = 0
         for k in range(len(m1[0])):
            count += (m1[i][k] * m2[k][j]) % 1000000000
         out[i][j] = count % 10000000001
   return out


def fastMatrixExpo(m1, power):
   if power == 0:
      out = [[0 for i in range(len(m1[0]))] for i in range(len(m1))]
      for i in range(len(m1)):
         out[i][i] = 1
      return out
   elif power % 2 == 0:
      lst = fastMatrixExpo(m1, power / 2)
      return matrixMult(lst, lst)
   else:
      lst = fastMatrixExpo(m1, power // 2)
      return matrixMult(matrixMult(lst, lst), m1)
   
lst = [[1,1],[1,0]]
n = int(input())
for i in range(n):
   a, b = list(map(int, input().split()))
   ans = fastMatrixExpo(lst, b - 1)[0][0]
   ans %= 1000000000
   print(i + 1, " ", ans)
      

        