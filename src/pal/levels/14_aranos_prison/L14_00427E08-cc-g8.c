/* func_PAL_L14_00427E08, the PAL copy of func_L14_004228C0: the same C, where wrap D_L14_001B167C (({e}) * 1.2f). */
#include "common.h"

extern int func_00283D38(int a, int b, float c);
/* Plays one sound effect derived from the owner's state block and then queues the level jingle. */
/* Scans the four slot words at state+0x20; at the first one that is set and passes func_002ACBC8,
   makes sure the pool record at state+0x14 exists and writes D_L14_001B17B8/BC into its first two
   floats. If none passes, frees the record. */
/* The light object: state byte, an update flag, the visibility flags, its state block,
   a frame counter and a word cleared when it shuts down. */
/* Its state block: the beam level, the done flag and the sound slot. */
/* A sound slot as seen from D_00188660 plus 0x70 per slot number. */
extern int D_L14_001B17C0 SDATA(D_L14_001B17C0);
extern float D_L14_001B17C4 SDATA(D_L14_001B17C4);
extern float D_L14_001B17C8 SDATA(D_L14_001B17C8);
extern float D_L14_001B17D0 SDATA(D_L14_001B17D0);
extern float func_00283198(float);
/* A prison searchlight: waits for the alarm, sweeps while it lasts, then fades out. */
/* Resets the moby's scale when its model says so, then lets it fall or die. */
extern float D_L14_001B1678 __attribute__((sda));
extern float D_L14_001B167C __attribute__((sda));
extern int D_L14_001B1660 __attribute__((sda));
extern int D_L14_001B1668 __attribute__((sda));
extern int D_L14_001B1690 __attribute__((sda));
extern int D_L14_001B1694 __attribute__((sda));
extern float D_L14_001B1698 __attribute__((sda));
extern float D_L14_001B169C __attribute__((sda));
extern float D_L14_001B16A0 __attribute__((sda));
extern float D_L14_001B16A4 __attribute__((sda));
extern char D_L14_002594F0[][0x280];
extern void func_L14_004229A0(char *, char *, int, int, int, float, float, float);

void func_PAL_L14_00427E08(char *object) {
    char *state = *(char **)(object + 0x68);

    D_L14_001B1678 -= ((D_L14_001B167C) * 1.2f);
    if (D_L14_001B1678 <= -8.0f)
        D_L14_001B1678 += 8.0f;
    func_L14_004229A0(object, D_L14_002594F0[*(int *)(state + 0x38)],
        D_L14_001B1660, D_L14_001B1668, *(int *)(state + 0x2C) - 2,
        *(float *)(state + 0x40), *(float *)(state + 0x44), D_L14_001B16A0);
    func_L14_004229A0(object, D_L14_002594F0[*(int *)(state + 0x38)] + 0x140,
        D_L14_001B1690, D_L14_001B1694, *(int *)(state + 0x2C),
        D_L14_001B1698, D_L14_001B169C, D_L14_001B16A4);
}

extern float func_00283198(float a);
extern int func_00283D38(int a, int b, float c);

/* Steps the owner's state block, then blends the two colours its state asks for. */
/* The id-list walks below (func_L14_00426D18, func_L14_00428A08, func_L14_00428BA0) read
   D_L14_001B259C as a bare symbol, while the `sda` int above reaches the same word through $gp.
   The assembler takes the last `.extern` size it has seen: the second name's 12 bytes (bare
   `lui`/`lw`) must come after the 4 bytes of the int's, so these functions follow
   func_L14_00409B20. D_L14_001B25B8 is a plain int: its `.extern` comes last in the file, which
   leaves a load in a branch delay slot on $gp and every other load on `lui`/`lw`. */
/* Sets the flag bit (+0xBE, 4) of every entity in the id list the state's group word names,
   unless the word is -1. */
/* Overlays for an owner (L14Obj) and the state block it points to (L14Cfg); only the fields the
   next two functions touch are named. Typed member accesses are what give retail's order of the
   compare's two loads (the scalar global first): with `*(int *)(p + off)` casts the field load
   is scheduled ahead of it. */
typedef struct {
    char pad0[0x220];
    float vec[4];
    char pad1[0x324 - 0x230];
    float scale;
    float angle;
    float blend;
    int stamp;
} L14Cfg;

typedef struct {
    char pad0[0x20];
    unsigned char kind;
    unsigned char group;
    char pad1[0x31 - 0x22];
    unsigned char live;
    char pad2[0x68 - 0x32];
    L14Cfg *cfg;
    char pad3[0x78 - 0x6C];
    int tint;
    char pad4[0xAA - 0x7C];
    short cls;
} L14Obj;

typedef struct {
    int a;
    int b;
} L14ColorPair;

extern void func_L14_00428BA0(L14Obj *);
extern L14ColorPair D_L14_001B18C0[];
/* Advances the owner's pulse (the angle, then the blend it gives), tints the owner with the
   first colour pair and, when its stamp is not the current one, refreshes every live class-0x112B
   entity of its group (joint 0 position into +0x220, then the stamp) and queues
   func_L14_00428BA0 for the owner. */
/* D_L14_001B18D0 is only used for its address, taken through $gp. D_L14_001B18E0 is one 8-byte
   object: its first word is loaded in a branch delay slot (so on $gp), its second as a bare
   symbol, which is how retail loads the two colours. */
/* For every live class-0x112B entity in the owner's group, builds the marker's vector from the
   entity's size and stored position and hands it to func_L00_00325AE8 with the second colour
   pair blended by the entity's pulse. */
void func_L14_00428BA0(L14Obj *self);
