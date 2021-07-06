#include <HPC4WC/field.h>

#include <stdexcept>

namespace HPC4WC {

Field::Field(const_idx_t& ni, const_idx_t& nj, const_idx_t& nk, const_idx_t& num_halo) : m_ni(ni), m_nj(nj), m_nk(nk), m_num_halo(num_halo) {
    m_data.resize(nk, Eigen::MatrixXd::Zero(ni + 2 * num_halo, nj + 2 * num_halo));
}

Field::Field(const_idx_t& ni, const_idx_t& nj, const_idx_t& nk, const_idx_t& num_halo, const double& value)
    : m_ni(ni), m_nj(nj), m_nk(nk), m_num_halo(num_halo) {
    m_data.resize(nk, Eigen::MatrixXd::Constant(ni + 2 * num_halo, nj + 2 * num_halo, value));
}

double Field::operator()(const_idx_t& i, const_idx_t& j, const_idx_t& k) const {
    if (k < 0 || k >= m_data.size() || i < 0 || i >= m_data[k].rows() || j < 0 || j >= m_data[k].cols()) {
        throw std::out_of_range("double Field::operator()(i, j, k): out of bounds.");
    }
    return m_data[k](i, j);
}
double& Field::operator()(const_idx_t& i, const_idx_t& j, const_idx_t& k) {
    if (k < 0 || k >= m_data.size() || i < 0 || i >= m_data[k].rows() || j < 0 || j >= m_data[k].cols()) {
        throw std::out_of_range("double& Field::operator()(i, j, k): out of bounds.");
    }
    return m_data[k](i, j);
}

void Field::setFrom(const Field& other) {
    if (m_nk != other.m_nk || m_ni != other.m_ni || m_nj != other.m_nj || m_num_halo != other.m_num_halo) {
        throw std::logic_error("Field::setFrom(other): Sizes do not match.");
    }
    for (idx_t k = 0; k < m_nk; k++) {
        m_data[k] = other.m_data[k];
    }
}

void Field::setFrom(const Eigen::MatrixXd& ij_plane_part, const_idx_t& i, const_idx_t& j, const_idx_t& k) {
    m_data[k].block(i, j, ij_plane_part.rows(), ij_plane_part.cols()) = ij_plane_part;
}

}  // namespace HPC4WC