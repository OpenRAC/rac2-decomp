#include "include_asm.h"
#include "names.h"
extern void mem_clear(unsigned int *, unsigned int, int);
extern char *ref_0029EFD0_00[] __attribute__((sda));
extern char *ref_0029EFD0_01[] __attribute__((sda));
extern unsigned int ref_0029EFD0_02[] __attribute__((sda));
extern char *ref_0029EFD0_03[] __attribute__((sda));
extern int ref_0029EFD0_04[] __attribute__((sda));
extern char ref_0029EFD0_05[];
extern void moby_init_instance(char *, int);
extern void STUB_printf(const char *, ...);

/* The pool uses 256-byte slots; only fields needed by allocation are named. */
typedef struct MobyPoolSlot {
    unsigned char pad00[0x20];
    unsigned char state;
    unsigned char pad21[0x47];
    void *vars;
    unsigned char pad6C[0x34];
    unsigned int spawn_frame;
    unsigned char padA4[0x5C];
} MobyPoolSlot;

/* Measured partial layouts; original type and game roles are unknown. */
typedef unsigned int Rac2Native_abf21065e887d7a9_FallbackU32;

typedef struct Rac2Native_abf21065e887d7a9_FallbackPredicate112Layout {
    unsigned char unknown_00[0x90];
    Rac2Native_abf21065e887d7a9_FallbackU32 flags_90;
    Rac2Native_abf21065e887d7a9_FallbackU32 unknown_94;
    Rac2Native_abf21065e887d7a9_FallbackU32 flags_98;
} Rac2Native_abf21065e887d7a9_FallbackPredicate112Layout;

extern Rac2Native_abf21065e887d7a9_FallbackPredicate112Layout g_request_flag_table;

typedef unsigned char u8;

extern u8 g_moby_animation_state_pool[];

extern float func_00283CE0_4(int a);

extern void Ff2d8e5ad_FUN_002A3110(unsigned char *a, int b, unsigned char *c);

extern void Ff2d8e5ad_FUN_00283130(unsigned char *a, long long v);

extern void Ff2d8e5ad_FUN_002830C0(unsigned char *a, unsigned char *b, unsigned char *c);

extern void Ff2d8e5ad_FUN_00282D30(unsigned char *a, unsigned char *b, float f);

extern void Ff2d8e5ad_FUN_00283098(unsigned char *a, unsigned char *b, unsigned char *c);

extern void Ff2d8e5ad_FUN_00282CC0(unsigned char *a, unsigned char *b, unsigned char *c);

extern float Ff2d8e5ad_FUN_00282E48(unsigned char *a, unsigned char *b);

typedef float f32;

typedef unsigned int u32;

extern void func_00282A60_1 (char *node, int zero, int size);

extern void *g_moby_object_slots[16];

extern u32 g_moby_object_slot_flags[16];

extern void func_002A3F10_1(char *, int, int *, char *);

extern void func_00282D30_4(char *, char *, float);

extern void copy_matrix_rotation(char *, char *);

extern void func_00283788_1(char *, char *, char *);

extern void func_00282CC0_7(char *, char *, char *);

extern void func_002A3F10_2(char *a, int b, char *c, char *d);

extern void func_00282D30_19(char *a, char *b, float f);

extern void func_00283098_6(char *a, char *b, char *c);

extern void func_00282CC0_20(char *a, char *b, char *c);

extern void get_moby_joint_matrices_batch(char *);

extern void func_00282D30_7(char *, char *, float);

extern void func_00283098_3(char *, char *, char *);

extern void func_00282CC0_9(char *, char *, char *);

typedef struct {
    unsigned char key;
    unsigned char reserved01[11];
    int target;
} Row16b52b2850;

typedef struct {
    unsigned char reserved00[32];
    Row16b52b2850 *rows;
} ListObjectb52b2850;

typedef struct {
    short first;
    short second;
} Pairb52b2850;

extern int g_selected_object_table[];

extern ListObjectb52b2850 *g_object_l03_pointer_table[];

extern Pairb52b2850 g_point_list_pair_table[];

void mem_clear(unsigned int *dst, unsigned int val, int size);

