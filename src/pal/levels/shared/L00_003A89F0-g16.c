#include "common.h"
/* func_PAL_L00_003A89F0, the PAL copy of func_L00_003A53E8: the same C, with its tick counts at 50 Hz.
   The spill slots follow gcse's bucket order, (hash % 335) here: the `short` values, vars (set beside
   self, read through holder) and the hit list reached through RayBlock's tail give retail's order. */
struct Rac2Native_5f824a0e369ccf7b_src_record { u8 b0,b1,b2,b3; u16 s4,s6,s8,s10,s12; u8 e,f; };
extern struct Rac2Native_5f824a0e369ccf7b_src_record D_L00_00294900[];
extern u8 D_00139568[];
extern float D_L00_001AF670[4] __attribute__((sda));
extern unsigned int D_L00_001AF680 __attribute__((sda));
extern unsigned int D_L00_001AF684 __attribute__((sda));
extern unsigned int D_L00_001AF688 __attribute__((sda));
extern unsigned int D_L00_001AF68C __attribute__((sda));
extern unsigned int D_L00_001AF690 __attribute__((sda));
extern int D_L00_001AF6B4 __attribute__((sda));
typedef struct {
    char pad0[0x730];
    float a550[4];
    float a560[4];
    float a570[4];
    float a580[4];
    char pad4[0x488];
    char * aa18;
    char pad5[0x634];
    unsigned int b050;
    char pad6[0xC];
    int b060;
    char pad7[0x20C];
    int b270;
    char pad8[0xE3C];
    char * c0b0;
    int c0b4;
    char pad10[0x4];
    int c0bc;
    char pad11[0x18];
    u8 c0d8;
    char pad12[0x3];
    u8 c0dc;
    char pad13[0x22F];
    short c30c;
    char pad14[0x46];
    int c354;
} GameView;
typedef struct { char pad[0x1A0]; unsigned int b320, b324; } InputView;
extern GameView D_00189E20 NOT_SDA;
extern InputView D_00138180 NOT_SDA;
/* Only this measured prefix of the level's pulse-curve state is used here. */
typedef struct { float start; int reserved,ticks,mode; float next; int reserved2,nextTicks; } PulseCurvePrefix;
typedef struct { char pad[0x160]; PulseCurvePrefix pulse; } CameraView;
extern CameraView D_L00_001B8C80 NOT_SDA;
typedef struct { char p0[0x28]; unsigned int animation; char p1[0x28]; float rate; char p2[0x18]; float power; char tail[0x6C]; } WeaponEntry;
extern WeaponEntry D_L00_00262570[];
extern char *D_L00_001C3280[];
extern int func_00282978(void *),func_00282948(void *),func_002829D8(void *);
extern int func_002E5CF8(int,int,char *);
extern void func_002A75E0(void *,int,int,int,int),func_002A7470(void *,int,int,int);
extern int func_L00_002C42E0(int,int);
extern int func_L00_002D4040(int),func_L00_002D3F30(int,int);
extern void func_00273318(void *,unsigned int,void *,int,int,int,float,float,float);
extern void func_L00_002AF568(void);
extern void func_L00_002D6B70(int);
extern int func_L00_002D6998(struct Rac2Native_5f824a0e369ccf7b_src_record *);
extern float func_002A7940(void),func_00283CE0(int),func_002A7878(float,float),func_00283B98(float,float);
extern void func_L00_003A6538(void *);
/* The binder: func_L00_002E6EF8 in 23 programs, its twin func_L08_002F2D10 in levels 08, 09,
   19 and 30, so the call carries a name without an address. */
extern void ref_L00_003A53E8_00(void (*)(void *),void *);
extern void func_L00_0032A1A8(char *,char *,void *,float);
extern void func_0029FCC0(char *,int,char *),func_L00_003A5FC0(void *,void *);
extern void func_00282D30(void *,void *,float),func_00282CC0(void *,void *,void *);
extern int func_00277F48(float,void *,int,void *,int);
extern void func_002A8E20(void *,void *),func_0032D758(void *,int,void *);
extern void func_00283410(void *,void *),func_00283678(void *,void *),func_00283738(void *,void *,void *);
extern void func_002AB668(void *,int,float),func_002ACDE8(void *,void *,void *);
extern char *func_L00_003A5DC0(void *,void *,void *,void *);

static inline void SetCameraPulse(CameraView *camera, float amount, int ticks)
{
    camera->pulse.start = amount;
    camera->pulse.ticks = ticks;
    camera->pulse.next = amount;
    camera->pulse.nextTicks = ticks;
    camera->pulse.mode = 0;
}

typedef struct { char p0[6]; short startup, delay, cooldown; char p1[0x20]; float phase; char p2[0x18]; int charged; } BlastTimers;

/* The blast's scratch matrix runs straight into the ray origin and bias and the list of objects hit. */
typedef struct { float rows[2][4]; float origin[4]; float bias[4]; char *hits[20]; } RayTail;
typedef struct { float rows[2][4]; RayTail tail; } RayBlock;

