#include "labs/Lab1.h"

const std::string Lab1::program_path =
    "/mnt/d/LETI/k1/s2/proga/1stLab/build/main";

std::vector<std::vector<std::string>>
Lab1::run(const std::string &fileName, const double &threshold) {
  std::string command = program_path;
  command += " \"" + fileName + "\"";
  command += " -tr " + std::to_string(threshold);

  FILE *pipe = popen(command.c_str(), "r");
  if (!pipe) {
    throw std::runtime_error("Failed to run process");
  }

  std::vector<std::vector<std::string>> output(3);
  std::string section;
  char buffer[128];

  while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
    std::string line(buffer);
    if (line.find("Byte occurrence frequencies:") != std::string::npos) {
      section = "freq";
    } else if (line.find("Quantitative representation:") != std::string::npos) {
      section = "quant";
    } else if (line.find("Histogram:") != std::string::npos) {
      section = "hist";
    } else if (!line.empty()) {
      if (section == "freq") {
        output[0].push_back(line);
      } else if (section == "quant") {
        output[1].push_back(line);
      } else if (section == "hist") {
        output[2].push_back(line);
      }
    }
  }

  pclose(pipe);
  return output;
}