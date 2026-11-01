#include "include_asm.h"

#include "common.h"
struct L02ListObj {
    char pad0[0x34];
    unsigned short f34;
    char pad1[0x32];
    void *f68;
};
struct L02ListSub {
    char pad0[4];
    int f04;
    int f08;
    char pad1[8];
    int f14;
    int f18;
    struct L02ListObj *f1C;
};
struct L02TurnSub {
    char pad0[0x0C];
    float f0C;
    float f10;
    int f14;
    void *f18;
};
struct L02TurnObj {
    char pad0[0x10];
    char pad1[0x58];
    struct L02TurnSub *f68;
};
struct L02SpinSub {
    char pad0[4];
    float f04;
    int f08;
    float f0C;
    void *f10;
};
struct L02SpinObj {
    char pad0[0x10];
    char pad1[0x58];
    struct L02SpinSub *f68;
};

/* Measured pointer-list starts are accessed without guessing their capacities. */
void func_PAL_L02_003C85E0(char *arg)
{
    char *parent = *(char **)(arg + 0x68);
    struct L02ListObj **list;
    struct L02TurnObj **turn;
    struct L02SpinObj **spin;
    int i;
    int j;

    (*(int *)(parent + 0x130)) = 0x3C;
    i = 0;
    if ((*(int *)(parent + 0x118)) > 0) {
        list = (struct L02ListObj **)(parent + 0xC0);
        do {
            struct L02ListObj *obj = list[i];
            struct L02ListSub *sub = obj->f68;

            sub->f04 = 0;
            sub->f14 = sub->f18;
            sub->f08 = 0;
            if (sub->f1C != 0)
                sub->f1C->f34 |= 0x41;
            list[i]->f34 &= 0xFFBE;
        } while (++i < (*(int *)(parent + 0x118)));
    }
    j = 0;
    if ((*(int *)(parent + 0x110)) > 0) {
        turn = (struct L02TurnObj **)(parent + 0x20);
        do {
            struct L02TurnObj *obj = turn[j];
            struct L02TurnSub *sub = obj->f68;
            float angle;

            sub->f14 = 0;
            (*(int *)(parent + 0x11C)) = 0;
            angle = (float)(*(int *)(parent + 8)) * (0.020000001f);
            sub->f0C = -1.0f;
            sub->f10 = angle;
            qcopy((char *)turn[j] + 0x10, (char *)sub->f18 + 0x10);
        } while (++j < (*(int *)(parent + 0x110)));
    }
    j = 0;
    if ((*(int *)(parent + 0x114)) > 0) {
        spin = (struct L02SpinObj **)(parent + 0x70);
        do {
            struct L02SpinObj *obj = spin[j];
            struct L02SpinSub *sub = obj->f68;

            sub->f08 = 0;
            sub->f04 = 0.040000003f;
            sub->f0C = -1.0f;
            qcopy((char *)spin[j] + 0x10, (char *)sub->f10 + 0x10);
        } while (++j < (*(int *)(parent + 0x114)));
    }
}
