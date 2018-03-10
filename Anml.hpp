/**
 * @file Anml.hpp
 * @brief Declaration of Anml functions.
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
#ifndef APSDK_ANML_HPP_
#define APSDK_ANML_HPP_

#include "AnmlMacro.hpp"
#include "AnmlNetwork.hpp"
#include "Automaton.hpp"
#include "ElementMap.hpp"

#include <string>

#include <micron/ap/ap_anml.h>

namespace ap {

/**
 * @brief  Wrapper class for ap_anml_t functionality.
 */
class Anml {
public:
  Anml();

  /**
   * Copying may result in destruction of the
   * orginal object. Do NOT allow copying.
   */
  Anml(const Anml&) = delete;

  Anml(Anml&&);

  AnmlMacro
  loadMacro(const std::string&);

  AnmlNetwork
  createNetwork(const std::string&);

  void
  compileMacros() const;

  std::pair<Automaton, ElementMap>
  compileAnml() const;

  ~Anml();

private:
  // ap_anml_t instance that this object refers to.
  ap_anml_t m_anml;
}; // class Anml

} // namespace ap

#endif // APSDK_ANML_HPP_
