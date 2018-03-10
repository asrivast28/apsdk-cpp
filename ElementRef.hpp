/**
 * @file ElementRef.hpp
 * @brief Declaration of ElementRef functions.
 *
 * Copyright 2018 Georgia Institute of Technology
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef APSDK_ELEMENTREF_HPP_
#define APSDK_ELEMENTREF_HPP_

#include <string>

#include <micron/ap/ap_anml.h>

namespace ap {

/**
 * @brief  Wrapper class for ap_element_ref_t functionality.
 */
class ElementRef {
public:
  ElementRef();

  ElementRef(const ap_anml_element_ref_t&);

  ElementRef(const ElementRef&);

  ap_anml_element_ref_t
  operator*() const;

  bool
  operator==(const ElementRef&) const;

  ~ElementRef();

private:
  // ap_element_ref_t instance that this object refers to.
  ap_anml_element_ref_t m_elementRef;
}; // class ElementRef

class ElementRefHasher {
public:
  size_t
  operator()(const ElementRef&) const;
}; // class ElementRefHasher

} // namespace ap

#endif // APSDK_ELEMENTREF_HPP_
