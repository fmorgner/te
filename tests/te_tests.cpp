#include "suites/simple_variable_replacement_suite.h"

#include "cute/cute.h"
#include "cute/cute_runner.h"
#include "cute/tap_listener.h"

int main(int argc, char const * const * argv)
  {
  auto listener = cute::tap_listener<cute::null_listener>{};
  auto runner = cute::makeRunner(listener, argc, argv);

  auto failed = SimpleVariableReplacementSuite{}.RunWith(runner);

  return !failed;
  }
