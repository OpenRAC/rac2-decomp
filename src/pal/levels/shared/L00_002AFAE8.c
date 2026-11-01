#include "include_asm.h"

extern void func_0029F338(void *moby);
extern void func_PAL_002A7E68(void *, int, int, int);
typedef struct {
    char pad0[6];
    unsigned char flag;
} HeroItemMobyClass;
typedef struct {
    char pad0[0x24];
    HeroItemMobyClass *cls;
    char pad28[9];
    unsigned char visible;
    short drawDistance;
    unsigned short flags;
    char pad36[2];
    long long spawnFrame;
    char pad40[0x23];
    unsigned char mode;
    void (*update)(char *);
} HeroItemMoby;
typedef struct {
    HeroItemMoby *moby;      
    HeroItemMoby *other;     
    HeroItemMoby *extra;     
    char pad0C[4];
    int buttonMask;          
    int respawnFrame;        
    unsigned char ammoFlag;  
    char pad19[0x24 - 0x19];
    int state;               
    int id;                  
    char pad2C[0x50 - 0x2C];
} HeroItemSlot;
typedef struct {
    char pad0[0x1220];
    HeroItemSlot slots[5];       
    char pad13B0[0x2290 - 0x13B0];
    HeroItemMoby *heroMoby;      
    char pad2294[39];
    unsigned char itemFlag;      
    char pad22BC[12];
    int pendingItem;             
    char pad22CC[24];
    int selectedItem0;           
    char pad22E8[8];
    int selectedItem3;           
    char pad22F4[520];
    short packDisabled;          
} HeroItemsCreateState;
extern HeroItemsCreateState D_00189E20_items;
extern unsigned char D_00139568[];
extern unsigned char D_001A7A00[] __attribute__((sda));
extern int D_001A7398[] __attribute__((sda));
extern int D_00139688[];
extern int D_L00_001B18D8[] __attribute__((sda)), D_L00_001B19C8[] __attribute__((sda));
typedef struct {
    char pad0[0xA0];
    short joint;
    char padA2[14];
} HeroItemEase;
extern HeroItemEase D_0018B9A0[];
typedef struct {
    char pad0[0x14];
    int object;
    int other;
    unsigned char flag;
    char pad1[0x71];
    unsigned short ammo;
    char pad2[0x50];
} HeroItemDefinition;
extern HeroItemDefinition D_L00_00262570[];
extern void func_PAL_00295298(int);
extern HeroItemMoby *func_0029EFD0(int);
extern void func_00282A60(void *, int, int);
extern void func_L00_00390938(int);
#define ITEM_DEF(id) (&D_L00_00262570[D_00139568[id]])
#define HERO_ITEMS (&D_00189E20_items)
extern int D_L00_001B18D8[] __attribute__((sda));