/* Control the two-stage blast and trace its individual fan rays. */
void func_PAL_L00_003A89F0(char *moby)
{
    char *state = *(char **)(moby + 0x68);
    char damage[0x30];
    float probe[4], side[4], forward[4], up[4], bias[4];
    float frame[3][4], orientation[3][4];
    RayBlock block;
    int masks[20];
    float rotation[4], ray[4], start[4], end[4];
    int ready, count, i;
    float step, angle;
    if (*(u8 *)(moby + 0x20) == 0) {
        *(u8 *)(moby + 0x20) = 1;
        *(int *)(state + 0x4C) = -1;
        *(short *)(state + 8) = 0;
        *(short *)(state + 10) = 0;
    }
    if (*(u8 *)(moby + 0x20) == 6 && func_00282978(state + 4)) {
        func_002E5CF8(2,0,moby);
        *(u8 *)(moby + 0x20) = 1;
    }
    if (*(u8 *)(moby + 0x42) == *(u8 *)(moby + 0x43)) {
        int flags = *(u8 *)(moby + 0x60);
        if (flags & 2)
            func_002A75E0(moby,1,0,2,0);
    }
    if (D_00189E20.c0b4 == 1)
        func_L00_002C42E0(29,1);
    func_002829D8(state);
    {
    char *holder = state;
    char *vars;
    if (D_00189E20.c0b4 == 29) {
        unsigned int color;
        if (*(float *)state > 0.0f && func_L00_002D4040(-1))
            color = 0x600000FF;
        else
            color = 0x600FFF0F;
        func_00273318(moby,color,0,0x21,-1,4,1.3f,0.0f,90.0f);
    }
    {
        char *owner = moby;
        char *self;
        if (D_00189E20.b270)
            D_00189E20.aa18 = (char *)D_00189E20.b270;
        ready = 1;
        if (D_00189E20.c0b4 == 29) {
            if (!func_00282948(&D_00189E20.c354))
                ready = 0;
        } else
            D_00189E20.c354 = 33;
        if (*(u8 *)(moby + 0x20) == 1 && !D_00189E20.c0dc && *(float *)state == 0.0f &&
            D_00189E20.b060 >= 19 && ready) {
            if ((D_00138180.b320 & D_00189E20.b050) && func_L00_002D3F30(-1,1)) {
                WeaponEntry *weapon = D_L00_00262570 + D_00139568[0x1A];
                if (*(u8 *)(D_00189E20.c0b0 + 0x43) == weapon->animation ||
                    D_00189E20.c0bc || D_00189E20.c30c) {
                    { short v = ((s32)(D_L00_001AF680) * 5 + 2) / 6; ((BlastTimers *)state)->startup = v; }
                    { short v = ((s32)(D_L00_001AF688) * 5 + 2) / 6; ((BlastTimers *)state)->delay = v; }
                    { short v = ((s32)(D_L00_001AF690) * 5 + 2) / 6; ((BlastTimers *)state)->cooldown = v; }
                    ((BlastTimers *)state)->charged = 1;
                } else {
                    ((BlastTimers *)state)->startup = 2;
                    { short v = ((s32)(D_L00_001AF684) * 5 + 2) / 6; ((BlastTimers *)state)->delay = v; }
                    { short v = ((s32)(D_L00_001AF68C) * 5 + 2) / 6; ((BlastTimers *)state)->cooldown = v; }
                    ((BlastTimers *)state)->charged = 0;
                }
                func_L00_002AF568();
                *(int *)(state + 0x4C) = func_L00_002D6998(D_L00_00294900);
                *(u8 *)(moby + 0x20) = 2;
                *(float *)(state + 0xC) = func_002A7940();
                func_002A7470(moby,2,0,0);
                *(float *)(state + 0x20) = 1.0f / func_00283CE0(*(short *)(state + 8));
                *(float *)(state + 0x24) = 1.0f / func_00283CE0(*(short *)(state + 10));
                *(float *)(state + 0x28) = func_002A7940();
                ((BlastTimers *)state)->phase = func_002A7940();
                {
                    int t = ((s32)(D_L00_001AF6B4) * 5 + 2) / 6;
                    *(int *)(state + 0x40) = t;
                    *(float *)(state + 0x44) = 1.0f / func_00283CE0(t);
                }
            } else if (D_00138180.b324 & D_00189E20.b050) {
                func_002E5CF8(4,0,moby);
            }
            if (!((D_00138180.b320 & D_00189E20.b050) && func_L00_002D4040(-1) && D_00189E20.c0d8) &&
                *(int *)(state + 0x4C) >= 0) {
                func_L00_002D6B70(*(int *)(state + 0x4C));
                *(int *)(state + 0x4C) = -1;
            }
        }
        if (*(short *)(state + 6) == 0) {
            func_00282978(state + 10);
            func_00282978(state + 8);
            func_00282948(state + 0x40);
            if (*(unsigned long *)(state + 8) & 0xFFFFFFFF)
                ref_L00_003A53E8_00(func_L00_003A6538,moby);
        }
        if ((unsigned int)(*(u8 *)(moby + 0x20) - 2) >= 2 || !func_00282978(state + 6))
            return;
        self = owner;
        vars = holder;
        {
        RayTail *tail = &block.tail;
        if (D_00189E20.aa18) {
            func_L00_0032A1A8(D_00189E20.aa18,state + 0x10,D_00189E20.a580,1.0f);
            qcopy(D_00189E20.a550, D_00189E20.a580);
        }
        if (*(u8 *)(moby + 0x20) == 2) {
            *(u8 *)(moby + 0x20) = 3;
            func_0029FCC0(moby,0,state + 0x10);
            func_L00_003A5FC0(moby,state + 0x10);
            qcopy(vars + 0x30, D_00189E20.a580);
            ref_L00_003A53E8_00(func_L00_003A6538,moby);
            func_002E5CF8(0,0,moby);
            if (*(int *)(state + 0x48))
                SetCameraPulse(&D_L00_001B8C80, 0.12f, 25);
            else
                SetCameraPulse(&D_L00_001B8C80, 0.06f, 25);
            return;
        }
        *(u8 *)(moby + 0x20) = 6;
        *(short *)(state + 4) = 23;
        {
        unsigned short id = *(unsigned short *)(moby + 0xAA);
        WeaponEntry *weapon = D_L00_00262570 + D_00139568[0x1A];
        float power = weapon->power;
        *(int *)(damage + 0x14) = 0x10000;
        *(int *)(damage + 0x20) = 1;
        *(u8 *)(damage + 0x18) = 3;
        *(u8 *)(damage + 0x19) = 2;
        *(short *)(damage + 0x1A) = id;
        *(float *)(damage + 0x1C) = power;
        *(char **)(damage + 0x10) = moby;
        func_00282D30(probe,moby + 0xD0,-1.35f);
        func_00282CC0(probe,probe,moby + 0x10);
        func_00282D30(side,self + 0xC0,0.275f);
        func_00282CC0(probe,probe,side);
        count = func_00277F48(1.5f,probe,1,D_00189E20.c0b0,0);
        for (i = 0; i < count; i++) {
            if (D_L00_001C3280[i] != D_00189E20.c0b0) {
                func_00282D30(damage,moby + 0xD0,-1.5f);
                *(float *)(damage + 0xC) = 5627.9248046875f;
                func_002A8E20(D_L00_001C3280[i],damage);
                func_0032D758(D_L00_001C3280[i],26,moby);
            }
        }
        func_00283410(&block,D_L00_001AF670);
        func_00283678(orientation,&block);
        func_0029FCC0(moby,0,(char *)block.tail.origin);
        if (D_00189E20.c30c == 1) {
            func_00282D30(forward,moby + 0xD0,-1.0f);
            func_00282D30(up,self + 0xC0,-1.0f);
            func_00282D30(bias,moby + 0xE0,0.1f);
            func_00283738(frame,self + 0xC0,orientation);
        } else {
            qcopy(forward, D_00189E20.a550);
            qcopy(up, D_00189E20.a560);
            func_00282D30(bias,D_00189E20.a570,-0.1f);
            func_00283738(frame,D_00189E20.a550,orientation);
        }
        qcopy(vars + 0x30, forward);
        {
        int rayCount, rayIndex, clearIndex, restoreIndex;
        step = 1.0471977f;
        angle = 0.0f;
        rayCount = 0;
        {
            char **list = tail->hits;
            for (clearIndex = 0; clearIndex < 20; clearIndex++) { list[clearIndex] = 0; masks[clearIndex] = 0; }
        }
        {
            for (rayIndex = 19; rayIndex >= 0; rayIndex--) {
                char *hit;
                float spread = func_002A7878(0.01f,0.3272492588f);
                func_002AB668(rotation,(int)up,spread);
                func_002ACDE8(ray,forward,rotation);
                func_002ACDE8(block.tail.bias,bias,rotation);
                angle = func_00283B98(func_002A7878(step * 0.5f,step * 1.5f),angle);
                func_002AB668(rotation,(int)forward,angle);
                func_002ACDE8(ray,ray,rotation);
                func_002ACDE8(block.tail.bias,block.tail.bias,rotation);
                func_00282D30(ray,ray,32.0f);
                func_00282CC0(start,block.tail.origin,block.tail.bias);
                func_00282CC0(end,start,ray);
                hit = func_L00_003A5DC0(moby,start,end,damage);
                if (hit) {
                    masks[rayCount] = *(int *)(hit + 0x98);
                    {
                        char **list = tail->hits;
                        list[rayCount++] = hit;
                    }
                    *(int *)(hit + 0x98) = 0;
                }
            }
        }
        {
            char **list = tail->hits;
            for (restoreIndex = 0; restoreIndex < rayCount; restoreIndex++)
                *(int *)(list[restoreIndex] + 0x98) = masks[restoreIndex];
        }
        }
        {
            WeaponEntry *weapon = D_L00_00262570 + D_00139568[0x1A];
            *(float *)state = 1.0f / weapon->rate;
        }
        }
        }
    }
    }
}

