#include "range.h"

#include <mpi.h>

#include "utils.h"

Range MakeDistributedRange(size_t N) {
  auto [procid, num_procs] = utils::GetProcessInfo();

  if (procid == 0) {
    for (int reciever_id = 1; reciever_id < num_procs; ++reciever_id) {
      Range::Send(
          Range{
              (N + 1) * reciever_id / num_procs,
              (N + 1) * (reciever_id + 1) / num_procs,
          },
          reciever_id);
    }

    return {0, (N + 1) / num_procs};
  } else {
    return Range::Receive();
  }
}