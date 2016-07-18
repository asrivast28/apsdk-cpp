#include "SymbolChange.hpp"

#include <cassert>

namespace ap {

/**
 * @brief  Initialized the object using maximum number of allowed changes.
 *
 * @param maxChanges  Maximum number of allowed changes. 
 */
SymbolChange::SymbolChange(
  unsigned maxChanges 
) : m_changes(maxChanges),
    m_symbols(maxChanges, "[\\x00]"),
    m_index(0)
{
}

/**
 * @brief  Adds a symbol to be changed.
 *
 * @param elementRef  Reference of the element in which substitution is to be done.
 * @param paramRef    Reference of the parameter which is to be substituted.
 * @param symbol      Symbol with which the substitution is to be done.
 */
void
SymbolChange::add(
  const ElementRef& elementRef,
  const AnmlMacro::ParamRef& paramRef,
  const std::string& symbol
)
{
  // There should be space for another addition.
  assert(m_index < m_symbols.size());

  // Add symbol for availability of char*.
  m_symbols[m_index] = symbol;

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
