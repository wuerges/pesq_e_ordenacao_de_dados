


class P:
    def __init__(self, x, y):
        self.x = x
        self.y = y


    def __eq__(self, o):
        return self.x == o.x and self.y == o.y

class I:
    def __init__(self, p1, p2):
        self.p1 = p1
        self.p2 = p2

    def mid(self):
        midx = (self.p1.x + self.p2.x) // 2
        midy = (self.p1.y + self.p2.y) // 2
        return P(midx, midy)

    def cols(self, i):
        rx = self.p1.x <= i.p1.x <= self.p2.x or self.p1.x <= i.p2.x <= self.p2.x
        ry = self.p1.y <= i.p1.y <= self.p2.y or self.p1.y <= i.p2.y <= self.p2.y
        return rx and ry


class IT:
    def __init__(self, p1, p2):
        self.i = I(p1, p2)
        self.v = int(1e16)
        self.mid = self.i.mid()
        self.q1 = None
        self.q2 = None
        self.q3 = None
        self.q4 = None

    def update(self, i, v):
        if self.i.cols(i):
            self.v = v
            if self.i.p1 == self.i.p2:
                return
            else:
                self.get_q1().update(i, v)
                self.get_q2().update(i, v)
                self.get_q3().update(i, v)
                self.get_q4().update(i, v)

    def get_q1(self):
        if not self.q1:
            self.q1 = IT(self.i.p1, self.mid)
        return self.q1

    def get_q2(self):
        if not self.q2:
            p1 = P(self.mid.x+1, self.i.p1.y)
            p2 = P(self.i.p2.x, self.mid.y)
            self.q2 = IT(p1, p2)
        return self.q2

    def get_q3(self):
        if not self.q3:

            self.q3 = IT(P(self.mid.x+1, self.mid.y+1), self.i.p2)
        return self.q3

    def get_q4(self):
        if not self.q4:
            p1 = P(self.i.p1.x, self.mid.y+1)
            p2 = P(self.mid.x, self.i.p2.y)
            self.q4 = IT(p1, p2)
        return self.q4
