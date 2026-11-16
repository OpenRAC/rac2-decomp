#include "names.h"
/* func_PAL_L20_00449C78, the PAL copy of func_L20_004441D8: the same C, where the acceleration factor
 * 1/60 becomes 0.02, the two lifetimes c and d are scaled to 50 Hz and 60 becomes 50.
 * Built with -frac2-sticky-volatile-refs: qzero_nc's volatile asm keeps the delay-slot search of
 * the func_002A7878 call in the i loop from taking the loop increment.
 * func_002A8F70 is declared with the definition's own types (src/game/002A7750-records.c) and its
 * float argument fourth: the bank-preserving typed interleaving AGENTS.md permits (integer bank
 * a0-t0 and $f12 unchanged). With the float last both calls schedule the $f12 move into the jal slot;
 * computing the arguments into locals first changes nothing (v3767). */
#include "common.h"

#define F(p, o) (*(float *)((char *)(p) + (o)))
#define P(p, o) (*(char **)((char *)(p) + (o)))

extern unsigned short **g_yeedil_death_lists __attribute__((section(".sdata")));
extern unsigned short *g_group_l20_id_lists[] __attribute__((nosda));
extern char *g_part_info_table __attribute__((section(".sdata")));
extern char *g_group_l20_member_table __attribute__((section(".sdata")));
extern char *g_linked_moby_table __attribute__((section(".sdata")));
extern char *g_moby_l20_list_end __attribute__((section(".sdata")));
extern char *g_hero_moby __attribute__((nosda));
extern char g_effect_color_table[] __attribute__((section(".sdata")));
extern int g_group_count __attribute__((sda));
extern int g_yeedil_death_blast_count __attribute__((sda));
extern int g_yeedil_death_color_table[] MACRO_ADDR;
extern int D_L20_001B2210_gp SDATA(D_L20_001B2210);
extern float g_yeedil_death_scales[2] __attribute__((sda));
extern int g_yeedil_death_trail_param __attribute__((sda));
extern int g_yeedil_death_range_table[] MACRO_ADDR;
extern int D_L20_001B2230_gp SDATA(D_L20_001B2230);
extern float g_yeedil_death_accel_range[] MACRO_ADDR;
extern float D_L20_001B2240_gp[] SDATA(D_L20_001B2240);
extern int g_yeedil_death_trail_count __attribute__((sda));
extern float g_yeedil_death_accel_range_b[] MACRO_ADDR;
extern float D_L20_001B2250_gp SDATA(D_L20_001B2250);
extern float g_level_shared_float __attribute__((sda));

extern int PlayMobySound(int, int, void *);
extern void moby_mark_spawned(void *);
extern void vec_store_helper(void *);
extern void vec_clear_128(void *);
extern void transform_vector(void *, void *, void *);
extern float math_fabs(float);
extern float coll_probe_ground_height_below(void *, int, float);
extern float math_random_float_range(float, float);
extern float math_random_angle(void);
extern int math_random_int_below(int);
extern int math_random_int_range(int, int);
extern int FastTweenColor(int, int, float);
extern char *moby_get_private_value_0(void *);
extern void part_queue_impact_effect(char *object, int kind, int bits, float strength, void *position, void *vector);
extern char *part_spawn_trail(void *, void *, void *, int, int, int, int, int, int);
extern char *debris_l20_spawn_piece_pal(char *, char *, char *, char *);

typedef union {
    int q __attribute__((mode(TI)));
    float f[4];
} Vector;

typedef struct {
    char pad0[0x21C];
    int damage_group_0; /* 0x21C */
    char pad220[4];
    int groups[3]; /* 0x224 */
    int matrix_index; /* 0x230 */
    char pad234[8];
    int damage_group_1; /* 0x23C */
    char pad240[0x1618];
    int group_index; /* 0x1858 */
} State;

