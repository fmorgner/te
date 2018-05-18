#ifndef SIMPLE_VARIABLE_REPLACEMNT_H
#define SIMPLE_VARIABLE_REPLACEMNT_H

#include "cute/cute_equals.h"

#include "../cute/extensions.h"
#include "../test_holder.h"

#include "te.h"

namespace simple_variable_replacement
  {

  void test_simple_variable_replacement()
    {
    auto oData = TMapS2M{{"variable", {{"", "replacement"}}}};
    ASSERT_EQUAL("replacement", perform_replacement(oData, "{{ variable }}"));
    }

  void test_simple_variable_replacement_without_root_value_should_produce_empty_replacement()
    {
    auto oData = TMapS2M{{"variable", {{"not_the_root", "replacement"}}}};
    ASSERT_EQUAL("", perform_replacement(oData, "{{ variable }}"));
    }

  void test_simple_variable_replacement_without_replacement_for_variable_should_leave_template_intact()
    {
    auto oData = TMapS2M{};
    ASSERT_EQUAL("{{ variable }}", perform_replacement(oData, "{{ variable }}"));
    }

  auto suite = cutex::NamedSuite {
    "Simple variable replacement",
      {
      CUTE(test_simple_variable_replacement),
      CUTE(test_simple_variable_replacement_without_root_value_should_produce_empty_replacement),
      CUTE(test_simple_variable_replacement_without_replacement_for_variable_should_leave_template_intact),
      }
  };

  }



#endif
