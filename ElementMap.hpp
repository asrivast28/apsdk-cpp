/**
 * @file ElementMap.hpp
 * @brief Declaration of ElementMap functions.
 * @author Ankit Srivastava <asrivast@gatech.edu>
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
#ifndef APSDK_ELEMENTMAP_HPP_
#define APSDK_ELEMENTMAP_HPP_

#include "ElementRef.hpp"

#include <string>

#include <micron/ap/ap_anml.h>

namespace ap {

/**
 * @brief  Wrapper class for ap_element_map_t functionality. 
 */
class ElementMap {
public:
  ElementMap();

  ElementMap(const ap_element_map_t&);

  ElementMap(const std::string&);

  /**
   * Copying may result in destruction of the
   * orginal object. Do NOT allow copying.
   */
  ElementMap(const ElementMap&) = delete;

  ElementMap(ElementMap&&);

  ElementMap&
  operator=(ElementMap&&);

  ElementRef
  getElementRef(const std::string&) const;

  std::string
  getElementId(const ElementRef&) const; 

  void
  save(const std::string&) const;

  ap_element_map_t
  operator*();

  ~ElementMap();

private:
  // ap_element_map_t instance that this object refers to.
  ap_element_map_t m_elementMap;
}; // class ElementMap

} // namespace ap

#endif // APSDK_ELEMENTMAP_HPP_
