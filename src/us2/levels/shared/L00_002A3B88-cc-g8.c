/* func_US2_L00_002A3B88, the USA v2.00 copy of func_L00_002A3B88: the same C, where rename func_00292078 becomes func_US2_00292928; rename func_L00_00303990 becomes func_US2_L00_00304660; rename func_00294F10 becomes func_US2_002957C0; rename func_0029CD48 becomes func_US2_0029DB80; rename func_002B4C18 becomes func_US2_002B5B38; rename func_L00_0036F488 becomes func_US2_L00_003706F0; rename func_L00_002E6348 becomes func_US2_L00_002E6D60; rename func_L00_0037F7E8 becomes func_US2_L00_00380C50; rename func_L00_0037F790 becomes func_US2_L00_00380BF8; rename func_L00_002E6400 becomes func_US2_L00_002E6E18; rename func_002F5FB8 becomes func_US2_002F6E10; rename func_0027C480 becomes func_US2_0027CAE0; .... */
/* func_US2_L00_002A3B88 (RunLevelLoop): clears level state, restores its settings and services frames
 * until loading ends. A -G8 unit of its own. In the loop header the plain `sd` of D_001A7200 and
 * then the volatile T1_COUNT (0x10000800) clear come just before the first jal; the compiler's
 * default set-side volatile rule (GCC 2.95's) leaves that slot empty, as retail does, where the
 * EE tree's rule fills it with the clear of the frame accumulator (docs/build/compiler-notes.md).
 * T1_COUNT (include/common.h) is the EE timer 1 count register, 0x10000800. */
#include "common.h"

/* Partial views of the resident settings, weapon table and per-level statistics. */
typedef struct {
    char reserved00[0x18];
    int mode;
    char reserved1c[10];
    short pending, reset, ready, announce, reserved2e;
    int output;
} SoundSettings;
typedef struct {
    int active;
    unsigned char channel;
    char reserved05[15];
    int sound;
    char reserved18[200];
} WeaponResource __attribute__((aligned(16)));
typedef struct {
    unsigned short visits, reserved;
    unsigned int maximum, visited;
} LevelStatistics;

extern unsigned char D_L00_0025BBA0[];
extern const char D_L00_001A7C88[];
extern int D_L00_001A8F00[] __attribute__((sda));
extern int D_L00_001A8F04, D_L00_001A8F08;
extern int D_L00_001A8ED4, D_L00_001A8FE0;
extern int D_L00_001B19C4[] __attribute__((sda));
extern int D_L00_001B19D4[] __attribute__((sda));
extern int D_L00_001B18D8[] __attribute__((sda));
extern int D_L00_001B1680[] __attribute__((sda));
extern int D_L00_001B1680_1 NOT_SDA;
extern int D_L00_001B19C0;
extern float D_L00_001B19CC;
extern short D_L00_001BCB24 NOT_SDA;
extern int D_001A7290, D_001A72C0;
extern short D_001A7A18;
extern unsigned int D_001A7AF0;
extern unsigned char D_00139568[];
typedef struct {
    unsigned char reserved0000[0x1248];
    int weapon;
    unsigned char reserved124c[0x22c1 - 0x124c];
    unsigned char flush;
} LevelLoopHero;
extern LevelLoopHero D_00189E20;
extern WeaponResource D_L00_00262570[];
extern SoundSettings D_00152C00;
extern int D_001A7904, D_001A79F0, D_001A7398, D_001A7A04;
extern unsigned char D_001A7B1F;
extern unsigned char D_001A7BE8[] __attribute__((sda));
extern unsigned char D_0019B3D2 NOT_SDA;
extern unsigned char D_001395CA NOT_SDA, D_001395E5 NOT_SDA, D_00139629 NOT_SDA;
extern unsigned int D_001A7390;
extern LevelStatistics D_0018C360[];
extern unsigned char D_001A7248[] __attribute__((sda));
extern long D_001A7200 MACRO_ADDR;
typedef struct {
    unsigned char reserved00[0x10];
    int held;
    unsigned char reserved14[0x15c-0x14];
    int pressed;
    int reserved160;
    int alternate;
    int reserved168;
    int transition;
    unsigned char reserved170[0x17c-0x170];
    int counter;
} LevelLoopInput;
extern LevelLoopInput D_001393E0;
extern unsigned short D_0018C9DC NOT_SDA;
extern struct { char reserved00[0x84]; unsigned short resume; } D_0018C958;
extern int D_001A7420, D_001A7424, D_001A7B90;
extern int D_L00_001A7C80 __attribute__((sda));
extern int D_L00_001A7C84 __attribute__((sda));
extern unsigned char D_L00_0021DDB0[];
extern short D_001A63F0 NOT_SDA;
extern unsigned char D_0018D278[];

