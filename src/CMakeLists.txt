file(GLOB SOURCES *.cpp ${CMAKE_CURRENT_SOURCE_DIR}/fcgicc-0.1.3/src/*.cc ${FASTCGI_INCLUDE})
file(GLOB EXTRA_SOURCES ../include/*.h) # making happy Qt-Creator project tab
include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/fcgicc-0.1.3/src ${CMAKE_CURRENT_SOURCE_DIR}/fcgicc-0.1.3/fastcgi_devkit ${FASTCGI_INCLUDE})
link_directories(${FASTCGI_LINK})
get_property(LINK_DIRS DIRECTORY PROPERTY LINK_DIRECTORIES)
message(STATUS "${LOCAL_CMAKE_PROJECT_NAME} link directories: ${LINK_DIRS}")
add_library(${LIB_STATIC_NAME} STATIC ${SOURCES} ${EXTRA_SOURCES})
target_link_libraries(${LIB_STATIC_NAME} ${FASTCGI_NAME} ${FASTCGI_NAME}++)

### Only if this the principal project ###
if("${LOCAL_CMAKE_PROJECT_NAME}" STREQUAL "${CMAKE_PROJECT_NAME}")

  ### Install binaries ###
  install(TARGETS ${LIB_STATIC_NAME} ARCHIVE DESTINATION ${LIB_INSTALL_DIR})

  ### Install headers ###
  file(GLOB HEADERS ../include/*.h)
  install(FILES ${HEADERS} DESTINATION ${HEADERS_INSTALL_DIR})

endif()

