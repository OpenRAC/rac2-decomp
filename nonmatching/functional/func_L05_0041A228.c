/* functional: high. From the near-miss draft (2152/2156 bytes; register allocation and scheduling differ); the draft named the camera position D_L05_001B96B0 where this level's code forms 0x1B96C0 (fixed). Same reads, writes and calls in retail's order. */
#include "common.h"
extern float func_002A7940(void);
extern void func_00281EB8(void *,int,int,int,float,float,float);
extern long long func_0027C878(int);
extern void func_002FC560(int,long long);
extern void func_00280328(void);
extern void func_00283658(void *,void *);
extern void func_00282D30(void *,void *,float);
extern void func_00282CC0(void *,void *,void *);
extern void func_00282CF0(void *,void *,void *);
extern void func_002830C0(void *,void *,void *);
extern void func_00282DD8(void *,void *,void *);
extern void func_00282F20(void *,void *,float);
extern void func_00281810(int,void *,void *,void *,int);
extern void func_002ACEC0(void *,void *,void *,float);
extern float func_00283B98(float,float);
extern void func_002AB668(void *,void *,float);
extern void func_002ACDE8(void *,void *,void *);
extern float D_L05_002B8330[][4],D_L05_002B8670[][4];
extern char D_L05_002B8550[],D_L05_001B96C0[];
extern int D_L05_001B11D0 __attribute__((sda));
extern int D_L05_001B11D4 __attribute__((sda));
extern int D_L05_001B11D8 __attribute__((sda));
extern int D_L05_001B11DC __attribute__((sda));
extern int D_L05_001B11E0 __attribute__((sda));
extern int D_L05_001B11E4 __attribute__((sda));
extern int D_L05_001B1218 __attribute__((sda));
extern int D_L05_001B1078 __attribute__((sda));
extern float D_L05_001B11E8 __attribute__((sda));
extern float D_L05_001B11F0 __attribute__((sda));
extern float D_L05_001B11F4 __attribute__((sda));
extern float D_L05_001B11FC __attribute__((sda));
extern float D_L05_001B1200 __attribute__((sda));
extern float D_L05_001B1204 __attribute__((sda));
extern float D_L05_001B120C __attribute__((sda));
extern float D_L05_001B1210 __attribute__((sda));
extern float D_L05_001B1214 __attribute__((sda));
extern float D_L05_001B121C __attribute__((sda));
extern float D_L05_001B1220 __attribute__((sda));
extern float D_L05_001B1224 __attribute__((sda));
extern float D_L05_001B1228 __attribute__((sda));
extern float D_L05_001B122C __attribute__((sda));
extern char D_L05_001B1090[] SDATA(D_L05_001B1090);
extern char D_L05_001B1130[] SDATA(D_L05_001B1130);
extern char D_L05_001B11A0[] SDATA(D_L05_001B11A0);
extern float D_L05_001B10F0[][4] SDATA(D_L05_001B10F0);
extern float D_L05_001B1160[][4] SDATA(D_L05_001B1160);
extern int D_L05_001B11F8 __attribute__((sda));
typedef struct { float x,y,z,w; } EffectVector;
typedef struct { float x,y,z; } EffectPosition;

typedef struct {
    int mode; char *owner; float radius, speed; char pad10[16];
    int alpha; char pad24[12]; int active; float size;
} EffectState;

