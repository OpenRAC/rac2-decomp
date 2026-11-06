/* func_PAL_00303548, the PAL copy of func_00302440: the same C, where rename func_003022A0 becomes func_PAL_003033A8. */

#define RAC2_T_V4_F213135AA
#define RAC2_T_WORKER_F9E2CD219
#define RAC2_T_OWNER_F9E2CD219

typedef int s32;

typedef unsigned char u8;

typedef unsigned int u32;

typedef float f32;

typedef struct {
    u8 field00[6];
    short field06;
    u8 field08[4];
    f32 field0C;
    u32 field10;
    u32 field14;
    u32 field18;
    u32 field1C;
    u32 field20;
} NativeCompactHeader;

typedef struct { float x, y, z, w; } V4_F213135aa;

    extern void func_0029FCC0(void *, int, void *);

    extern int func_00277258(void *, int, void *, float);

    extern int D_001BAF9C;

extern void func_00282D30(void *, void *, float);
extern V4_F213135aa ref_00303210_00[];
extern void func_00300330(void *);

extern int func_00282948(void *);

extern void func_00305798(void *);

extern void func_0029FCC0(void *, int, void *);

extern int func_00277258(void *, int, void *, float);

extern int D_001BAF9C;

extern void func_00300330(void *);

extern int func_00282948(void *p);

typedef struct {
    u8 pad00[0x80]; float position[4];
    u8 pad90[0x288]; float previousHeight;
    u8 pad31C[0x1514]; char *field1830;
    u8 pad1834[0xA5C]; char *field2290; int state;
    u8 pad2298[0x1C]; u8 field22B4;
} SurfacePlayer;
extern SurfacePlayer D_00189E20;
typedef struct {
    u8 pad000[0x140]; float position[4];
    u8 pad150[0x3C8 - 0x150]; float heightOffset;
} SurfaceCamera;
extern SurfaceCamera D_001B5200;
extern V4_F213135aa ref_00302DA0_04[];
/* Relocates serialized header offsets and compacts each row in its original storage. */

#ifndef RAC2_T_V4_F213135AA
#endif

#ifndef RAC2_T_WORKER_F9E2CD219
#endif

#ifndef RAC2_T_OWNER_F9E2CD219
#endif

/* relocates serialized offsets and compacts16-byte rows in their original storage using captured sourcewords */
NativeCompactHeader *func_00300618(NativeCompactHeader *header);

/* func_00300AA8 is in 00300618-draw-g8.c. */

/* scales a float argument by a field of the object into a stack buffer, then calls a second routine with the object, its flags, the buffer and three float arguments */
/* func_00300AA8 is defined in 00300618-draw-g8.c. */

/* func_00300F58 is defined in 00300F58-g8.c. */

int func_PAL_003033A8(char *obj, char *obj2, float x, float y);

int func_PAL_00303548(char *obj, char *obj2)
{
    if (*(u8 *)(obj + 32) != 3)
        return 3;
    return func_PAL_003033A8(obj, obj2, 0.0f, 0.0f);
}

/* func_00302A20 uses the quadword-copy profile in 00300618-qcopy.c. */

/* func_00302A88 uses the debug profile in 00300618-state.c. */

/* Resolve the player onto the surface grid and blend their height into it. */
typedef unsigned long long u64;

extern unsigned long func_0027C878(int);
extern void func_00280B90(void *, void *, int);

/* Regenerate the 8 by 8 mesh from four surface control points. */
/* func_00303568 is defined in 00303568.c. */

/* func_00303E20 is defined in 00303E20.c. */

/* func_00304128 is defined in 00304128.c. */

/* func_00304210 is defined in 00304210-g8.c. */

/* func_00304AD0 uses the profile in 00304AD0-g8-qcopy.c. */

/* Takes the position of the owner's child, and lets the child's motion take it over
   once the motion is of the right kind and is not busy. */
/* func_00304D38 is defined in 00304D38-g8.c. */

/* func_00305058 is defined in 00305058-qcopy.c. */

/* The table of hundred objects and the three helpers it uses sit at another
   address in every program, so they have no address of their own. */

/* Walks the table of objects and lets every entry the owner owns move it. */
void func_00305798(void *owner);

typedef struct { float x, y, z, w; } EffectVector __attribute__((aligned(16)));
typedef struct { u8 prefix[0x140]; EffectVector position; } EffectCameraView;
extern unsigned long func_0027C878(int);
extern void func_00282D30(void *, void *, float);
extern void func_00280B90(void *, void *, int);

extern EffectCameraView ref_00305910_00;

/* Draw three shrinking, independently colored layers facing the camera. */
extern EffectCameraView ref_00306040_00;
/* Packet initialization has distinct boot and level catalogue identities. */
/* Draw three shrinking, independently colored layers facing the camera. */
/* func_00307298 uses the profile in 00307298-g8-qcopy.c. */

/* The same as func_00304C78: the retail holds the two copies byte for byte the same. */
/* func_00307500 is defined in 00307500-g8.c. */

extern EffectCameraView ref_00307CC0_00;

/* Draw three shrinking, independently colored layers facing the camera. */
