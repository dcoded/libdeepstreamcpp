#pragma once

#include <spdlog/spdlog.h>

#define DEBUG_TRACE spdlog::get("console")->trace("{} {} {}" \
,   __PRETTY_FUNCTION__   \
,   __FILE__              \
,   __LINE__              \
);                                               