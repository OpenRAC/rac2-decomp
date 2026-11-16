/* func_PAL_L00_003021B0: the level gameplay loader. It relocates the level file's
 * sections (ties, shrubs, mobys, moby groups, paths, occlusion) into the aligned level
 * heap and returns the heap cursor. RAC1 counterpart: load_level_gameplay
 * (rac1-decomp src/overlays/shared/level_gameplay_loading.c), whose source shapes
 * this follows: the function-scope scratch int `tmp`, sequential record reads through
 * char pointers, and header words read as ints (RAC1 reads them as struct members).
 * The section-8 records are copied by an explicit goto loop: a do loop has its four
 * cursor advances turned into address givs by this cc1 (docs/COMPILER-NOTES.md).
 *
 * The PAL copy of func_L00_00300618: the same C, where the moby and tie index table
 * is the last 64 KB below the second buffer (D_001B22A0[1] + D_001B22B0 - 0x10000)
 * instead of the pointer in D_L00_001B19F0, each of its two users has its own table
 * local (retail keeps them in different registers), and func_00272198 takes 7.0f.
 */
#include "common.h"

typedef int TI128_00618 __attribute__((mode(TI)));
typedef union { TI128_00618 q; float f[4]; int i[4]; } Vec00618;

#define ALIGN64_00618(p) ((char *)(((int)(p) + 0x3F) & 0xFFFFFFC0u))
#define SECTION_00618(off) (hdr + ((int *)hdr)[(off) / 4])
#define SAVE_CELL_00618(uid) D_0019B4A8[((uid) >> 1) + (D_001A79F0 << 10)]

typedef struct {
    char pad00[0xC];
    char *data;                   /* 0x0C: the level data image */
    int i10;
    int i14;
    int i18;
    char pad1C[0x2C];
    char *heap;                   /* 0x48 */
    char *mark4C;
    char *mark50;
    char *mark54;
    char *mark58;
    char *mark5C;
    char *mark60;
    char *mark64;
} LoadCtx00618;

typedef struct { char pad00[0x529C]; int i529C; char pad52A0[0x18]; int i52B8; int i52BC; } Boot00618;
typedef struct { char pad00[0x23C]; int i23C; int i240; int i244; } Cfg00618;
typedef struct { void *hero; char pad04[0x3C]; int i40; int i44; int i48; } Sel00618;
typedef struct { char pad00[8]; int i8; char pad0C[0x84]; } Sound00618;  /* 0x90 */
typedef struct { char pad00[0x1730]; int count; Sound00618 *table; } Slots00618;
typedef struct { char pad00[0xC]; int count; int i10; unsigned short *bits; int i18; int i1C; float pos[2][4]; float dir[2][4]; } Tutorial00618;
typedef struct { char pad00[4]; char *p4; char *p8; int iC; int i10; int i14; } Coll00618;

typedef struct {
    Vec00618 bounds;              /* 0x00 */
    unsigned short h10;
    short h12;
    unsigned short h14;
    short h16;
    short h18;
    unsigned short h1A;
    unsigned char b1C;
    unsigned char b1D;            /* class index */
    unsigned char b1E;
    unsigned char b1F;
} Tie00618;                       /* 0x20 */

typedef struct { Vec00618 row[4]; } Matrix00618;   /* 0x40 */

typedef struct {
    char pad00[0x20];
    Tie00618 *first;              /* 0x20 */
    char pad24[0xC];
    char *table;                  /* 0x30 */
    char pad34[4];
    short h38;
    char pad3A[4];
    unsigned short h3E;
    float f40;
    char pad44[0xC];
    Vec00618 sphere;              /* 0x50: centreXYZ and radius */
} TieClass00618;

typedef struct {
    Vec00618 bounds;              /* 0x00 */
    float f10;
    char pad14[3];
    unsigned char b17;
    short h18;
    unsigned char b1A;            /* class index */
    unsigned char b1B;
    unsigned short h1C;
    unsigned short h1E;
} Shrub00618;                     /* 0x20 */

typedef struct {
    char pad00[0xC];
    float fC;
    char pad10[6];
    unsigned short h16;
    Shrub00618 *first;            /* 0x18 */
    float *p1C;
    float f20;
} ShrubClass00618;

typedef struct {
    char pad00[0x10];
    Vec00618 pos;                 /* 0x10 */
    unsigned char state;          /* 0x20 */
    unsigned char b21;
    char pad22[2];
    char *pClass;                 /* 0x24 */
    char pad28[4];
    float f2C;
    unsigned char b30;
    char pad31;
    unsigned short h32;
    unsigned short h34;
    unsigned short h36;
    int i38;
    char pad3C[0x27];
    unsigned char b63;
    int i64;
    int i68;
    char pad6C[0x12];
    unsigned char b7E;
    char pad7F[0x2B];
    short oClass;                 /* 0xAA */
    char padAC[4];
    unsigned char bB0;
    unsigned char bB1;
    short hB2;
    short hB4;
    short hB6;
    char padB8[0x38];
    float rot[4];                 /* 0xF0 */
} Moby00618;                      /* 0x100 */

typedef struct { char pad00[0x24]; float f24; char pad28[0x1C]; unsigned short h44; } MobyClass00618;

typedef struct {
    short h0, h2, h4, h6, h8;
    char pad0A[2];
    int iC, i10, i14, i18, i1C;
    char pad20[0x10];
} GroupEntry00618;                /* 0x30 */

typedef struct Groups00618 {
    int count;                    /* 0x00 */
    char *p4;
    char *p8;
    char *pC;
    char *p10;
    char *p14;
    char pad18[0x18];
    GroupEntry00618 entries[0];   /* 0x30 */
} Groups00618;

typedef struct { int offset; int size; } Blob00618;
typedef struct { int p14; int i18; int p1C; int i20; } Reloc00618;
extern Reloc00618 g_level_reloc_record MACRO_ADDR;
extern int g_region_members_table MACRO_ADDR;
extern struct Groups00618 *g_region_group_table MACRO_ADDR;
extern char *g_collision_pill_table MACRO_ADDR;   /* clip volumes, 0x90 bytes each */
extern int g_collision_pill_count MACRO_ADDR;
extern char *g_aranos_launch_poses MACRO_ADDR;   /* cuboids */
extern int g_collision_sphere_count MACRO_ADDR;
extern char *g_collision_sphere_table MACRO_ADDR;   /* spheres */
extern int g_collision_cylinder_count MACRO_ADDR;
extern char *g_collision_cylinder_table MACRO_ADDR;   /* cylinders */
extern int g_collision_record_count MACRO_ADDR;
extern int g_path_count MACRO_ADDR;     /* path count */
extern char *g_path_data MACRO_ADDR;   /* path data */
typedef struct { Vec00618 head; char *data; int i14; char pad18[8]; } Rail00618;   /* 0x20 */
extern Rail00618 *g_rail_table MACRO_ADDR;
extern int g_rail_count MACRO_ADDR;
extern char *g_level_data_block_ptr MACRO_ADDR;
extern int g_level_state_word_first MACRO_ADDR;
extern int g_level_state_word_second MACRO_ADDR;
extern int g_level_state_word_third MACRO_ADDR;

