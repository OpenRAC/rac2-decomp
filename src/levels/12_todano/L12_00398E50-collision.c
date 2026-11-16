#include "common.h"
extern void FastVecSub(void *,void *,void *);
extern void euler_rotation_basis(void *,void *);
extern void matrix_mul_vec3(void *,void *,void *);
extern void FastVecAdd(void *,void *,void *);
extern int coll_process_hit(void *,int,void *,int,float);
extern void *func_001153D4(void *,void *,unsigned int);
extern void matrix_from_basis_rows(void *,void *);
extern void transform_vector(void *,void *,void *);
extern void part_start_effect_default_table(void *,void *,int,void *,float);
extern u8 *g_impact_l12_moby_list[];

/* Tests nearby objects against a rectangle in the object's local frame. */
void coll_push_out_of_rectangle(u8 *object,u8 *dimensions) {
    float rotation[12],searchPosition[4],relativePosition[4],localPosition[4],inverseRotation[16],contactPosition[4];
    float radius; short max; int count,i;
    euler_rotation_basis(rotation,object+0xF0);
    max=*(short *)(dimensions+0xA)<*(short *)(dimensions+8)?*(short *)(dimensions+8):*(short *)(dimensions+0xA);
    radius=max*0.5f;
    qzero_nc(searchPosition);searchPosition[2]=radius;
    matrix_mul_vec3(searchPosition,searchPosition,rotation);FastVecAdd(searchPosition,searchPosition,object+0x10);
    count=coll_process_hit(searchPosition,16,object,0,radius);
    if(count) {
        u8 *list[count];
        func_001153D4(list,g_impact_l12_moby_list,count*sizeof(void *));
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
                    int hits=coll_process_hit(contactPosition,16,object,0,0.7f);
                    int j;
                    for(j=0;j<hits;j++) {
                        if(g_impact_l12_moby_list[j]==candidate) part_start_effect_default_table(candidate,object,0x10001,contactPosition,1.0f);
                    }
                }
            }
        }
    }
}
