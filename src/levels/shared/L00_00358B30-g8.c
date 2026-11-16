#include "common.h"

typedef int Quadword __attribute__((mode(TI)));
typedef struct {
    unsigned char pad00[0x80];
    Quadword position;
    Quadword rotation;
    unsigned char padA0[0x21F0];
    unsigned char *moby;
    unsigned char pad2294[0x32];
    unsigned char state;
} Hero;
extern Hero g_hero_state;
typedef struct {
    unsigned char pad00[0x64];
    int field64;
    unsigned char field68, field69, field6A, field6B;
} GameState;
extern GameState g_sound_state;
extern unsigned short g_current_music_id[];
typedef struct {
    int active, reserved04[3];
    Quadword position, rotation;
    int field30, field34, field38;
    unsigned char field3C, field3D, field3E, field3F, field40, field41;
    unsigned char reserved42[2];
    float field44, field48, field4C, field50;
    int field54, field58, field5C;
    unsigned char reserved60[0xC04];
    unsigned short fieldC64, reservedC66;
    int fieldC68, reservedC6C;
} SavedState;
extern SavedState g_controller_level_state;
extern unsigned char g_level_work_area[0xC70];
extern int g_tutorial_points[];
extern unsigned char g_fog_color_r[] __attribute__((sda));
extern unsigned char g_fog_color_g[] __attribute__((sda));
extern unsigned char g_fog_color_b[] __attribute__((sda));
extern float g_fog_near[] __attribute__((sda));
extern float g_fog_far[] __attribute__((sda));
extern float g_fog_near_intensity[] __attribute__((sda));
extern float g_fog_far_intensity;
extern unsigned char *g_moby_array_base[] __attribute__((sda));
extern unsigned char *g_moby_array_end_sentinel[] __attribute__((sda));
extern void mem_clear(void *, int, unsigned int);
extern void mem_copy_aligned(void *, const void *, unsigned int);
extern void load_scene_chunk(int, int);
extern void math_trap_always(void);
extern void SetHeroMode(int, int, void *);
extern void func_002A0F48(void *);
extern void euler_rotation_basis(void *, const void *);
extern void cam_reset_default(void);
extern void level_apply_data_blocks(void);

/* Puts Ratchet back to the saved position, view and settings when a level is reloaded. */
void RestoreSavedHeroState(void) {
    unsigned char *entity;
    int kind;
    int i;
    g_hero_state.state = 15;
    if (g_controller_level_state.active == 0) {
        mem_clear(g_level_work_area, 0, 0xC70);
        return;
    }
    mem_copy_aligned(g_level_work_area, &g_controller_level_state, 0xC70);
    qcopy(&g_hero_state.position, &g_controller_level_state.position);
    qcopy(&g_hero_state.rotation, &g_controller_level_state.rotation);
    *(int *)(g_hero_state.moby + 0x38) = g_controller_level_state.field30;
    *(int *)(g_hero_state.moby + 0x3C) = g_controller_level_state.field34;
    g_sound_state.field64 = g_controller_level_state.field38;
    g_sound_state.field68 = g_controller_level_state.field3C;
    g_sound_state.field69 = g_controller_level_state.field3D;
    g_sound_state.field6A = g_controller_level_state.field3E;
    g_sound_state.field6B |= 7;
    g_current_music_id[0] = g_controller_level_state.fieldC64;
    if (g_tutorial_points[0] != g_controller_level_state.fieldC68)
        load_scene_chunk(g_controller_level_state.fieldC68, *(int *)&g_controller_level_state.fieldC64);
    g_fog_color_r[0] = g_controller_level_state.field3F;
    g_fog_color_g[0] = g_controller_level_state.field40;
    g_fog_color_b[0] = g_controller_level_state.field41;
    g_fog_near[0] = g_controller_level_state.field44;
    g_fog_far[0] = g_controller_level_state.field48;
    g_fog_near_intensity[0] = g_controller_level_state.field4C;
    g_fog_far_intensity = g_controller_level_state.field50;
    if (g_controller_level_state.field54 != 0 && g_controller_level_state.field54 != 3) {
        kind = 0;
        switch (g_controller_level_state.field54) {
        case 1:
            kind = 0x57; /* Clank */
            break;
        case 2:
            kind = 0x1A3;
            break;
        default:
            math_trap_always();
        }
        for (i = 0; (entity = g_moby_array_base[0] + (i << 8)) < g_moby_array_end_sentinel[0]; i++) {
            if (*(short *)(entity + 0xAA) == kind) {
                SetHeroMode(g_controller_level_state.field54, g_controller_level_state.field5C, entity);
                break;
            }
        }
    }
done:
    func_002A0F48(g_hero_state.moby);
    euler_rotation_basis(g_hero_state.moby + 0xC0, &g_hero_state.rotation);
    cam_reset_default();
    level_apply_data_blocks();
}
