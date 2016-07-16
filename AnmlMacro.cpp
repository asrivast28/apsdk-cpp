#include "AnmlMacro.hpp"

#include <cstring>

namespace ap {

AnmlMacro::AnmlMacro(
) : m_macro(0)
{
}

AnmlMacro::AnmlMacro(
  const ap_macro_def_t& macro
) : m_macro(macro)
{
}

AnmlMacro::AnmlMacro(
  const AnmlMacro& that
) : m_macro(that.m_macro)
{
}

void
AnmlMacro::getParamFromName(
  const std::string& name
) const
{
  ap_macro_param_ref_t* param = 0;
  AP_GetMacroParamFromName(m_macro, param, name.c_str());
}

void
AnmlMacro::setMacroDefToBeCompiled(
) const
{
  AP_SetMacroDefToBeCompiled(m_macro);
}

struct ap_anml_element
AnmlMacro::getAnmlElement(
) const
{
  struct ap_anml_element element;
  memset(&element, 0, sizeof(element));
  element.res_type = RT_MACRO_REF;
  element.macro_ref = m_macro;

  return element;
}

AnmlMacro::~AnmlMacro(
)
{
}

} // namespace ap
