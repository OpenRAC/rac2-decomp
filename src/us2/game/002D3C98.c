#include "include_asm.h"
#include "names.h"

extern unsigned int g_menu_input_flags;
extern unsigned int g_frame_counter __attribute__((sda));
extern int g_current_map_index __attribute__((sda));
extern char g_pause_menu_state[];
typedef struct {
    char pad[0x1d4];
    unsigned short count;
    unsigned short unused;
    unsigned int maximum;
    unsigned int levels;
} Statistics_2D2CE8;
extern Statistics_2D2CE8 g_progress_statistics;
extern int func_0029C6F0(int);

/* Handles button input for a menu page: counts the visit in the statistics and either accepts, cancels or passes the button to the page. (USA v2.00) */
int menu_page_update_count_stats_us2(void)
{
    int result = 0;
    unsigned int flags = g_menu_input_flags;
    if (flags & 0x10) {
        Statistics_2D2CE8 *stats = &g_progress_statistics;
        char *root;
        int value, status;
        if (stats->count < 0xffff) stats->count++;
        if (g_frame_counter > stats->maximum) stats->maximum = g_frame_counter;
        stats->levels = (stats->levels | (1u << g_current_map_index)) | 0x80000000u;
        root = g_pause_menu_state;
        value = *(int *)(*(char **)(root + 0x14) + 0xe0);
        if (value != 0) *(int *)(root + 0x18) = value;
        else {
            switch (*(int *)(root + 0x134)) {
            case 0: status = -1; goto finish;
            default: break;
            }
        }
        status = 0;
finish:
        return status;
    }
    if (flags & 0x900) {
        Statistics_2D2CE8 *stats = &g_progress_statistics;
        if (stats->count < 0xffff) stats->count++;
        if (g_frame_counter > stats->maximum) stats->maximum = g_frame_counter;
        stats->levels = (stats->levels | (1u << g_current_map_index)) | 0x80000000u;
        result = 1;
    } else func_0029C6F0(flags);
    return result;
}

extern void SetupGifPaging(long);
extern void DoGifPaging(void);
void SetupGifPaging(long);
void DoGifPaging(void);
void func_0029C730(void);
extern void SetupGifPaging(long arg0);
extern void SetupGifPaging(long param_1);

/* Draws one menu page by calling its page-specific draw routine between the common start and end of menu drawing. (USA v2.00) */
unsigned long long menu_page_draw_2_us2(void)
{
    SetupGifPaging(0);
    func_0029C730();
    DoGifPaging();
    return 0;
}

extern void func_0029C7A0(void);

/* Draws one menu page by calling its page-specific draw routine between the common start and end of menu drawing. (USA v2.00) */
unsigned long long menu_page_draw_3_us2(void)
{
    SetupGifPaging(0);
    func_0029C7A0();
    DoGifPaging();
    return 0;
}

extern void func_0029C810(void);

/* Draws one menu page by calling its page-specific draw routine between the common start and end of menu drawing. (USA v2.00) */
int menu_page_draw_4_us2(void) {
    SetupGifPaging(0);
    func_0029C810();
    DoGifPaging();
    return 0;
}

