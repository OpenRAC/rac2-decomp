#include "include_asm.h"

#include "common.h"
#define W(p, o) (*(int *)((char *)(p) + (o)))
#define H(p, o) (*(short *)((char *)(p) + (o)))
#define UH(p, o) (*(unsigned short *)((char *)(p) + (o)))
#define B(p, o) (*(u8 *)((char *)(p) + (o)))
#define F(p, o) (*(float *)((char *)(p) + (o)))
typedef int PrisonQword __attribute__((mode(TI)));
typedef struct {
    char pad0[0x28 - 0x0];
    unsigned char b28;
    char pad29[0x30 - 0x29];
    float f30;
    char pad34[0x48 - 0x34];
    unsigned char b48;
    char pad49[0x4A - 0x49];
    unsigned char b4A;
    char pad4B[0x50 - 0x4B];
    char area50[0x10];
    unsigned char b60;
    char pad61[0x80 - 0x61];
    float f80;
    float f84;
    char pad88[0x8C - 0x88];
    float f8C;
    float f90;
    char pad94[0x98 - 0x94];
    int i98;
    char pad9C[0x100 - 0x9C];
    float f100;
    float f104;
    float f108;
    float f10C;
    float f110;
    char pad114[0x130 - 0x114];
    float f130;
    float f134;
    int i138;
    int i13C;
    char pad140[0x1D0 - 0x140];
    float f1D0;
    float f1D4;
    int i1D8;
    float f1DC;
    char pad1E0[0x1E2 - 0x1E0];
    short h1E2;
    short h1E4;
    char pad1E6[0x1E8 - 0x1E6];
    unsigned char b1E8;
    unsigned char b1E9;
    char pad1EA[0x210 - 0x1EA];
    int i210;
    int i214;
    int i218;
    char pad21C[0x2E0 - 0x21C];
    PrisonQword v2E0;
    char pad2F0[0x300 - 0x2F0];
    char area300[0x10];
    char pad310[0x314 - 0x310];
    short h314;
    char pad316[0x324 - 0x316];
    float f324;
    float f328;
    char pad32C[0x338 - 0x32C];
    short h338;
} PrisonGuardVars;
extern float coll_get_ground_distance_below(void *position, void *owner, void *output);
extern float fast_vec_dist(void *, void *);
extern void moby_mark_spawned(void *);
extern float math_random_float_range(float, float);
extern int FloatToInt(float);
extern float math_random_signed_float_range(float, float);
extern float math_random_angle(void);
extern void moby_set_state(void *, int, int);
extern void anim_start_blended_pal(void *, int, int, int);
extern void moby_update_ground_check(void *);
extern int moby_apply_damage_to_object_pal(char *object, char *state, int special);
extern void group_marker_alert_guards(unsigned char *);
extern int weapon_select_aim_target(char *self, int index, void *point, int force, float range, float height);
extern void cam_compute_view_direction(char *a0, char *a1, int a2);
extern int g_current_map_index[] __attribute__((sda));
extern int g_aim_l14_blocked_flag;
extern float g_guard_frame_scale __attribute__((sda));
extern char *g_guard_entry_tables[] __attribute__((sda));
extern char g_guard_reference_point[] __attribute__((sda));
extern char g_tether_l14_origin_vec[];

/* Shared guard logic: sets up its stats on the first frame, then checks for the player getting close, damage and the path to the player. (PAL) */
void guard_update_common_pal(char *moby)
{
    PrisonGuardVars *vars = *(PrisonGuardVars **)(moby + 0x68);
    int hit;

    if (B(moby, 0x20) == 0) {
        if (g_current_map_index[0] == 2 && F(moby, 0x18) > 400.0f) {
            if (g_aim_l14_blocked_flag == 0)
                return;
            coll_get_ground_distance_below(moby + 0x10, moby, moby + 0x10);
            vars->h338 = 1;
            W(moby, 0x9C) = 3;
            UH(moby, 0x34) |= 0x100;
            vars->f90 = fast_vec_dist(moby + 0x10, g_guard_reference_point) - 1.5f;
        } else {
            W(moby, 0x9C) = 12;
            vars->f90 = F(moby, 0x18) - 1.0f;
        }
        if (vars->i210 == -1) {
            moby_mark_spawned(moby);
            return;
        }
        {
            char *entry = g_guard_entry_tables[0] + vars->i210 * 0x30;
            if (H(entry, 0x30) != 0) {
                vars->i13C = vars->i218 = **(int **)(entry + 0x3C);
            } else {
                vars->i218 = -1;
            }
        }
        vars->f324 = math_random_float_range(1.0f, 1.333f);
        F(moby, 0x2C) = F(*(char **)(moby + 0x24), 0x24) * vars->f324;
        vars->b48 = FloatToInt(15.0f);
        vars->b4A = FloatToInt(6.4f);
        vars->i98 = 3;
        vars->f80 = 0.2f;
        vars->f84 = 0.2f;
        vars->f8C = 0.4f;
        vars->f108 = 0.4f;
        vars->f134 = 0.05f;
        vars->b60 = 11;
        vars->b28 = 3;
        vars->f30 = 0.333f;
        vars->f104 = vars->f324 * 0.2f;
        vars->f100 = vars->f324 * 0.3f;
        vars->f10C = 0.4f;
        vars->f110 = 1.5707964897155762f;
        vars->f130 = 0.523598849773407f;
        vars->i138 |= 0x280;
        vars->f1DC = math_random_signed_float_range(18.0f, 22.0f) * 0.01745329424738884f;
        vars->b1E8 = 7;
        vars->b1E9 = 6;
        vars->h1E2 = 100;
        vars->h1E4 = 150;
        vars->f1D4 = 3.0f;
        vars->f1D0 = g_guard_frame_scale * 0.020000001f;
        vars->f328 = math_random_angle();
        if (vars->i214 != 0) {
            UH(moby, 0x34) = (UH(moby, 0x34) | 0x41) & ~0x1000;
            W(moby, 0x98) = 0;
            moby_set_state(moby, 13, 4);
            if (B(moby, 0x43) != 10)
                anim_start_blended_pal(moby, 10, 0, 0);
        } else {
            moby_set_state(moby, 1, 0);
            if (B(moby, 0x43) != 0)
                anim_start_blended_pal(moby, 0, 0, 0);
        }
        vars->v2E0 = *(PrisonQword *)(moby + 0x10);
    }

    if (B(moby, 0x31) != 0) {
        if (fast_vec_dist(moby + 0x10, g_tether_l14_origin_vec) < 24.0f) {
            moby_update_ground_check(moby);
            B(moby, 0x6F) = 22;
        }
    }
    hit = moby_apply_damage_to_object_pal(moby, vars->area50, 0);
    if (hit != 0) {
        group_marker_alert_guards((unsigned char *)moby);
        if (hit >= 4)
            moby_set_state(moby, 12, -1);
    }
    if (B(moby, 0x20) != 12 && vars->i1D8 == 1)
        moby_set_state(moby, 12, -1);
    if ((u8)(B(moby, 0x95) - 3) >= 2)
        vars->h314 = weapon_select_aim_target(moby, vars->i210, 0, 0, 16.0f, 0.0f);
    if (vars->h338 != 0)
        cam_compute_view_direction(moby + 0x10, vars->area300, 0);
}
