#include "cute/cute.h"
#include "cute/cute_runner.h"
#include "cute/tap_listener.h"

#include "te.h"

#include <fstream>
#include <sstream>

template<typename ConcreteTest>
struct FilesystemTemplateTest
  {
  FilesystemTemplateTest()
    {
    static_cast<ConcreteTest *>(this)->GenerateTemplates();
    }
  };

struct SimpleReplacementTest : FilesystemTemplateTest<SimpleReplacementTest>
  {
  static constexpr auto TemplateName = "simple_replacement.tpl";

  void GenerateTemplates()
    {
    auto output = std::ofstream{TemplateName};
    output << "before {{ variable }} after {{ variable.id }}";
    }

  void test_simple_variable_replacement()
    {
    auto buffer = std::ostringstream{};
    TMapS2M mVariables{
        { "variable", {{ "",   "replacement" },{ "id", "an id for 2" }} }
    };

    auto oTe = Cte{mVariables, TemplateName};

    buffer << oTe;

    ASSERT_EQUAL(buffer.str(), "before replacement after an id for 2");
    }
  };

int main(int argc, char const * const * argv)
  {
  auto listener = cute::tap_listener<cute::null_listener>{};
  auto runner = cute::makeRunner(listener, argc, argv);

  auto suite = cute::suite{};

  auto oSimpleReplacementTest = SimpleReplacementTest{};
  suite += CUTE_MEMFUN(oSimpleReplacementTest, SimpleReplacementTest, test_simple_variable_replacement);

  return !runner(suite);
  }
