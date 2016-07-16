#ifndef APSDK_AUTOMATON_HPP_
#define APSDK_AUTOMATON_HPP_

#include <string>

#include <micron/ap/ap_anml.h>

namespace ap {

class Automaton {
public:
  Automaton();

  Automaton(const ap_automaton_t&, const ap_element_map_t&);

  /**
   * Copying may result in destruction of the
   * orginal object. Do NOT allow copying.
   */
  Automaton(const Automaton&) = delete;

  Automaton(Automaton&&);

  void
  getElementRef(const std::string&) const;

  void
  setSymbol();

  void
  save(const std::string&) const;

  void
  printInfo() const;

  ~Automaton();

private:
  ap_automaton_t m_automaton;
  ap_element_map_t m_elementMap;
}; // class Automaton

} // namespace ap

#endif // APSDK_AUTOMATON_HPP_
