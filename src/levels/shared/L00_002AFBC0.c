#include "include_asm.h"
#include "names.h"

extern void cancel_hero_item_animation(void);
extern void UpdateHeroSlotCallbacks(void);
extern void func_L00_002F6BE0(int, int, char *, char *, char *, int, int);
extern void level_release_slot_list(char *);
extern void hero_set_objects_flag_bit(void);
extern void hero_clear_tracked_slots(void);
extern void attachment_reset_all(void);
extern void hero_update_collision_capsule(void);
extern void hero_clear_queued_anim(void);
extern void func_002A677C(char *);
extern int hero_l00_set_action(int, int);
extern int level_run_slot_callback(int);
extern int g_pad_pressed_flags[];
extern char g_str_timed_state_text_a[];
extern char g_str_timed_state_text_b[];
extern char g_str_timed_state_text_c[];

extern void update_hero_item_slot_animation_blends(void);

extern void update_hero_held_items_and_orientation(void);

extern void hero_update_status_icon_overlay(void);

extern float func_00282C48_2(float d);

#ifndef RAC2_T_ROW_F3392E4BC
#define RAC2_T_ROW_F3392E4BC
typedef float Row_F3392e4bc[4];
#endif

extern char D_00189E20_12[];

extern void func_0029F338_1(void *moby);

#ifndef RAC2_T_V4_FA012328C
#define RAC2_T_V4_FA012328C
typedef int V4_Fa012328c __attribute__((mode(TI)));
#endif

extern char g_hero_vector_block[];

extern char g_hero_zero_vector[] __attribute__((sda));

extern void hero_clear_speeds(void);

extern void func_00282C88_4(void *p);

extern void pad_clear_port_state(void);

extern void func_L00_002D3CF8_1(int, int);

extern void func_L00_002D3C68_1(int, int, float);

extern void func_L00_002D3BD8_1(int, int);

extern void cam_set_view_space_height(int, int, float);

typedef unsigned char u8;

typedef int s32;

typedef float f32;

extern u8 D_00189E20_1[];

typedef struct { u8 prefix[0xc38]; f32 plane; f32 depth; } GornFloatInterval64;

#ifndef RAC2_T_V4_F6B9E759F
#define RAC2_T_V4_F6B9E759F
typedef struct {
    f32 x, y, z, w;
} V4_F6b9e759f;
#endif

#ifndef RAC2_T_M4_F6B9E759F
#define RAC2_T_M4_F6B9E759F
typedef struct {
    V4_F6b9e759f r[4];
} M4_F6b9e759f;
#endif

extern V4_F6b9e759f D_00189EA0_1[];

extern void func_00283410_5(M4_F6b9e759f *, V4_F6b9e759f *);

extern void func_00283788_3(M4_F6b9e759f *, M4_F6b9e759f *, V4_F6b9e759f *);

extern void func_002AB6D8_3(M4_F6b9e759f *, V4_F6b9e759f *);

extern void transform_vector(float *, char *, char *);

extern float func_00283248_1(float, float);

extern float math_approach_with_velocity(float *, float, char *, float, float, float, int);

extern void func_L00_002B3DC0_1(float, float, float);

extern char g_hero_steer_block[];

#ifndef RAC2_T_V4S_F31E44309
#define RAC2_T_V4S_F31E44309
typedef struct {
    f32 x, y, z, w;
} V4S_F31e44309;
#endif

extern V4S_F31e44309 D_00189E20_10[];

extern void func_00282D30_6(V4S_F31e44309 *, V4S_F31e44309 *, f32);

extern void anim_start_blended(void *, int, int, int);
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

/* One of the hero's item slots, 0x50 bytes each. */
typedef struct {
    HeroItemMoby *moby;     /* 0x00 */
    HeroItemMoby *other;    /* 0x04 */
    HeroItemMoby *extra;    /* 0x08 */
    char pad0C[4];
    int buttonMask;         /* 0x10 */
    int respawnFrame;       /* 0x14 */
    unsigned char ammoFlag; /* 0x18 */
    char pad19[0x24 - 0x19];
    int state;              /* 0x24 */
    int id;                 /* 0x28 */
    char pad2C[0x50 - 0x2C];
} HeroItemSlot;

