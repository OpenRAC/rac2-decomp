/* func_PAL_L22_003A83A8 (3,008 bytes, levels 22 and 23): the PAL copy of the HUD counters panel,
 * func_L22_003A5018 in v1.01 (src/levels/shared/L22_003A5018-hud-g8.c), with the same C and flags
 * (-O2 -G8 -ffunction-sections -g -frac2-sched-global-yield, config/cflags.txt). Only the two text
 * ids change: 0x2FA3 and 0x2F2C become 0xEC8 and 0xE51.
 */
#include "common.h"

extern u8 * D_L22_001A904C MACRO_ADDR;
extern int D_L22_001B2980 MACRO_ADDR;
extern float D_L22_001B2984 MACRO_ADDR;
extern int D_0018B694 NOT_SDA;
extern int D_L22_001B2AA8 MACRO_ADDR;
extern int D_001A7340 MACRO_ADDR;
typedef struct HudCounters {
    int unknown[2];
    int rightCount;
    int rightIcons;
    int unknown10[2];
    int leftCount;
    int leftIcons;
} HudCounters;
extern HudCounters D_L22_001B1910 NOT_SDA;
extern char D_L22_001AF4D8[] NOT_SDA;
extern int D_L22_001B2AC8 MACRO_ADDR;
extern int D_L22_001B2ACC MACRO_ADDR;
extern int D_L22_001B2AD0 MACRO_ADDR;
extern u64 D_L22_001AF418 MACRO_ADDR;
extern u64 D_L22_001AF428 MACRO_ADDR;
extern u8 *ref_L22_003A5018_00 __attribute__((sda));
extern float ref_L22_003A5018_01 __attribute__((sda)), ref_L22_003A5018_02 __attribute__((sda));
extern u64 ref_L22_003A5018_03 __attribute__((sda)), ref_L22_003A5018_04 __attribute__((sda));
extern int ref_L22_003A5018_05 __attribute__((sda));
extern float ref_L22_003A5018_06 __attribute__((sda));
extern int ref_L22_003A5018_07 __attribute__((sda));
extern int ref_L22_003A5018_08 __attribute__((sda));
extern int ref_L22_003A5018_09 __attribute__((sda));
extern int ref_L22_003A5018_10 __attribute__((sda));
extern int ref_L22_003A5018_11 __attribute__((sda));
extern int ref_L22_003A5018_12 __attribute__((sda));
extern int ref_L22_003A5018_13 __attribute__((sda));
extern int ref_L22_003A5018_14 __attribute__((sda));
extern int ref_L22_003A5018_15 __attribute__((sda));
extern int ref_L22_003A5018_16 __attribute__((sda));
extern int ref_L22_003A5018_17 __attribute__((sda));
extern int ref_L22_003A5018_18 __attribute__((sda));
extern int ref_L22_003A5018_19 __attribute__((sda));
extern int ref_L22_003A5018_20 __attribute__((sda));
extern int ref_L22_003A5018_21 __attribute__((sda));
extern int ref_L22_003A5018_22 __attribute__((sda));
extern int ref_L22_003A5018_23 __attribute__((sda));
extern int ref_L22_003A5018_24 __attribute__((sda));
extern int ref_L22_003A5018_25 __attribute__((sda));
extern int ref_L22_003A5018_26 __attribute__((sda));
extern int ref_L22_003A5018_27 __attribute__((sda));
extern int ref_L22_003A5018_28 __attribute__((sda));
extern int ref_L22_003A5018_29 __attribute__((sda));
extern int ref_L22_003A5018_30 __attribute__((sda));
extern int ref_L22_003A5018_31 __attribute__((sda));
extern int ref_L22_003A5018_32 __attribute__((sda));
extern int ref_L22_003A5018_33 __attribute__((sda));
extern int ref_L22_003A5018_34 __attribute__((sda));
extern int ref_L22_003A5018_35 __attribute__((sda));
extern int ref_L22_003A5018_36 __attribute__((sda));
extern int ref_L22_003A5018_37 __attribute__((sda));
extern int ref_L22_003A5018_38 __attribute__((sda));
extern int ref_L22_003A5018_39 __attribute__((sda));
extern int ref_L22_003A5018_40 __attribute__((sda));
extern int ref_L22_003A5018_41 __attribute__((sda));
extern u8 ref_L22_003A5018_42[] SDATA(ref_L22_003A5018_42);
extern int ref_L22_003A5018_43 __attribute__((sda));
extern int ref_L22_003A5018_44 __attribute__((sda));

extern int func_00336D50(void *, int);
extern void func_00300A00(void *, unsigned int, float, float, float, float, float);
extern int func_0028E588(int, int);
extern void func_0028EA58(void *, int, int, int, int, void *);
extern void func_0027EAE8(int, int, int, int, int, void *);
extern int func_00115DA8(char *, char *, ...);
extern int func_001157AC(char *);
extern int func_0027FB40(int, int, u64, char *, int);
extern char *func_00288FB8(int);
extern int func_L00_0030DD70(int, int);
extern void func_0029CC50(int, int, int);
extern int func_00282948(void *);
extern void func_002802E0(void *, int, int, int, int, int, int, int, int);
extern void func_0029B888(void *, unsigned int, char *, int, int, int, int, char *, int, int);
extern void func_L00_0030CF60(void);

