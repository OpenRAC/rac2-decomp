#include "common.h"

typedef struct {
    char pad0[0x14];
    unsigned short unk14;
    unsigned short unk16;
    char pad18[7];
    unsigned char unk1F;
} Record002F0FA0;

extern Record002F0FA0 *ref_002F0FA0_00;
extern Record002F0FA0 *ref_002F0FA0_01;
extern int ref_002F0FA0_02 __attribute__((nosda));
extern int ref_002F0FA0_03;
extern int ref_002F0FA0_04;
extern int ref_002F0FA0_05;
extern int ref_002F0FA0_06 __attribute__((sda));

void func_002F0FA0(void)
{
    Record002F0FA0 *p = ref_002F0FA0_00;
    int v = ref_002F0FA0_02;
    Record002F0FA0 *end = ref_002F0FA0_01;

    ref_002F0FA0_03 = v;
    ref_002F0FA0_04 = 0;
    ref_002F0FA0_05 = 0;
    ref_002F0FA0_06 = 0;

    if (p == end)
        return;

    do {
        p->unk16 = 0;
        p->unk14 = 0xFFFF;
        p->unk1F = 0xFF;
        p++;
    } while (p != ref_002F0FA0_01);
}
