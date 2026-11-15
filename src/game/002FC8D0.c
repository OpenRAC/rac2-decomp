#include "common.h"

extern char ref_L00_002FE8D8_00[];
extern int ref_L00_002FE8D8_01 __attribute__((sda));
extern float ref_L00_002FE8D8_02[];
extern int ref_L00_002FE8D8_03 __attribute__((sda));
extern void func_00282F20(float *, float *, float);
extern void func_00282C98(float *);

/* lot10: privately byte-gated bodies. */
extern s32 func_00126470(u8 *, s32, s32, s32, s32, s32, s32, s32);

extern s32 func_0011AEA0(s32);

extern s32 func_00126730(u8 *, u8 *);

extern s32 func_001244B8(s32, s32);

/* Family d50cdefed4015bae — 364 bytes, a 16384-byte block loop that builds two
   four-word GS packets per iteration and calls the measured SDK helper at
   0x00126288 in between.

   The resident write pointer at 0x001B3D08 is read ten times and stored three
   times.  Two authored views of that one measured cell are needed and are the
   qualified form here:
     * the read view is volatile, so every use is a fresh load -- the retail
       body re-loads the cell before every field store (aliasing through the
       loaded pointer is not enough to force it: without the qualifier cc1
       forwards a stored value into the next two reads);
     * the write view is an ordinary pointer, so the store written before the
       call is moved into the `jal` delay slot, which is where retail keeps it
       (a volatile store is left in place).
   The bare symbols keep the address materialisation a per-site assembler job
   (`lui`+`lw` mid-stream, the single `$gp` form in a delay slot).

   -G0 promotion (agent f02, 2026-10-07): under -G8 these two declarations need
   no attribute, because -G8 alone puts the cell in small data.  Under -G0 cc1
   would otherwise model each access as an explicit `lui`+`lw` pair, hoist the
   base into a callee-saved register and reuse it, which changes both the
   register allocation and the body size.  The measured `sda` attribute puts
   cc1 back on the one-instruction model, so gas expands every site exactly as
   the retail build did: absolute `lui`+`lw` in ordinary flow, the single `$gp`
   form inside the `.set nomacro` region cc1 emits for the `jal` delay slot.
   Nothing else about the body changed. */

extern int *volatile D_L02_001B3D08_3 __attribute__((sda));

extern int *D_L02_001B3D08_5 __attribute__((sda));

extern void D_00126288(int *a0, int a1, int a2, int a3, int a4, int a5, int a6, int a7);

extern int D_L03_001B31A0 __attribute__((sda));

extern int D_L03_001B31A4 __attribute__((sda));

extern void func_0011A950(int, int);

extern void func_0011B658(int);

/* Measured partial layouts; original type and game roles are unknown. */
typedef unsigned int Rac2Native_74a5d71aacb394c6_u32;

typedef struct {
    Rac2Native_74a5d71aacb394c6_u32 first[64];
    Rac2Native_74a5d71aacb394c6_u32 second[64];
    unsigned char gap[0x20];
    int count;
    Rac2Native_74a5d71aacb394c6_u32 current;
} Rac2Native_74a5d71aacb394c6_ExtraIndexState48;

extern int D_L03_002325D0[];

