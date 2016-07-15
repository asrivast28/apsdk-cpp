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

void
AnmlNetwork::addMacroRef(
  const AnmlMacro& macro,
  const std::string& anmlId
)
{
  struct ap_anml_element element = macro.getAnmlElement();
  element.id = anmlId.c_str();

  ap_anml_element_ref_t* elementRef = 0;
  AP_AddAnmlElement(*m_network, elementRef, &element); 
}

void
AnmlNetwork::exportAnml(
  const std::string& fileName
) const
{
  AP_ExportAnml(*m_network, fileName.c_str(), 0);
}

ap_anml_network_t*
AnmlNetwork::operator*(
)
{
  return m_network;
}

AnmlNetwork::~AnmlNetwork(
)
{
  m_network = 0;
}

} // namespace ap
