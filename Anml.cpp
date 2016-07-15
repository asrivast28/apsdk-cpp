#include "Anml.hpp"

#include "AnmlMacro.hpp"
#include "AnmlNetwork.hpp"


namespace ap {

Anml::Anml(
)
{
  m_anml = AP_CreateAnml();
}

Anml::Anml(
  const Anml&& other
)
{
  m_anml = other.m_anml;
}

AnmlMacro
Anml::loadMacro(
  const std::string& fileName
)
{
  ap_macro_def_t* macro = 0;
  AP_LoadAnmlMacro(m_anml, macro, 0, fileName.c_str(), 0, AP_OPT_DEFAULT, 0);
  return AnmlMacro(macro);
}


AnmlNetwork
Anml::createNetwork(
  const std::string& anmlId
)
{
  ap_anml_network_t* network = 0;
  AP_CreateAutomataNetwork(m_anml, network, anmlId.c_str());
  return AnmlNetwork(network);
}

void
Anml::compileMacros(
) const
{
  AP_CompileMacros(m_anml, 0, 0, 0, AP_OPT_DEFAULT, 0); 
}

Automaton
Anml::compile(
) const
{
  ap_automaton_t* automaton = 0;
  ap_element_map_t* elementMap = 0;
  AP_CompileAnml(m_anml, automaton, elementMap, 0, 0, AP_OPT_DEFAULT, 0);
  return Automaton(automaton, elementMap);
}

Anml::~Anml(
)
{
  AP_DestroyAnml(m_anml);
}

} // namespace ap
