/* func_L30_0040B9D8: opus-1 worker (v1989), USA v1.01, game -O2 -G8 -ffunction-sections.
 * Tier: one instruction short with allowed forms; exact bytes only with a form the rules forbid.
 * Best check, this file as written: 2196 bytes versus 2200 retail, 0 of 1 places match.
 * Only difference: retail's second `addiu v1,zero,1` in case 0 (before `swc1 f0,0x60(s2)`, used by
 * `sb v1,0x20(s3)`) is missing, and one beqz displacement follows from it. Compile as a -g8 unit.
 *
 * EXACT-BYTES FORM, NOT ALLOWED (invented test on an unrelated global, dead store in its arm):
 * replace the case 0 health line with
 *   {float t; if (D_L30_001A8F00) t=1.0f; t=D_L30_001B17B0;
 *    D_00189E20.maxHealth=D_00189E20.health=s->health=t;}
 * That gave 2200 bytes, 1 of 1 places match; PAL and US2 are "in neither catalogue". Level link
 * check not run on it.
 *
 * Why it works: qzero_nc's bare volatile asm flushes cse1, so obj->state=1 keeps its own QI
 * constant, scheduled in retail's slot. reload_cse_regs_1 then deletes it as a no-op, because v1
 * already holds SI 1 and QI is narrower. It survives only if a CODE_LABEL or a v1 set lies between
 * `sw v1,D_L30_001B180C` and that constant at reload time. An arm emptied by flow1 keeps the label
 * through reload; flow2 then drops the branch, the test and its load, so the bytes cannot
 * identify retail's real test. Measured with one test only, on a loaded global.
 *
 * Ruled out for the v1 kill. Compiled: a dead `s->count=2` store (the sb between the stores keeps
 * it alive in flow2's mem_set_list); a written-out else arm for the flag store (PRE moves s4/s1 out
 * of the test block, which needs the critical edge of `if (!copied) memcpy(...);`, and no
 * cross-jump resulted). Read from the compiler source, not compiled: lq to v0 (TImode is one GPR on
 * the R5900); output_block_move (no lq). Reasoned only, not compiled: other dead-store targets; a
 * test on activate (cprop should fold it); a test on copied (it must die at the branch for a3 to be
 * reused by the memcpy loops). Null tests on s or obj are forbidden. No sibling function with this
 * palette and health code was found by searching src for the memcpy and maxHealth forms.
 * To finish: recover what the test was. A DImode first constant would also keep the second one
 * (TRULY_NOOP_TRUNCATION fails from 64 bits), but no source form for that was found.
 *
 * Forms found here: char activate blocks the jump1 cmove, giving retail's bnel/movz shape; typed
 * PaletteRow computed pointer for the palette read; int return of func_L00_002C42E0 (the callee's
 * true type) gives case 4's -1 in v1; func_002ABBB8's real interleaved prototype fixes case 5;
 * the call in case 3's tail is func_002A7750, not func_002A7470.
 * Earlier draft corrections kept: state-nonzero always sets +0xA8 to 255; the +0x1A4 mask-0x4 gate
 * is positive; phase/bob tuning symbols were interchanged; case 6 shares the default exit, as
 * retail's seven-entry table does.
 *
 * closer D: reload_cse_regno_equal_p compares a CONST_INT by mode, so the second constant lives only with a label
 * between, or with a first constant in a wider mode. Moving the store to `copied = 1` gives 2200 bytes but puts the
 * first constant in a0 and costs 28 words. Per-arm flag stores give 2240 to 2244 bytes.
 */