/* Copies a block of image data from the console memory to the graphics chip in 16 KB pieces. */
void func_002FC8D0(u8 *dest, s32 vramAddr, s32 size) {
    u8 image[112];
    s32 remaining = (size + 0x3fff) & ~0x3fff;
    s32 srcOffset = 0, dstOffset = 0;
    for (; remaining > 0; remaining -= 0x4000) {
        func_00126470(image, (s32)(short)((vramAddr+srcOffset)>>8), 1, 1, 0, 0, 64, 64);
        srcOffset += 0x4000;
        FlushCache(0);
        func_00126730(image,dest+dstOffset);
        dstOffset += 0x3000;
        WaitGsPathsIdle(0,0);
    }
}
/* shared native body of family d50cdefed4015bae (default profile) */
/* Uploads image data to the graphics chip in 16 KB pieces by writing DMA packets. */
void func_002FC990(int data, int vramAddr, int size)
{
    int remaining = (size + 16383) & -16384;
    int vramOffset = 0;
    int dataOffset = 0;

    while (remaining > 0) {
        *(int *)((char *)D_L02_001B3D08_3 + 0) = 0x10000006;
        *(int *)((char *)D_L02_001B3D08_3 + 4) = 0;
        *(int *)((char *)D_L02_001B3D08_3 + 8) = 0;
        *(int *)((char *)D_L02_001B3D08_3 + 12) = 0x50000006;
        {
            int *next = (int *)((char *)D_L02_001B3D08_3 + 16);
            D_L02_001B3D08_5 = next;
            D_00126288(next, (short)((vramAddr + vramOffset) >> 8), 1, 1, 0, 0, 64, 64);
        }
        vramOffset += 16384;
        remaining -= 16384;
        {
            int *p = D_L02_001B3D08_3;
            int off = data + dataOffset;
            dataOffset += 12288;
            D_L02_001B3D08_5 = (int *)((char *)p + 96);
            *(int *)((char *)p + 96) = 0x30000300;
            *(int *)((char *)D_L02_001B3D08_3 + 4) = off;
            *(int *)((char *)D_L02_001B3D08_3 + 8) = 0;
            *(int *)((char *)D_L02_001B3D08_3 + 12) = 0x50000300;
            D_L02_001B3D08_5 = (int *)((char *)D_L02_001B3D08_3 + 16);
        }
    }
}

extern int func_00282A18(int);

/* Uploads a texture to the graphics chip in blocks and returns the texture setup value for it. */
long long func_002FCB00(int data, int destination, int width, int height)
{
    int block = width << 7;
    int offset = 0;
    int logwidth = log2dim(width);
    int logheight = log2dim(height);
    int width_mask = width & (width - 1);
    int height_mask = height & (height - 1);
    int remaining = width * (height << 2);

    if (width_mask)
        logwidth++;
    if (height_mask)
        logheight++;
    {
        int rounded = remaining - 1;
        rounded += block;
        remaining = rounded & -block;
    }
    if (remaining > 0) {
        int buffer_width = (width >> 6) << 16;
        int image_width = width << 16;
        int dma_tag = (block >> 4) | 0x30000000;
        int vif_tag = (block >> 4) | 0x50000000;

        do {
            int *next;
            int *cursor;
            int source;
            *(int *)((char *)D_L02_001B3D08_5 + 0) = 0x10000006;
            *(int *)((char *)D_L02_001B3D08_5 + 4) = 0;
            *(int *)((char *)D_L02_001B3D08_5 + 8) = 0;
            *(int *)((char *)D_L02_001B3D08_5 + 12) = 0x50000006;
            next = D_L02_001B3D08_5 + 4;
            D_L02_001B3D08_5 = next;
            remaining -= block;
            D_00126288(next, (short)((destination + offset) >> 8), buffer_width >> 16,
                       0, 0, 0, image_width >> 16, 32);
            cursor = D_L02_001B3D08_5;
            source = data + offset;
            offset += block;
            D_L02_001B3D08_5 = cursor + 24;
            *(int *)((char *)cursor + 96) = dma_tag;
            *(int *)((char *)D_L02_001B3D08_5 + 4) = source;
            *(int *)((char *)D_L02_001B3D08_5 + 8) = 0;
            *(int *)((char *)D_L02_001B3D08_5 + 12) = vif_tag;
            D_L02_001B3D08_5 = (int *)((char *)D_L02_001B3D08_5 + 16);
        } while (remaining > 0);
    }
    {
        long long result = destination >> 8;
        result |= (long long)(width >> 6) << 14;
        result |= (long long)logwidth << 26;
        result |= (long long)logheight << 30;
        result |= 0x400000000LL;
        return result;
    }
}


/* The guard reads the cell at 0x001B22C0/0x001B22C4: the read view is volatile (every use is a
   fresh load), and the write of the initialiser's result is an ordinary store, which is what
   leaves the first call's `lui` in the `bne` delay slot instead of duplicating it.  Both cells
   are reached with retail's one-instruction macro form, so they carry the `sda` attribute. */
extern int D_001B22C0 __attribute__((sda));

extern int D_001B22C4 __attribute__((sda));

