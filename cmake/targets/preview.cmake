# Archive target setup
# ******************************************************************************
set(GRAPHMIC_LIB_PREVIEW GraphMICLibPreview)
list(APPEND GRAPHMIC_INTERNAL_LIBRARY_TARGETS ${GRAPHMIC_LIB_PREVIEW})
list(APPEND GRAPHMIC_QML_MODULES preview)

message(STATUS "> Configure target: " ${GRAPHMIC_LIB_PREVIEW})

# target directories
# ******************************************************************************
set(SOURCE_DIR ${PROJECT_SOURCE_DIR}/modules/preview/src)
set(BINARY_DIR ${PROJECT_BINARY_DIR})

message(STATUS "  Target directories:")
message(STATUS "   - source dir: " ${SOURCE_DIR})
message(STATUS "   - binary dir: " ${BINARY_DIR})

# target sources
# ******************************************************************************
message(STATUS "  ${GRAPHMIC_LIB_PREVIEW} sources:")

AddSources("${SOURCE_DIR}/Export" "Export" list_preview_src)
AddSources("${SOURCE_DIR}/Modules" "Modules" list_preview_src)
AddSources("${SOURCE_DIR}/Preview" "Preview" list_preview_src)

# target
# ******************************************************************************
add_library(${GRAPHMIC_LIB_PREVIEW} SHARED ${list_preview_src})
add_library(GraphMIC::Preview ALIAS ${GRAPHMIC_LIB_PREVIEW})

# target properties
# ******************************************************************************
set_target_properties(${GRAPHMIC_LIB_PREVIEW} PROPERTIES COMPILE_FLAGS -fvisibility=hidden)
target_compile_definitions(${GRAPHMIC_LIB_PREVIEW} PUBLIC GRAPHMIC_LIB_PREVIEW=1)

# include
# ******************************************************************************
target_include_directories(${GRAPHMIC_LIB_PREVIEW} PUBLIC ${BINARY_DIR})

# target dependencies
# ******************************************************************************
target_link_libraries(${GRAPHMIC_LIB_PREVIEW}
	PUBLIC GraphMIC::Core
)
