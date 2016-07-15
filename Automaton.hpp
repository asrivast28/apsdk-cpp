#ifndef APSDK_AUTOMATON_HPP_
#define APSDK_AUTOMATON_HPP_

#include <string>

#include <micron/ap/ap_anml.h>

namespace ap {

class Automaton {
public:
  Automaton(ap_automaton_t*, ap_element_map_t*);

  /**
   * Copying may result in destruction of the
   * orginal object. Do NOT allow copying.
   */
  Automaton(const Automaton&) = delete;

  Automaton(const Automaton&&);

  void
  getElementRef(const std::string&) const;

  void
  setSymbol();

  void
  save(const std::string&) const;

  ~Automaton();

private:
  ap_automaton_t* m_automaton;
  ap_element_map_t* m_elementMap;
}; // class Automaton

} // namespace ap

#endif // APSDK_AUTOMATON_HPP_
