#include "AnmlMacro.hpp"


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
  ap_macro_param_ref_t* param = nullptr;
  AP_GetMacroParamFromName(*m_macro, param, name.c_str());
}

AnmlMacro::~AnmlMacro(
)
{
  m_macro = nullptr;
}

} // namespace ap
