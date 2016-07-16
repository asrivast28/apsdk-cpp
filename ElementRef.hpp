#ifndef APSDK_ELEMENTREF_HPP_
#define APSDK_ELEMENTREF_HPP_

#include <string>

#include <micron/ap/ap_anml.h>

namespace ap {

class ElementRef {
public:
  ElementRef();

  ElementRef(const ap_anml_element_ref_t&);

  ElementRef(const ElementRef&);

  ap_anml_element_ref_t
  operator*() const;

  ~ElementRef();

private:
  ap_anml_element_ref_t m_elementRef;
}; // class ElementRef

} // namespace ap

#endif // APSDK_ELEMENTREF_HPP_
