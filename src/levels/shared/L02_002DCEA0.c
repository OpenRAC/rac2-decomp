typedef struct { char pad0[0x268]; float rate; float progress; int mode; } S;
extern S ref_L02_002DCEA0_00;
/* Starts a timer that runs for the given time, unless one is already running. */
void func_L02_002DCEA0(int newMode, float duration) {
    S *state = &ref_L02_002DCEA0_00;
    if (state->progress == 0.0f) {
        state->mode = newMode;
        state->progress = 1.0f;
        state->rate = 1.0f / duration;
    }
}
