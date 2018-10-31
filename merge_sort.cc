#include <vector>
#include <iostream>
using namespace std;

const int INF = 1e8;


void swap(int & a, int & b) {
  int c = a;
  a = b;
  b = c;
}


void bubble_sort(vector<int> & vs) {
  for(int i = 0; i < vs.size(); ++i) {
    for(int j = 0; j < vs.size()-1; ++j) {
      if(vs[j] > vs[j+1]) {
        swap(vs[j], vs[j+1]);
      }
    }
  }
};

void merge_sort(vector<int> & vs, int a=0, int b = -1) {
  if(b < 0) b = vs.size() -1;

  if(b == a) {
    return;
  }
  if(b == a+1) {
    if(vs[a] > vs[b]) swap(vs[a], vs[b]);
    return;
  }

  int mid = (a + b) / 2;
  merge_sort(vs, a, mid);
  merge_sort(vs, mid+1, b);

  int ia = a;


  vector<int> aux(b-a+1);
  int li = a, ri = mid+1;
  for(int i = 0; i < aux.size(); ++i) {
    int va = li <= mid ? vs[li] : INF;
    int vb = ri <= b ? vs[ri] : INF;
    if(va < vb) {
      aux[i] = va;
      li++;
    }
    else {
      aux[i] = vb;
      ri++;
    }
  }

  for(int i = 0; i < aux.size(); ++i) {
    vs[ia+i] = aux[i];
  }

};



int main() {
  vector<int> vs{ 4, 5, 3, 12, 8, 2, 10, 20, 22};
  // vector<int> vs{ 2, 1, 0 };

  for(int k : vs) {
    cout << k << " ";
  }
  cout << '\n';

  merge_sort(vs);

  for(int k : vs) {
    cout << k << " ";
  }
  cout << '\n';
}