/* The callees' prototypes, as their definitions in src/ declare them. */
extern void func_00282A88(void *, int);
extern void func_0026FEB8(const char *, ...);
extern void func_002EED08(void), func_00290758(void);
extern void func_US2_00292928(int), func_00292408(int), func_002926B8(int), func_002925F0(int);
extern int func_002AD860(int);
extern int func_US2_L00_00304660(int, int);
extern void func_US2_002957C0(void), func_0028AB70(void), func_US2_0029DB80(void);
extern void func_002C9C20(void);
extern int func_002B49E0(int, int, int, int, unsigned char *);
extern void func_0027D330(int), func_002B6E78(int, int, int), func_002B72E8(int);
extern void func_00133220(void);
extern int func_0011D620(void *, int, int, void *, int, void *, int, void *, void *);
extern void func_US2_002B5B38(void), func_002B7320(void);
extern short func_002B7CE0(int);
extern void func_00294420(int);
extern void func_00280710(void), func_002FC280(void), func_002FC220(void);
extern void func_00284FC0(void), func_L00_002F0930(void), func_00284EA8(void);
extern int func_00132028(void);
extern void func_002B9000(void), func_US2_L00_003706F0(void), func_US2_L00_002E6D60(void);
extern void func_US2_L00_00380C50(void), func_US2_L00_00380BF8(void);
extern void func_L00_0036FA68(void), func_US2_L00_002E6E18(void);
extern void func_US2_002F6E10(void), func_L00_00370408(void), func_US2_0027CAE0(void), func_0027D900(void);
extern void func_US2_002CB860(void), func_US2_L00_002E6E60(void), func_US2_00287140(void), func_US2_0027CB08(void);
extern void func_US2_L00_00375F40(void), func_US2_L00_0037BA50(void), func_US2_002EB740(void);
extern int func_US2_002EA0C0(void);
extern int func_L00_002FC5C8(void), func_L00_002FC5E8(void);
extern void func_00282A28(void), func_L00_0032B288(void), func_L00_002D6FD8(void);
extern void func_US2_00299CF0(void), func_00298178(void), func_0027C540(int);
extern void func_002FC560(unsigned int, unsigned long long);
extern int func_0028E588(int, int);
/* Retail returns the full 64-bit texture descriptor in v0. */
extern unsigned long long func_0028E640(int);
extern void func_0028E868(int, int, int, int, int, int);
extern void func_0028F410(int, int, long long, float, float, float, float, float);
extern void func_0027C660(void), func_002FC3C0(unsigned long);
extern float func_00283CE0(int);
extern int func_001261F0(int);
extern void func_L00_003584B0(void), func_0027B948(void), func_002FC1D8(void);
extern void func_00133230(void), func_002E5FE0(void), func_002B7170(void), func_00288EA0(void);
extern void func_L00_0032B500(int), func_00297670(void *), func_US2_002ED260(void);

