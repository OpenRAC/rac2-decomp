#include "include_asm.h"

#include "common.h"
extern void *func_00115484(void *, int, unsigned int);
extern float D_00189EA0[4];
extern float func_L02_002F21C0(void *, void *);
extern int func_L02_004127F8(unsigned char *);
extern int func_PAL_L18_003FF648(unsigned char *, int);
extern unsigned short *D_L18_001FB320[];
extern char *D_L18_001B281C[] __attribute__((sda));
extern int D_L18_001B2838[] __attribute__((sda));
/* Each scan reads the current slot id again when advancing its group iterator. */
static __inline__ int L18_SelectionGroupId(char *p, int i, int base) {
    int off = i << 2;
    int *groups = (int *)(p + base);
    return *(int *)((char *)groups + off);
}

/* Selects the source, secondary member and target from the owner's three group
   lists. The first target scan prefers entries passing the flag and distance tests. */
int func_PAL_L18_003FEA20(char *owner, int slot) {
    char *secondary[2];
    char *state = *(char **)(owner + 0x68);
    char *source = 0;
    char *selected = 0;
    char *entity;
    int i;

    func_00115484(secondary, 0, 8);
    {
        unsigned short *entry;
        for (entry = D_L18_001FB320[L18_SelectionGroupId(state, slot, 0)];
             (L18_SelectionGroupId(state, slot, 0) & 0xff) != 0xff &&
             L18_SelectionGroupId(state, slot, 0) <= D_L18_001B2838[0] && entry != 0 &&
             ((short)entry[-1] >= 0 ||
              entry == D_L18_001FB320[L18_SelectionGroupId(state, slot, 0)]); entry++) {
            entity = D_L18_001B281C[0] + (*entry & 0x7fff) * 0x100;
            if (entity == 0) break;
            if (entity != 0 && *(unsigned char *)(entity + 0x20) != 0xfe &&
                *(unsigned char *)(entity + 0x20) != 0xfd &&
                (*(unsigned short *)(entity + 0x34) & 1) != 0) {
                source = entity;
                break;
            }
        }
    }
    if (source == 0) return 0;
    for (i = 0; i < 1; i++) {
        {
            unsigned short *entry;
            for (entry = D_L18_001FB320[L18_SelectionGroupId(state, slot, 0x20)];
                 (L18_SelectionGroupId(state, slot, 0x20) & 0xff) != 0xff &&
                 L18_SelectionGroupId(state, slot, 0x20) <= D_L18_001B2838[0] && entry != 0 &&
                 ((short)entry[-1] >= 0 ||
                  entry == D_L18_001FB320[L18_SelectionGroupId(state, slot, 0x20)]); entry++) {
                entity = D_L18_001B281C[0] + (*entry & 0x7fff) * 0x100;
                if (entity == 0) break;
                if (entity != secondary[0] && entity != 0 &&
                    *(unsigned char *)(entity + 0x20) != 0xfe &&
                    *(unsigned char *)(entity + 0x20) != 0xfd &&
                    (*(unsigned short *)(entity + 0x34) & 1) != 0) {
                    secondary[i] = entity;
                    break;
                }
            }
        }
    }
    if (secondary[0] == 0) return 0;
    {
        unsigned short *entry;
        for (entity = 0, entry = D_L18_001FB320[L18_SelectionGroupId(state, slot, 0x10)];
             (L18_SelectionGroupId(state, slot, 0x10) & 0xff) != 0xff &&
             L18_SelectionGroupId(state, slot, 0x10) <= D_L18_001B2838[0] && entry != 0 &&
             ((short)entry[-1] >= 0 ||
              entry == D_L18_001FB320[L18_SelectionGroupId(state, slot, 0x10)]); entry++) {
            entity = D_L18_001B281C[0] + (*entry & 0x7fff) * 0x100;
            if (entity == 0) break;
            if (*(unsigned char *)(entity + 0x31) != 0 &&
                func_L02_002F21C0(D_00189EA0, entity + 0x10) > 16.0f &&
                func_L02_004127F8((unsigned char *)entity) == 0) {
                selected = entity;
                break;
            }
        }
    }
    if (selected == 0) {
        {
            unsigned short *entry;
            for (entity = 0, entry = D_L18_001FB320[L18_SelectionGroupId(state, slot, 0x10)];
                 (L18_SelectionGroupId(state, slot, 0x10) & 0xff) != 0xff &&
                 L18_SelectionGroupId(state, slot, 0x10) <= D_L18_001B2838[0] && entry != 0 &&
                 ((short)entry[-1] >= 0 ||
                  entry == D_L18_001FB320[L18_SelectionGroupId(state, slot, 0x10)]); entry++) {
                entity = D_L18_001B281C[0] + (*entry & 0x7fff) * 0x100;
                if (entity == 0) break;
                if (func_L02_004127F8((unsigned char *)entity) == 0) {
                    selected = entity;
                    break;
                }
            }
        }
        if (selected == 0) goto fail;
    }
    func_L18_003F8D28(source, entity, (void *)L18_SelectionGroupId(state, slot, 0x10));
    func_L18_003F7818((unsigned char *)secondary[0], (unsigned char *)source, 0);
    func_PAL_L18_003FF648((unsigned char *)selected, 1);
    return 1;
fail:
    return 0;
}

