/* Spawns the effect particle and seeds it with the object's relative position,
 * rotated by the object's matrix. The four matrix rows are cleared with qzero_nc,
 * so the first row's address is built again for the transpose call, as in retail. */
#include "common.h"

typedef int Quad __attribute__((mode(TI)));
/* Known effect header and payload prefix; total allocation extent is unspecified. */
typedef struct { unsigned char b0,b1,b2,b3; int color; unsigned char seed,alpha; unsigned short size; float life; union { Quad q; float f[4]; } position; float payload[8]; } Particle;
extern Particle *func_002B9030(int);
extern int func_00283CF0(float);
extern int func_001163B0(void);
extern float func_00283CE0(int);
extern float func_00282E80(void *,void *);
extern float func_002A7878(float,float);
extern int func_002A77E0(int);
extern s32 func_002AB1F0(u8 *);
extern void func_00282CF0(float *,void *,void *);
extern void func_00283698(void *,void *);
extern void func_002830C0(float *,float *,void *);
extern unsigned char *ref_L00_0033C0D0_00;

Particle *func_L00_0033C0D0(char *object,Quad *position,float *velocity,int *config,int flag)
{
    float relative[4];
    Quad matrix[4];
    Particle *p=func_002B9030(0x4a);
    if(p) {
        float *out;
        p->alpha=FloatToInt(0.04f)-96;
        p->b3=flag?0x48:0x44;
        p->b1=0;
        out=p->payload;
        p->b2=*ref_L00_0033C0D0_00;
        p->seed=func_001163B0();
        p->life=0;
        qcopy(&p->position, position);
        out[0]=velocity[0];out[1]=velocity[1];out[2]=velocity[2];
        FastVecSub(relative,position,object+0x10);
        qzero_nc(&matrix[0]);qzero_nc(&matrix[1]);qzero_nc(&matrix[2]);qzero_nc(&matrix[3]);
        matrix_from_basis_rows(matrix,object+0xc0);
        transform_vector(relative,relative,matrix);
        out[4]=relative[0];out[5]=relative[1];out[6]=relative[2];
        *(char **)(out+3)=object;
        *(int **)(out+7)=config;
        p->size=*(unsigned short *)((char*)config+0xc);
        p->color=*config;
    }
    return p;
}
