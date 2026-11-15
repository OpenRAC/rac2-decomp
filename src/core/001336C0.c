#include "names.h"
extern int D_001A748C __attribute__((sda));
extern int D_001A7490 __attribute__((sda));
extern int func_001245D0(void);
/* Sets the sound stop callback and returns the old one. */
int func_001336C0(int newValue) {
    int oldValue;
    if (D_001A748C == 0)
        return SetCdCallbackHandler();
    oldValue = D_001A7490;
    D_001A7490 = newValue;
    return oldValue;
}
