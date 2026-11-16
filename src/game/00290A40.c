#include "ps2_hw.h"
#include "names.h"
#include "include_asm.h"

extern void *memset(void *, int, int);
extern char g_loader_memory[];
extern char g_ram_end[];
extern int g_packet_buffer_size[] __attribute__((sda));
extern char ref_L00_00290B48_00[];
extern char ref_L00_00290B48_01[];

typedef struct {
    unsigned long long words[2];
} __attribute__((aligned(16))) ParserScratch;

extern unsigned char ref_L00_00291640_01[];
extern unsigned short *func_002F4FA0(unsigned short *, unsigned short *, int, ParserScratch *);
extern unsigned short *vec_transform_vectors_vu0(unsigned short *, unsigned short *, int, ParserScratch *);
extern unsigned short *func_002F0B78(unsigned short *, unsigned short *, int, ParserScratch *);


extern int help_is_id_value_in_mapping_range(int a, char *b);

extern int help_store_id_in_slot_list(int a);

/* Qwen draft (branch qwen/autonomy, d969a356), checked by tools/check.py */
void cam_init_scene_state(void);

/* loops 56 times calling a two-argument helper and, unless the current index is zero, a second one-argument helper with that index. */
void gfx_run_filter_over_all_slots(char *query)
{
    int i;

    for (i = 0; i < 56; i++) {
        if (help_is_id_value_in_mapping_range(i, query) == 0)
            continue;
        if (i != 0)
            help_store_id_in_slot_list(i);
    }
}


typedef struct { int source, length, destination, flags; } Request_290AB0;
extern int sceSifSetDma(Request_290AB0 *, int);
extern int sceSifDmaStat(int);
extern int iop_load_module_buffer_no_result(int, int, int);

/* Sends a block of memory to the IOP with a DMA request and waits until it is done. Returns 1 on success, 0 on failure. */
int iop_send_block(int source, int destination, int length)
{
    Request_290AB0 request;
    int handle;
    int result = 1;
    request.source = source;
    request.destination = destination;
    request.length = length;
    request.flags = 0;
    handle = sceSifSetDma(&request, 1);
    if (handle) {
        while (sceSifDmaStat(handle) >= 0) {}
        if (iop_load_module_buffer_no_result(length, 0, 0) < 0)
            result = 0;
    }
    return result;
}

/* Works out where each big memory area starts and stores the addresses in one table. */
void InitMemSlots(void)
{
    int *state = (int *)g_loader_memory;
    unsigned int start, size;

    memset(state, 0, 0x9C);
    state[0] = 0;
    state[1] = 0x100000;
    start = ((unsigned int)ref_L00_00290B48_00 + 0x3FFF) & ~0x3FFF;
    state[2] = start;
    state[3] = start;
    size = g_packet_buffer_size[0];
    state[4] = state[3] + size;
    state[5] = state[4] + size;
    state[6] = state[5] + state[1];
    state[0x84 / 4] = (unsigned int)ref_L00_00290B48_01 - 0x8000;
    state[0x80 / 4] = state[0x84 / 4] - 0x40000;
    state[0x7C / 4] = state[0x80 / 4] - 0x64000;
    state[0x78 / 4] = state[0x7C / 4] - 0x2C000;
    state[0x74 / 4] = state[0x78 / 4] - 0x8000;
    state[0x68 / 4] = state[6];
    state[0x88 / 4] = (unsigned int)g_ram_end - 0x4000;
    state[0x70 / 4] = state[0x74 / 4] - 0x14000;
    state[0x6C / 4] = state[0x70 / 4];
    state[0x8C / 4] = 0x07000000;
    state[0x90 / 4] = 0x07100000;
    state[0x94 / 4] = 0x07180000;
    state[0x98 / 4] = 0x07200000;
}

