#include "common.h"

typedef struct Moby Moby;

/* A path of D_L17_001FE880. */
typedef struct {
    int count;                  /* 0x00 */
    u8 pad04[0x10 - 0x04];
    float start[3];             /* 0x10 */
    float length;               /* 0x1C */
    float end[4];               /* 0x20 */
} HazardPath;

/* The instance data of the path-linked hazard. */
typedef struct {
    int path;                   /* 0x00: index into the path table, or -1 */
    int next;                   /* 0x04: uid-table index of the next link in the chain, or -1 */
    float chainSpan;            /* 0x08 */
    float chainTime;            /* 0x0C */
    float x10;                  /* 0x10 */
    int x14;                    /* 0x14 */
    int x18;                    /* 0x18 */
    Moby *parent;               /* 0x1C */
    float x20;                  /* 0x20 */
    float x24;                  /* 0x24 */
    float x28;                  /* 0x28 */
    int sound;                  /* 0x2C */
    int timer;                  /* 0x30 */
    int isLinked;               /* 0x34 */
} HazardVars;

struct Moby {
    u8 pad0[0x10];
    float position[3];          /* 0x10 */
    float updateDist;           /* 0x1C */
    u8 state;                   /* 0x20 */
    u8 pad21[0x30 - 0x21];
    u8 x30;                     /* 0x30 */
    u8 pad31;
    u16 x32;                    /* 0x32 */
    u8 pad34[0x68 - 0x34];
    HazardVars *vars;           /* 0x68 */
    u8 pad6C[0x78 - 0x6C];
    int color;                  /* 0x78 */
    u8 pad7C[0xA8 - 0x7C];
    u8 impactSlot;              /* 0xA8 */
    u8 padA9;
    s16 oClass;                 /* 0xAA */
    u8 padAC[0xB2 - 0xAC];
    s16 uid;                    /* 0xB2 */
    u8 padB4[0xF0 - 0xB4];
    float rotation[4];          /* 0xF0 */
};


typedef struct {
    u8 bytes[0x70];
} SoundRecord;

typedef struct {
    u8 pad0[0x74];
    u8 active;                  /* 0x74 */
    u8 pad75[0x88 - 0x75];
    Moby *owner;                /* 0x88 */
} SoundVoice;

extern HazardPath *g_path_l17_table[];
extern Moby *g_moby_l17_pool;
extern Moby *D_L17_001B2C1C_1[] __attribute__((sda));
extern int D_L17_001B2748 MACRO_ADDR;
extern float D_L17_001AFCD0 __attribute__((sda)), D_L17_001AFCD4 __attribute__((sda));
extern float D_L17_001AFCD8 __attribute__((sda)), D_L17_001AFCDC __attribute__((sda));
extern float D_L17_001AFCE0 __attribute__((sda)), D_L17_001AFCE4 __attribute__((sda));
extern float D_L17_001AFCE8 __attribute__((sda)), D_L17_001AFCEC __attribute__((sda));
extern int D_L17_001AFCF0 __attribute__((sda));
extern char g_hero_position[];
extern SoundRecord g_sound_state[];
extern char D_L17_001A8F20[] MACRO_ADDR;
extern char D_L17_001AFCF8[], D_L17_001AFD28[];

extern float vec_distance_xy(void *, void *);
extern float fast_vec_dist(void *, void *);
extern float IntToFloat(int);
extern float math_random_float_range(float, float);
extern int PlayMobySound(int, int, void *);
extern void snd_stop_voice(int);
extern void STUB_printf(const char *, ...);
extern void moby_set_state(void *, int, int);
extern int PlacePathFollowerChainAtStart(void *);
extern int UpdatePathFollowerChain(void *);
extern void *part_find_owned_effect_slot(void *, int, int);
extern int flag_set_first_pending(void *);
extern int math_fast_float_d(int *);
extern char *SpawnExplosion(void *, float, int, int, int, int, int, int, int, int,
                          int, int, int, float);
extern void part_spawn_masked_debris(void *, int, void *, float, float, float, float, int);
extern Moby *cam_moby_create(void *, int, int, int, void *, void *, void *, int, float, float);
extern void part_spawn_scaled_bolts(void *, int, float);
extern void moby_mark_spawned(void *);

