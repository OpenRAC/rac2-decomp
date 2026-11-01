#include "include_asm.h"
extern int func_002DE3A0(int);
extern int func_002DE550(int);
extern int func_002C9A60(void);
extern void func_00287E80(void);
extern void func_00339760(void *);
extern volatile int D_001A8C88;
extern char *D_001A8CFC __attribute__((sda));

int func_US2_002DD7E8(char *object)
{
    func_002DE3A0(1);
    *(int *)(object + 0x48) = func_002DE550(0);
    *(int *)(object + 0x4C) = 0;
    func_002C9A60();
    func_00287E80();
    if (D_001A8C88 != 0 && D_001A8CFC != 0)
        func_00339760(D_001A8CFC + 0x3CEA0);
    return 0;
}

typedef struct {
    int first, second, third, fourth;
    char stamp[8];
    int invalid;
} SlotEntry_002DC900;
typedef struct {
    char pad000[0x8];
    int state;
    char pad00C[0x30 - 0xC];
    SlotEntry_002DC900 entries[4];
    char pad0A0[0x15C - 0xA0];
    int mode;
    int pad160;
    int selected;
} Slots_002DC900;
extern Slots_002DC900 D_001393E0;
extern char D_001F2840[];
extern int D_00258D70[];
extern int D_001ABBEC __attribute__((sda));
extern void func_0027C540(long);
extern void func_0027C660(void);
extern char *func_00288FB8(int);
extern char *func_002DF1F8(char *, int);
extern void func_0027FAA8(int, int, unsigned long, char *, int);

/* Menu line for the current slot: prints its name (and the follow-up line)
   while the menu is in its listing state. */
int func_US2_002DD630(int *box)
{
    char buf[64];
    char *g = D_001F2840;
    Slots_002DC900 *s = &D_001393E0;
    int idx;
    int next;
    int y;

    idx = s->entries[*(int *)(*(char **)(*(char **)(g + 0x14) + 0xE8) + 0x40)].first % 0x1C;
    func_0027C540(0);
    if (s->mode < 3 && s->selected < 0 && *(int *)(g + 0x164) >= 11 && s->state == 2) {
        if (idx == -1) {
            func_0027FAA8(box[6], box[7] + D_001ABBEC / 2, 0x80F0F0F0, func_00288FB8(0x2DAA), -1);
        } else {
            next = D_00258D70[idx * 2 + 1];
            y = 0;
            if (next < 0) y = D_001ABBEC >> 1;
            func_0027FAA8(box[6], box[7] + y, 0x80F0F0F0, func_002DF1F8(buf, idx), -1);
            if (next >= 0) {
                func_0027FAA8(box[6], box[7] + D_001ABBEC, 0x80F0F0F0, func_00288FB8(D_00258D70[idx * 2 + 1]), -1);
            }
        }
    }
    func_0027C660();
    return 2;
}
