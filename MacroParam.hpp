#ifndef APSDK_MACROPARAM_HPP_
#define APSDK_MACROPARAM_HPP_

#include <micron/ap/ap_anml.h>

namespace ap {

class MacroParam {
public:
  MacroParam(
    ap_macro_param_ref_t param
  ) : m_param(param)
  { }

  ~MacroParam()
  { }

private:
  ap_macro_param_ref_t m_param;
}; // class MacroParam

} // namespace ap

#endif // APSDK_MACROPARAM_HPP_