extern LoadCtx00618 g_level_load_context;
extern Boot00618 g_copy_setup_data;
typedef struct { int stage, busy; int *archive0; int archive1; } ArchiveLoad;
extern ArchiveLoad g_loader_archives MACRO_ADDR;
extern char g_hero_state[];
extern char g_scalar_transition_state[];
extern char g_level_clear_area_a[];
extern int g_is_pal_video MACRO_ADDR;
extern float g_frame_rate_scale MACRO_ADDR;
extern Coll00618 g_collision_result;
extern char g_collision_result_pointer[];
extern char g_collision_result_buffer[];
extern char g_level_clear_area_b[];
extern char g_level_clear_area_c[];
extern Cfg00618 g_hud_float_params;
extern unsigned char g_fog_color_r MACRO_ADDR;
extern unsigned char g_fog_color_g MACRO_ADDR;
extern unsigned char g_fog_color_b MACRO_ADDR;
extern float g_fog_near MACRO_ADDR;
extern float g_fog_far MACRO_ADDR;
extern float g_fog_near_intensity MACRO_ADDR;
extern float g_fog_far_intensity MACRO_ADDR;
extern int g_hero_locked_flag MACRO_ADDR;
extern float g_hero_proximity_threshold MACRO_ADDR;
extern float g_camera_offset_vector MACRO_ADDR;
extern float g_level_float_param_first MACRO_ADDR;
extern float g_level_float_param_second MACRO_ADDR;
extern float g_level_float_param_third MACRO_ADDR;
extern Sel00618 g_hero_moby_default;
extern Tutorial00618 g_tutorial_points;
extern int g_level_reloc_word MACRO_ADDR;
extern int g_light_distance_param MACRO_ADDR;
extern float g_light_far_param MACRO_ADDR;
extern float g_light_falloff_param MACRO_ADDR;
extern int g_light_scale_first MACRO_ADDR;
extern int g_light_scale_second MACRO_ADDR;
extern char g_gfx_dma_chain_buffer[];
extern char g_light_table[];
extern char g_effect_slot_records[];
extern char g_level_block_buffer[];
extern char g_str_startup_message[];
extern int g_level_entry_count MACRO_ADDR;
extern char g_level_copy_buffer[];
extern char g_level_entries_buffer[];
extern int g_tfrag_count MACRO_ADDR;
typedef struct { char pad00[0x36]; unsigned short h36; char pad38[2]; unsigned short h3A; char pad3C; unsigned char b3D; char pad3E[2]; } Tfrag00618;   /* 0x40 */
extern char *g_tfrag_render_data MACRO_ADDR;
typedef struct { char pad00[0x2C]; int count; } TextHdr00618;
extern TextHdr00618 g_tutorial_prompt_state;
extern unsigned char g_option_toggle_b[] MACRO_ADDR; /* option bytes; [2] is the language */
typedef struct { int offset; int pad4[3]; } Text00618;
extern Text00618 *g_level_text_table MACRO_ADDR;
extern int g_tie_count MACRO_ADDR;
extern Tie00618 *g_tie_table MACRO_ADDR;
extern Tie00618 *g_tie_table_end MACRO_ADDR;
extern Matrix00618 *g_tie_matrix_table MACRO_ADDR;
extern int g_level_value_word MACRO_ADDR;
extern int g_level_zero_word_first MACRO_ADDR;
extern int g_level_zero_word_second MACRO_ADDR;
extern int g_level_zero_word_third MACRO_ADDR;
extern int g_render_class_slot_count MACRO_ADDR;
extern TieClass00618 *g_tie_class_table[];
extern unsigned char g_tie_slot_by_class[];
extern Shrub00618 *g_shrub_table MACRO_ADDR;
extern int g_shrub_count MACRO_ADDR;
extern Matrix00618 *g_shrub_matrix_table MACRO_ADDR;
extern unsigned char *g_shrub_data_table MACRO_ADDR;
extern Shrub00618 *g_shrub_table_end MACRO_ADDR;
extern int g_level_l00_pointer_table[];
extern ShrubClass00618 *g_shrub_l00_class_table[];
extern unsigned char g_shrub_slot_by_class[];
typedef struct { float f0, f4, f8; int iC; float f10, f14, f18; int i1C; } Cam00618;
extern Cam00618 *g_camera_def_table MACRO_ADDR;
extern int g_camera_def_count MACRO_ADDR;
extern Slots00618 g_sound_state;
extern int g_collectible_value_table[][3];
extern int g_collectible_bonus_table[][3];
extern Moby00618 *g_moby_array_base[] MACRO_ADDR; /* moby array start (array: in-struct for alias analysis) */
extern Moby00618 *g_moby_list_tail MACRO_ADDR;
extern Moby00618 *g_moby_array_end_sentinel MACRO_ADDR;
extern Moby00618 *g_moby_array_last MACRO_ADDR;
extern char *g_level_heap_block_ptr MACRO_ADDR;
extern short g_moby_index_table[];
extern int g_current_map_index MACRO_ADDR;
extern unsigned char g_moby_group_flags[];
extern unsigned char g_moby_nibble_table[];
typedef struct { unsigned char pad[0x464]; unsigned char byUid[0]; } Progress00618;
extern Progress00618 g_controller_level_state;
extern unsigned char g_class_l00_flags_table[] MACRO_ADDR;
extern int g_turn_state_table[];
extern int g_moby_l00_group_count MACRO_ADDR;
extern char *g_launch_path_table[];
extern char *g_collision_grid_data MACRO_ADDR;
extern char *g_level_table_data MACRO_ADDR;
extern int g_level_table_count MACRO_ADDR;
extern char *g_env_preset_table MACRO_ADDR;
extern int g_env_preset_count MACRO_ADDR;
extern char g_level_clear_area_d[];
extern int g_level_header_extra_ptr MACRO_ADDR;
extern int g_packet_buffer_table[];
extern int g_packet_buffer_size MACRO_ADDR;
extern int g_aranos_launch_state MACRO_ADDR;
extern short g_level_counter_a NOT_SDA;
extern short g_moby_index_list_head NOT_SDA;
extern short g_homing_moby_index_list MACRO_ADDR;
extern short g_decoy_moby_index_list MACRO_ADDR;
extern short g_dark_sheep_moby_index_list MACRO_ADDR;
extern int g_launch_moby_list[];
extern int g_frame_l00_counter MACRO_ADDR;
extern int g_nanotech_ball_moby MACRO_ADDR;
extern int g_render_state_word MACRO_ADDR;
extern char g_level_blob_a[] __attribute__((sda));
extern char g_level_l00_flag_word[] __attribute__((sda));
extern char *g_setup_heap_pointer MACRO_ADDR;
extern char *g_level_blob_ptr MACRO_ADDR;

