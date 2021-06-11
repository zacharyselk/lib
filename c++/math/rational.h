#pragma once

#include <utility>
#include <iosfwd>

namespace z {

template<typename T>
class Rational {
public:
  constexpr Rational() : numerator(0), denominator(1) {}
  constexpr Rational(T n) : numerator(n), denominator(1) {}
  constexpr Rational(T n, T d) : numerator(n), denominator(d) { if (denominator < 0) { numerator *= -1; denominator *= -1; } simplify(); }

  constexpr T getNumerator() const { return numerator; }
  constexpr T getDenominator() const { return denominator; }

  constexpr explicit operator float() const { return static_cast<float>(numerator) / static_cast<float>(denominator); }

  constexpr explicit operator double() const { return static_cast<double>(numerator) / static_cast<double>(denominator); }

  constexpr explicit operator bool() const { return numerator != 0; }

  //constexpr operator Rational<unsigned long long>() const { return {numerator, denominator}; }

  constexpr Rational<T> &simplify() {
    T divisor = gcd(numerator, denominator);
    numerator /= divisor;
    denominator /= divisor;
    return *this;
  } 

  constexpr Rational<T> &invert() {
    if (numerator < 0) {
      numerator *= -1;
      denominator *= -1;
    } 
    std::swap(numerator, denominator);
    return this->simplify();
  }

  constexpr friend Rational<T> inverse(const Rational<T> &r) {
    return {r.denominator, r.numerator};
  }

  constexpr Rational<T> &operator=(const T &rhs) {
    numerator = rhs;
    denominator = 1;
    return *this;
  }

  constexpr bool operator==(const Rational<T> &rhs) const {
    return numerator == rhs.numerator && denominator == rhs.denominator;
  }

  constexpr bool operator!=(const Rational<T> &rhs) const {
    return !((*this) == rhs);
  }

  constexpr bool operator<(const Rational<T> &rhs) const {
    return numerator * rhs.denominator < denominator *rhs.numerator;
  }

  constexpr bool operator<=(const Rational<T> &rhs) const {
    return (*this) < rhs || (*this) == rhs;
  }

  constexpr bool operator>(const Rational<T> &rhs) const {
    return !((*this) <= rhs);
  }

  constexpr bool operator>=(const Rational<T> &rhs) const {
    return (*this) == rhs || (*this) > rhs;
  }

  constexpr Rational<T> &operator+=(const Rational<T> &rhs) {
    numerator = numerator*rhs.denominator + rhs.numerator*denominator;
    denominator = denominator * rhs.denominator;
    return this->simplify();
  }

  constexpr Rational<T> &operator-=(const Rational<T> &rhs) {
    return (*this) += (-rhs);
  }

  constexpr Rational<T> &operator*=(const Rational<T> &rhs) {
    numerator *= rhs.numerator;
    denominator *= rhs.denominator;
    return this->simplify();
  }

  constexpr Rational<T> &operator/=(const Rational<T> &rhs) {
    return (*this) *= inverse(rhs);
  }

  constexpr friend Rational<T> operator-(const Rational<T> &rhs) {
    return {-rhs.numerator, rhs.denominator};
  }

  constexpr friend Rational<T> operator+(const Rational<T> &lhs, const Rational<T> &rhs) {
    T n = lhs.numerator*rhs.denominator + rhs.numerator*lhs.denominator;
    T d = lhs.denominator * rhs.denominator;
    return {n, d};
  }

  constexpr friend Rational<T> operator-(const Rational<T> &lhs, const Rational<T> &rhs) {
    return lhs + (-rhs);
  }

  constexpr friend Rational<T> operator*(const Rational<T> &lhs, const Rational<T> &rhs) {
    T n = lhs.numerator * rhs.numerator;
    T d = lhs.denominator * rhs.denominator;
    return {n, d};
  }

  constexpr friend Rational<T> operator/(const Rational<T> &lhs, const Rational<T> &rhs) {
    return lhs * inverse(rhs);
  }

  constexpr friend std::ostream &operator<<(std::ostream &os, const Rational<T> &val) {
    return os << val.numerator << "/" << val.denominator;
  }
  
 private:
  T numerator, denominator;

  constexpr static T gcd(T a, T b) {
    return b ? gcd(b, a%b) : a;
  }
};

} // namespace z