extern void func_002FCE18(void);

extern void func_002FCF18(void);

extern int func_0011A930(int, void (*)(void), int);

extern void func_0011B6C0(int);

/* Installs the two DMA interrupt handlers, once. */
void func_002FCD18(void)
{
    if (D_001B22C0 != 0) {
        return;
    }
    if (D_001B22C4 != 0) {
        return;
    }
    if ((D_STAT & 0x20000) == 0) {
        *(unsigned int *)0x1000E010 = 0x20000;
    }
    D_001B22C0 = AddDmacHandler(1, HandleVif1DmaInterrupt, 0);
    D_001B22C4 = AddDmacHandler(15, HandleDmaErrorHang, 0);
    ProcessKernelQueueEntryD(1);
}

/* shared native body of family 349daa693c44d158 */
/* Removes the two DMA interrupt handlers and clears their ids. */
void func_002FCDA8(void)
{
    if ((D_STAT & 0x20000) != 0) {
        D_STAT = 0x20000;
    }
    RemoveDmacHandler(1, D_L03_001B31A0);
    RemoveDmacHandler(15, D_L03_001B31A4);
    ProcessKernelQueueEntryC(1);
    D_L03_001B31A0 = 0;
    D_L03_001B31A4 = 0;
}

ASM_FUNC("asm/game", func_002FCE18);


#define MACRO_ADDR __attribute__((section(".sdata")))

/*
 * The VU1 chain state. r1_D_00161000 (the write pointer), r1_D_00161010 (the
 * buffer index) and the two limits r1_D_0015F718/r1_D_0015F71C are all reached
 * with retail's one-instruction macro form, so they are MACRO_ADDR: the
 * assembler expands them through $at, or through $gp where the access
 * lands in a delay slot.
 */
extern int *r1_D_00161000 MACRO_ADDR;

/*
 * Append one quadword to the packet at r1_D_00161000. This one wants the
 * pointer typed as a quadword: stepping an `int *` by 4 folds the copy
 * retail keeps (`daddu $5,$2,$0`) into the increment and comes out one
 * instruction short, so the same symbol is declared a second time under
 * a quadword type.
 */
typedef struct {
    int w[4];
} Qword_r002FCF90;

extern Qword_r002FCF90 *r1_D_00161000_q __asm__("r1_D_00161000") MACRO_ADDR;

/* rac1-decomp src/game/vuchain.c: func_00235290 */
/* Appends a packet header word (tag) to the vector unit packet list. */
void func_002FCF90(int tag) {
    Qword_r002FCF90 *p = r1_D_00161000_q++;
    p->w[0] = tag + 0x90000000;
    p->w[1] = 0;
    p->w[2] = 0;
    p->w[3] = 0;
}

/* func_002FCFC8 is in 002FC8D0-g8.c. */

/* func_002FD1B8 is in 002FC8D0-disturb-g8.c. */

/* func_002FD828 is in its own G8 unit. */


/* func_002FDBD8 is in 002FC8D0-billboard-g8.c. */

/* func_002FDF40 is in 002FDF40-g8.c. */

/* func_002FE5A0 is in its own G8 unit. */

extern void func_002FE8D8(void *, float *);
extern void func_00282D30(float *, float *, float);
extern void func_00282CF0(float *, float *, float *);

/* Adds a scaled copy of the direction vector for an object onto another vector. */
void func_002FE880(void *object, float *destination, float scale)
{
    float vector[4];
    GetObjectFacingDirection(object, vector);
    FastVecScale(vector, vector, scale);
    FastVecSub(destination, destination, vector);
}

/* Works out the up or facing direction for an object, depending on the player's state. */
void func_002FE8D8(void *object, float *destination)
{
    char *state = ref_L00_002FE8D8_00;
    if (*(short *)(state + 0x348)) {
        if (!ref_L00_002FE8D8_01) {
            qcopy(destination, *(char **)(state + 0x2290) + 0xE0);
            return;
        }
    }
    if (ref_L00_002FE8D8_01) {
        FastVecSub(destination, ref_L00_002FE8D8_02, object);
        destination[2] = 0;
        vec_scale_to_length(destination, destination, 1.0f);
    } else if (ref_L00_002FE8D8_03) {
        float sign = 1.0f;
        if (*(float *)(state + 0xBC) > 0.0f) sign = -1.0f;
        FastVecSub(destination, (float *)(state + 0xB0), object);
        vec_scale_to_length(destination, destination, sign);
    } else {
        VectorCopyHelperA(destination);
    }
}