/* Return whether both flag bit 0x10000 at data offset 0x90 and flag bit 0x04000000 at offset 0x98 are set, retaining the measured early rejection path. */
int menu_are_both_status_flags_set(void)
{
    if ((g_request_flag_table.flags_90 & 0x10000u) == 0 &&
        (g_request_flag_table.flags_98 & 0x04000000u) != 0)
        return 0;
    if ((g_request_flag_table.flags_90 & 0x10000u) != 0 &&
        (g_request_flag_table.flags_98 & 0x04000000u) != 0)
        return 1;
    return 0;
}



/* Finds a free moby slot, initialises it for the given class, and returns it (or 0 if the pool is full). */
char *CreateMoby(int classId)
{
    MobyPoolSlot *slot;
    for (slot = (MobyPoolSlot *)ref_0029EFD0_01[0];
         slot < (MobyPoolSlot *)ref_0029EFD0_00[0]; slot++) {
        if (slot->state >= 254 && ref_0029EFD0_02[0] >= slot->spawn_frame) {
            if (slot->state == 255) slot[1].state = 255;
            moby_init_instance((char *)slot, classId);
            slot->vars = ref_0029EFD0_03[0] +
                (slot - (MobyPoolSlot *)ref_0029EFD0_01[0]) * 128;
            mem_clear(slot->vars, 0, 128);
            if (ref_0029EFD0_04[0]) --ref_0029EFD0_04[0];
            return (char *)slot;
        }
    }
    STUB_printf(ref_0029EFD0_05, ref_0029EFD0_02[0], classId);
    return 0;
}

/* func_0029F0C8 is defined in 0029F0C8.c. */

extern char *g_moby_pool_end __attribute__((sda));
extern int g_game_time __attribute__((sda));
extern void func_002A0C68(char *, unsigned int);

/* Marks a moby as ready: sets its state byte by pool position and records the spawn frame. */
void moby_mark_spawned(void *object)
{
    char *moby = (char *)object;
    if ((unsigned int)moby < (unsigned int)g_moby_pool_end)
        ((unsigned char *)moby)[0x20] = 0xFD;
    else
        ((unsigned char *)moby)[0x20] = 0xFE;
    *(int *)(moby + 0xA0) = g_game_time + 2;
    func_002A0C68(moby, 0x80807F7Fu);
}

/* shared native body of family d1172b6afb7d978b */
void update_moby_animation_state(u8 *moby)
{
    if (moby[66] != 255) {
        u8 *animTable = (u8 *)(*(volatile int *)(moby + 36) + 72);

        *(int *)(moby + 88) = *(int *)(*(int *)(animTable + (*(volatile u8 *)(moby + 66) << 2)) + (moby[64] << 2) + 28);
        moby[110] = *(u8 *)(*(int *)(animTable + (*(volatile u8 *)(moby + 66) << 2)) + 18);
        moby[108] = *(u8 *)(*(int *)(animTable + (*(volatile u8 *)(moby + 66) << 2)) + 17);
    } else {
        moby[108] = 255;
        moby[110] = 0;
        *(int *)(moby + 88) = (int)(g_moby_animation_state_pool + (moby[64] << 11));
    }

    *(int *)(moby + 92) = *(int *)(*(int *)(*(volatile int *)(moby + 36) + (moby[67] << 2) + 72) + (moby[65] << 2) + 28);
}

extern u8 g_sound_state[];
extern void snd_stop_voice(int);
extern int PlayMobySound(int, int, char *);

/* Starts or stops the sound attached to a moby depending on its flags. */
void moby_update_sound(void *object)
{
    u8 *moby = (u8 *)object;

    if (moby[0x6D] != 0xFF) {
        u8 *soundSlot = g_sound_state + moby[0x6D] * 0x70;

        if (*(int *)(soundSlot + 0x88) != (int)moby) {
            moby[0x6D] = 0xFF;
        } else if (*(short *)(soundSlot + 0x7E) != moby[0x6C] ||
                   (*(unsigned short *)(moby + 0x34) & 0x40) != 0 ||
                   (*(unsigned short *)(moby + 0x7C) & 0x8000) != 0) {
            snd_stop_voice(moby[0x6D]);
            moby[0x6D] = 0xFF;
        }
    } else if (moby[0x6C] != 0xFF &&
               (*(unsigned short *)(moby + 0x34) & 0x40) == 0 &&
               (*(unsigned short *)(moby + 0x7C) & 0x8000) == 0) {
        moby[0x6D] = (u8)PlayMobySound(moby[0x6C], 4, (char *)moby);
    }
}


