/* func_PAL_L12_0041E358, the PAL copy of func_L12_004190A8: the same C, where rename func_L12_00418D20 becomes func_PAL_L12_0041DFD0; rename func_002A7470 becomes func_PAL_002A7E68; rename func_L12_003E0858 becomes func_PAL_L12_003E4AC8; rename func_002ABBB8 becomes func_PAL_002AC718; rename func_002A6C58 becomes func_PAL_002A7650. */
/* Path driver with child coordination, sound phases and pose oscillation. */
#include "common.h"

typedef struct {
    u8 pad[0x50];
    s32 path0, path1, path2, trigger, child;
    u8 pad64[12];
    f32 position[4], rotation[4];
    f32 length, phase0, phase1, phase2;
    f32 progress, velocity;
    s32 timer, sound, soundTimer;
} DriverState;
typedef struct DriverObject DriverObject;
struct DriverObject {
    u8 pad00[0x10];
    float position[4];
    u8 state;
    u8 pad21[0xF];
    u8 f30;
    u8 pad31;
    u16 f32;
    u8 pad34[0xE];
    u8 animation, nextAnimation;
    u8 pad44[0x24];
    DriverState *vars;
    u8 pad6C[0x84];
    float rotation[4];
};
/* Partial sound anchor: indices advance by 0x70, independently of this view. */
typedef struct {
    u8 pad[0x74];
    u8 active;
    u8 pad75[9];
    s16 kind;
    u8 pad80[8];
    DriverObject *owner;
} DriverSound;
extern u8 D_00188660[];
extern u8 *D_L12_001B2E9C MACRO_ADDR;
extern u8 *D_L12_001B2E9C_gp SDATA(D_L12_001B2E9C);
extern u8 *D_L12_001FEAC0[];
extern float D_L12_001B1C00[2] __attribute__((sda));
extern float D_L12_001B1C10[2] __attribute__((sda));
extern float D_L12_001B1C24 __attribute__((sda));
extern float D_L12_001B1C28 __attribute__((sda));
extern float D_L12_001B1C2C __attribute__((sda));
extern float D_L12_001B1C30 __attribute__((sda));
extern float D_L12_001B1C34 __attribute__((sda));
extern float D_L12_001B1C38 __attribute__((sda));
extern float D_L12_001B1C3C __attribute__((sda));
extern float D_L12_001B1C40 __attribute__((sda));
extern void func_002A7750(void *,int,int);
extern void func_PAL_002A7E68(void *,int,void *,int);
extern float func_002A7940(void);
extern int func_002B3868(void *);
extern void func_002E59F8(int);
extern int func_002E5CF8(int,int,void *);
extern float func_00282E48(void *,void *);
extern int func_00282948(int *);
extern float func_002AA548(float *,float *,float,float,float,float);
extern void func_002C9828(void *,int,void *,void *,int,float);
extern void func_PAL_L12_0041DFD0(void *);
extern void func_00283098(void *,void *,void *);
extern void func_00282CC0(void *,void *,void *);
extern float func_002A89A8(float,void *,int);
extern int func_PAL_L12_003E4AC8(int,void *,void *);
extern int func_L12_003E09C8(int);
extern void func_L12_0041A5F8(void *);
extern int func_L03_003CA138(void *);
extern int func_L12_0041A698(void *);
extern u8 *func_002A9640(void *,int,int);
extern void func_PAL_002AC718(void *,void *,void *,float,float,int,int,int,float,float,float,float,int,float,int,int,int,int,int);
extern void func_PAL_002A7650(void *,int,int);
extern void func_0029F338(void *);
extern float func_00283B98(float,float);
extern float func_00283198(float);

