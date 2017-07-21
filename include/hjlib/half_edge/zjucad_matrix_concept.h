#ifndef ZJUCAD_MATRIX_CONCEPT_H
#define ZJUCAD_MATRIX_CONCEPT_H

#include <zjucad/matrix/matrix.h>

namespace hj
{
namespace half_edge
{

//get row numbers
template <typename M>
size_t get_row_numbers(const zjucad::matrix::matrix_expression<M> & m)
{
  return m().size(1);
}


//get column numbers
template <typename M>
size_t get_col_numbers(const zjucad::matrix::matrix_expression<M> & m)
{
  return m().size(2);
}

//get maximum coeffcient
template <typename M>
typename M::value_type get_max_coef(const zjucad::matrix::matrix_expression<M> & m)
{
  return max(m());
}

//get minimum coeffcient
template <typename M>
typename M::value_type get_min_coef(const zjucad::matrix::matrix_expression<M> & m)
{
  return m().size(2);
}

template <typename M>
M get_mat(const zjucad::matrix::matrix_expression<M> & m)
{
  return m();
}

template <typename M>
void resize_container(zjucad::matrix::matrix_expression<M> & con, size_t row, size_t col = 1)
{
  con().resize(row, con);
}

}//namespace half_edge
}//namespace hj

#endif
