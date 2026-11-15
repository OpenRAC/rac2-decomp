#include "common.h"

/* The moby fields this unit reads. */
typedef struct {
    u8 pad00[0x10];
    float position[4];          /* 0x10 */
    u8 state;                   /* 0x20 */
    u8 pad21[0x68 - 0x21];
    void *vars;                 /* 0x68 */
    u8 pad6C[0x78 - 0x6C];
    u32 color;                  /* 0x78 */
    u8 pad7C[0xB0 - 0x7C];
    u8 mission;                 /* 0xB0 */
    u8 padB1;
    u16 uid;                    /* 0xB2 */
    u8 padB4[0xBC - 0xB4];
    u8 fBC;                     /* 0xBC: 1 pressed now, 2 pressed before */
} Moby;

/* The button's instance data. */
typedef struct {
    int path;                   /* 0x00: index into D_L00_001FDA80, -1 for none */
    float tag;                  /* 0x04: the button clears the path points tagged with it */
    int byMission;              /* 0x08: also pressed once the moby's mission is complete */
    float phase;                /* 0x0C: glow pulse angle */
} ButtonVars;

/* A path, as 16-byte slots: slot 0 holds the point count, slots 1 to count the points. */
typedef union {
    int count;
    struct {
        float position[3];
        float tag;              /* matched against ButtonVars.tag */
    } point;
} PathSlot;

typedef struct {
    u8 pad000[0x464];
    u8 byUid[0];                /* 0x464: nonzero starts the button pressed */
} ProgressFlags;

/* Prefix of the hero. */
typedef struct {
    u8 pad000[0x33C];
    void *groundMoby;           /* 0x33C: the moby the hero stands on */
    u8 pad340[0x34E - 0x340];
    short f34E;                 /* 0x34E */
} Hero;

/* 0x400 bytes per level: three-bit press counts, two to a byte (low bits for an even uid),
   at uid / 2. Indexed by hand: a [][0x400] view adds the two offsets in the other order. */
extern u8 D_0019B4A8[];
/* 16 missions per level: bit 0x80 is set once the mission is complete. */
extern u8 D_0019B2E8[][16];
extern ProgressFlags D_L00_0021DDB0;
extern int g_current_map_index __attribute__((sda));       /* the current level */
extern PathSlot *D_L00_001FDA80[];                /* the level's paths */
extern Hero g_hero_state;

extern float math_random_angle(void);
extern float FastAddRotations(float angle, float delta);
extern float math_fast_sin_or_cos_b(float angle);
extern int FloatToInt(float value);
extern int PlayMobySound(int sound, int, void *moby);

/* Clears the tag of each point of the button's path that carries the button's tag. */
static __inline__ void ClearPathTags(ButtonVars *vars)
{
    PathSlot *slot;
    int list;
    int i;

    list = vars->path;
    if (list != -1) {
        i = 0;
        if (D_L00_001FDA80[list]->count > 0) {
            do {
                slot = D_L00_001FDA80[list] + i;
                if (slot[1].point.tag == vars->tag)
                    slot[1].point.tag = 0.0f;
                list = vars->path;
                ++i;
            } while (i < D_L00_001FDA80[list]->count);
        }
    }
}

/* A floor button: sinks into place, then glows until the hero stands on it (or its mission
   is complete), then counts the press in the level's progress and unblocks its path. */
void FloorButtonUpdate(Moby *moby)
{
    ButtonVars *vars = moby->vars;
    u8 *counter;
    int count;
    int intensity;
    u32 grey;
    u32 alphaGreen;
    u32 blue;
    short id;
    u16 uid;
    u8 value;

    switch (moby->state) {
    case 0:
        /* Settle into the floor; start pressed if it was pressed before or its mission is done. */
        vars->phase = math_random_angle();
        id = moby->uid;
        moby->position[2] -= 0.35f;
        if (!D_L00_0021DDB0.byUid[id]) {
            count = D_0019B4A8[(id >> 1) + g_current_map_index * 0x400];
            if (moby->uid & 1)
                count = (count >> 4) & 7;
            else
                count &= 7;
            if (!count && !(vars->byMission && (D_0019B2E8[g_current_map_index][moby->mission] & 0x80)))
                goto waiting;
        }
        moby->fBC = 2;
        moby->color = 0x80208020;
        moby->state = 2;
        ClearPathTags(vars);
        return;
waiting:
        moby->state = 1;
        return;

    case 1:
        /* Pulse the glow between 32 and 128. */
        vars->phase = FastAddRotations(vars->phase, 0.10471977f);    /* 6 degrees a frame */
        intensity = FloatToInt((math_fast_sin_or_cos_b(vars->phase) * 4.0f - 3.0f) * 128.0f);
        if (intensity > 128)
            intensity = 128;
        else if (intensity < 32)
            intensity = 32;
        grey = (u32)intensity;
        alphaGreen = 0x80000000 | (grey << 8);
        blue = grey << 16;
        moby->color = blue | alphaGreen | grey;

        /* Wait for the hero to stand on the button, or for its mission. */
        if (g_hero_state.groundMoby != moby || g_hero_state.f34E) {
            if (!vars->byMission)
                return;
            if (!(D_0019B2E8[g_current_map_index][moby->mission] & 0x80))
                return;
        }

        /* Count the press (up to 7), then unblock the path. */
        uid = moby->uid;
        if (uid & 1) {
            counter = &D_0019B4A8[((short)uid >> 1) + g_current_map_index * 0x400];
            value = *counter;
            if (((value >> 4) & 7) != 7)
                *counter = value + 0x10;
        } else {
            counter = &D_0019B4A8[((short)uid >> 1) + g_current_map_index * 0x400];
            value = *counter;
            if ((value & 7) != 7)
                *counter = value + 1;
        }
        moby->state = 2;
        moby->fBC = 1;
        moby->color = 0x80208020;
        PlayMobySound(0, 0, moby);
        ClearPathTags(vars);
    }
}
