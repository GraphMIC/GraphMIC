# MITK
# ********************************************************************************

set(MITK_DEPENDS)
set(proj_DEPENDENCIES)
set(proj MITK)

if(NOT MITK_DIR)

  # Create CMake options to customize the MITK build
  # ******************************************************************************

  option(MITK_USE_SUPERBUILD "Use superbuild for MITK" ON)
  option(MITK_USE_BLUEBERRY "Build the BlueBerry platform in MITK" OFF)
  option(MITK_BUILD_ALL_PLUGINS "Build all MITK plugins" OFF)
  option(MITK_BUILD_TESTING "Build the MITK unit tests" OFF)
  option(MITK_USE_CTK "Use CTK in MITK" ${MITK_USE_BLUEBERRY})
  option(MITK_USE_DCMTK "Use DCMTK in MITK" ON)
  option(MITK_USE_QT "Use Nokia's Qt library in MITK" OFF)
  option(MITK_USE_OpenCV "Use Intel's OpenCV library" ON)
  option(MITK_USE_Python "Enable Python wrapping in MITK" ON)
  option(MITK_USE_Boost "Enable Boost in MITK" ON)
  option(MITK_USE_CppUnit "Enable CppUnit in MITK" OFF)
  option(MITK_USE_GLEW "Enable GLEW in MITK" OFF)

  if(MITK_USE_BLUEBERRY AND NOT MITK_USE_CTK)
    message("Forcing MITK_USE_CTK to ON because of MITK_USE_BLUEBERRY")
    set(MITK_USE_CTK ON CACHE BOOL "Use CTK in MITK" FORCE)
  endif()

  if(MITK_USE_CTK AND NOT MITK_USE_QT)
    message("Forcing MITK_USE_QT to ON because of MITK_USE_CTK")
    set(MITK_USE_QT ON CACHE BOOL "Use Nokia's Qt library in MITK" FORCE)
  endif()

  set(MITK_USE_CableSwig ${MITK_USE_Python})
  set(MITK_USE_GDCM 1)
  set(MITK_USE_ITK 1)
  set(MITK_USE_VTK 1)

  mark_as_advanced(MITK_USE_SUPERBUILD
  )

  set(mitk_cmake_boolean_args
    MITK_USE_SUPERBUILD
    MITK_USE_BLUEBERRY
    MITK_BUILD_ALL_PLUGINS
    MITK_USE_CTK
    MITK_USE_DCMTK
    MITK_USE_QT
    MITK_USE_OpenCV
    MITK_USE_Python
    MITK_USE_Boost
    MITK_USE_CppUnit
    MITK_USE_GLEW
  )

  set(DESIRED_QT_VERSION 5)


  set(additional_mitk_cmakevars)

  # Configure the set of default pixel types
  set(MITK_ACCESSBYITK_INTEGRAL_PIXEL_TYPES
    "int, unsigned int, short, unsigned short, char, unsigned char"
  CACHE STRING "List of integral pixel types used in AccessByItk and InstantiateAccessFunction macros")

  set(MITK_ACCESSBYITK_FLOATING_PIXEL_TYPES
    "double, float"
  CACHE STRING "List of floating pixel types used in AccessByItk and InstantiateAccessFunction macros")

  set(MITK_ACCESSBYITK_COMPOSITE_PIXEL_TYPES
    ""
  CACHE STRING "List of composite pixel types used in AccessByItk and InstantiateAccessFunction macros")

  set(MITK_ACCESSBYITK_DIMENSIONS
    "2,3"
  CACHE STRING "List of dimensions used in AccessByItk and InstantiateAccessFunction macros")

  foreach(_arg MITK_ACCESSBYITK_INTEGRAL_PIXEL_TYPES MITK_ACCESSBYITK_FLOATING_PIXEL_TYPES
  MITK_ACCESSBYITK_COMPOSITE_PIXEL_TYPES MITK_ACCESSBYITK_DIMENSIONS)
  mark_as_advanced(${_arg})
  list(APPEND additional_mitk_cmakevars "-D${_arg}:STRING=${${_arg}}")
endforeach()

# Create options to inject pre-build dependencies
# ******************************************************************************

foreach(proj CTK DCMTK GDCM VTK ITK OpenCV CableSwig)
  if(MITK_USE_${proj})
    set(MITK_${proj}_DIR "${${proj}_DIR}" CACHE PATH "Path to ${proj} build directory")
    mark_as_advanced(MITK_${proj}_DIR)
    if(MITK_${proj}_DIR)
      list(APPEND additional_mitk_cmakevars "-D${proj}_DIR:PATH=${MITK_${proj}_DIR}")
    endif()
  endif()
endforeach()

