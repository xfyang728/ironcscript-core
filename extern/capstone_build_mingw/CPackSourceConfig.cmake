# This file will be configured to contain variables for CPack. These variables
# should be set in the CMake list file of the project before CPack module is
# included. The list of available CPACK_xxx variables and their associated
# documentation may be obtained using
#  cpack --help-variable-list
#
# Some variables are common to all generators (e.g. CPACK_PACKAGE_NAME)
# and some are specific to a generator
# (e.g. CPACK_NSIS_EXTRA_INSTALL_COMMANDS). The generator specific variables
# usually begin with CPACK_<GENNAME>_xxxx.


set(CPACK_BINARY_7Z "OFF")
set(CPACK_BINARY_IFW "OFF")
set(CPACK_BINARY_NSIS "ON")
set(CPACK_BINARY_NUGET "OFF")
set(CPACK_BINARY_WIX "OFF")
set(CPACK_BINARY_ZIP "OFF")
set(CPACK_BUILD_SOURCE_DIRS "D:/MyCode/CScriptEngine/capstone_src;D:/MyCode/CScriptEngine/capstone_build_mingw")
set(CPACK_CMAKE_GENERATOR "MinGW Makefiles")
set(CPACK_COMPONENT_UNSPECIFIED_HIDDEN "TRUE")
set(CPACK_COMPONENT_UNSPECIFIED_REQUIRED "TRUE")
set(CPACK_DEBIAN_PACKAGE_ARCHITECTURE "AMD64")
set(CPACK_DEBIAN_PACKAGE_CONTROL_EXTRA "D:/MyCode/CScriptEngine/capstone_src/packages/deb/triggers")
set(CPACK_DEBIAN_PACKAGE_DEPENDS "libc6 (>= 2.2.5)")
set(CPACK_DEBIAN_PACKAGE_FILE_NAME "libcapstone-dev_6.0.0_AMD64")
set(CPACK_DEBIAN_PACKAGE_MULTIARCH "same")
set(CPACK_DEBIAN_PACKAGE_NAME "libcapstone-dev")
set(CPACK_DEBIAN_PACKAGE_ORIGINAL_MAINTAINER "Debian Security Tools <team+pkg-security@tracker.debian.org>")
set(CPACK_DEBIAN_PACKAGE_PRIORITY "optional")
set(CPACK_DEBIAN_PACKAGE_SECTION "libdevel")
set(CPACK_DEBIAN_PACKAGE_SOURCE "capstone")
set(CPACK_DEBIAN_PACKAGE_VERSION "6.0.0")
set(CPACK_DEFAULT_PACKAGE_DESCRIPTION_FILE "D:/vcpkg/downloads/tools/cmake-3.25.1-windows/cmake-3.25.1-windows-i386/share/cmake-3.25/Templates/CPack.GenericDescription.txt")
set(CPACK_DEFAULT_PACKAGE_DESCRIPTION_SUMMARY "capstone built using CMake")
set(CPACK_DMG_PACKAGE_FILE_NAME "capstone-6.0.0")
set(CPACK_DMG_SLA_USE_RESOURCE_FILE_LICENSE "ON")
set(CPACK_GENERATOR "7Z;ZIP")
set(CPACK_IGNORE_FILES "/CVS/;/\\.svn/;/\\.bzr/;/\\.hg/;/\\.git/;\\.swp\$;\\.#;/#")
set(CPACK_INSTALLED_DIRECTORIES "D:/MyCode/CScriptEngine/capstone_src;/")
set(CPACK_INSTALL_CMAKE_PROJECTS "")
set(CPACK_INSTALL_PREFIX "C:/Program Files (x86)/capstone")
set(CPACK_MODULE_PATH "")
set(CPACK_NSIS_DISPLAY_NAME "capstone")
set(CPACK_NSIS_INSTALLER_ICON_CODE "")
set(CPACK_NSIS_INSTALLER_MUI_ICON_CODE "")
set(CPACK_NSIS_INSTALL_ROOT "$PROGRAMFILES64")
set(CPACK_NSIS_MODIFY_PATH "ON")
set(CPACK_NSIS_PACKAGE_FILE_NAME "capstone-6.0.0-Windows-x64")
set(CPACK_NSIS_PACKAGE_NAME "capstone 6.0.0")
set(CPACK_NSIS_UNINSTALL_NAME "Uninstall")
set(CPACK_OBJCOPY_EXECUTABLE "C:/msys64/mingw64/bin/objcopy.exe")
set(CPACK_OBJDUMP_EXECUTABLE "C:/msys64/mingw64/bin/objdump.exe")
set(CPACK_OUTPUT_CONFIG_FILE "D:/MyCode/CScriptEngine/capstone_build_mingw/CPackConfig.cmake")
set(CPACK_PACKAGE_CONTACT "Rot127 <unisono@quyllur.org>")
set(CPACK_PACKAGE_DEFAULT_LOCATION "/")
set(CPACK_PACKAGE_DESCRIPTION "Capstone is a lightweight multi-platform, multi-architecture disassembly framework. These are the development headers and libraries.
 Features:
 - Support hardware architectures: AArch64, ARM, Alpha, BPF, EVM, HPPA, LongArch, M680X, M68K, MOS65XX, Mips, PowerPC, RISCV, SH, Sparc, SystemZ, TMS320C64x, TriCore, WASM, x86, XCore, Xtensa.
 - Clean/simple/lightweight/intuitive architecture-neutral API.
 - Provide details on disassembled instructions (called \"decomposer\" by some others).
 - Provide some semantics of the disassembled instruction, such as list of implicit registers read & written.
 - Thread-safe by design.
 - Special support for embedding into firmware or OS kernel.
 - Distributed under the open source BSD license.")
set(CPACK_PACKAGE_DESCRIPTION_FILE "D:/vcpkg/downloads/tools/cmake-3.25.1-windows/cmake-3.25.1-windows-i386/share/cmake-3.25/Templates/CPack.GenericDescription.txt")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Lightweight multi-architecture disassembly framework - devel files")
set(CPACK_PACKAGE_FILE_NAME "capstone-6.0.0-Source")
set(CPACK_PACKAGE_HOMEPAGE_URL "https://www.capstone-engine.org/")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "capstone")
set(CPACK_PACKAGE_INSTALL_REGISTRY_KEY "capstone")
set(CPACK_PACKAGE_NAME "capstone")
set(CPACK_PACKAGE_RELOCATABLE "true")
set(CPACK_PACKAGE_VENDOR "Rot127")
set(CPACK_PACKAGE_VERSION "6.0.0")
set(CPACK_PACKAGE_VERSION_MAJOR "6")
set(CPACK_PACKAGE_VERSION_MINOR "0")
set(CPACK_PACKAGE_VERSION_PATCH "0")
set(CPACK_PROJECT_CONFIG_FILE "D:/MyCode/CScriptEngine/capstone_src/CPackConfig.cmake")
set(CPACK_READELF_EXECUTABLE "C:/msys64/mingw64/bin/readelf.exe")
set(CPACK_RESOURCE_FILE_LICENSE "D:/MyCode/CScriptEngine/capstone_src/LICENSES/LICENSE.TXT")
set(CPACK_RESOURCE_FILE_README "D:/vcpkg/downloads/tools/cmake-3.25.1-windows/cmake-3.25.1-windows-i386/share/cmake-3.25/Templates/CPack.GenericDescription.txt")
set(CPACK_RESOURCE_FILE_WELCOME "D:/vcpkg/downloads/tools/cmake-3.25.1-windows/cmake-3.25.1-windows-i386/share/cmake-3.25/Templates/CPack.GenericWelcome.txt")
set(CPACK_RPM_CHANGELOG_FILE "D:/MyCode/CScriptEngine/capstone_src/ChangeLog")
set(CPACK_RPM_PACKAGE_ARCHITECTURE "AMD64")
set(CPACK_RPM_PACKAGE_DESCRIPTION "Capstone is a lightweight multi-platform, multi-architecture disassembly framework. These are the development headers and libraries.
 Features:
 - Support hardware architectures: AArch64, ARM, Alpha, BPF, EVM, HPPA, LongArch, M680X, M68K, MOS65XX, Mips, PowerPC, RISCV, SH, Sparc, SystemZ, TMS320C64x, TriCore, WASM, x86, XCore, Xtensa.
 - Clean/simple/lightweight/intuitive architecture-neutral API.
 - Provide details on disassembled instructions (called \"decomposer\" by some others).
 - Provide some semantics of the disassembled instruction, such as list of implicit registers read & written.
 - Thread-safe by design.
 - Special support for embedding into firmware or OS kernel.
 - Distributed under the open source BSD license.")
set(CPACK_RPM_PACKAGE_FILE_NAME "capstone-devel-6.0.0.AMD64")
set(CPACK_RPM_PACKAGE_GROUP "Development/Libraries")
set(CPACK_RPM_PACKAGE_LICENSE "BSD3, LLVM")
set(CPACK_RPM_PACKAGE_NAME "capstone-devel")
set(CPACK_RPM_PACKAGE_REQUIRES "glibc >= 2.2.5")
set(CPACK_RPM_PACKAGE_SOURCES "ON")
set(CPACK_RPM_PACKAGE_VERSION "6.0.0")
set(CPACK_RPM_POST_INSTALL_SCRIPT_FILE "D:/MyCode/CScriptEngine/capstone_src/packages/rpm/postinstall.sh")
set(CPACK_RPM_POST_UNINSTALL_SCRIPT_FILE "D:/MyCode/CScriptEngine/capstone_src/packages/rpm/postinstall.sh")
set(CPACK_SET_DESTDIR "OFF")
set(CPACK_SOURCE_7Z "ON")
set(CPACK_SOURCE_GENERATOR "7Z;ZIP")
set(CPACK_SOURCE_IGNORE_FILES "/CVS/;/\\.svn/;/\\.bzr/;/\\.hg/;/\\.git/;\\.swp\$;\\.#;/#")
set(CPACK_SOURCE_INSTALLED_DIRECTORIES "D:/MyCode/CScriptEngine/capstone_src;/")
set(CPACK_SOURCE_OUTPUT_CONFIG_FILE "D:/MyCode/CScriptEngine/capstone_build_mingw/CPackSourceConfig.cmake")
set(CPACK_SOURCE_PACKAGE_FILE_NAME "capstone-6.0.0-Source")
set(CPACK_SOURCE_TOPLEVEL_TAG "Windows-x64-Source")
set(CPACK_SOURCE_ZIP "ON")
set(CPACK_STRIP_FILES "")
set(CPACK_SYSTEM_NAME "Windows-x64")
set(CPACK_THREADS "1")
set(CPACK_TOPLEVEL_TAG "Windows-x64-Source")
set(CPACK_WIX_SIZEOF_VOID_P "8")

if(NOT CPACK_PROPERTIES_FILE)
  set(CPACK_PROPERTIES_FILE "D:/MyCode/CScriptEngine/capstone_build_mingw/CPackProperties.cmake")
endif()

if(EXISTS ${CPACK_PROPERTIES_FILE})
  include(${CPACK_PROPERTIES_FILE})
endif()
