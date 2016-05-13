# project setup
# ******************************************************************************
cmake_minimum_required(VERSION 3.0)

set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${CMAKE_CURRENT_SOURCE_DIR}/cmake;${CMAKE_CURRENT_SOURCE_DIR}/cmakeExternals;")
include(Functions)

set(MY_PROJECT_NAME "GraphMIC")

# build type
# ******************************************************************************

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Setting build type to 'Debug' as none was specified.")
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build." FORCE)

  # Set the possible values of build type for cmake-gui
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY
  STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

# project directories
# ******************************************************************************
set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/install)
SET(PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(PROJECT_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR})
set(PROJECT_INSTALL_DIR ${CMAKE_INSTALL_PREFIX})
set(PROJECT_BUILD_DIR ${CMAKE_CURRENT_SOURCE_DIR}/build)

message(STATUS "  Project directories:")
message(STATUS "   - project source dir: " ${PROJECT_SOURCE_DIR})
message(STATUS "   - project binary dir: " ${PROJECT_BINARY_DIR})
message(STATUS "   - project build dir: " ${PROJECT_BUILD_DIR})
message(STATUS "   - project install dir: " ${PROJECT_INSTALL_DIR})

# output directories
# ******************************************************************************
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BUILD_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BUILD_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BUILD_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${PROJECT_BUILD_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${PROJECT_BUILD_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${PROJECT_BUILD_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${PROJECT_BUILD_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${PROJECT_BUILD_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PROJECT_BUILD_DIR})

message(STATUS "  Output directory: " ${PROJECT_BUILD_DIR})


# superbuild option
# ******************************************************************************

option(GRAPHMIC_USE_SUPERBUILD "Build ${MY_PROJECT_NAME} and the projects it depends on via SuperBuild.cmake." OFF)

if(GRAPHMIC_USE_SUPERBUILD)
  project(${MY_PROJECT_NAME}-Superbuild)
else()
  project(${MY_PROJECT_NAME})
endif()

if(GRAPHMIC_USE_SUPERBUILD)
  include(SuperBuild)
  return()
endif()

# graphmic
# ******************************************************************************

list(APPEND CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -stdlib=libc++")
add_definitions(-DUSE_INSTALL_TARGET)

# moc
# ******************************************************************************
set(CMAKE_AUTOMOC true)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY AUTOMOC_TARGETS_FOLDER "AUTOMOC")

# project meta information
# ******************************************************************************
set(GRAPHMIC_VERSION_MAJOR 1)
set(GRAPHMIC_VERSION_MINOR 0)
set(GRAPHMIC_VERSION_PATCH 0)
set(GRAPHMIC_ORG_NAME graphmic)
set(GRAPHMIC_ORG_DOMAIN org)

message(STATUS "> Configure project: GraphMIC (v${GRAPHMIC_VERSION_MAJOR}.${GRAPHMIC_VERSION_MINOR}.${GRAPHMIC_VERSION_PATCH})")

# rpath
# ******************************************************************************
if(APPLE)
  set(CMAKE_SKIP_BUILD_RPATH false)
  set(CMAKE_BUILD_WITH_INSTALL_RPATH false)
  set(CMAKE_INSTALL_RPATH "@executable_path/../Frameworks")
  set(CMAKE_INSTALL_RPATH_USE_LINK_PATH true)

  message(STATUS "  rpath: " ${CMAKE_INSTALL_RPATH})
endif()

# libraries
# ******************************************************************************

set(GRAPHMIC_QT_VERSION "5.6.0" CACHE STRING "Qt Version")
set(GRAPHMIC_QT_MODUlES Core Gui Widgets Quick Qml Concurrent Network DBus PrintSupport)
set(GRAPHMIC_INTERNAL_LIBRARY_TARGETS)

find_package(Qt5 ${GRAPHMIC_QT_VERSION} EXACT CONFIG REQUIRED ${GRAPHMIC_QT_MODUlES})
add_definitions(${QT_DEFINITIONS})

find_package(MITK 2014.10.99 REQUIRED)
link_directories(${MITK_LINK_DIRECTORIES})

if(${GRAPHMIC_CONFIGURED_VIA_SUPERBUILD})
else()
  find_package(BoostNumPy REQUIRED)
  find_package(Boost COMPONENTS python REQUIRED)

  set(GRAPHMIC_BUILD_TESTING false CACHE BOOL "build graphmic tests")
  set(GRAPHMIC_BUILD_MATH_NODES false CACHE BOOL "build math nodes")
  set(GRAPHMIC_BUILD_CV_NODES false CACHE BOOL "build OpenCV nodes")
  set(GRAPHMIC_BUILD_ITK_NODES false CACHE BOOL "build ITK nodes")
endif()

# boost - python - numpy paths
# ******************************************************************************

message(STATUS "  Boost Numpy paths:")
message(STATUS "   - Boost Numpy lib: " ${BOOST_NUMPY_LIBRARY})
message(STATUS "   - Boost Numpy include: " ${BOOST_NUMPY_INCLUDE_DIR})

message(STATUS "  Boost paths:")
message(STATUS "   - Boost lib dir: " ${BOOST_LIBRARYDIR})
message(STATUS "   - Boost include dir: " ${Boost_INCLUDE_DIR})
message(STATUS "   - Boost debug lib: " ${Boost_PYTHON_LIBRARY_DEBUG})
message(STATUS "   - Boost release lib: " ${Boost_PYTHON_LIBRARY_RELEASE})

message(STATUS "  Python paths:")
message(STATUS "   - Python lib: " ${PYTHON_LIBRARY})
message(STATUS "   - Python include: " ${PYTHON_INCLUDE_DIR})

# qt paths
# ******************************************************************************
set(GRAPHMIC_QT_ROOT_DIRECTORY  ${Qt5_DIR}/../../..)
set(GRAPHMIC_QT_BINARY_DIRECTORY ${GRAPHMIC_QT_ROOT_DIRECTORY}/bin)
set(GRAPHMIC_QT_QML_DIRECTORY ${GRAPHMIC_QT_ROOT_DIRECTORY}/qml)
set(GRAPHMIC_QT_PLUGINS_DIRECTORY ${GRAPHMIC_QT_ROOT_DIRECTORY}/plugins)
set(GRAPHMIC_QT_LIB_DIRECTORY ${GRAPHMIC_QT_ROOT_DIRECTORY}/lib)

message(STATUS "  Qt paths:")
message(STATUS "   - Qt root dir: " ${GRAPHMIC_QT_ROOT_DIRECTORY})
message(STATUS "   - Qt binary dir: " ${GRAPHMIC_QT_BINARY_DIRECTORY})
message(STATUS "   - Qt qml dir: " ${GRAPHMIC_QT_QML_DIRECTORY})
message(STATUS "   - Qt plugins dir: " ${GRAPHMIC_QT_PLUGINS_DIRECTORY})
message(STATUS "   - Qt lib dir: " ${GRAPHMIC_QT_LIB_DIRECTORY})

# boost numpy paths
# ******************************************************************************
set(GRAPHMIC_BOOSTNUMPY_LIB_DIRECTORY ${BOOST_NUMPY_LIBRARY})

# mitk paths
# ******************************************************************************
set(GRAPHMIC_MITK_LIB_DIRECTORY ${MITK_DIR}/lib)
set(GRAPHMIC_MITK_EP_LIB_DIRECTORY ${MITK_DIR}/../ep/lib)

message(STATUS "  MITK paths:")
message(STATUS "   - MITK lib dir: " ${GRAPHMIC_MITK_LIB_DIRECTORY})
message(STATUS "   - MITK ep dir: " ${GRAPHMIC_MITK_EP_LIB_DIRECTORY})

# targets
# ******************************************************************************
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/targets/core.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/targets/python.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/targets/preview.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/targets/viewer.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/targets/logic.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/targets/app.cmake)

if(GRAPHMIC_BUILD_TESTING)
  include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/targets/test.cmake)
endif()
