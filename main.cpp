#include <iostream>
#include <functional>
#include <mpi.h>

#include "result.h"
#include "range.h"
#include "crunching.h"
#include "utils.h"

int main(int argc, char *argv[]) {
    size_t N = 1e8;

    MPI_Init(&argc, &argv);

    utils::ExecuteInMain([&](){
        auto [procid, num_procs] = utils::GetProcessInfo();
        std::cout << "N = " << N << std::endl;
        std::cout << "p = " << num_procs << std::endl;
    });

    double multithread_integral;

    double multithread_time = utils::TimeIt([&](){
        Range my_range = MakeDistributedRange(N);

        Result result{crunching::ProcessRange(my_range, N)};

        auto integral = Result::Merge(result);
        if (integral.has_value()) {
            multithread_integral = integral.value();
        }
    });

    utils::ExecuteInMain([&](){
        double singlethread_integral;
        double singlethread_time = utils::TimeIt([&](){
            singlethread_integral = crunching::ProcessRange(Range{0, N + 1}, N);
        });
        std::cout << "I[singleprocess] = " << singlethread_integral << std::endl;
        std::cout << "multiprocessing relative error is " <<
        (multithread_integral - singlethread_integral) / singlethread_integral << std::endl;
        std::cout << "multiprocessing speedup is " << singlethread_time / multithread_time << std::endl;
    });

    MPI_Finalize();
    return 0;
}
