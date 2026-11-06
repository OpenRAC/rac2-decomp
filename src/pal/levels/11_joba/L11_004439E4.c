#include "include_asm.h"

typedef unsigned char u8;
typedef unsigned short u16;
extern u8 D_L11_004465F8[];
extern void func_300150(void *);
extern void func_2F8AD0(void *, void *);
extern void func_31F338(void);
extern u8 *D_L11_001FC420[];
extern u8 *D_L11_001B359C __attribute__((section(".sdata")));
extern u8 *D_L11_001FC420[];
extern u8 *D_L11_001B359C;
extern u8 *D_L11_001B368C __attribute__((sda));
extern u8 D_00189E20[];
extern u8 D_001A63A8[];

void func_PAL_L11_004459B8(u8 *obj) {
    u8 *state = *(u8 **)(obj + 0x68);
    u16 *counter = (u16 *)(obj + 0x96);
    if (*counter <= 0xFFFE) {
        *counter = *counter + 1;
    }
    func_300150(state + 0x190);
    func_2F8AD0(D_L11_004465F8, obj);
    func_31F338();
}

