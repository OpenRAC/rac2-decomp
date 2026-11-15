#include "common.h"

typedef int Quad __attribute__((mode(TI)));
typedef struct { char pad00[0xb0]; float origin[4]; char padc0[0x21d0]; int mask; } CollisionState;
extern CollisionState g_hero_state;
extern Quad D_L00_001BF230[2];
extern int D_L00_001A8FF0[] __attribute__((sda));
extern int coll_test_point(void *,int,float,void *);
extern void FastVecSub(float *,void *,void *);
extern void vec_scale_to_length(float *,float *,float);
extern float FastVecDot(float *,float *);
extern void FastVecScale(float *,float *,float);
extern void vec_fast_normalize(void *,void *,void *);
extern void FastVecAdd(void *,void *,void *);

typedef struct { char pad[0x10]; Quad position; char pad20[0x48]; char *data; } CollisionObject;

/* Pushes a moving object out of walls and slides its speed along the wall it hit. */
void coll_object_with_walls(CollisionObject *object)
{
    float normal[4],projection[4],remaining[4];
    char *data=object->data;
    void *position=&object->position;
    int collided;
    collided = coll_test_point(position,0,0.25f,(void *)g_hero_state.mask);
    if (collided) {
        qcopy(position,D_L00_001BF230);
        if(D_L00_001A8FF0[0]) {
            float dot;
            char *vector=data+0x30;
            FastVecSub(normal,g_hero_state.origin,position);
            vec_scale_to_length(normal,normal,1.0f);
            dot=FastVecDot(normal,(float *)vector);
            FastVecScale(projection,normal,dot);
            FastVecSub(remaining,vector,projection);
            vec_fast_normalize(vector,remaining,&D_L00_001BF230[1]);
            FastVecAdd(vector,vector,projection);
        } else {
            float vertical=*(float *)(data+0x38);
            *(float *)(data+0x38)=0;
            vec_fast_normalize(data+0x30,data+0x30,&D_L00_001BF230[1]);
            *(float *)(data+0x38)=vertical;
        }
    }
}
