#ifndef KEY_CONCEPT_H
#define KEY_CONCEPT_H

namespace hj{ namespace half_edge{

//special implementation
template <typename Con>
class hash_key_of_list
{
public:
  typedef sparse_key_tag key_category;
  typedef typename Con::const_iterator::value_type* key_type;
  hash_key_of_list(const Con &con){}
  const typename Con::const_iterator::value_type *
  operator()(const typename Con::const_iterator &it) const {
    return this->operator()(*it);
  }
  const typename Con::const_iterator::value_type *
  operator()(const typename Con::value_type &v) const {
    return &(v);
  }
};

template <typename Con>
class hash_key_of_vector
{
public:
  typedef range_key_tag key_category;
  typedef size_t key_type;
  hash_key_of_vector(const Con &con)
    :con_(con){}
  size_t operator()(const typename Con::const_iterator &it) const {
    return this->operator()(*it);
  }
  size_t operator()(const typename Con::value_type &v) const {
    return (&(v)-&(*con_.begin()));
  }
private:
  const Con &con_;
};

template <typename Cat, typename Con>
class hash_key_imp
{
};

template <typename Con>
class hash_key_imp<sparse_key_tag, Con>
{
public:
  typedef hash_key_of_list<Con> imp;
};

template <typename Con>
class hash_key_imp<range_key_tag, Con>
{
public:
  typedef hash_key_of_vector<Con> imp;
};

template <typename Con>
class hash_key
{
public:
  typedef typename hash_key_imp<typename Con::key_category, Con>::imp key;
};

}//namespace half_edge
}//namespace hj


#endif
