from it import *


t1 = IT(P(0,0), P(10000,10000))


i1 = I(P(5, 10), P(20, 30))
i2 = I(P(8, 20), P(8,20))


print("testando se intervalo está vazio")
print(t1.query(i1))
print("colocando elemento no intervalo")
t1.update(i1, 1)

print("testando se tem um elemento no intervalo")
print(t1.query(i2))