void func_L05_0041A228(char *o)
{
    struct { int colors[36]; EffectPosition vertices[34]; } render;
    EffectVector point;
    float basis[4][4],view[4],rotation[4];
    union { int q __attribute__((mode(TI))); float f[4]; } uv;
    EffectState *st=*(EffectState **)(o+0x68);
    float width,height,radius;
    int j;
    EffectPosition *out;
    int *color;
    if (st->active) {
        float radius, angle;
        st->size+=D_L05_001B122C;
        D_L05_001B11D8=0x80000000;
        D_L05_001B11E0=0x40000000;
        D_L05_001B11DC=0x20000000;
        D_L05_001B11E4=D_L05_001B11D4=0xFFFF0000;
        radius=D_L05_001B121C;
        radius+=st->size;
        angle=func_002A7940();
        func_00281EB8(o+0x10,0x31,0x40801010,1,radius,0.0f,angle);
        radius=D_L05_001B1220;
        radius+=st->size;
        angle=func_002A7940();
        func_00281EB8(o+0x10,0x31,0x707F7F7F,1,radius,0.0f,angle);
        radius=D_L05_001B1224;
        radius+=st->size;
        angle=func_002A7940();
        func_00281EB8(o+0x10,0x2F,0x407F7F7F,1,radius,0.0f,angle);
        radius=D_L05_001B1228;
        radius+=st->size;
        angle=func_002A7940();
        func_00281EB8(o+0x10,D_L05_001B1218,0x407F7F7F,1,radius,0.0f,angle);
        return;
    }
    func_002FC560(6,func_0027C878(D_L05_001B11D0));
    func_002FC560(0x42,0x8000000048LL);
    func_002FC560(8,0);
    func_002FC560(0x14,0xFF9000000260LL);
    func_00280328();
    func_00283658(basis[0],o+0xC0);
    func_00282D30(&point,basis[0],-D_L05_001B11E8);
    func_00282CC0(basis[3],o+0x10,&point);
    width=D_L05_001B1200;
    height=D_L05_001B1214;
    if (*(short *)(st->owner+0xAA)==0x97C) width=height=0.2f;
    { float (*table)[4]; int i;
    table=D_L05_002B8330;
    out=render.vertices; color=render.colors;
    for(i=33;i>=0;i--) {
        point.x=(*table)[0]*width; point.y=(*table)[1]*D_L05_001B1204; point.z=(*table)[2]*D_L05_001B1204; point.w=1.0f;table++;
        func_002830C0(&point,&point,basis[0]);
        out->x=point.x;out->y=point.y;out->z=point.z;out++;
        *color++=D_L05_001B11D4|st->alpha;
    }
    func_00281810(D_L05_001B1078,render.vertices,render.colors,D_L05_002B8550,1);
    }
    func_00282CF0(view,D_L05_001B96C0,basis[3]);
    func_00282DD8(basis[1],basis[0],view);func_00282F20(basis[1],basis[1],1.0f);
    func_00282DD8(basis[2],basis[1],basis[0]);
    func_002FC560(6,func_0027C878(11));

        func_002FC560(0x42,0x7F00000044LL);
    { float (*table)[4]; int i;
        table=D_L05_002B8670;out=render.vertices;color=render.colors;
        for(i=7;i>=0;i--) {
            point.x=(*table)[0]*width; point.y=(*table)[1]*D_L05_001B1204; point.z=(*table)[2]; point.w=1.0f;table++;
            
            func_002830C0(&point,&point,basis[0]);
            out->x=point.x;out->y=point.y;out->z=point.z;out++;
            *color++=(D_L05_001B11D8)|st->alpha;
        }
        func_00281810(8,render.vertices,render.colors,D_L05_001B1090,1);
    }
    
        func_002FC560(0x42,0x7F00000048LL);
    { float (*table)[4]; int i;
        table=D_L05_002B8670;out=render.vertices;color=render.colors;
        for(i=7;i>=0;i--) {
            point.x=(*table)[0]*width; point.y=(*table)[1]*D_L05_001B1204; point.z=(*table)[2]; point.w=1.0f;table++;
            point.x*=1.1f;point.y*=3.0f;
            func_002830C0(&point,&point,basis[0]);
            out->x=point.x;out->y=point.y;out->z=point.z;out++;
            *color++=(D_L05_001B11DC)|st->alpha;
        }
        func_00281810(8,render.vertices,render.colors,D_L05_001B1090,1);
    }
    
    func_002FC560(0x42,0x7F00000044LL);
    func_00282D30(&point,basis[0],height);func_00282CC0(basis[3],basis[3],&point);

    { float (*table)[4]; int i;
        table=D_L05_001B1160;out=render.vertices;color=render.colors;
        for(i=3;i>=0;i--) {
            func_00282F20(&point,*table++,D_L05_001B120C);
            func_002830C0(&point,&point,basis[0]);
            out->x=point.x;out->y=point.y;out->z=point.z;out++;
            *color++=(D_L05_001B11E0)|st->alpha;
        }
        func_00281810(4,render.vertices,render.colors,D_L05_001B11A0,1);
    }
    
        func_002FC560(0x42,0x7F00000048LL);
    { float (*table)[4]; int i;
        table=D_L05_001B1160;out=render.vertices;color=render.colors;
        for(i=3;i>=0;i--) {
            func_00282F20(&point,*table++,D_L05_001B1210);
            func_002830C0(&point,&point,basis[0]);
            out->x=point.x;out->y=point.y;out->z=point.z;out++;
            *color++=(D_L05_001B11E4)|st->alpha;
        }
        func_00281810(4,render.vertices,render.colors,D_L05_001B11A0,1);
    }
    
    uv.q=0;uv.f[2]=uv.f[3]=1.0f;
    func_002FC560(6,func_0027C878(0x40));
    func_00282CF0(basis[0],D_L05_001B96C0,basis[3]);func_00282F20(basis[0],basis[0],1.0f);
    func_00282DD8(basis[1],basis[0],uv.f);func_00282F20(basis[1],basis[1],1.0f);func_00282DD8(basis[2],basis[1],basis[0]);
    radius=st->radius;
    func_002ACEC0(basis[1],basis[1],basis[0],radius);func_002ACEC0(basis[2],basis[2],basis[0],radius);
    st->radius=func_00283B98(st->radius,st->speed*0.017453294f*D_L05_001B11FC);
    func_002AB668(rotation,basis[0],1.5707965f);
    for(j=0;j<4;j++) {
    { float (*table)[4]; int i;
        table=D_L05_001B10F0;out=render.vertices;color=render.colors;
        for(i=3;i>=0;i--) {
            point.x=(*table)[0]; point.y=(*table)[1]*D_L05_001B11F0; point.z=(*table)[2]*D_L05_001B11F4; point.w=1.0f;table++;
            func_002830C0(&point,&point,basis[0]);
            out->x=point.x;out->y=point.y;out->z=point.z;out++;
            *color++=D_L05_001B11F8|st->alpha;
        }
        func_00281810(4,render.vertices,render.colors,D_L05_001B1130,1);
    }
        if(j!=3) {func_002ACDE8(basis[1],basis[1],rotation);func_002ACDE8(basis[2],basis[2],rotation);}
    }
}
