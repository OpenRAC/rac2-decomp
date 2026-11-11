/* func_US2_0026EDE8: v2.00's copy of func_0026EDE8 (src/game/0026EA00-loader.c), the boot
 * title loop, with the same flags and source (see that file for what it takes). v2.00 skips
 * table 1 when it unpacks the archive's six resource tables, and sixteen of its callees are
 * v2.00's own functions. As elsewhere in v2.00, the pad's pressed word is at 0x1A4, not 0x1A0. */
#include "common.h"

typedef struct { char *data; int words[3]; } LoaderResource;
typedef struct { int code, count, data, size; } LoaderBank;
typedef struct { int offsets[0x64 / 4]; } LoaderArchive;
typedef struct { char pad[0x18]; LoaderArchive *archive; } LoaderMemory;
typedef struct { char pad[0x32C]; int base; char pad330[0x20]; int offset, count; } LoaderDisc;

/* The memory-card state at D_001393E0 (McState_298F00 in src/game/00298F00.c). */
typedef struct {
    int port, slot, type, free, result, format;
    short status, tries;
    char pad1C[0xA0 - 0x1C];
} BootCard;
typedef struct {
    BootCard card[2];
    char pad140[0x15C - 0x140];
    int state, sub, next_state, next_card;
} BootMemcard;

typedef struct { char pad[0x1A4]; unsigned int pressed; } LoaderPad;
typedef struct { char pad[0x2C]; int count; } LoaderTables;
typedef struct { char pad[0x24CC]; int enabled; } LoaderGame;
typedef struct { char pad[7]; char flag; } LoaderSound;
typedef struct { int active; short *sequence; } LoaderMovie;
typedef struct { char pad[10]; unsigned char index; } LoaderSelection;
typedef struct { char pad[4]; unsigned char mode; char rest[219]; } LoaderOption;
typedef struct { char pad[0x18]; int format; char pad1c[0x14]; int audio; } LoaderSettings;

extern LoaderMemory D_001BAEC0;
extern LoaderDisc D_0014B540;
extern BootMemcard D_001393E0[];
extern LoaderPad D_00138180;
extern LoaderTables D_00254E78;
extern LoaderGame D_00189E20;
extern LoaderSound D_001A63A8;
extern LoaderMovie D_001BAD40;
extern LoaderSelection D_00139568;
extern LoaderOption D_00239BA0[];
extern LoaderSettings D_00152C00;
extern char D_00238C80[], D_01806380[], D_0180DA80[];
extern int D_00138320[];
extern char *D_001B1604 __attribute__((sda));
extern LoaderResource *D_001B1840 __attribute__((sda));
extern LoaderArchive *D_001A7280[] __attribute__((sda));
extern unsigned long long D_001A7200 __attribute__((sda));
extern int D_001A8C88[] __attribute__((sda));
extern int D_001B16A8[] __attribute__((sda)), D_001B16AC[] __attribute__((sda));
extern int D_001A8BB0[] __attribute__((sda)), D_001A8BB4[] __attribute__((sda));
extern int D_001A8BB8[] __attribute__((sda)), D_001A8BBC[] __attribute__((sda));
extern int D_001A8B84[] __attribute__((sda)), D_001B1684[] __attribute__((sda)), D_001B1598[] __attribute__((sda));
extern unsigned char D_001A7BB0[] __attribute__((sda));
extern short D_001A7A10[] __attribute__((sda));
extern int D_001A7290[] __attribute__((sda)), D_001A72C0[] __attribute__((sda));
extern int D_001A7AF0[] __attribute__((sda)), D_001A7B90[] __attribute__((sda)), D_001A72D0[] __attribute__((sda));
extern unsigned short D_001A7AF2[] __attribute__((sda));
extern int D_001A7478 MACRO_ADDR;
extern float D_001B168C MACRO_ADDR;

