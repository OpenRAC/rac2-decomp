#include "common.h"
typedef int Vector128 __attribute__((mode(TI)));
typedef struct { int a,b,c,d; } __attribute__((aligned(16))) Quad16;
typedef struct {
    Quad16 vector;
    int owner,flags;
    unsigned char enabled,kind;
    unsigned short id;
    float distance;
    int active;
} CollisionRequest;
typedef struct { Vector128 next; CollisionRequest move; Vector128 direction; CollisionRequest area; } ProjectileWorkspace;
extern int coll_sweep_from_object(void *,float,float *,int,float,float,int,int,int);
extern void moby_set_state(unsigned char *,int,int);
extern void FastVecAdd(void *,void *,void *);
extern void make_hit_descriptor(char *,int,int,float,Quad16 *);
extern int CollLine(void *,void *,int,void *,void *);
extern int coll_test_point(void *,int,void *,float);
extern void FastVecScale(void *,void *,float);
extern int coll_process_hit(void *,int,void *,void *,float);
extern void vec_clear_128(Vector128 *);
extern char *part_create_flash(float,char *,int,int,int,int,int,int,int,int,int);
extern int PlayMobySound(int,int,char *);
extern void moby_mark_spawned(void *);
extern void math_apply_axis_rotation_to_quat(void *,void *,void *,float);
extern void ref_L16_004051A8_00(void *);
extern void ref_L16_004051A8_01(void (*)(void *),void *);
extern char *D_L16_001BFF58 __attribute__((nosda));
extern float D_L16_001B145C __attribute__((sda));
/* Projectile update: expires after 240 frames, moves along its velocity and, on a
 * hit, unless the object hit is the one its state records at +0x10, sends a blast
 * request (velocity scaled 1.5, or 3 with no object hit) through func_00277F48.
 * Both blast branches are written out in full; the compiler's cross-jumping merges
 * their common tails, as in retail. */
/* Updates a flying projectile (moby class 3773): it moves, explodes on a hit and disappears after a while. */
void projectile_l16_update(char *object)
{
    ProjectileWorkspace local;
    char *state=*(char **)(object+0x68);
    (*(int *)(state+0x24))++;
    if (*(int *)(state+0x24)>240) {
        coll_sweep_from_object(object,0.6f,(float *)(object+0x10),0x10003,*(float *)(state+0x14),0.0f,0,1,0);
        moby_set_state((unsigned char *)object,1,-1);
    }
    switch (*(unsigned char *)(object+0x20)) {
    case 0:
        FastVecAdd(&local.next,object+0x10,state);
        make_hit_descriptor((char *)&local.move,(int)object,3,*(float *)(state+0x14),(Quad16 *)state);
        local.move.id=*(unsigned short *)(object+0xaa);
        if (CollLine(object+0x10,&local.next,0,object,&local.move)!=0 || coll_test_point(object+0x10,0,object,0.3f)!=0) {
            if (D_L16_001BFF58!=0) {
                if (D_L16_001BFF58!=*(char **)(state+0x10)) {
                    qcopy(&local.direction,state);
                    FastVecScale(&local.direction,&local.direction,1.5f);
                    ((float *)&local.direction)[2]=1.0f;
                    ((float *)&local.direction)[3]=5627.9248f;
                    make_hit_descriptor((char *)&local.area,(int)object,0x10003,*(float *)(state+0x14),(Quad16 *)&local.direction);
                    local.area.kind=1;
                    local.area.id=*(unsigned short *)(object+0xaa);
                    local.area.enabled=0;
                    coll_process_hit(object+0x10,0,object,&local.area,0.6f);
                    moby_set_state((unsigned char *)object,1,-1);
                    return;
                }
            } else {
                qcopy(&local.direction,state);
                FastVecScale(&local.direction,&local.direction,3.0f);
                ((float *)&local.direction)[2]=1.0f;
                ((float *)&local.direction)[3]=5627.9248f;
                make_hit_descriptor((char *)&local.area,(int)object,0x10003,*(float *)(state+0x14),(Quad16 *)&local.direction);
                local.area.kind=1;
                local.area.id=*(unsigned short *)(object+0xaa);
                local.area.enabled=0;
                coll_process_hit(object+0x10,0,object,&local.area,0.6f);
                moby_set_state((unsigned char *)object,1,-1);
                return;
            }
        }
        qcopy(object+0x10,&local.next);
        FastVecScale(&local.direction,state,-0.5f);
        vec_clear_128((Vector128 *)&local.area);
        break;
    case 1:
        part_create_flash(0.25f,object+0x10,0,25,20,20,20,0,0,1,0);
        PlayMobySound(0,0,object);
        moby_mark_spawned(object);
        return;
    }
    math_apply_axis_rotation_to_quat(object+0xe0,object+0xe0,object+0xd0,D_L16_001B145C*0.017453294f);
    math_apply_axis_rotation_to_quat(object+0xc0,object+0xc0,object+0xd0,D_L16_001B145C*0.017453294f);
    ref_L16_004051A8_01(ref_L16_004051A8_00,object);
}