extern int func_00124418(void);
extern int sceDmaReset(int);
extern void gfx_update_display_mode_from_screen_type(void);
extern void func_0029D050(void);
extern void SetPalMode(int);
extern void EnableCache(int);
extern int func_00126DC0(int (*)(void));
extern int timer_update_vsync_counters(void);
extern void gfx_select_packet_buffer_setup(void);
extern void gfx_reset_packet_buffer(void);
extern void gfx_install_dma_handlers(void);
extern void gfx_write_clear_color_packets(void);
extern int sceCdInit(int);
extern int sce_cd_disk_ready(int);
extern int sceSifRebootIop(char *);
extern int iop_is_reset_done(void);
extern void STUB_printf(char *);
extern void sceSifInitRpc(int);
extern int DIntr(void);
extern void func_0011E7A0(void);
extern void func_0011F628(void);
extern int iop_loadfile_reset_state(void);
extern int sceCdMmode(int);
extern int iop_file_reset_state(void);
extern void load_start_request(int, int, void *);
extern void FlushCache(int);
extern void save_build_file_names(void *);
extern void gfx_start_dma_channel0_and_wait(void *);
/* Takes an address in retail's call, though its body (src/core/001339F0.c) never reads it. */
extern void load_default_copy_setup(void *);
extern int fast_decompress(void *, void *);
extern int iop_remote_cmd_send3(int, int, int);
extern int iop_remote_cmd_send1(int);
extern void iop_init_remote_buffer_server(void);
extern void pad_init_ports(void);
extern void mc_show_message_on_problem(void);
extern void gfx_init_view_context(void);
extern void UpdateViewContext(void);
extern void ResetSoundState(void);
extern void InitFileLoadSystem(void);
extern void load_clear_class_cache_table(void);
extern int func_00131628(void);
extern void mem_clear(void *, int, int);
extern int func_00126288(void *, int, int, int, int, int, int, int);
extern int sceGsExecLoadImage(void *, void *);
extern int gfx_wait_paths_idle(int, int);
extern void tex_load_pif_from_disc_table(void);
extern void req_reset_queue(void *);

extern char g_str_iop_reboot_image[];   /* path of the IOP reboot image */
extern char g_str_rebooted_iop[];   /* "Rebooted IOP" */
extern char g_str_loaded_irx_modules[];   /* "loaded irx modules" */
extern char g_iop_send_dma_block[];
extern char g_gs_transfer_buffer[];
extern char g_loader_movie[];
extern int g_widescreen_flag[] __attribute__((sda));
extern unsigned char g_language_settings[] __attribute__((sda));
extern int g_is_pal_video __attribute__((sda));
extern int g_iop_block_table[] __attribute__((sda));
extern int g_vram_iop_offset __attribute__((sda));
extern int g_vram_image_address __attribute__((sda));
extern int g_hero_moby_default[];

typedef struct {
    char pad000[0x32C];
    int base;
    char pad330[8];
    int offset;
    int count;
} Toc_00290C60;
extern Toc_00290C60 g_copy_setup_data;

/* The boot's one-time setup, RAC1's InitOnce: reboots the IOP, sets up video and the VU, loads
   the compressed module table from the disc and starts the IOP modules in it, sets up the
   memory areas and sound, and clears a small image. */
