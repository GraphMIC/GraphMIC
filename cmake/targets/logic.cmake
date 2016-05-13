# Archive target setup
# ******************************************************************************
set(GRAPHMIC_LIB_LOGIC GraphMICLibLogic)
list(APPEND GRAPHMIC_INTERNAL_LIBRARY_TARGETS ${GRAPHMIC_LIB_LOGIC})
list(APPEND GRAPHMIC_QML_MODULES logic)

message(STATUS "> Configure target: " ${GRAPHMIC_LIB_LOGIC})

# target directories
# ******************************************************************************
set(SOURCE_DIR ${PROJECT_SOURCE_DIR}/modules/logic/src)
set(BINARY_DIR ${PROJECT_BINARY_DIR})

message(STATUS "  Target directories:")
message(STATUS "   - source dir: " ${SOURCE_DIR})
message(STATUS "   - binary dir: " ${BINARY_DIR})

# configure files
# ******************************************************************************
message(STATUS "  configure files:")
message(STATUS "    - ${PROJECT_SOURCE_DIR}/cmake/meta_mitk.hpp.in >> ${PROJECT_BINARY_DIR}/meta_mitk.hpp")
message(STATUS "    - ${PROJECT_SOURCE_DIR}/cmake/meta_itk.hpp.in >> ${PROJECT_BINARY_DIR}/meta_itk.hpp")
message(STATUS "    - ${PROJECT_SOURCE_DIR}/cmake/meta_cv.hpp.in >> ${PROJECT_BINARY_DIR}/meta_cv.hpp")

configure_file(${PROJECT_SOURCE_DIR}/cmake/meta_mitk.hpp.in ${PROJECT_BINARY_DIR}/meta_mitk.hpp)

if(GRAPHMIC_BUILD_ITK_NODES)
	configure_file(${PROJECT_SOURCE_DIR}/cmake/meta_itk.hpp.in ${PROJECT_BINARY_DIR}/meta_itk.hpp)
endif()

if(GRAPHMIC_BUILD_CV_NODES)
	configure_file(${PROJECT_SOURCE_DIR}/cmake/meta_cv.hpp.in ${PROJECT_BINARY_DIR}/meta_cv.hpp)
endif()

# target sources
# ******************************************************************************
message(STATUS "  ${GRAPHMIC_LIB_LOGIC} sources:")

AddSources("${SOURCE_DIR}/Logic" "Logic" list_logic_src)
AddSources("${SOURCE_DIR}/Export" "Export" list_logic_src)
AddSources("${SOURCE_DIR}/Modules" "Modules" list_logic_src)
AddSources("${SOURCE_DIR}/Logic/Generic" "Generic" list_logic_src)

if(GRAPHMIC_BUILD_MATH_NODES)
	AddSources("${SOURCE_DIR}/Logic/Math" "Math" list_logic_src)
endif()
if(GRAPHMIC_BUILD_ITK_NODES)
	AddSources("${SOURCE_DIR}/Logic/Itk" "Itk" list_logic_src)
	AddSources("${SOURCE_DIR}/Logic/Itk/Registration" "Itk\\Registration" list_logic_src)
	AddSources("${SOURCE_DIR}/Logic/Itk/ImageToImageFilter" "Itk\\ImageToImageFilter" list_logic_src)
	AddSources("${SOURCE_DIR}/Logic/Itk/ImageToImageFilter/UnaryFunctorImageFilter" "Itk\\ImageToImageFilter\\UnaryFunctorImageFilter" list_logic_src)
	AddSources("${SOURCE_DIR}/Logic/Itk/ImageToImageFilter/BinaryFunctorImageFilter" "Itk\\ImageToImageFilter\\BinaryFunctorImageFilter" list_logic_src)
	AddSources("${SOURCE_DIR}/Logic/Itk/ImageToImageFilter/TernaryFunctorImageFilter" "Itk\\ImageToImageFilter\\TernaryFunctorImageFilter" list_logic_src)
	AddSources("${SOURCE_DIR}/Logic/Itk/ImageToImageFilter/NaryFunctorImageFilter" "Itk\\ImageToImageFilter\\NaryFunctorImageFilter" list_logic_src)
endif()
if(GRAPHMIC_BUILD_CV_NODES)
	AddSources("${SOURCE_DIR}/Logic/Cv" "Cv" list_logic_src)
	AddSources("${SOURCE_DIR}/Logic/Cv/Core" "Cv\\Core" list_logic_src)
	AddSources("${SOURCE_DIR}/Logic/Cv/ImgProc" "Cv\\ImgProc" list_logic_src)
	AddSources("${SOURCE_DIR}/Logic/Cv/FeatureDetect" "Cv\\FeatureDetect" list_logic_src)
endif()

# target
# ******************************************************************************
add_library(${GRAPHMIC_LIB_LOGIC} SHARED ${list_logic_src})
add_library(GraphMIC::Logic ALIAS ${GRAPHMIC_LIB_LOGIC})

# target properties
# ******************************************************************************
set_target_properties(${GRAPHMIC_LIB_LOGIC} PROPERTIES COMPILE_FLAGS -fvisibility=hidden)
set_target_properties(${GRAPHMIC_LIB_LOGIC} PROPERTIES PROJECT_LABEL Logic)
target_compile_definitions(${GRAPHMIC_LIB_LOGIC} PUBLIC GRAPHMIC_LIB_LOGIC=1)

# include
# ******************************************************************************
target_include_directories(${GRAPHMIC_LIB_LOGIC} PUBLIC ${BINARY_DIR})

# target dependencies
# ******************************************************************************
target_link_libraries(${GRAPHMIC_LIB_LOGIC}
	PUBLIC GraphMIC::Core
)
