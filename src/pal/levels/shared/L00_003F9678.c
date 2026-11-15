#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
typedef struct {
    TI128 direction;
    char *owner;
    int flags;
    unsigned char enabled,kind;
    unsigned short id;
    float scale;
    int active;
    char pad[12];
} CollisionRequest5238;
extern unsigned char D_0013957F;
typedef struct { char prefix[0x50]; float speed; char gap[0x1c]; float distance; char rest[0x6c]; } Tuning;
extern Tuning g_weapon_l00_table[];
extern char *g_hero_moby;
extern char g_collision_result[];
typedef struct { char prefix[0x18]; char *object; char gap[4]; TI128 position; } HitResultView;
extern void vec_scale_to_length(void *,void *,float);
extern int CollLine(char *,void *,int,char *,void *);
extern void func_PAL_L00_003F97D0(char *,char *);
extern int level_has_pending_inner_flag(char *);
extern int func_PAL_00335DD0(char *,int,int);

int func_PAL_L00_003F9678(char *object,char *source)
{
    unsigned int settingsIndex = D_0013957F;
    Tuning *settings = g_weapon_l00_table + settingsIndex;
    CollisionRequest5238 request;
    TI128 position;
    char *state = *(char **)(object + 0x68);
    request.flags = 0x10000;
    request.owner = object;
    request.active = 1;
    request.scale = settings->distance;
    qcopy(&request.direction,state);
    vec_scale_to_length(&request.direction,&request.direction,1.0f);
    request.id = *(unsigned short *)(object + 0xaa);
    *(float *)((char *)&request.direction + 12) = 5627.9248f;
    request.enabled = 1;
    request.kind = 1;
    if (*(int *)(state + 0x28) == 1) qcopy(&position,state + 0x40);
    else qcopy(&position,object + 0x10);
    if (CollLine(source,&position,0,g_hero_moby,&request) != 0) {
        char *hitPosition = g_collision_result + 0x20;
        HitResultView *result;
        func_PAL_L00_003F97D0(object,hitPosition);
        result = (HitResultView *)(hitPosition - 0x20);
        if (result->object == 0) return 1;
        if (level_has_pending_inner_flag(result->object) != 0) return 1;
        if (result->object != 0)
            func_PAL_00335DD0(result->object,0x42,*(int *)(object + 0xb8));
    }
    return 0;
}


