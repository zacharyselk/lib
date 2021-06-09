#include <functional>
#include <iterator>
#include <type_traits>

namespace z {

template<typename BidIt, typename Comp>
void insertionSort(BidIt begin, BidIt end, Comp comparitor) {
  // Return early if array is of lenth 0 or 1.
  if (begin == end || std::next(begin) == end) {
    return;
  }

  for (auto cur = std::next(begin); cur != end; ++cur) {
    auto key = *cur;
    BidIt other(cur);
    while (other != begin && comparitor(key, *std::prev(other))) {
      *other = *std::prev(other);
      --other;
    }
    *other = key;
  }
}

template<typename BidIt>
void insertionSort(BidIt begin, BidIt end) {
  using value_type = typename std::iterator_traits<BidIt>::value_type;
  insertionSort(begin, end, std::less<value_type>());
}

} // namespace z
