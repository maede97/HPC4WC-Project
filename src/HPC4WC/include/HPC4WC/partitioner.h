#pragma once
#include <HPC4WC/field.h>
#include <mpi.h>

#include <iostream>

// TODO: CHECK MPI ERRORS

namespace HPC4WC {

class Partitioner {
public:
    Partitioner(Field::const_idx_t& ni, Field::const_idx_t& nj, Field::const_idx_t& nk, Field::const_idx_t& num_halo);
    static void init(int argc, char* argv[]);
    static void finalize();

    FieldSPtr getField();
    FieldSPtr getGlobalField();
    void scatter();
    void gather();
    void haloExchange();

    const int rank() const;

private:
    MPI_Comm m_comm;
    int m_nnodes;
    int m_rank;
    int m_dimSize[2] = {0, 0};
    FieldSPtr m_field;
    FieldSPtr m_globalField;
};

}  // namespace HPC4WC