#include "include_asm.h"
#include "common.h"

/* The two small-data words below are reached through $gp in ordinary flow, not
   in a delay slot, so this unit has to be the -G8 sibling of L05_00428350.c. */
extern int D_L05_001B1B20 __attribute__((sda));

extern int D_L05_001B1B24 __attribute__((sda));

/* Three per-slot tables indexed by the state's slot number. Each is an incomplete sda array:
   cc1 then keeps every table address as one `la`, which the assembler expands to an adjacent
   absolute lui/addiu pair, while D_L05_001B157C (sized) is reached through $gp. */
extern float D_L05_001B3580[] __attribute__((sda));
extern int D_L05_001B3598[] __attribute__((sda));
extern int D_L05_001B35B0[] __attribute__((sda));
extern float D_L05_001B157C __attribute__((sda));
extern char D_L05_001B96C0[];
extern float func_00282E48(void *, void *);
extern int func_00282978(void *);
extern void func_0029F338(void *);
extern void func_L00_002E6DB8(void *, void *);
extern void func_L05_00428518(void *);

extern char *D_L05_001B1EC4 MACRO_ADDR;
extern char *D_L05_001B251C MACRO_ADDR;
extern int D_001A79F0 __attribute__((sda));
extern int func_L05_00379F38(void);
extern float D_L05_001B1AB4 __attribute__((sda));
extern float D_L05_001B1AB8 __attribute__((sda));
extern float D_L05_001B1ABC __attribute__((sda));
extern float D_L05_001B1A8C __attribute__((sda));
extern float D_L05_001B1A90 __attribute__((sda));
extern float D_L05_001B1A88 __attribute__((sda));
extern float D_L05_001B1A94 __attribute__((sda));
extern float D_L05_001B1A98 __attribute__((sda));
extern float D_L05_001B1A34 __attribute__((sda));
extern float D_L05_001B1A38 __attribute__((sda));
extern float D_L05_001B1A3C __attribute__((sda));
extern float D_L05_001B1A28 __attribute__((sda));
extern float D_L05_001B1A2C __attribute__((sda));
extern float D_L05_001B1A30 __attribute__((sda));
extern float D_L05_001B1A1C __attribute__((sda));
extern float D_L05_001B1A20 __attribute__((sda));
extern float D_L05_001B1A24 __attribute__((sda));
extern float D_L05_001B1A78 __attribute__((sda));
extern float D_L05_001B1A74 __attribute__((sda));
extern float D_L05_001B1B88 __attribute__((sda));
extern float D_L05_001B1B84 __attribute__((sda));
extern float D_L05_001B1B8C __attribute__((sda));
extern float D_L05_001B1B90 __attribute__((sda));
extern float D_L05_001B1B94 __attribute__((sda));
extern float D_L05_001B1B98 __attribute__((sda));
extern float D_L05_001B1B9C __attribute__((sda));
extern float D_L05_001B1BA0 __attribute__((sda));
extern float D_L05_001B1BA4 __attribute__((sda));
extern float D_L05_001B1BA8 __attribute__((sda));
extern float D_L05_001B1BAC __attribute__((sda));
extern float D_L05_001B1BB0 __attribute__((sda));
extern float D_L05_001B1BB4 __attribute__((sda));
extern float D_L05_001B1BB8 __attribute__((sda));
extern float D_L05_001B1BC0 __attribute__((sda));
extern float D_L05_001B1A58 __attribute__((sda));
extern float D_L05_001B1A5C __attribute__((sda));
extern float D_L05_001B1A64 __attribute__((sda));
extern float D_L05_001B1A4C __attribute__((sda));
extern float D_L05_001B1A50 __attribute__((sda));
extern float D_L05_001B1A54 __attribute__((sda));
extern float D_L05_001B1A70 __attribute__((sda));
extern float D_L05_001B1A6C __attribute__((sda));

/* The look record reached through the object's model entry: eight floats from +0x240. */
typedef struct {
    char pad[0x240];
    float a[3];
    float b[3];
    float c, d;
} LookSettings_L05_00442880;

/* The parameter block at +0x50 of the object's +0x70 record. */
typedef struct {
    float a[3];
    float b[3];
    char pad[0x74 - 0x18];
    float c, d;
} Params_L05_00442880;

