#include "include_asm.h"

#include "common.h"
typedef struct {
    int kind;
    int count;
    void *table0;
    void *table1;
    void *small0;
    void *counts;
    void *table2;
    void *table3;
    void *small1;
    void *small2;
    void *owner;
    void *callback;
    void *callback2;
} L08SpawnBlock;
extern char D_00189E20[];
extern char D_L08_002A0D00[];
extern char D_L08_0023EC80[];
extern char D_L08_0023ECF0[];
extern char D_L08_002A87F0[];
extern int D_L08_001B01B8[2] __attribute__((sda));
extern u16 D_L08_001B01C8[] SDATA(D_L08_001B01C8);
extern int D_L08_001B01D8 __attribute__((sda));
extern int D_L08_001B01DC __attribute__((sda));
extern void func_L08_003CFFE8(void);
extern void func_L00_002E6CF0(void);
extern void func_PAL_L04_003A47C0(L08SpawnBlock *);
extern void func_L04_003A5C08(void *, float);
extern void func_PAL_L04_003A49E0(L08SpawnBlock *);
extern void func_L04_003A1FA0(L08SpawnBlock *);
extern void func_L04_003A1FE0(L08SpawnBlock *);

/* Runs the shared spawn routines for the object, unless the level's player (the entity at
   D_00189E20+0x1830, kind 0x45) is alive while the mode word at +0x2294 is 0x31. The count
   is the state's +0x10 plus an entry of D_L08_001B01B8 picked by +0x18 (1 when -1); state
   0 sets the object up first and then shares state 1's step, state 2 has its own. */
void func_PAL_L08_003D3E18(char *object)
{
    L08SpawnBlock block;
    char *level = D_00189E20;
    char *player = *(char **)(level + 0x1830);
    char *state;
    int count;

    if (player != 0 && *(short *)(player + 0xAA) == 0x45 &&
        *(unsigned char *)(player + 0x20) != 0xFE && *(unsigned char *)(player + 0x20) != 0xFD &&
        *(int *)(level + 0x2294) == 0x31)
        return;
    state = *(char **)(object + 0x68);
    if (state == 0)
        return;
    count = 1;
    if (*(int *)(state + 0x18) != -1)
        count = D_L08_001B01B8[*(int *)(state + 0x18)];
    count += *(int *)(state + 0x10);
    block.kind = 7;
    block.count = count;
    block.small1 = &D_L08_001B01D8;
    block.small2 = &D_L08_001B01DC;
    block.table0 = D_L08_002A0D00;
    block.table1 = D_L08_0023EC80;
    block.small0 = D_L08_001B01C8;
    block.counts = D_L08_001B01B8;
    block.table2 = D_L08_0023ECF0;
    block.table3 = D_L08_002A87F0;
    block.owner = object;
    block.callback = func_L08_003CFFE8;
    block.callback2 = func_L00_002E6CF0;
    switch (*(unsigned char *)(object + 0x20)) {
    case 0:
        func_PAL_L04_003A47C0(&block);
        func_L04_003A5C08(object, *(float *)(state + 0x28));
    case 1:
        func_PAL_L04_003A49E0(&block);
        break;
    case 2:
        func_L04_003A1FA0(&block);
        break;
    }
    func_L04_003A1FE0(&block);
}
