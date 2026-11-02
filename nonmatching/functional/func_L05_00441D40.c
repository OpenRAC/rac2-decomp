/* functional: medium. Near-miss draft, not byte-compared in the latest sweep: paths the captured calls never take are unproven. */
/* Retained reconstruction, USA v1.01.
 * 348/352 bytes, game -O2 -G0. Real C now covers the GP constant snapshots, private blocks, descriptor and actor lookups. Direct block fields change the base register form; separate block pointers give 352 bytes but still swap object/private GPRs and field-store scheduling. Mixed scalar SDA views remove the old broad GP screen.
 * No strict linked match.
 */
#include "common.h"

extern float D_L05_001B1A10 SDATA(D_L05_001B1A10);
extern float D_L05_001B1A14 SDATA(D_L05_001B1A14);
extern float D_L05_001B1A18 SDATA(D_L05_001B1A18);
extern float D_L05_001B1A4C SDATA(D_L05_001B1A4C);
extern float D_L05_001B1A50 SDATA(D_L05_001B1A50);
extern float D_L05_001B1A54 SDATA(D_L05_001B1A54);
extern float D_L05_001B1A70 SDATA(D_L05_001B1A70);
extern float D_L05_001B1A5C SDATA(D_L05_001B1A5C);
extern float D_L05_001B1A64 SDATA(D_L05_001B1A64);
extern float D_L05_001B1A6C SDATA(D_L05_001B1A6C);
extern float D_L05_001B1A58 SDATA(D_L05_001B1A58);
extern float D_L05_001B1AC0 SDATA(D_L05_001B1AC0);
extern int D_L05_001B1B20 SDATA(D_L05_001B1B20);
extern int D_L05_001B1B74 SDATA(D_L05_001B1B74);
extern int D_L05_001B1B78 SDATA(D_L05_001B1B78);
extern unsigned char *D_L05_001B1EC4 __attribute__((sda));
extern unsigned char *D_L05_001B251C __attribute__((sda));
extern void func_00282C88(void *);
extern void func_L05_00441EA0(void *);
extern void func_L00_002E54E0(float);
extern void func_L05_003D1E20(void);
extern void func_L05_00442720(void);

void func_L05_00441D40(unsigned char *object)
{
    unsigned char *state = *(unsigned char **)(object + 0x70);
    unsigned char *entry, *actor, *actor_state, *tail, *table, *actors;
    float angle;
    float first0, first4, first8;
    float f00, f04, f08, f74, f10, f14, f78, f0C;
    first0 = D_L05_001B1A10;
    first4 = D_L05_001B1A14;
    first8 = D_L05_001B1A18;
    *(float *)(state + 0) = first0;
    *(float *)(state + 4) = first4;
    *(float *)(state + 8) = first8;
    func_00282C88(state + 0x10);
    *(int *)(state + 0x44) = 0;
    *(int *)(state + 0x40) = 0;
    f00 = D_L05_001B1A4C;
    f04 = D_L05_001B1A50;
    f08 = D_L05_001B1A54;
    f74 = D_L05_001B1A70;
    f10 = D_L05_001B1A5C;
    f14 = D_L05_001B1A64;
    f78 = D_L05_001B1A6C;
    f0C = D_L05_001B1A58;
    state = *(unsigned char **)(object + 0x70);
    *(float *)(state + 0x50) = f00;
    *(float *)(state + 0x54) = f04;
    *(float *)(state + 0x58) = f08;
    *(float *)(state + 0xc4) = f74;
    *(float *)(state + 0x60) = f10;
    *(float *)(state + 0x64) = f14;
    *(float *)(state + 0xc8) = f78;
    *(float *)(state + 0x5c) = f0C;
    state[0x6F] = 0;
    *(int *)(state + 0xc0) = 0;
    *(short *)(state + 0x6c) = 0;
    *(int *)(state + 0x68) = 0;
    *(int *)(state + 0x74) = 0;
    state[0x6E] = 0;
    func_00282C88(state + 0xA0);
    func_00282C88(state + 0xB0);
    func_L05_00441EA0(object);
    func_L00_002E54E0(4096.0f);
    table = D_L05_001B1EC4;
    actors = D_L05_001B251C;
    tail = *(unsigned char **)(object + 0x70) + 0xD4;
    *(short *)(tail + 4) = 0;
    *(short *)(tail + 6) = 0;
    *(short *)(tail + 0xC) = 0;
    *(short *)(tail + 0x10) = 0;
    angle = D_L05_001B1AC0;
    angle *= 0.01666666753590107f;
    entry = table + *(s16 *)(object + 0x84) * 0x20;
    entry = *(unsigned char **)(entry + 0x1C);
    actor = actors + *(int *)(entry + 0x20) * 0x100;
    *(int *)(entry + 0x58) = 0;
    actor_state = *(unsigned char **)(actor + 0x68);
    *(int *)(actor_state + 0x214) = -1;
    *(float *)(actor_state + 0x38) = angle;
    *(short *)(object + 0x7E) = 0;
    D_L05_001B1B20 = 0;
    func_L05_003D1E20();
    D_L05_001B1B74 = 0;
    D_L05_001B1B78 = 0;
    func_L05_00442720();
}