typedef struct {
    char pad[0x50];
    Params_L05_00442880 params;
} Record_L05_00442880;

/* Reports 1 while the second word is set; otherwise whether the first word,
   minus two, is below two as an unsigned value. */
int func_L05_00442860(void)
{
    if (D_L05_001B1B24 != 0)
        return 1;
    return (unsigned int)(D_L05_001B1B20 - 2) < 2;
}

/* On the first pass seeds the slot's speed and timer, then picks the state's +0x40 rate from
   the distance to D_L05_001B96C0; afterwards either chains func_L05_00428518 or releases the
   slot and drops the live count. */
void func_L05_00428350(char *object)
{
    char *state = *(char **)(object + 0x68);

    if (!*(unsigned char *)(object + 0x20)) {
        D_L05_001B3580[*(int *)(state + 0x3C)] = 0.01f;
        D_L05_001B3598[*(int *)(state + 0x3C)] = 0x80;
        *(unsigned char *)(object + 0x20) = 1;
        if (func_00282E48(object + 0x10, D_L05_001B96C0) > 200.0f)
            *(float *)(state + 0x40) = 4.0f;
        else if (func_00282E48(object + 0x10, D_L05_001B96C0) > 100.0f)
            *(float *)(state + 0x40) = 2.0f;
        else if (func_00282E48(object + 0x10, D_L05_001B96C0) > 25.0f)
            *(float *)(state + 0x40) = 1.0f;
        else if (func_00282E48(object + 0x10, D_L05_001B96C0) > 0.0f)
            *(float *)(state + 0x40) = 0.5f;
    }
    if (!func_00282978(state)) {
        func_00282978(state + 4);
        func_L00_002E6DB8(func_L05_00428518, object);
    } else {
        D_L05_001B35B0[*(int *)(state + 0x3C)] = 0;
        D_L05_001B157C -= 1.0f;
        func_0029F338(object);
    }
}

/* Loads the default look, then one of three parameter sets: the first when
   func_L05_00379F38 reports set (its middle vector depends on D_001A79F0 == 15), the
   second (which also overrides the look) when D_001A79F0 is 15, the third otherwise. The
   struct field stores let the scheduler hoist the global loads past them as retail does. */
void func_L05_00442880(char *object)
{
    Record_L05_00442880 *record = *(Record_L05_00442880 **)(object + 0x70);
    Params_L05_00442880 *params = &record->params;
    char *entry = *(char **)(D_L05_001B1EC4 + *(short *)(object + 0x84) * 32 + 0x1C);
    LookSettings_L05_00442880 *look =
        *(LookSettings_L05_00442880 **)(D_L05_001B251C + (*(int *)(entry + 0x20) << 8) + 0x68);

    look->a[0] = D_L05_001B1AB4;
    look->a[1] = D_L05_001B1AB8;
    look->a[2] = D_L05_001B1ABC;
    look->b[1] = D_L05_001B1A8C;
    look->b[2] = D_L05_001B1A90;
    look->b[0] = D_L05_001B1A88;
    look->c = D_L05_001B1A94;
    look->d = D_L05_001B1A98;
    if (func_L05_00379F38()) {
        if (D_001A79F0 == 15) {
            params->b[0] = D_L05_001B1A34;
            params->b[1] = D_L05_001B1A38;
            params->b[2] = D_L05_001B1A3C;
        } else {
            params->b[0] = D_L05_001B1A28;
            params->b[1] = D_L05_001B1A2C;
            params->b[2] = D_L05_001B1A30;
        }
        params->a[0] = D_L05_001B1A1C;
        params->a[1] = D_L05_001B1A20;
        params->a[2] = D_L05_001B1A24;
        params->c = D_L05_001B1A78;
        params->d = D_L05_001B1A74;
    } else if (D_001A79F0 == 15) {
        params->b[0] = D_L05_001B1B84;
        params->b[1] = D_L05_001B1B88;
        params->b[2] = D_L05_001B1B8C;
        record->params.a[0] = D_L05_001B1B90;
        params->a[1] = D_L05_001B1B94;
        params->a[2] = D_L05_001B1B98;
        params->c = D_L05_001B1B9C;
        params->d = D_L05_001B1BA0;
        look->a[0] = D_L05_001B1BA4;
        look->a[1] = D_L05_001B1BA8;
        look->a[2] = D_L05_001B1BAC;
        look->b[1] = D_L05_001B1BB0;
        look->b[2] = D_L05_001B1BB4;
        look->b[0] = D_L05_001B1BB8;
        look->c = D_L05_001B1A94;
        look->d = D_L05_001B1BC0;
    } else {
        params->b[0] = D_L05_001B1A58;
        params->b[1] = D_L05_001B1A5C;
        params->b[2] = D_L05_001B1A64;
        record->params.a[0] = D_L05_001B1A4C;
        params->a[1] = D_L05_001B1A50;
        params->a[2] = D_L05_001B1A54;
        params->c = D_L05_001B1A70;
        params->d = D_L05_001B1A6C;
    }
}

