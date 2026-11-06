#include "common.h"

/* -frac2-qcopy -frac2-qcopy-barrier: the grouped lq/sq copies with their barrier.
   `slot` holds the parent link address, then the final add's origin. */

typedef int ParticleWord __attribute__((mode(TI)));
typedef union { ParticleWord word; float f[4]; } ParticleVector;
extern void func_00282CC0(void *, void *, void *);
extern int func_00277258(void *, int, void *, float);
extern int func_002AD470(void *, void *, void *, void *, void *, void *);
extern s32 func_002AD0B0(u8 *);
extern void func_00282C88(ParticleWord *);
extern float func_00283B98(float, float);
extern float func_00283BE0(float, float);
extern void func_002833F0(void *, void *);
extern void func_00283738(void *, void *, void *);
extern void func_00282D30(void *, void *, float);

/* Update the pickup's anchor, turn it, and compose the visible orientation. */
void func_00301F18(u8 *object, void *outPosition, void *outAngles)
{
    char *state=*(char **)(object+0x68);
    ParticleVector spinMatrix[3], anchorMatrix[3];
    ParticleVector rotation, offset, position, angles;
    char *parent;
    float step, tilt, radius, lift;
    int detach;
    u8 *origin; char *slot;
    if (*(char **)(state+0x5c)) {
        func_002AD470(object,*(char **)(state+0x5c),state,state+0x10,&position,&angles);
    } else {
        qcopy(&position, state);
        qcopy(&angles, state+0x10);
    }
    origin = object+0x10;
    do {
    if (object[0x20]==3 && *(char **)(state+0x5c)) {
        parent=*(char **)(state+0x5c);
        detach=0;
        if (*(u8 *)(parent+0x20)==254) detach=1;
        else if (*(u8 *)(parent+0x20)==253) detach=1;
        else if (!func_00277258(object+0x10,0x22,object,0.25f)) detach=1;
        if (detach) {
            object[0x20]=1;
            func_00282C88((ParticleWord *)(state+0x30));
            *(float *)(state+0x3c)=1.0f;
            parent=(char *)func_002AD0B0((u8 *)*(char **)(state+0x5c));
            slot = state+0x5c;
            if (parent) {
                qcopy(state+0x20, parent+0x10);
                *(char **)slot=0;
            } else {
                func_00282C88((ParticleWord *)(state+0x20));
                *(char **)slot=0;
            }
        }
    }
    switch (*(short *)(object+0xaa)) {
    case 13: step=0.04f; tilt=-0.25f; radius=0.04875f; lift=0.325f; break;
    case 14: step=0.03f; tilt=-0.5f; radius=0.0245f; lift=0.35f; break;
    case 15: step=0.025f; tilt=-0.4f; radius=0.05625f; lift=0.375f; break;
    default: step=0.0175f; tilt=-0.35f; radius=0.135f; lift=0.3f; break;
    }
    if (*(u8 *)(state+0x55)&1) {
        *(float *)(state+0x50)=func_00283B98(*(float *)(state+0x50),step);
        *(float *)(state+0x58)=func_00283B98(*(float *)(state+0x58),-0.0125f);
    } else {
        *(float *)(state+0x50)=func_00283BE0(*(float *)(state+0x50),step);
        *(float *)(state+0x58)=func_00283BE0(*(float *)(state+0x58),-0.0125f);
    }
    qcopy(&rotation, state+0x50);
    rotation.f[1]=tilt;
    func_002833F0(spinMatrix,&rotation);
    func_002833F0(anchorMatrix,&angles);
    func_00283738(object+0xc0,anchorMatrix,spinMatrix);
    func_00282D30(origin,&anchorMatrix[2],radius);
    func_00282D30(&offset,object+0xc0,lift);
    func_00282CC0(origin,origin,&offset);
    } while (0);
    slot = (char *)origin; func_00282CC0(slot,slot,&position);
    if (outPosition) qcopy(outPosition, &position);
    if (outAngles) qcopy(outAngles, &angles);
}
