#include "SymbolChange.hpp"

#include <cassert>
#include <cstring>

namespace ap {

/**
 * @brief  Converts the first B bytes of the number to hex.
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
    char hex[3];
    sprintf(hex, "%02x", *x);
    symbol[0] = hex[0];
    symbol[1] = hex[1];
    ++x;
  }
  return symbols;
}

template std::array<SymbolChange::HexSymbolType, 4> SymbolChange::getHexSymbols<4>(unsigned);

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
 * @param hexValue    Symbol with which the substitution is to be done.
 * @param negation    Flag specifying if the symbol is to be negated. Defaults to false.
 */
void
SymbolChange::add(
  const ElementRef& elementRef,
  const AnmlMacro::ParamRef& paramRef,
  const HexSymbolType& hexValue,
  const bool negation
)
{
  // There should be space for another addition.
  assert(m_index < m_symbols.size());

  // Add symbol for availability of char*.
  std::string hexSymbol("[" + std::string(negation ? "^" : "") + "\\x" +
                        std::string(hexValue.begin(), hexValue.end()) + "]");
  strcpy(m_symbols[m_index].data(), hexSymbol.c_str());

  // Add symbol change.
  struct ap_symbol_change& change = m_changes[m_index];
  change.element_ref = *elementRef;
  change.symbol_set = m_symbols[m_index].data();
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
