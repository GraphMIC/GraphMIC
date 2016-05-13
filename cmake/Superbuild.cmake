# GraphMIC options
# ******************************************************************************
set(GRAPHMIC_BUILD_TESTING false CACHE BOOL "build graphmic tests")
set(GRAPHMIC_BUILD_MATH_NODES false CACHE BOOL "build math nodes")
set(GRAPHMIC_BUILD_CV_NODES false CACHE BOOL "build OpenCV nodes")
set(GRAPHMIC_BUILD_ITK_NODES false CACHE BOOL "build ITK nodes")

# ExternalProjects
# ******************************************************************************

set(external_projects
  MITK
)

set(EXTERNAL_MITK_DIR "${MITK_DIR}" CACHE PATH "Path to MITK build directory")
mark_as_advanced(EXTERNAL_MITK_DIR)
if(EXTERNAL_MITK_DIR)
  set(MITK_DIR ${EXTERNAL_MITK_DIR})
endif()

# Look for git early on, if needed
if(NOT MITK_DIR AND MITK_USE_CTK AND NOT CTK_DIR)
  find_package(Git REQUIRED)
endif()

find_program(PATCH_COMMAND patch)
if((NOT PATCH_COMMAND OR NOT EXISTS ${PATCH_COMMAND}) AND WIN32)
  downloadFile(${MITK_THIRDPARTY_DOWNLOAD_PREFIX_URL}/patch.exe
               ${CMAKE_CURRENT_BINARY_DIR}/patch.exe)
  find_program(PATCH_COMMAND patch ${CMAKE_CURRENT_BINARY_DIR})
endif()
if(NOT PATCH_COMMAND)
  message(FATAL_ERROR "No patch program found.")
endif()

# External project settings
# ******************************************************************************

include(ExternalProject)

set(ep_base "${CMAKE_BINARY_DIR}/CMakeExternals")
set_property(DIRECTORY PROPERTY EP_BASE ${ep_base})

set(ep_install_dir "${CMAKE_BINARY_DIR}/CMakeExternals/Install")
set(ep_suffix "cmake")
set(ep_prefix "ep")
set(ep_build_shared_libs ON)
set(ep_build_testing OFF)

# Compute -G arg for configuring external projects with the same CMake generator:
if(CMAKE_EXTRA_GENERATOR)
  set(gen "${CMAKE_EXTRA_GENERATOR} - ${CMAKE_GENERATOR}")
else()
  set(gen "${CMAKE_GENERATOR}")
endif()

# Use this value where semi-colons are needed in ep_add args:
set(sep "^^")

if(MSVC_VERSION)
  set(ep_common_C_FLAGS "${CMAKE_C_FLAGS} /bigobj /MP")
  set(ep_common_CXX_FLAGS "${CMAKE_CXX_FLAGS} /bigobj /MP")
endif()

set(ep_common_args
  -DBUILD_TESTING:BOOL=${ep_build_testing}
  -DCMAKE_INSTALL_PREFIX:PATH=${ep_install_dir}
  -DBUILD_SHARED_LIBS:BOOL=${ep_build_shared_libs}
  -DCMAKE_BUILD_TYPE:STRING=${CMAKE_BUILD_TYPE}
  -DCMAKE_C_COMPILER:FILEPATH=${CMAKE_C_COMPILER}
  -DCMAKE_CXX_COMPILER:FILEPATH=${CMAKE_CXX_COMPILER}
  -DCMAKE_C_FLAGS:STRING=${CMAKE_C_FLAGS}
  -DCMAKE_CXX_FLAGS:STRING=${CMAKE_CXX_FLAGS}
  # debug flags
  -DCMAKE_CXX_FLAGS_DEBUG:STRING=${CMAKE_CXX_FLAGS_DEBUG}
  -DCMAKE_C_FLAGS_DEBUG:STRING=${CMAKE_C_FLAGS_DEBUG}
  # release flags
  -DCMAKE_CXX_FLAGS_RELEASE:STRING=${CMAKE_CXX_FLAGS_RELEASE}
  -DCMAKE_C_FLAGS_RELEASE:STRING=${CMAKE_C_FLAGS_RELEASE}
  # relwithdebinfo
  -DCMAKE_CXX_FLAGS_RELWITHDEBINFO:STRING=${CMAKE_CXX_FLAGS_RELWITHDEBINFO}
  -DCMAKE_C_FLAGS_RELWITHDEBINFO:STRING=${CMAKE_C_FLAGS_RELWITHDEBINFO}
  # link flags
  -DCMAKE_EXE_LINKER_FLAGS:STRING=${CMAKE_EXE_LINKER_FLAGS}
  -DCMAKE_SHARED_LINKER_FLAGS:STRING=${CMAKE_SHARED_LINKER_FLAGS}
  -DCMAKE_MODULE_LINKER_FLAGS:STRING=${CMAKE_MODULE_LINKER_FLAGS}

)

