/**
 * @file ElementMap.hpp
 * @brief Declaration of ElementMap functions.
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
