#include "include_asm.h"

#include "common.h"
extern unsigned char D_001395B8[0x100];
extern void func_00282CF0(void *, void *, void *);
extern char *D_L02_001B359C __attribute__((sda));
extern int D_001A79F0[] __attribute__((sda));
extern unsigned char D_0019B2E8[];
extern unsigned char D_001395B8[];
struct PortalPlayer {
    char pad0[0x80];
    float pos[4];
    char pad90[0x182];
    short state;
    char pad214[0x128];
    char *portal;
    int active;
    char pad344[0x21ac];
    unsigned char flag;
};
extern struct PortalPlayer D_00189E20;
extern unsigned char D_00189EA0[];
extern unsigned char D_001A7BC8[] __attribute__((sda));
extern unsigned int D_00138324 __attribute__((nosda));
extern unsigned char D_L02_001C0700[];
extern void func_PAL_002A7E68(void *, int, int, int);
extern void func_002A7750(void *, int, int);
extern void func_L00_003294F0(void *, int);
extern void func_L00_003672F8(void);
extern void func_PAL_L02_003294D8(int, int);
extern void func_002DF3F8(void *, void *);
extern void func_PAL_002AFC10(int);
extern void func_002AFDD8(void *, void *, void *, int);
extern void func_002B0C28(int, int, int);
extern void func_00288CB0(int, int);
extern int func_00288AA0(void *, int);
extern int func_00288BE8(void *);
extern void func_L02_00404778(void);
extern void func_002F5CB8(void (*)(void), void *);
extern void func_002AD7B8(int);

void func_PAL_L02_00408E78(char *obj) {
    char *d = *(char **)(obj + 0x68);
    float v[4];
    int dest;

    switch (*(unsigned char *)(obj + 0x20)) {
    case 0: {
        int zone;
        if (*(unsigned char *)(obj + 0x43) != 2) func_PAL_002A7E68(obj, 2, 0, 1);
        func_002A7750(obj, 1, -1);
        *(unsigned char *)(obj + 0x30) = 255;
        if (D_001A79F0[0] == 26) *(short *)(obj + 0x32) = 255;
        qcopy(d + 0x20, obj + 0x10);
        qcopy(d + 0x30, obj + 0xf0);
        zone = D_001A79F0[0] << 4;
        *(short *)(d + 0x1e) = D_0019B2E8[*(unsigned char *)(obj + 0xb0) + zone] >> 7;
        if (D_0019B2E8[*(unsigned char *)(obj + 0xb0) + zone] & 0x80) {
            if (*(int *)(d + 4)) func_L00_003294F0(D_L02_001B359C + (*(int *)(d + 4) << 8), 1);
        }
        if (D_001A79F0[0] == 2 && D_001395B8[0x71] == 26) {
            func_L00_003672F8();
            D_001395B8[0x71] = 1;
            func_PAL_L02_003294D8(*(int *)(d + 0x14), *(int *)(d + 0x10));
            func_002DF3F8(D_00189EA0, D_00189EA0 + 0x10);
            if (D_001A7BC8[4] && !D_001395B8[0xa5]) {
                D_001395B8[0xa5] = 1;
                func_PAL_002AFC10(4);
            }
        }
    }
    case 1:
        if (D_00189E20.portal == obj && D_00189E20.active) {
            func_00282CF0(v, D_00189E20.pos, obj + 0x10);
            func_002AFDD8(obj, v, v, 0);
            if (v[2] < -0.6f) {
                int currentLevel;
                currentLevel = D_001A79F0[0];
                D_00189E20.state = 2;
                dest = 2;
                if (currentLevel == 26) {
                    func_002B0C28(8, 0x1303, 1);
                } else {
                    func_002B0C28(8, D_0019B2E8[*(unsigned char *)(obj + 0xb0) + (currentLevel << 4)] & 0x80 ? 0x131F : 0x1302, 1);
                    dest = 26;
                }
                if (D_00138324 & 0x10) {
                    func_002DF3F8(D_00189EA0, D_00189EA0 + 0x10);
                    func_00288CB0(dest, 1);
                    if (dest == 26) D_001395B8[1] = 1;
                }
            }
        }
        if (D_001A79F0[0] == 26 && (D_0019B2E8[0x1a0 + *(unsigned char *)(obj + 0xb0)] & 0x80)) {
            if (D_001A7BC8[4]) return;
            if (func_00288AA0(D_L02_001C0700, 0xa7)) {
                func_00288AA0(D_L02_001C0700, 4);
                func_00288AA0(D_L02_001C0700, 0xa8);
                func_00288BE8(D_L02_001C0700);
                func_002F5CB8(func_L02_00404778, obj);
                D_00189E20.flag = 0;
                func_002AD7B8(4);
                func_002A7750(obj, 3, -1);
            }
        }
        break;
    }
}
