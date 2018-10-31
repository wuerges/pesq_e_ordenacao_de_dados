#include <vector>
#include <iostream>
using namespace std;





int binary_search(int k, vector<int> & vs) {
  int a = 0, b = vs.size() - 1;

  while(a != b) {
    int mid = (a + b) / 2;
    if(k > vs[mid]) {
      a = mid+1;
    }
    else {
      b = mid;
    }
  }
  if (vs[a] == k) return a;
  return -1;
};



int main() {
  vector<int> vs{1, 4, 8, 10, 20, 22};

  for(int k : vs) {
    cout << k << " ";
  }
  cout << '\n';
  for(int k : vs) {
    cout << (k-1) << " " << binary_search(k-1, vs) << '\n';
    cout << (k) << " " << binary_search(k, vs) << '\n';
    cout << (k+1) << " " << binary_search(k+1, vs) << '\n';
  }
}
