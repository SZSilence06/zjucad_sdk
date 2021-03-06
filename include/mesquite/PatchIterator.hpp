/* ***************************************************************** 
    MESQUITE -- The Mesh Quality Improvement Toolkit

    Copyright 2006 Lawrence Livermore National Laboratory.  Under 
    the terms of Contract B545069 with the University of Wisconsin -- 
    Madison, Lawrence Livermore National Laboratory retains certain
    rights in this software.

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License 
    (lgpl.txt) along with this library; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

    (2006) kraftche@cae.wisc.edu    

  ***************************************************************** */

#ifndef MSQ_PATCH_ITERATOR_HPP
#define MSQ_PATCH_ITERATOR_HPP

#include "Mesquite.hpp"
#include "PatchSet.hpp"

namespace MESQUITE_NS {

class PatchData;
class MsqError;

class PatchIterator {
public:
  
  inline PatchIterator( PatchSet* set ) 
    : patchSet(set)
    {}
  
  bool get_next_patch( PatchData&, MsqError& err );
  
  PatchSet* get_patch_set() const { return patchSet; }
  
  void reset(); //!< reset current position to beginning o
  
private:

  PatchSet* patchSet;
  
  std::vector<PatchSet::PatchHandle> patches;
  std::vector<Mesh::ElementHandle> elems;
  std::vector<Mesh::VertexHandle> verts;
  std::vector<PatchSet::PatchHandle>::iterator current;
};

} // namespace Mesquite

#endif
