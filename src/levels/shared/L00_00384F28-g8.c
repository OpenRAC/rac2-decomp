#include "include_asm.h"
#include "names.h"
extern unsigned char *D_L00_001B1EA4[] __attribute__((sda));
extern unsigned char *D_L00_001AC0C0[] __attribute__((sda));
extern unsigned char *D_L00_001B1EA0[] __attribute__((sda));
extern void func_L00_00383B90(void *);


/* func_L00_00383B90 passes its object in a0; this handler does not read it. */
/* Runs the update function of every live object of the same kind as the first one, plus every hover bomb. */
void func_L00_00384F28(void *self)
{
    unsigned char *object=D_L00_001B1EA0[0];
    short classId=*(short *)(D_L00_001AC0C0[0]+0xAA);
    while ((unsigned int)object < (unsigned int)D_L00_001B1EA4[0]) {
        if (object && *(short *)(object+0xAA)==classId && object[0x20]!=0xFE && object[0x20]!=0xFD && object!=D_L00_001AC0C0[0])
            (*(void (**)(void *))(object+0x64))(object);
        else if (object && *(short *)(object+0xAA)==0x5D8 /* Hoverbomb Projectile */ && object[0x20]!=0xFE && object[0x20]!=0xFD && *(void (**)(void *))(object+0x64)==UpdateTwoPlayerGoalController)
            (*(void (**)(void *))(object+0x64))(object);
        object+=0x100;
    }
}