/* A sphere moved along a velocity and tested for collisions: the contact
   normal, the position and velocity it updates, the moby it belongs to (then
   the moby it hit) and the ids of mobys to ignore. Field names describe how
   func_002FE9D0 uses them. */
typedef struct {
    float normal[4];
    float position[4];
    float velocity[4];
    char *moby;
    int *ignoredIds;
    int ignoredCount;
    float radius;
    float bounce;
    float minFacing;
    int pad48;
    int collisionFlags;
    int slideOnCreatures;
    int surface;
    int useOffset;
    float offset;
} SweptSphere;

/* The collision queries' output: the moby hit, the contact point, the
   sphere centre at contact and the surface normal. */
typedef struct {
    char pad[0x18];
    char *moby;
    int pad1C;
    float point[4];
    float center[4];
    float normal[4];
} CollisionOutput;

extern CollisionOutput ref_L00_002FE9D0_00;
extern void func_002FE8D8(void *, float *);
extern void func_00282F20(float *, float *, float);
extern void func_00282D30(float *, float *, float);
extern void func_00282CF0(float *, float *, float *);
extern void func_00282CC0(float *, float *, float *);
extern void func_00283028(float *, float *, float *);
extern float func_00282DB0(float *, float *);
extern int func_00277258(float, float *, int, void *);
extern int func_002761F8(void *, void *, int, void *, int);
extern int func_00278E78(void);

/* One collision step: tests the sphere (or a point offset from it) and,
   on a hit that is not ignored, moves it to the contact and either bounces
   its velocity off the surface, scaling the normal part by `bounce`
   (returns 1), or stops it at the contact point (returns 2); 0 otherwise. The query pointer and the
   separate dot product statement give retail's register use. */
int func_002FE9D0(SweptSphere *sphere)
{
    float facing[4] __attribute__((aligned(16)));
    float point[4] __attribute__((aligned(16)));
    float along[4] __attribute__((aligned(16)));
    float across[4] __attribute__((aligned(16)));
    float *position;
    float *query;
    float *velocity;
    float dot;
    int result = 0, hit, i;
    char *moby;

    GetObjectFacingDirection(sphere->moby + 0x10, facing);
    if (sphere->useOffset) {
        vec_scale_to_length(point, (float *)(sphere->moby + 0xE0), sphere->offset);
        FastVecAdd(point, sphere->position, point);
        position = sphere->position;
        query = point;
    } else {
        qcopy(point, sphere->position);
        query = point;
        position = sphere->position;
    }
    hit = TestPointAgainstCollision(sphere->radius, query, sphere->collisionFlags, sphere->moby);
    if (hit) {
        hit = 1;
    } else {
        hit = 0;
        if (CollLine(sphere, position, sphere->collisionFlags, sphere->moby, 0)) hit = 2;
    }
    sphere->moby = 0;
    if (hit) {
        sphere->surface = GetCollHitMaterial();
        moby = ref_L00_002FE9D0_00.moby;
        if (moby) {
            for (i = 0; i < sphere->ignoredCount; i++) {
                if (*(short *)(moby + 0xAA) == sphere->ignoredIds[i]) return 0;
            }
            sphere->moby = ref_L00_002FE9D0_00.moby;
        }
        if (hit == 1) qcopy(position, ref_L00_002FE9D0_00.center);
        else qcopy(position, ref_L00_002FE9D0_00.point);
        FastVecScale(sphere->normal, ref_L00_002FE9D0_00.normal, 0.0009765625f);
        vec_scale_to_length(sphere->normal, sphere->normal, 1.0f);
        if (FastVecDot(facing, sphere->normal) < sphere->minFacing ||
            (sphere->moby && *(short *)(*(char **)(sphere->moby + 0x24) + 0x46) == 5 &&
             sphere->slideOnCreatures)) {
            velocity = sphere->velocity;
            FastVectorNormalize(velocity, velocity, sphere->normal);
            result++;
            dot = FastVecDot(velocity, sphere->normal);
            FastVecScale(along, sphere->normal, dot);
            FastVecSub(across, velocity, along);
            FastVecScale(velocity, along, sphere->bounce);
            FastVecAdd(velocity, across, velocity);
        } else {
            qcopy(position, ref_L00_002FE9D0_00.point);
            result = 2;
        }
    }
    return result;
}

