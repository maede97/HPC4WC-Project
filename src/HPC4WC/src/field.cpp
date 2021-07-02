#include <HPC4WC/field.h>

namespace HPC4WC {

Field::Field(const_idx_t& ni, const_idx_t& nj, const_idx_t& nk, const_idx_t& num_halo) : m_ni(ni), m_nj(nj), m_nk(nk), m_num_halo(num_halo) {
    m_data.resize(nk, Eigen::MatrixXd::Zero(ni + 2 * num_halo, nj + 2 * num_halo));
}

double Field::operator()(const_idx_t& i, const_idx_t& j, const_idx_t& k) const {
    return m_data[k](i + m_num_halo, j + m_num_halo);
}
double& Field::operator()(const_idx_t& i, const_idx_t& j, const_idx_t& k) {
    return m_data[k](i + m_num_halo, j + m_num_halo);
}

void Field::setFrom(const Field& other) {
    // TODO: check size!
    for (idx_t k = 0; k < m_nk; k++) {
        m_data[k] = other.m_data[k];
    }
}

void Field::setFrom(const Eigen::MatrixXd& ij_plane, const_idx_t& k) {
    m_data[k].block(m_num_halo, m_num_halo, m_ni, m_nj) = ij_plane;
}

void Field::setFrom(const Eigen::MatrixXd& ij_plane_part, const_idx_t& i, const_idx_t& j, const_idx_t& k) {
    m_data[k].block(m_num_halo + i, m_num_halo + j, ij_plane_part.rows(), ij_plane_part.cols()) = ij_plane_part;
}

}  // namespace HPC4WC