
#include <vector>
#include <iostream>
using namespace std;



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

  cout << "a=" << a << '\n';
  cout << "b=" << b << '\n';
  for(int k : vs) {
    cout << k << " ";
  }
  cout << '\n';


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
  for(int i = 0; i < aux.size(); ++i) {
    if(vs[a] < vs[b]) {
      aux[i] = vs[a];
      a++;
    }
    else {
      aux[i] = vs[b];
      b++;
    }
  }

  cout << "aux: ";
  for(int k : aux) {
    cout << k << ' ';
  }
  cout << '\n';

  for(int i = 0; i < aux.size(); ++i) {
    vs[ia+i] = aux[i];
  }

};



int main() {
  vector<int> vs{ 4, 5, 3, 12, 8, 2, 10, 20, 22};

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
