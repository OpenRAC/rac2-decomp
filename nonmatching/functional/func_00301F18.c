/* functional: medium. Near-miss draft of retail size with the same frame: differences are allocation and scheduling, with some block order; paths the captured calls never take are unproven. */
/* 31 October 2026: decomp-permuter (asm passes off) matches 28/28 with one change, the else
   branch's first copy written through the address of `state`:
       char **slot = &state; qcopy(&position, *slot);
   Retail keeps `state` in $s2 throughout, so this models no real memory traffic; it is an
   artefact, not used. Natural spellings measured 0/28: `state + 0`, ParticleVector casts and
   indexing, a `src` local for both copies, re-reading object + 0x68. The real source must
   reorder the same allocation; this branch is where to look. */
/* Retained near miss (M4, 26 October 2026); not linked.
 * Unit: src/game/00301F18-qcopy.c, profile -O2 -G0 -ffunction-sections -frac2-qcopy -frac2-qcopy-barrier.
 * 900/900 bytes, 0/28 places: only the &position/&angles address pseudos take $s7/$fp the other way
 * round (8 words). Closed here: the parent-state test as an if/else-if chain (the `||` form folds into a
 * range check) and the found-parent arm first. Declaring angles before position gives retail's
 * registers but swaps the two stack slots (4 words). Queued for the permuter.
 */
#include "common.h"

typedef int ParticleWord __attribute__((mode(TI)));
typedef union { ParticleWord word; float f[4]; } ParticleVector;
typedef struct { int a,b,c,d; } __attribute__((aligned(16))) Quad16;
extern void func_00282CF0(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern int func_00277258(void *, int, void *, float);
extern char ref_00305798_00[];

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
    if (*(char **)(state+0x5c)) {
        func_002AD470(object,*(char **)(state+0x5c),state,state+0x10,&position,&angles);
    } else {
        qcopy(&position, state);
        qcopy(&angles, state+0x10);
    }
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
            if (parent) {
                qcopy(state+0x20, parent+0x10);
                *(char **)(state+0x5c)=0;
            } else {
                func_00282C88((ParticleWord *)(state+0x20));
                *(char **)(state+0x5c)=0;
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
    func_00282D30(object+0x10,&anchorMatrix[2],radius);
    func_00282D30(&offset,object+0xc0,lift);
    func_00282CC0(object+0x10,object+0x10,&offset);
    func_00282CC0(object+0x10,object+0x10,&position);
    if (outPosition) qcopy(outPosition, &position);
    if (outAngles) qcopy(outAngles, &angles);
}
