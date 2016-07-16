#include "SymbolChange.hpp"

namespace ap {

SymbolChange::SymbolChange(
) : m_changes(),
    m_symbols()
{
}

void
SymbolChange::add(
  const ElementRef& elementRef,
  const AnmlMacro::ParamRef& paramRef,
  const std::string& symbol
)
{
  m_symbols.push_back(symbol);

  struct ap_symbol_change change;
  change.element_ref = *elementRef;
  change.symbol_set = m_symbols.rbegin()->c_str();
  change.param_ref = *paramRef;

  m_changes.push_back(change);
}

unsigned
SymbolChange::count(
) const
{
  return m_changes.size();
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
