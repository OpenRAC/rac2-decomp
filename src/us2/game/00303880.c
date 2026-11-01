#include "include_asm.h"


typedef int s32;
typedef unsigned char u8;
typedef struct { float x, y, z, w; } V4_F213135aa;
extern s32 func_00282A18(s32 value);
typedef struct {
    u8 pad00[0x80]; float position[4];
    u8 pad90[0x288]; float previousHeight;
    u8 pad31C[0x1514]; char *field1830;
    u8 pad1834[0xA5C]; char *field2290; int state;
    u8 pad2298[0x1C]; u8 field22B4;
} SurfacePlayer;
extern SurfacePlayer D_00189E20;
extern char D_001A8BD0[] __attribute__((sda));
typedef struct {
    u8 pad000[0x140]; float position[4];
    u8 pad150[0x3C8 - 0x150]; float heightOffset;
} SurfaceCamera;
extern SurfaceCamera D_001B5200;
extern V4_F213135aa ref_00302DA0_04[];
extern void ref_00302DA0_00(int, int, float);
extern int ref_00302DA0_01(int, int);
extern void ref_00302DA0_02(void);
extern int ref_00302DA0_03(void);
extern int func_00303E20(char *, void *, int *, int *);
extern void func_002A7750(u8 *, u8, s32);
extern float func_002AA140(float, float, float);
extern void func_002ABBB8(void *, void *, void *, float, float, int, int, int,
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
        if (func_00303E20(object,D_00189E20.position,(int *)(state+0x90),(int *)(state+0x94))) {
            *(int *)(state+0x98)=0;
            func_002A7750((u8 *)object,5,-1);
        }
    }
    if (*(int *)(state+0x98)>=0) {
        center=*(float *)(state+0x70)+*(float *)(state+4);
        ceiling=center+*(float *)(state+0x34)+1.0f;
        if (D_001B5200.position[2]<=ceiling && center-*(float *)(state+0x34)-1.0f<=D_001B5200.position[2])
            D_001B5200.heightOffset=ceiling-D_001B5200.position[2];
        { SurfacePlayer *player = &D_00189E20;
        if (player->state!=0x38 && player->state!=0x79 &&
            (player->state!=0x39 || *(int *)(*(char **)(player->field2290+0x24)+0x1f0)) &&
            player->state!=0x7a) {
            if (player->state==0x31) {
                func_002ABBB8(player->field1830, D_001A8BD0, 0, 0.0f, 0.0f, 10, 3, 16,
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
        if (D_00189E20.state==0x31 && *(int *)(state+0x98)>5)
            ref_00302DA0_03();
        blend=(float)*(int *)(state+0x98)*0.05f;
        if (blend>1.0f) blend=1.0f;
        index=*(int *)(state+0x40)*64+*(int *)(state+0x94)*8+*(int *)(state+0x90);
        D_00189E20.position[2]=func_002AA140(D_00189E20.position[2],
            ref_00302DA0_04[index].z-(float)*(int *)(state+0x98)*0.016666668f,blend);
        ++*(int *)(state+0x98);
    }
}

