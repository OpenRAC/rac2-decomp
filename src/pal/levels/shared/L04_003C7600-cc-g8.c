/* func_PAL_L04_003C7600, the PAL copy of func_L04_003C4050: the same C, where wrap D_L04_0023D540[i] (({e}) * 8.0f); lit 8.0f becomes 9.6f. */
#include "common.h"

/* DrawEmitterParticles, the render callback that func_L04_003C3BA0
 * (L04-particle-emitter-g8.c) registers. It builds a basis facing the camera and its
 * mirror, then draws each particle of the emitter's range: two faces of the
 * D_L04_002AB860 box for particles flagged in D_L04_0023D158, a fading sprite
 * otherwise. Last it draws the emitter's own six-face box. Its $gp tables need -G8,
 * so it has a unit of its own instead of its place in L04_002CC748.c. */
typedef unsigned int EQ __attribute__((mode(TI)));
typedef union { EQ q; float f[4]; } EVec;
typedef struct { float x,y,z,w; } RPoint __attribute__((aligned(16)));
#define EB(p,o) (*(u8 *)((char *)(p)+(o)))
#define EH(p,o) (*(s16 *)((char *)(p)+(o)))
#define EI(p,o) (*(s32 *)((char *)(p)+(o)))
#define EF(p,o) (*(float *)((char *)(p)+(o)))
extern char *D_L04_001B25CC;
extern char D_L04_001B9680[];
extern EVec D_L04_0023BDD0[];
extern float D_L04_0023CA50[],D_L04_0023CD70[];
extern u8 D_L04_0023D090[],D_L04_0023D158[];
extern float D_L04_0023D220[],D_L04_0023D540[];
extern s16 D_L04_0023D860[],D_L04_0023D9F0[],D_L04_0023DB80[];
extern float D_L04_001B2E78,D_L04_001B2E80;
extern u16 D_L04_001B2E7C __attribute__((sda));
extern int D_L04_001AF330 __attribute__((sda));
extern float D_L04_001AF334 __attribute__((sda));
extern EVec D_L04_001AF340[] SDATA(D_L04_001AF340);
extern u8 D_L04_001AF380[] SDATA(D_L04_001AF380);
extern float D_L04_001AF388[] SDATA(D_L04_001AF388);
extern float D_L04_001AF38C[] MACRO_ADDR;
extern u8 D_L04_001AF3A8[] SDATA(D_L04_001AF3A8);
extern RPoint D_L04_002AB6E0[],D_L04_002AB7A0[];
extern int D_L04_002AB860[][4];
extern float D_L04_002AB8C0[],D_L04_002AB8C4[],D_L04_002AB920[];
extern float ref_L04_003C4050_00;
extern u64 func_0027C878(int);
extern void func_00280B90(void *,int,int);
extern u32 func_00282978(s16 *);
extern void func_00282CF0(void *,void *,void *);
extern void func_00282D30(void *,void *,float);
extern void func_00282DD8(void *,void *,void *);
extern void func_00282F20(void *,void *,float);
extern void func_002830C0(void *,void *,void *);
extern float func_00283CE0(int);
extern int func_00283CF0(float);
extern int func_002A77E0(int);
extern void func_002FC560(int,u64);
extern void func_L04_003C4858(void *,int);