typedef struct {
    char pad0[0x1220];
    HeroItemSlot slots[5];      /* 0x1220 */
    char pad13B0[0x2290 - 0x13B0];
    HeroItemMoby *heroMoby;     /* 0x2290 */
    char pad2294[39];
    unsigned char itemFlag;     /* 0x22BB */
    char pad22BC[12];
    int pendingItem;            /* 0x22C8 */
    char pad22CC[24];
    int selectedItem0;          /* 0x22E4 */
    char pad22E8[8];
    int selectedItem3;          /* 0x22F0 */
    char pad22F4[520];
    short packDisabled;         /* 0x24FC */
} HeroItemsCreateState;
extern HeroItemsCreateState D_00189E20_items;
extern unsigned char g_item_slot_to_record[];
extern unsigned char g_player_stats[] __attribute__((sda));
extern int g_menu_choice_table[] __attribute__((sda));
extern int g_item_ammo_counts[];
extern int g_ring_animation_counter[] __attribute__((sda)), g_frame_l00_counter[] __attribute__((sda));
typedef struct {
    char pad0[0xA0];
    short joint;
    char padA2[14];
} HeroItemEase;
extern HeroItemEase g_hero_item_ease_table[];
typedef struct {
    char pad0[0x14];
    int object;
    int other;
    unsigned char flag;
    char pad1[0x71];
    unsigned short ammo;
    char pad2[0x50];
} HeroItemDefinition;
extern HeroItemDefinition g_weapon_l00_table[];
extern void SwitchCachedDiscAsset(int);
extern HeroItemMoby *CreateMoby(int);
extern void mem_clear(void *, int, int);
extern char *tether_create_holder(int);

/* calls three measured no-argument functions in sequence */
/* Runs the three per-frame hero item updates one after another. */
void hero_update_items_frame(void) {
 update_hero_item_slot_animation_blends();
 update_hero_held_items_and_orientation();
 hero_update_status_icon_overlay();
}

#define ITEM_DEF(id) (&D_L00_00262570[D_00139568[id]])
#define HERO_ITEMS (&D_00189E20_items)

