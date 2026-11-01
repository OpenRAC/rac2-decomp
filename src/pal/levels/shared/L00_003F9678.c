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
extern Tuning D_L00_00262570[];
extern char *D_0018C0B0;
extern char D_L00_001BF200[];
typedef struct { char prefix[0x18]; char *object; char gap[4]; TI128 position; } HitResultView;
extern void func_00282F20(void *,void *,float);
extern int func_002761F8(char *,void *,int,char *,void *);
extern void func_PAL_L00_003F97D0(char *,char *);
extern int func_L00_0031BE88(char *);
extern void func_PAL_00335DD0(char *,int,int);

int func_PAL_L00_003F9678(char *object,char *source)
{
    unsigned int settingsIndex = D_0013957F;
    Tuning *settings = D_L00_00262570 + settingsIndex;
    CollisionRequest5238 request;
    TI128 position;
    char *state = *(char **)(object + 0x68);
    request.flags = 0x10000;
    request.owner = object;
    request.active = 1;
    request.scale = settings->distance;
    qcopy(&request.direction,state);
    func_00282F20(&request.direction,&request.direction,1.0f);
    request.id = *(unsigned short *)(object + 0xaa);
    *(float *)((char *)&request.direction + 12) = 5627.9248f;
    request.enabled = 1;
    request.kind = 1;
    if (*(int *)(state + 0x28) == 1) qcopy(&position,state + 0x40);
    else qcopy(&position,object + 0x10);
    if (func_002761F8(source,&position,0,D_0018C0B0,&request) != 0) {
        char *hitPosition = D_L00_001BF200 + 0x20;
        HitResultView *result;
        func_PAL_L00_003F97D0(object,hitPosition);
        result = (HitResultView *)(hitPosition - 0x20);
        if (result->object == 0) return 1;
        if (func_L00_0031BE88(result->object) != 0) return 1;
        if (result->object != 0)
            func_PAL_00335DD0(result->object,0x42,*(int *)(object + 0xb8));
    }
    return 0;
}


