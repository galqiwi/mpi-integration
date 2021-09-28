#pragma once
#include <mpi.h>
#include <cstddef>

struct Range {
    size_t from, to; // Range [from, to)
    static Range Receive() {
        unsigned long int packet[2];
        MPI_Status status;
        MPI_Recv(
            /* void *buf             (aka pointer to start) = */ &packet, // <--- объявлен после MPI_Init
            /* int count             (aka number of words)  = */ 2,
            /* MPI_Datatype datatype (aka word type)        = */ MPI_UNSIGNED_LONG,
            /* int source            (aka rank of sender)   = */ 0,
            /* int tag               (aka tag)              = */ 0,
            /* MPI_Comm comm         (aka communicator)     = */ MPI_COMM_WORLD,
            /* MPI_Status *status    (aka status of recv)   = */ &status
        );
        return {packet[0], packet[1]};
    }
    static void Send(Range range, int reciever_id) {
        unsigned long int packet[] = {range.from, range.to};
        MPI_Send(
            /* const void *buf       (aka pointer to start) = */ &packet,
            /* int count             (aka number of words)  = */ 2,
            /* MPI_Datatype datatype (aka word type)        = */ MPI_UNSIGNED_LONG,
            /* int dest              (aka rank of receiver) = */ reciever_id,
            /* int tag               (aka tag)              = */ 0,
            /* MPI_Comm comm         (aka communicator)     = */ MPI_COMM_WORLD
        );
    }
};

Range MakeDistributedRange(size_t N);