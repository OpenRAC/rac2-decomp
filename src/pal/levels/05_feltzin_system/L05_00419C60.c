#include "include_asm.h"
#include "names.h"


extern void vec_clear_128(char *block);
extern int math_random_int_below(int kind);
extern char *moby_get_motion_data(char *object);
extern void *state_get_stored_pointer_value(char *object);
extern void level_append_object(char *object, int a1, int a2, int a3);
extern void func_PAL_L05_0037E8E0(char *object);
extern int moby_process_collision_hit(char *object, int a1, int a2, int a3);
extern void moby_check_player_in_view_and_range(char *object, int a1, float a2);
extern int moby_can_take_next_step(char *object);
extern void func_PAL_L05_0037DE20(char *object);
extern int math_fast_float_d(char *block);
extern char *D_L05_001B251C __attribute__((sda));
extern char g_sound_state[];
extern int snd_play_from_class_bank(int, int, char *, int);
typedef struct {
    char pad0[0x104];
    int x104, x108, pad10C, mode, pad114, pad118;
    int has_target;
    char *target;
} Target05;
extern float fast_vec_dist(char *a, char *b);
extern void func_PAL_L05_0041A480(char *obj);
extern void func_PAL_L05_0041A580(char *object);
extern void func_PAL_L05_0041A628(char *obj);

/* Per-frame update. On the first frame it initializes the object; afterwards it points the record
   at moby state+0x260, renews the D_00188660 slot in state+0x270 near that target at random and the
   one in state+0x26C when the object no longer owns it. */
void func_PAL_L05_0041A270(char *object)
{
    char *state = *(char **)(object + 0x68);
    Target05 *r;
    char *rec, *rec2;
    char buf[0x10];

    if (*(unsigned char *)(object + 0x20) == 0) {
        *(unsigned char *)(object + 0x30) = 0xFF;
        if (state_get_stored_pointer_value(object) == 0)
            return;
        func_PAL_L05_0041A480(object);
        vec_clear_128(buf);
        if (*(int *)(state + 0x264) != 0)
            level_append_object(object, 0, 0, 0);
        return;
    }
    r = (Target05 *)moby_get_motion_data(object);
    if (r->mode == 0)
        return;
    {
        int one = 1;

        func_PAL_L05_0037E8E0(object);
        moby_process_collision_hit(object, 0, 0, 0);
        moby_check_player_in_view_and_range(object, one, 32.0f);
        if (r->mode == one) {
            if (*(int *)(state + 0x260) != -1) {
                r->has_target = 1;
                r->target = D_L05_001B251C + *(int *)(state + 0x260) * 256;
                if (fast_vec_dist(r->target + 0x10, object + 0x10) < 10.0f) {
                    rec2 = g_sound_state + *(int *)(state + 0x270) * 0x70;
                    if (*(char **)(rec2 + 0x88) != object ||
                        *(unsigned char *)(rec2 + 0x74) == 0) {
                        if (math_random_int_below(0x190) == 0)
                            *(int *)(state + 0x270) =
                                snd_play_from_class_bank(0xE, 0, object, 0xFBF);
                    }
                }
            }
            if (r->x104 != 0)
                func_PAL_L05_0041A580(object);
            if (moby_can_take_next_step(object) != 0)
                func_PAL_L05_0037DE20(object);
            math_fast_float_d(state + 0x268);
            func_PAL_L05_0041A628(object);
        }
    }
    rec = g_sound_state + *(int *)(state + 0x26C) * 0x70;
    if (*(char **)(rec + 0x88) != object || *(unsigned char *)(rec + 0x74) == 0)
        *(int *)(state + 0x26C) = snd_play_from_class_bank(0, 6, object, 0xF73);
}


#include "common.h"
extern void func_306630(char *dst, char *src, char *src2);
extern float func_332B50(float a, float b);
extern float func_332C18(void);
extern void func_33B330(char *dst, float a, float b, float c);
extern char *func_379CA0(char *object);
extern void func_37AEC0(char *object, int flag);
extern int D_L05_00221D10[];
extern char *D_L05_001B2614 __attribute__((sda));

void func_PAL_L05_0041A480(char *obj)
{
    char *sub = *(char **)(obj + 0x68);
    char *table;
    float a, b, c;

    *(unsigned char *)(obj + 0x20) = 1;
    *(unsigned short *)(obj + 0x34) = *(unsigned short *)(obj + 0x34) | 0x100;
    *(int *)(func_379CA0(obj) + 0x148) = 0x14;
    func_37AEC0(obj, 1);
    table = D_L05_001B2614 + D_L05_00221D10[0] * 128;
    *(int *)(sub + 0x26C) = -1;
    *(int *)(sub + 0x270) = -1;
    *(float *)(sub + 0x180) = 20.0f;
    *(int *)(sub + 0x268) = 0;
    *(float *)(obj + 0x2C) = 0.02f;
    a = func_332B50(0.0f, *(float *)table);
    b = func_332C18();
    c = func_332C18();
    func_33B330(obj + 0x10, a, b, c);
    func_306630(obj + 0x10, table + 0x30, obj + 0x10);
}

