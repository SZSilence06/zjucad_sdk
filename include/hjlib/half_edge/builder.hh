template <typename ME>
mat_builder<ME>
build_topology(const ME &cells) {
  return mat_builder<ME>(cells);
}

template <typename TMPL, typename ME>
void
assign(mesh_tmpl<TMPL> &mt, const mat_builder<ME> &b)
{
  assign_from_mat(mt, b.cells_);
  //assign_from_mat_with_addface(mt, b.cells_);
}

//! @assume triangular manifold
template <typename TMPL, typename ME>
void
assign_from_mat(mesh_tmpl<TMPL> &mt, const ME &cellst)
{
  using namespace std;
  
  typedef TMPL mesh_t;
  typedef ME matrix_t;  
  typedef typename mesh_t::verts_t::const_iterator CVI;
  typedef typename mesh_t::edges_t::const_iterator CEI;
  
  mesh_t &m = mt();
  const matrix_t &cells = get_mat(cellst);
  
  assert(get_row_numbers(cells) == 3);
  //insert vert
  const size_t vert_num = get_max_coef(cells) + 1;
  
  std::vector<CVI> vis(vert_num);
  for(size_t vi = 0; vi < vert_num; ++vi)
    vis[vi] = m.add(typename mesh_t::vert_t());

  // insert (inner) edges and face without set oppo
  vector<map<size_t, CEI> > adj_map(vert_num); // adj_map[from][to] = he

  for(size_t fi = 0; fi < get_col_numbers(cells); ++fi) {
    typename TMPL::faces_t::const_iterator f = m().add(typename TMPL::face_t());
    typedef std::vector<typename TMPL::edges_t::const_iterator> e_con;
    e_con edges;
    edges.reserve(get_row_numbers(cells));
    
    // insert
    for(size_t ei = 0; ei < get_row_numbers(cells); ++ei)
      edges.push_back(m().add(typename TMPL::edge_t()));
    // set edge and vert, init map
    for(size_t ei = 0; ei < get_row_numbers(cells); ++ei) {
      if(!vis[cells(ei, fi)]->edge())
        m[vis[cells(ei, fi)]].edge() = edges[ei];

      m[edges[ei]].vert() = vis[cells(ei, fi)];
      m[edges[ei]].face() = f;
      m[edges[ei]].next() = edges[(ei+1)%edges.size()];
      m[edges[ei]].prev() = edges[(edges.size()+ei-1)%edges.size()];

      const size_t from = cells(ei, fi), to = cells((ei+1)%get_row_numbers(cells), fi);
      auto loc = adj_map[from].find(to);
      if(loc != adj_map[from].end()) {
        char error[256];
        sprintf(error, "in assign_from_mat: duplicated edge from %ld to %ld.", from, to);
        throw std::runtime_error(error);
      }
      else
        adj_map[from].insert(loc, make_pair(to, edges[(ei+1)%get_row_numbers(cells)]));
    }
    // set face
    m[f].edge() = edges[0];
  }

  // add boundary edges and set oppo
  for(size_t vi = 0; vi < adj_map.size(); ++vi) {
    for(typename map<size_t, CEI>::const_iterator vjj = adj_map[vi].begin();
        vjj != adj_map[vi].end(); ++vjj) {
      const size_t vj = vjj->first;
      assert(vi != vj);
      CEI &oppo = adj_map[vj][vi];
      if(!oppo) { // pair the boundary
        oppo = m().add(typename TMPL::edge_t());
        m[oppo].vert() = vjj->second->prev()->vert();
      }
      m[vjj->second].oppo() = oppo;
      m[oppo].oppo() = vjj->second;
    }
  }

  // link boundary edges
  for(CEI ei = m.edges().begin(); ei != m.edges().end(); ++ei) {
    if(ei->face()) {
      assert(!!ei->next() && !!ei->prev());
      continue;
    }
    for(CEI ej = ei->oppo();;) {
      ej = ej->prev()->oppo(); // ccw of out edges
      if(!ej->face()) { // border
        m[ei].next() = ej;
        m[ej].prev() = ei;
        break;
      }
    }
  }
}


