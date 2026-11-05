#include "common.h"

typedef int Quad __attribute__((mode(TI)));
typedef struct { char pad00[0xb0]; float origin[4]; char padc0[0x21d0]; int mask; } CollisionState;
extern CollisionState D_00189E20;
extern Quad D_L00_001BF230[2];
extern int D_L00_001A8FF0[] __attribute__((sda));
extern int func_00277258(void *,int,float,void *);
extern void func_00282CF0(float *,void *,void *);
extern void func_00282F20(float *,float *,float);
extern float func_00282DB0(float *,float *);
extern void func_00282D30(float *,float *,float);
extern void func_00283028(void *,void *,void *);
extern void func_00282CC0(void *,void *,void *);

typedef struct { char pad[0x10]; Quad position; char pad20[0x48]; char *data; } CollisionObject;

void func_L00_003B39D0(CollisionObject *object)
{
    float normal[4],projection[4],remaining[4];
    char *data=object->data;
    void *position=&object->position;
    int collided;
    collided = func_00277258(position,0,0.25f,(void *)D_00189E20.mask);
    if (collided) {
        qcopy(position,D_L00_001BF230);
        if(D_L00_001A8FF0[0]) {
            float dot;
            char *vector=data+0x30;
            func_00282CF0(normal,D_00189E20.origin,position);
            func_00282F20(normal,normal,1.0f);
            dot=func_00282DB0(normal,(float *)vector);
            func_00282D30(projection,normal,dot);
            func_00282CF0(remaining,vector,projection);
            func_00283028(vector,remaining,&D_L00_001BF230[1]);
            func_00282CC0(vector,vector,projection);
        } else {
            float vertical=*(float *)(data+0x38);
            *(float *)(data+0x38)=0;
            func_00283028(data+0x30,data+0x30,&D_L00_001BF230[1]);
            *(float *)(data+0x38)=vertical;
        }
    }
}
