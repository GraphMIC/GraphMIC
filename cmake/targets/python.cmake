# Archive target setup
# ******************************************************************************
set(GRAPHMIC_LIB_PYTHON GraphMICLibPython)
list(APPEND GRAPHMIC_INTERNAL_LIBRARY_TARGETS ${GRAPHMIC_LIB_PYTHON})
list(APPEND GRAPHMIC_QML_MODULES python)

message(STATUS "> Configure target: " ${GRAPHMIC_LIB_PYTHON})

# target directories
# ******************************************************************************
set(SOURCE_DIR ${PROJECT_SOURCE_DIR}/modules/python/src)
set(BINARY_DIR ${PROJECT_BINARY_DIR})

message(STATUS "  Target directories:")
message(STATUS "   - source dir: " ${SOURCE_DIR})
message(STATUS "   - binary dir: " ${BINARY_DIR})

# target sources
# ******************************************************************************
message(STATUS "  ${GRAPHMIC_LIB_PYTHON} sources:")

AddSources("${SOURCE_DIR}/Export" "Export" list_python_src)
AddSources("${SOURCE_DIR}/Modules" "Modules" list_python_src)
AddSources("${SOURCE_DIR}/Python" "Python" list_python_src)
AddSources("${SOURCE_DIR}/Python/Node" "Python\\Node" list_python_src)
AddSources("${SOURCE_DIR}/Python/Object" "Python\\Object" list_python_src)

# target
# ******************************************************************************
add_library(${GRAPHMIC_LIB_PYTHON} SHARED ${list_python_src})
add_library(GraphMIC::Python ALIAS ${GRAPHMIC_LIB_PYTHON})

# target properties
# ******************************************************************************
set_target_properties(${GRAPHMIC_LIB_PYTHON} PROPERTIES COMPILE_FLAGS -fvisibility=hidden)
target_compile_definitions(${GRAPHMIC_LIB_PYTHON} PUBLIC GRAPHMIC_LIB_PYTHON=1)

# include
# ******************************************************************************
target_include_directories(${GRAPHMIC_LIB_PYTHON} PUBLIC ${BINARY_DIR})
target_include_directories(${GRAPHMIC_LIB_PYTHON} PUBLIC ${BOOST_NUMPY_INCLUDE_DIR})
target_include_directories(${GRAPHMIC_LIB_PYTHON} PUBLIC ${Boost_INCLUDE_DIR})
target_include_directories(${GRAPHMIC_LIB_PYTHON} PUBLIC ${PYTHON_INCLUDE_DIR})

# target dependencies
# ******************************************************************************
target_link_libraries(${GRAPHMIC_LIB_PYTHON}
  PUBLIC GraphMIC::Core
  ${BOOST_NUMPY_LIBRARY}
  ${PYTHON_LIBRARY}
  ${Boost_PYTHON_LIBRARY_DEBUG}
)
