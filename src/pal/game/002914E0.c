#include "ps2_hw.h"
#include "names.h"
#include "include_asm.h"

/* func_PAL_002914E0, the PAL copy of func_00290C60 (RAC1's InitOnce): the same C, where D_001A7B90 is
   set to 1 and a switch on sceScfGetLanguage's result picks the game language first, as in RAC1. */
extern char g_loader_memory[];
extern char g_ram_end[];
extern char ref_L00_00290B48_00[];
extern int iop_send_block(int source, int destination, int length);
extern void InitMemSlots(void);

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
extern int fast_decompress_pal(void *, void *);
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
extern int func_PAL_00131620(void);
extern int console_get_region(void);
extern void mem_clear(void *, int, int);
extern int func_00126288(void *, int, int, int, int, int, int, int);
extern int sceGsExecLoadImage(void *, void *);
extern int gfx_wait_paths_idle(int, int);
extern void tex_load_pif_from_disc_table_pal(void);
extern void req_reset_queue(void *);

extern char g_str_iop_reboot_image[];   /* path of the IOP reboot image */
extern char g_str_rebooted_iop[];   /* "Rebooted IOP" */
extern char g_str_loaded_irx_modules[];   /* "loaded irx modules" */
extern char g_str_stub_printf[];   /* "Unsupported language" */
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

void func_PAL_002914E0(void)
{
    char buffer[2048];
    char *image;
    char *scratch;
    int *state;
    int handle;
    int mode;
    int lang;

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
    g_is_pal_video = 1;
    save_build_file_names(buffer);
    gfx_start_dma_channel0_and_wait(g_iop_send_dma_block);
    load_default_copy_setup(g_ram_end - 0xFE8C);
    image = (char *)((((unsigned int)ref_L00_00290B48_00 + 0x3FFF) & ~0x3FFF) + 0x2C0000);
    scratch = g_ram_end - 0x8000 - (g_copy_setup_data.count << 11);
    load_start_request(g_copy_setup_data.offset + g_copy_setup_data.base, g_copy_setup_data.count, scratch);
    FlushCache(0);
    fast_decompress_pal(scratch, image);
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
    lang = func_PAL_00131620();
    switch (lang) {
    case 2:
        g_language_settings[4] = 2;
        break;
    case 4:
        g_language_settings[4] = 3;
        break;
    case 3:
        g_language_settings[4] = 4;
        break;
    case 5:
        g_language_settings[4] = 5;
        break;
    default:
        STUB_printf(g_str_stub_printf);
        /* fallthrough */
    case 1:
        g_language_settings[4] = 0;
        break;
    }
    mode = console_get_region();
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
    tex_load_pif_from_disc_table_pal();
    T1_MODE = 0x82;
    T1_COUNT = 0;
    req_reset_queue(g_loader_movie);
}

void gfx_call_sync_helper(void);

void func_PAL_00291A20(void)
{
  cam_init_scene_state();
  return;
}


void func_PAL_00291A40(void)
{
  gfx_restore_draw_position();
  return;
}

