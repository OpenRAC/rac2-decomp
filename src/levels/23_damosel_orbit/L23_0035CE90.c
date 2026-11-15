#include "include_asm.h"
#include "common.h"

typedef int TI16 __attribute__((mode(TI)));

extern int func_419CA0(int);

extern char g_hero_position[];

extern const int D_L23_001B1684 __attribute__((sda));

extern int *D_L23_001B36A8 __attribute__((sda));

extern int *g_path_lists[];

extern void FastVecSub(void *, void *, void *);

extern void vec_scale_to_length(void *, void *, float);

extern float fast_vec_dist(void *, void *);

extern void path_push_piece_history(char *arg0, int arg1);

extern void func_3242D0(int, int, int);

extern void moby_stop_effects(char *arg0);

extern int D_L23_001B36B0 __attribute__((sda));


/* func_L23_00394218 is defined in L23_00394218.c. */

typedef unsigned int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vec;
typedef struct { char pad[0x18]; char *hit; int count; Vec point; char gap[0x10]; Vec normal; } Collision;
typedef struct { char pad[0x70]; float material; char tail[0x6C]; } Material;

extern unsigned char D_00139574;

extern char *g_hero_moby;

extern int D_L23_001AC790 __attribute__((sda));

extern Collision g_last_ray_hit;

extern Material D_L23_00266A70[];

extern int CollLine(void *, void *, int, void *, void *);

extern int math_fast_float_d(char *);

extern void FastVecAdd(char *, char *, char *);

extern void FastVecScale(void *, void *, float);

extern void vec_scale_to_length(void *, void *, float);

extern void vec_fast_normalize_helper(void *, void *, float);

extern void vec_fast_normalize(void *, void *, void *);

extern void cam_compute_view_direction(void *, void *, int);

extern void table_clear_entry_flag(int);

extern void part_spawn_big_explosion(void *, void *, void *);

extern void part_l00_spawn_impact_burst(void *, void *, void *);

extern void part_spawn_spark_puff(void *);


/* Moves a thrown shell one step, checks what it hits, and on impact makes it bounce or burst. */
void shell_update_thrown(char *obj) {
    struct {
        Vec velocity, normal, old, surface;
        struct {
            Vec vector;
            char *moby;
            int flags;
            unsigned char kind, active;
            unsigned short class_id;
            float material;
            int enabled;
        } packet;
    } frame;
    char *ctx = *(char **)(obj + 0x68);
    char *position = obj + 0x10;
    char *hit;
    Collision *collision;

    frame.velocity.q = 0;
    frame.velocity.f[2] = 0.033333335f;
    frame.normal.q = 0;
    frame.normal.f[2] = 1.0f;
    qcopy(&frame.old, position);
    FastVecAdd(position, position, ctx);
    cam_compute_view_direction(position, &frame.surface, 0);
    FastVecScale(&frame.surface, &frame.surface, 0.0003055556f);
    part_spawn_spark_puff(obj);
    frame.packet.moby = obj;
    frame.packet.flags = 0x830000;
    if (*(int *)(ctx + 0x18) < 0x122)
        frame.packet.flags = 0x830001;
    frame.packet.enabled = 1;
    frame.packet.material = (D_00139574 + D_L23_00266A70)->material;
    qcopy(&frame.packet.vector, ctx);
    vec_fast_normalize_helper(&frame.packet.vector, &frame.packet.vector, 1.0f);
    frame.packet.kind = 2;
    frame.packet.vector.f[3] = 5627.925f;
    frame.packet.class_id = *(unsigned short *)(obj + 0xAA);
    frame.packet.vector.f[2] = 1.0f;
    frame.packet.active = 1;
    (*(int *)(ctx + 0x14))++;
    if (CollLine(&frame.old, position, 0x10, obj, &frame.packet)) {
        collision = &g_last_ray_hit;
        hit = collision->hit;
        if (hit) {
            Collision *reread;
            char *model;
            if ((hit == g_hero_moby || *(short *)(hit + 0xAA) == MOBY_CLASS_BOMB_GLOVE) && *(int *)(ctx + 0x18) >= 0x122)
                goto finish;
            reread = &g_last_ray_hit;
            model = reread->hit;
            if (*(int *)(model + 0x64) == D_L23_001AC790 && *(short *)(model + 0xAA) != 0x336 /* moby class 822 */)
                goto finish;
            obj[0xBC] = 1;
            {
                void *source = &reread->point;
                void *dest = obj + 0x10;
                qcopy(dest, source);
            }
            vec_fast_normalize(&frame.velocity, ctx, &reread->normal);
            vec_scale_to_length(&frame.velocity, &frame.velocity, 0.033333335f);
            vec_scale_to_length(&frame.normal, &reread->normal, 1.0f);
        } else {
            collision = &g_last_ray_hit;
            if (collision->count <= 0)
                goto finish;
            obj[0xBC] = 1;
            qcopy(position, &collision->point);
            vec_fast_normalize(&frame.velocity, ctx, &collision->normal);
            vec_scale_to_length(&frame.velocity, &frame.velocity, 0.033333335f);
            vec_scale_to_length(&frame.normal, &collision->normal, 1.0f);
        }
    } else if (math_fast_float_d(ctx + 0x18)) {
        obj[0xBC] = 1;
        FastVecAdd((char *)&frame.velocity, (char *)&frame.velocity, ctx);
    }
finish:
    if (*(unsigned char *)(obj + 0xBC)) {
        table_clear_entry_flag(*(int *)(ctx + 0x1C));
        if (*(int *)(ctx + 0x14) < 20)
            part_spawn_big_explosion(obj, &frame.velocity, &frame.normal);
        else
            part_l00_spawn_impact_burst(obj, &frame.velocity, &frame.normal);
    }
}




