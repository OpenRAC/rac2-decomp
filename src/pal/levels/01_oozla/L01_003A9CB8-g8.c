#include "include_asm.h"

#include "common.h"
typedef struct {
    u8 pad00[0x10];
    float position[4];           
    u8 state;                    
    u8 pad21[0x68 - 0x21];
    void *vars;                  
    u8 pad6C[0x78 - 0x6C];
    u32 color;                   
    u8 pad7C[0xB0 - 0x7C];
    u8 mission;                  
    u8 padB1;
    u16 uid;                     
    u8 padB4[0xBC - 0xB4];
    u8 fBC;                      
} Moby;
typedef struct {
    int path;                    
    float tag;                   
    int byMission;               
    float phase;                 
} ButtonVars;
typedef union {
    int count;
    struct {
        float position[3];
        float tag;               
    } point;
} PathSlot;
typedef struct {
    u8 pad000[0x464];
    u8 byUid[0];                 
} ProgressFlags;
typedef struct {
    u8 pad000[0x33C];
    void *groundMoby;            
    u8 pad340[0x34E - 0x340];
    short f34E;                  
} Hero;
extern u8 D_0019B4A8[];
extern u8 D_0019B2E8[][16];
extern ProgressFlags D_L00_0021DDB0;
extern int D_001A79F0 __attribute__((sda));
extern PathSlot *D_L00_001FDA80[];
extern Hero D_00189E20;
extern float func_002A7940(void);
extern float func_00283B98(float angle, float delta);
extern float func_00283198(float angle);
extern int func_00283CF0(float value);
extern int func_002E5CF8(int sound, int, void *moby);
/* Clears the tag of each point of the button's path that carries the button's tag. */
static __inline__ void ClearPathTags(ButtonVars *vars)
{
    PathSlot *slot;
    int list;
    int i;

    list = vars->path;
    if (list != -1) {
        i = 0;
        if (D_L00_001FDA80[list]->count > 0) {
            do {
                slot = D_L00_001FDA80[list] + i;
                if (slot[1].point.tag == vars->tag)
                    slot[1].point.tag = 0.0f;
                list = vars->path;
                ++i;
            } while (i < D_L00_001FDA80[list]->count);
        }
    }
}

/* A floor button: sinks into place, then glows until the hero stands on it (or its mission
   is complete), then counts the press in the level's progress and unblocks its path. */
void func_PAL_L01_003B55C4(Moby *moby)
{
    ButtonVars *vars = moby->vars;
    u8 *counter;
    int count;
    int intensity;
    u32 grey;
    u32 alphaGreen;
    u32 blue;
    short id;
    u16 uid;
    u8 value;

    switch (moby->state) {
    case 0:
        /* Settle into the floor; start pressed if it was pressed before or its mission is done. */
        vars->phase = func_002A7940();
        id = moby->uid;
        moby->position[2] -= 0.35f;
        if (!D_L00_0021DDB0.byUid[id]) {
            count = D_0019B4A8[(id >> 1) + D_001A79F0 * 0x400];
            if (moby->uid & 1)
                count = (count >> 4) & 7;
            else
                count &= 7;
            if (!count && !(vars->byMission && (D_0019B2E8[D_001A79F0][moby->mission] & 0x80)))
                goto waiting;
        }
        moby->fBC = 2;
        moby->color = 0x80208020;
        moby->state = 2;
        ClearPathTags(vars);
        return;
waiting:
        moby->state = 1;
        return;

    case 1:
        /* Pulse the glow between 32 and 128. */
        vars->phase = func_00283B98(vars->phase, 0.12566373f);    /* 6 degrees a frame */
        intensity = func_00283CF0((func_00283198(vars->phase) * 4.0f - 3.0f) * 128.0f);
        if (intensity > 128)
            intensity = 128;
        else if (intensity < 32)
            intensity = 32;
        grey = (u32)intensity;
        alphaGreen = 0x80000000 | (grey << 8);
        blue = grey << 16;
        moby->color = blue | alphaGreen | grey;

        /* Wait for the hero to stand on the button, or for its mission. */
        if (D_00189E20.groundMoby != moby || D_00189E20.f34E) {
            if (!vars->byMission)
                return;
            if (!(D_0019B2E8[D_001A79F0][moby->mission] & 0x80))
                return;
        }

        /* Count the press (up to 7), then unblock the path. */
        uid = moby->uid;
        if (uid & 1) {
            counter = &D_0019B4A8[((short)uid >> 1) + D_001A79F0 * 0x400];
            value = *counter;
            if (((value >> 4) & 7) != 7)
                *counter = value + 0x10;
        } else {
            counter = &D_0019B4A8[((short)uid >> 1) + D_001A79F0 * 0x400];
            value = *counter;
            if ((value & 7) != 7)
                *counter = value + 1;
        }
        moby->state = 2;
        moby->fBC = 1;
        moby->color = 0x80208020;
        func_002E5CF8(0, 0, moby);
        ClearPathTags(vars);
    }
}