set(MITK_BOOST_ROOT "${BOOST_ROOT}" CACHE PATH "Path to Boost directory")
mark_as_advanced(MITK_BOOST_ROOT)
if(MITK_BOOST_ROOT)
  list(APPEND additional_mitk_cmakevars "-DBOOST_ROOT:PATH=${MITK_BOOST_ROOT}")
endif()

if(MITK_USE_Boost)
  option(MITK_USE_SYSTEM_Boost "Use the system Boost" OFF)
  set(MITK_USE_Boost_LIBRARIES "python" CACHE STRING "A semi-colon separated list of required Boost libraries")
  list(APPEND additional_mitk_cmakevars "-DMITK_USE_Boost_LIBRARIES:STRING=${MITK_USE_Boost_LIBRARIES}")
endif()

set(MITK_SOURCE_DIR "" CACHE PATH "MITK source code location. If empty, MITK will be cloned from MITK_GIT_REPOSITORY")
  set(MITK_GIT_REPOSITORY "https://github.com/MITK/MITK.git" CACHE STRING "The git repository for cloning MITK")
  set(MITK_GIT_TAG "18c26d1" CACHE STRING "The git tag/hash to be used when cloning from MITK_GIT_REPOSITORY")
  mark_as_advanced(MITK_SOURCE_DIR MITK_GIT_REPOSITORY MITK_GIT_TAG)

  # Create the final variable containing superbuild boolean args
  # ******************************************************************************

  set(mitk_boolean_args)
  foreach(mitk_cmake_arg ${mitk_cmake_boolean_args})
    list(APPEND mitk_boolean_args -D${mitk_cmake_arg}:BOOL=${${mitk_cmake_arg}})
  endforeach()

  # Additional MITK CMake variables
  # ******************************************************************************

  if(MITK_USE_QT AND QT_QMAKE_EXECUTABLE)
    list(APPEND additional_mitk_cmakevars "-DQT_QMAKE_EXECUTABLE:FILEPATH=${QT_QMAKE_EXECUTABLE}")
  endif()

  if(MITK_USE_CTK)
    list(APPEND additional_mitk_cmakevars "-DGIT_EXECUTABLE:FILEPATH=${GIT_EXECUTABLE}")
  endif()

  if(MITK_INITIAL_CACHE_FILE)
    list(APPEND additional_mitk_cmakevars "-DMITK_INITIAL_CACHE_FILE:INTERNAL=${MITK_INITIAL_CACHE_FILE}")
  endif()

  set(MITK_BINARY_DIR ${proj}-build)

  if(MITK_USE_Python)
    set(MITK_PYTHON_MAJOR_VERSION 2)
    set(MITK_PYTHON_MINOR_VERSION 7)

    if(UNIX)
      set(Python_DIR "${CMAKE_BINARY_DIR}/${proj}/bin/${ep_prefix}")
      set(PYTHON_EXECUTABLE "${Python_DIR}/bin/python${CMAKE_EXECUTABLE_SUFFIX}")
      set(PYTHON_INCLUDE_DIR "${Python_DIR}/include/python${MITK_PYTHON_MAJOR_VERSION}.${MITK_PYTHON_MINOR_VERSION}")
      set(PYTHON_INCLUDE_DIR2 "${PYTHON_INCLUDE_DIR}")
      set(PYTHON_LIBRARY "${Python_DIR}/lib/${CMAKE_SHARED_LIBRARY_PREFIX}python${MITK_PYTHON_MAJOR_VERSION}.${MITK_PYTHON_MINOR_VERSION}${CMAKE_SHARED_LIBRARY_SUFFIX}")
      set(MITK_PYTHON_SITE_DIR "${Python_DIR}/lib/python${MITK_PYTHON_MAJOR_VERSION}.${MITK_PYTHON_MINOR_VERSION}/site-packages")
    else()
      set(Python_DIR "${CMAKE_BINARY_DIR}/${proj}/bin/${ep_prefix}/lib/python${MITK_PYTHON_MAJOR_VERSION}.${MITK_PYTHON_MINOR_VERSION}")
      set(PYTHON_EXECUTABLE "${Python_DIR}/bin/python${CMAKE_EXECUTABLE_SUFFIX}")
      set(PYTHON_INCLUDE_DIR "${Python_DIR}/include")
      set(PYTHON_INCLUDE_DIR2 "${PYTHON_INCLUDE_DIR}")
      set(PYTHON_LIBRARY "${Python_DIR}/libs/python${MITK_PYTHON_MAJOR_VERSION}${MITK_PYTHON_MINOR_VERSION}.lib")
      set(MITK_PYTHON_SITE_DIR "${Python_DIR}/Lib/site-packages")
    endif()
  endif()

  if(MITK_USE_Boost AND MITK_USE_Python)
    set(Boost_LIBRARY_DIR "${CMAKE_BINARY_DIR}/${proj}/bin/${ep_prefix}/lib")
    set(Boost_INCLUDE_DIR "${CMAKE_BINARY_DIR}/${proj}/bin/${ep_prefix}/include")
    if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
      set(Boost_PYTHON_LIBRARY_DEBUG "${CMAKE_BINARY_DIR}/${proj}/bin/${ep_prefix}/lib/${CMAKE_SHARED_LIBRARY_PREFIX}boost_python-mt-d${CMAKE_SHARED_LIBRARY_SUFFIX}")
      set(Boost_PYTHON_LIBRARY_RELEASE "${Boost_PYTHON_LIBRARY_DEBUG}")
    else()
      set(Boost_PYTHON_LIBRARY_DEBUG "${CMAKE_BINARY_DIR}/${proj}/bin/${ep_prefix}/lib/${CMAKE_SHARED_LIBRARY_PREFIX}boost_python-mt${CMAKE_SHARED_LIBRARY_SUFFIX}")
      set(Boost_PYTHON_LIBRARY_RELEASE "${Boost_PYTHON_LIBRARY_DEBUG}")
    endif()
  endif()

  set(proj_DEPENDENCIES)
  set(MITK_DEPENDS ${proj})

  if(NOT MITK_SOURCE_DIR)
    set(mitk_source_location
      SOURCE_DIR ${CMAKE_BINARY_DIR}/${proj}/src
      GIT_REPOSITORY ${MITK_GIT_REPOSITORY}
      GIT_TAG ${MITK_GIT_TAG}
    )
  else()
    set(mitk_source_location
      SOURCE_DIR ${MITK_SOURCE_DIR}
    )
  endif()

  set(_patch_command patch -p1 < ${GRAPHMIC_PATCH_DIR}/MITK-2015.05.99.patch)

  ExternalProject_Add(${proj}
    CMAKE_GENERATOR ${LIB_BUILD_GENERATOR}
    ${mitk_source_location}
    BINARY_DIR ${CMAKE_BINARY_DIR}/${proj}/bin
    PREFIX ${proj}/${ep_suffix}
    PATCH_COMMAND ${_patch_command}
    ${LIB_BUILD_CMD}
    INSTALL_COMMAND ""
    CMAKE_ARGS
    ${ep_common_args}
    ${mitk_boolean_args}
    ${additional_mitk_cmakevars}
    -DBUILD_SHARED_LIBS:BOOL=ON
    -DBUILD_TESTING:BOOL=${MITK_BUILD_TESTING}
    CMAKE_CACHE_ARGS
    ${ep_common_cache_args}
    CMAKE_CACHE_DEFAULT_ARGS
    ${ep_common_cache_default_args}
    DEPENDS
    ${proj_DEPENDENCIES}
  )

  set(MITK_DIR "${CMAKE_BINARY_DIR}/${proj}/bin/${MITK_BINARY_DIR}")

