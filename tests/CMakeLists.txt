add_executable("te_tests" "te_tests.cpp")
target_link_libraries("te_tests" "stdc++fs")
add_test(NAME "te_tests" COMMAND "te_tests")

add_custom_target("run_te_test"
  ALL
  DEPENDS "te_tests"
  COMMAND ${CMAKE_COMMAND} "--build" "${CMAKE_BINARY_DIR}" "--target" "test"
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  COMMENT "Executing 'te' unit tests"
  )
