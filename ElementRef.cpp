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

/**
 * @brief  Default destructor.
 */
ElementRef::~ElementRef(
)
{
  m_elementRef = 0;
}

}
