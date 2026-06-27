#include <stdio.h>

extern "C" {
    FILE _iob_workaround[3] = { *stdin, *stdout, *stderr };
    FILE* __cdecl __iob_func(void) {
        return _iob_workaround;
    }
    FILE* (*__imp___iob_func)(void) = __iob_func;
}
