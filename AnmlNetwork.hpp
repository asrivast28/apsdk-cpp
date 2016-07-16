#ifndef APSDK_ANMLNETWORK_HPP_
#define APSDK_ANMLNETWORK_HPP_

#include "AnmlMacro.hpp"

#include <string>

#include <micron/ap/ap_anml.h>

namespace ap {

class AnmlNetwork {
public:
  AnmlNetwork(const ap_anml_network_t&);

  AnmlNetwork(const AnmlNetwork&);

  void
  addMacroRef(const AnmlMacro&, const std::string&);

  void
  exportAnml(const std::string&) const;

  ~AnmlNetwork();

private:
  ap_anml_network_t m_network;
}; // class AnmlNetwork

} // namespace ap

#endif // APSDK_ANMLNETWORK_HPP_
