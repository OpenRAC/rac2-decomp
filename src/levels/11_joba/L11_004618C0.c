#include "include_asm.h"
#include "names.h"

/* Defined in L11_004618C0-g8.c. */

/* func_L11_0046D660 is in L11_004618C0-f7-g8.c. */

extern void func_00281EB8(void *a0, int a1, unsigned int a2, int a3, float f12, float f13,
                          float f14);

extern float func_002A7940(void);

extern int func_00283CF0(float f12);

/* Emits two coloured passes over each 16-byte entry. */
void func_L11_004701A0(char *moby) {
    char *vars = *(char **)(moby + 0x68);
    float baseSize = 0.2f;
    float scaledSize;
    unsigned int colorA, colorB;
    int i;
    float randomAngle;

    colorA = 0x106060;
    colorB = 0x808080;
    colorA |= FloatToInt(*(float *)(vars + 0x18) * 63.0f) << 24;
    colorB |= FloatToInt(*(float *)(vars + 0x18) * 128.0f) << 24;
    for (i = 0; i < *(int *)(vars + 0x10); i++) {
        randomAngle = RandomAngle();
        DrawBillboardQuad_00281EB8(vars + 0x20 + i * 0x10, 0x31, colorA, 1, 0.2f, 0.08f, randomAngle);
        scaledSize = baseSize * 0.4f;
        randomAngle = RandomAngle();
        DrawBillboardQuad_00281EB8(vars + 0x20 + i * 0x10, 0x31, colorB, 1, scaledSize, 0.08f, randomAngle);
    }
}

/* func_L11_004702F0 is in L11_004618C0-state-g8.c ($gp height-control reads). */

/* Wakes a moby from its first state and makes it visible and active. */
void func_L11_00472DE8(unsigned char *moby) {
    unsigned short flags;

    if (moby[0x20] != 0)
        return;
    flags = *(unsigned short *)(moby + 0x34);
    moby[0x20] = 1;
    *(unsigned short *)(moby + 0x34) = flags | 0x41;
}

/* func_L11_00472E10 lives in L11_00472E10-g8.c. */

/* Defined in L11_00474920-g8.c. */

/* func_L11_0047A310 is in L11_004618C0-group-g8.c ($gp moby table reads). */

extern char *r1_D_L08_00167680;

/* rac1-decomp src/overlays/shared/vendor_002D3DF8.c: func_L08_00315068 */
/* Sets a flag byte in a shared table used by the overlay code. */
void func_L11_004885A0(void) {
    r1_D_L08_00167680[0x88] = 1;
}

extern void func_803004A8(void *);
extern void func_80300D98(void *, void *);
extern void func_80301000(void *, void *);

/* Fills a moby's effect data blocks with default values and resets it. */
void func_L11_004885B8(unsigned char *moby) {
    unsigned char buf[0x40];
    unsigned char *innerBlock;

    *(int *)(*(unsigned char **)(moby + 0x70) + 0xC0) = 4;
    innerBlock = *(unsigned char **)(moby + 0x70) + 0x30;
    *(float *)(innerBlock + 0x20) = 0.05f;
    *(float *)(innerBlock + 0x24) = 0.3f;
    *(float *)(innerBlock + 0x28) = 1.0f;
    *(unsigned short *)(innerBlock + 0x2C) = 1;
    func_803004A8(innerBlock);
    {
        unsigned char *outerBlock = *(unsigned char **)(moby + 0x70);

        *(float *)(outerBlock + 0x10) = 0.3f;
        *(float *)(outerBlock + 0x14) = 0.3f;
        *(float *)(outerBlock + 0x18) = 1.0f;
        *(unsigned short *)(outerBlock + 0x1C) = 1;
        func_803004A8(outerBlock);
    }
    func_80300D98(buf, moby + 0x40);
    func_80301000(moby, buf);
    *(unsigned short *)(moby + 0x7E) = 0;
}
