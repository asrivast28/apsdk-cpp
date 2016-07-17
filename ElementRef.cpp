#include "ElementRef.hpp"

namespace ap {

ElementRef::ElementRef(
) : m_elementRef(0)
{
}

ElementRef::ElementRef(
  const ap_anml_element_ref_t& elementRef
) : m_elementRef(elementRef)
{
}

ElementRef::ElementRef(
  const ElementRef& that 
) : m_elementRef(that.m_elementRef)
{
}

ap_anml_element_ref_t
ElementRef::operator*(
) const
{
  return m_elementRef;
}

ElementRef::~ElementRef(
)
{
  m_elementRef = 0;
}

}
