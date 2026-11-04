/* func_PAL_L05_00447F28, the PAL copy of func_L05_00441D40: the same C, where 0.016666668f becomes
   0.020000001f. */
#include "include_asm.h"
#include "common.h"

extern int D_L05_001B1B20 __attribute__((sda));

extern char *D_L05_001B1EC4 MACRO_ADDR;
extern char *D_L05_001B251C MACRO_ADDR;
extern float D_L05_001B1A58 __attribute__((sda));
extern float D_L05_001B1A5C __attribute__((sda));
extern float D_L05_001B1A64 __attribute__((sda));
extern float D_L05_001B1A4C __attribute__((sda));
extern float D_L05_001B1A50 __attribute__((sda));
extern float D_L05_001B1A54 __attribute__((sda));
extern float D_L05_001B1A70 __attribute__((sda));
extern float D_L05_001B1A6C __attribute__((sda));

typedef struct ListMoby_0042C928 {
    char pad0[0x28];
    struct ListMoby_0042C928 *next;
    char pad2C[0x7E];
    short oclass;
} ListMoby_0042C928;

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

void func_PAL_L05_00447F28(Object_00441D40 *object)
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
    rate = D_L05_001B1AC0 * 0.020000001f;
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