/* func_L23_003BDA20 is defined in L23_003BDA20-g8.c ($gp, -ffast-math). */

/* func_L23_003BEA00 is defined in L23_003BEA00-g8.c ($gp). */

/* func_L23_003BF9B0 is defined in L23_003BF9B0-g8.c ($gp, and -g for its division padding). */

extern void func_2F7DD0(char *);

extern void func_2F7E00(char *);

/* Updates two timers of an object and counts its frame age up (stopping at the limit). */
void moby_tick_timers(char *moby) {
    char *state = *(char **)(moby + 0x68);

    func_2F7DD0(state + 0x250);
    func_2F7E00(state + 0x254);
    if (*(unsigned short *)(moby + 0x96) <= 0xFFFE)
        *(unsigned short *)(moby + 0x96) += 1;
}

/* func_L23_003BFE90 is matched in L23_003BFE90.c (built with -frac2-zero-ti-barrier). */

extern void func_323FF0(char *, int, int, int);

/* Plays an animation on an object and/or on the object it is linked to, chosen by the bits of a flag. */
void moby_play_anim_and_link(char *moby, int anim_id, int arg2, int arg3, int target_bits, float arg5) {
    char *state = *(char **)(moby + 0x68);

    if (target_bits & 1)
        func_323FF0(moby, anim_id, 0, 4);
    if (target_bits & 2)
        func_323FF0(*(char **)(state + 0x2A0), anim_id, 0, 4);
}

extern void func_367150(int);

/* Puts an object back to its idle look: clears its links and effects and starts the idle animation. */
void moby_reset_idle_clear_links(char *moby) {
    char *state = *(char **)(moby + 0x68);
    int none = -1;

    moby_stop_effects(moby);
    *(short *)(state + 0x178) = 0;
    *(unsigned short *)(*(char **)(state + 0x2A0) + 0x34) |= 0x41;
    *(unsigned short *)(*(char **)(state + 0x2A0) + 0x34) &= 0xEFFF;
    *(int *)(*(char **)(state + 0x2A0) + 0x98) = 0;
    *(int *)(moby + 0x98) = 0;
    *(unsigned short *)(moby + 0x34) = (*(unsigned short *)(moby + 0x34) | 0x41) & 0xEFFF;
    func_3242D0(moby, 0xD, 4);
    *(int *)(state + 0x25C) = 0;
    if (*(int *)(state + 0x3B4) != none) {
        func_367150(*(int *)(state + 0x3B4));
        *(int *)(state + 0x3B4) = none;
    }
}

/* func_L23_003C00D0 is matched in L23_003C00D0.c (built with -g). */

/* func_L23_003C01F8 is matched in L23_003C01F8.c (built with -frac2-qcopy -frac2-qcopy-barrier). */

/* func_L23_003C02C8 is defined in L23_003C02C8-g8.c ($gp). */

/* func_L23_003C0A60 is defined in L23_003C0A60-g8.c ($gp). */

