#include "include_asm.h"

#include "common.h"
typedef unsigned int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vec;
typedef struct {
    int count;                   
    u8 pad04[0x10 - 0x04];
    Vec points[1];               
} LiftPath;
typedef struct {
    u8 pad00[0x50];
    u8 motion[0x40];             
    u8 pad90[0x98 - 0x90];
    float verticalSpeed;         
    u8 pad9C[0xA4 - 0x9C];
    int path;                    
    u8 padA8[0xAC - 0xA8];
    s16 atLast;                  
    u8 padAE[0xB4 - 0xAE];
    int sound;                   
    u8 padB8[0xC8 - 0xB8];
    int point;                   
    int needsTrigger;            
    int f0D0;                    
    int hasRecord;               
    float *record;               
    u8 padDC[0xE0 - 0xDC];
    Vec velocity;                
} LiftVars;
typedef struct {
    u8 pad00[0x10];
    Vec position;                
    u8 state;                    
    u8 pad21[0x68 - 0x21];
    LiftVars *vars;              
    u8 pad6C[0xF0 - 0x6C];
    Vec rotation;                
} Moby;
typedef struct {
    u8 pad0000[0x212];
    s16 f212;                    
    s16 f214;                    
    u8 pad0216[0x33C - 0x216];
    Moby *groundMoby;            
    int groundedFrames;          
    u8 pad0344[0x2290 - 0x344];
    Moby *moby;                  
} Hero;
typedef struct {
    u8 bytes[0x70];
} SoundRecord;
typedef struct {
    u8 pad0[0x74];
    u8 active;                   
    u8 pad75[0x88 - 0x75];
    Moby *owner;                 
} SoundVoice;
extern Hero D_00189E20;
extern SoundRecord D_00188660[];
extern LiftPath *D_L17_001FE880[];
extern int D_00138324[];
extern float D_L17_001B0220 __attribute__((sda));
extern float D_L17_001B0228 __attribute__((sda));
extern float D_L17_001B022C __attribute__((sda));
extern float D_L17_001B0234 __attribute__((sda));
extern int func_002B38B8(void *);
extern int func_002B3868(void *);
extern int func_L00_002D40F0(void);
extern int func_L06_003E3ED0(void *);
extern void func_002B0C28(int, int, int);
extern void func_002A7750(void *, int, int);
extern void func_L00_002D40A0(void *, int, float);
extern int func_002E5CF8(int, int, void *);
extern void func_002E59F8(int);
extern void func_L17_003C3250(void *);
extern float *func_L00_002D70A0(int);
extern void func_L00_002D7140(void *);
extern float func_002AA548(float *, float *, float, float, float, float);
extern float func_00282C48(float);
extern int func_00282978(s16 *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_002AD6F0(void *, void *, void *, void *);

/* Moves a lift between the first and the last point of its path: triangle
   starts it while the hero stands on it, it eases to the other end with its
   travel sound, and while idle it jumps to the hero's end when the hero is more
   than 10 units above or below it. Riders follow its movement. */
void func_US2_L17_003C48B0(Moby *moby)
{
    Quad old;
    Quad delta;
    LiftVars *vars = moby->vars;
    LiftPath *path;
    int sound;
    int point;
    Vec *velocity;

    qcopy(&old, &moby->position);
    path = D_L17_001FE880[vars->path];
    switch (moby->state) {
    case 0:
        /* Waiting at one end. */
        vars->sound = -1;
        if (D_00189E20.groundMoby == moby && D_00189E20.groundedFrames) {
            if (vars->needsTrigger && !func_002B38B8(moby))
                goto finish;
            func_002B0C28(8, 0x12EC, 1);
            if (D_00138324[0] & 0x10) {
                if (!vars->atLast) {
                    func_002A7750(moby, 4, -1);
                    velocity = &vars->velocity;
                    vars->point = 1;
                    func_00282CF0(velocity, &path->points[1], &path->points[0]);
                    func_00282F20(velocity, velocity, D_L17_001B0220 * 0.016666668f);
                } else {
                    func_002A7750(moby, 5, -1);
                    velocity = &vars->velocity;
                    point = path->count - 2;
                    vars->point = point;
                    func_00282CF0(velocity, &path->points[point], &path->points[point + 1]);
                    func_00282F20(velocity, velocity, D_L17_001B0220 * 0.016666668f);
                }
                break;
            }
        }
        if (moby->position.f[2] + 10.0f < D_00189E20.moby->position.f[2] && vars->atLast) {
            qcopy(&moby->position, &path->points[0]);
            vars->atLast = 0;
        } else if (D_00189E20.moby->position.f[2] < moby->position.f[2] - 10.0f && !vars->atLast) {
            qcopy(&moby->position, &path->points[path->count - 1]);
            vars->atLast = 1;
            moby->position.f[2] += 0.2f;
        }
        break;

    case 4:
        /* Leaving the first point. */
        if (func_002B3868(moby))
            func_L00_002D40A0(&moby->position, 0, moby->rotation.f[2]);
        if (func_L00_002D40F0() == 1)
            goto finish;
        func_002A7750(moby, 1, -1);
        break;

    case 5:
        /* Leaving the last point. */
        if (func_002B3868(moby))
            func_L00_002D40A0(&moby->position, 0, moby->rotation.f[2]);
        if (func_L00_002D40F0() == 1)
            goto finish;
        func_002A7750(moby, 3, -1);
        break;

    case 1:
        /* Travelling to the last point. */
        if (func_002B3868(moby))
            vars->verticalSpeed = 0.0f;
        {
            SoundVoice *voice = (SoundVoice *)&D_00188660[vars->sound];

            if (voice->owner != moby || !voice->active)
                vars->sound = func_002E5CF8(0, 4, moby);
        }
        if (func_L06_003E3ED0(moby)) {
            D_00189E20.f212 = 4;
            D_00189E20.f214 = 4;
            func_L17_003C3250(moby);
            if (!vars->hasRecord) {
                float *record = func_L00_002D70A0(5);
                float value;

                vars->record = record;
                if (record) {
                    vars->hasRecord = 1;
                    record[0] = D_L17_001B0228;
                    value = D_L17_001B022C;
                    vars->record[1] = value;
                    vars->record[3] = D_L17_001B0234;
                }
            }
        }
        func_002AA548(&moby->position.f[2], &vars->verticalSpeed,
                      path->points[path->count - 1].f[2], 0.0019444445f, 0.003888889f, 0.5f);
        if (func_00282C48(moby->position.f[2] - path->points[path->count - 1].f[2]) < 0.2f) {
            func_002A7750(moby, 0, -1);
            sound = vars->sound;
            if (sound != -1) {
                SoundVoice *voice = (SoundVoice *)&D_00188660[sound];

                if (voice->owner == moby && voice->active)
                    func_002E59F8(sound);
            }
            vars->sound = -1;
            if (vars->hasRecord) {
                func_L00_002D7140(vars->record);
                vars->hasRecord = 0;
            }
            vars->atLast = !vars->atLast;
        }
        break;

    case 2:
        /* Stopped: when the count runs out, head back to the first point. */
        sound = vars->sound;
        if (sound != -1) {
            SoundVoice *voice = (SoundVoice *)&D_00188660[sound];

            if (voice->owner == moby && voice->active)
                func_002E59F8(sound);
        }
        vars->sound = -1;
        if (func_00282978(&vars->atLast)) {
            func_002A7750(moby, 5, -1);
            velocity = &vars->velocity;
            point = vars->point - 1;
            vars->point = point;
            func_00282CF0(velocity, &path->points[point], &path->points[point + 1]);
            func_00282F20(velocity, velocity, D_L17_001B0220 * 0.016666668f);
        }
        break;

    case 3:
        /* Travelling to the first point. */
        if (func_002B3868(moby))
            vars->verticalSpeed = 0.0f;
        {
            SoundVoice *voice = (SoundVoice *)&D_00188660[vars->sound];

            if (voice->owner != moby || !voice->active)
                vars->sound = func_002E5CF8(0, 4, moby);
        }
        if (func_L06_003E3ED0(moby)) {
            D_00189E20.f212 = 4;
            D_00189E20.f214 = 4;
            func_L17_003C3250(moby);
            if (!vars->hasRecord) {
                float *record = func_L00_002D70A0(5);
                float value;

                vars->record = record;
                if (record) {
                    vars->hasRecord = 1;
                    record[0] = D_L17_001B0228;
                    value = D_L17_001B022C;
                    vars->record[1] = value;
                    vars->record[3] = D_L17_001B0234;
                }
            }
        }
        func_002AA548(&moby->position.f[2], &vars->verticalSpeed,
                      path->points[0].f[2], 0.0019444445f, 0.003888889f, 0.5f);
        if (func_00282C48(moby->position.f[2] - path->points[0].f[2]) < 0.2f) {
            vars->atLast = 0;
            func_002A7750(moby, 0, -1);
            if (vars->hasRecord) {
                func_L00_002D7140(vars->record);
                vars->hasRecord = 0;
            }
            sound = vars->sound;
            if (sound != -1) {
                SoundVoice *voice = (SoundVoice *)&D_00188660[sound];

                if (voice->owner == moby && voice->active)
                    func_002E59F8(sound);
            }
            vars->sound = -1;
        }
        break;
    }

finish:
    if (!func_L06_003E3ED0(moby) && vars->hasRecord) {
        func_L00_002D7140(vars->record);
        vars->hasRecord = 0;
    }
    func_00282CF0(&delta, &moby->position, &old);
    func_002AD6F0(vars->motion, &delta, &moby->rotation, &moby->rotation);
}
