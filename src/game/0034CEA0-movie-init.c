#include "ps2_hw.h"
typedef unsigned char u8;
extern char *D_001B23CC[] __attribute__((sda));
extern char *ref_L00_0034F408_00 __attribute__((sda));
extern int D_001B23C8 __attribute__((sda));
extern void func_0026FEB8(void *, ...);
struct AudioDecoderState {
    char pad0[0xD90F8];
    int dmac_handler_id;
    int intc_handler_id;
};
struct AudioDecoderThreadArgs {
    char pad0[4];
    void (*entry)();
    void *stack;
    int stack_size;
    void *gp;
    int priority;
    char pad18[8];
    int gs_tag;
    char pad24[0xC];
};
extern int D_001B23D0 __attribute__((sda));
extern char ref_L00_0034F408_01[];
extern char ref_L00_0034F408_02[] __attribute__((sda));
extern void func_0012F690(void);
extern void func_00350590(u8 *);
extern int func_00351720(void *, int, int, void *, int, int, void *, int);
extern int func_0034F7D8(void *, void *, int, int);
extern int func_00351828(void *, int, int, void *, char *);
extern void func_00351DE8(void *, int, int, int);
extern int func_0011AA20(struct AudioDecoderThreadArgs *);
extern int func_0011AA40(int, void *);
extern int func_00350698(u8 *, int, int);
extern int func_00126DC0(void *);
extern int func_0011A930(int, void *, int);
extern int func_0011B6C0(int);
extern void func_0034FFC0();
extern void func_00350190();
extern void func_00351A80();
extern int func_00350240();
extern int func_00350378();
/* func_0034F408(int, int, int) */
int func_0034F408(int stream_source, int source_mode, int callback_context) {
    struct AudioDecoderThreadArgs decoder_thread;
    int thread_id;
    int opened;
    D_CTRL |= 3;
    D_STAT = 4;
    func_00350590(ref_L00_0034F408_00);
    func_0012F690();
    func_00351720(((char *)D_001B23CC[0]) + 0xD9048, D_001B23C8 + 0x1D05C0, 0xEB768,
                  ((char *)D_001B23CC[0]) + 0x52040, D_001B23C8 + 0x1C7180, 0x100,
                  ((char *)D_001B23CC[0]) + 0xD6040, 0x200);
    func_0034F7D8(((char *)D_001B23CC[0]) + 0xD9100, ((char *)D_001B23CC[0]) + 0x50040, 0x2000,
                  D_001B23C8 + 0x1D01C0);
    func_00351828(((char *)D_001B23CC[0]) + 0xD9048, 0, 0, func_00350240, D_001B23CC[0]);
    func_00351828(((char *)D_001B23CC[0]) + 0xD9048, 3, callback_context, func_00350378, D_001B23CC[0]);
    func_00351DE8(((char *)D_001B23CC[0]) + 0xD9168,
                  (D_001B23C8 & 0x0FFFFFFF) | 0x20000000,
                  D_001B23C8 + 0x1A0000, 2);
    decoder_thread.stack = ((char *)D_001B23CC[0]) + 0xD2040;
    decoder_thread.entry = func_00351A80;
    decoder_thread.stack_size = 0x4000;
    decoder_thread.priority = 1;
    decoder_thread.gp = ref_L00_0034F408_02;
    decoder_thread.gs_tag = 0;
    thread_id = func_0011AA20(&decoder_thread);
    D_001B23D0 = thread_id;
    func_0011AA40(thread_id, ((char *)D_001B23CC[0]) + 0xD9048);
    if (func_00350698(((char *)D_001B23CC[0]) + 0xD9040, stream_source, source_mode) == 0) {
        opened = 0;
        func_0026FEB8(ref_L00_0034F408_01);
    } else {
        opened = 1;
    }
    func_00126DC0(func_0034FFC0);
    ((struct AudioDecoderState *)D_001B23CC[0])->dmac_handler_id = func_0011A930(2, func_00350190, 0);
    func_0011B6C0(2);
    return opened;
}
