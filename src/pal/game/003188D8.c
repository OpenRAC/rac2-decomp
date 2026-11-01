#include "include_asm.h"

INCLUDE_ASM("asm/pal/game", func_PAL_003188D8);

INCLUDE_ASM("asm/pal/game", func_PAL_003192E0);

void func_0027BA48(void);

void func_PAL_00319748(void)
{
  func_003182C0();
  return;
}


#include "common.h"
extern void func_002AEF28(float, float, char *, char *, float, char *);
extern void func_00318200(char *);
extern void func_PAL_002AC3C0(char *, char *);
extern int func_00282978(void *);
extern void func_002AEE70(char *, float, float, char *, float, char *);
extern void func_002AEF28(float, float, char *, char *, float, char *);
extern void func_PAL_002AC3C0(char *, char *);
extern int func_00282978(void *);

void func_PAL_00319768(char *object)
{
    char *data = *(char **)(object + 0x68);
    func_PAL_002AC3C0(object, data + 0x50);
    func_00282978(data + 0x270);
    if (func_00282978(data + 0x272)) {
        func_002AEE70(object, 0.1f, 0.10471977f, data + 0x27C, -1.0f, data + 0x280);
        func_002AEF28(0.13962635397911071777f, 0.031415932f, object, data + 0x284, 0.031415932f, data + 0x288);
    }
    if (*(unsigned short *)(object + 0x96) <= 65534)
        (*(unsigned short *)(object + 0x96))++;
}

