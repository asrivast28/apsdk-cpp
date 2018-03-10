/**
 * @file AnmlMacro.hpp
 * @brief Declaration of AnmlMacro functions.
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
#ifndef APSDK_ANMLMACRO_HPP_
#define APSDK_ANMLMACRO_HPP_

#include <string>

#include <micron/ap/ap_anml.h>

namespace ap {

/**
 * @brief  Wrapper class for ap_macro_def_t functionality.
 */
class AnmlMacro {
public:
  class ParamRef;

public:
  AnmlMacro();

  AnmlMacro(const ap_macro_def_t&);

  AnmlMacro(const AnmlMacro&);

  void
  setMacroDefToBeCompiled() const;

  ParamRef
  getParamFromName(const std::string&) const;

  struct ap_anml_element
  getAnmlElement() const;

  ~AnmlMacro();

private:
  // ap_macro_def_t instance that this object refers to.
  ap_macro_def_t m_macro;
}; // class AnmlMacro

/**
 * @brief  Wrapper class for ap_macro_param_ref_t functionality.
 */
class AnmlMacro::ParamRef {
public:
  ParamRef();

  ParamRef(const ap_macro_param_ref_t&);

  ParamRef(const ParamRef&);

  ap_macro_param_ref_t
  operator*() const;

  ~ParamRef();

private:
  // ap_macro_param_ref_t instance that this object refers to.
  ap_macro_param_ref_t m_paramRef;
}; // class AnmlMacro::ParamRef

} // namespace ap

#endif // APSDK_ANMLMACRO_HPP_
