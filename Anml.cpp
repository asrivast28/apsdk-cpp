#include "Anml.hpp"

#include "AnmlMacro.hpp"
#include "AnmlNetwork.hpp"


namespace ap {

Anml::Anml(
) : m_anml(AP_CreateAnml())
{
}

Anml::Anml(
  Anml&& that
) : m_anml(that.m_anml)
{
  that.m_anml = 0;
}

AnmlMacro
Anml::loadMacro(
  const std::string& fileName
)
{
  ap_macro_def_t macro;
  AP_LoadAnmlMacro(m_anml, &macro, 0, fileName.c_str(), 0, AP_OPT_DEFAULT, 0);
  return AnmlMacro(macro);
}


AnmlNetwork
Anml::createNetwork(
  const std::string& anmlId
)
{
  ap_anml_network_t network;
  AP_CreateAutomataNetwork(m_anml, &network, anmlId.c_str());
  return AnmlNetwork(network);
}

void
Anml::compileMacros(
) const
{
  AP_CompileMacros(m_anml, 0, 0, 0, AP_OPT_DEFAULT, 0);
}

std::pair<Automaton, ElementMap>
Anml::compileAnml(
) const
{
  ap_automaton_t automaton;
  ap_element_map_t elementMap;
  AP_CompileAnml(m_anml, &automaton, &elementMap, 0, 0, AP_OPT_DEFAULT, 0);
  return std::pair<Automaton, ElementMap>(Automaton(automaton), ElementMap(elementMap));
}

Anml::~Anml(
)
{
  if (m_anml != 0) {
    AP_DestroyAnml(m_anml);
  }
  m_anml = 0;
}

} // namespace ap
