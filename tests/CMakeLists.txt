macro(cute_suite SUITE)
  set(TEST_TARGET "te_test_${SUITE}")
  add_executable("${TEST_TARGET}" te_test_driver.cpp)
  target_link_libraries("${TEST_TARGET}" stdc++fs)
  add_test(NAME "${SUITE}" COMMAND "${TEST_TARGET}")
  list(APPEND TE_TEST_TARGETS "${TEST_TARGET}")
  set_target_properties(${TEST_TARGET}
    PROPERTIES COMPILE_FLAGS "-include ${CMAKE_CURRENT_SOURCE_DIR}/suites/${SUITE}.h"
  )
endmacro()

cute_suite("simple_variable_replacement")
cute_suite("invalid_template_syntax")

message(STATUS "Registered Suites: ${TE_TEST_TARGETS}")

add_custom_target("run_te_test"
  ALL
  DEPENDS ${TE_TEST_TARGETS}
  COMMAND ${CMAKE_COMMAND} "--build" "${CMAKE_BINARY_DIR}" "--target" "test"
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  COMMENT "Executing 'te' unit tests"
  )
