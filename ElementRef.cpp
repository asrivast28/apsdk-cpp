/**
 * @file ElementRef.cpp
 * @brief Implementation of ElementRef functions.
 * @author Ankit Srivastava <asrivast@gatech.edu>
 * @version 1.0
 * @date 2016-09-09
 */
#include "ElementRef.hpp"

namespace ap {

/**
 * @brief  Default constructor.
 */
ElementRef::ElementRef(
) : m_elementRef(0)
{
}

/**
 * @brief  Constructor for creating the object with a given
 *         ap_anml_element_ref_t instance.
 */
ElementRef::ElementRef(
  const ap_anml_element_ref_t& elementRef
) : m_elementRef(elementRef)
{
}

/**
 * @brief  Copy constructor.
 */
ElementRef::ElementRef(
  const ElementRef& that
) : m_elementRef(that.m_elementRef)
{
}

/**
 * @brief  Overloaded indirection operator implementation.
 *
 * @return  Returns the underlying ap_anml_element_ref_t instance.
 */
ap_anml_element_ref_t
ElementRef::operator*(
) const
{
  return m_elementRef;
}

bool
ElementRef::operator==(
  const ElementRef& that
) const
{
  return (m_elementRef == *that);
}

/**
 * @brief  Default destructor.
 */
ElementRef::~ElementRef(
)
{
  m_elementRef = 0;
}

size_t
ElementRefHasher::operator()(
  const ElementRef& elementRef
) const
{
  return std::hash<ap_anml_element_ref_t>()(*elementRef);
}

}
