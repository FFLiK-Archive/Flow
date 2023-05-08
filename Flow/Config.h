#pragma once

// Build Type Values
#define Flow_Auto 0
#define Flow_Windows 1
#define Flow_MacOS 2

// Build Mode Values
#define Flow_Debug 0
#define Flow_Release 1

// ===== Config Setting Zone =====

// Build Type : Flow_Windows or Flow_MacOS or Flow_Auto
#define FlowBuildType Flow_Auto

// Build Mode : Flow_Debug, Flow_Release
#define FlowBuildMode Flow_Release

// Version Information
#define FlowVersion "v 0.1"

// ===============================

// ====== Available Values =======
// WIN_BUILD or MAC_BUILD
// DEBUG or RELEASE

// WIN_BUILD or MAC_BUILD value
#if FlowBuildType == Windows
#define WIN_BUILD true
#define MAC_BUILD false
#elif FlowBuildType == MacOS
#define WIN_BUILD false
#define MAC_BUILD true
#else
#if _WIN32
#define WIN_BUILD true
#define MAC_BUILD false
#elif __APPLE__
#define WIN_BUILD false
#define MAC_BUILD true
#endif
#endif

// DEBUG or RELEASE value
#if FlowBuildMode == debug
#define DEBUG_BUILD true
#define RELEASE_BUILD false
#else
#define DEBUG false
#define RELEASE true
#endif

using Time = time_t;