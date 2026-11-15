#include "names.h"
extern int D_001A748C __attribute__((sda));
extern int D_001A7490 __attribute__((sda));
extern int sceCdCallback(void);
/* Sets the sound stop callback and returns the old one. */
int snd_set_stop_callback(int newValue) {
    int oldValue;
    if (D_001A748C == 0)
        return sceCdCallback();
    oldValue = D_001A7490;
    D_001A7490 = newValue;
    return oldValue;
}
