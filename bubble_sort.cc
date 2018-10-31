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



int main() {
  vector<int> vs{ 4, 5, 3, 12, 8, 2, 10, 20, 22};

  for(int k : vs) {
    cout << k << " ";
  }
  cout << '\n';

  bubble_sort(vs);

  for(int k : vs) {
    cout << k << " ";
  }
  cout << '\n';
}
