#include "AnmlNetwork.hpp"


namespace ap {

AnmlNetwork::AnmlNetwork(
  ap_anml_network_t* network
) : m_network(network)
{
}

AnmlNetwork::AnmlNetwork(
  const AnmlNetwork& other
)
{
  m_network = other.m_network;
}

AnmlNetwork::~AnmlNetwork(
)
{
  m_network = nullptr;
}

} // namespace ap
