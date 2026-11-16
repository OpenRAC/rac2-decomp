#include "common.h"

extern char ref_L00_002FE8D8_00[];
extern int ref_L00_002FE8D8_01 __attribute__((sda));
extern float ref_L00_002FE8D8_02[];
extern int ref_L00_002FE8D8_03 __attribute__((sda));
extern void vec_scale_to_length(float *, float *, float);
extern void vec_copy_helper_a(float *);

/* lot10: privately byte-gated bodies. */
extern s32 func_00126470(u8 *, s32, s32, s32, s32, s32, s32, s32);

extern void FlushCache(s32);

extern s32 func_00126730(u8 *, u8 *);

extern s32 gfx_wait_paths_idle(s32, s32);

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

extern void g_gfx_gs_image_packet_build(int *a0, int a1, int a2, int a3, int a4, int a5, int a6, int a7);

extern int g_dmac_handler_id_a __attribute__((sda));

extern int g_dmac_handler_id_b __attribute__((sda));

extern void RemoveDmacHandler(int, int);

extern void kernel_process_queue_entry_c(int);

/* Measured partial layouts; original type and game roles are unknown. */
typedef unsigned int Rac2Native_74a5d71aacb394c6_u32;

typedef struct {
    Rac2Native_74a5d71aacb394c6_u32 first[64];
    Rac2Native_74a5d71aacb394c6_u32 second[64];
    unsigned char gap[0x20];
    int count;
    Rac2Native_74a5d71aacb394c6_u32 current;
} Rac2Native_74a5d71aacb394c6_ExtraIndexState48;

extern int g_known_id_list[];

/* Copies a block of image data from the console memory to the graphics chip in 16 KB pieces. */
void gfx_copy_image_to_gs_blocks(u8 *dest, s32 vram_addr, s32 size) {
    u8 image[112];
    s32 remaining = (size + 0x3fff) & ~0x3fff;
    s32 src_offset = 0, dst_offset = 0;
    for (; remaining > 0; remaining -= 0x4000) {
        func_00126470(image, (s32)(short)((vram_addr+src_offset)>>8), 1, 1, 0, 0, 64, 64);
        src_offset += 0x4000;
        FlushCache(0);
        func_00126730(image,dest+dst_offset);
        dst_offset += 0x3000;
        gfx_wait_paths_idle(0,0);
    }
}
/* shared native body of family d50cdefed4015bae (default profile) */
/* Uploads image data to the graphics chip in 16 KB pieces by writing DMA packets. */
void gfx_upload_image_to_gs_packets(int data, int vram_addr, int size)
{
    int remaining = (size + 16383) & -16384;
    int vram_offset = 0;
    int data_offset = 0;

    while (remaining > 0) {
        *(int *)((char *)D_L02_001B3D08_3 + 0) = 0x10000006;
        *(int *)((char *)D_L02_001B3D08_3 + 4) = 0;
        *(int *)((char *)D_L02_001B3D08_3 + 8) = 0;
        *(int *)((char *)D_L02_001B3D08_3 + 12) = 0x50000006;
        {
            int *next = (int *)((char *)D_L02_001B3D08_3 + 16);
            D_L02_001B3D08_5 = next;
            g_gfx_gs_image_packet_build(next, (short)((vram_addr + vram_offset) >> 8), 1, 1, 0, 0, 64, 64);
        }
        vram_offset += 16384;
        remaining -= 16384;
        {
            int *p = D_L02_001B3D08_3;
            int off = data + data_offset;
            data_offset += 12288;
            D_L02_001B3D08_5 = (int *)((char *)p + 96);
            *(int *)((char *)p + 96) = 0x30000300;
            *(int *)((char *)D_L02_001B3D08_3 + 4) = off;
            *(int *)((char *)D_L02_001B3D08_3 + 8) = 0;
            *(int *)((char *)D_L02_001B3D08_3 + 12) = 0x50000300;
            D_L02_001B3D08_5 = (int *)((char *)D_L02_001B3D08_3 + 16);
        }
    }
}

