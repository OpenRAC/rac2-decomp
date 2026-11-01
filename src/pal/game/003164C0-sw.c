#include "include_asm.h"

#include "common.h"
extern void func_00282D30(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_002A7470(void *, int, int, int);
extern void func_0029F338(void *);
typedef struct {
    char pad0[0x80]; float launchOrigin[4];
    char pad90[0x148]; int action; char pad1DC[0x554]; char aimMatrix[48];
    float aimX, aimY;
    char pad768[0xAC8]; int fireMask;
    char pad1234[0x105C]; unsigned char *moby; int mode;
    char pad2298[0x20]; unsigned char active; char pad22B9[3]; unsigned char locked;
} ThrowHero;
typedef struct { char pad0[0x1A0]; int buttons; } ThrowPad;
extern ThrowHero D_00189E20;
extern ThrowPad D_00138180;
typedef struct { char pad0[0x18]; unsigned char *moby; char pad1C[4]; float point[4]; } ThrowCollision;
extern ThrowCollision D_001BAF80;
extern char D_001B5200[], D_001B5340[], D_001F1AF8[], D_00239BA0[];
extern unsigned char D_0013958A;
typedef struct { char pad[0x54]; float speed; char tail[0x88]; } ThrowClass;
extern void func_00283678(void *, void *);
extern void func_00283698(void *, void *);
extern void func_002830C0(void *, void *, void *);
extern void func_00283098(void *, void *, void *);
extern float func_00283248(float, float);
extern float func_00283B98(float, float);
extern float func_00283180(float);
extern float func_00283198(float);
extern float func_00283BE0(float, float);
extern float func_00282E20(void *);
extern float func_00282C10(float);
extern void func_002AF000(void *, float, float, float);
extern int func_002761F8(void *, void *, int, void *, int);
extern void func_00314E28(void *, void *, void *, float, float, float);
extern void func_002829D8(void *);
extern void func_00282948(void *);
extern void func_0026F748(int, int);
extern int func_0026F730(int, int);
extern void func_0026F758(int);
extern void func_002E5CF8(int, int, void *);
extern int func_0026F738(int);
extern void func_0026F760();
extern float func_0029F530(void *);
extern void func_003159D0(void *, void *, void *);
extern void func_002ACA50(void *, void *, int);
extern void *func_003158A8(void *, void *, void *);
#define THROW_FLOAT(p,o) (*(float *)((char *)(p)+(o)))
#define THROW_INT(p,o) (*(int *)((char *)(p)+(o)))
#define THROW_PTR(p,o) (*(unsigned char **)((char *)(p)+(o)))
extern void func_PAL_0026F5B8(int, int);
extern void func_0026F768();
extern int func_0026F740(int);

void func_PAL_003164C0(unsigned char *self)
{
    typedef unsigned int Quad __attribute__((mode(TI)));
    typedef union { Quad q; float f[4]; } Vec;
    struct { Vec position, offset, grip, basis[4], launch, end;
        char matrix[48]; char inverse[64]; Vec aim, velocity, temp; } frame;
#define position frame.position
#define offset frame.offset
#define grip frame.grip
#define basis frame.basis
#define launch frame.launch
#define end frame.end
#define matrix frame.matrix
#define inverse frame.inverse
#define aim frame.aim
#define velocity frame.velocity
#define temp frame.temp
    unsigned char *data, *heldData, *player;
    float angle, pitch, slope, distance, height, power;
    int hit;
    if (!self) return;
    grip.q = 0;
    grip.f[0] = 0.4f;
    grip.f[1] = -0.15f;
    grip.f[2] = -0.05f;
    data = THROW_PTR(self,0x68);
    func_00283678(matrix,D_001B5200);
    func_00283698(inverse,matrix);
    if (!data) return;
    qcopy(&position,self+0x10);
    func_00282D30(&basis[0],self+0xD0,-1.0f);
    qcopy(&basis[1],self+0xC0);
    qcopy(&basis[2],self+0xE0);
    func_002830C0(&offset,&grip,basis);
    func_00282CC0(data+0x40,&position,&offset);
    if (THROW_PTR(data,0x50)) {
        THROW_INT(THROW_PTR(data,0x50),0x9C)=1;
    }
    if (!THROW_PTR(data,0x50) || THROW_PTR(data,0x50)[0x20]==0xFE || THROW_PTR(data,0x50)[0x20]==0xFD)
        THROW_PTR(data,0x50)=0;
    if (D_00189E20.mode==1) func_PAL_0026F5B8(0x1D,1);
    if (THROW_PTR(data,0x50) && !D_00189E20.locked) {
        heldData=THROW_PTR(THROW_PTR(data,0x50),0x68);
        velocity.q=0;
        velocity.f[0]=(D_00138180.buttons&4)?0.120000005f:0.080000006f;
        aim.q=velocity.q;
        func_00283098(&aim,&aim,D_00189E20.aimMatrix);
        launch.f[0]=func_00283180(func_00283B98(-0.3619680106639862f,func_00283248(D_00189E20.aimX,D_00189E20.aimY)))*0.8590390086f;
        launch.f[1]=func_00283198(func_00283B98(-0.3619680106639862f,func_00283248(D_00189E20.aimX,D_00189E20.aimY)))*0.8590390086f;
        launch.f[2]=0;
        func_00282CC0(&launch,&launch,D_00189E20.launchOrigin);
        launch.f[2]+=0.4908199906f;
        func_00283248(aim.f[0],aim.f[1]);
        func_00282D30(&end,&aim,5e+01f);
        func_00282CC0(&end,&end,&launch);
        if (D_00138180.buttons&4) {
            temp.q=0;
            temp.f[2]=6.0f;
            hit=0;
            velocity.q=temp.q;
            func_002830C0(&velocity,&velocity,inverse);
            player=D_00189E20.moby;
            func_00283BE0(THROW_FLOAT(player,0xF8),func_00283248(velocity.f[0],velocity.f[1]));
            angle=func_00283248(velocity.f[0],velocity.f[1]);
            pitch=func_00283248(func_00282E20(&velocity),velocity.f[2]);
            if(pitch>0.5934119821f) pitch=0.5934119821f;
            if(pitch< -1.396263599f) pitch=-1.396263599f;
            func_002AF000(&velocity,(D_00138180.buttons&4)?6.0f:4.0f,angle,pitch);
            {
                float planarLength=func_00282E20(&velocity);
                float z = velocity.f[2];
                if(planarLength!=0) slope=z/planarLength;
                else slope=z*100.0f;
            }
            {
                float fallTime=func_00282C10((D_00138180.buttons&4)?0.01176f:0.00784f);
                distance=((fallTime+fallTime)*fallTime)*(1.0f-slope)*255.10204f;
            }
            height=slope*distance;
            if(distance>0) {
                velocity.f[0]=func_00283180(angle)*distance;
                velocity.f[1]=func_00283198(angle)*distance;
                velocity.f[2]=height;
                func_00282CC0(&temp,D_001B5340,&velocity);
                if(func_002761F8(D_001B5340,&temp,2,self,0) && D_001BAF80.moby!=D_00189E20.moby) {
                    qcopy(&end,D_001BAF80.point);
                    hit=1;
                    angle=func_00283248(end.f[0]-launch.f[0],end.f[1]-launch.f[1]);
                }
                if(!hit) {
                    end.f[0]=(func_00283180(angle)*distance)*5.0f;
                    end.f[1]=(func_00283198(angle)*distance)*5.0f;
                    end.f[2]=height*5.0f;
                    func_00282CC0(&end,&end,D_001B5340);
                }
            }
        }
        power=(D_00138180.buttons&4)?6.0f:4.0f;
        func_00314E28(&launch,&end,heldData,0.00392f,1.0f,power);
    }
    func_002829D8(data+0x58);
    switch(self[0x20]) {
    case 0:
        THROW_PTR(data,0x50)=0;
        if (self[0x60]&2) self[0x20]=2;
        else self[0x20]=1;
        /* Fall through. */
    case 1:
        if(self[0x60]&2) self[0x20]=2;
        /* Fall through. */
    case 2:
        if(D_00189E20.mode==1) func_PAL_0026F5B8(0x1D,1);
        if(self[0x42]==self[0x43] && self[0x42]==3 && (self[0x60]&2)) func_002A7470(self,1,0,2);
        if(THROW_FLOAT(data,0x58)==0 && !D_00189E20.locked && (D_00138180.buttons&D_00189E20.fireMask)) {
            if(func_0026F730(-1,1)) {
                func_0026F760(4);
                if(self[0x43]!=3) func_002A7470(self,3,0,2);
                self[0x20]=3;
                {
                    ThrowClass *weapon = &((ThrowClass *)D_00239BA0)[D_0013958A];
                    THROW_FLOAT(data,0x58) = 1.0f / weapon->speed;
                }
            } else func_002E5CF8(4,0,self);
        }
        if(!(D_00138180.buttons&D_00189E20.fireMask) || !func_0026F740(-1)) {
            if(D_00189E20.action>=8 || !D_00189E20.active) func_0026F768();
        }
        break;
    case 3:
        if(self[0x42]==self[0x43] && self[0x42]==3 && func_0029F530(self)>=2.0f) {
            if(THROW_PTR(data,0x50)) {
                func_003159D0(&launch,THROW_PTR(data,0x50),THROW_PTR(THROW_PTR(data,0x50),0x68));
                func_002ACA50(THROW_PTR(data,0x50),D_001F1AF8,0x3F);
                THROW_PTR(data,0x50)=0;
                THROW_INT(data,0x54)=8;
            }
            self[0x20]=2;
        }
        break;
    case 4: break;
    case 5: self[0x20]=6; break;
    case 6:
        if(THROW_PTR(data,0x50)) {func_0029F338(THROW_PTR(data,0x50));THROW_PTR(data,0x50)=0;}
        break;
    }
    func_00282948(data+0x54);
    if(THROW_PTR(data,0x50)) qcopy(THROW_PTR(data,0x50)+0x10,data+0x40);
    else if(!THROW_INT(data,0x54) && func_0026F740(-1)) {
        qzero_nc(&aim);
        THROW_PTR(data,0x50)=func_003158A8(self,data+0x40,&aim);
    }
}