//! @assign from mat use add_face function
//! @NOTE use add_face function will make each halfedge and its
//! @opposite one adjacent in a vector thus improve cache hit proportion
template <typename TMPL, typename ME>
void
assign_from_mat_with_addface(mesh_tmpl<TMPL> &mt, const ME &cellst)
{
  std::cout << "add_face" << std::endl;
  using namespace std;
  
  typedef TMPL mesh_t;
  typedef ME matrix_t;  
  typedef typename mesh_t::verts_t::const_iterator CVI;
  typedef typename mesh_t::edges_t::const_iterator CEI;
  typedef typename mesh_t::faces_t::const_iterator CFI;
  
  mesh_t &m = mt();
  const matrix_t &cells = get_mat(cellst);
  
  assert(get_row_numbers(cells) == 3);
  //insert vert
  const size_t vert_num = get_max_coef(cells) + 1;

  vector<CVI> vis;
  vis.reserve(vert_num);
  for(size_t vi = 0; vi < vert_num; ++vi)
    vis[vi] = m.add(typename mesh_t::vert_t());

  for (size_t fi=0; fi<get_col_numbers(cells); ++fi)
  {
    vector<CVI> vert_loop;
    vert_loop.clear();
    vert_loop.reserve(3);
    for (size_t i=0; i<get_row_numbers(cells); ++i)
    {
      vert_loop.push_back(vis[cells(i, fi)]);
    }

    CFI f_new = add_face_keep_topo(mt, vert_loop.begin(), get_row_numbers(cells));
    if (f_new == CFI())
    {
      char error[256];
      sprintf(error, "in assign_from_mat_with_add_face: duplicated edge of new face (%ld, %ld, %ld)", cells(0, fi), cells(1, fi), cells(2, fi));
      throw std::runtime_error(error);
    }
  }
}


////////////////////with properties//////////////////////////////////

//! @assume cells code the face list of a triangular manifold
template <typename ME>
mat_builder_with_id<ME>
build_with_id(const ME &cells)
{
  return mat_builder_with_id<ME>(cells);
}

template <typename TMPL, typename ME>
void
assign(mesh_tmpl<TMPL> &mt, const mat_builder_with_id<ME> &b)
{
  assign_from_mat(mt, b.cells_);

  typedef TMPL mesh_t;

  typedef typename mesh_t::verts_t::const_iterator CVI;
  typedef typename mesh_t::faces_t::const_iterator CFI;

  size_t id = 0;
  for(auto vi = mt().verts().begin(); vi != mt().verts().end(); ++vi, ++id)
    mt()[vi].id() = id;

  id = 0;
  for(auto fi = mt().faces().begin(); fi != mt().faces().end(); ++fi, ++id)
    mt()[fi].id() = id;
}

//! @brief load property from matrix to halfedge
//! @param mesh for the mesh to build
//!        begin for the start iterator of the element whose property will be changed
//!        end is the iterator point to the next element of the latest.
//!        pro_ref is a function which return the reference of the property object
//!        pm is property matrix store the property data.
template <typename MESH, typename OWN_ITR, typename PRO_TYPE, typename TMP, typename MAT>
int assign_property(MESH & mesh, const OWN_ITR &begin, const OWN_ITR & end, PRO_TYPE (TMP::*pro_ref)(), const MAT & pm)
{
  size_t row = get_row_numbers(pm);
  size_t col = get_col_numbers(pm);
  
  size_t idx = 0;
  
  for(OWN_ITR i = begin; i != end; ++i, ++idx)
  {
    PRO_TYPE p = (mesh()[i].*pro_ref)();
    p.resize(row, 1);
    //resize_container(p, row);
    for (size_t j=0; j<row; ++j)
      p(j, 0) = pm(j, idx);
  }
}
