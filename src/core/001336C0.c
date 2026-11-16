#include "names.h"
extern int g_snd_cmd_result __attribute__((sda));
extern int g_snd_stop_callback __attribute__((sda));
extern void *sceCdCallback(void);
/* Sets the sound stop callback and returns the old one. */
void *snd_set_stop_callback(int newValue) {
    int oldValue;
    if (g_snd_cmd_result == 0)
        return sceCdCallback();
    oldValue = g_snd_stop_callback;
    g_snd_stop_callback = newValue;
    return oldValue;
}