extern char D_0021F9C0[];

/* Returns slot number index of the 64-slot table, or nothing if out of range. */
void *func_002FEC50(int index) {
    void *result = 0;
    if ((unsigned int)index < 64u)
        result = D_0021F9C0 + index * 0x50;
    return result;
}

extern void func_0029F978(unsigned char *, unsigned int, unsigned char *);

/* Finds a free slot in the 64-slot table, sets it up for an object and returns its number. */
int func_002FEC78(unsigned char *object, unsigned int flags)
{
    char *p = D_0021F9C0;
    int i = 0;
    do {
        if (*(unsigned char **)(p + 0x40) != 0) {
            i++;
            p += 0x50;
            continue;
        } else {
            *(int *)(p + 4) = -1;
            *(unsigned char **)(p + 0x40) = object;
            p[3] = 0;
            p[0] = 0;
            *(int *)(p + 0xC) = 0;
            *(int *)(p + 8) = 0;
            *(int *)(p + 0x10) = 0;
            *(int *)(p + 0x14) = 0;
            *(int *)(p + 0x18) = 0;
            *(int *)(p + 0x1C) = 0;
            *(int *)(p + 0x30) = 0;
            *(int *)(p + 0x34) = 0;
            *(int *)(p + 0x38) = 0;
            *(int *)(p + 0x3C) = 0;
            p[2] = 0;
            *(int *)(p + 0x20) = 0;
            *(int *)(p + 0x24) = 0;
            *(int *)(p + 0x28) = 0;
            *(int *)(p + 0x2C) = 0;
            p[1] = 0;
            AttachManipulator(object, flags, (unsigned char *)p);
            break;
        }
    } while (i < 64);
    return i;
}

extern void func_0029F9F0(char *, char *);
/* Releases a slot of the 64-slot table. */
void func_002FED28(unsigned int index) { if (index < 64u) { char *p = D_0021F9C0 + index * 0x50; DetachManipulator(*(char **)(p + 0x40), p); *(char **)(p + 0x40) = 0; } }


/* func_002FED90 is matched in its own unit, src/game/002FED90-qcopy.c (-frac2-qcopy). */

extern char D_002212E0[];

/* Clears the flag word of one entry in a table of small records. */
void func_002FEE50(int index) {
    int *p;
    if (index < 0) return;
    p = (int *)((unsigned int)D_002212E0 + (index << 5));
    p[7] = 0;
}

/* func_002FEE70 is defined in 002FEE70.c. */


/* Does nothing. */
void func_002FF288(void)
{
}

extern void func_0029F0C8(void *, int);
extern void func_00282A60(unsigned int *, unsigned int, int);
extern void func_002A0F48(void *);
extern char *ref_L00_002FF290_00 __attribute__((sda));
extern char *ref_L00_002FF290_01 __attribute__((sda));
/* Sets up an object of the given kind and gives it a cleared 128-byte block of private data. */
void func_002FF290(char *object, int kind)
{
    char *data;
    InitMobyInstance(object, kind);
    data = ref_L00_002FF290_01 + (((int)object - (int)ref_L00_002FF290_00) >> 8) * 128;
    *(char **)(object + 0x68) = data;
    ClearMemory((unsigned int *)data, 0, 128);
    if ((*(unsigned short *)(object + 0x34) & 4) == 0)
        func_002A0F48(object);
}

/* func_002FF300 is matched in its own unit, src/game/002FF300.c (default flags). */

extern char *D_001B2348 __attribute__((sda));
extern void func_002FF290(char *, int);

