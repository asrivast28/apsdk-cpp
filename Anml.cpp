#include "Anml.hpp"

#include "AnmlMacro.hpp"
#include "AnmlNetwork.hpp"


namespace ap {

/**
 * @brief  Initializes the instance with an ANML workspace.
 */
Anml::Anml(
) : m_anml(AP_CreateAnml())
{
}

/**
 * @brief  Move constructor.
 */
Anml::Anml(
  Anml&& that
) : m_anml(that.m_anml)
{
  // Ensure that the other instance doesn't destroy the workspace.
  that.m_anml = 0;
}

/**
 * @brief  Loads macro from the given ANML file.
 *
 * @param fileName  Name of the ANML file from which macro is to be loaded.
 *
 * @return  Returns AnmlMacro instance for the loaded macro. 
 */
AnmlMacro
Anml::loadMacro(
  const std::string& fileName
)
{
  ap_macro_def_t macro;
  AP_LoadAnmlMacro(m_anml, &macro, 0, fileName.c_str(), 0, AP_OPT_DEFAULT, 0);
  return AnmlMacro(macro);
}


/**
 * @brief  Creates an ANML network in this workspace.
 *
 * @param anmlId  ANML id of the network to be created.
 *
 * @return  Returns AnmlNetwork instance for the created network. 
 */
AnmlNetwork
Anml::createNetwork(
  const std::string& anmlId
)
{
  ap_anml_network_t network;
  AP_CreateAutomataNetwork(m_anml, &network, anmlId.c_str());
  return AnmlNetwork(network);
}

/**
 * @brief  Precompiles all the loaded macros.
 */
void
Anml::compileMacros(
) const
{
  AP_CompileMacros(m_anml, 0, 0, 0, AP_OPT_DEFAULT, 0);
}

/**
 * @brief  Compiles the ANML workspace.
 *
 * @return  Returns Automaton and ElementMap instances generated as a result of the compilation. 
 */
std::pair<Automaton, ElementMap>
Anml::compileAnml(
) const
{
  ap_automaton_t automaton;
  ap_element_map_t elementMap;
  AP_CompileAnml(m_anml, &automaton, &elementMap, 0, 0, AP_OPT_DEFAULT, 0);
  return std::pair<Automaton, ElementMap>(Automaton(automaton), ElementMap(elementMap));
}

/**
 * @brief  Destuctor for destroying the associated ANML workspace.
 */
Anml::~Anml(
)
{
  if (m_anml != 0) {
    AP_DestroyAnml(m_anml);
  }
  m_anml = 0;
}

} // namespace ap
