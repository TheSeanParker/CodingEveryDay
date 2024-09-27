template <int TreePos, int N> struct FibSlow_t {
    static constexpr auto value = FibSlow_t<TreePos, N - 1>::value +
                                  FibSlow_t<TreePos + (1 << N), N - 2>::value;
};

template <int TreePos> struct FibSlow_t<TreePos, 0> {
    static constexpr auto value = 0;
};
template <int TreePos> struct FibSlow_t<TreePos, 1> {
    static constexpr auto value = 1;
};

int fib25 = FibSlow_t<0, 25>::value;