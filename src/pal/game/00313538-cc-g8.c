/* func_PAL_00313538, the PAL copy of func_003120C8: the same C, where rename func_002BC768 becomes func_PAL_002BD400; rename func_002B0A68 becomes func_PAL_002B15D8; rename func_0032C700 becomes func_PAL_0032DF28. */
#include "common.h"

typedef struct CrateMoby CrateMoby;

/* A crate's instance data. */
typedef struct {
    char pad00[0xA0];
    CrateMoby *above;           /* 0xA0: the crate stacked on this one */
    CrateMoby *below;           /* 0xA4: the crate this one stands on */
    char padA8[4];
    int flags;                  /* 0xAC */
    char padB0[0xCA - 0xB0];
    unsigned char burstFrame;   /* 0xCA */
    char padCB[0xF0 - 0xCB];
    void *attachment;           /* 0xF0: what the crate rides on, 0 for none */
} CrateVars;

struct CrateMoby {
    char pad00[0x10];
    float position[4];          /* 0x10 */
    unsigned char state;        /* 0x20 */
    char pad21[0x34 - 0x21];
    unsigned short flags;       /* 0x34 */
    char pad36[0x68 - 0x36];
    CrateVars *vars;            /* 0x68 */
    char pad6C[0x98 - 0x6C];
    int collision;              /* 0x98 */
    char pad9C[0xAA - 0x9C];
    short oClass;               /* 0xAA */
    char padAC[0xBC - 0xAC];
    unsigned char command;      /* 0xBC */
    char padBD[0xE0 - 0xBD];
    float up[4];                /* 0xE0 */
};

/* The hit message that destroyed the crate. */
typedef struct {
    char pad00[0x10];
    float position[4];          /* 0x10 */
} CrateHit;

extern int g_game_time;          /* the frame counter */
extern int g_death_time_a, g_death_time_b;
extern int g_hero_health_percent;
extern int g_nanotech_last_time __attribute__((sda)), g_nanotech_cooldown __attribute__((sda));
extern char *g_hero_moby NOT_SDA; /* the hero */
extern char *g_turret_target_moby;

extern int subtract_integer_with_clamp(int);
extern int snd_play_from_class_bank(int index, int value, char *object, int kind);
extern int PlayMobySound(int index, int a1, char *a2);
extern int moby_is_in_special_class_range(void *);
extern void math_trap_always(void);
extern char *part_spawn_flash_pal(char *pos, int spin, int color, float spread, float low, float high,
                           float accel, float size);
extern void FastVecSub(void *out, void *a, void *b);
extern float math_step_int_toward_target(int *, int, int);
extern int moby_transform_point_by_attachment(char *, char *, char *, char *);
extern void part_spawn_masked_debris_pal(char *self, int mask, float *arg2, float, float, float, float, unsigned char);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecAdd(void *out, void *a, void *b);
extern char *part_spawn_explosion_pal(void *position, int flash, int n0, int n1, int n2, int n3, int n4,
                           int orient, float size, float distance, int mode, int extra, int flags,
                           char *owner);

/* Destroys a crate: sounds, unlinks it from its stack, spawns debris and the bolts it drops. */
void DestroyCrate_pal(CrateMoby *self, int explode, CrateHit *hit)
{
    float position[4], direction[4], velocity[4];
    CrateVars *vars = self->vars;
    CrateMoby *crate;
    int i, amount, kind;

    if (subtract_integer_with_clamp(g_game_time - g_death_time_a) >= 2) {
        switch (self->oClass) {
        case 0x1FA: snd_play_from_class_bank(0, 0, (char *)self, MOBY_CLASS_CRATE); break;
        case MOBY_CLASS_AMMO_CRATE: snd_play_from_class_bank(1, 0, (char *)self, MOBY_CLASS_AMMO_CRATE); break;
        default: PlayMobySound(0, 0, (char *)self); break;
        }
        g_death_time_a = g_game_time;
    }
    if (subtract_integer_with_clamp(g_game_time - g_death_time_b) >= 2)
        g_death_time_b = g_game_time;
    if (vars->above) {
        vars->above->vars->below = vars->below;
        vars->above->vars->flags |= 0x24;
    }
    if (vars->below) {
        if (!moby_is_in_special_class_range(vars->below->vars->above))
            math_trap_always();
        vars->below->vars->above = vars->above;
        vars->below->vars->flags |= 0x24;
    }
    crate = self;
    do {
        CrateVars *crate_vars = crate->vars;
        crate_vars->flags |= 0x20;
        crate = crate_vars->above;
    } while (crate);
    qcopy(position, self->position);
    position[2] += 0.3f;
    part_spawn_flash_pal((char *)position, 1, 0x40808080, 0.3f, 1.01f, 1.075f, 0.05f, 50000.0f);
    i = 4;
    do {
        part_spawn_flash_pal((char *)position, 1, 0x40808080, 0.3f, 1.01f, 1.07f, 0.05f, 50000.0f);
        --i;
    } while (i >= 0);
    if (hit)
        qcopy(direction, hit->position);
    else
        FastVecSub(direction, self->position, g_hero_moby + 0x10);
    if (subtract_integer_with_clamp(g_game_time - g_nanotech_last_time) >= 201) {
        g_nanotech_cooldown = 0;
        g_nanotech_last_time = g_game_time;
    } else if (g_game_time != g_nanotech_last_time) {
        math_step_int_toward_target(&g_nanotech_cooldown, 0, subtract_integer_with_clamp(g_game_time - g_nanotech_last_time) >> 2);
        g_nanotech_last_time = g_game_time;
    }
    if (g_hero_health_percent >= 251 && g_nanotech_cooldown < 5)
        amount = 4;
    else if (g_hero_health_percent >= 201 && g_nanotech_cooldown < 10)
        amount = 3;
    else if (g_hero_health_percent >= 151 && g_nanotech_cooldown < 15)
        amount = 2;
    else
        amount = g_hero_health_percent >= 101 && g_nanotech_cooldown < 20;
    if (amount) {
        int type;
        kind = 0;
        type = self->oClass;
        g_nanotech_cooldown += amount;
        switch (type) {
        case MOBY_CLASS_CRATE: case MOBY_CLASS_AMMO_CRATE:
            switch (amount) {
            case 1: kind = 1; break;
            case 2: kind = 5; break;
            case 3: default: kind = 37; break;
            }
            break;
        case MOBY_CLASS_NANOTECH_CRATE: case MOBY_CLASS_PURPLE_NANOTECH_CRATE:
            kind = (1 << (amount - 1)) - 1;
            if (kind > 15)
                kind = 15;
            break;
        }
        if (kind) {
            qzero_nc(velocity);
            if (vars->attachment && !g_turret_target_moby)
                moby_transform_point_by_attachment((char *)self, vars->attachment, (char *)self->position, (char *)velocity);
            part_spawn_masked_debris_pal((char *)self, kind, velocity, 3.0f, 6.0f, 3.0f, 6.0f, 255);
        }
    }
    self->state = 3;
    self->flags |= 1;
    self->command = 12;
    self->collision = 0;
    if (explode) {
        vars->burstFrame = 1;
        vec_scale_to_length(velocity, self->up, 0.5f);
        FastVecAdd(velocity, velocity, self->position);
        part_spawn_explosion_pal(velocity, 0, 10, 10, 10, 10, 15, 0, 1.0f, 0.0f, 0, 0, 0, 0);
    }
}
