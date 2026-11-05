#include "common.h"

extern void func_00282CF0(void *, void *, void *);
extern float func_00282DF0(void *);
extern float func_00282DB0(void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern int func_00283CF0(float);
extern unsigned char *D_L01_001FF164;
extern int func_00115AC0(char *, char *, int);
extern void func_L00_002AF7D0(void);
extern void func_L00_002B1F90(void);
extern void func_L00_002D2E68(void);
extern void func_L00_002A6708(void);
extern void func_L00_002A53B8(void);
extern void func_L00_002D24B8(void);
extern void func_002A677C(int);
extern void ref_L01_002B3458_00(void);
extern void ref_L01_002B3458_01(int, int);

extern void func_00283098(void *, void *, void *);
extern void func_00283738(void *, void *, void *);
extern void func_00280B90(void *, void *, int);
extern void func_00281DE8(void *, int, int, int);

extern char *D_L01_001B255C MACRO_ADDR;
extern void *func_00325768(int);
extern int func_002E45B8(float);
extern float func_00310580(float, float);
extern void func_002E3738(void *, void *, float);
extern unsigned char *D_L01_001FF040;

typedef int MotionQuad __attribute__((mode(TI)));
typedef union { float v[4]; MotionQuad q; } MotionVec;

typedef struct {
    MotionVec motion;
    char pad10[0x70];
    MotionVec position;
    char pad90[0x50];
    MotionVec probeEnd;
    char padF0[0x4D0];
    char *held;
} MotionHero;
typedef struct {
    MotionVec velocity;
    char pad10[0x10];
    int flags;
    char pad24[0xC];
    int frame;
    float gain;
    float distance;
    int pad3C;
    int sound;
} MotionState;
typedef struct { MotionVec forward[4]; MotionVec inverse[4]; } MotionPath;

extern MotionHero motionHero __asm__("D_00189E20");
typedef struct {
    char pad00[0x30];
    float hitX;
    float hitY;
} MotionCollision;
extern MotionCollision motionCollision __asm__("D_L01_001BF900");

extern char D_00188660[];
extern int D_L01_001B2088[] __attribute__((sda));
extern MotionPath *D_L01_001B264C[] __attribute__((sda));
extern float D_L01_001BF928;
extern void func_00282D08(void *, void *, void *, float);
extern float func_00282E48(void *, void *);
extern float func_00282E80(void *, void *);
extern void func_00282F70(void *, void *, float);
extern void func_002833F0(void *, void *);
extern int func_002A8C28(void *, void *, int, int, int, int, float, float, float);
extern void func_002AC9F8(void *, float);
extern int func_002ACBC8(void *, int);
extern int func_002C9218(int, void *, void *, float);
extern void func_002E59F8(int);
extern int func_002E5CF8(int, int, void *);
extern int func_L00_002E0200(void *, float, float, int, void *);
extern int func_L01_0031B300(void *, void *, void *, void *);

extern void func_002E3470(void *, void *, void *);

typedef int ClosestPointQuad __attribute__((mode(TI)));

typedef struct { char *p[6]; } Sep6;

extern Sep6 D_L01_001AA550;

extern char D_L01_001AA568[];

extern char D_L01_001AA578[];

extern char D_L01_001AA588[];

extern int func_00115DA8_2(char *dst, char *fmt, ...);

extern char D_L01_00189E20[];

extern char D_L01_002637A0[];

extern s32 D_L01_001A8F40[] __attribute__((sda));

extern char D_L01_00189E20_sda[] __attribute__((sda));

extern void func_002C7CA8(void);

extern void func_002B4070(void);

extern void func_002ADDC8(void);

extern void func_002C37C8(void);

extern void func_002AEB80(void);

extern void func_002B9878(void);

extern void func_002A7740(void);

extern void func_002AB1C8(void);

extern void func_002A9520(void);

extern void func_002A9310(void);

extern void func_002FDB00(void *a0);

extern void func_002AB328(void);

extern void func_0030F444(int a0);

extern char D_L01_00189E20[];

extern void func_002A8EE0(int a0, int a1);

extern char D_L01_00139568[];

extern unsigned char D_0018C0D4[];

extern void func_002BEB90(unsigned long, unsigned long);

extern void *D_0018C0B0;

extern float D_L01_00189F90;

extern unsigned short *D_L01_001FB020[];

extern unsigned short *r1_D_L01_001ABFC0[];

extern char *r1_D_L01_00160058 MACRO_ADDR;

extern int r1_D_L01_00160058_m __asm__("r1_D_L01_00160058") MACRO_ADDR;

extern char *D_L01_001FE180[];

typedef struct {
    int path;
    float radius;
    int volumes[6];
    int lists[12];
    int mobys[11];
    signed char switches[4];
} SpatialTriggerSettings;

typedef struct { char prefix[0x2290]; void *moby; } ProbeHero;
typedef struct { char pad[0x18]; void *moby; int count; char gap[0x20]; float normal[4]; } ProbeResult;
extern ProbeResult D_L01_001BF900;

extern char D_L01_00189F10[];

extern int D_L01_001BF91C;

extern float func_L00_002D3A58(void *);

extern void func_L00_002D36E0(void *, float, float, float, int);

extern float func_00282E20(void *);

extern void func_L00_002D3B58(void *, void *, float);

extern void func_00282D30(void *, void *, float);

extern int func_002761F8(void *, void *, int, void *, int);

extern int func_00278E78(void);

extern float func_L00_002D3EA8(void *);

extern char D_L01_001B94C0[];

extern char D_00189EA0[];

extern int func_311B48(char *a0, void *a1, int a2);

extern int func_3163C8(char *a0, void *a1);

extern int func_316558(char *a0, void *a1);

extern int func_3164A0(char *a0, void *a1);

extern void func_002E3CD8(void *a0, void *a1);

extern void func_002E3F60(void *a0, void *a1);

extern void func_002E34A0(void *a0, void *a1, void *a2);

extern void func_L01_002E3940(void *a0, void *a1, void *a2);

extern void func_002E3470(void *a0, void *a1, void *a2);

extern void func_002E3918(void *a0, void *a1, void *a2);

extern void func_002E3470(void *a0, void *a1, void *a2);

extern float func_00283B98(float f12, float f13);

extern float func_00283198(float f12);

extern int func_00283D38(int a0, int a1, float f12);

extern float func_002A7878(float f12, float f13);

extern void func_002AEC18(void *a0, int a1);

extern float func_002E3B10(float f12, float f13);

extern int func_002B50E0(char *a0, char *a1, float f12);

extern char *func_00321F08(int a0);

extern void func_003140B0(char *a0, char *a1, int a2, float f12, float f13,
                          float f14, float f15);

extern char D_00139A28[];


extern int D_L01_001A79F0;

extern int D_L01_0028EA50[];

extern int D_L01_001C5D20[];

extern void func_002A6CF0(int a0);

extern float func_002E3618(void *a0, void *a1);

extern unsigned char D_L01_001AA6F8[];

extern char D_00188660[];

extern int func_003711D8(int a0);

extern unsigned char D_L01_001395B8[];

extern void func_003907B8(int a0, int a1, int a2);


void func_L01_002A84D8(void) {
    char *p;

    func_002C7CA8();
    func_002B4070();
    func_002ADDC8();
    func_002C37C8();
    func_002AEB80();
    p = D_L01_00189E20;
    if (*(unsigned char *)(p + 0x22B4) != 0) {
        func_002B9878();
        func_002A7740();
        if (*(unsigned char *)(p + 0x22B4) != 0) {
            func_002AB1C8();
            func_002A9520();
            func_002A9310();
            func_002FDB00(p + 0x80);
            func_002AB328();
            func_0030F444(*(int *)(p + 0x2290));
        }
    }
}


void func_L01_002A9298(void) {
    char *b = D_L01_00189E20;
    int i = *(int *)(b + 0x1248);
    unsigned char c;
    unsigned char *t;

    if (i < 0)
        return;
    c = *(unsigned char *)(D_L01_00139568 + i);
    t = (unsigned char *)D_L01_002637A0 + c * 0xE0;
    if (t[4] == 0)
        return;
    if (*(int *)(b + 0x1220) == 0)
        return;
    func_002A8EE0(*(int *)(b + 0x1220), *(int *)(b + 0x2290));
}



typedef int LedgeQuad __attribute__((mode(TI)));
typedef struct {
unsigned char pad0[464];
short cooldown;
unsigned char pad1d2[146];
float radius;
unsigned char pad268[180];
float groundHeight;
unsigned char pad320[382];
unsigned char pastApex;
unsigned char pad49f[1945];
float frame;
unsigned char padc3c[5716];
void * moby;
int state;
unsigned char pad2298[4];
int control;
unsigned char pad22a0[20];
unsigned char vehicle;
} LedgeProbeResident;
extern LedgeProbeResident ledgeHero __asm__("D_00189E20");
extern float func_002C9280(void *);
extern void func_002C92D8(void *, void *, float);
extern float func_002C9628(void *);
extern float func_002E3560(void *, void *);
extern float func_002E3A48(float);
extern int func_002D3C80(void *, void *, int, void *, int);
extern int func_002D77E8(void);
extern char *func_003148A0(void *);
extern char *func_00316D00(void *);
extern int func_002D4CE0(void *, int, void *, float);
typedef struct {
    unsigned char pad0[0x18];
    void *moby;
    unsigned char pad1c[4];
    float position[4];
    unsigned char pad30[16];
    float normal[4];
} LedgeProbeHit;
extern LedgeProbeHit ledgeHit __asm__("D_L01_001BF900");
#define FL(p,o) (*(float *)((char *)(p)+(o)))
#define IN(p,o) (*(int *)((char *)(p)+(o)))
/* The ledge probe of func_L00_002ACF88 without its vehicle == 1 branch. */
int func_L01_002AE128(void *position, void *unused, char *out)
{
    float v0[4], v1[4], v2[4], v3[4], v4[4], v5[4], v6[4], v7[4], v8[4], v9[4], v10[4], v11[4], v12[4], v13[4], v14[4], v15[4], v16[4], v17[4], v18[4], v19[4];
    char *a, *b;
    void *object;
    int go, found, i, kind, ok;
    int edge, j;
    float height;
    float step, max;
    float down, top, drop, d, length;
    LedgeProbeResident *hero;
    if (out) IN(out,0x28)=0;
    if (ledgeHero.cooldown) return 0;
    go=0;
    if (ledgeHero.vehicle==0) {
        if ((ledgeHero.control==4 && (ledgeHero.pastApex || func_002C9280((char *)&ledgeHero+0xf0)<0.05833333730697632f)) || ledgeHero.control==2 || ledgeHero.state==8 || ledgeHero.state==25 || ledgeHero.state==26) go=1;
        if (ledgeHero.state==14 && ledgeHero.frame<37.0f) go=0;
    }
    if (out != (char *)&ledgeHero+0x550) go=1;
    if (!go) return 0;
    hero=&ledgeHero;
    down=-0.7f; top=1.15f; drop=-1.43f;
    found=0;
    qcopy(v0,position);
    func_002E3738(v4,hero,hero->radius);
    func_002E3470(v0,v0,v4);
    func_002E3738(v4,(char *)&ledgeHero+0x20,1.65f);
    func_002E3470(v1,v0,v4);
    func_002E3738(v4,(char *)&ledgeHero+0x20,-top);
    func_002E3470(v2,v0,v4);
    func_002E3738(v3,hero,0.075f);
    for(i=0; i<4; i++) {
        func_002E3470(v1,v1,v3);
        func_002E3470(v2,v2,v3);
        if(func_002D3C80(v1,v2,4,ledgeHero.moby,0)) {
            kind=func_002D77E8();
            if(kind!=9 && kind!=12 && kind!=0 && func_002C9628(ledgeHit.normal)<0.349065899848938f) found=1;
        }
        if(found) break;
    }
    object=0;
    if(!found) goto fail;
    if(ledgeHit.moby) {
        ok=0;
        a=func_003148A0(ledgeHit.moby);
        b=func_00316D00(ledgeHit.moby);
        if(a && (*(unsigned short *)(a+0x1e)&1)) ok=1;
        else if(b) ok=IN(b,0x3c)&1;
        if(!ok) return 0;
        object=ledgeHit.moby;
    }
    if(out) *(void **)(out+0x38)=ledgeHit.moby;
    qcopy(v6,ledgeHit.position);
    func_002E34A0(v5,v6,position);
    if(1.5f<func_002C9280(v5)) return 0;
    func_002E3738(v7,(char *)&ledgeHero+0x20,0.005f);
    func_002E3470(v7,v7,v6);
    func_002E3738(v8,(char *)&ledgeHero,-1.0f);
    func_002E3470(v8,v8,v7);
    if(func_002D3C80(v8,v7,2,ledgeHero.moby,0)) {
        if(!ledgeHit.moby || ledgeHit.moby!=object) return 0;
    }
    if(out) {
        func_002E3738(v9,(char *)&ledgeHero+0x20,0.6f);
        func_002E3470(v9,v9,v6);
        if(func_002D4CE0(v9,4,ledgeHero.moby,0.45f)) IN(out,0x34)|=1;
        else IN(out,0x34)&=~1;
    }
    height=func_002C9280(v5);
    if(height+ledgeHero.groundHeight<1.8f || height<0.5f) return 0;
    *(LedgeQuad *)v11=0; FL(v11,0)=1.0f; FL(v11,8)=down;
    func_002E3918(v11,v11,(char *)&ledgeHero);
    edge=0;
    func_002E3470(v11,v11,v6);
    func_002E34A0(v9,position,v11);
    func_002C92D8(v9,v9,0.0f);
    func_002E3470(v9,v9,v11);
    func_002E3738(v10,(char *)&ledgeHero+0x20,-down*0.2f);
    for(j=0;j<5;j++) {
        if(func_002D3C80(v9,v11,2,0,0)) {
            func_002E3738(v12,ledgeHit.normal,1.0f);
            edge=1;
            func_002C92D8(v12,v12,0.0f);
            break;
        }
        func_002E3470(v9,v9,v10);
        func_002E3470(v11,v11,v10);
    }
    if(!edge) return 0;
    length=func_002E3560((char *)&ledgeHero,v12);
    if(!(length<func_002E3A48(1.134464144706726f))) return 0;
    step=0.03f;
    max=2.4f;
    qcopy(v18,v6);
    func_002E3738(v17,(char *)&ledgeHero+0x2c0,-0.05f);
    func_002E3738(v16,v12,step);
    func_002E3470(v15,v16,v17);
    func_002E34A0(v16,v16,v17);
    func_002E3470(v13,v18,v16);
    func_002E3470(v14,v18,v15);
    for(d=0.0f;d<max;d+=step) {
        if(!func_002D3C80(v14,v13,4,ledgeHero.moby,0)) {
            if(out) {
                qcopy(out+0x10,v18);
                func_002E3738(v19,v12,0.5f);
                func_002E3738(out,(char *)&ledgeHero+0x2c0,-drop);
                func_002E3470(out,v19,out);
                func_002E3470(out,out+0x10,out);
                FL(out,0x24)=func_002E3B10(FL(v12,0),FL(v12,4));
                IN(out,0x28)=1;
            }
            return 1;
        }
        qcopy(v18,ledgeHit.position);
        func_002E3470(v14,v18,v15);
        func_002E3470(v13,v18,v16);
    }
fail:
    return 0;
}
#undef FL
#undef IN

typedef int HeroQuad __attribute__((mode(TI)));
extern char D_00189E20[];
extern unsigned char D_00139568[];
extern char D_L01_001B7B00[];
extern int func_L00_002D4040(int);
extern int func_L00_002ADEA0(int);
extern void func_L00_00311080(void *, void *, int, int, int, int);
extern void func_L00_00310D30(void *, void *);
extern void func_002AA2E8(void *, float, float);
extern void func_L00_00310C88(void *, void *);
extern void func_00282C88(void *);
extern void func_00283098(void *, void *, void *);
extern float func_00283B98(float, float);

/* A moby's model: the part of it the file uses. */
typedef struct MobyModel {
    char pad00[0x10];
    int f10;
    char pad14[0x32];
    short kind;                 /* 0x46 */
} MobyModel;

/* A moby (0x100 bytes), as far as the file uses it. */
typedef struct Moby {
    char pad00[5];
    unsigned char flags;
    char pad06[2];
    float fade;                 /* 0x08: 1.0 fully shown, 0.0 gone */
    char pad0C[0x17];
    unsigned char animation;    /* 0x23 */
    MobyModel *model;           /* 0x24 */
    int f28;
    char pad2C[5];
    unsigned char f31;
    char pad32[2];
    unsigned short state;       /* 0x34 */
    char pad36[2];
    char *buffer0;              /* 0x38 */
    char *buffer1;              /* 0x3C */
    char pad40[0x58];
    int f98;
    char pad9C[0x24];
    HeroQuad matrix[3];         /* 0xC0 */
    char padF0[0x10];
} Moby;

/* One entry of the weapon table (0xE0 bytes). */
typedef struct WeaponInfo {
    char pad00[0x2C];
    int animation;              /* 0x2C */
    int altAnimation;           /* 0x30: used while the hero's state is 12 */
    char pad34[0xAC];
} WeaponInfo;

/* The hero block (D_00189E20), the fields func_L01_002B0318 uses. */
typedef struct HeroState {
    char pad00[0x90];
    HeroQuad position;          /* 0x90 */
    char padA0[0x730 - 0xA0];
    HeroQuad matrix[3];         /* 0x730 */
    float f760;
    char pad764[0xC];
    union {
        HeroQuad quad;
        float v[4];
    } f770;                     /* 0x770: copy of position, z eased to 0 */
    char pad780[0xE98 - 0x780];
    Moby *attached[2];          /* 0xE98 */
    char padEA0[4];
    int attachedMode;           /* 0xEA4: 0 shown, 1 fading out, 2 fading out fast */
    char padEA8[0x2290 - 0xEA8];
    Moby *moby;                 /* 0x2290 */
    char pad2294[8];
    int state;                  /* 0x229C */
    char pad22A0[0x22B8 - 0x22A0];
    unsigned char f22B8;
    char pad22B9;
    unsigned char f22BA;
    char pad22BB[8];
    unsigned char f22C3;
    char pad22C4[0x24B0 - 0x22C4];
    int animation;              /* 0x24B0 */
    int weaponId;               /* 0x24B4 */
} HeroState;

/* For the hero's two attached mobys: point them at their buffers, start the animation the
   current item's table entry names, fade them in or out (removing one that has faded out),
   then copy the hero moby's matrix to hero + 0x730 and ease hero + 0x778 to 0. */
void func_L01_002B0318(void)
{
    HeroState *hero;
    HeroState *state;
    HeroQuad *matrix;
    WeaponInfo *weapon;
    int weaponId, animation;
    int i;

    hero = (HeroState *)D_00189E20;
    if (hero->f22B8 && hero->f22BA && !func_L00_002D4040(-1))
        func_L00_002AF7D0();
    for (i = 0; i < 2; i++) {
        HeroState *player = (HeroState *)D_00189E20;
        Moby **slot = &player->attached[i];

        if (*slot) {
            (*slot)->buffer0 = D_L01_001B7B00 + i * 0xC00;
            (*slot)->buffer1 = D_L01_001B7B00 + 0x600 + i * 0xC00;
            weaponId = func_L00_002ADEA0(0);
            if (weaponId == player->weaponId) {
                weapon = &((WeaponInfo *)D_L01_002637A0)[D_00139568[weaponId]];
                animation = weapon->animation;
                if (player->state == 12)
                    animation = weapon->altAnimation;
                if (animation != -1 && (*slot)->animation != animation) {
                    player->animation = animation;
                    func_L00_00311080(player->moby, *slot, animation, 0, 8, 1);
                }
            }
            {
                HeroState *owner = (HeroState *)D_00189E20;

                func_L00_00310D30(owner->moby, *slot);
                if (owner->attachedMode) {
                    if (owner->attachedMode == 2)
                        func_002AA2E8(&(*slot)->fade, 0.0f, 0.25f);
                    else
                        func_002AA2E8(&(*slot)->fade, 0.0f, 0.07f);
                    hero = (HeroState *)D_00189E20;
                    if ((*slot)->fade == 0.0f) {
                        func_L00_00310C88(hero->moby, slot);
                        return;
                    }
                } else {
                    func_002AA2E8(&(*slot)->fade, 1.0f, 0.2f);
                    if (((*slot)->flags & 2) && !owner->f22BA) {
                        owner->attachedMode = 1;
                        (*slot)->f28 = 0;
                        owner->f22B8 = 0;
                        return;
                    }
                }
            }
        }
    }
    matrix = ((HeroState *)D_00189E20)->matrix;
    state = (HeroState *)D_00189E20;
    {
        Moby *moby = state->moby;

        matrix[0] = moby->matrix[0];
        matrix[1] = moby->matrix[1];
        matrix[2] = moby->matrix[2];
        func_00282C88(&state->f760);
    }
    state->f760 = 1.0f;
    func_00283098(&state->f760, &state->f760, matrix);
    state->f770.quad = state->position;
    if (!state->f22C3)
        state->f770.v[2] = func_00283B98(state->f770.v[2], 0.0f);
}

extern void func_L00_002AF7D0(void);
extern void func_L00_002B1F90(void);
extern void func_L00_00322EC8(char *a0);
extern void func_L00_002D2E68(void);
extern void func_L00_002A6708(void);
extern void func_L00_002A53B8(void);
extern void func_L00_002D24B8(void);
extern void func_002A677C(int a0);
extern void func_L01_002BEB90(int a0, int a1);
extern void func_L01_002B3D28(void);
extern char D_00189E20[];

void func_L01_002B3458(int a0, int a1, int a2) {
    char *s0 = D_00189E20;

    func_L00_002AF7D0();
    s0[0x22B6] = 1;
    func_L00_002B1F90();
    *(int *)(s0 + 0x2290) = *(int *)(s0 + 0xC18);
    func_L00_00322EC8(s0 + 0x18E0);
    func_L00_00322EC8(s0 + 0x1A30);
    *(int *)(*(int *)(s0 + 0x2290) + 0x9C) = -1;
    if (a0 != 4 || *(unsigned char *)(s0 + 0x22B4) != a0)
        func_L00_002D2E68();
    func_L00_002A6708();
    func_L00_002A53B8();
    {
        char *s1 = D_00189E20;

        *(unsigned char *)(s1 + 0x22B4) = a0;
        *(int *)(s1 + 0xC14) = a2;
        *(int *)(s1 + 0x2290) = a2;
    }
    func_L01_002B3D28();
    {
        char *s2 = D_00189E20;

        *(float *)(s2 + 0x250) = *(float *)(s2 + 0x258);
        *(float *)(s2 + 0x254) = *(float *)(s2 + 0x25C);
        *(unsigned short *)(*(int *)(s2 + 0x2290) + 0x34) |= 6;
        *(float *)(s2 + 0xC20) = 1.0f;
        *(float *)(s2 + 0xC24) = 1.0f;
        func_L00_002D24B8();
        func_002A677C(*(int *)(s2 + 0x2290));
        *(unsigned short *)(s2 + 0x24F2) = a1;
    }
    func_L01_002BEB90(a1, 2);
}



/* func_L01_002B3788 is defined in L01_002B3788-contact.c. */

/* func_L01_002B3D28 is defined in L01_002B3D28.c. */



/* Stops the hero against a wall: casts two rays along the movement direction (or the vector at
   the start of the hero's data when forced or nearly still), keeps the moby it hit and takes the
   velocity component into the wall's flattened normal away. */
void func_L01_002B4DA0(int force)
{
    float origin[4] __attribute__((aligned(16)));
    float endpoint[4] __attribute__((aligned(16)));
    float lowOrigin[4] __attribute__((aligned(16)));
    float farEndpoint[4] __attribute__((aligned(16)));
    float height, radius, slope;
    int material;
    char *base;
    char *velocity = D_L01_00189F10;

    if (func_L00_002D3A58(velocity) < 0.0016666668f)
        return;
    base = velocity - 0xF0;
    height = 0.37f;
    radius = 0.5f;
    if ((unsigned)(*(int *)(base + 0x229C) - 17) < 2) {
        height = 0;
        radius = 0.7f;
    }
    func_L00_002D36E0(origin, 0, 0, height, 1);
    func_L00_002D36E0(lowOrigin, 0, 0, height * 0.3f, 1);
    if (force || func_00282E20(velocity) < 0.01f) {
        func_00282F20(endpoint, base, radius);
        func_00282F20(farEndpoint, base, radius * 1.4f);
    } else {
        func_L00_002D3B58(endpoint, velocity, 0);
        func_00282F20(endpoint, endpoint, radius);
        func_00282D30(farEndpoint, endpoint, 1.4f);
    }
    func_00282CC0(endpoint, endpoint, origin);
    material = -1;
    func_00282CC0(farEndpoint, farEndpoint, lowOrigin);
    {
        char *hero = D_L01_00189E20;

        if (func_002761F8(lowOrigin, farEndpoint, 2, ((ProbeHero *)hero)->moby, 0) && D_L01_001BF91C > 0)
            material = func_00278E78();
    }
    slope = 0;
    {
        char *hero = D_L01_00189E20;

        if (func_002761F8(origin, endpoint, 2, ((ProbeHero *)hero)->moby, 0) && D_L01_001BF900.count > 0)
            slope = func_L00_002D3EA8(D_L01_001BF900.normal);
    }
    if (slope >= 0.8726647f || material == 8 || material == 12) {
        float dot;
        char *hero = D_L01_00189E20;

        *(void **)(hero + 0x270) = D_L01_001BF900.moby;
        func_L00_002D3B58(D_L01_001BF900.normal, D_L01_001BF900.normal, 0);
        func_00282F20(D_L01_001BF900.normal, D_L01_001BF900.normal, 1);
        dot = func_00282DB0(D_L01_001BF900.normal, hero + 0xF0);
        if (dot < 0) {
            func_00282D30(D_L01_001BF900.normal, D_L01_001BF900.normal, -dot);
            func_00282CC0(hero + 0xF0, hero + 0xF0, D_L01_001BF900.normal);
        }
    }
}

/* func_L01_002B5EA0 is in L01_002A7248-collide-g8.c. */

/* func_L01_002B6948 is in L01_002B6948-velocity.c. */

/* func_L01_002BE0E0 is defined in L01_002A7248-timers-g8.c. */

void func_L01_002C1988(unsigned long x) {
    unsigned long mode = 1;
    if (x)
        mode = 2;
    if (D_0018C0D4[0] == 0)
        func_002BEB90(0, mode);
}

/* func_L01_002C2CF0 is defined in L01_002C2CF0-keep-block-order.c. */

void func_L01_002C8990(void) {
    *(unsigned short *)((char *)D_0018C0B0 + 0x34) |= 1;
}

void func_L01_002C89A8(void) {
    *(unsigned short *)((char *)D_0018C0B0 + 0x34) &= 0xFFFE;
}

void func_L01_002C98B8(void) {
    if (D_L01_00189F90 < 0.045f)
        func_002BEB90(0, 1);
    else
        func_002BEB90(3, 1);
}


void func_L01_002E1510(char *a0, int a1, char *a2, int a3, char *a4) {
    float buf[12];
    char *p;
    char *q;
    char *r;
    int n;
    int i;

    if (a1 > 0) {
        q = a0 + 0x30;
        p = a0 + 0x20;
        n = a1;
        for (; n != 0; n--) {
            func_00283098(p, p, a2);
            p += 0x90;
            func_00283098(q, q, a2);
            q += 0x90;
        }
    }
    func_00283738(buf, a2, a2);
    for (i = 0; i < a3; i++) {
        int k = (i & 1) ? 2 : 0;
        if (a1 > 0) {
            p = a0 + (k * 16 + 16);
            q = a0 + k * 16;
            r = a0;
            n = a1;
            while (n != 0) {
                func_00283098(q, q, buf);
                n--;
                q += 0x90;
                func_00283098(p, p, buf);
                p += 0x90;
                func_00280B90(r, a4, 1);
                r += 0x90;
            }
        }
    }
}


/* func_L01_002E1680 is defined in L01_002E1680.c. */

/* Draws a textured quad with the given corners and colour; rotate turns the texture
   coordinates by that many quarter turns. */
void func_L01_002E2608(MotionVec *corners, int texture, int kind, int color, int rotate)
{
    struct {
        MotionVec pos[4];
        int color[4];
        float uv[4][2];
        char reserved[32];
    } packet;
    float rotated[4][2];
    int i, j, k;

    func_00281DE8(&packet, texture, kind, 128);
    packet.color[0] = packet.color[1] = packet.color[2] = packet.color[3] = color;

    packet.uv[0][0] = 0.0f;
    packet.uv[0][1] = 0.0f;
    packet.uv[1][0] = 0.0f;
    packet.uv[1][1] = 1.0f;
    packet.uv[2][0] = 1.0f;
    packet.uv[2][1] = 0.0f;
    packet.uv[3][0] = 1.0f;
    packet.uv[3][1] = 1.0f;
    if (rotate) {
        for (j = 0; j < 4; j++) {
            rotated[j][0] = packet.uv[j][0];
            rotated[j][1] = packet.uv[j][1];
        }
        for (k = 0; k < 4; k++) {
            packet.uv[k][0] = rotated[(k + rotate) % 4][0];
            packet.uv[k][1] = rotated[(k + rotate) % 4][1];
        }
    }

    for (i = 0; i < 4; i++) {
        qcopy(&packet.pos[i], &corners[i]);
        packet.pos[i].v[3] = 1;
    }
    func_00280B90(&packet, 0, 0);
}

/* func_L01_002EABA8 is defined in L01_002A7248-pre.c. */


/* Defined in L01_002F14E8-g8.c. */

INCLUDE_ASM("asm/levels", func_L01_002F1588);



INCLUDE_ASM("asm/levels", func_L01_00304270);

/* Defined in L01_00310BC0.c. */

/* rac1-decomp src/overlays/shared/mobyutil_0026E8E0.c: func_L01_0026F090 */
// Walks a list of moby indices and sets the state byte of each one that is non-negative.
void func_L01_003115E8(int list, int state)
{
    unsigned short *p;
    unsigned short *q = (unsigned short *)r1_D_L01_001ABFC0[list];
    if (q != 0) {
        p = q;
        do {
            char *m = (char *)(((*p & 0x7FFF) << 8) + r1_D_L01_00160058_m);
            if (m[0x20] >= 0) {
                m[0x20] = state;
            }
        } while (*(short *)p++ >= 0);
    }
}

/* Defined in L01_00311C18.c. */

/* func_L01_003120A8 is defined in L01_003120A8-helpers.c. */

void func_L01_003128C0(char *p) {
    *(int *)(p + 0x70) = 0;
    *(float *)(p + 0x74) = 0.2f;
}


/* chain of four probes on the same object; the first that reports a hit picks the code */
int func_L01_003165E8(char *a0, int a1, char *a2, char *a3, char *t0) {
    if (a1 >= 0) {
        char *p = D_L01_001FE180[a1];
        if (func_311B48(a0, p + 0x10, *(int *)p))
            return 1;
    }
    if (func_3163C8(a0, a2))
        return 2;
    if (func_316558(a0, a3))
        return 3;
    if (func_3164A0(a0, t0))
        return 4;
    return 0;
}

void func_L01_00316C48(void *a0, void *a1, void *a2, void *a3, void *t0) {
    float p[0x10];
    float q[0x10];
    float v[4];

    func_002E3CD8(p, a3);
    func_002E3F60(p, p);
    func_002E3CD8(q, t0);
    func_002E34A0(v, a0, a2);
    func_L01_002E3940(v, v, p);
    func_L01_002E3940(v, v, q);
    func_002E3470(a1, v, a2);
}

/* func_L01_00318638 is defined in L01_00318638-qcopy-barrier.c. */

void func_L01_0031A278(char *a0, float *a1, float f12, float f13, float f14) {
    a1[0] = f12;
    a1[1] = f13;
    a1[2] = f14;
    func_002E3918(a1, a1, a0 + 0xC0);
    func_002E3470(a1, a1, a0 + 0x10);
}

/* Retail compares the vertical speed on landing, then stores the same value on both sides of the
 * test, so this call's arms merge at jump2 and only the comparison stays behind. */
static inline void MotionLandingSpeed(float *speed, float rising, float falling)
{
    if (0 < *speed) {
        *speed = rising;
    } else {
        *speed = falling;
    }
}

void func_L01_0031AB20(char *m, MotionState *state, int path, float height, float radius, float extent)
{
    MotionVec old, start, delta, turn, target, change, samples[8], matrix[3], actual;
    float speed, gain, limit, accel, ground;
    int i, handle;
    int phase = D_L01_001B2088[0];

    if ((phase & 15) == (((int)m >> 8) & 15)) {
        float dist = func_00282E48(&motionHero.position, m + 0x10);

        if (*(unsigned short *)(m + 0x34) & 0x1000) {
            if (state->distance < dist) {
                *(unsigned short *)(m + 0x34) &= 0xEFFF;
            }
        } else if (dist < state->distance) {
            *(unsigned short *)(m + 0x34) |= 0x1000;
        }
    }
    qcopy(&old, m + 0x10);
    if (motionHero.held == m) {
        qcopy(&start, m + 0x10);
        start.v[2] += 0.5f;
        if (func_002761F8(&start, &motionHero.probeEnd, 2, m, 0)) {
            motionHero.held = 0;
        }
        func_00282CF0(&delta, m + 0x10, &motionHero.position);
        if (state->frame != -1 && func_002ACBC8(m + 0x10, state->frame)) {
            func_00283098(&delta, &delta, D_L01_001B264C[0][state->frame].inverse);
            delta.v[1] = 0;
            func_00283098(&delta, &delta, D_L01_001B264C[0][state->frame].forward);
        }
        gain = 4.0f;
        if (state->gain != 0) {
            gain = state->gain;
        }
        func_00282F70(&delta, &delta, gain);
        func_00282CC0(&delta, &delta, &motionHero.position);
        func_00282F20(&turn, &motionHero.motion, gain);
        func_00282CC0(&turn, &turn, &motionHero.position);
        turn.v[2] = delta.v[2];
        func_00282D08(&delta, &delta, &turn, 0.5f);
        func_00282CF0(&delta, &delta, &motionHero.position);
        func_00282F20(&delta, &delta, gain);
        func_00282CC0(&delta, &delta, &motionHero.position);
        if (state->flags & 4) {
            gain = func_00282E80(m + 0x10, &delta) * 0.5333333611f;
            accel = 0.01388888899f;
            limit = 0.2666666806f;
        } else {
            gain = func_00282E80(m + 0x10, &delta) * 0.06666667014f;
            accel = 0.00555555569f;
            limit = 0.1333333403f;
        }
        if (limit < gain) {
            gain = limit;
        }
        func_00282CF0(&target, &delta, m + 0x10);
        target.v[2] = 0;
        func_00282F20(&target, &target, gain);
        func_00282CF0(&change, &target, state);
        func_002AC9F8(&change, accel);
        state->velocity.v[0] += change.v[0];
        state->velocity.v[1] += change.v[1];
    } else {
        speed = func_00282DF0(state);
        func_002AA2E8(&speed, 0, 0.002777777845f);
        func_00282F20(state, state, speed);
    }
    if (0.001f < func_00282DF0(state)) {
        if (!(state->flags & 2)) {
            qcopy(&start, m + 0x10);
            qcopy(&delta, m + 0x10);
            start.v[2] += 0.25f;
            delta.v[2] -= 1;
            ground = 0;
            if (func_002761F8(&start, &delta, 16, m, 0)) {
                ground = D_L01_001BF928;
            }
            if (*(float *)(m + 0x18) < ground) {
                *(float *)(m + 0x18) = ground;
                MotionLandingSpeed(&state->velocity.v[2], 0, 0);
            } else {
                state->velocity.v[2] -= 0.00555555569f;
            }
        }
        if (!(state->flags & 4) && func_00282E80(m + 0x10, &motionHero.position) < radius + 2.5f) {
            float toward;

            func_00282CF0(&start, &motionHero.position, m + 0x10);
            start.v[2] = 0;
            func_00282F20(&start, &start, 1);
            toward = func_00282DB0(&start, state);
            if (0 < toward) {
                func_00282F20(&delta, &start, -toward);
                func_00282CC0(state, state, &delta);
            }
        }
        turn.q = 0;
        turn.v[2] = 0.7853982449f;
        func_00282CC0(m + 0x10, m + 0x10, state);
        qcopy(&delta, m + 0x10);
        delta.v[2] += 0.25f;
        func_002833F0(matrix, &turn);
        func_00282F70(&start, state, radius);
        for (i = 0; i < 8; i++) {
            func_00283098(&start, &start, matrix);
            func_00282CC0(&samples[i], m + 0x10, &start);
            samples[i].v[2] += 0.25f;
            func_L01_0031B300(m, state, &delta, &samples[i]);
        }
        func_00282D30(&target, state, 5);
        func_00282CC0(&target, &target, m + 0x10);
        target.v[2] += radius;
        func_002A8C28(m, &target, 0x4000000, 0, 1, 0, radius + 0.2f, 1, 1);
        qcopy(&change, m + 0x10);
        change.v[2] += height;
        if (func_L00_002E0200(&change, radius, extent, 0, m)) {
            *(float *)(m + 0x10) = motionCollision.hitX;
            *(float *)(m + 0x14) = motionCollision.hitY;
        }
        if (path != -1) {
            func_002C9218(path, m + 0x10, m + 0x10, radius);
        }
        func_00282CF0(&actual, m + 0x10, &old);
        gain = func_00282E20(&actual);
        if (gain < func_00282E20(state)) {
            state->velocity.v[0] = actual.v[0];
            state->velocity.v[1] = actual.v[1];
        }
        if (func_00282E20(state) != 0) {
            char *sound = D_00188660 + state->sound * 0x70;

            if (*(char **)(sound + 0x88) != m || !((unsigned char *)sound)[0x74]) {
                state->sound = func_002E5CF8(0, 4, m);
            }
        } else {
            handle = state->sound;
            if (handle != -1) {
                unsigned char *sound = (unsigned char *)D_00188660 + handle * 0x70;

                if (*(char **)(sound + 0x88) == m && sound[0x74]) {
                    func_002E59F8(handle);
                }
            }
            state->sound = -1;
        }
    } else {
        handle = state->sound;
        if (handle != -1) {
            char *sound = D_00188660 + handle * 0x70;

            if (*(char **)(sound + 0x88) == m && ((unsigned char *)sound)[0x74]) {
                func_002E59F8(handle);
            }
        }
        state->sound = -1;
    }
}

typedef int TI128 __attribute__((mode(TI)));
typedef union { TI128 q; float f[4]; } Vector;
extern float func_00282C48(float f12);

int func_L01_0031B300(void *a0, void *a1, void *a2, void *a3) {
    Vector v, w;
    float f20;
    float f2;
    char *g;
    char *h;
    char *p;
    int v1;

    if (func_002761F8(a2, a3, 0x10, a0, 0) == 0)
        goto fail;
    g = (char *)&D_L01_001BF900;
    p = *(char **)(g + 0x18);
    if (p != 0) {
        v1 = *(short *)(p + 0xAA);
        if (v1 == 0x881 || v1 == 0)
            return 0;
        f20 = *(float *)(a0 + 0x18);
    } else {
        f20 = *(float *)(a0 + 0x18);
    }
    qcopy(&w, g + 0x40);
    h = g + 0x40;
    func_00282F20(w.f, w.f, 1.0f);
    func_00282CF0(&v, a3, g + 0x20);
    f2 = func_00282C48(func_00282DB0(v.f, w.f));
    func_00282F20(w.f, (float *)h, f2);
    func_00282CC0(a0 + 0x10, a0 + 0x10, &w);
    *(float *)(a0 + 0x18) = f20;
    return 1;
fail:
    return 0;
}


int func_L01_0031BC68(int a0, int a1, float phase) {
    float v = func_00283198(phase);
    return func_00283D38(a0, a1, v * 0.5f + 0.5f);
}




void func_L01_003208D0(void *a0, float *a1, int a2) {
    unsigned char *p = (unsigned char *)a0;
    float r;
    int i;

    if (p[0x23] == 0 && a2 == 0)
        return;

    r = func_00283B98(*a1, 0.14544412f);
    *a1 = r;
    r = func_00283198(r);
    i = func_00283D38(0x8000C020, 0x80008000, (r + 0.5f) * 0.5f);
    if (func_002A7878(0.0f, 1.0f) < 0.05f)
        i = func_00283D38(i, 0x8080FFFF, 0.3f);
    func_002AEC18(a0, i);

    if (a2 != 0) {
        if (p[0x23] < 0x3D)
            p[0x23] = p[0x23] + 3;
        else
            p[0x23] = 0x40;
    } else {
        if (p[0x23] >= 4)
            p[0x23] = p[0x23] - 3;
        else
            p[0x23] = 0;
    }
}

/* One entity of the group: the kind word is at 0xAA. */
typedef struct L01Thing {
    u8 pad[0xAA];
    s16 kind;
} L01Thing;

/* The group: the count is at 0x44, the list of entities at 0x18C. */
typedef struct L01Group {
    u8 pad[0x44];
    s16 count;
    u8 pad46[0x18C - 0x46];
    L01Thing *items[1];     /* bounded by count */
} L01Group;

extern L01Group D_L01_001BD1C0;
extern u8 D_001A7A40[] __attribute__((sda));
extern u8 D_L01_001B1E60[] __attribute__((sda));
extern f32 D_L01_001B1E80[] __attribute__((sda));
extern void func_0029F978(u8 *p, int a1, u8 *a2);

void func_L01_003209F8(L01Thing *entry, s32 arg1, s32 id, f32 value)
{
    L01Thing *e;
    s32 wanted;
    s32 i;

    if (D_L01_001A8F40[0] != 2)
        return;
    if (D_001A7A40[0] == 0)
        return;
    wanted = entry->kind;
    if (id != -1)
        wanted = id;
    for (i = 0; i < D_L01_001BD1C0.count; i++) {
        e = D_L01_001BD1C0.items[i];
        if (e->kind != wanted)
            continue;
        if (D_L01_001B1E60[1] != 0)
            continue;
        func_0029F978((u8 *)e, arg1, D_L01_001B1E60);
        D_L01_001B1E80[0] = value;
        D_L01_001B1E80[1] = value;
        D_L01_001B1E80[2] = value;
    }
}

int func_L01_00321178(char *a0, char *a1) {
    float v = func_002E3B10(*(float *)(a1 + 0) - *(float *)(a0 + 0x10),
                            *(float *)(a1 + 4) - *(float *)(a0 + 0x14));
    return func_002B50E0(a0, a1, v);
}

int func_L01_00322288(int a0, float f12) {
    char *p = func_00321F08(a0);
    if (p == 0)
        return 0;
    func_003140B0((char *)a0 + 0xF8, p + 0xB4, 0, f12, *(float *)(p + 0x14),
                  *(float *)(p + 0x18), *(float *)(p + 0x1C));
    return 1;
}



/* shared native body of family d1b66aa7f0ecd20d */
void func_L01_003242C8(char *dst, int x, int idx)
{
    Sep6 t;
    t = D_L01_001AA550;
    if (x > 999999) {
        int m = x / 1000000;
        int w = x % 1000000;
        func_00115DA8_2(dst, D_L01_001AA568, m, t.p[idx % 6], w / 1000,
                          t.p[idx % 6], w % 1000);
    } else if (x >= 1000)
        func_00115DA8_2(dst, D_L01_001AA578, x / 1000,
                          t.p[idx % 6], x % 1000);
    else
        func_00115DA8_2(dst, D_L01_001AA588, x);
}


extern int func_00115AC0(char *dst, char *src, int len);

/* Expands a template: copies src into the scratchpad, then writes it to out, replacing %d (next number) and %<n>d (n-th number) with the numbers listed in nums (every second int, up to ten, stopped by -1). */
void func_L01_00324410(char *out, char *src, int *nums)
{
    int tab[10];
    unsigned char buf[32];
    int i;
    int *p;
    int *q;
    unsigned char *s;
    char *w;
    int n;
    int cnt;
    int v;

    p = nums;
    i = 0;
    func_00115AC0((char *)0x70000000, src, 0xFF);

    q = tab;
    for (;;) {
        p += 2;
        v = p[-2];
        if (v == -1)
            break;
        *q++ = v;
        i++;
        if (i >= 10)
            break;
    }

    s = (unsigned char *)0x70000000;
    w = out;
    cnt = 0;
    while (*s != 0) {
        if (*s == '%') {
            if (s[1] == 'd') {
                v = cnt++;
                s += 2;
            } else {
                v = s[1] - '0';
                s += 3;
            }
            func_L01_003242C8((char *)buf, tab[v], 0);
            n = 0;
            if (*buf != 0) {
                while (buf[n] != 0 && n < 32) {
                    *w = buf[n];
                    n++;
                    w++;
                }
            }
            *w = 0;
        } else {
            *w = *s;
            s++;
            w++;
        }
    }
    *w = 0;
}


/* func_L01_00324550 is in L01_00324550-narrowsave.c. */

/* func_L01_003245E0 is defined in L01_002A7248-g8.c (this unit has no $gp access for it). */

void func_L01_003246A0(int a) {
    char *base = D_00139A28;
    char *p;
    base = base + 0xC;
    p = base + a * 16;
    if (*(int *)p == 0)
        *(int *)p = 1;
}

/* func_L01_003246D0 is defined in L01_003246D0.c. */

/* Scans the half-open span of the pair table for the caller's key. */
int func_L01_003246F8(int key) {
 unsigned n=(unsigned)D_L01_001A79F0;
 int i;
 int end;
 if(n>=0x13) return 0;
 i=D_L01_0028EA50[n];
 end=D_L01_0028EA50[n+1];
 while(i<end) {
  if(D_L01_001C5D20[i]==key) return i;
  i++;
 }
 return -1;
}

typedef union {
    ClosestPointQuad q;
    float v[4];
} ParticleVec;

typedef struct SpanParticle {
    unsigned char f0;
    unsigned char f1;
    unsigned char texture;      /* 2 */
    unsigned char f3;
    int color0;                 /* 4 */
    char pad8;
    unsigned char f9;
    short kind;                 /* 0xA */
    int color1;                 /* 0xC */
    ParticleVec start;          /* 0x10: v[3] is the life */
    ParticleVec end;            /* 0x20: start plus the scaled velocity, v[3] = 1 */
    ParticleVec velocity;       /* 0x30: v[3] is the caller's scale */
} SpanParticle;

/* RAC1 counterpart: src/overlays/shared/span_particle.c, spawn_span_particle. */
/* Spawns a span particle of the given kind (0 to 2) at pos, moving along vec and carrying scale. */
void func_L01_00326DD8(float *pos, int kind, float *vec, float scale)
{
    float velocity[4];
    float *velocityPtr = velocity;
    float scaled[4];
    float end[4];
    SpanParticle *p;
    int alpha;
    float speed;
    float life;
    int texture;

    *(ClosestPointQuad *)velocity = *(ClosestPointQuad *)vec;
    p = func_00325768(0);
    if (p != 0) {
        alpha = 0;
        texture = kind;
        life = 0.0f;
        speed = life;
        switch (texture) {
        case 0:
            alpha = 0x14;
            life = 0.015f;
            speed = func_00310580(0.01f, 1.0f);
            break;
        case 1:
            alpha = 0xD;
            life = 0.5f;
            speed = func_00310580(1.0f, 5.0f);
            break;
        case 2:
            alpha = 0xD;
            life = 1.0f;
            texture = 1;
            speed = func_00310580(20.0f, 30.0f);
            break;
        }
        *(ClosestPointQuad *)scaled = *(ClosestPointQuad *)velocityPtr;
        func_002E3738(scaled, scaled, speed);
        p->kind = kind;
        p->color0 = ((alpha >> 2) << 24) | 0x606060;
        p->color1 = (alpha << 24) | 0x907070;
        p->f9 = func_002E45B8(4.0f) + 0x60;
        p->f3 = 0x44;
        p->f1 = 3;
        p->texture = D_L01_001FF040[texture];
        p->start.q = *(ClosestPointQuad *)pos;
        func_002E3470(end, pos, scaled);
        p->end.q = *(ClosestPointQuad *)end;
        p->start.v[3] = life;
        p->end.v[3] = 1.0f;
        p->velocity.q = *(ClosestPointQuad *)velocityPtr;
        p->velocity.v[3] = scale;
    }
}

typedef int Quad331CA0 __attribute__((mode(TI)));
typedef struct { unsigned char b0, b1, b2, b3; int color; unsigned char seed, alpha; unsigned short size; float life; union { Quad331CA0 q; float f[4]; } position; float payload[8]; } Particle331CA0;
extern Particle331CA0 *func_002B9030(int kind);
extern float func_002A7878(float low, float high);
extern int func_00283CF0(float value);
extern unsigned char *D_L01_001FF164;

/* Spawns the burst particle of the given kind at position, carrying the velocity and the size scale in its payload. */
void func_L01_00331CA0(Quad331CA0 *position, int kind, Quad331CA0 *velocity, float scale)
{
    Quad331CA0 saved = *velocity;
    Quad331CA0 *vp = &saved;
    Particle331CA0 *p = func_002B9030(0x49);

    if (p) {
        float life = 0.0f;
        int tint = 0;

        switch (kind) {
        case 0:
            func_002A7878(0.25f, 0.25f);
            life = 0.12f;
            tint = 0x20;
            break;
        case 1:
            func_002A7878(1.0f, 1.0f);
            life = 0.5f;
            tint = 0xD;
            break;
        }
        p->size = 0x37;
        p->color = (tint << 24) | 0xFFFFFF;
        p->alpha = func_00283CF0(4.0f) + 0x20;
        p->b1 = 0;
        p->b3 = 0x48;
        p->b2 = D_L01_001FF164[kind];
        p->life = life * 210000.0f;
        p->seed = func_002A7878(0.0f, 360.0f);
        p->position.q = *position;
        *(Quad331CA0 *)p->payload = *vp;
        p->payload[3] = scale;
    }
}


/* func_L01_00331E08 is in L01_00331E08.c. */

/* Averages each 16-byte record of the table the argument points at against the record
   (i + 1) % n, storing the result in the record's own +0xC field and returning the
   running sum; a null argument reports and answers -1.0f. */
float func_L01_003377C8(unsigned char *a0) {
    unsigned char *s2;
    unsigned char *q;
    int s0, s1, n;
    float f20;
    float f0;

    s2 = a0;
    f20 = 0.0f;
    if (s2 == 0) {
        func_002A6CF0((int)D_L01_001AA6F8);
        return -1.0f;
    }
    n = *(int *)s2;
    if (n <= 0)
        return f20;
    s0 = 0;
    do {
        s1 = s0 + 1;
        f0 = func_002E3618(s2 + 0x10 + (s0 << 4), s2 + 0x10 + ((s1 % n) << 4));
        q = s2 + (s0 << 4);
        *(float *)(q + 0x1C) = f0;
        f20 += f0;
        s0 = s1;
        n = *(int *)s2;
    } while (s0 < n);
    return f20;
}

typedef struct PathPoint {
    float v[4];
} PathPoint;

/* A closed path: the point count, then the points from offset 0x10. */
typedef struct Path {
    int count;
    int pad04[3];
    PathPoint points[1];
} Path;

typedef struct PathFollower {
    char pad00[0x10];
    PathPoint position;
} PathFollower;

/* Moves distance further along the closed path from the given segment, walking forward or
   back by direction; writes the point reached to out and returns the segment it lies on. */
int func_L01_00337888(PathFollower *follower, Path *path, PathPoint *out, int segment, int direction, float distance)
{
    float toNext[4];
    float toFollower[4];
    int next;
    int last;
    float length;
    float step = distance;

    last = path->count - 1;
    if (segment == last)
        next = direction > 0 ? 0 : last - 1;
    else if (segment == 0) {
        next = last;
        if (direction > 0)
            next = 1;
    } else
        next = segment + direction;
    func_00282CF0(toNext, &path->points[next], &path->points[segment]);
    length = func_00282DF0(toNext);
    func_00282F20(toNext, toNext, 1.0f);
    func_00282CF0(toFollower, &follower->position, &path->points[segment]);
    distance = func_00282DB0(toFollower, toNext);
    distance += step;
    if (length < distance) {
        last = path->count - 1;
        segment = next;
        if (segment == last)
            next = direction > 0 ? 0 : last - 1;
        else if (segment == 0) {
            next = last;
            if (direction > 0)
                next = 1;
        } else
            next = segment + direction;
        func_00282CF0(toNext, &path->points[next], &path->points[segment]);
        distance -= length;
        func_00282F20(toNext, toNext, 1.0f);
    }
    func_00282F20(toNext, toNext, distance);
    func_00282CC0(out, toNext, &path->points[segment]);
    return segment;
}

int func_L01_00355BA0(int index, int value) {
    char *p = D_00188660 + index * 0x70;
    *(unsigned short *)(p + 0x80) = value;
    return 1;
}


void func_L01_00371228(int a0, int a1) {
    int i = func_003711D8(a0);
    if (i >= 0)
        D_L01_001395B8[i] |= (unsigned char)(1 << a1);
}

INCLUDE_ASM("asm/levels", func_L01_003801B8);

/* func_L01_003808C0 is in L01_003808C0-g8.c for its GP accesses. */

/* func_L01_0038EF40 is in L01_0038EF40.c: its unit needs -g. */

/* A model with kind 0x12 is exempt from the trigger's visibility switches. */
#define SPATIAL_TRIGGER_EXEMPT(p) \
    ((p) && (p)->model && (p)->model->kind == 0x12)

typedef struct TriggerSettings {
    char pad00[0x7C];
    signed char f7C;
    signed char f7D;
    char pad7E;
    signed char f7F;
} TriggerSettings;

/* Applies a trigger's settings to the moby at index: each switch is positive to turn its
   effect on, negative to turn it off; inactive reverses them. */
void func_L01_003907B8(int index, TriggerSettings *settings, int active)
{
    Moby *p = (Moby *)D_L01_001B255C + index;

    if (p) {
        if (active) {
            if (settings->f7C > 0)
                p->state &= ~2;
            else if (settings->f7C < 0)
                p->state |= 2;
            if (settings->f7D > 0 && !SPATIAL_TRIGGER_EXEMPT(p)) {
                p->f31 = 1;
                p->state &= ~1;
            } else if (settings->f7D < 0 && !SPATIAL_TRIGGER_EXEMPT(p)) {
                p->f31 = 0;
                p->state |= 1;
            }
            if (settings->f7F > 0 && p->model) {
                p->f98 = p->model->f10;
            } else if (settings->f7F < 0 && p->model) {
                p->f98 = 0;
            }
        } else {
            if (settings->f7C > 0 && !SPATIAL_TRIGGER_EXEMPT(p)) {
                p->state |= 2;
            } else if (settings->f7C < 0 && !SPATIAL_TRIGGER_EXEMPT(p)) {
                p->state &= ~2;
            }
            if (settings->f7D > 0 && !SPATIAL_TRIGGER_EXEMPT(p)) {
                p->f31 = 0;
                p->state |= 1;
            } else if (settings->f7D < 0 && !SPATIAL_TRIGGER_EXEMPT(p)) {
                p->f31 = 1;
                p->state &= ~1;
            }
            if (settings->f7F > 0) {
                p->f98 = 0;
            } else if (settings->f7F < 0) {
                p->f98 = p->model->f10;
            }
        }
    }
}

#undef SPATIAL_TRIGGER_EXEMPT

void func_L01_003909E0(int a0, int a1, int a2, int a3) {
    unsigned short *p = D_L01_001FB020[a2];
    if (p != 0) {
        do {
            func_003907B8(*p & 0x7FFF, a1, a3);
        } while (*(short *)p++ >= 0);
    }
}

extern int func_002A8AF0(float *, float *, int);
extern int func_002ACBC8(void *, int);

void func_L01_00390A50(char *object)
{
    SpatialTriggerSettings *settings;
    ClosestPointQuad point;
    int flag = 0;
    int i;
    int j;
    int k;
    int *mobys;
    int forced;
    char *path;

    settings = *(SpatialTriggerSettings **)(object + 0x68);
    *(unsigned char *)(object + 0x30) = 0xFF;
    if (settings->switches[2])
        qcopy(&point, D_L01_001B94C0);
    else
        qcopy(&point, D_00189EA0);
    forced = *(unsigned char *)(object + 0x95);
    if (forced == 0) {
        if (settings->radius > 0.0f && func_002E3618(object + 0x10, &point) < settings->radius)
            flag = 1;
        if (!flag) {
            if (settings->path != -1) {
                path = D_L01_001FE180[settings->path];
                flag = func_002A8AF0((float *)&point, (float *)(path + 0x10), *(int *)path) != 0;
            }
        }
        if (!flag) {
            for (i = 0; ; i++) {
                if (i >= 6)
                    goto done;
                if (settings->volumes[i] == -1)
                    continue;
                if (func_002ACBC8(&point, settings->volumes[i]))
                    break;
            }
            goto set;
        }
    } else {
        do {
            if (forced == 1) {
set:
                flag = 1;
            } else {
                flag = 0;
            }
        } while (0);
    }
done:
    if ((flag && !*(unsigned char *)(object + 0xBC)) ||
        (!flag && *(unsigned char *)(object + 0xBC)) ||
        !*(unsigned char *)(object + 0x20)) {
        if (flag)
            *(unsigned char *)(object + 0xBC) = 1;
        else
            *(unsigned char *)(object + 0xBC) = 0;
        *(unsigned char *)(object + 0x20) = *(unsigned char *)(object + 0xBC) + 1;
        mobys = settings->mobys;
        for (j = 0; j < 12; j++) {
            if (settings->lists[j] != -1)
                func_L01_003909E0((int)object, (int)settings, settings->lists[j], flag);
        }
        for (k = 0; k < 11; k++) {
            if (mobys[k] != -1)
                func_L01_003907B8(mobys[k], (TriggerSettings *)settings, flag);
        }
    }
}

void func_L01_00390C60(char *a0)
{
    char *v0 = *(char **)(a0 + 0x68);
    char *v1;
    unsigned char a1;

    if (v0 == 0)
        return;
    v1 = *(char **)v0;
    if (v1 == 0)
        return;
    a1 = *(unsigned char *)(v1 + 0x20);
    if (a1 == 0xFE)
        return;
    if (a1 == 0xFD)
        return;
    if (*(unsigned short *)(v1 + 0x34) & 1)
        *(unsigned short *)(a0 + 0x34) |= 0x41;
    else
        *(unsigned short *)(a0 + 0x34) &= 0xFFBE;
}

void func_L01_00394148(void)
{
    L01Thing *e;
    s32 i;

    if (D_L01_001A8F40[0] != 2)
        return;
    if (D_001A7A40[0] == 0)
        return;
    for (i = 0; i < D_L01_001BD1C0.count; i++) {
        e = D_L01_001BD1C0.items[i];
        if (e->kind != 0x398 && e->kind != 0x1BF)
            continue;
        if (D_L01_001B1E60[1] != 0)
            continue;
        func_0029F978((u8 *)e, 0, D_L01_001B1E60);
        D_L01_001B1E80[0] = 2.1f;
        D_L01_001B1E80[1] = 2.1f;
        D_L01_001B1E80[2] = 2.1f;
    }
}

INCLUDE_ASM("asm/levels", func_L01_00394240);
