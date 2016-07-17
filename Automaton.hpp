#ifndef APSDK_AUTOMATON_HPP_
#define APSDK_AUTOMATON_HPP_

#include "ElementMap.hpp"
#include "SymbolChange.hpp"

#include <string>

#include <micron/ap/ap_anml.h>

namespace ap {

class Automaton {
public:
  Automaton();

  Automaton(const ap_automaton_t&);

  Automaton(const std::string&);

  /**
   * Copying may result in destruction of the
   * orginal object. Do NOT allow copying.
   */
  Automaton(const Automaton&) = delete;

  Automaton(Automaton&&);

  void
  setSymbol(ElementMap&, SymbolChange&);

  void
  save(const std::string&) const;

  void
  printInfo() const;

  ~Automaton();

private:
  ap_automaton_t m_automaton;
}; // class Automaton

} // namespace ap

#endif // APSDK_AUTOMATON_HPP_
