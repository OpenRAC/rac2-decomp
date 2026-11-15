#include "common.h"

typedef int Vector __attribute__((mode(TI)));
typedef struct {
    unsigned char pad0[0x80];
    Vector q080;
    Vector q090;
    unsigned char pada0[0x1864 - 0xA0];
    char *object;
    float phase;
    unsigned char pad186c[0x2010 - 0x186C];
    Vector joint;
    unsigned char pad2020[0x2290 - 0x2020];
    char *moby;
    unsigned char pad2294[0x2520 - 0x2294];
    short timer;
    short variant;
    unsigned int color;
} Hero5CB0;
extern Hero5CB0 g_hero_state;
extern unsigned char D_001A7A40[] __attribute__((sda));
extern char *CreateMoby(int);
extern void func_002A0F48(char *);
extern void moby_transform_joint_to_world(char *, int, char *);
extern void hero_queue_glow_draw_routine(void);
extern void moby_transform_joint_point(char *, int, char *);
extern void copy_matrix3x4(void *, void *);
extern float ApproachValue(float *, float, float);
extern float FastAddRotations(float, float);
extern int FastDecTimer(short *);
extern int PlayMobySound(int, int, char *);
extern float math_fast_sin_or_cos_b(float);
extern unsigned int FastTweenColor(unsigned int, unsigned int, float);

/* Create and pose the hero effect object, then advance and blend its colors. */
void UpdateHeroJointEffect(void)
{
    float joint[4] __attribute__((aligned(16)));
    float matrix[16] __attribute__((aligned(16)));
    float scale;
    unsigned int first;
    unsigned int second;
    unsigned int color;
    if (g_hero_state.object == 0) {
        char *created;
        created = CreateMoby(0x4B4 /* moby class 1204 */);
        g_hero_state.object = created;
        if (created) {
            *(unsigned int *)(created + 0x78) = 0x801432D7;
            g_hero_state.color = 0x301432D7;
            {
                char *placed = g_hero_state.object;
                qcopy_nc(placed + 0x10, &g_hero_state.q080);
                qcopy_nc(placed + 0xF0, &g_hero_state.q090);
                *(short *)(placed + 0x32) = 0x40;
                (g_hero_state.object)[0x31] = 1;
                (g_hero_state.object)[0x30] = 0;
                *(short *)(g_hero_state.object + 0x34) = 0;
                *(float *)(g_hero_state.object + 0x2C) *= 1.7f;
                *(unsigned short *)(g_hero_state.object + 0x34) |= 0x10;
                func_002A0F48(g_hero_state.object);
            }
        }
    }
    if ((*(unsigned short *)(g_hero_state.moby + 0x34) ^ 1) & 1) {
        moby_transform_joint_to_world(g_hero_state.moby, 7, (char *)joint);
        qcopy(&g_hero_state.joint, joint);
        hero_queue_glow_draw_routine();
        if (g_hero_state.object) {
            moby_transform_joint_point(g_hero_state.moby, 7, (char *)matrix);
            qcopy_nc(g_hero_state.object + 0x10, matrix + 12);
            copy_matrix3x4(g_hero_state.object + 0xC0, matrix);
            func_002A0F48(g_hero_state.object);
            scale = 1.7f;
            if (D_001A7A40[3])
                scale = 3.1f;
            if (g_hero_state.timer)
                scale *= 1.4f;
            ApproachValue((float *)(g_hero_state.object + 0x2C), *(float *)(*(char **)(g_hero_state.object + 0x24) + 0x24) * scale, 0.02f);
        }
    }
    g_hero_state.phase = FastAddRotations(g_hero_state.phase, 0.049451005f);
    first = 0x281414C8;
    second = 0x1E00004B;
    if (!FastDecTimer(&g_hero_state.timer)) {
        g_hero_state.phase = FastAddRotations(g_hero_state.phase, 0.20362177f);
        switch (g_hero_state.variant) {
        case 1: first = 0x2814C814; second = 0x1E004B00; break;
        case 2: first = 0x2814C8C8; second = 0x1E004B4B; break;
        case 3: first = 0x323232FA; second = 0x1E000078; break;
        case 4: first = 0x28F01414; second = 0x1E4B0000; break;
        }
        if (g_hero_state.timer >= 50 && (g_hero_state.timer & 1))
            PlayMobySound(g_hero_state.variant + 16, 0, g_hero_state.moby);
    }
    color = FastTweenColor(first, second, math_fast_sin_or_cos_b(g_hero_state.phase) * 0.5f + 0.5f);
    if (g_hero_state.object)
        *(unsigned int *)(g_hero_state.object + 0x78) = FastTweenColor(*(unsigned int *)(g_hero_state.object + 0x78), color, 0.1f);
    g_hero_state.color = FastTweenColor(g_hero_state.color, color, 0.1f);
}
