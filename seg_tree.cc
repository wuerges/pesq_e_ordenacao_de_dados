#include <memory>
#include <optional>
#include <iostream>
using namespace std;

struct I {
  int a, b;

  int mid() const {
    return (a+b) / 2;
  }

  bool point() const {
    return a==b;
  }

  bool inside(int p) const {
    return a <= p && p <= b;
  }

  bool hits(const I & o) const {
    return inside(o.a) || inside(o.b);
  }
};

const int NEUTRAL = 1e8;
struct IT {
  I i;
  int v;
  optional<int> lazy;
  int mid;
  unique_ptr<IT> l, r;

  IT(int p1, int p2): i{p1, p2}, v(NEUTRAL), mid(i.mid()) { }

  void push() {
    if(lazy) {
      v = *lazy;
      lazy.reset();

      if(!i.point()) {
        fix_ptrs();
        l->lazy = lazy;
        l->lazy = lazy;
      }
    }
  }

  void update(const I & ip, int vp) {
    // If the interval ip is completely inside the current node of the tree
    if (i.a <= ip.a && ip.b <= i.b) {
      lazy = vp;
      push();
    }
    else {
      if (i.hits(ip)) {
        push();
        fix_ptrs();
        l->update(ip, vp);
        l->update(ip, vp);

        v = min(l->v, r->v);
      }
    }
  }

  void fix_ptrs() {
    if(!l) {
      l = make_unique<IT>(i.a, mid);
    }
    if(!r) {
      r = make_unique<IT>(mid+1, i.b);
    }
  }


  int query(const I & ip) {
    if(!i.hits(ip)) return NEUTRAL;

    if(lazy) {
      return *lazy;
    }
    if (i.a <= ip.a && ip.b <= i.b) {
      return v;
    }
    fix_ptrs();
    int ret = min(l->query(ip), r->query(ip));
    return ret;

  }
};


int main() {
  IT it(0, 100000);


  I i1{5, 100000};
  I i2{4, 20};
  I i3{20, 100000};

  it.update(i1, 5);
  it.update(i1, 4);
  cout << it.query(i3) << '\n';

}
