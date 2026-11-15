#include "include_asm.h"
#include "common.h"

/* Measured purchase-panel layout and pricing records. */
typedef struct { short field[12]; } TextLayout;
typedef struct { int id; int kind; int rest[4]; } ShopEntry;
typedef struct {
    char prefix[0x80];
    int index;
    int active;
    char padding[0xB8];
    ShopEntry entries[0];
} PurchaseModel;
typedef struct { char prefix[0x88]; unsigned short price; char rest[0x56]; } ShopClass;
extern unsigned char g_item_slot_to_record[];
extern char g_weapon_l00_table[];
extern int D_L00_001B25A8 __attribute__((sda));
extern int g_player_bolts __attribute__((sda));
extern char D_L00_001AD798[7];
extern char D_L00_001AD6C8[3];
extern void *memset(void *, int, unsigned int);
extern void text_draw_window_medium(TextLayout *, unsigned long long, unsigned char *, int);
extern int sprintf(char *, char *, ...);
extern int GetSelectedShopItemPrice(void);

/* Layouts measured from the selected-item panel. */
typedef struct { unsigned int word[4]; } PanelColors;
typedef struct { int price; int pad[3]; unsigned char *name; int pad2[2]; } ShopItem;
extern PanelColors D_L00_001AD768;
typedef struct { char prefix[0x144]; ShopItem items[0]; } ShopModel;
extern ShopModel g_purchase_menu_model;
extern float D_L00_001B25E0 __attribute__((sda));
extern int D_L00_001B1BB8[] __attribute__((sda));
extern int g_screen_width __attribute__((sda));
extern int D_001A79FC __attribute__((sda));
extern int GetIconFrame(int, int);
extern int hud_draw_sprite_gradient(int, int, int, int, int, unsigned int *);
extern int GetLocalizedString(int);
extern void text_draw_right_aligned_medium(int, int, unsigned long long, unsigned char *, int);
extern void text_format_number_with_separators(char *, int);
extern void text_draw_medium(int, int, unsigned long long, unsigned char *, int);
extern int text_draw_centered_medium(int, int, unsigned long long, unsigned char *, int);
extern void text_draw_right_aligned_small(int, int, unsigned long long, unsigned char *, int);


extern char *record_find_by_id(int a0, int a1);

extern void func_00282AB0_1(char *target, char *base, int len);

typedef struct {
    short key;
    short index;
    int value;
} Query;

typedef struct {
    int key;
    int value;
} Entry32fd6f60;

extern Entry32fd6f60 D_L07_002A4100[];

/* Measured partial layouts; original type and game roles are unknown. */
typedef struct Rac2Native_acdcf1600d770d3b_ScalarConfigure116State {
    unsigned char prefix_00[0x60];
    unsigned int value_60;
    int value_64;
    unsigned char selector_68;
    unsigned char axis_69;
    unsigned char mode_6a;
    unsigned char dirty_6b;
} Rac2Native_acdcf1600d770d3b_ScalarConfigure116State;

extern Rac2Native_acdcf1600d770d3b_ScalarConfigure116State D_00188660_2[];

/* Walks up to 25 records of 10 bytes; for each record whose 16-bit key is non-negative and whose table byte is set, resolves an object through a helper and copies/relocates it with the record's 16-bit length, capping the destination table at 25 entries. */
/* Copies each listed block of data into the object it belongs to when the level is set up. */
void level_copy_data_blocks_to_objects(char *table)
{
    int i = 0;

    if (i < *(int *)table) {
        int absolute_flag = 1;
        char *data_cursor = table + 8;
        char *record_cursor = table + 4;

        do {
            char *owner = record_find_by_id(*(short *)(record_cursor + 14), *(short *)(record_cursor + 12));
            if (owner != 0) {
                char *dest;
                if (*(short *)(record_cursor + 10) == absolute_flag)
                    dest = (char *)(*(int *)record_cursor + (int)owner);
                else
                    dest = (char *)(*(int *)record_cursor + *(int *)(owner + 104));
                func_00282AB0_1(dest, data_cursor, *(unsigned short *)(record_cursor + 8));
            }
            i++;
            data_cursor += 16;
            record_cursor += 16;
        } while (i < *(int *)table);
    }
}