/* Runs the big enemy death. It stops its sounds, removes nearby leftovers, damages everything in its two groups and bursts out sparks and debris. (PAL: 50 Hz timings) */
void yeedil_boss_explode_death_pal(char *self) {
    State *s = (State *)P(self, 0x68);
    char *self_pos;
    char *obj;
    float height;
    float scale;
    Vector pos;
    Vector vel;
    Vector acc;
    int color_start;
    int color_end;
    int lifetime_a;
    int lifetime_b;
    float sample;

    PlayMobySound(17, 0, self);
    {
        unsigned short *list = g_yeedil_death_lists[s->groups[s->group_index]];

        if (list != 0) {
            do {
                char *info = g_part_info_table + ((*list & 0x7FFF) << 5);

                if (info == 0) {
                    break;
                }
                info[0x1E] |= 4;
                list++;
                if (list == 0) {
                    break;
                }
            } while (*(short *)(list - 1) >= 0 || list == g_yeedil_death_lists[s->groups[s->group_index]]);
        }
    }
    s->group_index++;
    self_pos = self + 0x10;
    obj = g_group_l20_member_table;
    if (obj <= g_moby_l20_list_end && (unsigned char)obj[0x20] != 255) {
        char *bound;

        for (;;) {
            unsigned short type = *(unsigned short *)(obj + 0xAA);

            if ((unsigned short)(type - 0x1233) < 2) {
                goto hit;
            }
            if ((short)type == 0x1231) {
                goto hit;
            }
            if ((short)type == 0x1232) {
                goto hit;
            }
            if ((short)type != 0x1357) {
                bound = g_moby_l20_list_end;
                goto next_object;
            }
        hit:
            if (!(math_fabs(F(self, 0x18) - F(obj, 0x18)) < 10.0f)) {
                bound = g_moby_l20_list_end;
                goto next_object;
            }
            moby_mark_spawned(obj);
            bound = g_moby_l20_list_end;
        next_object:
            obj += 256;
            if (bound < obj) {
                goto objects_done;
            }
            if ((unsigned char)obj[0x20] != 255) {
                continue;
            }
            goto objects_done;
        }
    }
objects_done:
    {
        unsigned short *list;
        float damage = 0.0f;

        for (list = g_group_l20_id_lists[s->damage_group_0];
             (s->damage_group_0 & 0xFF) != 0xFF && s->damage_group_0 <= g_group_count && list != 0 &&
             ((list != 0 && (short)list[-1] >= 0) || list == g_group_l20_id_lists[s->damage_group_0]);
             list++) {
            char *member = g_group_l20_member_table + ((*list & 0x7FFF) << 8);

            if (member == 0) {
                break;
            }
            if ((*(unsigned short *)(member + 0x34) ^ 1) & 1) {
                if (damage == 0.0f) {
                    char *info = moby_get_private_value_0(member);

                    if (info == 0) {
                        continue;
                    }
                    damage = (float)*(short *)(info + 4) * 0.25f;
                }
                part_queue_impact_effect(member, (int)g_hero_moby, 0x10000, damage, member + 0x10, g_effect_color_table);
            }
        }
    }
    {
        unsigned short *list;
        float damage = 0.0f;

        for (list = g_group_l20_id_lists[s->damage_group_1];
             (s->damage_group_1 & 0xFF) != 0xFF && s->damage_group_1 <= g_group_count && list != 0 &&
             ((list != 0 && (short)list[-1] >= 0) || list == g_group_l20_id_lists[s->damage_group_1]);
             list++) {
            char *member = g_group_l20_member_table + ((*list & 0x7FFF) << 8);

            if (member == 0) {
                break;
            }
            if ((*(unsigned short *)(member + 0x34) ^ 1) & 1) {
                if (damage == 0.0f) {
                    char *info = moby_get_private_value_0(member);

                    if (info == 0) {
                        continue;
                    }
                    damage = (float)*(short *)(info + 4) * 0.25f;
                }
                part_queue_impact_effect(member, (int)g_hero_moby, 0x10000, damage, member + 0x10, g_effect_color_table);
            }
        }
    }
    sample = coll_probe_ground_height_below(self_pos, 0, 0.5f) - 2.0f;
    height = F(self, 0x18) - 0.5f;
    g_level_shared_float = sample;
    {
        int i;

        for (i = 0; i < g_yeedil_death_blast_count; i++) {
            vec_store_helper(&pos);
            pos.f[0] = math_random_float_range(-1.0f, 1.0f);
            pos.f[1] = math_random_float_range(-1.0f, 1.0f);
            transform_vector(&pos, &pos, g_linked_moby_table + s->matrix_index * 128);
            pos.f[2] = height + math_random_float_range(-0.5f, 0.5f);
            sample = math_random_float_range(0.0f, 1.0f);
            color_start = FastTweenColor(D_L20_001B2210_gp, g_yeedil_death_color_table[1], sample);
            sample = math_random_float_range(0.0f, 1.0f);
            color_end = FastTweenColor(g_yeedil_death_color_table[2], g_yeedil_death_color_table[3], sample);
            scale = g_yeedil_death_scales[math_random_int_below(2)];
            vec_clear_128(&vel);
            vel.f[3] = scale;
            vec_clear_128(&acc);
            acc.f[3] = scale;
            acc.f[2] = math_random_float_range(D_L20_001B2240_gp[0], g_yeedil_death_accel_range[1]) * 0.020000001f;
            lifetime_a = (math_random_int_range(1, D_L20_001B2230_gp) * 5 + 2) / 6;
            lifetime_b = (math_random_int_range(g_yeedil_death_range_table[1], g_yeedil_death_range_table[2]) * 5 + 2) / 6;
            part_spawn_trail(&pos, &vel, &acc, color_start, color_end, lifetime_a, lifetime_b, 50, g_yeedil_death_trail_param);
        }
    }
    {
        int i;

        for (i = 0; i < g_yeedil_death_trail_count; i++) {
            vec_store_helper(&pos);
            pos.f[0] = math_random_float_range(-1.0f, 1.0f);
            pos.f[1] = math_random_float_range(-1.0f, 1.0f);
            transform_vector(&pos, &pos, g_linked_moby_table + s->matrix_index * 128);
            pos.f[2] = height + math_random_float_range(-0.5f, 0.5f);
            qzero_nc(&vel);
            vel.f[2] = math_random_angle();
            qzero_nc(&acc);
            acc.f[2] = math_random_float_range(D_L20_001B2240_gp[4], g_yeedil_death_accel_range_b[1]) * 0.020000001f;
            debris_l20_spawn_piece_pal(self, (char *)&pos, (char *)&vel, (char *)&acc);
        }
    }
}
