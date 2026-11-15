#include "common.h"
#include "structs.h"

   /* current buffer */
extern short r1_D_0015EDC4;
extern void func_00287E98(void);
extern int D_001A8A64 __attribute__((sda));

/* Sets a flag that tells the menu a confirmation is pending. */
void func_00287E98(void) {
    D_001A8A64 = 1;
}


/* Clears the confirmation-pending flag. */
void func_00287EA8(void) {
    D_001A8A64 = 0;
}

/* 0xE0-byte slots of the table at D_00239BA0; f4A and f4C link the slots. */
typedef struct {
    int f00;
    char pad04[0x46];
    short next;
    short prev;
    char pad4E[0x1E];
    int f6C;
    char pad70[0x1E];
    unsigned short f8E;
    char pad90[0x50];
} Slot287E98;
extern Slot287E98 D_00239BA0[];
extern unsigned char D_00139568[];
extern int D_00139868[];
extern int D_00139688[];

/* The second lookup re-reads D_00139568[index], which cc1 forwards from the stored value. With
   a cast on v instead, index and the link swap $a2/$a3 and the second mult moves ahead of the
   store. */
/* Moves an index to the next entry in its chain and raises its saved values to match that entry. */
void func_00287EB0(int index)
{
    Slot287E98 *s = &gWeaponTable_00239BA0[gItemSlotToRecord[index]];
    short v = s->next;
    if (v == 0) return;
    {
        int x = s->f6C;
        if (x >= 0) {
            x <<= 5;
            if (D_00139868[index] < x) D_00139868[index] = x;
        }
    }
    gItemSlotToRecord[index] = v;
    if (gWeaponTable_00239BA0[gItemSlotToRecord[index]].f00 != 0) gItemAmmoCounts[index] = gWeaponTable_00239BA0[gItemSlotToRecord[index]].f8E;
}

/* Counts how many entries follow the first entry of the chain that contains the given slot. */
int func_00287F60(int index)
{
    int count = 0;
    int i = index;
    while (gWeaponTable_00239BA0[i].prev != 0) i = gWeaponTable_00239BA0[i].prev;
    if (gWeaponTable_00239BA0[i].next != 0) {
        do {
            i = gWeaponTable_00239BA0[i].next;
            count++;
        } while (gWeaponTable_00239BA0[i].next != 0);
    }
    return count;
}

/* Moves a slot to the entry that is n steps along its chain, if the chain is long enough. Returns 1 on success. */
int func_00287FF8(int slot, int n)
{
    int result = 0;
    int i = slot;
    int k;
    if (CountChainEntriesAfterHead(i) >= n) {
        while (gWeaponTable_00239BA0[i].prev != 0) i = gWeaponTable_00239BA0[i].prev;
        if (n > 0) {
            for (k = n; k != 0; k--) i = gWeaponTable_00239BA0[i].next;
        }
        gItemSlotToRecord[slot] = (unsigned char)i;
        result = 1;
    }
    return result;
}