void InitOnce(void)
{
    char buffer[2048];
    char *image;
    char *scratch;
    int *state;
    int handle;
    int mode;

    func_00124418();
    sceDmaReset(1);
    g_widescreen_flag[0] = 0;
    g_language_settings[1] = 0;
    gfx_update_display_mode_from_screen_type();
    func_0029D050();
    SetPalMode(1);
    EnableCache(3);
    func_00126DC0(timer_update_vsync_counters);
    gfx_select_packet_buffer_setup();
    InitMemSlots();
    gfx_select_packet_buffer_setup();
    gfx_reset_packet_buffer();
    gfx_install_dma_handlers();
    gfx_write_clear_color_packets();
    sceCdInit(0);
    sce_cd_disk_ready(0);
    while (!sceSifRebootIop(g_str_iop_reboot_image)) {
    }
    while (!iop_is_reset_done()) {
    }
    STUB_printf(g_str_rebooted_iop);
    sceSifInitRpc(0);
    DIntr();
    func_0011E7A0();
    func_0011F628();
    iop_loadfile_reset_state();
    sceCdInit(0);
    sce_cd_disk_ready(0);
    sceCdMmode(2);
    iop_file_reset_state();
    load_start_request(1000, 1, buffer);
    FlushCache(0);
    g_is_pal_video = 0;
    save_build_file_names(buffer);
    gfx_start_dma_channel0_and_wait(g_iop_send_dma_block);
    load_default_copy_setup(g_ram_end - 0xFE8C);
    image = (char *)((((unsigned int)ref_L00_00290B48_00 + 0x3FFF) & ~0x3FFF) + 0x2C0000);
    scratch = g_ram_end - 0x8000 - (g_copy_setup_data.count << 11);
    load_start_request(g_copy_setup_data.offset + g_copy_setup_data.base, g_copy_setup_data.count, scratch);
    FlushCache(0);
    fast_decompress(scratch, image);
    FlushCache(0);
    handle = iop_remote_cmd_send3(1, 0x55730, 0);
    iop_send_block(*(int *)(image + 0x50) + (int)image, *(int *)(image + 0x54), handle);
    iop_send_block(*(int *)(image + 0x48) + (int)image, *(int *)(image + 0x4C), handle);
    iop_send_block(*(int *)(image + 0x18) + (int)image, *(int *)(image + 0x1C), handle);
    iop_send_block(*(int *)(image + 0x20) + (int)image, *(int *)(image + 0x24), handle);
    iop_send_block(*(int *)(image + 0x28) + (int)image, *(int *)(image + 0x2C), handle);
    iop_send_block(*(int *)(image + 0x30) + (int)image, *(int *)(image + 0x34), handle);
    iop_send_block(*(int *)(image + 0x38) + (int)image, *(int *)(image + 0x3C), handle);
    iop_send_block(*(int *)(image + 0x40) + (int)image, *(int *)(image + 0x44), handle);
    iop_send_block(*(int *)(image + 0x40) + (int)image, *(int *)(image + 0x44), handle);
    iop_send_block(*(int *)(image + 0x58) + (int)image, *(int *)(image + 0x5C), handle);
    iop_remote_cmd_send1(handle);
    STUB_printf(g_str_loaded_irx_modules);
    iop_init_remote_buffer_server();
    sce_cd_disk_ready(0);
    pad_init_ports();
    state = (int *)g_loader_memory;
    g_iop_block_table[0] = -1;
    g_iop_block_table[12] = -1;
    g_vram_iop_offset = 0;
    g_vram_image_address = 0x60000;
    g_iop_block_table[28] = 0x70000;
    g_iop_block_table[29] = 0xB0000;
    g_iop_block_table[30] = 0x140000;
    g_iop_block_table[31] = 0x1D0000;
    g_iop_block_table[32] = 0x1E0000;
    g_iop_block_table[1] = state[0x78 / 4];
    g_hero_moby_default[12] = -1;
    g_hero_moby_default[6] = -1;
    sce_cd_disk_ready(0);
    mc_show_message_on_problem();
    gfx_init_view_context();
    UpdateViewContext();
    gfx_reset_packet_buffer();
    sce_cd_disk_ready(0);
    ResetSoundState();
    InitFileLoadSystem();
    load_clear_class_cache_table();
    mode = func_00131628();
    switch (mode) {
    case 1:
        g_language_settings[1] = mode;
        break;
    case 0:
    case 2:
        g_language_settings[1] = 0;
        break;
    }
    mem_clear(g_gs_transfer_buffer, 0x80808080, 0x100);
    func_00126288(buffer, 0x3FFB, 1, 0, 0, 0, 8, 8);
    FlushCache(0);
    sceGsExecLoadImage(buffer, g_gs_transfer_buffer);
    gfx_wait_paths_idle(0, 0);
    tex_load_pif_from_disc_table();
    T1_MODE = 0x82;
    T1_COUNT = 0;
    req_reset_queue(g_loader_movie);
}

/* Calls func_00278EB0, which fills the lighting data block. */
void gfx_lighting_init_wrapper(void)
{
  cam_init_scene_state();
  return;
}

extern void gfx_restore_draw_position(void);

