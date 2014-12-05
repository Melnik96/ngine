# Install script for directory: /home/melnik/projects/nutty/ngine/source

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "0")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/ngine" TYPE DIRECTORY FILES "/home/melnik/projects/nutty/ngine/source/./" FILES_MATCHING REGEX "/[^/]*\\.h$")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/melnik/projects/nutty/ngine/build/source/render/cmake_install.cmake")
  include("/home/melnik/projects/nutty/ngine/build/source/scenegraph/cmake_install.cmake")
  include("/home/melnik/projects/nutty/ngine/build/source/iohand/cmake_install.cmake")
  include("/home/melnik/projects/nutty/ngine/build/source/math/cmake_install.cmake")
  include("/home/melnik/projects/nutty/ngine/build/source/physics/cmake_install.cmake")
  include("/home/melnik/projects/nutty/ngine/build/source/sound/cmake_install.cmake")
  include("/home/melnik/projects/nutty/ngine/build/source/core/cmake_install.cmake")
  include("/home/melnik/projects/nutty/ngine/build/source/import/cmake_install.cmake")
  include("/home/melnik/projects/nutty/ngine/build/source/network/cmake_install.cmake")
  include("/home/melnik/projects/nutty/ngine/build/source/gui/cmake_install.cmake")
  include("/home/melnik/projects/nutty/ngine/build/source/mesh/cmake_install.cmake")

endif()

