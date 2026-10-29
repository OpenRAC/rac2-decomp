/* Nonmatching: US/US2/PAL 768/764 bytes, 0/1 each. Default profile.
 * Six checks, including the final retained-profile confirmation. The initial
 * 764-byte draft incorrectly skipped drawing for an inactive object and is
 * INVALID: retail skips physics but still reaches rotation and registration.
 * This corrected form preserves that flow. Narrow no-cse-follow-jumps ties;
 * GCSE off756 loses the needed saved position-pointer lifetime and is rejected.
 * Remaining: collision scratch-address copy, impulse/query saved-register
 * priorities, and metadata/call scheduling. Reopen on a new source-lifetime
 * or narrow compiler witness; no fake interface or memory-order controls.
 * Both Impact objects are40 bytes, separately aligned16 (natural stack
 * padding). 261F8 copies40 via LQ0/LQ10/LD20; A8E20 reads float+0x24.
 * Preserve the genuinely uninitialized field24; do not shorten the objects
 * or add an invented zero. Destination and impulse vectors are16 bytes each.
 * The explosion constructor returns an object pointer and has eight32-bit
 * GPR arguments, oneF32 and two32-bit stack words (retail LW at+C0/C8).
 * Physical callback30:00416FB0 is canonical func_L13_0040DE50, void(ptr).
 */
#include "common.h"

/* Both the ray walker (two LQ plus LD+0x20) and A8E20 consume40 bytes.
 * Field24 is genuinely not initialized by these retail call sites. */
typedef struct {
    float direction[4];
    void *owner;
    int mask;
    unsigned char kind,mode;
    unsigned short objectClass;
    float damage;
    int enabled;
    float field24;
} Impact;
typedef char ImpactExtentCheck[sizeof(Impact)==40 ? 1 : -1];
typedef struct {
    float velocity[4];
    void *owner;
    float radius;
    unsigned char reserved18[0xC];
    int age;
} MovingState;
extern void *D_L30_001C0218 NOT_SDA;
extern float D_L30_001B1F04[] NOT_SDA;
extern float D_L30_001B1F04_gp[] SDATA(D_L30_001B1F04);
extern int func_002A8C28(void *,float,void *,int,float,float,int,int,int);
extern void func_002A7750(void *,int,int);
extern void func_00282CC0(void *,void *,void *);
extern void func_002A8C00(Impact *,void *,int,float,float *);
extern int func_002761F8(void *,void *,int,void *,Impact *);
extern int func_00277258(void *,int,void *,float);
extern void func_00282D30(void *,void *,float);
extern int func_00277F48(void *,float,int,void *,Impact *);
extern void func_00282C88(void *);
extern void *func_L16_00406080(void *,int,int,int,int,int,int,int,float,int,int);
extern void func_0029F338(void *);
extern void func_002ACEC0(void *,void *,void *,float);
extern void func_L13_0040DE50(void *);
extern void func_L08_002F2D10(void (*)(void *),void *);

void func_L30_00416A88(unsigned char *object)
{
    float destination[4] __attribute__((aligned(16)));
    Impact ray __attribute__((aligned(16)));
    float impulse[4] __attribute__((aligned(16)));
    Impact sweep __attribute__((aligned(16)));
    MovingState *state=*(MovingState **)(object+0x68);
    if(!object[0xBC]) {
        if(++state->age>240 && !object[0xBC]) {
            func_002A8C28(object,0.6f,object+0x10,0x10003,state->radius,0.0f,0,1,0);
            func_002A7750(object,1,-1);
        }
        switch(object[0x20]) {
        case 0:
            func_00282CC0(destination,object+0x10,state->velocity);
            func_002A8C00(&ray,object,3,state->radius,state->velocity);
            ray.objectClass=*(unsigned short *)(object+0xAA);
            if(func_002761F8(object+0x10,destination,0,object,&ray) ||
               func_00277258(object+0x10,0,object,0.3f)) {
                void *hit=D_L30_001C0218;
                float *kick=impulse;
                float strength;
                if(hit) {
                    if(hit==state->owner) goto move;
                    qcopy(kick,state->velocity);
                    strength=1.5f;
                } else {
                    qcopy(kick,state->velocity);
                    strength=3.0f;
                }
                func_00282D30(kick,kick,strength);
                kick[2]=1.0f;
                kick[3]=5627.9248046875f;
                func_002A8C00(&sweep,object,0x10003,state->radius,kick);
                sweep.mode=1;
                sweep.objectClass=*(unsigned short *)(object+0xAA);
                sweep.kind=0;
                func_00277F48(object+0x10,0.6f,0,object,&sweep);
                if(!object[0xBC]) func_002A7750(object,1,-1);
                return;
            }
        move:
            if(!object[0xBC]) qcopy(object+0x10,destination);
            /* These real retail calls keep the unused scratch-vector updates. */
            func_00282D30(impulse,state->velocity,-0.5f);
            func_00282C88(sweep.direction);
            break;
        case 1:
            func_L16_00406080(object+0x10,0,25,20,20,20,0,0,0.25f,1,0);
            func_0029F338(object);
            return;
        }
    }
    func_002ACEC0(object+0xE0,object+0xE0,object+0xD0,D_L30_001B1F04_gp[0]*0.01745329424738884f);
    func_002ACEC0(object+0xC0,object+0xC0,object+0xD0,D_L30_001B1F04_gp[0]*0.01745329424738884f);
    func_L08_002F2D10(func_L13_0040DE50,object);
}
