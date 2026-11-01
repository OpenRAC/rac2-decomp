#include "common.h"

/* Weapon wheel. One scratch int holds the colour and then the name's length: the reassignment is why cprop leaves retail's copy into the colour register. */
#define F(p,t,o) (*(t *)((char *)(p)+(o)))
extern float func_00283CE0(int);
extern int func_00283CF0(float);
extern float func_00283B98(float,float);
extern void func_0034CD70(void *,int,float);
extern int func_00290748(void);
extern void func_0028B740(void *,int *,int *);
extern int func_00115DA8(char *,char *,...);
extern unsigned int func_00283D38(unsigned int,unsigned int,float);
extern void func_0027FAA8(int,int,unsigned int,char *,int);
extern char *func_00288FB8(int);
extern unsigned int func_001157AC(const char *);
extern int D_001B18D0;
extern char **D_001B18D4;
extern int D_001A8D48 __attribute__((sda));
extern int D_001A8C64 __attribute__((sda));
extern char *D_001A8CFC __attribute__((sda));
extern unsigned char D_00139568[];
extern int D_001A73B8[] MACRO_ADDR;
extern int D_00139688[];
typedef struct { int active; char reserved04[0x44]; short localizedName; char reserved4A[0x3E]; unsigned short sellsAmmo; char reserved8A[4]; unsigned short ammoCapacity; char reserved90[0x50]; } WheelWeaponRecord;
extern WheelWeaponRecord D_L00_00262570[];
extern char D_001A8E28[];
int func_US2_0028D110(char *o)
{
    float a,b;
    int alpha,x,y,i,selected,split,j,len,yy;
    unsigned int scratch;
    char buffer[80], *text,*tail;
    WheelWeaponRecord *record;
    unsigned char *fade=(unsigned char *)o+0x70;
    a=func_00283CE0(fade[0])/func_00283CE0(8);
    if(a>1.0f) a=1.0f; else if(a<0.0f) a=0.0f;
    b=func_00283CE0(fade[1])/func_00283CE0(8);
    if(b>1.0f) b=1.0f; else if(b<0.0f) b=0.0f;
    alpha=func_00283CF0(a*128.0f);
    i=0;
    x=F(o,int,0x50); y=F(o,int,0x54);
    func_0028B740(o,&x,&y);
    for(;i<D_001B18D0;i++) {
        func_00283B98(((float)i*2.0f*3.1415927f)/(float)D_001B18D0-3.1415927f,1.5707964f);
        if(F(o,int,0x74)==i && F(D_001B18D4[D_001A8D48]+i*28,int,0) && D_001A8CFC) {
            float f=(float)(i+7);
            if(f>7.0f) f-=8.0f;
            func_0034CD70(D_001A8CFC+0x376c8,1,f);
        }
        if(F(D_001B18D4[D_001A8D48]+i*28,int,0) && D_001A8CFC) {
            char *p=D_001A8CFC+0x38000;
            F(p,int,0x79DC)=func_00290748()?func_00283CF0((float)alpha*0.5f):0;
        }
    }
    selected=F(o,int,0x74);
    if(selected>=0 && F(D_001B18D4[D_001A8D48]+selected*28,int,0) && !D_001A8C64) {
        int n=D_001A73B8[selected], value;
        float opacity;
        record=&D_L00_00262570[D_00139568[n]];
        opacity=a*b;

        if(record->active && record->sellsAmmo) {
            value=D_00139688[n];
            func_00115DA8(buffer,D_001A8E28,value,record->ammoCapacity);
            {
                unsigned int c;
                if (value) c=func_00283D38(0x00f0f0f0,0x80f0f0f0,opacity);
                else c=func_00283D38(0x004040ff,0x804040ff,opacity);
                func_0027FAA8(x+105,y+112,c,buffer,-1);
            }
        }
        scratch=func_00283D38(0x00f0f0f0,0x80f0f0f0,opacity);
        split=0;
        text=func_00288FB8(D_L00_00262570[D_00139568[F(D_001B18D4[D_001A8D48]+selected*28,int,0x18)]].localizedName);
        if(text && func_001157AC(text)) {
            unsigned int color=scratch;
            scratch=func_001157AC(text);
            len=scratch;
            tail=text;
            for(j=0;j<len;j++) {
                tail++;
                if(*(unsigned char *)tail=='-') {tail++;split=j+2;break;}
            }
            if(!split) {
                tail=text;
                for(j=0;j<len;j++) {
                    tail++;
                    if(*(unsigned char *)tail==' ') {tail++;split=j+1;break;}
                }
            }
            yy=y+100;
            if(D_L00_00262570[D_00139568[D_001A73B8[selected]]].sellsAmmo) yy=y+75;
            else { int splitY=y+85; yy=split ? splitY : yy; }
            if(split) {
                func_0027FAA8(x+105,yy,color,text,split);
                func_0027FAA8(x+105,yy+16,color,tail,-1);
            } else func_0027FAA8(x+105,yy,color,text,-1);
        }
    }
    return F(o,int,0x58);
}