extern char D_L00_0021DE10[];

/* Applies the level data blocks from the standard table. */
void level_apply_data_blocks(void)
{
    level_copy_data_blocks_to_objects(D_L00_0021DE10);
}



extern int D_001B19E8 __attribute__((sda));

extern int D_001B19EC __attribute__((sda));

extern int D_001B8F0C __attribute__((sda));

extern char D_00188660_3[];

extern int AllocateSoundVoice(char *a0, int a1, int a2, int a3, int a4);

/* Shared slot table: the first free record of a 112-byte table is filled with the index and the
 * caller's value; returns the record number, or -1 when the index is out of range. */
/* Starts a sound or effect in a free slot and remembers its index, returning the slot or -1. */
int snd_start_in_slot(int index, int a1, int a2)
{
    int slot;
    char *record;

    if (D_001B19EC == 0)
        return -1;
    index = index + D_001B8F0C;
    if (index >= D_001B19E8)
        return -1;
    slot = AllocateSoundVoice((char *)(D_001B19EC + index * 32), a1, a2, 0, 1024);
    if (slot >= 0) {
        record = D_00188660_3 + slot * 112;
        *(int *)(record + 136) = a2;
        *(short *)(record + 126) = index;
    }
    return slot;
}

/* Same slot table as func_L00_0035F5A0, but with the caller's own record: the helper gets the
 * slot's record, the value goes in at 0x40 and the helper's second value becomes the fifth
 * argument; the record's index word is written at 126 and the value word at 140. */
/* Starts a sound or effect from a given table entry, filling a free slot and returning it or -1. */
int snd_start_from_table_entry(int index, int a1, int a2, int a3)
{
    int slot;
    char *record;

    if (index >= D_001B19E8)
        return -1;
    if (index == 0xFFFFFFFFU) {
        return -1;
    } else {
        slot = AllocateSoundVoice((char *)(D_001B19EC + index * 32), a1, 0, a2 + 0x40, a3);
        if (slot >= 0) {
            record = D_00188660_3 + slot * 112;
            *(int *)(record + 140) = a2;
            *(short *)(record + 126) = index;
        }
        return slot;
    }
}

/* Builds a slot index out of three weight/kind arguments and fills the same 112-byte record as
 * above; the record's value word comes from the fifth argument, the helper's from the sixth. */
/* Works out a table entry from three small values, then starts it in a free slot, returning the slot or -1. */
int snd_start_from_weights(int a0, int a1, int a2, int a3, int a4, int a5)
{
    int index;
    int sum;
    int slot;
    char *record;

    if (a0 == 0xFFFFFFFFU)
        return -1;
    sum = a0 * 4 + a1 * 2;
    sum += a2;
    index = sum + D_001B8F0C;
    if (index >= D_001B19E8)
        return -1;
    slot = AllocateSoundVoice((char *)(D_001B19EC + index * 32), a3, a4, 0, a5);
    if (slot >= 0) {
        record = D_00188660_3 + slot * 112;
        *(int *)(record + 136) = a4;
        *(short *)(record + 126) = index;
    }
    return slot;
}

extern Entry32fd6f60 D_L00_002A3B00[];

/* Table search: walks the 8-byte records of D_L00_002A3B00 until the key is
 * found or the -1 terminator is met, and stores the record's index and value. */
void resolve_lookup_record(Query *q)
{
    int i = 0;

    if (D_L00_002A3B00[0].key != -1 && D_L00_002A3B00[0].key != q->key) {
        do {
            i++;
        } while (D_L00_002A3B00[i].key != -1 && D_L00_002A3B00[i].key != q->key);
    }
    q->index = i;
    q->value = D_L00_002A3B00[i].value;
}

