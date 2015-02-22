# Install script for directory: /Users/Wqxhouse-Mac/vrproject/CVRPlugins_xcode/calit2/vrphysics

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
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
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

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/plugins" TYPE SHARED_LIBRARY FILES "/Users/Wqxhouse-Mac/vrproject/calvr/lib/calvr-plugins/Debug/libvrphysics.dylib")
    if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/plugins/libvrphysics.dylib" AND
       NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/plugins/libvrphysics.dylib")
      execute_process(COMMAND "/opt/local/bin/install_name_tool"
        -id "libvrphysics.dylib"
        "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/plugins/libvrphysics.dylib")
    endif()
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/plugins" TYPE SHARED_LIBRARY FILES "/Users/Wqxhouse-Mac/vrproject/calvr/lib/calvr-plugins/Release/libvrphysics.dylib")
    if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/plugins/libvrphysics.dylib" AND
       NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/plugins/libvrphysics.dylib")
      execute_process(COMMAND "/opt/local/bin/install_name_tool"
        -id "libvrphysics.dylib"
        "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/plugins/libvrphysics.dylib")
    endif()
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/plugins" TYPE SHARED_LIBRARY FILES "/Users/Wqxhouse-Mac/vrproject/calvr/lib/calvr-plugins/MinSizeRel/libvrphysics.dylib")
    if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/plugins/libvrphysics.dylib" AND
       NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/plugins/libvrphysics.dylib")
      execute_process(COMMAND "/opt/local/bin/install_name_tool"
        -id "libvrphysics.dylib"
        "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/plugins/libvrphysics.dylib")
    endif()
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/plugins" TYPE SHARED_LIBRARY FILES "/Users/Wqxhouse-Mac/vrproject/calvr/lib/calvr-plugins/RelWithDebInfo/libvrphysics.dylib")
    if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/plugins/libvrphysics.dylib" AND
       NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/plugins/libvrphysics.dylib")
      execute_process(COMMAND "/opt/local/bin/install_name_tool"
        -id "libvrphysics.dylib"
        "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/plugins/libvrphysics.dylib")
    endif()
  endif()
endif()

