#include "common.h"

/* Newlib multibyte conversion; reconstructed against the retail library. */

typedef struct {
    u8 pad000[0x34];
    const char *_current_locale; /* 0x34 */
} MbtowcReent;

typedef enum {
    ESCAPE,
    DOLLAR,
    BRACKET,
    AT,
    B,
    J,
    NULCH,
    JIS_CHAR,
    OTHER,
    JIS_C_NUM
} JIS_CHAR_TYPE;

typedef enum {
    ASCII,
    A_ESC,
    A_ESC_DL,
    JIS,
    JIS_1,
    JIS_2,
    J_ESC,
    J_ESC_BR,
    J2_ESC,
    J2_ESC_BR,
    DONE,
    INV,
    JIS_S_NUM
} JIS_STATE;

typedef enum { COPY_A, COPY_J, COPY_J2, MAKE_A, MAKE_J, NOOP, EMPTY, ERROR } JIS_ACTION;

#define ESC_CHAR 0x1b

#define _issjis1(c) ((c) >= 0x81 && (c) <= 0x9f || (c) >= 0xe0 && (c) <= 0xef)
#define _issjis2(c) ((c) >= 0x40 && (c) <= 0x7e || (c) >= 0x80 && (c) <= 0xfc)
#define _iseucjp(c) ((c) >= 0xa1 && (c) <= 0xfe)
#define _isjis(c) ((c) >= 0x21 && (c) <= 0x7e)

extern JIS_STATE g_jis_state_table[JIS_S_NUM][JIS_C_NUM];
extern JIS_ACTION g_jis_action_table[JIS_S_NUM][JIS_C_NUM];
extern const char g_str_locale_name_c[];
extern const char g_str_locale_name_posix[];
extern const char g_str_locale_name_empty[];

extern unsigned int strlen(const char *);

extern int strcmp(const char *, const char *);

/* Reads one multibyte character (such as Shift-JIS or EUC-JP) and gives its code. */
int MultibyteToWideCharReentrant(MbtowcReent *r, int *pwc, const char *s, unsigned int n, int *state) {
    int dummy;
    unsigned char *t = (unsigned char *)s;

    if (pwc == 0)
        pwc = &dummy;

    if (s != 0 && n == 0)
        return -1;

    if (r->_current_locale == 0 || (strlen(r->_current_locale) <= 1)) {
        /* fall-through */
    } else if (!strcmp(r->_current_locale, g_str_locale_name_c)) {
        int char1 = *t;
        if (s == 0)
            return 0; /* not state-dependent */
        if (_issjis1(char1)) {
            int char2 = t[1];
            if (n <= 1)
                return -1;
            if (_issjis2(char2)) {
                *pwc = (((int)*t) << 8) + (int)(*(t + 1));
                return 2;
            } else
                return -1;
        }
    } else if (!strcmp(r->_current_locale, g_str_locale_name_posix)) {
        int char1 = *t;
        if (s == 0)
            return 0; /* not state-dependent */
        if (_iseucjp(char1)) {
            int char2 = t[1];
            if (n <= 1)
                return -1;
            if (_iseucjp(char2)) {
                *pwc = (((int)*t) << 8) + (int)(*(t + 1));
                return 2;
            } else
                return -1;
        }
    } else if (!strcmp(r->_current_locale, g_str_locale_name_empty)) {
        JIS_STATE curr_state;
        JIS_ACTION action;
        JIS_CHAR_TYPE ch;
        unsigned char *ptr;
        int i, curr_ch;

        if (s == 0) {
            *state = 0;
            return 1; /* state-dependent */
        }

        curr_state = (*state == 0 ? ASCII : JIS);
        ptr = t;

        for (i = 0; i < n; ++i) {
            curr_ch = t[i];
            switch (curr_ch) {
            case ESC_CHAR:
                ch = ESCAPE;
                break;
            case '$':
                ch = DOLLAR;
                break;
            case '@':
                ch = AT;
                break;
            case '(':
                ch = BRACKET;
                break;
            case 'B':
                ch = B;
                break;
            case 'J':
                ch = J;
                break;
            case '\0':
                ch = NULCH;
                break;
            default:
                if (_isjis(curr_ch))
                    ch = JIS_CHAR;
                else
                    ch = OTHER;
            }

            action = g_jis_action_table[curr_state][ch];
            curr_state = g_jis_state_table[curr_state][ch];

            switch (action) {
            case NOOP:
                break;
            case EMPTY:
                *state = 0;
                *pwc = 0;
                return i;
            case COPY_A:
                *state = 0;
                *pwc = (int)*ptr;
                return (i + 1);
            case COPY_J:
                *state = 0;
                *pwc = (((int)*ptr) << 8) + (int)(*(ptr + 1));
                return (i + 1);
            case COPY_J2:
                *state = 1;
                *pwc = (((int)*ptr) << 8) + (int)(*(ptr + 1));
                return (ptr - t) + 2;
            case MAKE_A:
            case MAKE_J:
                ptr = (unsigned char *)(t + i + 1);
                break;
            case ERROR:
            default:
                return -1;
            }
        }

        return -1; /* n < bytes needed */
    }

    /* otherwise this must be the "C" locale or unknown locale */
    if (s == 0)
        return 0; /* not state-dependent */

    *pwc = (int)*t;

    if (*t == '\0')
        return 0;

    return 1;
}
