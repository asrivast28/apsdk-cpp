#ifndef APSDK_SYMBOLCHANGE_HPP_
#define APSDK_SYMBOLCHANGE_HPP_

#include "AnmlMacro.hpp"
#include "ElementRef.hpp"

#include <string>
#include <vector>

#include <micron/ap/ap_reload.h>

namespace ap {

/**
 * @brief  Wrapper class for ap_symbol_change functionality.
 */
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
  // Vector containing all the changes associated with this object.
  std::vector<struct ap_symbol_change> m_changes;
  // Vector containing all the symbols for the changes associated with this object.
  std::vector<std::string> m_symbols;
  // Current count of the changes stored in this object. 
  unsigned m_index;
}; // class SymbolChange

} // namespace ap

#endif // APSDK_SYMBOLCHANGE_HPP_
