#include "names.h"
typedef unsigned int u32;
typedef unsigned long long u64;
typedef unsigned int TI128 __attribute__((mode(TI)));
typedef union {TI128 q;float v[4];} Vector;
typedef struct {Vector corners[4];u32 colors[4];Vector uv[2];u64 state[4];} SurfacePacket;
extern void matrix_mul_vec3(void *,void *,void *);
extern void mat_build_basis_from_vecs(void *,void *,void *);
/* Retail translates the matrix along its first axis by the incoming f12 value. */
extern void moby_add_scaled_vec_to_offset(char *,float);
extern void gfx_build_transformed_rows(void *,void *,float,float,float);
extern int math_random_int_range(int,int);
extern float math_random_float_range(float,float);
extern void part_l03_init_effect_record(unsigned char *,int,int,int);
extern void VU1_addGSregister(u32,u64),draw_world_quad(void *,void *,int);
#define F(p,o) (*(float *)((char *)(p)+(o)))
#define I(p,o) (*(int *)((char *)(p)+(o)))
/* Draws a small textured quad at the object, picking a random texture scroll each frame. */
void gfx_draw_scrolling_surface_quad(void *argument)
{
    unsigned char *object=argument;
    SurfacePacket packet;
    float matrix[16];
    Vector transformed,source;
    char *state=*(char **)(object+0x68);
    int texture;
    source.q=0;
    source.v[0]=F(state,0x10);source.v[1]=F(state,0x14);source.v[2]=F(state,0x18);source.v[3]=1.0f;
    transformed.q=source.q;
    matrix_mul_vec3(&transformed,&transformed,object+0xC0);
    mat_build_basis_from_vecs(matrix,object+0x10,&transformed);
    moby_add_scaled_vec_to_offset((char *)matrix,F(state,0x1C));
    gfx_build_transformed_rows(&packet,matrix,F(state,0x20),F(state,0x24),0.0f);
    switch(object[0x20]) {
    case 0:
    case 1:
    case 2:
        texture=math_random_int_range(0,1);
        part_l03_init_effect_record((unsigned char *)&packet,I(state,0x28+texture*4),2,(int)0x80808080);
        packet.uv[0].v[0]=math_random_float_range(0.0f,1.0f-F(state,8));
        packet.uv[0].v[1]=math_random_float_range(0.0f,1.0f-F(state,8));
        packet.uv[0].v[2]=packet.uv[0].v[0];
        packet.uv[0].v[3]=packet.uv[0].v[1]+F(state,8);
        packet.uv[1].v[0]=packet.uv[0].v[0]+F(state,8);
        packet.uv[1].v[1]=packet.uv[0].v[1];
        packet.uv[1].v[2]=packet.uv[0].v[0]+F(state,8);
        packet.uv[1].v[3]=packet.uv[0].v[1]+F(state,8);
        break;
    case 3:
        texture=(I(state,0x0C)/I(state,0x3C))%3;
        part_l03_init_effect_record((unsigned char *)&packet,I(state,0x30+texture*4),2,(int)0x80808080);
        break;
    }
    VU1_addGSregister(0x47,0x53001);
    draw_world_quad(&packet,0,0);
    VU1_addGSregister(0x47,0x5360B);
}
