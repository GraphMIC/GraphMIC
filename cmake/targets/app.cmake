# App target setup
# ******************************************************************************
set(GRAPHMIC_APP_NAME ${PROJECT_NAME})
list(APPEND GRAPHMIC_QML_MODULES app)

if(APPLE)
    set(GRAPHMIC_APP_EXECUTABLE ${GRAPHMIC_APP_NAME}.app)
elseif(WIN32)
    set(GRAPHMIC_APP_EXECUTABLE ${GRAPHMIC_APP_NAME}.exe)
else()
  set(GRAPHMIC_APP_EXECUTABLE ${GRAPHMIC_APP_NAME})
endif()

# target directories
# ******************************************************************************
set(SOURCE_DIR ${PROJECT_SOURCE_DIR}/modules/app/src)
set(BINARY_DIR ${PROJECT_BINARY_DIR})

set(GRAPHMIC_APP_BUILD_DIR ${PROJECT_BUILD_DIR})
set(GRAPHMIC_APP_INSTALL_DIR ${PROJECT_INSTALL_DIR})
set(GRAPHMIC_APP_INSTALL_EXECUTABLE ${PROJECT_SOURCE_DIR}/install/GraphMIC.app/Contents/MacOS/GraphMIC)
set(GRAPHMIC_APP_INSTALL_LIBS_DIR ${PROJECT_SOURCE_DIR}/install/GraphMIC.app/Contents/Frameworks)

message(STATUS "  ${GRAPHMIC_APP_NAME} directories:")
message(STATUS "   - source dir: " ${SOURCE_DIR})
message(STATUS "   - binary dir: " ${BINARY_DIR})
message(STATUS "   - build dir: " ${GRAPHMIC_APP_BUILD_DIR})
message(STATUS "   - install dir: " ${GRAPHMIC_APP_INSTALL_DIR})

# application bundle
# ******************************************************************************
if(APPLE)
  set(MACOSX_BUNDLE_BUNDLE_VERSION 1)
  set(MACOSX_BUNDLE_LONG_VERSION_STRING ${GRAPHMIC_VERSION_MAJOR}.${GRAPHMIC_VERSION_MINOR}.${GRAPHMIC_VERSION_PATCH})
  set(MACOSX_BUNDLE_SHORT_VERSION_STRING ${GRAPHMIC_VERSION_MAJOR}.${GRAPHMIC_VERSION_MINOR}.${GRAPHMIC_VERSION_PATCH})
  set(MACOSX_BUNDLE_ICON_FILE ${PROJECT_NAME}.icns)
  set(MACOSX_BUNDLE_BUNDLE_NAME ${GRAPHMIC_APP_NAME})
  set(MACOSX_BUNDLE_RESOURCES ${GRAPHMIC_APP_BUILD_DIR}/${GRAPHMIC_APP_EXECUTABLE}/Contents/Resources)
  set(MACOSX_BUNDLE_ICON ${PROJECT_SOURCE_DIR}/res/icons/develop/${MACOSX_BUNDLE_ICON_FILE})
endif()

# configure files
# ******************************************************************************
message(STATUS "  configure files:")
message(STATUS "    - ${PROJECT_SOURCE_DIR}/cmake/meta_graphmic.hpp.in >> ${PROJECT_BINARY_DIR}/meta_graphmic.hpp")
message(STATUS "    - ${PROJECT_SOURCE_DIR}/cmake/info.plist.in >> ${PROJECT_BINARY_DIR}/info.plist")

configure_file(${PROJECT_SOURCE_DIR}/cmake/meta_graphmic.hpp.in ${PROJECT_BINARY_DIR}/meta_graphmic.hpp)
configure_file(${PROJECT_SOURCE_DIR}/cmake/info.plist.in ${PROJECT_BINARY_DIR}/info.plist)

# target sources
# ******************************************************************************
message(STATUS "  ${GRAPHMIC_APP_NAME} sources:")

AddSources("${SOURCE_DIR}/App" "App" list_app_src)

# target resources
# ******************************************************************************
message(STATUS "  ${GRAPHMIC_APP_NAME} resources:")

AddResources("res/asset" "asset" list_app_res)
AddResources("res/font/font-awesome" "font" list_app_res)
AddResources("res/font/roboto" "font" list_app_res)
AddResources("res/qml/lib" "qml" list_app_res)
AddResources("res/qml/view" "qml" list_app_res)
AddResources("res/qml/modules" "modules" list_app_res)
AddResources("res/config" "config" list_app_res)

