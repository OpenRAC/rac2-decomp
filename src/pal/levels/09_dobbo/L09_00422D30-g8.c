#include "include_asm.h"

#include "common.h"
typedef int DobboQuad __attribute__((mode(TI)));
extern void vec_local_offset_to_world(void *, void *, float, float, float);
extern u8 *moby_create_configured(void *, void *, int, void *, int, int);
extern void FastVecScale(void *, void *, float);
extern void *part_spawn_object_following_effect(void *, void *, int, int, int, int, int, int, float, float);
extern void moby_set_state(void *, int, int);
extern void *part_find_owned_effect_slot(void *, int, int);
extern void func_PAL_L00_0032C328(void *, void *, void *, void *, int, int, int, int, int, int, int);
extern char *func_PAL_L00_003FB330(void *, int, int, int, int, int, int, int, int, int, int, int, float, float);
extern void func_PAL_002AC718(void *, void *, void *, int, int, int, int, float, float, float, float, int, int, int, int, int, float, float, float);
extern void matrix_mul_vec3(void *, void *, void *);
extern void func_PAL_L00_00328480(void *, void *, int, int, void *, float, float, float, float, int, int);
extern void func_PAL_L00_002ED7E8(void *, void *, void *, int, int, float, float, float, float, float);
extern void moby_mark_spawned(void *);
extern int D_L09_001B1B70 __attribute__((sda));
extern float D_L09_001B1B48[2] __attribute__((sda));
extern float D_L09_001B1B40[2] __attribute__((sda));
extern float D_L09_001B1B50[2] __attribute__((sda));

void func_PAL_L09_00422D30(char *obj) {
    float offset[4], first[4], second[4], velocity[4], extra[4];
    char *data = *(char **)(obj+0x68);
    *(DobboQuad *)offset = 0;
    offset[1] = 5.0f;
    offset[2] = 18.0f;
    switch (*(unsigned char *)(obj+0x20)) {
    case 0:
        vec_local_offset_to_world(obj, first, 0.0f,4.0f,19.0f);
        vec_local_offset_to_world(obj, second,0.0f,10.0f,13.0f);
        first[3] = 0.2f; second[3] = 1.3f;
        moby_create_configured(first,second,0x28608020,obj,7,1);
        FastVecScale(offset,offset,*(float *)(obj+0x2C));
        part_spawn_object_following_effect(offset,obj,0x28608020,-1,0,-1,0,0x60,*(float *)(obj+0x2C)*1470000.0f,0.0f);
        moby_set_state(obj,1,-1);
        break;
    case 1:
        if (part_find_owned_effect_slot(obj,0x4010000,0) && !*(int *)data) moby_set_state(obj,2,-1);
        *(unsigned char *)(obj+0xA8) = 0xFF;
        break;
    case 2:
        func_PAL_L00_0032C328(obj,D_L09_001B1B50,D_L09_001B1B48,D_L09_001B1B40,0xFFFF,0,D_L09_001B1B70,0,0x87F,0xFF,0);
        *(DobboQuad *)second = 0;
        vec_local_offset_to_world(obj,first,offset[0],offset[1],offset[2]);
        func_PAL_L00_003FB330(first,0,12,12,12,12,12,0,1,0,0,0,*(float *)(obj+0x2C),20.0f);
        func_PAL_002AC718(obj,second,first,20,1,1,-1,0.0f,0.0f,0.0f,0.0f,0,0,-1,0,0x810001,9.0f,0.75f,0.0f);
        *(DobboQuad *)velocity = 0;
        velocity[1] = 0.080000006f;
        matrix_mul_vec3(velocity,velocity,obj+0xC0);
        func_PAL_L00_00328480(obj,first,10,1,velocity,0.25f,5.0f,0.75f,1.5f,0x7FAAAA40,0);
        *(DobboQuad *)extra = 0;
        extra[1] = 0.24000001f; extra[2] = -0.10000001f;
        func_PAL_L00_002ED7E8(obj,offset,extra,60,3,*(float *)(obj+0x2C)*2.0f,0.24000001f,1.0f,5.0f,1.0f);
        if (D_L09_001B1B70 >= 0) {
            *(short *)(obj+0x7C) = (1 << D_L09_001B1B70) | 0x8000;
            moby_set_state(obj,3,-1);
        } else moby_mark_spawned(obj);
        break;
    }
}
