#include <HPC4WC/partitioner.h>

#include <iostream>

namespace HPC4WC {

Partitioner::Partitioner(Field::const_idx_t& ni, Field::const_idx_t& nj, Field::const_idx_t& nk, Field::const_idx_t& num_halo) {
    MPI_Comm_size(MPI_COMM_WORLD, &m_nnodes);
    MPI_Comm_rank(MPI_COMM_WORLD, &m_rank);

    MPI_Dims_create(m_nnodes, 2, m_dimSize);

    int periods[2] = {1, 1};
    int reorder = 1;

    MPI_Cart_create(MPI_COMM_WORLD, 2, m_dimSize, periods, reorder, &m_comm);
    int coords[2];
    MPI_Cart_coords(m_comm, m_rank, 2, coords);

    if (m_rank == 0) {
        m_globalField = std::make_shared<Field>(ni, nj, nk, num_halo);
    }

    Field::idx_t local_ni, local_nj;
    local_ni = ni / m_dimSize[0];
    local_nj = nj / m_dimSize[1];
    if (coords[0] == m_dimSize[0] - 1) {
        local_ni = ni - (m_dimSize[0] - 1) * local_ni;
    }
    if (coords[1] == m_dimSize[1] - 1) {
        local_nj = nj - (m_dimSize[1] - 1) * local_nj;
    }

    m_field = std::make_shared<Field>(local_ni, local_nj, nk, num_halo);
}

void Partitioner::init(int argc, char* argv[]) {
    MPI_Init(&argc, &argv);
}

void Partitioner::finalize() {
    MPI_Finalize();
}

FieldSPtr Partitioner::getField() {
    return m_field;
}

FieldSPtr Partitioner::getGlobalField() {
    return m_globalField;
}

void Partitioner::scatter() { /* do stuff */
}
void Partitioner::gather() { /* do stuff */
}
void Partitioner::haloExchange() { /* do stuff */
}

const int Partitioner::rank() const {
    return m_rank;
}

}  // namespace HPC4WC