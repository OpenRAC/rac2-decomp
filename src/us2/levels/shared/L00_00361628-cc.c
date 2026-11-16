/* func_US2_L00_00361628, the USA v2.00 copy of func_L00_003603C0: the same C, where rename func_002E64A0 becomes func_US2_002E72D8. */
#include "common.h"

/* Measured purchase-panel layout and pricing records. */
/* Layouts measured from the selected-item panel. */
typedef struct { unsigned int word[4]; } PanelColors;
typedef struct { int price; int pad[3]; unsigned char *name; int pad2[2]; } ShopItem;
extern PanelColors g_menu_panel_colors;
typedef struct { char prefix[0x144]; ShopItem items[0]; } ShopModel;
extern ShopModel g_purchase_menu_model;
typedef struct {
    int key;
    int value;
} Entry32fd6f60;

extern Entry32fd6f60 g_level_entry_table[];

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
/* Shared slot table: the first free record of a 112-byte table is filled with the index and the
 * caller's value; returns the record number, or -1 when the index is out of range. */
/* Same slot table as func_L00_0035F5A0, but with the caller's own record: the helper gets the
 * slot's record, the value goes in at 0x40 and the helper's second value becomes the fifth
 * argument; the record's index word is written at 126 and the value word at 140. */
/* Builds a slot index out of three weight/kind arguments and fills the same 112-byte record as
 * above; the record's value word comes from the fifth argument, the helper's from the sixth. */
extern Entry32fd6f60 g_sound_lookup_table[];

/* Table search: walks the 8-byte records of D_L00_002A3B00 until the key is
 * found or the -1 terminator is met, and stores the record's index and value. */
typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vector;
typedef void (*DrawCallback)(void *);
extern int g_game_l00_mode __attribute__((sda));
extern char *g_launch_moby_list[];
extern short g_pickup_key_ids[2] MACRO_ADDR;
extern unsigned int g_equipment_bits __attribute__((sda));
extern Vector g_camera_l00_position;
extern char g_hero_position[];

extern unsigned int g_pad_held_flags;
extern char g_hero_moby_default[];
extern int g_pickup_request_pending __attribute__((sda));
extern void UpdateEquipmentPieces_us2(void *);
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

/* Updates a pickup that glows and pulses its colour, and activates when the hero is near or riding vehicle class 0xD54. */
void pickup_update_interactive_us2(unsigned char *object) {
    Vector position;
    Vector offset;
    Vector angles;
    unsigned char *private = *(unsigned char **)(object + 0x68);
    char **slot;
    int i;
    short key;
    char *spawn;
    unsigned int shade;
    int available;
    if (!g_game_l00_mode) UpdateEquipmentPieces_us2(object);
    if ((unsigned char)object[0x31]) {
        private[0xE] = (unsigned char)private[0xE] + 2;
        key = g_pickup_key_ids[(g_equipment_bits >> 4) & 1];
        for (i = 0; g_launch_moby_list[i]; i++) {
            slot = g_launch_moby_list + i;
            if (*(short *)(g_launch_moby_list[i] + 0xAA) == key) {
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
        available = TryClaimNotice(2, 0x12ea, 1) != 0;
        if ((g_pad_held_flags & 0x10) && available) {
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
            g_pickup_request_pending = 1;
        }
    }
}

/* Same body as func_L00_003046D0: compares two words of a 332-byte-stride table and calls the
 * two helpers when the entry ahead is greater; returns 1. */
/* func_L00_00367308 is defined in L00_00358D98-g8.c. */

#define NOT_SDA __attribute__((section(".data")))

extern void *r1_D_0012F86C_00367720 NOT_SDA;

/* rac1-decomp src/core/001138A8.c: func_001138A8 */
/* func_L00_0036F488 is defined in L00_0036F488-g8.c. */

/* The level's own resident word and resident object: each place resolves its own value from
 * the retail bytes (0x001A8F00 and 0x001AC0C0 in 00_aranos_tutorial), so both are sda. */
typedef struct L00_0036FA68_Object {
    unsigned char pad00[0x64];
    void (*field64)(struct L00_0036FA68_Object *);
} L00_0036FA68_Object;

extern L00_0036FA68_Object *ref_L00_001AC0C0_00 __attribute__((sda));

/* The tick gate's callee is a neighbouring local function in six of the programs. */
/* Runs the level's tick chain once: the three-argument engine reset, a gate on the resident
 * word and the boot flag, then the subsystem updates and the resident object's callback. */
/* func_L00_00373D40 is defined in L00_00373D40-g8.c. */

/* func_L00_00373F48 is defined in L00_00373F48-g64.c. */

/* func_L00_00374348 is defined in L00_00374348.c. */

/* Dispatch on a mode word: mode 1 goes through the recording wrapper, the other modes replay. */
/* func_L00_00374C18 is defined in L00_00374C18-g8.c. */

/* Draws the selected-item panel, its value and label, and the top counter. */
/* func_L00_00377C50 is defined in L00_00377C50-g8.c. */

/* func_L00_003781B0 is defined in L00_003781B0.c. */

/* func_L00_00378578 is defined in L00_00378578.c. */

/* Draws the selected purchase prompt, quantity, total price and bolt icon. */
/* Measured rows of the confirmation prompt: the price is their first word. */
/* The call must reach the compiler's builtin: its argument setup order differs from a plain call. */
/* Draws the confirmation prompt, with another message and layout when the price is affordable. */
/* func_L00_00378DE0 is defined in L00_00378DE0-g8.c. */

/* func_L00_00378E90 is defined in L00_00378E90.c. */

/* func_L00_0037A2E8 is defined in L00_0037A2E8-qcopy.c. */

/* func_L00_0037A610 is defined in L00_0037A610-g8.c. */

