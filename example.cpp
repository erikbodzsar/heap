#include <iostream>
#include <string>
#include <map>
#include "heap.hpp"

using namespace std;

int main() {
  heap<string, int> h;

  h.insert("a", 0);
  h.insert("b", 2);
  h.insert("c", 1);
  h.update("c", -2);

  cout << "min heap:" << endl;
  while (!h.empty()) {
    pair<string, int> i = h.get_min();
    h.pop_min();
    cout << i.first << " " << i.second << endl;
  }

  // ---
  cout << endl;

  heap<string, int, greater<int> > h_reverse;

  h_reverse.insert("a", 0);
  h_reverse.insert("b", 2);
  h_reverse.insert("c", 1);
  h_reverse.update("c", -2);

  cout << "max heap:" << endl;
  while (!h_reverse.empty()) {
    pair<string, int> i = h_reverse.get_min();
    h_reverse.pop_min();
    cout << i.first << " " << i.second << endl;
  }

  return 0;
}
