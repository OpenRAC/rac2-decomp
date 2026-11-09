/* func_US2_L25_0040E340, the USA v2.00 copy of func_L25_0040CDA0: the same C, where rename func_00288E18 becomes func_US2_00289840; rename func_0029B758 becomes func_US2_0029C548. */
/* func_US2_L25_0040E340, the level's mission update (setup, timer, completion).
   The function lives in its own small-data unit; its callees func_L25_003752D8, 00376FE0 and
   00377608 are in L25_00373ED0-g8.c and really return void.

   The timer y passes through label_y, the HUD label idiom (see its comment, and
   L25_00373ED0-fade-g8.c). Its tests leave no instruction but keep the 1 in $s2 and decide
   the registers of the later quadword clears. Case 1 sets active = 1 again before
   func_L05_00379B60: retail sets $s2 there (addiu s2,zero,1 at +0x158). The countdown from six is
   in retail too (its backward branch and padding). */
#include "common.h"
typedef unsigned int Quad __attribute__((mode(TI)));

typedef struct MissionContext {
    float *health;
    char pad04[0xC];
    int paused;
    int completed;
    char pad18[0xC];
    int enabled;
    int pad28;
    int timerVisible;
    float scale;
    char pad34[0x20];
    int (*deathCallback)(char *, int);
    char pad58[0x20];
    char *owner;
} MissionContext;
typedef struct InventoryView {
    char pad00[0x51c];
    unsigned short dialogue;
    char pad51e[0x186];
    unsigned int completed;
} InventoryView;
extern MissionContext D_L25_00221850;
extern InventoryView D_0018C958;
extern char *D_L25_001B0CE0 __attribute__((sda));
extern int D_L25_001B0CD0 __attribute__((sda)), D_L25_001B0CD4 __attribute__((sda));
extern int D_L25_001B0CD8 __attribute__((sda)), D_L25_001B0CDC __attribute__((sda));
extern int D_L25_001B0CC0 __attribute__((sda)), D_L25_001B0CB0 __attribute__((sda));
extern int D_L25_001B0CF8 __attribute__((sda));
extern char *D_0018C0B0 __attribute__((nosda));

extern int D_L25_001B3060 MACRO_ADDR, D_L25_001B1BC8 MACRO_ADDR;
extern int D_L25_001B209C MACRO_ADDR;
extern int D_00138324 __attribute__((nosda));
extern char *D_L25_001A904C MACRO_ADDR;
extern float D_L25_001B2904 MACRO_ADDR;
extern unsigned char D_001A7C01 MACRO_ADDR;
extern int D_001A79F0 MACRO_ADDR;
extern int func_L25_0040DCD0(char *,int);
extern int func_US2_00289840(int,int);
extern int func_00282948(void *);
extern void func_L05_00379B60(void);
extern void func_L05_0030C930(int,int);
extern int func_002E5DA0(int,int,char *,int);
extern int func_L25_0040D208(void);
extern void func_US2_0029C548(int,void *);
extern void func_L05_00442828(void *,void *,int);
extern void func_L05_00445B58(void *,void *);
extern void func_L05_0037B210(void);
extern void func_00288CB0(int,int);
extern void func_L05_0037B108(void);
extern int func_L05_00442860(void);
#define I(p,o) (*(int *)((char *)(p)+(o)))
#define B(p,o) (*(unsigned char *)((char *)(p)+(o)))
#define H(p,o) (*(unsigned short *)((char *)(p)+(o)))

extern void func_L25_003752D8(u8 *);
extern void func_L25_00376FE0(u8 *, f32);
extern void func_L25_00377608(u8 *, f32);

extern int D_L25_001B2900;

/* label_y, the HUD label idiom (accepted 7 November 2026; one shared definition, `active` the
   literal 1 at every call). Its tests do not change the result: flow deletes their stores and
   jump2 their jumps, but only after allocation and both scheduling passes. */
static __inline__ int label_y(void *handle, float value, float scale, float half, int active)
{
    int mode = D_L25_001B2900;
    float scaled = value * scale + half;
    int result = (int)scaled;
    void *copy;

    if (mode == active)
        scaled = scale;
    if (handle != 0)
        scaled = scale;
    copy = handle;
    if (copy != 0)
        scaled = half;
    return result;
}

