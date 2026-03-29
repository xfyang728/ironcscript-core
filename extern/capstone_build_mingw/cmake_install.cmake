# Install script for directory: D:/MyCode/CScriptEngine/capstone_src

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/capstone")
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

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "C:/msys64/mingw64/bin/objdump.exe")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/capstone" TYPE FILE FILES
    "D:/MyCode/CScriptEngine/capstone_src/include/capstone/aarch64.h"
    "D:/MyCode/CScriptEngine/capstone_src/include/capstone/arm64.h"
    "D:/MyCode/CScriptEngine/capstone_src/include/capstone/arm.h"
    "D:/MyCode/CScriptEngine/capstone_src/include/capstone/capstone.h"
    "D:/MyCode/CScriptEngine/capstone_src/include/capstone/cs_operand.h"
    "D:/MyCode/CScriptEngine/capstone_src/include/capstone/evm.h"
    "D:/MyCode/CScriptEngine/capstone_src/include/capstone/wasm.h"
    "D:/MyCode/CScriptEngine/capstone_src/include/capstone/mips.h"
    "D:/MyCode/CScriptEngine/capstone_src/include/capstone/ppc.h"
    "D:/MyCode/CScriptEngine/capstone_src/include/capstone/x86.h"
    "D:/MyCode/CScriptEngine/capstone_src/include/capstone/sparc.h"
    "D:/MyCode/CScriptEngine/capstone_src/include/capstone/systemz.h"
    "D:/MyCode/CScriptEngine/capstone_src/include/capstone/systemz_compatibility.h"
    "D:/MyCode/CScriptEngine/capstone_src/include/capstone/xcore.h"
    "D:/MyCode/CScriptEngine/capstone_src/include/capstone/m68k.h"
    "D:/MyCode/CScriptEngine/capstone_src/include/capstone/tms320c64x.h"
    "D:/MyCode/CScriptEngine/capstone_src/include/capstone/m680x.h"
    "D:/MyCode/CScriptEngine/capstone_src/include/capstone/mos65xx.h"
    "D:/MyCode/CScriptEngine/capstone_src/include/capstone/bpf.h"
    "D:/MyCode/CScriptEngine/capstone_src/include/capstone/riscv.h"
    "D:/MyCode/CScriptEngine/capstone_src/include/capstone/sh.h"
    "D:/MyCode/CScriptEngine/capstone_src/include/capstone/tricore.h"
    "D:/MyCode/CScriptEngine/capstone_src/include/capstone/platform.h"
    "D:/MyCode/CScriptEngine/capstone_src/include/capstone/sh.h"
    "D:/MyCode/CScriptEngine/capstone_src/include/capstone/alpha.h"
    "D:/MyCode/CScriptEngine/capstone_src/include/capstone/hppa.h"
    "D:/MyCode/CScriptEngine/capstone_src/include/capstone/loongarch.h"
    "D:/MyCode/CScriptEngine/capstone_src/include/capstone/xtensa.h"
    "D:/MyCode/CScriptEngine/capstone_src/include/capstone/arc.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "D:/MyCode/CScriptEngine/capstone_build_mingw/capstone.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/capstone" TYPE FILE FILES
    "D:/MyCode/CScriptEngine/capstone_build_mingw/capstone-config.cmake"
    "D:/MyCode/CScriptEngine/capstone_build_mingw/capstone-config-version.cmake"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "D:/MyCode/CScriptEngine/capstone_build_mingw/libcapstone.a")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/capstone/capstone-targets.cmake")
    file(DIFFERENT _cmake_export_file_changed FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/capstone/capstone-targets.cmake"
         "D:/MyCode/CScriptEngine/capstone_build_mingw/CMakeFiles/Export/a9b5d84ad64c19ad8b017b7d94696c98/capstone-targets.cmake")
    if(_cmake_export_file_changed)
      file(GLOB _cmake_old_config_files "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/capstone/capstone-targets-*.cmake")
      if(_cmake_old_config_files)
        string(REPLACE ";" ", " _cmake_old_config_files_text "${_cmake_old_config_files}")
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/capstone/capstone-targets.cmake\" will be replaced.  Removing files [${_cmake_old_config_files_text}].")
        unset(_cmake_old_config_files_text)
        file(REMOVE ${_cmake_old_config_files})
      endif()
      unset(_cmake_old_config_files)
    endif()
    unset(_cmake_export_file_changed)
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/capstone" TYPE FILE FILES "D:/MyCode/CScriptEngine/capstone_build_mingw/CMakeFiles/Export/a9b5d84ad64c19ad8b017b7d94696c98/capstone-targets.cmake")
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/capstone" TYPE FILE FILES "D:/MyCode/CScriptEngine/capstone_build_mingw/CMakeFiles/Export/a9b5d84ad64c19ad8b017b7d94696c98/capstone-targets-release.cmake")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "D:/MyCode/CScriptEngine/capstone_build_mingw/cstool.exe")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/cstool.exe" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/cstool.exe")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "C:/msys64/mingw64/bin/strip.exe" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/cstool.exe")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "D:/MyCode/CScriptEngine/capstone_build_mingw/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
