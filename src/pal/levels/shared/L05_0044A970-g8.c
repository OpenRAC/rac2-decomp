#include "names.h"
/* func_PAL_L05_0044A970, the PAL copy of func_L05_004445E8: the same C, with the chosen limit scaled to 50 Hz. */
#include "common.h"
extern int slot_find_active_in_chain(int);
extern float *moby_get_private_value_0(void *);
extern void *ship_find_lock_target(void *,void *,void *);
extern void FastVecSub(void *,void *,void *);
extern float FastVecLength(void *),FastVecDot(void *,void *);
extern float math_fast_angle_helper(float),math_fabs(float);
extern int CollLine(void *,void *,int,void *,int);
extern char g_spawn_entry_table[];
extern int g_ship_lock_duration_alt __attribute__((sda)),g_ship_lock_duration_normal __attribute__((sda));
extern float g_ship_lock_angle_limit __attribute__((sda));
extern int g_feltzin_mission_index;
extern char g_origin_vec[];
/* Updates the ship's missile lock-on: keeps or drops the current target and counts how long it has been locked, up to a limit (PAL: 50 Hz). */
void ship_update_target_lock_pal(char *object)
{
    float delta[4];
    char *state=*(char **)(object+0x68);
 int index=slot_find_active_in_chain(1);
    char *table;
    int limit;
    char *target;
    float *health;
    float length,dot;
    if(index<0 || *(int *)((table=g_spawn_entry_table)+index*40+20)<=0) {
        *(int *)(state+0x18)=0; *(int *)(state+0x14)=0; *(int *)(state+0x1c)=0;
        return;
    }
    limit=((s32)(*(int *)(table+0x168)?g_ship_lock_duration_alt:g_ship_lock_duration_normal) * 5 + 2) / 6;
    target=*(char **)(state+0x18);
    if(!target) {
        char *next_target;
        *(int *)(object+0x98)=0;
        next_target=ship_find_lock_target(state+0x20,0,*(void **)(state+0x14));
        *(int *)(object+0x98)=*(int *)(*(char **)(object+0x24)+0x10);
        if(next_target==*(char **)(state+0x14)) {
            if(++*(int *)(state+0x1c)<=limit) return;
            *(int *)(state+0x1c)=limit;
            goto clamp;
        }
        *(char **)(state+0x14)=next_target; goto reset;
    }
    {
        if ((u8)target[0x20] == 0xfe) goto invalid;
        if ((u8)target[0x20] == 0xfd) goto invalid;
        health=moby_get_private_value_0(target);
        if(health && *health<=0.0f) {
            invalid:
            *(int *)(state+0x1c)=*(int *)(state+0x18)=0; return;
        }
        FastVecSub(delta,*(char **)(state+0x18)+0x10,object+0x10);
        length=FastVecLength(delta);
        dot=FastVecDot(object+0xc0,delta);
        if(length==0.0f) goto zero_length;
        {
            *(int *)(object+0x98)=0;
            if(math_fabs(1.5707964f-math_fast_angle_helper(dot/length))>g_ship_lock_angle_limit*0.017453294f ||
               (g_feltzin_mission_index%5==0 && CollLine(g_origin_vec,*(char **)(state+0x18)+0x10,16,*(void **)(state+0x18),0))) {
                *(int *)(state+0x18)=0; *(int *)(state+0x14)=0; *(int *)(state+0x1c)=0;
            } else { if(++*(int *)(state+0x1c)>limit) *(int *)(state+0x1c)=limit; }
            *(int *)(object+0x98)=*(int *)(*(char **)(object+0x24)+0x10);
        }
    }
    goto clamp;
zero_length:
    *(int *)(state+0x18)=0;
    *(int *)(state+0x14)=0;
reset:
    *(int *)(state+0x1c)=0;
clamp:
    if(*(int *)(state+0x1c)>limit) *(int *)(state+0x1c)=limit;
}
