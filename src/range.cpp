#include "range.h"

#include "utils.h"

Range MakeDistributedRange(size_t N) {
  auto [procid, num_procs] = utils::GetProcessInfo();

  if (procid == 0) {
    for (int receiver_id = 1; receiver_id < num_procs; ++receiver_id) {
      Range::Send(
          Range{
              (N + 1) * receiver_id / num_procs,
              (N + 1) * (receiver_id + 1) / num_procs,
          },
          receiver_id);
    }

    return {0, (N + 1) / num_procs};
  } else {
    return Range::Receive();
  }
}