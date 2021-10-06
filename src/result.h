#pragma once
#include <mpi.h>

#include <iostream>

#include "utils.h"

struct Result {
  double value;
  static Result Receive(int sender_id) {
    double value;
    MPI_Status status;
    MPI_Recv(
        /* void *buf             (aka pointer to start) = */ &value,
        /* int count             (aka number of words)  = */ 1,
        /* MPI_Datatype datatype (aka word type)        = */ MPI_DOUBLE,
        /* int source            (aka rank of sender)   = */ sender_id,
        /* int tag               (aka tag)              = */ 0,
        /* MPI_Comm comm         (aka communicator)     = */ MPI_COMM_WORLD,
        /* MPI_Status *status    (aka status of recv)   = */ &status);
    return {value};
  }
  static Result Receive(int sender_id, Result my_result) {
    if (sender_id == 0) {
      return my_result;
    } else {
      return Receive(sender_id);
    }
  }
  static void Send(Result result) {
    MPI_Send(
        /* const void *buf       (aka pointer to start) = */ &result,
        /* int count             (aka number of words)  = */ 1,
        /* MPI_Datatype datatype (aka word type)        = */ MPI_DOUBLE,
        /* int dest              (aka rank of receiver) = */ 0,
        /* int tag               (aka tag)              = */ 0,
        /* MPI_Comm comm         (aka communicator)     = */ MPI_COMM_WORLD);
  }
  static std::optional<double> Merge(Result result) {
    auto [procid, num_procs] = utils::GetProcessInfo();

    if (procid == 0) {
      double integral = 0;
      for (int sender_id = 0; sender_id < num_procs; ++sender_id) {
        Result partial_result = Receive(sender_id, result);
        integral += partial_result.value;
        std::cout << "I[" << sender_id << "] = " << partial_result.value
                  << std::endl;
      }
      std::cout << "I = " << integral << std::endl;
      return integral;
    } else {
      Result::Send(result);
      return std::nullopt;
    }
  }
};