extern int D_L22_001B2980;
static __inline__ int label_y(void *handle, float value, float scale, float half, int active)
{
    int mode = D_L22_001B2980;
    float scaled = value * scale + half;
    int result = (int)scaled;
    void *copy;

    if (mode == active)
        scaled = scale;
    if (handle != 0)
        scaled = scale;
    copy = handle;
    if (copy != 0)
        scaled = half;
    return result;
}

static __inline__ int screen_coord(int mode, float value, float offset)
{
    float scaled = value * D_L22_001B2984 + 0.5f;

    if (mode == 1)
        return (int)(scaled + offset);
    return (int)scaled;
}

int func_PAL_L22_003A83A8(void) {
    char textBuffer[64];
    char *text;
    union { u64 d[2]; u32 w[4]; } colours;
    u8 box[32];
    u8 *obj = ref_L22_003A5018_00;
    u8 *ctl = *(u8 **)(obj + 0x68);
    int y;
    int one, one2;
    int colour;
    char *label, *hint;

    {
        void *sprite = (void *)(u32)func_00336D50(D_L22_001A904C + 0x8710, 0xC3);
        float sy = (float)screen_coord(D_L22_001B2980, ref_L22_003A5018_02, 3.0f);
        func_00300A00(sprite, 0x60442D00, ref_L22_003A5018_01, sy, 1.0f, 1.0f, 0.0f);
    }
    {
        void *sprite = (void *)(u32)func_00336D50(D_L22_001A904C + 0x8710, 0xC4);
        float sy = (float)screen_coord(D_L22_001B2980, ref_L22_003A5018_02, 3.0f);
        func_00300A00(sprite, 0x60241700, ref_L22_003A5018_01, sy, 1.0f, 1.0f, 0.0f);
    }
    {
        void *sprite = (void *)(u32)func_00336D50(D_L22_001A904C + 0x8710, 0xC5);
        float sy = (float)screen_coord(D_L22_001B2980, ref_L22_003A5018_02, 3.0f);
        func_00300A00(sprite, 0x55F0C070, ref_L22_003A5018_01, sy, 1.0f, 1.0f, 0.0f);
    }
    {
        void *sprite = (void *)(u32)func_00336D50(D_L22_001A904C + 0x8710, 0xC3);
        float sy = (float)screen_coord(D_L22_001B2980, ref_L22_003A5018_02, 3.0f);
        func_00300A00(sprite, 0x60442D00, ref_L22_003A5018_01, sy, -1.0f, 1.0f, 0.0f);
    }
    {
        void *sprite = (void *)(u32)func_00336D50(D_L22_001A904C + 0x8710, 0xC4);
        float sy = (float)screen_coord(D_L22_001B2980, ref_L22_003A5018_02, 3.0f);
        func_00300A00(sprite, 0x60241700, ref_L22_003A5018_01, sy, -1.0f, 1.0f, 0.0f);
    }
    {
        void *sprite = (void *)(u32)func_00336D50(D_L22_001A904C + 0x8710, 0xC5);
        float sy = (float)screen_coord(D_L22_001B2980, ref_L22_003A5018_02, 3.0f);
        func_00300A00(sprite, 0x55F0C070, ref_L22_003A5018_01, sy, -1.0f, 1.0f, 0.0f);
    }
    one = 1;
    { void *sprite = (void *)(u32)func_0028E588(0xEAA4, one);
    func_0028EA58(sprite, ref_L22_003A5018_14, label_y(sprite, (float)ref_L22_003A5018_15, D_L22_001B2984, 0.5f, 1), ref_L22_003A5018_16, ref_L22_003A5018_17, ref_L22_003A5018_42); }
    { void *sprite = (void *)(u32)func_0028E588(0xEAA4, 0);
    func_0028EA58(sprite, ref_L22_003A5018_18, label_y(sprite, (float)ref_L22_003A5018_19, D_L22_001B2984, 0.5f, 1), ref_L22_003A5018_20, ref_L22_003A5018_21, ref_L22_003A5018_42); }

    {
        float ratio = (float)D_0018B694 / (float)*(short *)(ctl + 0x324);
        int x, width;
        colours.d[0] = ref_L22_003A5018_03;
        width = ref_L22_003A5018_12;
        x = ref_L22_003A5018_09 + ref_L22_003A5018_07 + ref_L22_003A5018_13;
        y = ref_L22_003A5018_10 + ref_L22_003A5018_08 / 2 - ref_L22_003A5018_11 / 2;
        ref_L22_003A5018_43++;
        colours.d[1] = D_L22_001AF418;
        colours.w[1] = (colours.w[1] & 0xFFFF00FF) | ((int)(ratio * 255.0f) << 8);
        func_0027EAE8(x, y, x + (int)(ratio * (float)width), y + ref_L22_003A5018_11, 0xFFFFF1, &colours);
    }
    {
        float ratio = *(float *)(ctl + 0x20) / (float)D_L22_001B2AA8;
        int right, width, height;
        colours.d[0] = ref_L22_003A5018_04;
        width = ref_L22_003A5018_12;
        right = D_001A7340 - ref_L22_003A5018_09 - ref_L22_003A5018_07 - 4;
        colours.w[0] = (colours.w[1] & 0xFFFF00FF) | ((int)(ratio * 255.0f) << 8);
        height = ref_L22_003A5018_11;
        colours.d[1] = D_L22_001AF428;
        func_0027EAE8(right - (int)(ratio * (float)width), y, right, y + height, 0xFFFFF1, &colours);
    }

    {
        void *sprite = (void *)(u32)func_0028E588(0xEAA5, 0);
        func_0028EA58(sprite, ref_L22_003A5018_22, screen_coord(D_L22_001B2980, (float)ref_L22_003A5018_23, 1.0f), ref_L22_003A5018_24, ref_L22_003A5018_25, ref_L22_003A5018_42);
    }
    {
        void *sprite = (void *)(u32)func_0028E588(0xEAA5, 0);
        func_0028EA58(sprite, ref_L22_003A5018_26, screen_coord(D_L22_001B2980, (float)ref_L22_003A5018_27, 1.0f), ref_L22_003A5018_28, ref_L22_003A5018_29, ref_L22_003A5018_42);
    }
    one2 = 1;
    func_00115DA8(textBuffer, D_L22_001AF4D8, D_L22_001B1910.leftCount);
    text = textBuffer;
    {
    int value = label_y(obj, (float)ref_L22_003A5018_33, D_L22_001B2984, 0.5f, 1);
    colour = ref_L22_003A5018_30;
    func_0027FB40(ref_L22_003A5018_32, value, colour, text, func_001157AC(text));
    }
    func_00115DA8(text, D_L22_001AF4D8, D_L22_001B1910.rightCount);
    {
    int value = label_y((void *)colour, (float)ref_L22_003A5018_35, D_L22_001B2984, 0.5f, 1);
    colour = ref_L22_003A5018_30;
    func_0027FB40(ref_L22_003A5018_34, value, colour, text, func_001157AC(text));
    }
    if (D_L22_001B1910.leftIcons) {
        void *sprite = (void *)(u32)func_0028E588(0xEAA5, one2);
        func_0028EA58(sprite, ref_L22_003A5018_36, screen_coord(D_L22_001B2980, (float)ref_L22_003A5018_37, 1.0f), ref_L22_003A5018_40, ref_L22_003A5018_41, ref_L22_003A5018_42);
    }
    if (D_L22_001B1910.leftIcons >= 2) {
        void *sprite = (void *)(u32)func_0028E588(0xEAA5, 1);
        int x = ref_L22_003A5018_36 + ref_L22_003A5018_44;
        func_0028EA58(sprite, x, screen_coord(D_L22_001B2980, (float)ref_L22_003A5018_37, 1.0f), ref_L22_003A5018_40, ref_L22_003A5018_41, ref_L22_003A5018_42);
    }
    if (D_L22_001B1910.rightIcons) {
        void *sprite = (void *)(u32)func_0028E588(0xEAA5, 1);
        func_0028EA58(sprite, ref_L22_003A5018_38, screen_coord(D_L22_001B2980, (float)ref_L22_003A5018_39, 1.0f), ref_L22_003A5018_40, ref_L22_003A5018_41, ref_L22_003A5018_42);
    }
    if (D_L22_001B1910.rightIcons >= 2) {
        void *sprite = (void *)(u32)func_0028E588(0xEAA5, 1);
        int x = ref_L22_003A5018_38 - ref_L22_003A5018_44;
        func_0028EA58(sprite, x, screen_coord(D_L22_001B2980, (float)ref_L22_003A5018_39, 1.0f), ref_L22_003A5018_40, ref_L22_003A5018_41, ref_L22_003A5018_42);
    }
    if (D_L22_001B2AC8 != -1 && obj[0x95] != 10) {
        switch (D_L22_001B2AC8) {
        case 0: func_L00_0030DD70((int)func_00288FB8(0xEC8), -1); break;
        case 2: func_00288FB8(0x1241); func_0029CC50(0x1241, *(short *)(ctl + 0x32C), -1); break;
        case 1: func_00288FB8(0x1240); func_0029CC50(0x1240, D_L22_001B2ACC, -1); break;
        }
        ref_L22_003A5018_05 = 0;
        func_00282948(&D_L22_001B2AD0);
        if (D_L22_001B2AD0 <= 0) D_L22_001B2AC8 = -1;
    }
    if (ref_L22_003A5018_31) {
        func_002802E0(box, 240, 480, 44, 468, 256, label_y(ctl, 320.0f, ref_L22_003A5018_06, 0.5f, 1), 16, 3);
        label = func_00288FB8(0x9FC);
        hint = func_00288FB8(0xE51);
        func_0029B888(box, 0x80F0F0F0, label, 0, 0, -1, 0, hint, 0, 0);
    }
    func_L00_0030CF60();
    return 1;
}
