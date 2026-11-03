/* functional: high. From the near-miss draft (GPT-6.1 Sol, 2052/2052 bytes, scheduling and register allocation differ); the draft's u offset for the last pass read D_L04_001AF548 where retail forms 0x1AF558 (fixed). Same reads, writes and calls in retail's order. */
#include "common.h"
typedef unsigned int RQ __attribute__((mode(TI)));
typedef union { RQ q; float f[4]; } RVec;
typedef struct { float x,y,z,w; } RPoint __attribute__((aligned(16)));
#define RB(p,o) (*(u8 *)((char *)(p)+(o)))
#define RH(p,o) (*(s16 *)((char *)(p)+(o)))
#define RI(p,o) (*(s32 *)((char *)(p)+(o)))
#define RF(p,o) (*(float *)((char *)(p)+(o)))
extern char *D_L04_001B25CC;
extern char D_L04_001B9680[];
extern RVec D_L04_0023BDD0[];
extern float D_L04_0023D220[],D_L04_0023D540[],D_L04_0023CA50[],D_L04_0023CD70[];
extern u8 D_L04_0023D090[],D_L04_0023D158[];
extern s16 D_L04_0023D860[],D_L04_0023D9F0[],D_L04_0023DB80[];
extern float D_L04_001B2E78,D_L04_001B2E80;
extern int D_L04_001AF330 __attribute__((sda));
extern float D_L04_001AF334 __attribute__((sda));
extern RVec D_L04_001AF340[] SDATA(D_L04_001AF340);
extern u8 D_L04_001AF380[] SDATA(D_L04_001AF380);
extern float D_L04_001AF388[] SDATA(D_L04_001AF388);
extern float D_L04_001AF38C[];
extern u8 D_L04_001AF3A8[] SDATA(D_L04_001AF3A8);
extern u16 D_L04_001B2E7C __attribute__((sda));
extern RPoint D_L04_002AB7A0[], D_L04_002AB6E0[];
extern int D_L04_002AB860[][4];
extern float D_L04_002AB924[],D_L04_002AB920[],D_L04_002AB8C4[],D_L04_002AB8C0[];
extern float D_L04_001AF558;
extern void func_00282CF0(void *,void *,void *);
extern void func_00282F20(void *,void *,float);
extern void func_00282DD8(void *,void *,void *);
extern void func_00282D30(void *,void *,float);
extern void func_002830C0(void *,void *,void *);
extern u64 func_0027C878(int);
extern void func_002FC560(int,u64);
extern void func_00280B90(void *,int,int);
extern u32 func_00282978(s16 *);
extern float func_00283CE0(int);
extern int func_00283CF0(float);
extern int func_002A77E0(int);
extern void func_L04_003C4858(void *,int);
void func_L04_003C4050(char *self) {
    RVec position,up,basis[4],other[4];
    struct {
        RPoint vertices[4];
        u32 colors[4]; float uv[8]; u64 giftag[4];
    } packet;
    char *state=*(char **)(self+0x68);
    char *matrix=D_L04_001B25CC+RI(state,4)*128;
    u32 alpha=(u32)RB(state,0x5C)<<24;
    u32 rgb=(RB(state,0x5F)<<16)|(RB(state,0x5E)<<8)|RB(state,0x5D);
    int end=RH(state,0)+RH(state,2)+RH(state,0x40);
    int i,j,k,index,opacity;
    RPoint *vertex;
    float *u,*v;
    float speed,size,age;
    qcopy(&position,self+0x10);
    up.q=0;
    position.f[3]=1.0f; up.f[2]=1.0f;
    func_00282CF0(&basis[0],D_L04_001B9680,&position);
    func_00282F20(&basis[0],&basis[0],1.0f);
    func_00282DD8(&basis[1],&basis[0],&up);
    func_00282F20(&basis[1],&basis[1],1.0f);
    func_00282DD8(&basis[2],&basis[1],&basis[0]);
    qcopy(&basis[3],&position);
    func_00282D30(&other[0],&basis[0],-1.0f);
    func_00282DD8(&other[1],&other[0],&up);
    func_00282F20(&other[1],&other[1],1.0f);
    func_00282DD8(&other[2],&other[1],&other[0]);
    qcopy(&other[3],&basis[3]);
    packet.giftag[1]=func_0027C878(RI(state,0x54)+0x3F);
    packet.giftag[2]=0xFF9000000260ULL; packet.giftag[3]=0x8000000048ULL;
    packet.giftag[0]=0;
    func_002FC560(0x4A,0); func_002FC560(0x47,0x51001);
    for(i=RH(state,0);i<end;i++) {
        RVec *transform;
        age=D_L04_0023D220[i]-D_L04_0023D540[i];
        transform=D_L04_0023D090[i] ? other : basis;
        D_L04_0023D220[i]=age;
        if(age<=-8.0f) D_L04_0023D220[i]=age+8.0f;
        func_002830C0(&transform[3],&D_L04_0023BDD0[i],matrix);
        speed=D_L04_0023CA50[i]; size=D_L04_0023CD70[i];
        if(D_L04_0023D158[i]) {
            packet.giftag[3]=0x8000000044ULL;
            for(j=2;j<4;j++) {
                v=(float *)((char *)&packet+0x54); u=(float *)((char *)&packet+0x50);
                for(k=0;k<4;k++) {
                    vertex=&packet.vertices[k];
                    index=D_L04_002AB860[j][k];
                    vertex->x=D_L04_002AB7A0[index].x;
                    vertex->y=D_L04_002AB7A0[index].y*speed;
                    vertex->z=D_L04_002AB7A0[index].z*size;
                    vertex->w=1.0f;
                    func_002830C0(&packet.vertices[k],&packet.vertices[k],transform);
                    *u=D_L04_002AB924[index*2]+D_L04_0023D220[i];
                    *v=D_L04_002AB920[index*2];
                    packet.colors[k]=alpha*D_L04_001AF3A8[index]|rgb;
                    u=(float *)((char *)u+8); v=(float *)((char *)v+8);
                }
                func_00280B90(&packet,0,0);
            }
        } else {
            if(D_L04_0023D860[i]) {
                func_00282978(&D_L04_0023D860[i]);
                opacity=func_00283CF0((1.0f-func_00283CE0(D_L04_0023D860[i])*D_L04_001B2E78)*D_L04_001AF334);
            } else if(D_L04_0023D9F0[i]) {
                if(func_00282978(&D_L04_0023D9F0[i])) {
                    func_L04_003C4858(self,i); opacity=0;
                    D_L04_0023D090[i]=func_002A77E0(2);
                } else opacity=func_00283CF0(func_00283CE0(D_L04_0023D9F0[i])*D_L04_001B2E80*D_L04_001AF334);
            } else {
                if(func_00282978(&D_L04_0023DB80[i])) D_L04_0023D9F0[i]=D_L04_001B2E7C;
                opacity=D_L04_001AF330;
            }
            packet.giftag[3]=0x8000000048ULL;
            opacity=(u32)opacity<<24;
            v=(float *)((char *)&packet+0x54); u=(float *)((char *)&packet+0x50);
            for(k=0;k<4;k++) {
                vertex=&packet.vertices[k];
                vertex->x=D_L04_001AF340[k].f[0];
                vertex->y=D_L04_001AF340[k].f[1]*speed;
                vertex->z=D_L04_001AF340[k].f[2]*size;
                vertex->w=1.0f;
                *u=D_L04_001AF388[k*2]-D_L04_0023D220[i];
                *v=D_L04_001AF38C[k*2];
                packet.colors[k]=(u32)opacity*D_L04_001AF380[k]|RI(state,0x38);
                func_002830C0(&packet.vertices[k],&packet.vertices[k],transform);
                u=(float *)((char *)u+8); v=(float *)((char *)v+8);
            }
            func_00280B90(&packet,0,0);
        }
    }
    packet.giftag[1]=func_0027C878(RI(state,0x58)+0x3F);
    packet.giftag[3]=0x8000000044ULL;
    qcopy(&basis[3],matrix+0x30);
    basis[3].f[2]-=RF(state,0x50);
    if(!RH(state,0x42)) {
        for(j=0;j<6;j++) {
            v=(float *)((char *)&packet+0x54); u=(float *)((char *)&packet+0x50);
            for(k=0;k<4;k++) {
                vertex=&packet.vertices[k];
                index=D_L04_002AB860[j][k];
                vertex->x=D_L04_002AB6E0[index].x;
                vertex->y=D_L04_002AB6E0[index].y*RF(state,0x48);
                vertex->z=D_L04_002AB6E0[index].z*RF(state,0x4C);
                vertex->w=1.0f;
                func_002830C0(&packet.vertices[k],&packet.vertices[k],basis);
                *u=D_L04_002AB8C4[index*2]+D_L04_001AF558;
                *v=D_L04_002AB8C0[index*2];
                packet.colors[k]=D_L04_001AF3A8[index]*0xFF000000|rgb;
                u=(float *)((char *)u+8); v=(float *)((char *)v+8);
            }
            func_00280B90(&packet,0,0);
        }
    }
}