/* Picks one of two pointers held at +88 and +92 of the receiver, choosing +92 when the byte at +66 equals 255, then returns a value derived from the scale word at +68: either a halved table lookup, or a weighted blend of two table lookups plus the scale, or an interpolation between a lookup at +92 and a lookup at +88 weighted by one minus the scale. */
float moby_get_anim_value(char *moby)
{
    char *p;
    char *q;
    float t;

    if (*(unsigned char *)(moby + 66) != 255)
        p = *(char **)(moby + 88);
    else
        p = *(char **)(moby + 92);

    if (*(float *)(moby + 68) == 0.0f)
        return func_00283CE0_4(*(short *)(p + 4)) * 0.0625f;

    if (*(unsigned char *)(moby + 66) != *(unsigned char *)(moby + 67) ||
        *(unsigned char *)(moby + 64) > *(unsigned char *)(moby + 65))
        return func_00283CE0_4(*(short *)(p + 4)) * 0.0625f + *(float *)(moby + 68);

    q = *(char **)(moby + 92);
    t = func_00283CE0_4(*(short *)(p + 4)) * (1.0f - *(float *)(moby + 68));
    t = t + func_00283CE0_4(*(short *)(q + 4)) * *(float *)(moby + 68);
    return t * 0.0625f;
}


extern int log2dim(int);

/* Reads the number of animation entries for a moby and a value built from that count. */
void moby_get_anim_entry_count(char *object, int *count, int *value)
{
    char *p = *(char **)(object + 0x24);
    int index = *(unsigned char *)(p + 0x2C);
    if (index != 0) {
        int n;
        index = (int)p + (index << 4);
        n = *(short *)(index + 2);
        *count = n;
        *value = log2dim(n * 2);
    } else {
        *count = 0;
        *value = 0;
    }
}

/* Works out the midpoint position between two joints of a moby, in world space, and its radius. */
void func_0029F6A0(
    unsigned char *obj, unsigned int index, unsigned char *dest)
{
    unsigned char m0[16];
    unsigned char m1[16];
    unsigned char *base;
    unsigned char *p;
    short n;

    base = *(unsigned char **)(obj + 36);
    p = base + ((unsigned int)*(unsigned char *)(base + 44) << 4);
    p = p + ((index << 4) + 64u);
    n = *(short *)(p + 6);
    if (n < *(short *)(p + 14))
        n = *(short *)(p + 14);
    if (n >= 0)
        Ff2d8e5ad_FUN_002A3110(obj, n + 1, (unsigned char *)0x80000000u);
    Ff2d8e5ad_FUN_00283130(m0, *(long long *)(p));
    Ff2d8e5ad_FUN_00283130(m1, *(long long *)(p + 8));
    *(float *)(m0 + 12) = 1.0f;
    *(float *)(m1 + 12) = 1.0f;
    if (n >= 0) {
        Ff2d8e5ad_FUN_002830C0(m0, m0, (unsigned char *)
            (((unsigned int)*(short *)(p + 6) << 6) + 0x70000000u));
        Ff2d8e5ad_FUN_002830C0(m1, m1, (unsigned char *)
            (((unsigned int)*(short *)(p + 14) << 6) + 0x70000000u));
    }
    Ff2d8e5ad_FUN_00282D30(m0, m0, *(float *)(obj + 44) * 0.0009765625f);
    Ff2d8e5ad_FUN_00282D30(m1, m1, *(float *)(obj + 44) * 0.0009765625f);
    Ff2d8e5ad_FUN_00283098(m0, m0, obj + 192);
    Ff2d8e5ad_FUN_00283098(m1, m1, obj + 192);
    Ff2d8e5ad_FUN_00282CC0(m0, m0, obj + 16);
    Ff2d8e5ad_FUN_00282CC0(m1, m1, obj + 16);
    Ff2d8e5ad_FUN_00282CC0(dest, m0, m1);
    Ff2d8e5ad_FUN_00282D30(dest, dest, 0.5f);
    *(float *)(dest + 12) = Ff2d8e5ad_FUN_00282E48(dest, m0);
}