/* Calls func_00278F80. */
void gfx_lighting_wrapper(void) {
    gfx_restore_draw_position();
}


/* func_00291158 is matched in its own unit, 00291158.c. */

/* func_00291268 is in 00290A40-g8.c. */


/* Does nothing. */
void gfx_empty_stub(void)
{
}


static __inline__ void qcopy(void *dst, const void *src) {
    __asm__ __volatile__("lq $2,0x0(%1)\n\tsq $2,0x0(%0)"
                         : : "r"(dst), "r"(src) : "$2", "memory");
}

typedef struct {
    float color[3];
    float radius;
    float position[3];
    float range;
} LightDef;

typedef struct {
    char pad0[0xC];
    char *buffer;
    int active;
    char pad14[0x30 - 0x14];
} LightSlot;

extern float IntToFloat(int);
extern char g_light_buffers[];
extern char g_dynamic_lights[];
extern char g_dynamic_light_states[];
extern void mem_fast_helper_b(void *, int);

/* Adds a point light with the given position, range, radius and color. Returns its slot number, or -1 if all 8 slots are used. */
int gfx_add_point_light(float *position, float range, float radius, int color)
{
    LightDef *def;
    LightSlot *slot;
    int i;

    for (i = 0; i < 8; i++) {
        if (((LightSlot *)g_dynamic_light_states)[i].active == 0) {
            break;
        }
    }
    if (i == 8) {
        return -1;
    }
    def = (LightDef *)(g_dynamic_lights + (i << 5));
    slot = (LightSlot *)(g_dynamic_light_states + i * 0x30);
    qcopy(def->position, position);
    def->range = range;
    def->color[0] = IntToFloat(color & 0xFF) * 0.0078125f;
    def->color[1] = IntToFloat((color >> 8) & 0xFF) * 0.0078125f;
    def->color[2] = IntToFloat((color >> 16) & 0xFF) * 0.0078125f;
    def->radius = radius;
    mem_fast_helper_b(slot, 0x30);
    slot->active = 1;
    slot->buffer = g_light_buffers + (i << 10);
    return i;
}


extern void gfx_flush_light_part_indices(int index);
extern void mem_fast_helper_b(void *, int);
extern char g_dynamic_lights[];
extern char g_dynamic_light_states[];

/* Frees a point light slot and clears its data. */
void gfx_free_point_light(int index) {
    if ((unsigned int)index >= 8)
        return;
    gfx_flush_light_part_indices(index);
    mem_fast_helper_b((void *)(g_dynamic_lights + (index << 5)), 0x20);
    mem_fast_helper_b((void *)(g_dynamic_light_states + index * 0x30), 0x30);
}

/* func_002914B8 is in 00290A40-g16.c. */

/* Splits the light's data into its three sections and records where each one starts and how long it is. */
void CreatePointLight(int index)
{
    unsigned char *record = ref_L00_00291640_01 + index * 0x30;
    unsigned short *position = *(unsigned short **)(record + 0xC);
    unsigned short *end = position + 0x200;
    LightDef *def = &((LightDef *)g_dynamic_lights)[index];
    ParserScratch *scratch = (ParserScratch *)def->position;
    ParserScratch scratchCopy;
    qcopy(&scratchCopy, scratch);

    if (position < end) {
        *(short *)record = 0;
        position = func_002F4FA0(position, end, index, scratch);
        *(short *)(record + 2) = (position - *(unsigned short **)(record + 0xC));
        if (position < end) {
            *(short *)(record + 4) = (position - *(unsigned short **)(record + 0xC));
            position = vec_transform_vectors_vu0(position, end, index, scratch);
            *(short *)(record + 6) = (position - *(unsigned short **)(record + 0xC)) - *(unsigned short *)(record + 4);
            if (position < end) {
                *(short *)(record + 8) = (position - *(unsigned short **)(record + 0xC));
                position = func_002F0B78(position, end, index, scratch);
                *(short *)(record + 0xA) = (position - *(unsigned short **)(record + 0xC)) - *(unsigned short *)(record + 8);
            }
        }
    }
}
