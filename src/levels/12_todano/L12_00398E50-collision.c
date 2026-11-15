#include "common.h"
extern void func_00282CF0(void *,void *,void *);
extern void func_002833F0(void *,void *);
extern void func_00283098(void *,void *,void *);
extern void func_00282CC0(void *,void *,void *);
extern int func_00277F48(void *,int,void *,int,float);
extern void *func_001153D4(void *,void *,unsigned int);
extern void func_00283698(void *,void *);
extern void func_002830C0(void *,void *,void *);
extern void func_002A90C8(void *,void *,int,void *,float);
extern u8 *D_L12_001C42C0[];

/* Tests nearby objects against a rectangle in the object's local frame. */
void func_L12_00412548(u8 *object,u8 *dimensions) {
    float rotation[12],searchPosition[4],relativePosition[4],localPosition[4],inverseRotation[16],contactPosition[4];
    float radius; short max; int count,i;
    euler_rotation_basis(rotation,object+0xF0);
    max=*(short *)(dimensions+0xA)<*(short *)(dimensions+8)?*(short *)(dimensions+8):*(short *)(dimensions+0xA);
    radius=max*0.5f;
    qzero_nc(searchPosition);searchPosition[2]=radius;
    matrix_mul_vec3(searchPosition,searchPosition,rotation);FastVecAdd(searchPosition,searchPosition,object+0x10);
    count=func_00277F48(searchPosition,16,object,0,radius);
    if(count) {
        u8 *list[count];
        func_001153D4(list,D_L12_001C42C0,count*sizeof(void *));
        for(i=0;i<count;i++) {
            u8 *candidate=list[i];
            if(candidate && candidate[0x20]!=254 && candidate[0x20]!=253) {
                FastVecSub(relativePosition,candidate+0x10,object+0x10);
                matrix_from_basis_rows(inverseRotation,rotation);transform_vector(localPosition,relativePosition,inverseRotation);qcopy_nc(contactPosition,localPosition);
                if(contactPosition[0]<-(*(short *)(dimensions+8)*0.5f+0.7f)) contactPosition[0]=-*(short *)(dimensions+8)*0.5f;
                else if(contactPosition[0]>*(short *)(dimensions+8)*0.5f+0.7f) contactPosition[0]=*(short *)(dimensions+8)*0.5f;
                if(contactPosition[2]<-(*(short *)(dimensions+0xA)*0.5f+1.5f)) contactPosition[2]=-*(short *)(dimensions+0xA)*0.5f;
                else if(contactPosition[2]>*(short *)(dimensions+0xA)*0.5f+1.5f) contactPosition[2]=*(short *)(dimensions+0xA)*0.5f;
                contactPosition[1]=0;
                matrix_mul_vec3(contactPosition,contactPosition,rotation);FastVecAdd(contactPosition,contactPosition,object+0x10);
                {
                    int hits=func_00277F48(contactPosition,16,object,0,0.7f);
                    int j;
                    for(j=0;j<hits;j++) {
                        if(D_L12_001C42C0[j]==candidate) func_002A90C8(candidate,object,0x10001,contactPosition,1.0f);
                    }
                }
            }
        }
    }
}
