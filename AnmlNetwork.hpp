#ifndef APSDK_ANMLNETWORK_HPP_
#define APSDK_ANMLNETWORK_HPP_

#include <micron/ap/ap_anml.h>

namespace ap {

class AnmlNetwork {
public:
  AnmlNetwork(ap_anml_network_t*);

  AnmlNetwork(const AnmlNetwork&);

  ~AnmlNetwork();

private:
  ap_anml_network_t* m_network;
}; // class AnmlNetwork

} // namespace ap

#endif // APSDK_ANMLNETWORK_HPP_
