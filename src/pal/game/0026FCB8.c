#include "include_asm.h"
#include "names.h"

typedef struct { char pad[0x32C]; int base; int offset; int count; } Table26FE48;
extern Table26FE48 g_copy_setup_data;
extern char D_001C5540[];
extern int D_001A730C __attribute__((sda));
extern unsigned long long D_001A7468 __attribute__((sda));
extern int load_read_disc_with_pause(char *, int, int);
extern void LoadPifAsPSMT8H(char *, unsigned long long *, int, int);

void func_PAL_0026FCB8(void)
{
    unsigned long long local[4];
    char *data = D_001C5540;
    load_read_disc_with_pause(data, g_copy_setup_data.offset + g_copy_setup_data.base, g_copy_setup_data.count);
    LoadPifAsPSMT8H(data, local, D_001A730C, 0x3FFC00);
    *(volatile unsigned long long *)&D_001A7468 = local[0];
}

