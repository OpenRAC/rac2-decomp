/* Spawns a bolt effect moby (class 0xCF7) from a position and velocity: the state block holds its
   frame count and rate, its fade, and a slot from a three-way counter; mode 1 aims it at the camera,
   mode 2 first steps it once and flags a hit. Needs -g (pre-div.s nop pair). */
#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
extern int func_002B4038(int,int);
extern char *func_0029EFD0(int);
extern void func_003001E0(void *,void *,void *);
extern int func_00283CF0(float);
extern float func_00283CE0(int);
extern char *func_L00_0032A088(int,int);
extern void func_002AFFD8(void *,void *,int);
extern void func_00282D30(void *,void *,float);
extern void func_L00_003F51A0(char *,char *);
extern void func_L00_003F5F90(char *);
extern float func_00282DF0(void *);
extern void func_00282F20(void *,void *,float);
extern void func_00282CC0(void *,void *,void *);
extern int func_L00_003F5238(char *,char *);
extern unsigned char D_0013957F[];
typedef struct { char prefix[0x50]; float speed; char gap[0x1c]; float distance; char rest[0x6c]; } Tuning;
extern Tuning D_L00_00262570[];
extern unsigned short D_L00_001B0938 __attribute__((sda));
extern unsigned int D_L00_001B0934 __attribute__((sda));
extern char D_L00_001B8DC0[];
/* Only the measured header fields are viewed; this is not a whole-object size. */
typedef struct { char prefix[0x30]; unsigned char stamp,enabled; short tag; } HeaderView;
typedef struct {
    char pad00[0x10];
    int frames;
    float rate;
    short slot, id;
    char *target;
    short age, fadeFrames;
    float fadeRate;
    int mode;
    char pad2C[4];
    TI128 velocity, origin;
} BoltState;

char *func_L00_003F4C68(char *position,char *velocity,int id,int mode)
{
    TI128 direction, previous;
    char *object,*location;
    BoltState *state;
    float frames;
    HeaderView *header;
    unsigned char stamp;
    int next;
    if (id == -1 || func_002B4038(0xc04,id) == 0) return 0;
    object=func_0029EFD0(0xcf7);
    if (object != 0) {
        *(unsigned char *)(object + 0x30) = 0xFF;
        *(unsigned short *)(object + 0x32) = 0xFF;
        *(unsigned char *)(object + 0x31) = 1;
        location=object+0x10;
        state=*(BoltState **)(object+0x68);
        qcopy(location,position);
        object[0x20]=0;
        func_003001E0(state,velocity,position);
        frames=0.016666668f * (D_L00_00262570 + D_0013957F[0])->speed;
        state->frames=func_00283CF0(128.0f / frames);
        /* Call and division in one statement: retail has no line label between them,
           so no division padding (docs/build/compiler-notes.md). */
        state->rate=1.0f/func_00283CE0(state->frames);
        state->id=id;
        state->target=func_L00_0032A088(0xc04,id);
        state->age=0;
        state->fadeFrames=D_L00_001B0938;
        state->fadeRate=1.0f/func_00283CE0(state->fadeFrames);
        state->mode=mode;
        func_002AFFD8(location,&direction,1);
        func_00282D30(&direction,&direction,-1.0f);
        func_L00_003F51A0(object,(char *)&direction);
        if (D_L00_001B0934 > 3) D_L00_001B0934=0;
        state->slot=D_L00_001B0934;
        D_L00_001B0934=((int)(D_L00_001B0934+1))%3;
        func_L00_003F5F90(object);
        if (mode == 1) {
            qcopy(&state->origin,D_L00_001B8DC0);
            func_00282F20(&state->velocity,D_L00_001B8DC0 + 0x230,func_00282DF0(velocity));
        }
        if (mode == 2) {
            qcopy(&previous,position);
            func_00282CC0(location,position,velocity);
            if (func_L00_003F5238(object,(char *)&previous) != 0) object[0x20]=2;
        }
    }
    return object;
}
