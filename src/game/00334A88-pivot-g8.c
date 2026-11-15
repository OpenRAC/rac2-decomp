#include "common.h"
typedef int Qword_34A88 __attribute__((mode(TI)));
typedef union { Qword_34A88 q; float f[4]; } V651;
typedef struct { char p0[0x31C]; float distance; char p320[0x28]; short h348,h34A,h34C,h34E; char p350[0x14E]; unsigned char b49E; char p49F[15]; short h4AE; char p4B0[0x1DE4]; int i2294; } Hero651;
extern Hero651 g_hero_state;
extern char D_001B53A0[];
extern int D_001A8CA0;
extern float D_001B120C __attribute__((sda));
extern short D_001B11D8 __attribute__((sda)), D_001B11F0 __attribute__((sda)), D_001B11F4 __attribute__((sda)), D_001B1208 __attribute__((sda)), D_001B1220 __attribute__((sda));
extern float D_001B11C0 __attribute__((sda)), D_001B11C4 __attribute__((sda)), D_001B1234 __attribute__((sda));
extern float FastVecDot(void *, void *), FastVecLength(void *), IntToFloat(int), cam_compute_signed_angle_to_point(void *,float);
extern int FloatToInt(float), coll_test_point(void *,int,int,float),FastDecTimer(void *),cam_resolve_position(void *,int);
extern void FastVecScale(void *,void *,float),FastVecSub(void *,void *,void *),lerp_vector(void *,void *,void *,float);
extern void hero_copy_vector_to_out(int, Qword_34A88 *);
extern void cam_compute_offset(void *,int,float);
#define H651(p,o) (*(short *)((p)+(o)))
#define F651(p,o) (*(float *)((p)+(o)))
#define I651(p,o) (*(int *)((p)+(o)))
#define B651(p,o) (*(unsigned char *)((p)+(o)))
/* Updates the camera pivot state each frame: follows the camera axis, runs the pivot state machine and writes the resulting vector to the output. */
void cam_update_pivot_state(char *moby, void *result)
{
    V651 base_vec, temp_vec;

    char *camera = D_001B53A0;
    char *state = *(char **)(moby+0x70)+0x60;
    char *axis;
    int mode, blocked;
    float scalar;
    if (g_hero_state.h348 || D_001A8CA0 || (H651(state,0xEE) && g_hero_state.h34E)) {
        H651(state,0xEC)=15;
        B651(state,0xD6)=1;
        H651(state,0xEE)=1;
        FastVecScale(state+0x10,camera+0x30,FastVecDot(state,camera+0x30));
        qcopy(state+0x20,state+0x10);
        mode=B651(state,0xC4);
        axis=camera+0x30;
        if ((unsigned)(mode-5)<3 || mode==3)
            cam_compute_offset(state+0x30,1,D_001B120C*0.5f);
    } else {
        if (H651(state,0xEE)==1) {
            FastVecScale(state+0x10,camera+0x30,FastVecDot(state,camera+0x30));
            qcopy(state+0x20,state+0x10);
            mode=B651(state,0xC4);
            axis=camera+0x30;
            if ((unsigned)(mode-5)<3 || mode==3)
                cam_compute_offset(state+0x30,1,D_001B120C*0.5f);
            scalar=IntToFloat(H651(state,0xD8))/IntToFloat(15);
            H651(state,0xD8)=FloatToInt(IntToFloat(H651(state,0xEC))*scalar);
            H651(state,0xEE)=2;
        } else {
            axis=camera+0x30;
            if (H651(state,0xEE)>=2) {
            scalar=FastVecDot(state,axis);
            FastVecScale(state+0x10,axis,scalar);
            qcopy(state+0x20,state+0x10);
            mode=B651(state,0xC4);
            axis=camera+0x30;
            if ((unsigned)(mode-5)<3 || mode==3)
                cam_compute_offset(state+0x30,1,D_001B120C*0.5f);
            if (++H651(state,0xEE)>=16) H651(state,0xEE)=0;
            }
        }
    }
    hero_copy_vector_to_out((int)moby,&base_vec.q);
    if (g_hero_state.i2294==0x74) {
        FastVecScale(result,axis,FastVecDot(state,axis));
        FastVecSub(state,state,result);
        FastVecScale(result,axis,FastVecDot(axis,state+0x60));
        qcopy(state+0x10,result);
        if (B651(state,0xC4)!=11) {
            char *mode_data;
            B651(state,0xC4)=11;
            qcopy(moby+0x40,moby);
            mode_data=*(char **)(moby+0x70)+0x20;
            H651(mode_data,0)=D_001B11D8;
            F651(mode_data,0x24)=1.0f/IntToFloat(H651(mode_data,0));
        }
        return;
    }
    switch (B651(state,0xC4)) {
    case 2: {
        float angle;
        if (g_hero_state.i2294==17 || (g_hero_state.b49E && g_hero_state.distance>0.2f && ((angle=cam_compute_signed_angle_to_point(moby,F651(state,0xB0)))<D_001B11C4 || angle>D_001B11C0))) {
            B651(state,0xC4)=1;
            H651(state,0xC6)=D_001B11F0;
            F651(state,0xC8)=1.0f/IntToFloat(H651(state,0xC6));
        }
        blocked=0;
        if (g_hero_state.h34C && (!g_hero_state.b49E || g_hero_state.h4AE>=16)) blocked=1;
        else if (cam_resolve_position(&temp_vec,1)!=1) blocked=1;
        else {
            scalar=FastVecDot(&temp_vec,axis);
            if (scalar<FastVecLength(state+0x10)) blocked=1;
        }
        if (blocked) {
            qcopy(result,state+0x10);
            scalar=FastVecDot(&base_vec,axis);
            FastVecScale(&temp_vec,axis,scalar);
            FastVecSub(state,&base_vec,&temp_vec);
        } else {
            cam_resolve_position(&temp_vec,1);
            FastVecScale(result,axis,FastVecDot(&temp_vec,axis));
            FastVecSub(state,&temp_vec,result);
        }
        break;
    }
    case 3: case 5: case 6: case 7:
        lerp_vector(state+0x10,state+0x30,state+0x20,(float)H651(state,0xD4)*F651(state,0xCC));
        if (!B651(state,0xD7) && coll_test_point(moby+0x30,18,0,0.2f)) {
            qcopy(state+0x30,state+0x10); B651(state,0xD7)=1;
        }
        qcopy(result,state+0x10);
        scalar=FastVecDot(&base_vec,axis);
        FastVecScale(&temp_vec,axis,scalar);
        FastVecSub(state,&base_vec,&temp_vec);
        if (FastDecTimer(state+0xD4)) {
            if (B651(state,0xC4)==9) {
                B651(state,0xC4)=10; H651(state,0xD4)=D_001B1220;
                qcopy(state+0x20,state+0x10);
                FastVecScale(&temp_vec,axis,F651(state,0xD0));
                FastVecSub(state+0x30,state+0x20,&temp_vec);
            } else if (B651(state,0xC4)==6) {
                B651(state,0xC4)=7; H651(state,0xD4)=D_001B11F4;
                qcopy(state+0x30,state+0x20); qcopy(state+0x20,state+0x10);
            } else {
                B651(state,0xC4)=4; H651(state,0xC6)=D_001B1208;
                F651(state,0xC8)=1.0f/IntToFloat(H651(state,0xC6));
            }
        }
        break;
    case 8:
        qcopy(result,state+0x10);
        scalar=FastVecDot(&base_vec,axis);
        FastVecScale(&temp_vec,axis,scalar);
        FastVecSub(state,&base_vec,&temp_vec);
        break;
    case 9: case 10:
        FastVecScale(result,axis,FastVecDot(&base_vec,axis));
        FastVecSub(state,&base_vec,result);
        lerp_vector(result,result,state+0x20,D_001B1234);
        break;
    default:
        FastVecScale(result,axis,FastVecDot(&base_vec,axis));
        FastVecSub(state,&base_vec,result);
        break;
    }
}