/* Updates a path-linked hazard, its movement sound and its destruction effects. */
void UpdatePathHazard(Moby *moby)
{
    HazardVars *vars = moby->vars;
    int flash;
    int color;

    vars->x20 = moby->oClass == 0x8AD ? D_L17_001AFCD4 : D_L17_001AFCE4;
    vars->x24 = moby->oClass == 0x8AD ? D_L17_001AFCD0 : D_L17_001AFCE0;
    vars->x28 = moby->oClass == 0x8AD ? D_L17_001AFCD8 : D_L17_001AFCE8;
    vars->x10 = moby->oClass == 0x8AD ? D_L17_001AFCDC : D_L17_001AFCEC;

    flash = (D_L17_001B2748 + moby->uid) % 60 < 15;
    color = flash ? 0x80FFFFFF : 0x80404040;
    moby->color = color;

    if (moby->oClass == 0x8D8 || moby->oClass == 0x8AD) {
        if (moby->state == 2 && vec_distance_xy(moby->position, g_hero_position) < 80.0f) {
            SoundVoice *voice = (SoundVoice *)&g_sound_state[vars->sound];
            if (voice->owner != moby || !voice->active)
                vars->sound = PlayMobySound(0, 4, moby);
        } else {
            int sound = vars->sound;
            if (sound != -1) {
                SoundVoice *voice = (SoundVoice *)&g_sound_state[sound];
                if (voice->owner == moby && voice->active)
                    snd_stop_voice(sound);
            }
            vars->sound = -1;
        }
    }

    switch (moby->state) {
    case 0:
        vars->sound = -1;
        vars->isLinked = 0;
        if (vars->path == -1 || g_path_l17_table[vars->path]->count < 2) {
            STUB_printf(D_L17_001AFCF8, moby->oClass, moby->uid);
            STUB_printf(D_L17_001AFD28);
            moby_mark_spawned(moby);
            break;
        }
        moby->x32 = 0x180;
        moby->x30 = 0xFF;
        {
            int index = vars->next;
            if (index == -1) {
                vars->chainSpan = 0.0f;
            } else {
                int count = 0;
                do {
                    index = g_moby_l17_pool[index].vars->next;
                    count++;
                } while (index != -1);
                vars->chainSpan = IntToFloat(count);
            }
        }
        vars->chainTime = vars->chainSpan * 4.0f;
        {
            HazardPath *path = g_path_l17_table[vars->path];
            path->length = fast_vec_dist(path->start, path->end);
        }
        vars->x14 = 0;
        vars->x18 = 0;
        if (vars->next != -1) {
            D_L17_001B2C1C_1[0][vars->next].vars->parent = moby;
            vars->isLinked = 1;
            moby_set_state(moby, 3, -1);
        } else {
            moby_set_state(moby, 2, -1);
        }
        moby->state = 1;
        break;
    case 1:
        PlacePathFollowerChainAtStart(moby);
        if (D_L17_001AFCF0 && !vars->isLinked)
            moby->state = 2;
        else
            moby->state = 3;
        break;
    case 2:
        if (D_L17_001AFCF0)
            UpdatePathFollowerChain(moby);
        if (part_find_owned_effect_slot(moby, 0x4010000, 1))
            moby_set_state(moby, 5, -1);
        moby->impactSlot = 0xFF;
        break;
    case 3:
        if (vars->next != -1) {
            Moby *other = g_moby_l17_pool + vars->next;
            if (!other || other->state == 0xFE || other->state == 0xFD)
                moby_set_state(moby, 4, -1);
        }
        if (part_find_owned_effect_slot(moby, 0x4010000, 1))
            moby_set_state(moby, 5, -1);
        moby->impactSlot = 0xFF;
        break;
    case 4:
        if (flag_set_first_pending(moby))
            vars->timer = 5;
        if (math_fast_float_d(&vars->timer))
            moby_set_state(moby, 5, -1);
        break;
    case 5:
        if (moby->oClass == 0x8AD) {
            float *pos = moby->position;
            float *rot;
            float a, b;
            Moby *created;
            moby->updateDist = 1000000.0f;
            SpawnExplosion(pos, 10.0f, 0, 10, 10, 10, 10, 20, 0, 1, 0, 0, 0, 20.0f);
            rot = moby->rotation;
            part_spawn_masked_debris(moby, 11, D_L17_001A8F20, 3.0f, 6.0f, 3.0f, 6.0f, 255);
            a = math_random_float_range(-10.0f, 10.0f);
            b = math_random_float_range(20.0f, 30.0f);
            created = cam_moby_create(moby, 2, 0x8AD, 2, pos, rot, D_L17_001A8F20, 255, a, b);
            if (created)
                created->vars->sound = 0;
            part_spawn_scaled_bolts(moby, 1, 0.0f);
            moby_mark_spawned(moby);
        } else {
            moby->updateDist = 1000000.0f;
            SpawnExplosion(moby->position, 3.0f, 0, 10, 10, 10, 10, 20, 0, 1, 0, 0, 0, 20.0f);
            part_spawn_masked_debris(moby, 31, D_L17_001A8F20, 3.0f, 6.0f, 3.0f, 6.0f, 255);
            part_spawn_scaled_bolts(moby, 1, 0.0f);
            moby_mark_spawned(moby);
        }
        break;
    }
}
