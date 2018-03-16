#include <iostream>
#include <vector>
#include "bubbleSort.h"

int main()
{
  int len;
  
  int a[5] = {5,4,3,2,1};
  bubbleSort(a[0], a[4], true);

  std::vector<int> b;
  for(int i = 5; i >= 0; --i)
    b.push_back(i);
  bubbleSort(b[0], b[4], true);

  std::string c = "Hello World";
  bubbleSort(c[0], c[c.length()-1], true);

  // Does not work
  /*
  std::vector<double> d;
  d.push_back(343.432);
  d.push_back(32.2);
  d.push_back(45);
  d.push_back(3.25);
  d.push_back(3453.3);
  bubbleSort(d.begin(), d.end(), true);
  */

  // Does not work
  /*
  int e[5] = {4,6,2,78,1};
  int* ePtrBegin = &e[0];
  int* ePtrEnd   = &e[4];
  bubbleSort(ePtrBegin, ePtrEnd, true);
  */

  len = 4;
  int f[len] = {3,6,1,2};

  std::cout << "Simple Bubblesort on:\n";
  for(int i = 0; i < len; ++i)
    std::cout << f[i] << ' ';
  std::cout << "\n\n";
  
  bubbleSort_simple(f, len);

  std::cout << "Final array:\n";
  for(int i = 0; i < len; ++i)
    std::cout << f[i] << ' ';
  std::cout << "\n\n";
}
