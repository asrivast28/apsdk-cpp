#ifndef APSDK_APCALL_HPP_
#define APSDK_APCALL_HPP_

#include <stdexcept>
#include <string>

namespace ap {

template<typename Func, Func func>
class APCall {
public:
  APCall(const char* funcName)
    : m_func(func), m_funcName(funcName)
  { }

  template <typename... Args>
  int 
  operator()(Args&&... args)
  {
    int error = m_func(std::forward<Args>(args)...);
    if (error < 0) {
      throw std::runtime_error("Error " + std::to_string(error) + " in call to " + m_funcName + ".");
    }
    return error;
  }

private:
  Func m_func;
  std::string m_funcName;
}; // class APCall

} // namespace ap

#define APCALL_CHECK(FUNC) APCall<decltype(&FUNC), &FUNC>(#FUNC)

#endif // APSDK_APCALL_HPP_
