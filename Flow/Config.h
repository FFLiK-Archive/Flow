//==========================================

// Project : Flow
// Developer : 유태우 & 장서현 (KSA DS Project)

// Setting Zone
#define Release false
#define Version 
#define BuildEnv window //window or mac

//==========================================

// Do not touch
#if BuildEnv == window
#define EnvWindow
#else
#define EnvMac
#endif