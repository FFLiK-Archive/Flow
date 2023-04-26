#pragma once

// ===== Config Setting Zone =====

// Build Type : window or mac
#define FlowBuildType window

// Build Mode : debug, release
#define FlowBuildMode debug

// Version Information
#define FlowVersion "v 0.1"

// ===============================


// WINDOW_BUILD or MAC_BUILD value
#if FlowBuildType == window
#define WINDOW_BUILD true
#define MAC_BUILD false
#else
#define WINDOW_BUILD false
#define MAC_BUILD true
#endif

// DEBUG or RELEASE value
#if FlowBuildMode == debug
#define DEBUG_BUILD true
#define RELEASE_BUILD false
#else
#define DEBUG false
#define RELEASE true
#endif