extern void func_0011AEA0(int);
extern int func_001261F0(int);
extern int func_00132028(void);
extern void func_00133220(void);
extern void func_0026EA00(int);
extern void func_0026EAC8(int);
extern void func_0026EC58(unsigned short *);
extern void func_0027B948(void), func_US2_0027CB08(void), func_US2_0027CB80(void);
extern void func_0027D330(int);
extern void func_00280710(void);
extern void func_00282A28(void);
extern float func_00283CE0(int);
extern int func_00284E80(void);
extern void func_00284EA8(void), func_00284FC0(void), func_00285338(void), func_US2_00287140(void);
extern int func_00288AA0(unsigned char *, int);
extern int func_00288BE8(void *);
extern void func_0028AB70(void);
extern void func_00290758(void), func_00290C60(void);
extern void func_US2_00292650(int *, int);
extern void func_US2_00292928(int), func_00292408(int), func_002925F0(int), func_002926B8(int);
extern void func_US2_00293138(void);
extern void func_US2_002957C0(void);
extern void func_00298178(void), func_US2_00299CF0(void);
extern void func_US2_0029DB80(void);
extern void func_US2_0029E308(int, int);
extern int func_002B49E0(int, int, int, int, unsigned char *);
extern int func_002B4B70(int, int);
extern void func_US2_002B5B38(void);
extern void func_002B67E0(int, int);
extern int func_002B7B18(int, int, int);
extern short func_002B7CE0(int);
extern void func_002B9000(void);
extern void func_002C9C20(void);
extern void func_US2_002CB860(void);
extern int func_US2_002EA0C0(void);
extern void func_US2_002EB740(void);
extern void func_US2_002ED260(void);
extern void func_002EED08(void);
extern void func_US2_002F6E10(void);
extern void func_002FC220(void), func_002FC280(void);
extern void func_002FC3C0(unsigned long long);
extern long long func_002FCB00(int, int, int, int);

static inline BootMemcard *Memcard(void) { BootMemcard *mc = D_001393E0; return mc; }
static inline int CardType(BootMemcard *mc) { return mc->card[0].type; }
static inline int CardFormat(BootMemcard *mc) { return mc->card[0].format; }
static inline int CardStatus(BootMemcard *mc) { return mc->card[0].status; }
static inline int CardFree(BootMemcard *mc) { return mc->card[0].free; }

