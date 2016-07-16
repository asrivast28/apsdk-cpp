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

AnmlMacro::ParamRef
AnmlMacro::getParamFromName(
  const std::string& name
) const
{
  ap_macro_param_ref_t param;
  AP_GetMacroParamFromName(m_macro, &param, name.c_str());
  return ParamRef(param);
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

AnmlMacro::ParamRef::ParamRef(
) : m_paramRef(0)
{
}

AnmlMacro::ParamRef::ParamRef(
  const ParamRef& that 
) : m_paramRef(that.m_paramRef)
{
}

AnmlMacro::ParamRef::ParamRef(
  const ap_macro_param_ref_t& paramRef
) : m_paramRef(paramRef)
{
}

ap_macro_param_ref_t
AnmlMacro::ParamRef::operator*(
) const
{
  return m_paramRef;
}

AnmlMacro::ParamRef::~ParamRef(
)
{
  m_paramRef = 0;
}

} // namespace ap
