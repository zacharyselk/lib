#pragma once

#include <array>
#include <string>
#include <sstream>


/// @brief An abstract class used as the genaric interface when formating.
///
/// This parent abstract class is used to create a genaric interface that can be
/// used for type erasure while allowing for each type to be converted to a
/// string.
class CommonFormatType {
public:
  virtual ~CommonFormatType() = default;
  virtual std::string toString() = 0;
};

/// @brief The genaric implementation of a CommonFormatType used as default.
template<typename T>
class SomeFormatType : public CommonFormatType {
public:
  SomeFormatType(T t) : data(t) {}
  virtual std::string toString() override {
    std::stringstream ss;
    ss << data;
    return ss.str();
  }

private:
  T data;
};

/// @brief Adapts a given piece of data into an arbitrary FormatType object.
template<typename T>
std::unique_ptr<CommonFormatType> buildType(T &&data) {
  return std::make_unique<SomeFormatType<T>>(data);
}


class AbstractFormatObj {
public:
  virtual ~AbstractFormatObj() = default;
  virtual std::string format(const std::string&) = 0;
};

template<typename... Ts>
class WrappedFormatObj : public AbstractFormatObj {
public:
  std::array<std::unique_ptr<CommonFormatType>, sizeof...(Ts)> data;

  constexpr auto createArray(Ts &&... values) 
    -> std::array<std::unique_ptr<CommonFormatType>, sizeof...(Ts)> {
    return { buildType(std::forward<Ts>(values))... };
  }

  int toInt(const std::string &str) {
    const char* string = str.c_str();
    int len = str.size();
    int sign = 1;
    switch (*string) {
      case '-':
        sign = -1;
      case '+':
        ++string;
        --len;
    }

    int val = 0;
    switch (len) {
      case 10: val += (*(string++) - '0') * 1000000000;
      case 9: val += (*(string++) - '0') * 100000000;
      case 8: val += (*(string++) - '0') * 10000000;
      case 7: val += (*(string++) - '0') * 1000000;
      case 6: val += (*(string++) - '0') * 100000;
      case 5: val += (*(string++) - '0') * 10000;
      case 4: val += (*(string++) - '0') * 1000;
      case 3: val += (*(string++) - '0') * 100;
      case 2: val += (*(string++) - '0') * 10;
      case 1: val += *(string++) - '0';
    }

    return val*sign;
  }


  explicit WrappedFormatObj(Ts &&... values) : data(createArray(std::forward<Ts>(values)...)) {}
  virtual std::string format(const std::string &str) {
    std::string formattedString;
    for (size_t i = 0, j = 0; i < str.size(); ++i) {
      if (str[i] == '{') {
        std::string formattingString;
        while (str[++i] != '}') formattingString.push_back(str[i]);
        if (formattingString.size() > 0) {
          auto val = toInt(formattingString);
          formattedString.append(data[val]->toString());
        } else {
          formattedString.append(data[j++]->toString());
        }
        
      } else {
        formattedString.push_back(str[i]);
      }

    }
    return formattedString;
  }
};

class FormatObj {
public:
  std::unique_ptr<AbstractFormatObj> ptr;

  template<typename... Ts>
  FormatObj(Ts &&... values) {
    ptr = std::make_unique<WrappedFormatObj<Ts...>>(std::forward<Ts>(values)...);
  }

  std::string format(const std::string &str) {
    return ptr->format(str);
  }
};

template<typename... Ts>
std::string formatString(std::string str, Ts &&... args) {
  FormatObj obj(std::forward<Ts>(args)...);
  
  return obj.format(str);
}
