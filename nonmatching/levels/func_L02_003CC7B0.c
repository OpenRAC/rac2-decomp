/* sol-high; USA v1.01: 1304/1304 bytes, 0/2 places.
 * Profile: -O2 -G8 -ffunction-sections -fno-cse-follow-jumps.
 * The typed private data and hero layouts recover the retail 0x60 frame.
 * Separate constructor calls, followed by one child-pointer read used for both
 * the null check and attach call, recover the creation branch. The child field
 * is declared volatile: retail rereads it after publication, calls and the
 * halfword stores through the child pointer; no access casts are used.
 * Remaining: initialization FP store ordering/registers, the post-query
 * integer return allocation, global-mask argument scheduling and final CSE.
 * Corrected the old behavior error: the global mask gates BOTH state tests.
 * Disabling both CSE path controls ties the single-control profile. Grouped
 * compiler qcopy pairs tie the relevant differences; disabling sched1 is worse.
 * Next: recover the original initialization subobject/assignment structure.
 * All required declarations follow below.
 *
 * closer D, 1 November 2026: 28 words at -G0, but the volatile child field is refused, and the rereads depend on it.
 */
#include "common.h"
#define W(p,o) (*(int *)((char *)(p)+(o)))
#define H(p,o) (*(short *)((char *)(p)+(o)))
#define U(p,o) (*(unsigned short *)((char *)(p)+(o)))
#define F(p,o) (*(float *)((char *)(p)+(o)))
#define P(p,o) (*(char **)((char *)(p)+(o)))
struct CC7Hero {
    char pad0[0xd0]; float direction[4];
    char pade0[0x18c]; unsigned char *obj26c; unsigned char *obj270;
    char pad274[0xc8]; int portal; int active;
    char pad344[0x1f4c]; int target;
};
extern struct CC7Hero D_00189E20;
extern char D_L02_001BA500[];
extern int D_L02_001B30C8 __attribute__((nosda));
extern int ref_L02_003CC7B0_00 __attribute__((sda));
extern int ref_L02_003CC7B0_01(float);
extern char *ref_L02_003CC7B0_02(int);
extern void ref_L02_003CC7B0_03(void *,void *);
extern float ref_L02_003CC7B0_04(void);
extern int ref_L02_003CC7B0_05(int);
extern void ref_L02_003CC7B0_06(void *,int,int);
extern float ref_L02_003CC7B0_07(void *,void *);
extern void ref_L02_003CC7B0_08(void *);
extern void ref_L02_003CC7B0_09(void *,int,void *);
extern void ref_L02_003CC7B0_10(void *,void *);
extern char *ref_L02_003CC7B0_11(void *,int,int);
extern int ref_L02_003CC7B0_12(void *,void *,int);
extern void ref_L02_003CC7B0_13(void *);
extern void ref_L02_003CC7B0_14(void *);
extern int ref_L02_003CC7B0_15(int,int);
extern void ref_L02_003CC7B0_16(void *,int,int,int,float,float);
extern float ref_L02_003CC7B0_17(float,float);
extern float ref_L02_003CC7B0_18(float,float);
struct CC7Data {
    char pad0[0x28];
    unsigned char kind;
    unsigned char init;
    char pad2a[0x4];
    unsigned char mode;
    char pad2f[0x1];
    float f30;
    char pad34[0x14];
    unsigned char b48;
    char pad49[0x1];
    unsigned char b4a;
    char pad4b[0x15];
    unsigned char b60;
    char pad61[0x4];
    unsigned char b65;
    char pad66[0x3];
    unsigned char b69;
    char pad6a[0x16];
    float f80;
    float f84;
    char pad88[0x4];
    float f8c;
    float f90;
    char pad94[0x4];
    int w98;
    char pad9c[0x30];
    int wcc;
    char padd0[0x30];
    float f100;
    float f104;
    float f108;
    float f10c;
    float f110;
    char pad114[0x1c];
    float f130;
    float f134;
    char pad138[0x4];
    int w13c;
    char pad140[0xc];
    char * p14c;
    char pad150[0xb0];
    int w200;
    int w204;
    char pad208[0x108];
    short h310;
    short h312;
    int w314;
    int w318;
    int w31c;
    int w320;
    int w324;
    int w328;
    char pad32c[0x4];
    int w330;
    char pad334[0x8];
    int w33c;
    char pad340[0x30];
    char * volatile other;
    char pad374[0x6];
    short h37a;
    char pad37c[0xa];
    short h386;
    float f388;
    float f38c;
};
int func_L02_003CC7B0(unsigned char *obj) {
    struct CC7Data *data=(struct CC7Data *)P(obj,0x68);
    unsigned char *hit;
    char *child;
    float mat[16] __attribute__((aligned(16)));
    int value, allowed;
    if (!(unsigned char)obj[0x20]) {
        data->b48=ref_L02_003CC7B0_01(15.0f);
        data->b4a=ref_L02_003CC7B0_01(19.2f);
        data->init=1;
        if (data->w318==-1 || data->w31c==-1) return 1;
        {
            qcopy((char *)data+0x340,obj+0x10); qcopy((char *)data+0x350,obj+0x10);
            data->b60=16; data->f80=0.5f; data->b69=0xfe;
            data->f8c=0.4f; data->f84=0.5f; data->w98=3;
            data->f90=F(obj,0x18)-6.0f; data->wcc=data->w330;
            data->b65=19; data->kind=3; data->f30=1.25f;
            if (!data->h310) data->other=ref_L02_003CC7B0_02(0xa20);
            else data->other=ref_L02_003CC7B0_02(0xa21);
            child=data->other;
            if (!child) return 1;
            ref_L02_003CC7B0_03(child,obj);
            U(data->other,0x32)=U(obj,0x32);
            U(data->other,0x34)|=0x100;
            data->f38c=ref_L02_003CC7B0_04();
            data->f388=ref_L02_003CC7B0_04();
            data->f134=0.05f; data->f104=0.2f; data->f100=0.825f; data->f108=0.4f;
            data->f110=1.5707964897155762f; data->f130=0.523598849773407f;
            data->w13c=data->w318; data->p14c=(char *)data+0x210;
            data->mode=1; data->f10c=0.4f;
            if (ref_L02_003CC7B0_05(2)) U(obj,0x34)|=0x8000; else U(obj,0x34)&=0x7fff;
            if (data->h312) {
                ref_L02_003CC7B0_06(obj,23,4);
                W(obj,0x98)=0; U(obj,0x34)=(U(obj,0x34)|0x41)&0xefff;
                U(data->other,0x34)|=0x41;
                U(data->other,0x34)&=0xefff; W(data->other,0x98)=0;
            } else if (data->w320!=-1 && data->w324!=-1) ref_L02_003CC7B0_06(obj,17,4);
            else if (data->w328!=-1) ref_L02_003CC7B0_06(obj,19,4);
            else ref_L02_003CC7B0_06(obj,1,0);
        }
    }
    if (obj[0x31] && ref_L02_003CC7B0_07(obj+0x10,D_L02_001BA500)<24.0f) {
        ref_L02_003CC7B0_08(obj); obj[0x6f]=22;
    }
    ref_L02_003CC7B0_09(obj,0,mat);
    ref_L02_003CC7B0_10(data->other+0xc0,mat);
    qcopy(data->other+0x10,mat+12);
    hit=ref_L02_003CC7B0_11(obj,0x10000,0);
    if (hit && P(hit,0x20) && H(P(hit,0x20),0xaa)==0xb5a) obj[0xa8]=0xff;
    if (ref_L02_003CC7B0_12(obj,(char *)data+0x50,0)) ref_L02_003CC7B0_13(obj);
    if ((unsigned char)data->mode==2) ref_L02_003CC7B0_14(obj);
    if (data->w314!=-1 && (ref_L02_003CC7B0_00&15)==(((int)obj>>8)&15)) {
        value=ref_L02_003CC7B0_15(data->w314,-1);
        if (value<data->h37a) data->h386=300;
        data->h37a=value;
    }
    if (((unsigned char)obj[0x95]==3 || (unsigned char)obj[0x20]==23) && !(D_L02_001B30C8&15))
        ref_L02_003CC7B0_16(obj,data->w31c,0,0,16.0f,0.0f);
    if (data->w204==1) {
        if (data->w33c) {
            allowed=0;
            if (D_00189E20.obj26c==obj || D_00189E20.obj270==obj || (D_00189E20.active && !D_00189E20.portal)) allowed=1;
            else if (ref_L02_003CC7B0_18(F(obj,0xf8),ref_L02_003CC7B0_17(F(data,0x1f0)-F(obj,0x10),F(data,0x1f4)-F(obj,0x14)))<1.5707964897155762f) allowed=1;
            if (!allowed) data->w204=0; else data->h386=300;
        }
    } else if (data->h386) {
        data->w200=D_00189E20.target; qcopy((char *)data+0x1f0,D_00189E20.direction); data->w204=1;
    }
    return 0;
}
