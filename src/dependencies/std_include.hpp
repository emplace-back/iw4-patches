#pragma once

#include <windows.h>
#include <mutex>
#include <fstream>
#include <filesystem>
#include <cctype>
#include <d3d9.h>
#include <sstream>
#include <assert.h>
#include <regex>
#include <intrin.h>
#include <winsock.h>

using namespace std::literals;

#include "dependencies/hooks/detours.hpp"

#include "game/game.hpp"

#include "utils/utils.hpp"
#include "utils/hook.hpp"
#include "utils/memory.hpp"
#include "utils/string.hpp"
#include "utils/concurrency.hpp"

#include "core/misc/misc.hpp"
#include "core/command/command.hpp"
#include "core/host/host.hpp"
#include "core/security/security.hpp"
#include "core/network/network.hpp"
#include "core/scheduler/scheduler.hpp"
#include "core/exception/exception.hpp"