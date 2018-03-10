/**
 * @file Automaton.hpp
 * @brief Declaration of Automaton functions.
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
#ifndef APSDK_AUTOMATON_HPP_
#define APSDK_AUTOMATON_HPP_

#include "ElementMap.hpp"
#include "SymbolChange.hpp"

#include <string>

#include <micron/ap/ap_anml.h>

namespace ap {

/**
 * @brief  Wrapper class for ap_automaton_t functionality.
 */
class Automaton {
public:
  // Device invalidates the Automaton object during loading.
  // Therefore, Device needs to modify the underlying pointer.
  friend class Device;

public:
  Automaton();

  Automaton(const ap_automaton_t&);

  Automaton(const std::string&);

  Automaton(const Automaton&);

  Automaton(Automaton&&);

  Automaton&
  operator=(Automaton&&);

  void
  setSymbol(ElementMap&, SymbolChange&);

  void
  save(const std::string&) const;

  void
  printInfo() const;

  ap_automaton_t
  operator*();

  ~Automaton();

private:
  // ap_automaton_t instance that this object refers to.
  ap_automaton_t m_automaton;
}; // class Automaton

} // namespace ap

#endif // APSDK_AUTOMATON_HPP_