else()

  # The project is provided using MITK_DIR, nevertheless since other
  # projects may depend on MITK, let's add an 'empty' one
  MacroEmptyExternalProject(${proj} "${proj_DEPENDENCIES}")

  # Further, do some sanity checks in the case of a pre-built MITK
  set(my_itk_dir ${ITK_DIR})
  set(my_vtk_dir ${VTK_DIR})
  set(my_qmake_executable ${QT_QMAKE_EXECUTABLE})

  find_package(MITK REQUIRED)

  if(my_itk_dir AND ITK_DIR)
    if(NOT my_itk_dir STREQUAL ${ITK_DIR})
      message(FATAL_ERROR "ITK packages do not match:\n   ${MY_PROJECT_NAME}: ${my_itk_dir}\n  MITK: ${ITK_DIR}")
    endif()
  endif()

  if(my_vtk_dir AND VTK_DIR)
    if(NOT my_vtk_dir STREQUAL ${VTK_DIR})
      message(FATAL_ERROR "VTK packages do not match:\n   ${MY_PROJECT_NAME}: ${my_vtk_dir}\n  MITK: ${VTK_DIR}")
    endif()
  endif()

  if(my_qmake_executable AND MITK_QMAKE_EXECUTABLE)
    if(NOT my_qmake_executable STREQUAL ${MITK_QMAKE_EXECUTABLE})
      message(FATAL_ERROR "Qt qmake does not match:\n   ${MY_PROJECT_NAME}: ${my_qmake_executable}\n  MITK: ${MITK_QMAKE_EXECUTABLE}")
    endif()
  endif()

endif()