/* Clears level state, restores its settings and services frames until loading ends. */
void func_US2_L00_002A3B88(void)
{
    int i, allowed, oldMode, flush, extra, limit, ticks, sound, period;
    float spriteSize;
    float elapsed, angle;
    if (!(((unsigned int)D_L00_0025BBA0 - (unsigned int)&D_L00_001B1680_1) & 15) && !((unsigned int)&D_L00_001B1680_1 & 15)) {
        func_00282A88(&D_L00_001B1680_1, (unsigned int)D_L00_0025BBA0 - (unsigned int)&D_L00_001B1680_1);
    } else {
        func_0026FEB8(D_L00_001A7C88);
        for (i = 0; i < (int)((unsigned int)D_L00_0025BBA0 - (unsigned int)&D_L00_001B1680_1); i++) ((unsigned char *)&D_L00_001B1680_1)[i] = 0;
    }
    func_002EED08();
    D_L00_001A8F00[0] = 0;
    D_L00_001A8F08 = -2;
    D_L00_001A8F04 = 0;
    D_L00_001B19C4[0] = 0;
    func_00290758();
    if (D_001A7290 != D_001A7A18) func_US2_00292928(D_001A7A18);
    {
        int weapon = D_00139568[10];
        if (D_001A72C0 != D_L00_00262570[weapon].channel)
            func_00292408(D_L00_00262570[weapon].channel);
    }
    {
        int output = (D_001A7AF0 >> 16) & 31;
        if (D_00152C00.output != output) func_002926B8(output);
    }
    if (D_00152C00.mode != (D_001A7AF0 & 3)) func_002925F0(D_001A7AF0 & 3);
    if (!D_L00_00262570[D_00139568[D_00189E20.weapon]].active) func_002AD860(10);
    func_US2_L00_00304660(1, 0);
    func_US2_002957C0();
    func_0028AB70();
    func_US2_0029DB80();
    func_002C9C20();
    D_00152C00.ready = 1;
    if (D_00152C00.reset) D_00152C00.reset = 0;
    allowed = 1;
    if (D_00152C00.pending || D_001A7904
        || D_001A79F0 == 0 || D_001A79F0 == 5 || D_001A79F0 == 10 || D_001A79F0 == 15
        || (D_001A79F0 > 20 && D_001A79F0 != 24)
        || (D_001A79F0 == 4 && D_001A7B1F && !D_001395CA)
        || (D_001A79F0 == 9 && D_001395E5)
        || (D_001A79F0 == 14 && !D_0019B3D2))
        allowed = 0;
    if (allowed && D_00152C00.announce) func_002B49E0(6, 1, 6, 0, 0);
    D_00152C00.pending = 0;
    D_001A7904 = 0;
    func_0027D330(4);
    D_L00_001B18D8[0] = 0;
    func_002B6E78(0, 1, 1024);
    func_002B72E8(0);
    if (D_001A79F0 < 28 && !D_001A7BE8[D_001A79F0]) D_001A7BE8[D_001A79F0] = 1;
    if (D_0018C360[D_001A79F0].visits < 65535) D_0018C360[D_001A79F0].visits++;
    if (D_0018C360[D_001A79F0].maximum < D_001A7390) D_0018C360[D_001A79F0].maximum = D_001A7390;
    D_0018C360[D_001A79F0].visited = D_0018C360[D_001A79F0].visited | (1u << D_001A79F0) | 0x80000000u;
    func_00133220();
    func_0011D620(D_001A7248, 3, 0, 0, 0, 0, 0, 0, 0);
    func_US2_002B5B38();
    if (!D_L00_001A8F00[0]) func_002B7320();
    func_002B7CE0(1);
    func_00294420(D_L00_00262570[D_00139568[D_001A7398]].sound);
    func_002B7CE0(1);
    func_00294420(D_L00_00262570[D_00139568[D_001A7A04]].sound);
    func_002B7CE0(1);
    while (!D_L00_001A8ED4) {
        D_L00_001B19D4[0] = 0;
        flush = 0;
        extra = 0;
        D_001A7200 += T1_COUNT;
        T1_COUNT = 0;
        func_00280710();
        func_002FC280();
        func_002FC220();
        func_00284FC0();
        func_L00_002F0930();
        func_00284EA8();
        func_00132028();
        oldMode = D_L00_001A8F00[0];
        switch (oldMode) {
        case -1: case 0:
            func_002B9000();
            func_US2_L00_003706F0();
            if (D_L00_001A7C80 == 1) {
                T1_COUNT = 0;
                func_002B9000();
                func_US2_L00_003706F0();
            }
            func_US2_L00_002E6D60();
            break;
        case 8:
            func_002B9000();
            func_US2_L00_00380C50();
            func_US2_L00_00380BF8();
            break;
        case 7:
            func_002B9000();
            func_L00_0036FA68();
            func_US2_L00_002E6E18();
            break;
        case 1:
            func_US2_002F6E10();
            break;
        case 2:
            func_002B9000();
            func_L00_00370408();
            func_US2_0027CAE0();
            func_0027D900();
            break;
        case 3:
            func_002B9000();
            func_US2_002CB860();
            func_US2_L00_002E6E60();
            break;
        case 4:
            func_002B9000();
            func_US2_00287140();
            func_US2_0027CB08();
            break;
        case 5:
            func_002B9000();
            func_US2_L00_00375F40();
            func_US2_L00_0037BA50();
            break;
        case 6:
            func_002B9000();
            func_US2_002EA0C0();
            func_US2_002EB740();
            break;
        case 9:
            func_002B9000();
            func_L00_002FC5C8();
            func_L00_002FC5E8();
            break;
        case -2: case 10: default:
            func_00282A28();
            break;
        }
        D_L00_001B19C4[0]++;
        func_L00_0032B288();
        if (!D_L00_001A8F00[0]) func_L00_002D6FD8();
        func_US2_00299CF0();
        func_00298178();
        if ((unsigned)(D_001393E0.pressed - 15) < 2 || D_001393E0.alternate == 15 || D_L00_001B1680[0]) {
            if (D_001393E0.transition || D_001393E0.held) {
                D_001393E0.counter = 0;
                D_001A7420 = 21;
                D_001A7424 = 64;
                D_L00_001B1680[0] = 0;
                if (!D_L00_001A8F00[0])
                    func_002B49E0(4, 1, 1, 0, 0);
                else
                    func_002B49E0(4, 2, 1, 0, 0);
            } else if (D_L00_001B1680[0] == -1) {
                if (!D_L00_001A8F00[0]) {
                    if (!D_0018C958.resume) D_0018C958.resume = 1;
                    D_L00_001B1680[0] = 0;
                }
            } else if (!D_L00_001A8F00[0] && !D_0018C9DC) {
                func_002B49E0(4, 1, 2, 0, 0);
                D_L00_001B1680[0] = -1;
            } else {
                if ((unsigned)(D_001393E0.pressed - 15) < 2 || D_001393E0.alternate == 15)
                    D_L00_001B1680[0] = 30;
                else
                    D_L00_001B1680[0] = D_L00_001B1680[0] - 1;
                period = 55;
                func_0027C540(0);
                spriteSize = 272.0f;
                func_002FC560(71, 0x2004bULL);
                func_0028E868(func_0028E588(0x755d, 0), 425, 250, 64, 64, 128);
                angle = ((float)(D_L00_001B18D8[0] % period) * -6.2831854820251465f) / (float)period;
                func_0028F410(64, 64, func_0028E640(func_0028E588(0x755d, 1)), 7312.0f, 4512.0f, spriteSize, spriteSize, angle);
                func_0027C660();
                if (D_001A7420 == 2) D_L00_001B1680[0] = 0;
            }
        }
        func_002FC3C0(1);
        elapsed = func_00283CE0(T1_COUNT);
        D_L00_001B19CC = elapsed * (D_001A7B90 ? 0.00008680556f : 0.00010416667f);
        if (!D_00189E20.flush && !D_L00_001B19D4[0]) {
            if (!D_L00_001A8F00[0]) {
                ticks = T1_COUNT;
                limit = D_001A7B90 ? 11520 : 9600;
                if (D_L00_001A7C80 == 0) {
                    if (limit < ticks) {
                        D_L00_001A7C84 = 0;
                        D_L00_001A7C80 = 1;
                    }
                } else if (D_L00_001A7C80 == 1) {
                    if (D_L00_001A7C84 >= 2) {
                        D_L00_001A7C84 = 0;
                        D_L00_001A7C80 = 2;
                    }
                } else if (D_L00_001A7C80 == 2) {
                    if (D_L00_001A7C84 >= 4 && ticks <= limit) {
                        D_L00_001A7C84 = 0;
                        D_L00_001A7C80 = 3;
                    }
                } else if (D_L00_001A7C80 == 3) {
                    D_L00_001A7C80 = 0;
                    D_L00_001A7C84 = 0;
                }
                D_L00_001A7C84++;
                if (D_L00_001A7C80 == 0) {
                    func_001261F0(0);
                    D_L00_001B18D8[0]++;
                } else if (D_L00_001A7C80 == 1) {
                    D_L00_001B18D8[0]++;
                } else if (D_L00_001A7C80 == 2) {
                    if (limit < ticks) D_L00_001A7C84 = 0;
                    if (!D_L00_001A8F00[0]) {
                        func_002B9000();
                        func_US2_L00_003706F0();
                    } else if (D_L00_001A8F00[0] == 2 && !D_L00_001BCB24) {
                        func_002B9000();
                        func_L00_00370408();
                    }
                    func_L00_002D6FD8();
                    func_001261F0(0);
                    D_L00_001B18D8[0]++;
                } else if (D_L00_001A7C80 == 3) {
                    func_001261F0(0);
                    func_001261F0(0);
                    D_L00_001B18D8[0]++;
                }
                func_L00_003584B0();
            } else if (D_L00_001A8F00[0] == 2) {
                int now = T1_COUNT;
                int budget = D_001A7B90 ? 11520 : 9600;
                if (budget < now && !D_L00_001BCB24) {
                    func_002B9000();
                    func_L00_00370408();
                }
                func_L00_002D6FD8();
                func_L00_003584B0();
                func_001261F0(0);
                D_L00_001B18D8[0]++;
            } else {
                func_001261F0(0);
                D_L00_001A7C80 = 0;
                D_L00_001A7C84 = 0;
                D_L00_001B18D8[0]++;
                func_L00_003584B0();
            }
            D_L00_001A8FE0 = 0;
        }
        func_0027B948();
        if (!D_L00_001A8F00[0] && D_00189E20.flush) { flush = 1; extra = 1; }
        if (flush) {
            func_002FC1D8();
            func_00133230();
            func_00132028();
            func_002E5FE0();
            func_002B7170();
            sound = D_001A63F0;
            if (*(int *)D_L00_0021DDB0) sound = *(int *)(D_L00_0021DDB0 + 0xc64);
            func_00288EA0();
            func_US2_L00_00304660(0, extra);
            func_L00_0032B500(0);
            func_002B6E78(sound, 1, 1024);
            func_0028AB70();
        } else {
            func_US2_002B5B38();
            if (D_L00_001A8F00[0] != oldMode) D_L00_001B19C4[0] = 0;
            if (D_L00_001B19D4[0]) func_002FC1D8();
        }
        if (D_0018C360[D_001A79F0].maximum < D_001A7390) D_0018C360[D_001A79F0].maximum = D_001A7390;
    }
    func_00297670(D_0018D278 + D_001A79F0 * 2048);
    if (D_L00_001B19C0 != D_001A79F0) D_00139629 = D_001A79F0;
    func_US2_002ED260();
}