void func_US2_L25_0040E340(char *obj)
{
    char *state = *(char **)(obj+0x68);
    float a[4] __attribute__((aligned(16)));
    float b[4] __attribute__((aligned(16)));
    float c[4] __attribute__((aligned(16)));
    float d[4] __attribute__((aligned(16)));
    int delay;
    int active = 1;
    MissionContext *ctx;
    switch (B(obj,0x20)) {
    case 0:
        ctx = &D_L25_00221850;
        
        ctx->scale=8.0f;
        ctx->deathCallback=func_L25_0040DCD0;
        D_L25_001B0CE0=obj;
        D_L25_001B0CD0=0; D_L25_001B0CD4=0;
        D_L25_001B0CD8=0; D_L25_001B0CDC=0;
        H(obj,0x32)=0x1ff; B(obj,0x30)=0xff; B(obj,0x20)=1;
        I(state,0x2c)=150; I(state,0x30)=300;
        I(state,0x38)=180; I(state,0x34)=720; I(state,0x24)=0;
        ctx->health=*(float **)state;
        ctx->enabled=1;
        D_L25_001B3060=540;
        ctx->owner=obj;
        if (D_0018C0B0) H(D_0018C0B0,0x34)|=0x41;
    case 1:
        
        if (!D_0018C958.dialogue) func_US2_00289840(0xa16,0x6d);
        
        if (func_00282948(state+0x34)) D_L25_00221850.timerVisible=0;
        else D_L25_00221850.timerVisible=1;
        active = 1;
        func_L05_00379B60();
        func_L05_0030C930(label_y(obj, -2.3e+02f, D_L25_001B2904, 0.5f, 1),2);
        qcopy(obj+0x10,(void *)((I(state,0x20)<<8) + D_L25_001B209C + 0x10));
        if (D_00138324&0x10) func_002E5DA0(0,0,obj,0xeee);
        if (D_L25_001A904C && !D_L25_001B0CDC) {
            func_US2_0029C548(0,func_L25_0040D208);
            D_L25_001B0CDC=active;
        }
        /* Retail executes this counted wait before reading the mission state:
           6, decrement, padded backward bgez, decrement in its delay slot. */
        for (delay=6; delay>=0; delay--) {}
        if (D_L25_00221850.paused || D_L25_001B1BC8<6) break;
        if (D_L25_00221850.completed<=0) {
            D_L25_00221850.timerVisible=1;
            if (!func_00282948(state+0x2c)) break;
            I(state,0x2c)=540;
            func_L05_00442828(&D_L25_001B0CC0,&D_L25_001B0CB0,240);
            *(Quad *)a=0; *(Quad *)b=0;
            B(obj,0x20)=3;
            a[0]=359.0f; a[1]=440.0f; a[2]=524.0f;
            b[0]=403.0f; b[1]=456.0f; b[2]=524.0f;
            func_L25_003752D8((u8 *)1);
            func_L25_00376FE0((u8 *)a,10.0f); func_L25_00377608((u8 *)b,10.0f);
            *(Quad *)d = *(Quad *)c = 0;
            c[0]=417.18f; c[1]=454.03f; c[2]=532.6f;
            d[0]=420.93f; d[1]=413.79f; d[2]=534.54f;
            func_L05_00445B58(c,d);
        } else {
            if (func_00282948(state+0x2c)) {
                func_L05_0037B210(); func_US2_0029C548(0,0);
                D_001A7C01=1; func_00288CB0(2,1);
            } else {
                if (!D_L25_001B0CF8) {
                    func_L05_0037B108(); D_L25_001B0CF8=1;
                }
                { u32 seen = D_0018C958.completed & (1u << D_001A79F0);
                if (!seen) func_US2_00289840(0xa36,0x8d); }
            }
        }
        break;
    case 2:
        break;
    case 3:
        
        if (!func_L05_00442860()) {
            D_L25_00221850.timerVisible=0;
            D_L25_00221850.completed++;
            B(obj,0x20)=active;
        }
        break;
    }
}
