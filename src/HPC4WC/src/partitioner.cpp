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
    int my_coords[2];
    MPI_Cart_coords(m_comm,m_rank, 2, my_coords);
    if (m_rank == 0) {
        for (Field::idx_t k = 0; k < m_field->num_k(); k++) {
            for (int rank = 1; rank < m_numRanks; rank++) {
                auto localSizes = getLocalFieldSize(rank);
                std::vector<double> buf(localSizes.first*localSizes.second);
                Field::idx_t interior_ni, interior_nj; // if partitioning of domain is exactly possible, use this indices
                interior_ni = m_ni / m_dimSize[0];
                interior_nj = m_nj / m_dimSize[1];

                Field::idx_t start_row = (my_coords[0]-1)*interior_ni;
                Field::idx_t start_col = (my_coords[1]-1)*interior_nj;

                Field::idx_t idx = 0;
                for(Field::idx_t i=start_row;i<start_row+localSizes.first;++i){
                    for(Field::idx_t j=start_col;j<start_col+localSizes.second;++j){
                        buf[idx++] = m_globalField->operator()(i+m_num_halo,j+m_num_halo,k);
                    }
                }
                // send buf with its values to each rank
                MPI_Send(buf.data(),buf.size().second,MPI_DOUBLE,rank, k,m_comm);
            }
        }
        // copy over to fill in small data of rank 0
        auto localSizes = getLocalFieldSize(0);
        std::vector<double> buf(localSizes.first*localSizes.second);
        Field::idx_t interior_ni, interior_nj; // if partitioning of domain is exactly possible, use this indices
        interior_ni = m_ni / m_dimSize[0];
        interior_nj = m_nj / m_dimSize[1];

        Field::idx_t start_row = (my_coords[0]-1)*interior_ni;
        Field::idx_t start_col = (my_coords[1]-1)*interior_nj;
        for (Field::idx_t k = 0; k < m_field->num_k(); k++) {
            for(Field::idx_t i=start_row;i<start_row+localSizes.first;++i){
                for(Field::idx_t j=start_col;j<start_col+localSizes.second;++j){
                    m_field->operator()(i+m_num_halo-start_row,j+m_num_halo-start_col,k) = m_globalField->operator()(i+m_num_halo,j+m_num_halo,k);
                }
            }
        }
        
    }
    else{
        auto localSizes = getLocalFieldSize(m_rank);
        std::vector<double> buf(localSizes.first * localSizes.second);


        for(Field::idx_t k = 0; k < m_field->num_k(); k++){
            Field::idx_t idx=0;
            MPI_Recv(buf.data(),buf.size(),MPI_DOUBLE,0, k, m_comm);
            // unbpack buf into k plane
            for(Field::idx_t i = 0; i<localSizes.first;++i){
                for(Field::idx_t j = 0; j<localSizes.second;++j){
                    m_field->operator()(i+m_num_halo,j+m_num_halo,k) = buf[idx++];
                }
            }
        }
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