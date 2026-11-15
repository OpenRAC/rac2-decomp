#include "common.h"

typedef struct {
    int id, kind, classId, price, marked, upgrade;
} Menu6608Entry;
typedef struct {
    char pad[0x140];
    Menu6608Entry entries[64];
    int count;
    int locked;
} Menu6608State;
typedef struct {
    int active;
    unsigned char type;
    char pad5[0xF];
    int classId;
    char pad18[0x54];
    int cost;
    char pad70[0x18];
    unsigned short ammo;
    char pad8A[0x56];
} Menu6608Item;
extern char D_0021F240[];
#define MENU_STATE ((Menu6608State *)D_0021F240)
extern Menu6608Item D_00239BA0[];
/* Through a pointer, so the slot index is evaluated before the table's address. */
#define MENU_ITEMS ((Menu6608Item *)D_00239BA0)
extern unsigned char D_00139568[];
extern unsigned char D_001A7B68[] MACRO_ADDR;
extern unsigned char D_001A7AF8[] MACRO_ADDR;
extern int D_00262E40[][5];
extern int func_00288D58(void);
extern int func_002883E8(int);
extern int func_00287F60(int);
extern void func_002FADB0(void);

static __inline__ int menu6608Special(int id)
{
    int special = 0;
    switch (id) {
    case 12: case 14: case 17: case 18: case 53:
        special = 1;
    }
    return special;
}
#define MENU6608_TYPE_OK(type, id) ((type) >= 2 || ((type) == 1 && menu6608Special(id)))
static __inline__ int menu6608TypeOk(int id)
{
    int n = CountChainEntriesAfterHead(id);
    if (MENU6608_TYPE_OK(n, id)) return 1;
    return 0;
}
static __inline__ int menu6608CanUpgrade(int id)
{
    int eligible = 0;
    int result;
    if (MENU_ITEMS[gItemSlotToRecord[id]].active) {
        result = menu6608TypeOk(id);
    } else {
        result = 0;
    }
    if (result) eligible = id != 16;
    return eligible;
}
static __inline__ int menu6608HasType(int id)
{
    Menu6608Item *item = &MENU_ITEMS[gItemSlotToRecord[id]];
    if (item->active && MENU6608_TYPE_OK(item->type, id)) return 1;
    return 0;
}

