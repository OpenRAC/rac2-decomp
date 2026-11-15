#include "include_asm.h"
#include "names.h"


typedef int s32;
typedef unsigned char u8;
typedef struct { float x, y, z, w; } V4_F213135aa;
extern s32 log2dim(s32 value);
typedef struct {
    u8 pad00[0x80]; float position[4];
    u8 pad90[0x288]; float previousHeight;
    u8 pad31C[0x1514]; char *field1830;
    u8 pad1834[0xA5C]; char *field2290; int state;
    u8 pad2298[0x1C]; u8 field22B4;
} SurfacePlayer;
extern SurfacePlayer g_hero_state;
extern char D_001A8BD0[] __attribute__((sda));
typedef struct {
    u8 pad000[0x140]; float position[4];
    u8 pad150[0x3C8 - 0x150]; float heightOffset;
} SurfaceCamera;
extern SurfaceCamera g_active_camera;
extern V4_F213135aa ref_00302DA0_04[];
extern void ref_00302DA0_00(int, int, float);
extern int ref_00302DA0_01(int, int);
extern void ref_00302DA0_02(void);
extern int ref_00302DA0_03(void);
extern int FindSurfaceGridCell(char *, void *, int *, int *);
extern void moby_set_state(u8 *, u8, s32);
extern float math_lerp_float(float, float, float);
extern void SpawnExplosionEffects(void *, void *, void *, float, float, int, int, int,
    float, float, float, float, int, float, int, int, int, int, int);

/* func_00302A20 uses the quadword-copy profile in 00300618-qcopy.c. */

/* func_00302A88 uses the debug profile in 00300618-state.c. */



/* Resolve the player onto the surface grid and blend their height into it. */
void func_US2_00303B98(char *object)
{
    char *state=*(char **)(object+0x68);
    float center, ceiling, blend;
    int index;
    if (*(int *)(state+0x98)==-1) {
        if (FindSurfaceGridCell(object,g_hero_state.position,(int *)(state+0x90),(int *)(state+0x94))) {
            *(int *)(state+0x98)=0;
            moby_set_state((u8 *)object,5,-1);
        }
    }
    if (*(int *)(state+0x98)>=0) {
        center=*(float *)(state+0x70)+*(float *)(state+4);
        ceiling=center+*(float *)(state+0x34)+1.0f;
        if (g_active_camera.position[2]<=ceiling && center-*(float *)(state+0x34)-1.0f<=g_active_camera.position[2])
            g_active_camera.heightOffset=ceiling-g_active_camera.position[2];
        { SurfacePlayer *player = &g_hero_state;
        if (player->state!=0x38 && player->state!=0x79 &&
            (player->state!=0x39 || *(int *)(*(char **)(player->field2290+0x24)+0x1f0)) &&
            player->state!=0x7a) {
            if (player->state==0x31) {
                SpawnExplosionEffects(player->field1830, D_001A8BD0, 0, 0.0f, 0.0f, 10, 3, 16,
                    4.0f, 2.0f, 9.0f, 1.0f, -1, 15.0f, 1, 1, -1, 0, 0x00810001);
                ref_00302DA0_00(0x88,0,0.0f);
                player->field1830=0;
                ref_00302DA0_01(0,1);
                ref_00302DA0_02();
                player->previousHeight=player->position[2];
            }
            if (player->field22B4)
                ref_00302DA0_01(0x7a,1);
            else if (*(int *)(*(char **)(player->field2290+0x24)+0x1f0))
                ref_00302DA0_01(0x79,1);
            else ref_00302DA0_01(0x39,1);
        }
        }
        if (g_hero_state.state==0x31 && *(int *)(state+0x98)>5)
            ref_00302DA0_03();
        blend=(float)*(int *)(state+0x98)*0.05f;
        if (blend>1.0f) blend=1.0f;
        index=*(int *)(state+0x40)*64+*(int *)(state+0x94)*8+*(int *)(state+0x90);
        g_hero_state.position[2]=math_lerp_float(g_hero_state.position[2],
            ref_00302DA0_04[index].z-(float)*(int *)(state+0x98)*0.016666668f,blend);
        ++*(int *)(state+0x98);
    }
}

