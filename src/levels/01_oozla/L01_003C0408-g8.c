/* func_L01_003C0408 (Oozla): steer a moby around its arena centre towards its target.
   Each mode-1 branch stores the height itself and `return distance` follows the inner
   if/else, so the return-value copy is a block of its own: the scheduler cannot hoist
   it over the height store, the height temporary takes $f0 as in retail, and the
   -1000 fallback's store (through $f1) is not cross-jumped with it.
   -frac2-hazard-labels keeps the forward branch into the division on its hazard nop
   (docs/build/compiler-notes.md, Labels on hazard nops). */
#include "common.h"

extern float func_00282E80(void *, void *);
extern float func_00283248(float, float);
extern float func_00283BE0(float, float);
extern float func_00282C48(float);
extern float func_00283B98(float, float);
extern float func_00283180(float);
extern float func_00283198(float);
extern void func_L01_003BFDC8(void *, int, int, int);
extern int func_L01_00321178(void *, void *);
extern void func_002B5278(void *, float);

/* 128-byte arena rows with a full 16-byte centre at +0x30. */
typedef struct {
    u8 prefix[0x30];
    float centre[4];
    u8 rest[0x40];
} L01ArenaRow;

/* The table pointer, read with retail's absolute macro load at each use
   (docs/build/compiler-notes.md, incomplete sda array read as element 0). */
extern L01ArenaRow *D_L01_001B264C[] __attribute__((sda));
extern float D_L01_001AFED0 __attribute__((sda));

/* The hero's position at +0x80; the owner stays an incomplete byte array. */
typedef struct {
    u8 prefix[0x80];
    float position[4];
} L01HeroPositionView;
extern u8 D_00189E20[];

float func_L01_003C0408(u8 *obj)
{
    u8 *s = *(u8 **)(obj + 0x68);
    float distance, angle, delta, magnitude;

    if (*(int *)(s + 0x124) == 1) {
        distance = func_00282E80(obj + 0x10, *(u8 **)(s + 0x120) + 0x10);
        angle = func_00283248(
            *(float *)(obj + 0x10) - D_L01_001B264C[0][*(int *)(s + 0x2CC)].centre[0],
            *(float *)(obj + 0x14) - D_L01_001B264C[0][*(int *)(s + 0x2CC)].centre[1]);
        delta = func_00283BE0(
            func_00283248(
                *(float *)(*(u8 **)(s + 0x120) + 0x10) - D_L01_001B264C[0][*(int *)(s + 0x2CC)].centre[0],
                *(float *)(*(u8 **)(s + 0x120) + 0x14) - D_L01_001B264C[0][*(int *)(s + 0x2CC)].centre[1]),
            angle);
        magnitude = func_00282C48(delta);
        if (distance > *(float *)(s + 0x2EC)) {
            if (obj[0x43] != s[0x2E1])
                func_L01_003BFDC8(obj, s[0x2E1], 0, 20);
            if (magnitude < D_L01_001AFED0 * 0.017453294f) {
                qcopy(s + 0x2A0, *(u8 **)(s + 0x120) + 0x10);
            } else {
                delta = delta / magnitude;
                delta = delta * 0.087266474f;
                qcopy(s + 0x2A0, D_L01_001B264C[0][*(int *)(s + 0x2CC)].centre);
                *(float *)(s + 0x2A0) += func_00283180(func_00283B98(angle, delta)) * 38.0f;
                *(float *)(s + 0x2A4) += func_00283198(func_00283B98(angle, delta)) * 38.0f;
            }
            func_L01_00321178(obj, s + 0x2A0);
            *(float *)(obj + 0x18) = *(float *)(s + 0x2E8);
        } else {
            if (obj[0x43] != s[0x2E2] && obj[0x95] != 3)
                func_L01_003BFDC8(obj, s[0x2E2], 0, 20);
            func_002B5278(obj, func_00283248(*(float *)(*(u8 **)(s + 0x120) + 0x10) - *(float *)(obj + 0x10),
                                             *(float *)(*(u8 **)(s + 0x120) + 0x14) - *(float *)(obj + 0x14)));
            *(float *)(obj + 0x18) = *(float *)(s + 0x2E8);
        }
        return distance;
    }
    if (obj[0x43] != s[0x2E2] && obj[0x95] != 3)
        func_L01_003BFDC8(obj, s[0x2E2], 0, 20);
    func_002B5278(obj, func_00283248(((L01HeroPositionView *)D_00189E20)->position[0] - *(float *)(obj + 0x10),
                                     ((L01HeroPositionView *)D_00189E20)->position[1] - *(float *)(obj + 0x14)));
    *(float *)(obj + 0x18) = *(float *)(s + 0x2E8);
    return -1000.0f;
}
