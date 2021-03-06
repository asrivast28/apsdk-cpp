/**
 * @file AnmlMacro.cpp
 * @brief Implementation of AnmlMacro functions.
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
#include "AnmlMacro.hpp"

#include "APCall.hpp"

#include <cstring>

namespace ap {

/**
 * @brief  Default constructor.
 */
AnmlMacro::AnmlMacro(
) : m_macro(0)
{
}

/**
 * @brief  Constructor for creating the object with a given
 *         ap_macro_def_t instance.
 */
AnmlMacro::AnmlMacro(
  const ap_macro_def_t& macro
) : m_macro(macro)
{
}

/**
 * @brief  Copy constructor.
 */
AnmlMacro::AnmlMacro(
  const AnmlMacro& that
) : m_macro(that.m_macro)
{
}

/**
 * @brief  Gets parameter reference for the given parameter name.
 *
 * @param name  Name of the parameter in the macro.
 *
 * @return  AnmlMacro::ParamRef object containing the reference.
 */
AnmlMacro::ParamRef
AnmlMacro::getParamFromName(
  const std::string& name
) const
{
  ap_macro_param_ref_t param;
  APCALL_CHECK_ZERO(AP_GetMacroParamFromName)(m_macro, &param, name.c_str());
  return ParamRef(param);
}

/**
 * @brief  Marks the macro for precompilation.
 */
void
AnmlMacro::setMacroDefToBeCompiled(
) const
{
  APCALL_CHECK_ZERO(AP_SetMacroDefToBeCompiled)(m_macro);
}

/**
 * @brief  Gets ap_anml_element instance for the given macro.
 */
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

/**
 * @brief  Default destructor.
 */
AnmlMacro::~AnmlMacro(
)
{
}

/**
 * @brief  Default constructor.
 */
AnmlMacro::ParamRef::ParamRef(
) : m_paramRef(-1)
{
}

/**
 * @brief  Constructor for creating the object with a given
 *         ap_macro_param_ref_t instance.
 */
AnmlMacro::ParamRef::ParamRef(
  const ap_macro_param_ref_t& paramRef
) : m_paramRef(paramRef)
{
}

/**
 * @brief  Copy constructor.
 *
 * @param  Object to be copied from.
 */
AnmlMacro::ParamRef::ParamRef(
  const ParamRef& that
) : m_paramRef(that.m_paramRef)
{
}

/**
 * @brief  Overloaded indirection operator implementation.
 *
 * @return  Returns the ap_macro_param_ref_t instance.
 */
ap_macro_param_ref_t
AnmlMacro::ParamRef::operator*(
) const
{
  return m_paramRef;
}

/**
 * @brief  Default destructor.
 */
AnmlMacro::ParamRef::~ParamRef(
)
{
  m_paramRef = 0;
}

} // namespace ap
