#include "AnmlNetwork.hpp"

#include "APCall.hpp"


namespace ap {

/**
 * @brief  Constructor for creating the object with a given
 *         ap_network_ref_t instance.
 */
AnmlNetwork::AnmlNetwork(
  const ap_anml_network_t& network
) : m_network(network)
{
}

/**
 * @brief  Copy constructor.
 */
AnmlNetwork::AnmlNetwork(
  const AnmlNetwork& that
) : m_network(that.m_network)
{
}

/**
 * @brief  Adds a reference to the given macro, with the given id.
 *
 * @param macro   Macro reference to be added to the network.
 * @param anmlId  ANML id of the reference to be added.
 */
void
AnmlNetwork::addMacroRef(
  const AnmlMacro& macro,
  const std::string& anmlId
)
{
  struct ap_anml_element element = macro.getAnmlElement();
  element.id = anmlId.c_str();

  ap_anml_element_ref_t elementRef;
  APCALL_CHECK(AP_AddAnmlElement)(m_network, &elementRef, &element);
}

/**
 * @brief  Exports the ANML network to the given file.
 *
 * @param fileName  Name of the file to which the network is to be exported.
 */
void
AnmlNetwork::exportAnml(
  const std::string& fileName
) const
{
  APCALL_CHECK(AP_ExportAnml)(m_network, fileName.c_str(), static_cast<const char*>(0));
}

/**
 * @brief  Default destructor.
 */
AnmlNetwork::~AnmlNetwork(
)
{
}

} // namespace ap
