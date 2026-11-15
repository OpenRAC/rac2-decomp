#include "include_asm.h"
#include "names.h"
extern void func_00282A60(unsigned int *, unsigned int, int);
extern char *ref_0029EFD0_00[] __attribute__((sda));
extern char *ref_0029EFD0_01[] __attribute__((sda));
extern unsigned int ref_0029EFD0_02[] __attribute__((sda));
extern char *ref_0029EFD0_03[] __attribute__((sda));
extern int ref_0029EFD0_04[] __attribute__((sda));
extern char ref_0029EFD0_05[];
extern void func_0029F0C8(char *, int);
extern void func_0026FEB8(const char *, ...);

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

extern Rac2Native_abf21065e887d7a9_FallbackPredicate112Layout D_00139768;

typedef unsigned char u8;

extern u8 D_L03_001D2540[];

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

extern void *D_L00_001B1E00[16];

extern u32 D_L00_001B1E40[16];

extern void func_002A3F10_1(char *, int, int *, char *);

extern void func_00282D30_4(char *, char *, float);

extern void func_00283658(char *, char *);

extern void func_00283788_1(char *, char *, char *);

extern void func_00282CC0_7(char *, char *, char *);

extern void func_002A3F10_2(char *a, int b, char *c, char *d);

extern void func_00282D30_19(char *a, char *b, float f);

extern void func_00283098_6(char *a, char *b, char *c);

extern void func_00282CC0_20(char *a, char *b, char *c);

extern void func_002A3DB8(char *);

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

extern int D_L03_001DE1C0[];

extern ListObjectb52b2850 *D_L03_001DAB80[];

extern Pairb52b2850 D_L03_001DDA00[];

void func_00282A60(unsigned int *dst, unsigned int val, int size);

/* Return whether both flag bit 0x10000 at data offset 0x90 and flag bit 0x04000000 at offset 0x98 are set, retaining the measured early rejection path. */
int func_0029DE38(void)
{
    if ((D_00139768.flags_90 & 0x10000u) == 0 &&
        (D_00139768.flags_98 & 0x04000000u) != 0)
        return 0;
    if ((D_00139768.flags_90 & 0x10000u) != 0 &&
        (D_00139768.flags_98 & 0x04000000u) != 0)
        return 1;
    return 0;
}



/* Finds a free moby slot, initialises it for the given class, and returns it (or 0 if the pool is full). */
char *func_0029EFD0(int classId)
{
    MobyPoolSlot *slot;
    for (slot = (MobyPoolSlot *)ref_0029EFD0_01[0];
         slot < (MobyPoolSlot *)ref_0029EFD0_00[0]; slot++) {
        if (slot->state >= 254 && ref_0029EFD0_02[0] >= slot->spawn_frame) {
            if (slot->state == 255) slot[1].state = 255;
            InitMobyInstance((char *)slot, classId);
            slot->vars = ref_0029EFD0_03[0] +
                (slot - (MobyPoolSlot *)ref_0029EFD0_01[0]) * 128;
            ClearMemory(slot->vars, 0, 128);
            if (ref_0029EFD0_04[0]) --ref_0029EFD0_04[0];
            return (char *)slot;
        }
    }
    STUB_printf(ref_0029EFD0_05, ref_0029EFD0_02[0], classId);
    return 0;
}

/* func_0029F0C8 is defined in 0029F0C8.c. */

extern char *D_001B1B60 __attribute__((sda));
extern int D_001B1688 __attribute__((sda));
extern void func_002A0C68(char *, unsigned int);

/* Marks a moby as ready: sets its state byte by pool position and records the spawn frame. */
void func_0029F338(void *object)
{
    char *moby = (char *)object;
    if ((unsigned int)moby < (unsigned int)D_001B1B60)
        ((unsigned char *)moby)[0x20] = 0xFD;
    else
        ((unsigned char *)moby)[0x20] = 0xFE;
    *(int *)(moby + 0xA0) = gGameTime + 2;
    func_002A0C68(moby, 0x80807F7Fu);
}

/* shared native body of family d1172b6afb7d978b */
void func_0029F390(u8 *moby)
{
    if (moby[66] != 255) {
        u8 *animTable = (u8 *)(*(volatile int *)(moby + 36) + 72);

        *(int *)(moby + 88) = *(int *)(*(int *)(animTable + (*(volatile u8 *)(moby + 66) << 2)) + (moby[64] << 2) + 28);
        moby[110] = *(u8 *)(*(int *)(animTable + (*(volatile u8 *)(moby + 66) << 2)) + 18);
        moby[108] = *(u8 *)(*(int *)(animTable + (*(volatile u8 *)(moby + 66) << 2)) + 17);
    } else {
        moby[108] = 255;
        moby[110] = 0;
        *(int *)(moby + 88) = (int)(D_L03_001D2540 + (moby[64] << 11));
    }

    *(int *)(moby + 92) = *(int *)(*(int *)(*(volatile int *)(moby + 36) + (moby[67] << 2) + 72) + (moby[65] << 2) + 28);
}

extern u8 D_00188660[];
extern void func_002E59F8(int);
extern int func_002E5CF8(int, int, char *);

