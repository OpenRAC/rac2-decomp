#include "include_asm.h"

#include "common.h"
typedef unsigned int Quad __attribute__((mode(TI)));
typedef struct {
    char x[10];
} Sequence;
extern Sequence D_L06_001AF700;
extern int D_001A79F0;
extern u8 D_0018C0D4 NOT_SDA;
extern char D_L06_001B9840[];
typedef struct {
    u8 pad[0x74];
    u8 active;
    u8 pad75[0x13];
    char *owner;
} Effect;
extern u8 D_00188660[];
extern void func_0026FEB8(char *, ...);
extern void func_0029F338(char *);
extern int func_002A77E0(int);
extern float func_00283B98(float, float);
extern int func_00283CF0(float);
extern float func_00282C10(float);
extern float func_00282E48(void *, void *);
extern int func_00283DB8(void *, float);
extern void func_L00_002E6EF8(void *, void *);
extern int func_002E59B0(void *, int);
extern int func_002E5CF8(int, int, void *);
extern void func_00282948(void *);
extern void func_002E59F8(int);
typedef struct {
    float radius;
    int count;
    float step;
    int valid;
    u8 order[0x20];
    int effect;
    int timer;
} Data;
typedef struct {
    char pad0[0x20];
    u8 state;
    char pad21[0xF];
    u8 mode;
    char pad31[3];
    u16 flags;
    char pad36[0x32];
    Data *data;
    char pad6C[0x8C];
    float angle;
} Object;
extern char D_L06_001AFFA0[], D_L06_001AFFE0[];
extern Sequence D_L06_001B0000;
extern float D_L06_001AFF20 __attribute__((sda));
extern void func_PAL_L06_004046D8(void);

INCLUDE_ASM("asm/pal/levels", func_PAL_L06_004042F8);

