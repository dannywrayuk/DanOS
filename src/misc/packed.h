#pragma once

// Allow Packed Structures without Intellisense Errors
#ifdef __INTELLISENSE__
#define packed
#define __attribute__()
#endif