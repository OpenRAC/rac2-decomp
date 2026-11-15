#include "common.h"

typedef int TI128 __attribute__((mode(TI)));
extern u8 *func_0029EFD0(int);
extern void func_0026FEB8(const char *, ...);
extern char ref_L02_003C0890_00[];

/* Known actor prefix; later fields and complete extent remain unspecified. */
struct ActorPrefix {
    TI128 first, position;
    u8 reserved20[0x10];
    u8 mode, active;
    u16 kind, flags;
};

void func_L02_003C0890(u8 *object) {
    u8 *data = *(u8 **)(object + 0x68);
    u8 *child;
    if (object[0x20] == 0) {
        *(int *)(data + 4) = 0;
        object[0x20] = 1;
        object[0x30] = 0x80;
        {
            f32 heading = *(f32 *)(object + 0xF8);
            int value = *(int *)(data + 0x14);
            *(int *)(data + 8) = 0;
            *(f32 *)(data + 0x10) = heading;
            *(int *)(data + 0x18) = value;
        }
        child = CreateMoby(0xAFC);
        *(u8 **)(data + 0x1C) = child;
        if (child) {
            child[0x30] = object[0x30];
            {
                struct ActorPrefix *metadata = *(struct ActorPrefix **)(data + 0x1C);
                metadata->kind = ((struct ActorPrefix *)object)->kind;
            }
            {
                struct ActorPrefix *snapshot = *(struct ActorPrefix **)(data + 0x1C);
                snapshot->position = ((struct ActorPrefix *)object)->position;
            }
            {
                struct ActorPrefix *flags = *(struct ActorPrefix **)(data + 0x1C);
                flags->flags |= 0x41;
            }
        } else {
            STUB_printf(ref_L02_003C0890_00, *(short *)(object + 0xB2));
        }
    }
}
