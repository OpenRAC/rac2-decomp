#include "names.h"
/* Restores a memory card save packet into the registered blocks (rac1's
   memcard_restore_data): after the CRC check, copies each saved block into the matching
   entry's slot, marking it exact (1), short (-1) or long (-2); counts changed blocks,
   missing ids, a size mismatch and unrestored entries, and stores the error count in
   the current card slot. Block id 6000 is compared but not copied. */
typedef struct {
    unsigned char *data;
    int size;
    int id;
    int status;
} RestoreEntry29B168;

typedef struct {
    int id;
    int size;
    unsigned char data[1];
} RestoreBlock29B168;

typedef struct {
    unsigned char pad0[0x24];
    int errors;
    unsigned char pad28[0x78];
} CardSlot29B168;

typedef struct {
    CardSlot29B168 slot[2];
    unsigned char pad140[0xC];
    int cur;
} CardState29B168;

extern CardState29B168 g_memcard_state;
extern int g_restore_counter __attribute__((sda));
extern int save_verify_block_checksum(char *);
extern int memcard_GetDataSize(int *);
extern int memcmp(void *, void *, int);
extern void mem_copy_aligned(void *, void *, int);

int MemcardRestoreData(unsigned char *save_packet, int slot, RestoreEntry29B168 *restore_entries)
{
    RestoreEntry29B168 *matched_entry;
    int errors;
    int total;
    int i;
    int copySize;
    unsigned char *slot_destination;

    if (save_verify_block_checksum((char *)save_packet) == 0) {
        return 1;
    }
    save_packet += 8;
    errors = 0;
    total = 8;
    for (i = 0; restore_entries[i].data != 0; i++) {
        restore_entries[i].status = 0;
    }
    while (((RestoreBlock29B168 *)save_packet)->id != -1) {
        i = 0;
        if (restore_entries[0].data == 0) {
            goto missing;
        }
        while (restore_entries[i].id != ((RestoreBlock29B168 *)save_packet)->id) {
            i++;
            if (restore_entries[i].data == 0) {
                goto missing;
            }
        }
        if (((RestoreEntry29B168 *)(((unsigned int)i << 4) + (unsigned int)restore_entries))->data != 0) {
            int blockSize;
            int entrySize;
            matched_entry = (RestoreEntry29B168 *)(((unsigned int)i << 4) + (unsigned int)restore_entries);
            entrySize = matched_entry->size;
            blockSize = ((RestoreBlock29B168 *)save_packet)->size;
            slot_destination = matched_entry->data + slot * entrySize;
            if (blockSize == entrySize) {
                copySize = entrySize;
                matched_entry->status = 1;
            } else if (blockSize < entrySize) {
                copySize = blockSize;
                matched_entry->status = -1;
            } else {
                copySize = entrySize;
                matched_entry->status = -2;
            }
            if (memcmp(slot_destination, ((RestoreBlock29B168 *)save_packet)->data, copySize) != 0) {
                g_restore_counter++;
            }
            if (((RestoreEntry29B168 *)(((unsigned int)i << 4) + (unsigned int)restore_entries))->id != 6000) {
                mem_copy_aligned(slot_destination, ((RestoreBlock29B168 *)save_packet)->data, copySize);
                total += ((copySize + 3) & ~3) + 8;
            } else {
                total += ((((RestoreBlock29B168 *)save_packet)->size + 3) & ~3) + 8;
            }
        } else {
        missing:
            errors++;
        }
        save_packet += ((((RestoreBlock29B168 *)save_packet)->size + 3) & ~3) + 8;
    }
    total += 8;
    if (total != memcard_GetDataSize((int *)restore_entries)) {
        errors++;
    }
    save_packet += 8;
    for (i = 0; restore_entries[i].data != 0 && restore_entries[i].id != ((RestoreBlock29B168 *)save_packet)->id; i++) {
        if (restore_entries[i].status <= 0) {
            errors++;
        }
    }
    g_memcard_state.slot[g_memcard_state.cur].errors = errors;
    return errors;
}
