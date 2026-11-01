#include "include_asm.h"

#include "common.h"
typedef struct {
    char pad0[0x10];
    float pos[4];                    
    char pad20[0x20];
    unsigned char key;               
    unsigned char next_key;          
    char pad42[2];
    float blend;                     
    char pad48[0x19];
    unsigned char alpha;             
    char pad62;
    unsigned char flags;             
    char pad64[4];
    char *keys;                      
    char pad6C[0x3E];
    short type;                      
} SceneActor;
typedef struct {
    char pad0[0x30];
    int selected;                    
    int frame;                       
    int tick;                        
    int chunk;                       
    short end;                       
    short pad42;
    short count;                     
    short pad46;
    short wait;                      
    char pad4A[0x0E];
    int done;                        
    char pad5C[0x10];
    int start;                       
    int destination;                 
    char pad74[0x118];
    SceneActor *actors[17];          
} Scene2EB1E0;
typedef struct {
    char pad0[0x2290];
    SceneActor *focus;               
} Game2EB1E0;
typedef struct {
    char pad0[0x1A0];
    union {
        unsigned long long held;
        unsigned int words[2];
    } buttons;                       
} Input2EB1E0;
typedef struct {
    unsigned char pad0[0x0A];
    unsigned char x0A;
    unsigned char x0B;
    unsigned char pad0C[0x08];
    int x14;
} Global001A7A00;
extern Scene2EB1E0 D_001B8840;
extern Game2EB1E0 D_00189E20_9;
extern char D_00138180[];
#define INPUT ((Input2EB1E0 *)D_00138180)
extern char D_001A63A8_3[];
extern SceneActor *D_001B2148;
extern Global001A7A00 D_001A7A00 MACRO_ADDR;
extern int D_001A7478 MACRO_ADDR;
extern int D_001A79F0 MACRO_ADDR;
extern int D_001A7B90 MACRO_ADDR;
extern int D_001A8BB8 MACRO_ADDR;
extern float D_001B15A0 MACRO_ADDR;
extern void func_002F5220(void);
extern void func_002ED0A0(void);
extern int func_002B6D28(void);
extern void func_002B7CE0(int);
extern void func_002EB598(void);
extern int func_002EB158(int);
extern int func_002F5AF8(void);
extern void func_0029F390(void *);
extern float func_00283CE0(int);
extern void func_00282D30(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_US2_002E72D8(void *);
extern void func_002ECB70(void);
extern void func_0027CFD0(void *, void *);
extern void func_002A0F48(void *);
extern void func_0026F790(void *, int);
extern void func_002E4AC8(void);
extern void func_002914B8(void);
extern void func_002F52B8(void);

/* Advances the scripted scene one frame: fades in, lets the player skip once the fade is
   done, pages in the next chunk every 80 or 96 ticks and poses each actor between its two
   current keys. Returns 1 when the player skipped. */
int func_US2_002EC038(void)
{
    SceneActor *actor;
    float first[4], last[4];
    float fade;
    int skip, done, camera, i;

    if (D_001B8840.done)
        return 0;
    if (D_001B8840.frame + 1 >= D_001B8840.end) {
        D_001A8BB8 = 0;
        D_001B8840.done = 1;
        return 0;
    }
    func_002F5220();
    func_002ED0A0();
    fade = D_001B15A0 - 0.34f;
    D_001B8840.tick++;
    D_001B8840.frame++;
    D_001B15A0 = fade;
    if (fade < 0.0f)
        D_001B15A0 = 0.0f;
    if (D_001B8840.frame >= D_001B8840.wait)
        func_002B6D28();

    skip = 0;
    done = D_001B8840.frame >= D_001B8840.end;
    if (D_001B8840.frame >= 18 && D_001B15A0 == 0.0f) {
        if ((D_001A7A00.x0A || D_001A7A00.x0B || D_001A7478 || D_001A79F0 <= 0)
            && (INPUT->buttons.words[1] & 0x800))
            skip = 1;
        else if ((INPUT->buttons.held & 0x8000000000FULL) == 0x8000000000FULL)
            skip = 1;
    }

    if (skip || done) {
        D_001B8840.done = 1;
        D_001A8BB8 = 0;
    } else {
        int ticks = D_001A7B90 ? 80 : 96;
        if (D_001B8840.tick >= ticks) {
            D_001B8840.chunk++;
            if (*(short *)(D_001A63A8_3 + 4))
                func_002B7CE0(1);
            func_002EB598();
            func_002EB158(D_001B8840.chunk + 1);
        }
        camera = func_002F5AF8();
        for (i = 0; i < D_001B8840.count; i++) {
            char *keys;
            int key, type;

            actor = D_001B8840.actors[i];
            key = D_001B8840.tick >> 1;
            actor->next_key = key + 1;
            actor->key = key;
            func_0029F390(actor);
            actor->blend = func_00283CE0(D_001B8840.tick & 1) * 0.5f;
            if (camera && (D_001B8840.tick & 1))
                actor->blend = 1.0f;
            keys = actor->keys;
            func_00282D30(first, keys + actor->key * 16, 1.0f - actor->blend);
            func_00282D30(last, keys + actor->next_key * 16, actor->blend);
            func_00282CC0(actor->pos, first, last);
            type = actor->type;
            if (type == 0xD54) {
                actor->flags = 8;
                func_US2_002E72D8(actor);
                if (!D_001B2148 || D_001B2148->type == type)
                    func_0027CFD0(func_002ECB70, actor);
            }
            actor->alpha = 255;
            func_002A0F48(actor);
            if (actor->type == 0) {
                D_00189E20_9.focus = actor;
                func_0026F790(actor, 1);
            }
        }
    }
    func_002E4AC8();
    func_002914B8();
    func_002F52B8();
    return skip;
}
