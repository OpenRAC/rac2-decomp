#include "include_asm.h"

#include "common.h"
typedef unsigned int U128 __attribute__((mode(TI)));
typedef struct { float x, y, z, w; } Vec4 __attribute__((aligned(16)));
extern unsigned char D_00189E20[];
extern char D_00189F10[];
#define FLD(base, type, offset) (((struct { u8 pad[offset]; type v; } *)(base))->v)
#define H(type, offset) FLD(D_00189E20, type, offset)
#define HP(offset) ((void *)&H(u8, offset))
extern unsigned char D_00188660[];
extern unsigned char D_L23_00260310[];
extern unsigned char D_L23_001BA500[];
typedef struct { u16 count; u16 pad; u32 time; u32 levels; } StatRecord;
typedef struct { StatRecord records[32]; } StatTable;
extern StatTable D_0018C750;
extern u16 D_0018CF10;
extern unsigned int D_001A7390 __attribute__((sda));
extern unsigned int D_001A79F0 __attribute__((sda));
extern unsigned char D_00138180[];
extern u32 D_00138320;
/* the pad-buttons word inside D_00138180 */
static __inline__ void stat_bump(StatTable *table, int index)
{
    u32 clock;
    if (table->records[index].count < 0xFFFF) table->records[index].count++;
    clock = D_001A7390;
    if (table->records[index].time < clock) table->records[index].time = clock;
    table->records[index].levels = (table->records[index].levels | (1 << D_001A79F0)) | 0x80000000;
}
extern u8 D_001A7B08[0x40] __attribute__((sda));
extern unsigned char D_001A7B2A __attribute__((sda));
typedef struct { int field[11]; } AnimRecord;
extern AnimRecord D_L23_00261E90[];
extern float D_L23_001ACE68[];
extern int D_L23_001A8FF0 __attribute__((sda));
extern void *D_L23_001B2F30 __attribute__((sda));
extern void *D_L23_001B2F38 __attribute__((sda));
extern void *D_L23_001C4B00[];
extern void func_L00_002AA478(int, int);
extern void func_L00_002AA570(int, int);
extern void func_L00_002AA750(int, int);
extern void func_L00_002AA938(int, int, int);
extern void func_L00_002AABE0(int, int, int);
extern void func_L00_002AAE00(void);
extern void func_L00_002A9E30(float, float, float, float);
extern void func_L00_002AA0F0(float, float, float);
extern int func_L00_002ADEA0(int);
extern int func_L00_002ACF88(void *, void *, void *);
extern void func_L00_002AC578(void);
extern void func_L00_002B35A0(void);
extern int func_L00_002B3998(float);
extern void func_L00_002B39F0(float, int);
extern void func_L00_002B3D10(void);
extern void func_L00_002B3EF8(int, float, float, float);
extern void func_L00_002B3F68(void);
extern void func_L00_002B41B8(float, float);
extern void func_L00_002B4208(float);
extern void func_L00_002B42D8(void *);
extern void func_L00_002B54F8(float, float);
extern float func_L00_002B5590(void *);
extern void func_L00_002B6560(void);
extern void func_L00_002B6BC8(void);
extern void func_L00_002B75A0(float, float, float);
extern void func_L00_002B7B80(void);
extern void func_L00_002B8930(void);
extern void func_L00_002B8CB8(void);
extern void func_L00_002B94D8(float);
extern void func_L00_002B9598(void);
extern float func_L00_002B9B38(void *, int);
extern int func_L00_002B9B88(int index, int flags);
extern void func_L00_002B9BB0(int, void *, int);
extern void func_L00_002B9F00(float, float, float);
extern void func_L00_002BA508(void);
extern int func_L00_002CAF20(void);
extern void func_L00_002D2168(int, int, float);
extern void func_L00_002D34C0(void *, void *, float);
extern void func_L00_002D36E0(void *, int, float, float, float);
extern void func_L00_002D3778(void *, void *, float);
extern void func_L00_002D3798(void *, void *, float);
extern void func_L00_002D38A0(void *, void *, float);
extern void func_L00_002D3960(void *, void *);
extern float func_L00_002D3A58(void *);
extern float func_L00_002D3B00(void *);
extern void func_L00_002D3BD8(void *, void *, float);
extern int func_L00_002D6900(unsigned int index);
extern void func_L00_00322BE0(void *, int);
extern float func_L00_0032F038(int);
extern void func_L00_0041E958(float, float, float);
extern void func_L22_002B8E10(int);
extern int func_002761F8(void *, void *, int, void *, int);
extern int func_00277F48(float, void *, int, void *, void *);
extern float func_00282C48(float);
extern void func_00282C88(void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern void func_00282DD8(void *, void *, void *);
extern float func_00282E20(void *);
extern float func_00282E48(void *, void *);
extern float func_00282E80(void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282F70(void *, void *, float);
extern void func_00283098(void *, void *, void *);
extern float func_00283180(float);
extern float func_00283198(float);
extern float func_00283248(float, float);
extern float func_00283B98(float, float);
extern float func_00283BE0(float, float);
extern float func_00283C80(float, float);
extern int func_00283CF0(float);
extern void func_002A8C00(void *, void *, int, float, void *);
extern void func_002A8F70(void *, void *, int, void *, void *, float);
extern float func_002AA2E8(void *, float, float);
extern float func_002AA3A8(void *, void *, float, float, float, float);
extern float func_002AA738(float, int, float);
extern void func_002AA800(void *, int, float, float);
extern float func_002AA898(void *, float, void *, float, float, float, int);
extern int func_002ABB78(void *);
extern void func_002AC9F8(void *, float);
extern void func_002E59F8(int);
extern void func_002FD1B8(void *, void *, int, float, float, float, float);
extern int func_00282948(void *);
extern float func_00282DB0(void *, void *);
extern float func_00282DF0(void *);
extern void func_00290010(int, int, int, float);
extern void *func_0029EFD0(int);
extern void func_002A0F48(void *);
extern int func_002A7820(int, int);
extern float func_002A7878(float, float);
extern float func_002A78D8(float, float);
extern float func_002AA458(void *, void *, void *, float, float, float);
extern void func_002BE278(void *, void *, int, float);
extern int func_002E5CF8(int, int, void *);
extern void func_L00_002A9D38(void *, void *, float);
extern void func_L00_002AB0A8(float, float);
extern void func_L00_002AB0D8(float, float);
extern void func_L00_002AB0F0(float, float);
extern void func_L00_002ADCF8(void *);
extern void func_L00_002B3DC0(float, float, float);
extern void func_L00_002B4308(void);
extern void func_L00_002B6198(float);
extern void func_L00_002BA220(void);
extern void func_L00_002C9228(void);
extern void func_L00_002D3638(void *, int, float, float, float);
extern void func_L00_002D3B58(void *, void *, float);
extern int func_L00_002EE4D8(void *, void *, float);
extern int func_L00_0031D620(int, int, float);
extern int func_L00_003417B8(void *, int, int, int);
extern u8 D_00139568[];
extern u32 D_L23_001B22C8 __attribute__((sda));
extern float D_L23_00262210[], D_L23_00291A70[];
extern u8 D_L23_00266A70[];
extern int func_00282978(void *);
extern float func_00282C10(float);
extern void func_002830C0(void *,void *,void *);
extern void func_00283410(void *,void *);
extern void func_00283698(void *,void *);
extern int func_002A77E0(int);
extern int func_002A88A0(float *,float *,float,float,float);
extern void func_002AF000(void *,float,float,float);
extern float func_L00_002A9F30(float *,int);
extern void func_L00_002AB0C0(float,float);
extern void func_L00_002BA138(void *,int);
extern void func_L00_00322A98(void *,void *);
extern void func_L00_00322AC0(void *,int,int,float);
extern void func_L00_00323F28(void *,void *,float,float,float);
extern void *func_L00_00338D28(void *,void *,float);
extern int func_L22_002A8CE0(int);
extern float D_L23_001A7DAC[][4] __attribute__((sda));
extern s32 func_002A8C28(u8 *object, const Vec4 *position, s32 mask, float radius, float strength, float direction_scale, s32 type, s32 kind, s32 last);
extern void func_L23_004234C0(u8 *object, const Vec4 *position, s32 alternate);
extern void func_0029FCC0(u8 *object, s32 joint_index, Vec4 *out);
extern void func_002AFD88(u8 *object, Vec4 *out, float x, float y, float z);
extern s32 func_L00_00325FC8(float *angle, s32 first_color, s32 second_color, float step);
extern s32 func_L00_00341820(void *path, Vec4 *out, s32 *index, float *fraction, float step, s32 wrap);
extern s32 func_L00_00341FA8(void *path, Vec4 *position, Vec4 *state, s32 *index, float *fraction,
                            s32 wrap, float max_distance, float first, float second);
extern void func_L00_002B8F00(const Vec4 *input, Vec4 output_matrix[4], s32 mode,
                            float first, float second, float third);
extern u8 *func_002BF728(const Vec4 *from, const Vec4 *to, float radius, float floor);
typedef struct Probe48 {
    Vec4 vector;             
    u32 unused10;
    u32 unused14;
    u8 type;                 
    u8 kind;                 
    u16 id;                  
    u32 unused1c[5];
} Probe48;
typedef union Vec { U128 q; f32 f[4]; } Vec;
typedef struct Moby {
    u8 pad0[0x10];
      Vec pos;
    u8 pad20[0x3];
      u8 f23;
    u8 pad24[0xC];
      u8 f30;
      u8 f31;
      u16 f32;
      u16 f34;
    u8 pad36[0xB];
      u8 f41;
      u8 f42;
      u8 f43;
    u8 pad44[0x1C];
      u8 f60;
    u8 pad61[0x7];
      u8* f68;
    u8 pad6C[0x3E];
      s16 fAA;
    u8 padAC[0x14];
      Vec fC0[3];
      Vec rot;
} Moby;
extern s32 D_US2_001CAB40;
extern char D_US2_001A8F20[] MACRO_ADDR;
extern void func_L02_00392C70();
extern void func_L02_003948D0();

void func_US2_L23_002C39B8(void)
{
    u8 *entry_object = H(u8 *, 0x2290);
    int entry_substate = H(int, 0x2298);
    u8 entry_animation = entry_object[0x43];
    float shared_speed;
    float shared_rate;
    float shared_limit;
    u8 *hero;

    /* Only one state arm runs per invocation. Its temporary vectors and probe
     * records share storage; every pointer passed to a common tail is resident. */
    union {
        struct {
            Vec4 forward;
        } state_00;
        struct {
            Vec4 position;
            Vec4 velocity;
            Vec4 lateral;
        } state_32;
        struct {
            Vec4 joint_position;
            Vec4 projected_position;
            Vec4 offset;
        } state_67;
        struct {
            Vec4 local;
            Vec4 impulse;
            Vec4 output_matrix[4];
        } state_86;
        struct {
            Vec4 targetPosition;
            Vec4 desired;
            Vec4 offset;
        } state_24;
        struct {
            Vec4 targetPosition;
            Vec4 relative;
            Vec4 scaled;
            Vec4 delta;
        } state_25;
        struct {
            Vec4 direction;
            Vec4 angles;
            Vec4 matrices[4];
            Vec4 rotation;
            Vec4 inverse[4];
            Vec4 lateral;
            Vec4 relative;
            Vec4 point;
        } state_2b;
        struct {
            Vec4 delta;             /* also the contact origin */
            union {
                Vec4 movement;
                unsigned char contact[48] __attribute__((aligned(16)));
            } u;
            Vec4 force;
        } state_14;
        struct {
            unsigned char query[48] __attribute__((aligned(16)));
            Vec4 impulse;
            Vec4 point;
        } state_1f;
        struct {
            Vec4 impulse;
        } state_02;
        struct {
            Vec4 local;
            Vec4 target_position;
            Vec4 impulse;
        } state_7b;
        struct {
            Vec4 position;
            Vec4 velocity;
        } state_30;
        struct {
            Vec4 first;             /* path sample, or the spawned debris origin */
            Vec4 second;            /* second path sample, or the debris velocity */
            union {
                struct { Vec4 displacement; Vec4 previousStep; } d;
                struct { Vec4 probeA; Vec4 probeB; } p;
                unsigned char query[48] __attribute__((aligned(16)));
            } u;
            Vec4 direction;
            Vec4 position;
        } state_27;
        struct {
            Vec4 reference_position;
            Vec4 particle_position; /* later the path position */
            Vec4 particle_velocity; /* later the path difference */
        } state_71;
        struct {
            Vec4 contact;           /* first vector of a 64-byte contact record */
            Vec4 contact_rest[3];
            Vec4 side;
            Vec4 candidate;
            Vec4 direction;
        } state_19;
        struct {
            Vec4 rotation;
        } state_06;
        struct {
            Vec4 origin;
            Vec4 endpoint;          /* also the push force */
        } state_07;
        struct {
            Vec4 difference;
        } state_62;
        struct {
            Vec4 difference;
        } state_63;
        struct {
            Vec4 middle;
            Vec4 first;
            Vec4 second;
        } state_4d;
        struct {
            Vec4 hitPosition;       /* first vector of a 64-byte contact record */
            Vec4 hit_rest[3];
            Vec4 side;
            Vec4 candidate;
            Vec4 line;
        } state_49;
        struct {
            Vec4 effect_position;
            Probe48 probe;
            Vec4 local_offset;
            Vec4 midpoint;
        } state_5d;
        struct {
            Vec4 effect_position;
        } state_5e;
        struct {
            Vec4 effect_position;
        } state_58;
        struct {
            Vec4 effect_position;
        } state_57;
        struct {
            Vec4 effect_position;
        } state_59;
        struct { Vec s00, s10, s20, s30, s40, s50, s60; } mine;
        struct { Vec a, b, m1[4], e, m2[4], vB0, vC0, vD0; } mine2b;
    } workspace;

    switch (H(u32, 0x2294)) {
/* Hand reconstruction of the first state groups; offsets are in D_00189E20. */
case 0: case 1: case 3: case 4: case 28: case 29: case 30:
case 57: case 109: case 111: case 125:
{
    float step;
    if (H(u8, 0x22B9)) func_L00_002AA478(15, 30);
    if (H(u8, 0x1492)) func_L00_002B54F8(0.7f, 0.0f);
    else func_L00_002B54F8(0.5f, 0.033333335f);
    func_L00_002B9F00(3.7f, 0.0f, 0.35f);
    func_L00_002B39F0(1.0f, 0);
    if ((H(u32, 0x2294) == 1 || H(u32, 0x2294) == 29) && H(u8, 0x22B5)) {

        *(U128 *)&workspace.state_00.forward = 0; workspace.state_00.forward.x = 1.0f;
        func_00283098(HP(0x190), &workspace.state_00.forward, &FLD(D_L23_001BA500, u8, 0x370));
        H(float, 0x1A0) = FLD(D_L23_001BA500, float, 0x158);
        func_L00_002B3EF8(0, 1.0f, 0.0f, 2.9088826f);
        if (H(u8, 0x22BB) && H(int, 0x1B8) == 120) {
            stat_bump(&D_0018C750, 18);
        }
    }
    if (H(u32, 0x2294) == 3 && func_L00_002CAF20()) goto finish;
    if (H(u32, 0x2294) == 4 &&
        (H(float, 0x24B8) > 0.2f || H(u8 *, 0x2290)[0x43] == 14 || H(u8 *, 0x2290)[0x43] == 15)) {
        if (H(u32, 0x2294) == 4) func_L00_002B3EF8(0, 0.002f, 0.07f, 0.1163553f);
        if (func_00282C48(H(float, 0x1A4)) > 0.0058177654f) {
            int anim = H(float, 0x1A4) < 0.0f;
            anim += 14;
            if (H(u8 *, 0x2290)[0x43] != anim)
                func_L00_002D2168(anim, 0, 5.0f);
            H(float, 0xC20) = func_00282C48(H(float, 0x1A4)) * 18.093401f;
            if (H(float, 0xC20) < 0.55f) H(float, 0xC20) = 0.55f;
            if (H(float, 0xC20) > 2.5f) H(float, 0xC20) = 2.5f;
        } else if (H(float, 0x1A4) == 0.0f && H(u8 *, 0x2290)[0x43] != 13) {
            func_L00_002D2168(13, 0, 7.0f);
        }
    }
    H(float, 0x1B0) = 0.0f;
    if (H(u32, 0x2294) == 3) {
        float rate = H(float, 0x17C) + 1.0f;
        if (rate > 1.0f) rate = 1.0f;
        step = rate * 0.0075000003f;
        H(float, 0x24AC) = step;
        if (H(u8 *, 0x2290)[0x42] == H(u8 *, 0x2290)[0x43]) {
            shared_rate = H(float, 0x174) / step;
            if (shared_rate > 5.0f && (float)H(u8 *, 0x2290)[0x41] < 5.5f) {
                func_L00_002A9E30(13.0f, shared_rate, 0.5f, -1.0f);
                if (H(float, 0xC20) > 1.1f) H(float, 0xC20) = 1.1f;
            } else if ((float)H(u8 *, 0x2290)[0x41] > 6.5f) H(float, 0xC20) = 1.0f;
        }
    } else if (H(u32, 0x2294) == 4) {
        step = H(u8, 0x1492) ? 0.00047222225f : 0.0075000003f;
    } else step = 0.004916667f;
    func_L00_002B41B8(0.0f, step);
    func_00282C88(HP(0xF0));
    func_L00_002B94D8(step);
    if (H(u8, 0x1497) && D_001A7B08[3]) {
        if (H(float, 0x31C) > 0.2f) { func_L00_002D34C0(HP(0xF0),HP(0x120),0.0061111115f); goto finish; }
        func_L00_002D34C0(HP(0xF0), HP(0xF0), 0.015000001f);
        if (H(int, 0x33C)) {
            qcopy(&H(U128, 0x80), &H(U128, 0x2D0));
            H(s16, 0x34E) = 0;
            H(float, 0x31C) = 0.0f;
        }
        goto finish;
    }
    func_L22_002B8E10(0);
    if (H(s16, 0x34E)) { func_L00_002D34C0(&H(Vec4, 0xf0), &H(Vec4, 0x130), 0.0069444445f); func_L00_002B4308(); }
    else func_L00_002D34C0(&H(Vec4, 0xf0), &H(Vec4, 0xf0), 0.0150000006f);
    goto finish;
}


    case 0x7C:
        {
        u8 *player = D_00189E20;
        if (FLD(player, Moby *, 0x7A4) == 0) {
            Moby *m = func_0029EFD0(0x52A);
            FLD(player, Moby *, 0x7A4) = m;
            if (FLD(player, Moby *, 0x7A4) != 0) {
                qcopy(&m->pos, &FLD(player, Vec, 0x80));
                qcopy(&m->rot, &FLD(player, Vec, 0x90));
                m->f32 = 0x40;
                FLD(player, Moby *, 0x7A4)->f31 = 1;
                FLD(player, Moby *, 0x7A4)->f30 = 0;
                FLD(player, Moby *, 0x7A4)->f23 = 0;
                FLD(player, Moby *, 0x7A4)->f34 |= 0x800;
                func_002A0F48(FLD(player, Moby *, 0x7A4));
                func_002E5CF8(0, 0, FLD(player, Moby *, 0x7A4));
            }
        }
        if (FLD(player, Moby *, 0x7A4)) {
            Moby *source, *effect;
            FLD(player, Moby *, 0x7A4)->f23 += func_00283CF0(5.0f);
            if (FLD(player, Moby *, 0x7A4)->f23 > 0x80) FLD(player, Moby *, 0x7A4)->f23 = 0x80;
            effect = FLD(player, Moby *, 0x7A4);
            source = FLD(player, Moby *, 0x2290);
            qcopy(&effect->pos, &source->pos);
            qcopy(&effect->rot, &source->rot);
            func_002A0F48(effect);
        }
        }
        H(float, 0xF8) = 0.0f;
        func_L00_002EE4D8(&H(Vec, 0xF0), &H(Vec, 0xF0), func_00282E20(&H(Vec, 0xF0)) * 0.92f);
        func_L00_002C9228();
        goto finish;

case 0x32: case 0x33: case 0x34:
{
    float oldPitch,steer,minimumSteer,pitchChange,controllerScale,rate,maximumInput,steeringLimit;
    if (H(u32,0x2294)==0x34) {
        if (H(s32,0x1B8)>70) D_0018CF10=65535;
        func_L00_002B9BB0(5,H(void*,0x2290),15);func_L00_002D6900(22);
    } else {
        int slot=H(s32,0x2440);
        if (slot!=-1 && FLD(D_00188660+slot*0x70, void *, 0x88)==H(void*,0x2290) &&
            FLD(D_00188660+slot*0x70, u8, 0x74)) func_002E59F8(slot);
        H(s32,0x2440)=-1;
    }
    if (H(s16,0xA4A)) {
        int count;
        func_00282978(HP(0xA4A));count=(s16)H(u16,0xA4A)>>2;
        if (count>8) count=8;
        func_L00_002AA938(count,0,0);
    }
    if (H(u32,0x2294)==0x32 && !H(s32,0xC2C) && H(float,0xC38)>0.0f && H(float,0xC38)<10.0f)
        func_L00_002AA938(4,1,0);
    if (H(u32,0x2294)==0x33 && H(s32,0x22A0)==0x34 && H(s32,0x1B8)<15)
        func_L00_002AA938((20-H(s32,0x1B8))/3+1,1,0);
    if (H(s32,0x2298)==1) {
        if (H(s32,0x1B8)==1) {
            func_L00_002AABE0(3,16,0);
            if (D_L23_001B2F30)
                func_002FD1B8(D_L23_001B2F30,D_L23_001B2F38,0,H(float,0x80),H(float,0x84),0.4f,-0.3f);
            H(u16,0xA4A)=70;
        }
        ++H(s32,0xA20);
        if (H(s32,0xA20)>40) H(s32,0x2298)=0;
    }
    {
        float horizontal=FLD(D_00138180, float, 0x128), vertical=FLD(D_00138180, float, 0x12C);
        maximumInput=horizontal<vertical?vertical:horizontal;
    }
    steeringLimit=0.011635531f;steeringLimit+=maximumInput*0.008726647f; /* retail max.s, not float-to-int/OR */
    steer=0.0f;
    minimumSteer=0.2f;
    if ((FLD(D_00138180, u64, 0x1A0)&0xC0)==0x80 || H(s32,0x2298)==1) {
        steer=FLD(D_00138180, float, 0x12C)*1.5f;
        if (steer>1.0f) steer=1.0f;
        if (steer<minimumSteer) steer=minimumSteer;
        if (FLD(D_00138180, s32, 0x1DC)!=0x79) {
            ++H(s16,0xA42);H(s16,0xA40)=0;
            steer=(float)H(s16,0xA42)*0.025f+0.5f;
            if (steer>1.0f) steer=1.0f;
        }
        if (H(s32,0x2298)==1 && steer<0.35f) steer=0.35f;
        steer*=1.361357f;
    } else if (FLD(D_00138180, u32, 0x1A0)&0x40) {
        steer=FLD(D_00138180, float, 0x128)*1.5f;
        if (steer>1.0f) steer=1.0f;
        if (steer<minimumSteer) steer=minimumSteer;
        if (FLD(D_00138180, s32, 0x1DC)!=0x79) {
            H(s16,0xA42)=0;++H(s16,0xA40);
            steer=(float)H(s16,0xA40)*0.025f+0.5f;
            if (steer>1.0f) steer=1.0f;
        }
        if ((float)H(s32,0x24C0)<1500.0f) steer=1.0f;
        steer*= -1.361357f;
    } else {
        H(s16,0xA40)=0;H(s16,0xA42)=0;
    }
    if (FLD(D_00138180, u32, 0x1A0)&0x40) {
        ++H(s16,0xA4E);
        if (FLD(D_00138180, float, 0x128)>0.75f) {
            if (++H(s16,0xA4C)>90) {
                if (D_0018C750.records[11].count < 0xFFFF) D_0018C750.records[11].count++;
            }
            {
                u32 clock = D_001A7390;
                if (D_0018C750.records[11].time < clock) D_0018C750.records[11].time = clock;
                D_0018C750.records[11].levels = (D_0018C750.records[11].levels | (1 << D_001A79F0)) | 0x80000000;
            }
        } else H(s16,0xA4C)=0;
    } else {H(s16,0xA4E)=0;H(s16,0xA4C)=0;}
    if (FLD(D_00138180, u32, 0x1A4)&0x40) {
        hero=D_00189E20;
        if ((s32)(D_L23_001B22C8-FLD(hero,u32,0xA54))<70) ++FLD(hero,s32,0xA50);
        FLD(hero,u32,0xA54)=D_L23_001B22C8;
    }
    if (H(s16,0xA4E)>70) H(s32,0xA50)=0;
    if (FLD(D_00138180, u32, 0x1A0)&0x80) H(s32,0xA50)=0;
    if (H(u32,0x2294)==0x33) steer=0.0f;
    oldPitch=H(float,0x94);
    func_002AA898(HP(0x94), steer, HP(0xA28), 0.015f, 0.2f, steeringLimit, 0);
    pitchChange=func_00283BE0(H(float,0x94),oldPitch);
    func_L00_002B39F0(1.0f, 0);func_L00_002B3EF8(0,0.007f,0.08f,0.087266475f);
    H(float,0xA2C)=H(float,0x1A4);func_00282948(HP(0xA34));
    if (H(s32,0x2298)==1) H(float,0x1B0)=0.10000001f;
    else if (H(u32,0x2294)==0x34) {
        if (FLD(D_00138180, u32, 0x1A0)&10) H(float,0x1B0)=0.116666675f;
        else H(float,0x1B0)=0.04666667f;
    }
    else H(float,0x1B0)=0.050000004f;
    controllerScale=H(float,0x24B8);
    if (((FLD(D_00138180, u32, 0x1A0)&0xC0) || H(s32,0x2298)==1) && H(float,0x24B8)<1.0f) controllerScale=1.0f;
    if (H(float,0x24B8)>0.15f) {
        float minimum=H(u32,0x2294)==0x34?0.4f:0.35f;
        if (controllerScale<minimum) controllerScale=minimum;
    }
    if (H(u32,0x2294)!=0x34 || !(FLD(D_00138180, u32, 0x1A0)&10)) H(float,0x1B0)*=controllerScale;
    if (func_00282948(HP(0xA30))) {

        int low,high,choice;
        func_0029FCC0(H(void*,0x2290),4,&workspace.state_32.position);
        *(U128 *)&workspace.state_32.lateral = 0; workspace.state_32.lateral.x = 0.4f;
        func_00283098(&workspace.state_32.lateral,&workspace.state_32.lateral,H(u8*,0x2290)+0xC0);
        func_00282CC0(&workspace.state_32.position,&workspace.state_32.position,&workspace.state_32.lateral);
        qcopy(&workspace.state_32.velocity, &H(Vec4,0x110));
        func_00282F20(&workspace.state_32.lateral,&workspace.state_32.lateral,0.025000002f);
        func_00282CC0(&workspace.state_32.velocity,&workspace.state_32.velocity,&workspace.state_32.lateral);workspace.state_32.velocity.z+=0.033333335f;
        func_002BF728(&workspace.state_32.position,&workspace.state_32.velocity,25200.0f,-1.0f);
        choice=func_002A77E0(100);
        if ((float)choice<40.0f) H(s32,0xA30)=func_002A7820(4,11);
        else H(s32,0xA30)=func_002A7820(40,90);
    }
    if (H(u32,0x2294)==0x34) {
        u8 *attachment;
        if (func_00282978(HP(0xA38)) && (attachment=H(u8*,0x1310)) && *(s16*)(attachment+0xAA)==0x261) {
            int i;
            for(i=0;i<4;++i) {

                float energy;
                func_0029FCC0(attachment,i%2,&workspace.state_32.position);
                *(U128 *)&workspace.state_32.lateral = 0; workspace.state_32.lateral.x = -0.15f;
                func_00283098(&workspace.state_32.lateral,&workspace.state_32.lateral,H(u8*,0x2290)+0xC0);
                func_00282CC0(&workspace.state_32.position,&workspace.state_32.position,&workspace.state_32.lateral);
                workspace.state_32.position.x+=func_002A7878(0.0f,0.03f);
                workspace.state_32.position.y+=func_002A7878(0.0f,0.03f);
                workspace.state_32.position.z+=func_002A7878(0.0f,0.03f);
                qcopy(&workspace.state_32.velocity, &H(Vec4,0x110));
                func_L00_00323F28(&workspace.state_32.velocity,&workspace.state_32.velocity,-0.012500001f,H(float,0x98),H(float,0x94));
                H(s16,0xA38)=func_00283CF0((0.116666675f-H(float,0x1B4))*42.85714f);
                energy=func_002A7878(6300.0f,9450.0f);
                func_002BF728(&workspace.state_32.position,&workspace.state_32.velocity,energy,-1.0f);
            }
        }
    }
    if (H(u32,0x2294)==0x34) func_L00_002B41B8(0.003611111f,0.0022222223f);
    else func_L00_002B41B8(0.0019444445f,0.0011111111f);
    {
        float angle=func_00283B98(-H(float,0x94),0.0f);
        if (H(u32,0x2294)==0x34) func_002AF000(HP(0xF0),H(float,0x1B4),H(float,0x98),angle);
        else if (H(u32,0x2294)==0x32) {
            float speed=H(float,0x1B4)*func_L00_002A9F30(D_L23_00262210,30)*5.0f;
            if (H(s32,0x22A0)==0x34 && H(s32,0x1B8)<15 && speed<0.075f) speed=0.075f;
            func_002AF000(HP(0xF0),speed,H(float,0x98),angle);
        } else if (H(u32,0x2294)==0x33) {
            float speed=func_00282DF0(HP(0x160));
            if (H(s32,0x22A0)==0x34) func_002AA2E8(&speed,0.0f,0.0022222223f);
            else func_002AA2E8(&speed,0.0f,0.0011111111f);
            func_00282F20(HP(0x160),HP(0x160),speed);qcopy(&H(Vec4,0xF0), &H(Vec4,0x160));
        }
        func_L22_002B8E10(0);
        rate=H(float,0xA2C)*func_00283180(angle)*-7.0f;
    }
    func_002AA898(HP(0x90), rate, HP(0xA24), 0.007f, 0.17f, 0.020362178f, 0);
    func_L00_002AB0C0(0.009f,0.22f);func_L00_002AB0D8(0.04f,0.2f);func_L00_002AB0F0(0.02f,0.2f);
    FLD(D_L23_00260310, float, 0x114)=pitchChange*47.0f;FLD(D_L23_00260310, float, 0x118)=rate*1.5f;FLD(D_L23_00260310, float, 0x110)=rate*1.4f;
    if (FLD(D_L23_00260310, float, 0x114)>0.8726647f) FLD(D_L23_00260310, float, 0x114)=0.8726647f;
    else if (FLD(D_L23_00260310, float, 0x114)< -0.8726647f) FLD(D_L23_00260310, float, 0x114)=-0.8726647f;
    FLD(D_L23_00260310, float, 0x364)=0.03f;
    FLD(D_L23_00260310, float, 0x368)=0.22f;
    FLD(D_L23_00260310, float, 0x324)=pitchChange*40.0f;
    FLD(D_L23_00260310, float, 0x328)=rate*1.1f;
    FLD(D_L23_00260310, float, 0x414)=0.03f;
    FLD(D_L23_00260310, float, 0x418)=0.22f;
    FLD(D_L23_00260310, float, 0x3D4)=pitchChange*40.0f;
    FLD(D_L23_00260310, float, 0x3D8)=rate*1.1f;
    goto finish;
}


case 0x73:
{
    s32 amount = 10 - H(s32, 0x1b8) / 3;
    float speed;
    if (8 < amount) amount = 8;
    func_L00_002AA938(amount, 0, 0);
    H(float, 0xf8) = 0.0f;
    speed = func_00282E20(&H(Vec4, 0xf0));
    func_L00_002EE4D8(&H(Vec4, 0xf0), &H(Vec4, 0xf0), speed * 0.920000017f);
    func_L22_002B8E10(0);
    goto finish;
}



case 0x72:
{
    float speed;
    func_L00_002AA478(15, 30);
    H(float, 0xf8) = 0.0f;
    speed = func_00282E20(&H(Vec4, 0xf0));
    func_L00_002EE4D8(&H(Vec4, 0xf0), &H(Vec4, 0xf0), speed * 0.920000017f);
    func_L22_002B8E10(0);
    func_L00_002C9228();
    goto finish;
}



case 0x67:
case 0x7f:
{

    float speed = func_00282DF0(&H(Vec4, 0x160));
    func_002AA2E8(&speed, 0.0f, 0.00111111114f);
    func_00282F20(&H(Vec4, 0x160), &H(Vec4, 0x160), speed);
    qcopy(&H(Vec4, 0xf0), &H(Vec4, 0x160));
    if (func_00282948(&H(s32, 0xa30)) == 2) {
        func_0029FCC0(H(u8 *, 0x2290), 4, &workspace.state_67.joint_position);
        *(U128 *)&workspace.state_67.offset = 0;
        workspace.state_67.offset.x = 0.400000006f;
        func_00283098(&workspace.state_67.offset, &workspace.state_67.offset, H(u8 *, 0x2290) + 0xc0);
        func_00282CC0(&workspace.state_67.joint_position, &workspace.state_67.joint_position, &workspace.state_67.offset);
        qcopy(&workspace.state_67.projected_position, &H(Vec4, 0x110));
        func_00282F20(&workspace.state_67.offset, &workspace.state_67.offset, 0.0250000022f);
        func_00282CC0(&workspace.state_67.projected_position, &workspace.state_67.projected_position, &workspace.state_67.offset);
        workspace.state_67.projected_position.z = workspace.state_67.projected_position.z + 0.0333333351f;
        func_002BF728(&workspace.state_67.joint_position, &workspace.state_67.projected_position, 25200.0f, -1.0f);
        if (H(s32, 0x1b8) < 40) {
            H(s32, 0xa30) = func_002A7820(2, 5);
            H(s32, 0xa30) = H(s32, 0xa30) + H(s32, 0x1b8) / 5;
        } else if (70 < H(s32, 0x1b8)) {
            H(s32, 0xa30) = func_002A7820(10, 20);
        }
    }
    if (0.0f < H(float, 0xa3c)) H(float, 0xa3c) = 0.0f;
    func_002AA2E8(&H(float, 0xa3c), -0.0250000022f, 0.000416666677f);
    H(float, 0xf8) = H(float, 0xa3c);
    goto finish;
}



case 0x35: case 0x36:
{
    if (H(u32,0x2294)==0x36) func_L00_002AA478(15,30);
    if (H(float,0x174)>0.025000002f) func_L00_002AA750(4,12);
    if (H(u32,0x2294)==0x35 && H(float,0x174)>0.016666668f) func_L00_002AA570(0,1);
    if (H(s16,0xA4A)) {
        int count;
        --H(u16,0xA4A);count=(s16)H(u16,0xA4A)>>3;
        if (count>6) count=6;
        func_L00_002AA938(count,0,0);
    }
    H(float,0xC20)=0.6f;func_L00_002B39F0(0.050000004f, 0);
    if (!FLD(D_00138180, int, 0x1D4) && H(float,0x1B0)<0.025000002f) H(float,0x1B0)=0.025000002f;
    func_L00_002B3EF8(0,0.007f,0.08f,0.087266475f);func_00282948(HP(0x798));
    if (H(u32,0x2294)==0x35) {
        float speed;
        if (FLD(D_00138180, int, 0x1D4) && H(s32,0x798)) H(float,0x1B0)=0.050000004f;
        if (func_00282C48(H(float,0x1A8))>0.78539824f) H(float,0x1B0)=0.0f;
        func_L00_002B41B8(0.0011111111f,0.0013888889f);
        speed=H(float,0x1B4)*func_L00_002A9F30(D_L23_00262210,30)*5.5f;
        H(float,0xF0)=func_00283180(H(float,0x98))*speed;
        H(float,0xF4)=func_00283198(H(float,0x98))*speed;H(float,0xF8)=0.0f;
    } else {H(float,0x1B4)=0.0f;func_00282C88(HP(0xF0));}
    if (H(u32,0x2294)==0x35 && !H(s32,0xC2C) && H(float,0xC38)>0.0f && H(float,0xC38)<10.0f)
        func_L00_002AA938(4,1,0);
    func_L00_002B94D8(0.0011666666f);
    func_L22_002B8E10(0);func_L00_002C9228();
    goto finish;
}


case 0x85:
{
    u8 *attached = H(u8 *, 0x1830);
    qcopy(&H(Vec4, 0x80), (Vec4 *)(attached + 0x10));
    qcopy(&H(Vec4, 0x90), (Vec4 *)(attached + 0xf0));
    goto finish;
}



    case 0x86: {
        f32 t;
        func_00282D30(&workspace.mine.s00, &H(Vec, 0x2C0), -1.0f);
        t = 0.0f;
        if (H(float, 0x24B8) > 0.2f) t = -H(float, 0x1FB4) * 0.75f;
        func_002AA3A8(&H(float, 0x7C0), &H(float, 0x7C4), t, 0.007f, 0.3f, 0.03f);
        func_00282D30(&workspace.mine.s10, &H(Vec, 0x0), H(float, 0x7C0));
        func_00282CC0(&workspace.mine.s00, &workspace.mine.s00, &workspace.mine.s10);
        func_00282F20(&workspace.mine.s00, &workspace.mine.s00, 1.0f);
        func_L00_002B8F00(&workspace.mine.s00, &workspace.mine.s30, 0, 0.025f, 0.4f, 0.0f);
        H(float, 0x1B4) = 0.21666668f;
        func_00282F20(&H(Vec, 0xF0), &H(Vec, 0x0), H(float, 0x1B4));
        func_L00_002D3B58(&H(Vec, 0xF0), &H(Vec, 0xF0), 0.0f);
        func_00282C88(&workspace.mine.s00);
        workspace.mine.s00.f[1] = -H(float, 0x1FB0);
        func_00283098(&H(Vec, 0x190), &workspace.mine.s00, &FLD(D_L23_001BA500, u8, 0x370));
        func_L00_002B3EF8(0, 0.02f, 0.3f, 0.034906592f);
        goto finish;
    }

case 0x2F:
{
    int next_animation=-1, blend=0;
    if (H(u8,0x1492)) func_L00_002B54F8(0.7f,0.0f);
    else func_L00_002B54F8(0.5f,0.033333335f);
    func_L00_002B9F00(3.7f,0.0f,0.35f);func_L00_002B39F0(1.0f, 0);
    func_L00_002B41B8(0.004916667f,0.004916667f);
    func_00282C88(HP(0xF0));func_L00_002B94D8(0.004916667f);
    if (H(s16,0x34E)) { func_L00_002D34C0(HP(0xF0),HP(0x110),0.0069444445f);func_L00_002B4308(); }
    else func_L00_002D34C0(HP(0xF0),HP(0xF0),0.015000001f);
    if (next_animation!=-1 && H(u8*,0x2290)[0x42]!=0x36)
        func_L00_002D2168(next_animation,0,(float)blend);
    else if ((H(u8*,0x2290)[0x60]&2) && H(u8*,0x2290)[0x42]==0x36)
        func_L00_002D2168(func_L22_002A8CE0(0),0,5.0f);
    goto finish;
}


    case 0x8A: case 0x8B:
        func_L00_002B9F00(3.7f, 0.0f, 0.35f);
        H(float, 0x1B0) = 0.0f;
        func_L00_002B41B8(0.004916667f, 0.004916667f);
        func_00282C88(&H(Vec, 0xF0));
        func_L00_002B94D8(0.004916667f);
        if (H(s16, 0x34E)) {
            func_L00_002D34C0(&H(Vec, 0xF0), &H(Vec, 0x120), 0.0061111115f);
            func_L00_002B4308();
        } else {
            func_L00_002D34C0(&H(Vec, 0xF0), &H(Vec, 0xF0), 0.015000001f);
        }
        if (H(Moby *, 0xB10)) {
            H(float, 0x1A0) = func_00283248(H(Moby *, 0xB10)->pos.f[0] - *(float *)(entry_object + 0x10), H(Moby *, 0xB10)->pos.f[1] - *(float *)(entry_object + 0x14));
            func_L00_002B3EF8(0, 0.02f, 0.15f, 0.10471977f);
        }
        goto finish;

case 0x23:
{
    func_L00_002B9F00(3.7f,0.0f,0.35f);
    H(float,0x1B0)=0.0f;
    func_L00_002B41B8(0.004916667f,0.004916667f);
    func_00282C88(HP(0xF0));
    func_L00_002B94D8(0.004916667f);
    if (H(s16,0x34E)) {
        func_L00_002D34C0(HP(0xF0),HP(0x120),0.0061111115f);
        func_L00_002B4308();
    } else func_L00_002D34C0(HP(0xF0),HP(0xF0),0.015000001f);
    if (H(u8*,0xAA4)) {
        H(float, 0x1a0) = func_00283248(*(float *)(H(u8*,0xAA4) + 0x10) - *(float *)(entry_object + 0x10),
                                     *(float *)(H(u8*,0xAA4) + 0x14) - *(float *)(entry_object + 0x14));
        func_L00_002B3EF8(0, 0.0199999996f, 0.150000006f, 0.104719773f);
    }
    goto finish;
}


case 0x24:
{

    float bearing,firstRoot,secondRoot;
    qcopy(&workspace.state_24.targetPosition, H(u8*,0xAA4)+0x10);
    H(float,0xAB0)=func_00282E48(HP(0x80),&workspace.state_24.targetPosition);
    H(float,0xAAC)=60.0f;
    if (H(float,0xAA0)>0.0f) H(float,0xAAC)=H(float,0xAB0)/H(float,0x170);
    if (H(s32,0x2298)==0) {
        func_002AA2E8(HP(0xAA0),0.45000002f,0.022222223f);
        bearing=func_00283248(*(float*)(H(u8*,0xAA4)+0x10)-*(float*)(entry_object+0x10),
                              *(float*)(H(u8*,0xAA4)+0x14)-*(float*)(entry_object+0x14));
        if (H(s32,0x3A0) && func_00283C80(H(float,0x98),bearing)>1.5707964f)
            bearing=func_00283B98(bearing,3.1415927f);
        H(float,0x1A0)=bearing;
        func_L00_002B3EF8(0,0.03f,0.15f,0.12217307f);
    } else if (H(s32,0x2298)==1) func_002AA2E8(HP(0xAA0),0.0f,0.011666667f);
    if (func_002A88A0(&firstRoot,&secondRoot,-0.0058333334f,H(float,0xAA0),1.9f-H(float,0xAB0))>0 && firstRoot>0.0f) {
        H(s32,0x2298)=1;
        H(float,0xAAC)=firstRoot;
    }
    H(u16,0x226)=3;
    if (H(float,0xAAC)<20.0f) H(s32,0xAB4)=1;
    if (H(s32,0xAB4)) func_002AA800(HP(0x94),0,0.0f,0.063995413f);
    else {
        float horizontal=func_00282E80(HP(0x80),&workspace.state_24.targetPosition);
        bearing=func_00283248(horizontal,workspace.state_24.targetPosition.z-H(float,0x88));
        bearing=func_00283B98(-bearing,1.5707965f);
        func_002AA800(HP(0x94),0,bearing,0.10762865f);
    }
    bearing=func_00283B98(H(float,0x98),-1.5707965f);
    workspace.state_24.offset.x=func_00283180(bearing)*-0.57f;
    bearing=func_00283B98(H(float,0x98),-1.5707965f);
    workspace.state_24.offset.y=func_00283198(bearing)*-0.57f;
    workspace.state_24.offset.z=0.0f;
    func_00282CC0(&workspace.state_24.offset,&workspace.state_24.offset,HP(0x80));
    func_00282CF0(&workspace.state_24.desired,H(u8*,0xAA4)+0x10,&workspace.state_24.offset);
    func_00282F20(HP(0xF0),&workspace.state_24.desired,H(float,0xAA0));
    if (H(float,0xAAC)<30.0f) H(float,0xF8)-=(30.0f-H(float,0xAAC))*0.008055556f;
    goto finish;
}


case 0x25:
{

    func_002AA2E8(HP(0xABC),H(float,0xAC0),0.16666667f);
    qcopy(&H(Vec4,0xF0), &H(Vec4,0x110));
    func_00282D30(HP(0xF0),HP(0xF0),0.9f);
    H(float,0xF8)-=0.004166667f;
    qcopy(&workspace.state_25.targetPosition, H(u8*,0xAA4)+0x10);
    H(float,0xAB0)=func_00282E48(HP(0x80),&workspace.state_25.targetPosition);
    func_00282CC0(&workspace.state_25.relative,HP(0x80),HP(0xF0));
    func_00282CF0(&workspace.state_25.delta,&workspace.state_25.relative,&workspace.state_25.targetPosition);
    func_00282F20(&workspace.state_25.delta,&workspace.state_25.delta,H(float,0xABC));
    func_00282CC0(&workspace.state_25.scaled,&workspace.state_25.targetPosition,&workspace.state_25.delta);
    func_00282CF0(HP(0xF0),&workspace.state_25.scaled,HP(0x80));
    goto finish;
}


    case 0x2B: {
        s32 above;
        f32 vz, yaw;

        if ((H(s32, 0xC28) & 2) && entry_object[0x43] == 0x34) {
            func_L00_002D2168(0x35, 0xA, 12.0f);
            H(float, 0xC20) = 0.3f;
        }
        vz = H(float, 0xF8);
        if (H(Moby *, 0xAD4) && H(Moby *, 0xAD4)->f68 && *(s32 *)(H(Moby *, 0xAD4)->f68 + 0x34)) {
            yaw = H(Moby *, 0xAD4)->rot.f[2];
            if (func_00283C80(yaw, H(float, 0x98)) > 90.0f) yaw = func_00283B98(yaw, 3.1415927f);
            func_002AA898(&H(float, 0xAEC), yaw, &H(float, 0xAF8), 0.02f, 0.3f, 0.0f, 0);
        }
        H(float, 0x1A0) = H(float, 0xAEC);
        func_L00_002B3EF8(0, 0.02f, 0.3f, 0.078539826f);
        func_00282CF0(&workspace.mine2b.a, &H(Moby *, 0xAD4)->pos, &H(Vec, 0x80));
        func_00282F20(&workspace.mine2b.a, &workspace.mine2b.a, 1.0f);
        if (workspace.mine2b.a.f[2] < 0.23f) workspace.mine2b.a.f[2] = 0.23f;
        func_00282C88(&workspace.mine2b.e);
        workspace.mine2b.e.f[2] = H(float, 0x98);
        func_00283410(workspace.mine2b.m1, &workspace.mine2b.e);
        func_00283698(workspace.mine2b.m2, workspace.mine2b.m1);
        func_002830C0(&workspace.mine2b.a, &workspace.mine2b.a, workspace.mine2b.m2);
        workspace.mine2b.b.f[0] = -func_00283248(func_00282C10(workspace.mine2b.a.f[0] * workspace.mine2b.a.f[0] + workspace.mine2b.a.f[2] * workspace.mine2b.a.f[2]), workspace.mine2b.a.f[1]);
        workspace.mine2b.b.f[1] = func_00283248(workspace.mine2b.a.f[2], workspace.mine2b.a.f[0]);
        func_002AA898(&H(float, 0x94), workspace.mine2b.b.f[1], &H(float, 0xA4), 0.04f, 0.2f, 0.15998854f, 0);
        func_002AA898(&H(float, 0x90), workspace.mine2b.b.f[0], &H(float, 0xA0), 0.04f, 0.2f, 0.15998854f, 0);
        above = H(float, 0x88) < H(Moby *, 0xAD4)->pos.f[2];

        if (H(s16, 0xADC)) {
            if (above && H(s32, 0x1B8) > 0x28 && H(float, 0x24B8) > 0.25f) {
                f32 push;
                func_L00_002B39F0(1.0f, 0);
                push = H(float, 0x24B8) * 0.0035f;
                if (push > 0.083333336f) push = 0.083333336f;
                workspace.mine2b.vB0.f[0] = func_00283180(H(float, 0x1A0)) * push;
                workspace.mine2b.vB0.f[1] = func_00283198(H(float, 0x1A0)) * push;
                workspace.mine2b.vB0.f[2] = 0.0f;
                func_00282CC0(&H(Vec, 0xF0), &H(Vec, 0xF0), &workspace.mine2b.vB0);
            }
            if (H(s16, 0xADC)) {
                if (func_00282E80(&H(Vec, 0x80), &H(Moby *, 0xAD4)->pos) < H(float, 0xAE0) * 1.57f || H(float, 0x31C) > 1.5f) {
                    func_L00_002D34C0(&H(Vec, 0xF0), &H(Vec, 0x110), 0.011111111f);
                    if (H(s16, 0xAFE) && func_L00_002D3B00(&H(Vec, 0xF0)) > 0.0f) {
                        func_00282CF0(&workspace.mine2b.vB0, &H(Vec, 0x80), &H(Moby *, 0xAD4)->pos);
                        func_L00_002D34C0(&H(Vec, 0xF0), &H(Vec, 0xF0), 0.015833333f);
                    }
                }
                {
                f32 drag = func_00282DF0(&H(Vec, 0xF0)) * 0.00025f;
                func_00282D30(&workspace.mine2b.vB0, &H(Vec, 0xF0), -1.0f);
                func_00282F20(&workspace.mine2b.vB0, &workspace.mine2b.vB0, drag);
                }
                func_00282CC0(&H(Vec, 0xF0), &H(Vec, 0xF0), &workspace.mine2b.vB0);
            }
        }
        if (H(Moby *, 0xAD4) && H(Moby *, 0xAD4)->f68) {
            f32 *limits = (f32 *)H(Moby *, 0xAD4)->f68;
            f32 sp = func_00282DF0(&H(Vec, 0xF0));
            if (limits[3] < sp) {
                func_002AA2E8(&sp, limits[3], 0.004166667f);

                func_00282F20(&H(Vec, 0xF0), &H(Vec, 0xF0), sp);
            }
        }
        {
        f32 side = func_00283B98(H(float, 0x98), -1.5707965f);
        workspace.mine2b.vD0.f[0] = func_00283180(side) * 0.15f;
        workspace.mine2b.vD0.f[1] = func_00283198(side) * 0.15f;
        }
        workspace.mine2b.vD0.f[2] = 0.0f;
        func_00282CC0(&workspace.mine2b.vD0, &workspace.mine2b.vD0, &H(Vec, 0x80));
        func_00282CC0(&workspace.mine2b.vB0, &workspace.mine2b.vD0, &H(Vec, 0xF0));
        func_00282CF0(&workspace.mine2b.vC0, &workspace.mine2b.vB0, &H(Moby *, 0xAD4)->pos);
        func_00282F20(&workspace.mine2b.vC0, &workspace.mine2b.vC0, H(float, 0xAE4));
        func_00282CC0(&workspace.mine2b.vB0, &H(Moby *, 0xAD4)->pos, &workspace.mine2b.vC0);
        func_00282CF0(&H(Vec, 0xF0), &workspace.mine2b.vB0, &workspace.mine2b.vD0);
        {
        f32 previous = H(float, 0xAE4), change;
        func_002AA3A8(&H(float, 0xAE4), &H(float, 0xAE8), H(float, 0xAE0), H(float, 0xB04), H(float, 0xB08), H(float, 0xB0C));
        change = H(float, 0xAE4) - previous;
        if (H(float, 0xAE4) < func_00282DF0(&workspace.mine2b.vC0)) {
            func_00282F20(&workspace.mine2b.vC0, &workspace.mine2b.vC0, change);
            func_00282CC0(&H(Vec, 0x80), &H(Vec, 0x80), &workspace.mine2b.vC0);
        }
        }
        if (H(s16, 0xAFE) && above) {
            f32 target = 0.23333335f;
            f32 sp = func_00282E20(&H(Vec, 0xF0));
            if (sp < target) {
                func_002AA3A8(&sp, &H(float, 0xAF4), target, 0.047f, 0.3f, 0.0f);

                workspace.mine2b.vB0.f[0] = func_00283180(H(float, 0xAEC)) * H(float, 0xAF4);
                workspace.mine2b.vB0.f[1] = func_00283198(H(float, 0xAEC)) * H(float, 0xAF4);
                workspace.mine2b.vB0.f[2] = 0.0f;
                func_00282CC0(&H(Vec, 0xF0), &H(Vec, 0xF0), &workspace.mine2b.vB0);
            }
        }
        if (H(s16, 0xADC) && H(s16, 0x34E)) {
            if ((vz < 0.0f && H(float, 0xF8) > 0.0f) || H(s16, 0xAFC)) {
                s32 c;
                f32 s;
                H(s16, 0xAFE) = 0;
                s = func_00282C10(H(float, 0xAE0) / H(float, 0xAF0)) * 3.1415927f;
                if (H(s16, 0xAFC)) {
                    c = H(s16, 0xAFC) == 1;
                } else {
                    workspace.mine2b.vB0.q = H(U128, 0x110);

                    c = func_L00_002B5590(&workspace.mine2b.vB0) > 0.0f;
                }
                if (c) {
                    if (entry_object[0x43] != 0x35) {
                        func_L00_002D2168(0x35, 6, 17.0f);
                        H(s16, 0xAFC) = 1;
                        goto finish;
                    }
                    if (H(Moby *, 0x2290)->f42 == H(Moby *, 0x2290)->f43) {
                        func_L00_002A9E30(42.0f, s, 0.5f, -1.0f);
                        H(s16, 0xAFC) = 0;
                    }
                } else {
                    if (entry_object[0x43] != 0x35) {
                        func_L00_002D2168(0x35, 0x15, 9.0f);
                        H(s16, 0xAFC) = 2;
                        goto finish;
                    }
                    if (H(Moby *, 0x2290)->f42 == H(Moby *, 0x2290)->f43) {
                        func_L00_002A9E30(12.0f, s, 0.5f, -1.0f);
                        H(s16, 0xAFC) = 0;
                    }
                }
            }
        }
        goto finish;
    }

case 20:
{
    float distance, limit, magnitude;
    int accelerate, settle;
    if (H(int, 0xC2C) || H(float, 0xC38) < (float)D_L23_00261E90[H(s16, 0xBFC)].field[6]) H(u8, 0x1239) = 2;
    H(float, 0x1B0) = 0.0f;
    if (H(u8, 0x1492)) {
        if (H(void *, 0xBE4)) {
            float range = func_00282E80(HP(0x80), H(u8 *, 0xBE4) + 16);
            int boost = H(u8, 0x1496) || H(u8, 0x149B) || H(u8, 0x1495);
            if ((range > 2.0f && range < 5.0f) || boost) H(float, 0x1B0) = 0.075f;
            func_L00_002B41B8(0.0011111111f, 0.0011111111f);
            H(float, 0xF0) = func_00283180(H(float, 0x98)) * H(float, 0x1B4);
            H(float, 0xF4) = func_00283198(H(float, 0x98)) * H(float, 0x1B4);
        } else {
            func_L00_002B41B8(0.00055555557f, 0.00055555557f);
            func_L00_002D3BD8(HP(0xF0), HP(0xF0), H(float, 0x1B4));
        }
    } else {
        accelerate = (H(u64, 0x1490) & 0x00FFFF0000000000ULL) || H(u8, 0x149B) || H(float, 0x31C) > 4.0f;
        if (H(void *, 0xBE4)) {
            func_00282CF0(&workspace.state_14.delta, H(u8 *, 0xBE4) + 16, HP(0x80));
            distance = func_L00_002D3A58(&workspace.state_14.delta);
            if ((distance > 2.0f && distance < 5.0f) || accelerate) H(float, 0x1B0) = 0.075f;
            func_L00_002B41B8(0.0069444445f, 0.0069444445f);
            func_00282F20(&workspace.state_14.u.movement, HP(0x0), H(float, 0x1B4));
            func_L00_002D3BD8(HP(0xF0), HP(0xF0), 0.0f);
            func_00282CC0(HP(0xF0), HP(0xF0), &workspace.state_14.u.movement);
        } else {
            if (accelerate && H(int, 0x1B8) < 70) H(float, 0x1B0) = 0.075f;
            func_L00_002B41B8(0.004166667f, 0.004166667f);
            func_L00_002D3BD8(HP(0xF0), HP(0xF0), H(float, 0x1B4));
        }
    }
    if (H(int, 0xBE8) || H(void *, 0xBE4)) {
        H(float, 0x1A0) = H(float, 0xBEC);
        qcopy(&H(Vec4, 0x190), &H(Vec4, 0xBC0));
        func_L00_002B3EF8(0, 0.05f, 0.2f, 0.2821616f);
    } else if (H(float, 0xC38) < 25.0f) func_L00_002B75A0(8.0f, 1.0471977f, 1.0471977f);
    limit = 0.12833333f;
    if (H(float, 0x31C) > 2.25f) limit = 0.064166665f;
    else if (H(float, 0x31C) > 1.8f) limit = 0.0898333266f;
    if (!H(int, 0xC2C) && H(float, 0xC38) > 23.5f && H(float, 0x118) < 0.0f && H(s16, 0x34E)) {


        qcopy(&workspace.state_14.delta, &H(Vec4, 0x80));
        func_L00_002D3778(&workspace.state_14.delta, &workspace.state_14.delta, -0.5f);
        func_00282F20(&workspace.state_14.force, HP(0x0), 2.0f);
        func_002A8C00(workspace.state_14.u.contact, H(void *, 0x2290), 0x10000, 2.0f, &workspace.state_14.force);
        *(float *)(workspace.state_14.u.contact + 12) = 5627.9248f;
        workspace.state_14.u.contact[24] = 0;
        workspace.state_14.u.contact[25] = 1;
        *(u16 *)(workspace.state_14.u.contact + 26) = 71;
        func_00277F48(0.4f, &workspace.state_14.delta, 0x10, H(void *, 0x2290), workspace.state_14.u.contact);
    }
    if (func_L00_002B3998(25.7f)) {
        func_L00_002D6900(25);
        H(u16, 0x1FA) = 50;
        if (D_001A7B2A) {
            FLD(D_L23_001BA500, float, 0x180) = 0.1f;
            FLD(D_L23_001BA500, int, 0x188) = 30;
            H(u16, 0x224) = 35;
            FLD(D_L23_001BA500, int, 0x16C) = 0;
        }
    }
    settle = 14;
    if (H(int, 0x1B8) < 9) {
        magnitude = func_L00_002D3B00(HP(0xF0));
        func_002AA2E8(&magnitude, limit, 0.041666668f);
        func_L00_002D3B58(HP(0xF0), HP(0xF0), magnitude);
    } else if (H(int, 0x1B8) > settle) {
        float speed;
        func_L00_002D34C0(HP(0xF0), HP(0xF0), 0.036111113f);
        if (func_L00_002D3B00(HP(0xF0)) < 0.0f) H(float, 0xC00) = 1.0f;
        shared_speed = -0.6166667f;
        if (D_L23_001A8FF0) shared_speed = -1.1666667f;
        if (func_L00_002D3B00(HP(0xF0)) < shared_speed) func_L00_002D3B58(HP(0xF0), HP(0xF0), shared_speed);
    }
    goto finish;

}


case 21: case 131:
{
    float angle, correction, speed, heading;
    int steer, locked;
    H(float, 0x1B0) = 0.0f;
    if (H(int, 0xC2C) || H(float, 0xC38) < (float)D_L23_00261E90[H(s16, 0xBFC)].field[6]) H(u8, 0x1239) = 2;
    locked = H(int, 0x22A0) == 1 && H(int, 0x22A8) >= 21;
    if (!locked) {
        if (H(int, 0xBE8) || H(void *, 0xBE4)) {
            int sharp = 0;
            if (H(u8, 0x22C3)) {
                angle = func_L00_002B9B38(HP(0xBC0), 0);
                correction = func_L00_002B9B38(HP(0xBC0), 1);
            } else {
                angle = func_00283BE0(H(float, 0xBEC), H(float, 0x98));
                correction = func_002AA738(H(float, 0xBEC), 1, H(float, 0x98));
            }
            if (correction < 4.3633237f) sharp = 1;

            if (angle > 0.0f) H(float, 0xC20) = 1.0f / (correction + 1.0f);
            H(float, 0x1A0) = H(float, 0xBEC);
            qcopy(&H(Vec4, 0x190), &H(Vec4, 0xBC0));
            if (sharp) func_L00_002B3EF8(1, 0.057f, 0.2f, 0.2821616f);
            else func_L00_002B3EF8(0, 0.057f, 0.2f, 0.2821616f);

        } else {
            steer = 1;
            if (H(u32, 0x2294) == 131 && H(int, 0x1B8) > 11) steer = 0;
            else if (!H(int, 0xC2C) && H(float, 0xC38) > 6.0f) steer = 0;
            if (steer) {
                if (H(u32, 0x2294) == 21) func_L00_002B75A0(14.0f, 0.52359885f, 0.78539824f);
                else func_L00_0041E958(64.0f, 0.17453295f, 0.3490659f);
            }
        }
    }
    if (!H(int, 0xC2C) && H(u8 *, 0x2290)[0x43] == 26 && func_L00_002B3998(33.0f)) {
        if (H(u8, 0x1492) && H(float, 0x170) < 0.033333335f) {
            H(float, 0xF0) += func_00283180(H(float, 0x98)) * 0.021666666f;
            H(float, 0xF4) += func_00283198(H(float, 0x98)) * 0.021666666f;
            qcopy(&H(Vec4, 0x140), &H(Vec4, 0xF0));
        }
        if (H(u32, 0x2294) == 21) func_L00_002BA508();
    }
    if (H(u8, 0x1492)) {
        if (func_L00_002B3998(84.0f)) {
            speed = 0.041666668f;
            heading = func_00283B98(H(float, 0x98), 3.1415927f);
            if (D_00138320 & 8) speed = 0.050000004f;
            H(float, 0xF0) += func_00283180(heading) * speed;
            H(float, 0xF4) += func_00283198(heading) * speed;
            qcopy(&H(Vec4, 0x140), &H(Vec4, 0xF0));
        }
        { func_L00_002B9598(); goto finish; }
    }
    func_L00_002B41B8(0.010277778f, 0.007777778f);
    func_L00_002B4208(99999.0f);
    if (H(s16, 0x34E)) func_L00_002D34C0(&H(Vec4, 0xf0), &H(Vec4, 0x130), 0.0069444445f);
    else func_L00_002D34C0(&H(Vec4, 0xf0), &H(Vec4, 0xf0), 0.0150000006f);
    goto finish;
}


case 19:
{
    unsigned char *animation;
    int steer;
    float distance, excess, scaled, radius, limit, angle, magnitude, rate, offset;
    if (H(int, 0xC2C) || H(float, 0xC38) < (float)D_L23_00261E90[H(s16, 0xBFC)].field[8]) H(u8, 0x1239) = 2;
    if (H(u8, 0x1492)) { func_L00_002B9598(); goto finish; }
    animation = (unsigned char *)&D_L23_00261E90[H(s16, 0xBFC)];
    H(float, 0x1B0) = 0.0f;
    if (H(void *, 0xBE4) && H(int, 0x1B8) < 4) {
        distance = func_00282E80(H(u8 *, 0xBE4) + 16, HP(0x80));
        if (D_L23_001A8FF0) distance = func_00282E48(H(u8 *, 0xBE4) + 16, HP(0x80));
        distance -= 0.5f;
        if (distance < 0.0f) distance = 0.0f;
        if (*(int *)(animation + 4) == 0) { offset = 0.75f; radius = 0.8f; limit = 4.0f; }
        else if (*(int *)(animation + 4) == 1) { offset = 0.6f; radius = 1.7f; limit = 4.0f; }
        else { offset = 1.3f; radius = 1.7f; limit = 1.9f; }
        excess = distance - offset;
        if (func_00282C48(excess) < radius + 3.0f) {
            scaled = excess * 1.1111112f;
            if (scaled > limit) scaled = limit;
            if (scaled > 1.0f) H(float, 0xBF4) = scaled;
        }
    }
    switch (*(int *)(animation + 4)) {
    case 0:
        if (H(float, 0xC38) < 18.0f) H(float, 0x1B0) = H(float, 0xBF4) * 0.07333334f;
        break;
    case 1:
        if (H(int, 0xC2C) || H(float, 0xC38) < 9.0f) {
            if (H(float, 0xC38) > 8.0f) H(float, 0x1B0) = H(float, 0xBF4) * 0.050000004f;
            else if (H(float, 0xC38) > 7.0f) H(float, 0x1B0) = H(float, 0xBF4) * 0.075f;
            else H(float, 0x1B0) = H(float, 0xBF4) * 0.095f;
        }
        break;
    case 2:
        if (H(int, 0xC2C) || H(float, 0xC38) < 12.0f) H(float, 0x1B0) = H(float, 0xBF4) * 0.06166667f;
        break;
    }
    func_002AA2E8(HP(0xC20), 1.0f, 0.2f);
    if (H(int, 0xBE8) || H(void *, 0xBE4)) {
        if (H(u8, 0x22C3)) angle = func_L00_002B9B38(HP(0xBC0), 0);
        else angle = func_00283BE0(H(float, 0xBEC), H(float, 0x98));
        magnitude = func_00282C48(angle);
        if (*(int *)(animation + 4) == 1 && angle > 0.0f) H(float, 0xC20) = 1.0f / (magnitude + 1.0f);
        H(float, 0x1A0) = H(float, 0xBEC);
        qcopy(&H(Vec4, 0x190), &H(Vec4, 0xBC0));
        func_L00_002B3EF8(0, 0.05f, 0.2f, 0.2821616f);
    } else {
        steer = 1;
        if (*(int *)(animation + 4) == 1 && !H(int, 0xC2C) && H(float, 0xC38) > 7.0f) steer = 0;
        if (steer) func_L00_002B75A0(5.0f, 0.78539824f, 0.78539824f);
    }
    func_L00_002B41B8(0.010277778f, 0.007777778f);
    if (H(int, 0xBE8)) {
        if (H(u8, 0x22C3)) func_L00_002B42D8(HP(0xBC0));
        else func_L00_002B4208(H(float, 0xBEC));
    } else func_L00_002B4208(99999.0f);
    if (H(s16, 0x34E)) func_L00_002D34C0(HP(0xF0), HP(0x130), 0.0069444445f);
    else func_L00_002D34C0(HP(0xF0), HP(0xF0), 0.015000001f);
    func_L00_002B9F00(3.7f, 0.0f, 0.35f);
    goto finish;
}


case 0x77:
    func_002AA2E8(&H(float, 0x1b4), 0.0f, 0.00666666683f);
    if (D_L23_001A8FF0) {
        func_00282F20(&H(Vec4, 0xf0), &H(Vec4, 0xbd0), H(float, 0x1b4));
        if (0.0f < H(float, 0x31c))
            func_L00_002D34C0(&H(Vec4, 0xf0), &H(Vec4, 0x130), 0.0069444445f);
        else func_L00_002D3B58(&H(Vec4, 0xf0), &H(Vec4, 0xf0), 0.0f);
        func_00282D30(&H(Vec4, 0x190), &H(Vec4, 0xbd0), -1.0f);
    } else {
        H(float, 0xf0) = func_00283180(H(float, 0xbf0)) * H(float, 0x1b4);
        H(float, 0xf4) = func_00283198(H(float, 0xbf0)) * H(float, 0x1b4);
        if (0.0f < H(float, 0x31c)) H(float, 0xf8) = H(float, 0x128) - 0.0069444445f;
        else H(float, 0xf8) = 0.0f;
        H(float, 0x1a0) = func_00283B98(H(float, 0xbf0), 3.14159274f);
    }
    func_L00_002B3EF8(0, 0.0500000007f, 0.200000003f, 0.282161593f);
    goto finish;



case 0x1F:
{
    s32 start, fade;
    if (H(s32,0xBE8) || H(s32,0xBE4)) {
        H(float,0x1A0)=H(float,0xBEC);
        func_L00_002B3EF8(0,0.05f,0.2f,0.28216159f);
    } else if (H(s32,0x1B8)<4) func_L00_002B75A0(11.0f,0.87266469f,-1.0f);
    H(float,0x1B0)=0.0f;
    start = 10;
    fade = 18;
    if (H(s32,0x1B8)>start && H(s32,0x1B8)<18) H(float,0x1B0)=0.3f;
    if (H(s32,0x1B8)==8 && H(float,0x184)<0.33333334f) {
        func_L00_00322A98(H(void*,0x2290),HP(0x18E0));
        func_L00_00322AC0(HP(0x18E0),48,2,0.0f);
        func_L00_00322AC0(HP(0x18E0),23,4,0.0f);
        func_L00_00322AC0(HP(0x18E0),12,6,0.0f);
    }
    {
        int mode = H(s32,0x1B8)>fade?5:0;
        func_L00_00322BE0(HP(0x18E0),mode);
    }
    if (H(u8,0x1492)) {
        if (H(s32,0x1B8)>start && H(s32,0x1B8)<17 && H(float,0x178)<0.14166668f) {
            H(float,0xF0)+=func_00283180(H(float,0x98))*0.020000001f;
            H(float,0xF4)+=func_00283198(H(float,0x98))*0.020000001f;
            qcopy(&H(Vec4,0x140), &H(Vec4,0xF0));
        }
        func_L00_002B9598();
    } else {
        if (H(s32,0x1B8)>start) func_L00_002B41B8(0.052777778f,0.025f);
        if (H(s32,0xBE8)) func_L00_002B4208(H(float,0xBEC));
        else func_L00_002B4208(99999.0f);
    }
    {
        u8 *target;
        if (H(u32,0x2294)==0x1F && H(s32,0x1B8)>start && H(s32,0x1B8)<22 && (target=H(u8*,0x1220))) {


            float angle;
            int hit;
            workspace.state_1f.impulse.x=func_00283180(H(float,0x98))*2.0f;
            workspace.state_1f.impulse.y=func_00283198(H(float,0x98))*2.0f;
            workspace.state_1f.impulse.z=1.3f;
            func_002A8C00(workspace.state_1f.query, H(void*,0x2290), 0x30000, 3.0f, &workspace.state_1f.impulse);
            *(float*)(workspace.state_1f.query+12)=5627.9248f;
            workspace.state_1f.query[25]=3;
            workspace.state_1f.query[24]=0;
            *(u16*)(workspace.state_1f.query+26)=*(u16*)(target+0xAA);
            angle=H(float,0x98);
            workspace.state_1f.point.x=func_00283180(angle)*0.8f;
            workspace.state_1f.point.y=func_00283198(angle)*0.8f;
            workspace.state_1f.point.z=0.55f;
            func_00282CC0(&workspace.state_1f.point,&workspace.state_1f.point,HP(0x80));
            hit=func_00277F48(0.8f, &workspace.state_1f.point, 0, target, workspace.state_1f.query);
            func_L00_002BA138(target,hit);
            angle=func_00283B98(H(float,0x98),-0.87266469f);
            workspace.state_1f.point.x=func_00283180(angle)*0.8f;
            workspace.state_1f.point.y=func_00283198(angle)*0.8f;
            workspace.state_1f.point.z=0.55f;
            func_00282CC0(&workspace.state_1f.point,&workspace.state_1f.point,HP(0x80));
            hit=func_00277F48(0.8f, &workspace.state_1f.point, 0, H(void*,0x2290), workspace.state_1f.query);
            func_L00_002BA138(target,hit);
            angle=func_00283B98(H(float,0x98),0.87266469f);
            workspace.state_1f.point.x=func_00283180(angle)*0.8f;
            workspace.state_1f.point.y=func_00283198(angle)*0.8f;
            workspace.state_1f.point.z=0.55f;
            func_00282CC0(&workspace.state_1f.point,&workspace.state_1f.point,HP(0x80));
            hit=func_00277F48(0.8f, &workspace.state_1f.point, 0, target, workspace.state_1f.query);
            func_L00_002BA138(target,hit);
        }
    }
    if (H(s32,0x1B8)>10) func_L00_002B9F00(3.7f,0.0f,0.35f);
    func_L22_002B8E10(1);
    if (H(s16,0x34E)) { func_L00_002D34C0(&H(Vec4, 0xf0), HP(0x120), 0.0061111115f); func_L00_002B4308(); goto finish; }
    func_L00_002D34C0(&H(Vec4, 0xf0), &H(Vec4, 0xf0), 0.0150000006f); goto finish;
}


case 0x22:
{
    H(float,0x1B0)=0.0f;
    if (H(s32,0xBE8)) {
        H(float,0x1A0)=H(float,0xBEC);
        qcopy(&H(Vec4,0x190), &H(Vec4,0xBC0));
        func_L00_002B3EF8(0,0.04f,0.2f,0.28216159f);
    } else func_L00_002B75A0(11.0f,0.87266469f,-1.0f);
    func_L00_002B41B8(0.008333334f,0.009722223f);
    func_L00_002B4208(99999.0f);
    if (H(s16, 0x34E)) {
        func_L00_002D34C0(&H(Vec4, 0xf0), &H(Vec4, 0x110), 0.015000001f); func_L00_002B4308();
    } else func_L00_002D34C0(&H(Vec4, 0xf0), &H(Vec4, 0xf0), 0.0150000006f);
    goto finish;
}


case 2: case 112:
{
    int early = H(u8, 0x1494) && H(float, 0x24C4) < 0.25f;
    float weight, turn_step, angle, factor, move;
    if (H(u8, 0x22B9) || early) {
        if (H(float, 0x174) > 0.016666668f) func_L00_002AA570(0, 2);
        if (H(float, 0x174) > 0.008333334f) func_L00_002AA750(2, 4);
        func_L00_002AA938(5, 2, 0);
    }
    if (!H(s16, 0x1454)) {
        float first_angle, second_angle;
        if (H(float, 0x174) < 0.028333336f) {
            H(u8, 0x40C) = 1;
            if (func_00282C48(H(float, 0x1A8)) > 2.0943954f && H(float, 0x24B8) == 1.0f)
                H(u8, 0x40F) = 1;
        }
        first_angle = func_L00_0032F038(1);
        second_angle = func_L00_0032F038(7);
        if (func_00283C80(first_angle, second_angle) > 1.9198624f &&
            func_00282C48(H(float, 0x1A8)) > 1.2217306f && H(float, 0x24B8) == 1.0f) {
            H(u8, 0x40F) = 1;
            H(u8, 0x40C) = 1;
        }
        if (func_00282C48(H(float, 0x1A8)) < 0.087266475f) H(u8, 0x40C) = 0;
    }
    if (H(u8, 0x40F) && func_00282C48(H(float, 0x1A8)) < 0.06981318f) H(u8, 0x40F) = 0;
    if (H(float, 0x24B8) < 0.2f) {
        if (H(int, 0x410)) H(u8, 0x40F) = 1;
        H(float, 0x1B0) = 0.0f;
        qcopy(&H(Vec4, 0x190), &H(Vec4, 0x3F0));
        H(float, 0x1A0) = H(float, 0x408);
    } else {
        func_L00_002B3D10();
        if (func_L00_002ADEA0(0) == 10 && (H(float, 0x24BC) == 1.0f || H(int, 0x410)) && !H(u8, 0x22BA)) {
            qcopy(&H(Vec4, 0x3F0), &H(Vec4, 0x190));
            H(int, 0x410) = 1;
            H(float, 0x408) = H(float, 0x1A0);
        } else {
            qcopy(&H(Vec4, 0x3F0), &H(Vec4, 0x0));
            H(float, 0x408) = H(float, 0x98);
        }
    }
    if (H(float, 0xA70) > 0.0f) {
        Vec4 *push = &H(Vec4, 0xA60);
        func_L00_002B54F8(0.7f, 0.0f);
        *(U128 *)&workspace.state_02.impulse = *(U128 *)push;
        H(float, 0x1B0) += func_L00_002B5590(&workspace.state_02.impulse);
        if (H(float, 0x1B0) < 0.011666667f) H(float, 0x1B0) = 0.011666667f;
        func_00282C88(push);
    }
    weight = 1.0f;
    if (H(s16, 0x1454)) func_L00_002B35A0();
    else {
        H(float, 0x1458) = H(float, 0x98);
        qcopy(&H(Vec4, 0x1440), &H(Vec4, 0x0));
        if (H(int, 0x2298) == 1 && !H(u8, 0x40F) && !H(u8, 0x22BA)) {
            func_L00_002B3EF8(0, 0.02f, 0.17f, 0.16580631f);
        } else {
            angle = func_00282C48(H(float, 0x1A8));
            if ((H(float, 0x24B8) < 0.9f || (H(u8, 0x22BA) && !H(u8, 0x40F))) && angle > 0.78539824f)
                weight = 0.0f;
            func_L00_002B3F68();
        }
    }
    func_L00_002B7B80();
    func_L00_002B8CB8();
    if (H(u8, 0x40F)) {
        float limit = 0.09916667f - func_00282C48(H(float, 0x1A8)) * 0.029178405f;
        if (limit < 0.0f) limit = 0.0f;
        if (H(float, 0x1B0) > limit) H(float, 0x1B0) = limit;
    }
    move = weight * 0.005f;
    turn_step = 0.0055555557f;
    if (H(u8, 0x40F)) {
        factor = 2.617994f - H(float, 0x1A8);
        if (factor > 1.0f) factor = 1.0f;
        if (factor < 0.2f) factor = 0.2f;
        H(float, 0x1B0) *= factor;
        turn_step = 0.004722222f;
    }
    angle = func_00282C48(H(float, 0x1A8));
    if (H(float, 0x24B8) < 0.75f && angle > 0.6108653f) {
        factor = 1.0f - angle * 0.4f;
        if (factor < 0.0f) factor = 0.0f;
        H(float, 0x1B0) *= factor;
    }
    func_L00_002B41B8(move, turn_step);
    if (H(u8, 0x40C) || H(s16, 0x1454)) {
        if (!H(u8, 0x22C3)) {
            if (H(s16, 0x1454)) func_L00_002B4208(H(float, 0x1458));
            else func_L00_002B4208(H(float, 0x1A0));
        } else if (H(s16, 0x1454)) func_L00_002B42D8(HP(0x1440));
        else func_L00_002B42D8(HP(0x190));
    } else func_L00_002B4208(99999.0f);
    func_L22_002B8E10(1);
    if (H(s16, 0x214)) func_L00_002B9F00(5.0f, 0.2f, 0.35f);
    
    if (H(s16, 0x34E)) {
        
        { func_L00_002D34C0(&H(Vec4, 0xf0), HP(0x130), 0.0069444445f); func_L00_002B4308(); goto finish; }
    }
    { func_L00_002D34C0(&H(Vec4, 0xf0), &H(Vec4, 0xf0), 0.0150000006f); goto finish; }
}


case 0x7b:
{

    float turn, shape;
    s32 hits, i;
    func_L00_002B9BB0(4, H(u8 *, 0x2290), 13);
    func_L00_002B39F0(1.0f, 0);
    H(float, 0x1b0) = 0.191666678f;
    func_L00_002A9D38(&workspace.state_7b.local, &H(Vec4, 0x9f0), 0.170000002f);
    turn = (0.0203621779f * H(float, 0x24b8)) * workspace.state_7b.local.x;
    if (D_L23_001A8FF0 == 0 && H(s32, 0x1b8) < 60) {
        turn = turn * 0.100000001f;
        H(float, 0x1b0) = 0.5f;
    }
    if (0.200000003f < H(float, 0x24b8)) func_L00_002B3DC0(0.0f, 0.0f, turn);
    func_L00_002B41B8(0.027777778f, 0.00416666688f);
    func_L00_002B4208(99999.0f);
    if (D_L23_001A8FF0) {
        qcopy(&workspace.state_7b.target_position, &H(Vec4, 0x2d0));
        func_L00_002D3778(&workspace.state_7b.target_position, &workspace.state_7b.target_position, 0.170000002f);
        func_002AA458(&H(Vec4, 0x80), &workspace.state_7b.target_position, &H(float, 0xa00),
                     0.0399999991f, 0.300000012f, 0.125f);
    } else {
        func_002AA3A8(&H(float, 0x88), &H(float, 0xa00), H(float, 0x318) + 0.170000002f,
                     0.0399999991f, 0.300000012f, 0.125f);
    }
    func_00282D30(&workspace.state_7b.target_position, &H(Vec4, 0x110), 3.0f);
    func_00282CC0(&workspace.state_7b.target_position, &workspace.state_7b.target_position, &H(Vec4, 0xe0));
    hits = func_00277F48(0.569999993f, &workspace.state_7b.target_position, 0, H(u8 *, 0x2290), 0);
    if (hits != 0) {
        func_00282D30(&workspace.state_7b.impulse, &H(Vec4, 0x110), 7.0f);
        for (i = 0; i < hits; ++i) {
            if (func_002ABB78(D_L23_001C4B00[i]) != 0)
                func_002A8F70(D_L23_001C4B00[i], H(u8 *, 0x2290), 0x10000,
                             &H(Vec4, 0x80), &workspace.state_7b.impulse, 1.0f);
        }
    }
    func_L00_002AB0A8(0.0170000009f, 0.300000012f);
    func_L00_002AB0D8(0.0250000004f, 0.300000012f);
    func_L00_002AB0F0(0.0299999993f, 0.270000011f);
    shape = turn * 27.0f;
    if (1.70000005f < shape) shape = 1.70000005f;
    else if (shape < -1.70000005f) shape = -1.70000005f;
    FLD(D_L23_00260310, float, 0x60) = -shape;
    FLD(D_L23_00260310, float, 0x278) = shape * 0.5f;
    FLD(D_L23_00260310, float, 0x1C8) = shape * 0.5f;
    goto finish;
}



    case 0x2E:
        func_L00_002B9598();
        func_L00_002AB0A8(0.04f, 0.2f);
        func_L00_002AB0C0(0.04f, 0.2f);
        func_L00_002AB0D8(0.04f, 0.2f);
        func_L00_002AB0F0(0.02f, 0.2f);
        if (entry_object[0x43] == 0x37) {
            f32 t = H(float, 0x1A8);
            if (t > 1.4f) t = 1.4f;
            else if (t < -1.4f) t = -1.4f;
            FLD(D_L23_00260310, float, 0x60) = t * -0.14f;
            FLD(D_L23_00260310, float, 0x118) = t * 0.3f;
            FLD(D_L23_00260310, float, 0x1C0) = t * -0.22f;
            FLD(D_L23_00260310, float, 0x278) = t * 0.4f;
            FLD(D_L23_00260310, float, 0x274) = func_00282C48(t) * -0.09f;
            FLD(D_L23_00260310, float, 0x270) = func_00282C48(t) * 0.08f;
        } else if (entry_object[0x43] == 0x66) {
            f32 dir = func_00283B98(func_00283BE0(func_00283248(H(float, 0x110), H(float, 0x114)), H(float, 0x98)), 3.1415927f);
            f32 k = H(float, 0x174) * 6.9813175f;
            if (k > 0.43633235f) k = 0.43633235f;
            {
            f32 forward = func_00283180(dir) * k;
            f32 side = -func_00283198(dir) * k;
            FLD(D_L23_00260310, float, 0x114) = forward;
            FLD(D_L23_00260310, float, 0x110) = side;
            }
        }
        if (H(s16, 0x34E)) {
            func_L00_002D34C0(&H(Vec, 0xF0), &H(Vec, 0x110), 0.0069444445f);
        } else {
            H(float, 0xF8) = 0.0f;
            func_L00_002D34C0(&H(Vec, 0xF0), &H(Vec, 0xF0), 0.041666668f);
        }
        goto finish;

    case 0x30: {
        f32 prev, d, t;
        if (D_001A79F0 == 0 || (D_001A79F0 == 1 && D_US2_001CAB40 == 0)) func_L00_002B9BB0(2, H(Moby *, 0x2290), 0x13);
        if ((u32)D_001A79F0 < 2) {
            func_L00_002AA938(4, 2, 1);
        } else {
            func_L00_002AA938(4, 2, 0);
            workspace.mine.s00.f[0] = H(float, 0x80) + func_002A7878(-0.25f, 0.25f);
            workspace.mine.s00.f[1] = H(float, 0x84) + func_002A7878(-0.25f, 0.25f);
            workspace.mine.s00.f[2] = H(float, 0x88) + func_002A7878(-0.1f, 0.4f);
            func_00282D30(&workspace.mine.s10, &H(Vec, 0x110), 0.9f);
            workspace.mine.s10.f[0] += func_002A7878(-0.011666667f, 0.011666667f);
            workspace.mine.s10.f[1] += func_002A7878(-0.011666667f, 0.011666667f);
            workspace.mine.s10.f[2] += func_002A7878(0.016666668f, 0.033333335f);
            func_L00_00338D28(&workspace.mine.s00, &workspace.mine.s10, func_002A7878(37800.0f, 75600.0f));
        }
        H(float, 0x1A0) = H(float, 0xB40);
        prev = H(float, 0x98);
        func_L00_002B3EF8(0, 0.033f, 0.3f, 0.069813184f);
        d = func_00283C80(H(float, 0x98), prev);
        func_00282C88(&H(Vec, 0xF0));
        func_L00_002B94D8(0.0019444445f);
        H(float, 0xF8) = H(float, 0x118) - 0.013888889f;
        if (H(float, 0xF8) > -0.011111111f) H(float, 0xF8) = -0.011111111f;
        if (d > 0.023271061f) d = 0.023271061f;
        t = d * 9.0f;
        func_002AA898(&H(float, 0x90), t * 0.5f, &H(float, 0xB54), 0.007f, 0.17f, 0.020362178f, 0);
        func_002AA898(&H(float, 0x94), -H(float, 0xB44), &H(float, 0xB58), 0.035f, 0.3f, 0.031997707f, 0);
        func_L00_002AB0C0(0.009f, 0.22f);
        func_L00_002AB0D8(0.04f, 0.2f);
        func_L00_002AB0F0(0.02f, 0.2f);
        FLD(D_L23_00260310, float, 0x118) = t * 2.1f;
        FLD(D_L23_00260310, float, 0x110) = t * 3.5f;
        goto finish;
    }

case 0x27: case 0x28: case 0x29: case 0x2A: case 0x3E:
{

    int typeAllowsPose,poseAvailable,heightJump,configuration;
    if ((u32)(H(u32,0x2294)-0x28)>=2U && H(u32,0x2294)!=0x3E) func_L00_002B9BB0(0,H(void*,0x2290),0);
    else {
        int slot=H(s32,0x242C);
        if (slot!=-1 && FLD(D_00188660+slot*0x70, void *, 0x88)==H(void*,0x2290) &&
            FLD(D_00188660+slot*0x70, u8, 0x74)) func_002E59F8(slot);
        H(s32,0x242C)=-1;
    }
    if (H(u32,0x2294)==0x27 || H(u32,0x2294)==0x2A) {

        float angle;
        float magnitude;
        qcopy(&workspace.state_27.first, &H(Vec4,0x80));
        angle=func_002A78D8(0.0f,0.52359885f);
        angle=func_00283B98(H(float,0x64C),angle);
        magnitude=func_002A7878(0.06666667f,0.116666675f);
        workspace.state_27.second.x=func_00283180(angle)*magnitude;
        workspace.state_27.second.y=func_00283198(angle)*magnitude;
        workspace.state_27.second.z=0.0f;
        workspace.state_27.second.z=func_002A7878(0.050000004f,0.083333336f);
        workspace.state_27.second.w=-0.008333334f;
        func_002BE278(&workspace.state_27.first,&workspace.state_27.second,0,-1.0f);
    }
    configuration=FLD(D_L23_00266A70+D_00139568[H(s32,0x1248)]*0xE0, s32, 0x1C);
    typeAllowsPose=configuration!=0;
    if (H(s32,0x1248)==13) typeAllowsPose=0;
    poseAvailable=0;
    if (typeAllowsPose) poseAvailable=H(u8,0x22BA)!=0;
    func_L00_00341FA8(H(void*,0x630),HP(0x80),HP(0x5D0),HP(0x634),HP(0x638),H(s32,0x654),999.0f,2.0f,2.5f);
    if (H(s32,0x660))
        func_L00_00341FA8(H(void*,0x664),HP(0x80),HP(0x610),HP(0x668),HP(0x66C),H(s32,0x670),999.0f,2.0f,2.5f);
    heightJump=0;
    if (H(float,0x31C)>1.0699999f && H(u32,0x2294)!=0x28 && H(u32,0x2294)!=0x3E && !H(s32,0x660))
        heightJump=H(s32,0x1BC)>30;
    if (heightJump) ++H(s32,0x6C8); else H(s32,0x6C8)=0;
    if ((H(s32,0x640) && ++H(s32,0x640)) || heightJump) {
        qcopy(&H(Vec4,0xF0), &H(Vec4,0x120));
        if ((u32)(H(u32,0x2294)-0x28)<2U) { func_L00_002B6560();goto finish; }
        if (func_00282E20(HP(0xF0)) < 0.041666668f) {
            func_002AA2E8(HP(0x1B4), 0.06666667f, 0.011111111f);
            H(float,0xF0)=func_00283180(H(float,0x64C))*H(float,0x1B4);
            H(float,0xF4)=func_00283198(H(float,0x64C))*H(float,0x1B4);
        }
        H(float,0xF8)-=0.0061111115f;

        goto finish;
    } else {
        float pathStep=(float)H(s32,0x648);
        float pathSpeed=H(float,0x644)*pathStep;
        if (H(u32,0x2294)==0x3E) pathSpeed=H(float,0x69C)*pathStep;
        func_L00_00341820(H(void*,0x630), &workspace.state_27.first, HP(0x634), HP(0x638), pathSpeed, H(s32,0x654));
        if (H(s32,0x660))
            func_L00_00341820(H(void*,0x664), &workspace.state_27.second, HP(0x668), HP(0x66C), pathSpeed, H(s32,0x670));
        if (H(s32,0x1BC)>90) {
            int segment,hitA,hitB;
            float weight,heading;
            pathSpeed=H(float,0x170);pathSpeed*=30.0f;
            qcopy(&workspace.state_27.u.p.probeA, &H(Vec4,0x80));
            segment=H(s32,0x634);weight=H(float,0x638);
            hitA=func_L00_00341820(H(void*,0x630), &workspace.state_27.u.p.probeA, &segment, &weight, pathSpeed, H(s32,0x654));
            qcopy(&workspace.state_27.u.p.probeB, &H(Vec4,0x80));
            segment=H(s32,0x634);weight=H(float,0x638);
            hitB=func_L00_00341820(H(void*,0x630), &workspace.state_27.u.p.probeB, &segment, &weight, pathSpeed+0.1f, H(s32,0x654));
            if ((!(hitA | hitB) || H(s32,0x654)) && H(u32,0x2294)==0x27) {
                heading=func_00283248(workspace.state_27.u.p.probeB.x-workspace.state_27.u.p.probeA.x,workspace.state_27.u.p.probeB.y-workspace.state_27.u.p.probeA.y);
                heading=func_00283BE0(H(float,0x64C),heading)*0.47f;
                if (heading>0.78539824f) heading=0.78539824f;
                if (heading< -0.78539824f) heading=-0.78539824f;
                func_L00_002AB0A8(0.03f,0.2f);
                if (H(s32,0x65C)) FLD(D_L23_00260310, float, 0x64)=-heading;
                else FLD(D_L23_00260310, float, 0x64)=heading;
            }
        }
        if (H(u32,0x2294)!=0x28 && H(u32,0x2294)!=0x3E && H(u32,0x2294)!=0x29) {
            float horizontal=func_00282E20(HP(0x110));
            FLD(D_L23_00260310, float, 0x60)=func_00283248(horizontal,H(float,0x118));
        }
        if (typeAllowsPose) {
            u8 *pose_hero=D_00189E20;
            float poseScale=0.3f;
            func_L00_002AB0F0(0.017f,0.3f);
            func_L00_002AB0C0(0.027f,poseScale);
            func_L00_002AB0D8(0.027f,poseScale);
            if (FLD(pose_hero,void*,0x6A8)) {
                float angle,sideScale;
                func_00282CF0(&workspace.state_27.u.d.displacement,FLD(pose_hero,u8*,0x6A8)+0x10,&FLD(pose_hero,u8,0x80));
                func_00283098(&workspace.state_27.u.d.displacement,&workspace.state_27.u.d.displacement,&FLD(pose_hero,u8,0x40));
                angle=func_00283248(workspace.state_27.u.d.displacement.x,workspace.state_27.u.d.displacement.y);
                if (FLD(pose_hero,u8*,0x2290)[0x42]==0x31) {
                    angle=func_00283BE0(angle,1.5707965f);sideScale=0.2f;
                } else {
                    angle=func_00283BE0(angle,-1.5707965f);sideScale=0.5f;
                }
                FLD(D_L23_00260310, float, 0x1C8)=angle*sideScale;
                FLD(D_L23_00260310, float, 0x278)=angle*poseScale;
            } else {
                u8 action=FLD(pose_hero,u8*,0x2290)[0x43];
                float angularBase,pose;
                if (action!=0x31 && FLD(pose_hero,u8*,0x2290)[0x43]==0x48) {
                    poseScale=0.5f;
                    pose=func_00283B98(0.13962635f,FLD(pose_hero,float,0x6A0));
                    angularBase=-0.06981318f;
                    FLD(D_L23_00260310, float, 0x278)=pose;
                    FLD(D_L23_00260310, float, 0x118)=func_00283B98(angularBase,FLD(pose_hero,float,0x6A0)*poseScale);
                    FLD(D_L23_00260310, float, 0x1C8)=func_00283B98(angularBase,FLD(pose_hero,float,0x6A0)*poseScale);
                } else if (action==0x31 || action==0x47) {
                    poseScale=0.58823526f;
                    pose=func_00283B98(-0.8203048f,FLD(pose_hero,float,0x6A0));
                    angularBase=0.73303837f;
                    FLD(D_L23_00260310, float, 0x278)=pose;
                    FLD(D_L23_00260310, float, 0x118)=func_00283B98(angularBase,FLD(pose_hero,float,0x6A0)*poseScale);
                    FLD(D_L23_00260310, float, 0x1C8)=func_00283B98(angularBase,FLD(pose_hero,float,0x6A0)*poseScale);
                }
            }
        }
        {
            int nextIndex=func_L00_003417B8(H(void*,0x630),H(s32,0x634),H(s32,0x648),H(s32,0x654));
            float distance;
            func_00282CF0(&workspace.state_27.u.d.displacement,(u8*)H(void*,0x630)+(nextIndex*16+16),&workspace.state_27.first);
            distance=func_00282DF0(&workspace.state_27.u.d.displacement);
            if (distance<0.001f) {
                if (H(s32,0x634)==nextIndex) { H(s32,0x640)=1;goto finish; }
            } else {
                H(float,0x64C)=func_00283248(workspace.state_27.u.d.displacement.x,workspace.state_27.u.d.displacement.y);
                H(float,0x650)=func_00283248(func_00282E20(&workspace.state_27.u.d.displacement),workspace.state_27.u.d.displacement.z);
            }
        }
        H(float,0x1A0)=func_00283B98(H(float,0x64C),H(float,0x658));
        func_L00_002B3EF8(0,0.015f,0.15f,0.10471977f);
        if (((u32)(H(u32,0x2294)-0x28)<2U && !H(u8,0x49C)) || H(u32,0x2294)==0x3E) {
            if (H(s32,0x694)) {
                float desired=func_00283248(H(float,0x620)-H(float,0x80),H(float,0x624)-H(float,0x84));
                if (func_00283C80(H(float,0x98),desired)<1.5707965f) {
                    H(float,0x1A0)=desired;
                    func_L00_002B3EF8(0,0.04f,0.2f,0.10471977f);
                }
            }
            if (H(s32,0x660) && H(s32,0x678)<49) {
                float fraction;
                func_00282CF0(&workspace.state_27.u.d.displacement,&workspace.state_27.first,&workspace.state_27.second);
                ++H(s32,0x678);
                fraction=(float)H(s32,0x678)*0.020833334f;
                func_00282D30(&workspace.state_27.u.d.displacement,&workspace.state_27.u.d.displacement,fraction);
                fraction=(float)(H(s32,0x678)-1)*0.020833334f;
                func_00282CF0(&workspace.state_27.u.d.previousStep,&workspace.state_27.first,&workspace.state_27.second);
                func_00282D30(&workspace.state_27.u.d.previousStep,&workspace.state_27.u.d.previousStep,fraction);
                H(float,0x88)+=workspace.state_27.u.d.displacement.z-workspace.state_27.u.d.previousStep.z;
                func_00282CC0(&workspace.state_27.u.d.previousStep,&workspace.state_27.second,&workspace.state_27.u.d.displacement);
                func_00282CF0(&workspace.state_27.u.d.displacement,&workspace.state_27.u.d.previousStep,HP(0x80));
                H(float,0xF0)=workspace.state_27.u.d.displacement.x;H(float,0xF4)=workspace.state_27.u.d.displacement.y;
                func_00282CF0(&workspace.state_27.u.d.displacement,&workspace.state_27.first,HP(0x5D0));
                H(float,0x88)+=workspace.state_27.u.d.displacement.z;
                if (H(float,0x88)<H(float,0x5D8) && H(s32,0x678)<49 && H(float,0x88)<H(float,0x5D8)) H(float,0x88)=H(float,0x5D8);
            } else {
                func_00282CF0(&workspace.state_27.u.d.displacement,&workspace.state_27.first,HP(0x5D0));
                H(float,0xF0)=workspace.state_27.u.d.displacement.x;
                H(float,0x88)+=workspace.state_27.u.d.displacement.z;
                H(float,0xF4)=workspace.state_27.u.d.displacement.y;
                func_00282CF0(&workspace.state_27.u.d.previousStep,HP(0x5D0),HP(0x80));
                workspace.state_27.u.d.previousStep.z=0.0f;
                if (func_00282DF0(&workspace.state_27.u.d.previousStep)>0.016666668f)
                    func_00282F20(&workspace.state_27.u.d.previousStep,&workspace.state_27.u.d.previousStep,0.016666668f);
                H(float,0x80)+=workspace.state_27.u.d.previousStep.x;
                H(float,0x84)+=workspace.state_27.u.d.previousStep.y;
            }
            if (H(u32,0x2294)==0x3E) H(float,0xF8)-=0.006388889f;
            else func_L00_002B6560();
        } else {
            float steering,slope,speedAdjustment,negativeDistance,distance;
            int segment;float weight;
            H(s32,0x660)=0;
            steering=0.0f;
            if (H(float,0x24B8)>0.2f && poseAvailable) {
                func_L00_002B39F0(1.0f, 0);
                steering=func_00283BE0(H(float,0x1A0),H(float,0x64C));
                if (steering>0.78539824f) steering=0.78539824f;
                else if (steering< -0.78539824f) steering=-0.78539824f;
            }

            func_002AA898(HP(0x6A0), steering, HP(0x6A4), 0.015f, 0.3f, 0.0f, 0);
            func_002AA2E8(HP(0x680),0.20000002f,0.004166667f);
            segment=H(s32,0x634);weight=H(float,0x638);
            qcopy(&workspace.state_27.u.p.probeA, &H(Vec4,0x80));
            func_L00_00341820(H(void*,0x630), &workspace.state_27.u.p.probeA, &segment, &weight, 0.3f, H(s32,0x654));
            slope=func_00283248(func_00282E80(HP(0x5D0),&workspace.state_27.u.p.probeA),workspace.state_27.u.p.probeA.z-H(float,0x5D8));
            if (slope>0.0f) {
                speedAdjustment=slope*-0.07957746f;
                if (slope>0.26179942f) H(s32,0x67C)=0;
                else if (slope<0.13962635f && H(s32,0x67C)==0) H(s32,0x67C)=-1;
            } else {
                speedAdjustment=-slope*0.38197184f;
                if (slope< -0.19198623f) H(s32,0x67C)=1;
                else if (slope> -0.122173056f && H(s32,0x67C)==1) H(s32,0x67C)=-1;
            }
            if (H(float,0x674)<speedAdjustment) func_002AA2E8(HP(0x674),speedAdjustment,0.0022222223f);
            else func_002AA2E8(HP(0x674),speedAdjustment,0.00055555557f);
            if (H(float,0x674)>0.20000002f) H(float,0x674)=0.20000002f;
            if (H(float,0x674)< -0.041666668f) H(float,0x674)=-0.041666668f;
            H(float,0x644)=H(float,0x680)+H(float,0x674);
            if (H(float,0x644)<0.0f) H(float,0x644)=0.0f;
            func_00282CF0(HP(0xF0),&workspace.state_27.first,HP(0x5D0));
            func_00282CF0(&workspace.state_27.u.d.displacement,HP(0x5D0),HP(0x80));
            negativeDistance=-func_00282DF0(&workspace.state_27.u.d.displacement);
            func_002AA3A8(&negativeDistance,HP(0x6AC),0.0f,0.03f,0.3f,0.116666675f);
            distance=func_00282DF0(&workspace.state_27.u.d.displacement);
            if (distance<H(float,0x6AC)) H(float,0x6AC)=distance;
            if (H(float,0x6AC)<distance) func_00282F20(&workspace.state_27.u.d.displacement,&workspace.state_27.u.d.displacement,H(float,0x6AC));
            func_00282CC0(HP(0x80),HP(0x80),&workspace.state_27.u.d.displacement);
            if (H(float,0x88)<H(float,0x5D8) && H(float,0x31C)<1.0f && H(float,0x88)<H(float,0x5D8))
                H(float,0x88)=H(float,0x5D8);
        }
        if (H(u32,0x2294)==0x2A && H(s32,0x1B8)<20) {


            float angle=func_002A78D8(0.3490659f,0.6108653f);
            angle=func_00283B98(H(float,0x64C),angle);
            workspace.state_27.direction.x=func_00283180(angle);workspace.state_27.direction.y=func_00283198(angle);workspace.state_27.direction.z=0.0f;
            func_002A8C00(workspace.state_27.u.query, H(void*,0x2290), 0x10000, 1.0f, &workspace.state_27.direction);
            qcopy(&workspace.state_27.position, &H(Vec4,0x80));workspace.state_27.position.z+=0.6f;
            func_00277F48(1.0f, &workspace.state_27.position, 0x10, H(void*,0x2290), workspace.state_27.u.query);
        }
        goto finish;
    }
}


case 0x71:
{

    float angle, radius, distance, vertical_error;
    s32 next_index;
    func_L00_002ADCF8(&workspace.state_71.reference_position);
    if (*(u8 *)(H(u8 *, 0x2290) + 0x43) == 0x5f) {
        func_L00_002B9BB0(0, H(u8 *, 0x2290), 0);
        if ((D_L23_001B22C8 & 1) != 0) {
            qcopy(&workspace.state_71.particle_position, &workspace.state_71.reference_position); /* lq/sq at 002C524C */
            func_00282D30(&workspace.state_71.particle_velocity, &H(Vec4, 0x110), 0.400000006f);
            angle = func_002A78D8(0.0f, 0.52359885f);
            angle = func_00283B98(H(float, 0x700), angle);
            radius = func_002A7878(0.0f, 0.0666666701f);
            workspace.state_71.particle_velocity.x = workspace.state_71.particle_velocity.x + func_00283180(angle) * radius;
            workspace.state_71.particle_velocity.y = workspace.state_71.particle_velocity.y + func_00283198(angle) * radius;
            workspace.state_71.particle_velocity.z = func_002A7878(0.0500000045f, 0.0833333358f);
            workspace.state_71.particle_velocity.w = -0.00972222257f;
            func_002BE278(&workspace.state_71.particle_position, &workspace.state_71.particle_velocity, 0, -1.0f);
        }
    }
    func_L00_00341FA8(H(void *, 0x6e0), &workspace.state_71.reference_position, &H(Vec4, 0x6d0),
                       &H(s32, 0x6e4), &H(float, 0x6e8), H(s32, 0x6fc),
                       999.0f, 8.0f, 2.5f);
    if (H(s32, 0x6f0) != 0) {
        qcopy_nc(&H(Vec4, 0xf0), &H(Vec4, 0x120));
        H(s32, 0x6f0) = H(s32, 0x6f0) + 1;
        H(float, 0xf8) = H(float, 0xf8) - 0.00611111149f;
        goto finish;
    }
    func_L00_00341820(H(void *, 0x6e0), &workspace.state_71.particle_position, &H(s32, 0x6e4), &H(float, 0x6e8), H(float, 0x6f4), H(s32, 0x6fc));
    next_index = func_L00_003417B8(H(void *, 0x6e0), H(s32, 0x6e4), 1, H(s32, 0x6fc));
    func_00282CF0(&workspace.state_71.particle_velocity, H(u8 *, 0x6e0) + 0x10 + next_index * 0x10, &workspace.state_71.particle_position);
    if (func_00282DF0(&workspace.state_71.particle_velocity) < 0.00100000005f) {
        if (H(s32, 0x6e4) == next_index) {
            H(s32, 0x6f0) = 1;
            goto finish;
        }
    } else {
        H(float, 0x700) = func_00283248(workspace.state_71.particle_velocity.x, workspace.state_71.particle_velocity.y);
        distance = func_00282E20(&workspace.state_71.particle_velocity);
        H(float, 0x704) = func_00283248(distance, workspace.state_71.particle_velocity.z);
    }
    H(float, 0x1a0) = H(float, 0x700);
    func_L00_002B3EF8(0, 0.0179999992f, 0.200000003f, 0.107628651f);
    func_002AA2E8(&H(float, 0x6f4), 0.233333349f, 0.00249999994f);
    func_00282CF0(&H(Vec4, 0xf0), &workspace.state_71.particle_position, &H(Vec4, 0x6d0));
    func_00282CF0(&workspace.state_71.particle_velocity, &H(Vec4, 0x6d0), &workspace.state_71.reference_position);
    vertical_error = -func_00282DF0(&workspace.state_71.particle_velocity);
    func_002AA3A8(&vertical_error, &H(float, 0x708), 0.0f,
                 0.0500000007f, 0.300000012f, 0.166666672f);
    distance = func_00282DF0(&workspace.state_71.particle_velocity);
    if (distance < H(float, 0x708)) H(float, 0x708) = distance;
    if (H(float, 0x708) < distance)
        func_00282F20(&workspace.state_71.particle_velocity, &workspace.state_71.particle_velocity, H(float, 0x708));
    func_00282CC0(&H(Vec4, 0x80), &H(Vec4, 0x80), &workspace.state_71.particle_velocity);
    goto finish;
}



case 23: case 24:
    func_00282CF0(HP(0x190), HP(0x560), HP(0x550));
    H(float, 0x1A0) = func_00283248(H(float, 0x190), H(float, 0x194));
    func_L00_002B3EF8(0, 0.04f, 0.2f, 0.10471977f);
    if (H(u8, 0x22C3) != 2) func_002AA800(HP(0x94), 0, 0.0f, 0.078539826f);
    func_00282CF0(HP(0xF0), HP(0x550), HP(0x80));
    func_002AC9F8(HP(0xF0), 0.06666667f);
    func_002AA2E8(HP(0x580),H(float,0x88),0.050000004f);
    goto finish;


case 0x46: case 0x47:
    func_00282CF0(HP(0x190),HP(0x560),HP(0x550));
    H(float,0x1A0)=func_00283248(H(float,0x190),H(float,0x194));
    func_L00_002B3EF8(0,0.02f,0.2f,0.078539826f);
    func_00282CF0(HP(0xF0),HP(0x550),HP(0x80));func_002AC9F8(HP(0xF0),0.028333336f);
    func_002AA2E8(HP(0x580),H(float,0x88),0.050000004f);
    goto finish;


case 25: case 26:
{

    func_00282CF0(HP(0x190), HP(0x560), HP(0x550));
    H(float, 0x1A0) = func_00283248(H(float, 0x190), H(float, 0x194));
    func_L00_002B3EF8(0, 0.02f, 0.2f, 0.078539826f);
    func_00282CF0(&workspace.state_19.direction, HP(0x560), HP(0x550));
    func_00282C88(HP(0xF0));
    if (H(u32, 0x2294) == 25) func_00282DD8(&workspace.state_19.side, HP(0x2C0), &workspace.state_19.direction);
    else func_00282DD8(&workspace.state_19.side, &workspace.state_19.direction, HP(0x2C0));
    func_00282F20(&workspace.state_19.side, &workspace.state_19.side, 0.2f);
    func_00282CC0(&workspace.state_19.candidate, HP(0x80), &workspace.state_19.side);
    if (func_L00_002ACF88(HP(0x80), HP(0x90), 0) &&
        func_L00_002ACF88(&workspace.state_19.candidate, HP(0x90), &workspace.state_19.contact)) {
        func_00282CF0(HP(0xF0), &workspace.state_19.contact, HP(0x80));
        func_00282F20(HP(0xF0), HP(0xF0), D_L23_001ACE68[func_00283CF0(H(float, 0xC38))] * 0.5f);
    }
    goto finish;
}



case 0x76:
    H(float, 0x1a0) = H(float, 0x32c);
    H(float, 0x1b0) = 0.0916666687f;
    func_L00_002B6198(0.0069444445f);
    func_L00_002D34C0(&H(Vec4, 0xf0), &H(Vec4, 0x130), 0.00499999989f);
    goto finish;



case 6: case 44:
{
    if (H(u32, 0x2294) == 44) {

        float target = H(float, 0x31C) > 4.0f ? 0.43633235f : 0.0f;
        qcopy(&workspace.state_06.rotation, &H(Vec4, 0x90));
        func_002AA898(&workspace.state_06.rotation.y, target, HP(0xA4), 0.02f, 0.3f, 0.043633237f, 0);
        func_002AA898(&workspace.state_06.rotation.x, 0.0f, HP(0xA0), 0.02f, 0.3f, 0.043633237f, 0);
        func_L00_002AA0F0(H(float, 0xA0), H(float, 0xA4), 0);
        if (H(float, 0x31C) > 1.0f) H(int, 0x2298) = 1;
    }
    func_L00_002B3D10();
    if (!H(s16, 0x1E0)) func_L00_002B6BC8();
    func_L00_002B7B80();
    func_L00_002B54F8(0.7f, 0.0f);
    func_L00_002D34C0(HP(0xF0), HP(0xF0), H(float, 0xA80));
    if (func_L00_002D3B00(HP(0xF0)) < -0.833333373f) {
        
        { func_L00_002D3B58(&H(Vec4, 0xf0), &H(Vec4, 0xf0), -0.833333373f); goto finish; }
    }
    goto finish;
}


case 0x74:
{
    float speed;
    H(u8, 0x22bc) = 1;
    func_002AA2E8(&H(float, 0xa88), H(float, 0xa90), 0.00242406875f);
    func_002AA2E8(&H(float, 0xa8c), H(float, 0xa94), 0.00242406875f);
    func_L00_002AA0F0(H(float, 0xa88), H(float, 0xa8c), 0.0f);
    speed = func_00282E20(&H(Vec4, 0xf0));
    func_L00_002EE4D8(&H(Vec4, 0xf0), &H(Vec4, 0xf0), speed * 0.899999976f);
    func_L00_002D34C0(&H(Vec4, 0xf0), &H(Vec4, 0xf0), H(float, 0xa80));
    speed = func_L00_002D3B00(&H(Vec4, 0xf0));
    if (speed < -0.833333373f) {
        
        { func_L00_002D3B58(&H(Vec4, 0xf0), &H(Vec4, 0xf0), -0.833333373f); goto finish; }
    }
    goto finish;
}



case 0x82:
{
    s32 phase, color;
    u32 held;
    float elevation, factor, step;
    func_L00_002B9BB0(4, H(u8 *, 0x2290), 13);
    phase = func_L00_0031D620(720, 180, H(float, 0x5b0) * 0.0199999996f);
    color = func_L00_00325FC8(&H(float, 0x5a0), 0x60ffffff, 0x40ffc0a0,
                             (float)phase * 0.000290888245f);
    func_00290010(2, color, 0, 1.0f - H(float, 0x5b0) * 0.0199999996f);
    held = FLD(D_00138180, u32, 0x1A0) & 0x40;
    if (H(float, 0x5b0) == 0.0f) held = 0;
    if (held != 0) {
        func_002AA2E8(&H(float, 0x5b0), 0.0f, 0.100000001f);
        func_L00_002D38A0(&H(Vec4, 0xf0), &H(Vec4, 0xf0), 0.0250000004f);
    } else func_002AA2E8(&H(float, 0x5b0), 0.0f, 0.0199999996f);
    if ((FLD(D_00138180, u32, 0x1A4) & 0x40) != 0) func_002AA2E8(&H(float, 0x5b0), 0.0f, 0.5f);
    func_L00_002D34C0(&H(Vec4, 0xf0), &H(Vec4, 0xf0), 0.0075000003f);
    elevation = func_L00_002D3B00(&H(Vec4, 0xf0));
    if (0.100000009f < elevation)
        func_L00_002D3B58(&H(Vec4, 0xf0), &H(Vec4, 0xf0), 0.100000009f);
    elevation = func_L00_002D3B00(&H(Vec4, 0xf0));
    if (elevation < -0.200000018f)
        func_L00_002D3B58(&H(Vec4, 0xf0), &H(Vec4, 0xf0), -0.200000018f);
    elevation = func_L00_002D3B00(&H(Vec4, 0xf0));
    if (25.0f < H(float, 0x5b0) && H(short, 0x5be) < 90 && elevation < 0.0f && H(float, 0x31c) < 1.20000005f) {
        factor = (H(float, 0x31c) - 0.25f) * 1.0526315f;
        H(u16, 0x5be) = H(u16, 0x5be) + 1;
        if (factor < 0.0f) factor = 0.0f;
        func_L00_002D3B58(&H(Vec4, 0xf0), &H(Vec4, 0xf0), elevation * factor);
        if (H(float, 0x31c) < 0.25f)
            func_002AA3A8(&H(float, 0x88), &H(float, 0x5b4), H(float, 0x318) + 0.25f,
                         0.0270000007f, 0.300000012f, 0.0833333358f);
    } else if (0.0f < elevation) H(short, 0x5be) = 0;
    FLD(D_L23_001BA500, float, 0x3C8) = func_L00_002D3B00(&H(Vec4, 0xf0));
    func_L00_002B7B80();
    func_L00_002B39F0(H(float, 0x24b8) * 0.200000018f, 0);
    if (H(float, 0x24b8) < 0.200000003f) H(float, 0x1a0) = H(float, 0x98);
    func_L00_002B3EF8(0, 0.0270000007f, 0.300000012f, H(float, 0x24b8) * 0.087266475f);
    step = 0.00138888892f;
    if (H(float, 0x24b8) < 0.200000003f) step = 0.000555555569f;
    func_L00_002B6198(step);
    goto finish;
}



    case 8: {
        f32 k;
        if (func_L00_002ADEA0(3) == 2) {
            s32 idx = H(s32, 0x243C);
            if (idx != -1) {
                char *e = D_00188660 + idx * 0x70;
                if (*(Moby **)(e + 0x88) == H(Moby *, 0x2290) && *(u8 *)(e + 0x74)) func_002E59F8(idx);
            }
            H(s32, 0x243C) = -1;
            func_L00_002B9BB0(3, H(Moby *, 0x2290), 2);
        } else {
            s32 idx = H(s32, 0x2438);
            if (idx != -1) {
                char *e = D_00188660 + idx * 0x70;
                if (*(Moby **)(e + 0x88) == H(Moby *, 0x2290) && *(u8 *)(e + 0x74)) func_002E59F8(idx);
            }
            H(s32, 0x2438) = -1;
            func_L00_002B9BB0(4, H(Moby *, 0x2290), 0xD);
        }
        shared_limit = 0.050000004f;
        if (H(s32, 0x1338) == 3) shared_limit = 0.083333336f;
        k = 0.72f;
        if (H(u8, 0x24EF)) {
            shared_limit = 0.12833333f;
            k = 0.98640007f;
        }
        if (H(float, 0x24C8) != 0.0f) k = H(float, 0x24C8);
        {
            f32 v = func_L00_002D3B00(&H(Vec, 0xF0));
            func_L00_002B39F0(shared_limit, 0);
            func_L00_002B3EF8(0, 0.025f, 0.3f, 0.20943955f);
            func_L00_002B41B8(0.004166667f, 0.0019444445f);
            func_L00_002B4208(99999.0f);
            func_L00_002B7B80();
            func_L00_002D3960(&H(Vec, 0xF0), &H(Vec, 0xF0));
            func_002AA3A8(&v, &H(float, 0xA98), -shared_limit * k, 0.025f, 0.3f, 0.28333336f);
            func_L00_002D34C0(&H(Vec, 0xF0), &H(Vec, 0xF0), -v);
        }
        if (H(float, 0x88) < H(float, 0x490)) func_002AA2E8(&H(float, 0x490), H(float, 0x88), 0.06666667f);
        func_L00_002AC578();
        goto finish;
    }

case 7: case 9: case 10: case 11: case 12: case 13: case 14: case 15:
case 16: case 17: case 18: case 27: case 56: case 69: case 72:
case 91: case 102: case 110: case 129: case 137: case 146:
{
    float magnitude, saved_speed;
    int frame, mark;
    if (H(u32, 0x2294) == 27 && !H(s16, 0x24FC) && H(int, 0x1338) == 3 && func_L00_002B3998(10.0f))
        func_L00_002B9B88(4, 0);
    if (H(s16, 0x528) && H(u8, 0x1492)) H(float, 0x1B0) = H(float, 0x1B4);
    else {
        if (H(u8, 0x49C)) func_L00_002B39F0(0.09916667f, 0);
        func_L00_002B39F0(H(float, 0x4A4), 0);
    }
    if (H(u32, 0x2294) == 18) {
        if (H(int, 0x1B8) == 20) {
            func_L00_002AABE0(3, 16, 1);
            if (D_L23_001B2F30)
                func_002FD1B8(D_L23_001B2F30, D_L23_001B2F38, 0,
                              H(float, 0x80), H(float, 0x84), 0.4f, 0.35f);
        }
        if (H(float, 0xC38) >= 4.0f && H(float, 0xC38) <= 7.0f) func_L00_002AA938(7, 0, 0);
    }
    mark = H(s16, 0x4AC); frame = H(int, 0x1B8);
    if (frame == mark) qcopy(&H(Vec4, 0x460), &H(Vec4, 0x80));
    if (H(u8, 0x49C) || (frame < mark &&
        H(u32, 0x2294) != 11 && H(u32, 0x2294) != 16 && H(u32, 0x2294) != 12 &&
        H(u32, 0x2294) != 17 && H(u32, 0x2294) != 27 && H(u32, 0x2294) != 137 && H(u32, 0x2294) != 72)) {
        if (H(s16, 0x528)) {
            func_L00_002B9598();
            if (H(u32, 0x2294) == 10 && H(int, 0x1B8) < 10 && H(float, 0x178) < 0.116666675f) {
                H(float, 0xF0) += func_00283180(H(float, 0x98)) * 0.011666667f;
                H(float, 0xF4) += func_00283198(H(float, 0x98)) * 0.011666667f;
                qcopy(&H(Vec4, 0x140), &H(Vec4, 0xF0));
            }
        } else {
            func_L00_002B3EF8(0, 0.015f, 0.2f, 0.2501639f);
            saved_speed = H(float, 0x1B4);
            if (H(u8, 0x49C) > 1) H(float, 0x1B4) *= 0.4f;
            if (H(s16, 0x1454)) func_L00_002B4208(H(float, 0x1458));
            else func_L00_002B4208(99999.0f);
            H(float, 0x1B4) = saved_speed;
            if (H(u8, 0x49C) != 1) func_L00_002B41B8(H(float, 0x500), H(float, 0x504));
            if (H(u8, 0x49C)) {
                if (FLD(D_00138180, int, 0x1D4) && H(s16, 0x34A)) H(float, 0x1B4) = 0.0f;
                if (H(u8, 0x49C)) func_L00_002B94D8(H(float, 0x504));
            }
            func_L00_002B54F8(0.5f, 0.033333335f);
            if (H(u32, 0x2294) == 9 && H(int, 0x1B8) < H(s16, 0x4AC) + 4)
                func_L00_002D3798(HP(0xF0), HP(0xF0), H(int, 0x1B8) * 0.0044444446f);
            if (H(u32, 0x2294) == 10 && H(int, 0x1B8) < 34)
                func_L00_002D3798(HP(0xF0), HP(0xF0), H(int, 0x1B8) * 0.014722222f);
            if (H(int, 0x1B8) < 10 && H(float, 0x24B8) > 0.2f) {

                qcopy(&workspace.state_07.origin, &H(Vec4, 0x80));
                func_L00_002D38A0(&workspace.state_07.origin, &workspace.state_07.origin, 0.5f);
                func_L00_002D3798(&workspace.state_07.endpoint, &workspace.state_07.origin, 0.95f);
                if (func_002761F8(&workspace.state_07.origin, &workspace.state_07.endpoint, 4, H(void *, 0x2290), 0)) H(s16, 0x524) = 1;
            }
        }
    } else {
        func_L00_002B6BC8();
        if (H(u32, 0x2294) == 18) {
            magnitude = func_00282E20(HP(0xF0));
            if (magnitude > 0.06166667f) magnitude = 0.06166667f;
            func_00282F70(HP(0xF0), HP(0xF0), magnitude);
        }
    }
    if (H(float, 0x318) > H(float, 0x490)) {
        H(float, 0x490) += 0.10000001f;
        if (H(float, 0x490) > H(float, 0x318)) H(float, 0x490) = H(float, 0x318);
    }
    if (H(float, 0x490) > H(float, 0x88)) H(float, 0x490) = H(float, 0x88);
    if (H(int, 0x1B8) > H(s16, 0x4AC) && func_L00_002D3B00(HP(0xF0)) < 0.001f &&
        (!H(u8, 0x49D) || H(int, 0x1B8) > H(int, 0x434)) &&
        (H(u32, 0x2294) != 14 || H(int, 0x1B8) > 17)) {
        H(u8, 0x49E) = 1;
        if (H(float, 0x458) != 0.0f) H(float, 0x520) = H(float, 0x458);
    }
    if (!H(u8, 0x22B4)) func_L00_002B7B80();
    if (H(u8, 0x22B4) == 1) func_L00_002B8930();
    if (H(u32, 0x2294) == 16 || H(u32, 0x2294) == 13)
        func_L00_00322BE0(HP(0x18E0), H(int, 0x1B8) < 13 ? 0 : 2);
    if (H(u32, 0x2294) == 129)
        func_L00_00322BE0(HP(0x18E0), H(int, 0x1B8) < 14 ? 0 : 2);
    if (H(u32, 0x2294) == 16 && H(int, 0x1B8) > 8 && H(float, 0xC38) < 28.0f) {

        int count, i;
        func_L00_002D36E0(&workspace.state_07.origin, 1, 0.8f, 0.0f, 0.3f);
        count = func_00277F48(0.9f, &workspace.state_07.origin, 0, H(void *, 0x2290), 0);
        if (count) {
            func_00282D30(&workspace.state_07.endpoint, HP(0x110), 7.0f);
            for (i = 0; i < count; i++) {
                if (func_002ABB78(D_L23_001C4B00[i]))
                    func_002A8F70(D_L23_001C4B00[i], H(void *, 0x2290), 0x10000, HP(0x80), &workspace.state_07.endpoint, 1.0f);
            }
        }
    }
    if (H(u32, 0x2294) == 56 && !H(u8, 0x49E) && H(float, 0xF8) > 0.025000002f)
        func_L00_002AAE00();
    func_L00_002B6560();
    func_L00_002AC578();
    goto finish;
}


case 22:
{
    float speed = func_L00_002D3A58(HP(0xF0));
    if (!H(s16, 0x34E) && H(int, 0x1B8) >= 11) speed -= 0.0027777778f;
    else speed -= 0.0011111111f;
    if (speed < 0.0f) speed = 0.0f;
    if (H(u8, 0x1497)) func_L00_002B9F00(3.7f, 0.0f, 0.35f);
    func_L00_002D3BD8(HP(0xF0), HP(0xF0), speed);
    
    { func_L00_002D34C0(&H(Vec4, 0xf0), &H(Vec4, 0xf0), 0.004f); goto finish; }
}


    case 0x8C:
        qzero(D_00189F10);
        H(float, 0xF8) = -0.38333336f;
        goto finish;

case 0x62:
{

    float distance;
    u8 mode;
    float weight;
    func_00282CF0(&workspace.state_62.difference, &H(Vec4, 0x18a0), &H(Vec4, 0x80));
    H(float, 0x1a0) = func_00283248(workspace.state_62.difference.x, workspace.state_62.difference.y);
    distance = func_00282E20(&workspace.state_62.difference);
    if (0.200000003f < distance) {
        hero = D_00189E20;
        FLD(hero, float, 0x24b8) = 1.0f;
        H(float, 0x1a0) = func_00283248(workspace.state_62.difference.x, workspace.state_62.difference.y);
        H(float, 0x1b0) = distance; /* store in ordinary branch delay slot */
        if (distance < D_L23_001A7DAC[0][2]) H(float, 0x1b0) = D_L23_001A7DAC[0][1] * 0.0166666675f;
        else H(float, 0x1b0) = D_L23_001A7DAC[1][1] * 0.0166666675f;
        if (H(u8, 0x22b4) == 1) H(float, 0x1b0) = 0.0150000006f;
    } else {
        H(float, 0x24b8) = 1.0f;
        H(float, 0x1a0) = H(float, 0x18ac);
        H(float, 0x1b0) = 0.0f;
    }
    weight = 1.0f;
    mode = H(u8, 0x22b4);
    if (mode == 3) func_L00_002B3EF8(0, 0.0299999993f, 0.300000012f, 0.0930842459f);
    else if (mode == 1) func_L00_002B3EF8(0, 0.0299999993f, 0.300000012f, 0.130899712f);
    else if (mode == 0) func_L00_002B3EF8(0, 0.0299999993f, 0.300000012f, 0.130899712f);
    else goto turn_done;
    if (H(u8, 0x22b4) == 0) func_L00_002B7B80();
turn_done:
    func_L00_002B41B8(weight * 0.00499999989f, 0.00555555569f);
    func_L00_002B4208(99999.0f);
    if (H(u8, 0x22b4) == 0) func_L22_002B8E10(1);
    if (H(s16, 0x34E)) { func_L00_002D34C0(&H(Vec4, 0xf0), &H(Vec4, 0x110), 0.0069444445f); func_L00_002B4308(); }
    else func_L00_002D34C0(&H(Vec4, 0xf0), &H(Vec4, 0xf0), 0.0150000006f);
    {
        s32 found, k;
        u8 *m;
        qcopy(&workspace.state_07.endpoint, &H(Vec4, 0xE0));
        found = func_00277F48(H(float, 0x264) + 0.2f, &workspace.state_07.endpoint, 0, H(void *, 0x2290), 0);
        for (k = 0; k < found; k++) {
            m = (u8 *)D_L23_001C4B00[k];
            if (m) {
                switch (*(s16 *)(m + 0xAA)) {
                case 0xCB:
                    func_002A8F70(m, H(void *, 0x2290), 0x10000, HP(0xE0), D_US2_001A8F20, 100.0f);
                    break;
                case 0x1366:
                    func_L02_00392C70();
                    break;
                case 0x1367:
                    func_L02_003948D0();
                    break;
                }
            }
        }
    }
    goto finish;
}



case 0x63:
{

    func_00282CF0(&workspace.state_63.difference, &H(Vec4, 0x18a0), &H(Vec4, 0x80));
    if (func_00282DB0(&workspace.state_63.difference, &H(Vec4, 0x160)) < 0.0f)
        func_00282C88(&H(Vec4, 0x160));
    func_00282C88(&H(Vec4, 0xf0));
    func_L00_002B94D8(0.0075000003f);
    func_L22_002B8E10(0);
    if (H(s16, 0x34E)) {
        
        
        { func_L00_002D34C0(&H(Vec4, 0xf0), &H(Vec4, 0x110), 0.0069444445f); func_L00_002B4308(); }
    } else func_L00_002D34C0(&H(Vec4, 0xf0), &H(Vec4, 0xf0), 0.0150000006f);
    goto finish;
}



case 0x3C: case 100:
    func_00282C88(HP(0xF0));goto finish;


case 0x65:
    func_00282C88(&H(Vec4, 0xf0));
    if ((float)H(s32, 0x18c0) * 0.5f < H(float, 0x334) - H(float, 0x88))
        H(float, 0xf8) = -0.00416666688f;
    else H(float, 0xf8) = -0.0166666675f;
    goto finish;



case 0x79:
    func_L00_002BA220();
    /* fall through */


case 0x78:
    func_00282C88(&H(Vec4, 0xf0));
    H(float, 0xf8) = -0.0166666675f;
    goto finish;



case 0x7a:
    func_00282C88(&H(Vec4, 0xf0));
    H(float, 0xf8) = -0.00583333336f;
    goto finish;



case 0x3F: case 0x43:
    func_L00_002B9F00(3.7f,0.0f,0.35f);func_L00_002B39F0(1.0f, 0);H(float,0x1B0)=0.0f;
    func_L00_002B41B8(0.0f,0.0035f);func_00282C88(HP(0xF0));func_L22_002B8E10(0);
    if (H(s16, 0x34E)) {
        { func_L00_002D34C0(&H(Vec4, 0xf0), HP(0x130), 0.0069444445f); func_L00_002B4308(); }
    } else func_L00_002D34C0(&H(Vec4, 0xf0), &H(Vec4, 0xf0), 0.0150000006f);
    goto finish;


    case 0x4D: {
        char *t = (char *)&D_L23_00261E90[H(s16, 0xBFC)];
        H(float, 0x1B0) = 0.0f;
        if ((FLD(t, s32, 0x04) == 0 || FLD(t, s32, 0x04) == 1) && H(float, 0xC38) < 5.5f) H(float, 0x1B0) = 0.058333337f;
        if (H(s32, 0xC2C) == 0 && (f32)FLD(t, s32, 0x1C) <= H(float, 0xC38) && H(float, 0xC38) <= (f32)FLD(t, s32, 0x20)) {
            s32 side = 2;
            if (FLD(t, s32, 0x04) == 1) side = 0;
            func_0029FCC0(H(Moby *, 0x2290), side, &workspace.mine.s10);
            func_0029FCC0(H(Moby *, 0x2290), side | 1, &workspace.mine.s20);
            func_00282CC0(&workspace.mine.s00, &workspace.mine.s10, &workspace.mine.s20);
            func_00282D30(&workspace.mine.s00, &workspace.mine.s00, 0.5f);
            func_002A8C28(H(Moby *, 0x2290), &workspace.mine.s00, 0x10000, 0.25f, 1.0f, 1.0f, 0, 1, 0);
        }
        func_002AA2E8(&H(float, 0xC20), 1.0f, 0.2f);
        if (H(s32, 0xBE8) || H(Moby *, 0xBE4)) {
            H(float, 0x1A0) = H(float, 0xBEC);
            func_L00_002B3EF8(0, 0.05f, 0.2f, 0.2821616f);
        } else {
            func_L00_002B75A0(5.0f, 0.78539824f, 0.78539824f);
        }
        func_L00_002B41B8(0.010277778f, 0.007777778f);
        if (H(s32, 0xBE8)) {
            if (H(u8, 0x22C3) == 2) func_L00_002B42D8(&H(Vec, 0xBC0));
            else func_L00_002B4208(H(float, 0xBEC));
        } else {
            func_L00_002B4208(99999.0f);
        }
        if (H(s16, 0x34E)) {
            H(float, 0xF8) = H(float, 0x118) - 0.0069444445f;
            func_L00_002B4308();
        } else {
            H(float, 0xF8) -= 0.015000001f;
        }
        func_L00_002B9F00(0.7f, 0.0f, 0.3f);
        goto finish;
    }

case 0x4B:
    func_L00_002B39F0(0.033333335f, 0);func_L00_002B3EF8(0,0.04f,0.2f,0.14544412f);
    func_L00_002B41B8(0.004166667f,0.0019444445f);func_L00_002B4208(99999.0f);
    func_L00_002D3960(HP(0xF0),HP(0xF0));{ func_L00_002D34C0(&H(Vec4, 0xf0), &H(Vec4, 0xf0), 0.024000002f); goto finish; }


case 0x4E:
    H(float,0x1A0)=H(float,0x32C);H(float,0x1B0)=0.09166667f;
    func_L00_002B6198(0.0069444445f);
    { func_L00_002D34C0(&H(Vec4, 0xf0), HP(0x130), 0.005f); goto finish; }




case 0x41:
    func_L00_002B39F0(0.050000004f, 0);
    if (!H(s16,0x1E0)) func_L00_002B6BC8();
    func_L00_002D34C0(HP(0xF0),HP(0xF0),0.0033333334f);
    if (H(float,0xF8)< -0.16666667f) H(float,0xF8)=-0.16666667f;
    goto finish;


case 0x44:
    if (H(float,0xF8)>0.0f) func_L00_002AA0F0(0.0f,0.20943955f,0.0f);
    { func_L00_002D34C0(&H(Vec4, 0xf0), &H(Vec4, 0xf0), 0.0055555557f); goto finish; }


case 0x40: case 0x4C:
{
    float acceleration,maximum,turn;
    func_L00_002B39F0(0.050000004f, 0);
    maximum=0.16580631f;acceleration=0.033f;
    if (H(u8,0x40F)) {maximum=0.19489513f;acceleration=0.037f;}
    func_L00_002B3EF8(0,acceleration,0.15f,maximum);func_L00_002B41B8(0.005f,0.0055555557f);
    if (H(float,0x174)<0.011666667f) {
        H(u8,0x40C)=1;
        if (func_00282C48(H(float,0x1A8))>1.7453294f && H(float,0x24B8)>0.8f) H(u8,0x40F)=1;
    }
    {
        float firstAngle=func_L00_0032F038(0),secondAngle=func_L00_0032F038(2);
        if (func_00283C80(firstAngle,secondAngle)>2.617994f &&
            func_00282C48(H(float,0x1A8))>1.2217306f && H(float,0x24B8)>0.8f) {
            H(u8,0x40F)=1;H(u8,0x40C)=1;
        }
    }
    if (func_00282C48(H(float,0x1A8))<0.087266475f) H(u8,0x40C)=0;
    if (H(u8,0x40F)) {
        if (func_00282C48(H(float,0x1A8))<0.06981318f) H(u8,0x40F)=0;
        if (H(u8,0x40F)) {
            turn=0.050000004f-func_00282C48(H(float,0x1A8))*0.02122066f;
            if (turn<0.0f) turn=0.0f;
            if (turn<H(float,0x1B0)) H(float,0x1B0)=turn;
        }
    }
    if (H(u8,0x40C)) func_L00_002B4208(H(float,0x1A0));
    else func_L00_002B4208(99999.0f);
    func_L22_002B8E10(1);
    if (H(s16, 0x34E)) { func_L00_002D34C0(&H(Vec4, 0xf0), &H(Vec4, 0x130), 0.0069444445f); func_L00_002B4308(); }
    else func_L00_002D34C0(&H(Vec4, 0xf0), &H(Vec4, 0xf0), 0.0150000006f);
    goto finish;
}


case 0x42:
{
    float speed=func_00282E20(HP(0xF0))*(H(s16,0x34E)?0.99f:0.92f);
    func_L00_002EE4D8(HP(0xF0),HP(0xF0),speed);
    H(float,0xF8)=0.0f;
    if (H(s16,0x34E)) { func_L00_002D34C0(HP(0xF0),HP(0x120),0.0061111115f); goto finish; }
    { func_L00_002D34C0(&H(Vec4, 0xf0), &H(Vec4, 0xf0), 0.004f); goto finish; }
}


case 0x49: case 0x4A:
{

    H(float,0xC20)=1.3f;
    func_00282CF0(HP(0x190),HP(0x560),HP(0x550));
    H(float,0x1A0)=func_00283248(H(float,0x190),H(float,0x194));
    func_L00_002B3EF8(0,0.02f,0.2f,0.078539826f);
    func_00282CF0(&workspace.state_49.line,HP(0x560),HP(0x550));func_00282C88(HP(0xF0));
    if (H(u32,0x2294)==0x49) func_00282DD8(&workspace.state_49.side,HP(0x2C0),&workspace.state_49.line);
    else func_00282DD8(&workspace.state_49.side,&workspace.state_49.line,HP(0x2C0));
    func_00282F20(&workspace.state_49.side,&workspace.state_49.side,0.2f);func_00282CC0(&workspace.state_49.candidate,HP(0x80),&workspace.state_49.side);
    if (func_L00_002ACF88(HP(0x80),HP(0x90),0) && func_L00_002ACF88(&workspace.state_49.candidate,HP(0x90),&workspace.state_49.hitPosition)) {
        func_00282CF0(HP(0xF0),&workspace.state_49.hitPosition,HP(0x80));
        func_00282F20(HP(0xF0), HP(0xF0), D_L23_00291A70[func_00283CF0(H(float,0xC38))] * 0.5f); goto finish;
    }
    goto finish;
}


case 0x56:
case 0x5f:
    func_L00_002B9F00(3.70000005f, 0.0f, 0.349999994f);
    func_L00_002B39F0(1.0f, 0);
    H(float, 0x1b0) = 0.0f;
    func_L00_002B41B8(0.0f, 0.00491666701f);
    func_00282C88(&H(Vec4, 0xf0));
    func_L00_002B94D8(0.00491666701f);
    func_L22_002B8E10(0);
    if (H(s16, 0x34E)) {
        
        
        { func_L00_002D34C0(&H(Vec4, 0xf0), &H(Vec4, 0x130), 0.0069444445f); func_L00_002B4308(); }
    } else func_L00_002D34C0(&H(Vec4, 0xf0), &H(Vec4, 0xf0), 0.0150000006f);
    goto finish;



case 0x5d:
{


    s32 mode;
    func_L00_002B39F0(1.0f, 0);
    func_L00_002B3EF8(0, 0.0199999996f, 0.200000003f, 0.0319977067f);
    H(float, 0x1b0) = 0.0f;
    func_00282C88(&H(Vec4, 0xf0));
    func_L00_002B94D8(0.00491666701f);
    if (H(s32, 0xc2c) == 0) {
        func_L00_002D36E0(&workspace.state_5d.local_offset, 0, 2.4f, 0.0f, 0.0f);
        func_002A8C00(&workspace.state_5d.probe, H(u8 *, 0x2290), 0xb0000, 50.0f, &workspace.state_5d.local_offset);
        workspace.state_5d.probe.vector.w = 5627.9248f; /* exact bits 0x45afdf66 */
        workspace.state_5d.probe.type = 7;
        workspace.state_5d.probe.kind = 1;
        workspace.state_5d.probe.id = *(u16 *)(H(u8 *, 0x2290) + 0xaa);
        switch (H(short, 0xbfc)) {
        case 0:
            if (7.0f < H(float, 0xc38) && H(float, 0xc38) < 14.0f) {
                func_0029FCC0(H(u8 *, 0x2290), 3, &workspace.state_5d.effect_position);
                func_00277F48(2.70000005f, &workspace.state_5d.effect_position, 0x10, H(u8 *, 0x2290), &workspace.state_5d.probe);
            }
            break;
        case 1:
            if (7.0f < H(float, 0xc38) && H(float, 0xc38) < 14.0f) {
                func_0029FCC0(H(u8 *, 0x2290), 4, &workspace.state_5d.effect_position);
                func_00277F48(2.70000005f, &workspace.state_5d.effect_position, 0x10, H(u8 *, 0x2290), &workspace.state_5d.probe);
            }
            break;
        case 2:
            if (14.0f < H(float, 0xc38) && H(float, 0xc38) < 21.0f) {
                func_0029FCC0(H(u8 *, 0x2290), 3, &workspace.state_5d.effect_position);
                func_0029FCC0(H(u8 *, 0x2290), 4, &workspace.state_5d.midpoint);
                func_00282CC0(&workspace.state_5d.midpoint, &workspace.state_5d.effect_position, &workspace.state_5d.midpoint);
                func_00282D30(&workspace.state_5d.midpoint, &workspace.state_5d.midpoint, 0.5f);
                func_00277F48(2.70000005f, &workspace.state_5d.midpoint, 0x10, H(u8 *, 0x2290), &workspace.state_5d.probe);
            }
            break;
        }
    }
    switch (H(short, 0xbfc)) {
    case 0: case 1:
        if (H(s32, 0xc2c) == 0 && 7.0f <= H(float, 0xc38) && H(float, 0xc38) < 15.6999998f)
            H(float, 0x1b0) = 0.400000036f;
        func_L00_002B41B8(0.0500000007f, 0.0388888903f);
        func_L00_002B4208(99999.0f);
        break;
    case 2:
        if (H(s32, 0xc2c) == 0 && 11.0f <= H(float, 0xc38) && H(float, 0xc38) < 20.0f)
            H(float, 0x1b0) = 0.5f;
        func_L00_002B41B8(0.0416666679f, 0.0333333351f);
        func_L00_002B4208(99999.0f);
        break;
    }
    func_L22_002B8E10(1);
    if (H(s16, 0x34E)) {
        
        
        { func_L00_002D34C0(&H(Vec4, 0xf0), &H(Vec4, 0x130), 0.0069444445f); }
    } else func_L00_002D34C0(&H(Vec4, 0xf0), &H(Vec4, 0xf0), 0.0150000006f);
    goto finish;
}



case 0x5e:
{

    H(float, 0x1b0) = 0.0f;
    func_L00_002B41B8(0.0f, 0.00491666701f);
    func_00282C88(&H(Vec4, 0xf0));
    func_L00_002B94D8(0.00491666701f);
    if (H(s32, 0xc2c) == 0) {
        /* Ordered FP comparisons matter: retain the retail NaN fallthrough. */
        if (22.0f < H(float, 0xc38) && H(float, 0xc38) < 55.0f) {
            H(float, 0xc20) = 1.0f;
        } else if (H(s32, 0xc2c) == 0 && H(float, 0xc38) <= 22.0f) {
            func_0029FCC0(H(u8 *, 0x2290), 4, &workspace.state_5e.effect_position);
            func_L23_004234C0(entry_object, &workspace.state_5e.effect_position, 1);
            H(float, 0xc20) = 1.0f;
        }
    }
    if (H(s16, 0x34E)) {
        func_L00_002D34C0(&H(Vec4, 0xf0), &H(Vec4, 0x130), 0.0069444445f); func_L00_002B4308();
    } else func_L00_002D34C0(&H(Vec4, 0xf0), &H(Vec4, 0xf0), 0.0150000006f);
    goto finish;
}



case 0x58:
{

    func_L00_002B39F0(0.216666684f, 0);
    func_L00_002D36E0(&workspace.state_58.effect_position, 1, 0.0f, 0.0f, -1.0f);
    func_002A8C28(H(u8 *, 0x2290), &workspace.state_58.effect_position, 0x30000, 3.5f, 2.0f, 1.0f, 0, 1, 0);
    if (H(short, 0x1e0) == 0) func_L00_002B6BC8();
    func_L00_002D34C0(&H(Vec4, 0xf0), &H(Vec4, 0xf0), 0.0102777779f);
    if (func_L00_002D3B00(&H(Vec4, 0xf0)) < -0.950000048f) {
        
        { func_L00_002D3B58(&H(Vec4, 0xf0), &H(Vec4, 0xf0), -0.950000048f); goto finish; }
    }
    goto finish;
}



case 0x57:
{

    float first_angle, second_angle, turn;
    s32 i;
    func_00283C80(H(float, 0x98), H(float, 0x1a0));
    for (i = 0; i < 3; ++i) {
        float angle = func_00283B98(-0.785398245f, (float)i * 0.785398245f);
        func_L00_002D3638(&workspace.state_57.effect_position, 1, 1.79999995f, angle, 1.39999998f);
        func_002A8C28(H(u8 *, 0x2290), &workspace.state_57.effect_position, 0x04000000, 2.70000005f, 2.0f, 1.0f, 0, 1, 0);
    }
    shared_limit = 0.078539826f;
    func_L00_002B39F0(0.216666684f, 0);
    if (H(s32, 0x1b8) < 3) {
        H(u8, 0x40c) = 1;
        if (1.74532938f < func_00282C48(H(float, 0x1a8)) &&
            0.800000012f < H(float, 0x24b8)) H(u8, 0x40f) = 1;
    }
    first_angle = func_L00_0032F038(0);
    second_angle = func_L00_0032F038(2);
    if (2.61799407f < func_00283C80(first_angle, second_angle) &&
        1.22173059f < func_00282C48(H(float, 0x1a8)) &&
        0.800000012f < H(float, 0x24b8)) {
        H(u8, 0x40f) = 1;
        H(u8, 0x40c) = 1;
    }
    if (func_00282C48(H(float, 0x1a8)) < 0.087266475f) H(u8, 0x40c) = 0;
    do {
    if (H(u8, 0x40f) != 0) {
        if (func_00282C48(H(float, 0x1a8)) < 0.069813177f) H(u8, 0x40f) = 0;
        if (H(u8, 0x40f) != 0) shared_limit = 0.107628651f;
    }
    shared_rate = 0.300000012f;
    } while (0);
    if (H(short, 0x1454) != 0) {
        func_L00_002B35A0();
    } else {
        H(float, 0x1458) = H(float, 0x98);
        qcopy(&H(Vec4, 0x1440), &H(Vec4, 0x0));
        func_L00_002B3EF8(0, 0.0274999999f, shared_rate, shared_limit);
    }
    func_L00_002B41B8(0.0102777779f, 0.00555555569f);
    if (H(short, 0x1454) == 0) {
        turn = H(float, 0x1a4) * 17.0f;
        if (1.89999998f < turn) turn = 1.89999998f;
        else if (turn < -1.89999998f) turn = -1.89999998f;
        FLD(D_L23_00260310, float, 0x1494) = 0.0240000002f;
        FLD(D_L23_00260310, float, 0x1334) = 0.0270000007f;
        FLD(D_L23_00260310, float, 0x13E4) = 0.0199999996f;
        FLD(D_L23_00260310, float, 0x1498) = 0.300000012f;
        FLD(D_L23_00260310, float, 0x1338) = 0.300000012f;
        FLD(D_L23_00260310, float, 0x13E8) = 0.300000012f;
        FLD(D_L23_00260310, float, 0x12F0) = -turn * 0.200000003f;
        FLD(D_L23_00260310, float, 0x12F8) = turn * 0.370000005f;
        FLD(D_L23_00260310, float, 0x13A8) = turn * 0.569999993f;
    }
    if (H(u8, 0x40c) || H(short, 0x1454)) {
        if (H(short, 0x1454)) func_L00_002B42D8(&H(Vec4, 0x1440));
        else func_L00_002B42D8(&H(Vec4, 0x190));
    } else func_L00_002B4208(99999.0f);
    func_L22_002B8E10(1);
    if (H(s16, 0x34E)) {
        func_L00_002D34C0(&H(Vec4, 0xf0), &H(Vec4, 0x130), 0.0069444445f); func_L00_002B4308();
    } else func_L00_002D34C0(&H(Vec4, 0xf0), &H(Vec4, 0xf0), 0.0150000006f);
    goto finish;
}



case 0x59:
case 0x5a:
{

    float length, elevation;
    func_00282F20(&workspace.state_59.effect_position, &H(Vec4, 0xf0), 3.5f);
    func_002AFD88(H(u8 *, 0x2290), &workspace.state_59.effect_position, 0.0f, 0.0f, 2.0f);
    func_00282CC0(&workspace.state_59.effect_position, &workspace.state_59.effect_position, &H(Vec4, 0x80));
    func_002A8C28(H(u8 *, 0x2290), &workspace.state_59.effect_position, 0xb0000, 5.0f, 100.0f, 1.0f, 0, 1, 0);
    length = func_L00_002D3A58(&H(Vec4, 0xf0));
    if (0.0833333358f < length) {
        func_00282D30(&H(Vec4, 0x190), &H(Vec4, 0xf0), -1.0f);
        func_L00_002B3EF8(0, 0.0500000007f, 0.200000003f, 12.833334f);
    }
    if (H(short, 0x34e)) func_002AA2E8(&length, 0.0f, 0.0194444451f);
    else length = length * 0.899999976f;
    elevation = func_L00_002D3B00(&H(Vec4, 0xf0));
    func_L00_002D3BD8(&H(Vec4, 0xf0), &H(Vec4, 0xf0), length);
    elevation -= 0.0152777778f;
    if (0.183333337f < elevation) elevation = 0.183333337f;
    func_L00_002D3B58(&H(Vec4, 0xf0), &H(Vec4, 0xf0), elevation); goto finish;
}



case 0x37:
    if (H(u8*,0x2290)[0x43]==0x44) func_L00_002B3EF8(0,0.137f,0.25f,0.20362177f);
    else func_L00_002B3EF8(0,1.0f,0.1f,0.40724355f);
    goto finish;


case 0x60:
case 0x61:
    func_00282C88(&H(Vec4, 0xf0));
    goto finish;

    default: goto finish;
    }


finish:
    if (entry_substate != H(int, 0x2298)) H(int, 0x1C0) = 0;
    if (entry_animation != entry_object[0x43]) H(int, 0x1C4) = 0;
}