extern int log2dim(int);

/* Uploads a texture to the graphics chip in blocks and returns the texture setup value for it. */
long long tex_upload_blocks_return_setup(int data, int destination, int width, int height)
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
            g_gfx_gs_image_packet_build(next, (short)((destination + offset) >> 8), buffer_width >> 16,
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
extern int g_vif1_dma_handler_id __attribute__((sda));

extern int g_dma_error_handler_id __attribute__((sda));

extern void gfx_handle_vif1_dma_interrupt(void);

extern void gfx_handle_dma_error_hang(void);

extern int AddDmacHandler(int, void (*)(void), int);

extern void kernel_process_queue_entry_d(int);

/* Installs the two DMA interrupt handlers, once. */
void gfx_install_dma_handlers(void)
{
    if (g_vif1_dma_handler_id != 0) {
        return;
    }
    if (g_dma_error_handler_id != 0) {
        return;
    }
    if ((D_STAT & 0x20000) == 0) {
        *(unsigned int *)0x1000E010 = 0x20000;
    }
    g_vif1_dma_handler_id = AddDmacHandler(1, gfx_handle_vif1_dma_interrupt, 0);
    g_dma_error_handler_id = AddDmacHandler(15, gfx_handle_dma_error_hang, 0);
    kernel_process_queue_entry_d(1);
}

/* shared native body of family 349daa693c44d158 */
/* Removes the two DMA interrupt handlers and clears their ids. */
void gfx_remove_dma_handlers(void)
{
    if ((D_STAT & 0x20000) != 0) {
        D_STAT = 0x20000;
    }
    RemoveDmacHandler(1, g_dmac_handler_id_a);
    RemoveDmacHandler(15, g_dmac_handler_id_b);
    kernel_process_queue_entry_c(1);
    g_dmac_handler_id_a = 0;
    g_dmac_handler_id_b = 0;
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
void append_dma_tag(int tag) {
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

extern void moby_get_facing_direction(void *, float *);
extern void FastVecScale(float *, float *, float);
extern void FastVecSub(float *, float *, float *);

/* Adds a scaled copy of the direction vector for an object onto another vector. */
void vec_add_object_direction_scaled(void *object, float *destination, float scale)
{
    float vector[4];
    moby_get_facing_direction(object, vector);
    FastVecScale(vector, vector, scale);
    FastVecSub(destination, destination, vector);
}

/* Works out the up or facing direction for an object, depending on the player's state. */
void moby_get_facing_direction(void *object, float *destination)
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
        vec_copy_helper_a(destination);
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
extern void moby_get_facing_direction(void *, float *);
extern void vec_scale_to_length(float *, float *, float);
extern void FastVecScale(float *, float *, float);
extern void FastVecSub(float *, float *, float *);
extern void FastVecAdd(float *, float *, float *);
extern void vec_fast_normalize(float *, float *, float *);
extern float FastVecDot(float *, float *);
extern int coll_test_point(float, float *, int, void *);
extern int CollLine(void *, void *, int, void *, int);
extern int GetCollHitMaterial(void);

/* One collision step: tests the sphere (or a point offset from it) and,
   on a hit that is not ignored, moves it to the contact and either bounces
   its velocity off the surface, scaling the normal part by `bounce`
   (returns 1), or stops it at the contact point (returns 2); 0 otherwise. The query pointer and the
   separate dot product statement give retail's register use. */
int CollideSweptSphere(SweptSphere *sphere)
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

    moby_get_facing_direction(sphere->moby + 0x10, facing);
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
    hit = coll_test_point(sphere->radius, query, sphere->collisionFlags, sphere->moby);
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
            vec_fast_normalize(velocity, velocity, sphere->normal);
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

extern char g_object_slot_table[];

/* Returns slot number index of the 64-slot table, or nothing if out of range. */
void *slot_get_by_index(int index) {
    void *result = 0;
    if ((unsigned int)index < 64u)
        result = g_object_slot_table + index * 0x50;
    return result;
}

extern void AttachManipulator(unsigned char *, unsigned int, unsigned char *);

/* Finds a free slot in the 64-slot table, sets it up for an object and returns its number. */
int slot_alloc_for_object(unsigned char *object, unsigned int flags)
{
    char *p = g_object_slot_table;
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

extern void moby_detach_manipulator(char *, char *);
/* Releases a slot of the 64-slot table. */
void slot_free(unsigned int index) { if (index < 64u) { char *p = g_object_slot_table + index * 0x50; moby_detach_manipulator(*(char **)(p + 0x40), p); *(char **)(p + 0x40) = 0; } }


/* func_002FED90 is matched in its own unit, src/game/002FED90-qcopy.c (-frac2-qcopy). */

extern char g_effect_slot_table[];

/* Clears the flag word of one entry in a table of small records. */
void table_clear_entry_flag(int index) {
    int *p;
    if (index < 0) return;
    p = (int *)((unsigned int)g_effect_slot_table + (index << 5));
    p[7] = 0;
}

/* func_002FEE70 is defined in 002FEE70.c. */


/* Does nothing. */
void game_noop(void)
{
}

extern void moby_init_instance(void *, int);
extern void mem_clear(unsigned int *, unsigned int, int);
extern void func_002A0F48(void *);
extern char *ref_L00_002FF290_00 __attribute__((sda));
extern char *ref_L00_002FF290_01 __attribute__((sda));
/* Sets up an object of the given kind and gives it a cleared 128-byte block of private data. */
void moby_init_with_private_data(char *object, int kind)
{
    char *data;
    moby_init_instance(object, kind);
    data = ref_L00_002FF290_01 + (((int)object - (int)ref_L00_002FF290_00) >> 8) * 128;
    *(char **)(object + 0x68) = data;
    mem_clear((unsigned int *)data, 0, 128);
    if ((*(unsigned short *)(object + 0x34) & 4) == 0)
        func_002A0F48(object);
}

/* func_002FF300 is matched in its own unit, src/game/002FF300.c (default flags). */

extern char *g_effect_object __attribute__((sda));
extern void moby_init_with_private_data(char *, int);

/* Sets up the preview object so it is small, hidden at first and ready to show. */
void shop_setup_preview_object(void)
{
    char *object;
    moby_init_with_private_data(g_effect_object, 0x3EF);
    object = g_effect_object;
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

extern PreviewCameraPrefix g_active_camera;
extern PreviewState g_object_preview_state __attribute__((sda));
/* Distances along the preview's basis rows, separate small-data floats
   (retail loads D_001AD814 in a branch delay slot, so it is not an offset
   from a common base). */
extern float g_preview_basis_scale_a SDATA(D_001AD808) __attribute__((sda));
extern float g_preview_basis_scale_b SDATA(D_001AD80C) __attribute__((sda));
extern float g_preview_basis_scale_c SDATA(D_001AD810) __attribute__((sda));
extern float g_preview_basis_scale_d SDATA(D_001AD814) __attribute__((sda));
extern float g_preview_basis_scale_e SDATA(D_001AD818) __attribute__((sda));
extern float FastAddRotations(float, float);
extern void euler_rotation_basis(float *, float *);
extern void shop_spawn_preview_light_burst(void *);

/* Places the previewed object in front of the camera, turns it a little
   (about x when spinning, else about z) and offsets it along its own basis.
   The two spinning branches end in the same scale-and-add, which cc1's
   cross-jumping merges into one tail as in retail. */
void PlaceObjectBeforeCamera(PreviewObjectPrefix *object)
{
    float offset[4] __attribute__((aligned(16)));
    float basis[12] __attribute__((aligned(16)));
    float temporary[4] __attribute__((aligned(16)));
    int special = object->classId == MOBY_CLASS_MINITURRET_GLOVE || object->classId == MOBY_CLASS_MEGATURRET_GLOVE;
    int compact = 0;
    if (object->classId == MOBY_CLASS_CHOPPER || object->classId == MOBY_CLASS_MULTI_STAR ||
        object->classId == MOBY_CLASS_SPIDERBOT_GLOVE || object->classId == MOBY_CLASS_TANKBOT_GLOVE || special)
        compact = 1;
    if (special) {
        FastVecScale(offset, g_active_camera.forward, 2.5f);
    } else if (compact) {
        FastVecScale(offset, g_active_camera.forward, 2.0f);
    } else {
        FastVecScale(offset, g_active_camera.forward, 3.0f);
    }
    FastVecAdd(object->position, g_active_camera.position, offset);
    if (g_object_preview_state.spin)
        object->rotation[0] = FastAddRotations(object->rotation[0], 0.03490659f);
    else
        object->rotation[2] = FastAddRotations(object->rotation[2], 0.03490659f);
    euler_rotation_basis(basis, object->rotation);
    if (g_object_preview_state.spin) {
        if (compact) {
            FastVecScale(temporary, basis + 4, g_preview_basis_scale_e);
            FastVecAdd(object->position, object->position, temporary);
            FastVecScale(temporary, basis, g_preview_basis_scale_d);
            FastVecAdd(object->position, object->position, temporary);
        } else {
            FastVecScale(temporary, basis + 4, g_preview_basis_scale_b);
            FastVecAdd(object->position, object->position, temporary);
            FastVecScale(temporary, basis, g_preview_basis_scale_a);
            FastVecAdd(object->position, object->position, temporary);
        }
    } else {
        FastVecScale(temporary, basis + 8, g_preview_basis_scale_c);
        FastVecAdd(object->position, object->position, temporary);
    }
    func_002A0F48(object);
    shop_spawn_preview_light_burst(object);
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
extern float g_preview_size_scale SDATA(D_001AD81C) __attribute__((sda));
extern float g_default_effect_vector[] MACRO_ADDR;
extern unsigned char *g_part_tex_ground_effect;
extern float IntToFloat(int);
extern void lerp_vector(float *, float *, float *, float);
extern int FloatToInt(float);
/* The particle constructor of 002BF6F0-c65a0.c, declared with its three
   float parameters after the first five integers (as 0032DD40-g8.c does):
   each register bank keeps its order, and retail sets up the arguments in
   this order. */
extern Particle_C65A0 *part_spawn_gravity_fade(const float *, const float *, int, unsigned int, int, int, int,
                                   float, float, float, int);

/* Emits three particles between 0.1 and 9 units in front of the camera,
   at the point the preview timer has reached; their phase advances once
   per call. */
void EmitParticlesBeforeCamera(void)
{
    float offset[4] __attribute__((aligned(16)));
    float farPoint[4] __attribute__((aligned(16)));
    float nearPoint[4] __attribute__((aligned(16)));
    float position[4] __attribute__((aligned(16)));
    int phase = g_object_preview_state.phase;
    int secondPhase;
    float size, interpolation;
    Particle_C65A0 *particle;
    FastVecScale(offset, g_active_camera.forward, 9.0f);
    FastVecAdd(farPoint, g_active_camera.position, offset);
    FastVecScale(offset, g_active_camera.forward, 0.1f);
    FastVecAdd(nearPoint, g_active_camera.position, offset);
    interpolation = IntToFloat(g_object_preview_state.frames) * g_object_preview_state.rate;
    lerp_vector(position, nearPoint, farPoint, interpolation);
    size = g_preview_size_scale * 210000.0f;
    particle = part_spawn_gravity_fade(position, g_default_effect_vector, 4, 0xFF2020, phase, 127, 127,
                            size, size, 0.0f, 0);
    if (particle) {
        particle->shade = *g_part_tex_ground_effect;
        particle->variation = FloatToInt(0.4f) + 64;
    }
    secondPhase = (phase + 128) % 255;
    particle = part_spawn_gravity_fade(position, g_default_effect_vector, 4, 0xFF2020, secondPhase, 127, 127,
                            size, size, 0.0f, 0);
    if (particle) {
        particle->shade = *g_part_tex_ground_effect;
        particle->variation = FloatToInt(0.4f) + 64;
    }
    size *= 0.5f;
    particle = part_spawn_gravity_fade(position, g_default_effect_vector, 4, 0xFFFFFF, secondPhase, 127, 127,
                            size, size, 0.0f, 0);
    if (particle) {
        particle->shade = *g_part_tex_ground_effect;
        particle->variation = FloatToInt(0.4f) + 64;
    }
    g_object_preview_state.phase++;
}

extern short g_unused_short;

extern short ref_L00_002FFFE0_00 __attribute__((sda));

extern short g_screen_adjust_offsets[];

extern void VU1_addGSregister(int, long long);

extern void gfx_draw_colored_rectangle(int, int, int, int, int);

/* Draws a dark overlay on the screen whose strength comes from the preview fade value. */
void shop_draw_preview_dim_overlay(void)
{
    short alpha;
    VU1_addGSregister(0x42, ((long long)ref_L00_002FFFE0_00 << 32) | 0x44);
    alpha = ref_L00_002FFFE0_00;
    gfx_draw_colored_rectangle(0, g_screen_adjust_offsets[0xA9], 0, g_screen_adjust_offsets[0xA8], (alpha << 24) | 0xFFFFFF);
}






/* Puts a value in the first free place of a 64-entry list and returns the place, or -1 if full. */
s32 slot_list_add(s32 *list,s32 value) {
 s32 place_index=-1,i=0,flag_value=1; s32 *p=list;
 for(;i<64;i++,p++) {
  if(*p==0) {
   *p=value;
   list[0x89]=flag_value;
   list[0x88]++;
   place_index=i;
   p[0x40]=0;
   break;
  }
 }
 return place_index;
}

/* Clear corresponding indexed words and decrement a record count */
/* Removes one entry from the 64-entry list and resets it when it becomes empty. */
void slot_list_remove(Rac2Native_74a5d71aacb394c6_ExtraIndexState48 *state, int index) {
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

extern float vec_fast_helper_c(char *origin, char *point);

/* The origin the distance helper is given.  The retail materialises it as
   `lui $s5,0x19` + `addiu $a0,$s5,-0x6160`, so it is the word at 0x190000 taken 0x6160
   lower; the helper's point is the row word plus 0x10. */
extern char g_data_block_base[];

/* Sorts the listed objects by distance from the player and keeps the nearest ones. */
void moby_sort_entries_by_distance(void *table_ptr) {
    State00300330 *state = (State00300330 *)table_ptr;
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
            distances[i] = vec_fast_helper_c((char *)g_data_block_base - 0x6160, (char *)(state->row0[i] + 0x10));
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

extern State003004B0 g_game_override_state;

/* Returns the saved value for the current entry if enabled, otherwise the value given. */
float game_get_override_value(float value) {
    float result = value;
    if (g_game_override_state.enabled != 0)
        result = g_game_override_state.records[g_game_override_state.index].value;
    return result;
}

/* shared native body of family 8a42bc68419c7402 */
/* Tells whether a value is in the list of ids (1 if found, else 0). */
int game_is_id_in_list(int value)
{
    int i;
    int found = 0;

    for (i = 0; i < g_known_id_list[64]; i++)
    {
        if (g_known_id_list[i] == value)
        {
            found = 1;
            break;
        }
    }
    return found;
}

/* func_00300540 : dispatch: weapon category selected by the identifier */
/* Sorts a weapon id into a group: 2, 1, or 0 for all others. */
s32 weapon_get_group(s32 weapon_id) {
    s32 group = 0;
    if (weapon_id == 0 || weapon_id == 14 || weapon_id == 13) group = 2;
    else if (weapon_id == 1 || weapon_id == 3 || weapon_id == 11 || weapon_id == 12) group = 1;
    return group;
}

