#include "common.h"

/* func_002EAB18: sets up a level after its archive is read: resets the engine
 * and class tables, decompresses the archive, uploads textures, registers the
 * moby classes and the HUD class, then lays out the moby and particle buffers
 * and the sound banks. RAC1's counterpart is initialize_level_runtime. */

typedef struct {
    char pad[0x2c0];
    int x, y;
    float time;
    char gap[0x1fc4];
    int flag;
} LoadEngine;
extern LoadEngine loadEngine __asm__("D_00189E20_9");

typedef struct {
    char pad[0x1c];
    int count; /* class slot of the HUD class */
    short mode, selected;
    char gap[8];
    short a, b;
    char gap2[8];
    unsigned long long packet;
} LoadState;
extern LoadState loadState __asm__("D_00152C00");

typedef struct {
    int texture, data, textureCount, textureInfo;
    int mobyCount, mobys, classCount, classes;
    int partCount, parts, pointCount, points;
    int classData, partData, textureData, partInfo;
    int unknown40, unknown44, sky;
    int unknown4c, unknown50, unknown54, unknown58, unknown5c, unknown60;
    int sound[5];
} ArchiveHeader;
typedef struct { int offset; unsigned short dimension, pad6; int pad8[2]; } TextureRecord;
typedef struct { int offset, id, special, padC; char map[16]; } MobyRecord;

typedef struct {
    char pad[0x18];
    ArchiveHeader *header;
    char gap[0x1c];
    char *firstClass;
    char gap2[0xc];
    char *end;
    char gap3[0x24];
    char *uiClass;
    char gap4[4];
    char *uiInfo;
} LoadBuffers;
extern LoadBuffers loadBuffers __asm__("D_001BAEC0");

typedef struct { char pad[0x17b4]; unsigned int soundState; } SoundState;
typedef struct { char pad[0x28]; int left, right; } BankVolume;

extern float D_001B15A0 __attribute__((sda));
extern int D_001B22B0 __attribute__((sda));
extern int D_001B15A4 __attribute__((sda));
extern int D_001A72F4 __attribute__((sda));
extern int D_001A72D4 __attribute__((sda));
extern int D_001A72D0 __attribute__((sda));
extern int D_001B1B4C __attribute__((sda));
extern int D_001B1B40 __attribute__((sda));
extern int D_001A7290 __attribute__((sda));
extern short D_001A7A18 __attribute__((sda));
extern char *D_001B1604 __attribute__((sda));
extern int D_001B1B5C __attribute__((sda));
extern int D_001B1B6C __attribute__((sda));
extern int D_001B1D98 __attribute__((sda));
extern int D_001B1D90 __attribute__((sda));
extern int D_001B1D94 __attribute__((sda));
extern int D_001B159C __attribute__((sda));
extern int D_001B1B74 __attribute__((sda));
extern unsigned char *D_001B1B60 __attribute__((sda));
extern unsigned char *D_001B1B64 __attribute__((sda));
extern int D_001B1D9C __attribute__((sda));
extern int D_001B1DA0 __attribute__((sda));
extern int D_001B2130[] __attribute__((sda));
extern int D_001B2134[] __attribute__((sda));
extern int D_001B2138[] __attribute__((sda));
extern int D_001B213C[] __attribute__((sda));
extern int D_001B2140[] __attribute__((sda));
extern int D_001ABEC0[] SDATA(D_001ABEC0);

extern char D_0014B540[];
extern char D_00188660[];
extern char D_001A91E0[];
extern char D_001B1740[];
extern char D_001C2740[], D_001C2B40[], D_001C2C40[];
extern unsigned long long D_001C4DC0[];
extern char *D_001CDB80[];
extern short D_001CE300[];
extern char D_001CE4E0[];
extern int D_001D0600[];
extern int D_001D0E00[];
extern char D_001D1580[];
extern char D_001F1D40[];

extern void func_00290B48(), func_00282A60(), func_0027A9F0(), func_0027AB40(), func_002FC1D8();
extern void func_0027D330(), func_00293000(), func_00291EC0(), func_00293890(), func_00292328();
extern void func_00282A88(), func_00282B50(), func_0029F0C8(), func_0027B7E0(), func_002EA968();
extern int func_0029D4D0(), func_00282A18();
extern int func_002B7C10(int, int, int);
extern int func_00133580(int);
extern int func_00132828(void);
extern void func_0011AEA0(int);
extern void func_002934B8(void *, void *);
extern void func_00291DE0(void *, int);
extern void func_00291CA8(void *, int, void *, int);
extern void func_002EAAA8(void *, int *);

