#include "AnmlNetwork.hpp"



namespace ap {

AnmlNetwork::AnmlNetwork(
  const ap_anml_network_t& network
) : m_network(network)
{
}

AnmlNetwork::AnmlNetwork(
  const AnmlNetwork& that
) : m_network(that.m_network)
{
}

void
AnmlNetwork::addMacroRef(
  const AnmlMacro& macro,
  const std::string& anmlId
)
{
  struct ap_anml_element element = macro.getAnmlElement();
  element.id = anmlId.c_str();

  ap_anml_element_ref_t elementRef;
  AP_AddAnmlElement(m_network, &elementRef, &element);
}

void
AnmlNetwork::exportAnml(
  const std::string& fileName
) const
{
  AP_ExportAnml(m_network, fileName.c_str(), 0);
}

AnmlNetwork::~AnmlNetwork(
)
{
}

} // namespace ap
