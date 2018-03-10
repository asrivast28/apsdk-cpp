/**
 * @file SymbolChange.hpp
 * @brief Declaration of SymbolChange functions.
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
#ifndef APSDK_SYMBOLCHANGE_HPP_
#define APSDK_SYMBOLCHANGE_HPP_

#include "AnmlMacro.hpp"
#include "ElementRef.hpp"

#include <array>
#include <vector>

#include <micron/ap/ap_load.h>
#if (APSDKVERSION <= 26)
#include <micron/ap/ap_reload.h>
#endif

namespace ap {

/**
 * @brief  Wrapper class for ap_symbol_change functionality.
 */
class SymbolChange {
public:
  typedef std::array<char, 2> HexSymbolType;

public:
  static
  SymbolChange::HexSymbolType
  getHexSymbol(unsigned char);

  template <unsigned N = 4>
  static
  std::array<SymbolChange::HexSymbolType, N>
  getHexSymbols(unsigned);

  static
  std::string
  getSymbolSet(const HexSymbolType&, const bool = false);

  static
  std::string
  getSymbolSet(const std::pair<HexSymbolType, HexSymbolType>&, const bool = false);

  static
  std::string
  getSymbolSet(const std::vector<HexSymbolType>&, const bool = false);

  static
  std::string
  getSymbolSet(const std::vector<std::pair<HexSymbolType, HexSymbolType> >&, const bool = false);

public:
  SymbolChange(unsigned);

  void
  add(const ElementRef&, const AnmlMacro::ParamRef&, const std::string&);

  struct ap_symbol_change*
  operator*();

  unsigned
  count() const;

  ~SymbolChange();

private:
  // Vector containing all the changes associated with this object.
  std::vector<struct ap_symbol_change> m_changes;
  // Vector containing all the symbols for the changes associated with this object.
  std::vector<std::string> m_symbols;
  // Current count of the changes stored in this object.
  unsigned m_index;
}; // class SymbolChange

} // namespace ap

#endif // APSDK_SYMBOLCHANGE_HPP_
