#include <HPC4WC/partitioner.h>

#include <iostream>

namespace HPC4WC {

Partitioner::Partitioner(Field::const_idx_t& ni, Field::const_idx_t& nj, Field::const_idx_t& nk, Field::const_idx_t& num_halo) : m_ni(ni), m_nj(nj), m_num_halo(num_halo) {
    MPI_Comm_size(MPI_COMM_WORLD, &m_numRanks);
    MPI_Comm_rank(MPI_COMM_WORLD, &m_rank);

    MPI_Dims_create(m_numRanks, 2, m_dimSize);

    int periods[2] = {1, 1};
    int reorder = 1;

    MPI_Cart_create(MPI_COMM_WORLD, 2, m_dimSize, periods, reorder, &m_comm);

    auto local_size = getLocalFieldSize(m_rank);

    m_field = std::make_shared<Field>(local_size.first, local_size.second, nk, m_num_halo);

    if (m_rank == 0) {
        m_globalField = std::make_shared<Field>(m_ni, m_nj, nk, m_num_halo);
    }
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

void Partitioner::scatter() { 
    if (m_rank == 0) {
        for (Field::idx_t k = 0; k < m_field->num_k(); k++) {
            auto localSizes = getLocalFieldSize(0);
            //*m_field.get()[k].block(0, 0, localSizes.first, localSizes.second);

            
            for (int i = 1; i < m_numRanks; i++) {
                localSizes = getLocalFieldSize(i);
                std::vector<double> buf(localSizes.first*localSizes.second);
            }
        }
    }
    else 
    {
        auto localSizes = getLocalFieldSize(m_rank);
        std::vector<double> buf(localSizes.first * localSizes.second);
    }
}
void Partitioner::gather() { /* do stuff */
}
void Partitioner::haloExchange() { /* do stuff */
}

const int Partitioner::rank() const {
    return m_rank;
}

std::pair<Field::idx_t, Field::idx_t> Partitioner::getLocalFieldSize(int rank)
{
    int coords[2];
    MPI_Cart_coords(m_comm, rank, 2, coords);

    Field::idx_t local_ni, local_nj;
    local_ni = m_ni / m_dimSize[0];
    local_nj = m_nj / m_dimSize[1];
    if (coords[0] == m_dimSize[0] - 1) {
        local_ni = m_ni - (m_dimSize[0] - 1) * local_ni;
    }
    if (coords[1] == m_dimSize[1] - 1) {
        local_nj = m_nj - (m_dimSize[1] - 1) * local_nj;
    }
    return std::make_pair(local_ni, local_nj);
}

}  // namespace HPC4WC