/* Spawns the mobys for the hero's equipped item slots, releasing disabled slots. */
void func_PAL_L00_002AFAE8(void)
{
    HeroItemMoby *moby;
    int disabled;

    if (!HERO_ITEMS->slots[0].moby && D_L00_001B18D8[0] > HERO_ITEMS->slots[0].respawnFrame &&
        (!HERO_ITEMS->pendingItem || HERO_ITEMS->pendingItem == HERO_ITEMS->selectedItem0)) {
        int id = HERO_ITEMS->selectedItem0;
        int saved, i;

        if (!id) {
            if (D_001A7A00[8] || (saved = D_001A7398[0]) == 0)
                id = 10;
            else
                id = saved;
        }
        func_PAL_00295298(ITEM_DEF(id)->object);
        for (i = 0; i < 3; i++) {
            func_00282A60(&D_0018B9A0[i], 0, sizeof(HeroItemEase));
            D_0018B9A0[i].joint = -1;
        }
        HERO_ITEMS->slots[0].id = id;
        moby = func_0029EFD0(ITEM_DEF(id)->object);
        if (moby) {
            moby->drawDistance = 32;
            moby->visible = 1;
            moby->spawnFrame = HERO_ITEMS->heroMoby->spawnFrame;
            if (moby->cls->flag)
                moby->mode = 16;
            HERO_ITEMS->slots[0].state = 2;
            HERO_ITEMS->slots[0].moby = moby;
            HERO_ITEMS->slots[0].ammoFlag = 0;
            if (ITEM_DEF(id)->ammo && !D_00139688[id])
                HERO_ITEMS->slots[0].ammoFlag = 255;
            if (id == 10) {
                HERO_ITEMS->slots[0].buttonMask = 128;
                HERO_ITEMS->slots[0].state = 2;
                func_PAL_002A7E68(moby, 1, 0, 1);
            } else {
                HERO_ITEMS->slots[0].buttonMask = 32;
            }
            HERO_ITEMS->itemFlag = ITEM_DEF(HERO_ITEMS->slots[0].id)->flag;
        }
    }

    if (!HERO_ITEMS->slots[3].moby) {
        int id = HERO_ITEMS->selectedItem3;

        if (!id) {
            id = D_001A7398[3];
            if (!id || id == 8 || id == 4) {
                id = D_001A7A00[0x9] ? 3 : 2;
                if (id)
                    D_001A7398[3] = id;
            }
        }
        HERO_ITEMS->slots[3].id = id;
        moby = func_0029EFD0(ITEM_DEF(id)->object);
        if (moby) {
            moby->drawDistance = 32;
            moby->visible = 1;
            moby->spawnFrame = HERO_ITEMS->heroMoby->spawnFrame;
            if (moby->cls->flag)
                moby->mode = 16;
            HERO_ITEMS->slots[3].state = 2;
            HERO_ITEMS->slots[3].moby = moby;
            if (HERO_ITEMS->packDisabled)
                moby->flags |= 0x41;
            if (!HERO_ITEMS->packDisabled && (HERO_ITEMS->slots[3].id == 3 || HERO_ITEMS->slots[3].id == 8)) {
                func_L00_00390938(0);
                func_L00_00390938(1);
            }
        }
    }

    if (!HERO_ITEMS->slots[3].other) {
        moby = func_0029EFD0(ITEM_DEF(1)->object);
        if (moby) {
            moby->drawDistance = 32;
            moby->visible = 1;
            moby->spawnFrame = HERO_ITEMS->heroMoby->spawnFrame;
            if (moby->cls->flag)
                moby->mode = 16;
            HERO_ITEMS->slots[3].state = 2;
            HERO_ITEMS->slots[3].other = moby;
            if (HERO_ITEMS->packDisabled)
                moby->flags |= 0x41;
        }
    }

    disabled = 0;
    if (*(short *)(D_001A7A00 + 0x18) == 4 || D_001A7A00[0x49]
        || D_001A7A00[0x42] || D_001A7A00[0x4B] || D_001A7A00[0x4A])
        disabled = 1;
    if (HERO_ITEMS->slots[2].moby && disabled) {
        func_0029F338(HERO_ITEMS->slots[2].moby);
        HERO_ITEMS->slots[2].moby = 0;
    }
    if (!HERO_ITEMS->slots[2].moby && !disabled) {
        HeroItemMoby *slotMoby;
        int id = D_001A7398[2];

        if (!id)
            id = 47;
        HERO_ITEMS->slots[2].id = id;
        slotMoby = func_0029EFD0(ITEM_DEF(id)->object);
        if (slotMoby) {
            slotMoby->drawDistance = 32;
            slotMoby->visible = 1;
            slotMoby->spawnFrame = HERO_ITEMS->heroMoby->spawnFrame;
            slotMoby->flags |= 2;
            slotMoby->update = 0;
            if (slotMoby->cls->flag)
                slotMoby->mode = 16;
            slotMoby->flags |= 0x800;
            HERO_ITEMS->slots[2].moby = slotMoby;
            HERO_ITEMS->slots[2].state = 2;
        }
    }

    disabled = 0;
    if (*(short *)(D_001A7A00 + 0x18) == 4 || D_001A7A00[0x49]
        || D_001A7A00[0x42] || D_001A7A00[0x4B] || D_001A7A00[0x4A])
        disabled = 1;
    if (disabled) {
        if (HERO_ITEMS->slots[1].moby) {
            func_0029F338(HERO_ITEMS->slots[1].moby);
            HERO_ITEMS->slots[1].moby = 0;
        }
        if (HERO_ITEMS->slots[1].other) {
            func_0029F338(HERO_ITEMS->slots[1].other);
            HERO_ITEMS->slots[1].other = 0;
        }
    }
    if (!HERO_ITEMS->slots[1].moby && !disabled) {
        if (D_L00_001B19C8[0] < 3)
            HERO_ITEMS->slots[1].id = D_001A7398[1] = (*(short *)(D_001A7A00 + 0x24));
        else
            HERO_ITEMS->slots[1].id = D_001A7398[1];
        if (!HERO_ITEMS->slots[1].id)
            HERO_ITEMS->slots[1].id = 52;
        moby = func_0029EFD0(ITEM_DEF(HERO_ITEMS->slots[1].id)->object);
        if (moby) {
            moby->drawDistance = 32;
            moby->visible = 1;
            moby->spawnFrame = HERO_ITEMS->heroMoby->spawnFrame;
            moby->update = 0;
            if (moby->cls->flag)
                moby->mode = 16;
            HERO_ITEMS->slots[1].moby = moby;
            HERO_ITEMS->slots[1].state = 2;
        }
        moby = func_0029EFD0(ITEM_DEF(HERO_ITEMS->slots[1].id)->other);
        if (moby) {
            moby->drawDistance = 32;
            moby->visible = 1;
            moby->spawnFrame = HERO_ITEMS->heroMoby->spawnFrame;
            moby->update = 0;
            if (moby->cls->flag)
                moby->mode = 16;
            HERO_ITEMS->slots[1].other = moby;
            HERO_ITEMS->slots[1].state = 2;
        }
    }

    if (!HERO_ITEMS->slots[4].moby && D_001A7A00[0xFD]) {
        HeroItemMoby *slotMoby;

        slotMoby = func_0029EFD0(ITEM_DEF(5)->object);
        HERO_ITEMS->slots[4].id = 5;
        if (slotMoby) {
            slotMoby->drawDistance = 32;
            slotMoby->visible = 1;
            slotMoby->spawnFrame = HERO_ITEMS->heroMoby->spawnFrame;
            if (slotMoby->cls->flag)
                slotMoby->mode = 16;
            HERO_ITEMS->slots[4].moby = slotMoby;
            HERO_ITEMS->slots[4].state = 2;
        }
    }
    if (!HERO_ITEMS->slots[4].other && D_001A7A00[0x12A]) {
        HeroItemMoby *slotMoby;

        slotMoby = func_0029EFD0(ITEM_DEF(50)->object);
        HERO_ITEMS->slots[4].id = 50;
        if (slotMoby) {
            slotMoby->drawDistance = 32;
            slotMoby->visible = 1;
            slotMoby->spawnFrame = HERO_ITEMS->heroMoby->spawnFrame;
            HERO_ITEMS->slots[4].other = slotMoby;
            HERO_ITEMS->slots[4].state = 2;
        }
    }
    if (!HERO_ITEMS->slots[4].extra && D_001A7A00[0xFF]) {
        HeroItemMoby *slotMoby;

        slotMoby = func_0029EFD0(ITEM_DEF(7)->object);
        HERO_ITEMS->slots[4].id = 7;
        if (slotMoby) {
            slotMoby->drawDistance = 32;
            slotMoby->visible = 1;
            slotMoby->spawnFrame = HERO_ITEMS->heroMoby->spawnFrame;
            HERO_ITEMS->slots[4].extra = slotMoby;
            HERO_ITEMS->slots[4].state = 2;
        }
    }
}

