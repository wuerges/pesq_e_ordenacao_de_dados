from it import *


t1 = IT(P(0,0), P(10000,10000))


i1 = I(P(5, 10), P(20, 30))


t1.update(i1, 5)
print(t1.query(i1))