#define SOUND_ENTRY(index) ((DriverSound *)((s32)D_00188660 + (index) * 0x70))
#define SOUND_LIVE(index) (SOUND_ENTRY(index)->owner == self && SOUND_ENTRY(index)->active)
static __inline__ void driver_clear_sound(DriverObject *self, DriverState *state)
{
    int slot = state->sound;
    if (slot != -1) {
        DriverSound *entry = SOUND_ENTRY(slot);
        if (entry->owner == self && entry->active) func_002E59F8(slot);
    }
    state->sound = -1;
}
#define CLEAR_SOUND() driver_clear_sound(self, state)

void func_PAL_L12_0041E358(DriverObject *self)
{
    DriverState *state = self->vars;
    u8 *path;
    float a[4] __attribute__((aligned(16)));
    float b[4] __attribute__((aligned(16)));
    u8 *hit;
    int accepted;
    switch (self->state) {
    case 0: {
        u8 *initialPath;
        state->sound = -1;
        if (state->path0 == -1 && state->path2 == -1 && state->path1 != 0 &&
            state->trigger == -1 && state->child == -1) {
            func_002A7750(self,7,-1);
            break;
        }
        initialPath = D_L12_001FEAC0[state->path0];
        state->length = func_00282E48(initialPath+0x10,initialPath+0x20);
        func_002A7750(self,3,-1);
        self->f30 = 0xff;
        self->f32 = 0xff;
        qcopy(state->position,self->position);
        qcopy(state->rotation,self->rotation);
        state->phase0 = func_002A7940();
        state->phase1 = func_002A7940();
        state->phase2 = func_002A7940();
        func_002A7750(self,1,-1);
        break;
    }
    case 1:
        if (func_002B3868(self)) CLEAR_SOUND();
        if (func_L03_003CA138(D_L12_001B2E9C + (state->child << 8)))
            func_002A7750(self,2,-1);
        break;
    case 2:
        if (func_002B3868(self)) CLEAR_SOUND();
        path = D_L12_001FEAC0[state->path0];
        func_002AA548(&state->progress,&state->velocity,(float)(*(int *)path-1),
                     0.020000001f,0.002f,0.40000004f);
        func_002C9828(path,0,state->position,state->rotation,0,state->progress);
        func_PAL_L12_0041DFD0(self);
        state->rotation[1] *= -0.333f;
        if (!SOUND_LIVE(state->sound))
            state->sound = func_002E5CF8(0,4,self);
        if (state->progress >= (float)(*(int *)path-1)) {
            func_002A7750(self,3,-1);
            state->timer = 50;
            if (self->nextAnimation != 1) func_PAL_002A7E68(self,1,0,25);
            CLEAR_SOUND();
            state->sound = func_002E5CF8(1,0,self);
        }
        break;
    case 3:
        if (func_002B3868(self)) CLEAR_SOUND();
        if (func_00282948(&state->timer)) {
            func_00283098(a,D_L12_001B1C00,(u8 *)self+0xC0);
            func_00282CC0(a,a,self->position);
            func_00283098(b,D_L12_001B1C10,(u8 *)self+0xC0);
            func_00282CC0(b,b,self->position);
            b[2] += 2.0f;
            b[2] = func_002A89A8(0.5f,b,0);
            if (!func_PAL_L12_003E4AC8(state->trigger,a,b)) {
                func_L12_0041A5F8(D_L12_001B2E9C + (state->child << 8));
                func_002A7750(self,4,-1);
                if (self->nextAnimation != 0) func_PAL_002A7E68(self,0,0,25);
                CLEAR_SOUND();
                state->sound = func_002E5CF8(2,0,self);
                state->soundTimer = 12;
                state->progress = 0;
                state->velocity = 0;
            } else state->timer = 37;
        } else if (state->timer >= 38) {
            if (state->sound == -1 || !SOUND_LIVE(state->sound) ||
                SOUND_ENTRY(state->sound)->kind != 1)
                state->sound = func_002E5CF8(1,0,self);
        }
        break;
    case 4:
        if (func_002B3868(self)) CLEAR_SOUND();
        path = D_L12_001FEAC0[state->path1];
        func_002AA548(&state->progress,&state->velocity,(float)(*(int *)path-1),
                     0.002f,0.002f,0.40000004f);
        func_002C9828(path,0,state->position,state->rotation,0,state->progress);
        func_PAL_L12_0041DFD0(self);
        state->rotation[1] *= -0.333f;
        if (!func_00282948(&state->soundTimer)) {
            if (state->sound == -1 || !SOUND_LIVE(state->sound))
                state->sound = func_002E5CF8(2,0,self);
        }
        if (state->progress >= (float)(*(int *)path-1)) {
            func_002A7750(self,5,-1);
            state->progress = 0;
        }
        break;
    case 5:
        if (func_002B3868(self)) CLEAR_SOUND();
        if (self->nextAnimation == 0 &&
            func_L12_0041A698(D_L12_001B2E9C_gp + (state->child << 8))) {
            if (self->nextAnimation != 1) func_PAL_002A7E68(self,1,0,25);
            state->soundTimer = 12;
            CLEAR_SOUND();
            state->sound = func_002E5CF8(1,0,self);
        } else if (func_L12_003E09C8(state->trigger)) {
            func_002A7750(self,6,-1);
            if (self->nextAnimation != 0) func_PAL_002A7E68(self,0,0,25);
            CLEAR_SOUND();
            if (!SOUND_LIVE(state->sound))
                state->sound = func_002E5CF8(2,4,self);
        } else if (self->animation == 1 && !func_00282948(&state->soundTimer)) {
            if (state->sound == -1 || !SOUND_LIVE(state->sound) ||
                SOUND_ENTRY(state->sound)->kind != 1)
                state->sound = func_002E5CF8(1,0,self);
        }
        break;
    case 6:
        if (func_002B3868(self)) CLEAR_SOUND();
        path = D_L12_001FEAC0[state->path2];
        func_002AA548(&state->progress,&state->velocity,(float)(*(int *)path-1),
                     D_L12_001B1C3C*0.00040000002f,
                     D_L12_001B1C3C*0.00040000002f,
                     D_L12_001B1C40*0.020000001f);
        func_002C9828(path,0,state->position,state->rotation,0,state->progress);
        func_PAL_L12_0041DFD0(self);
        state->rotation[1] *= -0.333f;
        if (!SOUND_LIVE(state->sound)) state->sound = func_002E5CF8(0,4,self);
        if (state->progress >= (float)(*(int *)path-1)) {
            func_002A7750(self,1,-1);
            state->progress = 0;
        }
        break;
    case 7:
        if (func_002B3868(self)) CLEAR_SOUND();
        hit = func_002A9640(self,0x10000,0);
        if (hit) {
            u8 *owner = *(u8 **)(hit+0x20);
            accepted = 0;
            if (owner && (*(s16 *)(owner+0xAA) == 0xB69 || *(s16 *)(owner+0xAA) == 0xF9E))
                accepted = 1;
            if (!accepted) {
                func_PAL_002AC718(self,self->position,0,0,0,10,3,9,4,2,9,0,-1,15,1,1,-1,0,0x810001);
                func_PAL_002A7650(self,0,3);
                func_0029F338(self);
                return;
            }
        }
        break;
    }
    if (self->state != 7) {
        qcopy(self->position,state->position);
        qcopy(self->rotation,state->rotation);
        state->phase0 = func_00283B98(state->phase0,D_L12_001B1C38*0.0003490659f);
        self->rotation[0] = func_00283B98(D_L12_001B1C34*(func_00283198(state->phase0)*0.017453294f),state->rotation[0]);
        state->phase1 = func_00283B98(state->phase1,D_L12_001B1C30*0.0003490659f);
        self->rotation[1] = func_00283B98(D_L12_001B1C2C*(func_00283198(state->phase1)*0.017453294f),state->rotation[1]);
        state->phase2 = func_00283B98(state->phase2,D_L12_001B1C28*0.0003490659f);
        self->position[2] += D_L12_001B1C24*func_00283198(state->phase2);
    }
}
