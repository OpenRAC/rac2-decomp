#include "names.h"
/* func_PAL_L05_0041CA40, the PAL copy of func_L05_00417D48: the same C. */
#include "common.h"

extern void func_L05_00418200(void *);
extern void vec_clear_128(char *);
extern unsigned int g_equipment_bits MACRO_ADDR;
/* A pointer table whose slot 0 holds the active object (L30_003B3F70-g8.c also reads it as an array). */
extern void *g_held_object_ptr[] __attribute__((nosda));
extern char g_light_spot_sum[] MACRO_ADDR;
extern char g_light_spot_position[] MACRO_ADDR;
extern float g_light_spot_count;
/* Model ids per equipment selector, one 4-entry table per D_001A7AF0 bit field. */
extern short g_equipment_part_class_a[] MACRO_ADDR;
extern short g_equipment_part_class_b[] MACRO_ADDR;
extern short g_equipment_part_class_c[] MACRO_ADDR;
extern short g_equipment_part_class_d[] MACRO_ADDR;
extern short g_equipment_part_class_e[] MACRO_ADDR;
extern short g_equipment_part_class_f[] MACRO_ADDR;
extern short g_equipment_part_class_g[] MACRO_ADDR;
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
    int unk_0;
    int unk_4;
    short unk_8;
    short unk_A;
    char padC[0x8];
    int unk_14;
    int unk_18;
    int unk_1C;
    char pad20[0x10];
    int unk_30;
    int unk_34;
    int unk_38;
    int unk_3C;
    char * unk_40;
    char * unk_44;
    char * unk_48;
    char * unk_4C;
    char * unk_50;
    int unk_54;
    int unk_58;
    int unk_5C;
    char pad60[0x40];
    int unk_A0;
    char padA4[0x8];
    char * unk_AC;
    char padB0[0x140];
    char * unk_1F0;
    char * unk_1F4;
    char * unk_1F8;
    char * unk_1FC;
    char * unk_200;
    char * unk_204;
    char * unk_208;
    int unk_20C;
    int unk_210;
    char pad214[0x4C];
    int unk_260;
    int unk_264;
    int unk_268;
    int unk_26C;
    int unk_270;
    char * unk_274;
    char * unk_278;
    int unk_27C;
} State_L05_00417D48;

typedef struct {
    char pad0[0x10];
    char pos[0x10];
    unsigned char state;
    char pad21[0x13];
    unsigned short mode_bits;
    char pad36[0x32];
    State_L05_00417D48 *vars;
} Obj_L05_00417D48;

/* State 0 spawns the equipment parts chosen by the D_001A7AF0 selector bits; state 1 updates timers and the
 * position copy. */
