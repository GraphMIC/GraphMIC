# BoostNumpy
# ********************************************************************************

set(proj BoostNumpy)

if(NOT BoostNumpy_DIR)

  # Set CMake args to customize the BoostNumpy build
  # ******************************************************************************

  set(proj_DEPENDENCIES MITK)
  set(additional_cmake_args)

  list(APPEND additional_cmake_args
    -DBUILD_TESTS:BOOL=OFF
    -DBUILD_EXAMPLES:BOOL=OFF
    -DBOOST_INCLUDEDIR:PATH=${Boost_INCLUDE_DIR}
    -DBOOST_LIBRARYDIR:PATH=${Boost_LIBRARY_DIR}
    -DBoost_LIBRARY_DIR_DEBUG:PATH=${Boost_LIBRARY_DIR}
    -DBoost_LIBRARY_DIR_RELEASE:PATH=${Boost_LIBRARY_DIR}
    -DBoost_PYTHON_LIBRARY_DEBUG:PATH=${Boost_PYTHON_LIBRARY_DEBUG}
    -DBoost_PYTHON_LIBRARY_RELEASE:PATH=${Boost_PYTHON_LIBRARY_RELEASE}
    -DBoost_INCLUDE_DIR:PATH=${Boost_INCLUDE_DIR}
    -DPYTHON_EXECUTABLE:PATH=${PYTHON_EXECUTABLE}
    -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_BINARY_DIR}/${proj}/bin
  )

  ExternalProject_Add(${proj}
    GIT_REPOSITORY "https://github.com/ndarray/Boost.NumPy.git"
    CMAKE_GENERATOR ${LIB_BUILD_GENERATOR}
    ${LIB_BUILD_CMD}
    SOURCE_DIR ${CMAKE_BINARY_DIR}/${proj}/src
    BINARY_DIR ${CMAKE_BINARY_DIR}/${proj}/bin
    PREFIX ${proj}/cmake
    CMAKE_ARGS ${additional_cmake_args}
    CMAKE_CACHE_ARGS
    ${ep_common_cache_args}
    CMAKE_CACHE_DEFAULT_ARGS
    ${ep_common_cache_default_args}
    DEPENDS
    ${proj_DEPENDENCIES}
  )

  set(BOOST_NUMPY_DIR "${CMAKE_BINARY_DIR}/${proj}/bin")
  set(BOOST_NUMPY_LIBRARY "${BOOST_NUMPY_DIR}/lib/${CMAKE_SHARED_LIBRARY_PREFIX}boost_numpy${CMAKE_SHARED_LIBRARY_SUFFIX}")
  set(BOOST_NUMPY_INCLUDE_DIR "${BOOST_NUMPY_DIR}/include")

  # OS X - only: Custom post-build step to set the shared library install name.
  if (APPLE)
    ExternalProject_Add_Step(${proj} fixBoostNumpy
      COMMAND install_name_tool -change libpython2.7.dylib \@rpath/libpython2.7.dylib ${BOOST_NUMPY_LIBRARY}
      COMMAND install_name_tool -id \@rpath/libboost_numpy.dylib ${BOOST_NUMPY_LIBRARY}
      DEPENDEES install
    )
  endif(APPLE)
else()
  # The project is provided using BoostNumpy_DIR, nevertheless since other
  # projects may depend on BoostNumpy, let's add an 'empty' one
  MacroEmptyExternalProject(${proj} "${proj_DEPENDENCIES}")
endif()
