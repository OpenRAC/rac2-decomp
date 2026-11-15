#include "common.h"

extern void func_L05_00418200(void *);
extern void vec_clear_128(char *);
extern unsigned int g_equipment_bits MACRO_ADDR;
/* A pointer table whose slot 0 holds the active object (L30_003B3F70-g8.c also reads it as an array). */
extern void *D_0018B650[] __attribute__((nosda));
extern char g_light_spot_sum[] MACRO_ADDR;
extern char D_L05_001B3510[] MACRO_ADDR;
extern float g_light_spot_count;
/* Model ids per equipment selector, one 4-entry table per D_001A7AF0 bit field. */
extern short D_L05_001A8F70[] MACRO_ADDR;
extern short D_L05_001A8F78[] MACRO_ADDR;
extern short D_L05_001A8F80[] MACRO_ADDR;
extern short D_L05_001A8F88[] MACRO_ADDR;
extern short D_L05_001A8F90[] MACRO_ADDR;
extern short D_L05_001A8F98[] MACRO_ADDR;
extern short D_L05_001A8FA0[] MACRO_ADDR;
extern char *equipment_spawn_part_moby(void *, float, int, int);
extern char *CreateTransformClone(void *, float);
extern int table_find_last_used_entry(int);
extern int hero_get_shield_value(void);
extern int hero_get_shield_limit(void);
extern int math_fast_float_d(char *);
extern int snd_is_voice_playing_for_owner(void *, int);
extern int PlayMobySound(int, int, void *);
extern void wobbling_light_update(void *);
extern void load_forward_resident_address(void *);

typedef struct {
    int f0;
    int f4;
    short f8;
    short fA;
    char padC[0x8];
    int f14;
    int f18;
    int f1C;
    char pad20[0x10];
    int f30;
    int f34;
    int f38;
    int f3C;
    char * f40;
    char * f44;
    char * f48;
    char * f4C;
    char * f50;
    int f54;
    int f58;
    int f5C;
    char pad60[0x40];
    int fA0;
    char padA4[0x8];
    char * fAC;
    char padB0[0x140];
    char * f1F0;
    char * f1F4;
    char * f1F8;
    char * f1FC;
    char * f200;
    char * f204;
    char * f208;
    int f20C;
    int f210;
    char pad214[0x4C];
    int f260;
    int f264;
    int f268;
    int f26C;
    int f270;
    char * f274;
    char * f278;
    int f27C;
} State_L05_00417D48;

typedef struct {
    char pad0[0x10];
    char pos[0x10];
    unsigned char state;
    char pad21[0x13];
    unsigned short modeBits;
    char pad36[0x32];
    State_L05_00417D48 *pVar;
} Obj_L05_00417D48;

/* State 0 spawns the equipment parts chosen by the D_001A7AF0 selector bits; state 1 updates timers and the
 * position copy. */
