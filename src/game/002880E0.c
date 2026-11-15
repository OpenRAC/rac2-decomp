#include "include_asm.h"
#include "names.h"

typedef struct { int id; int value; } MappingEntry;

typedef struct { int v[12]; } Blob;

typedef struct {
    unsigned int marker;
    unsigned char reserved04[0x38];
    unsigned short class_code;
    unsigned char reserved3E[0xa2];
} MappedClassEntry;

typedef int s32;

typedef unsigned char u8;

typedef unsigned int u32;

extern MappingEntry D_002403C0[];

extern Blob D_L00_001A8E60;

extern unsigned char g_item_slot_to_record[];

extern MappedClassEntry g_weapon_l00_table[];

extern s32 memset(u8 *, s32, s32);

extern void req_reset_queue(unsigned char *);

typedef struct {
    int word00;
    unsigned char byte04;
    unsigned char pad05[7];
    int word0C;
    unsigned char pad10[0x3A];
    short child;
    short parent;
    unsigned char pad4E[0x32];
    int word80;
    unsigned char pad84[4];
    unsigned short half88;
    unsigned char pad8A[8];
    unsigned short half92;
    unsigned char pad94[0x4C];
} __attribute__((aligned(16))) ClassRecord;

/* a pending table row: five halfwords, the value compared at +6 */
typedef struct {
    short id;
    short pad0;
    short pad1;
    short value;
    short pad2;
} PendingEntry;

extern ClassRecord g_weapon_table[];

extern int g_weapon_menu_slots[] __attribute__((section(".sdata")));

extern PendingEntry D_0025E328[];

extern int help_is_id_in_either_table(int);

/* Find a mapped record by its unsigned halfword class and return its opaque word. */

/* func_002889B8 : clears three fields, initializes a block, then sets two flags */

/* 48-byte `ldl/ldr` → `sdl/sdr` stack copy of an absolute global, then a */
/* Checks whether a help id is in a fixed list of ids. Returns 1 if found, otherwise 0. */
int help_is_id_in_fixed_list(int helpId)
{
    Blob table;
    int i;
    table = D_L00_001A8E60;
    for (i = 0; table.v[i]; i++)
        if (helpId == table.v[i])
            return 1;
    return 0;
}


/* Adds a help id to the small list of waiting help ids, unless it is already handled or blocked. */
void help_queue_pending_id(int helpId)
{
    ClassRecord *record;
    short *idPtr;
    int i;

    if (help_is_id_in_either_table(helpId) == 0)
        return;
    if (D_0025E328[0].value != -1) {
        idPtr = &D_0025E328[0].value;
        do {
            if (helpId == *idPtr)
                return;
            idPtr += 5;
        } while (*idPtr != -1);
    }
    record = &g_weapon_table[g_item_slot_to_record[helpId]];
    if (record->word0C != 0)
        return;
    if (help_is_id_in_fixed_list(helpId) != 0)
        return;
    for (i = 0; i < 8; i++) {
        if (g_weapon_menu_slots[i] == 0 || g_weapon_menu_slots[i] == helpId)
            break;
    }
    if (i < 8)
        g_weapon_menu_slots[i] = helpId;
}




/* search56 byte-mapped E0 records by U16class3C, return opaque32 marker0 elsezero */
/* Looks through the 56 help records for one with the given class code and returns its first word, or 0. */
unsigned int help_find_record_marker_by_class(unsigned int key)
{
    int i;
    for (i = 0; i < 56; i++) {
        MappedClassEntry *record = &g_weapon_l00_table[g_item_slot_to_record[i]];
        if (record->class_code == key)
            return record->marker;
    }
    return 0;
}

/* the six action tables of the selector and its flag */
typedef struct {
    void *slot[6];
    int flag;
} SlotTable;

extern SlotTable ref_L00_00288508_00;

extern unsigned short D_0018C964;

extern int subtitle_request_voice_line(int, int);

extern void value_set_entry_by_index(int, int);

