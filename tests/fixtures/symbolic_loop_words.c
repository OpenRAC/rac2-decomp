#include "common.h"

typedef struct {
    unsigned short first, second;
    unsigned char reserved[11], mark;
} SymbolicRow;

extern SymbolicRow *rows;
extern SymbolicRow *late_limit;
extern SymbolicRow *early_limit __attribute__((sda));
extern SymbolicRow *explicit_limit[] SDATA(explicit_limit);

#define CLEAR_TO(limit) do { \
    SymbolicRow *p = rows; \
    if (p != (limit)) { \
        do { p->second = 0xffff; p->first = 0xffff; p->mark = 0xff; p++; } \
        while (p != (limit)); \
    } \
} while (0)

void unknown_limit_loop(void) { CLEAR_TO(late_limit); }
void known_gp_limit_loop(void) { CLEAR_TO(early_limit); }
void explicit_gp_limit_loop(void) { CLEAR_TO(explicit_limit[0]); }

/* The two C spellings below denote the same assembler object. */
extern SymbolicRow *raw_alias __asm__("early_limit");
void alias_of_known_limit_loop(void) { CLEAR_TO(raw_alias); }

extern SymbolicRow *announced_alias __asm__("plain_limit") __attribute__((sda));
SymbolicRow *announce_raw_alias(void) { return announced_alias; }
extern SymbolicRow *plain_limit;
void ordinary_spelling_loop(void) { CLEAR_TO(plain_limit); }

struct SymbolicRequest { int header[2], payload[8]; };
extern struct SymbolicRequest request __attribute__((sda));
extern int poll_request(void *);
void unknown_address_loop(void) {
    while (poll_request(request.payload)) {}
}

/* At -G0, this first reference is unknown to the assembler; the second
   follows a real small-data definition, despite the earlier extern. */
extern SymbolicRow *defined_later __attribute__((sda));
void before_definition_loop(void) { CLEAR_TO(defined_later); }
SymbolicRow *defined_later __attribute__((section(".sdata"))) = 0;
void after_definition_loop(void) { CLEAR_TO(defined_later); }
