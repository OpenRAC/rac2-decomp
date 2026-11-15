#include "common.h"

/* func_L12_00407DE8 is a unit of its own: it needs the opt-in quadword-copy profile and its
   scheduling barrier (-frac2-qcopy -frac2-qcopy-barrier, config/cflags.txt). */

typedef int Quadword __attribute__((mode(TI)));
extern int func_002A8C28(void *, float, void *, int, float, float, int, int, int);
extern void func_L12_0031E1D0(void *, int, int);
extern void func_00282CC0(void *, void *, void *);
extern void func_002A8C00(void *, void *, int, void *, float);
extern int func_002761F8(void *, void *, int, void *, void *);
extern void func_00282D30(void *, void *, float);
extern int func_00277F48(void *, int, void *, void *, float);
extern void func_0032C700(void *, int, int, int, int, int, int, int, int, int, int, int, float, float);
extern void func_0029F338(void *);
extern void ref_L12_00407DE8_00(void *, void *);
extern void func_L12_004081F8(void *);
extern char D_L12_001C0258[];   /* collision result; +0x0 the object hit */
typedef struct { u8 pad[24]; u8 mode; u8 active; u16 owner; u8 rest[20]; } Query __attribute__((aligned(16)));
/* Projectile update (the func_L16_004051A8 family): expires after 240 frames, moves along its
 * velocity and, on a hit, unless the object hit is the one its state records at +0x10, sends a
 * blast request (velocity scaled 1.5, or 3 with no object hit) through func_00277F48. Both blast
 * branches are written out in full; cross-jumping merges their common tails, as in retail. */
/* Updates a flying blast shot: it moves, hits things, damages them and disappears after a short time. */
void func_L12_00407DE8(u8 *obj) {
    u8 *state=*(u8 **)(obj+0x68);
    float next[4];
    Query hit;
    float impact[4];
    Query hit2;
    if (++*(int *)(state+0x24)>240) {
        SweepCollisionFromObject(obj,0.6f,obj+0x10,0x10001,*(float *)(state+0x14),0.0f,0,1,0);
        func_L12_0031E1D0(obj,1,-1);
    }
    switch(obj[0x20]) {
    case 0:
        FastVecAdd(next,obj+0x10,state);
        make_hit_descriptor(&hit,obj,1,state,*(float *)(state+0x14));
        hit.owner=*(u16 *)(obj+0xAA);
        if (CollLine(obj+0x10,next,0,obj,&hit)) {
            if (*(void **)D_L12_001C0258) {
                if (*(void **)D_L12_001C0258!=*(void **)(state+0x10)) {
                    *(Quadword *)impact=*(Quadword *)state;
                    FastVecScale(impact,impact,1.5f);
                    impact[2]=1.0f;
                    impact[3]=5627.9248046875f;
                    make_hit_descriptor(&hit2,obj,0x10001,impact,*(float *)(state+0x14));
                    hit2.active=1;
                    hit2.owner=*(u16 *)(obj+0xAA);
                    hit2.mode=0;
                    ProcessCollisionHit(obj+0x10,0,obj,&hit2,0.6f);
                    func_L12_0031E1D0(obj,1,-1);
                    return;
                }
            } else {
                *(Quadword *)impact=*(Quadword *)state;
                FastVecScale(impact,impact,3.0f);
                impact[2]=1.0f;
                impact[3]=5627.9248046875f;
                make_hit_descriptor(&hit2,obj,0x10001,impact,*(float *)(state+0x14));
                hit2.active=1;
                hit2.owner=*(u16 *)(obj+0xAA);
                hit2.mode=0;
                ProcessCollisionHit(obj+0x10,0,obj,&hit2,0.6f);
                func_L12_0031E1D0(obj,1,-1);
                return;
            }
        }
        *(Quadword *)(obj+0x10)=*(Quadword *)next;
        FastVecScale(impact,state,-0.5f);
        break;
    case 1:
        SpawnExplosion(obj+0x10,0,3,3,3,3,3,0,0,0,0,0,0.75f,20.0f);
        MarkMobySpawned(obj);
        return;
    }
    ref_L12_00407DE8_00(DrawBlastProjectileGlow,obj);
}
