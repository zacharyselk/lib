#include <functional>
#include <iterator>
#include <type_traits>

namespace z {

template<typename BidIt, typename Comp>
void bubbleSort(BidIt begin, BidIt end, Comp comparitor) {
  auto rBegin(end);
  for (auto start = begin; start != std::prev(end); ++start) {
    for (auto finish = std::prev(end); finish != start; --finish) {
      if (*finish < *std::prev(finish)) {
        std::swap(*finish, *std::prev(finish));
      }
    }
  }
}

template<typename BidIt>
void bubbleSort(BidIt begin, BidIt end) {
  using value_type = typename std::iterator_traits<BidIt>::value_type;
  bubbleSort(begin, end, std::less<value_type>());
}

} // namespace z
