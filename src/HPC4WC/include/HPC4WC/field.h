#pragma once

#include <Eigen/Core>
#include <vector>

namespace HPC4WC {

/*
    A field. Holds data.
    @todo: Set storage order based on config!
 */
class Field {
public:
    using idx_t = int;
    using const_idx_t = const int;

    Field(const_idx_t& ni, const_idx_t& nj, const_idx_t& nk, const_idx_t& num_halo);

    Field(const Field&) = delete;
    Field() = delete;

    ~Field() {}

    /*
        Indexing:
        0/0 --> first point inside (NO HALO)
        -1/-1 --> halo corner (potentially more negative)
        ni-1/nj-1 --> last corner inside (NO HALO)
        ni/nj --> halo corner (potentially more positive)
    */
    double operator()(const_idx_t& i, const_idx_t& j, const_idx_t& k) const;
    double& operator()(const_idx_t& i, const_idx_t& j, const_idx_t& k);

    void setFrom(const Field&);
    void setFrom(const Eigen::MatrixXd& ij_plane, const_idx_t& k);
    void setFrom(const Eigen::MatrixXd& ij_plane_part, const_idx_t& i, const_idx_t& j, const_idx_t& k);

    const_idx_t num_i() const {
        return m_ni;
    }
    const_idx_t num_j() const {
        return m_nj;
    }
    const_idx_t num_k() const {
        return m_nk;
    }
    const_idx_t num_halo() const {
        return m_num_halo;
    }

private:
    idx_t m_ni;
    idx_t m_nj;
    idx_t m_nk;
    idx_t m_num_halo;

    std::vector<Eigen::MatrixXd> m_data;
};

}  // namespace HPC4WC