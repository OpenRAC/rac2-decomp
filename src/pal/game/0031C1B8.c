#include "include_asm.h"



#include "common.h"
extern float FastAddRotations(float, float);
extern float math_fabs(float);
extern void math_build_axis_angle_quat(void *, void *, float);
extern void vec_rotate_by_quaternion(void *, void *, void *);
extern int math_random_int_below(int);
extern int D_001AFAFC SDATA(D_001AFAFC);
extern void func_PAL_0031E690(void *, int);
extern int snd_is_voice_playing_for_owner(void *, int);
extern int PlayMobySound(int, int, void *);
extern void snd_stop_voice(int);
extern void func_PAL_002AC3C0(void *, void *);
extern int FastDecTimer(void *);
extern char g_sound_state[];

void func_PAL_0031DAB8(char *object)
{
    float axis[4];
    char *state = *(char **)(object + 0x68);
    if (*(unsigned char *)(object + 0x95) != 0 &&
        *(unsigned char *)(object + 0x20) != 3 &&
        *(unsigned char *)(object + 0x95) != 5 &&
        *(int *)(state + 0x294) == 0) {
        *(float *)(state + 0x27C) = FastAddRotations(*(float *)(state + 0x27C), 0.3141593039035797f);
        if (0.00001f <= math_fabs(*(float *)(state + 0x27C))) {
            char *target;
            target = *(char **)(state + 0x270);
            math_build_axis_angle_quat(axis, target + 0xE0, *(float *)(state + 0x27C));
            { char *row = *(char **)(state + 0x270) + 0xC0;
                vec_rotate_by_quaternion(row, row, axis); }
            { char *row = *(char **)(state + 0x270) + 0xD0;
                vec_rotate_by_quaternion(row, row, axis); }
            target = *(char **)(state + 0x274);
            math_build_axis_angle_quat(axis, target + 0xE0, *(float *)(state + 0x27C));
            { char *row = *(char **)(state + 0x274) + 0xC0;
                vec_rotate_by_quaternion(row, row, axis); }
            { char *row = *(char **)(state + 0x274) + 0xD0;
                vec_rotate_by_quaternion(row, row, axis); }
            target = *(char **)(state + 0x278);
            math_build_axis_angle_quat(axis, target + 0xE0, *(float *)(state + 0x27C));
            { char *row = *(char **)(state + 0x278) + 0xC0;
                vec_rotate_by_quaternion(row, row, axis); }
            { char *row = *(char **)(state + 0x278) + 0xD0;
                vec_rotate_by_quaternion(row, row, axis); }
        }
        /* Each snapshot is consumed by the immediately following opaque call;
         * no C memory access crosses the non-clobbering transfer. */
        if (math_random_int_below(D_001AFAFC) == 1) {
            qcopy_nc(axis, *(char **)(state + 0x270) + 0x10);
            func_PAL_0031E690(axis, 1);
        }
        if (math_random_int_below(D_001AFAFC) == 1) {
            qcopy_nc(axis, *(char **)(state + 0x274) + 0x10);
            func_PAL_0031E690(axis, 1);
        }
        if (math_random_int_below(D_001AFAFC) == 1) {
            qcopy_nc(axis, *(char **)(state + 0x278) + 0x10);
            func_PAL_0031E690(axis, 1);
        }
        if (!snd_is_voice_playing_for_owner(*(void **)(state + 0x278), *(int *)(state + 0x290)))
            *(int *)(state + 0x290) = PlayMobySound(0, 4, *(void **)(state + 0x278));
    } else {
        int handle = *(int *)(state + 0x290);
        if (handle != -1) {
            char *sound = g_sound_state + handle * 112;
            if (*(char **)(sound + 0x88) == *(char **)(state + 0x278) &&
                *(unsigned char *)(sound + 0x74) != 0)
                snd_stop_voice(handle);
        }
        *(int *)(state + 0x290) = -1;
    }
    func_PAL_002AC3C0(object, state + 0x50);
    FastDecTimer(state + 0x240);
    FastDecTimer(state + 0x242);
    if (*(unsigned short *)(object + 0x96) < 0xFFFF)
        *(unsigned short *)(object + 0x96) += 1;
}

