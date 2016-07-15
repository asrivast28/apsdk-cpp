#include "AnmlMacro.hpp"

#include <cstring>

namespace ap {

AnmlMacro::AnmlMacro(
  ap_macro_def_t* macro
) : m_macro(macro)
{
}

AnmlMacro::AnmlMacro(
  const AnmlMacro& other 
)
{
  m_macro = other.m_macro; 
}

void
AnmlMacro::getParamFromName(
  const std::string& name
) const
{
  ap_macro_param_ref_t* param = 0;
  AP_GetMacroParamFromName(*m_macro, param, name.c_str());
}

void
AnmlMacro::setMacroDefToBeCompiled(
) const
{
  AP_SetMacroDefToBeCompiled(*m_macro);
}

struct ap_anml_element
AnmlMacro::getAnmlElement(
) const
{
  struct ap_anml_element element;
  memset(&element, 0, sizeof(element));
  element.res_type = RT_MACRO_REF;
  element.macro_ref = *m_macro;

  return element;
}

ap_macro_def_t*
AnmlMacro::operator*(
)
{
  return m_macro;
}

AnmlMacro::~AnmlMacro(
)
{
  m_macro = 0;
}

} // namespace ap
