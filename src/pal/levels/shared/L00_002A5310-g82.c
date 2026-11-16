#include "include_asm.h"

#include "common.h"
typedef int Vector __attribute__((mode(TI)));
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
extern Control5518 g_hero_item_attach_records;
extern Vector g_hero_effect_vectors_a[7];
extern Vector g_hero_effect_vectors_b[7];
extern Vector g_hero_effect_vectors_c[7];
extern int g_hero_manipulator_ids[7] SDATA(D_L00_001A7E40);
extern float g_hero_effect_fade_table[12] SDATA(D_L00_001A7E10);
extern void hero_update_effect_delay_timer_pal(void);
extern void moby_detach_manipulator(char *, char *);
extern void AttachManipulator(unsigned char *, unsigned int, unsigned char *);

/* Clamp control rotations and initialize, fade or retire the hero effects. */
void ClampHeroControlAndUpdateEffects_pal(void)
{
    g_hero_item_attach_records.out_yaw = g_hero_item_attach_records.yaw * 0.25f;
    if (g_hero_item_attach_records.out_yaw > 0.148353f)
        g_hero_item_attach_records.out_yaw = 0.148353f;
    else if (g_hero_item_attach_records.out_yaw < -0.148353f)
        g_hero_item_attach_records.out_yaw = -0.148353f;
    g_hero_item_attach_records.out_pitch = g_hero_item_attach_records.pitch * 0.35714287f;
    if (g_hero_item_attach_records.out_pitch > 0.296706f)
        g_hero_item_attach_records.out_pitch = 0.296706f;
    if (g_hero_item_attach_records.out_pitch < -0.17453295f)
        g_hero_item_attach_records.out_pitch = -0.17453295f;
    if ((unsigned int)(*(unsigned char *)((char *)g_hero_state.moby + 0x43) - 1) < 2) {
        if (g_hero_item_attach_records.out_yaw > 0.03490659f)
            g_hero_item_attach_records.out_yaw = 0.03490659f;
        if (g_hero_item_attach_records.out_yaw < -0.03490659f)
            g_hero_item_attach_records.out_yaw = -0.03490659f;
        if (g_hero_item_attach_records.out_pitch > 0.122173056f)
            g_hero_item_attach_records.out_pitch = 0.122173056f;
        if (g_hero_item_attach_records.out_pitch < -0.122173056f)
            g_hero_item_attach_records.out_pitch = -0.122173056f;
    }
    hero_update_effect_delay_timer_pal();
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
                AttachManipulator(g_hero_state.moby, g_hero_manipulator_ids[i],
                             (unsigned char *)&g_hero_state.effects[i]);
                g_hero_state.effects[i].enabled = 1;
                qcopy(&g_hero_state.effects[i].a, g_hero_effect_vectors_a + i);
                qcopy(&g_hero_state.effects[i].b, g_hero_effect_vectors_b + i);
                qcopy(&g_hero_state.effects[i].c, g_hero_effect_vectors_c + i);
            }
        }
    }
    {
        int i;
        for (i = 0; i < 7; i++)
            g_hero_state.effects[i].fade = g_hero_effect_fade_table[g_hero_state.counter];
    }
}
