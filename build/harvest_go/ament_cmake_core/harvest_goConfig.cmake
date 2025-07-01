# generated from ament/cmake/core/templates/nameConfig.cmake.in

# prevent multiple inclusion
if(_harvest_go_CONFIG_INCLUDED)
  # ensure to keep the found flag the same
  if(NOT DEFINED harvest_go_FOUND)
    # explicitly set it to FALSE, otherwise CMake will set it to TRUE
    set(harvest_go_FOUND FALSE)
  elseif(NOT harvest_go_FOUND)
    # use separate condition to avoid uninitialized variable warning
    set(harvest_go_FOUND FALSE)
  endif()
  return()
endif()
set(_harvest_go_CONFIG_INCLUDED TRUE)

# output package information
if(NOT harvest_go_FIND_QUIETLY)
  message(STATUS "Found harvest_go: 0.1.0 (${harvest_go_DIR})")
endif()

# warn when using a deprecated package
if(NOT "" STREQUAL "")
  set(_msg "Package 'harvest_go' is deprecated")
  # append custom deprecation text if available
  if(NOT "" STREQUAL "TRUE")
    set(_msg "${_msg} ()")
  endif()
  # optionally quiet the deprecation message
  if(NOT ${harvest_go_DEPRECATED_QUIET})
    message(DEPRECATION "${_msg}")
  endif()
endif()

# flag package as ament-based to distinguish it after being find_package()-ed
set(harvest_go_FOUND_AMENT_PACKAGE TRUE)

# include all config extra files
set(_extras "")
foreach(_extra ${_extras})
  include("${harvest_go_DIR}/${_extra}")
endforeach()
