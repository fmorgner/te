#include "cute/cute.h"
#include "cute/cute_runner.h"
#include "cute/tap_listener.h"

int main(int argc, char const * const * argv)
  {
  auto listener = cute::tap_listener<cute::null_listener>{};
  auto runner = cute::makeRunner(listener, argc, argv);

  auto suite = cute::suite{};
  runner(suite);
  }