/* Builds the vendor's weapon and upgrade list: which weapons can be bought, upgraded or refilled with ammo. Removes duplicate entries at the end. */
void func_002F6608(int hideUnowned)
{
    int listLen, id;

    if (IsFlagByteSet()) {
        int i;
        for (i = 0; i < 56; i++) {
            if (i != 10 && MENU_ITEMS[gItemSlotToRecord[i]].active)
                StoreHelpIdInSlotList(i);
        }
    }
    for (listLen = 0; listLen < 32; listLen++) {
        if (D_001A7B68[listLen] == 255) break;
    }
    MENU_STATE->count = 0;
    if (!MENU_STATE->locked) {
        int i;
        for (i = 0; i < listLen; i++) {
            if (D_001A7B68[i] == 255) continue;
            id = D_001A7B68[i] & 63;
            if (gItemOwnedFlags[id] && menu6608CanUpgrade(id) && !menu6608HasType(id) && MENU_ITEMS[gItemSlotToRecord[id]].cost <= 0 && IsFlagByteSet()) {
                int classId = MENU_ITEMS[gItemSlotToRecord[id]].classId;
                MENU_STATE->entries[MENU_STATE->count].id = id;
                MENU_STATE->entries[MENU_STATE->count].kind = 0;
                MENU_STATE->entries[MENU_STATE->count].marked = 0;
                MENU_STATE->entries[MENU_STATE->count].price = 0xCDB;
                MENU_STATE->entries[MENU_STATE->count].classId = classId;
                MENU_STATE->entries[MENU_STATE->count].upgrade = 1;
                MENU_STATE->count++;
            }
            if (D_001A7B68[i] & 64) {
                if (MENU_ITEMS[gItemSlotToRecord[id]].ammo) {
                    int classId;
                    MENU_STATE->entries[MENU_STATE->count].id = id;
                    classId = MENU_ITEMS[gItemSlotToRecord[id]].classId;
                    MENU_STATE->entries[MENU_STATE->count].kind = 1;
                    MENU_STATE->entries[MENU_STATE->count].price = 0xCDB;
                    MENU_STATE->entries[MENU_STATE->count].marked = 0;
                    MENU_STATE->entries[MENU_STATE->count].classId = classId;
                    MENU_STATE->entries[MENU_STATE->count].upgrade = 0;
                    MENU_STATE->count++;
                }
            } else if (!hideUnowned && !gItemOwnedFlags[id]) {
                MENU_STATE->entries[MENU_STATE->count].id = id;
                MENU_STATE->entries[MENU_STATE->count].kind = 0;
                MENU_STATE->entries[MENU_STATE->count].marked = 0;
                MENU_STATE->entries[MENU_STATE->count].price = 0xCDB;
                MENU_STATE->entries[MENU_STATE->count].classId = (id == 9 || id == 73) ? 601 : MENU_ITEMS[gItemSlotToRecord[id]].classId;
                MENU_STATE->entries[MENU_STATE->count].upgrade = 0;
                MENU_STATE->count++;
            }
        }
        {
            int id;
            for (id = 0; id < 56; id++) {
                int eligible;
                if (!MENU_ITEMS[gItemSlotToRecord[id]].active || !gItemOwnedFlags[id]) continue;
                eligible = 0;
                if (menu6608TypeOk(id)) eligible = id != 16;
                if (eligible) {
                    if (!menu6608HasType(id)) {
                        if (MENU_ITEMS[gItemSlotToRecord[id]].cost <= 0 && IsFlagByteSet()) {
                            int j;
                            for (j = 0; j < MENU_STATE->count; j++)
                                if (MENU_STATE->entries[j].id == id) break;
                            if (j < MENU_STATE->count && MENU_STATE->entries[j].upgrade) continue;
                            {
                                int classId = MENU_ITEMS[gItemSlotToRecord[id]].classId;
                                MENU_STATE->entries[MENU_STATE->count].id = id;
                                MENU_STATE->entries[MENU_STATE->count].kind = 0;
                                MENU_STATE->entries[MENU_STATE->count].marked = 0;
                                MENU_STATE->entries[MENU_STATE->count].price = 0xCDB;
                                MENU_STATE->entries[MENU_STATE->count].classId = classId;
                                MENU_STATE->entries[MENU_STATE->count].upgrade = 1;
                                MENU_STATE->count++;
                            }
                        }
                    }
                }
                if (gItemOwnedFlags[id] && MENU_ITEMS[gItemSlotToRecord[id]].ammo) {
                    int j;
                    for (j = 0; j < MENU_STATE->count; j++)
                        if (MENU_STATE->entries[j].id == id) break;
                    if (j < MENU_STATE->count && !MENU_STATE->entries[j].upgrade) continue;
                    {
                        int price = D_00262E40[id][0];
                        int classId = MENU_ITEMS[gItemSlotToRecord[id]].classId;
                        MENU_STATE->entries[MENU_STATE->count].id = id;
                        MENU_STATE->entries[MENU_STATE->count].kind = 1;
                        MENU_STATE->entries[MENU_STATE->count].marked = 0;
                        MENU_STATE->entries[MENU_STATE->count].price = price;
                        MENU_STATE->entries[MENU_STATE->count].classId = classId;
                        MENU_STATE->entries[MENU_STATE->count].upgrade = 0;
                        MENU_STATE->count++;
                    }
                }
            }
        }
    } else {
        int id;
        for (id = 0; id < 56; id++) {
            if (id != 12 && id != 18 && id != 14 && id != 17 && id != 53 && id != 44) continue;
            {
                int owned = gItemOwnedFlags[id];
                int price, classId;
                if (owned && !MENU_ITEMS[gItemSlotToRecord[id]].ammo) continue;
                price = D_00262E40[id][0];
                classId = MENU_ITEMS[gItemSlotToRecord[id]].classId;
                MENU_STATE->entries[MENU_STATE->count].id = id;
                MENU_STATE->entries[MENU_STATE->count].marked = 0;
                MENU_STATE->entries[MENU_STATE->count].price = price;
                MENU_STATE->entries[MENU_STATE->count].classId = classId;
                MENU_STATE->entries[MENU_STATE->count].upgrade = 0;
                if (!owned) MENU_STATE->entries[MENU_STATE->count].kind = 0;
                else MENU_STATE->entries[MENU_STATE->count].kind = 1;
                MENU_STATE->count++;
            }
        }
        MarkBoughtSpecialItemsOwned();
    }
    {
        int i, j, k, changed;
        int id0, kind0, upgrade0;
        do {
            changed = 0;
            for (i = 0; i < MENU_STATE->count - 1; i++) {
                id0 = MENU_STATE->entries[i].id;
                kind0 = MENU_STATE->entries[i].kind;
                upgrade0 = MENU_STATE->entries[i].upgrade;
                for (j = i + 1; j < MENU_STATE->count; j++) {
                    if (MENU_STATE->entries[j].id == id0 && MENU_STATE->entries[j].kind == kind0 && MENU_STATE->entries[j].upgrade == upgrade0) {
                        changed = 1;
                        for (k = j; k < MENU_STATE->count - 1; k++) {
                            MENU_STATE->entries[k].id = MENU_STATE->entries[k + 1].id;
                            MENU_STATE->entries[k].kind = MENU_STATE->entries[k + 1].kind;
                            MENU_STATE->entries[k].marked = MENU_STATE->entries[k + 1].marked;
                            MENU_STATE->entries[k].price = MENU_STATE->entries[k + 1].price;
                            MENU_STATE->entries[k].classId = MENU_STATE->entries[k + 1].classId;
                            MENU_STATE->entries[k].upgrade = MENU_STATE->entries[k + 1].upgrade;
                        }
                    }
                    if (changed) {
                        i = MENU_STATE->count;
                        j = i;
                        MENU_STATE->count--;
                    }
                }
            }
        } while (changed);
    }
}
