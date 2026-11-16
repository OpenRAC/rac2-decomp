#include "include_asm.h"
#include "common.h"







extern int func_002A77E0_3(int x);

/* func_PAL_L00_004040D8, the PAL copy of func_L00_003FF7B8: four random floats, four fixed ones,
   then the fade table at +0x20 scaled to 50 Hz, which turns its loop into a count-up one. */
void func_PAL_L00_004040D8(char *self)
{
    float *p = *(float **)(self + 104);
    float *q = p;
    int *w;
    int i;
    int j;

    for (i = 3; i >= 0; i--)
    {
        *q = (float)func_002A77E0_3(255);
        q++;
    }

    p[4] = -1.0000000000000000000000e+00f;
    p[5] = -2.2500000000000000000000e+00f;
    p[6] = 1.2500000000000000000000e+00f;
    p[7] = 2.5000000000000000000000e+00f;

    w = (int *)(p + 8);
    for (j = 0; j < 4; j++)
    {
        w[j] = ((s32)(j * 64 + 63) * 5 + 2) / 6;
    }

    p[12] = 2.5000000000000000000000e+00f;
    p[13] = 3.0000000000000000000000e+00f;
    p[15] = 2.5000000000000000000000e+00f;
    p[14] = 3.0000000000000000000000e+00f;
}


extern void moby_set_state(char *arg, int mode, int value);
extern void func_PAL_L00_004040D8(char *arg);
extern void func_PAL_L00_004041C0(char *arg);
extern float vec_distance_xy(char *arg, char *table);
extern float math_fabs(float value);
extern void value_set_entry_by_index_pal(int arg, int value);
extern void help_unlock_entry(int arg);
extern int moby_handle_request_slot_state(int arg);
extern void moby_mark_spawned(char *arg);
extern char D_00189EA0_2[];
extern unsigned char g_action_flag __attribute__((sda));
extern void func_002E6EF8(void (*f)(char *), char *arg);

/* two-state update on a record: state 0 marks a byte with 255 and either runs a shared two-call teardown when a global latch byte is set and a sub-object field is non-zero, or plays a mode/value pair plus a call; state 1 runs a setup call and two float queries against a stored table and, when both are below 2.0, plays three fixed calls and either tears down or writes 120 into a sub-object field */
void func_PAL_L00_004043A0(char *arg)
{
    int *object = *(int **)(arg + 104);
    unsigned char state = *(unsigned char *)(arg + 32);

    switch (state) {
    case 0:
        *(unsigned char *)(arg + 48) = 255;
        if (g_action_flag != 0 && object[17] != 0) {
            moby_mark_spawned((char *)object[17]);
            moby_mark_spawned(arg);
            return;
        } else {
            moby_set_state(arg, 1, -1);
            func_PAL_L00_004040D8(arg);
        }
        break;
    case 1:
        func_PAL_L00_004041C0(arg);
        if (vec_distance_xy(arg + 16, D_00189EA0_2) < 2.0f) {
            if (math_fabs(*(float *)(arg + 24) - *(float *)(D_00189EA0_2 + 8)) < 2.0f) {
                value_set_entry_by_index_pal(4658, -1);
                help_unlock_entry(54);
                moby_handle_request_slot_state(54);
                if (object[17] != 0) {
                    moby_mark_spawned((char *)object[17]);
                    moby_mark_spawned(arg);
                    return;
                }
                object[16] = 100;
            }
        }
        break;
    }
}