static inline void TransformVertex(RPoint *v, EVec *m)
{
    func_002830C0(v, v, m);
}
void func_PAL_L04_003C7600(char *self) {
    EVec position,up,basis[4],other[4];
    struct {
        RPoint vertices[4];
        u32 colors[4]; struct { float u,v; } uv[4]; u64 giftag[4];
    } packet;
    char *state=*(char **)(self+0x68);
    char *matrix=D_L04_001B25CC+EI(state,4)*128;
    u32 alpha=(u32)EB(state,0x5C)<<24;
    u32 rgb=(EB(state,0x5F)<<16)|(EB(state,0x5E)<<8)|EB(state,0x5D);
    int end=EH(state,0)+EH(state,2)+EH(state,0x40);
    int i,j,k,index,opacity;
    RPoint *vertex;
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
    /* The mirrored basis, for particles flagged in D_L04_0023D090. */
    do {
        func_00282D30(&other[0],&basis[0],-1.0f);
        func_00282DD8(&other[1],&other[0],&up);
        func_00282F20(&other[1],&other[1],1.0f);
        func_00282DD8(&other[2],&other[1],&other[0]);
        qcopy(&other[3],&basis[3]);
    } while (0);
    packet.giftag[1]=func_0027C878(EI(state,0x54)+0x3F);
    packet.giftag[2]=0xFF9000000260ULL; packet.giftag[3]=0x8000000048ULL;
    packet.giftag[0]=0;
    func_002FC560(0x4A,0); func_002FC560(0x47,0x51001);
    for(i=EH(state,0);i<end;i++) {
        EVec *transform,*chosen;
        age=D_L04_0023D220[i]-((D_L04_0023D540[i]) * 1.2f);
        chosen=D_L04_0023D090[i] ? other : basis;
        transform=chosen;
        D_L04_0023D220[i]=age;
        if(age<=-8.0f) D_L04_0023D220[i]=age+8.0f;
        func_002830C0(&transform[3],&D_L04_0023BDD0[i],matrix);
        speed=D_L04_0023CA50[i]; size=D_L04_0023CD70[i];
        if(D_L04_0023D158[i]) {
            packet.giftag[3]=0x8000000044ULL;
            for(j=2;j<4;j++) {
                for(k=0;k<4;k++) {
                    vertex=&packet.vertices[k];
                    index=D_L04_002AB860[j][k];
                    vertex->x=D_L04_002AB7A0[index].x;
                    vertex->y=D_L04_002AB7A0[index].y*speed;
                    vertex->z=D_L04_002AB7A0[index].z*size;
                    vertex->w=1.0f;
                    TransformVertex(vertex,transform);
                    packet.uv[k].u=(D_L04_002AB920+1)[index*2]+D_L04_0023D220[i]; /* u: the second float of each pair */
                    packet.uv[k].v=D_L04_002AB920[index*2];
                    packet.colors[k]=alpha*D_L04_001AF3A8[index]|rgb;
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
            for(k=0;k<4;k++) {
                vertex=&packet.vertices[k];
                vertex->x=D_L04_001AF340[k].f[0];
                vertex->y=D_L04_001AF340[k].f[1]*speed;
                vertex->z=D_L04_001AF340[k].f[2]*size;
                vertex->w=1.0f;
                packet.uv[k].u=D_L04_001AF388[k*2]-D_L04_0023D220[i];
                packet.uv[k].v=D_L04_001AF38C[k*2];
                packet.colors[k]=(u32)opacity*D_L04_001AF380[k]|EI(state,0x38);
                TransformVertex(vertex,transform);
            }
            func_00280B90(&packet,0,0);
        }
    }
    packet.giftag[1]=func_0027C878(EI(state,0x58)+0x3F);
    packet.giftag[3]=0x8000000044ULL;
    qcopy(&basis[3],matrix+0x30);
    basis[3].f[2]-=EF(state,0x50);
    if(!EH(state,0x42)) {
        for(j=0;j<6;j++) {
            for(k=0;k<4;k++) {
                vertex=&packet.vertices[k];
                index=D_L04_002AB860[j][k];
                vertex->x=D_L04_002AB6E0[index].x;
                vertex->y=D_L04_002AB6E0[index].y*EF(state,0x48);
                vertex->z=D_L04_002AB6E0[index].z*EF(state,0x4C);
                vertex->w=1.0f;
                TransformVertex(vertex,basis);
                packet.uv[k].u=D_L04_002AB8C4[index*2]+ref_L04_003C4050_00;
                packet.uv[k].v=D_L04_002AB8C0[index*2];
                packet.colors[k]=D_L04_001AF3A8[index]*0xFF000000|rgb;
            }
            func_00280B90(&packet,0,0);
        }
    }
}
