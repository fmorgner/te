#ifndef __FILESYSTEM_TEMPLATE_SUITE_BASE_H
#define __FILESYSTEM_TEMPLATE_SUITE_BASE_H

#include <filesystem>
#include <fstream>
#include <sstream>

template<typename ConcreteSuite>
struct FilesystemTemplateSuiteBase
  {
  FilesystemTemplateSuiteBase()
    {
    if(!std::filesystem::exists(ConcreteSuite::TemplateName))
      {
      auto output = std::ofstream{ConcreteSuite::TemplateName};
      output << ConcreteSuite::Template;
      }
    }

  template<typename RunnerType>
  bool RunWith(RunnerType & runner)
    {
    return runner(static_cast<ConcreteSuite *>(this)->GetSuite(), ConcreteSuite::SuiteName);
    }

  std::ostringstream oOutputBuffer{};
  };

#endif