/* Pick the action of the mapped class of PARAM, then hand it to the game. */
void help_show_message_for_id(int helpId)
{
    SlotTable table;
    int messageId;
    int i;

    if (helpId == 10) {
        subtitle_request_voice_line(0x9F8, 0x4F);
    } else if (helpId == 27) {
        subtitle_request_voice_line(0x9F7, 0x4E);
    } else if (D_0018C964 == 0) {
        subtitle_request_voice_line(0x9AA, 1);
    }

    messageId = -1;
    table = ref_L00_00288508_00;
    {
        MappedClassEntry *entry = &g_weapon_l00_table[g_item_slot_to_record[helpId]];
        int *actionList = 0;
        if (entry->reserved04[0] < 6) {
            actionList = (int *)table.slot[((u8 *)entry)[4]];
        }
        if (actionList) {
            for (i = 0; actionList[i] != -1; i += 2) {
                if (actionList[i] == helpId) { messageId = actionList[i + 1]; break; }
            }
        }
    }
    if (helpId == 10) {
        u8 *levelEntry = (u8 *)&g_weapon_l00_table[g_item_slot_to_record[10]];
        int level = levelEntry[4];
        if (level >= 2) messageId = 0x1296;
        if (level >= 3) messageId = 0x1297;
        if (level >= 4) messageId = 0x1296;
        if (level >= 5) messageId = 0x1297;
    }
    if (messageId >= 0)
        value_set_entry_by_index(messageId, -1);
    else
        value_set_entry_by_index(0, -1);
}

extern int flag_is_byte_set(void);

/* True when the id is in the mapping table and its value is at or past the
   table's bound while still inside the small id range. */
int help_is_id_value_in_mapping_range(int id, int value)
{
    int i;

    if (id == 9 && flag_is_byte_set() != 0)
        return 1;
    for (i = 0; D_002403C0[i].id != -2; i++) {
        if (id == D_002403C0[i].id && value >= D_002403C0[i].value && value < 0x15)
            return 1;
    }
    return 0;
}

/* Returns 1 when the id is in the mapping table. */
int help_is_id_in_mapping_table(int id) {
    int i;
    for (i = 0; D_002403C0[i].id != -2; i++)
        if (id == D_002403C0[i].id) return 1;
    return 0;
}


/* Walks to the root of the chain index is in, then depth links down it, and
   copies that entry to dst when its kind byte equals depth.  Returns 1 when
   copied. */
int help_copy_record_at_depth(ClassRecord *dst, int index, int depth)
{
    int ret = 0;
    int i;
    int n;

    if (depth < 0xFF) {
        i = index;
        while (g_weapon_table[i].parent != 0)
            i = g_weapon_table[i].parent;
        for (n = 0; n < depth && g_weapon_table[i].child != 0; n++)
            i = g_weapon_table[i].child;
        if (g_weapon_table[i].byte04 == depth) {
            ret = 1;
            *dst = g_weapon_table[i];
        }
    }
    return ret;
}



/* Resets a request queue: empties it and fills its slots with the "none" value. */
void req_reset_queue(u8 *queue) {
    *(s32 *)(queue + 0x30) = 0;
    *(s32 *)(queue + 0x34) = 0;
    *(s32 *)(queue + 0x38) = 0;
    memset(queue + 8, 0xcd, 0x28);
    *(s32 *)(queue + 0x44) = 0;
    *(s32 *)(queue + 0x40) = 1;
}

/* Takes the oldest request out of the queue and gives back its value and flag. Returns 0 if the queue is empty. */
s32 req_pop_queue(u8 *queue,s32 *outValue,s32 *outFlag) {
 s32 *values,*flags; s32 idx;
 if(*(s32 *)(queue+0x38)==0) return 0;
 if(--*(s32 *)(queue+0x38)==0) *(s32 *)(queue+0x44)=0;
 values=(s32 *)(queue+8); flags=(s32 *)(queue+12);
 *outValue=*(s32 *)((u32)values+(*(s32 *)(queue+0x34)<<3));
 *outFlag=*(s32 *)((u32)flags+(*(s32 *)(queue+0x34)<<3));
 values=(s32 *)((u32)values+(*(s32 *)(queue+0x34)<<3)); *values=-1;
 flags=(s32 *)((u32)flags+(*(s32 *)(queue+0x34)<<3)); *flags=-1;
 idx=*(s32 *)(queue+0x34)+1;
 if(idx==5) idx=0;
 *(s32 *)(queue+0x34)=idx;
 return 1;
}

/* Adds a request to the end of the queue. Returns 0 if the queue is full or locked. */
s32 req_push_queue(u8 *queue,s32 value) {
 s32 next;
 if(*(s32 *)(queue+0x38)==5 || *(s32 *)(queue+0x44)!=0) return 0;
 *(s32 *)((u32)queue+(*(s32 *)(queue+0x30)<<3)+8)=value;
 *(u32 *)((u32)queue+(*(s32 *)(queue+0x30)<<3)+12)=(u32)(value-0x20U)<0x91;
 next=*(s32 *)(queue+0x30)+1;
 if(next==5) next=0;
 *(s32 *)(queue+0x38)=*(s32 *)(queue+0x38)+1;
 *(s32 *)(queue+0x30)=next;
 return 1;
}
