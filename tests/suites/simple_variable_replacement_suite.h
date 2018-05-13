#ifndef __SIMPLE_VARIABL_REPLACEMENT_SUITE_H
#define __SIMPLE_VARIABL_REPLACEMENT_SUITE_H

#include "filesystem_template_suite_base.h"

#include "te.h"

#include "cute/cute.h"
#include "cute/cute_runner.h"
#include "cute/tap_listener.h"

struct SimpleVariableReplacementSuite : FilesystemTemplateSuiteBase<SimpleVariableReplacementSuite>
  {
  static constexpr auto SuiteName = "Simple variable replacements";

  static constexpr auto TemplateName = "simple_variable_replacement.tpl";
  static constexpr auto Template = "{{ variable }}";

  auto GetSuite()
    {
    return cute::suite {
      CUTE_SMEMFUN(SimpleVariableReplacementSuite, test_simple_variable_replacement),
      CUTE_SMEMFUN(SimpleVariableReplacementSuite, test_simple_variable_replacement_results_in_empty_string_without_value_for_root_property),
      };
    }

  private:
    void test_simple_variable_replacement()
      {
      TMapS2M mVariables{
          { "variable", {{ "", "replacement" }} }
      };

      oOutputBuffer << Cte{mVariables, TemplateName};
      ASSERT_EQUAL("replacement", oOutputBuffer.str());
      }

    void test_simple_variable_replacement_results_in_empty_string_without_value_for_root_property()
      {
      TMapS2M mVariables{
          { "variable", {{ "not-the-root", "replacement" }} }
      };

      oOutputBuffer << Cte{mVariables, TemplateName};
      ASSERT_EQUAL("", oOutputBuffer.str());
      }
  };

#endif