extern int load_read_disc_with_pause_pal(void *, int, int);
extern void FlushCache(int);
extern int fast_decompress_pal(void *, void *);
extern void mem_clear(void *, int, int);
extern void moby_clear_object_slots(void);
extern void func_001163A0(int);
extern void SetFrameTimingMode(int);
extern void mem_fast_helper_b(void *, int);
extern void gfx_apply_display_config(void);
extern void SetBackgroundColor(int, int, int);
extern void gfx_start_dma_channel0_and_wait(void *);
extern void STUB_printf(const char *, ...);
extern void mem_copy_aligned(void *, void *, int);
extern void func_002F0468(void *);
extern void matrix_mul_vec3(void *, void *, void *);
extern float FastVecLength(void *);
extern float math_max_float(float, float);
extern void scale_vector(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern void mem_fast_helper_c(void *, void *, int);
extern int FloatToInt(float);
extern float IntToFloat(int);
extern void shrub_process_render_data(void *);
extern void resolve_lookup_record(void *);
extern int level_get_difficulty_scaled(int);
extern void func_PAL_0029FA60(void *, int);
extern float coll_probe_ground_height_below(void *, int, float);
extern void func_002A0F48(void *);
extern void gfx_pack_render_command_fields(void *, u64, u64, u64, u64);
extern void level_store_value_in_table_slot(void *, int);
extern Moby00618 *CreateMoby(int);
extern void counter_clear_group(void);
extern void InitializeHero_pal(void);
extern void hero_reset_start_aim_speed(void);
extern void SetupLevelCameras(void);
extern void cam_update_state_pal(void);
extern void pad_clear_port_state(void);
extern void level_init_object_tables(void);
extern void func_PAL_L00_00369AF8(void);
extern void level_clear_slot_table(void);
extern void level_l00_clear_counter_list(void);
extern void level_l00_clear_counter_list_2(void);
extern void moby_clear_fading_list(void);
extern void gfx_enable_draw_flag(void);
extern void sheep_clear_active_list(void);
extern void cam_set_transition_frames(float);
extern void pickup_update_interactive(unsigned char *);

char *func_PAL_L00_003021B0(int reload)
{
    char *hdr = g_level_load_context.data;
    char *heap = g_level_load_context.heap;
    float *startPos;
    short *idx = g_moby_index_table; /* moby index by file order, rebuilt at each use */
    int tmp; /* scratch int: section 0x44's data base, a group's offset and end flag in the group loop */
    char *p;

    if (!reload) {
        load_read_disc_with_pause_pal(heap, g_copy_setup_data.i52B8 + g_copy_setup_data.i529C, g_copy_setup_data.i52BC);
        g_loader_archives.archive1 = (int)heap;
    }
    FlushCache(0);
    fast_decompress_pal((void *)g_loader_archives.archive1, hdr);
    FlushCache(0);
    mem_clear(g_hero_state, 0, 0x2540);
    mem_clear(g_scalar_transition_state, 0, 0x410);
    mem_clear(g_level_clear_area_a, 0, 0x180);
    moby_clear_object_slots();
    func_001163A0(1234);
    if (g_is_pal_video) {
        if (g_frame_rate_scale == 1.0f)
            SetFrameTimingMode(1);
    } else {
        if (g_frame_rate_scale != 1.0f)
            SetFrameTimingMode(0);
    }
    g_collision_result.p4 = g_collision_result_pointer;
    g_collision_result.p8 = g_collision_result_buffer;
    g_collision_result.iC = 0;
    g_collision_result.i10 = 0;
    g_collision_result.i14 = 0;
    mem_fast_helper_b(g_level_clear_area_b, 0x1C000);
    mem_fast_helper_b(g_level_clear_area_c, 0xC0);

    /* section 0: the level header */
    p = SECTION_00618(0);
    g_hud_float_params.i23C = *(int *)p;
    p += 4;
    g_hud_float_params.i240 = *(int *)p;
    p += 4;
    g_hud_float_params.i244 = *(int *)p;
    p += 4;
    g_fog_color_r = *(unsigned char *)p;
    p += 4;
    g_fog_color_g = *(unsigned char *)p;
    p += 4;
    g_fog_color_b = *(unsigned char *)p;
    p += 4;
    g_fog_near = *(float *)p;
    g_fog_far = *(float *)(p + 4);
    g_fog_near_intensity = *(float *)(p + 8);
    g_fog_far_intensity = *(float *)(p + 0xC);
    g_hero_proximity_threshold = *(float *)(p + 0x10);
    g_hero_locked_flag = 0;
    p += 0x14;
    if (*(int *)p) {
        g_hero_locked_flag = 1;
        g_camera_offset_vector = *(float *)(p + 4);
        g_level_float_param_first = *(float *)(p + 8);
        g_level_float_param_second = *(float *)(p + 0xC);
        g_level_float_param_third = 1.0f;
    }
    startPos = (float *)(p + 0x10);
    p += 0x20;
    g_hero_moby_default.i40 = *(int *)p;
    g_hero_moby_default.i44 = *(int *)(p + 4);
    g_hero_moby_default.i48 = *(int *)(p + 8);
    g_tutorial_points.count = 0;
    p += 0x10;
    if (*(int *)(p + 0xC)) {
        int i;

        g_tutorial_points.count = *(int *)(p + 0xC);
        for (i = 0; i < g_tutorial_points.count; i++) {
            float *e = (float *)((char *)&g_tutorial_points + (i << 4));

            e[8] = *(float *)p;
            e[9] = *(float *)(p + 4);
            e[10] = *(float *)(p + 8);
            e[16] = *(float *)(p + 0x10);
            e[17] = *(float *)(p + 0x14);
            e[18] = *(float *)(p + 0x18);
            p += 0x20;
        }
    } else {
        p += 0x20;
    }
    g_level_reloc_word = *(int *)p;
    gfx_apply_display_config();
    g_light_far_param = 983040.0f;
    g_light_falloff_param = 500.0f;
    g_light_scale_second = 0x3C0;
    g_light_scale_first = 0x3C0;
    g_light_distance_param = 0x1F4000;
    SetBackgroundColor(g_hud_float_params.i23C, g_hud_float_params.i240, g_hud_float_params.i244);
    gfx_start_dma_channel0_and_wait(g_gfx_dma_chain_buffer);
    mem_fast_helper_b(g_light_table, 0x100);
    mem_fast_helper_b(g_effect_slot_records, 0x180);
    mem_fast_helper_b(g_level_block_buffer, 0x400);

    /* section 4: up to twelve 64-byte records */
    {
        char *s = SECTION_00618(4);
        int n = *(int *)s;

        s += 0x10;
        if (n >= 12) {
            STUB_printf(g_str_startup_message);
            n = 12;
        }
        if (n)
            mem_copy_aligned(g_level_block_buffer, s, n << 6);
    }

    /* section 0x84 */
    if (((int *)hdr)[0x84 / 4]) {
        char *s = SECTION_00618(0x84);
        int n = *(int *)s;

        s += 0x10;
        g_level_entry_count = n;
        if (n) {
            char *entries;

            mem_copy_aligned(g_level_copy_buffer, s, n << 4);
            entries = g_level_entries_buffer;
            mem_copy_aligned(entries, s + (g_level_entry_count << 4), g_level_entry_count << 7);
            if (g_level_entry_count > 0) {
                char *e = entries;
                int left = g_level_entry_count;

                do {
                    if (*(int *)(e + 0x48) < 0)
                        *(int *)(e + 0x48) = 11;
                    if (*(int *)(e + 0x4C) < 0)
                        *(int *)(e + 0x4C) = 11;
                    e += 0x80;
                } while (--left);
            }
        }
    } else {
        g_level_entry_count = 0;
    }
    if (g_tfrag_count > 0) {
        char *e = g_tfrag_render_data + 0x36;
        int left = g_tfrag_count;

        do {
            *(unsigned short *)e = 0xFFFF;
            e += 0x40;
        } while (--left);
    }
    {
        int i = 0;

        while (i < g_tfrag_count) {
            unsigned short *q = (unsigned short *)0x70003000;
            int k = 0;

            while (k < 0x3FF && i < g_tfrag_count) {
                *q++ = i;
                k++;
                i++;
            }
            *q = 0xFFFF;
            func_002F0468((void *)0x70003000);
        }
    }
    g_level_load_context.mark4C = heap;

    /* section 0x10: the help text of the current language (D_001A7BB2[2]) */
    if (((int *)hdr)[0x10 / 4]) {
        int lang = g_option_toggle_b[2] * 4;
        char *s = hdr + *(int *)(hdr + lang + 0x10);
        int size;
        int i;

        g_tutorial_prompt_state.count = *(int *)s;
        s += 4;
        size = *(int *)s;
        s += 4;
        g_level_text_table = (Text00618 *)heap;
        size += 3;
        size &= ~3;
        size -= 8;
        mem_copy_aligned(heap, s, size);
        for (i = 0; i < g_tutorial_prompt_state.count; i++) {
            int delta = (int)g_level_text_table - 8;

            g_level_text_table[i].offset += delta;
        }
        heap = ALIGN64_00618(heap + size);
    }
    g_level_load_context.mark50 = heap;

    /* section 0x34: the ties */
    {
        char *s = SECTION_00618(0x34);
        int n = *(int *)s;
        char *mark;
        int last;
        int i;

        s += 0x10;
        g_tie_count = n;
        if (n >= 0x1000)
            g_tie_count = 0xFFF;
        g_tie_table = (Tie00618 *)heap;
        g_level_value_word = g_level_load_context.i14;
        heap += g_tie_count << 5;
        g_level_zero_word_first = 0;
        g_level_zero_word_second = 0;
        g_level_zero_word_third = 0;
        if (g_tie_count)
            mem_clear(g_tie_table, 0, g_tie_count << 5);
        heap = ALIGN64_00618(heap);
        g_tie_matrix_table = (Matrix00618 *)heap;
        heap += g_tie_count << 6;
        if (g_tie_count)
            mem_clear(g_tie_matrix_table, 0, g_tie_count << 6);
        mark = heap;
        last = -1;
        g_tie_table_end = g_tie_table + g_tie_count;
        for (i = 0; i < g_tie_count; i++) {
            Tie00618 *tie = g_tie_table + i;
            Matrix00618 *m = g_tie_matrix_table + i;
            int draw;
            int occl;
            float scale;

            tie->b1D = g_tie_slot_by_class[*(int *)s];
            if (tie->b1D != last) {
                g_tie_class_table[tie->b1D]->first = tie;
                g_tie_class_table[tie->b1D]->h3E = 0;
                g_tie_class_table[tie->b1D]->table = mark;
                last = tie->b1D;
            }
            g_tie_class_table[tie->b1D]->h3E++;
            mark += ((g_tie_class_table[tie->b1D]->h38 + 3) >> 1) << 2;
            draw = *(int *)(s + 4) >> 4;
            if (draw >= 0x100)
                draw = 0xFF;
            tie->h18 = 0;
            tie->h1A = 0xFFFF;
            tie->h16 = 0;
            tie->h14 = 0xFFFF;
            tie->b1C = draw;
            tie->b1F = 0xFF;
            occl = *(int *)(s + 0xC);
            qcopy(&m->row[0], s + 0x10);
            qcopy(&m->row[1], s + 0x20);
            qcopy(&m->row[2], s + 0x30);
            qcopy(&m->row[3], s + 0x40);
            tie->h10 = occl;
            s += 0x50;
            tie->h12 = i;
            m->row[3].f[3] = g_tie_class_table[tie->b1D]->f40;
            matrix_mul_vec3(tie, &g_tie_class_table[tie->b1D]->sphere, m);
            scale = FastVecLength(&m->row[0]);
            scale = math_max_float(scale, FastVecLength(&m->row[1]));
            tie->bounds.f[3] = g_tie_class_table[tie->b1D]->sphere.f[3] * math_max_float(scale, FastVecLength(&m->row[2]));
            scale_vector(tie, tie, m->row[3].f[3]);
            FastVecAdd(tie, tie, &m->row[3]);
            (g_tie_matrix_table + i)->row[0].f[3] = 1.0f / FastVecLength(&(g_tie_matrix_table + i)->row[0]);
            (g_tie_matrix_table + i)->row[1].f[3] = 1.0f / FastVecLength(&(g_tie_matrix_table + i)->row[1]);
            (g_tie_matrix_table + i)->row[2].f[3] = 1.0f / FastVecLength(&(g_tie_matrix_table + i)->row[2]);
            tie->h18 = *(unsigned short *)s;
            s += 0x10;
        }
        if (g_render_class_slot_count >= 0x80)
            g_render_class_slot_count = 0x7F;
        heap = ALIGN64_00618(mark);
    }

    /* section 0x94: tie groups */
    if (((int *)hdr)[0x94 / 4]) {
        short *s = (short *)SECTION_00618(0x94);
        int idx = *s++;

        while (idx != -1) {
            if (idx < g_tie_count) {
                Tie00618 *tie = g_tie_table + idx;
                TieClass00618 *cls = g_tie_class_table[tie->b1D];

                mem_copy_aligned(cls->table + ((((cls->h38 + 3) >> 1) * (tie - cls->first)) << 2), s + 1, *s << 1);
            }
            s += *s + 1;
            idx = *s++;
        }
    }

    /* section 0x38: a relocated pointer table */
    {
        int *s = (int *)SECTION_00618(0x38);
        int n = *s++;
        int size = *s++;
        int *offs;
        char *base;

        s += 2;
        offs = s;
        g_level_reloc_record.p14 = (int)heap;
        heap += n << 2;
        heap = ALIGN64_00618(heap);
        s += (n + 3) & ~3;
        base = heap;
        heap += size;
        heap = ALIGN64_00618(heap);
        if (n) {
            int i;

            for (i = 0; i < n; i++) {
                if (offs[i] != -1) {
                    g_level_reloc_record.i18 = i + 1;
                    ((int *)g_level_reloc_record.p14)[i] = (int)(base + offs[i]);
                } else {
                    ((int *)g_level_reloc_record.p14)[i] = 0;
                }
            }
        }
        if (size)
            mem_fast_helper_c(base, (char *)(((int)s + 0xF) & ~0xF), size);
    }
    g_level_load_context.mark54 = heap;

    /* section 0x40: the shrubs */
    {
        char *s = SECTION_00618(0x40);
        int n = *(int *)s;
        int last;
        int i;

        g_shrub_table = (Shrub00618 *)heap;
        s += 0x10;
        g_shrub_count = n;
        heap += n << 5;
        if (n)
            mem_clear(g_shrub_table, 0, n << 5);
        heap = ALIGN64_00618(heap);
        g_shrub_matrix_table = (Matrix00618 *)heap;
        heap += g_shrub_count << 6;
        if (g_shrub_count)
            mem_clear(g_shrub_matrix_table, 0, g_shrub_count << 6);
        g_shrub_data_table = (unsigned char *)heap;
        heap += g_shrub_count * 0x60;
        heap = ALIGN64_00618(heap);
        if (g_shrub_count)
            mem_clear(g_shrub_data_table, 0, g_shrub_count * 0x60);
        last = -1;
        g_level_l00_pointer_table[1] = (int)g_shrub_data_table;
        g_shrub_table_end = g_shrub_table + g_shrub_count;
        for (i = 0; i < g_shrub_count; i++) {
            int cls = g_shrub_slot_by_class[*(int *)s];
            Shrub00618 *shrub = g_shrub_table + i;
            Matrix00618 *m = g_shrub_matrix_table + i;
            float radius, a, b, scale;
            int w, h, r, g, bl;

            shrub->b1A = cls;
            if (cls != last) {
                last = cls;
                g_shrub_l00_class_table[cls]->first = shrub;
                g_shrub_l00_class_table[cls]->h16 = 0;
            }
            g_shrub_l00_class_table[cls]->h16++;
            shrub->h18 = i;
            radius = *(float *)(s + 4);
            shrub->f10 = radius;
            if (radius < 16.0f)
                shrub->f10 = 16.0f;
            shrub->b1B = 0;
            shrub->h1E = 0xFFFF;
            if (g_shrub_l00_class_table[cls]->p1C) {
                float t;

                shrub->b17 = FloatToInt(*g_shrub_l00_class_table[cls]->p1C);
                t = IntToFloat(shrub->b17) + 24.0f;
                if (shrub->f10 < t)
                    shrub->f10 = t;
            }
            qcopy(&m->row[0], s + 0x10);
            qcopy(&m->row[1], s + 0x20);
            qcopy(&m->row[2], s + 0x30);
            qcopy(&m->row[3], s + 0x40);
            s += 0x50;
            m->row[3].f[3] = g_shrub_l00_class_table[cls]->f20;
            a = (FastVecLength(&m->row[0]) + FastVecLength(&m->row[1])) * 0.5f;
            b = FastVecLength(&m->row[2]);
            w = FloatToInt(a * 4096.0f);
            h = FloatToInt(b * 4096.0f);
            if (h > 0x10000)
                h = 0x10000;
            if (w > 0x10000)
                w = 0x10000;
            m->row[2].i[3] = w | (h << 16);
            r = *(int *)s;
            s += 4;
            g = *(int *)s;
            s += 4;
            bl = *(int *)s;
            s += 8;
            g = (g << 8) | 0x80000000;
            m->row[0].i[3] = (bl << 16) | g | r;
            shrub->h1C = *(unsigned short *)s;
            s += 0x10;
            matrix_mul_vec3(shrub, g_shrub_l00_class_table[cls], m);
            scale = FastVecLength(&m->row[0]);
            scale = math_max_float(scale, FastVecLength(&m->row[1]));
            shrub->bounds.f[3] = g_shrub_l00_class_table[cls]->fC * math_max_float(scale, FastVecLength(&m->row[2]));
            scale_vector(shrub, shrub, m->row[3].f[3]);
            FastVecAdd(shrub, shrub, &m->row[3]);
        }
    }
    {
        unsigned short *q = (unsigned short *)0x70000000;
        int i;

        for (i = 0; i < g_shrub_count; i++)
            *q++ = i;
        *q = 0xFFFF;
        shrub_process_render_data((void *)0x70000000);
    }
    {
        int i;

        for (i = 0; i < g_shrub_count; i++) {
            unsigned char *q = g_shrub_data_table + i * 0x60;
            int r = 0;
            int g = 0;
            int b = 0;
            int n = 24;
            int j;

            for (j = 0; j < n; j++) {
                r += q[0];
                g += q[1];
                b += q[2];
                q += 4;
            }
            g /= n;
            b /= n;
            r /= n;
            *(int *)((char *)g_shrub_matrix_table + i * 0x40 + 0x1C) = (b << 16) | (g << 8) | r;
        }
    }

    /* section 0x44: another relocated pointer table */
    {
        int *s = (int *)SECTION_00618(0x44);
        int n = *s++;
        int size = *s++;
        int *offs;

        s += 2;
        offs = s;
        g_level_reloc_record.p1C = (int)heap;
        heap += n << 2;
        heap = ALIGN64_00618(heap);
        s += n;
        tmp = (int)heap;
        heap += size;
        heap = ALIGN64_00618(heap);
        if (n) {
            int i;

            for (i = 0; i < n; i++) {
                if (offs[i] != -1) {
                    g_level_reloc_record.i20 = i + 1;
                    ((int *)g_level_reloc_record.p1C)[i] = tmp + offs[i];
                } else {
                    ((int *)g_level_reloc_record.p1C)[i] = 0;
                }
            }
        }
        if (size)
            mem_fast_helper_c((char *)tmp, (char *)(((int)s + 0xF) & ~0xF), size);
    }

    /* section 8: 32-byte records */
    if (((int *)hdr)[8 / 4]) {
        char *s = SECTION_00618(8);
        int n = *(int *)s;

        g_camera_def_table = (Cam00618 *)heap;
        s += 0x10;
        g_camera_def_count = n;
        heap += n << 5;
        if (n)
            mem_clear(g_camera_def_table, 0, n << 5);
        heap = ALIGN64_00618(heap);
        if (g_camera_def_count > 0) {
            Cam00618 *e = g_camera_def_table;
            int left = g_camera_def_count;

        copy_record:
            e->iC = *(int *)s;
            s += 4;
            e->f0 = ((float *)s)[0];
            e->f4 = ((float *)s)[1];
            e->f8 = ((float *)s)[2];
            s += 0xC;
            e->f10 = ((float *)s)[0];
            e->f14 = ((float *)s)[1];
            e->f18 = ((float *)s)[2];
            s += 0xC;
            e->i1C = *(int *)s;
            s += 4;
            e++;
            if (--left)
                goto copy_record;
        }
    }

    /* section 0xC: 0x90-byte records */
    if (((int *)hdr)[0xC / 4]) {
        char *s = SECTION_00618(0xC);
        int n = *(int *)s;

        s += 0x10;
        g_sound_state.count = n;
        if (n) {
            int size = n * 0x90;
            int i;

            g_sound_state.table = (Sound00618 *)heap;
            heap += size;
            heap = ALIGN64_00618(heap);
            mem_clear(g_sound_state.table, 0, size);
            for (i = 0; i < g_sound_state.count; i++) {
                Sound00618 *e = g_sound_state.table + i;

                mem_copy_aligned(e, s, 0x90);
                s += 0x90;
                resolve_lookup_record(e);
            }
        } else {
            g_sound_state.table = 0;
        }
    }

    /* section 0x4C: the mobys */
    g_level_load_context.mark58 = heap;
    {
        char *p = SECTION_00618(0x4C);
        int levels = (int)g_moby_group_flags;
        int n2;
        int count = 0;
        int n;
        char *next;
        int i;

        n = *(int *)p;
        p += 4;
        n2 = *(int *)p;
        p += 0xC;
        g_moby_array_base[0] = (Moby00618 *)heap;
        mem_clear(heap, 0, (n + n2) << 8);
        mem_clear(g_collectible_value_table, 0, 0xC0);
        mem_clear(g_collectible_bonus_table, 0, 0xC0);
        for (i = 0; i < n; i++) {
            int cls;
            int w2;
            int flags;
            int uid;
            int bolts;
            int bolts2;
            int xp;
            int xp2;
            int w9;
            int b1;
            int x1;
            char skip = 0;

            next = p + ((*(int *)p >> 2) << 2);
            p += 4;
            cls = *(int *)p;
            p += 4;
            w2 = *(int *)p;
            p += 4;
            flags = *(int *)p;
            p += 4;
            uid = *(int *)p;
            p += 4;
            bolts = *(int *)p;
            p += 4;
            bolts2 = *(int *)p;
            p += 4;
            xp = *(int *)p;
            p += 4;
            xp2 = *(int *)p;
            p += 4;
            w9 = *(int *)p;
            p += 4;
            b1 = bolts;
            x1 = xp;
            if (cls >= 0 && w9 > 0) {
                int k = cls + g_current_map_index * 16;
                int lvl = (*(unsigned char *)(k + levels) >> (w2 * 2)) & 3;

                if (lvl == 0)
                    lvl = level_get_difficulty_scaled(cls);
                if (*(int *)p == 0x1F5 || *(int *)p == 0x200) {
                    skip = w9 < lvl;
                } else if (lvl < w9) {
                    g_collectible_value_table[cls][w2] += x1;
                    g_collectible_bonus_table[cls][w2] += b1;
                    skip = 1;
                }
            }
            if (!skip && flags) {
                if (g_controller_level_state.byUid[uid]) {
                    skip = 1;
                } else if (flags & 3) {
                    if (g_class_l00_flags_table[cls] & 0x80) {
                        if (flags & 2) {
                            int odd = uid & 1;
                            int c = SAVE_CELL_00618(uid);

                            if (!(odd ? (c >> 4) & 8 : c & 8)) {
                                unsigned char *cell = &SAVE_CELL_00618(uid);
                                int c2 = *cell;
                                int v = odd ? c2 | 0x80 : c2 | 8;
                                int c3;
                                int w;

                                *cell = v;
                                c3 = *cell;
                                w = odd ? c3 & 0x8F : c3 & 0xF8;
                                *cell = w;
                            }
                            b1 = bolts2;
                            x1 = xp2;
                        } else {
                            skip = 1;
                        }
                    } else {
                        skip = !(flags & 1);
                    }
                } else if (flags & 8) {
                    if (reload) {
                        int odd = uid & 1;
                        unsigned char *cell = &SAVE_CELL_00618(uid);
                        int c = *cell;
                        int w = odd ? c & 0x8F : c & 0xF8;

                        *cell = w;
                    } else {
                        int odd = uid & 1;
                        int c = SAVE_CELL_00618(uid);

                        if (odd ? (c >> 4) & 7 : c & 7)
                            skip = 1;
                    }
                } else if ((flags & 0xC) == 4) {
                    int odd = uid & 1;
                    int c = SAVE_CELL_00618(uid);

                    if (odd ? (c >> 4) & 7 : c & 7)
                        skip = 1;
                }
            }
            if (skip) {
                idx[i] = -1;
            } else {
                Moby00618 *m;
                int snap;
                float lift;
                int pv;
                int r;
                int g;
                int b;
                int upd;

                idx[i] = count;
                m = g_moby_array_base[0] + count;
                func_PAL_0029FA60(m, *(int *)p);
                p += 4;
                m->hB2 = uid;
                m->bB0 = cls;
                m->bB1 = w2 & 0xF;
                if (flags == 0)
                    m->bB1 |= 0x80;
                m->hB4 = b1;
                m->hB6 = x1;
                if (m->pClass)
                    m->f2C = ((MobyClass00618 *)m->pClass)->f24 * *(float *)p;
                p += 4;
                m->h32 = *(unsigned short *)p;
                p += 4;
                m->b30 = *(unsigned char *)p;
                p += 0xC;
                m->pos.f[0] = ((float *)p)[0];
                m->pos.f[1] = ((float *)p)[1];
                m->pos.f[2] = ((float *)p)[2];
                p += 0xC;
                m->rot[0] = ((float *)p)[0];
                m->rot[1] = ((float *)p)[1];
                m->rot[2] = ((float *)p)[2];
                p += 0xC;
                m->b21 = *(unsigned char *)p;
                p += 4;
                snap = *(int *)p;
                p += 4;
                lift = *(float *)p;
                p += 4;
                if (snap) {
                    float h = coll_probe_ground_height_below(&m->pos, 0, 0.5f);

                    if (0.0f < h)
                        m->pos.f[2] = h + lift;
                }
                p += 4;
                pv = *(int *)p;
                m->h36 = 0x7F80;
                p += 4;
                m->i68 = pv;
                if (*(int *)p == 0)
                    m->h36 = 0;
                p += 4;
                if (m->pClass)
                    ((MobyClass00618 *)m->pClass)->h44 |= *(unsigned short *)p;
                m->h34 |= *(unsigned short *)p;
                p += 4;
                if (m->pClass)
                    func_002A0F48(m);
                r = *(int *)p;
                p += 4;
                g = *(int *)p;
                p += 4;
                b = *(int *)p;
                p += 4;
                upd = *(int *)p;
                p += 4;
                gfx_pack_render_command_fields(m, (b << 16) + (g << 8) + r, 0, 0, 0);
                m->i38 = upd;
                m->b7E &= 0xFE;
                if (g_current_map_index >= 0 && *(int *)p != -1)
                    level_store_value_in_table_slot(m, *(int *)p);
                count++;
            }
            p = next;
        }
        {
            Moby00618 *tail = g_moby_array_base[0] + count;
            int total = (count + n2) << 8;

            g_moby_list_tail = tail;
            func_PAL_0029FA60(tail, 0);
            heap += total;
            tail->state = 0xFD;
            g_moby_array_end_sentinel = g_moby_list_tail + 1;
            g_moby_array_end_sentinel->state = 0xFF;
            g_level_heap_block_ptr = heap;
            heap += n2 << 7;
            heap = ALIGN64_00618(heap);
            g_level_load_context.mark5C = heap;
            g_moby_array_last = (Moby00618 *)((char *)g_moby_array_base[0] + total - 0x100);
        }
    }

    /* sections 0x60 / 0x5C: pointed-to blobs copied into the heap */
    if (((int *)hdr)[0x60 / 4]) {
        char *pv = SECTION_00618(0x60);
        Blob00618 *tbl = (Blob00618 *)SECTION_00618(0x5C);
        int i;
        Moby00618 *m;

        for (i = 0; i < g_camera_def_count; i++) {
            int k = g_camera_def_table[i].i1C;

            if (k < 0) {
                g_camera_def_table[i].i1C = 0;
            } else {
                int size = tbl[k].size;
                char *src = pv + tbl[k].offset;

                g_camera_def_table[i].i1C = (int)heap;
                mem_fast_helper_c(heap, src, size);
                tbl[k].offset = (int)heap;
                heap += size;
            }
        }
        for (i = 0; i < g_sound_state.count; i++) {
            int k = g_sound_state.table[i].i8;

            if (k < 0) {
                g_sound_state.table[i].i8 = 0;
            } else {
                int size = tbl[k].size;
                char *src = pv + tbl[k].offset;

                g_sound_state.table[i].i8 = (int)heap;
                mem_fast_helper_c(heap, src, size);
                tbl[k].offset = (int)heap;
                heap += size;
            }
        }
        for (m = g_moby_array_base[0]; m != g_moby_array_end_sentinel; m++) {
            if (m->oClass == 0) {
                m->i68 = 0;
            } else {
                int k = m->i68;

                if (k < 0) {
                    m->i68 = 0;
                } else {
                    int size = tbl[k].size;
                    char *src = pv + tbl[k].offset;

                    m->i68 = (int)heap;
                    mem_fast_helper_c(heap, src, size);
                    tbl[k].offset = (int)heap;
                    heap += size;
                }
            }
        }
        heap = ALIGN64_00618(heap);
    }
    g_level_load_context.mark60 = heap;

    /* section 0x58: moby references through the blob directory */
    if (((int *)hdr)[0x58 / 4]) {
        int *q = (int *)SECTION_00618(0x58);
        Blob00618 *tbl = (Blob00618 *)SECTION_00618(0x5C);

        while (q[0] >= 0) {
            int x = tbl[q[0]].offset;
            int off = q[1];

            if (x >= g_level_load_context.i18) {
                int *r = (int *)(x + off);

                if (*r >= 0)
                    *r = idx[*r];
            }
            q += 2;
        }
    }

    /* section 0x64: pointer relocations through the blob directory */
    if (((int *)hdr)[0x64 / 4]) {
        int *q = (int *)SECTION_00618(0x64);
        Blob00618 *tbl = (Blob00618 *)SECTION_00618(0x5C);

        while (q[0] >= 0) {
            int x = tbl[q[0]].offset;
            int off = q[1];

            if (x >= g_level_load_context.i18) {
                int *r = (int *)(x + off);

                *r += x;
            }
            q += 2;
        }
    }

    /* section 0x50: moby groups */
    if (((int *)hdr)[0x50 / 4]) {
        char *q = SECTION_00618(0x50);
        char *base = heap;
        int *offs;
        int n;
        int size;
        int i;

        n = *(int *)q;
        q += 4;
        size = *(int *)q;
        offs = (int *)(q + 0xC);
        heap += size;
        q = (char *)offs + (n << 2);
        heap = ALIGN64_00618(heap);
        if (size)
            mem_fast_helper_c(base, q, size);
        mem_clear(g_turn_state_table, 0, 0x3C0);
        for (i = 0; i < n; i++, offs++) {
            tmp = *offs;
            if (tmp >= 0) {
                int g = (int)(base + tmp);
                unsigned short *src;
                short *dst;

                g_turn_state_table[i] = g;
                src = (unsigned short *)g;
                dst = (short *)src;
                g_moby_l00_group_count = i + 1;
                do {
                    int id = *src;
                    short t;

                    tmp = *(short *)src;
                    g = (id & 0x7FFF) << 1; /* the entry's slot in the moby index, in two steps */
                    g += (int)idx;
                    tmp &= 0x8000;
                    t = *(short *)g;
                    if (t >= 0)
                        *dst++ = t;
                    if (tmp) {
                        if (g_turn_state_table[i] < (int)dst)
                            dst[-1] |= 0x8000;
                        else
                            g_turn_state_table[i] = 0;
                        break;
                    }
                    src++;
                } while (!tmp);
            }
        }
    }

    /* section 0x54: blob pointers into a copied pool */
    if (((int *)hdr)[0x54 / 4]) {
        char *q = SECTION_00618(0x54);
        char *base = heap;
        Blob00618 *tbl;
        int size;
        int n;
        int i;

        size = *(int *)q;
        q += 4;
        n = *(int *)q;
        q += 0xC;
        heap += size;
        heap = ALIGN64_00618(heap);
        if (size)
            mem_fast_helper_c(base, q, size);
        q += size;
        tbl = (Blob00618 *)SECTION_00618(0x5C);
        for (i = 0; i < n; i++) {
            int w = *(int *)q;
            int hi = w >> 16;
            int x = tbl[w & 0xFFFF].offset;

            if (x >= g_level_load_context.i18)
                *(int *)(x + hi) = (int)(base + *(int *)(q + 4));
            q += 8;
        }
    }

    /* section 0x78: paths */
    if (((int *)hdr)[0x78 / 4]) {
        char *q = SECTION_00618(0x78);
        char *src;
        int size;
        int i;

        g_path_count = *(int *)q;
        src = q + *(int *)(q + 4);
        size = *(int *)(q + 8);
        g_path_data = heap;
        heap += size;
        q += 0x10;
        heap = ALIGN64_00618(heap);
        if (size)
            mem_fast_helper_c(g_path_data, src, size);
        for (i = 0; i < g_path_count; i++) {
            g_launch_path_table[i] = g_path_data + *(int *)q;
            q += 4;
        }
    }

    /* section 0x7C: rails */
    if (((int *)hdr)[0x7C / 4]) {
        char *q = SECTION_00618(0x7C);
        char *src;
        char *copy;
        int n;
        int size;
        int i;

        n = *(int *)q;
        g_rail_count = n;
        src = q + *(int *)(q + 4);
        size = *(int *)(q + 8);
        g_rail_table = (Rail00618 *)heap;
        heap += n << 5;
        q += 0x10;
        heap = ALIGN64_00618(heap);
        if (n > 0) {
            Rail00618 *e = g_rail_table;

            i = n;
            do {
                qcopy(e, q);
                q += 0x10;
                e->i14 = *(int *)q;
                q += 0x10;
                e++;
            } while (--i != 0);
        }
        copy = heap;
        heap += size;
        heap = ALIGN64_00618(heap);
        if (size)
            mem_fast_helper_c(copy, src, size);
        for (i = 0; i < g_rail_count; i++) {
            g_rail_table[i].data = copy + *(int *)q;
            q += 4;
        }
    }

    /* section 0x74: clip volumes, 0x90-byte records from 0x80-byte sources */
    if (((int *)hdr)[0x74 / 4]) {
        char *q = SECTION_00618(0x74);
        int n = *(int *)q;
        int i;

        g_collision_pill_table = heap;
        g_collision_pill_count = n;
        q += 0x10;
        heap += n * 0x90;
        heap = ALIGN64_00618(heap);
        if (n)
            mem_clear(g_collision_pill_table, 0, n * 0x90);
        for (i = 0; i < g_collision_pill_count; i++) {
            mem_copy_aligned(g_collision_pill_table + i * 0x90, q, 0x90);
            q += 0x80;
        }
    }

    /* sections 0x68, 0x6C, 0x70: cuboids, spheres and cylinders */
    if (((int *)hdr)[0x68 / 4]) {
        char *q = SECTION_00618(0x68);
        int n = *(int *)q;
        int i;

        g_aranos_launch_poses = heap;
        q += 0x10;
        g_collision_sphere_count = n;
        heap += n << 7;
        heap = ALIGN64_00618(heap);
        if (n)
            mem_clear(g_aranos_launch_poses, 0, n << 7);
        for (i = 0; i < g_collision_sphere_count; i++) {
            mem_copy_aligned(g_aranos_launch_poses + (i << 7), q, 0x80);
            q += 0x80;
        }
    }
    if (((int *)hdr)[0x6C / 4]) {
        char *q = SECTION_00618(0x6C);
        int n = *(int *)q;
        int i;

        g_collision_sphere_table = heap;
        q += 0x10;
        g_collision_cylinder_count = n;
        heap += n << 7;
        heap = ALIGN64_00618(heap);
        if (n)
            mem_clear(g_collision_sphere_table, 0, n << 7);
        for (i = 0; i < g_collision_cylinder_count; i++) {
            mem_copy_aligned(g_collision_sphere_table + (i << 7), q, 0x80);
            q += 0x80;
        }
    }
    if (((int *)hdr)[0x70 / 4]) {
        char *q = SECTION_00618(0x70);
        int n = *(int *)q;
        int i;

        g_collision_cylinder_table = heap;
        q += 0x10;
        g_collision_record_count = n;
        heap += n << 7;
        heap = ALIGN64_00618(heap);
        if (n)
            mem_clear(g_collision_cylinder_table, 0, n << 7);
        for (i = 0; i < g_collision_record_count; i++) {
            mem_copy_aligned(g_collision_cylinder_table + (i << 7), q, 0x80);
            q += 0x80;
        }
    }

    /* section 0x88 */
    if (((int *)hdr)[0x88 / 4]) {
        char *s = SECTION_00618(0x88);
        int size = *(int *)s;

        g_collision_grid_data = heap;
        s += 0x10;
        size += 0x4000;
        heap += size;
        mem_copy_aligned(g_collision_grid_data, s, size);
        heap = ALIGN64_00618(heap);
    }

    /* section 0x80 */
    if (((int *)hdr)[0x80 / 4]) {
        char *s = SECTION_00618(0x80);
        int n = *(int *)s;

        g_level_table_data = heap;
        s += 0x10;
        g_level_table_count = n;
        heap = (char *)(((int)heap + (n << 4) + 0x83F) & 0xFFFFFFC0u);
        if (n)
            mem_copy_aligned(g_level_table_data, s, (n << 4) + 0x800);
        else
            mem_copy_aligned(g_level_table_data, s, 0x800);
    }

    /* section 0x8C */
    if (((int *)hdr)[0x8C / 4]) {
        char *s = SECTION_00618(0x8C);
        int n = *(int *)s;

        g_env_preset_table = heap;
        s += 0x10;
        g_env_preset_count = n;
        heap += n << 5;
        heap = ALIGN64_00618(heap);
        if (n)
            mem_copy_aligned(g_env_preset_table, s, n << 5);
    }
    g_level_data_block_ptr = heap;
    g_level_load_context.mark64 = heap;
    heap += 0x20000;
    g_level_state_word_second = -1;
    g_level_state_word_first = 0;
    g_level_state_word_third = 0;
    mem_fast_helper_b(g_level_clear_area_d, 0x200);

    if (g_current_map_index >= 0) {
        g_hero_moby_default.hero = 0;
        if (0.0f < startPos[0]) {
            Moby00618 *m = CreateMoby(0xD54);

            m->pos.f[0] = startPos[0];
            m->pos.f[1] = startPos[1];
            m->pos.f[2] = startPos[2];
            m->rot[2] = startPos[3];
            m->h32 = 0xFF;
            m->b30 = 0x10;
            m->i64 = (int)pickup_update_interactive;
            m->h34 &= 0xFFFD;
            if (m->b63)
                m->b63 = 8;
            func_002A0F48(m);
            g_hero_moby_default.hero = m;
            level_store_value_in_table_slot(m, 0);
        }
    }
    heap = (char *)(((int)heap + 0xF) & ~0xF);

    /* section 0x98: the group record and its five tables */
    {
        char *s;
        int size;
        int i;

        s = SECTION_00618(0x98);
        g_region_group_table = (Groups00618 *)heap;
        size = *(int *)s;
        heap += size;
        mem_copy_aligned(g_region_group_table, s + 4, size);
        if (g_region_group_table->p4)
            g_region_group_table->p4 += (int)g_region_group_table;
        else
            g_region_group_table->p4 = 0;
        if (g_region_group_table->p8)
            g_region_group_table->p8 += (int)g_region_group_table;
        else
            g_region_group_table->p8 = 0;
        if (g_region_group_table->pC)
            g_region_group_table->pC += (int)g_region_group_table;
        else
            g_region_group_table->pC = 0;
        if (g_region_group_table->p10)
            g_region_group_table->p10 += (int)g_region_group_table;
        else
            g_region_group_table->p10 = 0;
        if (g_region_group_table->p14)
            g_region_group_table->p14 += (int)g_region_group_table;
        else
            g_region_group_table->p14 = 0;
        for (i = 0; i < g_region_group_table->count; i++) {
            GroupEntry00618 *e;

            e = (GroupEntry00618 *)g_region_group_table + i;
            if (e[1].h0)
                e[1].iC += (int)g_region_group_table->p4;
            else
                e[1].iC = 0;
            e = (GroupEntry00618 *)g_region_group_table + i;
            if (e[1].h2)
                e[1].i10 += (int)g_region_group_table->p8;
            else
                e[1].i10 = 0;
            e = (GroupEntry00618 *)g_region_group_table + i;
            if (e[1].h4)
                e[1].i14 += (int)g_region_group_table->pC;
            else
                e[1].i14 = 0;
            e = (GroupEntry00618 *)g_region_group_table + i;
            if (e[1].h6)
                e[1].i18 += (int)g_region_group_table->p10;
            else
                e[1].i18 = 0;
            e = (GroupEntry00618 *)g_region_group_table + i;
            if (e[1].h8)
                e[1].i1C += (int)g_region_group_table->p14;
            else
                e[1].i1C = 0;
        }
        {
            int bytes;

            g_region_members_table = (int)heap;
            bytes = g_region_group_table->count * 0x1C;
            heap += bytes;
            mem_clear((void *)g_region_members_table, 0, bytes);
        }
        {
            int j;

            for (j = 0; j < g_region_group_table->count; j++)
                *(int *)((j << 2) + g_region_members_table) = g_region_members_table + (g_region_group_table->count << 2) + j * 0x18;
        }
    }

    if (g_level_header_extra_ptr && ((int *)hdr)[0x90 / 4]) {
        int *q = (int *)SECTION_00618(0x90);
        int *q0;
        int n1;
        int n2;
        int n3;
        int bad1 = 1;
        int bad2;

        q0 = q;
        n1 = q[0];
        n2 = q[1];
        n3 = q[2];
        q += 4;
        if (g_tutorial_points.count) {
            q += n1 * 2;
            if (g_tutorial_points.i18 == n1)
                bad1 = 0;
            g_tutorial_points.i1C = bad1 == 0;
        } else if (g_tfrag_count == n1) {
            int i;

            bad1 = 0;
            for (i = 0; i < n1; i++) {
                if (((Tfrag00618 *)g_tfrag_render_data)[i].b3D != q[1])
                    bad1 = 1;
                q += 2;
            }
        } else {
            q += n1 * 2;
        }
        bad2 = 1;
        if (g_tie_table_end - g_tie_table == n2) {
            int i;

            bad2 = 0;
            for (i = 0; i < n2; i++) {
                int id = (unsigned short)q[1];

                if (g_tie_table[i].h10 != id)
                    bad2 = 1;
                q += 2;
            }
        } else {
            q += n2 * 2;
        }
        {
            unsigned short *table;
            Moby00618 *m;
            int i;

            table = (unsigned short *)(g_packet_buffer_table[1] + g_packet_buffer_size - 0x10000);
            mem_clear(table, -1, 0x10000);
            for (i = 0; i < n3; i++) {
                if ((unsigned)(q[i * 2 + 1] + 0x4000) < 0x8000)
                    table[q[i * 2 + 1] + 0x4000] = q[i * 2];
            }
            for (m = g_moby_array_base[0]; m->state != 0xFF; m++) {
                if (m->h36 != 0x7F80) {
                    if ((unsigned)(m->hB2 + 0x4000) < 0x8000) {
                        short v = table[m->hB2 + 0x4000];

                        if (v < 0)
                            m->h36 = 0x7F80;
                        else
                            m->h36 = ((v >> 3) << 8) | (1 << (v & 7));
                    } else {
                        m->h36 = 0x7F80;
                    }
                }
            }
        }
        if (bad1) {
            if (g_tfrag_count > 0) {
                unsigned short *e = (unsigned short *)(g_tfrag_render_data + 0x3A);
                int left = g_tfrag_count;

                do {
                    *e = 0x7F80;
                    e = (unsigned short *)((char *)e + 0x40);
                } while (--left);
            }
        } else if (g_tutorial_points.count) {
            int i;

            q = q0 + 4;
            for (i = 0; i < n1; i++) {
                int w = q[0];

                g_tutorial_points.bits[i] = ((w >> 3) << 8) | (1 << (w & 7));
                q += 2;
            }
        } else {
            int i;

            q = q0 + 4;
            for (i = 0; i < n1; i++) {
                int w = q[0];

                ((Tfrag00618 *)g_tfrag_render_data)[i].h3A = ((w >> 3) << 8) | (1 << (w & 7));
                q += 2;
            }
        }
        if (bad2) {
            unsigned short *table;
            Tie00618 *t;
            int i;

            table = (unsigned short *)(g_packet_buffer_table[1] + g_packet_buffer_size - 0x10000);
            q = &q0[n1 * 2 + 4];
            mem_clear(table, 0xFFFEFFFE, 0x8000);
            for (i = 0; i < n2; i++) {
                if ((unsigned)q[i * 2 + 1] < 0x4000)
                    table[q[i * 2 + 1]] = q[i * 2];
            }
            for (t = g_tie_table; t != g_tie_table_end; t++) {
                int id = t->h10;

                if ((unsigned)id < 0x4000) {
                    short v = table[id];

                    if (v < 0)
                        t->h10 = 0x7F80;
                    else
                        t->h10 = ((v >> 3) << 8) | (1 << (v & 7));
                } else {
                    t->h10 = 0x7F80;
                }
            }
        } else {
            int i;

            q = &q0[n1 * 2 + 4];
            for (i = 0; i < n2; i++) {
                int w = q[0];

                g_tie_table[i].h10 = ((w >> 3) << 8) | (1 << (w & 7));
                q += 2;
            }
        }
        g_aranos_launch_state = 2;
    } else {
        Moby00618 *moby;
        Tie00618 *tie;

        for (moby = g_moby_array_base[0]; moby != g_moby_array_last; moby++)
            moby->h36 = 0x7F80;
        for (tie = g_tie_table; tie != g_tie_table_end; tie++)
            tie->h10 = 0x7F80;
        if (g_tfrag_count > 0) {
            unsigned short *e = (unsigned short *)(g_tfrag_render_data + 0x3A);
            int left = g_tfrag_count;

            do {
                *e = 0x7F80;
                e = (unsigned short *)((char *)e + 0x40);
            } while (--left);
        }
        g_aranos_launch_state = 0;
        g_tutorial_points.i1C = 0;
    }
    counter_clear_group();
    InitializeHero_pal();
    hero_reset_start_aim_speed();
    SetupLevelCameras();
    cam_update_state_pal();
    pad_clear_port_state();
    level_init_object_tables();
    func_PAL_L00_00369AF8();
    level_clear_slot_table();
    level_l00_clear_counter_list();
    level_l00_clear_counter_list_2();
    moby_clear_fading_list();
    gfx_enable_draw_flag();
    g_level_counter_a = 0;
    g_moby_index_list_head = 0;
    g_homing_moby_index_list = 0;
    g_decoy_moby_index_list = 0;
    g_dark_sheep_moby_index_list = 0;
    sheep_clear_active_list();
    {
        int i;

        for (i = 0x13; i >= 0; i--)
            g_launch_moby_list[i] = 0;
    }
    g_frame_l00_counter = 0;
    g_nanotech_ball_moby = 0;
    g_render_state_word = 0xE0;
    if (g_hero_moby_default.hero) {
        Moby00618 *m = g_hero_moby_default.hero;
        char *hero = g_hero_state;

        *(long long *)((char *)m + 0x38) = *(long long *)(*(char **)(hero + 0x2290) + 0x38);
    }
    cam_set_transition_frames(7.0f);
    switch (g_current_map_index) {
    case 2:
    case 5:
    case 6:
    case 7:
    case 8:
    case 10:
        g_setup_heap_pointer = g_level_blob_a;
        break;
    default:
        g_setup_heap_pointer = g_level_l00_flag_word;
        break;
    }
    g_level_blob_ptr = g_setup_heap_pointer;
    return heap;
}
