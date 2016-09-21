//
// type_id.h
// ~~~~~~~~~~~~~~~~~~~~~~
// Very simple type id system so that we're not dependent on typeid() in
// the case of systems compiling with -no-rtti
//
// Copyright (c) 2014 Chris Glover (c.d.glover at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef EXECUTORS_EXPERIMENTAL_BITS_TYPE_ID_H
#define EXECUTORS_EXPERIMENTAL_BITS_TYPE_ID_H

#include <cstdint>
#include <type_traits>

namespace std {
namespace experimental {
inline namespace concurrency_v1 {

struct __type_info {
  const void* _M_id;
  __type_info(const void* id)
    : _M_id(id)
    {}
};

inline bool operator==(const __type_info& lhs, const __type_info& rhs) {
  return lhs._M_id == rhs._M_id;
}

template<typename _Ty> 
struct __type_id_impl {
  static const int _M_id;
  static const void* _Id() {
    return &_M_id;
  }
};

template<typename _Ty>
const int __type_id_impl<_Ty>::_M_id(0);

template<typename _Ty> 
const __type_info& __type_id() {
  static __type_info __this_id(__type_id_impl<std::decay_t<_Ty>>::_Id());
  return __this_id;
}

template<typename _Ty> 
const __type_info& __type_id(_Ty const&) {
  return __type_id<_Ty>();
}
  
} // inline namespace concurrency_v1
} // namespace experimental
} // namespace std

#endif