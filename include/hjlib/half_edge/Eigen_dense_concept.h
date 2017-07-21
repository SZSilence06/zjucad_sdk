#ifndef EIGEN_DENSE_CONCEPT_H
#define EIGEN_DENSE_CONCEPT_H

#include <Eigen/Geometry>
#include <Eigen/Core>

namespace hj
{
namespace half_edge
{
//get row numbers
template <typename M>
size_t get_row_numbers(const Eigen::DenseBase<M> & m)
{
  return m.rows();
}


//get column numbers
template <typename M>
size_t get_col_numbers(const Eigen::DenseBase<M> & m)
{
  return m.cols();
}

//get maximum coeffcient
template <typename M>
typename Eigen::internal::traits<M>::Scalar get_max_coef(const Eigen::DenseBase<M> & m)
{
  return m.maxCoeff();
}

//get minimum coeffcient
template <typename M>
typename Eigen::internal::traits<M>::Scalar get_min_coef(const Eigen::DenseBase<M> & m)
{
  return m.minCoeff();
}

template <typename M>
M get_mat(const Eigen::DenseBase<M> & m)
{
  return m;
}

template <typename M>
void resize_container(Eigen::DenseBase<M> & con, size_t row, size_t col = 1)
{
  con.resize(row, col);
}
/*
template <typename PM, typename ME>
void assign_property(PM & p, const ME & m)
{
  size_t idx = 0;
  for(auto i = m.verts().begin(); i != m.verts().end(); ++i, ++idx)
  {
    for (size_t i=0; i<m[i].coord_.size(); ++i)
    {
      //assign(m[i].coord_, nods(colon(), idx));
      
    }
  }
}
//*/


}//namespace half_edge
}//namespace hj

#endif
