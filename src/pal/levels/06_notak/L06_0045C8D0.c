#include "include_asm.h"



#include "common.h"
extern void FastVecAdd(char *, char *, char *);
extern int FloatToInt(float);
extern void set_moby_color(char *, int, int, int);
extern void vec_scale_to_length(char *, char *, float);
extern int g_machine_hit_counter __attribute__((sda));
extern int g_machine_hit_flag __attribute__((sda));
extern void moby_fade_out_update_pal();
extern void object_start_tumble(char *);
extern int FloatToInt(float);

void object_start_tumble_pal(char *a0)
{
    char *s2 = *(char **)(a0 + 0x68);
    int v;

    FastVecAdd(a0 + 0x10, a0 + 0x10, s2);
    v = FloatToInt((float)g_machine_hit_counter * 1.5f);
    set_moby_color(a0, v, FloatToInt((float)g_machine_hit_counter * 1.25f), g_machine_hit_counter);
    if (g_machine_hit_flag != 0) {
        vec_scale_to_length(s2, s2, 0.14000002f);
        *(float *)(s2 + 0x8) = *(float *)(s2 + 0x8) + 0.22000001f;
        *(unsigned int *)(a0 + 0x64) = (unsigned int)moby_fade_out_update_pal;
        *(float *)(a0 + 0x2C) = *(float *)(a0 + 0x2C) * 0.75f;
        set_moby_color(a0, 0x10, 0x10, 0x10);
    }
}


extern void moby_set_state(char *, int, int);
extern void *part_find_owned_effect_slot(char *, int, int);
extern int PlayMobySound(int, int, char *);
extern void part_spawn_scaled_bolts_pal(char *, int, float);
extern void moby_mark_spawned(char *);
extern void FastVecScale(char *, char *, float);
extern void part_spawn_debris_mask_pal(char *, int, void *, int, float, float, float, float);

void breakable_l06_object_update_pal(unsigned char *a0)
{
    char *o = *(char **)(a0 + 0x68);

    switch (a0[0x20]) {
    case 0:
        *(unsigned short *)(a0 + 0x34) |= 0x800;
        moby_set_state((char *)a0, 1, -1);
        break;
    case 1:
        if (part_find_owned_effect_slot((char *)a0, 0x4010000, 0) != 0) {
            if (*(int *)o == 0) {
                moby_set_state((char *)a0, 2, -1);
            }
        }
        a0[0xA8] = 0xFF;
        break;
    case 2: {
        char tmp[16];

        FastVecScale(tmp, (char *)(a0 + 0xD0), -0.040000003f);
        part_spawn_debris_mask_pal((char *)a0, 7, tmp, 0xFF, 3.0f, 6.0f, 3.0f, 6.0f);
        PlayMobySound(0, 0, (char *)a0);
        part_spawn_scaled_bolts_pal((char *)a0, 1, 0.0f);
        moby_mark_spawned((char *)a0);
        break;
    }
    }
}



void breakable_object_alt_update_pal(unsigned char *a0)
{
    char *o = *(char **)(a0 + 0x68);

    switch (a0[0x20]) {
    case 0:
        *(unsigned short *)(a0 + 0x34) |= 0x800;
        moby_set_state((char *)a0, 1, -1);
        break;
    case 1:
        if (part_find_owned_effect_slot((char *)a0, 0x4010000, 0) != 0) {
            if (*(int *)o == 0) {
                moby_set_state((char *)a0, 2, -1);
            }
        }
        a0[0xA8] = 0xFF;
        break;
    case 2: {
        char tmp[16];

        FastVecScale(tmp, (char *)(a0 + 0xD0), -0.040000003f);
        part_spawn_debris_mask_pal((char *)a0, 7, tmp, 0xFF, 3.0f, 6.0f, 3.0f, 6.0f);
        PlayMobySound(0, 0, (char *)a0);
        part_spawn_scaled_bolts_pal((char *)a0, 1, 0.0f);
        moby_mark_spawned((char *)a0);
        break;
    }
    }
}


extern short *g_group_l06_id_lists[];
extern char *g_moby_l06_table[] __attribute__((sda));
extern float math_random_angle(void);
extern void part_emit_spark_burst_remove_pal(char *);
extern void func_PAL_002A7E68(char *, int, int, int);

void wake_actors_trigger_update_pal(unsigned char *obj)
{
    char *data;
    char *hit;
    short *list, *cursor;
    char *target;
    char *state;
    if (obj[0x20] == 0) {
        *(unsigned short *)(obj + 0x34) |= 0x800;
        obj[0x20] = 1;
    }
    data = *(char **)(obj + 0x68);
    hit = (char *)part_find_owned_effect_slot((char *)obj, 0x10000, 0);
    if (hit && *(short *)(*(char **)(hit + 0x20) + 0xAA) != 0xFE5) {
        if (*(int *)data == 255) { part_emit_spark_burst_remove_pal((char *)obj); return; }
        {
            list = g_group_l06_id_lists[*(int *)data];
            if (list == 0) { part_emit_spark_burst_remove_pal((char *)obj); return; }
            {
                cursor = list;
                do {
                    target = g_moby_l06_table[0] + ((*cursor & 0x7FFF) << 8);
                    if (*(signed char *)(target + 0x20) >= 0 && *(short *)(target + 0xAA) == 0xBBA) {
                        state = *(char **)(target + 0x68);
                        if (*(float *)(state + 0x20) > 0.0f) {
                            *(float *)(state + 0x5A4) = math_random_angle();
                            qcopy(state + 0x5B0, state + 0x460);
                            *(short *)(state + 0x24C) = 0xE1;
                            target[0x20] = 4;
                            func_PAL_002A7E68(target, 6, 0, 8);
                            *(int *)(state + 0x5A0) = 0;
                            *(short *)(state + 0x492) = 0;
                            target[0x20] = 5;
                            target[0x95] = 1;
                        }
                    }
                } while (*cursor++ >= 0);
            }
        }
        if (*(int *)(data + 4) == 255) goto destroy;
        list = g_group_l06_id_lists[*(int *)(data + 4)];
        if (list == 0) {
 destroy:
            part_emit_spark_burst_remove_pal((char *)obj); return;
        }
        {
            cursor = list;
            do {
                target = g_moby_l06_table[0] + ((*cursor & 0x7FFF) << 8);
                if (*(signed char *)(target + 0x20) >= 0 && *(short *)(target + 0xAA) == 0xBBA) {
                    state = *(char **)(target + 0x68);
                    *(float *)(state + 0x5A4) = math_random_angle();
                    qcopy(state + 0x5B0, state + 0x460);
                    *(short *)(state + 0x24C) = 0xE1;
                    target[0x20] = 4;
                    func_PAL_002A7E68(target, 6, 0, 8);
                    target[0x20] = 5;
                    target[0x95] = 1;
                }
            } while (*cursor++ >= 0);
        }
        part_emit_spark_burst_remove_pal((char *)obj);
    }
    obj[0xA8] = 255;
}