/* Sets up the preview object so it is small, hidden at first and ready to show. */
void func_002FF3F8(void)
{
    char *object;
    InitObjectWithPrivateData(D_001B2348, 0x3EF);
    object = D_001B2348;
    *(unsigned char *)(object + 0x30) = 255;
    *(unsigned short *)(object + 0x34) |= 0x43;
    *(int *)(object + 0x98) = 0;
    *(float *)(object + 0x18) = 5.0f;
    *(float *)(object + 0x14) = 5.0f;
    *(float *)(object + 0x10) = 5.0f;
}

/* func_002FF450 is matched in its own unit, src/game/002FC8D0-preview.c (-g). */

/* The camera's eye position and view direction. */
typedef struct {
    char reserved00[0x140];
    float position[4];
    char reserved150[0x220];
    float forward[4];
} PreviewCameraPrefix;

/* State of the object preview. Retail reaches these fields at offsets from
   the start of one small-data object: each access is an absolute two-word
   macro that never fills a delay slot, while code elsewhere stores the
   first halfword through $gp. */
typedef struct {
    short s00;
    short frames;
    float rate;
    char pad08[0x34 - 0x08];
    unsigned char phase;
    unsigned char spin;
} PreviewState;

typedef struct {
    char reserved00[0x10];
    float position[4];
    char reserved20[0x8A];
    short classId;
    char reservedAC[0x44];
    float rotation[4];
} PreviewObjectPrefix;

extern PreviewCameraPrefix D_001B5200;
extern PreviewState D_001B2310 __attribute__((sda));
/* Distances along the preview's basis rows, separate small-data floats
   (retail loads D_001AD814 in a branch delay slot, so it is not an offset
   from a common base). */
extern float D_001AD808 SDATA(D_001AD808) __attribute__((sda));
extern float D_001AD80C SDATA(D_001AD80C) __attribute__((sda));
extern float D_001AD810 SDATA(D_001AD810) __attribute__((sda));
extern float D_001AD814 SDATA(D_001AD814) __attribute__((sda));
extern float D_001AD818 SDATA(D_001AD818) __attribute__((sda));
extern float func_00283B98(float, float);
extern void func_002833F0(float *, float *);
extern void func_00300048(void *);

/* Places the previewed object in front of the camera, turns it a little
   (about x when spinning, else about z) and offsets it along its own basis.
   The two spinning branches end in the same scale-and-add, which cc1's
   cross-jumping merges into one tail as in retail. */
void func_002FF968(PreviewObjectPrefix *object)
{
    float offset[4] __attribute__((aligned(16)));
    float basis[12] __attribute__((aligned(16)));
    float temporary[4] __attribute__((aligned(16)));
    int special = object->classId == 0xC5A /* Miniturret Glove */ || object->classId == 0xA65 /* Megaturret Glove */;
    int compact = 0;
    if (object->classId == 0x879 /* Chopper */ || object->classId == 0xAF6 /* Multi-Star */ ||
        object->classId == 0x907 /* Spiderbot Glove */ || object->classId == 0xE7A /* Tankbot Glove */ || special)
        compact = 1;
    if (special) {
        FastVecScale(offset, gActiveCamera.forward, 2.5f);
    } else if (compact) {
        FastVecScale(offset, gActiveCamera.forward, 2.0f);
    } else {
        FastVecScale(offset, gActiveCamera.forward, 3.0f);
    }
    FastVecAdd(object->position, gActiveCamera.position, offset);
    if (gObjectPreviewState.spin)
        object->rotation[0] = FastAddRotations(object->rotation[0], 0.03490659f);
    else
        object->rotation[2] = FastAddRotations(object->rotation[2], 0.03490659f);
    euler_rotation_basis(basis, object->rotation);
    if (gObjectPreviewState.spin) {
        if (compact) {
            FastVecScale(temporary, basis + 4, D_001AD818);
            FastVecAdd(object->position, object->position, temporary);
            FastVecScale(temporary, basis, D_001AD814);
            FastVecAdd(object->position, object->position, temporary);
        } else {
            FastVecScale(temporary, basis + 4, D_001AD80C);
            FastVecAdd(object->position, object->position, temporary);
            FastVecScale(temporary, basis, D_001AD808);
            FastVecAdd(object->position, object->position, temporary);
        }
    } else {
        FastVecScale(temporary, basis + 8, D_001AD810);
        FastVecAdd(object->position, object->position, temporary);
    }
    func_002A0F48(object);
    SpawnPreviewLightBurst(object);
}

