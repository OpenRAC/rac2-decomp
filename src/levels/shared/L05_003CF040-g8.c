#include "common.h"
extern void moby_randomize_reach_and_angles(char *);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecScale(void *, void *, float);
extern float D_L05_001AFBE4 __attribute__((sda));
extern float D_L05_001AFB68[1] __attribute__((sda));
extern int vec_fast_helper_b(void *);
extern void moby_mark_spawned(char *);
extern float math_fabs(float);
extern int moby_class_id_to_table_index(int);
extern float FastAddRotations(float, float);
extern void cam_shake_if_object_near(char *);
extern int func_L05_003CF350(char *);
extern int snd_play_from_class_bank(int, int, char *, int);
extern int g_current_map_index;
extern unsigned char D_00139619[1] NOT_SDA;
extern void func_L05_003CFCF0(char *, int, int);
/* Moves a flying debris piece, slows it down, and removes it when it hits something or leaves
   the world. */
void func_L05_003CF040(unsigned char *obj)
{
    char *s = *(char **)(obj + 0x68);
    int kind;
    switch ((unsigned char)obj[0x20]) {
    case 0:
        obj[0x20] = 1;
        moby_randomize_reach_and_angles(obj);
    case 2:
    case 3:
        FastVecAdd(obj + 0x10, obj + 0x10, s + 0x10);
        FastVecScale(s + 0x10, s + 0x10, (D_L05_001AFBE4 - 1.0f) + 1.0f);
        if ((unsigned char)obj[0x20] != 2) {
            if (vec_fast_helper_b(s + 0xC) && (unsigned char)obj[0x31] == 0) {
                moby_mark_spawned(obj);
                return;
            }
        } else {
            if (math_fabs(*(float *)(s + 0x10)) < 0.01f &&
                math_fabs(*(float *)(s + 0x14)) < 0.01f &&
                math_fabs(*(float *)(s + 0x18)) < 0.01f)
                obj[0x20] = 1;
        }
    case 1:
        kind = moby_class_id_to_table_index(*(short *)(obj + 0xAA));
        *(float *)(obj + 0x2C) = *(float *)(*(char **)(obj + 0x24) + 0x24) * D_L05_001AFB68[kind];
        *(float *)(obj + 0xF0) = FastAddRotations(*(float *)s, *(float *)(obj + 0xF0));
        *(float *)(obj + 0xF4) = FastAddRotations(*(float *)(s + 4), *(float *)(obj + 0xF4));
        *(float *)(obj + 0xF8) = FastAddRotations(*(float *)(s + 8), *(float *)(obj + 0xF8));
        cam_shake_if_object_near(obj);
        if (func_L05_003CF350(obj) || *(float *)(obj + 0x10) < 2.0f || *(float *)(obj + 0x10) > 1021.0f ||
            *(float *)(obj + 0x14) < 2.0f || *(float *)(obj + 0x14) > 1021.0f ||
            *(float *)(obj + 0x18) < 2.0f || *(float *)(obj + 0x18) > 1021.0f) {
            if (D_L05_001AFB68[kind] >= 5.0f) {
                snd_play_from_class_bank(0, 0, obj, 0x956);
                if (g_current_map_index == 5 && D_00139619[0] == 0)
                    func_L05_003CFCF0(obj, 1, 5);
                else
                    func_L05_003CFCF0(obj, 0, 5);
            } else {
                if (*(short *)(obj + 0xAA) == 0x954) snd_play_from_class_bank(0, 0, obj, 0x954);
                if (*(short *)(obj + 0xAA) == 0x955) snd_play_from_class_bank(0, 0, obj, 0x955);
            }
            moby_mark_spawned(obj);
        }
        break;
    }
}