void func_002EAB18(void)
{
    char *base, *records, *p;
    unsigned char *entry;
    ArchiveHeader *header;
    TextureRecord *textures;
    MobyRecord *moby;
    int i, j, size;
    BankVolume *bank;

    loadEngine.time = -1.0f;
    loadState.mode = 2;
    loadState.selected = -1;
    D_001B15A0 = 1.0f;
    D_001B22B0 = 0x100000;
    loadEngine.x = 0;
    loadEngine.y = 0;
    loadEngine.flag = 0;
    D_001B15A4 = 0;
    func_00290B48();
    D_001A72D0 = D_001A72F4;
    D_001A72D4 = D_001A72F4;
    func_00282A60(D_001B1740, 0x87654321, 16);
    func_00282A60(D_001CE4E0, -1, 0x2000);
    func_00282A60(D_001D1580, -1, 0xf00);
    func_00282A60(D_001D0E00, 0, 0xf0);
    func_0027A9F0();
    func_0027AB40();
    func_002FC1D8();
    {
        char *disc = D_0014B540;
        int *sector = (int *)(disc + 0x3e58);
        int *length = (int *)(disc + 0x3e5c);
        int index = loadState.b * 8;

        func_002B7C10((int)loadBuffers.header + 0x400000,
                      *(int *)(index + (int)sector) + *(int *)(disc + 0x3e24),
                      *(int *)(index + (int)length));
    }
    func_0027D330(6);
    func_00133580(0);
    func_0011AEA0(0);
    size = func_0029D4D0((int)loadBuffers.header + 0x400000, (int)loadBuffers.header);
    func_0011AEA0(0);

    header = loadBuffers.header;
    func_00293000((char *)header + header->texture, header->textureCount, 0,
                  (char *)header + header->textureInfo);
    base = (char *)header + header->data;
    records = base + header->classData;
    textures = (TextureRecord *)((char *)header + header->classes);
    D_001B1B4C = header->classCount;
    for (i = 0; i < D_001B1B4C; i++)
        D_001D0600[i] = (int)records + textures[i].offset + (func_00282A18(textures[i].dimension) << 28);

    func_00291EC0(base + header->sky);
    moby = (MobyRecord *)((char *)header + header->mobys);
    D_001B1B40 = 0;
    for (j = 0; j < header->mobyCount; j++, moby++) {
        char *object = moby->offset ? base + moby->offset : 0;

        if (moby->special) {
            D_001C4DC0[0] = loadState.packet;
            D_001C4DC0[1] = 0xFFA0000000E0ULL;
            D_001C4DC0[2] = 0x0040000400004000ULL;
            func_00293890(object, 0, D_001A91E0, moby->id);
            D_001D0E00[D_001B1B40 - 1] = 0xfffc0000;
        } else
            func_00293890(object, (char *)header + header->classes, moby->map, moby->id);
    }

    /* The HUD class (id 0xd54) takes the next class slot. The slot is read back
     * from loadState.count after the count was bumped, as retail does. */
    {
        int n = D_001B1B40;

        loadState.count = n;
        n++;
        D_001B1B40 = n;
        D_001CDB80[loadState.count] = loadBuffers.uiClass;
        D_001CE300[loadState.count] = 0xd54;
        D_001CE4E0[0xd54] = loadState.count;
        D_001D0E00[loadState.count] = 0xfffc0000;
        loadBuffers.firstClass = D_001CDB80[0];
    }
    if (D_001A7290 != D_001A7A18)
        func_00292328(D_001A7A18);
    func_002934B8((void *)D_001CDB80[0], (void *)loadBuffers.uiInfo);
    D_001D0E00[0] = 0xfffc0000;

    D_001B1604 = base + header->textureData;
    func_00291DE0((char *)header + header->points, header->pointCount);
    {
        int partData = (int)base + header->partData;
        char *parts = (char *)header + header->parts;

        func_00291CA8((char *)header + header->partInfo, partData, parts, header->partCount);
    }

    p = (char *)loadBuffers.header + size;
    loadBuffers.end = p;
    func_00282A88(D_001C2B40, 0x100);
    func_00282A88(D_001C2C40, 0x180);
    func_00282A88(D_001C2740, 0x400);
    func_00282B50(D_001C2740, D_001ABEC0, 0x40);
    D_001B1B5C = (int)p;
    func_00282A60(p, 0, 0x4000);
    p += 0x4000;
    entry = (unsigned char *)D_001B1B5C;
    D_001B159C = (int)entry;
    func_0029F0C8(entry, 0);
    entry[0x20] = 0xfd;
    D_001B1B60 = (unsigned char *)D_001B159C + 0x100;
    D_001B1B60[0x20] = 0xff;
    D_001B1B6C = (int)p;
    p += 0x2000;
    D_001B1D98 = -1;
    D_001B1D90 = (int)p;
    D_001B1B64 = D_001B1B60 + 0x3f00;
    D_001B1D94 = 0;
    D_001B1D9C = 0;
    func_00282A88(D_001F1D40, 0x200);
    func_0027B7E0();
    D_001B1B74 = 0x3c0;
    D_001B1DA0 = 0x1f4000;
    func_002EA968();
    {
        SoundState *sound = (SoundState *)D_00188660;

        sound->soundState = 0xffffffffU;
    }

    bank = (BankVolume *)(base + header->sound[4] + 0x18);
    bank->left = 0xc000;
    bank->right = 0xc000;
    bank = (BankVolume *)(base + header->sound[3] + 0x18);
    bank->left = 0xc000;
    bank->right = 0xc000;
    bank = (BankVolume *)(base + header->sound[2] + 0x18);
    bank->left = 0xc000;
    bank->right = 0xc000;
    bank = (BankVolume *)(base + header->sound[1] + 0x18);
    bank->left = 0xc000;
    bank->right = 0xc000;
    bank = (BankVolume *)(base + header->sound[0] + 0x18);
    bank->left = 0xc000;
    bank->right = 0xc000;
    func_0011AEA0(0);
    func_002EAAA8(base + header->sound[4], &D_001B2140[0]);
    func_002EAAA8(base + header->sound[2], &D_001B2138[0]);
    func_002EAAA8(base + header->sound[3], &D_001B213C[0]);
    func_002EAAA8(base + header->sound[1], &D_001B2134[0]);
    func_002EAAA8(base + header->sound[0], &D_001B2130[0]);
    func_00132828();
}
