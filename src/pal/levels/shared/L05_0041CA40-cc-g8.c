#include "names.h"
/* func_PAL_L05_0041CA40, the PAL copy of func_L05_00417D48: the same C. */
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
void func_PAL_L05_0041CA40(Obj_L05_00417D48 *o)
{
    State_L05_00417D48 *st = o->pVar;
    int mode = o->state;
    int id;
    unsigned int flags;

    switch (mode) {
    case 0:
        st->f30 = -1;
        st->f270 = -1;
        st->f260 = 1;
        st->f264 = 0x2ee0;
        st->f0 = 0;
        st->f4 = 0;
        st->f8 = 0;
        st->fA = 0;
        st->f20C = 0;
        st->f210 = 0;
        st->f14 = 0;
        st->f18 = 0;
        st->f1C = 0;
        st->f34 = 0;
        st->f38 = 0;
        st->f3C = 0;
        st->f268 = 0;
        st->f26C = 0;
        st->f27C = 0;
        o->state = 1;
        o->modeBits |= 0x100;
        func_L05_00418200(o);
        vec_clear_128(g_light_spot_sum);
        D_0018B650[0] = o;
        flags = g_equipment_bits & 3;
        g_light_spot_count = 0;
        o->modeBits |= 0x41;
        st->f40 = equipment_spawn_part_moby(o, 0.05f, 0, D_L05_001A8F70[flags]);
        if (st->f40) *(int *)(st->f40 + 0x98) = 0;
        flags = (g_equipment_bits >> 2) & 3;
        id = D_L05_001A8F78[flags];
        st->f44 = equipment_spawn_part_moby(o, 0.05f, 0, id);
        st->f48 = equipment_spawn_part_moby(o, 0.05f, 1, id);
        if (st->f44) *(int *)(st->f44 + 0x98) = 0;
        if (st->f48) *(int *)(st->f48 + 0x98) = 0;
        flags = (g_equipment_bits >> 4) & 3;
        st->f4C = equipment_spawn_part_moby(o, 0.05f, 0, D_L05_001A8F80[flags]);
        if (st->f4C) *(int *)(st->f4C + 0x98) = 0;
        st->f50 = CreateTransformClone(o, 0.05f);
        flags = (g_equipment_bits >> 6) & 1;
        id = D_L05_001A8F88[flags];
        st->fAC = equipment_spawn_part_moby(o, 0.05f, 0, id);
        st->f1F0 = equipment_spawn_part_moby(o, 0.05f, 1, id);
        if (st->fAC) *(int *)(st->fAC + 0x98) = 0;
        if (st->f1F0) *(int *)(st->f1F0 + 0x98) = 0;
        flags = (g_equipment_bits >> 9) & 1;
        id = D_L05_001A8F98[flags];
        st->f1F4 = equipment_spawn_part_moby(o, 0.05f, 0, id);
        st->f1F8 = equipment_spawn_part_moby(o, 0.05f, 1, id);
        if (st->f1F4) *(int *)(st->f1F4 + 0x98) = 0;
        if (st->f1F8) *(int *)(st->f1F8 + 0x98) = 0;
        if (table_find_last_used_entry(3)) {
            flags = (g_equipment_bits >> 7) & 3;
            id = D_L05_001A8F90[flags];
            if (id) {
                st->f1FC = equipment_spawn_part_moby(o, 0.05f, 0, id);
                st->f200 = equipment_spawn_part_moby(o, 0.05f, 1, id);
                if (st->f1FC) *(int *)(st->f1FC + 0x98) = 0;
                if (st->f200) *(int *)(st->f200 + 0x98) = 0;
            }
        }
        flags = (g_equipment_bits >> 10) & 3;
        id = D_L05_001A8FA0[flags];
        st->f204 = equipment_spawn_part_moby(o, 0.05f, 0, id);
        st->f208 = equipment_spawn_part_moby(o, 0.05f, 1, id);
        if (st->f204) *(int *)(st->f204 + 0x98) = 0;
        if (st->f208) *(int *)(st->f208 + 0x98) = 0;
        if (table_find_last_used_entry(4) != -1) {
            st->f274 = equipment_spawn_part_moby(o, 0.05f, 0, 0x10E2);
            if (st->f274) *(int *)(st->f274 + 0x98) = 0;
        }
        if (table_find_last_used_entry(5) != -1) {
            st->f278 = equipment_spawn_part_moby(o, 0.05f, 0, 0x10E4);
            if (st->f278) *(int *)(st->f278 + 0x98) = 0;
        }
        st->f58 = 70;
        st->f54 = 60;
        st->f5C = 0;
        st->fA0 = 0;
        break;
    case 1:
        if (hero_get_shield_value() < hero_get_shield_limit()) st->f260 = mode;
        if (st->f260) {
            if (math_fast_float_d((char *)&st->f264)) st->f268 = mode;
        }
        if (!snd_is_voice_playing_for_owner(o, st->f30)) st->f30 = PlayMobySound(0, 4, o);
        wobbling_light_update(o);
        qcopy(D_L05_001B3510, o->pos);
        load_forward_resident_address(o);
        break;
    }
}
