#ifndef HJ_HALF_EDGE_BUILDER_H_
#define HJ_HALF_EDGE_BUILDER_H_

//! @file half_edge.h
//! @brief build a half_edge data structure from various inputs
//! @author Jin Huang
//! @date 201406-

#include <vector>
#include <cassert>
#include <map>
#include <algorithm>
#include <stdexcept>

#ifdef EIGEN_WORLD_VERSION
#include "Eigen_dense_concept.h"
#endif

#ifdef ZJUCAD_MATRIX_VERSION
#include "zjucad_matrix_concept.h"
#endif

#include "half_edge.h"

namespace hj { namespace half_edge {

template <typename ME>
class mat_builder
{
public:
  mat_builder(const ME &cells) :cells_(cells){}
  const ME &cells_;
};

//! @assume cells code the face list of a triangular manifold, throw
//! exception for non-manifold.
template <typename ME>
mat_builder<ME>
build_topology(const ME &cells);


template <typename ME>
class mat_builder_with_id
{
public:
  mat_builder_with_id(const ME &cells) :cells_(cells){}
  const ME &cells_;
};

//! @assume cells code the face list of a triangular manifold, throw
//! exception for non-manifold.
template <typename ME>
mat_builder_with_id<ME>
build_with_id(const ME &cells);

#include "builder.hh"

}}

#endif
