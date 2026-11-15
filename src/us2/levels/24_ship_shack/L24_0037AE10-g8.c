#include "include_asm.h"
#include "names.h"

typedef struct { float x,y,z,w; } Point;
typedef struct {
    unsigned char pad0[0x80];
    Point position;
    unsigned char pad90[8];
    float heading;
    unsigned char pad9c[0x2294-0x9c];
    int mode;
    unsigned char pad2298[4];
    int activity;
} PlayerView;
extern unsigned char g_hero_state[];
extern int D_L24_001AEBB8 __attribute__((sda));
extern int D_L24_001AEBBC __attribute__((sda));
extern int D_L24_001A8F00;
extern unsigned int D_00138324 __attribute__((nosda));
extern void moby_set_state(unsigned char *, unsigned char, int);
extern void math_store_angle_update_result(char *, float *, int, int, float);
extern float vec_distance_xy(void *, void *);
extern float math_fabs(float);
extern float mat_fast_helper_a(float, float);
extern float FastDiffRots(float, float);
extern int TryClaimNotice(int, int, int);
extern int request_begin_slot(int, int, int, int, unsigned char *);

void func_US2_L24_0037AE10(unsigned char *object)
{
    unsigned int permitted;
    int selected;
    float *animation = *(float **)(object + 0x68);
    switch (object[0x20]) {
    case 0:
        moby_set_state(object, 1, -1);
        break;
    case 1:
        permitted = 1;
        selected = 0;
        math_store_angle_update_result((char *)object, animation,
                          D_L24_001AEBB8, D_L24_001AEBBC, 0.043633237f);
        if (((PlayerView *)g_hero_state)->activity && ((PlayerView *)g_hero_state)->mode != 3) {
            if (((PlayerView *)g_hero_state)->activity != 1) permitted = 0;
        }
        if (vec_distance_xy(object + 0x10, &((PlayerView *)g_hero_state)->position) > 3.0f ||
            math_fabs(((PlayerView *)g_hero_state)->position.z - *(float *)(object + 0x18)) > 0.7f)
            permitted = 0;
        if (FastDiffRots(((PlayerView *)g_hero_state)->heading,
              mat_fast_helper_a(*(float *)(object + 0x10) - ((PlayerView *)g_hero_state)->position.x,
                            *(float *)(object + 0x14) - ((PlayerView *)g_hero_state)->position.y)) > 1.5707965f)
            permitted = 0;
        if (((PlayerView *)g_hero_state)->mode == 0x1c || ((PlayerView *)g_hero_state)->mode == 0x31) permitted = 0;
        if (permitted) selected = TryClaimNotice(1, 0x12EB, 1) != 0;
        if ((D_00138324 & 0x10) && selected) {
            request_begin_slot(5, 1, (int)object, 0, 0);
            object[0x20] = 2;
        }
        break;
    case 2:
        if (!D_L24_001A8F00) object[0x20] = 1;
        break;
    }
}
