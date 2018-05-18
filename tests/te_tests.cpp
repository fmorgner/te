#include "cute/cute.h"
#include "cute/cute_runner.h"
#include "cute/tap_listener.h"
#include "cute/xml_listener.h"

#include "cute/extensions.h"

#include "test_holder.h"

#include "suites/invalid_template_syntax.h"
#include "suites/simple_variable_replacement.h"

#include "te.h"

int main(int argc, char const * const * argv)
  {
  auto xml = cute::xml_file_opener{argc, argv};
  auto listener = cute::xml_listener<cute::tap_listener<>>{xml.out};
  auto runner = cute::makeRunner(listener, argc, argv);

  auto success = true;

  success &= invalid_template_syntax::suite.run_with(runner);
  success &= simple_variable_replacement::suite.run_with(runner);

  return !success;
  }
