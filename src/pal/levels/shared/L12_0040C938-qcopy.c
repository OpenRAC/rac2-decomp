#include "include_asm.h"

#include "common.h"
typedef int Quadword __attribute__((mode(TI)));
extern int coll_sweep_from_object(void *, float, void *, int, float, float, int, int, int);
extern void moby_set_state(void *, int, int);
extern void FastVecAdd(void *, void *, void *);
extern void make_hit_descriptor(void *, void *, int, void *, float);
extern int CollLine(void *, void *, int, void *, void *);
extern void FastVecScale(void *, void *, float);
extern int coll_process_hit(void *, int, void *, void *, float);
extern void func_PAL_L00_003FB330(void *, int, int, int, int, int, int, int, int, int, int, int, float, float);
extern void moby_mark_spawned(void *);
extern void ref_L12_00407DE8_00(void *, void *);
extern void blast_projectile_draw_glow(void *);
extern char D_L12_001C0258[];
typedef struct { u8 pad[24]; u8 mode; u8 active; u16 owner; u8 rest[20]; } Query __attribute__((aligned(16)));

/* Projectile update (the func_L16_004051A8 family): expires after 240 frames, moves along its
 * velocity and, on a hit, unless the object hit is the one its state records at +0x10, sends a
 * blast request (velocity scaled 1.5, or 3 with no object hit) through func_00277F48. Both blast
 * branches are written out in full; cross-jumping merges their common tails, as in retail. */
void func_PAL_L12_0040C938(u8 *obj) {
    u8 *state=*(u8 **)(obj+0x68);
    float next[4];
    Query hit;
    float impact[4];
    Query hit2;
    if (++*(int *)(state+0x24)>240) {
        coll_sweep_from_object(obj,0.6f,obj+0x10,0x10001,*(float *)(state+0x14),0.0f,0,1,0);
        moby_set_state(obj,1,-1);
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
                    coll_process_hit(obj+0x10,0,obj,&hit2,0.6f);
                    moby_set_state(obj,1,-1);
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
                coll_process_hit(obj+0x10,0,obj,&hit2,0.6f);
                moby_set_state(obj,1,-1);
                return;
            }
        }
        *(Quadword *)(obj+0x10)=*(Quadword *)next;
        FastVecScale(impact,state,-0.5f);
        break;
    case 1:
        func_PAL_L00_003FB330(obj+0x10,0,3,3,3,3,3,0,0,0,0,0,0.75f,20.0f);
        moby_mark_spawned(obj);
        return;
    }
    ref_L12_00407DE8_00(blast_projectile_draw_glow,obj);
}