/* func_002FFCF8 is in 002FC8D0-fade.c. */

typedef struct {
    float velocity[3], gravity, size_delta;
    unsigned char alpha_delta, phase_delta;
    unsigned short pad16;
    int pad18;
    void (*update)(char *);
} ParticleContext_C65A0;
typedef struct {
    unsigned char byte0, byte1, shade, kind;
    unsigned int color;
    unsigned char phase, variation;
    short timer;
    float size, position[4];
    ParticleContext_C65A0 context;
} Particle_C65A0;
extern float D_001AD81C SDATA(D_001AD81C) __attribute__((sda));
extern float D_001A8BD0[] MACRO_ADDR;
extern unsigned char *D_001F2614;
extern float func_00283CE0(int);
extern void func_00282D08(float *, float *, float *, float);
extern int func_00283CF0(float);
/* The particle constructor of 002BF6F0-c65a0.c, declared with its three
   float parameters after the first five integers (as 0032DD40-g8.c does):
   each register bank keeps its order, and retail sets up the arguments in
   this order. */
extern Particle_C65A0 *func_002C65A0(const float *, const float *, int, unsigned int, int, int, int,
                                   float, float, float, int);

/* Emits three particles between 0.1 and 9 units in front of the camera,
   at the point the preview timer has reached; their phase advances once
   per call. */
void func_002FFD78(void)
{
    float offset[4] __attribute__((aligned(16)));
    float farPoint[4] __attribute__((aligned(16)));
    float nearPoint[4] __attribute__((aligned(16)));
    float position[4] __attribute__((aligned(16)));
    int phase = gObjectPreviewState.phase;
    int secondPhase;
    float size, interpolation;
    Particle_C65A0 *particle;
    FastVecScale(offset, gActiveCamera.forward, 9.0f);
    FastVecAdd(farPoint, gActiveCamera.position, offset);
    FastVecScale(offset, gActiveCamera.forward, 0.1f);
    FastVecAdd(nearPoint, gActiveCamera.position, offset);
    interpolation = IntToFloat(gObjectPreviewState.frames) * gObjectPreviewState.rate;
    lerp_vector(position, nearPoint, farPoint, interpolation);
    size = D_001AD81C * 210000.0f;
    particle = SpawnGravityFadeParticle(position, D_001A8BD0, 4, 0xFF2020, phase, 127, 127,
                            size, size, 0.0f, 0);
    if (particle) {
        particle->shade = *D_001F2614;
        particle->variation = FloatToInt(0.4f) + 64;
    }
    secondPhase = (phase + 128) % 255;
    particle = SpawnGravityFadeParticle(position, D_001A8BD0, 4, 0xFF2020, secondPhase, 127, 127,
                            size, size, 0.0f, 0);
    if (particle) {
        particle->shade = *D_001F2614;
        particle->variation = FloatToInt(0.4f) + 64;
    }
    size *= 0.5f;
    particle = SpawnGravityFadeParticle(position, D_001A8BD0, 4, 0xFFFFFF, secondPhase, 127, 127,
                            size, size, 0.0f, 0);
    if (particle) {
        particle->shade = *D_001F2614;
        particle->variation = FloatToInt(0.4f) + 64;
    }
    gObjectPreviewState.phase++;
}

extern short D_001B2346;

extern short ref_L00_002FFFE0_00 __attribute__((sda));

extern short D_001A6480[];

extern void func_002FC560(int, long long);

extern void func_0027DE50(int, int, int, int, int);

/* Draws a dark overlay on the screen whose strength comes from the preview fade value. */
void func_002FFFE0(void)
{
    short alpha;
    VU1_addGSregister(0x42, ((long long)ref_L00_002FFFE0_00 << 32) | 0x44);
    alpha = ref_L00_002FFFE0_00;
    DrawColoredRectangle(0, gScreenAdjustOffsets[0xA9], 0, gScreenAdjustOffsets[0xA8], (alpha << 24) | 0xFFFFFF);
}






