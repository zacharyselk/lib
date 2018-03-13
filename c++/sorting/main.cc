#include<vector>
#include "bubbleSort.h"

int main()
{
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
}