# target
# ******************************************************************************
if(APPLE)
  add_executable(${GRAPHMIC_APP_NAME} MACOSX_BUNDLE ${list_app_src} ${MACOSX_BUNDLE_ICON})
elseif(WIN32)
  add_executable(${GRAPHMIC_APP_NAME} WIN32_EXECUTABLE ${list_app_src})
else()
  add_executable(${GRAPHMIC_APP_NAME} ${list_app_src})
endif()

# include directories
# ******************************************************************************
target_include_directories(${GRAPHMIC_APP_NAME} PUBLIC ${BINARY_DIR})
target_include_directories(${GRAPHMIC_APP_NAME} PUBLIC ${SOURCE_DIR})

# post-build: resources
# ******************************************************************************
execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory ${MACOSX_BUNDLE_RESOURCES})
execute_process(COMMAND ${CMAKE_COMMAND} -E copy_if_different ${MACOSX_BUNDLE_ICON} ${MACOSX_BUNDLE_RESOURCES})
add_custom_command(TARGET ${GRAPHMIC_APP_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory "${PROJECT_SOURCE_DIR}/res" ${PROJECT_BUILD_DIR}/${GRAPHMIC_APP_EXECUTABLE}/Contents/Resources)

# post-build: python
# ******************************************************************************
execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory ${MACOSX_BUNDLE_RESOURCES}/lib)
execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory ${MACOSX_BUNDLE_RESOURCES}/lib/python2.7)
add_custom_command(TARGET ${GRAPHMIC_APP_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory "${GRAPHMIC_MITK_EP_LIB_DIRECTORY}/python2.7" ${PROJECT_BUILD_DIR}/${GRAPHMIC_APP_EXECUTABLE}/Contents/Resources/lib/python2.7)

# post-build: modules
# ******************************************************************************
message(STATUS "  copy qml modules:")
foreach(_module ${GRAPHMIC_QML_MODULES})
  message(STATUS "   modules/${_module}/qml")
  add_custom_command(TARGET ${GRAPHMIC_APP_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory "${PROJECT_SOURCE_DIR}/modules/${_module}/qml" ${PROJECT_BUILD_DIR}/${GRAPHMIC_APP_EXECUTABLE}/Contents/Modules/${GRAPHMIC_ORG_DOMAIN}/${GRAPHMIC_ORG_NAME}/${_module})
endforeach()

# target properties
# ******************************************************************************
if(APPLE)
  set_target_properties(${GRAPHMIC_APP_NAME} PROPERTIES MACOSX_BUNDLE_INFO_PLIST ${PROJECT_BINARY_DIR}/info.plist)
endif()

# target dependencies
# ******************************************************************************
target_link_libraries(${GRAPHMIC_APP_NAME}
  PUBLIC GraphMIC::Logic
  PUBLIC GraphMIC::Viewer
    PUBLIC GraphMIC::Preview
    PUBLIC GraphMIC::Python
)

# install
# ******************************************************************************
set(GRAPHMIC_CPP_MICROSERVICE_NAME libCppMicroServices.2.99.0.dylib)
set(GRAPHMIC_CPP_MICROSERVICE_BUILD_PATH ${GRAPHMIC_MITK_LIB_DIRECTORY}/${GRAPHMIC_CPP_MICROSERVICE_NAME})
set(GRAPHMIC_CPP_MICROSERVICE_RPATH @rpath/${GRAPHMIC_CPP_MICROSERVICE_NAME})

message(STATUS "  fix CppMicroservice rpath:")
message(STATUS "   from: " ${GRAPHMIC_CPP_MICROSERVICE_BUILD_PATH})
message(STATUS "   to: " ${GRAPHMIC_CPP_MICROSERVICE_RPATH})

if(APPLE)
  set(GRAPHMIC_INSTALL_EXECUTABLE_DIR ${PROJECT_INSTALL_DIR}/${GRAPHMIC_APP_EXECUTABLE}/Contents/MacOS)
  set(GRAPHMIC_INSTALL_PLUGINS_DIR ${PROJECT_INSTALL_DIR}/${GRAPHMIC_APP_EXECUTABLE}/Contents/Plugins)
  set(GRAPHMIC_INSTALL_LIBS_DIR ${PROJECT_INSTALL_DIR}/${GRAPHMIC_APP_EXECUTABLE}/Contents/Frameworks/)
  set(GRAPHMIC_INSTALL_RESOURCES_DIR ${PROJECT_INSTALL_DIR}/${GRAPHMIC_APP_EXECUTABLE}/Contents/Resources)

  install(TARGETS ${GRAPHMIC_APP_NAME} ${GRAPHMIC_INTERNAL_LIBRARY_TARGETS}
    BUNDLE DESTINATION . COMPONENT Runtime RUNTIME DESTINATION bin COMPONENT Runtime
    LIBRARY DESTINATION ./${GRAPHMIC_APP_EXECUTABLE}/Contents/Frameworks COMPONENT Runtime RUNTIME DESTINATION bin COMPONENT Runtime
  )

  install(FILES ${PROJECT_SOURCE_DIR}/res/icons/release/${MACOSX_BUNDLE_ICON_FILE} DESTINATION "${GRAPHMIC_INSTALL_RESOURCES_DIR}")
  install(FILES ${PROJECT_SOURCE_DIR}/cmake/qt.conf DESTINATION "${GRAPHMIC_INSTALL_RESOURCES_DIR}")
  install(FILES ${BOOST_NUMPY_LIBRARY} DESTINATION "${GRAPHMIC_APP_EXECUTABLE}/Contents/Frameworks")

  install(
    DIRECTORY "${GRAPHMIC_QT_QML_DIRECTORY}/"
    DESTINATION "${GRAPHMIC_INSTALL_EXECUTABLE_DIR}"
    PATTERN "*_debug*" EXCLUDE
  )

  install(
    DIRECTORY "${GRAPHMIC_QT_PLUGINS_DIRECTORY}/"
    DESTINATION "${GRAPHMIC_INSTALL_PLUGINS_DIR}"
    PATTERN "*_debug*" EXCLUDE
  )

  install(
    DIRECTORY "${GRAPHMIC_MITK_LIB_DIRECTORY}/"
    DESTINATION "${GRAPHMIC_APP_EXECUTABLE}/Contents/Frameworks"
    PATTERN "*_debug*" EXCLUDE
  )

  install(
    DIRECTORY "${GRAPHMIC_BOOSTNUMPY_LIB_DIRECTORY}/"
    DESTINATION "${GRAPHMIC_APP_EXECUTABLE}/Contents/Frameworks"
    PATTERN "*_debug*" EXCLUDE
  )

  install(
    DIRECTORY "${GRAPHMIC_MITK_EP_LIB_DIRECTORY}/"
    DESTINATION "${GRAPHMIC_APP_EXECUTABLE}/Contents/Frameworks"
    PATTERN "*_debug*" EXCLUDE
    PATTERN "cmake*" EXCLUDE
    PATTERN "pkgconfig" EXCLUDE
    PATTERN "python2.7" EXCLUDE
  )

  foreach(_module ${GRAPHMIC_QT_MODUlES})
    install(
      DIRECTORY "${GRAPHMIC_QT_LIB_DIRECTORY}/Qt${_module}.framework/"
      DESTINATION "${GRAPHMIC_APP_EXECUTABLE}/Contents/Frameworks/Qt${_module}.framework"
      PATTERN "*_debug*" EXCLUDE
    )
  endforeach()

  install(CODE "
    execute_process(COMMAND \"${CMAKE_INSTALL_NAME_TOOL}\" -id \"${GRAPHMIC_CPP_MICROSERVICE_RPATH}\" ${GRAPHMIC_APP_INSTALL_LIBS_DIR}/${GRAPHMIC_CPP_MICROSERVICE_NAME})
    execute_process(COMMAND \"${CMAKE_INSTALL_NAME_TOOL}\" -change ${GRAPHMIC_CPP_MICROSERVICE_BUILD_PATH} \"${GRAPHMIC_CPP_MICROSERVICE_RPATH}\" ${GRAPHMIC_APP_INSTALL_EXECUTABLE})
    execute_process(COMMAND \"${CMAKE_INSTALL_NAME_TOOL}\" -change ${GRAPHMIC_CPP_MICROSERVICE_BUILD_PATH} \"${GRAPHMIC_CPP_MICROSERVICE_RPATH}\" ${GRAPHMIC_APP_INSTALL_LIBS_DIR}/libMitkPlanarFigure.dylib)
    execute_process(COMMAND \"${CMAKE_INSTALL_NAME_TOOL}\" -change ${GRAPHMIC_CPP_MICROSERVICE_BUILD_PATH} \"${GRAPHMIC_CPP_MICROSERVICE_RPATH}\" ${GRAPHMIC_APP_INSTALL_LIBS_DIR}/libMitkSceneSerializationBase.dylib)
    execute_process(COMMAND \"${CMAKE_INSTALL_NAME_TOOL}\" -change ${GRAPHMIC_CPP_MICROSERVICE_BUILD_PATH} \"${GRAPHMIC_CPP_MICROSERVICE_RPATH}\" ${GRAPHMIC_APP_INSTALL_LIBS_DIR}/libMitkCore.dylib)
    execute_process(COMMAND \"${CMAKE_INSTALL_NAME_TOOL}\" -change ${GRAPHMIC_CPP_MICROSERVICE_BUILD_PATH} \"${GRAPHMIC_CPP_MICROSERVICE_RPATH}\" ${GRAPHMIC_APP_INSTALL_LIBS_DIR}/libMitkLegacyGL.dylib)
    execute_process(COMMAND \"${CMAKE_INSTALL_NAME_TOOL}\" -change ${GRAPHMIC_CPP_MICROSERVICE_BUILD_PATH} \"${GRAPHMIC_CPP_MICROSERVICE_RPATH}\" ${GRAPHMIC_APP_INSTALL_LIBS_DIR}/libMitkOverlays.dylib)
    execute_process(COMMAND \"${CMAKE_INSTALL_NAME_TOOL}\" -change ${GRAPHMIC_CPP_MICROSERVICE_BUILD_PATH} \"${GRAPHMIC_CPP_MICROSERVICE_RPATH}\" ${GRAPHMIC_APP_INSTALL_LIBS_DIR}/libMitkRigidRegistration.dylib)
    execute_process(COMMAND \"${CMAKE_INSTALL_NAME_TOOL}\" -change ${GRAPHMIC_CPP_MICROSERVICE_BUILD_PATH} \"${GRAPHMIC_CPP_MICROSERVICE_RPATH}\" ${GRAPHMIC_APP_INSTALL_LIBS_DIR}/libMitkAlgorithmsExt.dylib)
    execute_process(COMMAND \"${CMAKE_INSTALL_NAME_TOOL}\" -change ${GRAPHMIC_CPP_MICROSERVICE_BUILD_PATH} \"${GRAPHMIC_CPP_MICROSERVICE_RPATH}\" ${GRAPHMIC_APP_INSTALL_LIBS_DIR}/libMitkDataTypesExt.dylib)
    execute_process(COMMAND \"${CMAKE_INSTALL_NAME_TOOL}\" -change ${GRAPHMIC_CPP_MICROSERVICE_BUILD_PATH} \"${GRAPHMIC_CPP_MICROSERVICE_RPATH}\" ${GRAPHMIC_APP_INSTALL_LIBS_DIR}/libMitkMapperExt.dylib)
    execute_process(COMMAND \"${CMAKE_INSTALL_NAME_TOOL}\" -change ${GRAPHMIC_CPP_MICROSERVICE_BUILD_PATH} \"${GRAPHMIC_CPP_MICROSERVICE_RPATH}\" ${GRAPHMIC_APP_INSTALL_LIBS_DIR}/libMitkContourModel.dylib)
    execute_process(COMMAND \"${CMAKE_INSTALL_NAME_TOOL}\" -change ${GRAPHMIC_CPP_MICROSERVICE_BUILD_PATH} \"${GRAPHMIC_CPP_MICROSERVICE_RPATH}\" ${GRAPHMIC_APP_INSTALL_LIBS_DIR}/libMitkSegmentation.dylib)
    execute_process(COMMAND \"${CMAKE_INSTALL_NAME_TOOL}\" -change ${GRAPHMIC_CPP_MICROSERVICE_BUILD_PATH} \"${GRAPHMIC_CPP_MICROSERVICE_RPATH}\" ${GRAPHMIC_APP_INSTALL_LIBS_DIR}/libMitkLegacyAdaptors.dylib)
    execute_process(COMMAND \"${CMAKE_INSTALL_NAME_TOOL}\" -change ${GRAPHMIC_CPP_MICROSERVICE_BUILD_PATH} \"${GRAPHMIC_CPP_MICROSERVICE_RPATH}\" ${GRAPHMIC_APP_INSTALL_LIBS_DIR}/libMitkSurfaceInterpolation.dylib)
    execute_process(COMMAND \"${CMAKE_INSTALL_NAME_TOOL}\" -change ${GRAPHMIC_CPP_MICROSERVICE_BUILD_PATH} \"${GRAPHMIC_CPP_MICROSERVICE_RPATH}\" ${GRAPHMIC_APP_INSTALL_LIBS_DIR}/libMitkImageStatistics.dylib)
    execute_process(COMMAND \"${CMAKE_INSTALL_NAME_TOOL}\" -change ${GRAPHMIC_CPP_MICROSERVICE_BUILD_PATH} \"${GRAPHMIC_CPP_MICROSERVICE_RPATH}\" ${GRAPHMIC_APP_INSTALL_LIBS_DIR}/libMitkImageExtraction.dylib)
    execute_process(COMMAND \"${CMAKE_INSTALL_NAME_TOOL}\" -change ${GRAPHMIC_CPP_MICROSERVICE_BUILD_PATH} \"${GRAPHMIC_CPP_MICROSERVICE_RPATH}\" ${GRAPHMIC_APP_INSTALL_LIBS_DIR}/libMitkMultilabel.dylib)
    execute_process(COMMAND \"${CMAKE_INSTALL_NAME_TOOL}\" -change ${GRAPHMIC_CPP_MICROSERVICE_BUILD_PATH} \"${GRAPHMIC_CPP_MICROSERVICE_RPATH}\" ${GRAPHMIC_APP_INSTALL_LIBS_DIR}/libMitkGraphAlgorithms.dylib)
    execute_process(COMMAND \"${CMAKE_INSTALL_NAME_TOOL}\" -change ${GRAPHMIC_CPP_MICROSERVICE_BUILD_PATH} \"${GRAPHMIC_CPP_MICROSERVICE_RPATH}\" ${GRAPHMIC_APP_INSTALL_LIBS_DIR}/libMitkOpenCVVideoSupport.dylib)
    execute_process(COMMAND \"${CMAKE_INSTALL_NAME_TOOL}\" -change ${GRAPHMIC_CPP_MICROSERVICE_BUILD_PATH} \"${GRAPHMIC_CPP_MICROSERVICE_RPATH}\" ${GRAPHMIC_APP_INSTALL_LIBS_DIR}/MitkCore/libMitkIGTIO.dylib)
    execute_process(COMMAND \"${CMAKE_INSTALL_NAME_TOOL}\" -change ${GRAPHMIC_CPP_MICROSERVICE_BUILD_PATH} \"${GRAPHMIC_CPP_MICROSERVICE_RPATH}\" ${GRAPHMIC_APP_INSTALL_LIBS_DIR}/MitkCore/libMitkIpPicSupportIO.dylib)
    execute_process(COMMAND \"${CMAKE_INSTALL_NAME_TOOL}\" -change ${GRAPHMIC_CPP_MICROSERVICE_BUILD_PATH} \"${GRAPHMIC_CPP_MICROSERVICE_RPATH}\" ${GRAPHMIC_APP_INSTALL_LIBS_DIR}/MitkCore/libMitkVtkShaders.dylib)
    execute_process(COMMAND \"${CMAKE_INSTALL_NAME_TOOL}\" -change ${GRAPHMIC_CPP_MICROSERVICE_BUILD_PATH} \"${GRAPHMIC_CPP_MICROSERVICE_RPATH}\" ${GRAPHMIC_APP_INSTALL_LIBS_DIR}/MitkCore/libMitkIOExt.dylib)
    execute_process(COMMAND \"${CMAKE_INSTALL_NAME_TOOL}\" -change ${GRAPHMIC_CPP_MICROSERVICE_BUILD_PATH} \"${GRAPHMIC_CPP_MICROSERVICE_RPATH}\" ${GRAPHMIC_APP_INSTALL_LIBS_DIR}/MitkCore/libMitkMultilabelIO.dylib)
    "
    COMPONENT Runtime
  )

  foreach(_lib ${GRAPHMIC_INTERNAL_LIBRARY_TARGETS})
    install(CODE "
      execute_process(COMMAND \"${CMAKE_INSTALL_NAME_TOOL}\" -change ${GRAPHMIC_CPP_MICROSERVICE_BUILD_PATH} \"${GRAPHMIC_CPP_MICROSERVICE_RPATH}\" ${GRAPHMIC_APP_INSTALL_LIBS_DIR}/lib${_lib}.dylib)
    ")
  endforeach()

endif()
