SET(_BOOST_NUMPY_SEARCH
  $ENV{PROGRAMFILES}/boost
  $ENV{PROGRAMFILES}/boost.numpy
  $ENV{PROGRAMW6432}/boost
  $ENV{PROGRAMW6432}/boost.numpy
  $ENV{BOOST_ROOT}
  $ENV{BOOST_DIR}
  $ENV{BOOST_NUMPY_DIR}
  ${BoostNumpy_DIR}
  )

find_path(BOOST_NUMPY_INCLUDE_DIR boost/numpy.hpp PATHS ${_BOOST_NUMPY_SEARCH} PATH_SUFFIXES "include")
find_library(BOOST_NUMPY_LIBRARY_RELEASE NAMES boost_numpy HINTS ${_BOOST_NUMPY_SEARCH} PATH_SUFFIXES "lib")
find_library(BOOST_NUMPY_LIBRARY_DEBUG NAMES boost_numpy-gd HINTS ${_BOOST_NUMPY_SEARCH} PATH_SUFFIXES "lib")

if (${BOOST_NUMPY_LIBRARY_DEBUG} STREQUAL "BOOST_NUMPY_LIBRARY_DEBUG-NOTFOUND")
  # Only release version found
  message(STATUS "Warning: Boost::NumPy debug library not found")
  set(BOOST_NUMPY_LIBRARY ${BOOST_NUMPY_LIBRARY_RELEASE})
else()
  # Release and debug
  set(BOOST_NUMPY_LIBRARY optimized ${BOOST_NUMPY_LIBRARY_RELEASE} debug ${BOOST_NUMPY_LIBRARY_DEBUG})
endif()

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(BoostNumPy  DEFAULT_MSG
                                  BOOST_NUMPY_LIBRARY BOOST_NUMPY_INCLUDE_DIR)

mark_as_advanced(BOOST_NUMPY_LIBRARY BOOST_NUMPY_INCLUDE_DIR)