/* picks the nearest entry of the objects the index table names, and stores its index */
void SelectNearestPathNode(char *arg0, int arg1) {
    struct {
        TI16 a;
        float b[4];
    } loc;
    char *src = arg0 + 0x10;
    char *state;
    float best;
    int i;

    state = *(char **)(arg0 + 0x68);
    qcopy(&loc.a, src);
    FastVecSub(loc.b, src, g_hero_position);
    best = 30000.0f;
    vec_scale_to_length(loc.b, loc.b, 4.0f);
    FastVecAdd((char *)&loc.a, (char *)&loc.a, (char *)loc.b);
    for (i = 0; i < D_L23_001B1684; i++) {
        int *obj;
        int k;

        if (arg1 != 0 && func_419CA0(i) == 0)
            continue;
        obj = g_path_lists[D_L23_001B36A8[i]];
        for (k = 0; k < *obj; k++) {
            float d = fast_vec_dist((char *)obj + 0x10 + k * 0x10, &loc.a);

            if (d < best) {
                best = d;
                path_push_piece_history(arg0, i);
                *(short *)(state + 0x2B6) = k;
            }
        }
    }
}

extern int func_419CA0(int);

/* Lists the numbers of all bits that are set in a 64-bit mask, optionally skipping the ones that are not allowed. Returns how many were found. */
int math_list_set_bit_indices(int arg0, unsigned long long mask, int *out_ids, int only_allowed) {
    int *dest = out_ids;
    int i = 0;
    int count = 0;

    while (i < 0x40) {
        if (mask & 1) {
            if (only_allowed == 0 || func_419CA0(i) != 0) {
                *dest = i;
                count++;
                dest++;
            }
        }
        i++;
        mask >>= 1;
    }
    return count;
}

extern int *D_L23_001B36A8 __attribute__((sda));

extern int *g_path_lists[];

extern char g_path_end_masks[];

extern int func_419070(long long v, char *arg);

/* Tells which end of a path piece the object is at. Returns 0 for the start, or the last point number for the other end. */
int path_get_piece_end(int arg0, int index, char *arg) {
    int piece_a;
    int piece_b;
    int last_point;

    piece_a = D_L23_001B36A8[index];
    if (func_419070(*(long long *)(g_path_end_masks + (piece_a << 4)), arg) != 0)
        return 0;
    piece_b = D_L23_001B36A8[index];
    last_point = *g_path_lists[piece_b] - 1;
    func_419070(*(long long *)(g_path_end_masks + (piece_b << 4) + 8), arg);
    return last_point;
}

/* Remembers a new path piece as the current one and pushes the three earlier ones down a short history list. */
void path_push_piece_history(char *moby, int new_piece) {
    char *state = *(char **)(moby + 0x68);
    short slot = *(short *)(state + 0x2BE);
    unsigned short old_piece = *(unsigned short *)(state + 0x2B4);
    int offset;
    int next_slot;

    next_slot = (slot + 1) % 3;
    offset = next_slot * 2;
    *(short *)(state + 0x2BE) = next_slot;
    *(short *)(state + offset + 0x2B8) = old_piece;
    *(short *)(state + 0x2B4) = new_piece;
}

extern const int D_L23_001B1688 __attribute__((sda));

extern int *D_L23_001B36A8 __attribute__((sda));

extern int *g_path_lists[];

extern char g_path_end_masks[];

extern char g_hero_position[];

extern int math_list_set_bit_indices(int arg0, unsigned long long v, int *arg2, int arg3);

extern int path_get_piece_end(int arg0, int index, char *arg);

extern void path_push_piece_history(char *arg0, int arg1);

extern int math_random_int_below(int);

extern int mothership_is_single_rejected_bit(long long);

extern float fast_vec_dist(void *, void *);

extern void FastVecSub(void *, void *, void *);

extern float FastVecDot(void *, void *);

