#include "include_asm.h"
#include "names.h"

extern float func_002A7878_1(float low, float high);
typedef unsigned char L00_0037F7E8_u8;
extern L00_0037F7E8_u8 *func_002A08A0(void);
extern L00_0037F7E8_u8 *g_moby_l00_list_head __attribute__((sda));
extern L00_0037F7E8_u8 ref_L00_001B267C_00[] __attribute__((sda));
extern unsigned char g_hero_override_flag __attribute__((sda));
typedef struct L00_0038BD00_Kind {
    unsigned char pad00[0x46];
    short type;
} L00_0038BD00_Kind;
typedef struct L00_0038BD00_Node {
    unsigned char pad00[0x20];
    unsigned char mode;
    unsigned char pad21[3];
    L00_0038BD00_Kind *kind;
    struct L00_0038BD00_Node *next;
} L00_0038BD00_Node;
typedef struct {
    unsigned char pad[0x2290];
    int value;
} D_00189E20_Struct;
extern D_00189E20_Struct g_hero_state;
extern float fast_vec_dist(char *object, char *other);
extern int pickup_start_fly_to_target(char *object, int value, float first, float second);
extern int moby_is_ammo(char *object);
extern int pickup_check_stock_increase(char *value);

/* Walk the level's node list from D_L00_001B1EA8: each node's own measure is
 * compared with the limit (2.7, or 10.0 when D_001A7B2A is set); a node of kind
 * 0x13 is then handed to func_003022A0, any other node to its own handler. A mode
 * of 0xFE or 0xFD, or a null next pointer, ends the walk. */
void moby_trigger_nearby_response_us2(char *object)
{
    L00_0038BD00_Node *node;
    float limit;
    float step;
    float value;
    int mode;
    int result;
    L00_0038BD00_Kind *kind;

    limit = 2.7f;
    if (g_hero_override_flag != 0)
        limit = 10.0f;
    node = (L00_0038BD00_Node *)g_moby_l00_list_head;
    if (node == 0)
        return;
    step = 0.01745329424738884f;
    while (1) {
        mode = node->mode;
        if (mode == 0xFE)
            return;
        if (mode == 0xFD)
            return;
        if (node != 0 && (kind = node->kind) != 0 && kind->type == 0x13) {
            value = fast_vec_dist((char *)node + 0x10, object + 0x10);
            if (value < limit) {
                value = func_002A7878_1(-30.0f, 30.0f);
                result = pickup_start_fly_to_target((char *)node, g_hero_state.value, value * step, 0.0f);
            } else {
                node = node->next;
                goto next;
            }
        } else {
            if (moby_is_ammo((char *)node) == 0) {
                node = node->next;
                goto next;
            }
            value = fast_vec_dist((char *)node + 0x10, object + 0x10);
            if (value < limit) {
                result = pickup_check_stock_increase((char *)node);
            } else {
                node = node->next;
                goto next;
            }
        }
        if (result != 0)
            return;
        node = node->next;
next:
        /* The walk's end test: the goto above reaches it with the next pointer
         * already loaded, which is the shape retail's code has. */
        if (node == 0)
            return;
    }
}