set(ep_common_cache_args
)

set(ep_common_cache_default_args
  "-DCMAKE_PREFIX_PATH:PATH=${CMAKE_PREFIX_PATH}"
  "-DCMAKE_INCLUDE_PATH:PATH=${CMAKE_INCLUDE_PATH}"
  "-DCMAKE_LIBRARY_PATH:PATH=${CMAKE_LIBRARY_PATH}"
)

set(GRAPHMIC_PATCH_DIR ${CMAKE_CURRENT_SOURCE_DIR}/cmakeExternals/patch)
set(GRAPHMIC_EXTLIB_BUILD_DIR ${PROJECT_BUILD_DIR}/external)

file(MAKE_DIRECTORY ${GRAPHMIC_EXTLIB_BUILD_DIR})

set(LIB_BUILD_GENERATOR "${CMAKE_GENERATOR}")
set(LIB_BUILD_CMD "")

# Suggest UNIX Makefiles for external libraries
if(UNIX)
  set(LIB_BUILD_CORES 1 CACHE INTEGER "Number of build cores")
  set(LIB_BUILD_GENERATOR "Unix Makefiles")# CACHE STRING "Build Generator")
  set(LIB_BUILD_CMD BUILD_COMMAND make -j${LIB_BUILD_CORES})
endif()

# Include external projects
include(CMakeExternals/MITK.cmake)
include(CMakeExternals/BoostNumpy.cmake)

# Project Configure
# ******************************************************************************

set(GRAPHMIC_QT_VERSION "5.6.0" CACHE STRING "Qt Version")
set(GRAPHMIC_QT_MODUlES Core Gui Widgets Quick Qml Concurrent Network DBus PrintSupport)

find_package(Qt5 ${GRAPHMIC_QT_VERSION} EXACT CONFIG REQUIRED ${GRAPHMIC_QT_MODUlES})

set(proj ${MY_PROJECT_NAME})

ExternalProject_Add(${proj}
  CMAKE_GENERATOR ${gen}
  CMAKE_CACHE_ARGS
  -DGRAPHMIC_USE_SUPERBUILD:BOOL=OFF
  -DGRAPHMIC_CONFIGURED_VIA_SUPERBUILD:BOOL=ON
  # ----------------- Miscellaneous ---------------
  -DGRAPHMIC_SUPERBUILD_BINARY_DIR:PATH=${PROJECT_BINARY_DIR}
  -DMITK_DIR:PATH=${MITK_DIR}
  -DQT_QMAKE_EXECUTABLE:FILEPATH=${QT_QMAKE_EXECUTABLE}
  -DQt5_DIR:PATH=${Qt5_DIR}
  -DBOOST_NUMPY_DIR:PATH=${BOOST_NUMPY_DIR}
  -DBOOST_NUMPY_LIBRARY:PATH=${BOOST_NUMPY_LIBRARY}
  -DBOOST_NUMPY_INCLUDE_DIR:PATH=${BOOST_NUMPY_INCLUDE_DIR}
  -DBoost_LIBRARY_DIR:PATH=${Boost_LIBRARY_DIR}
  -DBoost_INCLUDE_DIR:PATH=${Boost_INCLUDE_DIR}
  -DBoost_PYTHON_LIBRARY_DEBUG:PATH=${Boost_PYTHON_LIBRARY_DEBUG}
  -DBoost_PYTHON_LIBRARY_RELEASE:PATH=${Boost_PYTHON_LIBRARY_RELEASE}
  -DPYTHON_INCLUDE_DIR:PATH=${PYTHON_INCLUDE_DIR}
  -DPYTHON_LIBRARY:PATH=${PYTHON_LIBRARY}
  -DGRAPHMIC_BUILD_ITK_NODES:BOOL=${GRAPHMIC_BUILD_ITK_NODES}
  -DGRAPHMIC_BUILD_MATH_NODES:BOOL=${GRAPHMIC_BUILD_MATH_NODES}
  -DGRAPHMIC_BUILD_CV_NODES:BOOL=${GRAPHMIC_BUILD_CV_NODES}
  -DGRAPHMIC_BUILD_TESTING:BOOL=${GRAPHMIC_BUILD_TESTING}
  SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}
  BINARY_DIR ${CMAKE_BINARY_DIR}/${MY_PROJECT_NAME}
  DEPENDS
  BoostNumpy
)

if (APPLE)
  ExternalProject_Add_Step(${proj} fixBoostNumpy
    COMMAND install_name_tool -change libboost_numpy.dylib \@rpath/libboost_numpy.dylib ${PROJECT_BUILD_DIR}/libGraphMICLibPython.dylib
    DEPENDEES build
  )
endif(APPLE)
