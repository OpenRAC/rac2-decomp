#include "names.h"
typedef unsigned char u8;
typedef int Quad __attribute__((mode(TI)));
extern float g_teleporter_child_height_offset __attribute__((sda));
extern float g_teleporter_child_yaw_degrees __attribute__((sda));
extern void euler_rotation_basis(void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);

/* Move the three children from the common orbit and tilt their frames. */
void teleporter_update_orbiting_children(u8 *object)
{
    Quad displacement;
    u8 *state=*(u8 **)(object+0x68);
    u8 **slot=(u8 **)(state+0x14);
    int left=2;
    do {
        float distance;
        u8 *child=*slot;
        float height;
        float yaw;
        *(Quad *)(child+0x10)=*(Quad *)(object+0x10);
        height=*(float *)(child+0x18)+g_teleporter_child_height_offset;
        yaw=g_teleporter_child_yaw_degrees*0.017453294f;
        *(float *)(child+0x18)=height;
        *(float *)(*slot+0xF4)=yaw;
        distance=*(float *)(state+0x20)*2.4f-1.2f;
        euler_rotation_basis(*slot+0xC0,*slot+0xF0);
        vec_scale_to_length(&displacement,*slot+0xC0,distance);
        FastVecAdd(*slot+0x10,*slot+0x10,&displacement);
        *(float *)(*slot+0xF4)=*(float *)(state+0x24)*-1.0471977f-0.3490659f;
        euler_rotation_basis(*slot+0xC0,*slot+0xF0);
        slot++;
    } while (--left>=0);
}
