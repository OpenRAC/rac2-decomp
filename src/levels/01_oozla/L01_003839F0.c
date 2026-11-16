#include "common.h"

extern unsigned char g_bouncing_weapon_index;
extern void FastVecScale(void *, void *, float);
extern void cam_compute_view_direction(void *, void *, int);
extern void part_l00_spawn_impact_burst(void *, void *, void *);
extern void part_spawn_spark_puff(void *);

typedef unsigned int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vec;
typedef struct { char pad[0x18]; char *hit; int count; Vec point; char gap[0x10]; Vec normal; } Collision;
typedef struct { char pad[0x70]; float material; char tail[0x6C]; } Material;
extern char *g_hero_moby NOT_SDA;
/* sda: one `lw` macro instruction at -G0, scheduled as a single load as in retail. */
extern int g_debris_l01_model_id __attribute__((sda));
extern Collision g_collision_l01_hit;
extern Material g_action_table[];
extern void vec_fast_normalize_helper(void *, void *, float);
extern int CollLine(void *, void *, int, void *, void *);
extern void vec_fast_normalize(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern int math_fast_float_d(char *);
extern void table_clear_entry_flag(int);
extern void part_spawn_big_explosion(void *, void *, void *);

extern void FastVecAdd(char *, char *, char *);

/* Moves a bouncing piece of debris through the air. It bounces off surfaces and counts its bounces, then breaks up in a bigger way after 20. */
void bouncing_l01_debris_update(char *object) {
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
    char *vars = *(char **)(object + 0x68);
    char *position = object + 0x10;
    char *hit;
    Collision *collision;

    frame.velocity.q = 0;
    frame.velocity.f[2] = 0.033333335f;
    frame.normal.q = 0;
    frame.normal.f[2] = 1.0f;
    qcopy(&frame.old, position);
    FastVecAdd(position, position, vars);
    cam_compute_view_direction(position, &frame.surface, 0);
    FastVecScale(&frame.surface, &frame.surface, 0.0003055556f);
    part_spawn_spark_puff(object);
    frame.packet.moby = object;
    frame.packet.flags = 0x830000;
    if (*(int *)(vars + 0x18) < 0x122)
        frame.packet.flags = 0x830001;
    frame.packet.enabled = 1;
    frame.packet.material = (g_bouncing_weapon_index + g_action_table)->material;
    qcopy(&frame.packet.vector, vars);
    vec_fast_normalize_helper(&frame.packet.vector, &frame.packet.vector, 1.0f);
    frame.packet.kind = 2;
    frame.packet.vector.f[3] = 5627.925f;
    frame.packet.class_id = *(unsigned short *)(object + 0xAA);
    frame.packet.vector.f[2] = 1.0f;
    frame.packet.active = 1;
    (*(int *)(vars + 0x14))++;
    if (CollLine(&frame.old, position, 0x10, object, &frame.packet)) {
        collision = &g_collision_l01_hit;
        hit = collision->hit;
        if (hit) {
            Collision *reread;
            char *model;
            if ((hit == g_hero_moby || *(short *)(hit + 0xAA) == MOBY_CLASS_BOMB_GLOVE) && *(int *)(vars + 0x18) >= 0x122)
                goto finish;
            reread = &g_collision_l01_hit;
            model = reread->hit;
            if (*(int *)(model + 0x64) == g_debris_l01_model_id && *(short *)(model + 0xAA) != 0x336 /* moby class 822 */)
                goto finish;
            object[0xBC] = 1;
            {
                void *source = &reread->point;
                void *dest = object + 0x10;
                qcopy(dest, source);
            }
            vec_fast_normalize(&frame.velocity, vars, &reread->normal);
            vec_scale_to_length(&frame.velocity, &frame.velocity, 0.033333335f);
            vec_scale_to_length(&frame.normal, &reread->normal, 1.0f);
        } else {
            collision = &g_collision_l01_hit;
            if (collision->count <= 0)
                goto finish;
            object[0xBC] = 1;
            qcopy(position, &collision->point);
            vec_fast_normalize(&frame.velocity, vars, &collision->normal);
            vec_scale_to_length(&frame.velocity, &frame.velocity, 0.033333335f);
            vec_scale_to_length(&frame.normal, &collision->normal, 1.0f);
        }
    } else if (math_fast_float_d(vars + 0x18)) {
        object[0xBC] = 1;
        FastVecAdd((char *)&frame.velocity, (char *)&frame.velocity, vars);
    }
finish:
    if (*(unsigned char *)(object + 0xBC)) {
        table_clear_entry_flag(*(int *)(vars + 0x1C));
        if (*(int *)(vars + 0x14) < 20)
            part_spawn_big_explosion(object, &frame.velocity, &frame.normal);
        else
            part_l00_spawn_impact_burst(object, &frame.velocity, &frame.normal);
    }
}
