#include "include_asm.h"
#include "names.h"

extern int g_tether_fin_counter;
extern void moby_mark_spawned(char *object);
extern void offset_moby_class_point_pairs(char *object, int mode, int delta);
extern float math_random_float_range(float low, float high);
extern float math_wrap_angle_to_pi(float angle);
extern float FastAddRotations(float value, float amount);
extern void func_002A10E8(char *object);

void func_PAL_L00_00398568(char *object)
{
    char *s1 = *(char **)(object + 0x68);
    char *other = *(char **)(s1 + 8);
    unsigned char tag = *(unsigned char *)(other + 0x20);

    if (tag == 0 || (tag & 0xF0) == 0xF0) {
        moby_mark_spawned(object);
        return;
    }
    if (other != 0) {
        if ((*(unsigned short *)(object + 0x34) & 1) != (*(unsigned short *)(other + 0x34) & 1)) {
            unsigned short bits = *(unsigned short *)(object + 0x34) & 0xFFFE;

            *(unsigned short *)(object + 0x34) = bits;
            bits |= *(unsigned short *)(*(char **)(s1 + 8) + 0x34) & 1;
            *(unsigned short *)(object + 0x34) = bits;
        }
    }
    if (g_tether_fin_counter < 0x15)
        *(unsigned short *)(object + 0x34) |= 0x41;
    {
        int current = *(int *)(s1 + 4);
        int next = current - 0xC0;
        int delta = -0xC0;

        *(int *)(s1 + 4) = next;
        if (next >= 0x1001) {
            delta = -0x10C0;
            *(int *)(s1 + 4) = current - 0x10C0;
        } else if (next < 0) {
            delta = 0xF40;
            *(int *)(s1 + 4) = current + 0xF40;
        }
        offset_moby_class_point_pairs(*(char **)(object + 0x24), 0, delta);
    }
    *(float *)(object + 0x2C) = *(float *)(*(char **)(object + 0x24) + 0x24)
                                * *(float *)(s1 + 0xC) * math_random_float_range(0.5f, 1.0f);
    *(float *)(object + 0xF4) = FastAddRotations(*(float *)(object + 0xF4),
                                             math_wrap_angle_to_pi(*(float *)(s1 + 0xC)));
    func_002A10E8(object);
}


