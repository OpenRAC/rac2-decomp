/* Complete C near miss; NOT linked and no exact-C credit.
 * Measured source unit: src/levels/shared/L00_002B36E0.c
 * Game profile: -O2 -G0 -ffunction-sections -frac2-qcopy -frac2-qcopy-barrier
 * Compiled/retail bytes: 544/544. US: 0/24; US2: 0/24; PAL: ABSENT.
 * Residual and reopening condition: Directional-bit temporary registers and vector-history copy scheduling remain different. A cached real history index removes the extra index reload; qcopy/barrier and direct TI copies were measured. Reopen with independent alias/lifetime evidence for these two blocks.
 * Field views describe only measured prefixes, not complete game-object extents.
 */

#include "common.h"
typedef int Quad __attribute__((mode(TI)));
typedef struct {
    char prefix[0x108]; float x, y;
    char gap[0x90]; unsigned int held;
    char gap2[0xC]; int buttons;
} ControllerView;
typedef struct {
    char prefix[0x1454]; short timer;
    char gap[0x93A]; Quad positions[32];
    char gap2[0x20]; float input[4];
    char gap3[0x70]; Quad previous;
    char gap4[0x254]; int mode;
    char gap5[0x2B]; unsigned char status;
    char gap6[0x78]; float heights[32];
    int heightIndex, heightCount, positionIndex, positionCount;
    char gap7[0xEC]; float speed, otherSpeed;
} HeroLoopView;
extern char D_00189E20[];
extern char D_00138180[];
extern int func_00282978(short *timer);
extern int func_L00_002D3400(void);
extern float func_L00_002B3900(void);
extern float func_00282E20(void *vector);
extern void func_L00_002BA7D8(void);
extern void func_00283410(void *out, void *vector);
extern void func_00283388(void *out);
extern void func_00283698(void *out, void *in);
extern void func_L00_002B32F8(void);
extern void func_L00_002C2DE8(void);
extern void func_L00_002C30B0(void);

void func_L00_002B36E0(void)
{
    HeroLoopView *hero;
    int buttons;
    int index;
    int dx;
    int dy;
    int forward, right, left, backward;
    qcopy(D_00189E20 + 0x2030, D_00189E20 + 0x80);
    if (((ControllerView *)D_00138180)->held & 3) {
        if (((HeroLoopView *)D_00189E20)->timer <= 0)
            ((HeroLoopView *)D_00189E20)->timer = 1;
    } else {
        func_00282978(&((HeroLoopView *)D_00189E20)->timer);
    }
    hero = (HeroLoopView *)D_00189E20;
    if (hero->mode == 16)
        hero->timer = 0;
    hero->status = func_L00_002D3400();
    hero->input[0] = ((ControllerView *)D_00138180)->x;
    hero->input[1] = ((ControllerView *)D_00138180)->y;
    *(int *)(D_00189E20 + 0x270) = 0;
    hero->otherSpeed = func_L00_002B3900();
    if (func_00282E20(hero->input) < 0.25f) {
        buttons = ((ControllerView *)D_00138180)->buttons;
        forward = (buttons >> 12) & 1;
        right = (buttons >> 13) & 1;
        left = (buttons >> 15) & 1;
        backward = (buttons >> 14) & 1;
        dx = right - left;
        dy = backward - forward;
        hero->input[0] = (float)dx;
        hero->input[1] = (float)dy;
    }
    hero->speed = func_L00_002B3900();
    func_L00_002BA7D8();
    hero->heights[hero->heightIndex] = *(float *)(D_00189E20 + 0x98);
    hero->heightIndex = (hero->heightIndex + 1) % 32;
    if (++hero->heightCount > 32)
        hero->heightCount = 32;
    index = hero->positionIndex;
    hero->positions[index] = *(Quad *)(D_00189E20 + 0x80);
    hero->positionIndex = (index + 1) % 32;
    if (++hero->positionCount > 32)
        hero->positionCount = 32;
    func_00283410(D_00189E20, D_00189E20 + 0x90);
    func_00283388(D_00189E20 + 0x40);
    func_00283698(D_00189E20 + 0x40, D_00189E20);
    func_L00_002B32F8();
    func_L00_002C2DE8();
    func_L00_002C30B0();
}
