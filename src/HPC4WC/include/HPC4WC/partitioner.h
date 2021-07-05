#pragma once
#include <HPC4WC/field.h>
#include <mpi.h>

#include <iostream>

// TODO: CHECK MPI ERRORS

namespace HPC4WC {

class Partitioner {
    using idx_t = Field::idx_t;
    using const_idx_t = Field::const_idx_t;
public:
    Partitioner(const_idx_t& ni, const_idx_t& nj, const_idx_t& nk, const_idx_t& num_halo);
    static void init(int argc, char* argv[]);
    static void finalize();

    FieldSPtr getField();
    FieldSPtr getGlobalField();
    void scatter();
    void gather();
    void haloExchange();

    const int rank() const;

private:
    std::pair<idx_t, idx_t> getLocalFieldSize(int rank);

    MPI_Comm m_comm;
    int m_numRanks;
    int m_rank;
    int m_dimSize[2] = {0, 0};
    FieldSPtr m_field;
    FieldSPtr m_globalField;
    const_idx_t m_ni, m_nj, m_num_halo;
};

}  // namespace HPC4WC