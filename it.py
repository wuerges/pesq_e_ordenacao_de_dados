
identity = int(1e8)

class P:
    def __init__(self, x, y):
        self.x = x
        self.y = y


    def __eq__(self, o):
        return self.x == o.x and self.y == o.y


    def lt(self, o):
        return self.x <= o.x and self.y <= o.y

    def __repr__(self):
        return "P({}, {})".format(self.x, self.y)

class I:
    def __init__(self, p1, p2):
        self.p1 = p1
        self.p2 = p2

    def mid(self):
        midx = (self.p1.x + self.p2.x) // 2
        midy = (self.p1.y + self.p2.y) // 2
        return P(midx, midy)

    def inside(self, p):

        return self.p1.lt(p) and p.lt(self.p2)

    def cols(self, i):
        return self.inside(i.p1) or self.inside(i.p2) or self.inside(P(i.p1.x, i.p2.y)) or self.inside(P(i.p2.x, i.p2.y))

    def __repr__(self):
        return "I({}, {})".format(self.p1, self.p2)

class IT:
    def __init__(self, p1, p2):
        self.i = I(p1, p2)
        self.v = identity
        self.lazy = (False, 0)
        self.mid = self.i.mid()
        self.q1 = None
        self.q2 = None
        self.q3 = None
        self.q4 = None

    def __repr__(self):
        return "IT({}, {})".format(self.i, self.v)

    def update(self, i, v):
        #if the interval covers the subtree completely
        if i.p1.lt(self.i.p1) and self.i.p2.lt(i.p2):
            print("lazy", self, i, v)
            self.lazy = (True, v)
            self.push()
        elif self.i.cols(i):
            self.push()
            print("collides", self, i, v)

            self.fix_ptrs()
            self.q1.update(i, v)
            self.q2.update(i, v)
            self.q3.update(i, v)
            self.q4.update(i, v)

            self.v = min(self.q1.v, self.q2.v, self.q3.v, self.q4.v)

    def fix_ptrs(self):
        if not self.q1:
            self.q1 = IT(self.i.p1, self.mid)

        if not self.q2:
            p1 = P(self.mid.x+1, self.i.p1.y)
            p2 = P(self.i.p2.x, self.mid.y)
            self.q2 = IT(p1, p2)

        if not self.q3:
            self.q3 = IT(P(self.mid.x+1, self.mid.y+1), self.i.p2)

        if not self.q4:
            p1 = P(self.i.p1.x, self.mid.y+1)
            p2 = P(self.mid.x, self.i.p2.y)
            self.q4 = IT(p1, p2)


    def push(self):
        (l, v) = self.lazy
        if l:
            self.lazy = (False, 0)
            self.v = v
            if not self.i.p1 == self.i.p2:
                self.fix_ptrs()
                self.q1.lazy = (l, v)
                self.q2.lazy = (l, v)
                self.q3.lazy = (l, v)
                self.q4.lazy = (l, v)


    def query(self, i):
        if not self.i.cols(i):
            return identity

        (l, v) = self.lazy
        if l:
            return v
        if i.p1.lt(self.i.p1) and self.i.p2.lt(i.p2):
            return self.v
        self.fix_ptrs()

        return min(self.q1.query(i), self.q2.query(i), self.q3.query(i), self.q4.query(i))
