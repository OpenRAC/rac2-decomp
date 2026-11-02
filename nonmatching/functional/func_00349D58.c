/* functional: medium. Near-miss draft of retail size with the same frame: differences are allocation and scheduling, with some block order; paths the captured calls never take are unproven. */
/* Tier sol-high, task v1286, USA v1.01, default -O2 -G0 profile.
 * Best: 1860/1860 bytes; 0/28 places match. Frame 0x70 and prologue GPRs agree.
 * 95/465 instruction words differ after ignoring relocation values.
 * First mismatch: +0x1e8, f20/f21 swapped (zero versus shared scale/color).
 * Packed colors 0x60442d00 and 0x55f0c070 are loaded early as FP constants;
 * retail materializes each into v0 at its key pair, then retains it in f20.
 * No first-allocation store difference remains: capture parent before clearing,
 * and use clear order 1,2,3,0. Repeated sprite address expressions recover the
 * s1->s6 and s2->fp copies. SDA declarations and 3.0f*global fix scalar setup.
 * Separate per-pair float locals enlarge the frame to 0x80; FP-first argument
 * interleaving changes scheduling without a match. -fno-gcse regresses to 1852.
 * Union, memcpy, and pointer-cast inline bit transfers compile identically.
 * Next useful experiment needs independent float/color lifetime or type evidence.
 * Use a separate unit if matched: same-file C calls and scalar constants.
 * All required declarations and the inline bit-transfer helper are below.
 */
static __inline__ float ColorBits(unsigned int bits)
{
    union { unsigned int bits; float value; } color;
    color.bits = bits;
    return color.value;
}

extern int func_00336E40(void *);
extern void *func_00336DA8(int,int);
extern void func_003361E0(void *,void *,void *);
extern void func_00336408(void *,int,int,void *,void *);
extern void func_00336390(void *,void *,int);
extern void func_00336498(void *,unsigned int,unsigned int);
extern void func_003364B0(void *,unsigned int,unsigned int);
extern void func_00336CE0(void *,unsigned int);
extern void func_00336B90(void *,int);
extern void func_00336CC8(void *,int);
extern int *func_00335E20(void *);
extern void *func_00335E18(void *);
extern void func_003494D0(void *,void *);
extern void func_00349628(void *,int);
extern void func_00349590(void *,void *);
extern void func_003495C0(void *,void *);
extern void func_00349678(void *,float);
extern void func_00349670(void *,int);
extern void func_003495D8(void *,int,float,float,float,float,float);
extern void func_00349610(void *,int,float,float);
extern void func_00349630(void *,int);
extern int func_003495C8(void *,int);
extern char D_001AE5F8[],D_001AE608[],D_001AE610[],D_001AE618[];
extern float D_001B23A4 __attribute__((sda));
extern int D_001B23A0 __attribute__((sda));
extern int D_001A7B90 __attribute__((sda));
extern int D_001A7A00 __attribute__((sda));

