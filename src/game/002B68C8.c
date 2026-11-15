#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;
typedef unsigned int u32;
extern u8 D_001A63A8[];
extern void func_002B66F0(void);
extern void func_002B6938(void);
extern void func_0026FEB8(void *);
extern char D_001AA198[];

/* Resident file-load state and three streaming channel records. */
typedef struct {
    u8 pad0[0x24]; int handle; u8 pad28[0x14]; short mode;
    u8 pad3e[2]; u8 flags[4]; u32 busy0; u8 pad48[6]; short step0;
    u8 pad50[0x18]; u32 busy1; u8 pad6c[6]; short step1;
    u8 pad74[0x18]; u32 busy2; u8 pad90[6]; short step2;
} InitState;

/* Sets the music and file-load state to its starting values and registers the load callbacks. */
void func_002B68C8(void)
{
    InitState *s;
    int mode;
    STUB_printf(D_001AA198);
    s = (InitState *)gMusicState;
    mode = -1;
    s->mode = mode;
    s->flags[0] = 0x20;
    s->flags[1] = 0;
    s->flags[2] = 0;
    s->flags[3] = 0;
    s->busy0 = 0;
    s->step0 = 0;
    s->busy1 = 0;
    s->step1 = 0;
    s->busy2 = 0;
    s->step2 = 0;
    s->handle = mode;
    RunSoundSetupSequence();
    RegisterDiscReadCallback();
}
