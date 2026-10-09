#pragma once

//ALL EXTERNAL STUFF

#define WIN32_LEAN_AND_MEAN // eleminates all unnecessary windows for a smaller build
#define NOMINAX // removes min/max keywords so we can create those functions

// win 32 headers
#include <objbase.h>
#include <Windows.h>

//std headers
#include <algorithm>
#include <array>
#include <atomic>
#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <filesystem>
#include <functional>
#include <list>
#include <map>
#include <memory>
#include <optional>
#include <string>
#include <unordered_map>
#include <variant>
#include <vector>