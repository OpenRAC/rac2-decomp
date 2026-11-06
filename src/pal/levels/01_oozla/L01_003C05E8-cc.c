/* func_PAL_L01_003C05E8, the PAL copy of func_L01_003BCA38: the same C, where wrap func_002A7878(180.0f,240.0f) (({e}) * 5.0f + 2.0f) * 0.. */
#include "common.h"
extern void *func_0029EFD0(int);
extern float func_002A7940(void),func_002A7878(float,float),func_00283180(float),func_00283198(float);
extern int func_002A77E0(int);
extern void func_002A0F48(char *);
extern void func_00282D30(void *,void *,float);
extern float func_00282DF0(void *);
extern void func_002833F0(void *,void *);
extern void func_00283098(void *,void *,void *);
extern float func_00283248(float,float);
extern float func_00283B98(float,float);
extern int func_00283CF0(float);
typedef struct L01DebrisHeader {
    char pad[0x20];
    unsigned char initialized;
    char pad21[3];
    char *definition;
    int field28;
    float scale;
    unsigned char alpha, flags;
} L01DebrisHeader;
char *func_PAL_L01_003C05E8(char *parent,int kind,void *position,void *rotation,int life,int mode,void *velocity,void *spin,void *dimensions,float speed)
{
    float temp[4] __attribute__((aligned(16)));
    float direction[4] __attribute__((aligned(16)));
    float matrix[12] __attribute__((aligned(16)));
    char *obj=func_0029EFD0(kind);
    char *s;
    float angle, magnitude;
    if(obj) {
        float scale=((L01DebrisHeader *)parent)->scale / *(float *)(((L01DebrisHeader *)parent)->definition+0x24);
        s=*(char **)(obj+0x68);
        ((L01DebrisHeader *)obj)->scale=*(float *)(((L01DebrisHeader *)obj)->definition+0x24)*scale;
        ((L01DebrisHeader *)obj)->flags=1;
        *(long long *)(obj+0x38)=*(long long *)(parent+0x38);
        *(unsigned char *)(obj+0x20)=1;
        qcopy(obj+0x10,position);
        qcopy(obj+0xF0,rotation);
        func_002833F0(obj+0xC0,rotation);
        *(unsigned char *)(obj+0x30)=255;
        *(short *)(obj+0x32)=128;
        *(float *)(s+0x40)=func_002A7940();
        *(float *)(s+0x38)=speed;
        if(kind==0xA28) {
            *(float *)(s+0x44)=0.349065899848938f;
            if(speed==0.0f) *(float *)(s+0x38)=func_002A7878(9.0f,15.0f)*0.00040000002f;
            *(float *)(s+0x3C)=func_002A7878(-3.0f,-1.5f)*0.020000001f;
        } else {
            *(float *)(s+0x44)=1.5707964897155762f;
            if(!func_002A77E0(1)) *(float *)(s+0x44)=-*(float *)(s+0x44);
            if(*(float *)(s+0x38)==0.0f) *(float *)(s+0x38)=func_002A7878(9.0f,12.0f)*0.00040000002f;
            *(float *)(s+0x3C)=func_002A7878(-100.0f,-200.0f)*0.020000001f;
        }
        *(int *)(obj+0x98)=0;
        if(!life) *(int *)(s+0x30)=func_00283CF0(((func_002A7878(180.0f,240.0f)) * 5.0f + 2.0f) * 0.16666667f);
        else *(int *)(s+0x30)=life;
        *(int *)(s+0x34)=mode;
        if(func_00282DF0(velocity)==0.0f) {
            if(func_00282DF0(dimensions)==0.0f && *(float *)((char *)dimensions+12)==0.0f) angle=func_002A7940();
            else {
                func_002833F0(matrix,rotation);
                func_00283098(direction,dimensions,matrix);
                angle=func_00283248(direction[0],direction[1]);
                angle=func_00283B98(angle,func_002A7878(-1.047197699546814f,1.047197699546814f));
            }
            magnitude=func_002A7878(0.7f,1.8f)*0.020000001f;
            temp[0]=func_00283180(angle)*magnitude;
            temp[1]=func_00283198(angle)*magnitude;
            temp[2]=0;
            qcopy(s,temp);
        } else qcopy(s,velocity);
        if(func_00282DF0(spin)==0.0f) {
            temp[2]=func_002A7878(0.015707966f,0.03839725f);
            qcopy(s+0x10,temp);
        } else qcopy(s+0x10,spin);
        if(func_00282DF0(dimensions)==0.0f && *(float *)((char *)dimensions+12)==0.0f) {
            qcopy(temp,*(char **)(obj+0x24)+0x30);
            magnitude=*(float *)(obj+0x2C);
            magnitude*=0.0009765625f;
            func_00282D30(temp,temp,magnitude);
            temp[3]*=magnitude;
            qcopy(s+0x20,temp);
        } else qcopy(s+0x20,dimensions);
        func_002A0F48(obj);
    }
    return obj;
}
