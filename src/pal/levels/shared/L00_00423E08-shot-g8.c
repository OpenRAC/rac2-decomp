#include "include_asm.h"

#include "common.h"
typedef int Quad128 __attribute__((mode(TI)));
extern char *func_0029EFD0(int);
extern void func_0029F338(void *);
extern void func_002A0F48(void *);
extern char *func_002AB1F0(char *);
extern void func_002AFFD8(void *, void *, int);
extern int func_002B4038(int, int);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern void func_00282F20(void *, void *, float);
extern float func_00283CE0(int);
extern int func_00283CF0(float);
extern int func_002FED90(void *, float, float, float, void *);
extern void func_L00_0037FA90(void *, void *, float, float, float);
extern void ref_L00_0041EB38_00(void (*)(void *), void *);
extern void func_PAL_L00_00424840(void *);
typedef struct {
    char pad0[0x50];
    float speed;                   
    char pad54[224 - 0x54];
} ShotKind;
typedef struct {
    unsigned int slot;             
    int pad04[3];
    int frame;                     
    int ownerIndex;                
    int ownerKind;                 
    char *target;                  
    float velocity[3];             
    float speed;                   
    int pad30;
    int handle;                    
    int count;                     
    float step;                    
    float fade;                    
} ShotState;
extern ShotKind D_L00_00262570[];
extern char D_00139570[];
extern Quad128 D_00189EA0 __attribute__((nosda));
extern char D_00189E20[];
extern float D_L00_001B1498 __attribute__((sda));
extern float D_L00_001B1494 __attribute__((sda));
extern unsigned int D_L00_001B1490 __attribute__((sda));

/* Spawn object 0xC89 at origin, aimed along the owner, at target or along the hero. */
char *func_PAL_L00_00423E08(Quad128 *origin, char *owner, char *target)
{
    Quad128 normal, position;
    char *object, *collision, *hero;
    ShotState *state;
    float speed;
    int count, ownerIndex, ownerKind;

    object = func_0029EFD0(0xC89);
    if (object) {
        ((unsigned char *)object)[0x30] = 255;
        *(short *)(object + 0x34) = 0x100;
        *(short *)(object + 0x32) = 255;
        object[0x31] = 1;
        *(char **)(object + 0xB8) = owner;
        object[0x20] = 0;
        state = *(ShotState **)(object + 0x68);
        speed = (D_L00_00262570 + ((unsigned char *)D_00139570)[0x16])->speed * 0.020000001f;
        hero = D_00189E20;
        if (*(short *)(hero + 0x24EC) == 1) {
            func_00282F20(state->velocity, owner + 0xD0, -speed);
            *(Quad128 *)(object + 0x10) = *origin;
        } else {
            if (target) {
                char *point = target + 0x10;

                qcopy(&position, point);
                collision = func_002AB1F0(target);
                if (collision) {
                    func_002AFFD8(point, &normal, 1);
                    func_00282D30(&normal, &normal, *(float *)(collision + 0x10));
                    func_00282CC0(&position, &position, &normal);
                }
                func_00282CF0(state->velocity, &position, origin);
                func_00282F20(state->velocity, state->velocity, speed);
            } else if (*(int *)(hero + 0x1500)) {
                func_L00_0037FA90(state->velocity, origin, speed, 30.0f, 0.3490658998f);
            } else {
                func_00282F20(state->velocity, hero + 0x760, speed);
            }
            *(Quad128 *)(object + 0x10) = *origin;
        }
        state->speed = speed;
        count = func_00283CF0(30.0f / speed) + 1;
        state->count = count;
        state->step = 1.0f / func_00283CE0(count);
        *(float *)(object + 0x2C) = *(float *)(*(char **)(object + 0x24) + 0x24) * D_L00_001B1498;
        object[0x20] = 0;
        state->target = target;
        if (target) {
            collision = func_002AB1F0(target);
            if (collision)
                *(unsigned short *)(collision + 0x1E) |= 0x80;
        }
        state->fade = 1;
        ownerIndex = *(short *)(*(char **)(owner + 0x68) + 0x12);
        state->ownerIndex = ownerIndex;
        ownerKind = *(short *)(owner + 0xAA);
        state->ownerKind = ownerKind;
        if (!func_002B4038(ownerKind, ownerIndex)) {
            func_0029F338(object);
            return 0;
        }
        state->frame = 0;
        D_L00_001B1494 = 0;
        if (D_L00_001B1490 > 15)
            D_L00_001B1490 = 0;
        state->slot = D_L00_001B1490;
        D_L00_001B1490++;
        if ((int)D_L00_001B1490 > 15)
            D_L00_001B1490 = 0;
        position = *(Quad128 *)(object + 0x10);
        *(Quad128 *)(object + 0x10) = D_00189EA0;
        state->handle = func_002FED90(object, 1.0f, 1.0f, 1.0f, 0);
        *(Quad128 *)(object + 0x10) = position;
        ref_L00_0041EB38_00(func_PAL_L00_00424840, object);
        func_002A0F48(object);
    }
    return object;
}
