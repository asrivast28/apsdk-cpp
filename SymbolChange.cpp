#include "SymbolChange.hpp"

#include <cassert>

namespace ap {

SymbolChange::SymbolChange(
  unsigned maxChanges 
) : m_changes(maxChanges),
    m_symbols(maxChanges),
    m_index(0)
{
}

void
SymbolChange::add(
  const ElementRef& elementRef,
  const AnmlMacro::ParamRef& paramRef,
  const std::string& symbol
)
{
  assert(m_index < m_symbols.size());

  m_symbols[m_index] = symbol;

  struct ap_symbol_change& change = m_changes[m_index];
  change.element_ref = *elementRef;
  change.symbol_set = m_symbols.rbegin()->c_str();
  change.param_ref = *paramRef;

  ++m_index;
}

unsigned
SymbolChange::count(
) const
{
  return m_index;
}

struct ap_symbol_change*
SymbolChange::operator*(
)
{
  return &m_changes[0];
}

SymbolChange::~SymbolChange(
)
{
}

} // namespace ap
