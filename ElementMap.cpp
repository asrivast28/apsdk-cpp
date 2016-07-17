#include "ElementMap.hpp"

#include <micron/ap/ap_element_map.h>
#include <micron/ap/sys/platform.h>
#if defined(LINUX32) || defined(LINUX64)
#include <fcntl.h>
#include <unistd.h>
#endif


namespace ap {

ElementMap::ElementMap(
) : m_elementMap(0)
{
}

ElementMap::ElementMap(
  const ap_element_map_t& elementMap
) : m_elementMap(elementMap)
{
}

ElementMap::ElementMap(
  const std::string& fileName
) : m_elementMap(0)
{
  file_descriptor_t fd;
#if defined(LINUX32) || defined(LINUX64)
	fd = open(fileName.c_str(),O_RDONLY, S_IRUSR);
#else
	//fd = CreateFileA(fileName.c_str(), GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
#endif
  AP_RestoreElementMap(&m_elementMap, fd);
#if defined(LINUX32) || defined(LINUX64)
  close(fd);
#else
  //CloseHandle(fd);
#endif
}

ElementMap::ElementMap(
  ElementMap&& that
) : m_elementMap(that.m_elementMap)
{
  that.m_elementMap = 0;
}

ElementRef
ElementMap::getElementRef(
  const std::string& elementId
) const
{
  ap_anml_element_ref_t elementRef;
  AP_GetElementRefFromElementId(m_elementMap, &elementRef, elementId.c_str());
  return ElementRef(elementRef);
}

void
ElementMap::save(
  const std::string& fileName
) const
{
  file_descriptor_t fd;
#if defined(LINUX32) || defined(LINUX64)
	fd = open(fileName.c_str(),O_WRONLY|O_CREAT|O_TRUNC, S_IRUSR|S_IRGRP|S_IROTH|S_IWUSR);
#else
	fd = CreateFileA(fileName.c_str(), GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
#endif
  AP_SaveElementMap(m_elementMap, fd);
#if defined(LINUX32) || defined(LINUX64)
  close(fd);
#else
  CloseHandle(fd);
#endif
}

ap_element_map_t
ElementMap::operator*(
)
{
  return m_elementMap;
}

ElementMap::~ElementMap(
)
{
  if (m_elementMap != 0) {
    AP_DestroyElementMap(m_elementMap);
    m_elementMap = 0;
  }
}

} // namespace ap
