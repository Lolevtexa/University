#pragma once

#include "../List/List.hpp"

static bool haveErrors = false;

List InputFromFile(const char *, String &, String &);

void OutputToFile(const char *, List, std::ios_base::openmode);

void Processing(List &, String, String);