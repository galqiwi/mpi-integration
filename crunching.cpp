#include "crunching.h"

namespace crunching {

inline double integral_function(double x) {
  return 4 / (1 + x * x);
}

double ProcessRange(Range range, size_t N) {
  double out{0};

  double start_value = integral_function((double)range.from / ((double)N));
  for (size_t subrange_id = range.from; subrange_id < range.to; ++subrange_id) {
    double end_value =
        integral_function((double)(subrange_id + 1) / ((double)N));
    out += (start_value + end_value) / ((double)(2 * N));
    std::swap(start_value, end_value);
  }
  return out;
}

}  // namespace crunching