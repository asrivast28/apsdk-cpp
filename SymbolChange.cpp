/**
 * @file SymbolChange.cpp
 * @brief Implementation of SymbolChange functions.
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
#include "SymbolChange.hpp"

#include <cassert>
#include <cstring>


namespace ap {

/**
 * @brief  Converts the given byte to hex.
 *
 * @param x  Byte to be converted to hex.
 *
 * @return  Hex symbol for the byte.
 */
SymbolChange::HexSymbolType
SymbolChange::getHexSymbol(
  unsigned char x
)
{
  char hex[3];
  sprintf(hex, "%02x", x);

  HexSymbolType symbol;
  symbol[0] = hex[0];
  symbol[1] = hex[1];
  return symbol;
}

/**
 * @brief  Converts the B least significant bytes of the number to hex.
 *
 * @tparam B  Number of bytes to be converted.
 * @param n   Number to be converted to hex.
 *
 * @return  Array of B hex symbols, one for each byte.
 */
template <unsigned B>
std::array<SymbolChange::HexSymbolType, B>
SymbolChange::getHexSymbols(
  unsigned n
)
{
  // Reinterpret the given number as stream of unsigned char bytes.
  unsigned char* x = reinterpret_cast<unsigned char*>(&n);
  std::array<HexSymbolType, B> symbols;
  // Assign the hex symbol for each byte.
  for (HexSymbolType& symbol : symbols) {
    symbol = getHexSymbol(*x);
    ++x;
  }
  return symbols;
}

template std::array<SymbolChange::HexSymbolType, 2> SymbolChange::getHexSymbols<2>(unsigned);
template std::array<SymbolChange::HexSymbolType, 3> SymbolChange::getHexSymbols<3>(unsigned);
template std::array<SymbolChange::HexSymbolType, 4> SymbolChange::getHexSymbols<4>(unsigned);

/**
 * @brief  Returns symbol set for a single hex symbol.
 *
 * @param hexSymbol  Hex symbol for which character class is required.
 * @param negation   Flag specifying if the symbol is to be negated. Defaults to false.
 *
 * @return  Character class corresponding to the hex symbol.
 */
std::string
SymbolChange::getSymbolSet(
  const HexSymbolType& hexSymbol,
  const bool negation
)
{
  return std::string("[" + std::string(negation ? "^" : "") + "\\x" +
                     std::string(hexSymbol.data(), hexSymbol.size()) + "]");
}

/**
 * @brief  Returns symbol set for hex symbols in a given range.
 *
 * @param hexSymbols  Hex symbols representing lower and upper limit of the character class.
 * @param negation    Flag specifying if the symbol is to be negated. Defaults to false.
 *
 * @return  Character class corresponding to the range.
 */
std::string
SymbolChange::getSymbolSet(
  const std::pair<HexSymbolType, HexSymbolType>& hexSymbols,
  const bool negation
)
{
  return std::string("[" + std::string(negation ? "^" : "") +
                     "\\x" + std::string(hexSymbols.first.data(), hexSymbols.first.size()) + "-" +
                     "\\x" + std::string(hexSymbols.second.data(), hexSymbols.second.size()) + "]");
}

/**
 * @brief  Returns symbol set for multiple hex symbols.
 *
 * @param hexSymbols  Vector of hex symbols for which character class is required.
 * @param negation    Flag specifying if the symbol is to be negated. Defaults to false.
 *
 * @return  Character class corresponding to the hex symbols.
 */
std::string
SymbolChange::getSymbolSet(
  const std::vector<HexSymbolType>& hexSymbols,
  const bool negation
)
{
  std::string allSymbols;
  for (const HexSymbolType& s : hexSymbols) {
    allSymbols.append("\\x" + std::string(s.data(), s.size()));
  }
  return "[" + std::string(negation ? "^" : "") + allSymbols + "]";

}

/**
 * @brief  Returns symbol set for multiple hex symbol ranges.
 *
 * @param hexSymbols  Vector of hex symbol ranges for which character class is required.
 * @param negation    Flag specifying if the symbol is to be negated. Defaults to false.
 *
 * @return  Character class corresponding to the hex symbol ranges.
 */
std::string
SymbolChange::getSymbolSet(
  const std::vector<std::pair<HexSymbolType, HexSymbolType> >& hexSymbols,
  const bool negation
)
{
  std::string allSymbols;
  for (const std::pair<HexSymbolType, HexSymbolType>& i : hexSymbols) {
    allSymbols.append("\\x" + std::string(i.first.data(), i.first.size()) + "-" +
                      "\\x" + std::string(i.second.data(), i.second.size()));
  }
  return "[" + std::string(negation ? "^" : "") + allSymbols + "]";

}

/**
 * @brief  Initialized the object using maximum number of allowed changes.
 *
 * @param maxChanges  Maximum number of allowed changes.
 */
SymbolChange::SymbolChange(
  unsigned maxChanges
) : m_changes(maxChanges),
    m_symbols(maxChanges),
    m_index(0)
{
}

/**
 * @brief  Adds a symbol to be changed.
 *
 * @param elementRef  Reference of the element in which substitution is to be done.
 * @param paramRef    Reference of the parameter which is to be substituted.
 * @param symbolSet   Symboli set with which the substitution is to be done.
 */
void
SymbolChange::add(
  const ElementRef& elementRef,
  const AnmlMacro::ParamRef& paramRef,
  const std::string& symbolSet
)
{
  // There should be space for another addition.
  assert(m_index < m_symbols.size());

  // Add symbol for availability of char*.
  m_symbols[m_index] = symbolSet;

  // Add symbol change.
  struct ap_symbol_change& change = m_changes[m_index];
  change.element_ref = *elementRef;
  change.symbol_set = m_symbols[m_index].c_str();
  change.param_ref = *paramRef;

  // Increase the count of added changes.
  ++m_index;
}

/**
 * @brief  Returns the current count of added symbol changes.
 */
unsigned
SymbolChange::count(
) const
{
  return m_index;
}

/**
 * @brief  Overloaded indirection operator implementation.
 *
 * @return  Returns the pointer to ap_symbol_change array.
 */
struct ap_symbol_change*
SymbolChange::operator*(
)
{
  return &m_changes[0];
}

/**
 * @brief  Default destructor.
 */
SymbolChange::~SymbolChange(
)
{
}

} // namespace ap
