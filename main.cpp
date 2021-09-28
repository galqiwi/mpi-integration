#include <mpi.h>

#include <functional>
#include <iostream>

#include "crunching.h"
#include "range.h"
#include "result.h"
#include "utils.h"

int main(int argc, char* argv[]) {
  size_t n = 1e8;

  MPI_Init(&argc, &argv);

  utils::ExecuteInMain([&]() {
    auto [procid, num_procs] = utils::GetProcessInfo();
    std::cout << "n = " << n << std::endl;
    std::cout << "p = " << num_procs << std::endl;
  });

  double multithread_integral;

  double multithread_time = utils::TimeIt([&]() {
    Range my_range = MakeDistributedRange(n);

    Result result{crunching::ProcessRange(my_range, n)};

    auto integral = Result::Merge(result);
    if (integral.has_value()) {
      multithread_integral = integral.value();
    }
  });

  utils::ExecuteInMain([&]() {
    std::cout << "Time = " << multithread_time << "s" << std::endl;
  });

  MPI_Finalize();
  return 0;
}
