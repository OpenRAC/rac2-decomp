/* func_PAL_L05_00432530, the PAL copy of func_L05_0042C928: the same C, where 0.00029088825f
   becomes 0.0003490659f; func_L01_00397950 becomes func_PAL_L01_0039AD60. */
#include "include_asm.h"
#include "names.h"
#include "common.h"

typedef struct ListMoby_0042C928 {
    char pad0[0x28];
    struct ListMoby_0042C928 *next;
    char pad2C[0x7E];
    short oclass;
} ListMoby_0042C928;
extern u8 g_level_progress_flags[] MACRO_ADDR;
extern int D_001A79F0_1;
extern char *g_hero_moby NOT_SDA;
extern float g_collectible_spin_x __attribute__((sda));
extern float g_collectible_spin_y __attribute__((sda));
extern float g_collectible_spin_z __attribute__((sda));
extern ListMoby_0042C928 *g_pickup_first_moby __attribute__((sda));
extern ListMoby_0042C928 *g_moby_l05_list_head;
extern char *CreateMoby(s32 a0);
extern float math_random_angle(void);
extern void moby_init_randomized_vars_pal(char *a0);
extern void set_moby_color(char *a0, s32 a1, s32 a2, s32 a3);

/* Creates a collectible of class 0x126C at a position, unless that one has already been collected (PAL). */
char *pickup_spawn_if_not_taken_pal(float *pos, u32 kind, s32 a2, s32 a3)
{
    char *moby;
    char *vars;
    ListMoby_0042C928 *p;
    u8 *collected = g_level_progress_flags;

    if (kind >= 4 || collected[kind + (D_001A79F0_1 << 2)] != 0)
        return 0;
    moby = CreateMoby(0x126C);
    if (moby != 0) {
        float x, y, z, r;

        vars = *(char **)(moby + 0x68);
        *(long *)(moby + 0x38) = *(long *)(g_hero_moby + 0x38);
        qcopy(moby + 0x10, pos);
        *(s16 *)(moby + 0x32) = 0x40;
        *(u8 *)(moby + 0x30) = 0x40;
        *(u8 *)(moby + 0x31) = 1;
        *(u32 *)vars = kind;
        qcopy(vars + 0x10, moby + 0x10);
        *(float *)(vars + 0x1C) = *(float *)(moby + 0xF8);
        *(float *)(moby + 0xF0) = math_random_angle();
        *(float *)(moby + 0xF4) = math_random_angle();
        *(float *)(moby + 0xF8) = math_random_angle();
        r = math_random_angle();
        x = g_collectible_spin_x;
        y = g_collectible_spin_y;
        z = g_collectible_spin_z;
        *(float *)(moby + 0xFC) = r;
        *(s32 *)(vars + 8) = a3;
        *(s32 *)(vars + 4) = a2;
        x *= 0.0003490659f;
        y *= 0.0003490659f;
        z *= 0.0003490659f;
        *(float *)(vars + 0x60) = z;
        *(float *)(vars + 0x68) = x;
        *(float *)(vars + 0x64) = y;
        *(u8 *)(moby + 0x20) = 1;
        moby_init_randomized_vars_pal(moby);
        set_moby_color(moby, 0x82, 0x82, 0x82);
        if (g_pickup_first_moby == 0) {
            for (p = g_moby_l05_list_head; p != 0; p = p->next) {
                if (p->oclass == 0xFBF)
                    g_pickup_first_moby = p;
            }
        }
    }
    return moby;
}