/* A moby in the level's list, linked through +0x28 and tagged by the class id at +0xAA. */
typedef struct ListMoby_0042C928 {
    char pad0[0x28];
    struct ListMoby_0042C928 *next;
    char pad2C[0x7E];
    short oclass;
} ListMoby_0042C928;
extern u8 D_0019B278[] MACRO_ADDR;
extern int D_001A79F0_1;
extern char *D_0018C0B0 NOT_SDA;
extern float D_L05_001B1748 __attribute__((sda));
extern float D_L05_001B174C __attribute__((sda));
extern float D_L05_001B1750 __attribute__((sda));
extern ListMoby_0042C928 *D_L05_001B1780 __attribute__((sda));
extern ListMoby_0042C928 *D_L05_001B2528;
extern char *func_0029EFD0(s32 a0);
extern float func_002A7940(void);
extern void func_L01_00397950(char *a0);
extern void func_002A0488(char *a0, s32 a1, s32 a2, s32 a3);

char *func_L05_0042C928(float *pos, u32 kind, s32 a2, s32 a3)
{
    char *moby;
    char *vars;
    ListMoby_0042C928 *p;
    u8 *collected = D_0019B278;

    if (kind >= 4 || collected[kind + (D_001A79F0_1 << 2)] != 0)
        return 0;
    moby = func_0029EFD0(0x126C);
    if (moby != 0) {
        float x, y, z, r;

        vars = *(char **)(moby + 0x68);
        *(long *)(moby + 0x38) = *(long *)(D_0018C0B0 + 0x38);
        qcopy(moby + 0x10, pos);
        *(s16 *)(moby + 0x32) = 0x40;
        *(u8 *)(moby + 0x30) = 0x40;
        *(u8 *)(moby + 0x31) = 1;
        *(u32 *)vars = kind;
        qcopy(vars + 0x10, moby + 0x10);
        *(float *)(vars + 0x1C) = *(float *)(moby + 0xF8);
        *(float *)(moby + 0xF0) = func_002A7940();
        *(float *)(moby + 0xF4) = func_002A7940();
        *(float *)(moby + 0xF8) = func_002A7940();
        r = func_002A7940();
        x = D_L05_001B1748;
        y = D_L05_001B174C;
        z = D_L05_001B1750;
        *(float *)(moby + 0xFC) = r;
        *(s32 *)(vars + 8) = a3;
        *(s32 *)(vars + 4) = a2;
        x *= 0.00029088825f;
        y *= 0.00029088825f;
        z *= 0.00029088825f;
        *(float *)(vars + 0x60) = z;
        *(float *)(vars + 0x68) = x;
        *(float *)(vars + 0x64) = y;
        *(u8 *)(moby + 0x20) = 1;
        func_L01_00397950(moby);
        func_002A0488(moby, 0x82, 0x82, 0x82);
        if (D_L05_001B1780 == 0) {
            for (p = D_L05_001B2528; p != 0; p = p->next) {
                if (p->oclass == 0xFBF)
                    D_L05_001B1780 = p;
            }
        }
    }
    return moby;
}