void func_00349D58(char *object,char *data,void *context)
{
    int *p;
    void *parent;
    char *label;
    char *parameters,*parameters1,*parameters2,*parameters3,*parameters4;
    float value;
    float packed;
    *(void **)(object+0x13c)=context;
    if(context) {
        p=func_00336DA8(16,func_00336E40(context));
        *(int **)(object+8)=p;
        parent=*(void **)(object+0x13c);
        p[1]=0;p[2]=0;p[3]=0;p[0]=0;
        p=func_00336DA8(16,func_00336E40(parent));
        *(int **)(object+0x1c8)=p;
        p[1]=0;p[2]=0;p[3]=0;p[0]=0;
    }
    func_003361E0(object+0x10,D_001AE5F8,context);
    func_003361E0((object+0x5c),D_001AE608,context);
    func_003361E0((object+0xa8),D_001AE610,context);
    label=object+0xf4;
    func_00336408(label,146,0,D_001AE618,context);
    func_00336390((object+0x5c),data+0x8710,17);
    func_00336390((object+0xa8),data+0x8710,18);
    func_00336498(label,0x8049c1ff,0x80001eff);
    func_003364B0(label,0x50f0c070,0x50f0c070);
    func_00336CE0(label,0x60442d00);
    func_00336B90(label,100);
    value=3.0f*D_001B23A4+0.5f;
    func_00336CC8(label,D_001B23A0==1?(int)(value+1.0f):(int)value);
    *func_00335E20((object+0x5c))=0x60442d00;
    *func_00335E20((object+0xa8))=0x55f0c070;
    parameters=object+0x140;
    func_003494D0(parameters,context);
    func_00349628(parameters,2);
    func_00349590(parameters,*(void **)(object+0x1c8));
    func_003495C0(parameters,object+0x1cc);
    func_00349678(parameters,0.005f);
    func_00349670(parameters,2);
    packed=50.0f;
    func_003495D8(parameters,0,0.0f,ColorBits(0x80f0c070),packed,0.0f,0.0f);
    func_003495D8(parameters,1,1.0f,-2.2126951167197445e-38f,packed,0.0f,0.0f);
    func_00349610(parameters,0,0.0f,0.0f);
    func_00349630(parameters,1);
    parameters1=object+0x1d4;
    func_003494D0(parameters1,context);
    func_00349628(parameters1,3);
    func_003495D8(parameters1,0,0.0f,ColorBits(0x442d00),0.0f,0.0f,0.0f);
    packed=ColorBits(0x60442d00);
    func_003495D8(parameters1,1,0.3f,packed,0.0f,0.0f,0.0f);
    func_003495D8(parameters1,2,1.0f,packed,0.0f,0.0f,0.0f);
    func_00349610(parameters1,1,0.0f,2.0f);
    func_00349590(parameters1,func_00335E20((object+0x5c)));
    func_00349670(parameters1,0);
    func_003495C0(parameters1,object+0x1cc);
    func_00349630(parameters1,-1);
    func_00349678(parameters1,D_001A7B90?0.14f:0.11666667461395264f);
    parameters2=object+0x25c;
    func_003494D0(parameters2,context);
    func_00349628(parameters2,3);
    func_003495D8(parameters2,0,0.0f,0.0f,0.0f,0.0f,0.0f);
    func_003495D8(parameters2,1,0.3f,1.0f,1.0f,0.0f,0.0f);
    func_003495D8(parameters2,2,1.0f,1.0f,1.0f,0.0f,0.0f);
    func_00349590(parameters2,func_00335E18((object+0x5c)));
    func_00349670(parameters2,0);
    func_003495C0(parameters2,object+0x1d0);
    func_00349630(parameters2,-1);
    func_00349678(parameters2,D_001A7B90?0.14f:0.11666667461395264f);
    func_003495C8(parameters2,0);
    parameters3=object+0x2e4;
    func_003494D0(parameters3,context);
    func_00349628(parameters3,3);
    func_003495D8(parameters3,0,0.0f,ColorBits(0xf0c070),0.0f,0.0f,0.0f);
    packed=ColorBits(0x55f0c070);
    func_003495D8(parameters3,1,0.3f,packed,0.0f,0.0f,0.0f);
    func_003495D8(parameters3,2,1.0f,packed,0.0f,0.0f,0.0f);
    func_00349610(parameters3,1,0.0f,3.0f);
    func_00349590(parameters3,func_00335E20((object+0xa8)));
    func_00349670(parameters3,0);
    func_003495C0(parameters3,object+0x1cc);
    func_00349630(parameters3,-1);
    func_00349678(parameters3,D_001A7B90?0.14f:0.11666667461395264f);
    parameters4=object+0x36c;
    func_003494D0(parameters4,context);
    func_00349628(parameters4,3);
    func_003495D8(parameters4,0,0.0f,1.2000000476837158f,1.2000000476837158f,0.0f,0.0f);
    func_003495D8(parameters4,1,0.3f,1.0f,1.0f,0.0f,0.0f);
    func_003495D8(parameters4,2,1.0f,1.0f,1.0f,0.0f,0.0f);
    func_00349590(parameters4,func_00335E18((object+0xa8)));
    func_00349670(parameters4,0);
    func_003495C0(parameters4,object+0x1d0);
    func_00349630(parameters4,-1);
    func_00349678(parameters4,D_001A7B90?0.14f:0.11666667461395264f);
    *(int *)(object+0x3f4)=0;
    *(int *)(object+0x400)=-1;
    *(int *)(object+0x3f8)=0;
    *(int *)(object+0xc)=0;
    *(int *)(object+4)=D_001A7A00;
}
