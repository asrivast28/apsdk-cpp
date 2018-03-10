/**
 * @file ElementRef.cpp
 * @brief Implementation of ElementRef functions.
 *
 * Copyright 2018 Georgia Institute of Technology
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "ElementRef.hpp"

namespace ap {

/**
 * @brief  Default constructor.
 */
ElementRef::ElementRef(
) : m_elementRef(0)
{
}

/**
 * @brief  Constructor for creating the object with a given
 *         ap_anml_element_ref_t instance.
 */
ElementRef::ElementRef(
  const ap_anml_element_ref_t& elementRef
) : m_elementRef(elementRef)
{
}

/**
 * @brief  Copy constructor.
 */
ElementRef::ElementRef(
  const ElementRef& that
) : m_elementRef(that.m_elementRef)
{
}

/**
 * @brief  Overloaded indirection operator implementation.
 *
 * @return  Returns the underlying ap_anml_element_ref_t instance.
 */
ap_anml_element_ref_t
ElementRef::operator*(
) const
{
  return m_elementRef;
}

bool
ElementRef::operator==(
  const ElementRef& that
) const
{
  return (m_elementRef == *that);
}

/**
 * @brief  Default destructor.
 */
ElementRef::~ElementRef(
)
{
  m_elementRef = 0;
}

size_t
ElementRefHasher::operator()(
  const ElementRef& elementRef
) const
{
  return std::hash<ap_anml_element_ref_t>()(*elementRef);
}

}
