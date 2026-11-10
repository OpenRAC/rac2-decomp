#include "common.h"

/* func_L09_003C0DF8 of L09_002F8BA0.c, in a unit of its own: its MACRO_ADDR declarations of
   D_001A79F0 and the record bases are not the ones the rest of that file uses. Retail reads each
   of them with the absolute `lui`/`lw` pair in ordinary flow and with one $gp-relative `lw` where
   reorg puts the load in a branch delay slot; a single MACRO_ADDR declaration gives exactly that
   mix (docs/build/compiler-notes.md, small data). */

/* The trailing flags have no measured fixed extent. */
typedef struct {
    unsigned char padding[0x464];
    unsigned char active[0];
} DobboFlags;
extern DobboFlags D_L09_0021E9F0;
/* One 1 KB table per planet, a 3-bit count in each nibble; the low bit of the number picks it. */
extern u8 D_0019B4A8[];
extern int D_001A79F0 MACRO_ADDR;

/* The level's target points: retail indexes these records with a 0x80-byte stride. */
typedef struct {
    char pad[0x30];
    float pos[4];
    char pad40[0x30];
    float rot[4];
} DobboPoint;
extern DobboPoint *D_L09_001B294C MACRO_ADDR;

/* The mover's own variables: where it started, which point it goes to and how far it is. */
typedef struct {
    float pos[4];  /* 0x00 */
    float rot[4];  /* 0x10 */
    int point;     /* 0x20 */
    float time;    /* 0x24 */
    float t;       /* 0x28 */
    int trigger;   /* 0x2C */
    int link;      /* 0x30 */
} DobboMoverVars;

/* The fields of a moby this function touches. They are written as members: a store through a
   member lets retail's later loads of the record base (a scalar global) be scheduled before it. */
typedef struct {
    char pad00[0x10];
    float pos[4];           /* 0x10 */
    u8 state;               /* 0x20 */
    char pad21[0x13];
    u16 flags;              /* 0x34 */
    char pad36[0x32];
    DobboMoverVars *vars;   /* 0x68 */
    char pad6C[0x46];
    u16 uid;                /* 0xB2 */
    char padB4[8];
    u8 armed;               /* 0xBC */
    char padBD[0x33];
    float rot[4];           /* 0xF0 */
} DobboMoby;
extern DobboMoby *D_L09_001B285C MACRO_ADDR; /* the level's mobys, 0x100 bytes each */

extern void func_002A7750(void *, int, int);
extern void func_00282CF0(void *, void *, void *), func_00282D30(void *, void *, float), func_00282CC0(void *, void *, void *);
extern float func_00283180(float), func_002AA150(float, float, float);

/* A moby that glides to a target point once another moby arms it, and stays there afterwards.
   State 0 records where it starts; if it was triggered before (its flag byte, or its count in
   D_0019B4A8) it is put on the target at once (state 3), otherwise it waits (state 1). State 1
   waits for the trigger moby to be armed and alive, passes the arming on to the linked moby,
   raises its own count (up to 7) and starts moving. State 2 eases position and rotation towards
   the target over `time` frames with a cosine curve. State 3 sets flag 2 of the moby when there
   is no linked moby or the linked one is not armed. */
void func_L09_003C0DF8(DobboMoby *moby) {
    DobboMoverVars *vars = moby->vars;
    float v[4];
    float blend;
    int id;
    int id2;    /* state 1 reads the number again into a register of its own, as retail does */
    int bits;

    switch (moby->state) {
    case 0:
        if (vars->point == -1) {
            moby->flags |= 2;
            func_002A7750(moby, 4, -1);
            break;
        }
        qcopy_nc(vars->pos, moby->pos);
        qcopy_nc(vars->rot, moby->rot);
        id = moby->uid;
        /* The byte is read once, ahead of the odd/even test, and each arm tests its own nibble. */
        if (D_L09_0021E9F0.active[(s16)id]
            || (bits = D_0019B4A8[((s16)id >> 1) + (D_001A79F0 << 10)],
                (id & 1) ? ((bits >> 4) & 7) : (bits & 7))) {
            qcopy_nc(moby->pos, D_L09_001B294C[vars->point].pos);
            qcopy_nc(moby->rot, D_L09_001B294C[vars->point].rot);
            moby->flags |= 2;
            func_002A7750(moby, 3, -1);
        } else {
            func_002A7750(moby, 1, -1);
        }
        break;
    case 1:
        if (vars->trigger == -1)
            break;
        if (D_L09_001B285C[vars->trigger].state == 0xFE)
            break;
        if (D_L09_001B285C[vars->trigger].state == 0xFD)
            break;
        if (D_L09_001B285C[vars->trigger].armed == 0)
            break;
        if (vars->link != -1)
            D_L09_001B285C[vars->link].armed = moby->state;
        id2 = moby->uid;
        if (id2 & 1) {
            if (((D_0019B4A8[((s16)id2 >> 1) + (D_001A79F0 << 10)] >> 4) & 7) != 7)
                D_0019B4A8[((s16)id2 >> 1) + (D_001A79F0 << 10)] += 0x10;
        } else {
            if ((D_0019B4A8[((s16)id2 >> 1) + (D_001A79F0 << 10)] & 7) != 7)
                D_0019B4A8[((s16)id2 >> 1) + (D_001A79F0 << 10)] += 1;
        }
        func_002A7750(moby, 2, -1);
        break;
    case 2:
        vars->t += 1.0f / vars->time;
        if (vars->t > 1.0f)
            vars->t = 1.0f;
        blend = (1.0f - func_00283180(vars->t * 3.14159274f)) * 0.5f;
        func_00282CF0(v, D_L09_001B294C[vars->point].pos, vars->pos);
        func_00282D30(v, v, blend);
        func_00282CC0(moby->pos, vars->pos, v);
        moby->rot[2] = func_002AA150(vars->rot[2], D_L09_001B294C[vars->point].rot[2], blend);
        moby->rot[1] = func_002AA150(vars->rot[1], D_L09_001B294C[vars->point].rot[1], blend);
        moby->rot[0] = func_002AA150(vars->rot[0], D_L09_001B294C[vars->point].rot[0], blend);
        if (vars->t >= 1.0f)
            func_002A7750(moby, 3, -1);
        break;
    case 3:
        if (vars->link == -1 || D_L09_001B285C[vars->link].armed == 0)
            moby->flags |= 2;
        break;
    }
}