/* Attaches a manipulator record to a moby and adds it to the moby's list. */
void AttachManipulator(u8 *moby,u32 jointId,u8 *record) {
 u8 *p;
 if(record[1]!=0) return;
 record[0]=jointId; record[1]=1;
 *(f32 *)(record+0x1c)=1.0f;
 *(f32 *)(record+0x20)=1.0f;
 *(f32 *)(record+0x24)=1.0f;
 *(f32 *)(record+0x28)=1.0f;
 p=*(u8 **)(*(u8 **)(*(u8 **)(moby+0x24)+0x1c)+record[0]*4+4);
 *(u32 *)(record+4)=p[p[0]+4]*0x40+0x70000000;
 *(u8 **)(record+8)=*(u8 **)(moby+0x54);
 *(u8 **)(moby+0x54)=record;
}

/* unlinks a node from a singly linked list (head case and inner-chain case) and calls a release routine on it; does nothing for a null node */
void moby_detach_manipulator (char *list, char *node)
{
  char *cur;

  if (node == 0)
    return;

  if (*(char **) (list + 84) == node)
    {
      *(char **) (list + 84) = *(char **) (node + 8);
    }
  else if (*(char **) (list + 84) != 0)
    {
      cur = *(char **) (list + 84);
      while (*(char **) (cur + 8) != 0 && *(char **) (cur + 8) != node)
        cur = *(char **) (cur + 8);
      if (*(char **) (cur + 8) == node)
        *(char **) (cur + 8) = *(char **) (node + 8);
    }
  func_00282A60_1 (node, 0, 64);
}

/* Reserve or reuse an object slot, reset its associated state and return signed slot index */
int moby_alloc_object_slot(void *object)
{
    int index;
    for (index = 0; index < 16; ++index) {
        if (g_moby_object_slots[index] == 0 ||
            g_moby_object_slots[index] == object) {
            g_moby_object_slots[index] = object;
            g_moby_object_slot_flags[index] = 0;
            return index;
        }
    }
    return -1;
}

/* Empties all 16 slots of the object slot table. */
void moby_clear_object_slots(void)
{
    int i;
    for (i = 0; i < 16; i++) {
        g_moby_object_slots[i] = 0;
        g_moby_object_slot_flags[i] = 0;
    }
}


/* Copies an int argument into a 64-byte stack local, scales the float at offset 44 of the first pointer by 1/1024, and runs five helpers over the two pointers and that local buffer. */
void moby_transform_joint_point(char *moby, int jointIndex, char *out)
{
    int n;
    char buf[64];
    float f;

    n = jointIndex;
    f = *(float *)(moby + 44) * 0.0009765625f;
    func_002A3F10_1(moby, 1, &n, out);
    func_00282D30_4(out + 48, out + 48, f);
    copy_matrix_rotation(buf, moby + 192);
    func_00283788_1(out, buf, out);
    func_00282CC0_7(out + 48, out + 48, moby + 16);
}

/* scales a float field by 1/1024, stores an int argument in a stack record, and drives four helper calls with frame and object-field pointers */
void moby_transform_joint_to_world(char *moby, int jointIndex, char *out)
{
    char buf[80];
    float x;

    x = *(float *)(moby + 44);
    *(int *)(buf + 64) = jointIndex;
    x = x * 0.0009765625f;
    func_002A3F10_2(moby, 1, buf + 64, buf);
    func_00282D30_19(out, buf + 48, x);
    func_00283098_6(out, out, moby + 192);
    func_00282CC0_20(out, out, moby + 16);
}

/* Loops n times over a 16-byte-strided pointer, scaling the first pointer float at offset 44 by 1/1024 and calling three helpers with that pointer and two offsets of the first argument. */
void moby_transform_point_list(char *moby, int n, char *p3, char *points)
{
    float f = *(float *)(moby + 44) * 0.0009765625f;

    get_moby_joint_matrices_batch(moby);
    if (n > 0) {
        do {
            func_00282D30_7(points, points, f);
            func_00283098_3(points, points, moby + 192);
            func_00282CC0_9(points, points, moby + 16);
            points += 16;
        } while (--n != 0);
    }
}


