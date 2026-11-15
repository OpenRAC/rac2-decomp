#include "common.h"

typedef int Vector __attribute__((mode(TI)));

/* The seven 0x40-byte effect records in the resident hero state. */
typedef struct {
    unsigned char type;
    unsigned char active;
    unsigned char pad2;
    unsigned char enabled;
    unsigned char pad4[8];
    float fade;
    Vector a;
    Vector b;
    Vector c;
} Effect5518;

typedef struct {
    unsigned char pad[0xEC0];
    Effect5518 effects[7];
    unsigned char pad1080[0x100];
    int counter;
    unsigned char pad1184[0x2290 - 0x1184];
    unsigned char *moby;
} Hero5518;

extern Hero5518 g_hero_state;

typedef struct {
    unsigned char pad[0x274];
    float pitch;
    float yaw;
    unsigned char pad27c[0x8A4 - 0x27C];
    float out_pitch;
    float out_yaw;
} Control5518;

extern Control5518 D_L00_0025BE10;
extern Vector D_L00_0025DD90[7];
extern Vector D_L00_0025DE00[7];
extern Vector D_L00_0025DE70[7];
extern int D_L00_001A7E40[7] SDATA(D_L00_001A7E40);
extern float D_L00_001A7E10[12] SDATA(D_L00_001A7E10);
extern void hero_update_effect_delay_timer(void);
extern void moby_detach_manipulator(char *, char *);
extern void AttachManipulator(unsigned char *, unsigned int, unsigned char *);

/* Clamp control rotations and initialize, fade or retire the hero effects. */
void ClampHeroControlAndUpdateEffects(void)
{
    D_L00_0025BE10.out_yaw = D_L00_0025BE10.yaw * 0.25f;
    if (D_L00_0025BE10.out_yaw > 0.148353f)
        D_L00_0025BE10.out_yaw = 0.148353f;
    else if (D_L00_0025BE10.out_yaw < -0.148353f)
        D_L00_0025BE10.out_yaw = -0.148353f;
    D_L00_0025BE10.out_pitch = D_L00_0025BE10.pitch * 0.35714287f;
    if (D_L00_0025BE10.out_pitch > 0.296706f)
        D_L00_0025BE10.out_pitch = 0.296706f;
    if (D_L00_0025BE10.out_pitch < -0.17453295f)
        D_L00_0025BE10.out_pitch = -0.17453295f;
    if ((unsigned int)(*(unsigned char *)((char *)g_hero_state.moby + 0x43) - 1) < 2) {
        if (D_L00_0025BE10.out_yaw > 0.03490659f)
            D_L00_0025BE10.out_yaw = 0.03490659f;
        if (D_L00_0025BE10.out_yaw < -0.03490659f)
            D_L00_0025BE10.out_yaw = -0.03490659f;
        if (D_L00_0025BE10.out_pitch > 0.122173056f)
            D_L00_0025BE10.out_pitch = 0.122173056f;
        if (D_L00_0025BE10.out_pitch < -0.122173056f)
            D_L00_0025BE10.out_pitch = -0.122173056f;
    }
    hero_update_effect_delay_timer();
    if (g_hero_state.counter == 0)
        return;
    g_hero_state.counter += 1;
    if (g_hero_state.counter >= 12)
        g_hero_state.counter = 0;
    if (g_hero_state.counter == 0) {
        int i;
        for (i = 0; i < 7; i++) {
            if (g_hero_state.effects[i].active)
                moby_detach_manipulator((char *)g_hero_state.moby, (char *)&g_hero_state.effects[i]);
        }
        return;
    }
    {
        int i;
        for (i = 0; i < 7; i++) {
            if (!g_hero_state.effects[i].active) {
                AttachManipulator(g_hero_state.moby, D_L00_001A7E40[i],
                             (unsigned char *)&g_hero_state.effects[i]);
                g_hero_state.effects[i].enabled = 1;
                qcopy(&g_hero_state.effects[i].a, D_L00_0025DD90 + i);
                qcopy(&g_hero_state.effects[i].b, D_L00_0025DE00 + i);
                qcopy(&g_hero_state.effects[i].c, D_L00_0025DE70 + i);
            }
        }
    }
    {
        int i;
        for (i = 0; i < 7; i++)
            g_hero_state.effects[i].fade = D_L00_001A7E10[g_hero_state.counter];
    }
}
