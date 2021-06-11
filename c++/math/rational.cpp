#include <iostream>
#include "rational.h"

#define TEST_OP(lhs, op, rhs) check<decltype(lhs), decltype(rhs)>(lhs op rhs, lhs, rhs, #op, __FILE__, __LINE__)
#define TEST_EQ(lhs, rhs) check<decltype(lhs), decltype(rhs)>(lhs == rhs, lhs, rhs, "==", __FILE__, __LINE__)

template<typename T, typename U>
int check(bool result, const T &lhs, const U &rhs, const char* operation, const char* file, const int line) {
  if (result == false) {
    std::cerr << file << ':' << line << ". Error \"" << lhs << ' ' << operation << ' ' << rhs << "\" resolved as false\n";
    return 1;
  } else {
    return 0;
  }
}

int main() {
  int errors{};
  z::Rational<int> a(1, 2), b(1, 2), c(1, 3);
  auto d = a + b;

  errors += TEST_OP(a, ==, b);
  errors += TEST_OP(b, ==, a);
  errors += TEST_OP(a, !=, c);
  errors += TEST_OP(c, !=, a);
  errors += TEST_OP(a, <=, b);
  errors += TEST_OP(a*b, >, a*c);
  errors += TEST_EQ(a, b);
  errors += TEST_EQ(b*c, c*b);
  errors += TEST_EQ(c*3, d);
  errors += TEST_EQ(d*3, inverse(c));
  errors += TEST_EQ(d*3, 1/c);

  if (errors > 0) {
    std::cout << "Failed: " << errors << " Errors found\n";
  } else {
    std::cout << "Passed\n";
  }

  return 0;
}
