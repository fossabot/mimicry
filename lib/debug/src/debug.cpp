#include "debug.h"

void debug (const char* message) {
 printf(ANSI_BOLD "%s:%d: " ANSI_COLOR_MAGENTA "%s: " ANSI_RESET "%s [" ANSI_BOLD ANSI_COLOR_MAGENTA "%s" ANSI_RESET "]\n", __FILE__, __LINE__, message, __func__);
} 