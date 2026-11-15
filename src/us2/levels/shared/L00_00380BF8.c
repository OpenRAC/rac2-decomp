#include "include_asm.h"
#include "names.h"

typedef unsigned char L00_0037F7E8_u8;
typedef unsigned short L00_0037F7E8_u16;
typedef unsigned int L00_0037F7E8_u32;
extern void SetBackgroundColor(int, int, int);
extern int request_begin_slot(int, int, int, int, int);
extern unsigned int ref_L00_0036F480_00(void);
extern void game_reset_frame_counters(void);
extern int UpdateSoundVoices();
extern L00_0037F7E8_u8 *func_002A08A0(void);
extern L00_0037F7E8_u8 *D_L00_001B1EA8 __attribute__((sda));
extern void func_002A05A8(char *);
extern void func_002A0F48(void *);
extern void hero_l00_update_frame_2(void);
extern void cam_update_state(void);
extern void UpdateObjectPreviewSequence(void);
extern void part_update_all(void);
extern void game_update_idle_frame_counters(void);
extern L00_0037F7E8_u32 g_save_menu_flags __attribute__((sda));
typedef struct L00_0037F7E8_Object {
    L00_0037F7E8_u8 pad00[0x20];
    signed char field20;
    L00_0037F7E8_u8 pad21[7];
    struct L00_0037F7E8_Object *next;
    L00_0037F7E8_u8 pad2C[8];
    L00_0037F7E8_u16 field34;
    L00_0037F7E8_u8 pad36[0x2e];
    void (*field64)(struct L00_0037F7E8_Object *);
    L00_0037F7E8_u8 pad68[0x42];
    short fieldAA;
} L00_0037F7E8_Object;
extern int ref_L00_001A8F00_00 __attribute__((sda));
extern L00_0037F7E8_u8 ref_L00_001B267C_00[] __attribute__((sda));

void func_US2_L00_00380C50(void)
{
    L00_0037F7E8_u8 *head;
    L00_0037F7E8_Object *object;
    short id;

    SetBackgroundColor(0, 0, 0);
    if (ref_L00_001A8F00_00 == 0 && (g_save_menu_flags & 1)) {
        if (request_begin_slot(4, 1, 1, 0, 0) == 0)
            return;
    }
    if (ref_L00_0036F480_00() != 0)
        return;
    game_reset_frame_counters();
    UpdateSoundVoices();
    D_L00_001B1EA8 = head = func_002A08A0();
    object = (L00_0037F7E8_Object *)head;
    if (object != 0) {
        while (object != 0) {
            if (object->field20 >= 0) {
                id = object->fieldAA;
                if (id == 0xDC1) {
                    object->field64(object);
                    if ((object->field34 & 4) == 0)
                        func_002A0F48(object);
                } else if (id == 0xCB2 || id == 0xB02 || id == 0x259
                           || id == 0xA5C || id == 0x1192) {
                    func_002A05A8((char *)object);
                    func_002A0F48(object);
                }
            }
            object = object->next;
        }
    }
    if (ref_L00_001B267C_00[0])
        hero_l00_update_frame_2();
    if (ref_L00_001B267C_00[1])
        cam_update_state();
    UpdateObjectPreviewSequence();
    part_update_all();
    game_update_idle_frame_counters();
}

