# Archive target setup
# ******************************************************************************
set(GRAPHMIC_LIB_VIEWER GraphMICLibViewer)
list(APPEND GRAPHMIC_INTERNAL_LIBRARY_TARGETS ${GRAPHMIC_LIB_VIEWER})
list(APPEND GRAPHMIC_QML_MODULES viewer)

message(STATUS "> Configure target: " ${GRAPHMIC_LIB_VIEWER})

# target directories
# ******************************************************************************
set(SOURCE_DIR ${PROJECT_SOURCE_DIR}/modules/viewer/src)
set(BINARY_DIR ${PROJECT_BINARY_DIR})

message(STATUS "  Target directories:")
message(STATUS "   - source dir: " ${SOURCE_DIR})
message(STATUS "   - binary dir: " ${BINARY_DIR})

# target sources
# ******************************************************************************
message(STATUS "  ${GRAPHMIC_LIB_VIEWER} sources:")

AddSources("${SOURCE_DIR}/Export" "Export" list_viewer_src)
AddSources("${SOURCE_DIR}/Modules" "Modules" list_viewer_src)
AddSources("${SOURCE_DIR}/Viewer" "Viewer" list_viewer_src)

# target
# ******************************************************************************
add_library(${GRAPHMIC_LIB_VIEWER} SHARED ${list_viewer_src})
add_library(GraphMIC::Viewer ALIAS ${GRAPHMIC_LIB_VIEWER})

# target properties
# ******************************************************************************
set_target_properties(${GRAPHMIC_LIB_VIEWER} PROPERTIES COMPILE_FLAGS -fvisibility=hidden)
target_compile_definitions(${GRAPHMIC_LIB_VIEWER} PUBLIC GRAPHMIC_LIB_VIEWER=1)

# include
# ******************************************************************************
target_include_directories(${GRAPHMIC_LIB_VIEWER} PUBLIC ${BINARY_DIR})

# target dependencies
# ******************************************************************************
target_link_libraries(${GRAPHMIC_LIB_VIEWER}
	PUBLIC GraphMIC::Core
)
