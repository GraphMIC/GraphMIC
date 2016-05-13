# Archive target setup
# ******************************************************************************
set(GRAPHMIC_LIB_CORE GraphMICLibCore)
list(APPEND GRAPHMIC_INTERNAL_LIBRARY_TARGETS ${GRAPHMIC_LIB_CORE})
list(APPEND GRAPHMIC_QML_MODULES core)

message(STATUS "> Configure target: " ${GRAPHMIC_LIB_CORE})

# target directories
# ******************************************************************************
set(SOURCE_DIR ${PROJECT_SOURCE_DIR}/modules/core/src)
set(BINARY_DIR ${PROJECT_BINARY_DIR})

message(STATUS "  Target directories:")
message(STATUS "   - source dir: " ${SOURCE_DIR})
message(STATUS "   - binary dir: " ${BINARY_DIR})

# target sources
# ******************************************************************************
message(STATUS "  ${GRAPHMIC_LIB_CORE} sources:")

AddSources("${SOURCE_DIR}/Export" "Export" list_core_src)
AddSources("${SOURCE_DIR}/Dialog" "Dialog" list_core_src)
AddSources("${SOURCE_DIR}/Notification" "Notification" list_core_src)
AddSources("${SOURCE_DIR}/Interface" "Interface" list_core_src)
AddSources("${SOURCE_DIR}/Modules" "Modules" list_core_src)
AddSources("${SOURCE_DIR}/Data" "Data" list_core_src)
AddSources("${SOURCE_DIR}/Image" "Image" list_core_src)
AddSources("${SOURCE_DIR}/Node" "Node" list_core_src)
AddSources("${SOURCE_DIR}/Slot" "Slot" list_core_src)
AddSources("${SOURCE_DIR}/Component" "Component" list_core_src)
AddSources("${SOURCE_DIR}/Connection" "Connection" list_core_src)
AddSources("${SOURCE_DIR}/Param" "Param" list_core_src)
AddSources("${SOURCE_DIR}/Logic" "Logic" list_core_src)
AddSources("${SOURCE_DIR}/IO" "IO" list_core_src)
AddSources("${SOURCE_DIR}/Util" "Util" list_core_src)
AddSources("${SOURCE_DIR}/Debug" "Debug" list_core_src)
AddSources("${SOURCE_DIR}/App" "App" list_core_src)

# target
# ******************************************************************************
add_library(${GRAPHMIC_LIB_CORE} SHARED ${list_core_src})
add_library(GraphMIC::Core ALIAS ${GRAPHMIC_LIB_CORE})

# target properties
# ******************************************************************************
set_target_properties(${GRAPHMIC_LIB_CORE} PROPERTIES COMPILE_FLAGS -fvisibility=hidden)
target_compile_definitions(${GRAPHMIC_LIB_CORE} PUBLIC GRAPHMIC_LIB_CORE=1)

# include
# ******************************************************************************
target_include_directories(${GRAPHMIC_LIB_CORE} PUBLIC ${BINARY_DIR})

# target dependencies
# ******************************************************************************
target_link_libraries(${GRAPHMIC_LIB_CORE}
  PUBLIC Qt5::Core
  PUBLIC Qt5::DBus
  PUBLIC Qt5::Network
  PUBLIC Qt5::PrintSupport
  PUBLIC Qt5::Widgets
  PUBLIC Qt5::Gui
  PUBLIC Qt5::Quick
  PUBLIC Qt5::Qml
  PUBLIC Qt5::Concurrent
)

if(${GRAPHMIC_BUILD_CV_NODES})
  mitk_use_modules(TARGET ${GRAPHMIC_LIB_CORE} MODULES
    MitkCore
    MitkPlanarFigure
    MitkRigidRegistration
    MitkAlgorithmsExt
    MitkMapperExt
    MitkSegmentation
    MitkImageStatistics
    MitkOpenCVVideoSupport
    ITKLabelMap
  )
else()
  mitk_use_modules(TARGET ${GRAPHMIC_LIB_CORE} MODULES
    MitkCore
    MitkPlanarFigure
    MitkRigidRegistration
    MitkAlgorithmsExt
    MitkMapperExt
    MitkSegmentation
    MitkImageStatistics
    #TODO wihout OpenCV dependency
    MitkOpenCVVideoSupport
    ITKLabelMap
  )
endif()
