#include <boost/mp.hpp>
#include <ranges>

template <class... TRhs>
constexpr auto append() {
  return []<class... TLhs> { return boost::mp::type_list<TLhs..., TRhs...>{}; };
}

template <class... TRhs>
constexpr auto append(boost::mp::type_list<TRhs...>) {
  return []<class... TLhs> { return boost::mp::type_list<TLhs..., TRhs...>{}; };
}

template <auto N, class... Ns>
auto insert = []<class... Ts> {
  auto v = boost::mp::list<Ts...>();
  auto head = v | std::ranges::views::take(boost::mp::ct<N>);
  auto tail = v | std::ranges::views::drop(boost::mp::ct<N>);
  return boost::mp::type_list<>{} | append(head) | append<Ns...>() |
         append(tail);
};

static_assert((boost::mp::list<int, double, float>() | insert<1, short>) ==
              boost::mp::list<int, short, double, float>());

int main() {}