/* Starts or stops the sound attached to a moby depending on its flags. */
void func_0029F450(void *object)
{
    u8 *moby = (u8 *)object;

    if (moby[0x6D] != 0xFF) {
        u8 *soundSlot = gSoundState + moby[0x6D] * 0x70;

        if (*(int *)(soundSlot + 0x88) != (int)moby) {
            moby[0x6D] = 0xFF;
        } else if (*(short *)(soundSlot + 0x7E) != moby[0x6C] ||
                   (*(unsigned short *)(moby + 0x34) & 0x40) != 0 ||
                   (*(unsigned short *)(moby + 0x7C) & 0x8000) != 0) {
            StopSoundVoice(moby[0x6D]);
            moby[0x6D] = 0xFF;
        }
    } else if (moby[0x6C] != 0xFF &&
               (*(unsigned short *)(moby + 0x34) & 0x40) == 0 &&
               (*(unsigned short *)(moby + 0x7C) & 0x8000) == 0) {
        moby[0x6D] = (u8)PlayMobySound(moby[0x6C], 4, (char *)moby);
    }
}


/* Picks one of two pointers held at +88 and +92 of the receiver, choosing +92 when the byte at +66 equals 255, then returns a value derived from the scale word at +68: either a halved table lookup, or a weighted blend of two table lookups plus the scale, or an interpolation between a lookup at +92 and a lookup at +88 weighted by one minus the scale. */
float func_0029F530(char *moby)
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


extern int func_00282A18(int);

/* Reads the number of animation entries for a moby and a value built from that count. */
void func_0029F648(char *object, int *count, int *value)
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
void func_0029F978(u8 *moby,u32 jointId,u8 *record) {
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
void func_0029F9F0 (char *list, char *node)
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
int func_0029FA88(void *object)
{
    int index;
    for (index = 0; index < 16; ++index) {
        if (D_L00_001B1E00[index] == 0 ||
            D_L00_001B1E00[index] == object) {
            D_L00_001B1E00[index] = object;
            D_L00_001B1E40[index] = 0;
            return index;
        }
    }
    return -1;
}

/* Empties all 16 slots of the object slot table. */
void func_0029FAE0(void)
{
    int i;
    for (i = 0; i < 16; i++) {
        D_L00_001B1E00[i] = 0;
        D_L00_001B1E40[i] = 0;
    }
}


/* Copies an int argument into a 64-byte stack local, scales the float at offset 44 of the first pointer by 1/1024, and runs five helpers over the two pointers and that local buffer. */
void func_0029FC20(char *moby, int jointIndex, char *out)
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
void func_0029FCC0(char *moby, int jointIndex, char *out)
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
void func_0029FD48(char *moby, int n, char *p3, char *points)
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
void func_0029FEE0(void)
{
    int *selected;
    ListObjectb52b2850 *object;
    Row16b52b2850 *row;
    unsigned char *keys;
    unsigned int *dst;
    Pairb52b2850 *pair;
    int *next;

    selected = D_L03_001DE1C0;
    while (*selected >= 0) {
        next = selected + 1;
        object = D_L03_001DAB80[*selected];
        row = object->rows;
        for (;;) {
            keys = (unsigned char *)row;
            dst = (unsigned int *)(row->target & 0x7FFFFFFF);
            if (*keys != 255) {
                do {
                    pair = &D_L03_001DDA00[*keys];
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

extern int D_0018C0B0;
extern float D_001B1B90[];
extern void func_002A04E8(int, float *);
extern float func_00283248(float, float);
extern float func_00283180(float);
extern float func_00283198(float);

/* Works out a small direction vector (length 0.14) from a stored angle and saves it, with a fixed -0.99 height. */
void func_0029FFB8(void)
{
    float v[2];
    float a;

    func_002A04E8(gHeroMoby_0018C0B0, v);
    a = FastMatrixHelperA(v[0], v[1]);
    D_001B1B90[0] = FastSinOrCosA(a) * 0.14f;
    D_001B1B90[1] = FastSinOrCosB(a) * 0.14f;
    D_001B1B90[2] = -0.99f;
}

/* func_002A0048 is in 0029DE38-dma.c. */

extern void func_0011AEA0(int);
extern char D_00238F00[];
extern void *D_001B16B0 __attribute__((sda));
extern int D_001B16B4 __attribute__((sda));
extern void func_002A4D88(void *, int);

/* Copies a block of data to the graphics scratch area and starts the next upload. */
void func_002A0180(void)
{
    FlushCache(0);
    FastMemoryHelperC((void *)0x70003800, D_00238F00, 0x800);
    MobyAnimProc(D_001B16B0, D_001B16B4);
}

/* Fills a small scratch area with a fixed pattern. */
void func_002A01C8(void)
{
    ClearMemory((unsigned int *)0x70003A00, 0x40000000, 0x3C0);
}

extern void func_00282B50(void *, void *, int);

/* Saves the scratch area to a backup buffer. */
void func_002A01F0(void)
{
    FastMemoryHelperC((void *)((char *)D_L03_001DAB80 - 0x3C0), (void *)0x70003A00, 0x3C0);
}


/* Restores the scratch area from the backup buffer. */
void func_002A0220(void)
{
    FastMemoryHelperC((void *)0x70003A00, (void *)((char *)D_L03_001DAB80 - 0x3C0), 0x3C0);
}


/* func_002A0250 is in 0029DE38-textures-g8.c. */

/* func_002A0300 is in 0029DE38-g8.c. */

extern void func_0029FDF0(void);
extern void func_002A0180(void);
extern int func_002A0048(void);
extern int D_001B1B80;

/* Runs the texture upload, and then the graphics setup if it is switched on. */
int func_002A0380(void)
{
    int result;
    DmaMobyTextures();
    UploadScratchTextureData();
    result = D_001B1B80;
    if (result != 0)
        result = ConfigureGraphicsSetupDmaChain();
    return result;
}


/* func_002A03C0 is in 0029DE38-g8.c. */
