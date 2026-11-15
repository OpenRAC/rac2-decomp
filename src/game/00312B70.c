#include "names.h"
/* func_00312B70: func_002A0F48 takes the object alone (every caller passes one argument);
 * the three 16-byte copies are qcopy(), and the head stores are in the order whose
 * schedule loads the descriptor pointer after the flag stores, as retail does. */
#include "common.h"


extern char *CreateMoby(int);
extern void func_002A0F48(char *);
extern void hero_copy_field_to_moby(char *);

/* Spawns object 0x27F at the given position and fills its descriptor from a template record. */
char *moby_spawn_template_effect(char *tmpl, void *pos, int value, void *origin)
{
    char *obj = CreateMoby(0x27F /* moby class 639 */);
    char *d;

    if (obj != 0) {
        *(unsigned char *)(obj + 0x30) = 0xFF;
        *(unsigned short *)(obj + 0x34) = *(unsigned short *)(obj + 0x34) | 1;
        *(unsigned char *)(obj + 0x31) = 1;
        d = *(char **)(obj + 0x68);
        *(unsigned char *)(obj + 0x20) = 0;
        *(unsigned char *)(obj + 0xBC) = 0;
        qcopy(obj + 0x10, pos);
        if (origin != 0)
            qcopy(d, origin);
        else
            qcopy(d, tmpl);
        *(int *)(d + 0x20) = value;
        *(unsigned short *)(obj + 0x32) = *(unsigned char *)(tmpl + 0x3C);
        *(unsigned char *)(d + 0x24) = *(unsigned char *)(tmpl + 0x10);
        *(unsigned char *)(d + 0x25) = *(unsigned char *)(tmpl + 0x11);
        *(unsigned char *)(d + 0x26) = *(unsigned char *)(tmpl + 0x12);
        *(unsigned char *)(d + 0x27) = *(unsigned char *)(tmpl + 0x13);
        *(unsigned char *)(d + 0x28) = *(unsigned char *)(tmpl + 0x14);
        *(unsigned char *)(d + 0x29) = *(unsigned char *)(tmpl + 0x15);
        *(unsigned char *)(d + 0x68) = *(unsigned char *)(tmpl + 0x3D);
        *(unsigned short *)(d + 0x6C) = *(unsigned short *)(tmpl + 0x40);
        *(unsigned char *)(d + 0x2A) = *(unsigned char *)(tmpl + 0x16);
        *(unsigned char *)(d + 0x2B) = *(unsigned char *)(tmpl + 0x17);
        *(unsigned char *)(d + 0x2C) = *(unsigned char *)(tmpl + 0x18);
        *(unsigned char *)(d + 0x2D) = *(unsigned char *)(tmpl + 0x19);
        *(unsigned char *)(d + 0x2E) = *(unsigned char *)(tmpl + 0x1A);
        *(unsigned char *)(d + 0x69) = *(unsigned char *)(tmpl + 0x3E);
        *(unsigned short *)(d + 0x6E) = *(unsigned short *)(tmpl + 0x42);
        *(unsigned char *)(d + 0x2F) = *(unsigned char *)(tmpl + 0x1B);
        *(unsigned char *)(d + 0x30) = *(unsigned char *)(tmpl + 0x1C);
        *(unsigned char *)(d + 0x31) = *(unsigned char *)(tmpl + 0x1D);
        *(unsigned char *)(d + 0x32) = *(unsigned char *)(tmpl + 0x1E);
        *(unsigned char *)(d + 0x33) = *(unsigned char *)(tmpl + 0x1F);
        *(unsigned char *)(d + 0x6A) = *(unsigned char *)(tmpl + 0x3F);
        *(unsigned short *)(d + 0x70) = *(unsigned short *)(tmpl + 0x44);
        *(float *)(d + 0x34) = *(float *)(tmpl + 0x20);
        *(float *)(d + 0x38) = *(float *)(tmpl + 0x24);
        *(float *)(d + 0x3C) = *(float *)(tmpl + 0x28);
        *(float *)(d + 0x40) = *(float *)(tmpl + 0x2C);
        *(float *)(d + 0x44) = *(float *)(tmpl + 0x30);
        *(unsigned char *)(d + 0x6B) = *(unsigned char *)(tmpl + 0x48);
        *(unsigned short *)(d + 0x72) = *(unsigned short *)(tmpl + 0x46);
        *(int *)(d + 0x48) = *(int *)(tmpl + 0x34);
        *(int *)(d + 0x4C) = *(int *)(tmpl + 0x38);
        *(unsigned char *)(d + 0x1C) = *(unsigned char *)(tmpl + 0x49);
        *(int *)(d + 0x64) = -1;
        func_002A0F48(obj);
        hero_copy_field_to_moby(obj);
    }
    return obj;
}
