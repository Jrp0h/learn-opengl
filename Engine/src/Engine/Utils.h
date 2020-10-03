#pragma once

#include <sstream>
#include <string>
#include <vector>

class Utils {
  public:
    static std::string ConcatStrings(std::vector<std::string> strings) {
      std::stringstream ss;

      for(auto str : strings)
        ss << str;

      return ss.str();
    }
};
