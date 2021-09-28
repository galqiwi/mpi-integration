#include "utils.h"

#include <mpi.h>

namespace utils {

void ExecuteInMain(std::function<void()> function) {
  auto [procid, num_procs] = GetProcessInfo();

  if (procid == 0) {
    function();
  }
}

double TimeIt(std::function<void()> function) {
  double start_time = MPI_Wtime();
  function();
  double end_time = MPI_Wtime();
  return end_time - start_time;
}

std::pair<size_t, size_t> GetProcessInfo() {
  int procid, num_procs;
  MPI_Comm_rank(MPI_COMM_WORLD, &procid);
  MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
  return {procid, num_procs};
}

}  // namespace utils