/* func_0029FDF0 is in 0029DE38-textures-g8.c. */

/* shared native body of family b52b2850e37f2b40 */
void PatchMobyGifs(void)
{
    int *selected;
    ListObjectb52b2850 *object;
    Row16b52b2850 *row;
    unsigned char *keys;
    unsigned int *dst;
    Pairb52b2850 *pair;
    int *next;

    selected = g_selected_object_table;
    while (*selected >= 0) {
        next = selected + 1;
        object = g_object_l03_pointer_table[*selected];
        row = object->rows;
        for (;;) {
            keys = (unsigned char *)row;
            dst = (unsigned int *)(row->target & 0x7FFFFFFF);
            if (*keys != 255) {
                do {
                    pair = &g_point_list_pair_table[*keys];
                    if (pair->first != 0) {
                        dst[12] = (dst[12] & 0xFFFFC000u) | pair->first;
                    }
                    keys++;
                    if (pair->second != 0) {
                        dst[16] = (dst[16] & 0xFFFFC000u) | pair->second;
                    }
                    dst += 16;
                } while (*keys != 255);
            }
            if (row->target < 0) {
                goto out;
            }
            row++;
        }
out:
        ;
        selected = next;
    }
}

extern int g_hero_moby;
extern float g_light_direction[];
extern void func_002A04E8(int, float *);
extern float mat_fast_helper_a(float, float);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);

/* Works out a small direction vector (length 0.14) from a stored angle and saves it, with a fixed -0.99 height. */
void gfx_compute_light_direction(void)
{
    float v[2];
    float a;

    func_002A04E8(g_hero_moby, v);
    a = mat_fast_helper_a(v[0], v[1]);
    g_light_direction[0] = math_fast_sin_or_cos_a(a) * 0.14f;
    g_light_direction[1] = math_fast_sin_or_cos_b(a) * 0.14f;
    g_light_direction[2] = -0.99f;
}

/* func_002A0048 is in 0029DE38-dma.c. */

extern void FlushCache(int);
extern char g_tex_upload_scratch[];
extern void *g_scratch_upload_ptr __attribute__((sda));
extern int g_scratch_upload_arg __attribute__((sda));
extern void MobyAnimProc(void *, int);

/* Copies a block of data to the graphics scratch area and starts the next upload. */
void tex_upload_scratch_data(void)
{
    FlushCache(0);
    mem_fast_helper_c((void *)0x70003800, g_tex_upload_scratch, 0x800);
    MobyAnimProc(g_scratch_upload_ptr, g_scratch_upload_arg);
}

/* Fills a small scratch area with a fixed pattern. */
void mem_fill_scratch_area(void)
{
    mem_clear((unsigned int *)0x70003A00, 0x40000000, 0x3C0);
}

extern void mem_fast_helper_c(void *, void *, int);

/* Saves the scratch area to a backup buffer. */
void mem_save_scratch_area(void)
{
    mem_fast_helper_c((void *)((char *)g_object_l03_pointer_table - 0x3C0), (void *)0x70003A00, 0x3C0);
}


/* Restores the scratch area from the backup buffer. */
void mem_restore_scratch_area(void)
{
    mem_fast_helper_c((void *)0x70003A00, (void *)((char *)g_object_l03_pointer_table - 0x3C0), 0x3C0);
}


/* func_002A0250 is in 0029DE38-textures-g8.c. */

/* func_002A0300 is in 0029DE38-g8.c. */

extern void DmaMobyTextures(void);
extern void tex_upload_scratch_data(void);
extern int ConfigureGraphicsSetupDmaChain(void);
extern int g_tex_upload_result;

/* Runs the texture upload, and then the graphics setup if it is switched on. */
int tex_run_upload_and_setup(void)
{
    int result;
    DmaMobyTextures();
    tex_upload_scratch_data();
    result = g_tex_upload_result;
    if (result != 0)
        result = ConfigureGraphicsSetupDmaChain();
    return result;
}


/* func_002A03C0 is in 0029DE38-g8.c. */