/* Sets the screen effect values and marks which parts changed so they get updated. */
void gfx_configure_screen_effect(int value60, int selector68, int value64, int axis69, int mode6A)
{
    Rac2Native_acdcf1600d770d3b_ScalarConfigure116State *state = D_00188660_2;
    state->value_60 = value60;
    if (state->selector_68 != selector68) {
        state->selector_68 = selector68;
        state->dirty_6b |= 1;
    }
    if (state->value_64 != value64) {
        state->value_64 = value64;
        state->dirty_6b |= 4;
    }
    if (state->axis_69 != axis69 || state->mode_6a != mode6A) {
        state->mode_6a = mode6A;
        state->axis_69 = axis69;
        state->dirty_6b |= 2;
    }
}

/* Stores a number at an address unless the address is empty. */
void mem_store_int_if_not_null(int value, long address) {
    int *target = (int *)(int)address;
    if (target != 0)
        *target = value;
}


typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vector;
typedef void (*DrawCallback)(void *);
extern int D_L00_001A8F00 __attribute__((sda));
extern char *D_L00_00220DA0[];
extern short D_L00_001A8F80[2] MACRO_ADDR;
extern unsigned int g_equipment_bits __attribute__((sda));
extern Vector g_camera_l00_position;
extern char g_hero_position[];

