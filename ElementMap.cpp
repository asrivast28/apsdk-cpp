#include "ElementMap.hpp"

#include "APCall.hpp"

#include <micron/ap/ap_element_map.h>
#include <micron/ap/sys/platform.h>
#if defined(LINUX32) || defined(LINUX64)
#include <fcntl.h>
#include <unistd.h>
#endif


namespace ap {

/**
 * @brief  Default constructor.
 */
ElementMap::ElementMap(
) : m_elementMap(0)
{
}

/**
 * @brief  Constructor for creating the object with a given
 *         ap_element_map_t instance.
 */
ElementMap::ElementMap(
  const ap_element_map_t& elementMap
) : m_elementMap(elementMap)
{
}

/**
 * @brief  Constructor for creating the object by reading element map
 *         from the given file.
 *
 * @param fileName  Name of the file from which element map is to be read.
 */
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
  APCALL_CHECK(AP_RestoreElementMap)(&m_elementMap, fd);
#if defined(LINUX32) || defined(LINUX64)
  close(fd);
#else
  //CloseHandle(fd);
#endif
}

/**
 * @brief  Move constructor. 
 */
ElementMap::ElementMap(
  ElementMap&& that
) : m_elementMap(that.m_elementMap)
{
  that.m_elementMap = 0;
}

/**
 * @brief  Gets element reference corresponding to the given element id.
 *
 * @param elementId  Id of the element whose element ref is to be found.
 *
 * @return  ElementRef corresponding to the reference. 
 */
ElementRef
ElementMap::getElementRef(
  const std::string& elementId
) const
{
  ap_anml_element_ref_t elementRef;
  APCALL_CHECK(AP_GetElementRefFromElementId)(m_elementMap, &elementRef, elementId.c_str());
  return ElementRef(elementRef);
}

/**
 * @brief  Saves the element map to the given file.
 *
 * @param fileName  Name of the file in which element map is to be saved.
 */
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
  APCALL_CHECK(AP_SaveElementMap)(m_elementMap, fd);
#if defined(LINUX32) || defined(LINUX64)
  close(fd);
#else
  CloseHandle(fd);
#endif
}

/**
 * @brief  Overloaded indirection operator implementation.
 *
 * @return  Returns the underlying ap_element_map_t instance.
 */
ap_element_map_t
ElementMap::operator*(
)
{
  return m_elementMap;
}

/**
 * @brief  Default destructor.
 */
ElementMap::~ElementMap(
)
{
  // Destroy the element map only if it points to a valid instance.
  if (m_elementMap != 0) {
    APCALL_CHECK(AP_DestroyElementMap)(m_elementMap);
    m_elementMap = 0;
  }
}

} // namespace ap
