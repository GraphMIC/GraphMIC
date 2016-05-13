# Test target setup
# ******************************************************************************
set(GRAPHMIC_TEST_NAME ${PROJECT_NAME}Test)
list(APPEND GRAPHMIC_QML_MODULES test)

if(APPLE)
  	set(GRAPHMIC_TEST_EXECUTABLE ${GRAPHMIC_TEST_NAME}.app)
elseif(WIN32)
  	set(GRAPHMIC_TEST_EXECUTABLE ${GRAPHMIC_TEST_NAME}.exe)
else()
	set(GRAPHMIC_TEST_EXECUTABLE ${GRAPHMIC_TEST_NAME})
endif()

# target directories
# ******************************************************************************
set(SOURCE_DIR ${PROJECT_SOURCE_DIR}/modules/test/src)
set(BINARY_DIR ${PROJECT_BINARY_DIR})

set(GRAPHMIC_TEST_BUILD_DIR ${PROJECT_BUILD_DIR})
set(GRAPHMIC_TEST_INSTALL_DIR ${PROJECT_INSTALL_DIR})

message(STATUS "  ${GRAPHMIC_TEST_NAME} directories:")
message(STATUS "   - source dir: " ${SOURCE_DIR})
message(STATUS "   - binary dir: " ${BINARY_DIR})
message(STATUS "   - build dir: " ${GRAPHMIC_TEST_BUILD_DIR})
message(STATUS "   - install dir: " ${GRAPHMIC_TEST_INSTALL_DIR})

# test application bundle
# ******************************************************************************
if(APPLE)
	set(MACOSX_BUNDLE_BUNDLE_VERSION 1)
	set(MACOSX_BUNDLE_LONG_VERSION_STRING ${GRAPHMIC_VERSION_MAJOR}.${GRAPHMIC_VERSION_MINOR}.${GRAPHMIC_VERSION_PATCH})
	set(MACOSX_BUNDLE_SHORT_VERSION_STRING ${GRAPHMIC_VERSION_MAJOR}.${GRAPHMIC_VERSION_MINOR}.${GRAPHMIC_VERSION_PATCH})
	set(MACOSX_BUNDLE_ICON_FILE ${PROJECT_NAME}.icns)
	set(MACOSX_BUNDLE_BUNDLE_NAME ${GRAPHMIC_TEST_NAME})
	set(MACOSX_BUNDLE_RESOURCES ${GRAPHMIC_TEST_BUILD_DIR}/${GRAPHMIC_TEST_EXECUTABLE}/Contents/Resources)
	set(MACOSX_BUNDLE_ICON ${PROJECT_SOURCE_DIR}/res/icons/testing/${MACOSX_BUNDLE_ICON_FILE})
endif()

# configure files
# ******************************************************************************
message(STATUS "  configure files:")
message(STATUS "    - ${PROJECT_SOURCE_DIR}/cmake/info_test.plist.in >> ${PROJECT_BINARY_DIR}/info_test.plist")

configure_file(${PROJECT_SOURCE_DIR}/cmake/info_test.plist.in ${PROJECT_BINARY_DIR}/info_test.plist)

# target sources
# ******************************************************************************
message(STATUS "  ${GRAPHMIC_TEST_NAME} sources:")

AddSources("${SOURCE_DIR}/App" "App" list_test_src)
AddSources("${SOURCE_DIR}/Test" "Test" list_test_src)
AddSources("${SOURCE_DIR}/Test/Logic" "Test\\Logic" list_test_src)
AddSources("${SOURCE_DIR}/Modules" "Modules" list_test_src)

# target resources
# ******************************************************************************
message(STATUS "  ${GRAPHMIC_TEST_NAME} resources:")

AddResources("res/asset" "asset" list_test_res)
AddResources("res/font/font-awesome" "font" list_test_res)
AddResources("res/font/roboto" "font" list_test_res)
AddResources("res/qml/lib" "qml" list_test_res)
AddResources("res/qml/view" "qml" list_test_res)
AddResources("res/qml/modules" "modules" list_test_res)
AddResources("res/config" "config" list_test_res)

# target
# ************************************************	******************************
if(APPLE)
	add_executable(${GRAPHMIC_TEST_NAME} MACOSX_BUNDLE ${list_test_src} ${MACOSX_BUNDLE_ICON})
elseif(WIN32)
	add_executable(${GRAPHMIC_TEST_NAME} WIN32_EXECUTABLE ${list_test_src})
else()
	add_executable(${GRAPHMIC_TEST_NAME} ${list_test_src})
endif()

target_include_directories(${GRAPHMIC_TEST_NAME} PUBLIC ${BINARY_DIR})

# post-build: resources
# ******************************************************************************
execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory ${MACOSX_BUNDLE_RESOURCES})
execute_process(COMMAND ${CMAKE_COMMAND} -E copy_if_different ${MACOSX_BUNDLE_ICON} ${MACOSX_BUNDLE_RESOURCES})
add_custom_command(TARGET ${GRAPHMIC_TEST_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory "${PROJECT_SOURCE_DIR}/res" ${PROJECT_BUILD_DIR}/${GRAPHMIC_TEST_EXECUTABLE}/Contents/Resources)

# post-build: modules
# ******************************************************************************
message(STATUS "  copy qml modules:")
foreach(_module ${GRAPHMIC_QML_MODULES})
	message(STATUS "   modules/${_module}/qml")
	add_custom_command(TARGET ${GRAPHMIC_TEST_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory "${PROJECT_SOURCE_DIR}/modules/${_module}/qml" ${PROJECT_BUILD_DIR}/${GRAPHMIC_TEST_EXECUTABLE}/Contents/Modules/${GRAPHMIC_ORG_DOMAIN}/${GRAPHMIC_ORG_NAME}/${_module})
endforeach()

# target properties
# ******************************************************************************
if(APPLE)
	set_target_properties(${GRAPHMIC_TEST_NAME} PROPERTIES MACOSX_BUNDLE_INFO_PLIST ${BINARY_DIR}/info_test.plist)
endif()

# target dependencies
# ******************************************************************************
target_link_libraries(${GRAPHMIC_TEST_NAME}
	PUBLIC GraphMIC::Logic
	PUBLIC GraphMIC::Viewer
    PUBLIC GraphMIC::Preview
    PUBLIC GraphMIC::Python
)