/* Updates the equipment holder object (moby class 4031). On its first frame it creates the player's equipment parts; after that it keeps its sound, timers and light going. */
void equipment_holder_update(Obj_L05_00417D48 *object)
{
    State_L05_00417D48 *vars = object->pVar;
    int phase = object->state;
    int partClass;
    unsigned int selector;

    switch (phase) {
    case 0:
        vars->f30 = -1;
        vars->f270 = -1;
        vars->f260 = 1;
        vars->f264 = 0x3840;
        vars->f0 = 0;
        vars->f4 = 0;
        vars->f8 = 0;
        vars->fA = 0;
        vars->f20C = 0;
        vars->f210 = 0;
        vars->f14 = 0;
        vars->f18 = 0;
        vars->f1C = 0;
        vars->f34 = 0;
        vars->f38 = 0;
        vars->f3C = 0;
        vars->f268 = 0;
        vars->f26C = 0;
        vars->f27C = 0;
        object->state = 1;
        object->modeBits |= 0x100;
        func_L05_00418200(object);
        vec_clear_128(g_light_spot_sum);
        D_0018B650[0] = object;
        selector = g_equipment_bits & 3;
        g_light_spot_count = 0;
        object->modeBits |= 0x41;
        vars->f40 = equipment_spawn_part_moby(object, 0.05f, 0, D_L05_001A8F70[selector]);
        if (vars->f40) *(int *)(vars->f40 + 0x98) = 0;
        selector = (g_equipment_bits >> 2) & 3;
        partClass = D_L05_001A8F78[selector];
        vars->f44 = equipment_spawn_part_moby(object, 0.05f, 0, partClass);
        vars->f48 = equipment_spawn_part_moby(object, 0.05f, 1, partClass);
        if (vars->f44) *(int *)(vars->f44 + 0x98) = 0;
        if (vars->f48) *(int *)(vars->f48 + 0x98) = 0;
        selector = (g_equipment_bits >> 4) & 3;
        vars->f4C = equipment_spawn_part_moby(object, 0.05f, 0, D_L05_001A8F80[selector]);
        if (vars->f4C) *(int *)(vars->f4C + 0x98) = 0;
        vars->f50 = CreateTransformClone(object, 0.05f);
        selector = (g_equipment_bits >> 6) & 1;
        partClass = D_L05_001A8F88[selector];
        vars->fAC = equipment_spawn_part_moby(object, 0.05f, 0, partClass);
        vars->f1F0 = equipment_spawn_part_moby(object, 0.05f, 1, partClass);
        if (vars->fAC) *(int *)(vars->fAC + 0x98) = 0;
        if (vars->f1F0) *(int *)(vars->f1F0 + 0x98) = 0;
        selector = (g_equipment_bits >> 9) & 1;
        partClass = D_L05_001A8F98[selector];
        vars->f1F4 = equipment_spawn_part_moby(object, 0.05f, 0, partClass);
        vars->f1F8 = equipment_spawn_part_moby(object, 0.05f, 1, partClass);
        if (vars->f1F4) *(int *)(vars->f1F4 + 0x98) = 0;
        if (vars->f1F8) *(int *)(vars->f1F8 + 0x98) = 0;
        if (table_find_last_used_entry(3)) {
            selector = (g_equipment_bits >> 7) & 3;
            partClass = D_L05_001A8F90[selector];
            if (partClass) {
                vars->f1FC = equipment_spawn_part_moby(object, 0.05f, 0, partClass);
                vars->f200 = equipment_spawn_part_moby(object, 0.05f, 1, partClass);
                if (vars->f1FC) *(int *)(vars->f1FC + 0x98) = 0;
                if (vars->f200) *(int *)(vars->f200 + 0x98) = 0;
            }
        }
        selector = (g_equipment_bits >> 10) & 3;
        partClass = D_L05_001A8FA0[selector];
        vars->f204 = equipment_spawn_part_moby(object, 0.05f, 0, partClass);
        vars->f208 = equipment_spawn_part_moby(object, 0.05f, 1, partClass);
        if (vars->f204) *(int *)(vars->f204 + 0x98) = 0;
        if (vars->f208) *(int *)(vars->f208 + 0x98) = 0;
        if (table_find_last_used_entry(4) != -1) {
            vars->f274 = equipment_spawn_part_moby(object, 0.05f, 0, 0x10E2 /* moby class 4322 */);
            if (vars->f274) *(int *)(vars->f274 + 0x98) = 0;
        }
        if (table_find_last_used_entry(5) != -1) {
            vars->f278 = equipment_spawn_part_moby(object, 0.05f, 0, 0x10E4 /* moby class 4324 */);
            if (vars->f278) *(int *)(vars->f278 + 0x98) = 0;
        }
        vars->f58 = 70;
        vars->f54 = 60;
        vars->f5C = 0;
        vars->fA0 = 0;
        break;
    case 1:
        if (hero_get_shield_value() < hero_get_shield_limit()) vars->f260 = phase;
        if (vars->f260) {
            if (math_fast_float_d((char *)&vars->f264)) vars->f268 = phase;
        }
        if (!snd_is_voice_playing_for_owner(object, vars->f30)) vars->f30 = PlayMobySound(0, 4, object);
        wobbling_light_update(object);
        qcopy(D_L05_001B3510, object->pos);
        load_forward_resident_address(object);
        break;
    }
}
