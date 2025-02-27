#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class Lab1 {
private:
  static const std::string program_path;

public:
  static std::vector<std::vector<std::string>> run(const std::string &fileName,
                                                   const double &threshold);
};