/* Puts a value in the first free place of a 64-entry list and returns the place, or -1 if full. */
s32 func_00300280(s32 *list,s32 value) {
 s32 placeIndex=-1,i=0,flagValue=1; s32 *p=list;
 for(;i<64;i++,p++) {
  if(*p==0) {
   *p=value;
   list[0x89]=flagValue;
   list[0x88]++;
   placeIndex=i;
   p[0x40]=0;
   break;
  }
 }
 return placeIndex;
}

/* Clear corresponding indexed words and decrement a record count */
/* Removes one entry from the 64-entry list and resets it when it becomes empty. */
void func_00300300(Rac2Native_74a5d71aacb394c6_ExtraIndexState48 *state, int index) {
    state->first[index] = 0;
    state->second[index] = 0;
    if (--state->count == 0) {
        state->current = 0;
    }
}

/* The 64-entry table of the family above: two rows of 64 words, eight more words, and
   three counters.  (The same table is indexed as words by func_00300280: 0x88 -> 0x220,
   0x89 -> 0x224.) */
typedef struct {
    int row0[64];
    int row1[64];
    int row2[8];
    int count;
    int flag;
    int limit;
} State00300330;

extern float func_00282EB0(char *origin, char *point);

/* The origin the distance helper is given.  The retail materialises it as
   `lui $s5,0x19` + `addiu $a0,$s5,-0x6160`, so it is the word at 0x190000 taken 0x6160
   lower; the helper's point is the row word plus 0x10. */
extern char D_00190000[];

/* Sorts the listed objects by distance from the player and keeps the nearest ones. */
void func_00300330(void *tablePtr) {
    State00300330 *state = (State00300330 *)tablePtr;
    float distances[64];
    int i;
    int k;
    int calls;
    int score;
    int best;
    float bestdistance;

    if (state->flag == 0) {
        return;
    }
    calls = 0;
    for (i = 0; i < 64; i++) {
        if (state->row0[i] != 0) {
            state->row1[i] = 0;
            distances[i] = FastVectorHelperC((char *)D_00190000 - 0x6160, (char *)(state->row0[i] + 0x10));
            calls++;
        }
        if (calls == state->count) {
            break;
        }
    }
    i = 0;
    if (state->limit <= 0) {
        return;
    }
    if (state->count <= 0) {
        return;
    }
    for (; i < state->limit && i < state->count; i++) {
        bestdistance = 9999.0f;      /* the retail's 0x461C3C00 */
        best = -1;
        score = 0;
        for (k = 0; score < 64; k++) {
            float d = distances[k];
            if (d < bestdistance) {
                if (state->row1[k] == 0) {
                    if (state->row0[k] != 0) {
                        bestdistance = d;
                        best = score;
                    }
                }
            }
            score++;
        }
        state->row2[i] = state->row0[best];
        state->row1[best] = 1;
    }
}


typedef struct {
    int padding;
    float value;
    int reserved[2];
} Record003004B0;

typedef struct {
    Record003004B0 records[64];
    int enabled;
    int index;
} State003004B0;

extern State003004B0 D_00220DC0;

/* Returns the saved value for the current entry if enabled, otherwise the value given. */
float func_003004B0(float value) {
    float result = value;
    if (D_00220DC0.enabled != 0)
        result = D_00220DC0.records[D_00220DC0.index].value;
    return result;
}

/* shared native body of family 8a42bc68419c7402 */
/* Tells whether a value is in the list of ids (1 if found, else 0). */
int func_003004E0(int value)
{
    int i;
    int found = 0;

    for (i = 0; i < D_L03_002325D0[64]; i++)
    {
        if (D_L03_002325D0[i] == value)
        {
            found = 1;
            break;
        }
    }
    return found;
}

/* func_00300540 : dispatch: weapon category selected by the identifier */
/* Sorts a weapon id into a group: 2, 1, or 0 for all others. */
s32 func_00300540(s32 weaponId) {
    s32 group = 0;
    if (weaponId == 0 || weaponId == 14 || weaponId == 13) group = 2;
    else if (weaponId == 1 || weaponId == 3 || weaponId == 11 || weaponId == 12) group = 1;
    return group;
}

