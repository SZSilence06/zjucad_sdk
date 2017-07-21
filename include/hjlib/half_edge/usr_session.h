#ifndef USR_SESSION_H
#define USR_SESSION_H

#include <iostream>

#include "hash_key_concept.h"

namespace usr_session
{
class default_usr_session
{
 public:
  default_usr_session(){}

 public:
  template <typename TMPL, typename ITR>
  class del_session
  {
   public:
    int prev(const hj::half_edge::mesh_tmpl<TMPL> & m, const typename hj::half_edge::iterator_tmpl<ITR> &itr, default_usr_session & usr){}
    void post(){}
  };

  template <typename TMPL, typename ELE>
  class add_session
  {
   public:
    int prev(const hj::half_edge::mesh_tmpl<TMPL> & m, const ELE & e, default_usr_session & usr){
    }
    template <typename IT>
    void post(const IT &new_it) {
      //iterator passed here is iterator of new element
    }
  };
};
  
}


#endif