void func_US2_0026EDE8(void)
{
    LoaderResource *tables[8];
    int counts[8];
    short sequence[32];
    int frames = 0, loaded = 0, state;
    LoaderArchive *archive;
    char *image, *extra;
    float time;

    D_001A8C88[0] = 1;
    func_00290C60();
    {
        LoaderMemory *memory = &D_001BAEC0;
        LoaderDisc *disc = &D_0014B540;
        func_002B7B18((int)memory->archive + 0x400000, disc->offset + disc->base, disc->count);
    }
    while (D_001393E0->state == 2 && D_001393E0->next_state < 0) {
        func_US2_00299CF0();
        func_00298178();
        func_001261F0(0);
    }
    while (D_001393E0->state != 2 || D_001393E0->next_state >= 0) {
        func_US2_00299CF0();
        func_00298178();
        func_001261F0(0);
    }
    for (;;) {
        if (!(CardType(Memcard()) != 2
              || (CardFormat(Memcard()) != 0 && CardStatus(Memcard()) < -1 && CardFree(Memcard()) < 475)))
            break;
        loaded = 1;
        if (D_001393E0->state < 3 && D_001393E0->next_state < 0) {
            if (D_001393E0->card[0].type != 2)
                func_0026EAC8((int)D_01806380);
            else if (D_001393E0->card[0].status != -4)
                func_0026EAC8((int)D_0180DA80);
            if (D_001393E0->next_state < 0) {
                D_001393E0->next_state = 7;
                D_001393E0->next_card = 0;
            }
        }
        func_002B9000();
        func_US2_00299CF0();
        func_00298178();
        if (frames <= 119)
            frames++;
        func_001261F0(0);
        if (frames >= 61) {
            if (D_00138180.pressed & 0xFFFF0FFF)
                break;
        }
    }
    func_00290758();
    if (loaded) {
        int i;
        func_0027D330(5);
        for (i = 29; i >= 0; i--)
            func_001261F0(0);
    }
    {
        LoaderMemory *memory = &D_001BAEC0;
        func_002B7CE0(1);
        func_0011AEA0(0);
        func_US2_0029E308((int)memory->archive + 0x400000, (int)memory->archive);
        func_0011AEA0(0);
        func_002EED08();
        archive = memory->archive;
        func_0026EA00(archive->offsets[0x50 / 4] + (int)archive);
        D_001A7280[2] = memory->archive;
        func_US2_00293138();
        func_002B67E0(archive->offsets[8 / 4] + (int)archive, 0);
        {
            LoaderBank *bank = (LoaderBank *)(archive->offsets[0] + (int)archive);
            D_001B1604 = (char *)bank + bank->code + bank->size;
            func_US2_00292650((int *)((char *)bank + bank->data), bank->count);
        }
    }
    {
        int i, j;
        for (i = 0; i < 6; i++) {
            int *table, *part;
            int count;
            if (i == 1)
                continue;
            table = (int *)(archive->offsets[0x48 / 4] + (int)archive);
            part = (int *)((int)table + table[i]);
            count = part[0];
            part += 2;
            tables[i] = (LoaderResource *)part;
            counts[i] = count;
            for (j = 0; j < counts[i]; j++)
                tables[i][j].data += (int)tables[i] - 8;
        }
    }
    D_00254E78.count = counts[D_001A7BB0[4]];
    D_001B1840 = tables[D_001A7BB0[4]];
    image = (char *)(archive->offsets[0x10 / 4] + (int)archive);
    extra = (char *)(archive->offsets[0x60 / 4] + (int)archive);
    {
        int i;
        for (i = 44; i >= 0; i--)
            func_001261F0(0);
    }
    func_0027D330(30);
    {
        int i;
        for (i = 29; i >= 0; i--)
            func_001261F0(0);
    }
    func_0026EA00(archive->offsets[0x58 / 4] + (int)archive);
    {
        LoaderSound *sound;
        D_00189E20.enabled = 1;
        sound = &D_001A63A8;
        D_001A8BBC[0] = 20;
        D_001B16A8[0] = 20;
        D_001B16AC[0] = (int)D_00238C80;
        sound->flag = 0;
        D_001A8BB8[0] = -2;
        D_001A8BB0[0] = 0;
        D_001A8BB4[0] = 0;
        D_001B1684[0] = 0;
    }
    func_US2_002957C0();
    func_0028AB70();
    func_US2_0029DB80();
    func_002C9C20();
    {
        int i;
        for (i = 24; i >= 0; i--)
            func_001261F0(0);
    }
    func_0027D330(30);
    frames = 1800;
    D_001B1598[0] = 0;
    func_001261F0(0);
    func_00284E80();
    func_00133220();
    D_001A7478 = 3;
    func_00288AA0((unsigned char *)&D_001BAD40, 0xB2);
    func_00288BE8(&D_001BAD40);
    func_US2_002B5B38();
    while (!D_001A8B84[0]) {
        D_001B1840 = tables[D_001A7BB0[4]];
        D_00254E78.count = counts[D_001A7BB0[4]];
        /* T1_COUNT, the timer-1 counter register. */
        D_001A7200 += T1_COUNT;
        T1_COUNT = 0;
        func_00280710();
        func_002FC280();
        func_002FC220();
        func_00284FC0();
        func_00285338();
        func_00284EA8();
        func_00132028();
        state = D_001A8BB0[0];
        switch (state) {
        case -1:
        case 0:
            if (D_001A8BB4[0] == 3 || frames >= 1800) {
                frames = 0;
                func_0026EC58((unsigned short *)sequence);
                D_001BAD40.active = 1;
                D_001A7478 = 2;
                D_001BAD40.sequence = sequence;
                func_00288AA0((unsigned char *)&D_001BAD40, sequence[1]);
                func_00288BE8(&D_001BAD40);
            } else {
                func_002FCB00((int)(image + 0x10), D_001A72D0[3], 512, 416);
                func_002B49E0(3, 1, 6, 0, 0);
            }
            break;
        case 1:
            func_US2_002F6E10();
            if (extra) {
                int i;
                func_0026EA00((int)extra);
                for (i = 29; i >= 0; i--)
                    func_001261F0(0);
                func_0027D330(30);
                extra = 0;
            }
            break;
        case 3:
            frames++;
            func_002B9000();
            if (D_00138320[0])
                frames = 0;
            func_US2_002CB860();
            func_US2_0027CB80();
            if (frames >= 1800) {
                frames = 0;
                func_002B4B70(0, 0);
            }
            break;
        case 4:
            func_002B9000();
            func_US2_00287140();
            func_US2_0027CB08();
            break;
        case 6:
            func_002B9000();
            func_US2_002EA0C0();
            func_US2_002EB740();
            break;
        default:
            func_00282A28();
            break;
        }
        if (D_001A8BB0[0] != state)
            D_001B1684[0] = 0;
        else
            D_001B1684[0]++;
        func_US2_00299CF0();
        func_00298178();
        func_002FC3C0(1);
        time = func_00283CE0(T1_COUNT);
        D_001B168C = time * (D_001A7B90[0] ? 0.0000868055578f : 0.000104166669f);
        func_0027B948();
        func_US2_002B5B38();
        D_001B1598[0]++;
        func_001261F0(0);
    }
    if (D_001A7290[0] != D_001A7A10[4])
        func_US2_00292928(D_001A7A10[4]);
    if (D_001A72C0[0] != (D_00239BA0 + D_00139568.index)->mode)
        func_00292408((D_00239BA0 + D_00139568.index)->mode);
    if (D_00152C00.audio != (D_001A7AF2[0] & 31))
        func_002926B8(D_001A7AF2[0] & 31);
    if (D_00152C00.format != (D_001A7AF0[0] & 3))
        func_002925F0(D_001A7AF0[0] & 3);
    func_US2_002ED260();
}