extern unsigned int D_00138324;
extern char g_hero_moby_default[];
extern int D_L00_001B1AE0 __attribute__((sda));
extern void UpdateEquipmentPieces(void *);
/* func_L00_002E6EF8 in level 0; its address differs in levels 8, 9, 19 and 30. */
extern void ref_L00_003603C0_00(DrawCallback, void *);
extern void gfx_add_draw_callback_first(DrawCallback, void *);
extern void render_environment_mapped_object(void *);
extern void gfx_draw_ground_shadow(void *);
extern float vec_distance_xy(void *, void *);
extern float fast_vec_dist(void *, void *);
extern float IntToFloat(int);
extern float math_fast_sin_or_cos_a(float);
extern int TryClaimNotice(int, int, int);
extern void matrix_mul_vec3(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern float coll_probe_ground_height_below(void *, int, float);
extern float FastAddRotations(float, float);
extern int level_release_matching_resource(int);

/* The hero's current vehicle (+0x2BC) is class 0xD54 and not in state 253 or 254. An inline
   function reading the pointer once compiles differently (964 bytes); retail matches the
   expression repeated at each use. */
#define HERO_VEHICLE (*(unsigned char **)(D_00189EA0 + 0x2BC))
#define HERO_RIDING_D54() \
    (HERO_VEHICLE && *(short *)(HERO_VEHICLE + 0xAA) == 0xD54 && \
     (unsigned char)HERO_VEHICLE[0x20] != 254 && (unsigned char)HERO_VEHICLE[0x20] != 253)

/* Updates a pickup that glows and can be used when Ratchet stands close, or is riding the vehicle. */
void pickup_update_interactive(unsigned char *object) {
    Vector position;
    Vector offset;
    Vector angles;
    unsigned char *private = *(unsigned char **)(object + 0x68);
    char **slot;
    int index;
    short key;
    char *spawn;
    unsigned int shade;
    int available;
    if (!D_L00_001A8F00) UpdateEquipmentPieces(object);
    if ((unsigned char)object[0x31]) {
        private[0xE] = (unsigned char)private[0xE] + 2;
        key = D_L00_001A8F80[(g_equipment_bits >> 4) & 1];
        for (index = 0; D_L00_00220DA0[index]; index++) {
            slot = D_L00_00220DA0 + index;
            if (*(short *)(D_L00_00220DA0[index] + 0xAA) == key) {
                shade = (int)(math_fast_sin_or_cos_a(IntToFloat((unsigned char)private[0xE] - 128) * 0.024543693f) * 50.0f) + 140;
                *(unsigned int *)(*slot + 0x78) = shade | (shade << 8) | (shade << 16);
                *(unsigned short *)(*slot + 0x34) |= 0x10;
                break;
            }
        }
        ref_L00_003603C0_00(render_environment_mapped_object, object);
        if (vec_distance_xy(object + 0x10, &g_camera_l00_position) < 32.0f)
            gfx_add_draw_callback_first(gfx_draw_ground_shadow, object);
    }
    if (*(short *)(private + 0xC) != 0) {
        if (fast_vec_dist(object + 0x10, &g_hero_position) > 6.1f && !HERO_RIDING_D54())
            *(short *)(private + 0xC) = 0;
    } else {
        if (vec_distance_xy(object + 0x10, &g_hero_position) < 8.0f || HERO_RIDING_D54()) {
            if (fast_vec_dist(object + 0x10, &g_hero_position) < 6.0f || HERO_RIDING_D54())
                *(short *)(private + 0xC) = 1;
        }
    }
    if (*(unsigned short *)(object + 0x34) & 1) *(short *)(private + 0xC) = 0;
    if (*(short *)(private + 0xC)) {
        available = TryClaimNotice(2, 0x2798, 1) != 0;
        if ((D_00138324 & 0x10) && available) {
            offset.q = 0;
            angles.q = 0;
            offset.f[0] = 1.48f;
            offset.f[1] = 2.64f;
            angles.f[0] = -0.021118486f;
            angles.f[1] = 0.0588176f;
            angles.f[2] = 1.2252212f;
            matrix_mul_vec3(&position, &offset, object + 0xC0);
            FastVecAdd(&position, &position, object + 0x10);
            position.f[2] = coll_probe_ground_height_below(&position, 0, 0.5f);
            angles.f[2] = FastAddRotations(angles.f[2], *(float *)(object + 0xF8));
            spawn = g_hero_moby_default + 0x70;
            qcopy(spawn, &position);
            qcopy(spawn + 0x10, &angles);
            level_release_matching_resource(2);
            *(short *)(spawn - 0x4A) = 0;
            D_L00_001B1AE0 = 1;
        }
    }
}


extern void load_start_disc_read(int value, char *target);

extern void snd_pump_music_and_disc_read(int value);

extern int D_L00_001BCAC0[];

extern int g_copy_setup_data[];

/* Same body as func_L00_003046D0: compares two words of a 332-byte-stride table and calls the
 * two helpers when the entry ahead is greater; returns 1. */
/* Moves to the next cutscene chunk if it holds data, and starts it playing. */
int cutscene_start_next_chunk(int index)
{
    int next_index = index + 1;
    int *sequence = D_L00_001BCAC0;
    int *base = g_copy_setup_data;
    int *table = (int *)((char *)base + 16040);
    int row_offset = sequence[12] * 332;
    int hold = sequence[28];
    int next_offset = next_index * 4;
    int current = *(int *)((char *)table + (row_offset + index * 4));
    int following = *(int *)((char *)table + (next_offset + row_offset));

    row_offset = following - current;
    if (row_offset > 0) {
        load_start_disc_read(hold, (char *)(current + base[3977]));
        snd_pump_music_and_disc_read(0);
    }
    return 1;
}

extern unsigned short D_00152C26;

/* Sets a flag to 1. */
void state_set_flag_one(void) {
    D_00152C26 = 1;
}

/* func_L00_00367308 is defined in L00_00358D98-g8.c. */

#define NOT_SDA __attribute__((section(".data")))

extern void *r1_D_0012F86C_00367720 NOT_SDA;

/* rac1-decomp src/core/001138A8.c: func_001138A8 */
/* Returns a stored pointer value as a number. */
int state_get_stored_pointer_value(void) {
    return (int)r1_D_0012F86C_00367720;
}





/* Original assembly: $at as a working register (lw $at,off($a0)) and lui $ra in the return delay slot. */
ASM_FUNC("asm/levels", func_L00_0036BE28);

/* Original assembly: $at as a working register (lw $at,off($a0)) and lui $ra in the return delay slot. */
ASM_FUNC("asm/levels", func_L00_0036C9AC);

/* Original assembly: $at as a working register (lw $at,off($a0)) and lui $ra in the return delay slot. */
ASM_FUNC("asm/levels", func_L00_0036C9D4);

/* Original assembly: $at as a working register (lw $at,off($a0)) and lui $ra in the return delay slot. */
ASM_FUNC("asm/levels", func_L00_0036D274);

/* Original assembly: $at as a working register (lw $at,off($a0)) and lui $ra in the return delay slot. */
ASM_FUNC("asm/levels", func_L00_0036D29C);

/* Original assembly: $at as a working register (lw $at,off($a0)) and lui $ra in the return delay slot. */
ASM_FUNC("asm/levels", func_L00_0036EF40);

/* Original assembly: $at as a working register and trapping add/addi; the compiler cannot emit them. */
ASM_FUNC("asm/levels", func_L00_0036EF68);

/* Does nothing and returns 0. */
unsigned int stub_l00_return_zero_4(void)
{
    return 0;
}

/* func_L00_0036F488 is defined in L00_0036F488-g8.c. */

extern unsigned int g_save_menu_flags __attribute__((sda));

/* The level's own resident word and resident object: each place resolves its own value from
 * the retail bytes (0x001A8F00 and 0x001AC0C0 in 00_aranos_tutorial), so both are sda. */
extern int ref_L00_001A8F00_00 __attribute__((sda));

typedef struct L00_0036FA68_Object {
    unsigned char pad00[0x64];
    void (*field64)(struct L00_0036FA68_Object *);
} L00_0036FA68_Object;

extern L00_0036FA68_Object *ref_L00_001AC0C0_00 __attribute__((sda));

extern void SetBackgroundColor(int a, int b, int c);

extern int request_begin_slot(int a, int b, int c, int d, int e);

extern void game_reset_frame_counters(void);

extern void UpdateSoundVoices(void);

extern void part_update_all(void);

extern void level_count_active_records(void);

/* The tick gate's callee is a neighbouring local function in six of the programs. */
extern unsigned int ref_L00_0036FA68_00(void);

extern void game_update_idle_frame_counters(void);

extern void subtitle_update_state_machine(void);

/* Runs the level's tick chain once: the three-argument engine reset, a gate on the resident
 * word and the boot flag, then the subsystem updates and the resident object's callback. */
/* Runs one frame of the main update steps, then calls the update function of the level object. */
void level_run_frame_update_chain(void)
{
    L00_0036FA68_Object *object;

    SetBackgroundColor(0, 0, 0);
    if (ref_L00_001A8F00_00 == 0 && (g_save_menu_flags & 1)) {
        if (request_begin_slot(4, 1, 1, 0, 0) == 0)
            return;
    }
    if (ref_L00_0036FA68_00() != 0)
        return;
    game_reset_frame_counters();
    UpdateSoundVoices();
    part_update_all();
    level_count_active_records();
    object = ref_L00_001AC0C0_00;
    object->field64(object);
    game_update_idle_frame_counters();
    subtitle_update_state_machine();
}


/* func_L00_00373D40 is defined in L00_00373D40-g8.c. */

/* Empty function that does nothing. */
void stub_l00_nop(void)
{
}

/* func_L00_00373F48 is defined in L00_00373F48-g64.c. */

/* func_L00_00374348 is defined in L00_00374348.c. */

extern int D_0022F810;

/* Dispatch on a mode word: mode 1 goes through the recording wrapper, the other modes replay. */
/* Picks what to do for the current mode of the menu. */
void menu_dispatch_by_mode(void)
{
    switch (D_0022F810) {
    case 0:
        UpdateShopMenuInput();
        break;
    case 1:
        menu_call_update();
        break;
    case 2:
        UpdateShopMenuInput();
        break;
    case 3:
        UpdateShopMenuInput();
        break;
    }
}

extern void func_3747B0(void);

/* Calls the menu update function. */
void menu_call_update(void) {
    func_3747B0();
}

/* func_L00_00374C18 is defined in L00_00374C18-g8.c. */



/* func_L00_003769C0 is defined in L00_003769C0.c. */



/* Draws the selected-item panel, its value and label, and the top counter. */
void DrawSelectedItemInfoPanel(void) {
    PanelColors colors;
    char text[256];
    char *model = (char *)&g_purchase_menu_model;
    int index = *(int *)(model + 0x80);
    colors = D_L00_001AD768;
    D_L00_001B1BB8[1] = 0;
    hud_draw_sprite_gradient(GetIconFrame(0xEAA8, 0), 16, (int)(D_L00_001B25E0 * 51.0f + 0.5f),
                  192, (int)(D_L00_001B25E0 * 96.0f + 0.5f), colors.word);
    hud_draw_sprite_gradient(GetIconFrame(0xEAA8, 0), 400, (int)(D_L00_001B25E0 * 51.0f + 0.5f),
                  -192, (int)(D_L00_001B25E0 * 96.0f + 0.5f), colors.word);
    hud_draw_sprite_gradient(GetIconFrame(0xEAA8, 0), 16, (int)(D_L00_001B25E0 * 243.0f + 0.5f),
                  192, -(int)(D_L00_001B25E0 * 96.0f + 0.5f), colors.word);
    hud_draw_sprite_gradient(GetIconFrame(0xEAA8, 0), 400, (int)(D_L00_001B25E0 * 243.0f + 0.5f),
                  -192, -(int)(D_L00_001B25E0 * 96.0f + 0.5f), colors.word);
    text_draw_right_aligned_medium(270, (int)(D_L00_001B25E0 * 218.0f + 0.5f), 0x80F0F0F0ULL,
                  (unsigned char *)GetLocalizedString(0x318C), -1);
    text_format_number_with_separators(text, g_purchase_menu_model.items[index].price);
    text_draw_medium(270, (int)(D_L00_001B25E0 * 218.0f + 0.5f), 0x80F0F0F0ULL, (unsigned char *)text, -1);
    text_draw_centered_medium(g_screen_width >> 1, (int)(D_L00_001B25E0 * 277.0f + 0.5f), 0x80F0F0F0ULL,
                  g_purchase_menu_model.items[index].name, -1);
    colors.word[3] = 0x60F0F0B0;
    colors.word[2] = 0x60F0F0B0;
    colors.word[1] = 0x60F0F0B0;
    colors.word[0] = 0x60F0F0B0;
    text_format_number_with_separators(text, D_001A79FC);
    text_draw_right_aligned_small(444, 17, 0x80FFFFFFULL, (unsigned char *)text, -1);
    hud_draw_sprite_gradient(GetIconFrame(0xEAA2, 3), 458, (int)(D_L00_001B25E0 * 15.0f + 0.5f),
                  32, (int)(D_L00_001B25E0 * 32.0f + 0.5f), colors.word);
}


/* func_L00_00377C50 is defined in L00_00377C50-g8.c. */

/* func_L00_003781B0 is defined in L00_003781B0.c. */


/* func_L00_00378578 is defined in L00_00378578.c. */

/* Draws the selected purchase prompt, quantity, total price and bolt icon. */
void DrawVendorPurchasePanel(void) {
    TextLayout copy;
    /* This 24-byte workspace becomes the four-color array after drawing text. */
    union { TextLayout layout; unsigned int colors[4]; } seed;
    char text[256];
    PurchaseModel *model = (PurchaseModel *)&g_purchase_menu_model;
    int index;
    int message;
    unsigned short unit_price;
    if (model->active == 0) return;
    memset(&seed.layout, 0, 24);
    seed.layout.field[0] = 120;
    seed.layout.field[1] = (short)(D_L00_001B25E0 * 200.0f + 0.5f);
    seed.layout.field[2] = 160;
    seed.layout.field[3] = 352;
    seed.layout.field[4] = 256;
    seed.layout.field[5] = (short)(D_L00_001B25E0 * 160.0f + 0.5f);
    seed.layout.field[6] = 184;
    seed.layout.field[7] = (short)(D_L00_001B25E0 * 72.0f + 0.5f);
    seed.layout.field[8] = 16;
    seed.layout.field[9] = 3;
    copy = seed.layout;
    index = model->index;
    if (model->entries[index].kind == 1) {
        int selected_id = model->entries[index].id;
        unit_price = ((ShopClass *)g_weapon_l00_table)[g_item_slot_to_record[selected_id]].price;
        if ((int)unit_price <= g_player_bolts) {
            copy.field[9] = 1;
            copy.field[5] = (short)((float)(copy.field[0] + 12) * D_L00_001B25E0 + 0.5f);
            text_draw_window_medium(&copy, 0x80F0F0F0ULL, (unsigned char *)GetLocalizedString(0x1127), -1);
            sprintf(text, D_L00_001AD798, D_L00_001B25A8);
            copy.field[5] = (short)((float)(copy.field[0] + 40) * D_L00_001B25E0 + 0.5f);
            text_draw_window_medium(&copy, 0x80F0F0F0ULL, (unsigned char *)text, -1);
            sprintf(text, D_L00_001AD6C8, (unsigned int)D_L00_001B25A8 *
                ((ShopClass *)g_weapon_l00_table)[g_item_slot_to_record[model->entries[model->index].id]].price);
            text_draw_right_aligned_medium(256, (int)(D_L00_001B25E0 * 180.0f + 0.5f), 0x80F0F0F0ULL, (unsigned char *)text, -1);
            seed.colors[0] = 0x60F0F0B0;
            seed.colors[1] = 0x60F0F0B0;
            seed.colors[2] = 0x60F0F0B0;
            seed.colors[3] = 0x60F0F0B0;
            hud_draw_sprite_gradient(GetIconFrame(0x7567, 0), 260, (int)(D_L00_001B25E0 * 180.0f + 0.5f),
                          16, (int)(D_L00_001B25E0 * 16.0f + 0.5f), seed.colors);
            return;
        }
        message = 0x1128;
    } else {
        if (g_player_bolts >= GetSelectedShopItemPrice()) {
            copy.field[9] = 1;
            copy.field[5] = (short)((float)(copy.field[0] + 6) * D_L00_001B25E0 + 0.5f);
            message = 0x1129;
        } else goto no_money;
    }
    text_draw_window_medium(&copy, 0x80F0F0F0ULL, (unsigned char *)GetLocalizedString(message), -1);
    return;
no_money:
    text_draw_window_medium(&copy, 0x80F0F0F0ULL, (unsigned char *)GetLocalizedString(0x1128), -1);
}

/* Measured rows of the confirmation prompt: the price is their first word. */
typedef struct { int price; int rest[2]; } ConfirmRow;
typedef struct {
    char prefix[0x80];
    int index;
    int active;
    char padding[0xBC];
    ConfirmRow rows[0];
} ConfirmModel;
/* The call must reach the compiler's builtin: its argument setup order differs from a plain call. */
extern void *memset(void *, int, unsigned int);

/* Draws the confirmation prompt, with another message and layout when the price is affordable. */
void DrawPurchaseAffordabilityPrompt(void) {
    TextLayout copy;
    TextLayout layout;
    ConfirmModel *model = (ConfirmModel *)&g_purchase_menu_model;
    int top;
    float scale;
    if (model->active == 0) return;
    memset(&layout, 0, sizeof(layout));
    top = 314;
    scale = D_L00_001B25E0;
    layout.field[0] = (short)(scale * 120.0f + 0.5f);
    layout.field[1] = (short)(scale * top + 0.5f);
    layout.field[2] = top;
    layout.field[3] = 486;
    layout.field[4] = 400;
    layout.field[5] = (short)(scale * 217.0f + 0.5f);
    layout.field[6] = 164;
    layout.field[7] = (short)(scale * 186.0f + 0.5f);
    layout.field[8] = 16;
    layout.field[9] = 3;
    copy = layout;
    if (g_player_bolts >= model->rows[model->index].price) {
        copy.field[9] = 1;
        copy.field[5] = (short)((float)(copy.field[0] + 40) * scale + 0.5f);
        text_draw_window_medium(&copy, 0x80F0F0F0ULL, (unsigned char *)GetLocalizedString(0x1129), -1);
    } else {
        text_draw_window_medium(&copy, 0x80F0F0F0ULL, (unsigned char *)GetLocalizedString(0x1128), -1);
    }
}

/* func_L00_00378DE0 is defined in L00_00378DE0-g8.c. */

/* func_L00_00378E90 is defined in L00_00378E90.c. */

/* func_L00_0037A2E8 is defined in L00_0037A2E8-qcopy.c. */

/* func_L00_0037A610 is defined in L00_0037A610-g8.c. */

/* Empty function that does nothing. */
void stub_l00_nop_2(void)
{
}