/* Chooses the next path piece to travel to from a set of allowed ones, either at random or by nearest or farthest distance. */
void path_choose_next_piece(char *arg0, unsigned long long mask, int mode, int check)
{
    char *state = *(char **)(arg0 + 0x68);
    int count = D_L23_001B1688;
    int ids[count];
    int n;
    int id;
    float va[4];
    float vb[4];

    n = math_list_set_bit_indices((int)arg0, mask, ids, check);
    if (n == 0) {
        int d = *(short *)(state + 0x2B2);

        *(short *)(state + 0x2B2) = -d;
        return;
    }
    if (mode == 0) {
        int res;

        id = ids[math_random_int_below(n)];
        res = path_get_piece_end((int)arg0, id, (char *)(int)*(short *)(state + 0x2B4));
        *(short *)(state + 0x2B2) = res == 0 ? 1 : -1;
        *(short *)(state + 0x2B6) = res;
        path_push_piece_history(arg0, id);
        return;
    } else {
        char *pos[count];
        int res[count];
        long long *bits[count];
        int i;
        int best;

        for (i = 0; i < n; i++) {
            int *q;

            id = ids[i];
            res[i] = path_get_piece_end((int)arg0, id, (char *)(int)*(short *)(state + 0x2B4));
            q = g_path_lists[D_L23_001B36A8[id]];
            if (res[i] == 0) {
                pos[i] = (char *)(q + *q * 4);
                bits[i] = (long long *)(g_path_end_masks + 8 + (D_L23_001B36A8[id] << 4));
            } else {
                pos[i] = (char *)(q + 4);
                bits[i] = (long long *)(g_path_end_masks + (D_L23_001B36A8[id] << 4));
            }
        }
        best = 0;
        switch (mode) {
        case 1: {
            float bestDist = 30000.0f;
            int j;

            for (j = 0; j < n; j++) {
                int blocked = 0;
                float d;

                if (check)
                    blocked = mothership_is_single_rejected_bit(*bits[j]);
                d = fast_vec_dist(pos[j], *(void **)(state + 0x320));
                if ((d < bestDist && !blocked) || n == 1) {
                    best = j;
                    bestDist = d;
                }
            }
            break;
        }
        case 3: {
            float bestDot = -30000.0f;
            int j;

            for (j = 0; j < n; j++) {
                int blocked = 0;
                float d;

                if (check)
                    blocked = mothership_is_single_rejected_bit(*bits[j]);
                FastVecSub(va, g_hero_position, arg0 + 0x10);
                FastVecSub(vb, pos[j], arg0 + 0x10);
                d = FastVecDot(va, vb);
                if ((bestDot < d && !blocked) || n == 1) {
                    best = j;
                    bestDot = d;
                }
            }
            break;
        }
        case 2:
        default: {
            float bestDot = 30000.0f;
            int j;

            for (j = 0; j < n; j++) {
                int blocked = 0;
                float d;

                if (check)
                    blocked = mothership_is_single_rejected_bit(*bits[j]);
                FastVecSub(va, g_hero_position, arg0 + 0x10);
                FastVecSub(vb, pos[j], arg0 + 0x10);
                d = FastVecDot(va, vb);
                if ((d < bestDot && !blocked) || n == 1) {
                    best = j;
                    bestDot = d;
                }
            }
            break;
        }
        }
        if (res[best] == 0) {
            id = ids[best];
            *(short *)(state + 0x2B2) = 1;
        } else {
            id = ids[best];
            *(short *)(state + 0x2B2) = -1;
        }
        *(short *)(state + 0x2B6) = res[best];
        path_push_piece_history(arg0, id);
    }
}



/* Clears the selected-object flag and releases the object's two effects. */
void moby_clear_selected(char *moby) {
    D_L23_001B36B0 = 0;
    moby_stop_effects(moby);
}

extern void func_31A108(int);

/* Stops the two effects held by an object and empties their slots. */
void moby_stop_effects(char *moby) {
    int *effect_slot = (int *)(*(int *)(moby + 0x68) + 0x328);
    int i;

    for (i = 1; i >= 0; i--) {
        int effect = *effect_slot;

        if (effect != 0) {
            func_31A108(effect);
            *effect_slot = 0;
        }
        effect_slot++;
    }
}

/* func_L23_003C19E0 is defined in L23_0035CE90-g8.c (this unit has no $gp access for it). */

/* Starts an animation on an object and marks it as the selected object. */
void moby_select_play_anim(int moby) {
    func_3242D0(moby, 9, 2);
    D_L23_001B36B0 = moby;
}


/* func_L23_003C1B58 is matched in L23_003C1B58.c (built with -frac2-qcopy -frac2-qcopy-barrier). */

/* func_L23_003C1E88 is defined in L23_003C1E88-g8.c. */



/* func_L23_00415988 is in L23_0035CE90-f7-g8.c. */


/* Counts the frame age of an object up by one (stopping at the limit). */
void moby_increment_age(char *moby) {
    if (*(unsigned short *)(moby + 0x96) <= 0xFFFE)
        *(unsigned short *)(moby + 0x96) += 1;
}

/* func_L23_004160B0 is matched in L23_004160B0-g8.c (built with -g). */