/* Spawns the mobys for the hero's equipped item slots, releasing disabled slots. */
void SpawnHeroItemMobies(void)
{
    HeroItemMoby *moby;
    int disabled;

    if (!HERO_ITEMS->slots[0].moby && g_ring_animation_counter[0] > HERO_ITEMS->slots[0].respawnFrame &&
        (!HERO_ITEMS->pendingItem || HERO_ITEMS->pendingItem == HERO_ITEMS->selectedItem0)) {
        int id = HERO_ITEMS->selectedItem0;
        int saved, i;

        if (!id) {
            if (g_player_stats[8] || (saved = g_menu_choice_table[0]) == 0)
                id = 10;
            else
                id = saved;
        }
        SwitchCachedDiscAsset(ITEM_DEF(id)->object);
        for (i = 0; i < 3; i++) {
            mem_clear(&g_hero_item_ease_table[i], 0, sizeof(HeroItemEase));
            g_hero_item_ease_table[i].joint = -1;
        }
        HERO_ITEMS->slots[0].id = id;
        moby = CreateMoby(ITEM_DEF(id)->object);
        if (moby) {
            moby->drawDistance = 32;
            moby->visible = 1;
            moby->spawnFrame = HERO_ITEMS->heroMoby->spawnFrame;
            if (moby->cls->flag)
                moby->mode = 16;
            HERO_ITEMS->slots[0].state = 2;
            HERO_ITEMS->slots[0].moby = moby;
            HERO_ITEMS->slots[0].ammoFlag = 0;
            if (ITEM_DEF(id)->ammo && !g_item_ammo_counts[id])
                HERO_ITEMS->slots[0].ammoFlag = 255;
            if (id == 10) {
                HERO_ITEMS->slots[0].buttonMask = 128;
                HERO_ITEMS->slots[0].state = 2;
                anim_start_blended(moby, 1, 0, 1);
            } else {
                HERO_ITEMS->slots[0].buttonMask = 32;
            }
            HERO_ITEMS->itemFlag = ITEM_DEF(HERO_ITEMS->slots[0].id)->flag;
        }
    }

    if (!HERO_ITEMS->slots[3].moby) {
        int id = HERO_ITEMS->selectedItem3;

        if (!id) {
            id = g_menu_choice_table[3];
            if (!id || id == 8 || id == 4) {
                id = g_player_stats[0x9] ? 3 : 2;
                if (id)
                    g_menu_choice_table[3] = id;
            }
        }
        HERO_ITEMS->slots[3].id = id;
        moby = CreateMoby(ITEM_DEF(id)->object);
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
                tether_create_holder(0);
                tether_create_holder(1);
            }
        }
    }

    if (!HERO_ITEMS->slots[3].other) {
        moby = CreateMoby(ITEM_DEF(1)->object);
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
    if (*(short *)(g_player_stats + 0x18) == 4 || g_player_stats[0x49]
        || g_player_stats[0x42] || g_player_stats[0x4B] || g_player_stats[0x4A])
        disabled = 1;
    if (HERO_ITEMS->slots[2].moby && disabled) {
        func_0029F338_1(HERO_ITEMS->slots[2].moby);
        HERO_ITEMS->slots[2].moby = 0;
    }
    if (!HERO_ITEMS->slots[2].moby && !disabled) {
        HeroItemMoby *slotMoby;
        int id = g_menu_choice_table[2];

        if (!id)
            id = 47;
        HERO_ITEMS->slots[2].id = id;
        slotMoby = CreateMoby(ITEM_DEF(id)->object);
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
    if (*(short *)(g_player_stats + 0x18) == 4 || g_player_stats[0x49]
        || g_player_stats[0x42] || g_player_stats[0x4B] || g_player_stats[0x4A])
        disabled = 1;
    if (disabled) {
        if (HERO_ITEMS->slots[1].moby) {
            func_0029F338_1(HERO_ITEMS->slots[1].moby);
            HERO_ITEMS->slots[1].moby = 0;
        }
        if (HERO_ITEMS->slots[1].other) {
            func_0029F338_1(HERO_ITEMS->slots[1].other);
            HERO_ITEMS->slots[1].other = 0;
        }
    }
    if (!HERO_ITEMS->slots[1].moby && !disabled) {
        if (g_frame_l00_counter[0] < 3)
            HERO_ITEMS->slots[1].id = g_menu_choice_table[1] = (*(short *)(g_player_stats + 0x24));
        else
            HERO_ITEMS->slots[1].id = g_menu_choice_table[1];
        if (!HERO_ITEMS->slots[1].id)
            HERO_ITEMS->slots[1].id = 52;
        moby = CreateMoby(ITEM_DEF(HERO_ITEMS->slots[1].id)->object);
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
        moby = CreateMoby(ITEM_DEF(HERO_ITEMS->slots[1].id)->other);
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

    if (!HERO_ITEMS->slots[4].moby && g_player_stats[0xFD]) {
        HeroItemMoby *slotMoby;

        slotMoby = CreateMoby(ITEM_DEF(5)->object);
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
    if (!HERO_ITEMS->slots[4].other && g_player_stats[0x12A]) {
        HeroItemMoby *slotMoby;

        slotMoby = CreateMoby(ITEM_DEF(50)->object);
        HERO_ITEMS->slots[4].id = 50;
        if (slotMoby) {
            slotMoby->drawDistance = 32;
            slotMoby->visible = 1;
            slotMoby->spawnFrame = HERO_ITEMS->heroMoby->spawnFrame;
            HERO_ITEMS->slots[4].other = slotMoby;
            HERO_ITEMS->slots[4].state = 2;
        }
    }
    if (!HERO_ITEMS->slots[4].extra && g_player_stats[0xFF]) {
        HeroItemMoby *slotMoby;

        slotMoby = CreateMoby(ITEM_DEF(7)->object);
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

#undef HERO_ITEMS
#undef ITEM_DEF


/* Nested 3x3 sweep over two rows-of-four arrays: sums the results of calling the same routine with the difference of each of the nine element pairs, returns the sum. */
/* Measures how different two sets of rotation numbers are by adding up the gaps between matching entries. */
float mat_measure_difference(Row_F3392e4bc *matrixA, Row_F3392e4bc *matrixB)
{
    float sum = 0.0f;
    int i, j;

    for (i = 0; i < 3; i++)
        for (j = 0; j < 3; j++)
            sum += func_00282C48_2(matrixA[i][j] - matrixB[i][j]);
    return sum;
}

/* func_L00_002B0528 is in L00_002B0528-g8.c. */

/* func_L00_002B0968 is in L00_002AFBC0-attach-g8.c. */

/* for one fixed 80-byte slot: stores a value, rewrites a state word, dispatches through a function pointer at entry+100 unless the entry is null or carries a 253/254 sentinel, then releases two stored entry pointers, skipping the second when the slot index is 3 */
/* Frees one hero item slot: lets the item run its last callback, then removes its game objects. */
void hero_release_item_slot(int slot, int value)
{
    char *entry;
    void (*callback)(char *);

    {
        char *slotBase = D_00189E20_12 + slot * 80;

        *(int *)(slotBase + 4660) = value;
        if (*(int *)(slotBase + 4676) != 3) {
            *(int *)(slotBase + 4676) = 3;
            entry = *(char **)(slotBase + 4640);
            if (entry != 0) {
                if (*(unsigned char *)(entry + 32) != 254) {
                    if (*(unsigned char *)(entry + 32) != 253) {
                        callback = *(void (**)(char *))(entry + 100);
                        if (callback != 0)
                            callback(entry);
                    }
                }
            }
        }
    }
    {
        char *slotBase = D_00189E20_12 + slot * 80;

        entry = *(char **)(slotBase + 4640);
        *(int *)(slotBase + 4676) = 0;
        *(int *)(slotBase + 4680) = 0;
        if (entry != 0) {
            func_0029F338_1(entry);
            *(char **)(slotBase + 4640) = 0;
        }
        entry = *(char **)(slotBase + 4644);
        if (entry != 0 && slot != 3) {
            func_0029F338_1(entry);
            *(char **)(slotBase + 4644) = 0;
        }
    }
}

typedef struct {
    u8 pad0[0x98];
    f32 f98;
    u8 pad1[0x1A0 - 0x9C];
    f32 f1A0;
    f32 f1A4;
    f32 f1A8;
    u8 pad2[0x1B0 - 0x1AC];
    f32 f1B0;
    f32 f1B4;
    u8 pad3[0x1FC - 0x1B8];
    short a;
    u8 pad4[0xA70 - 0x1FE];
    f32 fA70;
    f32 fA74;
    f32 fA78;
    u8 pad4b[0x1FB0 - 0xA7C];
    f32 f1FB0;
    f32 f1FB4;
    u8 pad5[0x22C3 - 0x1FB8];
    u8 flag;
    u8 pad6[0x24F4 - 0x22C4];
    short b;
} D00189E20_Overlay;

extern D00189E20_Overlay g_hero_state;

extern f32 ApproachValue(float *, float, float);

/* The level's own dispatch table: 31 absolute code addresses, five of them (the cases
 * 14, 26, 27, 43 and 44) pointing at the arm that writes the two shorts and the rest at
 * the return.  It lives in the level's data, so it is named by its address. */
extern void *D_L00_002A00A0[31];

/* Dispatches on the argument through the level's table: the five listed cases write
 * 0x46 at +0x1FC and 3 at +0x24F4 of the resident block, the other twenty-six and every
 * argument out of the range only return. */
/* For a few special hero modes, sets a short timer and a state value. Other modes do nothing. */
void hero_start_timed_state_for_mode(int mode)
{
    /* Keeps the two arms alive: the addresses land in the discarded .data. */
    static void *cases[31] = {
        &&arm, &&ret, &&ret, &&ret, &&ret, &&ret, &&ret, &&ret,
        &&ret, &&ret, &&ret, &&ret, &&arm, &&arm, &&ret, &&ret,
        &&ret, &&ret, &&ret, &&ret, &&ret, &&ret, &&ret, &&ret,
        &&ret, &&ret, &&ret, &&ret, &&ret, &&arm, &&arm
    };

    if ((unsigned int)(mode - 14) < 31) {
        goto *D_L00_002A00A0[mode - 14];
    } else {
        goto ret;
    }
arm:
    g_hero_state.b = 3;
    g_hero_state.a = 0x46;
ret:
    return;
}

extern void ApplyHeroEquipmentRequest(int);
/* Read through its macro symbol: the copy reorg puts in a branch delay slot assembles
 * $gp-relative, the one in ordinary flow as lui/lw. */
extern int g_ring_animation_counter[] __attribute__((sda));

/* Per-frame pass over the seven 80-byte slots at +0x1220: an empty slot is released; in
 * state 2 a slot counts a tick, is released and, for a flagged entry whose animation set
 * allows it, starts animation 1; in state 3 it counts a byte tick and slots 0 and 1 (or a
 * flagged entry) are reinstalled with the shared value plus 2.  The entry's update
 * callback then runs, except for slot 6, a 253/254 sentinel entry, or slot 0 while the
 * block's word at +0x1500 is set and its mode at +0x1248 is not 10. */
void UpdateHeroSlotCallbacks(void)
{
    int i;

    for (i = 0; i < 7; i++) {
        u8 *base = D_00189E20_1;
        u8 *slot = base + i * 80;
        u8 *entry = *(u8 **)(slot + 0x1220);
        void (*callback)(char *);

        if (entry != 0) {
            switch (*(int *)(slot + 0x1244)) {
            case 2:
                ++*(int *)(slot + 0x1240);
                ApplyHeroEquipmentRequest(i);
                if ((entry[0x60] & 2) && entry[0x43] == 0
                    && (*(u8 **)(entry + 0x24))[0xC] >= 2)
                    anim_start_blended(entry, 1, 0, 2);
                break;
            case 3:
                ++slot[0x123B];
                if ((entry[0x60] & 2) || i == 1 || i == 0)
                    hero_release_item_slot(i, g_ring_animation_counter[0] + 2);
                break;
            }
            {
                u8 *block = D_00189E20_1;

                if (*(int *)(block + 0x1500) != 0 && i == 0
                    && *(int *)(block + 0x1248) != 10)
                    continue;
            }
            if (entry != 0 && entry[0x20] != 254 && entry[0x20] != 253 && i != 6) {
                callback = *(void (**)(char *))(entry + 0x64);
                if (callback != 0)
                    callback((char *)entry);
            }
        } else {
            ApplyHeroEquipmentRequest(i);
        }
    }
}


/* func_L00_002B2200 is in L00_002B2200-g8.c. */


/* Reset the hero update state, install the requested mode and object, and update the mode-one counters. */
void SetHeroMode(int mode, int value, char *object)
{
    char *hero;
    char *currentMoby;
    int newHealth;

    cancel_hero_item_animation();
    hero = (char *)D_00189E20_1;
    hero[0x22B6] = 1;
    UpdateHeroSlotCallbacks();
    *(int *)(hero + 0x2290) = *(int *)(hero + 0xC18);
    level_release_slot_list(hero + 0x18E0);
    level_release_slot_list(hero + 0x1A30);
    currentMoby = *(char **)(hero + 0x2290);
    *(int *)(currentMoby + 0x9C) = -1;
    if (mode != 4 || (unsigned char)hero[0x22B4] != mode)
        hero_set_objects_flag_bit();
    hero_clear_tracked_slots();
    attachment_reset_all();
    {
        char *heroAlias = (char *)D_00189E20_1;

        heroAlias[0x22B4] = (char)mode;
        *(int *)(heroAlias + 0xC14) = (int)object;
        *(int *)(heroAlias + 0x2290) = (int)object;
        if ((unsigned char)mode == 1 && (g_pad_pressed_flags[0] & 0x10) != 0) {
            func_L00_002F6BE0(0x23, 0, g_str_timed_state_text_a,
                             g_str_timed_state_text_b, g_str_timed_state_text_c, 0, 0);
            level_run_slot_callback(3);
        }
        {
            char *heroBlock = (char *)D_00189E20_1;

            hero_update_collision_capsule();
            *(float *)(heroBlock + 0x250) = *(float *)(heroBlock + 0x258);
            *(float *)(heroBlock + 0x254) = *(float *)(heroBlock + 0x25C);
            *(unsigned short *)(*(char **)(heroBlock + 0x2290) + 0x34) |= 6;
            *(float *)(heroBlock + 0xC24) = *(float *)(heroBlock + 0xC20) = 1.0f;
            hero_clear_queued_anim();
            func_002A677C(*(char **)(heroBlock + 0x2290));
            *(short *)(heroBlock + 0x24F2) = (short)value;
            if (mode == 1) {
                *(short *)(heroBlock + 0x24D4) = *(short *)(heroBlock + 0x24CC);
                newHealth = *(int *)(heroBlock + 0x24D0);
                *(int *)(heroBlock + 0x24CC) = newHealth;
                if (newHealth >= 5)
                    *(int *)(heroBlock + 0x24CC) = 4;
            }
            hero_l00_set_action(value, 2);
        }
    }
}

/* Zeroes a 16-byte global block, calls a setup helper, runs a per-slot reset helper over seven 16-byte units of a global table, then clears three word fields of a block 256 bytes below the table base. */
/* Clears the hero speed values and a group of saved vectors. */
void hero_reset_speeds_and_vectors(void)
{
    char *block;

    *(volatile V4_Fa012328c *)g_hero_zero_vector = 0;
    hero_clear_speeds();
    block = g_hero_vector_block;
    func_00282C88_4(block);
    func_00282C88_4(block - 16);
    func_00282C88_4(block + 16);
    func_00282C88_4(block + 32);
    func_00282C88_4(block + 48);
    func_00282C88_4(block + 96);
    func_00282C88_4(block - 96);
    block = block - 256;
    *(int *)(block + 420) = 0;
    *(int *)(block + 376) = 0;
    *(int *)(block + 368) = 0;
    pad_clear_port_state();
}


/* dispatch on the second integer argument: each arm runs a pair of sub-calls passing the first argument twice, the second call also forwarding the float argument */
/* Flattens a push vector in one of two ways and then sets its strength. */
void hero_flatten_push_vector(int vec, int useAlternate, float unusedScale, float scale)
{
    if (useAlternate != 0) {
        func_L00_002D3CF8_1(vec, vec);
        func_L00_002D3C68_1(vec, vec, scale);
    } else {
        func_L00_002D3BD8_1(vec, vec);
        cam_set_view_space_height(vec, vec, scale);
    }
}

/* func_L00_002B2CC8 is in L00_002B2CC8-interact.c. */

typedef struct {
    u8 pad0[0x2294];
    int mode;
    u8 pad2298[0x22C1 - 0x2298];
    u8 visited;
    u8 pad22C2[0x22C6 - 0x22C2];
    u8 slot;
} HeroSlotState;

extern int g_current_map_index[] __attribute__((sda));
extern int g_play_counter_total[] __attribute__((sda));
extern int g_slot_play_counters[] __attribute__((sda));
extern int g_map_play_counts[];
extern unsigned char g_moby_group_flags[][16];
extern int g_play_counters[][16];
extern void level_clear_entry_top_bits(void);
extern void FadeToBlack(int);

/* Bumps the current level's counter and a global total, runs a helper, then for a valid slot at 0x22C6 bumps a
 * per-level per-slot counter (only once the counter at D_L00_001B19C8 reaches 900, or 1800 in modes 0x74 and 0x79,
 * and while the slot's 0x80 flag is clear) and a 16-entry counter; always bumps the per-slot counter, calls
 * func_0027D330(0x10) and sets the byte at 0x22C1. */
/* Adds one to the play counters for the current level and slot, and marks the hero as having visited. */
void hero_record_play_counters(void)
{
    int threshold;
    int mode;

    g_map_play_counts[g_current_map_index[0]]++;
    g_play_counter_total[0]++;
    level_clear_entry_top_bits();
    if (((HeroSlotState *)D_00189E20_1)->slot != 0xFF) {
        mode = ((HeroSlotState *)D_00189E20_1)->mode;
        if (mode == 0x74 || mode == 0x79)
            threshold = 0x708;
        else
            threshold = 0x384;
        if (g_frame_l00_counter[0] >= threshold) {
            int level = g_current_map_index[0];
            int slot = ((HeroSlotState *)D_00189E20_1)->slot;
            if ((g_moby_group_flags[level][slot] & 0x80) == 0)
                g_play_counters[level][slot & 0xF]++;
        }
        g_slot_play_counters[((HeroSlotState *)D_00189E20_1)->slot & 0xF]++;
    }
    g_slot_play_counters[((HeroSlotState *)D_00189E20_1)->slot]++;
    FadeToBlack(0x10);
    ((HeroSlotState *)D_00189E20_1)->visited = 1;
}

/* tests the signed short identifier at offset 0xaa of a nonnull object against 71 */
/* Tells whether a game object exists and is of class 71. */
s32 moby_is_class_71(u8 *object) {
 if(object==0) return 0;
 return *(short *)(object+0xaa)==71 /* moby class 71 */;
}

extern int g_pad_pressed_flags[];

extern char g_cam_follow_matrix[];

extern float g_camera_target_rotation;

extern float hero_get_direction_angle_delta(char *, int);

extern float math_fabs(float);

extern float FastDiffRots(float, float);

/* Checks whether the hero is turned far enough away (at least the given angle) while a button is held. */
int hero_is_turned_past_angle(float minAngle) {
    float angle;

    if ((g_pad_pressed_flags[0] & 3) != 0) {
        if (g_hero_state.flag != 0)
            angle = math_fabs(hero_get_direction_angle_delta(g_cam_follow_matrix, 0));
        else
            angle = FastDiffRots(g_hero_state.f98, g_camera_target_rotation);
        if (angle < minAngle)
            return 0;
        return 1;
    }
    return 0;
}

/* func_L00_002B32F8 is in L00_002B32F8-hero.c. */

/* func_L00_002B35A0 is in L00_002B35A0.c. */

/* func_L00_002B36E0 is in L00_002B36E0-hero.c. */

extern char g_player_state[];

extern float FastVecLength(char *);

/* Works out how hard the player is pushing the stick, from 0 to 1. */
float hero_get_stick_magnitude(void) {
    float absX = math_fabs(g_hero_state.f1FB0);
    float absY = math_fabs(g_hero_state.f1FB4);
    float largest;
    float magnitude;

    if (absY < absX)
        largest = math_fabs(g_hero_state.f1FB0);
    else
        largest = math_fabs(g_hero_state.f1FB4);
    magnitude = (largest + FastVecLength(g_player_state)) * 0.5f;
    if (1.0f < magnitude)
        magnitude = 1.0f;
    return magnitude;
}

/* Test whether a scalar lies below a plane within its configured depth, rejecting unordered values */
/* Tells whether a value is just below a flat limit, no further than the allowed depth. */
int math_is_below_plane_within_depth(f32 value)
{
    GornFloatInterval64 *root = (GornFloatInterval64 *)D_00189E20_1;
    if (value < root->plane) {
        if (root->plane - value <= root->depth)
            return 1;
    }
    return 0;
}

/* clears the two floats at the head of the window block; the second store is the one the
   scheduler parks in the jr delay slot, so it is written second */
/* Sets the hero target speed and current speed to zero. */
void hero_clear_speeds(void)
{
    g_hero_state.f1B0 = 0.0f;
    g_hero_state.f1B4 = 0.0f;
}

/* builds one 64-byte block from a 3-float vector of the incoming scalars and another from a static table record one element in, combines them, then scales the result again from that record */
/* Turns the hero matrix by a rotation given as three numbers. */
void hero_rotate_matrix(f32 x, f32 y, f32 z) {
    V4_F6b9e759f rotation;
    M4_F6b9e759f rotationMatrix;
    M4_F6b9e759f heroMatrix;
    rotation.x = x;
    rotation.y = y;
    rotation.z = z;
    func_00283410_5(&rotationMatrix, &rotation);
    func_00283410_5(&heroMatrix, &D_00189EA0_1[1]);
    func_00283788_3(&heroMatrix, &heroMatrix, &rotationMatrix);
    func_002AB6D8_3(&heroMatrix, &D_00189EA0_1[1]);
}

/* Fills a two-float scratch buffer from one region of a fixed global, passes it with three forwarded floats and an out-parameter to another callee, stores the returned float back into the global, then feeds that out value to a final callee. */
/* Smoothly turns the hero toward a direction in the special movement mode. */
void hero_steer_heading_special(int index, float first, float second, float third)
{
    float offsetXY[2];
    char *block = g_hero_steer_block;
    float turnOut;
    float angleToTarget;

    transform_vector(offsetXY, block, block - 336);
    angleToTarget = func_00283248_1(offsetXY[0], offsetXY[1]);
    turnOut = 0.0f;
    *(float *)(block + 24) = math_approach_with_velocity(&turnOut, angleToTarget, block + 20, first, second, third, index);
    func_L00_002B3DC0_1(0.0f, 0.0f, turnOut);
}

/* Smoothly turns the hero toward the wanted direction, using the normal or the special method. */
void hero_steer_heading(int index, float first, float second, float third) {
    if (g_hero_state.flag != 0)
        hero_steer_heading_special(index, first, second, third);
    else
        g_hero_state.f1A8 = math_approach_with_velocity(&g_hero_state.f98, g_hero_state.f1A0, (char *)&g_hero_state.f1A4, first, second, third, index);
}


/* func_L00_002B3F68 is in L00_002B3F68.c. */

/* Moves the hero current speed toward the wanted speed, faster when speeding up than when slowing down. */
void hero_approach_speed(float riseRate, float fallRate) {
    if (g_hero_state.f1B4 < g_hero_state.f1B0)
        ApproachValue(&g_hero_state.f1B4, g_hero_state.f1B0, riseRate);
    else
        ApproachValue(&g_hero_state.f1B4, g_hero_state.f1B0, fallRate);
}


extern char g_drive_velocity_view[];

extern void vec_scale_to_length(char *, void *, float);

/* Copies a direction into the hero push vector and gives it the stored push length. */
void hero_set_push_direction(void *direction) {
    vec_scale_to_length(g_drive_velocity_view, direction, *(float *)(g_drive_velocity_view + 0xC4));
}

/* func_L00_002B4308 is in L00_002B4308.c. */

/* func_L00_002B4458 is in L00_002AFBC0-surface.c. */

/* func_L00_002B47A8 is in L00_002AFBC0-vectors.c. */

/* func_L00_002B5250 is in L00_002AFBC0-snap.c. */

extern void vec_build_spherical_offset(char *, float, float, float);

extern void FastVecScale(char *, char *, float);

extern void vec_clear_128(char *);

/* Builds the hero movement push from the stick values and shrinks it, or clears it when it is very small. */
void hero_build_move_impulse(float scale, float deadZone) {
    char *impulse = (char *)&g_hero_state + 0xA60;
    float length;

    vec_build_spherical_offset(impulse, g_hero_state.fA70, g_hero_state.fA78, g_hero_state.fA74);
    FastVecScale(impulse, impulse, scale);
    length = FastVecLength(impulse);
    if (length <= deadZone)
        vec_clear_128(impulse);
    else
        vec_scale_to_length(impulse, impulse, length - deadZone);
}




/* func_L00_002B5B60 is in L00_002B5B60-motion.c. */

/* scales four 16-byte records of a static table in place by a scalar, then multiplies one float field of a later record by the same scalar */
/* Scales a few saved hero vectors by the same amount. */
void hero_scale_saved_vectors(f32 scale) {
    V4S_F31e44309 *vectors = &D_00189E20_10[17];
    func_00282D30_6(vectors, vectors, scale);
    func_00282D30_6(vectors + 1, vectors + 1, scale);
    func_00282D30_6(vectors - 2, vectors - 2, scale);
    func_00282D30_6(vectors + 5, vectors + 5, scale);
    D_00189E20_10[27].y = D_00189E20_10[27].y * scale;
}

/* func_L00_002B6198 is in L00_002AFBC0-velocity.c. */

/* func_L00_002B6560 is in L00_002B6560.c. */


/* func_L00_002B75A0 is in L00_002AFBC0-target.c. */

/* func_L00_002B7718 is in L00_002B7718-g8.c. */
