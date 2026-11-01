#include "include_asm.h"

typedef int Rac2TI128 __attribute__((mode(TI)));
typedef struct Rec_0032B598 {
    unsigned char prefix_00[0x50];
    float f_50;
    float f_54;
    float f_58;
    float f_5C;
    float f_60;
    float f_64;
    float f_68;
    float f_6C;
    float f_70;
    float f_74;
    float f_78;
    float f_7C;
    float f_80;
    float f_84;
    float f_88;
    float f_8C;
    float f_90;
    float f_94;
    int w_98;
    int w_9C;
    int w_A0;
    int w_A4;
    int w_A8;
    unsigned char tail_AC[4];
} Rec_0032B598;
extern Rec_0032B598 D_002351A0[];
extern char D_00189F00[];
extern float func_002A7878(float low, float high);
extern float func_002A78D8(float low, float high);
extern void func_00282C88(void *p);

/* Claims the first free record of the twelve 0xB0-byte records at D_002351A0, keeps the owner's
   pointer in it, copies two quadwords in and fills the drawn values. */
void func_PAL_0032CDB0(char *owner, char *src, int arg)
{
    Rec_0032B598 *base = D_002351A0;
    Rec_0032B598 *slot;
    int i;

    for (i = 0; i < 12; i++) {
        slot = base + i;
        if (slot->w_9C != 0)
            continue;
        slot->w_9C = (int)owner;
        *(Rac2TI128 *)((char *)slot + 0x20) = *(Rac2TI128 *)D_00189F00;
        *(Rac2TI128 *)((char *)slot + 0x40) = *(Rac2TI128 *)src;
        slot->f_50 = func_002A7878(-3.14159274f, 3.14159274f);
        slot->f_54 = func_002A7878(-3.14159274f, 3.14159274f);
        slot->f_58 = func_002A7878(-3.14159274f, 3.14159274f);
        slot->f_74 = func_002A7878(-3.14159274f, 3.14159274f);
        slot->f_78 = func_002A7878(-3.14159274f, 3.14159274f);
        slot->f_7C = func_002A7878(-3.14159274f, 3.14159274f);
        slot->f_5C = func_002A78D8(0.001f, 0.005f);
        slot->f_60 = func_002A78D8(0.001f, 0.005f);
        slot->f_64 = func_002A78D8(0.001f, 0.005f);
        slot->f_80 = func_002A78D8(0.001f, 0.005f);
        slot->f_84 = func_002A78D8(0.001f, 0.005f);
        slot->f_88 = func_002A78D8(0.001f, 0.005f);
        slot->f_68 = func_002A7878(3.25f, 4.75f);
        slot->f_6C = func_002A7878(3.25f, 4.75f);
        slot->f_70 = func_002A7878(3.25f, 4.75f);
        slot->f_8C = func_002A7878(3.25f, 4.75f);
        slot->f_90 = func_002A7878(3.25f, 4.75f);
        slot->f_94 = func_002A7878(3.25f, 4.75f);
        func_00282C88(slot);
        func_00282C88((char *)slot + 0x10);
        slot->w_A8 = 0;
        slot->w_A0 = arg;
        slot->w_98 = 17;
        slot->w_A4 = arg;
        break;
    }
}
