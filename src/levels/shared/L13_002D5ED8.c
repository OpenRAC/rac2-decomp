#include "include_asm.h"
#include "names.h"

/* func_L13_002D5ED8 is in the sibling file L13_002D5ED8-decider.c (its own profile). */

#ifndef RAC2_T_TABLE_389848
#define RAC2_T_TABLE_389848
typedef struct {
    int entries[64];    /* +0x000 */
    int count;          /* +0x100 */
} Table_389848;
#endif

#ifndef RAC2_T_OBJ_389848
#define RAC2_T_OBJ_389848
typedef struct {
    char pad[0xAA];
    short key;          /* +0xAA */
} Obj_389848;
#endif

extern Table_389848 ref_L13_00232450_00;

/* Adds the object's key to the level's list when it is not already there: the count at +0x100
 * bounds a linear search over the words at +0, and an absent key is appended at the count
 * before the count is bumped. */
/* Remembers this object in the level list so it is only added once. */
void level_list_add_key(Obj_389848 *object)
{
    int found = 0;
    int i;

    for (i = 0; i < ref_L13_00232450_00.count; i++) {
        if (ref_L13_00232450_00.entries[i] == object->key) {
            found = 1;
            break;
        }
    }
    if (found == 0) {
        ref_L13_00232450_00.entries[ref_L13_00232450_00.count] = object->key;
        ++ref_L13_00232450_00.count;
    }
}

typedef struct {
    char pad_00[0x20];        /* +0x000 */
    unsigned char state;      /* +0x020 */
    char pad_21[0x0F];
    unsigned char flag;       /* +0x030 */
    char pad_31[0x37];
    Table_389848 *table;      /* +0x068 */
} Obj_38C1B8;

extern int IsPointInCuboid(void *, int);
extern void FadeToBlack(int);
extern void hero_record_play_counters(void);
extern void ref_L13_0038C1B8_00(int, int);
extern char g_hero_position[];
extern char g_hero_state[];

/* The state byte at +0x20 drives the work: state 0 clears the flag at +0x30 and moves the
 * object to state 1, state 1 walks the sixty-four entries of the table at +0x68 in two
 * halves of thirty-two, and any other state does nothing.  D_00189EA0 is the pointer the
 * entry test hands to func_002ACBC8, and the map selection block D_00189E20 sits 0x80
 * before it. */
/* Checks the listed objects each frame and sends the hero into a new state when the hero reaches one of them. */
void trigger_list_check_hero(Obj_38C1B8 *a0)
{
    Table_389848 *t = a0->table;
    int *e;
    unsigned char *q;
    unsigned char *m;
    int i;
    int j;
    int v;

    switch (a0->state) {
    case 0:
        a0->state = 1;
        a0->flag = 0xFF;
        break;
    case 1:
        q = (unsigned char *)g_hero_state;
        e = t->entries + 32;
        for (i = 0; i < 32; i++) {
            v = t->entries[i];
            if (v < 0)
                continue;
            if (IsPointInCuboid(g_hero_position, v) == 0)
                continue;
            if (t->count != 0) {
                *(float *)(q + 0x24C8) = 0.25f;
                continue;
            }
            m = (unsigned char *)g_hero_position - 0x80;
            if (m[0x22B4] != 0) {
                FadeToBlack(10);
                hero_record_play_counters();
            } else if (*(int *)(m + 0x2294) != 0x74) {
                ref_L13_0038C1B8_00(0x74, 1);
            }
        }
        for (j = 0; j < 32; j++) {
            v = e[j];
            if (v < 0)
                continue;
            if (IsPointInCuboid(g_hero_position, v) == 0)
                continue;
            FadeToBlack(10);
            hero_record_play_counters();
        }
        break;
    }
}

/* Read at +0xC0: a symbol-plus-offset address stays one two-instruction macro load, which reorg
 * cannot move into a branch delay slot. */
extern unsigned char g_unlocked_item_flags[] __attribute__((sda));
extern int FloatToInt(float);
extern float math_fast_sin_or_cos_b(float);
extern void moby_set_state(char *, int, int);
extern int flag_set_first_pending(char *);
extern void cam_lock_entry(int);
extern int ForceClaimNotice(int, int, int);
extern void ref_L13_003C5908_00(int, int);
extern float FastAddRotations(float, float);

/* State 0 opens the trigger; state 1 reacts to the hero being on the object, or being in state
 * 0x82 inside its cuboid. Then pulses the object's colour, in the channel the flag selects. */
