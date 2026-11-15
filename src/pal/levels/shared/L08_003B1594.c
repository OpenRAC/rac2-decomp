#include "include_asm.h"

#include "common.h"
extern u8 *g_hero_moby;
extern float math_random_float_range(float, float);
typedef int Quad_L08_003B2DB0 __attribute__((mode(TI)));
typedef struct {
    float dir[4];                  
    float f10;                     
    int f14;                       
    int owner;                     
    short h1C, h1E;                
    float f20;                     
    int f24, f28;                  
} Bolt_L08_003B2DB0;
typedef struct {
    char pad0[0x10];
    float pos[4];                  
    char pad20[0x23 - 0x20];
    u8 b23;                        
    char pad24[0x2C - 0x24];
    float scale;                   
    u8 b30, b31;                   
    short h32;                     
    u16 h34;                       
    char pad36[0x68 - 0x36];
    Bolt_L08_003B2DB0 *state;      
    char pad6C[0xF0 - 0x6C];
    int fF0;                       
    float fF4, fF8;                
} Moby_L08_003B2DB0;
extern char g_hero_position[];
extern Moby_L08_003B2DB0 *CreateMoby(int);
extern float fast_vec_dist(void *, void *);
extern void *SpawnJointFollowParticle(void *, float, int, int, int);
extern void func_002A0F48(void *);
extern f32 D_L08_001BE0B0;
extern u8 D_L08_00296CD0[];
extern u8 D_L08_001DB5E7;
extern u8 *D_L08_001B29DC __attribute__((sda));
extern u8 *D_L08_001B29E0 __attribute__((sda));
extern u8 *D_L08_001B29DC __attribute__((sda));
extern f32 mat_fast_helper_a(f32, f32);
extern f32 vec_length_xy(void *);
extern u8 *g_hero_moby;
extern void func_002A0F48();

Moby_L08_003B2DB0 *func_PAL_L08_003B6448(int owner, float *pos, float *dir, int life)
{
    float p[4] __attribute__((aligned(16)));
    float d[4] __attribute__((aligned(16)));
    Moby_L08_003B2DB0 *moby;
    Bolt_L08_003B2DB0 *state;
    int n;
    float *pp = p;
    float *dd = d;

    *(Quad_L08_003B2DB0 *)p = *(Quad_L08_003B2DB0 *)pos;
    *(Quad_L08_003B2DB0 *)d = *(Quad_L08_003B2DB0 *)dir;
    moby = CreateMoby(0x4EA);
    if (moby) {
        state = moby->state;
        state->owner = owner;
        moby->fF0 = 0;
        moby->scale *= 4.0f;
        moby->b30 = 0xFF;
        moby->h32 = 0xFF;
        moby->b31 = 1;
        moby->fF4 = -mat_fast_helper_a(vec_length_xy(dd), dd[2]);
        moby->fF8 = mat_fast_helper_a(d[0], dd[1]);
        qcopy(moby->pos, pp);
        qcopy(state->dir, dd);
        state->f10 = math_random_float_range(-0.031415932f, 0.031415932f);
        state->f14 = 0;
        state->h1C = life;
        state->h1E = life;
        state->f20 = fast_vec_dist(moby->pos, g_hero_position);
        state->f24 = 0;
        state->f28 = 0;
        n = life * 5 / 4;
        moby->h34 |= 0x200;
        moby->b23 = 0x40;
        SpawnJointFollowParticle(moby, 400000.0f, 0x2F7F4F4F, n, -1);
        SpawnJointFollowParticle(moby, 160000.0f, 0x4F7F7F7F, n, -1);
        func_002A0F48(moby);
    }
    return moby;
}



