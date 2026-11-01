#include "include_asm.h"

INCLUDE_ASM("asm/pal/levels", func_PAL_L11_00445BB8);


INCLUDE_ASM("asm/pal/levels", func_PAL_L11_004460C0);

#include "common.h"
extern u8 D_L11_004465F8[];
extern u8 *D_L11_001FC420[];
extern u8 *D_L11_001B359C __attribute__((section(".sdata")));
typedef struct {
    u8 pad0[0x10];
    float pos[4];
    u8 state;
    u8 pad21[0x89];
    short oclass;
    u8 padAC[0xC];
    void *owner;
    u8 padBC[4];
    float rot[12];
    float fF0;
    float fF4;
    float fF8;
} GroupMoby440B28;
typedef struct {
    u8 pad0[0xC0];
    int group;
} GroupVars440B28;
extern char *D_001B359C __attribute__((sda));
extern unsigned short *D_001FC420[];
extern float func_00283248(float, float);
extern void func_002833F0(void *, void *);
extern void func_PAL_L11_0043BE90(void *, int, int);
extern u8 *D_L11_001FC420[];
extern u8 *D_L11_001B359C;
extern u8 *D_L11_001B359C_base[] __asm__("D_L11_001B359C") __attribute__((sda));
extern u8 *D_L11_001B368C __attribute__((sda));
extern u8 D_00189E20[];
extern u8 D_001A63A8[];

int func_PAL_L11_00446380(u8 *object, float *target)
{
    GroupMoby440B28 *member;
    unsigned short *list;
    unsigned short *p;
    int group;
    float dx;

    group = ((GroupVars440B28 *)*(u8 **)(object + 0x68))->group;
    if (group == 0xFF)
        return 0;
    list = D_001FC420[group];
    if (list == 0)
        return 0;
    p = list;
    do {
        member = (GroupMoby440B28 *)(D_001B359C + (*p & 0x7FFF) * 0x100);
        if (member != 0 && member->state != 0xFE && member->state != 0xFD &&
            member->oclass == 0xD37 && member->state == 1) {
            member->owner = object;
            qcopy(member->pos, target);
            member->fF0 = 0.0f;
            member->fF4 = -1.5707965f;
            dx = target[0] - ((float *)func_L11_004417E8(object))[0];
            member->fF8 = func_00283248(dx, target[1] - ((float *)func_L11_004417E8(object))[1]);
            func_002833F0(member->rot, &member->fF0);
            func_PAL_L11_0043BE90(member, 0, 1);
            return 1;
        }
    } while ((short)*p++ >= 0);
    return 0;
}

