#ifndef APSDK_ANML_HPP_
#define APSDK_ANML_HPP_

#include "AnmlMacro.hpp"
#include "AnmlNetwork.hpp"
#include "Automaton.hpp"

#include <string>

#include <micron/ap/ap_anml.h>

namespace ap {

class Anml {
public:
  Anml();

  /**
   * Copying may result in destruction of the
   * orginal object. Do NOT allow copying.
   */
  Anml(const Anml&) = delete;

  Anml(Anml&&);

  AnmlMacro
  loadMacro(const std::string&);

  AnmlNetwork
  createNetwork(const std::string&);

  void
  compileMacros() const;

  Automaton
  compileAnml() const;

  ~Anml();

private:
  ap_anml_t m_anml;
}; // class Anml

} // namespace ap

#endif // APSDK_ANML_HPP_
