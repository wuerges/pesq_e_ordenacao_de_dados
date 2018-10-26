#include <memory>
#include <optional>
#include <iostream>
using namespace std;


struct P {
  int x,y;

  bool operator==(const P & o) const {
    return o.x == x && o.y == y;
  }

  bool lt(const P & o) const {
    return x <= o.x && y <= o.y;
  }
};

struct I {
  P p1, p2;

  P mid() const {
    return P{(p1.x + p2.x) / 2, (p1.y + p2.y) / 2};
  }

  bool point() const {
    return p1.x == p2.x && p1.y == p2.y;
  }

  bool inside(const P & p) const {
    return p1.lt(p) && p.lt(p2);
  }

  bool hits(const I & o) const {
    return inside(o.p1) || inside(o.p2)
      || inside(P{o.p1.x, o.p2.y}) || inside(P{o.p2.x, o.p2.y}) ;
  }
};

const int NEUTRAL = 1e8;
struct IT {
  I i;
  int v;
  optional<int> lazy;
  P mid;
  unique_ptr<IT> q1, q2, q3, q4;

  IT(P p1, P p2): i{p1, p2}, v(NEUTRAL), mid(i.mid()) { }

  void push() {
    if(lazy) {
      v = *lazy;
      lazy.reset();

      if(!i.point()) {
        fix_ptrs();
        q1->lazy = lazy;
        q2->lazy = lazy;
        q3->lazy = lazy;
        q4->lazy = lazy;
      }
    }
  }

  void update(const I & ip, int vp) {
    if (i.p1.lt(ip.p1) && ip.p2.lt(i.p2)) {
      lazy = vp;
      push();
    }
    else {
      if (i.hits(ip)) {
        push();
        fix_ptrs();
        q1->update(ip, vp);
        q2->update(ip, vp);
        q3->update(ip, vp);
        q4->update(ip, vp);

        v = min(q1->v, q2->v);
        v = min(q3->v, v);
        v = min(q4->v, v);
      }
    }
  }

  void fix_ptrs() {
    if(!q1) {
      q1 = make_unique<IT>(i.p1, mid);
    }
    if(!q2) {
      P n_p1{mid.x+1, i.p1.y};
      P n_p2{i.p2.x, mid.y};
      q2 = make_unique<IT>(n_p1, n_p2);
    }
    if(!q3) {
      q3 = make_unique<IT>(P{mid.x+1, mid.y+1}, i.p2);
    }
    if(!q4) {
      P n_p1{i.p1.x, mid.y+1};
      P n_p2{mid.x, i.p2.y};

      q4 = make_unique<IT>(n_p1, n_p2);
    }
  }


  int query(const I & ip) {
    if(!i.hits(ip)) return NEUTRAL;

    if(lazy) {
      return *lazy;
    }
    if (i.p1.lt(ip.p1) && ip.p2.lt(i.p2)) {
      return v;
    }
    fix_ptrs();
    int ret = min(q1->query(ip), q2->query(ip));
    ret = min(ret, q3->query(ip));
    ret = min(ret, q4->query(ip));
    return ret;

  }

};


int main() {
  IT it(P{0,0}, P{10000,10000});


  I i1{P{5, 10}, P{20, 30}};
  I i2{P{8, 20}, P{8,20}};

  it.update(i1, 5);
  cout << it.query(i2) << '\n';

}