extern float D_L05_001B1A10 __attribute__((sda));
extern float D_L05_001B1A14 __attribute__((sda));
extern float D_L05_001B1A18 __attribute__((sda));
extern float D_L05_001B1AC0 __attribute__((sda));
extern int D_L05_001B1B74 __attribute__((sda));
extern int D_L05_001B1B78 __attribute__((sda));
extern void func_00282C88(void *a0);
extern void func_L05_00441EA0(void *a0);
extern void func_L00_002E54E0(float a0);
extern void func_L05_003D1E20(void);
extern void func_L05_00442720(void);

typedef struct Block_00441D40 {
    float f00, f04, f08, f0C, f10, f14;
    int f18;
    short f1C;
    u8 f1E, f1F;
    int pad20;
    int f24;
    char pad28[0x28];
    char v50[0x10];
    char v60[0x10];
    int f70;
    float f74;
    float f78;
} Block_00441D40;

typedef struct Tail_00441D40 {
    char pad0[4];
    short f04;
    short f06;
    char pad8[4];
    short f0C;
    char padE[2];
    short f10;
} Tail_00441D40;

typedef struct State_00441D40 {
    float pos[3];
    int pad0C;
    char v10[0x30];
    int f40;
    int f44;
    char pad48[8];
    Block_00441D40 blk;
    char padCC[8];
    Tail_00441D40 tail;
} State_00441D40;

typedef struct Entry_00441D40 {
    char pad0[0x20];
    int index;
    char pad24[0x34];
    int f58;
} Entry_00441D40;

typedef struct Slot_00441D40 {
    char pad0[0x1C];
    Entry_00441D40 *entry;
} Slot_00441D40;

typedef struct ActorVars_00441D40 {
    char pad0[0x38];
    float rate;
    char pad3C[0x1D8];
    int f214;
} ActorVars_00441D40;

typedef struct Actor_00441D40 {
    char pad0[0x68];
    ActorVars_00441D40 *vars;
    char pad6C[0x94];
} Actor_00441D40;

typedef struct Object_00441D40 {
    char pad0[0x70];
    State_00441D40 *state;
    char pad74[0xA];
    short f7E;
    char pad80[4];
    short f84;
} Object_00441D40;

void func_L05_00441D40(Object_00441D40 *object)
{
    State_00441D40 *state;
    State_00441D40 *state2;
    Block_00441D40 *blk;
    Tail_00441D40 *tail;
    Entry_00441D40 *entry;
    ActorVars_00441D40 *vars;
    Slot_00441D40 *table;
    char *actors;
    float rate;

    state = object->state;
    state->pos[0] = D_L05_001B1A10;
    state->pos[1] = D_L05_001B1A14;
    state->pos[2] = D_L05_001B1A18;
    func_00282C88(state->v10);
    state->f40 = 0;
    state->f44 = 0;

    state2 = object->state;
    blk = &state2->blk;
    blk->f00 = D_L05_001B1A4C;
    blk->f04 = D_L05_001B1A50;
    blk->f08 = D_L05_001B1A54;
    blk->f74 = D_L05_001B1A70;
    blk->f78 = D_L05_001B1A6C;
    blk->f0C = D_L05_001B1A58;
    blk->f10 = D_L05_001B1A5C;
    blk->f14 = D_L05_001B1A64;
    blk->f70 = 0;
    blk->f1C = 0;
    blk->f18 = 0;
    blk->f24 = 0;
    blk->f1E = 0;
    blk->f1F = 0;
    func_00282C88(state2->blk.v50);
    func_00282C88(state2->blk.v60);
    func_L05_00441EA0(object);
    func_L00_002E54E0(4096.0f);

    table = (Slot_00441D40 *)D_L05_001B1EC4;
    actors = D_L05_001B251C;
    tail = &object->state->tail;
    tail->f06 = 0;
    tail->f0C = 0;
    tail->f10 = 0;
    tail->f04 = 0;
    rate = D_L05_001B1AC0 * 0.016666668f;
    entry = table[object->f84].entry;
    entry->f58 = 0;
    vars = ((Actor_00441D40 *)(actors + (entry->index << 8)))->vars;
    vars->rate = rate;
    vars->f214 = -1;
    object->f7E = 0;
    D_L05_001B1B20 = 0;
    func_L05_003D1E20();
    D_L05_001B1B74 = 0;
    D_L05_001B1B78 = 0;
    func_L05_00442720();
}