/* Updates a levitator pad that lifts the hero, and makes its glow pulse. */
void levitator_l13_pad_update(char *obj)
{
    char *rig = *(char **)(obj + 0x68);
    char *hero, *other;
    int word, level, glow;
    float turn, pulse;

    switch (*(unsigned char *)(obj + 0x20)) {
    case 0:
        *(unsigned short *)(obj + 0x34) |= 0x10;
        moby_set_state(obj, 1, -1);
        break;
    case 1:
        if (flag_set_first_pending(obj) != 0) {
            word = *(int *)rig;
            if (word != -1) {
                cam_lock_entry(word);
                *(int *)rig = -1;
            }
        }
        hero = g_hero_state;
        if (*(char **)(hero + 0x33C) == obj && *(int *)(hero + 0x340) != 0) {
            if (g_unlocked_item_flags[0xC0] != 0) {
                ForceClaimNotice(0xC, 0x27F7, 1);
                *(short *)(hero + 0x1F2) = 0xA;
                turn = *(float *)(rig + 0xC);
                if (turn != 0.0f)
                    *(float *)(hero + 0x5B8) = turn;
            }
        } else {
            other = g_hero_state;
            if (*(int *)(other + 0x2294) == 0x82) {
                level = *(int *)(rig + 8);
                if (level >= 0 && IsPointInCuboid(other + 0x80, level) != 0)
                    ref_L13_003C5908_00(6, 1);
            }
        }
        break;
    }
    if (*(unsigned char *)(obj + 0x31) != 0) {
        pulse = FastAddRotations(*(float *)(rig + 4), 0.10471977f);
        *(float *)(rig + 4) = pulse;
        glow = FloatToInt(math_fast_sin_or_cos_b(pulse) * 128.0f);
        if (glow > 0x80)
            glow = 0x80;
        else if (glow < 0x20)
            glow = 0x20;
        if (g_unlocked_item_flags[0xC0] != 0)
            *(int *)(obj + 0x78) = (glow << 8) | 0x80000000;
        else
            *(int *)(obj + 0x78) = glow | 0x80000000;
    }
}

static __inline__ void qcopy(void *dst, const void *src) {
    __asm__ __volatile__("lq $2,0x0(%1)\n\tsq $2,0x0(%0)"
                         : : "r"(dst), "r"(src) : "$2", "memory");
}

extern int moby_apply_damage_to_object(void *, void *, int);
extern int PlayMobySound(int, int, char *);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern void *SpawnExplosion(void *, int, int, int, int, int, int, int, float, float, int, int, int, int);
extern void moby_mark_spawned(void *);

typedef struct {
    unsigned char pad0[0x20];
    float f20;
    unsigned char pad24[0x50 - 0x24];
    unsigned char sub50[0x11];
    unsigned char b61;
    unsigned char b62;
    unsigned char pad63[0x6A - 0x63];
    unsigned char b6A;
    unsigned char pad6B[0xA8 - 0x6B];
    float fA8;
} L13_CD48Vars;

/* Keeps an enemy object alive, and when its health runs out makes a small explosion and removes it. */
void enemy_update_explode(unsigned char *m)
{
    L13_CD48Vars *v = *(L13_CD48Vars **)(m + 0x68);
    float p[4] __attribute__((aligned(16)));
    float b[4] __attribute__((aligned(16)));
    float a[4] __attribute__((aligned(16)));

    if (m[0x20] == 0) {
        level_list_add_key((Obj_389848 *)m);
        m[0x20] = 1;
    }
    v->b6A = 2;
    v->fA8 = 0.01f;
    v->b61 = 0xFF;
    v->b62 = 0xFF;
    if (moby_apply_damage_to_object(m, v->sub50, 0) != 0) {
        PlayMobySound(0, 0, (char *)m);
    }
    if (v->f20 <= 0.0f) {
        qcopy(p, m + 0x10);
        vec_scale_to_length(a, m + 0xD0, -2.0f);
        FastVecAdd(p, a, p);
        vec_scale_to_length(b, m + 0xC0, 1.5f);
        FastVecAdd(p, b, p);
        SpawnExplosion(p, 0, 0x19, 0x14, 0x14, 0x14, 0x2D, 1, 0.75f, 20.0f, 1, 0, 0, 0);
        moby_mark_spawned(m);
    }
}


/* The level's entity table: 0x100 bytes an entry. */
extern char *g_object_table_base __attribute__((section(".sdata")));

/* Compares the choice (0, 1 or 2) at +0x2CC of the object's state with its opponent's:
 * the entity the state names at +0x2C8 decides the opponent by its kind at +0xAA (0xEA3
 * reads the partner state's +0x2CC, 0xEA4 its +0x2C4; any other kind is a draw). Returns
 * 2 for a draw, 1 when the object's choice wins (0 over 1, 1 over 2, 2 over 0), else 0. */
/* Plays rock-paper-scissors for two creatures and says who wins: 2 is a draw, 1 means this one wins, 0 means it loses. */
int rps_judge(char *object)
{
    char *state = *(char **)(object + 0x68);
    char *entity = g_object_table_base + (*(int *)(state + 0x2C8) << 8);
    int mine;
    int other;

    if (*(short *)(entity + 0xAA) == 0xEA3 /* moby class 3747 */) {
        mine = *(int *)(state + 0x2CC);
        other = *(int *)(*(char **)(entity + 0x68) + 0x2CC);
    } else if (*(short *)(entity + 0xAA) == 0xEA4 /* moby class 3748 */) {
        mine = *(int *)(state + 0x2CC);
        other = *(int *)(*(char **)(entity + 0x68) + 0x2C4);
    } else {
        other = *(int *)(state + 0x2CC);
        mine = other;
    }

    if (mine == other)
        return 2;
    if (mine == 0 && other == 1)
        return 1;
    if (mine == 1 && other == 2)
        return 1;
    if (mine == 2 && other == 0)
        return 1;
    if (mine == 0 && other == 2)
        return 0;
    if (mine == 1 && other == 0)
        return 0;
    if (mine == 2 && other == 1)
        return 0;
    return 2;
}