void equipment_holder_update_pal(Obj_L05_00417D48 *obj)
{
    State_L05_00417D48 *state = obj->vars;
    int mode = obj->state;
    int part_class;
    unsigned int selector;

    switch (mode) {
    case 0:
        state->unk_30 = -1;
        state->unk_270 = -1;
        state->unk_260 = 1;
        state->unk_264 = 0x2ee0;
        state->unk_0 = 0;
        state->unk_4 = 0;
        state->unk_8 = 0;
        state->unk_A = 0;
        state->unk_20C = 0;
        state->unk_210 = 0;
        state->unk_14 = 0;
        state->unk_18 = 0;
        state->unk_1C = 0;
        state->unk_34 = 0;
        state->unk_38 = 0;
        state->unk_3C = 0;
        state->unk_268 = 0;
        state->unk_26C = 0;
        state->unk_27C = 0;
        obj->state = 1;
        obj->mode_bits |= 0x100;
        func_L05_00418200(obj);
        vec_clear_128(g_light_spot_sum);
        g_held_object_ptr[0] = obj;
        selector = g_equipment_bits & 3;
        g_light_spot_count = 0;
        obj->mode_bits |= 0x41;
        state->unk_40 = equipment_spawn_part_moby(obj, 0.05f, 0, g_equipment_part_class_a[selector]);
        if (state->unk_40) *(int *)(state->unk_40 + 0x98) = 0;
        selector = (g_equipment_bits >> 2) & 3;
        part_class = g_equipment_part_class_b[selector];
        state->unk_44 = equipment_spawn_part_moby(obj, 0.05f, 0, part_class);
        state->unk_48 = equipment_spawn_part_moby(obj, 0.05f, 1, part_class);
        if (state->unk_44) *(int *)(state->unk_44 + 0x98) = 0;
        if (state->unk_48) *(int *)(state->unk_48 + 0x98) = 0;
        selector = (g_equipment_bits >> 4) & 3;
        state->unk_4C = equipment_spawn_part_moby(obj, 0.05f, 0, g_equipment_part_class_c[selector]);
        if (state->unk_4C) *(int *)(state->unk_4C + 0x98) = 0;
        state->unk_50 = CreateTransformClone(obj, 0.05f);
        selector = (g_equipment_bits >> 6) & 1;
        part_class = g_equipment_part_class_d[selector];
        state->unk_AC = equipment_spawn_part_moby(obj, 0.05f, 0, part_class);
        state->unk_1F0 = equipment_spawn_part_moby(obj, 0.05f, 1, part_class);
        if (state->unk_AC) *(int *)(state->unk_AC + 0x98) = 0;
        if (state->unk_1F0) *(int *)(state->unk_1F0 + 0x98) = 0;
        selector = (g_equipment_bits >> 9) & 1;
        part_class = g_equipment_part_class_f[selector];
        state->unk_1F4 = equipment_spawn_part_moby(obj, 0.05f, 0, part_class);
        state->unk_1F8 = equipment_spawn_part_moby(obj, 0.05f, 1, part_class);
        if (state->unk_1F4) *(int *)(state->unk_1F4 + 0x98) = 0;
        if (state->unk_1F8) *(int *)(state->unk_1F8 + 0x98) = 0;
        if (table_find_last_used_entry(3)) {
            selector = (g_equipment_bits >> 7) & 3;
            part_class = g_equipment_part_class_e[selector];
            if (part_class) {
                state->unk_1FC = equipment_spawn_part_moby(obj, 0.05f, 0, part_class);
                state->unk_200 = equipment_spawn_part_moby(obj, 0.05f, 1, part_class);
                if (state->unk_1FC) *(int *)(state->unk_1FC + 0x98) = 0;
                if (state->unk_200) *(int *)(state->unk_200 + 0x98) = 0;
            }
        }
        selector = (g_equipment_bits >> 10) & 3;
        part_class = g_equipment_part_class_g[selector];
        state->unk_204 = equipment_spawn_part_moby(obj, 0.05f, 0, part_class);
        state->unk_208 = equipment_spawn_part_moby(obj, 0.05f, 1, part_class);
        if (state->unk_204) *(int *)(state->unk_204 + 0x98) = 0;
        if (state->unk_208) *(int *)(state->unk_208 + 0x98) = 0;
        if (table_find_last_used_entry(4) != -1) {
            state->unk_274 = equipment_spawn_part_moby(obj, 0.05f, 0, 0x10E2);
            if (state->unk_274) *(int *)(state->unk_274 + 0x98) = 0;
        }
        if (table_find_last_used_entry(5) != -1) {
            state->unk_278 = equipment_spawn_part_moby(obj, 0.05f, 0, 0x10E4);
            if (state->unk_278) *(int *)(state->unk_278 + 0x98) = 0;
        }
        state->unk_58 = 70;
        state->unk_54 = 60;
        state->unk_5C = 0;
        state->unk_A0 = 0;
        break;
    case 1:
        if (hero_get_shield_value() < hero_get_shield_limit()) state->unk_260 = mode;
        if (state->unk_260) {
            if (math_fast_float_d((char *)&state->unk_264)) state->unk_268 = mode;
        }
        if (!snd_is_voice_playing_for_owner(obj, state->unk_30)) state->unk_30 = PlayMobySound(0, 4, obj);
        wobbling_light_update(obj);
        qcopy(g_light_spot_position, obj->pos);
        load_forward_resident_address(obj);
        break;
    }
}
