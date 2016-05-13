function(AddSources rel_path group_name list_src)
  message(STATUS "   > ${rel_path} >> ${group_name}")
   #target_include_directories(${target} PUBLIC ${rel_path})
   include_directories(${rel_path})
  file(GLOB list_globbed "${rel_path}/*.h" "${rel_path}/*.cpp" "${rel_path}/*.cxx" "${rel_path}/*.hpp")
  foreach(file ${list_globbed})
    message(STATUS "     - ${file}")
  endforeach()
  set(list_return ${list_globbed} ${${list_src}})
  set(${list_src} ${list_return} PARENT_SCOPE)
  source_group(${group_name} FILES ${list_globbed})
endfunction()

function(AddResources rel_path group_name list_res)
  message(STATUS "   > ${rel_path} >> ${group_name}")
  # include_directories(${PROJECT_ROOT_DIR}/res/${rel_path})
  file(GLOB list_globbed "${rel_path}/*.qml" "${rel_path}/*.png" "${rel_path}/*.ttf" "${rel_path}/*.js" "${rel_path}/*.json" "${rel_path}/*.cfg")
  foreach(file ${list_globbed})
    message(STATUS "     - ${file}")
  endforeach()
  source_group(${group_name} FILES ${list_globbed})
  set(list_return ${list_globbed} ${${list_res}})
  set(${list_res} ${list_return} PARENT_SCOPE)
endfunction()

macro(MacroEmptyExternalProject proj dependencies)

  ExternalProject_Add(${proj}
    DOWNLOAD_COMMAND ""
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
    DEPENDS
      ${dependencies}
    )

endmacro()

