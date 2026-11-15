#include "include_asm.h"

#include "common.h"
extern void FastVecScale(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern void anim_start_blended(void *, int, int, int);
extern void moby_mark_spawned(void *);
typedef struct {
    char pad0[0x80]; float launchOrigin[4];
    char pad90[0x148]; int action; char pad1DC[0x554]; char aimMatrix[48];
    float aimX, aimY;
    char pad768[0xAC8]; int fireMask;
    char pad1234[0x105C]; unsigned char *moby; int mode;
    char pad2298[0x20]; unsigned char active; char pad22B9[3]; unsigned char locked;
} ThrowHero;
typedef struct { char pad0[0x1A0]; int buttons; } ThrowPad;
extern ThrowHero g_hero_state;
extern ThrowPad g_pad_state;
typedef struct { char pad0[0x18]; unsigned char *moby; char pad1C[4]; float point[4]; } ThrowCollision;
extern ThrowCollision g_collision_hit;
extern char g_active_camera[], g_camera_eye_state[], D_001F1AF8[], g_weapon_table[];
extern unsigned char D_0013958A;
typedef struct { char pad[0x54]; float speed; char tail[0x88]; } ThrowClass;
extern void copy_matrix3x4(void *, void *);
extern void matrix_from_basis_rows(void *, void *);
extern void transform_vector(void *, void *, void *);
extern void matrix_mul_vec3(void *, void *, void *);
extern float mat_fast_helper_a(float, float);
extern float FastAddRotations(float, float);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern float fast_subtract_rotations(float, float);
extern float vec_length_xy(void *);
extern float square_root(float);
extern void vec_build_spherical_offset(void *, float, float, float);
extern int CollLine(void *, void *, int, void *, int);
extern void moby_compute_throw_velocity(void *, void *, void *, float, float, float);
extern int vec_fast_helper_b(void *);
extern int math_fast_float_d(void *);
extern unsigned int stub_empty_8(int, int);
extern int stub_empty_5(int, int);
extern void stub_empty_10(int);
extern int PlayMobySound(int, int, void *);
extern int stub_empty_6(int);
extern void stub_empty_11();
extern float moby_get_anim_value(void *);
extern void thrown_item_launch(void *, void *, void *);
extern void AddMobyToIndexList(void *, void *, int);
extern void *thrown_item_spawn(void *, void *, void *);
#define THROW_FLOAT(p,o) (*(float *)((char *)(p)+(o)))
#define THROW_INT(p,o) (*(int *)((char *)(p)+(o)))
#define THROW_PTR(p,o) (*(unsigned char **)((char *)(p)+(o)))
extern unsigned int func_US2_0026F750(int, int);
extern void stub_empty_12();
extern int stub_empty_7(int);

void func_US2_00315DD0(unsigned char *self)
{
    typedef unsigned int Quad __attribute__((mode(TI)));
    typedef union { Quad q; float f[4]; } Vec;
    struct { Vec position, offset, grip, basis[4], launch, end;
        char matrix[48]; char inverse[64]; Vec aim, velocity, temp; } frame;
#define position frame.position
#define offset frame.offset
#define grip frame.grip
#define basis frame.basis
#define launch frame.launch
#define end frame.end
#define matrix frame.matrix
#define inverse frame.inverse
#define aim frame.aim
#define velocity frame.velocity
#define temp frame.temp
    unsigned char *data, *heldData, *player;
    float angle, pitch, slope, distance, height, power;
    int hit;
    if (!self) return;
    grip.q = 0;
    grip.f[0] = 0.4f;
    grip.f[1] = -0.15f;
    grip.f[2] = -0.05f;
    data = THROW_PTR(self,0x68);
    copy_matrix3x4(matrix,g_active_camera);
    matrix_from_basis_rows(inverse,matrix);
    if (!data) return;
    qcopy(&position,self+0x10);
    FastVecScale(&basis[0],self+0xD0,-1.0f);
    qcopy(&basis[1],self+0xC0);
    qcopy(&basis[2],self+0xE0);
    transform_vector(&offset,&grip,basis);
    FastVecAdd(data+0x40,&position,&offset);
    if (THROW_PTR(data,0x50)) {
        THROW_INT(THROW_PTR(data,0x50),0x9C)=1;
    }
    if (!THROW_PTR(data,0x50) || THROW_PTR(data,0x50)[0x20]==0xFE || THROW_PTR(data,0x50)[0x20]==0xFD)
        THROW_PTR(data,0x50)=0;
    if (g_hero_state.mode==1) func_US2_0026F750(0x1D,1);
    if (THROW_PTR(data,0x50) && !g_hero_state.locked) {
        heldData=THROW_PTR(THROW_PTR(data,0x50),0x68);
        velocity.q=0;
        velocity.f[0]=(g_pad_state.buttons&4)?0.10000000894f:0.06666667014f;
        aim.q=velocity.q;
        matrix_mul_vec3(&aim,&aim,g_hero_state.aimMatrix);
        launch.f[0]=math_fast_sin_or_cos_a(FastAddRotations(-0.3619680106639862f,mat_fast_helper_a(g_hero_state.aimX,g_hero_state.aimY)))*0.8590390086f;
        launch.f[1]=math_fast_sin_or_cos_b(FastAddRotations(-0.3619680106639862f,mat_fast_helper_a(g_hero_state.aimX,g_hero_state.aimY)))*0.8590390086f;
        launch.f[2]=0;
        FastVecAdd(&launch,&launch,g_hero_state.launchOrigin);
        launch.f[2]+=0.4908199906f;
        mat_fast_helper_a(aim.f[0],aim.f[1]);
        FastVecScale(&end,&aim,60.0f);
        FastVecAdd(&end,&end,&launch);
        if (g_pad_state.buttons&4) {
            temp.q=0;
            temp.f[2]=6.0f;
            hit=0;
            velocity.q=temp.q;
            transform_vector(&velocity,&velocity,inverse);
            player=g_hero_state.moby;
            fast_subtract_rotations(THROW_FLOAT(player,0xF8),mat_fast_helper_a(velocity.f[0],velocity.f[1]));
            angle=mat_fast_helper_a(velocity.f[0],velocity.f[1]);
            pitch=mat_fast_helper_a(vec_length_xy(&velocity),velocity.f[2]);
            if(pitch>0.5934119821f) pitch=0.5934119821f;
            if(pitch< -1.396263599f) pitch=-1.396263599f;
            vec_build_spherical_offset(&velocity,(g_pad_state.buttons&4)?6.0f:4.0f,angle,pitch);
            {
                float planarLength=vec_length_xy(&velocity);
                float z = velocity.f[2];
                if(planarLength!=0) slope=z/planarLength;
                else slope=z*100.0f;
            }
            {
                float fallTime=square_root((g_pad_state.buttons&4)?0.008166667074f:0.005444444716f);
                distance=((fallTime+fallTime)*fallTime)*(1.0f-slope)*367.3469238f;
            }
            height=slope*distance;
            if(distance>0) {
                velocity.f[0]=math_fast_sin_or_cos_a(angle)*distance;
                velocity.f[1]=math_fast_sin_or_cos_b(angle)*distance;
                velocity.f[2]=height;
                FastVecAdd(&temp,g_camera_eye_state,&velocity);
                if(CollLine(g_camera_eye_state,&temp,2,self,0) && g_collision_hit.moby!=g_hero_state.moby) {
                    qcopy(&end,g_collision_hit.point);
                    hit=1;
                    angle=mat_fast_helper_a(end.f[0]-launch.f[0],end.f[1]-launch.f[1]);
                }
                if(!hit) {
                    end.f[0]=(math_fast_sin_or_cos_a(angle)*distance)*5.0f;
                    end.f[1]=(math_fast_sin_or_cos_b(angle)*distance)*5.0f;
                    end.f[2]=height*5.0f;
                    FastVecAdd(&end,&end,g_camera_eye_state);
                }
            }
        }
        power=(g_pad_state.buttons&4)?6.0f:4.0f;
        moby_compute_throw_velocity(&launch,&end,heldData,0.002722222358f,1.0f,power);
    }
    vec_fast_helper_b(data+0x58);
    switch(self[0x20]) {
    case 0:
        THROW_PTR(data,0x50)=0;
        if (self[0x60]&2) self[0x20]=2;
        else self[0x20]=1;
        /* Fall through. */
    case 1:
        if(self[0x60]&2) self[0x20]=2;
        /* Fall through. */
    case 2:
        if(g_hero_state.mode==1) func_US2_0026F750(0x1D,1);
        if(self[0x42]==self[0x43] && self[0x42]==3 && (self[0x60]&2)) anim_start_blended(self,1,0,2);
        if(THROW_FLOAT(data,0x58)==0 && !g_hero_state.locked && (g_pad_state.buttons&g_hero_state.fireMask)) {
            if(stub_empty_5(-1,1)) {
                stub_empty_11(4);
                if(self[0x43]!=3) anim_start_blended(self,3,0,2);
                self[0x20]=3;
                {
                    ThrowClass *weapon = &((ThrowClass *)g_weapon_table)[D_0013958A];
                    THROW_FLOAT(data,0x58) = 1.0f / weapon->speed;
                }
            } else PlayMobySound(4,0,self);
        }
        if(!(g_pad_state.buttons&g_hero_state.fireMask) || !stub_empty_7(-1)) {
            if(g_hero_state.action>=9 || !g_hero_state.active) stub_empty_12();
        }
        break;
    case 3:
        if(self[0x42]==self[0x43] && self[0x42]==3 && moby_get_anim_value(self)>=2.0f) {
            if(THROW_PTR(data,0x50)) {
                thrown_item_launch(&launch,THROW_PTR(data,0x50),THROW_PTR(THROW_PTR(data,0x50),0x68));
                AddMobyToIndexList(THROW_PTR(data,0x50),D_001F1AF8,0x3F);
                THROW_PTR(data,0x50)=0;
                THROW_INT(data,0x54)=10;
            }
            self[0x20]=2;
        }
        break;
    case 4: break;
    case 5: self[0x20]=6; break;
    case 6:
        if(THROW_PTR(data,0x50)) {moby_mark_spawned(THROW_PTR(data,0x50));THROW_PTR(data,0x50)=0;}
        break;
    }
    math_fast_float_d(data+0x54);
    if(THROW_PTR(data,0x50)) qcopy(THROW_PTR(data,0x50)+0x10,data+0x40);
    else if(!THROW_INT(data,0x54) && stub_empty_7(-1)) {
        qzero_nc(&aim);
        THROW_PTR(data,0x50)=thrown_item_spawn(self,data+0x40,&aim);
    }
}
