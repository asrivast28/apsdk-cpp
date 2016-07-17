#ifndef APSDK_SYMBOLCHANGE_HPP_
#define APSDK_SYMBOLCHANGE_HPP_

#include "AnmlMacro.hpp"
#include "ElementRef.hpp"

#include <string>
#include <vector>

#include <micron/ap/ap_reload.h>

namespace ap {

class SymbolChange {
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
  std::vector<struct ap_symbol_change> m_changes;
  std::vector<std::string> m_symbols;
  unsigned m_index;
}; // class SymbolChange

} // namespace ap

#endif // APSDK_SYMBOLCHANGE_HPP_
