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

  template<typename RunnerType>
  bool RunWith(RunnerType & runner)
    {
    return runner(static_cast<ConcreteTest *>(this)->GenerateSuite(), ConcreteTest::SuiteName);
    }
  };

struct SimpleReplacementTest : FilesystemTemplateTest<SimpleReplacementTest>
  {
  static constexpr auto TemplateName = "simple_replacement.tpl";
  static constexpr auto SuiteName = "Simple variable replacements";

  auto GenerateTemplates()
    {
    auto output = std::ofstream{TemplateName};
    output << "{{ variable }}";
    }

  auto GenerateSuite()
    {
    return cute::suite {
      CUTE_SMEMFUN(SimpleReplacementTest, test_simple_variable_replacement),
      CUTE_SMEMFUN(SimpleReplacementTest, test_simple_variable_replacement_results_in_empty_string_without_value_for_root_property),
      };
    }

  private:
    void test_simple_variable_replacement()
      {
      auto buffer = std::ostringstream{};
      TMapS2M mVariables{
          { "variable", {{ "", "replacement" }} }
      };

      buffer << Cte{mVariables, TemplateName};
      ASSERT_EQUAL("replacement", buffer.str());
      }

    void test_simple_variable_replacement_results_in_empty_string_without_value_for_root_property()
      {
      auto buffer = std::ostringstream{};
      TMapS2M mVariables{
          { "variable", {{ "not-the-root", "replacement" }} }
      };

      buffer << Cte{mVariables, TemplateName};
      ASSERT_EQUAL("", buffer.str());
      }
  };

int main(int argc, char const * const * argv)
  {
  auto listener = cute::tap_listener<cute::null_listener>{};
  auto runner = cute::makeRunner(listener, argc, argv);

  auto failed = SimpleReplacementTest{}.RunWith(runner);

  return !failed;
  }
