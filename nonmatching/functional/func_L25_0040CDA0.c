/* functional: medium. Near-miss draft of retail size with the same frame: differences are allocation and scheduling, with some block order; paths the captured calls never take are unproven. */
/* sol-high retained draft, USA v1.01, game compiler -O2 -G8.
 * check.py: 1128/1128 bytes, 0 of 1 places match.
 * Six non-relocation instructions differ: the +0x24 and +0x78 context
 * stores are exchanged (+0xE4/+0xF4), the callback flag's constant remains
 * live from entry instead of being rematerialized at +0x158, and the second
 * vector-pair clear uses v0 rather than v1 (+0x304/+0x358/+0x35C).
 * Typed context/inventory views and MACRO_ADDR scalar declarations recover
 * retail's high-address lifetimes and the empty wait loop's bgez. A named
 * u32 completion-test result preserves sllv/and rather than srav/andi.
 * The four timer initializations are ordered to reproduce retail scheduling.
 * Callback arguments are 001B0CC0/001B0CB0, corrected from the earlier draft.
 * Explicit initialization pointer and chained second clear did not close
 * the remaining differences. No linked build was run. Required declarations
 * are included below; next useful input is independent lifetime/clear evidence.
 */
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
extern void func_00288E18(int,int);
extern int func_00282948(void *);
extern void func_L05_00379B60(void);
extern void func_L05_0030C930(int,int);
extern int func_002E5DA0(int,int,char *,int);
extern int func_L25_0040D208(void);
extern void func_0029B758(int,void *);
extern void func_L05_00442828(void *,void *,int);
extern void func_L25_003752D8(void *);
extern void func_L25_00376FE0(void *,float);
extern void func_L25_00377608(void *,float);
extern void func_L05_00445B58(void *,void *);
extern void func_L05_0037B210(void);
extern void func_00288CB0(int,int);
extern void func_L05_0037B108(void);
extern int func_L05_00442860(void);
#define I(p,o) (*(int *)((char *)(p)+(o)))
#define F(p,o) (*(float *)((char *)(p)+(o)))
#define B(p,o) (*(unsigned char *)((char *)(p)+(o)))
#define H(p,o) (*(unsigned short *)((char *)(p)+(o)))


void func_L25_0040CDA0(char *obj)
{
    char *state = *(char **)(obj+0x68);
    float a[4] __attribute__((aligned(16)));
    float b[4] __attribute__((aligned(16)));
    float c[4] __attribute__((aligned(16)));
    float d[4] __attribute__((aligned(16)));
    int i;
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
        ctx->owner=obj;
        D_L25_001B3060=540;
        if (D_0018C0B0) H(D_0018C0B0,0x34)|=0x41;
    case 1:
        
        if (!D_0018C958.dialogue) func_00288E18(0xa16,0x6d);
        
        if (func_00282948(state+0x34)) D_L25_00221850.timerVisible=0;
        else D_L25_00221850.timerVisible=1;
        func_L05_00379B60();
        func_L05_0030C930((int)(D_L25_001B2904*-224.0f+0.5f),2);
        qcopy(obj+0x10,(void *)((I(state,0x20)<<8) + D_L25_001B209C + 0x10));
        if (D_00138324&0x10) func_002E5DA0(0,0,obj,0xeee);
        if (D_L25_001A904C && !D_L25_001B0CDC) {
            func_0029B758(0,func_L25_0040D208);
            D_L25_001B0CDC=active;
        }
        for (i=6;i>=0;i--) {}
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
            func_L25_003752D8((void *)1);
            func_L25_00376FE0(a,10.0f); func_L25_00377608(b,10.0f);
            *(Quad *)d = *(Quad *)c = 0;
            c[0]=417.18f; c[1]=454.03f; c[2]=532.6f;
            d[0]=420.93f; d[1]=413.79f; d[2]=534.54f;
            func_L05_00445B58(c,d);
        } else {
            if (func_00282948(state+0x2c)) {
                func_L05_0037B210(); func_0029B758(0,0);
                D_001A7C01=1; func_00288CB0(2,1);
            } else {
                if (!D_L25_001B0CF8) {
                    func_L05_0037B108(); D_L25_001B0CF8=1;
                }
                { u32 seen = D_0018C958.completed & (1 << D_001A79F0);
                if (!seen) func_00288E18(0xa36,0x8d); }
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
