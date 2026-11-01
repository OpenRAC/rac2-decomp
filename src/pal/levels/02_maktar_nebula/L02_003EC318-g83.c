#include "include_asm.h"

typedef int TI128 __attribute__((mode(TI)));
extern unsigned char *D_L02_001B359C[3] __attribute__((sda));
extern char D_00189E20[];
extern float D_L02_001B0C10[2];
extern float D_L02_001B0C18 __attribute__((sda));
extern float func_00283248(float, float);
extern float func_00283C80(float, float);
extern float func_00283B98(float, float);
extern void func_002AF000(void *, float, float, float);
extern void func_00282CF0(void *, void *, void *);
extern void func_002AC9F8(float *, float);
extern void func_00282CC0(void *, void *, void *);
extern float func_00282DB0(void *, void *);

/* Steers the point at +0x10 of the actor's private data. The velocity comes from the actor's
   heading (turned by pi when the hero is within a quarter turn of it, as seen from the actor) and
   a tilt chosen by the class of the entity the actor follows (0x9C8 or not). The point moves by
   the velocity's difference to it, limited in length, and the entity's own point moves by the
   new one. When the new point and the flat vector from the actor to the entity make a positive
   product, the point is replaced by the velocity and the result is 1. */
int func_PAL_L02_003ED2A0(char *arg0) {
    char *state = *(char **)(arg0 + 0x68);
    unsigned char *ent = D_L02_001B359C[0] + (*(int *)state << 8);
    float tilt;
    float heading;
    float v0[4];
    float v1[4];
    float v2[4];
    char *pos;
    unsigned char *epos;
    char *g;

    if (*(short *)(ent + 0xAA) == 0x9C8)
        tilt = D_L02_001B0C10[1];
    else
        tilt = D_L02_001B0C10[0];
    heading = *(float *)(arg0 + 0xF8);
    g = D_00189E20;
    if (func_00283C80(*(float *)(arg0 + 0xF8),
                      func_00283248(*(float *)(g + 0x80) - *(float *)(arg0 + 0x10),
                                    *(float *)(g + 0x84) - *(float *)(arg0 + 0x14))) < 1.5707964f)
        heading = func_00283B98(heading, 3.1415927f);
    pos = state + 0x10;
    func_002AF000(v0, *(float *)(state + 0x44), heading, tilt * 0.01745329424738884f);
    epos = ent + 0x10;
    func_00282CF0(v1, v0, pos);
    func_002AC9F8(v1, D_L02_001B0C18 * 0.00040000002f);
    func_00282CC0(pos, pos, v1);
    func_00282CC0(epos, epos, pos);
    func_00282CF0(v2, epos, arg0 + 0x10);
    v2[2] = 0;
    if (0.0f < func_00282DB0(pos, v2)) {
        *(TI128 *)pos = *(TI128 *)v0;
        return 1;
    }
    return 0;
}