extern void func_379FA0(char *object, int a1, int a2, int a3, float f0, float f1, float f2,
                        float f3, int a8, int a9, int a10);

/* Runs the object's pending effect when three guards clear, then marks the run. */
void func_PAL_L05_0041A580(char *object)
{
    char *s1 = *(char **)(object + 0x68);
    char *r;

    r = func_379CA0(object);
    if (r == 0)
        return;
    if (*(int *)(r + 0x120) == 0)
        return;
    if (*(int *)(s1 + 0x268) != 0)
        return;
    if (*(unsigned char *)(object + 0x20) == 1)
        func_379FA0(object, 0x60800000, 1, 0, 0.75f, 5.0f, 1.0f, 1.0f, 0, -1, 0);
    *(int *)(s1 + 0x268) = 0x11;
}


extern char *feltzin_helper_create(char *a0, int a1);
extern void gfx_add_draw_callback_third(void *fn, char *object);
extern void beam_clear_record_owners(void);
extern void func_PAL_L05_0041AA78(char *obj);
extern void func_PAL_L05_0041ABE8(char *object);
extern void func_PAL_L05_0041ACA0(char *object);
extern void func_PAL_L05_0041AE80(char *obj);
extern void heavy_lancer_update(void);
extern char D_L05_002659E0[];

/* func_L05_00415958 is defined in L05_00415958-qcopy.c. */

/* Per-frame update. On the first frame it initializes the object and, if state+0x264 is set,
   clears the owners of the 128 interpolation records; afterwards it creates the two
   func_L05_00416D68 children once, points the record at moby state+0x260, and renews the
   D_00188660 slot in state+0x274 when the object no longer owns it. */
void func_PAL_L05_0041A808(char *object)
{
    char *state = *(char **)(object + 0x68);
    Target05 *r;
    char *rec;
    char buf[0x10];

    if (*(unsigned char *)(object + 0x20) == 0) {
        *(unsigned char *)(object + 0x30) = 0xFF;
        if (state_get_stored_pointer_value(object) == 0)
            return;
        func_PAL_L05_0041AA78(object);
        vec_clear_128(buf);
        if (*(int *)(state + 0x264) != 0) {
            char *base;
            int *p;
            int i;

            level_append_object(object, (int)beam_clear_record_owners, 0, 0);
            base = D_L05_002659E0;
            p = (int *)(base + 0x27F0);
            i = 0x7F;
            do {
                *p = 0;
                p -= 0x14;
                i--;
            } while (i >= 0);
        }
        return;
    }
    r = (Target05 *)moby_get_motion_data(object);
    if (r->mode == 0)
        return;
    if (*(int *)(state + 0x26C) == 0 && *(int *)(state + 0x270) == 0) {
        *(int *)(state + 0x26C) = (int)feltzin_helper_create(object, 0);
        *(int *)(state + 0x270) = (int)feltzin_helper_create(object, 1);
        *(float *)(*(int *)(state + 0x26C) + 0x2C) = *(float *)(object + 0x2C);
        *(float *)(*(int *)(state + 0x270) + 0x2C) = *(float *)(object + 0x2C);
    }
    {
        int one = 1;

        func_PAL_L05_0037E8E0(object);
        moby_process_collision_hit(object, 0, 0, 0);
        moby_check_player_in_view_and_range(object, one, 32.0f);
        if (r->mode == one) {
            if (*(int *)(state + 0x260) != -1) {
                r->has_target = 1;
                r->target = D_L05_001B251C + *(int *)(state + 0x260) * 256;
            }
            if (r->x108 != 0 && r->x104 != 0)
                func_PAL_L05_0041ABE8(object);
            if (moby_can_take_next_step(object) != 0)
                func_PAL_L05_0037DE20(object);
            math_fast_float_d(state + 0x268);
            func_PAL_L05_0041ACA0(object);
        }
    }
    rec = g_sound_state + *(int *)(state + 0x274) * 0x70;
    if (*(char **)(rec + 0x88) != object || *(unsigned char *)(rec + 0x74) == 0)
        *(int *)(state + 0x274) = snd_play_from_class_bank(1, 6, object, 0xF76);
    func_PAL_L05_0041AE80(object);
    gfx_add_draw_callback_third(heavy_lancer_update, object);
}

