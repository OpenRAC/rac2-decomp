#include "common.h"

typedef struct {
    char pad0[24];
    float f18;
    char pad1c[4];
    unsigned char f20;
    char pad21[116];
    unsigned char f95;
    char pad96[38];
    unsigned char fbc;
} F003C01C0obj;

typedef struct {
    char pad0[32];
    float f20;
    short f24;
    char pad26[8];
    unsigned char f2e;
    char pad2f[105];
    unsigned short f98;
    char pad9a[598];
    int f2f0;
    unsigned char f2f4;
    char pad2f5[3];
    int f2f8;
    int f2fc;
} F003C01C0s;

extern int moby_apply_damage_to_object(void *, void *, int);
extern int ApplyObjectReaction(void *, void *, void *, int);
extern void weapon_select_aim_target(void *, int, int, int, float, float);
extern void FastVecSub(void *, void *, void *);
extern float IntToFloat(int);
extern void hud_start_overlay(int, int, float);
extern char *g_moby_l01_table __attribute__((sda));
extern char *D_L01_001B264C __attribute__((sda));
extern float D_L01_001AFEE0 __attribute__((sda));
extern float D_L01_001AFEE4 __attribute__((sda));
extern float D_L01_001AFEE8 __attribute__((sda));
extern char g_hero_position[];

/* Handles damage taken by the Swamp Monster II and moves its linked parts with it. */
void swamp_monster_update_hit_reaction(F003C01C0obj *moby)
{
    F003C01C0s *vars = *(F003C01C0s **)((char *)moby + 0x68);
    int oldState = moby->f20;

    if (moby_apply_damage_to_object(moby, (char *)vars + 0x60, 0) || vars->f2e == 2) {
        if (vars->f20 <= 0.0f || vars->f2e == 2) {
            vars->f20 = 0.0f;
            if (vars->f2e == 2 && !(vars->f98 & 1)) {
                int zero __attribute__((mode(TI)));

                /* The cleared local is consumed only by the following call. */
                qzero_nc(&zero);
                ApplyObjectReaction(moby, (char *)vars + 0x60, &zero, 4);
                vars->f2e = 3;
                moby->f95 = 6;
                moby->fbc = 99;
                moby->f20 = 99;
            }
            if (vars->f2f8 != -1) {
                g_moby_l01_table[vars->f2f8 * 256 + 0xbc] = 1;
                if (vars->f2fc != -1) {
                    int index = vars->f2fc;
                    char *base = D_L01_001B264C;

                    /* Copying position leaves the separate transform row intact. */
                    qcopy_nc((char *)moby + 0x10, base + index * 128 + 0x30);
                    qcopy((char *)moby + 0xf0, base + index * 128 + 0x70);
                }
            }
        }
    }
    if (moby->f20 == 255) {
        moby->f20 = oldState;
    }
    weapon_select_aim_target(moby, vars->f2f0, 0, 0, 0.0f, 0.0f);
    if (*(char **)((char *)vars + 0x2e4)) {
        FastVecSub(*(char **)((char *)vars + 0x2e4) + 0x20,
                     (char *)moby + 0x10, g_hero_position);
        (*(char **)((char *)vars + 0x2e4))[0x1f] = 1;
        *(float *)(*(char **)((char *)vars + 0x2e4) + 0x10) =
            D_L01_001AFEE0 * 0.017453294f;
        if (vars->f2f4 || (moby->f95 == 3 && moby->f20 == 2)) {
            *(float *)*(char **)((char *)vars + 0x2e4) = D_L01_001AFEE8;
            *(int *)(*(char **)((char *)vars + 0x2e4) + 0x34) = 6;
        } else {
            *(float *)*(char **)((char *)vars + 0x2e4) = D_L01_001AFEE4;
            *(int *)(*(char **)((char *)vars + 0x2e4) + 0x34) = 3;
        }
    }
    if (*(float *)(g_hero_position + 8) < moby->f18 + 20.0f &&
        (unsigned)(moby->f95 - 2) < 5) {
        hud_start_overlay(2, 0, vars->f20 / IntToFloat(vars->f24));
    }
}
