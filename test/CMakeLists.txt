# boost
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DBOOST_TEST_DYN_LINK")
find_package( Boost 1.54.0 REQUIRED COMPONENTS unit_test_framework )
if(Boost_FOUND)

 set(LIB_PATH "${CMAKE_CURRENT_BINARY_DIR}/src")
 file(GLOB SOURCES *.cpp)
 link_directories(${LIB_PATH} ${Boost_LIBRARY_DIRS})
 include_directories(${Boost_INCLUDE_DIRS})
 add_executable(${TEST_NAME} ${SOURCES})
 add_dependencies(${TEST_NAME} ${LIB_STATIC_NAME})
 target_link_libraries(${TEST_NAME} ${LIB_STATIC_NAME} ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
 add_test(UnitTest ${TEST_NAME})

  ### Only if this the principal project ###
  if("${LOCAL_CMAKE_PROJECT_NAME}" STREQUAL "${CMAKE_PROJECT_NAME}")
    install(TARGETS ${TEST_NAME} RUNTIME DESTINATION ${TEST_INSTALL_DIR})
  endif()

else()
  message(STATUS "Missing required Boost UNIT TEST framework library. Test building skipped")
endif(Boost_FOUND)