#include "common.h"
#define F(p,o) (*(float *)((char *)(p)+(o)))
#define I(p,o) (*(int *)((char *)(p)+(o)))
#define P(p,o) (*(char **)((char *)(p)+(o)))
#define B(p,o) (*(unsigned char *)((char *)(p)+(o)))
#define H(p,o) (*(unsigned short *)((char *)(p)+(o)))
typedef struct { char pad[10]; unsigned short offset; char pad2[4]; } PaletteRow;
typedef struct {
 char pad0[0x80]; unsigned int position[4], rotation[4];
 char padA0[0xD0-0xA0]; unsigned int copyD0[4],copyE0[4];
 char padF0[0x33C-0xF0]; char *ground; int groundFlag;
 char pad344[0x1830-0x344]; char *vehicle; short vehicleId;
 char pad1836[6]; float health, maxHealth; int pad1844, healthPercent;
 char pad184C[0x1FB0-0x184C]; int cameraX; float cameraY;
 char pad1FB8[0x2290-0x1FB8]; char *hero; int state; int pad2298,mode;
 char pad22A0[0x24CC-0x22A0]; int heroHealth;
} VehicleHeroState;
extern VehicleHeroState D_00189E20;
extern struct { char pad[0x1A0]; int held, pressed; } D_00138180;
extern int D_00138324;
extern int D_L30_001A8F00 __attribute__((sda));
extern unsigned char D_L30_001B18A8 __attribute__((sda));
extern float D_L30_001B179C __attribute__((sda));
extern float D_L30_001B17B0 __attribute__((sda));
extern float D_L30_001B16CC __attribute__((sda));
extern float D_L30_001B16D0 __attribute__((sda));
extern float D_L30_001B16D4 __attribute__((sda));
extern float D_L30_001B16D8 __attribute__((sda));
extern float D_L30_001B16DC __attribute__((sda));
extern float D_L30_001B16E0 __attribute__((sda));
extern float D_L30_001B17E8 __attribute__((sda));
extern float D_L30_001B17EC __attribute__((sda));
extern float D_L30_001B17B8 __attribute__((sda));
extern float D_L30_001B16F4 __attribute__((sda));
extern int D_L30_001B1780 __attribute__((sda));
extern int D_L30_001B180C __attribute__((sda));
extern int D_L30_001B1704 __attribute__((sda));
extern int D_L30_001B1708 __attribute__((sda));
extern char *D_L30_001B17B4 __attribute__((sda));
extern char *D_L30_001B1808 __attribute__((sda));
extern char *D_L30_001B27C4;
extern void func_L30_0040AE38(char *);
extern unsigned short D_L30_001BE9C0[][8];
extern char D_L30_0025CEB0[], D_L30_001B9DC0[];
extern char *func_002A9640(char *,int,int);
extern void func_002AB800(char *,void *), func_002AB8C0(char *,void *);
extern float func_00282E20(void *), func_002A0558(char *,char *), func_00283B98(float,float), func_00283198(float), func_00282E48(void *,void *);
extern int func_002B0C28(int,int,int), func_002A77E0(int), func_002B3868(char *);
extern int func_L00_002C42E0(int,int);
extern void func_L30_0040C270(char *,int), func_L00_002D2168(int,int,float), func_L08_0041E4F8(char *);
extern void func_002A7750(char *,int,int), func_0029FCC0(char *,int,void *), func_002A93B0(char *), func_L00_002E6EF8(void (*)(char *),void *);
extern void func_002ABBB8(void *, void *, void *, float, float, int, int, int, float, float, float, float, int, float, int, int, int, int, int);
extern void func_002AEF28(char *,void *,void *,float,float,float);
extern void *memcpy(void *,const void *,unsigned int);
typedef struct {
 float velocity[4]; char pad10[16]; float pitch,yaw,roll,pad2C;
 float spawn[4]; char pad40[8]; float phase, bob, yawRate, pitchRate, height, pad5C, health;
 int classIndex; union { float throttle; int bits; } power;
 char pad6C[2]; unsigned char hitTimer; char pad6F[0x80-0x6F];
 unsigned char flash[16]; char *lastHit; int flags, alpha, count;
} VehicleVars;
typedef struct {
 char pad0[0x10]; float position[4]; unsigned char state; char pad21[3];
 char *classData; char pad28[4]; float damage; unsigned char color, visible;
 char pad32[0x68-0x32]; VehicleVars *vars; char pad6C[3]; unsigned char delay;
 char pad70[0x96-0x70]; unsigned short timer; int flags, animation;
 char padA0[8]; unsigned char hitFlag; char padA9[0xF0-0xA9]; float rotation[4];
} MuseumVehicle;
void func_L30_0040B9D8(MuseumVehicle *obj) {
    VehicleVars *s; char *hit;


    char activate;
    float k, scaled, rollRate, yawRate, pitchRate, bob;
    unsigned int pos[4] __attribute__((aligned(16)));
    s=obj->vars;
    if (obj->state) {
        obj->position[2]=s->height;
        hit=func_002A9640(obj,1,0);
        if (hit && P(hit,0x20) && *(short *)(P(hit,0x20)+0xAA)!=0xF2F && *(short *)(P(hit,0x20)+0xAA)!=0x942) {
            if (*(short *)(P(hit,0x20)+0xAA)!=0xFFF && (P(hit,0x20)!=s->lastHit || !s->hitTimer)) {
                B(s,0x87)=0xD2;B(s,0x88)=0xD2;B(s,0x89)=0xD2;
                func_002AB800(obj,&s->flash);
                s->health-=F(hit,0x2C);
                D_00189E20.health=s->health;
                if (s->health<=0.0f) obj->state=5;
                s->lastHit=P(hit,0x20);
                s->hitTimer=D_L30_001B18A8;
            }
        }
        obj->hitFlag=0xFF;
    } else s->height=obj->position[2];
    func_002AB8C0(obj,&s->flash);

    obj->damage=F(obj->classData,0x24)*D_L30_001B179C;
    if (D_00189E20.vehicle==obj) D_00189E20.healthPercent=(int)(D_00189E20.health/D_L30_001B17B0*200.0f);
    activate=0;
    switch (obj->state) {
    case 0: {
        char *palette; int copied;
        palette=D_L30_001B27C4+((PaletteRow *)((s->classIndex+D_L30_001B1780)*16+(char *)D_L30_001BE9C0))->offset*16;
        D_L30_001B1808=palette;copied=D_L30_001B180C;
        s->alpha=255; s->flags=0;
        if (!copied) memcpy(D_L30_0025CEB0,palette,0x400);
        D_L30_001B180C=1;
        qcopy(&s->spawn,obj->position); qzero_nc(s);
        D_00189E20.maxHealth=D_00189E20.health=s->health=D_L30_001B17B0;
        obj->state=1;
        s->power.bits=0;s->count=0;
        break; }
    case 1:
        if (func_00282E20(s)>0.004166667f) func_L30_0040C270(obj,0);
        if (D_00189E20.state==28 || D_00189E20.state==22 || D_00189E20.state==57 || D_00189E20.state==111 ||
            D_00189E20.mode==2 || D_00189E20.mode==4 || D_00189E20.mode==3 || D_00189E20.mode>=13 ||
            D_00189E20.mode==7 || D_00189E20.mode==10 || D_00189E20.mode==16 || D_00189E20.mode==5 || D_00189E20.state==98 ||
            D_00189E20.heroHealth<=0 || D_L30_001A8F00 || !D_00189E20.groundFlag) break;
        if (D_00189E20.ground && (*(short *)(D_00189E20.ground+0xAA)==0x13E || *(short *)(D_00189E20.ground+0xAA)==0x46F)) break;
        if (func_002A0558(obj,D_00189E20.hero)<D_L30_001B16CC && D_00189E20.state!=49) {
            int v=func_002B0C28(7,0x2798,1)!=0;
            if (D_00138180.pressed&16) activate=v;
        }
        if (activate) {
            func_L00_002C42E0(49,0);func_L00_002D2168(D_L30_001B1704,0,15.0f);
            qcopy(D_00189E20.rotation,obj->rotation);qcopy(D_00189E20.position,obj->position);
            D_00189E20.vehicle=obj;obj->state=3;obj->flags=0;I(D_00189E20.hero,0x9C)=-1;
        }
        break;
    case 3:
        if (D_00138180.held&4) {
            s->power.throttle-=D_L30_001B17E8;
            if (!func_002A77E0(9) || (D_00138180.pressed&4)) func_L08_0041E4F8(obj);
        } else s->power.throttle+=D_L30_001B17EC;
        if (D_L30_001B1708!=D_L30_001B1704 && D_L30_001B1704!=-1) func_L00_002D2168(D_L30_001B1704,0,15.0f);
        func_L30_0040C270(obj,1);
        if (s->power.throttle>1.0f) s->power.throttle=1.0f; else if (s->power.throttle<0.0f) s->power.throttle=0.0f;
        if (D_00189E20.vehicle==obj) {
            if (D_00138180.pressed&16) func_002A7750(obj,4,-1);
            qcopy(D_00189E20.copyD0,D_00189E20.copyE0);
        }
        break;
    case 4:
        if (func_002B3868(obj)) {
            D_00189E20.cameraX=0;D_00189E20.cameraY=-1.0f;func_L00_002C42E0(11,1);
            D_00189E20.vehicle=0;D_00189E20.vehicleId=-1;
        }
        obj->flags=0;I(D_00189E20.hero,0x9C)=0;func_L30_0040C270(obj,0);
        { unsigned int timer=obj->timer; unsigned int old=timer++; obj->timer=timer;
        if (old>=31) {obj->flags=I(obj->classData,0x10);obj->state=1;} }
        break;
    case 6: break;
    case 5:
        obj->flags=I(obj->classData,0x10);I(D_00189E20.hero,0x9C)=0;
        func_L00_002C42E0(0,1);func_0029FCC0(obj,0,pos);
        func_002ABBB8(obj,s,pos,0.0f,0.0f,10,3,16,4.0f,2.0f,9.0f,1.0f,-1,15.0f,1,1,-1,0,0x810001);
        qcopy(obj->position,&s->spawn);D_00189E20.vehicleId=-1;D_00189E20.vehicle=0;obj->state=0;
        break;
    }
    scaled=s->power.throttle;
    k=0.00029088824f;
    scaled=D_L30_001B16D4*(scaled*k);
    s->height=obj->position[2];
    s->phase=func_00283B98(s->phase,scaled);
    bob=func_00283198(s->phase)*D_L30_001B16D0*s->power.throttle;
    rollRate=D_L30_001B16D8; yawRate=D_L30_001B16DC; pitchRate=D_L30_001B16E0;
    s->bob=bob;
    obj->position[2]+=s->bob*s->power.throttle;
    func_002AEF28(obj,&s->yawRate,&s->pitchRate,rollRate*0.017453294f,yawRate*(s->power.throttle*k),pitchRate*(s->power.throttle*k));
    obj->rotation[2]=s->roll;obj->rotation[0]=func_00283B98(obj->rotation[0],s->pitch);obj->rotation[1]=func_00283B98(obj->rotation[1],s->yaw);
    if (obj->state==3) {func_0029FCC0(obj,(int)D_L30_001B17B4,D_00189E20.position);{char *h=(char *)&D_00189E20;F(h,0x88)+=D_L30_001B17B8;}qcopy(D_00189E20.rotation,obj->rotation);
        func_L00_002E6EF8(func_L30_0040AE38,obj);
    }
    if (obj->visible && func_00282E48(obj->position,D_L30_001B9DC0)<64.0f) {func_002A93B0(obj);obj->delay=60;}
}
