typedef float f32;
typedef unsigned char u8;
typedef int s32;
typedef unsigned int u32;
typedef struct { u32 items[5]; } NativeTable20;
extern const NativeTable20 LVL_5_FELTZIN_SYSTEM_D_001A8EB0;
void LVL_5_FELTZIN_SYSTEM_FUN_002F00E0(s32 *object) {
    object[0]=0; object[1]=0; object[2]=0; object[3]=0; object[4]=0;
}
u32 LVL_5_FELTZIN_SYSTEM_FUN_0030C2F8(s32 index) {
    NativeTable20 values=LVL_5_FELTZIN_SYSTEM_D_001A8EB0;
    return values.items[index];
}

u32 LVL_5_FELTZIN_SYSTEM_FUN_002C6850(u8 *object,u32 value) {
    if(value==255) value=object[0xa9];
    return value;
}

extern u32 LVL_5_FELTZIN_SYSTEM_D_0018C0B4;
u32 LVL_5_FELTZIN_SYSTEM_FUN_002EF120(void) {
    return LVL_5_FELTZIN_SYSTEM_D_0018C0B4;
}

s32 LVL_5_FELTZIN_SYSTEM_FUN_002FC208(f32 a,f32 b,f32 t) {
 f32 difference=b-a;
 f32 squared=t*t;
 a=a*t;
 difference=difference*squared;
 a=a+difference;
 return (s32)a;
}

extern u8 LVL_5_FELTZIN_SYSTEM_D_00189E20[];

typedef struct {
    u8 prefix[0x1220];
    u32 field1220;
    u8 gap[0x20];
    s32 field1244, field1248;
} NativeIndexedFieldsView;

u32 LVL_5_FELTZIN_SYSTEM_FUN_002C66E8(s32 index) {
 NativeIndexedFieldsView *p=(NativeIndexedFieldsView *)((u8 *)&LVL_5_FELTZIN_SYSTEM_D_00189E20+index*0x50);
 if(p->field1244==2) return p->field1220;
 return 0;
}

s32 LVL_5_FELTZIN_SYSTEM_FUN_002C6720(s32 index) {
 NativeIndexedFieldsView *p=(NativeIndexedFieldsView *)((u8 *)&LVL_5_FELTZIN_SYSTEM_D_00189E20+index*0x50);
 if(p->field1244==2) return p->field1248;
 return -1;
}

s32 LVL_5_FELTZIN_SYSTEM_FUN_002C7340(s32 value) {
 switch(value) {case 1:return 0x72;case 2:return 0x70;case 3:return 0x6e;default:return 0;}
}

/* Frozen Batch A A01-shared-108; acknowledged claim 8fc9d5f80b3d5f44a785f41c0f987dca4231aa565dd750932d09299d0bf9e9c4. */
typedef int BatchA_A01_s32;

extern BatchA_A01_s32 BatchA_A01_D_001A7B90;
extern BatchA_A01_s32 BatchA_A01_D_001A7BB8 __attribute__((sda));
extern BatchA_A01_s32 BatchA_A01_FUN_00124418(void);
extern BatchA_A01_s32 BatchA_A01_FUN_001257D0(BatchA_A01_s32, BatchA_A01_s32, BatchA_A01_s32, BatchA_A01_s32);

void LVL_5_FELTZIN_SYSTEM_FUN_00307B40(void) {
    BatchA_A01_FUN_00124418();
    if (BatchA_A01_D_001A7B90 != 0) BatchA_A01_D_001A7BB8 = 0;
    if (*(BatchA_A01_s32 *)0x001a7bb8 != 0) BatchA_A01_FUN_001257D0(0,0,0x50,1);
    else BatchA_A01_FUN_001257D0(0,1,BatchA_A01_D_001A7B90 != 0 ? 3 : 2,0);
}

/* Frozen Batch A A02-list-add-88; acknowledged claim 38ceeb041b6ba12996de10c402ca54295587db96246845b83b2ec894986b096f. */
typedef unsigned char BatchA_A02_u8;
typedef int BatchA_A02_s32;
typedef struct { char _0[0x10]; BatchA_A02_u8 n; char _11[3]; BatchA_A02_s32 off; char _18[4]; BatchA_A02_s32 ent[1]; } BatchA_A02_Blk;
void LVL_5_FELTZIN_SYSTEM_FUN_00317320(int *a0, int a1){
  BatchA_A02_Blk *r;
  int i;
  a0 += a1;
  r = *(BatchA_A02_Blk **)((char *)a0 + 0x48);
  if (r->off) r->off = (int)r + r->off;
  for (i = 0; i < r->n; i++) r->ent[i] = (int)r + r->ent[i];
}

/* Frozen Batch A A03-counter-mod50-80; acknowledged claim b5e8cf533fd3cee3cb2dcdd0bf7be9549f6cc39cd932c589176487a8b170abee. */
typedef int BatchA_A03_s32;
extern BatchA_A03_s32 BatchA_A03_D_001A8FE0[] __attribute__((sda));
extern BatchA_A03_s32 BatchA_A03_D_001A7BC0[] __attribute__((sda));
extern BatchA_A03_s32 BatchA_A03_D_001A7B90[] __attribute__((sda));
void LVL_5_FELTZIN_SYSTEM_FUN_0036AA08(void)
{
    if (BatchA_A03_D_001A8FE0[0] == 0) {
        BatchA_A03_s32 n = BatchA_A03_D_001A7BC0[0] + 1;
        BatchA_A03_D_001A7BC0[0] = n;
        if (n % 50 == 0) {
            if (BatchA_A03_D_001A7B90[0]) {
                BatchA_A03_D_001A7BC0[0] = n + 10;
            }
        }
    }
}

/* Frozen Batch A A05-store-rotation-52; acknowledged claim 43a7518b17439f6bdc9390be9d4164b47eec4bed94a72d581fdec3b883b0a554. */
typedef unsigned char BatchA_A05_u8;
typedef unsigned short BatchA_A05_u16;
typedef short BatchA_A05_s16;
typedef unsigned int BatchA_A05_u32;
typedef int BatchA_A05_s32;
typedef float BatchA_A05_f32;
typedef short BatchA_A05_BatchAs16;
typedef unsigned short BatchA_A05_BatchAu16;
typedef struct { BatchA_A05_u8 b[0x50]; BatchA_A05_BatchAs16 f50; BatchA_A05_BatchAs16 f52; BatchA_A05_u8 c[0x20]; BatchA_A05_BatchAs16 f74; BatchA_A05_BatchAs16 f76; BatchA_A05_u8 d[0x20]; BatchA_A05_BatchAs16 f98; BatchA_A05_BatchAs16 f9a; } BatchA_A05_BatchA52;
extern BatchA_A05_BatchA52 BatchA_A05_BatchA_D001A63A8;
void LVL_5_FELTZIN_SYSTEM_FUN_00340480(BatchA_A05_s32 a0) {
    if (a0 != 0) { BatchA_A05_BatchA_D001A63A8.f76 = 0; BatchA_A05_BatchA_D001A63A8.f74 = -0x8000; }
    BatchA_A05_BatchA_D001A63A8.f9a = 0;
    BatchA_A05_BatchA_D001A63A8.f50 = -0x8000;
    BatchA_A05_BatchA_D001A63A8.f52 = 0;
    BatchA_A05_BatchA_D001A63A8.f98 = -0x8000;
}

/* Frozen Batch A A06-inline-init-40; acknowledged claim f87e1c08ece3f12938d297032a913cd328169b7754a3ddd6dc5186c16697eb73. */
typedef unsigned char BatchA_A06_u8;
typedef unsigned short BatchA_A06_u16;
typedef short BatchA_A06_s16;
typedef unsigned int BatchA_A06_u32;
typedef int BatchA_A06_s32;
typedef float BatchA_A06_f32;
typedef short BatchA_A06_BatchAs16;
typedef unsigned short BatchA_A06_BatchAu16;
void LVL_5_FELTZIN_SYSTEM_FUN_00339F80(void *a0, char *a1){
    if (*(BatchA_A06_s32 *)(a1 + 0x14C) == 0) {
        *(void **)(a1 + 0x144) = a0;
        *(BatchA_A06_s32 *)(a1 + 0x14C) = 1;
        *(BatchA_A06_BatchAs16 *)(a1 + 0x142) = 0;
        *(BatchA_A06_s32 *)(a1 + 0x148) = 0;
        *(BatchA_A06_BatchAs16 *)(a1 + 0x140) = 0;
    }
}

/* Frozen Batch A A07-sda-multi-eq-44; acknowledged claim 6adc81ebaa8d8c8d04aa1aa3c8950e1d91861a258898c3cce6be7f792e8bdcf3. */
typedef unsigned char BatchA_A07_u8;
typedef unsigned short BatchA_A07_u16;
typedef short BatchA_A07_s16;
typedef unsigned int BatchA_A07_u32;
typedef int BatchA_A07_s32;
typedef float BatchA_A07_f32;
typedef short BatchA_A07_BatchAs16;
typedef unsigned short BatchA_A07_BatchAu16;
extern BatchA_A07_s32 BatchA_A07_BatchA_D001A79F0a[] __attribute__((sda));
BatchA_A07_s32 LVL_5_FELTZIN_SYSTEM_FUN_002EF080(void) {
    BatchA_A07_s32 v = BatchA_A07_BatchA_D001A79F0a[0];
    return (v == 0x16) | (v == 0x2CE) | (v == 0x17);
}

/* Frozen Batch A A08-sda-offset-40; acknowledged claim 1c862bca494fc9285ae124fddbbb78dd145686c54c3afa751addc9271a2f8b70. */
typedef unsigned char BatchA_A08_u8;
typedef unsigned short BatchA_A08_u16;
typedef short BatchA_A08_s16;
typedef unsigned int BatchA_A08_u32;
typedef int BatchA_A08_s32;
typedef float BatchA_A08_f32;
typedef short BatchA_A08_BatchAs16;
typedef unsigned short BatchA_A08_BatchAu16;
extern BatchA_A08_s32 BatchA_A08_BatchA_D001A904C[] __attribute__((sda));
void LVL_5_FELTZIN_SYSTEM_FUN_00324C00(BatchA_A08_s32 a0, BatchA_A08_s32 a1) {
    BatchA_A08_s32 base = BatchA_A08_BatchA_D001A904C[0];
    BatchA_A08_s32 *p;
    if (base == 0) return;
    p = (BatchA_A08_s32 *)(base + 0x38000);
    p[0x7368/4] = a0;
    p[0x736C/4] = a1;
}

/* Frozen Batch A A11-sda-3store-28; acknowledged claim 9b61d4cdd097ce0a56790793fdd6c129d3f0d822e40e788cde17e6418bdea65f. */
typedef unsigned char BatchA_A11_u8;
typedef unsigned short BatchA_A11_u16;
extern BatchA_A11_u8 BatchA_A11_D_001A63A8[];
void LVL_5_FELTZIN_SYSTEM_FUN_003404B8(void) {
    BatchA_A11_u8 *p = BatchA_A11_D_001A63A8;
    *(BatchA_A11_u16 *)(p + 0x50) = 4;
    *(BatchA_A11_u16 *)(p + 0x98) = 4;
    *(BatchA_A11_u16 *)(p + 0x74) = 4;
}

/* Frozen Batch A A13-eq-getter-20; acknowledged claim 88eaf851f31627d1562797f83f79f60446fca428598034e69d6748fe46ec5a79. */
typedef unsigned char BatchA_A13_u8;
typedef unsigned short BatchA_A13_u16;
typedef short BatchA_A13_s16;
typedef unsigned int BatchA_A13_u32;
typedef int BatchA_A13_s32;
typedef float BatchA_A13_f32;
typedef short BatchA_A13_BatchAs16;
typedef unsigned short BatchA_A13_BatchAu16;
extern unsigned int BatchA_A13_BatchA_D001A79F0b[] __attribute__((sda));
unsigned int LVL_5_FELTZIN_SYSTEM_FUN_002EEF48(void) { return BatchA_A13_BatchA_D001A79F0b[0] == 0x19u; }

/* Frozen Batch A A14-struct-2field-20; acknowledged claim 3e0e0bb01b3da304ddd50c7212de48bebcbf96d3b2d117369779044d96f69b21. */
typedef unsigned int BatchA_A14_u32;
typedef struct { unsigned char pad[0x2494]; BatchA_A14_u32 a; BatchA_A14_u32 b; } BatchA_A14_S;
extern BatchA_A14_S BatchA_A14_D_00189E20;
void LVL_5_FELTZIN_SYSTEM_FUN_002EA7E0(void) {
    BatchA_A14_D_00189E20.a = 0;
    BatchA_A14_D_00189E20.b = 0;
}

/* Frozen Batch A A16-sda-byte-16; acknowledged claim 3b1980407c8765dd4baf122f505692e49c411cbff6089e896e8b3921ce208b41. */
typedef unsigned char BatchA_A16_u8;
typedef unsigned short BatchA_A16_u16;
typedef short BatchA_A16_s16;
typedef unsigned int BatchA_A16_u32;
typedef int BatchA_A16_s32;
typedef float BatchA_A16_f32;
typedef short BatchA_A16_BatchAs16;
typedef unsigned short BatchA_A16_BatchAu16;
extern BatchA_A16_u8 BatchA_A16_BatchA_D001A7A0A[] __attribute__((sda));
int LVL_5_FELTZIN_SYSTEM_FUN_0030C8E8(void) { return BatchA_A16_BatchA_D001A7A0A[0] != 0; }

extern void LVL_5_FELTZIN_SYSTEM_FUN_002EFE38(f32, f32, f32, f32, s32, s32);

void LVL_5_FELTZIN_SYSTEM_FUN_002EF8E0(u8 *object) {
 object[0x1d]=0;
 if (*(f32 *)(object+0x10)>=0.0f)
  LVL_5_FELTZIN_SYSTEM_FUN_002EFE38(1.1243411302566528f,0.005f,0.2f,0.0f,0,3);
}

/* Scalar GS setup wrapper; pinned standard integer arguments and helper calls. */
extern void LVL_5_FELTZIN_SYSTEM_FUN_00308B50(int width, int height, int address, int mode);
extern void LVL_5_FELTZIN_SYSTEM_FUN_003906F8(unsigned int reg, unsigned long value);
extern void LVL_5_FELTZIN_SYSTEM_FUN_00308EB8(int width, int height);

void LVL_5_FELTZIN_SYSTEM_FUN_002FE030(int width, int height)
{
    int sum = width + height;
    int address;

    if (sum > 16)
        sum = 16;
    address = 0x3ff000 - (4 << sum);
    address = (address >> 13) << 13;
    LVL_5_FELTZIN_SYSTEM_FUN_00308B50(width, height, address, 1);
    LVL_5_FELTZIN_SYSTEM_FUN_003906F8(0x47, 0x30000UL);
    LVL_5_FELTZIN_SYSTEM_FUN_003906F8(0x42, 0x8000000044UL);
    LVL_5_FELTZIN_SYSTEM_FUN_00308EB8(0x100, 0x100);
    LVL_5_FELTZIN_SYSTEM_FUN_003906F8(0x42, 0x8000000044UL);
}

extern void LVL_5_FELTZIN_SYSTEM_FUN_002EBF60(f32, f32, f32, f32 *, s32);

void LVL_5_FELTZIN_SYSTEM_FUN_002C6578(f32 *output) {
 LVL_5_FELTZIN_SYSTEM_FUN_002EBF60(0.3f,0.0f,1.34f,output,1);
}

s32 LVL_5_FELTZIN_SYSTEM_FUN_002C6758(s32 index) {
 s32 value=LVL_5_FELTZIN_SYSTEM_FUN_002C6720(index);
 if(value==12 || value==17) return 1;
 return 0;
}

s32 LVL_5_FELTZIN_SYSTEM_FUN_002C6790(s32 index) {
 return LVL_5_FELTZIN_SYSTEM_FUN_002C6720(index)==47;
}

s32 LVL_5_FELTZIN_SYSTEM_FUN_002CBAC8(u8 *object) {
 if(object==0) return 0;
 return *(short *)(object+0xaa)==71;
}

/* Advances a signed index, wrapping or clamping to the measured count. */
s32 LVL_5_FELTZIN_SYSTEM_FUN_00353FB8(const s32 *count, s32 index, s32 delta, s32 wrap) {
    if (wrap != 0) {
        index = (index + delta + *count) % *count;
    } else {
        index += delta;
        if (delta < 0) {
            if (index < 0) index = 0;
        } else if (index > *count - 1) {
            index = *count - 1;
        }
    }
    return index;
}

/* Update the measured fields of the first matching key among13records. */
typedef struct { unsigned int fields[25]; int key; unsigned int busy; unsigned int tail[9]; } UpdateRecord;
typedef char UpdateRecordSize[(sizeof(UpdateRecord) == 144) ? 1 : -1];
extern UpdateRecord LVL_5_FELTZIN_SYSTEM_D_00294200[13];
void LVL_5_FELTZIN_SYSTEM_FUN_0030F418(int key, unsigned int value)
{
    int i;
    for (i = 0; i < 13; i++) {
        if (LVL_5_FELTZIN_SYSTEM_D_00294200[i].key == key) break;
    }
    if (i < 13) {
        LVL_5_FELTZIN_SYSTEM_D_00294200[i].fields[9] = value;
        if (LVL_5_FELTZIN_SYSTEM_D_00294200[i].busy == 0)
            LVL_5_FELTZIN_SYSTEM_D_00294200[i].fields[1] = value;
    }
}

typedef struct {
    u8 prefix[0xa7];
    u8 fielda7;
} OrbitalBitmapView;
extern u8 LVL_5_FELTZIN_SYSTEM_D_001395B8[];
u32 LVL_5_FELTZIN_SYSTEM_FUN_0031DD00(s32 index) {
    s32 slot=index/8;
    u32 bit=index%8;
    u32 previous=0;
    if(bit<8) {
        OrbitalBitmapView *state=(OrbitalBitmapView *)(LVL_5_FELTZIN_SYSTEM_D_001395B8+slot);
        previous=((s32)state->fielda7>>bit)&1;
    }
    return previous;
}

typedef struct {
    u32 field00,field04;
    s32 field08;
    u8 gap0c[4];
} OrbitalPairTableView16;
extern u8 LVL_5_FELTZIN_SYSTEM_D_00231E40[];
s32 LVL_5_FELTZIN_SYSTEM_FUN_00392FD8(u32 key,u32 owner) {
    OrbitalPairTableView16 *entry=(OrbitalPairTableView16 *)LVL_5_FELTZIN_SYSTEM_D_00231E40;
    s32 checked=0;
    do {
        ++checked;
        if(entry->field04==key && entry->field00==owner) return entry->field08;
        ++entry;
    } while(checked<32);
    return -1;
}

/* Apply nonzero signed halfword overrides to indexed rows of selected objects. */
typedef struct {
    unsigned int first;
    unsigned char reserved04[0x1c];
    unsigned int second;
    unsigned char reserved24[0x0f];
    unsigned char key;
    unsigned char reserved34[0x1c];
} ListOverrideRow;
typedef struct {
    unsigned char reserved00[0x0f];
    unsigned char count;
    unsigned char reserved10[0x0c];
    ListOverrideRow *rows;
} ListOverrideObject;
typedef struct { short first; short second; } ListOverridePair;
extern int LVL_5_FELTZIN_SYSTEM_D_0022E700[];
extern ListOverrideObject *LVL_5_FELTZIN_SYSTEM_D_00227200[];
extern ListOverridePair LVL_5_FELTZIN_SYSTEM_D_0022E100[];
void LVL_5_FELTZIN_SYSTEM_FUN_0037FF40(void)
{
    int *selected = LVL_5_FELTZIN_SYSTEM_D_0022E700;
    while (*selected >= 0) {
        ListOverrideObject *object = LVL_5_FELTZIN_SYSTEM_D_00227200[*selected];
        int i = 0;
        ListOverrideRow *row = object->rows;
        while (i < object->count) {
            ListOverridePair *pair = &LVL_5_FELTZIN_SYSTEM_D_0022E100[row->key];
            if (pair->first != 0)
                row->first = (row->first & 0xffffc000u) | pair->first;
            if (pair->second != 0)
                row->second = (row->second & 0xffffc000u) | pair->second;
            i++;
            row++;
        }
        selected++;
    }
}

/* Finds the first matching object in the thirty resident records. */
typedef struct {
    u8 field00[0x14];
    void *field14;
    u8 field18[8];
} NativeObjectSearchRecord32;
extern NativeObjectSearchRecord32 LVL_5_FELTZIN_SYSTEM_D_00262770[];
s32 LVL_5_FELTZIN_SYSTEM_FUN_003FFC40(void *object) {
    s32 result = -1;
    s32 index;
    for (index = 0; index < 30; index++) {
        if (LVL_5_FELTZIN_SYSTEM_D_00262770[index].field14 == object) {
            result = index;
            break;
        }
    }
    return result;
}

typedef struct { u8 prefix[0xaa]; short class_id; } ClassFilterObject;
typedef struct {
    u8 prefix[0x33c];
    ClassFilterObject *fallback;
    u8 middle[0x14f0];
    ClassFilterObject *primary;
    u8 trailing[0xa60];
    s32 mode;
} ClassFilterRoot;

s32 LVL_5_FELTZIN_SYSTEM_FUN_002EEFE0(s32 selection) {
    s32 found = 0;
    ClassFilterObject *primary = ((ClassFilterRoot *)LVL_5_FELTZIN_SYSTEM_D_00189E20)->primary;
    ClassFilterObject *fallback = ((ClassFilterRoot *)LVL_5_FELTZIN_SYSTEM_D_00189E20)->fallback;
    if (((ClassFilterRoot *)LVL_5_FELTZIN_SYSTEM_D_00189E20)->mode == 0x31) {
        if (primary) {
            switch (selection) {
                case 0: found = primary->class_id == 0xfbf; break;
                case 1: found = primary->class_id == 0x905; break;
                case 2: found = primary->class_id == 0xeef; break;
            }
        } else if (fallback && selection == 3) {
            found = fallback->class_id == 0xc20;
        }
    }
    return found;
}

/* Select one of three measured pointer slots for the requested kind. */
extern void *LVL_5_FELTZIN_SYSTEM_D_0018C0B0;
extern void *LVL_5_FELTZIN_SYSTEM_D_0018B134;
extern void *LVL_5_FELTZIN_SYSTEM_D_0018B040;
void *LVL_5_FELTZIN_SYSTEM_FUN_002BD868(int kind)
{
    if (kind == 0 || kind == 2 || kind == 3 || kind == 4 || kind == 5)
        return LVL_5_FELTZIN_SYSTEM_D_0018C0B0;
    if (kind == 1)
        return LVL_5_FELTZIN_SYSTEM_D_0018B134;
    if (kind == 6)
        return LVL_5_FELTZIN_SYSTEM_D_0018B040;
    return 0;
}

/* Find a mapped record by its unsigned halfword class and return its opaque word. */
typedef struct {
    unsigned int marker;
    unsigned char reserved04[0x38];
    unsigned short class_code;
    unsigned char reserved3E[0xa2];
} MappedClassEntry;
typedef char MappedClassStride[(sizeof(MappedClassEntry) == 0xe0) ? 1 : -1];
extern unsigned char LVL_5_FELTZIN_SYSTEM_D_00139568[];
extern MappedClassEntry LVL_5_FELTZIN_SYSTEM_D_00278A70[];
unsigned int LVL_5_FELTZIN_SYSTEM_FUN_0030BFD0(unsigned int key)
{
    int i;
    for (i = 0; i < 56; i++) {
        MappedClassEntry *record = &LVL_5_FELTZIN_SYSTEM_D_00278A70[LVL_5_FELTZIN_SYSTEM_D_00139568[i]];
        if (record->class_code == key)
            return record->marker;
    }
    return 0;
}

/* Relocates serialized header offsets and compacts each row in its original storage. */
typedef unsigned long long NativeCompactU64;
typedef union {
    s32 field00[4];
    struct {
        NativeCompactU64 field00;
        short field08;
        short field0A;
        unsigned short field0C;
        unsigned short field0E;
    } compact;
} NativeCompactRow16;
typedef struct {
    u8 field00[6];
    short field06;
    u8 field08[4];
    f32 field0C;
    u32 field10;
    u32 field14;
    u32 field18;
    u32 field1C;
    u32 field20;
} NativeCompactHeader;
extern s32 LVL_5_FELTZIN_SYSTEM_FUN_00306370(s32 value);
NativeCompactHeader *LVL_5_FELTZIN_SYSTEM_FUN_00395338(NativeCompactHeader *header) {
    u32 base = (u32)header;
    NativeCompactRow16 *source;
    s32 index;
    header->field10 += base;
    header->field14 += base;
    header->field18 += base;
    header->field1C += base;
    if (header->field20 != 0) header->field20 += base;
    index = 0;
    source = (NativeCompactRow16 *)header->field18;
    header->field0C *= 0.0032116016f;
    if (header->field06 > 0) {
        do {
            s32 first = source->field00[0];
            s32 second = source->field00[1];
            s32 third = source->field00[2];
            s32 fourth = source->field00[3];
            ((NativeCompactRow16 *)header->field18)[index].compact.field0A = first >> 4;
            source++;
            ((NativeCompactRow16 *)header->field18)[index].compact.field08 = second >> 4;
            ((NativeCompactRow16 *)header->field18)[index].compact.field0C = LVL_5_FELTZIN_SYSTEM_FUN_00306370(third);
            ((NativeCompactRow16 *)header->field18)[index].compact.field0E = LVL_5_FELTZIN_SYSTEM_FUN_00306370(fourth);
            ((NativeCompactRow16 *)header->field18)[index].compact.field00 = 0;
            index++;
        } while (index < header->field06);
    }
    return header;
}

extern s32 LVL_5_FELTZIN_SYSTEM_D_001A79F0;
s32 LVL_5_FELTZIN_SYSTEM_FUN_002EEF60(void) {
    s32 found = 0;
    if (LVL_5_FELTZIN_SYSTEM_D_001A79F0 == 25 || LVL_5_FELTZIN_SYSTEM_D_001A79F0 == 5 ||
        LVL_5_FELTZIN_SYSTEM_D_001A79F0 == 10 || LVL_5_FELTZIN_SYSTEM_D_001A79F0 == 15) {
        found = 1;
    }
    return found;
}

typedef struct { u8 prefix[0x34]; unsigned short flags; } FlagPairObjectView;
typedef struct {
    u8 prefix[0x1860];
    FlagPairObjectView *secondary;
    u8 between[0xa2c];
    FlagPairObjectView *primary;
} FlagPairResidentView;
typedef char FlagPairResidentSize[(sizeof(FlagPairResidentView) == 0x2294) ? 1 : -1];
void LVL_5_FELTZIN_SYSTEM_FUN_002EBA50(void) {
    FlagPairResidentView *root = (FlagPairResidentView *)LVL_5_FELTZIN_SYSTEM_D_00189E20;
    FlagPairObjectView *primary = root->primary;
    FlagPairObjectView *secondary;
    primary->flags |= 1;
    secondary = root->secondary;
    if (secondary) secondary->flags |= 1;
}

void LVL_5_FELTZIN_SYSTEM_FUN_002EBA88(void) {
    FlagPairResidentView *root = (FlagPairResidentView *)LVL_5_FELTZIN_SYSTEM_D_00189E20;
    FlagPairObjectView *primary = root->primary;
    FlagPairObjectView *secondary;
    primary->flags &= ~1;
    secondary = root->secondary;
    if (secondary) secondary->flags &= ~1;
}

typedef struct {
    u8 field0;
    u8 active;
    u8 middle[4];
    unsigned short count;
    u8 trailing[8];
} ConditionalResetSlot;
typedef char ConditionalResetSlotSize[(sizeof(ConditionalResetSlot) == 16) ? 1 : -1];
extern ConditionalResetSlot LVL_5_FELTZIN_SYSTEM_D_001B9500[8];
void LVL_5_FELTZIN_SYSTEM_FUN_002EF3A8(void) {
    ConditionalResetSlot *slot = LVL_5_FELTZIN_SYSTEM_D_001B9500;
    s32 remaining = 7;
    do {
        if (slot->active) {
            slot->active = 0;
            slot->count = 0;
        }
        --remaining;
        ++slot;
    } while (remaining >= 0);
}

typedef struct {
    u8 prefix[0x40];
    s32 mode;
    u8 between[0x14];
    s32 state;
} StateTransitionView;
typedef char StateTransitionViewSize[(sizeof(StateTransitionView) == 0x5c) ? 1 : -1];
extern StateTransitionView LVL_5_FELTZIN_SYSTEM_D_001BF800;
void LVL_5_FELTZIN_SYSTEM_FUN_0030B938(void) {
    if (LVL_5_FELTZIN_SYSTEM_D_001BF800.mode == 7 && LVL_5_FELTZIN_SYSTEM_D_001BF800.state == 1) {
        LVL_5_FELTZIN_SYSTEM_D_001BF800.state = 2;
    }
}

/* Substitute the first percent selector in a record's localized text. */
typedef struct {
    unsigned char gap0[10];
    short text_id;
    short mapped_key;
    unsigned char gap0e[26];
} DobboFormatRow396;
typedef struct {
    unsigned char gap0[32];
    DobboFormatRow396 *rows;
} DobboFormatRoot396;
typedef struct {
    unsigned char gap0[0x80];
    int amount;
    unsigned char gap84[0x5c];
} DobboFormatMapped396;
typedef char DobboFormatRowStride396[(sizeof(DobboFormatRow396) == 40) ? 1 : -1];
typedef char DobboFormatMappedStride396[(sizeof(DobboFormatMapped396) == 0xe0) ? 1 : -1];
extern DobboFormatRoot396 LVL_5_FELTZIN_SYSTEM_D_001C9CA0;
extern const char LVL_5_FELTZIN_SYSTEM_D_001A99E0[];
extern const char LVL_5_FELTZIN_SYSTEM_D_001A99E8[];
extern const unsigned char *LVL_5_FELTZIN_SYSTEM_FUN_0030CBA8(int);
extern void BOOT_FUN_00115DA8(char *, const char *, ...);
void LVL_5_FELTZIN_SYSTEM_FUN_00321380(int index, unsigned char *output)
{
    unsigned char temporary[80];
    const unsigned char *source = LVL_5_FELTZIN_SYSTEM_FUN_0030CBA8(LVL_5_FELTZIN_SYSTEM_D_001C9CA0.rows[index].text_id);
    unsigned char *p = temporary;
    if (!source)
        return;
    while (*source && *source != '%')
        *output++ = *source++;
    if (!*source) {
        *output = *source;
        return;
    }
    ++source;
    if (*source == 'b') {
        int key = LVL_5_FELTZIN_SYSTEM_D_001C9CA0.rows[index].mapped_key;
        DobboFormatMapped396 *record = (DobboFormatMapped396 *)&LVL_5_FELTZIN_SYSTEM_D_00278A70[LVL_5_FELTZIN_SYSTEM_D_00139568[key]];
        BOOT_FUN_00115DA8((char *)temporary, LVL_5_FELTZIN_SYSTEM_D_001A99E0, record->amount);
    } else {
        BOOT_FUN_00115DA8((char *)temporary, LVL_5_FELTZIN_SYSTEM_D_001A99E8);
    }
    ++source;
    while (*p)
        *output++ = *p++;
    while (*source)
        *output++ = *source++;
    *output = 0;
}

typedef struct { u8 prefix[0xc38]; f32 plane; f32 depth; } GornFloatInterval64;

int LVL_5_FELTZIN_SYSTEM_FUN_002CC218(f32 value)
{
    GornFloatInterval64 *root = (GornFloatInterval64 *)LVL_5_FELTZIN_SYSTEM_D_00189E20;
    if (value < root->plane) {
        if (root->plane - value <= root->depth)
            return 1;
    }
    return 0;
}

/* Update the observed two-axis selection fields and their combined index. */
typedef struct {
    unsigned char gap0[0x43c];
    int column, row, index, mode;
} DobboGridState312;
extern int LVL_5_FELTZIN_SYSTEM_FUN_00371A60(int, unsigned int, void *);
void LVL_5_FELTZIN_SYSTEM_FUN_00455188(DobboGridState312 *state, unsigned int buttons)
{
    if (buttons & 0x1000) {
        LVL_5_FELTZIN_SYSTEM_FUN_00371A60(3, 0, 0);
        --state->row;
        if (state->row < 0) {
            if (state->column == 0) {
                state->mode = 2;
                state->row = 1;
                state->column = 3;
            } else if (state->column == 1) {
                state->row = state->column;
            }
        }
    } else if (buttons & 0x4000) {
        int row;
        LVL_5_FELTZIN_SYSTEM_FUN_00371A60(3, 0, 0);
        row = state->row + 1;
        state->row = row > 1 ? 0 : row;
    } else if (buttons & 0x8000) {
        LVL_5_FELTZIN_SYSTEM_FUN_00371A60(3, 0, 0);
        --state->column;
        if (state->column < 0) {
            state->column = 3;
            state->row = 1;
            state->mode = 2;
        }
    } else if (buttons & 0x2000) {
        LVL_5_FELTZIN_SYSTEM_FUN_00371A60(3, 0, 0);
        ++state->column;
        if (state->column >= 2)
            state->column = 0;
    }
    state->index = state->column + state->row * 2;
}

extern void *LVL_5_FELTZIN_SYSTEM_D_001B2480[16];
extern u32 LVL_5_FELTZIN_SYSTEM_D_001B24C0[16];

int LVL_5_FELTZIN_SYSTEM_FUN_00329728(void *object)
{
    int index;
    for (index = 0; index < 16; ++index) {
        if (LVL_5_FELTZIN_SYSTEM_D_001B2480[index] == 0 ||
            LVL_5_FELTZIN_SYSTEM_D_001B2480[index] == object) {
            LVL_5_FELTZIN_SYSTEM_D_001B2480[index] = object;
            LVL_5_FELTZIN_SYSTEM_D_001B24C0[index] = 0;
            return index;
        }
    }
    return -1;
}

/* Append an observed point index and update the original geometric descriptor. */
typedef struct {
    unsigned char gap0[0x10];
    float plane[4];
    unsigned char gap20[0x10];
    float (*points)[4];
    unsigned char gap34[0x25];
    unsigned char indices[3];
    unsigned char count;
} OozlaAppendDescriptor164;
typedef struct {
    unsigned char gap0[0x68];
    OozlaAppendDescriptor164 *descriptor;
    unsigned char gap6c[0x54];
    float transform[3][4];
} OozlaAppendObject164;
typedef char OozlaAppendDescriptorCount164[((int)&((OozlaAppendDescriptor164 *)0)->count == 0x5c) ? 1 : -1];
extern void LVL_5_FELTZIN_SYSTEM_FUN_002F5268(OozlaAppendObject164 *, int, const float *);
extern void LVL_5_FELTZIN_SYSTEM_FUN_00306660(float *, const float *, const float *);
extern void LVL_5_FELTZIN_SYSTEM_FUN_00306AD8(float *, const float *, const float *);
extern void LVL_5_FELTZIN_SYSTEM_FUN_002F55B0(OozlaAppendObject164 *, float *, const float *);
unsigned int LVL_5_FELTZIN_SYSTEM_FUN_002F51C0(OozlaAppendObject164 *object, unsigned int index, const float *direction)
{
    float difference[4];
    OozlaAppendDescriptor164 *descriptor = object->descriptor;
    descriptor->indices[descriptor->count] = index;
    ++descriptor->count;
    LVL_5_FELTZIN_SYSTEM_FUN_002F5268(object, (int)descriptor->count - 1, direction);
    if (descriptor->count != 1) {
        LVL_5_FELTZIN_SYSTEM_FUN_00306660(difference, descriptor->points[descriptor->indices[0]], descriptor->points[descriptor->indices[1]]);
        LVL_5_FELTZIN_SYSTEM_FUN_00306AD8(difference, difference, &object->transform[0][0]);
        LVL_5_FELTZIN_SYSTEM_FUN_002F55B0(object, descriptor->plane, difference);
    }
    return descriptor->count;
}

typedef struct { f32 x, y, z, w; } JammingParameterRow;
typedef struct {
    u8 prefix[0x30];
    JammingParameterRow rows[4];
    f32 weights[3];
} JammingParameterRows;
void LVL_5_FELTZIN_SYSTEM_FUN_0045A600(f32 weight, f32 x, f32 y, f32 z, f32 w, JammingParameterRows *object, s32 index) {
    object->rows[index].x = x;
    object->rows[index].y = y;
    object->rows[index].z = z;
    object->rows[index].w = w;
    object->weights[index] = weight;
}

typedef struct { f32 x, y, z, w; } JammingGridRow;
typedef struct { JammingGridRow rows[3]; } JammingGridGroup;
typedef struct { u8 prefix[0x2c]; JammingGridGroup groups[2]; } JammingGridObject;
void LVL_5_FELTZIN_SYSTEM_FUN_0045AA98(f32 x, f32 y, f32 z, f32 w, JammingGridObject *object, s32 row, s32 group) {
    object->groups[group].rows[row].x = x;
    object->groups[group].rows[row].y = y;
    object->groups[group].rows[row].z = z;
    object->groups[group].rows[row].w = w;
}

extern unsigned char D_19B278[];

int LVL_5_FELTZIN_SYSTEM_FUN_0033D280(void)
{
    int count = 0;
    int i;

    for (i = 0; i < 0x1C; i++) {
        int j;

        for (j = 0; j < 4; j++) {
            if (D_19B278[i * 4 + j] != 0)
                count++;
        }
    }
    if (count < 0)
        count = 0;
    if (count > 0x28)
        count = 0x28;
    return count;
}

typedef struct { u8 before[0x68]; s32 active; u8 gap[6]; short state; } CallState;
extern u8 LVL_5_FELTZIN_SYSTEM_D_001A63A8[];
extern void FUN_00133400(s32);
s32 LVL_5_FELTZIN_SYSTEM_FUN_0033FEC0(void) {
    if (((CallState *)LVL_5_FELTZIN_SYSTEM_D_001A63A8)->active==0) return 0;
    if (((CallState *)LVL_5_FELTZIN_SYSTEM_D_001A63A8)->state!=3) return 0;
    FUN_00133400(((CallState *)LVL_5_FELTZIN_SYSTEM_D_001A63A8)->active); ((CallState *)LVL_5_FELTZIN_SYSTEM_D_001A63A8)->state=4;
    return 1;
}

f32 LVL_5_FELTZIN_SYSTEM_FUN_00332A58(f32 value, s32 count) {
    f32 factor = 1.0f - value;
    f32 product = factor;
    for (; count > 1; --count)
        product = product * factor;
    return 1.0f - product;
}

typedef struct {
    u8 pad0000[0x0000];
} ResidentBase1395B8;

s32 LVL_5_FELTZIN_SYSTEM_FUN_0031DC80(s32 index)
{
    s32 byte = index / 8;
    s32 bit = index % 8;
    s32 old;

    if ((u32)bit < 8) {
        old = (LVL_5_FELTZIN_SYSTEM_D_001395B8[byte + 0xA7] >> bit) & 1;
    } else {
        old = 0;
    }
    if ((u32)bit < 8) {
        LVL_5_FELTZIN_SYSTEM_D_001395B8[byte + 0xA7] |= 1 << bit;
    }
    return old;
}

typedef struct {
    u8 pad0000[0x2294];
    u32 kind;
    u32 unknown2298;
    u32 mode;
} ResidentFlags2294;

s32 LVL_5_FELTZIN_SYSTEM_FUN_002C6800(void)
{
    ResidentFlags2294 *root = (ResidentFlags2294 *)LVL_5_FELTZIN_SYSTEM_D_00189E20;

    if (root->mode == 17 || root->mode == 18
        || root->kind == 0x67 || root->kind == 0x7f
        || root->kind == 0x73 || root->kind == 0x72) {
        return 1;
    }
    return 0;
}

/* Prototype775 is a research label. Field names below describe only the
 * independently observed byte23 and binary32 word2C operations. */
typedef struct {
    u8 pad00[0x23];
    u8 field23;
    u8 pad24[8];
    f32 field2C;
} NativeUpdate775View;

extern void LVL_5_FELTZIN_SYSTEM_FUN_00328870(NativeUpdate775View *object);

void LVL_5_FELTZIN_SYSTEM_FUN_003B4048(NativeUpdate775View *object)
{
    object->field2C *= 1.025f;
    object->field23 -= 3;
    if (object->field23 < 4)
        LVL_5_FELTZIN_SYSTEM_FUN_00328870(object);
}


/* One fixed ordinary scalar source hypothesis. Byte offset and mask are
   measured; no original object/class/field name or allocation claim. The
   observed callers pass scalar one and ignore the result. */
void LVL_5_FELTZIN_SYSTEM_FUN_0033DFE8(unsigned char *entity, int enabled) {
    if (enabled)
        entity[0xBE] |= 4;
    else
        entity[0xBE] &= 0xFB;
}


/* One fixed ordinary scalar query. Signed halfword width, offset and
   equality constant are measured; no original class or field-name claim. */
int LVL_5_FELTZIN_SYSTEM_FUN_00336FB8(const unsigned char *entity) {
    return *(const signed short *)(entity + 0xAA) == 0x0CDB;
}


void LVL_5_FELTZIN_SYSTEM_FUN_002BF970(void)
{
}


unsigned int LVL_5_FELTZIN_SYSTEM_FUN_002EF0B0(void)
{
    return 0;
}


void LVL_5_FELTZIN_SYSTEM_FUN_00305978(void)
{
}


void LVL_5_FELTZIN_SYSTEM_FUN_0030C928(void)
{
}


void LVL_5_FELTZIN_SYSTEM_FUN_0030D6F0(void)
{
}


void LVL_5_FELTZIN_SYSTEM_FUN_00314BB0(void)
{
}


void LVL_5_FELTZIN_SYSTEM_FUN_00314BB8(void)
{
}


void LVL_5_FELTZIN_SYSTEM_FUN_003189E0(void)
{
}


void LVL_5_FELTZIN_SYSTEM_FUN_00321738(void)
{
}


unsigned int LVL_5_FELTZIN_SYSTEM_FUN_00384670(void)
{
    return 0;
}


void LVL_5_FELTZIN_SYSTEM_FUN_00389130(void)
{
}


void LVL_5_FELTZIN_SYSTEM_FUN_00390148(void)
{
}


void LVL_5_FELTZIN_SYSTEM_FUN_00393A88(void)
{
}


void LVL_5_FELTZIN_SYSTEM_FUN_00397168(void)
{
}


void LVL_5_FELTZIN_SYSTEM_FUN_003FC820(void)
{
}


void LVL_5_FELTZIN_SYSTEM_FUN_0042A558(void)
{
}


void LVL_5_FELTZIN_SYSTEM_FUN_00447DC0(void)
{
}


void LVL_5_FELTZIN_SYSTEM_FUN_00449830(void)
{
}


void LVL_5_FELTZIN_SYSTEM_FUN_00449A80(void)
{
}


void LVL_5_FELTZIN_SYSTEM_FUN_00449F78(void)
{
}


void LVL_5_FELTZIN_SYSTEM_FUN_004527F0(void)
{
}


void LVL_5_FELTZIN_SYSTEM_FUN_00453448(void)
{
}


void LVL_5_FELTZIN_SYSTEM_FUN_0045F250(void)
{
}


void LVL_5_FELTZIN_SYSTEM_FUN_004615E0(void)
{
}


void LVL_5_FELTZIN_SYSTEM_FUN_00462E78(void)
{
}
void LVL_5_FELTZIN_SYSTEM_FUN_003989B0(char *p)
{
    *(long long *)(p + 112) = 0LL;
    *(int *)(p + 80) = 0;
    *(int *)(p + 84) = 0;
    *(float *)(p + 88) = 1.0f;
    *(int *)(p + 92) = 0;
    *(int *)(p + 96) = 0;
    *(float *)(p + 100) = 1.0f;
    *(float *)(p + 104) = 1.0f;
    *(float *)(p + 108) = 1.0f;
    *(float *)(p + 8) = -1.0f;
    *(float *)(p + 24) = 1.0f;
    *(float *)(p + 40) = -1.0f;
    *(float *)(p + 56) = 1.0f;
    *(float *)(p + 4) = -1.0f;
    *(float *)(p + 36) = 1.0f;
    *(float *)(p + 52) = 1.0f;
    *(int *)(p + 0) = 0;
    *(int *)(p + 16) = 0;
    *(int *)(p + 32) = 0;
    *(int *)(p + 48) = 0;
    *(float *)(p + 12) = 1.0f;
    *(float *)(p + 28) = 1.0f;
    *(float *)(p + 44) = 1.0f;
    *(long long *)(p + 128) = 280993940374112LL;
    *(float *)(p + 20) = -1.0f;
    *(float *)(p + 60) = 1.0f;
}
void LVL_5_FELTZIN_SYSTEM_FUN_003C7C88(char *p)
{
    *(long long *)(p + 112) = 0LL;
    *(int *)(p + 80) = 0;
    *(int *)(p + 84) = 0;
    *(float *)(p + 88) = 1.0f;
    *(int *)(p + 92) = 0;
    *(int *)(p + 96) = 0;
    *(float *)(p + 100) = 1.0f;
    *(float *)(p + 104) = 1.0f;
    *(float *)(p + 108) = 1.0f;
    *(float *)(p + 8) = -1.0f;
    *(float *)(p + 24) = 1.0f;
    *(float *)(p + 40) = -1.0f;
    *(float *)(p + 56) = 1.0f;
    *(float *)(p + 4) = -1.0f;
    *(float *)(p + 36) = 1.0f;
    *(float *)(p + 52) = 1.0f;
    *(int *)(p + 0) = 0;
    *(int *)(p + 16) = 0;
    *(int *)(p + 32) = 0;
    *(int *)(p + 48) = 0;
    *(float *)(p + 12) = 1.0f;
    *(float *)(p + 28) = 1.0f;
    *(float *)(p + 44) = 1.0f;
    *(long long *)(p + 128) = 280993940374112LL;
    *(float *)(p + 20) = -1.0f;
    *(float *)(p + 60) = 1.0f;
}
void LVL_5_FELTZIN_SYSTEM_FUN_003D4B78(char *p)
{
    *(long long *)(p + 112) = 0LL;
    *(int *)(p + 80) = 0;
    *(int *)(p + 84) = 0;
    *(float *)(p + 88) = 1.0f;
    *(int *)(p + 92) = 0;
    *(int *)(p + 96) = 0;
    *(float *)(p + 100) = 1.0f;
    *(float *)(p + 104) = 1.0f;
    *(float *)(p + 108) = 1.0f;
    *(float *)(p + 8) = -1.0f;
    *(float *)(p + 24) = 1.0f;
    *(float *)(p + 40) = -1.0f;
    *(float *)(p + 56) = 1.0f;
    *(float *)(p + 4) = -1.0f;
    *(float *)(p + 36) = 1.0f;
    *(float *)(p + 52) = 1.0f;
    *(int *)(p + 0) = 0;
    *(int *)(p + 16) = 0;
    *(int *)(p + 32) = 0;
    *(int *)(p + 48) = 0;
    *(float *)(p + 12) = 1.0f;
    *(float *)(p + 28) = 1.0f;
    *(float *)(p + 44) = 1.0f;
    *(long long *)(p + 128) = 280993940374112LL;
    *(float *)(p + 20) = -1.0f;
    *(float *)(p + 60) = 1.0f;
}
void LVL_5_FELTZIN_SYSTEM_FUN_003DEF90(char *p)
{
    *(long long *)(p + 112) = 0LL;
    *(int *)(p + 80) = 0;
    *(int *)(p + 84) = 0;
    *(float *)(p + 88) = 1.0f;
    *(int *)(p + 92) = 0;
    *(int *)(p + 96) = 0;
    *(float *)(p + 100) = 1.0f;
    *(float *)(p + 104) = 1.0f;
    *(float *)(p + 108) = 1.0f;
    *(float *)(p + 8) = -1.0f;
    *(float *)(p + 24) = 1.0f;
    *(float *)(p + 40) = -1.0f;
    *(float *)(p + 56) = 1.0f;
    *(float *)(p + 4) = -1.0f;
    *(float *)(p + 36) = 1.0f;
    *(float *)(p + 52) = 1.0f;
    *(int *)(p + 0) = 0;
    *(int *)(p + 16) = 0;
    *(int *)(p + 32) = 0;
    *(int *)(p + 48) = 0;
    *(float *)(p + 12) = 1.0f;
    *(float *)(p + 28) = 1.0f;
    *(float *)(p + 44) = 1.0f;
    *(long long *)(p + 128) = 280993940374112LL;
    *(float *)(p + 20) = -1.0f;
    *(float *)(p + 60) = 1.0f;
}
void LVL_5_FELTZIN_SYSTEM_FUN_003E5E38(char *p)
{
    *(long long *)(p + 112) = 0LL;
    *(int *)(p + 80) = 0;
    *(int *)(p + 84) = 0;
    *(float *)(p + 88) = 1.0f;
    *(int *)(p + 92) = 0;
    *(int *)(p + 96) = 0;
    *(float *)(p + 100) = 1.0f;
    *(float *)(p + 104) = 1.0f;
    *(float *)(p + 108) = 1.0f;
    *(float *)(p + 8) = -1.0f;
    *(float *)(p + 24) = 1.0f;
    *(float *)(p + 40) = -1.0f;
    *(float *)(p + 56) = 1.0f;
    *(float *)(p + 4) = -1.0f;
    *(float *)(p + 36) = 1.0f;
    *(float *)(p + 52) = 1.0f;
    *(int *)(p + 0) = 0;
    *(int *)(p + 16) = 0;
    *(int *)(p + 32) = 0;
    *(int *)(p + 48) = 0;
    *(float *)(p + 12) = 1.0f;
    *(float *)(p + 28) = 1.0f;
    *(float *)(p + 44) = 1.0f;
    *(long long *)(p + 128) = 280993940374112LL;
    *(float *)(p + 20) = -1.0f;
    *(float *)(p + 60) = 1.0f;
}
void LVL_5_FELTZIN_SYSTEM_FUN_003E93E0(char *p)
{
    *(long long *)(p + 112) = 0LL;
    *(int *)(p + 80) = 0;
    *(int *)(p + 84) = 0;
    *(float *)(p + 88) = 1.0f;
    *(int *)(p + 92) = 0;
    *(int *)(p + 96) = 0;
    *(float *)(p + 100) = 1.0f;
    *(float *)(p + 104) = 1.0f;
    *(float *)(p + 108) = 1.0f;
    *(float *)(p + 8) = -1.0f;
    *(float *)(p + 24) = 1.0f;
    *(float *)(p + 40) = -1.0f;
    *(float *)(p + 56) = 1.0f;
    *(float *)(p + 4) = -1.0f;
    *(float *)(p + 36) = 1.0f;
    *(float *)(p + 52) = 1.0f;
    *(int *)(p + 0) = 0;
    *(int *)(p + 16) = 0;
    *(int *)(p + 32) = 0;
    *(int *)(p + 48) = 0;
    *(float *)(p + 12) = 1.0f;
    *(float *)(p + 28) = 1.0f;
    *(float *)(p + 44) = 1.0f;
    *(long long *)(p + 128) = 280993940374112LL;
    *(float *)(p + 20) = -1.0f;
    *(float *)(p + 60) = 1.0f;
}
void LVL_5_FELTZIN_SYSTEM_FUN_003EF6C0(char *p)
{
    *(long long *)(p + 112) = 0LL;
    *(int *)(p + 80) = 0;
    *(int *)(p + 84) = 0;
    *(float *)(p + 88) = 1.0f;
    *(int *)(p + 92) = 0;
    *(int *)(p + 96) = 0;
    *(float *)(p + 100) = 1.0f;
    *(float *)(p + 104) = 1.0f;
    *(float *)(p + 108) = 1.0f;
    *(float *)(p + 8) = -1.0f;
    *(float *)(p + 24) = 1.0f;
    *(float *)(p + 40) = -1.0f;
    *(float *)(p + 56) = 1.0f;
    *(float *)(p + 4) = -1.0f;
    *(float *)(p + 36) = 1.0f;
    *(float *)(p + 52) = 1.0f;
    *(int *)(p + 0) = 0;
    *(int *)(p + 16) = 0;
    *(int *)(p + 32) = 0;
    *(int *)(p + 48) = 0;
    *(float *)(p + 12) = 1.0f;
    *(float *)(p + 28) = 1.0f;
    *(float *)(p + 44) = 1.0f;
    *(long long *)(p + 128) = 280993940374112LL;
    *(float *)(p + 20) = -1.0f;
    *(float *)(p + 60) = 1.0f;
}
void LVL_5_FELTZIN_SYSTEM_FUN_003F8228(char *p)
{
    *(long long *)(p + 112) = 0LL;
    *(int *)(p + 80) = 0;
    *(int *)(p + 84) = 0;
    *(float *)(p + 88) = 1.0f;
    *(int *)(p + 92) = 0;
    *(int *)(p + 96) = 0;
    *(float *)(p + 100) = 1.0f;
    *(float *)(p + 104) = 1.0f;
    *(float *)(p + 108) = 1.0f;
    *(float *)(p + 8) = -1.0f;
    *(float *)(p + 24) = 1.0f;
    *(float *)(p + 40) = -1.0f;
    *(float *)(p + 56) = 1.0f;
    *(float *)(p + 4) = -1.0f;
    *(float *)(p + 36) = 1.0f;
    *(float *)(p + 52) = 1.0f;
    *(int *)(p + 0) = 0;
    *(int *)(p + 16) = 0;
    *(int *)(p + 32) = 0;
    *(int *)(p + 48) = 0;
    *(float *)(p + 12) = 1.0f;
    *(float *)(p + 28) = 1.0f;
    *(float *)(p + 44) = 1.0f;
    *(long long *)(p + 128) = 280993940374112LL;
    *(float *)(p + 20) = -1.0f;
    *(float *)(p + 60) = 1.0f;
}
void LVL_5_FELTZIN_SYSTEM_FUN_003F95D0(char *p)
{
    *(long long *)(p + 112) = 0LL;
    *(int *)(p + 80) = 0;
    *(int *)(p + 84) = 0;
    *(float *)(p + 88) = 1.0f;
    *(int *)(p + 92) = 0;
    *(int *)(p + 96) = 0;
    *(float *)(p + 100) = 1.0f;
    *(float *)(p + 104) = 1.0f;
    *(float *)(p + 108) = 1.0f;
    *(float *)(p + 8) = -1.0f;
    *(float *)(p + 24) = 1.0f;
    *(float *)(p + 40) = -1.0f;
    *(float *)(p + 56) = 1.0f;
    *(float *)(p + 4) = -1.0f;
    *(float *)(p + 36) = 1.0f;
    *(float *)(p + 52) = 1.0f;
    *(int *)(p + 0) = 0;
    *(int *)(p + 16) = 0;
    *(int *)(p + 32) = 0;
    *(int *)(p + 48) = 0;
    *(float *)(p + 12) = 1.0f;
    *(float *)(p + 28) = 1.0f;
    *(float *)(p + 44) = 1.0f;
    *(long long *)(p + 128) = 280993940374112LL;
    *(float *)(p + 20) = -1.0f;
    *(float *)(p + 60) = 1.0f;
}
void LVL_5_FELTZIN_SYSTEM_FUN_004239A0(char *p)
{
    *(long long *)(p + 112) = 0LL;
    *(int *)(p + 80) = 0;
    *(int *)(p + 84) = 0;
    *(float *)(p + 88) = 1.0f;
    *(int *)(p + 92) = 0;
    *(int *)(p + 96) = 0;
    *(float *)(p + 100) = 1.0f;
    *(float *)(p + 104) = 1.0f;
    *(float *)(p + 108) = 1.0f;
    *(float *)(p + 8) = -1.0f;
    *(float *)(p + 24) = 1.0f;
    *(float *)(p + 40) = -1.0f;
    *(float *)(p + 56) = 1.0f;
    *(float *)(p + 4) = -1.0f;
    *(float *)(p + 36) = 1.0f;
    *(float *)(p + 52) = 1.0f;
    *(int *)(p + 0) = 0;
    *(int *)(p + 16) = 0;
    *(int *)(p + 32) = 0;
    *(int *)(p + 48) = 0;
    *(float *)(p + 12) = 1.0f;
    *(float *)(p + 28) = 1.0f;
    *(float *)(p + 44) = 1.0f;
    *(long long *)(p + 128) = 280993940374112LL;
    *(float *)(p + 20) = -1.0f;
    *(float *)(p + 60) = 1.0f;
}
void LVL_5_FELTZIN_SYSTEM_FUN_00430C58(char *p)
{
    *(long long *)(p + 112) = 0LL;
    *(int *)(p + 80) = 0;
    *(int *)(p + 84) = 0;
    *(float *)(p + 88) = 1.0f;
    *(int *)(p + 92) = 0;
    *(int *)(p + 96) = 0;
    *(float *)(p + 100) = 1.0f;
    *(float *)(p + 104) = 1.0f;
    *(float *)(p + 108) = 1.0f;
    *(float *)(p + 8) = -1.0f;
    *(float *)(p + 24) = 1.0f;
    *(float *)(p + 40) = -1.0f;
    *(float *)(p + 56) = 1.0f;
    *(float *)(p + 4) = -1.0f;
    *(float *)(p + 36) = 1.0f;
    *(float *)(p + 52) = 1.0f;
    *(int *)(p + 0) = 0;
    *(int *)(p + 16) = 0;
    *(int *)(p + 32) = 0;
    *(int *)(p + 48) = 0;
    *(float *)(p + 12) = 1.0f;
    *(float *)(p + 28) = 1.0f;
    *(float *)(p + 44) = 1.0f;
    *(long long *)(p + 128) = 280993940374112LL;
    *(float *)(p + 20) = -1.0f;
    *(float *)(p + 60) = 1.0f;
}

extern u8 LVL_5_FELTZIN_SYSTEM_F62e6ff2b_D_00189E20[];
extern u8 LVL_5_FELTZIN_SYSTEM_F62e6ff2b_D_00188660[];

typedef struct {
    u8 pad0[4640];
    u32 field4640;
    u8 gap[4204];
    u32 field8848;
} NativeView;

s32 LVL_5_FELTZIN_SYSTEM_FUN_00371658(s32 id)
{
    u8 *record;
    u8 *cursor;
    s32 limit;

    limit = 52;
    if (id == 0 || (((NativeView *)&LVL_5_FELTZIN_SYSTEM_F62e6ff2b_D_00189E20)->field8848 != (u32)id &&
                    ((NativeView *)&LVL_5_FELTZIN_SYSTEM_F62e6ff2b_D_00189E20)->field4640 != (u32)id))
        limit = 42;

    id = 0;
    if (limit != 0) {
        record = (u8 *)&LVL_5_FELTZIN_SYSTEM_F62e6ff2b_D_00188660;
        if (record[116] != 0) {
            cursor = record + 116;
            do {
                id++;
                if (id >= limit)
                    break;
                cursor += 112;
            } while (*cursor != 0);
        }
    }
    return (id != limit) ? id : 52;
}

extern u8 LVL_5_FELTZIN_SYSTEM_F1c0a2bbf_D_001ADD18[];
extern u8 LVL_5_FELTZIN_SYSTEM_F1c0a2bbf_D_001ADD38[];
extern void LVL_5_FELTZIN_SYSTEM_F1c0a2bbf_FUN_00115E38(void *, s32, void *);

void LVL_5_FELTZIN_SYSTEM_FUN_00447DD8(u32 *p, u32 a1, u32 a2, u32 a3)
{
    if (a1 < 4u)
        LVL_5_FELTZIN_SYSTEM_F1c0a2bbf_FUN_00115E38(LVL_5_FELTZIN_SYSTEM_F1c0a2bbf_D_001ADD18, 37, LVL_5_FELTZIN_SYSTEM_F1c0a2bbf_D_001ADD38);
    p[0] = a2;
    p[1] = a3;
    p[2] = a1;
    p[5] = 0;
    p[3] = 0;
    p[4] = 0;
}
void LVL_5_FELTZIN_SYSTEM_FUN_003B7EB0(char *p)
{
    *(long long *)(p + 112) = 0LL;
    *(int *)(p + 80) = 0;
    *(int *)(p + 88) = 0;
    *(float *)(p + 96) = 1.0f;
    *(float *)(p + 104) = 1.0f;
    *(int *)(p + 84) = 0;
    *(float *)(p + 92) = 1.0f;
    *(int *)(p + 100) = 0;
    *(float *)(p + 108) = 1.0f;
    *(float *)(p + 8) = -2.0f;
    *(float *)(p + 24) = 2.0f;
    *(float *)(p + 40) = -2.0f;
    *(float *)(p + 56) = 2.0f;
    *(float *)(p + 4) = -2.0f;
    *(float *)(p + 36) = 2.0f;
    *(int *)(p + 0) = 0;
    *(int *)(p + 16) = 0;
    *(int *)(p + 32) = 0;
    *(int *)(p + 48) = 0;
    *(float *)(p + 12) = 1.0f;
    *(float *)(p + 28) = 1.0f;
    *(float *)(p + 44) = 1.0f;
    *(long long *)(p + 128) = 280993940374112LL;
    *(float *)(p + 20) = -2.0f;
    *(float *)(p + 52) = 2.0f;
    *(float *)(p + 60) = 1.0f;
}
void LVL_5_FELTZIN_SYSTEM_FUN_003F2220(char *p)
{
    *(long long *)(p + 112) = 0LL;
    *(int *)(p + 80) = 0;
    *(int *)(p + 88) = 0;
    *(float *)(p + 96) = 1.0f;
    *(float *)(p + 104) = 1.0f;
    *(int *)(p + 84) = 0;
    *(float *)(p + 92) = 1.0f;
    *(int *)(p + 100) = 0;
    *(float *)(p + 108) = 1.0f;
    *(float *)(p + 8) = -2.0f;
    *(float *)(p + 24) = 2.0f;
    *(float *)(p + 40) = -2.0f;
    *(float *)(p + 56) = 2.0f;
    *(float *)(p + 4) = -2.0f;
    *(float *)(p + 36) = 2.0f;
    *(int *)(p + 0) = 0;
    *(int *)(p + 16) = 0;
    *(int *)(p + 32) = 0;
    *(int *)(p + 48) = 0;
    *(float *)(p + 12) = 1.0f;
    *(float *)(p + 28) = 1.0f;
    *(float *)(p + 44) = 1.0f;
    *(long long *)(p + 128) = 280993940374112LL;
    *(float *)(p + 20) = -2.0f;
    *(float *)(p + 52) = 2.0f;
    *(float *)(p + 60) = 1.0f;
}
typedef struct { int v[12]; } Blob;
extern Blob LVL_5_FELTZIN_SYSTEM_F6894d7c1_D_001A8E60;
int LVL_5_FELTZIN_SYSTEM_FUN_0030BC00(int x)
{
    Blob b;
    int i;
    b = LVL_5_FELTZIN_SYSTEM_F6894d7c1_D_001A8E60;
    for (i = 0; b.v[i]; i++)
        if (x == b.v[i])
            return 1;
    return 0;
}
extern int LVL_5_FELTZIN_SYSTEM_Fafab4c55_FUN_00115DA8(char *, char *, ...);
extern char LVL_5_FELTZIN_SYSTEM_Fafab4c55_D_001AD5F0[];
extern char LVL_5_FELTZIN_SYSTEM_Fafab4c55_D_001AD600[];
extern char LVL_5_FELTZIN_SYSTEM_Fafab4c55_D_001AD608[];

void LVL_5_FELTZIN_SYSTEM_FUN_0038AB30(char *dst, int value)
{
    if (value > 999999)
        LVL_5_FELTZIN_SYSTEM_Fafab4c55_FUN_00115DA8(dst, LVL_5_FELTZIN_SYSTEM_Fafab4c55_D_001AD5F0, value / 1000000, (value / 1000) % 1000, value % 1000);
    else if (value >= 1000)
        LVL_5_FELTZIN_SYSTEM_Fafab4c55_FUN_00115DA8(dst, LVL_5_FELTZIN_SYSTEM_Fafab4c55_D_001AD600, value / 1000, value % 1000);
    else
        LVL_5_FELTZIN_SYSTEM_Fafab4c55_FUN_00115DA8(dst, LVL_5_FELTZIN_SYSTEM_Fafab4c55_D_001AD608, value);
}
typedef struct {
    char *base;
    unsigned limit;
    unsigned size;
    unsigned cur;
    int count;
    void *free;
} Hdr;

extern int LVL_5_FELTZIN_SYSTEM_Fe77c6258_FUN_00115E38(char *, int, char *);
extern char LVL_5_FELTZIN_SYSTEM_Fe77c6258_D_001ADD18[];
extern char LVL_5_FELTZIN_SYSTEM_Fe77c6258_D_001ADD60[];

void *LVL_5_FELTZIN_SYSTEM_FUN_00447E60(Hdr *p)
{
    void *q;
    unsigned cur;
    unsigned n;
    char *r;

    if (p->free != 0) {
        q = p->free;
        p->free = *(void **)q;
        p->count++;
        return q;
    }
    cur = p->cur;
    if (p->limit < cur + p->size) {
        LVL_5_FELTZIN_SYSTEM_Fe77c6258_FUN_00115E38(LVL_5_FELTZIN_SYSTEM_Fe77c6258_D_001ADD18, 83, LVL_5_FELTZIN_SYSTEM_Fe77c6258_D_001ADD60);
        return 0;
    }
    r = p->base + cur;
    p->cur = cur + p->size;
    p->count++;
    return r;
}
void LVL_5_FELTZIN_SYSTEM_FUN_0039E948(char *p)
{
    *(long long *)(p + 112) = 0LL;
    *(int *)(p + 80) = 0;
    *(int *)(p + 84) = 0;
    *(float *)(p + 88) = 1.0f;
    *(int *)(p + 92) = 0;
    *(int *)(p + 96) = 0;
    *(float *)(p + 100) = 1.0f;
    *(float *)(p + 104) = 1.0f;
    *(float *)(p + 108) = 1.0f;
    *(float *)(p + 8) = -2.0f;
    *(float *)(p + 24) = 2.0f;
    *(float *)(p + 40) = -2.0f;
    *(float *)(p + 56) = 2.0f;
    *(float *)(p + 4) = -2.0f;
    *(float *)(p + 36) = 2.0f;
    *(int *)(p + 0) = 0;
    *(int *)(p + 16) = 0;
    *(int *)(p + 32) = 0;
    *(int *)(p + 48) = 0;
    *(float *)(p + 12) = 1.0f;
    *(float *)(p + 28) = 1.0f;
    *(float *)(p + 44) = 1.0f;
    *(long long *)(p + 128) = 0x0000FF9000000260LL;
    *(float *)(p + 20) = -2.0f;
    *(float *)(p + 52) = 2.0f;
    *(float *)(p + 60) = 1.0f;
}
void LVL_5_FELTZIN_SYSTEM_FUN_003A0FD0(char *p)
{
    *(long long *)(p + 112) = 0LL;
    *(int *)(p + 80) = 0;
    *(int *)(p + 84) = 0;
    *(float *)(p + 88) = 1.0f;
    *(int *)(p + 92) = 0;
    *(int *)(p + 96) = 0;
    *(float *)(p + 100) = 1.0f;
    *(float *)(p + 104) = 1.0f;
    *(float *)(p + 108) = 1.0f;
    *(float *)(p + 8) = -2.0f;
    *(float *)(p + 24) = 2.0f;
    *(float *)(p + 40) = -2.0f;
    *(float *)(p + 56) = 2.0f;
    *(float *)(p + 4) = -2.0f;
    *(float *)(p + 36) = 2.0f;
    *(int *)(p + 0) = 0;
    *(int *)(p + 16) = 0;
    *(int *)(p + 32) = 0;
    *(int *)(p + 48) = 0;
    *(float *)(p + 12) = 1.0f;
    *(float *)(p + 28) = 1.0f;
    *(float *)(p + 44) = 1.0f;
    *(long long *)(p + 128) = 0x0000FF9000000260LL;
    *(float *)(p + 20) = -2.0f;
    *(float *)(p + 52) = 2.0f;
    *(float *)(p + 60) = 1.0f;
}
void LVL_5_FELTZIN_SYSTEM_FUN_00433468(char *p)
{
    *(long long *)(p + 112) = 0LL;
    *(int *)(p + 8) = 0;
    *(float *)(p + 24) = 2.0f;
    *(int *)(p + 40) = 0;
    *(float *)(p + 4) = -1.0f;
    *(float *)(p + 36) = 1.0f;
    *(float *)(p + 52) = 1.0f;
    *(int *)(p + 0) = 0;
    *(int *)(p + 16) = 0;
    *(int *)(p + 32) = 0;
    *(int *)(p + 48) = 0;
    *(float *)(p + 12) = 1.0f;
    *(float *)(p + 28) = 1.0f;
    *(float *)(p + 44) = 1.0f;
    *(long long *)(p + 128) = 0x0000FF9000000260LL;
    *(float *)(p + 56) = 2.0f;
    *(float *)(p + 20) = -1.0f;
    *(float *)(p + 60) = 1.0f;
}
typedef struct { short key; short val; } Entry;

extern Entry *LVL_5_FELTZIN_SYSTEM_Fc68ad20a_D_0018C2B8;

int LVL_5_FELTZIN_SYSTEM_FUN_002EA7F8(int key, int *out)
{
    Entry *e = LVL_5_FELTZIN_SYSTEM_Fc68ad20a_D_0018C2B8;
    Entry *p;

    if (e == 0)
        return 0;
    if (e->key == -1)
        goto notfound;
    p = e;
    for (;;) {
        if (key == p->key) {
            *out = p->val;
            return 1;
        }
        p++;
        if (p->key == -1)
            goto notfound;
    }
notfound:
    *out = 0;
    return 0;
}
typedef struct {
    int f0;
    short f4;
    unsigned char f6;
    char pad[0x18 - 7];
    int f18;
    int f1C;
} Blk;

extern Blk LVL_5_FELTZIN_SYSTEM_F55a1acb8_D_001A63A8;
extern short LVL_5_FELTZIN_SYSTEM_F55a1acb8_D_001A63AC;
extern int LVL_5_FELTZIN_SYSTEM_F55a1acb8_FUN_00133688(void);
extern void LVL_5_FELTZIN_SYSTEM_F55a1acb8_FUN_0011AEA0(int);

void LVL_5_FELTZIN_SYSTEM_FUN_00340F20(int x)
{
    unsigned char c;
    int q;
    int arg;

    if (x != 1)
        return;

    if (LVL_5_FELTZIN_SYSTEM_F55a1acb8_FUN_00133688()) {
        LVL_5_FELTZIN_SYSTEM_F55a1acb8_D_001A63AC = 2;
        return;
    }

    LVL_5_FELTZIN_SYSTEM_F55a1acb8_FUN_0011AEA0(0);

    c = LVL_5_FELTZIN_SYSTEM_F55a1acb8_D_001A63A8.f6;
    q = LVL_5_FELTZIN_SYSTEM_F55a1acb8_D_001A63A8.f18;
    LVL_5_FELTZIN_SYSTEM_F55a1acb8_D_001A63A8.f4 = 0;
    arg = c < 1;
    LVL_5_FELTZIN_SYSTEM_F55a1acb8_D_001A63A8.f6 = 0;

    if (q != 0) {
        int cb = LVL_5_FELTZIN_SYSTEM_F55a1acb8_D_001A63A8.f1C;
        LVL_5_FELTZIN_SYSTEM_F55a1acb8_D_001A63A8.f18 = 0;
        LVL_5_FELTZIN_SYSTEM_F55a1acb8_D_001A63A8.f1C = 0;
        ((void (*)(int, int))q)(cb, arg);
    }
}
void LVL_5_FELTZIN_SYSTEM_FUN_003E5968(void)
{
    int *p;
    int i;

    p = *(int **)0x1B32A0 + 60;
    for (i = 3; i >= 0; i--) { *p = 0; p -= 16; }

    p = *(int **)0x1B32A4 + 4799;
    for (i = 149; i >= 0; i--) { *p = 0; p -= 32; }

    p = *(int **)0x1B32A8;
    for (i = 9; i >= 0; i--) { p[1] = 0; p[0] = 0; p += 4; }
}
extern char LVL_5_FELTZIN_SYSTEM_Fa2dbe766_D_00189E20[];

int LVL_5_FELTZIN_SYSTEM_FUN_003D8E28(float f12)
{
    char *b;

    if (f12 <= 0.0f)
        goto fail;
    b = LVL_5_FELTZIN_SYSTEM_Fa2dbe766_D_00189E20;
    if (*(short *)(*(int *)(b + 8848) + 170) != 0)
        goto fail;
    if (*(unsigned char *)(b + 8884) != 0)
        goto fail;
    if (*(int *)(b + 8852) == 49)
        goto fail;
    if (*(int *)(b + 8860) == 20)
        goto fail;
    if (*(int *)(b + 9420) > 0)
        goto ok;
fail:
    return 0;
ok:
    return 1;
}
void LVL_5_FELTZIN_SYSTEM_FUN_00358888(void)
{
    *(short *)0x001AA802 = (*(unsigned char *)0x001A7BC9) ? 3 : 0;
    *(short *)0x001AA81A = (*(unsigned char *)0x001A7BCA) ? 3 : 0;
    *(short *)0x001AA832 = (*(unsigned char *)0x001A7BCB) ? 3 : 0;
    *(short *)0x001AA84A = (*(unsigned char *)0x001A7BCC) ? 3 : 0;
    *(short *)0x001AA862 = (*(unsigned char *)0x001A7BCE) ? 3 : 0;
}
void LVL_5_FELTZIN_SYSTEM_FUN_0040FED8(char *object)
{
    char *o = object;
    int *q = *(int **)(o + 104);

    if (*(unsigned char *)(o + 32))
        return;

    q[2] = 64;
    q[4] = 50;
    q[0] = 0;
    q[3] = -1;
    q[5] = 0;
    *(unsigned char *)(o + 32) = 1;
    q[6] = -1;

    *(float *)(o + 44) = *(float *)(*(int *)(o + 36) + 36) * 0.8f;
}
extern char LVL_5_FELTZIN_SYSTEM_Fea34650e_D_00189E20[];

void LVL_5_FELTZIN_SYSTEM_FUN_002EB8E8(void)
{
    char *b = LVL_5_FELTZIN_SYSTEM_Fea34650e_D_00189E20;
    char *p;
    int i;

    p = *(char **)(b + 3096);
    *(unsigned short *)(p + 52) &= 0xFFFE;

    for (i = 0; i < 7; i++) {
        p = *(char **)(b + 4640 + i * 80);
        if (p != 0)
            *(unsigned short *)(p + 52) &= 0xFFFE;
        p = *(char **)(b + 4644 + i * 80);
        if (p != 0)
            *(unsigned short *)(p + 52) &= 0xFFFE;
        p = *(char **)(b + 4648 + i * 80);
        if (p != 0)
            *(unsigned short *)(p + 52) &= 0xFFFE;
    }

    if (1) {
        char *c = LVL_5_FELTZIN_SYSTEM_Fea34650e_D_00189E20;
        p = *(char **)(c + 4892);
        if (p != 0)
            *(unsigned short *)(p + 52) &= 0xFFFE;
    }

    if (1) {
        char *c = LVL_5_FELTZIN_SYSTEM_Fea34650e_D_00189E20;
        if (*(unsigned char *)(c + 8884) == 1) {
            c = LVL_5_FELTZIN_SYSTEM_Fea34650e_D_00189E20;
            p = *(char **)(c + 6244);
            if (p != 0)
                *(unsigned short *)(p + 52) &= 0xFFFE;
        }
    }

    if (1) {
        char *c = LVL_5_FELTZIN_SYSTEM_Fea34650e_D_00189E20;
        if (*(short *)(c + 9468) != 0 || *(int *)(c + 8860) == 31) {
            c = LVL_5_FELTZIN_SYSTEM_Fea34650e_D_00189E20;
            p = *(char **)(c + 4880);
            if (p != 0)
                *(unsigned short *)(p + 52) |= 0x41;
            c = LVL_5_FELTZIN_SYSTEM_Fea34650e_D_00189E20;
            p = *(char **)(c + 4884);
            if (p != 0)
                *(unsigned short *)(p + 52) |= 0x41;
            c = LVL_5_FELTZIN_SYSTEM_Fea34650e_D_00189E20;
            p = *(char **)(c + 4892);
            if (p != 0)
                *(unsigned short *)(p + 52) |= 0x41;
        }
    }

    if (1) {
        char *c = LVL_5_FELTZIN_SYSTEM_Fea34650e_D_00189E20;
        if ((*(unsigned char *)(c + 8894) != 0 && *(int *)(c + 4680) == 10) ||
            *(unsigned char *)(c + 8895) != 0) {
            char *d = LVL_5_FELTZIN_SYSTEM_Fea34650e_D_00189E20;
            p = *(char **)(d + 4640);
            if (p != 0)
                *(unsigned short *)(p + 52) |= 0x41;
        }
    }
}
void LVL_5_FELTZIN_SYSTEM_FUN_0037D770(char *p)
{
    *(long long *)(p + 112) = 0;
    *(float *)(p + 8) = -1.0f;
    *(float *)(p + 24) = 1.0f;
    *(float *)(p + 40) = -1.0f;
    *(float *)(p + 56) = 1.0f;
    *(float *)(p + 4) = -1.0f;
    *(float *)(p + 36) = 1.0f;
    *(float *)(p + 52) = 1.0f;
    *(int *)(p + 0) = 0;
    *(int *)(p + 16) = 0;
    *(int *)(p + 32) = 0;
    *(int *)(p + 48) = 0;
    *(float *)(p + 12) = 1.0f;
    *(float *)(p + 28) = 1.0f;
    *(float *)(p + 44) = 1.0f;
    *(long long *)(p + 128) = 0x0000FF9000000260LL;
    *(float *)(p + 20) = -1.0f;
    *(float *)(p + 60) = 1.0f;
}
void LVL_5_FELTZIN_SYSTEM_FUN_003F28F8(char *p)
{
    *(long long *)(p + 112) = 0;
    *(float *)(p + 8) = -1.0f;
    *(float *)(p + 24) = 1.0f;
    *(float *)(p + 40) = -1.0f;
    *(float *)(p + 56) = 1.0f;
    *(float *)(p + 4) = -1.0f;
    *(float *)(p + 36) = 1.0f;
    *(float *)(p + 52) = 1.0f;
    *(int *)(p + 0) = 0;
    *(int *)(p + 16) = 0;
    *(int *)(p + 32) = 0;
    *(int *)(p + 48) = 0;
    *(float *)(p + 12) = 1.0f;
    *(float *)(p + 28) = 1.0f;
    *(float *)(p + 44) = 1.0f;
    *(long long *)(p + 128) = 0x0000FF9000000260LL;
    *(float *)(p + 20) = -1.0f;
    *(float *)(p + 60) = 1.0f;
}
void LVL_5_FELTZIN_SYSTEM_FUN_00416630(char *p)
{
    *(long long *)(p + 112) = 0;
    *(float *)(p + 8) = -1.0f;
    *(float *)(p + 24) = 1.0f;
    *(float *)(p + 40) = -1.0f;
    *(float *)(p + 56) = 1.0f;
    *(float *)(p + 4) = -1.0f;
    *(float *)(p + 36) = 1.0f;
    *(float *)(p + 52) = 1.0f;
    *(int *)(p + 0) = 0;
    *(int *)(p + 16) = 0;
    *(int *)(p + 32) = 0;
    *(int *)(p + 48) = 0;
    *(float *)(p + 12) = 1.0f;
    *(float *)(p + 28) = 1.0f;
    *(float *)(p + 44) = 1.0f;
    *(long long *)(p + 128) = 0x0000FF9000000260LL;
    *(float *)(p + 20) = -1.0f;
    *(float *)(p + 60) = 1.0f;
}
void LVL_5_FELTZIN_SYSTEM_FUN_0041D1B0(char *p)
{
    *(long long *)(p + 112) = 0;
    *(float *)(p + 8) = -1.0f;
    *(float *)(p + 24) = 1.0f;
    *(float *)(p + 40) = -1.0f;
    *(float *)(p + 56) = 1.0f;
    *(float *)(p + 4) = -1.0f;
    *(float *)(p + 36) = 1.0f;
    *(float *)(p + 52) = 1.0f;
    *(int *)(p + 0) = 0;
    *(int *)(p + 16) = 0;
    *(int *)(p + 32) = 0;
    *(int *)(p + 48) = 0;
    *(float *)(p + 12) = 1.0f;
    *(float *)(p + 28) = 1.0f;
    *(float *)(p + 44) = 1.0f;
    *(long long *)(p + 128) = 0x0000FF9000000260LL;
    *(float *)(p + 20) = -1.0f;
    *(float *)(p + 60) = 1.0f;
}
void LVL_5_FELTZIN_SYSTEM_FUN_00433400(char *p)
{
    *(long long *)(p + 112) = 0;
    *(float *)(p + 8) = -1.0f;
    *(float *)(p + 24) = 1.0f;
    *(float *)(p + 40) = -1.0f;
    *(float *)(p + 56) = 1.0f;
    *(float *)(p + 4) = -1.0f;
    *(float *)(p + 36) = 1.0f;
    *(float *)(p + 52) = 1.0f;
    *(int *)(p + 0) = 0;
    *(int *)(p + 16) = 0;
    *(int *)(p + 32) = 0;
    *(int *)(p + 48) = 0;
    *(float *)(p + 12) = 1.0f;
    *(float *)(p + 28) = 1.0f;
    *(float *)(p + 44) = 1.0f;
    *(long long *)(p + 128) = 0x0000FF9000000260LL;
    *(float *)(p + 20) = -1.0f;
    *(float *)(p + 60) = 1.0f;
}
extern char LVL_5_FELTZIN_SYSTEM_F0be97c76_D_00189E20[];

void LVL_5_FELTZIN_SYSTEM_FUN_002BF8F0(void)
{
    char *base = LVL_5_FELTZIN_SYSTEM_F0be97c76_D_00189E20;
    int i, j;

    for (i = 0; i < 7; i++) {
        for (j = 0; j < 3; j++) {
            char *p = *(char **)(base + 4640 + i * 80);

            if (j == 1)
                p = *(char **)(base + 4644 + i * 80);
            else if (j == 2)
                p = *(char **)(base + 4648 + i * 80);
            if (p != 0)
                *(long long *)(p + 56) = *(long long *)(*(char **)(base + 8848) + 56);
        }
    }
}

struct Slot { s32 w; s32 rest[4]; };
struct Table1 { char pad[19264]; struct Slot slots[48]; };
struct Table2 { char pad[52]; s32 slots[4]; };

extern struct Table1 LVL_5_FELTZIN_SYSTEM_Fee2b87d1_D_0014B540;
extern struct Table2 LVL_5_FELTZIN_SYSTEM_Fee2b87d1_D_00152CD0;

s32 LVL_5_FELTZIN_SYSTEM_FUN_0031D3C0(s32 value) {
    s32 i = 0;
    s32 *q;
    if (LVL_5_FELTZIN_SYSTEM_Fee2b87d1_D_0014B540.slots[0].w == value) goto after1;
    while (++i < 48) {
        if (LVL_5_FELTZIN_SYSTEM_Fee2b87d1_D_0014B540.slots[i].w == value) break;
    }
after1:
    if (i == 48) return 1;
    value = 0;
    if (LVL_5_FELTZIN_SYSTEM_Fee2b87d1_D_00152CD0.slots[0] == i) goto after2;
    while (++value < 3) {
        if (LVL_5_FELTZIN_SYSTEM_Fee2b87d1_D_00152CD0.slots[value] == i) break;
    }
after2:
    return value != 3;
}
extern int LVL_5_FELTZIN_SYSTEM_F954231c4_D_00231E40[][4];

int LVL_5_FELTZIN_SYSTEM_FUN_00392F70(int a0, int a1)
{
    int i;
    int r = 1;

    for (i = 0; i < 32; i++)
        if (LVL_5_FELTZIN_SYSTEM_F954231c4_D_00231E40[i][1] == a0 && LVL_5_FELTZIN_SYSTEM_F954231c4_D_00231E40[i][0] == a1) {
            r = 0;
            break;
        }
    return r;
}
/* Paired-strip packet emitter, 396 bytes, placed in levels/10_hrugis_cloud and
   levels/5_feltzin_system.  The body writes a 16-byte GIF header into the
   resident packet cursor (a small-data global), advances the cursor, then
   writes the tag words and two packed 64-bit strip descriptors.  The retail
   loads the cursor with LUI/LO and advances it through $gp, so the unit is
   compiled under the qualified small-data profile (-O2 -G8). */
extern int *LVL_5_FELTZIN_SYSTEM_Fa6a1a427_D_001B2C88 __attribute__((sda));
extern int LVL_5_FELTZIN_SYSTEM_Fa6a1a427_D_001A7350 __attribute__((sda));
extern int LVL_5_FELTZIN_SYSTEM_Fa6a1a427_D_001A7354 __attribute__((sda));

void LVL_5_FELTZIN_SYSTEM_FUN_003138E8(int a0, int a1, int a2, int a3, int p4, int p5)
{
    long long *q;

    *(int *)((char *)LVL_5_FELTZIN_SYSTEM_Fa6a1a427_D_001B2C88 + 0) = 0x10000003;
    *(int *)((char *)LVL_5_FELTZIN_SYSTEM_Fa6a1a427_D_001B2C88 + 4) = 0;
    *(int *)((char *)LVL_5_FELTZIN_SYSTEM_Fa6a1a427_D_001B2C88 + 8) = 0;
    *(int *)((char *)LVL_5_FELTZIN_SYSTEM_Fa6a1a427_D_001B2C88 + 12) = 0x50000003;
    q = (long long *)LVL_5_FELTZIN_SYSTEM_Fa6a1a427_D_001B2C88;
    LVL_5_FELTZIN_SYSTEM_Fa6a1a427_D_001B2C88 = (int *)((char *)q + 16);
    q[2] = 0x4400000000008001LL;
    q[3] = 17424;
    q[4] = 65;
    q[5] = p4;
#define LO_D0 (*(int *)((char *)&LVL_5_FELTZIN_SYSTEM_Fa6a1a427_D_001A7350 + 0))
#define HI_D4 (*(int *)((char *)&LVL_5_FELTZIN_SYSTEM_Fa6a1a427_D_001A7354 + 0))

    if (p5 != 0) {
        q[6] = (a0 + LO_D0 - 8)
             | ((long long)(a1 + HI_D4 - 8) << 16)
             | 0xFFFFF000000000LL;
        q[7] = (a2 + LO_D0 - 8)
             | ((long long)(a3 + HI_D4 - 8) << 16)
             | 0xFFFFF000000000LL;
    } else {
        q[6] = ((a0 << 4) + LO_D0 - 16)
             | ((long long)((a1 << 4) + HI_D4 - 16) << 16)
             | 0xFFFFF000000000LL;
        q[7] = ((a2 << 4) + LO_D0 - 16)
             | ((long long)((a3 << 4) + HI_D4 - 16) << 16)
             | 0xFFFFF000000000LL;
    }
    LVL_5_FELTZIN_SYSTEM_Fa6a1a427_D_001B2C88 = (int *)((char *)LVL_5_FELTZIN_SYSTEM_Fa6a1a427_D_001B2C88 + 48);
}
/* family 9bb235d69b795f0f - 372 bytes, 2 placements
   levels/10_hrugis_cloud @0x00316120, levels/5_feltzin_system @0x00313C08

   Builds one packet into the resident buffer: four-word header, advance the
   resident pointer by 16, three pinned 64-bit words plus the caller payload,
   then two packed 64-bit words selected by argument 7, then advance by 48.
   The | chain must be written unshifted-term first: that fixes both the
   accumulation register and the instruction interleaving (see SOLUTION.md).
*/

extern int *LVL_5_FELTZIN_SYSTEM_F9bb235d6_D_001B2C88 __attribute__((sda));
extern int LVL_5_FELTZIN_SYSTEM_F9bb235d6_D_001A7350 __attribute__((sda));
extern int LVL_5_FELTZIN_SYSTEM_F9bb235d6_D_001A7354 __attribute__((sda));

void LVL_5_FELTZIN_SYSTEM_FUN_00313C08(int a1, int a2, int a3, int a4,
                                       long long a5, int a6, int a7)
{
    *(int *)LVL_5_FELTZIN_SYSTEM_F9bb235d6_D_001B2C88 = 0x10000003;
    *(int *)((char *)LVL_5_FELTZIN_SYSTEM_F9bb235d6_D_001B2C88 + 4) = 0;
    *(int *)((char *)LVL_5_FELTZIN_SYSTEM_F9bb235d6_D_001B2C88 + 8) = 0;
    *(int *)((char *)LVL_5_FELTZIN_SYSTEM_F9bb235d6_D_001B2C88 + 12) = 0x50000003;
    {
        char *p = (char *)LVL_5_FELTZIN_SYSTEM_F9bb235d6_D_001B2C88;

        LVL_5_FELTZIN_SYSTEM_F9bb235d6_D_001B2C88 = (int *)(p + 16);
        *(long long *)(p + 16) = 0x4400000000008001LL;
        *(long long *)(p + 24) = 0x4410;
        *(long long *)(p + 32) = 0x46;
        *(long long *)(p + 40) = a5;
        if (a7 != 0) {
            *(long long *)(p + 48) = ((a1 + LVL_5_FELTZIN_SYSTEM_F9bb235d6_D_001A7350) - 8)
                                   | ((long long)((a2 + LVL_5_FELTZIN_SYSTEM_F9bb235d6_D_001A7354) - 8) << 16)
                                   | ((long long)a6 << 32);
            *(long long *)(p + 56) = ((a3 + LVL_5_FELTZIN_SYSTEM_F9bb235d6_D_001A7350) - 8)
                                   | ((long long)((a4 + LVL_5_FELTZIN_SYSTEM_F9bb235d6_D_001A7354) - 8) << 16)
                                   | ((long long)a6 << 32);
        } else {
            *(long long *)(p + 48) = (((a1 << 4) + LVL_5_FELTZIN_SYSTEM_F9bb235d6_D_001A7350) - 16)
                                   | ((long long)(((a2 << 4) + LVL_5_FELTZIN_SYSTEM_F9bb235d6_D_001A7354) - 16) << 16)
                                   | ((long long)a6 << 32);
            *(long long *)(p + 56) = (((a3 << 4) + LVL_5_FELTZIN_SYSTEM_F9bb235d6_D_001A7350) - 16)
                                   | ((long long)(((a4 << 4) + LVL_5_FELTZIN_SYSTEM_F9bb235d6_D_001A7354) - 16) << 16)
                                   | ((long long)a6 << 32);
        }
        LVL_5_FELTZIN_SYSTEM_F9bb235d6_D_001B2C88 = (int *)((char *)LVL_5_FELTZIN_SYSTEM_F9bb235d6_D_001B2C88 + 48);
    }
}
extern int *LVL_5_FELTZIN_SYSTEM_F060b9f20_D_001B2C88 __attribute__((sda));
extern int *LVL_5_FELTZIN_SYSTEM_F060b9f20_D_001B2AA0 __attribute__((sda));
extern int LVL_5_FELTZIN_SYSTEM_F060b9f20_D_001A72D0 __attribute__((sda));
extern int LVL_5_FELTZIN_SYSTEM_F060b9f20_D_001A72D4 __attribute__((sda));
extern int LVL_5_FELTZIN_SYSTEM_F060b9f20_D_001B1FBC __attribute__((sda));

typedef struct { int *saved; } SavedSlot;
extern SavedSlot LVL_5_FELTZIN_SYSTEM_F060b9f20_D_001B2AC0 __attribute__((sda));

typedef struct {
    char gap0[12];
    short count;
    char gap14[2];
    long long *table;
} ResidentTable;

void LVL_5_FELTZIN_SYSTEM_FUN_0036F538(void)
{
    ResidentTable *resident = (ResidentTable *)LVL_5_FELTZIN_SYSTEM_F060b9f20_D_001B2AA0;
    int *current = LVL_5_FELTZIN_SYSTEM_F060b9f20_D_001B2C88;
    int index;

    LVL_5_FELTZIN_SYSTEM_F060b9f20_D_001B2AC0.saved = current;
    LVL_5_FELTZIN_SYSTEM_F060b9f20_D_001B2C88 = (int *)((char *)current + 16);
    LVL_5_FELTZIN_SYSTEM_F060b9f20_D_001A72D0 = LVL_5_FELTZIN_SYSTEM_F060b9f20_D_001A72D4;
    LVL_5_FELTZIN_SYSTEM_F060b9f20_D_001B1FBC = 0;
    for (index = 0; index < resident->count; ++index)
        *(long long *)((char *)resident->table + index * 16) = 0;
}
extern unsigned char *LVL_5_FELTZIN_SYSTEM_Fe7046bc9_D_001B2520 __attribute__((sda));
extern unsigned char *LVL_5_FELTZIN_SYSTEM_Fe7046bc9_D_001B2524 __attribute__((sda));
extern unsigned int LVL_5_FELTZIN_SYSTEM_Fe7046bc9_D_001B2048 __attribute__((sda));
extern unsigned int LVL_5_FELTZIN_SYSTEM_Fe7046bc9_D_001B2440 __attribute__((sda));
void LVL_5_FELTZIN_SYSTEM_FUN_00328478(void)
{
    unsigned char *p = LVL_5_FELTZIN_SYSTEM_Fe7046bc9_D_001B2520;
    int seen = 0;
    unsigned int limit;
    LVL_5_FELTZIN_SYSTEM_Fe7046bc9_D_001B2440 = 0;
    while (p < LVL_5_FELTZIN_SYSTEM_Fe7046bc9_D_001B2524) {
        limit = LVL_5_FELTZIN_SYSTEM_Fe7046bc9_D_001B2048;
        do {
            if ((p[32] >= 254 && *(unsigned int *)(p + 160) <= limit) || seen) {
                LVL_5_FELTZIN_SYSTEM_Fe7046bc9_D_001B2440 = LVL_5_FELTZIN_SYSTEM_Fe7046bc9_D_001B2440 + 1;
                seen = (p[32] == 0xff) ? 1 : seen;
            }
            p += 256;
        } while (p < LVL_5_FELTZIN_SYSTEM_Fe7046bc9_D_001B2524);
    }
}
/* attempt 3: the project's existing (boot-qualified) spelling: -G0 profile plus
   an explicit `sda` attribute on the one resident word that retail addresses
   through $gp.  Used here as a control, to measure what -G8 changes. */

typedef struct __attribute__((packed)) { unsigned char mode[4]; } CdMode;

extern CdMode LVL_5_FELTZIN_SYSTEM_F1157be91_D_001A63E8;
extern unsigned char LVL_5_FELTZIN_SYSTEM_F1157be91_D_001A7900[] __attribute__((sda));
extern int LVL_5_FELTZIN_SYSTEM_F1157be91_D_001A7430[] __attribute__((sda));
extern int LVL_5_FELTZIN_SYSTEM_F1157be91_D_001A7434 __attribute__((sda));
extern int LVL_5_FELTZIN_SYSTEM_F1157be91_FUN_001334B8(int, int, int, CdMode *);
extern int LVL_5_FELTZIN_SYSTEM_F1157be91_FUN_00133230(void);
extern int LVL_5_FELTZIN_SYSTEM_F1157be91_FUN_00132028(void);

int LVL_5_FELTZIN_SYSTEM_FUN_00340DA8(int a0, int a1, int a2) {
    CdMode mode = LVL_5_FELTZIN_SYSTEM_F1157be91_D_001A63E8;
    mode.mode[1] = LVL_5_FELTZIN_SYSTEM_F1157be91_D_001A7900[0];
    LVL_5_FELTZIN_SYSTEM_F1157be91_D_001A7430[0] = 0;
    LVL_5_FELTZIN_SYSTEM_F1157be91_D_001A7434 = 0;
    LVL_5_FELTZIN_SYSTEM_F1157be91_FUN_001334B8(a1, a2, a0, &mode);
    LVL_5_FELTZIN_SYSTEM_F1157be91_FUN_00133230();
    LVL_5_FELTZIN_SYSTEM_F1157be91_FUN_00132028();
    return 1;
}
typedef struct {
    u8 field00[0x218]; signed short field218; u8 field21A[0x12e];
    signed short field348; u8 field34A[4]; signed short field34E;
    u8 field350[0x1147]; u8 field1497; u8 field1498[2]; u8 field149A;
    u8 field149B[0xdf9]; s32 field2294;
} NativeModeResident;
extern NativeModeResident LVL_5_FELTZIN_SYSTEM_F4e5bde81_D_00189E20;
extern s32 LVL_5_FELTZIN_SYSTEM_F4e5bde81_D_001A8FF0 __attribute__((sda));
extern volatile u8 LVL_5_FELTZIN_SYSTEM_F4e5bde81_D_001A7B08[4] __attribute__((sda));
extern s32 LVL_5_FELTZIN_SYSTEM_F4e5bde81_D_001A8FF4 __attribute__((sda));
s32 LVL_5_FELTZIN_SYSTEM_FUN_002EBC80(void) {
    s32 result = LVL_5_FELTZIN_SYSTEM_F4e5bde81_D_00189E20.field348;
    if (LVL_5_FELTZIN_SYSTEM_F4e5bde81_D_001A8FF0 != 0 && LVL_5_FELTZIN_SYSTEM_F4e5bde81_D_001A8FF4 == 0) result = 2;
    if (LVL_5_FELTZIN_SYSTEM_F4e5bde81_D_001A8FF4 != 0 || LVL_5_FELTZIN_SYSTEM_F4e5bde81_D_00189E20.field2294 == 59 ||
        (LVL_5_FELTZIN_SYSTEM_F4e5bde81_D_00189E20.field2294 == 110 && LVL_5_FELTZIN_SYSTEM_F4e5bde81_D_00189E20.field149A == 0) ||
        LVL_5_FELTZIN_SYSTEM_F4e5bde81_D_00189E20.field2294 == 109 || LVL_5_FELTZIN_SYSTEM_F4e5bde81_D_00189E20.field218 != 0 ||
        (LVL_5_FELTZIN_SYSTEM_F4e5bde81_D_00189E20.field1497 != 0 && LVL_5_FELTZIN_SYSTEM_F4e5bde81_D_001A7B08[3] != 0 &&
         LVL_5_FELTZIN_SYSTEM_F4e5bde81_D_00189E20.field2294 == 0 && LVL_5_FELTZIN_SYSTEM_F4e5bde81_D_00189E20.field34E < 4)) result = 1;
    if (result == 1 && LVL_5_FELTZIN_SYSTEM_F4e5bde81_D_00189E20.field149A != 0) result = 0;
    return result;
}
/* family 695584ed7d3e53db - 368 bytes, 2 placements
   levels/10_hrugis_cloud @0x00315C90, levels/5_feltzin_system @0x00313778

   Two-pass packet emitter.  On the "first" path (p5 == 0) it writes a four-word
   header into the resident packet cursor (a small-data global), points s0 at the
   payload area and advances the cursor by 112 bytes; on the other path s0 is a
   local scratch buffer.  An eight-argument helper then fills the payload, and a
   second pass emits the tag plus payload word or delegates to two helpers.

   The cursor is addressed through $gp at the two delay-slot sites only, so the
   declaration carries the `sda` attribute and the unit is compiled -G0. */

extern int *LVL_5_FELTZIN_SYSTEM_F695584ed_D_001B2C88 __attribute__((sda));

extern void LVL_5_FELTZIN_SYSTEM_F695584ed_FUN_00126288(void *p, int a1, int a2, int a3, int a4, int a5, int a6, int a7);
extern void LVL_5_FELTZIN_SYSTEM_F695584ed_FUN_0011AEA0(int a0);
extern void LVL_5_FELTZIN_SYSTEM_F695584ed_FUN_001265B0(void *a0, void *a1);

void LVL_5_FELTZIN_SYSTEM_FUN_00313778(int a0, int a1, int a2, int a3, int p4, int p5)
{
    int t5 = a3;
    int n = (1 << t5) >> 6;
    int stride = 1 << (t5 + p4 - 4);
    int *s0;
    char buf[96];

    if (n <= 0) {
        n = 1;
    }
    if (p5 == 0) {
        char *q;

        *(int *)((char *)LVL_5_FELTZIN_SYSTEM_F695584ed_D_001B2C88 + 0) = 0x10000006;
        *(int *)((char *)LVL_5_FELTZIN_SYSTEM_F695584ed_D_001B2C88 + 4) = 0;
        *(int *)((char *)LVL_5_FELTZIN_SYSTEM_F695584ed_D_001B2C88 + 8) = 0;
        *(int *)((char *)LVL_5_FELTZIN_SYSTEM_F695584ed_D_001B2C88 + 12) = 0x50000006;
        q = (char *)LVL_5_FELTZIN_SYSTEM_F695584ed_D_001B2C88;
        s0 = (int *)(q + 16);
        LVL_5_FELTZIN_SYSTEM_F695584ed_D_001B2C88 = (int *)(q + 112);
    } else {
        s0 = (int *)buf;
    }
    LVL_5_FELTZIN_SYSTEM_F695584ed_FUN_00126288(s0, (short)a1, (short)n, (short)a2, 0, 0, (short)(1 << t5), (short)(1 << p4));
    if (p5 == 0) {
        *(int *)((char *)LVL_5_FELTZIN_SYSTEM_F695584ed_D_001B2C88 + 0) = 0x30000000 | stride;
        *(int *)((char *)LVL_5_FELTZIN_SYSTEM_F695584ed_D_001B2C88 + 4) = a0;
        *(int *)((char *)LVL_5_FELTZIN_SYSTEM_F695584ed_D_001B2C88 + 8) = 0;
        *(int *)((char *)LVL_5_FELTZIN_SYSTEM_F695584ed_D_001B2C88 + 12) = 0x50000000 | stride;
        LVL_5_FELTZIN_SYSTEM_F695584ed_D_001B2C88 = (int *)((char *)LVL_5_FELTZIN_SYSTEM_F695584ed_D_001B2C88 + 16);
    } else {
        LVL_5_FELTZIN_SYSTEM_F695584ed_FUN_0011AEA0(0);
        LVL_5_FELTZIN_SYSTEM_F695584ed_FUN_001265B0(s0, (void *)a0);
    }
}
/* v2: guard reads p->count, loop counter is a second read (CSE -> copy). */
struct Elem {
    unsigned int f0;
    unsigned char pad0[31];
    unsigned char f35;
    unsigned char pad1[12];
    unsigned int f48;
    unsigned char pad2[28];
};
struct Node {
    struct Elem *elems;
    int count;
};
extern struct Node LVL_5_FELTZIN_SYSTEM_F9328256b_D_00226A00 __attribute__((nosda));
extern short LVL_5_FELTZIN_SYSTEM_F9328256b_D_00226700[][2];

void LVL_5_FELTZIN_SYSTEM_FUN_0037E418(void)
{
    struct Node *p = &LVL_5_FELTZIN_SYSTEM_F9328256b_D_00226A00;

    if (p->elems != 0) {
        do {
            struct Elem *e = p->elems;

            if (p->count > 0) {
                int n = p->count;

                do {
                    short *t = LVL_5_FELTZIN_SYSTEM_F9328256b_D_00226700[e->f35];
                    if (t[0] != 0) e->f0 = (e->f0 & 0xFFFFC000u) | (unsigned int)t[0];
                    if (t[1] != 0) e->f48 = (e->f48 & 0xFFFFC000u) | (unsigned int)t[1];
                    e++;
                } while (--n);
            }
            p++;
        } while (p->elems != 0);
    }
}
extern char *LVL_5_FELTZIN_SYSTEM_F8aa1a3c4_D_001B2C88 __attribute__((sda));
extern char LVL_5_FELTZIN_SYSTEM_F8aa1a3c4_D_001A6D40[];
extern char LVL_5_FELTZIN_SYSTEM_F8aa1a3c4_D_001A6E90[];

void LVL_5_FELTZIN_SYSTEM_FUN_00308A60(int a0)
{
    if (LVL_5_FELTZIN_SYSTEM_F8aa1a3c4_D_001B2C88 != 0) {
        *(int *)LVL_5_FELTZIN_SYSTEM_F8aa1a3c4_D_001B2C88 = 0x30000015;
        if (a0 == 0) {
            *(int *)(LVL_5_FELTZIN_SYSTEM_F8aa1a3c4_D_001B2C88 + 4) = (int)LVL_5_FELTZIN_SYSTEM_F8aa1a3c4_D_001A6D40;
        } else {
            *(int *)(LVL_5_FELTZIN_SYSTEM_F8aa1a3c4_D_001B2C88 + 4) = (int)LVL_5_FELTZIN_SYSTEM_F8aa1a3c4_D_001A6E90;
        }
        *(int *)(LVL_5_FELTZIN_SYSTEM_F8aa1a3c4_D_001B2C88 + 8) = 0;
        *(int *)(LVL_5_FELTZIN_SYSTEM_F8aa1a3c4_D_001B2C88 + 12) = 0x50000015;
        LVL_5_FELTZIN_SYSTEM_F8aa1a3c4_D_001B2C88 = LVL_5_FELTZIN_SYSTEM_F8aa1a3c4_D_001B2C88 + 16;
    }
}
void LVL_5_FELTZIN_SYSTEM_FUN_00337E60(int param_1, short *param_2, short param_3)
{
    int i;

    param_1 = (param_1 - *(int *)0x001B251C) << 8 >> 16;
    for (i = 1; i <= param_2[0]; i++) {
        if (param_2[i] == param_1) return;
    }
    if (param_2[0] < param_3) {
        param_2[0] = param_2[0] + 1;
        param_2[param_2[0]] = param_1;
    }
}
/* Family e8702d836bd3adba (120 B, 2 placements): call every registered
 * callback with its paired argument, bounded by a resident count word.
 *
 * The three resident globals are reached with `lui`+`lw` / `lui`+`addiu`
 * pairs that the ASSEMBLER macro expands from a single RTL insn; this only
 * happens when the externs carry the `sda` attribute (SYMBOL_REF_FLAG), which
 * suppresses gcc's HIGH/LO_SUM address split.  Without it the compiler keeps
 * the `%hi` in an extra callee-saved register and the body is 3 words long.
 */
typedef void (*fn_t)(int);

extern int LVL_5_FELTZIN_SYSTEM_Fe8702d83_D_001B1FF8 __attribute__((sda));   /* resident callback count */
extern fn_t LVL_5_FELTZIN_SYSTEM_Fe8702d83_D_001B1FD8[] __attribute__((sda)); /* callback table        */
extern int LVL_5_FELTZIN_SYSTEM_Fe8702d83_D_001B1FE8[] __attribute__((sda));  /* argument table        */

void LVL_5_FELTZIN_SYSTEM_FUN_002FF7B0(void) {
    int i;
    for (i = 0; i < LVL_5_FELTZIN_SYSTEM_Fe8702d83_D_001B1FF8; i++) {
        LVL_5_FELTZIN_SYSTEM_Fe8702d83_D_001B1FD8[i](LVL_5_FELTZIN_SYSTEM_Fe8702d83_D_001B1FE8[i]);
    }
}
/* Family 7a3a32da2b27da0d — 364 bytes, a block loop that builds two four-word
   GS packets per iteration and calls the measured SDK helper at 0x00126288
   between them.

   -G0 promotion (agent f02, 2026-10-07): the retail body reaches the resident
   write pointer at 0x001B2C88 ten times through the one-instruction small-data
   form (absolute `lui`+`lw` in ordinary flow, the single `$gp` form in the
   `jal` delay slot).  Under -G8 that model is free; under -G0 cc1 needs the
   measured `sda` attribute, otherwise it emits the explicit two-instruction
   pair and shifts register allocation.  Nothing else about the body changed. */

extern int *LVL_5_FELTZIN_SYSTEM_F7a3a32da_D_001B2C88 __attribute__((sda));

extern void LVL_5_FELTZIN_SYSTEM_F7a3a32da_FUN_00126288(int *p, int a, int b, int c, int d, int e, int f, int g);

void LVL_5_FELTZIN_SYSTEM_FUN_00390B28(char *dst, int src, int size)
{
    int count = (size + 16383) & -16384;
    int si = 0;
    int di = 0;
    int v;

    while (count > 0) {
        *(int *)LVL_5_FELTZIN_SYSTEM_F7a3a32da_D_001B2C88 = 0x10000006;
        *(int *)((char *)LVL_5_FELTZIN_SYSTEM_F7a3a32da_D_001B2C88 + 4) = 0;
        *(int *)((char *)LVL_5_FELTZIN_SYSTEM_F7a3a32da_D_001B2C88 + 8) = 0;
        *(int *)((char *)LVL_5_FELTZIN_SYSTEM_F7a3a32da_D_001B2C88 + 12) = 0x50000006;
        LVL_5_FELTZIN_SYSTEM_F7a3a32da_D_001B2C88 = (int *)((char *)LVL_5_FELTZIN_SYSTEM_F7a3a32da_D_001B2C88 + 16);
        v = (src + si) << 8;
        v = v >> 16;
        LVL_5_FELTZIN_SYSTEM_F7a3a32da_FUN_00126288(LVL_5_FELTZIN_SYSTEM_F7a3a32da_D_001B2C88, v, 1, 1, 0, 0, 64, 64);
        LVL_5_FELTZIN_SYSTEM_F7a3a32da_D_001B2C88 = (int *)((char *)LVL_5_FELTZIN_SYSTEM_F7a3a32da_D_001B2C88 + 96);
        *(int *)LVL_5_FELTZIN_SYSTEM_F7a3a32da_D_001B2C88 = 0x30000300;
        *(int *)((char *)LVL_5_FELTZIN_SYSTEM_F7a3a32da_D_001B2C88 + 4) = (int)(dst + di);
        *(int *)((char *)LVL_5_FELTZIN_SYSTEM_F7a3a32da_D_001B2C88 + 8) = 0;
        *(int *)((char *)LVL_5_FELTZIN_SYSTEM_F7a3a32da_D_001B2C88 + 12) = 0x50000300;
        si += 16384;
        di += 12288;
        count -= 16384;
        LVL_5_FELTZIN_SYSTEM_F7a3a32da_D_001B2C88 = (int *)((char *)LVL_5_FELTZIN_SYSTEM_F7a3a32da_D_001B2C88 + 16);
    }
}
/* Append one 16-byte record to the level's queue at 0x225FD0 and submit it
   through the DMA helper LVL_5_FELTZIN_SYSTEM_F0451f37d_FUN_0011AFE0.  The four queue globals live in a
   0x38-byte state block based at 0x1A7240; because they are reached with a
   constant offset from that base (a CONST address), cc1 gives the store a
   two-instruction length and refuses to drop it into the branch delay slot,
   which is what the retail body does as well.  */

typedef struct {
    int start;      /* +0x00 -> 0x1A7240 */
    int end;        /* +0x04 -> 0x1A7244 */
    int pad[10];    /* +0x08 .. +0x2F */
    int cursor;     /* +0x30 -> 0x1A7270 */
    int count;      /* +0x34 -> 0x1A7274 */
} LevelQueue0451f37d;

extern LevelQueue0451f37d LVL_5_FELTZIN_SYSTEM_F0451f37d_D_001A7240 __attribute__((sda));
extern char LVL_5_FELTZIN_SYSTEM_F0451f37d_D_00225FD0[];
extern int LVL_5_FELTZIN_SYSTEM_F0451f37d_FUN_0011AFE0(int *dma, int flag);

int LVL_5_FELTZIN_SYSTEM_FUN_0037DDB0(int p0, int p1, int p2, int p3)
{
    int args[4];
    int n, k;

    if (LVL_5_FELTZIN_SYSTEM_F0451f37d_D_001A7240.end - (LVL_5_FELTZIN_SYSTEM_F0451f37d_D_001A7240.cursor - LVL_5_FELTZIN_SYSTEM_F0451f37d_D_001A7240.start) < p2 * 16)
        return -1;
    if (LVL_5_FELTZIN_SYSTEM_F0451f37d_D_001A7240.count == 64)
        return -2;

    args[0] = p0;
    args[1] = LVL_5_FELTZIN_SYSTEM_F0451f37d_D_001A7240.cursor;
    args[2] = p1 * 16;
    args[3] = 0;
    LVL_5_FELTZIN_SYSTEM_F0451f37d_FUN_0011AFE0(args, 1);

    n = LVL_5_FELTZIN_SYSTEM_F0451f37d_D_001A7240.count;
    k = n;
    n = n + 1;
    LVL_5_FELTZIN_SYSTEM_F0451f37d_D_001A7240.count = n;
    *(int *)(LVL_5_FELTZIN_SYSTEM_F0451f37d_D_00225FD0 + k * 16) = LVL_5_FELTZIN_SYSTEM_F0451f37d_D_001A7240.cursor;
    *(int *)(LVL_5_FELTZIN_SYSTEM_F0451f37d_D_00225FD0 + k * 16 + 4) = p2;
    *(int *)(LVL_5_FELTZIN_SYSTEM_F0451f37d_D_00225FD0 + k * 16 + 8) = p3;
    LVL_5_FELTZIN_SYSTEM_F0451f37d_D_001A7240.cursor = LVL_5_FELTZIN_SYSTEM_F0451f37d_D_001A7240.cursor + p2 * 16;
    return k;
}


/* Measured partial layouts; original type and game roles are unknown. */
typedef unsigned int Rac2Native_abf21065e887d7a9_FallbackU32;

typedef struct Rac2Native_abf21065e887d7a9_FallbackPredicate112Layout {
    unsigned char unknown_00[0x90];
    Rac2Native_abf21065e887d7a9_FallbackU32 flags_90;
    Rac2Native_abf21065e887d7a9_FallbackU32 unknown_94;
    Rac2Native_abf21065e887d7a9_FallbackU32 flags_98;
} Rac2Native_abf21065e887d7a9_FallbackPredicate112Layout;


extern Rac2Native_abf21065e887d7a9_FallbackPredicate112Layout LVL_5_FELTZIN_SYSTEM_Fabf21065e887d7a9_AT003272E8_ROLE00;

int LVL_5_FELTZIN_SYSTEM_FUN_003272E8(void)
{
    if ((LVL_5_FELTZIN_SYSTEM_Fabf21065e887d7a9_AT003272E8_ROLE00.flags_90 & 0x10000u) == 0 &&
        (LVL_5_FELTZIN_SYSTEM_Fabf21065e887d7a9_AT003272E8_ROLE00.flags_98 & 0x04000000u) != 0)
        return 0;
    if ((LVL_5_FELTZIN_SYSTEM_Fabf21065e887d7a9_AT003272E8_ROLE00.flags_90 & 0x10000u) != 0 &&
        (LVL_5_FELTZIN_SYSTEM_Fabf21065e887d7a9_AT003272E8_ROLE00.flags_98 & 0x04000000u) != 0)
        return 1;
    return 0;
}


/* Measured partial layouts; original type and game roles are unknown. */
typedef struct Rac2Native_5b4b17178a13f443_SmallSlotReset128Owner {
    unsigned char prefix_00[0x120];
    void *slots_120[10];
    int count_148;
    int active_14c;
} Rac2Native_5b4b17178a13f443_SmallSlotReset128Owner;


extern void LVL_5_FELTZIN_SYSTEM_F5b4b17178a13f443_AT0033A3B0_ROLE00(void *object);

void LVL_5_FELTZIN_SYSTEM_FUN_0033A3B0(Rac2Native_5b4b17178a13f443_SmallSlotReset128Owner *owner)
{
    int index;
    if (owner->active_14c != 0) {
        for (index = 0; index < owner->count_148; ++index) {
            if (owner->slots_120[index] != 0) {
                LVL_5_FELTZIN_SYSTEM_F5b4b17178a13f443_AT0033A3B0_ROLE00(owner->slots_120[index]);
                owner->slots_120[index] = 0;
            }
        }
        owner->active_14c = 0;
    }
}


/* Measured partial layouts; original type and game roles are unknown. */
typedef struct Rac2Native_acdcf1600d770d3b_ScalarConfigure116State {
    unsigned char prefix_00[0x60];
    unsigned int value_60;
    int value_64;
    unsigned char selector_68;
    unsigned char axis_69;
    unsigned char mode_6a;
    unsigned char dirty_6b;
} Rac2Native_acdcf1600d770d3b_ScalarConfigure116State;


extern Rac2Native_acdcf1600d770d3b_ScalarConfigure116State LVL_5_FELTZIN_SYSTEM_Facdcf1600d770d3b_AT00371D98_ROLE00[];

void LVL_5_FELTZIN_SYSTEM_FUN_00371D98(unsigned int value, unsigned int selector, int other,
                        unsigned int axis, unsigned int mode)
{
    Rac2Native_acdcf1600d770d3b_ScalarConfigure116State *state = LVL_5_FELTZIN_SYSTEM_Facdcf1600d770d3b_AT00371D98_ROLE00;
    state->value_60 = value;
    if (state->selector_68 != selector) {
        state->dirty_6b |= 1;
        state->selector_68 = selector;
    }
    if (state->value_64 != other) {
        state->dirty_6b |= 4;
        state->value_64 = other;
    }
    if (state->axis_69 != axis || state->mode_6a != mode) {
        state->dirty_6b |= 2;
        state->axis_69 = axis;
        state->mode_6a = mode;
    }
}


/* Measured partial layouts; original type and game roles are unknown. */
typedef struct Rac2Native_b1b523716b470b36_FamilyNative192Vector {
    float x;
    float y;
    float z;
    float w;
} Rac2Native_b1b523716b470b36_FamilyNative192Vector;


extern void LVL_5_FELTZIN_SYSTEM_Fb1b523716b470b36_AT0039DAA8_ROLE01(Rac2Native_b1b523716b470b36_FamilyNative192Vector *out,
    const Rac2Native_b1b523716b470b36_FamilyNative192Vector *first, const Rac2Native_b1b523716b470b36_FamilyNative192Vector *second);
extern void LVL_5_FELTZIN_SYSTEM_Fb1b523716b470b36_AT0039DAA8_ROLE00(Rac2Native_b1b523716b470b36_FamilyNative192Vector *out,
    const Rac2Native_b1b523716b470b36_FamilyNative192Vector *first, const Rac2Native_b1b523716b470b36_FamilyNative192Vector *second);

void LVL_5_FELTZIN_SYSTEM_FUN_0039DAA8(void *object)
{
    Rac2Native_b1b523716b470b36_FamilyNative192Vector input;
    Rac2Native_b1b523716b470b36_FamilyNative192Vector output;
    char *base = (char *)object;
    char *state;
    char *source;
    char *kind;
    char *extra;

    input.w = 0.0f;
    state = *(char **)(base + 0x68);
    input.x = *(float *)(state + 0x74);
    input.y = *(float *)(state + 0x78);
    input.z = *(float *)(state + 0x7c);
    source = *(char **)(state + 0x70);
    LVL_5_FELTZIN_SYSTEM_Fb1b523716b470b36_AT0039DAA8_ROLE01(&output,
        (const Rac2Native_b1b523716b470b36_FamilyNative192Vector *)(source + 0x10), &input);
    LVL_5_FELTZIN_SYSTEM_Fb1b523716b470b36_AT0039DAA8_ROLE00((Rac2Native_b1b523716b470b36_FamilyNative192Vector *)(base + 0x10), &output,
        (const Rac2Native_b1b523716b470b36_FamilyNative192Vector *)(base + 0x10));
    source = *(char **)(state + 0x70);
    *(float *)(state + 0x74) = *(float *)(source + 0x10);
    *(float *)(state + 0x78) = *(float *)(source + 0x14);
    *(float *)(state + 0x7c) = *(float *)(source + 0x18);
    kind = *(char **)(source + 0x24);
    if (*(short *)(kind + 0x46) == 0x12) {
        extra = *(char **)(source + 0x68);
        if (*(unsigned char *)(extra + 0x14) == 0) {
            *(unsigned char *)(base + 0x20) = 7;
        }
    }
}


extern void LVL_5_FELTZIN_SYSTEM_Fb1b523716b470b36_AT003A0550_ROLE01(Rac2Native_b1b523716b470b36_FamilyNative192Vector *out,
    const Rac2Native_b1b523716b470b36_FamilyNative192Vector *first, const Rac2Native_b1b523716b470b36_FamilyNative192Vector *second);
extern void LVL_5_FELTZIN_SYSTEM_Fb1b523716b470b36_AT003A0550_ROLE00(Rac2Native_b1b523716b470b36_FamilyNative192Vector *out,
    const Rac2Native_b1b523716b470b36_FamilyNative192Vector *first, const Rac2Native_b1b523716b470b36_FamilyNative192Vector *second);

void LVL_5_FELTZIN_SYSTEM_FUN_003A0550(void *object)
{
    Rac2Native_b1b523716b470b36_FamilyNative192Vector input;
    Rac2Native_b1b523716b470b36_FamilyNative192Vector output;
    char *base = (char *)object;
    char *state;
    char *source;
    char *kind;
    char *extra;

    input.w = 0.0f;
    state = *(char **)(base + 0x68);
    input.x = *(float *)(state + 0x74);
    input.y = *(float *)(state + 0x78);
    input.z = *(float *)(state + 0x7c);
    source = *(char **)(state + 0x70);
    LVL_5_FELTZIN_SYSTEM_Fb1b523716b470b36_AT003A0550_ROLE01(&output,
        (const Rac2Native_b1b523716b470b36_FamilyNative192Vector *)(source + 0x10), &input);
    LVL_5_FELTZIN_SYSTEM_Fb1b523716b470b36_AT003A0550_ROLE00((Rac2Native_b1b523716b470b36_FamilyNative192Vector *)(base + 0x10), &output,
        (const Rac2Native_b1b523716b470b36_FamilyNative192Vector *)(base + 0x10));
    source = *(char **)(state + 0x70);
    *(float *)(state + 0x74) = *(float *)(source + 0x10);
    *(float *)(state + 0x78) = *(float *)(source + 0x14);
    *(float *)(state + 0x7c) = *(float *)(source + 0x18);
    kind = *(char **)(source + 0x24);
    if (*(short *)(kind + 0x46) == 0x12) {
        extra = *(char **)(source + 0x68);
        if (*(unsigned char *)(extra + 0x14) == 0) {
            *(unsigned char *)(base + 0x20) = 7;
        }
    }
}


/* Measured partial layouts; original type and game roles are unknown. */
typedef struct Rac2Native_9cdc323a4d0c2fbd_AnalysisOwner {
    unsigned char prefix_00[0x68];
    void *context_68;
} Rac2Native_9cdc323a4d0c2fbd_AnalysisOwner;

typedef struct Rac2Native_9cdc323a4d0c2fbd_AnalysisConditionalContext {
    unsigned char prefix_00[0x10];
    float vector_10[4];
    unsigned int field_20;
    unsigned int active_24;
} Rac2Native_9cdc323a4d0c2fbd_AnalysisConditionalContext;


extern void LVL_5_FELTZIN_SYSTEM_F9cdc323a4d0c2fbd_AT003AE6A8_ROLE00(float scale, Rac2Native_9cdc323a4d0c2fbd_AnalysisConditionalContext *context,
                                    float *vector, int mode);

void LVL_5_FELTZIN_SYSTEM_FUN_003AE6A8(Rac2Native_9cdc323a4d0c2fbd_AnalysisOwner *owner)
{
    Rac2Native_9cdc323a4d0c2fbd_AnalysisConditionalContext *context = owner->context_68;
    if (context->active_24 != 0) {
        LVL_5_FELTZIN_SYSTEM_F9cdc323a4d0c2fbd_AT003AE6A8_ROLE00(1.0f, context, context->vector_10, 0);
    }
}


extern void LVL_5_FELTZIN_SYSTEM_F9cdc323a4d0c2fbd_AT003B3188_ROLE00(float scale, Rac2Native_9cdc323a4d0c2fbd_AnalysisConditionalContext *context,
                                    float *vector, int mode);

void LVL_5_FELTZIN_SYSTEM_FUN_003B3188(Rac2Native_9cdc323a4d0c2fbd_AnalysisOwner *owner)
{
    Rac2Native_9cdc323a4d0c2fbd_AnalysisConditionalContext *context = owner->context_68;
    if (context->active_24 != 0) {
        LVL_5_FELTZIN_SYSTEM_F9cdc323a4d0c2fbd_AT003B3188_ROLE00(1.0f, context, context->vector_10, 0);
    }
}


/* Measured partial layouts; original type and game roles are unknown. */
typedef struct Rac2Native_86f665335d9cb905_AnalysisOwner {
    unsigned char prefix_00[0x68];
    void *context_68;
} Rac2Native_86f665335d9cb905_AnalysisOwner;


extern void LVL_5_FELTZIN_SYSTEM_F86f665335d9cb905_AT003CEF80_ROLE00(Rac2Native_86f665335d9cb905_AnalysisOwner *owner, void *context);

void LVL_5_FELTZIN_SYSTEM_FUN_003CEF80(Rac2Native_86f665335d9cb905_AnalysisOwner *owner)
{
    LVL_5_FELTZIN_SYSTEM_F86f665335d9cb905_AT003CEF80_ROLE00(owner, owner->context_68);
}


extern void LVL_5_FELTZIN_SYSTEM_F9cdc323a4d0c2fbd_AT003D66F0_ROLE00(float scale, Rac2Native_9cdc323a4d0c2fbd_AnalysisConditionalContext *context,
                                    float *vector, int mode);

void LVL_5_FELTZIN_SYSTEM_FUN_003D66F0(Rac2Native_9cdc323a4d0c2fbd_AnalysisOwner *owner)
{
    Rac2Native_9cdc323a4d0c2fbd_AnalysisConditionalContext *context = owner->context_68;
    if (context->active_24 != 0) {
        LVL_5_FELTZIN_SYSTEM_F9cdc323a4d0c2fbd_AT003D66F0_ROLE00(1.0f, context, context->vector_10, 0);
    }
}


extern void LVL_5_FELTZIN_SYSTEM_F9cdc323a4d0c2fbd_AT003DBD68_ROLE00(float scale, Rac2Native_9cdc323a4d0c2fbd_AnalysisConditionalContext *context,
                                    float *vector, int mode);

void LVL_5_FELTZIN_SYSTEM_FUN_003DBD68(Rac2Native_9cdc323a4d0c2fbd_AnalysisOwner *owner)
{
    Rac2Native_9cdc323a4d0c2fbd_AnalysisConditionalContext *context = owner->context_68;
    if (context->active_24 != 0) {
        LVL_5_FELTZIN_SYSTEM_F9cdc323a4d0c2fbd_AT003DBD68_ROLE00(1.0f, context, context->vector_10, 0);
    }
}


extern void LVL_5_FELTZIN_SYSTEM_F9cdc323a4d0c2fbd_AT003F2D20_ROLE00(float scale, Rac2Native_9cdc323a4d0c2fbd_AnalysisConditionalContext *context,
                                    float *vector, int mode);

void LVL_5_FELTZIN_SYSTEM_FUN_003F2D20(Rac2Native_9cdc323a4d0c2fbd_AnalysisOwner *owner)
{
    Rac2Native_9cdc323a4d0c2fbd_AnalysisConditionalContext *context = owner->context_68;
    if (context->active_24 != 0) {
        LVL_5_FELTZIN_SYSTEM_F9cdc323a4d0c2fbd_AT003F2D20_ROLE00(1.0f, context, context->vector_10, 0);
    }
}


extern void LVL_5_FELTZIN_SYSTEM_F9cdc323a4d0c2fbd_AT003F60F0_ROLE00(float scale, Rac2Native_9cdc323a4d0c2fbd_AnalysisConditionalContext *context,
                                    float *vector, int mode);

void LVL_5_FELTZIN_SYSTEM_FUN_003F60F0(Rac2Native_9cdc323a4d0c2fbd_AnalysisOwner *owner)
{
    Rac2Native_9cdc323a4d0c2fbd_AnalysisConditionalContext *context = owner->context_68;
    if (context->active_24 != 0) {
        LVL_5_FELTZIN_SYSTEM_F9cdc323a4d0c2fbd_AT003F60F0_ROLE00(1.0f, context, context->vector_10, 0);
    }
}


extern void LVL_5_FELTZIN_SYSTEM_F9cdc323a4d0c2fbd_AT00404F48_ROLE00(float scale, Rac2Native_9cdc323a4d0c2fbd_AnalysisConditionalContext *context,
                                    float *vector, int mode);

void LVL_5_FELTZIN_SYSTEM_FUN_00404F48(Rac2Native_9cdc323a4d0c2fbd_AnalysisOwner *owner)
{
    Rac2Native_9cdc323a4d0c2fbd_AnalysisConditionalContext *context = owner->context_68;
    if (context->active_24 != 0) {
        LVL_5_FELTZIN_SYSTEM_F9cdc323a4d0c2fbd_AT00404F48_ROLE00(1.0f, context, context->vector_10, 0);
    }
}


/* Measured partial layouts; original type and game roles are unknown. */
typedef struct Rac2Native_6af85cabb56d3b41_SmallConditional52Owner {
    unsigned char unknown_00[0x7d];
    unsigned char value_7d;
    short value_7e;
    unsigned char unknown_80[6];
    short identity_86;
} Rac2Native_6af85cabb56d3b41_SmallConditional52Owner;

typedef struct Rac2Native_6af85cabb56d3b41_SmallConditional52Global {
    unsigned char unknown_00[0x2294];
    int mode_2294;
    unsigned char unknown_2298[0x208];
    int identity_24a0;
} Rac2Native_6af85cabb56d3b41_SmallConditional52Global;


extern Rac2Native_6af85cabb56d3b41_SmallConditional52Global LVL_5_FELTZIN_SYSTEM_F6af85cabb56d3b41_AT004414F0_ROLE00;

void LVL_5_FELTZIN_SYSTEM_FUN_004414F0(Rac2Native_6af85cabb56d3b41_SmallConditional52Owner *owner)
{
    if (LVL_5_FELTZIN_SYSTEM_F6af85cabb56d3b41_AT004414F0_ROLE00.identity_24a0 != owner->identity_86 &&
        LVL_5_FELTZIN_SYSTEM_F6af85cabb56d3b41_AT004414F0_ROLE00.mode_2294 != 6) {
        owner->value_7d = 0;
        owner->value_7e = 3;
    }
}


void LVL_5_FELTZIN_SYSTEM_FUN_00446B30(float factor, void *context,
                                   float *destination,
                                   const float *first, const float *second)
{
    float complement = 1.0f - factor;
    destination[0] = complement * first[0] + factor * second[0];
    destination[1] = complement * first[1] + factor * second[1];
    destination[2] = complement * first[2] + factor * second[2];
    destination[3] = complement * first[3] + factor * second[3];
}


/* Measured partial layouts; original type and game roles are unknown. */
typedef struct Rac2Native_81be3b52930eb806_FallbackInterleavedFloat4Layout {
    unsigned char unknown_00[8];
    float first_0;
    float second_0;
    float first_1;
    float second_1;
    float first_2;
    float second_2;
    float first_3;
    float second_3;
} Rac2Native_81be3b52930eb806_FallbackInterleavedFloat4Layout;


void LVL_5_FELTZIN_SYSTEM_FUN_00446CE0(float factor,
                                     const Rac2Native_81be3b52930eb806_FallbackInterleavedFloat4Layout *source,
                                     float *destination)
{
    float complement = 1.0f - factor;
    destination[0] = complement * source->first_0 + factor * source->second_0;
    destination[1] = complement * source->first_1 + factor * source->second_1;
    destination[2] = complement * source->first_2 + factor * source->second_2;
    destination[3] = complement * source->first_3 + factor * source->second_3;
}


void LVL_5_FELTZIN_SYSTEM_FUN_0044C040(float first, float second, float **cell)
{
    (*cell)[0] = first;
    (*cell)[1] = second;
}


void LVL_5_FELTZIN_SYSTEM_FUN_00454068(float first, float second, float **cell)
{
    (*cell)[0] = first;
    (*cell)[1] = second;
}


/* Measured partial layouts; original type and game roles are unknown. */
typedef struct Rac2Native_79744baad5ad7f65_ScalarChange48Owner {
    unsigned int field_00;
    int value_04;
    unsigned char gap_08[0x3ec];
    int counter_3f4;
    int counter_3f8;
    int previous_3fc;
} Rac2Native_79744baad5ad7f65_ScalarChange48Owner;


extern unsigned char LVL_5_FELTZIN_SYSTEM_F79744baad5ad7f65_AT0045B4D8_ROLE00[];

void LVL_5_FELTZIN_SYSTEM_FUN_0045B4D8(Rac2Native_79744baad5ad7f65_ScalarChange48Owner *owner, int value)
{
    int previous = owner->value_04;
    if (previous != value && LVL_5_FELTZIN_SYSTEM_F79744baad5ad7f65_AT0045B4D8_ROLE00[0] == 0) {
        owner->previous_3fc = previous;
        owner->counter_3f8 = 180;
        owner->counter_3f4 = 300;
    }
    owner->value_04 = value;
}


/* Measured partial layouts; original type and game roles are unknown. */
typedef int Rac2Native_6b0741c38bf00fee_s32;

typedef unsigned char Rac2Native_6b0741c38bf00fee_u8;

typedef long Rac2Native_6b0741c38bf00fee_s64;

typedef unsigned long Rac2Native_6b0741c38bf00fee_u64;


extern Rac2Native_6b0741c38bf00fee_u8 LVL_5_FELTZIN_SYSTEM_F6b0741c38bf00fee_AT002BEA08_ROLE00[];
extern void LVL_5_FELTZIN_SYSTEM_F6b0741c38bf00fee_AT002BEA08_ROLE01(Rac2Native_6b0741c38bf00fee_u64, Rac2Native_6b0741c38bf00fee_s64, Rac2Native_6b0741c38bf00fee_s64, Rac2Native_6b0741c38bf00fee_s32);
extern void LVL_5_FELTZIN_SYSTEM_F6b0741c38bf00fee_AT002BEA08_ROLE02(short, short, short);

void LVL_5_FELTZIN_SYSTEM_FUN_002BEA08(void) {
 LVL_5_FELTZIN_SYSTEM_F6b0741c38bf00fee_AT002BEA08_ROLE01(LVL_5_FELTZIN_SYSTEM_F6b0741c38bf00fee_AT002BEA08_ROLE00[1],0,1,0x32);
 LVL_5_FELTZIN_SYSTEM_F6b0741c38bf00fee_AT002BEA08_ROLE02(0x16,7,0);
}


/* Measured partial layouts; original type and game roles are unknown. */
typedef int Rac2Native_28c929cadd7aca24_s32;

typedef unsigned char Rac2Native_28c929cadd7aca24_u8;

typedef struct {
    Rac2Native_28c929cadd7aca24_u8 prefix[0xc40];
    Rac2Native_28c929cadd7aca24_s32 selected;
    Rac2Native_28c929cadd7aca24_s32 index;
    Rac2Native_28c929cadd7aca24_u8 gap[0x1648];
    Rac2Native_28c929cadd7aca24_u8 *object;
} Rac2Native_28c929cadd7aca24_NativeResidentView;


extern Rac2Native_28c929cadd7aca24_NativeResidentView LVL_5_FELTZIN_SYSTEM_F28c929cadd7aca24_AT002EACF0_ROLE00;

void LVL_5_FELTZIN_SYSTEM_FUN_002EACF0(Rac2Native_28c929cadd7aca24_s32 selected, Rac2Native_28c929cadd7aca24_s32 index) {
    if (selected >= 0) {
        Rac2Native_28c929cadd7aca24_u8 *object = LVL_5_FELTZIN_SYSTEM_F28c929cadd7aca24_AT002EACF0_ROLE00.object;
        Rac2Native_28c929cadd7aca24_s32 offset = object[0x43] * 4;
        Rac2Native_28c929cadd7aca24_u8 *table = *(Rac2Native_28c929cadd7aca24_u8 **)(object + 0x24);
        Rac2Native_28c929cadd7aca24_u8 *entry = *(Rac2Native_28c929cadd7aca24_u8 **)(table + offset + 0x48);
        if (index < entry[0x10]) {
            LVL_5_FELTZIN_SYSTEM_F28c929cadd7aca24_AT002EACF0_ROLE00.selected = selected;
            LVL_5_FELTZIN_SYSTEM_F28c929cadd7aca24_AT002EACF0_ROLE00.index = index;
        }
    }
}


/* Measured partial layouts; original type and game roles are unknown. */
typedef float Rac2Native_5fc519c90e0e763a_f32;


extern void LVL_5_FELTZIN_SYSTEM_F5fc519c90e0e763a_AT002EBFF8_ROLE00(Rac2Native_5fc519c90e0e763a_f32);

void LVL_5_FELTZIN_SYSTEM_FUN_002EBFF8(Rac2Native_5fc519c90e0e763a_f32 value) {
 LVL_5_FELTZIN_SYSTEM_F5fc519c90e0e763a_AT002EBFF8_ROLE00(-value);
}


/* Measured partial layouts; original type and game roles are unknown. */
typedef unsigned int Rac2Native_74a5d71aacb394c6_u32;

typedef struct {
    Rac2Native_74a5d71aacb394c6_u32 first[64];
    Rac2Native_74a5d71aacb394c6_u32 second[64];
    unsigned char gap[0x20];
    int count;
    Rac2Native_74a5d71aacb394c6_u32 current;
} Rac2Native_74a5d71aacb394c6_ExtraIndexState48;


void LVL_5_FELTZIN_SYSTEM_FUN_00394E50(Rac2Native_74a5d71aacb394c6_ExtraIndexState48 *state, int index) {
    state->first[index] = 0;
    state->second[index] = 0;
    if (--state->count == 0) {
        state->current = 0;
    }
}


/* Measured partial layouts; original type and game roles are unknown. */
typedef unsigned int Rac2Native_03c444112283bc5f_u32;


extern Rac2Native_03c444112283bc5f_u32 LVL_5_FELTZIN_SYSTEM_F03c444112283bc5f_AT003A0EF8_ROLE00[139];

void LVL_5_FELTZIN_SYSTEM_FUN_003A0EF8(void)
{
    int i;
    LVL_5_FELTZIN_SYSTEM_F03c444112283bc5f_AT003A0EF8_ROLE00[138] = 5;
    LVL_5_FELTZIN_SYSTEM_F03c444112283bc5f_AT003A0EF8_ROLE00[137] = 0;
    LVL_5_FELTZIN_SYSTEM_F03c444112283bc5f_AT003A0EF8_ROLE00[136] = 0;
    for (i = 0; i < 64; ++i) {
        LVL_5_FELTZIN_SYSTEM_F03c444112283bc5f_AT003A0EF8_ROLE00[i] = 0;
        LVL_5_FELTZIN_SYSTEM_F03c444112283bc5f_AT003A0EF8_ROLE00[i + 64] = 0;
    }
    for (i = 7; i >= 0; --i)
        LVL_5_FELTZIN_SYSTEM_F03c444112283bc5f_AT003A0EF8_ROLE00[i + 128] = 0;
}


/* Target: FUN_003427B0 — identity function returning its first argument */
/* Disassembly: jr ra; move v0,a0 (MIPS delay slot) */
/* Compiled with: -O2 -G0 -ffunction-sections */

unsigned long LVL_5_FELTZIN_SYSTEM_FUN_002BD770(unsigned long param_1)
{
  return param_1;
}


/* Target: FUN_003427B0 — identity function returning its first argument */
/* Disassembly: jr ra; move v0,a0 (MIPS delay slot) */
/* Compiled with: -O2 -G0 -ffunction-sections */

unsigned long LVL_5_FELTZIN_SYSTEM_FUN_002EC830(unsigned long param_1)
{
  return param_1;
}


/* Returns the constant integer 1. Matches FUN_0012F940 disassembly and decompilation. */
int LVL_5_FELTZIN_SYSTEM_FUN_002F4B70(void) {
    return 1;
}


/* Returns the constant integer 1. Matches FUN_0012F940 disassembly and decompilation. */
int LVL_5_FELTZIN_SYSTEM_FUN_002F4B78(void) {
    return 1;
}


extern void LVL_5_FELTZIN_SYSTEM_QWEN_11a4c157d102_AT0030C6A8_ROLE000(unsigned char *);

void LVL_5_FELTZIN_SYSTEM_FUN_0030C6A8(void *owner)
{
    LVL_5_FELTZIN_SYSTEM_QWEN_11a4c157d102_AT0030C6A8_ROLE000(owner);
}



void LVL_5_FELTZIN_SYSTEM_QWEN_407ee6f17a73_AT0030C748_ROLE001(int);
void LVL_5_FELTZIN_SYSTEM_QWEN_407ee6f17a73_AT0030C748_ROLE000(void*);

void LVL_5_FELTZIN_SYSTEM_FUN_0030C748(void *param)
{
  LVL_5_FELTZIN_SYSTEM_QWEN_407ee6f17a73_AT0030C748_ROLE001((int)param);
  *(unsigned int *)param = 0;
  LVL_5_FELTZIN_SYSTEM_QWEN_407ee6f17a73_AT0030C748_ROLE000(param);
}


void LVL_5_FELTZIN_SYSTEM_QWEN_5696fcf76f0c_AT00329F38_ROLE000(unsigned int *dst, unsigned int val, int size);

void LVL_5_FELTZIN_SYSTEM_FUN_00329F38(void)
{
    LVL_5_FELTZIN_SYSTEM_QWEN_5696fcf76f0c_AT00329F38_ROLE000((unsigned int *)0x70003A00, 0x40000000, 0x3C0);
}


/*
 * Disassembled at 0x002cd220
 * Signature: int FUN_002cd220(void)
 * Behavior:
 *   - Saves RA on stack
 *   - Calls FUN_0027C540(0)
 *   - Calls FUN_0029C138()
 *   - Calls FUN_0027C660()
 *   - Restores RA from stack
 *   - Returns 0
 */
extern void LVL_5_FELTZIN_SYSTEM_QWEN_523e38f49b74_AT00358BD8_ROLE000(long);
extern void LVL_5_FELTZIN_SYSTEM_QWEN_523e38f49b74_AT00358BD8_ROLE002(void);
extern void LVL_5_FELTZIN_SYSTEM_QWEN_523e38f49b74_AT00358BD8_ROLE001(void);

int LVL_5_FELTZIN_SYSTEM_FUN_00358BD8(void)
{
  LVL_5_FELTZIN_SYSTEM_QWEN_523e38f49b74_AT00358BD8_ROLE000(0);
  LVL_5_FELTZIN_SYSTEM_QWEN_523e38f49b74_AT00358BD8_ROLE002();
  LVL_5_FELTZIN_SYSTEM_QWEN_523e38f49b74_AT00358BD8_ROLE001();
  return 0;
}


unsigned long long LVL_5_FELTZIN_SYSTEM_FUN_00358FD8(void);

extern void LVL_5_FELTZIN_SYSTEM_QWEN_f47929f95774_AT00358FD8_ROLE000(long);
extern void LVL_5_FELTZIN_SYSTEM_QWEN_f47929f95774_AT00358FD8_ROLE002(void);
extern void LVL_5_FELTZIN_SYSTEM_QWEN_f47929f95774_AT00358FD8_ROLE001(void);

unsigned long long LVL_5_FELTZIN_SYSTEM_FUN_00358FD8(void)
{
  LVL_5_FELTZIN_SYSTEM_QWEN_f47929f95774_AT00358FD8_ROLE000(0);
  LVL_5_FELTZIN_SYSTEM_QWEN_f47929f95774_AT00358FD8_ROLE002();
  LVL_5_FELTZIN_SYSTEM_QWEN_f47929f95774_AT00358FD8_ROLE001();
  return 0;
}


/* Function at 0x002cd8c0: FUN_002CD8C0
 * 
 * Disassembly summary:
 * - 12 instructions, 48 bytes total
 * - Prologue: save ra, allocate 16-byte stack frame
 * - Three calls to external functions:
 *   1. FUN_0027C540(0)
 *   2. FUN_0029C450()
 *   3. FUN_0027C660()
 * - Epilogue: restore ra, return 0, deallocate stack
 * - No local variables used
 * - Return type is void-like; returns zero in v0
 * - Delay slots are_NOP/unused in this case
 */

/* External function declarations (exact addresses from task metadata) */
extern void LVL_5_FELTZIN_SYSTEM_QWEN_cb305b1f1210_AT00359278_ROLE000(long);
extern void LVL_5_FELTZIN_SYSTEM_QWEN_cb305b1f1210_AT00359278_ROLE002(void);
extern void LVL_5_FELTZIN_SYSTEM_QWEN_cb305b1f1210_AT00359278_ROLE001(void);

long long LVL_5_FELTZIN_SYSTEM_FUN_00359278(void)
{
    LVL_5_FELTZIN_SYSTEM_QWEN_cb305b1f1210_AT00359278_ROLE000(0LL);
    LVL_5_FELTZIN_SYSTEM_QWEN_cb305b1f1210_AT00359278_ROLE002();
    LVL_5_FELTZIN_SYSTEM_QWEN_cb305b1f1210_AT00359278_ROLE001();
    return 0LL;
}


extern void LVL_5_FELTZIN_SYSTEM_QWEN_c23b3406f982_AT0035E670_ROLE000(long);
extern void LVL_5_FELTZIN_SYSTEM_QWEN_c23b3406f982_AT0035E670_ROLE002(void);
extern void LVL_5_FELTZIN_SYSTEM_QWEN_c23b3406f982_AT0035E670_ROLE001(void);

int LVL_5_FELTZIN_SYSTEM_FUN_0035E670(void)
{
    LVL_5_FELTZIN_SYSTEM_QWEN_c23b3406f982_AT0035E670_ROLE000(0);
    LVL_5_FELTZIN_SYSTEM_QWEN_c23b3406f982_AT0035E670_ROLE002();
    LVL_5_FELTZIN_SYSTEM_QWEN_c23b3406f982_AT0035E670_ROLE001();
    return 0;
}


void LVL_5_FELTZIN_SYSTEM_QWEN_68cf9ebb5ee2_AT0035E7E0_ROLE000(long);
void LVL_5_FELTZIN_SYSTEM_QWEN_68cf9ebb5ee2_AT0035E7E0_ROLE001(void);
void LVL_5_FELTZIN_SYSTEM_QWEN_68cf9ebb5ee2_AT0035E7E0_ROLE002(void);

unsigned long long LVL_5_FELTZIN_SYSTEM_FUN_0035E7E0(void)
{
    LVL_5_FELTZIN_SYSTEM_QWEN_68cf9ebb5ee2_AT0035E7E0_ROLE000(0);
    LVL_5_FELTZIN_SYSTEM_QWEN_68cf9ebb5ee2_AT0035E7E0_ROLE002();
    LVL_5_FELTZIN_SYSTEM_QWEN_68cf9ebb5ee2_AT0035E7E0_ROLE001();
    return 0;
}



/* 
 * Function: FUN_002D2EE0
 * 
 * Disassembly summary:
 * - Saves return address on stack
 * - Calls FUN_0027C540(0) (with zero argument)
 * - Calls FUN_0029C7A0()
 * - Calls FUN_0027C660()
 * - Restores return address
 * - Returns 0
 *
 * Notes:
 * - The function follows standard MIPS ABI prologue/epilogue.
 * - Delay slots are filled with NOP or argument setup as seen in disassembly.
 * - No local variables used.
 * - All external function addresses come from the assigned externals list.
 */

extern void LVL_5_FELTZIN_SYSTEM_QWEN_68f040eb20c9_AT0035E898_ROLE000(long arg0);
extern void LVL_5_FELTZIN_SYSTEM_QWEN_68f040eb20c9_AT0035E898_ROLE002(void);
extern void LVL_5_FELTZIN_SYSTEM_QWEN_68f040eb20c9_AT0035E898_ROLE001(void);

unsigned long long LVL_5_FELTZIN_SYSTEM_FUN_0035E898(void)
{
    LVL_5_FELTZIN_SYSTEM_QWEN_68f040eb20c9_AT0035E898_ROLE000(0);
    LVL_5_FELTZIN_SYSTEM_QWEN_68f040eb20c9_AT0035E898_ROLE002();
    LVL_5_FELTZIN_SYSTEM_QWEN_68f040eb20c9_AT0035E898_ROLE001();
    return 0;
}


/* External function declarations as per target specification */
extern void LVL_5_FELTZIN_SYSTEM_QWEN_92ea7c2f4a5c_AT0035EC48_ROLE000(long);
extern void LVL_5_FELTZIN_SYSTEM_QWEN_92ea7c2f4a5c_AT0035EC48_ROLE001(void);
extern void LVL_5_FELTZIN_SYSTEM_QWEN_92ea7c2f4a5c_AT0035EC48_ROLE002(void);

/* Implementation matching decompiled output */
long LVL_5_FELTZIN_SYSTEM_FUN_0035EC48(void)
{
  LVL_5_FELTZIN_SYSTEM_QWEN_92ea7c2f4a5c_AT0035EC48_ROLE000(0);
  LVL_5_FELTZIN_SYSTEM_QWEN_92ea7c2f4a5c_AT0035EC48_ROLE002();
  LVL_5_FELTZIN_SYSTEM_QWEN_92ea7c2f4a5c_AT0035EC48_ROLE001();
  return 0;
}


/* External functions declared with exact aliases from task.externals */
extern void LVL_5_FELTZIN_SYSTEM_QWEN_d01c568afacc_AT0035ED48_ROLE000(long param_1);
extern void LVL_5_FELTZIN_SYSTEM_QWEN_d01c568afacc_AT0035ED48_ROLE001(void);
extern void LVL_5_FELTZIN_SYSTEM_QWEN_d01c568afacc_AT0035ED48_ROLE002(void);

/* Candidate function: FUN_002d3390 */
unsigned long long LVL_5_FELTZIN_SYSTEM_FUN_0035ED48(void)
{
    LVL_5_FELTZIN_SYSTEM_QWEN_d01c568afacc_AT0035ED48_ROLE000(0);
    LVL_5_FELTZIN_SYSTEM_QWEN_d01c568afacc_AT0035ED48_ROLE002();
    LVL_5_FELTZIN_SYSTEM_QWEN_d01c568afacc_AT0035ED48_ROLE001();
    return 0;
}


/* Target: FUN_002d5540 on MIPS (SCUS_972.68, -O2 -G0 -ffunction-sections)
 * Calls three externals: FUN_0027C540(int), FUN_0029CED8(void), FUN_0027C660(void)
 * Returns 0. Stack frame size 16 bytes. Delay slots filled.
 */
extern void LVL_5_FELTZIN_SYSTEM_QWEN_093381cf82c3_AT00360EF8_ROLE000(long);
extern void LVL_5_FELTZIN_SYSTEM_QWEN_093381cf82c3_AT00360EF8_ROLE002(void);
extern void LVL_5_FELTZIN_SYSTEM_QWEN_093381cf82c3_AT00360EF8_ROLE001(void);

long long LVL_5_FELTZIN_SYSTEM_FUN_00360EF8(void)
{
    LVL_5_FELTZIN_SYSTEM_QWEN_093381cf82c3_AT00360EF8_ROLE000(0);
    LVL_5_FELTZIN_SYSTEM_QWEN_093381cf82c3_AT00360EF8_ROLE002();
    LVL_5_FELTZIN_SYSTEM_QWEN_093381cf82c3_AT00360EF8_ROLE001();
    return 0;
}


/* Returns the constant integer 1. Matches FUN_0012F940 disassembly and decompilation. */
int LVL_5_FELTZIN_SYSTEM_FUN_0036ABC0(void) {
    return 1;
}


/* Measured partial C views; original types and object ownership are unknown. */
typedef unsigned char QwenRecovery_4ecc6b5a4034_u8;
typedef unsigned int QwenRecovery_4ecc6b5a4034_u32;

/* Minimum external views; neither declaration allocates original game storage. */
typedef struct {
    QwenRecovery_4ecc6b5a4034_u8 prefix[0x24];
    QwenRecovery_4ecc6b5a4034_u32 word;
    QwenRecovery_4ecc6b5a4034_u8 tail[8];
} QwenRecovery_4ecc6b5a4034_ExtraResetRecord164;



extern QwenRecovery_4ecc6b5a4034_ExtraResetRecord164 LVL_5_FELTZIN_SYSTEM_QWEN_4ecc6b5a4034_AT0039E480_ROLE000[100];
extern QwenRecovery_4ecc6b5a4034_u32 LVL_5_FELTZIN_SYSTEM_QWEN_4ecc6b5a4034_AT0039E480_ROLE001[139];

void LVL_5_FELTZIN_SYSTEM_FUN_0039E480(void)
{
    int i;
    for (i = 99; i >= 0; --i)
        LVL_5_FELTZIN_SYSTEM_QWEN_4ecc6b5a4034_AT0039E480_ROLE000[i].word = 0;
    LVL_5_FELTZIN_SYSTEM_QWEN_4ecc6b5a4034_AT0039E480_ROLE001[138] = 5;
    LVL_5_FELTZIN_SYSTEM_QWEN_4ecc6b5a4034_AT0039E480_ROLE001[137] = 0;
    LVL_5_FELTZIN_SYSTEM_QWEN_4ecc6b5a4034_AT0039E480_ROLE001[136] = 0;
    for (i = 0; i < 64; ++i) {
        LVL_5_FELTZIN_SYSTEM_QWEN_4ecc6b5a4034_AT0039E480_ROLE001[i] = 0;
        LVL_5_FELTZIN_SYSTEM_QWEN_4ecc6b5a4034_AT0039E480_ROLE001[i + 64] = 0;
    }
    for (i = 7; i >= 0; --i)
        LVL_5_FELTZIN_SYSTEM_QWEN_4ecc6b5a4034_AT0039E480_ROLE001[i + 128] = 0;
}



void LVL_5_FELTZIN_SYSTEM_FUN_00447A50(int param_1, unsigned int param_2)
{
  *(unsigned int*)(param_1 + 0x44) = param_2;
  return;
}


void LVL_5_FELTZIN_SYSTEM_FUN_00447A58(int param_1, unsigned int param_2)
{
  *(unsigned int *)(param_1 + 0x40) = param_2;
  return;
}


void LVL_5_FELTZIN_SYSTEM_FUN_00447BB0(int param_1, unsigned int param_2)
{
  *(unsigned int *)(param_1 + 0x40) = param_2;
  return;
}


void LVL_5_FELTZIN_SYSTEM_FUN_00447D00(int param_1, unsigned int param_2)
{
  *(unsigned int*)(param_1 + 0x44) = param_2;
  return;
}


/* Target: FUN_003427B0 — identity function returning its first argument */
/* Disassembly: jr ra; move v0,a0 (MIPS delay slot) */
/* Compiled with: -O2 -G0 -ffunction-sections */

unsigned long LVL_5_FELTZIN_SYSTEM_FUN_00447DD0(unsigned long param_1)
{
  return param_1;
}


extern void LVL_5_FELTZIN_SYSTEM_QWEN_df8fc8ba49cf_AT0044A798_ROLE000(unsigned char *owner, int value);

void LVL_5_FELTZIN_SYSTEM_FUN_0044A798(unsigned char *owner, int value)
{
    LVL_5_FELTZIN_SYSTEM_QWEN_df8fc8ba49cf_AT0044A798_ROLE000(owner + 8, value);
}



void* LVL_5_FELTZIN_SYSTEM_FUN_0044F198(void* param_1);

extern void LVL_5_FELTZIN_SYSTEM_QWEN_f353c206e726_AT0044F198_ROLE000(int);
extern unsigned long long LVL_5_FELTZIN_SYSTEM_QWEN_f353c206e726_AT0044F198_ROLE001(unsigned long long);

void* LVL_5_FELTZIN_SYSTEM_FUN_0044F198(void* param_1)
{
  LVL_5_FELTZIN_SYSTEM_QWEN_f353c206e726_AT0044F198_ROLE000((int)param_1 + 8);
  LVL_5_FELTZIN_SYSTEM_QWEN_f353c206e726_AT0044F198_ROLE001((int)param_1 + 0x2b0);
  return param_1;
}


extern int LVL_5_FELTZIN_SYSTEM_QWEN_f2f9288a4e34_AT0044F338_ROLE000(int);

int LVL_5_FELTZIN_SYSTEM_FUN_0044F338(int owner)
{
    int result;
    result = LVL_5_FELTZIN_SYSTEM_QWEN_f2f9288a4e34_AT0044F338_ROLE000(owner);
    return *(int *)(owner + 0x378) + result * 0x14;
}



extern int LVL_5_FELTZIN_SYSTEM_QWEN_e41cd63258f5_AT0044F370_ROLE000(unsigned char *);

int LVL_5_FELTZIN_SYSTEM_FUN_0044F370(int owner)
{
    return LVL_5_FELTZIN_SYSTEM_QWEN_e41cd63258f5_AT0044F370_ROLE000((unsigned char *)(owner + 0x2b0));
}



void LVL_5_FELTZIN_SYSTEM_QWEN_f29f80950ce7_AT00452A90_ROLE000(int);

void LVL_5_FELTZIN_SYSTEM_FUN_00452A90(int param_1)
{
  LVL_5_FELTZIN_SYSTEM_QWEN_f29f80950ce7_AT00452A90_ROLE000(param_1 + 0x228);
  return;
}


extern void LVL_5_FELTZIN_SYSTEM_QWEN_bf824305b9f7_AT004533A8_ROLE000(unsigned char *owner, float *records);

void LVL_5_FELTZIN_SYSTEM_FUN_004533A8(unsigned char *owner, float *records)
{
    *(float **)(owner + 0x250) = records;
    LVL_5_FELTZIN_SYSTEM_QWEN_bf824305b9f7_AT004533A8_ROLE000(owner + 0x188, records);
}



void LVL_5_FELTZIN_SYSTEM_QWEN_61faeca45963_AT00453670_ROLE000(int param_1);

void LVL_5_FELTZIN_SYSTEM_FUN_00453670(int param_1)
{
  LVL_5_FELTZIN_SYSTEM_QWEN_61faeca45963_AT00453670_ROLE000(param_1 + 0x188);
  return;
}


/* Target: FUN_003427B0 — identity function returning its first argument */
/* Disassembly: jr ra; move v0,a0 (MIPS delay slot) */
/* Compiled with: -O2 -G0 -ffunction-sections */

unsigned long LVL_5_FELTZIN_SYSTEM_FUN_004537D8(unsigned long param_1)
{
  return param_1;
}


extern int LVL_5_FELTZIN_SYSTEM_QWEN_6add11b33414_AT00454588_ROLE000(unsigned char *owner);

int LVL_5_FELTZIN_SYSTEM_FUN_00454588(unsigned char *owner)
{
    return LVL_5_FELTZIN_SYSTEM_QWEN_6add11b33414_AT00454588_ROLE000(owner + 0x298);
}



extern void LVL_5_FELTZIN_SYSTEM_QWEN_de961518de48_AT004545A8_ROLE000(unsigned char *owner);

void LVL_5_FELTZIN_SYSTEM_FUN_004545A8(unsigned char *owner)
{
    LVL_5_FELTZIN_SYSTEM_QWEN_de961518de48_AT004545A8_ROLE000(owner + 0x298);
}



extern unsigned long long LVL_5_FELTZIN_SYSTEM_QWEN_7ba3cdeeb16b_AT00458EC8_ROLE000(unsigned long long);

unsigned long long LVL_5_FELTZIN_SYSTEM_FUN_00458EC8(unsigned long long value)
{
    LVL_5_FELTZIN_SYSTEM_QWEN_7ba3cdeeb16b_AT00458EC8_ROLE000(value);
    return value;
}



void LVL_5_FELTZIN_SYSTEM_FUN_00459110(int param_1, unsigned int param_2)
{
  *(unsigned int *)(param_1 + 0xb8) = param_2;
  return;
}


/* Target: FUN_003427B0 — identity function returning its first argument */
/* Disassembly: jr ra; move v0,a0 (MIPS delay slot) */
/* Compiled with: -O2 -G0 -ffunction-sections */

unsigned long LVL_5_FELTZIN_SYSTEM_FUN_0045A170(unsigned long param_1)
{
  return param_1;
}


void LVL_5_FELTZIN_SYSTEM_FUN_0045A4B0(int *param_1)
{
    param_1[0x150 / sizeof(int)] = 0;
}


void LVL_5_FELTZIN_SYSTEM_FUN_0045A650(int param_1, int param_2) {
    *(int *)(param_1 + 0x84) = param_2;
}


void LVL_5_FELTZIN_SYSTEM_FUN_0045A698(int param_1, unsigned int param_2)
{
  *(unsigned int *)(param_1 + 32) = param_2;
  return;
}


/* Target: FUN_003427B0 — identity function returning its first argument */
/* Disassembly: jr ra; move v0,a0 (MIPS delay slot) */
/* Compiled with: -O2 -G0 -ffunction-sections */

unsigned long LVL_5_FELTZIN_SYSTEM_FUN_0045F5F0(unsigned long param_1)
{
  return param_1;
}


/* Returns the constant integer 1. Matches FUN_0012F940 disassembly and decompilation. */
int LVL_5_FELTZIN_SYSTEM_FUN_004616E0(void) {
    return 1;
}


extern int LVL_5_FELTZIN_SYSTEM_QWEN_cc83cb329fcb_AT00462F20_ROLE000(unsigned char *);

int LVL_5_FELTZIN_SYSTEM_FUN_00462F20(int *owner)
{
    int result;
    long status;
    status = LVL_5_FELTZIN_SYSTEM_QWEN_cc83cb329fcb_AT00462F20_ROLE000((unsigned char *)owner);
    if (status == 0)
        result = *owner + owner[2] * 0xd0000;
    else
        result = 0;
    return result;
}

extern void LVL_5_FELTZIN_SYSTEM_Fc936841d_FUN_00306660(char *local, char *first, char *second);
extern void LVL_5_FELTZIN_SYSTEM_Fc936841d_FUN_00306630(char *target, char *first, char *local);

#ifndef RAC2_T_VEC16_FC936841D
#define RAC2_T_VEC16_FC936841D
typedef struct {
    float x;
    float y;
    float z;
    float w;
} Vec16_Fc936841d;
#endif


void LVL_5_FELTZIN_SYSTEM_FUN_00398948(Vec16_Fc936841d *object, int index)
{
    char local[16];

    LVL_5_FELTZIN_SYSTEM_Fc936841d_FUN_00306660(local, (char *)&object[index - 2], (char *)&object[index - 3]);
    LVL_5_FELTZIN_SYSTEM_Fc936841d_FUN_00306630((char *)&object[index - 1], (char *)&object[index - 2], local);
}
extern void LVL_5_FELTZIN_SYSTEM_Fc936841d_FUN_00306660(char *local, char *first, char *second);
extern void LVL_5_FELTZIN_SYSTEM_Fc936841d_FUN_00306630(char *target, char *first, char *local);

#ifndef RAC2_T_VEC16_FC936841D
#define RAC2_T_VEC16_FC936841D
typedef struct {
    float x;
    float y;
    float z;
    float w;
} Vec16_Fc936841d;
#endif


void LVL_5_FELTZIN_SYSTEM_FUN_003B78F8(Vec16_Fc936841d *object, int index)
{
    char local[16];

    LVL_5_FELTZIN_SYSTEM_Fc936841d_FUN_00306660(local, (char *)&object[index - 2], (char *)&object[index - 3]);
    LVL_5_FELTZIN_SYSTEM_Fc936841d_FUN_00306630((char *)&object[index - 1], (char *)&object[index - 2], local);
}
extern void LVL_5_FELTZIN_SYSTEM_Fc936841d_FUN_00306660(char *local, char *first, char *second);
extern void LVL_5_FELTZIN_SYSTEM_Fc936841d_FUN_00306630(char *target, char *first, char *local);

#ifndef RAC2_T_VEC16_FC936841D
#define RAC2_T_VEC16_FC936841D
typedef struct {
    float x;
    float y;
    float z;
    float w;
} Vec16_Fc936841d;
#endif


void LVL_5_FELTZIN_SYSTEM_FUN_003C7EE8(Vec16_Fc936841d *object, int index)
{
    char local[16];

    LVL_5_FELTZIN_SYSTEM_Fc936841d_FUN_00306660(local, (char *)&object[index - 2], (char *)&object[index - 3]);
    LVL_5_FELTZIN_SYSTEM_Fc936841d_FUN_00306630((char *)&object[index - 1], (char *)&object[index - 2], local);
}
extern void LVL_5_FELTZIN_SYSTEM_Fc936841d_FUN_00306660(char *local, char *first, char *second);
extern void LVL_5_FELTZIN_SYSTEM_Fc936841d_FUN_00306630(char *target, char *first, char *local);

#ifndef RAC2_T_VEC16_FC936841D
#define RAC2_T_VEC16_FC936841D
typedef struct {
    float x;
    float y;
    float z;
    float w;
} Vec16_Fc936841d;
#endif


void LVL_5_FELTZIN_SYSTEM_FUN_003D4EF8(Vec16_Fc936841d *object, int index)
{
    char local[16];

    LVL_5_FELTZIN_SYSTEM_Fc936841d_FUN_00306660(local, (char *)&object[index - 2], (char *)&object[index - 3]);
    LVL_5_FELTZIN_SYSTEM_Fc936841d_FUN_00306630((char *)&object[index - 1], (char *)&object[index - 2], local);
}
extern void LVL_5_FELTZIN_SYSTEM_Fc936841d_FUN_00306660(char *local, char *first, char *second);
extern void LVL_5_FELTZIN_SYSTEM_Fc936841d_FUN_00306630(char *target, char *first, char *local);

#ifndef RAC2_T_VEC16_FC936841D
#define RAC2_T_VEC16_FC936841D
typedef struct {
    float x;
    float y;
    float z;
    float w;
} Vec16_Fc936841d;
#endif


void LVL_5_FELTZIN_SYSTEM_FUN_003DF9E8(Vec16_Fc936841d *object, int index)
{
    char local[16];

    LVL_5_FELTZIN_SYSTEM_Fc936841d_FUN_00306660(local, (char *)&object[index - 2], (char *)&object[index - 3]);
    LVL_5_FELTZIN_SYSTEM_Fc936841d_FUN_00306630((char *)&object[index - 1], (char *)&object[index - 2], local);
}
extern void LVL_5_FELTZIN_SYSTEM_Fc936841d_FUN_00306660(char *local, char *first, char *second);
extern void LVL_5_FELTZIN_SYSTEM_Fc936841d_FUN_00306630(char *target, char *first, char *local);

#ifndef RAC2_T_VEC16_FC936841D
#define RAC2_T_VEC16_FC936841D
typedef struct {
    float x;
    float y;
    float z;
    float w;
} Vec16_Fc936841d;
#endif


void LVL_5_FELTZIN_SYSTEM_FUN_003F1C68(Vec16_Fc936841d *object, int index)
{
    char local[16];

    LVL_5_FELTZIN_SYSTEM_Fc936841d_FUN_00306660(local, (char *)&object[index - 2], (char *)&object[index - 3]);
    LVL_5_FELTZIN_SYSTEM_Fc936841d_FUN_00306630((char *)&object[index - 1], (char *)&object[index - 2], local);
}
extern void LVL_5_FELTZIN_SYSTEM_Fc936841d_FUN_00306660(char *local, char *first, char *second);
extern void LVL_5_FELTZIN_SYSTEM_Fc936841d_FUN_00306630(char *target, char *first, char *local);

#ifndef RAC2_T_VEC16_FC936841D
#define RAC2_T_VEC16_FC936841D
typedef struct {
    float x;
    float y;
    float z;
    float w;
} Vec16_Fc936841d;
#endif


void LVL_5_FELTZIN_SYSTEM_FUN_003FA0A8(Vec16_Fc936841d *object, int index)
{
    char local[16];

    LVL_5_FELTZIN_SYSTEM_Fc936841d_FUN_00306660(local, (char *)&object[index - 2], (char *)&object[index - 3]);
    LVL_5_FELTZIN_SYSTEM_Fc936841d_FUN_00306630((char *)&object[index - 1], (char *)&object[index - 2], local);
}
extern void LVL_5_FELTZIN_SYSTEM_Fc936841d_FUN_00306660(char *local, char *first, char *second);
extern void LVL_5_FELTZIN_SYSTEM_Fc936841d_FUN_00306630(char *target, char *first, char *local);

#ifndef RAC2_T_VEC16_FC936841D
#define RAC2_T_VEC16_FC936841D
typedef struct {
    float x;
    float y;
    float z;
    float w;
} Vec16_Fc936841d;
#endif


void LVL_5_FELTZIN_SYSTEM_FUN_00423D20(Vec16_Fc936841d *object, int index)
{
    char local[16];

    LVL_5_FELTZIN_SYSTEM_Fc936841d_FUN_00306660(local, (char *)&object[index - 2], (char *)&object[index - 3]);
    LVL_5_FELTZIN_SYSTEM_Fc936841d_FUN_00306630((char *)&object[index - 1], (char *)&object[index - 2], local);
}
extern void LVL_5_FELTZIN_SYSTEM_Fc936841d_FUN_00306660(char *local, char *first, char *second);
extern void LVL_5_FELTZIN_SYSTEM_Fc936841d_FUN_00306630(char *target, char *first, char *local);

#ifndef RAC2_T_VEC16_FC936841D
#define RAC2_T_VEC16_FC936841D
typedef struct {
    float x;
    float y;
    float z;
    float w;
} Vec16_Fc936841d;
#endif


void LVL_5_FELTZIN_SYSTEM_FUN_00430BF0(Vec16_Fc936841d *object, int index)
{
    char local[16];

    LVL_5_FELTZIN_SYSTEM_Fc936841d_FUN_00306660(local, (char *)&object[index - 2], (char *)&object[index - 3]);
    LVL_5_FELTZIN_SYSTEM_Fc936841d_FUN_00306630((char *)&object[index - 1], (char *)&object[index - 2], local);
}



extern void LVL_5_FELTZIN_SYSTEM_F01bd4546_FUN_00446E88(char *p, int v);
extern void LVL_5_FELTZIN_SYSTEM_F01bd4546_FUN_0045A658(char *p, int v);
extern void LVL_5_FELTZIN_SYSTEM_F01bd4546_FUN_0045A658(char *p, int v);
extern void LVL_5_FELTZIN_SYSTEM_F01bd4546_FUN_0045A658(char *p, int v);
extern void LVL_5_FELTZIN_SYSTEM_F01bd4546_FUN_0045A658(char *p, int v);
extern void LVL_5_FELTZIN_SYSTEM_F01bd4546_FUN_0045A658(char *p, int v);
extern void LVL_5_FELTZIN_SYSTEM_F01bd4546_FUN_0045A658(char *p, int v);
extern void LVL_5_FELTZIN_SYSTEM_F01bd4546_FUN_0045A6A0(char *p, float v);
extern void LVL_5_FELTZIN_SYSTEM_F01bd4546_FUN_0045A6A0(char *p, float v);
extern void LVL_5_FELTZIN_SYSTEM_F01bd4546_FUN_0045A6A0(char *p, float v);
extern void LVL_5_FELTZIN_SYSTEM_F01bd4546_FUN_0045A6A0(char *p, float v);
extern void LVL_5_FELTZIN_SYSTEM_F01bd4546_FUN_0045A6A0(char *p, float v);
extern void LVL_5_FELTZIN_SYSTEM_F01bd4546_FUN_0045A6A0(char *p, float v);

void LVL_5_FELTZIN_SYSTEM_FUN_0045DBB0(char *self, int x)
{
    char *p1, *p2, *p3, *p4, *p5, *p6;

    *(s32 *)(self + 5492) = x;
    if (*(s32 *)(self + 5496) != 0) {
        *(s32 *)(self + 5496) = 0;
        LVL_5_FELTZIN_SYSTEM_F01bd4546_FUN_00446E88(self + 1464, 0);
        p1 = self + 3052;
        p2 = self + 3188;
        p3 = self + 3324;
        p4 = self + 3460;
        p5 = self + 3596;
        p6 = self + 3732;
        LVL_5_FELTZIN_SYSTEM_F01bd4546_FUN_0045A658(p1, 1);
        LVL_5_FELTZIN_SYSTEM_F01bd4546_FUN_0045A658(p2, 1);
        LVL_5_FELTZIN_SYSTEM_F01bd4546_FUN_0045A658(p3, 1);
        LVL_5_FELTZIN_SYSTEM_F01bd4546_FUN_0045A658(p4, 1);
        LVL_5_FELTZIN_SYSTEM_F01bd4546_FUN_0045A658(p5, 1);
        LVL_5_FELTZIN_SYSTEM_F01bd4546_FUN_0045A658(p6, 1);
        LVL_5_FELTZIN_SYSTEM_F01bd4546_FUN_0045A6A0(p1, *(s32 *)0x1A7B90 ? 0.14f : 0.116666675f);
        LVL_5_FELTZIN_SYSTEM_F01bd4546_FUN_0045A6A0(p2, *(s32 *)0x1A7B90 ? 0.14f : 0.116666675f);
        LVL_5_FELTZIN_SYSTEM_F01bd4546_FUN_0045A6A0(p3, *(s32 *)0x1A7B90 ? 0.14f : 0.116666675f);
        LVL_5_FELTZIN_SYSTEM_F01bd4546_FUN_0045A6A0(p4, *(s32 *)0x1A7B90 ? 0.14f : 0.116666675f);
        LVL_5_FELTZIN_SYSTEM_F01bd4546_FUN_0045A6A0(p5, *(s32 *)0x1A7B90 ? 0.14f : 0.116666675f);
        LVL_5_FELTZIN_SYSTEM_F01bd4546_FUN_0045A6A0(p6, *(s32 *)0x1A7B90 ? 0.14f : 0.116666675f);
    }
}
extern void LVL_5_FELTZIN_SYSTEM_F70997ba9_FUN_003906F8(int a, int b);
extern void LVL_5_FELTZIN_SYSTEM_F70997ba9_FUN_002FEC08(int a);
extern void *LVL_5_FELTZIN_SYSTEM_F70997ba9_FUN_0030CBA8(int id);
extern int LVL_5_FELTZIN_SYSTEM_F70997ba9_FUN_00301AF0(void *p, int i);
extern void LVL_5_FELTZIN_SYSTEM_F70997ba9_FUN_00301A78(void);
extern void LVL_5_FELTZIN_SYSTEM_F70997ba9_FUN_00301F10(int a, int b, long c, void *d, int e);
extern void LVL_5_FELTZIN_SYSTEM_F70997ba9_FUN_00301A68(void);
extern void LVL_5_FELTZIN_SYSTEM_F70997ba9_FUN_002FED28(void);

int LVL_5_FELTZIN_SYSTEM_FUN_00365150(int *arg0)
{
    int min;
    int v;
    int slot;
    int count;
    int off;

    LVL_5_FELTZIN_SYSTEM_F70997ba9_FUN_003906F8(66, 68);
    LVL_5_FELTZIN_SYSTEM_F70997ba9_FUN_003906F8(71, 11);
    LVL_5_FELTZIN_SYSTEM_F70997ba9_FUN_002FEC08(0);
    min = LVL_5_FELTZIN_SYSTEM_F70997ba9_FUN_00301AF0(LVL_5_FELTZIN_SYSTEM_F70997ba9_FUN_0030CBA8(11613), -1);
    v = LVL_5_FELTZIN_SYSTEM_F70997ba9_FUN_00301AF0(LVL_5_FELTZIN_SYSTEM_F70997ba9_FUN_0030CBA8(11625), -1);
    if (v >= min)
        min = v;
    if (*(int *)0x1A79F0 != 0) {
        v = LVL_5_FELTZIN_SYSTEM_F70997ba9_FUN_00301AF0(LVL_5_FELTZIN_SYSTEM_F70997ba9_FUN_0030CBA8(11614), -1);
        if (v >= min)
            min = v;
    }
    v = LVL_5_FELTZIN_SYSTEM_F70997ba9_FUN_00301AF0(LVL_5_FELTZIN_SYSTEM_F70997ba9_FUN_0030CBA8(11626), -1);
    if (v >= min)
        min = v;
    v = LVL_5_FELTZIN_SYSTEM_F70997ba9_FUN_00301AF0(LVL_5_FELTZIN_SYSTEM_F70997ba9_FUN_0030CBA8(11627), -1);
    if (v >= min)
        min = v;
    v = LVL_5_FELTZIN_SYSTEM_F70997ba9_FUN_00301AF0(LVL_5_FELTZIN_SYSTEM_F70997ba9_FUN_0030CBA8(11599), -1);
    if (v >= min)
        min = v;
    slot = (arg0[8] - min) >> 1;
    if (slot <= 1)
        slot = 2;
    count = arg0[9] / (*(int *)0x1A79F0 != 0 ? 7 : 6);
    LVL_5_FELTZIN_SYSTEM_F70997ba9_FUN_00301A78();
    off = count - 6;
    LVL_5_FELTZIN_SYSTEM_F70997ba9_FUN_00301F10(slot, off, 0x80FFA888L, LVL_5_FELTZIN_SYSTEM_F70997ba9_FUN_0030CBA8(11613), -1);
    off += count;
    LVL_5_FELTZIN_SYSTEM_F70997ba9_FUN_00301F10(slot, off, 0x80FFA888L, LVL_5_FELTZIN_SYSTEM_F70997ba9_FUN_0030CBA8(11625), -1);
    off += count;
    LVL_5_FELTZIN_SYSTEM_F70997ba9_FUN_00301F10(slot, off, 0x80FFA888L, LVL_5_FELTZIN_SYSTEM_F70997ba9_FUN_0030CBA8(11626), -1);
    off += count;
    LVL_5_FELTZIN_SYSTEM_F70997ba9_FUN_00301F10(slot, off, 0x80FFA888L, LVL_5_FELTZIN_SYSTEM_F70997ba9_FUN_0030CBA8(11627), -1);
    off += count;
    LVL_5_FELTZIN_SYSTEM_F70997ba9_FUN_00301F10(slot, off, 0x80FFA888L, LVL_5_FELTZIN_SYSTEM_F70997ba9_FUN_0030CBA8(11599), -1);
    LVL_5_FELTZIN_SYSTEM_F70997ba9_FUN_00301A68();
    LVL_5_FELTZIN_SYSTEM_F70997ba9_FUN_002FED28();
    return 2;
}
extern float LVL_5_FELTZIN_SYSTEM_F307ea0ee_FUN_00307620(float, float);
extern float LVL_5_FELTZIN_SYSTEM_F307ea0ee_FUN_00307620(float, float);
extern float LVL_5_FELTZIN_SYSTEM_F307ea0ee_FUN_00307620(float, float);
extern float LVL_5_FELTZIN_SYSTEM_F307ea0ee_FUN_00307620(float, float);
extern float LVL_5_FELTZIN_SYSTEM_F307ea0ee_FUN_00307620(float, float);
extern float LVL_5_FELTZIN_SYSTEM_F307ea0ee_FUN_00307620(float, float);
extern float LVL_5_FELTZIN_SYSTEM_F307ea0ee_FUN_00306C08(float);
extern float LVL_5_FELTZIN_SYSTEM_F307ea0ee_FUN_00306C20(float);
extern float LVL_5_FELTZIN_SYSTEM_F307ea0ee_FUN_00306C20(float);
extern float LVL_5_FELTZIN_SYSTEM_F307ea0ee_FUN_00306C08(float);
extern float LVL_5_FELTZIN_SYSTEM_F307ea0ee_FUN_00306C20(float);
extern float LVL_5_FELTZIN_SYSTEM_F307ea0ee_FUN_00306C20(float);

void LVL_5_FELTZIN_SYSTEM_FUN_003B74C0(int unused, float *p, int n)
{
    float *v;
    int count;
    if (n <= 0)
        return;
    v = p;
    count = n;
    do {
        v[0] = LVL_5_FELTZIN_SYSTEM_F307ea0ee_FUN_00307620(v[0], v[3]);
        v[1] = LVL_5_FELTZIN_SYSTEM_F307ea0ee_FUN_00307620(v[1], v[4]);
        v[2] = LVL_5_FELTZIN_SYSTEM_F307ea0ee_FUN_00307620(v[2], v[5]);
        v[9] = LVL_5_FELTZIN_SYSTEM_F307ea0ee_FUN_00307620(v[9], v[12]);
        v[10] = LVL_5_FELTZIN_SYSTEM_F307ea0ee_FUN_00307620(v[10], v[13]);
        v[11] = LVL_5_FELTZIN_SYSTEM_F307ea0ee_FUN_00307620(v[11], v[14]);
        v[20] = LVL_5_FELTZIN_SYSTEM_F307ea0ee_FUN_00306C08(v[0]) * v[6];
        v[21] = LVL_5_FELTZIN_SYSTEM_F307ea0ee_FUN_00306C20(v[1]) * v[7];
        v[22] = -LVL_5_FELTZIN_SYSTEM_F307ea0ee_FUN_00306C20(v[2]) * v[8];
        v[24] = LVL_5_FELTZIN_SYSTEM_F307ea0ee_FUN_00306C08(v[9]) * v[15];
        v[25] = LVL_5_FELTZIN_SYSTEM_F307ea0ee_FUN_00306C20(v[10]) * v[16];
        v[26] = -LVL_5_FELTZIN_SYSTEM_F307ea0ee_FUN_00306C20(v[11]) * v[17];
        v += 32;
    } while (--count != 0);
}
extern float LVL_5_FELTZIN_SYSTEM_F307ea0ee_FUN_00307620(float, float);
extern float LVL_5_FELTZIN_SYSTEM_F307ea0ee_FUN_00307620(float, float);
extern float LVL_5_FELTZIN_SYSTEM_F307ea0ee_FUN_00307620(float, float);
extern float LVL_5_FELTZIN_SYSTEM_F307ea0ee_FUN_00307620(float, float);
extern float LVL_5_FELTZIN_SYSTEM_F307ea0ee_FUN_00307620(float, float);
extern float LVL_5_FELTZIN_SYSTEM_F307ea0ee_FUN_00307620(float, float);
extern float LVL_5_FELTZIN_SYSTEM_F307ea0ee_FUN_00306C08(float);
extern float LVL_5_FELTZIN_SYSTEM_F307ea0ee_FUN_00306C20(float);
extern float LVL_5_FELTZIN_SYSTEM_F307ea0ee_FUN_00306C20(float);
extern float LVL_5_FELTZIN_SYSTEM_F307ea0ee_FUN_00306C08(float);
extern float LVL_5_FELTZIN_SYSTEM_F307ea0ee_FUN_00306C20(float);
extern float LVL_5_FELTZIN_SYSTEM_F307ea0ee_FUN_00306C20(float);

void LVL_5_FELTZIN_SYSTEM_FUN_003F1830(int unused, float *p, int n)
{
    float *v;
    int count;
    if (n <= 0)
        return;
    v = p;
    count = n;
    do {
        v[0] = LVL_5_FELTZIN_SYSTEM_F307ea0ee_FUN_00307620(v[0], v[3]);
        v[1] = LVL_5_FELTZIN_SYSTEM_F307ea0ee_FUN_00307620(v[1], v[4]);
        v[2] = LVL_5_FELTZIN_SYSTEM_F307ea0ee_FUN_00307620(v[2], v[5]);
        v[9] = LVL_5_FELTZIN_SYSTEM_F307ea0ee_FUN_00307620(v[9], v[12]);
        v[10] = LVL_5_FELTZIN_SYSTEM_F307ea0ee_FUN_00307620(v[10], v[13]);
        v[11] = LVL_5_FELTZIN_SYSTEM_F307ea0ee_FUN_00307620(v[11], v[14]);
        v[20] = LVL_5_FELTZIN_SYSTEM_F307ea0ee_FUN_00306C08(v[0]) * v[6];
        v[21] = LVL_5_FELTZIN_SYSTEM_F307ea0ee_FUN_00306C20(v[1]) * v[7];
        v[22] = -LVL_5_FELTZIN_SYSTEM_F307ea0ee_FUN_00306C20(v[2]) * v[8];
        v[24] = LVL_5_FELTZIN_SYSTEM_F307ea0ee_FUN_00306C08(v[9]) * v[15];
        v[25] = LVL_5_FELTZIN_SYSTEM_F307ea0ee_FUN_00306C20(v[10]) * v[16];
        v[26] = -LVL_5_FELTZIN_SYSTEM_F307ea0ee_FUN_00306C20(v[11]) * v[17];
        v += 32;
    } while (--count != 0);
}
#ifndef RAC2_T_WORKER_F9E2CD219
#define RAC2_T_WORKER_F9E2CD219
typedef struct {
    unsigned char pad00[76];
    short field4C;
    unsigned char pad4E[2];
    int field50;
    float field54;
    float field58;
} Worker_F9e2cd219;
#endif


#ifndef RAC2_T_OWNER_F9E2CD219
#define RAC2_T_OWNER_F9E2CD219
typedef struct {
    unsigned char pad00[104];
    Worker_F9e2cd219 *child;
} Owner_F9e2cd219;
#endif


extern float LVL_5_FELTZIN_SYSTEM_F9e2cd219_FUN_00332A30(float value);
extern void LVL_5_FELTZIN_SYSTEM_F9e2cd219_FUN_00338428(void *out, void *in, void *tmp, int mode, float value);
extern void LVL_5_FELTZIN_SYSTEM_F9e2cd219_FUN_0039E140(void *owner, void *out);

void LVL_5_FELTZIN_SYSTEM_FUN_0039E058(Owner_F9e2cd219 *self)
{
    Worker_F9e2cd219 *child = self->child;

    LVL_5_FELTZIN_SYSTEM_F9e2cd219_FUN_00338428((char *)child + 48, (char *)child + 16, (char *)child + 32, 0,
            LVL_5_FELTZIN_SYSTEM_F9e2cd219_FUN_00332A30(child->field54));

    child->field54 = child->field54 + child->field58;
    LVL_5_FELTZIN_SYSTEM_F9e2cd219_FUN_0039E140(self, (char *)child + 48);

    if (child->field54 > 0.9f)
        child->field50 = 1;
    else
        child->field50 = 0;

    if (child->field54 >= 1.0f) {
        child->field54 = 1.0f;
        child->field4C = 1;
    }
}
#ifndef RAC2_T_WORKER_F9E2CD219
#define RAC2_T_WORKER_F9E2CD219
typedef struct {
    unsigned char pad00[76];
    short field4C;
    unsigned char pad4E[2];
    int field50;
    float field54;
    float field58;
} Worker_F9e2cd219;
#endif


#ifndef RAC2_T_OWNER_F9E2CD219
#define RAC2_T_OWNER_F9E2CD219
typedef struct {
    unsigned char pad00[104];
    Worker_F9e2cd219 *child;
} Owner_F9e2cd219;
#endif


extern float LVL_5_FELTZIN_SYSTEM_F9e2cd219_FUN_00332A30(float value);
extern void LVL_5_FELTZIN_SYSTEM_F9e2cd219_FUN_00338428(void *out, void *in, void *tmp, int mode, float value);
extern void LVL_5_FELTZIN_SYSTEM_F9e2cd219_FUN_003A0BE0(void *owner, void *out);

void LVL_5_FELTZIN_SYSTEM_FUN_003A0AF8(Owner_F9e2cd219 *self)
{
    Worker_F9e2cd219 *child = self->child;

    LVL_5_FELTZIN_SYSTEM_F9e2cd219_FUN_00338428((char *)child + 48, (char *)child + 16, (char *)child + 32, 0,
            LVL_5_FELTZIN_SYSTEM_F9e2cd219_FUN_00332A30(child->field54));

    child->field54 = child->field54 + child->field58;
    LVL_5_FELTZIN_SYSTEM_F9e2cd219_FUN_003A0BE0(self, (char *)child + 48);

    if (child->field54 > 0.9f)
        child->field50 = 1;
    else
        child->field50 = 0;

    if (child->field54 >= 1.0f) {
        child->field54 = 1.0f;
        child->field4C = 1;
    }
}
extern void LVL_5_FELTZIN_SYSTEM_F6df9730c_FUN_003064A8(char *dst, int *src, int count);

void LVL_5_FELTZIN_SYSTEM_FUN_00320F58(char *dst, unsigned char *src)
{
    int table[256];
    int tmp[16];
    int *q;
    int i, j, k;

    for (i = 0; i < 256; i++) {
        table[i] = 0;
        if (i & 0x01) table[i] = 0x0000000f;
        if (i & 0x02) table[i] |= 0x000000f0;
        if (i & 0x04) table[i] |= 0x00000f00;
        if (i & 0x08) table[i] |= 0x0000f000;
        if (i & 0x10) table[i] |= 0x000f0000;
        if (i & 0x20) table[i] |= 0x00f00000;
        if (i & 0x40) table[i] |= 0x0f000000;
        if (i & 0x80) table[i] |= 0xf0000000;
    }
    for (j = 0; j < 128; j++) {
        char *next;
        q = tmp;
        next = dst + 64;
        for (k = 15; k >= 0; k--) {
            *q++ = table[*src++];
        }
        LVL_5_FELTZIN_SYSTEM_F6df9730c_FUN_003064A8(dst, tmp, 64);
        dst = next;
        LVL_5_FELTZIN_SYSTEM_F6df9730c_FUN_003064A8(dst, tmp, 64);
        dst += 64;
        LVL_5_FELTZIN_SYSTEM_F6df9730c_FUN_003064A8(dst, tmp, 64);
        dst += 64;
        LVL_5_FELTZIN_SYSTEM_F6df9730c_FUN_003064A8(dst, tmp, 64);
        dst += 64;
    }
}
extern void LVL_5_FELTZIN_SYSTEM_Fdb046c5d_FUN_002F4D40(void *);
extern void LVL_5_FELTZIN_SYSTEM_Fdb046c5d_FUN_002F4B80(void *);
extern int LVL_5_FELTZIN_SYSTEM_Fdb046c5d_FUN_002F4F58(void *);
extern void LVL_5_FELTZIN_SYSTEM_Fdb046c5d_FUN_003068F8(float, void *, void *);
extern void LVL_5_FELTZIN_SYSTEM_Fdb046c5d_FUN_00306748(void *, void *, void *);
extern void LVL_5_FELTZIN_SYSTEM_Fdb046c5d_FUN_002F54E0(void *, void *, void *);
extern void LVL_5_FELTZIN_SYSTEM_Fdb046c5d_FUN_0033C3F8(void *, void *, int);
extern int LVL_5_FELTZIN_SYSTEM_Fdb046c5d_FUN_002F5600(void *, void *, void *, float, float);
extern int LVL_5_FELTZIN_SYSTEM_Fdb046c5d_FUN_00371900(int, int, void *);
extern void LVL_5_FELTZIN_SYSTEM_Fdb046c5d_FUN_002F51C0(void *, int, void *);
extern int LVL_5_FELTZIN_SYSTEM_Fdb046c5d_FUN_00371900(int, int, void *);
extern void LVL_5_FELTZIN_SYSTEM_Fdb046c5d_FUN_00371C50(int, void *);
extern char LVL_5_FELTZIN_SYSTEM_Fdb046c5d_D_001BFB40[];

int LVL_5_FELTZIN_SYSTEM_FUN_002F4768(char *obj)
{
    float buf[4];
    float out[4];
    char *p;
    char *s1;
    unsigned char k;
    int r;
    int s4;
    int s5;

    p = *(char **)(obj + 104);
    k = *(unsigned char *)(p + 92);
    if (k >= 3)
        return 1;
    if (k != 0)
        LVL_5_FELTZIN_SYSTEM_Fdb046c5d_FUN_002F4D40(obj);
    else
        LVL_5_FELTZIN_SYSTEM_Fdb046c5d_FUN_002F4B80(obj);

    s5 = LVL_5_FELTZIN_SYSTEM_Fdb046c5d_FUN_002F4F58(obj);
    if (s5 == -1)
        return 0;

    s1 = LVL_5_FELTZIN_SYSTEM_Fdb046c5d_D_001BFB40;
    s4 = -1;
    LVL_5_FELTZIN_SYSTEM_Fdb046c5d_FUN_003068F8(1.0f, s1, s1);
    LVL_5_FELTZIN_SYSTEM_Fdb046c5d_FUN_00306748(buf, s1, p);
    LVL_5_FELTZIN_SYSTEM_Fdb046c5d_FUN_002F54E0(obj, p + 16, buf);
    LVL_5_FELTZIN_SYSTEM_Fdb046c5d_FUN_0033C3F8(obj + 16, out, 1);
    r = LVL_5_FELTZIN_SYSTEM_Fdb046c5d_FUN_002F5600(p, s1, out, *(float *)(p + 56), *(float *)(p + 60));
    if (r == 0) {
        if (*(unsigned char *)(p + 94) != 255 && *(unsigned char *)(p + 92) == 0)
            s4 = LVL_5_FELTZIN_SYSTEM_Fdb046c5d_FUN_00371900(*(unsigned char *)(p + 94), 0, obj);
        LVL_5_FELTZIN_SYSTEM_Fdb046c5d_FUN_002F51C0(obj, s5, out);
    } else {
        if (*(unsigned char *)(p + 94) != 255)
            s4 = LVL_5_FELTZIN_SYSTEM_Fdb046c5d_FUN_00371900(*(unsigned char *)(p + 94), 0, obj);
    }
    if (s4 != -1)
        LVL_5_FELTZIN_SYSTEM_Fdb046c5d_FUN_00371C50(s4, p + 32);
    return 0;
}
extern void LVL_5_FELTZIN_SYSTEM_F7242f0a4_FUN_003066A0(char *out, void *source, float value);
extern void LVL_5_FELTZIN_SYSTEM_F7242f0a4_FUN_004389D8(char *buffer, int mode);
extern void LVL_5_FELTZIN_SYSTEM_F7242f0a4_FUN_00438878(int value, char *buffer);
extern void LVL_5_FELTZIN_SYSTEM_F7242f0a4_FUN_00306630(char *first, char *second, char *third);
extern float LVL_5_FELTZIN_SYSTEM_F7242f0a4_FUN_00306720(void *owner, char *buffer);

extern int LVL_5_FELTZIN_SYSTEM_F7242f0a4_D_001B9720[];

void LVL_5_FELTZIN_SYSTEM_FUN_004390A0(void *owner, int flag, float value)
{
    char buffer[32];
    int *root = LVL_5_FELTZIN_SYSTEM_F7242f0a4_D_001B9720;

    LVL_5_FELTZIN_SYSTEM_F7242f0a4_FUN_003066A0(buffer, root + 8, value);
    if (flag)
        LVL_5_FELTZIN_SYSTEM_F7242f0a4_FUN_004389D8(buffer + 16, 1);
    else
        LVL_5_FELTZIN_SYSTEM_F7242f0a4_FUN_00438878(root[-4], buffer + 16);
    LVL_5_FELTZIN_SYSTEM_F7242f0a4_FUN_00306630(buffer, buffer, buffer + 16);
    LVL_5_FELTZIN_SYSTEM_F7242f0a4_FUN_003066A0(owner, root + 12, LVL_5_FELTZIN_SYSTEM_F7242f0a4_FUN_00306720(root + 12, buffer));
}
extern char LVL_5_FELTZIN_SYSTEM_F45821cfb_D_001C7440[];
extern void LVL_5_FELTZIN_SYSTEM_F45821cfb_FUN_003065F8(char *);

void LVL_5_FELTZIN_SYSTEM_FUN_0045FC18(void)
{
    float *p = (float *)LVL_5_FELTZIN_SYSTEM_F45821cfb_D_001C7440;

    p[224] = 0.4f;
    p[225] = 0.8f;
    p[226] = 1.2f;
    *(int *)&p[227] = 0;
    p[228] = 0.577f;
    p[229] = 0.577f;
    p[230] = -0.577f;
    *(int *)&p[231] = 0;
    LVL_5_FELTZIN_SYSTEM_F45821cfb_FUN_003065F8((char *)&p[232]);
    LVL_5_FELTZIN_SYSTEM_F45821cfb_FUN_003065F8((char *)&p[236]);
}
extern char LVL_5_FELTZIN_SYSTEM_Fd8e166aa_D_001BCB00[];

void LVL_5_FELTZIN_SYSTEM_FUN_002FBED8(void)
{
    char *g = LVL_5_FELTZIN_SYSTEM_Fd8e166aa_D_001BCB00;
    int i = 0;
    int *table = *(int **)(g + 8);
    char *p = (char *)table + table[*(unsigned char *)0x1A7BB4];
    int n = *(int *)p;

    *(char **)(g + 12) = p + 8;
    *(int *)(g + 16) = n;
    for (i = 0; i < *(int *)(g + 16); i++) {
        char *q = *(char **)(g + 12);
        char *r = q - 8;

        *(int *)(q + i * 16) = *(int *)(q + i * 16) + (int)r;
    }
}
extern char LVL_5_FELTZIN_SYSTEM_F7cb419c1_D_001FF540[];

extern int LVL_5_FELTZIN_SYSTEM_F7cb419c1_FUN_00369FD0(int arg);

int LVL_5_FELTZIN_SYSTEM_FUN_003607C8(void)
{
    char *p = LVL_5_FELTZIN_SYSTEM_F7cb419c1_D_001FF540;

    *(int *)(p + 460) = LVL_5_FELTZIN_SYSTEM_F7cb419c1_FUN_00369FD0(*(int *)(p + 460));
    return 0;
}
extern char LVL_5_FELTZIN_SYSTEM_F0a76d85b_D_001B9580[];

extern void LVL_5_FELTZIN_SYSTEM_F0a76d85b_FUN_00306DE8(char *p);
extern void LVL_5_FELTZIN_SYSTEM_F0a76d85b_FUN_002FC6A0(void);

void LVL_5_FELTZIN_SYSTEM_FUN_0045FCA8(void)
{
    char *p = LVL_5_FELTZIN_SYSTEM_F0a76d85b_D_001B9580;

    *(int *)(p + 320) = 0;
    *(int *)(p + 324) = 0;
    *(int *)(p + 328) = 0;
    LVL_5_FELTZIN_SYSTEM_F0a76d85b_FUN_00306DE8(p + 880);
    LVL_5_FELTZIN_SYSTEM_F0a76d85b_FUN_002FC6A0();
}
extern char LVL_5_FELTZIN_SYSTEM_F391de845_D_001B96C0[];
extern float LVL_5_FELTZIN_SYSTEM_F391de845_FUN_003067D8(char *a, char *b);
extern float LVL_5_FELTZIN_SYSTEM_F391de845_FUN_00370350(void *self, float d, float x, float y);

float LVL_5_FELTZIN_SYSTEM_FUN_00370448(char *self, char *p)
{
    float v = LVL_5_FELTZIN_SYSTEM_F391de845_FUN_003067D8(p, LVL_5_FELTZIN_SYSTEM_F391de845_D_001B96C0);
    float *q = *(float **)(self + 8);

    return LVL_5_FELTZIN_SYSTEM_F391de845_FUN_00370350(q, v, q[0], q[1]);
}
extern int LVL_5_FELTZIN_SYSTEM_F2f080549_D_001A8FF4 __attribute__((sda));
extern char LVL_5_FELTZIN_SYSTEM_F2f080549_D_001B2190[] __attribute__((sda));
extern char LVL_5_FELTZIN_SYSTEM_F2f080549_D_001A9000[] __attribute__((sda));
extern float LVL_5_FELTZIN_SYSTEM_F2f080549_FUN_003067D8(char *a, char *b);

float LVL_5_FELTZIN_SYSTEM_FUN_0033C5F8(char *p)
{
    float v;

    if (LVL_5_FELTZIN_SYSTEM_F2f080549_D_001A8FF4 == 0) {
        v = LVL_5_FELTZIN_SYSTEM_F2f080549_FUN_003067D8(p, LVL_5_FELTZIN_SYSTEM_F2f080549_D_001B2190);
    } else {
        v = 100.0f - LVL_5_FELTZIN_SYSTEM_F2f080549_FUN_003067D8(p, LVL_5_FELTZIN_SYSTEM_F2f080549_D_001A9000);
    }
    return v;
}
extern char LVL_5_FELTZIN_SYSTEM_Fa76f1772_D_001BFB20[];
extern void LVL_5_FELTZIN_SYSTEM_Fa76f1772_FUN_00306660(char *local, char *data);
extern float LVL_5_FELTZIN_SYSTEM_Fa76f1772_FUN_00306720(char *local, char *p);

int LVL_5_FELTZIN_SYSTEM_FUN_0043C578(int a0, int a1)
{
    char local[16];
    int s0;
    int r;

    if (a1 != 1) {
        r = 0;
    } else {
        s0 = *(int *)(a0 + 112) + 352;
        LVL_5_FELTZIN_SYSTEM_Fa76f1772_FUN_00306660(local, LVL_5_FELTZIN_SYSTEM_Fa76f1772_D_001BFB20);
        r = LVL_5_FELTZIN_SYSTEM_Fa76f1772_FUN_00306720(local, (char *)s0) < 0.0f ? 1 : 0;
    }
    return r;
}
extern void LVL_5_FELTZIN_SYSTEM_F46b43b72_FUN_00340CB0(int value, char *target);
extern void LVL_5_FELTZIN_SYSTEM_F46b43b72_FUN_00340E78(int value);

extern int LVL_5_FELTZIN_SYSTEM_F46b43b72_D_001BD3C0[];
extern int LVL_5_FELTZIN_SYSTEM_F46b43b72_D_0014B540[];

int LVL_5_FELTZIN_SYSTEM_FUN_0031CAA0(int index)
{
    int j = index + 1;
    int *d = LVL_5_FELTZIN_SYSTEM_F46b43b72_D_001BD3C0;
    int *b = LVL_5_FELTZIN_SYSTEM_F46b43b72_D_0014B540;
    int *t = (int *)((char *)b + 25416);
    int n = d[12] * 332;
    int hold = d[28];
    int j4 = j * 4;
    int cur = *(int *)((char *)t + (n + index * 4));
    int next = *(int *)((char *)t + (j4 + n));

    n = next - cur;
    if (n > 0) {
        LVL_5_FELTZIN_SYSTEM_F46b43b72_FUN_00340CB0(hold, (char *)(cur + b[6341]));
        LVL_5_FELTZIN_SYSTEM_F46b43b72_FUN_00340E78(0);
    }
    return 1;
}
extern void LVL_5_FELTZIN_SYSTEM_Fa2d20de7_FUN_00332C60(void *object, float first, float second);
extern void LVL_5_FELTZIN_SYSTEM_Fa2d20de7_FUN_00306630(char *first, char *second, void *third);
extern int LVL_5_FELTZIN_SYSTEM_Fa2d20de7_FUN_002F6C50(void *first, char *second, int mode, int value, int extra);
extern void LVL_5_FELTZIN_SYSTEM_Fa2d20de7_FUN_00306660(void *first, void *second, void *third);
extern void LVL_5_FELTZIN_SYSTEM_Fa2d20de7_FUN_003066A0(void *first, void *second, float value);

extern short LVL_5_FELTZIN_SYSTEM_Fa2d20de7_D_001B96C0[];
extern short LVL_5_FELTZIN_SYSTEM_Fa2d20de7_D_001BFB20[];
extern int LVL_5_FELTZIN_SYSTEM_Fa2d20de7_D_001886CC[];

void LVL_5_FELTZIN_SYSTEM_FUN_00370200(void *object)
{
    LVL_5_FELTZIN_SYSTEM_Fa2d20de7_FUN_00332C60(object, 0.5f, 6.0f);
    LVL_5_FELTZIN_SYSTEM_Fa2d20de7_FUN_00306630(object, object, LVL_5_FELTZIN_SYSTEM_Fa2d20de7_D_001B96C0);
    if (LVL_5_FELTZIN_SYSTEM_Fa2d20de7_FUN_002F6C50(LVL_5_FELTZIN_SYSTEM_Fa2d20de7_D_001B96C0, object, 130, LVL_5_FELTZIN_SYSTEM_Fa2d20de7_D_001886CC[0], 0)) {
        LVL_5_FELTZIN_SYSTEM_Fa2d20de7_FUN_00306660(object, LVL_5_FELTZIN_SYSTEM_Fa2d20de7_D_001BFB20, LVL_5_FELTZIN_SYSTEM_Fa2d20de7_D_001B96C0);
        LVL_5_FELTZIN_SYSTEM_Fa2d20de7_FUN_003066A0(object, object, 0.75f);
        LVL_5_FELTZIN_SYSTEM_Fa2d20de7_FUN_00306630(object, object, LVL_5_FELTZIN_SYSTEM_Fa2d20de7_D_001B96C0);
    }
}
extern char LVL_5_FELTZIN_SYSTEM_F15d5f4fb_D_001B9580[];
extern char LVL_5_FELTZIN_SYSTEM_F15d5f4fb_D_00189E20[];
extern float LVL_5_FELTZIN_SYSTEM_F15d5f4fb_FUN_00306CD0(float a, float b);
extern float LVL_5_FELTZIN_SYSTEM_F15d5f4fb_FUN_00307708(float a, float b);
extern float LVL_5_FELTZIN_SYSTEM_F15d5f4fb_FUN_003067D8(char *a, char *b);

void LVL_5_FELTZIN_SYSTEM_FUN_004408D0(char *o)
{
    char *B = LVL_5_FELTZIN_SYSTEM_F15d5f4fb_D_001B9580;
    char *D = LVL_5_FELTZIN_SYSTEM_F15d5f4fb_D_00189E20;
    float *p = *(float **)(D + 8848);
    float r = LVL_5_FELTZIN_SYSTEM_F15d5f4fb_FUN_00307708(*(float *)(B + 344),
                      LVL_5_FELTZIN_SYSTEM_F15d5f4fb_FUN_00306CD0(p[4] - *(float *)(B + 320),
                              p[5] - *(float *)(B + 324)));

    if (r < 0.5585054f) {
        r = LVL_5_FELTZIN_SYSTEM_F15d5f4fb_FUN_003067D8(D + 128, B + 320);
        if (r < 8.0f) {
            *(char *)(B + 659) = 0;
            *(short *)(o + 126) = 2;
            *(float *)(B + 692) = 0.018f;
            *(float *)(B + 680) = 0.018f;
        } else {
            *(short *)(o + 126) = 4;
        }
    } else {
        *(short *)(o + 126) = 4;
    }
    *(char *)(o + 125) = 0;
}

#ifndef RAC2_T_S8_F4778F810
#define RAC2_T_S8_F4778F810
typedef signed char s8_F4778f810;
#endif

#ifndef RAC2_T_S16_F4778F810
#define RAC2_T_S16_F4778F810
typedef signed short s16_F4778f810;
#endif

#ifndef RAC2_T_U16_F4778F810
#define RAC2_T_U16_F4778F810
typedef unsigned short u16_F4778f810;
#endif





extern void LVL_5_FELTZIN_SYSTEM_F4778f810_FUN_0033C548(char *a, char *b, char *c, f32 d);
extern void LVL_5_FELTZIN_SYSTEM_F4778f810_FUN_00306630(char *a, char *b, char *c);
extern void LVL_5_FELTZIN_SYSTEM_F4778f810_FUN_00306AD8(char *a, char *b, char *c);
extern void LVL_5_FELTZIN_SYSTEM_F4778f810_FUN_003073E0(char *a, char *b);
extern void LVL_5_FELTZIN_SYSTEM_F4778f810_FUN_003071C0(char *a, char *b, char *c);
extern void LVL_5_FELTZIN_SYSTEM_F4778f810_FUN_00306AD8(char *a, char *b, char *c);
extern void LVL_5_FELTZIN_SYSTEM_F4778f810_FUN_00306660(char *a, char *b, char *c);
extern void LVL_5_FELTZIN_SYSTEM_F4778f810_FUN_00306660(char *a, char *b, char *c);

#ifndef RAC2_T_V4_F4778F810
#define RAC2_T_V4_F4778F810
typedef struct {
    f32 x, y, z, w;
} V4_F4778f810;
#endif


#ifndef RAC2_T_SUB_F4778F810
#define RAC2_T_SUB_F4778F810
typedef struct {
    u8 pad000[0x10];
    u8 at010[0x10];
    u8 at020[0x28];
    f32 f048;
} Sub_F4778f810;
#endif


#ifndef RAC2_T_OBJ_F4778F810
#define RAC2_T_OBJ_F4778F810
typedef struct {
    u8 pad000[0x10];
    u8 at010[0x58];
    char *p068;
    u8 pad06C[0xC0 - 0x6C];
    u8 at0C0[0x10];
} Obj_F4778f810;
#endif


void LVL_5_FELTZIN_SYSTEM_FUN_002F4B80(Obj_F4778f810 *obj)
{
    V4_F4778f810 tmp[6];
    Sub_F4778f810 *p = (Sub_F4778f810 *)obj->p068;

    LVL_5_FELTZIN_SYSTEM_F4778f810_FUN_0033C548((char *)obj + 0x10, (char *)p, (char *)p, p->f048);
    LVL_5_FELTZIN_SYSTEM_F4778f810_FUN_00306630((char *)obj + 0x10, (char *)obj + 0x10, (char *)p);
    LVL_5_FELTZIN_SYSTEM_F4778f810_FUN_00306AD8((char *)&tmp[0], (char *)p + 0x20, (char *)obj + 0xC0);
    LVL_5_FELTZIN_SYSTEM_F4778f810_FUN_003073E0((char *)p + 0x10, (char *)&tmp[3]);
    LVL_5_FELTZIN_SYSTEM_F4778f810_FUN_003071C0((char *)obj + 0xC0, (char *)&tmp[3], (char *)obj + 0xC0);
    LVL_5_FELTZIN_SYSTEM_F4778f810_FUN_00306AD8((char *)&tmp[1], (char *)p + 0x20, (char *)obj + 0xC0);
    LVL_5_FELTZIN_SYSTEM_F4778f810_FUN_00306660((char *)&tmp[2], (char *)&tmp[1], (char *)&tmp[0]);
    LVL_5_FELTZIN_SYSTEM_F4778f810_FUN_00306660((char *)obj + 0x10, (char *)obj + 0x10, (char *)&tmp[2]);
}

#ifndef RAC2_T_S8_F4778F810
#define RAC2_T_S8_F4778F810
typedef signed char s8_F4778f810;
#endif

#ifndef RAC2_T_S16_F4778F810
#define RAC2_T_S16_F4778F810
typedef signed short s16_F4778f810;
#endif

#ifndef RAC2_T_U16_F4778F810
#define RAC2_T_U16_F4778F810
typedef unsigned short u16_F4778f810;
#endif





extern void LVL_5_FELTZIN_SYSTEM_F4778f810_FUN_0033C548(char *a, char *b, char *c, f32 d);
extern void LVL_5_FELTZIN_SYSTEM_F4778f810_FUN_00306630(char *a, char *b, char *c);
extern void LVL_5_FELTZIN_SYSTEM_F4778f810_FUN_00306AD8(char *a, char *b, char *c);
extern void LVL_5_FELTZIN_SYSTEM_F4778f810_FUN_003073E0(char *a, char *b);
extern void LVL_5_FELTZIN_SYSTEM_F4778f810_FUN_003071C0(char *a, char *b, char *c);
extern void LVL_5_FELTZIN_SYSTEM_F4778f810_FUN_00306AD8(char *a, char *b, char *c);
extern void LVL_5_FELTZIN_SYSTEM_F4778f810_FUN_00306660(char *a, char *b, char *c);
extern void LVL_5_FELTZIN_SYSTEM_F4778f810_FUN_00306660(char *a, char *b, char *c);

#ifndef RAC2_T_V4_F4778F810
#define RAC2_T_V4_F4778F810
typedef struct {
    f32 x, y, z, w;
} V4_F4778f810;
#endif


#ifndef RAC2_T_SUB_F4778F810
#define RAC2_T_SUB_F4778F810
typedef struct {
    u8 pad000[0x10];
    u8 at010[0x10];
    u8 at020[0x28];
    f32 f048;
} Sub_F4778f810;
#endif


#ifndef RAC2_T_OBJ_F4778F810
#define RAC2_T_OBJ_F4778F810
typedef struct {
    u8 pad000[0x10];
    u8 at010[0x58];
    char *p068;
    u8 pad06C[0xC0 - 0x6C];
    u8 at0C0[0x10];
} Obj_F4778f810;
#endif


void LVL_5_FELTZIN_SYSTEM_FUN_002F4C60(Obj_F4778f810 *obj)
{
    V4_F4778f810 tmp[6];
    Sub_F4778f810 *p = (Sub_F4778f810 *)obj->p068;

    LVL_5_FELTZIN_SYSTEM_F4778f810_FUN_0033C548((char *)obj + 0x10, (char *)p, (char *)p, p->f048);
    LVL_5_FELTZIN_SYSTEM_F4778f810_FUN_00306630((char *)obj + 0x10, (char *)obj + 0x10, (char *)p);
    LVL_5_FELTZIN_SYSTEM_F4778f810_FUN_00306AD8((char *)&tmp[0], (char *)p + 0x20, (char *)obj + 0xC0);
    LVL_5_FELTZIN_SYSTEM_F4778f810_FUN_003073E0((char *)p + 0x10, (char *)&tmp[3]);
    LVL_5_FELTZIN_SYSTEM_F4778f810_FUN_003071C0((char *)obj + 0xC0, (char *)&tmp[3], (char *)obj + 0xC0);
    LVL_5_FELTZIN_SYSTEM_F4778f810_FUN_00306AD8((char *)&tmp[1], (char *)p + 0x20, (char *)obj + 0xC0);
    LVL_5_FELTZIN_SYSTEM_F4778f810_FUN_00306660((char *)&tmp[2], (char *)&tmp[1], (char *)&tmp[0]);
    LVL_5_FELTZIN_SYSTEM_F4778f810_FUN_00306660((char *)obj + 0x10, (char *)obj + 0x10, (char *)&tmp[2]);
}
extern char *LVL_5_FELTZIN_SYSTEM_Fa5c6e8ca_FUN_00379CA0(char *object, int flag);
extern void LVL_5_FELTZIN_SYSTEM_Fa5c6e8ca_FUN_003065F8(char *target);
extern void LVL_5_FELTZIN_SYSTEM_Fa5c6e8ca_FUN_0037BB28(char *object);
extern void LVL_5_FELTZIN_SYSTEM_Fa5c6e8ca_FUN_0037CD80(char *object, int value);
extern void LVL_5_FELTZIN_SYSTEM_Fa5c6e8ca_FUN_0037CDD8(char *object, int value);
extern void LVL_5_FELTZIN_SYSTEM_Fa5c6e8ca_FUN_0037D210(char *object);
extern void LVL_5_FELTZIN_SYSTEM_Fa5c6e8ca_FUN_0037AE40(char *object);
extern int LVL_5_FELTZIN_SYSTEM_Fa5c6e8ca_D_00221D10[];

void LVL_5_FELTZIN_SYSTEM_FUN_0037AEC0(char *object, int flag)
{
    char *s;
    int **slot;

    s = LVL_5_FELTZIN_SYSTEM_Fa5c6e8ca_FUN_00379CA0(object, flag);
    if (s == 0)
        return;

    *(short *)(object + 50) = 511;
    *(unsigned char *)(object + 48) = 255;
    *(short *)(object + 52) = *(unsigned short *)(object + 52) & 0xfffc;
    *(int *)(object + 152) = *(int *)(*(int *)(object + 36) + 16);
    *(int *)(s + 272) = 1;
    *(int *)(s + 248) = 0;
    LVL_5_FELTZIN_SYSTEM_Fa5c6e8ca_FUN_003065F8(s + 112);
    *(int *)(s + 268) = 0;
    *(int *)(s + 280) = 0;
    *(int *)(s + 252) = 0;
    *(int *)(s + 308) = 0;
    *(int *)(s + 332) = 1;
    *(int *)(s + 348) = 0;
    slot = *(int ***)(object + 104);
    *(float *)*slot = (float)*(int *)(s + 328);
    LVL_5_FELTZIN_SYSTEM_Fa5c6e8ca_D_00221D10[4] = LVL_5_FELTZIN_SYSTEM_Fa5c6e8ca_D_00221D10[4] + 1;
    LVL_5_FELTZIN_SYSTEM_Fa5c6e8ca_FUN_0037BB28(object);
    LVL_5_FELTZIN_SYSTEM_Fa5c6e8ca_FUN_0037CD80(object, 1);
    LVL_5_FELTZIN_SYSTEM_Fa5c6e8ca_FUN_0037CDD8(object, 1);
    if (flag)
        LVL_5_FELTZIN_SYSTEM_Fa5c6e8ca_FUN_0037D210(object);
    if (LVL_5_FELTZIN_SYSTEM_Fa5c6e8ca_D_00221D10[13] == 1)
        LVL_5_FELTZIN_SYSTEM_Fa5c6e8ca_FUN_0037AE40(object);
}


extern void LVL_5_FELTZIN_SYSTEM_Fd160fb9c_FUN_002BEA48(int arg0, int arg1, int arg2, int arg3);
extern int LVL_5_FELTZIN_SYSTEM_Fd160fb9c_FUN_002CC218(float value);
extern void LVL_5_FELTZIN_SYSTEM_Fd160fb9c_FUN_002BEA48(int arg0, int arg1, int arg2, int arg3);
extern int LVL_5_FELTZIN_SYSTEM_Fd160fb9c_FUN_002CC218(float value);
extern void LVL_5_FELTZIN_SYSTEM_Fd160fb9c_FUN_002BEA48(int arg0, int arg1, int arg2, int arg3);
extern int LVL_5_FELTZIN_SYSTEM_Fd160fb9c_FUN_002CC218(float value);
extern void LVL_5_FELTZIN_SYSTEM_Fd160fb9c_FUN_002BEA48(int arg0, int arg1, int arg2, int arg3);
extern int LVL_5_FELTZIN_SYSTEM_Fd160fb9c_FUN_002CC218(float value);
extern void LVL_5_FELTZIN_SYSTEM_Fd160fb9c_FUN_002BEA48(int arg0, int arg1, int arg2, int arg3);
extern int LVL_5_FELTZIN_SYSTEM_Fd160fb9c_FUN_002CC218(float value);
extern void LVL_5_FELTZIN_SYSTEM_Fd160fb9c_FUN_002BEA48(int arg0, int arg1, int arg2, int arg3);

#ifndef RAC2_T_RESIDENTSTATE_FD160FB9C
#define RAC2_T_RESIDENTSTATE_FD160FB9C
typedef struct {
    u8 pad000[0x1b8];
    int f1B8;
    u8 pad1bc[0xc2c - 0x1bc];
    int fC2C;
    u8 padc30[0x149d - 0xc30];
    u8 b149D;
    u8 pad149e[0x2290 - 0x149e];
    u8 *p2290;
    int f2294;
} ResidentState_Fd160fb9c;
#endif


extern ResidentState_Fd160fb9c LVL_5_FELTZIN_SYSTEM_Fd160fb9c_D_00189E20;

void LVL_5_FELTZIN_SYSTEM_FUN_002BECA0(void)
{
    int selector;

    if (LVL_5_FELTZIN_SYSTEM_Fd160fb9c_D_00189E20.f2294 == 2) {
        if (LVL_5_FELTZIN_SYSTEM_Fd160fb9c_D_00189E20.f1B8 < 15)
            return;
    }

    selector = LVL_5_FELTZIN_SYSTEM_Fd160fb9c_D_00189E20.b149D;

    if (LVL_5_FELTZIN_SYSTEM_Fd160fb9c_D_00189E20.f2294 == 2) {
        if (LVL_5_FELTZIN_SYSTEM_Fd160fb9c_D_00189E20.f1B8 == 22)
            LVL_5_FELTZIN_SYSTEM_Fd160fb9c_FUN_002BEA48(selector, 0, 1, 30);
    }

    switch (LVL_5_FELTZIN_SYSTEM_Fd160fb9c_D_00189E20.p2290[67]) {
    case 3:
        if (LVL_5_FELTZIN_SYSTEM_Fd160fb9c_D_00189E20.fC2C != 0)
            return;
        if (LVL_5_FELTZIN_SYSTEM_Fd160fb9c_FUN_002CC218(49.5f) != 0)
            LVL_5_FELTZIN_SYSTEM_Fd160fb9c_FUN_002BEA48(selector, 0, 1, 30);
        if (LVL_5_FELTZIN_SYSTEM_Fd160fb9c_FUN_002CC218(17.0f) != 0)
            LVL_5_FELTZIN_SYSTEM_Fd160fb9c_FUN_002BEA48(selector, 1, 1, 30);
        return;
    case 4:
        if (LVL_5_FELTZIN_SYSTEM_Fd160fb9c_D_00189E20.fC2C != 0)
            return;
        if (LVL_5_FELTZIN_SYSTEM_Fd160fb9c_FUN_002CC218(12.5f) != 0)
            LVL_5_FELTZIN_SYSTEM_Fd160fb9c_FUN_002BEA48(selector, 0, 1, 30);
        if (LVL_5_FELTZIN_SYSTEM_Fd160fb9c_FUN_002CC218(1.0f) != 0)
            LVL_5_FELTZIN_SYSTEM_Fd160fb9c_FUN_002BEA48(selector, 1, 1, 30);
        return;
    case 20:
        if (LVL_5_FELTZIN_SYSTEM_Fd160fb9c_D_00189E20.fC2C != 0)
            return;
        if (LVL_5_FELTZIN_SYSTEM_Fd160fb9c_FUN_002CC218(8.0f) != 0)
            LVL_5_FELTZIN_SYSTEM_Fd160fb9c_FUN_002BEA48(selector, 0, 1, 30);
        if (LVL_5_FELTZIN_SYSTEM_Fd160fb9c_FUN_002CC218(21.0f) != 0)
            LVL_5_FELTZIN_SYSTEM_Fd160fb9c_FUN_002BEA48(selector, 1, 1, 30);
        return;
    }
}
#ifndef RAC2_T_PERSISTENT_F882F1178
#define RAC2_T_PERSISTENT_F882F1178
typedef struct {
    unsigned char pad0[4960];
    void *p1360;
    void *p1364;
    void *p1368;
    unsigned char pad1[4512];
    float f250C;
    float f2510;
    float f2514;
} Persistent_F882f1178;
#endif


#ifndef RAC2_T_NODE_F882F1178
#define RAC2_T_NODE_F882F1178
typedef struct {
    unsigned char pad[120];
    int field120;
} Node_F882f1178;
#endif


extern Persistent_F882f1178 LVL_5_FELTZIN_SYSTEM_F882f1178_D_00189E20;
extern int LVL_5_FELTZIN_SYSTEM_F882f1178_D_001A8F00 __attribute__((sda));

extern float LVL_5_FELTZIN_SYSTEM_F882f1178_FUN_00307620(float, float);
extern float LVL_5_FELTZIN_SYSTEM_F882f1178_FUN_00306C20(float);
extern int LVL_5_FELTZIN_SYSTEM_F882f1178_FUN_003077C0(int, int, float);
extern float LVL_5_FELTZIN_SYSTEM_F882f1178_FUN_00307620(float, float);
extern float LVL_5_FELTZIN_SYSTEM_F882f1178_FUN_00307620(float, float);
extern float LVL_5_FELTZIN_SYSTEM_F882f1178_FUN_00306C20(float);
extern int LVL_5_FELTZIN_SYSTEM_F882f1178_FUN_003077C0(int, int, float);
extern void LVL_5_FELTZIN_SYSTEM_F882f1178_FUN_0033CD08(int, float *, int, int, float);
extern void LVL_5_FELTZIN_SYSTEM_F882f1178_FUN_0033CD08(int, float *, int, int, float);

void LVL_5_FELTZIN_SYSTEM_FUN_002ED270(void)
{
    Node_F882f1178 *node;

    node = (Node_F882f1178 *)LVL_5_FELTZIN_SYSTEM_F882f1178_D_00189E20.p1360;
    if (node != 0) {
        if (*(int *)0x1A8F00 == 2)
            LVL_5_FELTZIN_SYSTEM_F882f1178_D_00189E20.f250C = LVL_5_FELTZIN_SYSTEM_F882f1178_FUN_00307620(LVL_5_FELTZIN_SYSTEM_F882f1178_D_00189E20.f250C, 0.020362177863717079f);
        else
            LVL_5_FELTZIN_SYSTEM_F882f1178_D_00189E20.f250C = LVL_5_FELTZIN_SYSTEM_F882f1178_FUN_00307620(LVL_5_FELTZIN_SYSTEM_F882f1178_D_00189E20.f250C, 0.034906592220067978f);
        node->field120 = LVL_5_FELTZIN_SYSTEM_F882f1178_FUN_003077C0(0xd2d2d2, 0x285050,
                                 LVL_5_FELTZIN_SYSTEM_F882f1178_FUN_00306C20(LVL_5_FELTZIN_SYSTEM_F882f1178_D_00189E20.f250C) * 0.5f + 0.5f);
    }
    node = (Node_F882f1178 *)LVL_5_FELTZIN_SYSTEM_F882f1178_D_00189E20.p1364;
    if (node != 0) {
        if (LVL_5_FELTZIN_SYSTEM_F882f1178_D_001A8F00 != 2) {
            float limit;
            int which;

            limit = LVL_5_FELTZIN_SYSTEM_F882f1178_FUN_00307620(LVL_5_FELTZIN_SYSTEM_F882f1178_D_00189E20.f2510, 0.049451004713773727f);
            LVL_5_FELTZIN_SYSTEM_F882f1178_D_00189E20.f2510 = limit;
            which = 0x1ee628;
            if (limit > 0.0f && limit < 1.9198623895645142f) {
                which = 0x1e1ed2;
            }
            node->field120 = LVL_5_FELTZIN_SYSTEM_F882f1178_FUN_003077C0(node->field120, which, 0.070000000298023224f);
        } else {
            LVL_5_FELTZIN_SYSTEM_F882f1178_D_00189E20.f2510 = LVL_5_FELTZIN_SYSTEM_F882f1178_FUN_00307620(LVL_5_FELTZIN_SYSTEM_F882f1178_D_00189E20.f2510, 0.026179943233728409f);
            node->field120 = LVL_5_FELTZIN_SYSTEM_F882f1178_FUN_003077C0(0x1e1ed2, 0x1e1e50,
                                     LVL_5_FELTZIN_SYSTEM_F882f1178_FUN_00306C20(LVL_5_FELTZIN_SYSTEM_F882f1178_D_00189E20.f2510) * 0.5f + 0.5f);
        }
    }
    if (LVL_5_FELTZIN_SYSTEM_F882f1178_D_00189E20.p1368 != 0) {
        if (LVL_5_FELTZIN_SYSTEM_F882f1178_D_001A8F00 == 2)
            LVL_5_FELTZIN_SYSTEM_F882f1178_FUN_0033CD08((int)LVL_5_FELTZIN_SYSTEM_F882f1178_D_00189E20.p1368, &LVL_5_FELTZIN_SYSTEM_F882f1178_D_00189E20.f2514, 0xdcdcdc, 0x323232,
                    0.026179943233728409f);
        else
            LVL_5_FELTZIN_SYSTEM_F882f1178_FUN_0033CD08((int)LVL_5_FELTZIN_SYSTEM_F882f1178_D_00189E20.p1368, &LVL_5_FELTZIN_SYSTEM_F882f1178_D_00189E20.f2514, 0xdcdcdc, 0x323232,
                    0.040724355727434158f);
    }
}
extern void LVL_5_FELTZIN_SYSTEM_F8411efa9_FUN_003E5E38(char *pkt);
extern long long LVL_5_FELTZIN_SYSTEM_F8411efa9_FUN_002FEF40(char *p);
extern float LVL_5_FELTZIN_SYSTEM_F8411efa9_FUN_00306CD0(float x, float y);
extern float LVL_5_FELTZIN_SYSTEM_F8411efa9_FUN_00306790(char *p);
extern float LVL_5_FELTZIN_SYSTEM_F8411efa9_FUN_00306CD0(float x, float y);
extern void LVL_5_FELTZIN_SYSTEM_F8411efa9_FUN_00306E98(float *matrix, float *quat);
extern void LVL_5_FELTZIN_SYSTEM_F8411efa9_FUN_003068F8(float *off, char *src, float scale);
extern void LVL_5_FELTZIN_SYSTEM_F8411efa9_FUN_003E5EC0(char *pkt, float angle);
extern void LVL_5_FELTZIN_SYSTEM_F8411efa9_FUN_00303910(char *pkt, float *matrix, int mode);

void LVL_5_FELTZIN_SYSTEM_FUN_003E60E0(char *pos, int a1, int a2, char *a3, int t0,
                                        char *src, float f12, float f13)
{
    char pkt[144];
    float m[16];
    float quat[4];
    float off[4];
    long long r;

    LVL_5_FELTZIN_SYSTEM_F8411efa9_FUN_003E5E38(pkt);
    r = LVL_5_FELTZIN_SYSTEM_F8411efa9_FUN_002FEF40(a3);

    *(int *)(pkt + 76) = a1 + (a2 << 24);
    *(int *)(pkt + 72) = a1 + (a2 << 24);
    *(int *)(pkt + 68) = a1 + (a2 << 24);
    *(int *)(pkt + 64) = a1 + (a2 << 24);
    *(long long *)(pkt + 112) = 0LL;
    *(long long *)(pkt + 120) = r;
    *(long long *)(pkt + 128) = 280993940374112LL;
    *(long long *)(pkt + 136) = ((long long)t0 << 2) | 0x8000000040LL;

    quat[3] = 0.0f;
    quat[2] = LVL_5_FELTZIN_SYSTEM_F8411efa9_FUN_00306CD0(*(float *)(src + 0), *(float *)(src + 4));
    quat[1] = -LVL_5_FELTZIN_SYSTEM_F8411efa9_FUN_00306CD0(LVL_5_FELTZIN_SYSTEM_F8411efa9_FUN_00306790(src), *(float *)(src + 8));
    quat[0] = f13;

    LVL_5_FELTZIN_SYSTEM_F8411efa9_FUN_00306E98(m, quat);
    LVL_5_FELTZIN_SYSTEM_F8411efa9_FUN_003068F8(off, src, 0.025f);

    m[12] = *(float *)(pos + 0) + off[0];
    m[13] = *(float *)(pos + 4) + off[1];
    m[14] = *(float *)(pos + 8) + off[2];
    m[15] = 1.0f;

    LVL_5_FELTZIN_SYSTEM_F8411efa9_FUN_003E5EC0(pkt, f12);
    LVL_5_FELTZIN_SYSTEM_F8411efa9_FUN_00303910(pkt, m, 0);
}
extern void LVL_5_FELTZIN_SYSTEM_F8411efa9_FUN_003E93E0(char *pkt);
extern long long LVL_5_FELTZIN_SYSTEM_F8411efa9_FUN_002FEF40(char *p);
extern float LVL_5_FELTZIN_SYSTEM_F8411efa9_FUN_00306CD0(float x, float y);
extern float LVL_5_FELTZIN_SYSTEM_F8411efa9_FUN_00306790(char *p);
extern float LVL_5_FELTZIN_SYSTEM_F8411efa9_FUN_00306CD0(float x, float y);
extern void LVL_5_FELTZIN_SYSTEM_F8411efa9_FUN_00306E98(float *matrix, float *quat);
extern void LVL_5_FELTZIN_SYSTEM_F8411efa9_FUN_003068F8(float *off, char *src, float scale);
extern void LVL_5_FELTZIN_SYSTEM_F8411efa9_FUN_003E9468(char *pkt, float angle);
extern void LVL_5_FELTZIN_SYSTEM_F8411efa9_FUN_00303910(char *pkt, float *matrix, int mode);

void LVL_5_FELTZIN_SYSTEM_FUN_003E94D0(char *pos, int a1, int a2, char *a3, int t0,
                                        char *src, float f12, float f13)
{
    char pkt[144];
    float m[16];
    float quat[4];
    float off[4];
    long long r;

    LVL_5_FELTZIN_SYSTEM_F8411efa9_FUN_003E93E0(pkt);
    r = LVL_5_FELTZIN_SYSTEM_F8411efa9_FUN_002FEF40(a3);

    *(int *)(pkt + 76) = a1 + (a2 << 24);
    *(int *)(pkt + 72) = a1 + (a2 << 24);
    *(int *)(pkt + 68) = a1 + (a2 << 24);
    *(int *)(pkt + 64) = a1 + (a2 << 24);
    *(long long *)(pkt + 112) = 0LL;
    *(long long *)(pkt + 120) = r;
    *(long long *)(pkt + 128) = 280993940374112LL;
    *(long long *)(pkt + 136) = ((long long)t0 << 2) | 0x8000000040LL;

    quat[3] = 0.0f;
    quat[2] = LVL_5_FELTZIN_SYSTEM_F8411efa9_FUN_00306CD0(*(float *)(src + 0), *(float *)(src + 4));
    quat[1] = -LVL_5_FELTZIN_SYSTEM_F8411efa9_FUN_00306CD0(LVL_5_FELTZIN_SYSTEM_F8411efa9_FUN_00306790(src), *(float *)(src + 8));
    quat[0] = f13;

    LVL_5_FELTZIN_SYSTEM_F8411efa9_FUN_00306E98(m, quat);
    LVL_5_FELTZIN_SYSTEM_F8411efa9_FUN_003068F8(off, src, 0.025f);

    m[12] = *(float *)(pos + 0) + off[0];
    m[13] = *(float *)(pos + 4) + off[1];
    m[14] = *(float *)(pos + 8) + off[2];
    m[15] = 1.0f;

    LVL_5_FELTZIN_SYSTEM_F8411efa9_FUN_003E9468(pkt, f12);
    LVL_5_FELTZIN_SYSTEM_F8411efa9_FUN_00303910(pkt, m, 0);
}
extern void LVL_5_FELTZIN_SYSTEM_F2c74c194_FUN_003066A0(char *dst, char *src, float scale);
extern void LVL_5_FELTZIN_SYSTEM_F2c74c194_FUN_003066A0(char *dst, char *src, float scale);
extern void LVL_5_FELTZIN_SYSTEM_F2c74c194_FUN_003066A0(char *dst, char *src, float scale);
extern void LVL_5_FELTZIN_SYSTEM_F2c74c194_FUN_003066A0(char *dst, char *src, float scale);

void LVL_5_FELTZIN_SYSTEM_FUN_003DF138(char *p, float scale)
{
    LVL_5_FELTZIN_SYSTEM_F2c74c194_FUN_003066A0(p, p, scale);
    LVL_5_FELTZIN_SYSTEM_F2c74c194_FUN_003066A0(p + 16, p + 16, scale);
    LVL_5_FELTZIN_SYSTEM_F2c74c194_FUN_003066A0(p + 32, p + 32, scale);
    LVL_5_FELTZIN_SYSTEM_F2c74c194_FUN_003066A0(p + 48, p + 48, scale);
}
extern void LVL_5_FELTZIN_SYSTEM_F2c74c194_FUN_003066A0(char *dst, char *src, float scale);
extern void LVL_5_FELTZIN_SYSTEM_F2c74c194_FUN_003066A0(char *dst, char *src, float scale);
extern void LVL_5_FELTZIN_SYSTEM_F2c74c194_FUN_003066A0(char *dst, char *src, float scale);
extern void LVL_5_FELTZIN_SYSTEM_F2c74c194_FUN_003066A0(char *dst, char *src, float scale);

void LVL_5_FELTZIN_SYSTEM_FUN_003E5EC0(char *p, float scale)
{
    LVL_5_FELTZIN_SYSTEM_F2c74c194_FUN_003066A0(p, p, scale);
    LVL_5_FELTZIN_SYSTEM_F2c74c194_FUN_003066A0(p + 16, p + 16, scale);
    LVL_5_FELTZIN_SYSTEM_F2c74c194_FUN_003066A0(p + 32, p + 32, scale);
    LVL_5_FELTZIN_SYSTEM_F2c74c194_FUN_003066A0(p + 48, p + 48, scale);
}
extern void LVL_5_FELTZIN_SYSTEM_F2c74c194_FUN_003066A0(char *dst, char *src, float scale);
extern void LVL_5_FELTZIN_SYSTEM_F2c74c194_FUN_003066A0(char *dst, char *src, float scale);
extern void LVL_5_FELTZIN_SYSTEM_F2c74c194_FUN_003066A0(char *dst, char *src, float scale);
extern void LVL_5_FELTZIN_SYSTEM_F2c74c194_FUN_003066A0(char *dst, char *src, float scale);

void LVL_5_FELTZIN_SYSTEM_FUN_003E9468(char *p, float scale)
{
    LVL_5_FELTZIN_SYSTEM_F2c74c194_FUN_003066A0(p, p, scale);
    LVL_5_FELTZIN_SYSTEM_F2c74c194_FUN_003066A0(p + 16, p + 16, scale);
    LVL_5_FELTZIN_SYSTEM_F2c74c194_FUN_003066A0(p + 32, p + 32, scale);
    LVL_5_FELTZIN_SYSTEM_F2c74c194_FUN_003066A0(p + 48, p + 48, scale);
}
extern void LVL_5_FELTZIN_SYSTEM_F2c74c194_FUN_003066A0(char *dst, char *src, float scale);
extern void LVL_5_FELTZIN_SYSTEM_F2c74c194_FUN_003066A0(char *dst, char *src, float scale);
extern void LVL_5_FELTZIN_SYSTEM_F2c74c194_FUN_003066A0(char *dst, char *src, float scale);
extern void LVL_5_FELTZIN_SYSTEM_F2c74c194_FUN_003066A0(char *dst, char *src, float scale);

void LVL_5_FELTZIN_SYSTEM_FUN_003EF748(char *p, float scale)
{
    LVL_5_FELTZIN_SYSTEM_F2c74c194_FUN_003066A0(p, p, scale);
    LVL_5_FELTZIN_SYSTEM_F2c74c194_FUN_003066A0(p + 16, p + 16, scale);
    LVL_5_FELTZIN_SYSTEM_F2c74c194_FUN_003066A0(p + 32, p + 32, scale);
    LVL_5_FELTZIN_SYSTEM_F2c74c194_FUN_003066A0(p + 48, p + 48, scale);
}
extern void LVL_5_FELTZIN_SYSTEM_F2c74c194_FUN_003066A0(char *dst, char *src, float scale);
extern void LVL_5_FELTZIN_SYSTEM_F2c74c194_FUN_003066A0(char *dst, char *src, float scale);
extern void LVL_5_FELTZIN_SYSTEM_F2c74c194_FUN_003066A0(char *dst, char *src, float scale);
extern void LVL_5_FELTZIN_SYSTEM_F2c74c194_FUN_003066A0(char *dst, char *src, float scale);

void LVL_5_FELTZIN_SYSTEM_FUN_003F82B0(char *p, float scale)
{
    LVL_5_FELTZIN_SYSTEM_F2c74c194_FUN_003066A0(p, p, scale);
    LVL_5_FELTZIN_SYSTEM_F2c74c194_FUN_003066A0(p + 16, p + 16, scale);
    LVL_5_FELTZIN_SYSTEM_F2c74c194_FUN_003066A0(p + 32, p + 32, scale);
    LVL_5_FELTZIN_SYSTEM_F2c74c194_FUN_003066A0(p + 48, p + 48, scale);
}
extern void LVL_5_FELTZIN_SYSTEM_F2c74c194_FUN_003066A0(char *dst, char *src, float scale);
extern void LVL_5_FELTZIN_SYSTEM_F2c74c194_FUN_003066A0(char *dst, char *src, float scale);
extern void LVL_5_FELTZIN_SYSTEM_F2c74c194_FUN_003066A0(char *dst, char *src, float scale);
extern void LVL_5_FELTZIN_SYSTEM_F2c74c194_FUN_003066A0(char *dst, char *src, float scale);

void LVL_5_FELTZIN_SYSTEM_FUN_003F9658(char *p, float scale)
{
    LVL_5_FELTZIN_SYSTEM_F2c74c194_FUN_003066A0(p, p, scale);
    LVL_5_FELTZIN_SYSTEM_F2c74c194_FUN_003066A0(p + 16, p + 16, scale);
    LVL_5_FELTZIN_SYSTEM_F2c74c194_FUN_003066A0(p + 32, p + 32, scale);
    LVL_5_FELTZIN_SYSTEM_F2c74c194_FUN_003066A0(p + 48, p + 48, scale);
}




extern u8 LVL_5_FELTZIN_SYSTEM_F458c670e_D_00189E20[];

extern void LVL_5_FELTZIN_SYSTEM_F458c670e_FUN_00335A00(f32 *a, f32 *b, f32 c, f32 d, f32 e, f32 f);
extern f32 LVL_5_FELTZIN_SYSTEM_F458c670e_FUN_003065A0(f32 v);
extern void LVL_5_FELTZIN_SYSTEM_F458c670e_FUN_00335940(f32 *p, f32 v, f32 w);

#ifndef RAC2_T_RES_F458C670E
#define RAC2_T_RES_F458C670E
typedef struct {
    u8 pad000[0x88];
    f32 f088;
    u8 pad08C[0x1B8 - 0x08C];
    s32 i1B8;
    u8 pad1BC[0x330 - 0x1BC];
    f32 f330;
    u8 pad334[0x790 - 0x334];
    f32 f790;
    f32 f794;
    u8 pad798[4];
    f32 f79C;
    f32 f7A0;
    u8 pad7A4[0x9B0 - 0x7A4];
    f32 f9B0;
    u8 pad9B4[0xA3C - 0x9B4];
    f32 fA3C;
    u8 padA40[0x2294 - 0xA40];
    s32 i2294;
    u8 pad2298[4];
    s32 i229C;
    u8 pad22A0[4];
    s32 i22A4;
    u8 pad22A8[8];
    s32 i22B0;
} Res_F458c670e;
#endif


void LVL_5_FELTZIN_SYSTEM_FUN_002E1AA8(void)
{
    f32 old, v, r, sum;

    if (((Res_F458c670e *)LVL_5_FELTZIN_SYSTEM_F458c670e_D_00189E20)->i1B8 >= 11
        || ((Res_F458c670e *)LVL_5_FELTZIN_SYSTEM_F458c670e_D_00189E20)->f790 < 0.0f
        || ((Res_F458c670e *)LVL_5_FELTZIN_SYSTEM_F458c670e_D_00189E20)->i22A4 == 17
        || ((Res_F458c670e *)LVL_5_FELTZIN_SYSTEM_F458c670e_D_00189E20)->i22B0 == 17) {
        if (((Res_F458c670e *)LVL_5_FELTZIN_SYSTEM_F458c670e_D_00189E20)->i2294 == 53) {
            LVL_5_FELTZIN_SYSTEM_F458c670e_FUN_00335A00(&((Res_F458c670e *)LVL_5_FELTZIN_SYSTEM_F458c670e_D_00189E20)->f790,
                    &((Res_F458c670e *)LVL_5_FELTZIN_SYSTEM_F458c670e_D_00189E20)->fA3C,
                    0.0f, 0.03f, 0.3f, 0.025000002f);
            ((Res_F458c670e *)LVL_5_FELTZIN_SYSTEM_F458c670e_D_00189E20)->f794 = 0.0f;
        } else {
            old = ((Res_F458c670e *)LVL_5_FELTZIN_SYSTEM_F458c670e_D_00189E20)->f790;
            v = ((Res_F458c670e *)LVL_5_FELTZIN_SYSTEM_F458c670e_D_00189E20)->f794;
            ((Res_F458c670e *)LVL_5_FELTZIN_SYSTEM_F458c670e_D_00189E20)->f794 =
                v - (old * 0.005f + v * 0.045f);
            r = LVL_5_FELTZIN_SYSTEM_F458c670e_FUN_003065A0(old);
            if (r < 0.001f) {
                if (((Res_F458c670e *)LVL_5_FELTZIN_SYSTEM_F458c670e_D_00189E20)->f794 < 0.0001f)
                    ((Res_F458c670e *)LVL_5_FELTZIN_SYSTEM_F458c670e_D_00189E20)->f794 = 0.0f;
            }
        }
    }
    sum = ((Res_F458c670e *)LVL_5_FELTZIN_SYSTEM_F458c670e_D_00189E20)->f790
        + ((Res_F458c670e *)LVL_5_FELTZIN_SYSTEM_F458c670e_D_00189E20)->f794;
    ((Res_F458c670e *)LVL_5_FELTZIN_SYSTEM_F458c670e_D_00189E20)->f790 = sum;
    if (((Res_F458c670e *)LVL_5_FELTZIN_SYSTEM_F458c670e_D_00189E20)->i2294 == 53) {
        if (sum > 0.0f) {
            if (((Res_F458c670e *)LVL_5_FELTZIN_SYSTEM_F458c670e_D_00189E20)->f794 > 0.0f)
                ((Res_F458c670e *)LVL_5_FELTZIN_SYSTEM_F458c670e_D_00189E20)->f794 = 0.0f;
            LVL_5_FELTZIN_SYSTEM_F458c670e_FUN_00335940(&((Res_F458c670e *)LVL_5_FELTZIN_SYSTEM_F458c670e_D_00189E20)->f790,
                    0.0f, 0.011666667f);
        }
    }
    if (((Res_F458c670e *)LVL_5_FELTZIN_SYSTEM_F458c670e_D_00189E20)->i2294 != 124) {
        f32 x = ((Res_F458c670e *)LVL_5_FELTZIN_SYSTEM_F458c670e_D_00189E20)->f330;
        if (((Res_F458c670e *)LVL_5_FELTZIN_SYSTEM_F458c670e_D_00189E20)->i229C == 22)
            x = ((Res_F458c670e *)LVL_5_FELTZIN_SYSTEM_F458c670e_D_00189E20)->f9B0;
        LVL_5_FELTZIN_SYSTEM_F458c670e_FUN_00335A00(&((Res_F458c670e *)LVL_5_FELTZIN_SYSTEM_F458c670e_D_00189E20)->f79C,
                &((Res_F458c670e *)LVL_5_FELTZIN_SYSTEM_F458c670e_D_00189E20)->f7A0,
                x, 0.027f, 0.3f, 0.0f);
    }
    ((Res_F458c670e *)LVL_5_FELTZIN_SYSTEM_F458c670e_D_00189E20)->f088 =
        (((Res_F458c670e *)LVL_5_FELTZIN_SYSTEM_F458c670e_D_00189E20)->f79C + (-0.12f))
        + ((Res_F458c670e *)LVL_5_FELTZIN_SYSTEM_F458c670e_D_00189E20)->f790;
}
extern void LVL_5_FELTZIN_SYSTEM_F40487154_FUN_00306E78(char *a, char *b);
extern float LVL_5_FELTZIN_SYSTEM_F40487154_FUN_00306C20(float value);
extern void LVL_5_FELTZIN_SYSTEM_F40487154_FUN_003066A0(char *a, char *b, float value);
extern float LVL_5_FELTZIN_SYSTEM_F40487154_FUN_00307620(float value, float scale);

void LVL_5_FELTZIN_SYSTEM_FUN_003EBF88(char *object)
{
    char *data;
    float x;
    float y;
    float z;

    data = *(char **)(object + 104);
    LVL_5_FELTZIN_SYSTEM_F40487154_FUN_00306E78(object + 192, object + 240);
    x = LVL_5_FELTZIN_SYSTEM_F40487154_FUN_00306C20(*(float *)(data + 4)) * 0.15f + 0.35000002f;
    y = LVL_5_FELTZIN_SYSTEM_F40487154_FUN_00306C20(*(float *)(data + 8)) * 0.15f + 0.35000002f;
    z = LVL_5_FELTZIN_SYSTEM_F40487154_FUN_00306C20(*(float *)(data + 12)) * 0.15f + 0.35000002f;
    LVL_5_FELTZIN_SYSTEM_F40487154_FUN_003066A0(object + 192, object + 192, x);
    LVL_5_FELTZIN_SYSTEM_F40487154_FUN_003066A0(object + 208, object + 208, y);
    LVL_5_FELTZIN_SYSTEM_F40487154_FUN_003066A0(object + 224, object + 224, z);
    *(float *)(data + 4) = LVL_5_FELTZIN_SYSTEM_F40487154_FUN_00307620(*(float *)(data + 4), 0.5f);
    *(float *)(data + 8) = LVL_5_FELTZIN_SYSTEM_F40487154_FUN_00307620(*(float *)(data + 8), 0.5f);
    *(float *)(data + 12) = LVL_5_FELTZIN_SYSTEM_F40487154_FUN_00307620(*(float *)(data + 12), 0.5f);
}
extern void LVL_5_FELTZIN_SYSTEM_F40487154_FUN_00306E78(char *a, char *b);
extern float LVL_5_FELTZIN_SYSTEM_F40487154_FUN_00306C20(float value);
extern void LVL_5_FELTZIN_SYSTEM_F40487154_FUN_003066A0(char *a, char *b, float value);
extern float LVL_5_FELTZIN_SYSTEM_F40487154_FUN_00307620(float value, float scale);

void LVL_5_FELTZIN_SYSTEM_FUN_003F5B40(char *object)
{
    char *data;
    float x;
    float y;
    float z;

    data = *(char **)(object + 104);
    LVL_5_FELTZIN_SYSTEM_F40487154_FUN_00306E78(object + 192, object + 240);
    x = LVL_5_FELTZIN_SYSTEM_F40487154_FUN_00306C20(*(float *)(data + 4)) * 0.15f + 0.35000002f;
    y = LVL_5_FELTZIN_SYSTEM_F40487154_FUN_00306C20(*(float *)(data + 8)) * 0.15f + 0.35000002f;
    z = LVL_5_FELTZIN_SYSTEM_F40487154_FUN_00306C20(*(float *)(data + 12)) * 0.15f + 0.35000002f;
    LVL_5_FELTZIN_SYSTEM_F40487154_FUN_003066A0(object + 192, object + 192, x);
    LVL_5_FELTZIN_SYSTEM_F40487154_FUN_003066A0(object + 208, object + 208, y);
    LVL_5_FELTZIN_SYSTEM_F40487154_FUN_003066A0(object + 224, object + 224, z);
    *(float *)(data + 4) = LVL_5_FELTZIN_SYSTEM_F40487154_FUN_00307620(*(float *)(data + 4), 0.5f);
    *(float *)(data + 8) = LVL_5_FELTZIN_SYSTEM_F40487154_FUN_00307620(*(float *)(data + 8), 0.5f);
    *(float *)(data + 12) = LVL_5_FELTZIN_SYSTEM_F40487154_FUN_00307620(*(float *)(data + 12), 0.5f);
}
extern int LVL_5_FELTZIN_SYSTEM_F6eb4f363_FUN_00332AB8(int mode);
extern float LVL_5_FELTZIN_SYSTEM_F6eb4f363_FUN_00334770(char *object, char *local);
extern void LVL_5_FELTZIN_SYSTEM_F6eb4f363_FUN_003066A0(char *local, int value, float scale);
extern float LVL_5_FELTZIN_SYSTEM_F6eb4f363_FUN_00332B50(float low, float high);
extern void LVL_5_FELTZIN_SYSTEM_F6eb4f363_FUN_00348D38(char *object, char *local, float amount, float base);

void LVL_5_FELTZIN_SYSTEM_FUN_0039D998(char *object)
{
    char local[16];
    float base;
    int value = *(int *)(object + 104);

    if (LVL_5_FELTZIN_SYSTEM_F6eb4f363_FUN_00332AB8(5))
        return;
    base = LVL_5_FELTZIN_SYSTEM_F6eb4f363_FUN_00334770(object + 16, local);
    LVL_5_FELTZIN_SYSTEM_F6eb4f363_FUN_003066A0(local, value, 0.25f);
    LVL_5_FELTZIN_SYSTEM_F6eb4f363_FUN_00348D38(object + 16, local, LVL_5_FELTZIN_SYSTEM_F6eb4f363_FUN_00332B50(0.05f, 0.1f) * 210000.0f, base);
}
extern int LVL_5_FELTZIN_SYSTEM_F6eb4f363_FUN_00332AB8(int mode);
extern float LVL_5_FELTZIN_SYSTEM_F6eb4f363_FUN_00334770(char *object, char *local);
extern void LVL_5_FELTZIN_SYSTEM_F6eb4f363_FUN_003066A0(char *local, int value, float scale);
extern float LVL_5_FELTZIN_SYSTEM_F6eb4f363_FUN_00332B50(float low, float high);
extern void LVL_5_FELTZIN_SYSTEM_F6eb4f363_FUN_00348D38(char *object, char *local, float amount, float base);

void LVL_5_FELTZIN_SYSTEM_FUN_003A0440(char *object)
{
    char local[16];
    float base;
    int value = *(int *)(object + 104);

    if (LVL_5_FELTZIN_SYSTEM_F6eb4f363_FUN_00332AB8(5))
        return;
    base = LVL_5_FELTZIN_SYSTEM_F6eb4f363_FUN_00334770(object + 16, local);
    LVL_5_FELTZIN_SYSTEM_F6eb4f363_FUN_003066A0(local, value, 0.25f);
    LVL_5_FELTZIN_SYSTEM_F6eb4f363_FUN_00348D38(object + 16, local, LVL_5_FELTZIN_SYSTEM_F6eb4f363_FUN_00332B50(0.05f, 0.1f) * 210000.0f, base);
}
extern int LVL_5_FELTZIN_SYSTEM_F6eb4f363_FUN_00332AB8(int mode);
extern float LVL_5_FELTZIN_SYSTEM_F6eb4f363_FUN_00334770(char *object, char *local);
extern void LVL_5_FELTZIN_SYSTEM_F6eb4f363_FUN_003066A0(char *local, int value, float scale);
extern float LVL_5_FELTZIN_SYSTEM_F6eb4f363_FUN_00332B50(float low, float high);
extern void LVL_5_FELTZIN_SYSTEM_F6eb4f363_FUN_00348D38(char *object, char *local, float amount, float base);

void LVL_5_FELTZIN_SYSTEM_FUN_003A5968(char *object)
{
    char local[16];
    float base;
    int value = *(int *)(object + 104);

    if (LVL_5_FELTZIN_SYSTEM_F6eb4f363_FUN_00332AB8(5))
        return;
    base = LVL_5_FELTZIN_SYSTEM_F6eb4f363_FUN_00334770(object + 16, local);
    LVL_5_FELTZIN_SYSTEM_F6eb4f363_FUN_003066A0(local, value, 0.25f);
    LVL_5_FELTZIN_SYSTEM_F6eb4f363_FUN_00348D38(object + 16, local, LVL_5_FELTZIN_SYSTEM_F6eb4f363_FUN_00332B50(0.05f, 0.1f) * 210000.0f, base);
}
extern int LVL_5_FELTZIN_SYSTEM_Fc10c1216_FUN_003062D0(char *);
extern void LVL_5_FELTZIN_SYSTEM_Fc10c1216_FUN_003423C8(char *);
extern int LVL_5_FELTZIN_SYSTEM_Fc10c1216_FUN_00307778(float);
extern void LVL_5_FELTZIN_SYSTEM_Fc10c1216_FUN_00306630(char *, char *, char *);

void LVL_5_FELTZIN_SYSTEM_FUN_00347FC8(char *p)
{
    float *q = (float *)(p + 32);

    if (0.0f < q[3])
        q[1] = q[1] + q[3] * 0.007f;
    else if (0.03f < q[1])
        q[1] = q[1] + q[3] * 0.007f;
    else {
        q[1] = q[1] + q[3] * 1.4000000664964318275452e-03f;
        *(float *)(p + 12) = *(float *)(p + 12) + 5460.0f;
    }

    if (q[1] <= 0.0244f || LVL_5_FELTZIN_SYSTEM_Fc10c1216_FUN_003062D0(p + 10) != 0) {
        LVL_5_FELTZIN_SYSTEM_Fc10c1216_FUN_003423C8(p);
        return;
    }

    if (q[1] >= 0.12f) {
        q[3] = -q[3];
        q[1] = q[1] + q[3] * 0.007f;
    }
    *(float *)(p + 12) = *(float *)(p + 12) + 5460.0f;
    *(int *)(p + 4) = (*(int *)(p + 4) & 0xffffff) | (LVL_5_FELTZIN_SYSTEM_Fc10c1216_FUN_00307778(q[1] * 255.0f) << 24);
    q[2] = q[2] + 0.002f;
    if (q[2] > 1.0f)
        q[2] = q[2] - 1.0f;
    *(char *)(p + 8) = (char)(q[2] * 255.0f);
    LVL_5_FELTZIN_SYSTEM_Fc10c1216_FUN_00306630(p + 16, p + 16, (char *)(q + 4));
}
#ifndef RAC2_T_V4_F904CC63B
#define RAC2_T_V4_F904CC63B
typedef __attribute__((mode(TI))) int V4_F904cc63b;
#endif


extern char *LVL_5_FELTZIN_SYSTEM_F904cc63b_FUN_003387A8(char *p);
extern void LVL_5_FELTZIN_SYSTEM_F904cc63b_FUN_00306E98(V4_F904cc63b *dst, char *src);
extern void LVL_5_FELTZIN_SYSTEM_F904cc63b_FUN_00306630(V4_F904cc63b *dst, V4_F904cc63b *a, char *b);
extern void LVL_5_FELTZIN_SYSTEM_F904cc63b_FUN_00306660(V4_F904cc63b *dst, V4_F904cc63b *a, char *b);
extern void LVL_5_FELTZIN_SYSTEM_F904cc63b_FUN_00307120(V4_F904cc63b *dst, V4_F904cc63b *src);
extern void LVL_5_FELTZIN_SYSTEM_F904cc63b_FUN_00306AD8(V4_F904cc63b *dst, V4_F904cc63b *a, V4_F904cc63b *b);

int LVL_5_FELTZIN_SYSTEM_FUN_00338A28(char *a0, char *a1, char *a2, char *a3)
{
    V4_F904cc63b b0[4];
    V4_F904cc63b b1[1];
    V4_F904cc63b b2[4];
    V4_F904cc63b b3[4];
    char *p;

    p = LVL_5_FELTZIN_SYSTEM_F904cc63b_FUN_003387A8(a1);
    if (p == 0)
    {
        *(V4_F904cc63b *)a3 = 0;
        return 0;
    }
    LVL_5_FELTZIN_SYSTEM_F904cc63b_FUN_00306E98(b0, p);
    LVL_5_FELTZIN_SYSTEM_F904cc63b_FUN_00306630(b1, (V4_F904cc63b *)a2, p + 16);
    LVL_5_FELTZIN_SYSTEM_F904cc63b_FUN_00306660(b1, b1, a1 + 16);
    if (*(int *)(p + 60) & 2)
    {
        LVL_5_FELTZIN_SYSTEM_F904cc63b_FUN_00306E98(b3, p + 32);
        LVL_5_FELTZIN_SYSTEM_F904cc63b_FUN_00307120(b2, b3);
        LVL_5_FELTZIN_SYSTEM_F904cc63b_FUN_00306AD8(b1, b1, b2);
        LVL_5_FELTZIN_SYSTEM_F904cc63b_FUN_00306AD8(b1, b1, (V4_F904cc63b *)(a1 + 192));
    }
    else
    {
        LVL_5_FELTZIN_SYSTEM_F904cc63b_FUN_00306AD8(b1, b1, b0);
    }
    LVL_5_FELTZIN_SYSTEM_F904cc63b_FUN_00306630(b1, b1, a1 + 16);
    LVL_5_FELTZIN_SYSTEM_F904cc63b_FUN_00306660((V4_F904cc63b *)a3, b1, a2);
    return 1;
}
extern int LVL_5_FELTZIN_SYSTEM_F250fbfa4_FUN_003062D0(char *p);
extern void LVL_5_FELTZIN_SYSTEM_F250fbfa4_FUN_003423C8(char *p);
extern void LVL_5_FELTZIN_SYSTEM_F250fbfa4_FUN_00306630(char *p0, char *p1, char *p2);

void LVL_5_FELTZIN_SYSTEM_FUN_00351D10(char *a0)
{
    char local[16];
    char *s1 = a0;
    char *s0;
    int a1;
    int v1;
    char *p;

    if (LVL_5_FELTZIN_SYSTEM_F250fbfa4_FUN_003062D0(a0 + 10) != 0) {
        LVL_5_FELTZIN_SYSTEM_F250fbfa4_FUN_003423C8(a0);
        return;
    }
    s0 = a0 + 32;
    a1 = *(int *)(s1 + 4);
    v1 = (a1 >> 24) + *(unsigned char *)(s0 + 20);
    *(int *)(s1 + 4) = (a1 & 0x00ffffff) | (v1 << 24);
    p = s1 + 16;
    *(float *)(local + 0) = *(float *)(s1 + 32);
    *(float *)(local + 4) = *(float *)(s0 + 4);
    *(float *)(local + 8) = *(float *)(s0 + 8);
    *(int *)(local + 12) = 0;
    LVL_5_FELTZIN_SYSTEM_F250fbfa4_FUN_00306630(p, p, local);
    *(float *)(s0 + 8) = *(float *)(s0 + 8) - *(float *)(s0 + 12);
    *(unsigned char *)(s1 + 8) = *(unsigned char *)(s1 + 8) + *(unsigned char *)(s0 + 21);
    *(float *)(s1 + 12) = *(float *)(s1 + 12) + *(float *)(s0 + 16);
}
extern int LVL_5_FELTZIN_SYSTEM_F250fbfa4_FUN_003062D0(char *p);
extern void LVL_5_FELTZIN_SYSTEM_F250fbfa4_FUN_003423C8(char *p);
extern void LVL_5_FELTZIN_SYSTEM_F250fbfa4_FUN_00306630(char *p0, char *p1, char *p2);

void LVL_5_FELTZIN_SYSTEM_FUN_00352C90(char *a0)
{
    char local[16];
    char *s1 = a0;
    char *s0;
    int a1;
    int v1;
    char *p;

    if (LVL_5_FELTZIN_SYSTEM_F250fbfa4_FUN_003062D0(a0 + 10) != 0) {
        LVL_5_FELTZIN_SYSTEM_F250fbfa4_FUN_003423C8(a0);
        return;
    }
    s0 = a0 + 32;
    a1 = *(int *)(s1 + 4);
    v1 = (a1 >> 24) + *(unsigned char *)(s0 + 20);
    *(int *)(s1 + 4) = (a1 & 0x00ffffff) | (v1 << 24);
    p = s1 + 16;
    *(float *)(local + 0) = *(float *)(s1 + 32);
    *(float *)(local + 4) = *(float *)(s0 + 4);
    *(float *)(local + 8) = *(float *)(s0 + 8);
    *(int *)(local + 12) = 0;
    LVL_5_FELTZIN_SYSTEM_F250fbfa4_FUN_00306630(p, p, local);
    *(float *)(s0 + 8) = *(float *)(s0 + 8) - *(float *)(s0 + 12);
    *(unsigned char *)(s1 + 8) = *(unsigned char *)(s1 + 8) + *(unsigned char *)(s0 + 21);
    *(float *)(s1 + 12) = *(float *)(s1 + 12) + *(float *)(s0 + 16);
}
extern void LVL_5_FELTZIN_SYSTEM_Ffb202470_FUN_0044BB78(char *p);

char *LVL_5_FELTZIN_SYSTEM_FUN_0044CD60(char *object)
{
    LVL_5_FELTZIN_SYSTEM_Ffb202470_FUN_0044BB78(object + 8);
    return object;
}
extern void LVL_5_FELTZIN_SYSTEM_Ffb202470_FUN_0044BB78(char *p);

char *LVL_5_FELTZIN_SYSTEM_FUN_0044D1A0(char *object)
{
    LVL_5_FELTZIN_SYSTEM_Ffb202470_FUN_0044BB78(object + 8);
    return object;
}
extern void LVL_5_FELTZIN_SYSTEM_Ffb202470_FUN_0044BB78(char *p);

char *LVL_5_FELTZIN_SYSTEM_FUN_0044D458(char *object)
{
    LVL_5_FELTZIN_SYSTEM_Ffb202470_FUN_0044BB78(object + 8);
    return object;
}
extern void LVL_5_FELTZIN_SYSTEM_Ffb202470_FUN_0044BB78(char *p);

char *LVL_5_FELTZIN_SYSTEM_FUN_0044D9E0(char *object)
{
    LVL_5_FELTZIN_SYSTEM_Ffb202470_FUN_0044BB78(object + 8);
    return object;
}
extern void LVL_5_FELTZIN_SYSTEM_Ffb202470_FUN_0044BB78(char *p);

char *LVL_5_FELTZIN_SYSTEM_FUN_0044E468(char *object)
{
    LVL_5_FELTZIN_SYSTEM_Ffb202470_FUN_0044BB78(object + 8);
    return object;
}
extern void LVL_5_FELTZIN_SYSTEM_Ffb202470_FUN_0044BB78(char *p);

char *LVL_5_FELTZIN_SYSTEM_FUN_0044E730(char *object)
{
    LVL_5_FELTZIN_SYSTEM_Ffb202470_FUN_0044BB78(object + 8);
    return object;
}
extern void LVL_5_FELTZIN_SYSTEM_Ffb202470_FUN_0044BB78(char *p);

char *LVL_5_FELTZIN_SYSTEM_FUN_0044EAF8(char *object)
{
    LVL_5_FELTZIN_SYSTEM_Ffb202470_FUN_0044BB78(object + 8);
    return object;
}
extern void LVL_5_FELTZIN_SYSTEM_Ffb202470_FUN_0044BB78(char *p);

char *LVL_5_FELTZIN_SYSTEM_FUN_0044EDA8(char *object)
{
    LVL_5_FELTZIN_SYSTEM_Ffb202470_FUN_0044BB78(object + 8);
    return object;
}
extern void LVL_5_FELTZIN_SYSTEM_Ffb202470_FUN_0044BB78(char *p);

char *LVL_5_FELTZIN_SYSTEM_FUN_0044EFA0(char *object)
{
    LVL_5_FELTZIN_SYSTEM_Ffb202470_FUN_0044BB78(object + 8);
    return object;
}
extern void LVL_5_FELTZIN_SYSTEM_Fe524d931_FUN_0044BE50(char *p);
extern void LVL_5_FELTZIN_SYSTEM_Fe524d931_FUN_0044C040(char *p, float x, float y);
extern void LVL_5_FELTZIN_SYSTEM_Fe524d931_FUN_00371A60(int a, int b, int c);
extern void LVL_5_FELTZIN_SYSTEM_Fe524d931_FUN_00308980(void);
extern short LVL_5_FELTZIN_SYSTEM_Fe524d931_D_001A6480[];

int LVL_5_FELTZIN_SYSTEM_FUN_0044CEC0(char *object, int mask)
{
    char *sub = object + 8;
    short oldx;
    short oldy;
    int *v;

    LVL_5_FELTZIN_SYSTEM_Fe524d931_FUN_0044BE50(sub);
    v = *(int **)(object + 684);
    LVL_5_FELTZIN_SYSTEM_Fe524d931_FUN_0044C040(sub, *(float *)v, *(float *)(v + 1));
    if ((mask & 0x40) != 0 && *(int *)(object + 680) == 0)
        LVL_5_FELTZIN_SYSTEM_Fe524d931_FUN_00371A60(4, 0, 0);
    if ((mask & 0xf000) != 0) {
        short *p = LVL_5_FELTZIN_SYSTEM_Fe524d931_D_001A6480;
        oldx = p[180];
        oldy = p[181];
        if ((mask & 0x1000) != 0) {
            ((unsigned short *)p)[181] = ((unsigned short *)p)[181] - 1;
            if ((short)((unsigned short *)p)[181] < -32)
                p[181] = -32;
        }
        if ((mask & 0x4000) != 0) {
            unsigned short *q = (unsigned short *)LVL_5_FELTZIN_SYSTEM_Fe524d931_D_001A6480;
            q[181] = q[181] + 1;
            if ((short)q[181] > 32)
                ((short *)q)[181] = 32;
        }
        if ((mask & 0x8000) != 0) {
            unsigned short *q = (unsigned short *)LVL_5_FELTZIN_SYSTEM_Fe524d931_D_001A6480;
            q[180] = q[180] - 1;
            if ((short)q[180] < -40)
                ((short *)q)[180] = -40;
        }
        if ((mask & 0x2000) != 0) {
            unsigned short *q = (unsigned short *)LVL_5_FELTZIN_SYSTEM_Fe524d931_D_001A6480;
            q[180] = q[180] + 1;
            if ((short)q[180] > 40)
                ((short *)q)[180] = 40;
        }
        {
            short *q = LVL_5_FELTZIN_SYSTEM_Fe524d931_D_001A6480;
            if (oldx != q[180] || oldy != q[181])
                LVL_5_FELTZIN_SYSTEM_Fe524d931_FUN_00371A60(4, 0, 0);
        }
        LVL_5_FELTZIN_SYSTEM_Fe524d931_FUN_00308980();
    }
    return (mask >> 6) & 1;
}
extern void LVL_5_FELTZIN_SYSTEM_F0b028b34_FUN_004618B0(char *a, unsigned int b, int c, int d);
extern void LVL_5_FELTZIN_SYSTEM_F0b028b34_FUN_004618B0(char *a, unsigned int b, int c, int d);
extern void LVL_5_FELTZIN_SYSTEM_F0b028b34_FUN_00461840(int a);

int LVL_5_FELTZIN_SYSTEM_FUN_00461950(int *p)
{
    int i;

    p[17] = 1;
    p[3] = 0;
    p[4] = 0;
    p[5] = 0;
    p[22] = 0;
    p[23] = 0;
    for (i = 0; i < p[21]; i++) {
        *(long long *)((char *)p[20] + i * 24) = -1;
        *(long long *)((char *)p[20] + i * 24 + 8) = -1;
        *(int *)((char *)p[20] + i * 24 + 16) = 0;
        *(int *)((char *)p[20] + i * 24 + 20) = 0;
    }
    for (i = 0; i < p[2]; i++) {
        LVL_5_FELTZIN_SYSTEM_F0b028b34_FUN_004618B0((char *)(p[1] + i * 16), (i * 2048 + p[0]) & 0x0FFFFFFF, 3, 128);
    }
    LVL_5_FELTZIN_SYSTEM_F0b028b34_FUN_004618B0((char *)(p[1] + i * 16), p[1] & 0x0FFFFFFF, 2, 0);
    *(volatile unsigned int *)0x1000B420 = 0;
    *(volatile unsigned int *)0x1000B410 = p[0] & 0x0FFFFFFF;
    *(volatile unsigned int *)0x1000B430 = p[1] & 0x0FFFFFFF;
    LVL_5_FELTZIN_SYSTEM_F0b028b34_FUN_00461840(5);
    return 1;
}
extern void LVL_5_FELTZIN_SYSTEM_Fbdd4a4aa_FUN_00394B90(char *a, char *b);
extern void LVL_5_FELTZIN_SYSTEM_Fbdd4a4aa_FUN_00306630(char *a, char *b, char *c);
extern void LVL_5_FELTZIN_SYSTEM_Fbdd4a4aa_FUN_003066A0(char *a, char *b, float f);
extern void LVL_5_FELTZIN_SYSTEM_Fbdd4a4aa_FUN_00392A70(char *a, char *b);
extern void LVL_5_FELTZIN_SYSTEM_Fbdd4a4aa_FUN_003066A0(char *a, char *b, float f);
extern void LVL_5_FELTZIN_SYSTEM_Fbdd4a4aa_FUN_00306630(char *a, char *b, char *c);
extern void LVL_5_FELTZIN_SYSTEM_Fbdd4a4aa_FUN_003066A0(char *a, char *b, float f);
extern void LVL_5_FELTZIN_SYSTEM_Fbdd4a4aa_FUN_00306630(char *a, char *b, char *c);
extern int LVL_5_FELTZIN_SYSTEM_Fbdd4a4aa_FUN_003077C0(unsigned int a, int b, float f);
extern void LVL_5_FELTZIN_SYSTEM_Fbdd4a4aa_FUN_003423C8(char *a);

void LVL_5_FELTZIN_SYSTEM_FUN_00353AB8(int *obj)
{
    char *a = (char *)obj + 16;
    char *b = (char *)obj + 32;
    char tmp[16];

    LVL_5_FELTZIN_SYSTEM_Fbdd4a4aa_FUN_00394B90(a, a);
    *(int *)(b + 16) = *(int *)(b + 16) - 1;
    if (*(int *)(b + 16) < 0)
        *(int *)(b + 16) = 0;
    *(unsigned char *)((char *)obj + 8) = *(unsigned char *)((char *)obj + 8) + 1;
    LVL_5_FELTZIN_SYSTEM_Fbdd4a4aa_FUN_00306630(a, b, a);
    *(float *)((char *)obj + 12) = *(float *)((char *)obj + 12) + 1.5750000000000000000000e+03f;
    LVL_5_FELTZIN_SYSTEM_Fbdd4a4aa_FUN_003066A0(b, b, 9.9000000953674316406250e-01f);
    LVL_5_FELTZIN_SYSTEM_Fbdd4a4aa_FUN_00392A70(a, tmp);
    if ((*(int *)((char *)obj + 4) & 0xFF) < 32) {
        LVL_5_FELTZIN_SYSTEM_Fbdd4a4aa_FUN_003066A0(tmp, tmp, 1.5000000130385160446167e-03f);
        LVL_5_FELTZIN_SYSTEM_Fbdd4a4aa_FUN_00306630(b, b, tmp);
    } else {
        LVL_5_FELTZIN_SYSTEM_Fbdd4a4aa_FUN_003066A0(tmp, tmp, -7.5000000651925802230835e-04f);
        LVL_5_FELTZIN_SYSTEM_Fbdd4a4aa_FUN_00306630(b, b, tmp);
    }
    *(int *)((char *)obj + 4) = LVL_5_FELTZIN_SYSTEM_Fbdd4a4aa_FUN_003077C0(*(unsigned int *)((char *)obj + 4) & 0x00FFFFFF, 0, 2.5000000372529029846191e-02f)
        | (*(int *)(b + 16) << 24);
    if (*(int *)(b + 16) == 0)
        LVL_5_FELTZIN_SYSTEM_Fbdd4a4aa_FUN_003423C8((char *)obj);
}
#ifndef RAC2_T_OBJ_F7B2F1854
#define RAC2_T_OBJ_F7B2F1854
typedef struct Obj_F7b2f1854 {
    int *f0;
    int *f4;
    int *f8;
    int *f12;
    int *f16;
    int f20;
    int f24;
    int f28;
    int f32;
    int f36;
    int f40;
    int f44;
} Obj_F7b2f1854;
#endif


extern int *LVL_5_FELTZIN_SYSTEM_F7b2f1854_FUN_00447E60(int n);
extern int *LVL_5_FELTZIN_SYSTEM_F7b2f1854_FUN_00447DC8(int size, int *p);
extern void LVL_5_FELTZIN_SYSTEM_F7b2f1854_FUN_00446E88(Obj_F7b2f1854 *o, int v);

void LVL_5_FELTZIN_SYSTEM_FUN_00446FE8(Obj_F7b2f1854 *o, int a1, int count)
{
    int *p;
    int n;

    o->f44 = count;
    if (count != 0) {
        p = LVL_5_FELTZIN_SYSTEM_F7b2f1854_FUN_00447DC8(16, LVL_5_FELTZIN_SYSTEM_F7b2f1854_FUN_00447E60(count));
        n = o->f44;
        o->f0 = p;
        p[1] = 0;
        p[2] = 0;
        p[3] = 0;
        p[0] = 0;

        p = LVL_5_FELTZIN_SYSTEM_F7b2f1854_FUN_00447DC8(16, LVL_5_FELTZIN_SYSTEM_F7b2f1854_FUN_00447E60(n));
        n = o->f44;
        o->f8 = p;
        p[1] = 0;
        p[2] = 0;
        p[3] = 0;
        p[0] = 0;

        p = LVL_5_FELTZIN_SYSTEM_F7b2f1854_FUN_00447DC8(16, LVL_5_FELTZIN_SYSTEM_F7b2f1854_FUN_00447E60(n));
        n = o->f44;
        o->f4 = p;
        p[1] = 0;
        p[2] = 0;
        p[3] = 0;
        p[0] = 0;

        p = LVL_5_FELTZIN_SYSTEM_F7b2f1854_FUN_00447DC8(16, LVL_5_FELTZIN_SYSTEM_F7b2f1854_FUN_00447E60(n));
        n = o->f44;
        o->f12 = p;
        p[1] = 0;
        p[2] = 0;
        p[3] = 0;
        p[0] = 0;

        p = LVL_5_FELTZIN_SYSTEM_F7b2f1854_FUN_00447DC8(16, LVL_5_FELTZIN_SYSTEM_F7b2f1854_FUN_00447E60(n));
        o->f16 = p;
        p[1] = 0;
        p[2] = 0;
        p[3] = 0;
        p[0] = 0;
    }
    o->f40 = a1;
    o->f32 = 0;
    o->f20 = 0;
    o->f28 = 0;
    o->f24 = 0;
    o->f36 = 0;
    LVL_5_FELTZIN_SYSTEM_F7b2f1854_FUN_00446E88(o, 1);
}
extern void LVL_5_FELTZIN_SYSTEM_F449e2f67_FUN_004471C8(char *p);
extern void LVL_5_FELTZIN_SYSTEM_F449e2f67_FUN_004471C8(char *p);
extern void LVL_5_FELTZIN_SYSTEM_F449e2f67_FUN_004471C8(char *p);
extern void LVL_5_FELTZIN_SYSTEM_F449e2f67_FUN_004471C8(char *p);
extern void LVL_5_FELTZIN_SYSTEM_F449e2f67_FUN_004471C8(char *p);
extern void LVL_5_FELTZIN_SYSTEM_F449e2f67_FUN_004471C8(char *p);
extern void LVL_5_FELTZIN_SYSTEM_F449e2f67_FUN_00447988(char *p);
extern void LVL_5_FELTZIN_SYSTEM_F449e2f67_FUN_00447988(char *p);
extern void LVL_5_FELTZIN_SYSTEM_F449e2f67_FUN_004476F0(char *p);
extern void LVL_5_FELTZIN_SYSTEM_F449e2f67_FUN_00447988(char *p);
extern void LVL_5_FELTZIN_SYSTEM_F449e2f67_FUN_00447988(char *p);
extern void LVL_5_FELTZIN_SYSTEM_F449e2f67_FUN_00447988(char *p);
extern void LVL_5_FELTZIN_SYSTEM_F449e2f67_FUN_00447988(char *p);
extern void LVL_5_FELTZIN_SYSTEM_F449e2f67_FUN_00447988(char *p);

char *LVL_5_FELTZIN_SYSTEM_FUN_004549C8(char *p)
{
    LVL_5_FELTZIN_SYSTEM_F449e2f67_FUN_004471C8(p);
    LVL_5_FELTZIN_SYSTEM_F449e2f67_FUN_004471C8(p + 76);
    LVL_5_FELTZIN_SYSTEM_F449e2f67_FUN_004471C8(p + 152);
    LVL_5_FELTZIN_SYSTEM_F449e2f67_FUN_004471C8(p + 228);
    LVL_5_FELTZIN_SYSTEM_F449e2f67_FUN_004471C8(p + 304);
    LVL_5_FELTZIN_SYSTEM_F449e2f67_FUN_004471C8(p + 380);
    LVL_5_FELTZIN_SYSTEM_F449e2f67_FUN_00447988(p + 456);
    LVL_5_FELTZIN_SYSTEM_F449e2f67_FUN_00447988(p + 528);
    LVL_5_FELTZIN_SYSTEM_F449e2f67_FUN_004476F0(p + 600);
    LVL_5_FELTZIN_SYSTEM_F449e2f67_FUN_00447988(p + 664);
    LVL_5_FELTZIN_SYSTEM_F449e2f67_FUN_00447988(p + 736);
    LVL_5_FELTZIN_SYSTEM_F449e2f67_FUN_00447988(p + 808);
    LVL_5_FELTZIN_SYSTEM_F449e2f67_FUN_00447988(p + 880);
    LVL_5_FELTZIN_SYSTEM_F449e2f67_FUN_00447988(p + 952);
    return p;
}
extern void LVL_5_FELTZIN_SYSTEM_F449e2f67_FUN_004471C8(char *p);
extern void LVL_5_FELTZIN_SYSTEM_F449e2f67_FUN_004471C8(char *p);
extern void LVL_5_FELTZIN_SYSTEM_F449e2f67_FUN_004471C8(char *p);
extern void LVL_5_FELTZIN_SYSTEM_F449e2f67_FUN_004471C8(char *p);
extern void LVL_5_FELTZIN_SYSTEM_F449e2f67_FUN_004471C8(char *p);
extern void LVL_5_FELTZIN_SYSTEM_F449e2f67_FUN_004471C8(char *p);
extern void LVL_5_FELTZIN_SYSTEM_F449e2f67_FUN_00447988(char *p);
extern void LVL_5_FELTZIN_SYSTEM_F449e2f67_FUN_00447988(char *p);
extern void LVL_5_FELTZIN_SYSTEM_F449e2f67_FUN_004476F0(char *p);
extern void LVL_5_FELTZIN_SYSTEM_F449e2f67_FUN_00447988(char *p);
extern void LVL_5_FELTZIN_SYSTEM_F449e2f67_FUN_00447988(char *p);
extern void LVL_5_FELTZIN_SYSTEM_F449e2f67_FUN_00447988(char *p);
extern void LVL_5_FELTZIN_SYSTEM_F449e2f67_FUN_00447988(char *p);
extern void LVL_5_FELTZIN_SYSTEM_F449e2f67_FUN_00447988(char *p);

char *LVL_5_FELTZIN_SYSTEM_FUN_00456428(char *p)
{
    LVL_5_FELTZIN_SYSTEM_F449e2f67_FUN_004471C8(p);
    LVL_5_FELTZIN_SYSTEM_F449e2f67_FUN_004471C8(p + 76);
    LVL_5_FELTZIN_SYSTEM_F449e2f67_FUN_004471C8(p + 152);
    LVL_5_FELTZIN_SYSTEM_F449e2f67_FUN_004471C8(p + 228);
    LVL_5_FELTZIN_SYSTEM_F449e2f67_FUN_004471C8(p + 304);
    LVL_5_FELTZIN_SYSTEM_F449e2f67_FUN_004471C8(p + 380);
    LVL_5_FELTZIN_SYSTEM_F449e2f67_FUN_00447988(p + 456);
    LVL_5_FELTZIN_SYSTEM_F449e2f67_FUN_00447988(p + 528);
    LVL_5_FELTZIN_SYSTEM_F449e2f67_FUN_004476F0(p + 600);
    LVL_5_FELTZIN_SYSTEM_F449e2f67_FUN_00447988(p + 664);
    LVL_5_FELTZIN_SYSTEM_F449e2f67_FUN_00447988(p + 736);
    LVL_5_FELTZIN_SYSTEM_F449e2f67_FUN_00447988(p + 808);
    LVL_5_FELTZIN_SYSTEM_F449e2f67_FUN_00447988(p + 880);
    LVL_5_FELTZIN_SYSTEM_F449e2f67_FUN_00447988(p + 952);
    return p;
}
extern char *LVL_5_FELTZIN_SYSTEM_Ffc961fca_FUN_003387A8(char *a1);
extern void LVL_5_FELTZIN_SYSTEM_Ffc961fca_FUN_00306E98(char *dst, char *src);
extern void LVL_5_FELTZIN_SYSTEM_Ffc961fca_FUN_00306630(char *dst, char *src, char *tail);
extern void LVL_5_FELTZIN_SYSTEM_Ffc961fca_FUN_00306660(char *dst, char *src, char *tail);
extern void LVL_5_FELTZIN_SYSTEM_Ffc961fca_FUN_00306E98(char *dst, char *src);
extern void LVL_5_FELTZIN_SYSTEM_Ffc961fca_FUN_00307120(char *dst, char *src);
extern void LVL_5_FELTZIN_SYSTEM_Ffc961fca_FUN_00306AD8(char *dst, char *src, char *tail);
extern void LVL_5_FELTZIN_SYSTEM_Ffc961fca_FUN_00306AD8(char *dst, char *src, char *tail);
extern void LVL_5_FELTZIN_SYSTEM_Ffc961fca_FUN_00306AD8(char *dst, char *src, char *tail);
extern void LVL_5_FELTZIN_SYSTEM_Ffc961fca_FUN_00306630(char *dst, char *src, char *tail);
extern void LVL_5_FELTZIN_SYSTEM_Ffc961fca_FUN_003071C0(char *dst, char *src, char *tail);

void LVL_5_FELTZIN_SYSTEM_FUN_003B0FB0(char *o0, char *o1)
{
    char b0[64];
    char b1[64];
    char b2[64];
    char *r = LVL_5_FELTZIN_SYSTEM_Ffc961fca_FUN_003387A8(o1);

    if (r == 0)
        return;
    LVL_5_FELTZIN_SYSTEM_Ffc961fca_FUN_00306E98(b0, r);
    LVL_5_FELTZIN_SYSTEM_Ffc961fca_FUN_00306630(o0 + 16, o0 + 16, r + 16);
    LVL_5_FELTZIN_SYSTEM_Ffc961fca_FUN_00306660(o0 + 16, o0 + 16, o1 + 16);
    if ((*(int *)(r + 60) & 2) != 0) {
        LVL_5_FELTZIN_SYSTEM_Ffc961fca_FUN_00306E98(b2, r + 32);
        LVL_5_FELTZIN_SYSTEM_Ffc961fca_FUN_00307120(b1, b2);
        LVL_5_FELTZIN_SYSTEM_Ffc961fca_FUN_00306AD8(o0 + 16, o0 + 16, b1);
        LVL_5_FELTZIN_SYSTEM_Ffc961fca_FUN_00306AD8(o0 + 16, o0 + 16, o1 + 192);
    } else {
        LVL_5_FELTZIN_SYSTEM_Ffc961fca_FUN_00306AD8(o0 + 16, o0 + 16, b0);
    }
    LVL_5_FELTZIN_SYSTEM_Ffc961fca_FUN_00306630(o0 + 16, o0 + 16, o1 + 16);
    LVL_5_FELTZIN_SYSTEM_Ffc961fca_FUN_003071C0(o0 + 192, b0, o0 + 192);
}
extern int LVL_5_FELTZIN_SYSTEM_Fd1c348f5_FUN_003062D0(char *p);
extern int LVL_5_FELTZIN_SYSTEM_Fd1c348f5_FUN_00307778(float v);
extern int LVL_5_FELTZIN_SYSTEM_Fd1c348f5_FUN_003062D0(char *p);
extern void LVL_5_FELTZIN_SYSTEM_Fd1c348f5_FUN_003423C8(char *p);
extern int LVL_5_FELTZIN_SYSTEM_Fd1c348f5_FUN_00307778(float v);

void LVL_5_FELTZIN_SYSTEM_FUN_00345B30(char *p)
{
    char *q = p + 32;
    int r;
    int v;
    float f;

    *(unsigned char *)(p + 8) = *(unsigned char *)(p + 8) + *(unsigned char *)(q + 8);
    *(float *)(p + 24) = *(float *)(p + 24) + *(float *)(q + 16);
    *(float *)(p + 12) = *(float *)(p + 12) * *(float *)(q + 12);
    if (*(int *)(q + 4) == 0) {
        r = LVL_5_FELTZIN_SYSTEM_Fd1c348f5_FUN_003062D0(p + 10);
        if (r != 0) {
            *(int *)(q + 4) = 1;
            *(short *)(p + 10) = 30;
            *(int *)(p + 4) = *(int *)(q + 20) | 0x7f000000;
        } else {
            f = (float)(10 - *(short *)(p + 10)) * 9.6000003814697265625000e+00f;
            v = LVL_5_FELTZIN_SYSTEM_Fd1c348f5_FUN_00307778(f);
            *(int *)(p + 4) = ((v + 32) << 24) | *(int *)(q + 20);
        }
    } else {
        r = LVL_5_FELTZIN_SYSTEM_Fd1c348f5_FUN_003062D0(p + 10);
        if (r != 0) {
            LVL_5_FELTZIN_SYSTEM_Fd1c348f5_FUN_003423C8(p);
        } else {
            f = (float)*(short *)(p + 10) * 4.2333333492279052734375e+00f;
            v = LVL_5_FELTZIN_SYSTEM_Fd1c348f5_FUN_00307778(f);
            *(int *)(p + 4) = (v << 24) | *(int *)(q + 20);
        }
    }
}
extern void LVL_5_FELTZIN_SYSTEM_F2d5993bb_FUN_003063B8(char *p, int a1, int a2);
extern void LVL_5_FELTZIN_SYSTEM_F2d5993bb_FUN_00306408(char *p, int a1, int a2);
extern int LVL_5_FELTZIN_SYSTEM_F2d5993bb_FUN_003242F8(char *p, int a1);

int LVL_5_FELTZIN_SYSTEM_FUN_003243E0(char *out, int mult, int *recs)
{
    int off = 0;
    char *p = out + 8;
    char *r;
    int v;
    int w;

    if (*(int *)recs != 0) {
        r = (char *)recs;
        do {
            off += 8;
            v = *(int *)(r + 0) + mult * *(int *)(r + 4);
            *(int *)(p + 0) = *(int *)(r + 8);
            *(int *)(p + 4) = *(int *)(r + 4);
            p += 8;
            if (*(int *)(r + 8) == 6000)
                LVL_5_FELTZIN_SYSTEM_F2d5993bb_FUN_003063B8(p, 0, *(int *)(r + 4));
            else
                LVL_5_FELTZIN_SYSTEM_F2d5993bb_FUN_00306408(p, v, *(int *)(r + 4));
            w = *(int *)(r + 4);
            r += 16;
            p += w;
            off += w;
            p = (char *)(((int)p + 3) & ~3);
            off = (off + 3) & ~3;
        } while (*(int *)r != 0);
    }
    off += 8;
    *(int *)(p + 4) = 0;
    *(int *)(p + 0) = -1;
    v = LVL_5_FELTZIN_SYSTEM_F2d5993bb_FUN_003242F8(out + 8, off);
    *(int *)(out + 4) = v;
    *(int *)(out + 0) = off;
    return off + 8;
}
extern int LVL_5_FELTZIN_SYSTEM_F77a1e64d_FUN_00336F78(char *object);
extern float *LVL_5_FELTZIN_SYSTEM_F77a1e64d_FUN_003365D0(char *object);

int LVL_5_FELTZIN_SYSTEM_FUN_003EC0B0(char *object)
{
    float *p;

    if (LVL_5_FELTZIN_SYSTEM_F77a1e64d_FUN_00336F78(object) != 0)
        return 0;
    p = LVL_5_FELTZIN_SYSTEM_F77a1e64d_FUN_003365D0(object);
    if (p == 0)
        return 0;
    if (0.0f < *p)
        return 0;
    return 1;
}
extern int LVL_5_FELTZIN_SYSTEM_F77a1e64d_FUN_00336F78(char *object);
extern float *LVL_5_FELTZIN_SYSTEM_F77a1e64d_FUN_003365D0(char *object);

int LVL_5_FELTZIN_SYSTEM_FUN_003F5C68(char *object)
{
    float *p;

    if (LVL_5_FELTZIN_SYSTEM_F77a1e64d_FUN_00336F78(object) != 0)
        return 0;
    p = LVL_5_FELTZIN_SYSTEM_F77a1e64d_FUN_003365D0(object);
    if (p == 0)
        return 0;
    if (0.0f < *p)
        return 0;
    return 1;
}
extern int LVL_5_FELTZIN_SYSTEM_F77a1e64d_FUN_00336F78(char *object);
extern float *LVL_5_FELTZIN_SYSTEM_F77a1e64d_FUN_003365D0(char *object);

int LVL_5_FELTZIN_SYSTEM_FUN_00438818(char *object)
{
    float *p;

    if (LVL_5_FELTZIN_SYSTEM_F77a1e64d_FUN_00336F78(object) != 0)
        return 0;
    p = LVL_5_FELTZIN_SYSTEM_F77a1e64d_FUN_003365D0(object);
    if (p == 0)
        return 0;
    if (0.0f < *p)
        return 0;
    return 1;
}
extern void LVL_5_FELTZIN_SYSTEM_Fb342d477_D_0011AC60(int value);
extern void LVL_5_FELTZIN_SYSTEM_Fb342d477_FUN_00461840(int value);
extern void LVL_5_FELTZIN_SYSTEM_Fb342d477_FUN_004617D0(int value);
extern void LVL_5_FELTZIN_SYSTEM_Fb342d477_D_0011AC40(int value);

int LVL_5_FELTZIN_SYSTEM_FUN_00461E00(int *p)
{
    LVL_5_FELTZIN_SYSTEM_Fb342d477_D_0011AC60(p[16]);
    p[17] = 0;
    LVL_5_FELTZIN_SYSTEM_Fb342d477_FUN_00461840(5);
    p[7] = *(volatile int *)0x1000B410;
    p[8] = *(volatile int *)0x1000B430;
    p[9] = *(volatile int *)0x1000B420;
    p[10] = *(volatile int *)0x1000B400;
    if (*(volatile int *)0x10002010 & 0xF0)
        while (*(volatile int *)0x10002010 & 0xF0)
            ;
    LVL_5_FELTZIN_SYSTEM_Fb342d477_FUN_004617D0(0);
    p[11] = *(volatile int *)0x1000B010;
    p[12] = *(volatile int *)0x1000B020;
    p[13] = *(volatile int *)0x1000B000;
    p[14] = *(volatile int *)0x10002020;
    p[15] = *(volatile int *)0x10002010;
    LVL_5_FELTZIN_SYSTEM_Fb342d477_D_0011AC40(p[16]);
    return 1;
}
/* Family 0e7bb6a8908d30dc -- 244 bytes, 28 placements (1 boot + 27 levels). */

extern char *LVL_5_FELTZIN_SYSTEM_F0e7bb6a8_FUN_003387A8(char *a);
extern void LVL_5_FELTZIN_SYSTEM_F0e7bb6a8_FUN_00306E98(char *dst, char *src);
extern void LVL_5_FELTZIN_SYSTEM_F0e7bb6a8_FUN_00307120(char *dst, char *src);
extern void LVL_5_FELTZIN_SYSTEM_F0e7bb6a8_FUN_00307120(char *dst, char *src);
extern void LVL_5_FELTZIN_SYSTEM_F0e7bb6a8_FUN_00306660(char *dst, char *a, char *b);
extern void LVL_5_FELTZIN_SYSTEM_F0e7bb6a8_FUN_00306B00(char *a, char *b, char *c);
extern void LVL_5_FELTZIN_SYSTEM_F0e7bb6a8_FUN_00306E98(char *dst, char *src);
extern void LVL_5_FELTZIN_SYSTEM_F0e7bb6a8_FUN_00307210(char *a, char *b, char *c);
extern void LVL_5_FELTZIN_SYSTEM_F0e7bb6a8_FUN_00336A90(char *a, char *b);

int LVL_5_FELTZIN_SYSTEM_FUN_00338CF0(char *unused, char *obj, char *arg2, char *arg3, char *arg4, char *arg5)
{
    char buf0[64];
    char buf1[16];
    char buf2[64];
    char *p;

    p = LVL_5_FELTZIN_SYSTEM_F0e7bb6a8_FUN_003387A8(obj);
    if (p == 0)
        return 0;
    if (*(int *)(p + 60) & 0x40) {
        LVL_5_FELTZIN_SYSTEM_F0e7bb6a8_FUN_00306E98(buf0, obj + 240);
        LVL_5_FELTZIN_SYSTEM_F0e7bb6a8_FUN_00307120(buf0, buf0);
    } else {
        LVL_5_FELTZIN_SYSTEM_F0e7bb6a8_FUN_00307120(buf0, obj + 192);
    }
    LVL_5_FELTZIN_SYSTEM_F0e7bb6a8_FUN_00306660(buf1, arg2, obj + 16);
    LVL_5_FELTZIN_SYSTEM_F0e7bb6a8_FUN_00306B00(arg4, buf1, buf0);
    LVL_5_FELTZIN_SYSTEM_F0e7bb6a8_FUN_00306E98(buf2, arg3);
    LVL_5_FELTZIN_SYSTEM_F0e7bb6a8_FUN_00307210(buf2, buf0, buf2);
    LVL_5_FELTZIN_SYSTEM_F0e7bb6a8_FUN_00336A90(buf2, arg5);
    return 1;
}
extern void LVL_5_FELTZIN_SYSTEM_Fa2a84657_FUN_003066B8(float *tmp, char *v, float k);
extern void LVL_5_FELTZIN_SYSTEM_Fa2a84657_FUN_00306648(float *tmp, char *a, char *v);
extern int LVL_5_FELTZIN_SYSTEM_Fa2a84657_FUN_003062D0(char *field);
extern void LVL_5_FELTZIN_SYSTEM_Fa2a84657_FUN_003423C8(unsigned char *p);

void LVL_5_FELTZIN_SYSTEM_FUN_0034B878(unsigned char *p)
{
    float tmp[4];
    char *v;
    int n;

    v = (char *)p + 32;
    LVL_5_FELTZIN_SYSTEM_Fa2a84657_FUN_003066B8(tmp, v, 9.4999998807907104492188e-01f);
    *(float *)(v + 8) = *(float *)(v + 8) + 1.3888889225199818611145e-03f;
    LVL_5_FELTZIN_SYSTEM_Fa2a84657_FUN_00306648(tmp, (char *)p + 16, v);

    n = *(int *)(p + 4) + (int)0xFE000000;
    *(int *)(p + 4) = n;
    if (((unsigned)(n & 0xFF000000) - 1) > 0x5EFFFFFFu || LVL_5_FELTZIN_SYSTEM_Fa2a84657_FUN_003062D0((char *)p + 10) != 0) {
        LVL_5_FELTZIN_SYSTEM_Fa2a84657_FUN_003423C8(p);
    } else {
        float f0;
        float f1;

        f1 = *(float *)(p + 12);
        f0 = 2.1000000000000000000000e+05f - f1;
        f0 = f0 * 7.0000000298023223876953e-02f;
        f1 = f1 + f0;
        *(float *)(p + 12) = f1;
        p[8] = p[8] + 1;
    }
}
extern int LVL_5_FELTZIN_SYSTEM_F750245c6_D_001A7340 __attribute__((sda));
extern void LVL_5_FELTZIN_SYSTEM_F750245c6_FUN_00313A78(int a, int b, int c, int d, char *e, int f);
void LVL_5_FELTZIN_SYSTEM_FUN_0035AA58(int a0, char *a1)
{
    int h, k, p, m;
    k = a0 / 2 + 5;
    h = LVL_5_FELTZIN_SYSTEM_F750245c6_D_001A7340 / 2;
    m = h - k;
    p = h + k;
    LVL_5_FELTZIN_SYSTEM_F750245c6_FUN_00313A78(m - 2, 312, p + 4, 314, a1, 0);
    LVL_5_FELTZIN_SYSTEM_F750245c6_FUN_00313A78(m - 2, 333, p + 4, 335, a1, 0);
    LVL_5_FELTZIN_SYSTEM_F750245c6_FUN_00313A78(m - 2, 313, m, 334, a1, 0);
    LVL_5_FELTZIN_SYSTEM_F750245c6_FUN_00313A78(p + 2, 313, p + 4, 334, a1, 0);
}
extern float LVL_5_FELTZIN_SYSTEM_Fe617c30b_FUN_00307768(int a);
extern void LVL_5_FELTZIN_SYSTEM_Fe617c30b_FUN_003066A0(char *p, char *q, float f);
extern void LVL_5_FELTZIN_SYSTEM_Fe617c30b_FUN_00306630(char *p, char *q, char *r);
extern int LVL_5_FELTZIN_SYSTEM_Fe617c30b_FUN_00334BE0(int a, int b, float f);
extern int LVL_5_FELTZIN_SYSTEM_Fe617c30b_FUN_003062D0(char *p);
extern void LVL_5_FELTZIN_SYSTEM_Fe617c30b_FUN_003423C8(char *p);

void LVL_5_FELTZIN_SYSTEM_FUN_003441B0(char *a0)
{
    char *s0 = a0 + 32;
    int x;
    int u;
    int t;
    float f;

    x = *(int *)(s0 + 28);
    t = *(short *)(a0 + 10);
    u = *(short *)(s0 + 24) * (x - t) / x + *(short *)(s0 + 26);

    f = LVL_5_FELTZIN_SYSTEM_Fe617c30b_FUN_00307768(u) * 1000.0f;
    *(float *)(a0 + 12) = f;
    LVL_5_FELTZIN_SYSTEM_Fe617c30b_FUN_003066A0(s0, s0, 9.8000001907348632812500e-01f);
    LVL_5_FELTZIN_SYSTEM_Fe617c30b_FUN_00306630(a0 + 16, a0 + 16, s0);
    *(unsigned char *)(a0 + 8) = *(unsigned char *)(a0 + 8) + 1;
    f = LVL_5_FELTZIN_SYSTEM_Fe617c30b_FUN_00307768(*(int *)(s0 + 28));
    *(int *)(a0 + 4) = LVL_5_FELTZIN_SYSTEM_Fe617c30b_FUN_00334BE0(*(int *)(s0 + 20), *(int *)(s0 + 16),
                               (float)*(short *)(a0 + 10) / f);
    if (LVL_5_FELTZIN_SYSTEM_Fe617c30b_FUN_003062D0(a0 + 10) != 0)
        LVL_5_FELTZIN_SYSTEM_Fe617c30b_FUN_003423C8(a0);
}
extern int LVL_5_FELTZIN_SYSTEM_F4a4e68d9_D_001A904C __attribute__((sda));
extern void LVL_5_FELTZIN_SYSTEM_F4a4e68d9_FUN_0045F4F0(int);

void LVL_5_FELTZIN_SYSTEM_FUN_00324D00(void)
{
    int value = LVL_5_FELTZIN_SYSTEM_F4a4e68d9_D_001A904C;

    if (value != 0)
        LVL_5_FELTZIN_SYSTEM_F4a4e68d9_FUN_0045F4F0(value + 0x36F28);
}
extern int LVL_5_FELTZIN_SYSTEM_F4a4e68d9_D_001A904C __attribute__((sda));
extern void LVL_5_FELTZIN_SYSTEM_F4a4e68d9_FUN_0045F510(int);

void LVL_5_FELTZIN_SYSTEM_FUN_00325388(void)
{
    int value = LVL_5_FELTZIN_SYSTEM_F4a4e68d9_D_001A904C;

    if (value != 0)
        LVL_5_FELTZIN_SYSTEM_F4a4e68d9_FUN_0045F510(value + 0x36F28);
}
extern int LVL_5_FELTZIN_SYSTEM_F4a4e68d9_D_001A904C __attribute__((sda));
extern void LVL_5_FELTZIN_SYSTEM_F4a4e68d9_FUN_0045F4B0(int);

void LVL_5_FELTZIN_SYSTEM_FUN_003255D8(void)
{
    int value = LVL_5_FELTZIN_SYSTEM_F4a4e68d9_D_001A904C;

    if (value != 0)
        LVL_5_FELTZIN_SYSTEM_F4a4e68d9_FUN_0045F4B0(value + 0x36F28);
}
extern int LVL_5_FELTZIN_SYSTEM_F4a4e68d9_D_001A904C __attribute__((sda));
extern void LVL_5_FELTZIN_SYSTEM_F4a4e68d9_FUN_0045F530(int);

void LVL_5_FELTZIN_SYSTEM_FUN_00325608(void)
{
    int value = LVL_5_FELTZIN_SYSTEM_F4a4e68d9_D_001A904C;

    if (value != 0)
        LVL_5_FELTZIN_SYSTEM_F4a4e68d9_FUN_0045F530(value + 0x36F28);
}
extern int LVL_5_FELTZIN_SYSTEM_F4a4e68d9_D_001A904C __attribute__((sda));
extern void LVL_5_FELTZIN_SYSTEM_F4a4e68d9_FUN_004490C8(int);

void LVL_5_FELTZIN_SYSTEM_FUN_00326218(void)
{
    int value = LVL_5_FELTZIN_SYSTEM_F4a4e68d9_D_001A904C;

    if (value != 0)
        LVL_5_FELTZIN_SYSTEM_F4a4e68d9_FUN_004490C8(value + 0x36F28);
}
extern void LVL_5_FELTZIN_SYSTEM_F42d2147f_FUN_003068F8(char *a0, char *a1, float f);
extern void LVL_5_FELTZIN_SYSTEM_F42d2147f_FUN_003066A0(char *a0, char *a1, float f);
extern void LVL_5_FELTZIN_SYSTEM_F42d2147f_FUN_00306630(char *a0, char *a1, char *a2);
extern char LVL_5_FELTZIN_SYSTEM_F42d2147f_D_00189E20[];
extern char LVL_5_FELTZIN_SYSTEM_F42d2147f_D_00189EA0[];

void LVL_5_FELTZIN_SYSTEM_FUN_0043E988(char *object)
{
    char local[16];
    char buf[16];
    char *p = LVL_5_FELTZIN_SYSTEM_F42d2147f_D_00189E20;
    unsigned char v;

    LVL_5_FELTZIN_SYSTEM_F42d2147f_FUN_003068F8(local, (char *)(*(int *)(p + 8848) + 224), 1.0f);
    v = *(unsigned char *)(p + 8884);
    if (v == 2) {
        LVL_5_FELTZIN_SYSTEM_F42d2147f_FUN_003066A0(buf, local, 9.5f);
    } else if (v == 1) {
        LVL_5_FELTZIN_SYSTEM_F42d2147f_FUN_003066A0(buf, local, 0.75f);
    } else {
        LVL_5_FELTZIN_SYSTEM_F42d2147f_FUN_003066A0(buf, local, 1.6f);
    }
    LVL_5_FELTZIN_SYSTEM_F42d2147f_FUN_00306630(object + 48, LVL_5_FELTZIN_SYSTEM_F42d2147f_D_00189EA0, buf);
    LVL_5_FELTZIN_SYSTEM_F42d2147f_FUN_00306630(object + 48, LVL_5_FELTZIN_SYSTEM_F42d2147f_D_00189EA0 + 208, object + 48);
}
extern char LVL_5_FELTZIN_SYSTEM_F93479d13_D_00189E20[];
extern void LVL_5_FELTZIN_SYSTEM_F93479d13_FUN_00328870(char *entry);
extern void LVL_5_FELTZIN_SYSTEM_F93479d13_FUN_00328870(char *entry);

void LVL_5_FELTZIN_SYSTEM_FUN_002C9AB0(int slot, int value)
{
    char *e;
    void (*fn)(char *);

    {
        char *p = LVL_5_FELTZIN_SYSTEM_F93479d13_D_00189E20 + slot * 80;

        *(int *)(p + 4660) = value;
        if (*(int *)(p + 4676) != 3) {
            *(int *)(p + 4676) = 3;
            e = *(char **)(p + 4640);
            if (e != 0) {
                if (*(unsigned char *)(e + 32) != 254) {
                    if (*(unsigned char *)(e + 32) != 253) {
                        fn = *(void (**)(char *))(e + 100);
                        if (fn != 0)
                            fn(e);
                    }
                }
            }
        }
    }
    {
        char *q = LVL_5_FELTZIN_SYSTEM_F93479d13_D_00189E20 + slot * 80;

        e = *(char **)(q + 4640);
        *(int *)(q + 4676) = 0;
        *(int *)(q + 4680) = 0;
        if (e != 0) {
            LVL_5_FELTZIN_SYSTEM_F93479d13_FUN_00328870(e);
            *(char **)(q + 4640) = 0;
        }
        e = *(char **)(q + 4644);
        if (e != 0 && slot != 3) {
            LVL_5_FELTZIN_SYSTEM_F93479d13_FUN_00328870(e);
            *(char **)(q + 4644) = 0;
        }
    }
}
extern char LVL_5_FELTZIN_SYSTEM_F5fa3e1af_D_00189E20[];
extern float LVL_5_FELTZIN_SYSTEM_F5fa3e1af_FUN_003065F8(float *buf);
extern float LVL_5_FELTZIN_SYSTEM_F5fa3e1af_FUN_00306760(float *buf);

void LVL_5_FELTZIN_SYSTEM_FUN_003E74B0(char *obj)
{
    float buf[2];
    char *d = LVL_5_FELTZIN_SYSTEM_F5fa3e1af_D_00189E20;
    char *e = *(char **)(obj + 104);
    float a, b, x;

    a = -*(float *)(d + 8112);
    *(float *)(e + 20) = a;
    b = -*(float *)(d + 8116);
    *(float *)(e + 16) = b;

    if (a > 1.0f) {
        *(float *)(e + 20) = 1.0f;
    } else if (a < -1.0f) {
        *(float *)(e + 20) = -1.0f;
    }

    x = *(float *)(e + 16);
    if (x > 1.0f) {
        *(float *)(e + 16) = 1.0f;
    } else if (x < -1.0f) {
        *(float *)(e + 16) = -1.0f;
    }
    LVL_5_FELTZIN_SYSTEM_F5fa3e1af_FUN_003065F8(buf);
    buf[0] = *(float *)(e + 16);
    buf[1] = *(float *)(e + 20);
    *(float *)(e + 48) = LVL_5_FELTZIN_SYSTEM_F5fa3e1af_FUN_00306760(buf);
}


extern int LVL_5_FELTZIN_SYSTEM_F9a90bcc4_FUN_00332AB8(int count);

int LVL_5_FELTZIN_SYSTEM_FUN_0033DAD8(u8 *owner, int b, int *outIndex,
                                       float *o0, float *o1, float *o2, float *o3,
                                       float *o4, float *o5, float *o6)
{
    int n;
    int count;
    int i;
    int k;
    int left;
    u8 *p;

    n = 0;
    count = *(u8 *)(*(int *)(owner + 36) + 12);
    if (count != 0) {
        int *t = (int *)(*(int *)(owner + 36) + 72);
        u8 *q;
        left = count;
        do {
            q = *(u8 **)(*t + 20);
            if (q != 0 && *q == b)
                n++;
            t++;
            left--;
        } while (left != 0);
    }

    if (n != 0)
        goto second;

    return 0;

found:
    *o0 = *(float *)(p + 8) * 0.016666668f;
    *o1 = *(float *)(p + 12) * 0.016666668f;
    *o2 = *(float *)(p + 16) * 0.00027777778f;
    *o3 = *(float *)(p + 20) * 0.00027777778f;
    *o6 = *(float *)(p + 4) * 0.00027777778f;
    *o4 = *(float *)(p + 24);
    *o5 = *(float *)(p + 28);
    *outIndex = i;
    return 1;

second:
    k = LVL_5_FELTZIN_SYSTEM_F9a90bcc4_FUN_00332AB8(n);
    for (i = 0; i < *(u8 *)(*(int *)(owner + 36) + 12); i++) {
        char *tbl = (char *)(*(int *)(owner + 36) + 72);
        char *e = *(char **)(tbl + i * 4);
        p = *(u8 **)(e + 20);
        if (p == 0 || *p != b)
            continue;
        if (k == 0)
            goto found;
        k--;
    }
    return 0;
}


extern void LVL_5_FELTZIN_SYSTEM_Feda2e14e_FUN_00306630(void *out, void *in, void *src);
extern int LVL_5_FELTZIN_SYSTEM_Feda2e14e_FUN_003062D0(void *p);
extern void LVL_5_FELTZIN_SYSTEM_Feda2e14e_FUN_003423C8(void *self);
extern float LVL_5_FELTZIN_SYSTEM_Feda2e14e_FUN_00307768(int n);
extern int LVL_5_FELTZIN_SYSTEM_Feda2e14e_FUN_003077C0(int handle, int previous, float ratio);
extern char LVL_5_FELTZIN_SYSTEM_Feda2e14e_D_00189E20[];

void LVL_5_FELTZIN_SYSTEM_FUN_0034CA78(u8 *self)
{
    char *s2 = (char *)self + 32;
    int n;
    float a;
    float b;

    if (*(int *)(s2 + 28) == 1) {
        char *base = LVL_5_FELTZIN_SYSTEM_Feda2e14e_D_00189E20;
        *(float *)(self + 16) = *(float *)(base + 128) + *(float *)(s2 + 16);
        *(float *)(self + 20) = *(float *)(base + 132) + *(float *)(s2 + 20);
        *(float *)(self + 24) = *(float *)(base + 136) + *(float *)(s2 + 24);
        LVL_5_FELTZIN_SYSTEM_Feda2e14e_FUN_00306630(self + 16, self + 16, s2);
        *(float *)(s2 + 16) = *(float *)(self + 16) - *(float *)(base + 128);
        *(float *)(s2 + 20) = *(float *)(self + 20) - *(float *)(base + 132);
        *(float *)(s2 + 24) = *(float *)(self + 24) - *(float *)(base + 136);
    } else {
        LVL_5_FELTZIN_SYSTEM_Feda2e14e_FUN_00306630(self + 16, self + 16, s2);
    }

    if (*(float *)(self + 16) < 2.0f || *(float *)(self + 16) > 1021.0f
        || *(float *)(self + 20) < 2.0f || *(float *)(self + 20) > 1021.0f
        || *(float *)(self + 24) < 2.0f || *(float *)(self + 24) > 1021.0f) {
        LVL_5_FELTZIN_SYSTEM_Feda2e14e_FUN_003423C8(self);
        return;
    }

    if (LVL_5_FELTZIN_SYSTEM_Feda2e14e_FUN_003062D0((char *)self + 10) != 0) {
        LVL_5_FELTZIN_SYSTEM_Feda2e14e_FUN_003423C8(self);
        return;
    }

    n = *(int *)(self + 4) & 0xFFFFFF;
    a = LVL_5_FELTZIN_SYSTEM_Feda2e14e_FUN_00307768(*(short *)(self + 10) - 1);
    b = LVL_5_FELTZIN_SYSTEM_Feda2e14e_FUN_00307768(*(short *)(self + 10));
    *(int *)(self + 4) = LVL_5_FELTZIN_SYSTEM_Feda2e14e_FUN_003077C0(n, *(int *)(self + 4), a / b);
}
extern void LVL_5_FELTZIN_SYSTEM_Feb99aa89_FUN_002EBEB8(char *target, int mode, float value, float zero, float scale);
extern int LVL_5_FELTZIN_SYSTEM_Feb99aa89_FUN_002F6C50(char *first, char *second, int mode, int flag, int extra);
extern float LVL_5_FELTZIN_SYSTEM_Feb99aa89_FUN_003067D8(char *source, short *table);

extern short LVL_5_FELTZIN_SYSTEM_Feb99aa89_D_001BFB20[];
extern float LVL_5_FELTZIN_SYSTEM_Feb99aa89_D_0018A084;

int LVL_5_FELTZIN_SYSTEM_FUN_002C3988(float *out, float scale, float amount)
{
    char buffer[32];

    LVL_5_FELTZIN_SYSTEM_Feb99aa89_FUN_002EBEB8(buffer, 1, LVL_5_FELTZIN_SYSTEM_Feb99aa89_D_0018A084 - 0.02f, 0.0f, scale);
    LVL_5_FELTZIN_SYSTEM_Feb99aa89_FUN_002EBEB8(buffer + 16, 1, amount, 0.0f, scale);
    if (LVL_5_FELTZIN_SYSTEM_Feb99aa89_FUN_002F6C50(buffer, buffer + 16, 2, 0, 0)) {
        if (out)
            *out = LVL_5_FELTZIN_SYSTEM_Feb99aa89_FUN_003067D8(buffer, LVL_5_FELTZIN_SYSTEM_Feb99aa89_D_001BFB20);
        return 1;
    }
    return 0;
}
#ifndef RAC2_T_V4_FC3CB9262
#define RAC2_T_V4_FC3CB9262
typedef int V4_Fc3cb9262 __attribute__((mode(TI)));
#endif


extern void LVL_5_FELTZIN_SYSTEM_Fc3cb9262_FUN_00306630(char *a, char *b, char *c);
extern int LVL_5_FELTZIN_SYSTEM_Fc3cb9262_FUN_00307778(float f);
extern int LVL_5_FELTZIN_SYSTEM_Fc3cb9262_FUN_003062D0(char *a);
extern void LVL_5_FELTZIN_SYSTEM_Fc3cb9262_FUN_003423C8(char *a);

void LVL_5_FELTZIN_SYSTEM_FUN_00351760(char *a0)
{
    V4_Fc3cb9262 buf;
    char *s0 = a0 + 32;
    float f0;
    float f1;
    float f2;

    f1 = *(float *)(s0 + 16) + 1.0000000474974513053894e-03f;
    f2 = *(float *)(s0 + 8) - 3.0000000260770320892334e-03f;
    *(float *)(s0 + 16) = f1;
    *(float *)(s0 + 8) = f2;
    f0 = *(float *)(s0 + 20) * f1 * 2.1000000000000000000000e+05f;
    buf = *(V4_Fc3cb9262 *)s0;
    *(float *)(a0 + 12) = f0;
    LVL_5_FELTZIN_SYSTEM_Fc3cb9262_FUN_00306630(a0 + 16, a0 + 16, (char *)&buf);
    *(int *)(a0 + 4) = (LVL_5_FELTZIN_SYSTEM_Fc3cb9262_FUN_00307778((float)*(short *)(a0 + 10)) << 24) | 0x00FFD2D2;
    *(unsigned char *)(a0 + 8) = *(unsigned char *)(a0 + 8) + *(unsigned char *)(s0 + 24);
    if (LVL_5_FELTZIN_SYSTEM_Fc3cb9262_FUN_003062D0(a0 + 10) != 0)
        LVL_5_FELTZIN_SYSTEM_Fc3cb9262_FUN_003423C8(a0);
}
extern void LVL_5_FELTZIN_SYSTEM_Fc186f630_FUN_003068F8(char *local, char *a, float k);
extern float LVL_5_FELTZIN_SYSTEM_Fc186f630_FUN_00306720(char *a, char *src);
extern void LVL_5_FELTZIN_SYSTEM_Fc186f630_FUN_003066A0(char *dst, char *src, float k);
extern void LVL_5_FELTZIN_SYSTEM_Fc186f630_FUN_00306660(char *dst, char *src, char *local);

extern char LVL_5_FELTZIN_SYSTEM_Fc186f630_D_00189E20[];            /* 0x00189E20 */

#ifndef RAC2_T_V4_FC186F630
#define RAC2_T_V4_FC186F630
typedef int V4_Fc186f630 __attribute__((mode(TI)));
#endif


void LVL_5_FELTZIN_SYSTEM_FUN_002EC1E0(char *dst, char *src)
{
    char local[16];
    char *base;
    float f;

    base = LVL_5_FELTZIN_SYSTEM_Fc186f630_D_00189E20;
    switch (*(unsigned char *)(base + 8899)) {
    case 0:
        *(V4_Fc186f630 *)dst = *(V4_Fc186f630 *)src;
        *(int *)(dst + 8) = 0;
        break;
    case 1:
        LVL_5_FELTZIN_SYSTEM_Fc186f630_FUN_003068F8(local, base + 672, 1.0f);
        f = LVL_5_FELTZIN_SYSTEM_Fc186f630_FUN_00306720(local, src);
        LVL_5_FELTZIN_SYSTEM_Fc186f630_FUN_003066A0(local, local, f);
        LVL_5_FELTZIN_SYSTEM_Fc186f630_FUN_00306660(dst, src, local);
        break;
    case 2:
        f = LVL_5_FELTZIN_SYSTEM_Fc186f630_FUN_00306720(base + 704, src);
        LVL_5_FELTZIN_SYSTEM_Fc186f630_FUN_003066A0(local, base + 704, f);
        LVL_5_FELTZIN_SYSTEM_Fc186f630_FUN_00306660(dst, src, local);
        break;
    }
}


#ifndef RAC2_T_TI_F41EB487E
#define RAC2_T_TI_F41EB487E
typedef int TI_F41eb487e __attribute__((mode(TI)));
#endif


extern void LVL_5_FELTZIN_SYSTEM_F41eb487e_FUN_00306B00(void *a, void *b, void *c);
extern void LVL_5_FELTZIN_SYSTEM_F41eb487e_FUN_003066A0(void *a, void *b, float value);
extern void LVL_5_FELTZIN_SYSTEM_F41eb487e_FUN_002D1780(void *a, void *b, int c, float p, float q, float r);
extern void LVL_5_FELTZIN_SYSTEM_F41eb487e_FUN_00306660(void *a, void *b, void *c);
extern void LVL_5_FELTZIN_SYSTEM_F41eb487e_FUN_00306630(void *a, void *b, void *c);


#ifndef RAC2_T_VEC4_F41EB487E
#define RAC2_T_VEC4_F41EB487E
typedef struct {
    int a;
    int b;
    float c;
    float d;
} Vec4_F41eb487e;
#endif


#ifndef RAC2_T_RESIDENTSTATE_F41EB487E
#define RAC2_T_RESIDENTSTATE_F41EB487E
typedef struct {
    u8 pad000[0x80];
    u8 area080[0x218 - 0x80];
    short h218;
    u8 pad21a[0x2a0 - 0x21a];
    TI_F41eb487e q2A0;
    u8 pad2b0[0x2c0 - 0x2b0];
    u8 area2C0[0x31c - 0x2c0];
    float f31C;
    u8 pad320[0x34e - 0x320];
    short h34E;
    u8 pad350[0x22c3 - 0x350];
    u8 b22C3;
} ResidentState_F41eb487e;
#endif


extern ResidentState_F41eb487e LVL_5_FELTZIN_SYSTEM_F41eb487e_D_00189E20;

void LVL_5_FELTZIN_SYSTEM_FUN_002D1A40(void)
{
    u8 scratch[64];
    Vec4_F41eb487e A, B, C;
    float hi = 0.035f;
    float lo = 0.3f;

    *(TI_F41eb487e *)&A = 0;
    *(TI_F41eb487e *)&B = 0;
    *(TI_F41eb487e *)&C = 0;

    A.c = 1.0f;
    B.c = 0.8f;
    C.c = 0.8f;

    LVL_5_FELTZIN_SYSTEM_F41eb487e_FUN_00306B00(&B, &B, &LVL_5_FELTZIN_SYSTEM_F41eb487e_D_00189E20);

    *(TI_F41eb487e *)&A = *(TI_F41eb487e *)&LVL_5_FELTZIN_SYSTEM_F41eb487e_D_00189E20.q2A0;
    if (LVL_5_FELTZIN_SYSTEM_F41eb487e_D_00189E20.b22C3 == 2) {
        LVL_5_FELTZIN_SYSTEM_F41eb487e_FUN_003066A0(&A, &LVL_5_FELTZIN_SYSTEM_F41eb487e_D_00189E20.area2C0, -1.0f);
    }

    if (LVL_5_FELTZIN_SYSTEM_F41eb487e_D_00189E20.b22C3 == 1 && (LVL_5_FELTZIN_SYSTEM_F41eb487e_D_00189E20.h34E < 10 || LVL_5_FELTZIN_SYSTEM_F41eb487e_D_00189E20.f31C < 1.0f))
        *(TI_F41eb487e *)&A = *(TI_F41eb487e *)&LVL_5_FELTZIN_SYSTEM_F41eb487e_D_00189E20.q2A0;

    if (LVL_5_FELTZIN_SYSTEM_F41eb487e_D_00189E20.h34E != 0 && LVL_5_FELTZIN_SYSTEM_F41eb487e_D_00189E20.h218 != 0) {
        lo = 0.001f;
        hi = lo;
    }

    LVL_5_FELTZIN_SYSTEM_F41eb487e_FUN_002D1780(&A, scratch, 0, hi, lo, 0.0f);

    if (LVL_5_FELTZIN_SYSTEM_F41eb487e_D_00189E20.b22C3 == 1 && LVL_5_FELTZIN_SYSTEM_F41eb487e_D_00189E20.h34E != 0) {
        LVL_5_FELTZIN_SYSTEM_F41eb487e_FUN_00306B00(&C, &C, scratch);
        LVL_5_FELTZIN_SYSTEM_F41eb487e_FUN_00306660(&LVL_5_FELTZIN_SYSTEM_F41eb487e_D_00189E20.area080, &LVL_5_FELTZIN_SYSTEM_F41eb487e_D_00189E20.area080, &C);
        LVL_5_FELTZIN_SYSTEM_F41eb487e_FUN_00306630(&LVL_5_FELTZIN_SYSTEM_F41eb487e_D_00189E20.area080, &LVL_5_FELTZIN_SYSTEM_F41eb487e_D_00189E20.area080, &B);
    }
}
extern void LVL_5_FELTZIN_SYSTEM_F1edea3ae_FUN_002F00E0(char *p);
extern void LVL_5_FELTZIN_SYSTEM_F1edea3ae_FUN_002F00E0(char *p);
extern void LVL_5_FELTZIN_SYSTEM_F1edea3ae_FUN_003065E8(char *p);
extern void LVL_5_FELTZIN_SYSTEM_F1edea3ae_FUN_00440048(char *p);

void LVL_5_FELTZIN_SYSTEM_FUN_00440180(char *self)
{
    char *q = (char *)*(int **)(self + 112) + 176;
    float *f;

    *(int *)(q + 64) = 0;
    f = (float *)*(int **)(self + 112);
    f[40] = 3.0000001192092895507812e-01f;
    f[41] = 3.0000001192092895507812e-01f;
    f[39] = 0.0f;
    f[42] = 0.0f;
    *(int *)(q + 68) = 0;
    f[43] = 0.0f;
    f[18] = 9.9000000953674316406250e-01f;
    f[15] = 3.9999999105930328369141e-02f;
    f[16] = 3.9999999105930328369141e-02f;
    f[17] = 3.9999999105930328369141e-02f;
    f[10] = 7.0000000298023223876953e-02f;
    f[11] = 1.0000000000000000000000e+00f;
    f[19] = 3.9999999105930328369141e-02f;
    f[12] = 7.0000000298023223876953e-02f;
    f[13] = 1.0000000000000000000000e+00f;
    f[14] = 7.0000000298023223876953e-02f;

    LVL_5_FELTZIN_SYSTEM_F1edea3ae_FUN_002F00E0((char *)f + 80);
    LVL_5_FELTZIN_SYSTEM_F1edea3ae_FUN_002F00E0((char *)f);
    LVL_5_FELTZIN_SYSTEM_F1edea3ae_FUN_003065E8((char *)f + 144);
    LVL_5_FELTZIN_SYSTEM_F1edea3ae_FUN_00440048(self);

    *(short *)(self + 126) = 0;
}
extern int LVL_5_FELTZIN_SYSTEM_Fb4cfb7e0_FUN_00332AB8(int x);

void LVL_5_FELTZIN_SYSTEM_FUN_00406270(char *self)
{
    float *p = *(float **)(self + 104);
    float *q = p;
    int *w;
    int c;
    int i;
    int j;

    for (i = 3; i >= 0; i--)
    {
        *q = (float)LVL_5_FELTZIN_SYSTEM_Fb4cfb7e0_FUN_00332AB8(255);
        q++;
    }

    p[4] = -1.0000000000000000000000e+00f;
    p[5] = -2.2500000000000000000000e+00f;
    p[6] = 1.2500000000000000000000e+00f;
    p[7] = 2.5000000000000000000000e+00f;

    j = 3;
    w = (int *)(p + 11);
    c = 255;
    for (; j >= 0; j--)
    {
        *w = c;
        w--;
        c -= 64;
    }

    p[12] = 2.5000000000000000000000e+00f;
    p[13] = 3.0000000000000000000000e+00f;
    p[15] = 2.5000000000000000000000e+00f;
    p[14] = 3.0000000000000000000000e+00f;
}
extern int LVL_5_FELTZIN_SYSTEM_Ff4dd22f3_FUN_003062D0(char *p);
extern void LVL_5_FELTZIN_SYSTEM_Ff4dd22f3_FUN_003423C8(char *p);
extern void LVL_5_FELTZIN_SYSTEM_Ff4dd22f3_FUN_00306630(char *p, char *q, float *v);

void LVL_5_FELTZIN_SYSTEM_FUN_00351F80(char *self)
{
    char *p = self + 32;
    float v[4];
    int a1;

    if (LVL_5_FELTZIN_SYSTEM_Ff4dd22f3_FUN_003062D0(self + 10) != 0)
    {
        LVL_5_FELTZIN_SYSTEM_Ff4dd22f3_FUN_003423C8(self);
        return;
    }

    a1 = *(int *)(self + 4);
    *(int *)(self + 4) = (a1 & 0xffffff) | (((a1 >> 24) + (int)*(unsigned char *)(p + 20)) << 24);
    v[0] = *(float *)(self + 32);
    v[1] = *(float *)(p + 4);
    v[2] = *(float *)(p + 8);
    v[3] = 0.0f;
    LVL_5_FELTZIN_SYSTEM_Ff4dd22f3_FUN_00306630(self + 16, self + 16, v);
    *(unsigned char *)(self + 8) += *(unsigned char *)(p + 21);
    *(float *)(self + 12) += *(float *)(p + 16);
    *(float *)(p + 8) -= *(float *)(p + 12);
}
extern void LVL_5_FELTZIN_SYSTEM_Fbbb7bee1_FUN_00306390(int value);

void LVL_5_FELTZIN_SYSTEM_FUN_00390208(int mask)
{
    while (*(volatile int *)0x10008000 & 0x100)
        LVL_5_FELTZIN_SYSTEM_Fbbb7bee1_FUN_00306390(16);
    *(volatile int *)0x10008020 = 0;
    *(volatile int *)0x10008030 = mask & 0x0FFFFFFF;
    *(volatile int *)0x10008000 = 325;
    while (*(volatile int *)0x10008000 & 0x100)
        LVL_5_FELTZIN_SYSTEM_Fbbb7bee1_FUN_00306390(16);
}
extern void LVL_5_FELTZIN_SYSTEM_F624a0727_FUN_00447A98(char *target);
#ifndef RAC2_T_ENTRY_F624A0727
#define RAC2_T_ENTRY_F624A0727
typedef struct { char pad[8]; short n; void (*fn)(char *); } ENTRY_F624a0727;
#endif


void LVL_5_FELTZIN_SYSTEM_FUN_0044BF70(char *object)
{
    char *r = object + 12;
    char *q = object + 60;
    char *p = object + 392;
    int i;

    for (i = 4; i >= 0; i--) {
        if (*(short *)p != 0) {
            ENTRY_F624a0727 *t = *(ENTRY_F624a0727 **)q;
            t->fn(r + t->n);
        }
        r += 76;
        q += 76;
        p += 2;
    }
    if (*(int *)(object + 656) != 0) {
        LVL_5_FELTZIN_SYSTEM_F624a0727_FUN_00447A98(object + 408);
        if (*(int *)(object + 660) != 0) {
            if (*(int *)(object + 668) != 0)
                LVL_5_FELTZIN_SYSTEM_F624a0727_FUN_00447A98(object + 552);
            if (*(int *)(object + 664) != 0)
                LVL_5_FELTZIN_SYSTEM_F624a0727_FUN_00447A98(object + 480);
        }
    }
}
extern int LVL_5_FELTZIN_SYSTEM_F44faa168_D_001A904C __attribute__((sda));
extern void LVL_5_FELTZIN_SYSTEM_F44faa168_FUN_0045DE50(int value, int argument);

void LVL_5_FELTZIN_SYSTEM_FUN_00324AE0(int argument)
{
    int value = LVL_5_FELTZIN_SYSTEM_F44faa168_D_001A904C;

    if (value != 0)
        LVL_5_FELTZIN_SYSTEM_F44faa168_FUN_0045DE50(value + 0x376C8, argument);
}
extern int LVL_5_FELTZIN_SYSTEM_F44faa168_D_001A904C __attribute__((sda));
extern void LVL_5_FELTZIN_SYSTEM_F44faa168_FUN_0045DEC0(int value, int argument);

void LVL_5_FELTZIN_SYSTEM_FUN_00324B58(int argument)
{
    int value = LVL_5_FELTZIN_SYSTEM_F44faa168_D_001A904C;

    if (value != 0)
        LVL_5_FELTZIN_SYSTEM_F44faa168_FUN_0045DEC0(value + 0x376C8, argument);
}
extern int LVL_5_FELTZIN_SYSTEM_F44faa168_D_001A904C __attribute__((sda));
extern void LVL_5_FELTZIN_SYSTEM_F44faa168_FUN_0045DEC8(int value, int argument);

void LVL_5_FELTZIN_SYSTEM_FUN_00324B90(int argument)
{
    int value = LVL_5_FELTZIN_SYSTEM_F44faa168_D_001A904C;

    if (value != 0)
        LVL_5_FELTZIN_SYSTEM_F44faa168_FUN_0045DEC8(value + 0x376C8, argument);
}
extern int LVL_5_FELTZIN_SYSTEM_F44faa168_D_001A904C __attribute__((sda));
extern void LVL_5_FELTZIN_SYSTEM_F44faa168_FUN_0045DED0(int value, int argument);

void LVL_5_FELTZIN_SYSTEM_FUN_003260A8(int argument)
{
    int value = LVL_5_FELTZIN_SYSTEM_F44faa168_D_001A904C;

    if (value != 0)
        LVL_5_FELTZIN_SYSTEM_F44faa168_FUN_0045DED0(value + 0x376C8, argument);
}
extern void LVL_5_FELTZIN_SYSTEM_Fd06ec510_FUN_003A40F8(char *object);
extern void LVL_5_FELTZIN_SYSTEM_Fd06ec510_FUN_003A3CE0(char *object);
extern float LVL_5_FELTZIN_SYSTEM_Fd06ec510_FUN_00307620(float value, float step);
extern void LVL_5_FELTZIN_SYSTEM_Fd06ec510_FUN_003A3BE0(char *object);
extern void LVL_5_FELTZIN_SYSTEM_Fd06ec510_FUN_00394B90(char *target, char *source);
extern void LVL_5_FELTZIN_SYSTEM_Fd06ec510_FUN_00394C48(char *target, char *source);
extern void LVL_5_FELTZIN_SYSTEM_Fd06ec510_FUN_003A55B0(char *object);

void LVL_5_FELTZIN_SYSTEM_FUN_003A39F8(char *object)
{
    char *s0 = object;
    unsigned char mode = *(unsigned char *)(s0 + 32);
    char *s1 = *(char **)(s0 + 104);
    float result;

    switch (mode) {
    case 0:
        if (*(int *)(s1 + 20) != 0) {
            LVL_5_FELTZIN_SYSTEM_Fd06ec510_FUN_003A40F8(s0);
        } else {
            LVL_5_FELTZIN_SYSTEM_Fd06ec510_FUN_003A3CE0(s0);
        }
        result = LVL_5_FELTZIN_SYSTEM_Fd06ec510_FUN_00307620(*(float *)(s0 + 240), 3.4906592220067977905273e-02f);
        *(float *)(s0 + 240) = result;
        result = LVL_5_FELTZIN_SYSTEM_Fd06ec510_FUN_00307620(*(float *)(s0 + 244), 1.3089971244335174560547e-01f);
        *(float *)(s0 + 244) = result;
        LVL_5_FELTZIN_SYSTEM_Fd06ec510_FUN_003A3BE0(s0);
        break;
    case 1:
        LVL_5_FELTZIN_SYSTEM_Fd06ec510_FUN_00394B90((char *)(s0 + 16), (char *)(s0 + 16));
        LVL_5_FELTZIN_SYSTEM_Fd06ec510_FUN_00394C48(s1, s1);
        LVL_5_FELTZIN_SYSTEM_Fd06ec510_FUN_003A55B0(s0);
        break;
    }
}
extern float LVL_5_FELTZIN_SYSTEM_F500f9762_FUN_00307768(int index);
extern int LVL_5_FELTZIN_SYSTEM_F500f9762_FUN_00307778(float value);
extern void LVL_5_FELTZIN_SYSTEM_F500f9762_FUN_0032A4C8(int first, char *a, char *b, char *c);

void LVL_5_FELTZIN_SYSTEM_FUN_00336BB8(int first, char *object)
{
    char *s0 = object;
    short s1 = *(short *)(s0 + 0);
    unsigned short total;
    float limit;
    int result;

    if (s1 != 0 && *(short *)(s0 + 2) == 0)
        return;
    total = *(unsigned short *)(s0 + 12);
    *(short *)(s0 + 2) = 0;
    *(short *)(s0 + 0) = total;
    if (s1 != 0) {
        limit = LVL_5_FELTZIN_SYSTEM_F500f9762_FUN_00307768(*(short *)(s0 + 14));
        result = LVL_5_FELTZIN_SYSTEM_F500f9762_FUN_00307778((float)*(short *)(s0 + 12) * ((float)s1 / limit));
        *(short *)(s0 + 0) = (short)result;
        if ((short)result <= 0)
            *(short *)(s0 + 0) = 1;
    } else {
        int a, b, c;
        LVL_5_FELTZIN_SYSTEM_F500f9762_FUN_0032A4C8(first, (char *)&a, (char *)&b, (char *)&c);
        *(char *)(s0 + 4) = (unsigned char)a;
        *(char *)(s0 + 5) = (unsigned char)b;
        *(char *)(s0 + 6) = (unsigned char)c;
    }
}
extern void LVL_5_FELTZIN_SYSTEM_F8ad956d6_FUN_00447340(char *target);
extern void LVL_5_FELTZIN_SYSTEM_F8ad956d6_FUN_003906F8(int marker, int code);
extern void LVL_5_FELTZIN_SYSTEM_F8ad956d6_FUN_0031ED98(int first, int second);
extern void LVL_5_FELTZIN_SYSTEM_F8ad956d6_FUN_00366920(char *target);
extern void LVL_5_FELTZIN_SYSTEM_F8ad956d6_FUN_00447A98(char *target);

void LVL_5_FELTZIN_SYSTEM_FUN_0044B408(char *object)
{
    char *s0 = object;

    if (*(int *)(s0 + 1024) == 0)
        return;
    LVL_5_FELTZIN_SYSTEM_F8ad956d6_FUN_00447340(s0 + 8);
    LVL_5_FELTZIN_SYSTEM_F8ad956d6_FUN_00447340(s0 + 84);
    LVL_5_FELTZIN_SYSTEM_F8ad956d6_FUN_003906F8(66, 68);
    LVL_5_FELTZIN_SYSTEM_F8ad956d6_FUN_003906F8(71, 11);
    LVL_5_FELTZIN_SYSTEM_F8ad956d6_FUN_0031ED98(0, 1);
    LVL_5_FELTZIN_SYSTEM_F8ad956d6_FUN_00366920(0);
    LVL_5_FELTZIN_SYSTEM_F8ad956d6_FUN_00447340(s0 + 160);
    LVL_5_FELTZIN_SYSTEM_F8ad956d6_FUN_00447340(s0 + 236);
    LVL_5_FELTZIN_SYSTEM_F8ad956d6_FUN_00447A98(s0 + 312);
    LVL_5_FELTZIN_SYSTEM_F8ad956d6_FUN_00447A98(s0 + 384);
    LVL_5_FELTZIN_SYSTEM_F8ad956d6_FUN_00447A98(s0 + 456);
    LVL_5_FELTZIN_SYSTEM_F8ad956d6_FUN_00447A98(s0 + 528);
    LVL_5_FELTZIN_SYSTEM_F8ad956d6_FUN_00447A98(s0 + 600);
    LVL_5_FELTZIN_SYSTEM_F8ad956d6_FUN_00447A98(s0 + 672);
    LVL_5_FELTZIN_SYSTEM_F8ad956d6_FUN_00447A98(s0 + 744);
    LVL_5_FELTZIN_SYSTEM_F8ad956d6_FUN_00447A98(s0 + 816);
    LVL_5_FELTZIN_SYSTEM_F8ad956d6_FUN_00447A98(s0 + 888);
}
extern void LVL_5_FELTZIN_SYSTEM_Fccb147a4_FUN_003423C8(char *a, char *b);
extern void LVL_5_FELTZIN_SYSTEM_Fccb147a4_FUN_00394B90(char *a, char *b);

void LVL_5_FELTZIN_SYSTEM_FUN_0034CFD8(char *obj)
{
    char *sub = obj + 32;
    int w;
    int n;

    switch (*(unsigned char *)(sub + 2)) {
    case 2:
        *(float *)(obj + 16) = *(float *)(*(char **)(sub + 4) + 16) + *(float *)(sub + 16);
        *(float *)(obj + 20) = *(float *)(*(char **)(sub + 4) + 20) + *(float *)(sub + 20);
        *(float *)(obj + 24) = *(float *)(*(char **)(sub + 4) + 24) + *(float *)(sub + 24);
        break;
    case 1:
        goto tail;
    }
    w = *(int *)(obj + 4);
    n = (w >> 24);
    n = n - *(short *)(obj + 32);
    if (n <= 0) {
        LVL_5_FELTZIN_SYSTEM_Fccb147a4_FUN_003423C8(obj, sub);
        return;
    }
    *(int *)(obj + 4) = (w & 0xffffff) | (n << 24);
tail:
    if (*(unsigned char *)(sub + 3) != 0) {
        obj += 16;
        LVL_5_FELTZIN_SYSTEM_Fccb147a4_FUN_00394B90(obj, obj);
    }
}
extern void LVL_5_FELTZIN_SYSTEM_Fa5914967_FUN_003068F8(float *a, float *b, float c);

void LVL_5_FELTZIN_SYSTEM_FUN_00336408(float (*m)[4])
{
    int k;
    int i;
    float v[4];

    for (k = 0; k < 3; k++) {
        v[3] = 0.0f;
        for (i = 0; i < 3; i++)
            v[i] = m[i][k];
        LVL_5_FELTZIN_SYSTEM_Fa5914967_FUN_003068F8(v, v, 1.0f);
        for (i = 0; i < 3; i++)
            m[i][k] = v[i];
    }
}
extern char *LVL_5_FELTZIN_SYSTEM_F476e86a4_FUN_00446E30(char *p);
extern char *LVL_5_FELTZIN_SYSTEM_F476e86a4_FUN_00446E30(char *p);
extern void LVL_5_FELTZIN_SYSTEM_F476e86a4_FUN_004474E8(char *p, int a, int b);
extern void LVL_5_FELTZIN_SYSTEM_F476e86a4_FUN_00447528(char *p, int a, int b);
extern void LVL_5_FELTZIN_SYSTEM_F476e86a4_FUN_00447D00(char *p, int a);

void LVL_5_FELTZIN_SYSTEM_FUN_0045F258(char *a0, int a1, int a2, int a3, int t0)
{
    char *base = a0 + a1 * 72;
    float *p;
    char *vt;

    p = (float *)LVL_5_FELTZIN_SYSTEM_F476e86a4_FUN_00446E30(base);
    p[0] = (float)a2;
    p = (float *)LVL_5_FELTZIN_SYSTEM_F476e86a4_FUN_00446E30(base);
    p[1] = (float)a3;
    LVL_5_FELTZIN_SYSTEM_F476e86a4_FUN_004474E8(base, t0, t0);
    LVL_5_FELTZIN_SYSTEM_F476e86a4_FUN_00447528(base, t0, t0);
    LVL_5_FELTZIN_SYSTEM_F476e86a4_FUN_00447D00(base, t0 << 24);
    vt = *(char **)(base + 48);
    (*(void (**)(char *))(vt + 12))(base + *(short *)(vt + 8));
}
extern int LVL_5_FELTZIN_SYSTEM_Fcdb4d905_FUN_002FCA80(int a, int b, int c);

int LVL_5_FELTZIN_SYSTEM_FUN_002FCB58(float x, int a, int b, int c, int d, int e, int g)
{
    int r, p, q, s;
    if (x < 0.5f) {
        r = LVL_5_FELTZIN_SYSTEM_Fcdb4d905_FUN_002FCA80(a, b, c);
        if (r) return r;
        p = d;
        q = e;
        s = g;
    } else {
        r = LVL_5_FELTZIN_SYSTEM_Fcdb4d905_FUN_002FCA80(d, e, g);
        if (r) return r;
        p = a;
        q = b;
        s = c;
    }
    return LVL_5_FELTZIN_SYSTEM_Fcdb4d905_FUN_002FCA80(p, q, s);
}
extern char *LVL_5_FELTZIN_SYSTEM_F97fc4e13_FUN_0036B2A8(int a0, int a1);
extern void LVL_5_FELTZIN_SYSTEM_F97fc4e13_FUN_00306408(char *target, char *base, int len);

void LVL_5_FELTZIN_SYSTEM_FUN_0036B2F0(char *a0)
{
    int i = 0;

    if (i < *(int *)a0) {
        int one = 1;
        char *d = a0 + 8;
        char *e = a0 + 4;

        do {
            char *obj = LVL_5_FELTZIN_SYSTEM_F97fc4e13_FUN_0036B2A8(*(short *)(e + 14), *(short *)(e + 12));
            if (obj != 0) {
                char *t;
                if (*(short *)(e + 10) == one)
                    t = (char *)(*(int *)e + (int)obj);
                else
                    t = (char *)(*(int *)e + *(int *)(obj + 104));
                LVL_5_FELTZIN_SYSTEM_F97fc4e13_FUN_00306408(t, d, *(unsigned short *)(e + 8));
            }
            i++;
            d += 16;
            e += 16;
        } while (i < *(int *)a0);
    }
}
extern char *LVL_5_FELTZIN_SYSTEM_F1fa78648_FUN_0033E430(int a0, int a1);
extern char *LVL_5_FELTZIN_SYSTEM_F1fa78648_FUN_0033E460(int a0, int a1);
extern int LVL_5_FELTZIN_SYSTEM_F1fa78648_FUN_003062D0(char *a0);
extern float LVL_5_FELTZIN_SYSTEM_F1fa78648_FUN_00307620(float a0, float a1);

int LVL_5_FELTZIN_SYSTEM_FUN_003FDC20(int *a0)
{
    int i;
    int count = 0;
    char *base;
    char *rec;
    char *obj;

    rec = *(char **)((char *)a0 + 104);
    base = LVL_5_FELTZIN_SYSTEM_F1fa78648_FUN_0033E430(3076, *(short *)(rec + 26));
    base = base + *(int *)(LVL_5_FELTZIN_SYSTEM_F1fa78648_FUN_0033E460(3076, *(short *)(rec + 26)) + 4);
    obj = base + 16;
    rec = base;

    for (i = 119; i >= 0; i--) {
        if (*(short *)(rec + 18) != 0) {
            if (LVL_5_FELTZIN_SYSTEM_F1fa78648_FUN_003062D0(obj) != 0) {
                *(short *)(rec + 18) = 0;
            } else {
                count++;
                *(float *)(rec + 24) = LVL_5_FELTZIN_SYSTEM_F1fa78648_FUN_00307620(*(float *)(rec + 24), *(float *)(rec + 28));
            }
        }
        obj += 64;
        rec += 64;
    }
    return count;
}
extern void LVL_5_FELTZIN_SYSTEM_F6402b823_FUN_00447340(char *a);
extern void LVL_5_FELTZIN_SYSTEM_F6402b823_FUN_00447340(char *a);
extern void LVL_5_FELTZIN_SYSTEM_F6402b823_FUN_00447340(char *a);
extern void LVL_5_FELTZIN_SYSTEM_F6402b823_FUN_00447340(char *a);
extern void LVL_5_FELTZIN_SYSTEM_F6402b823_FUN_00447A98(char *a);
extern void LVL_5_FELTZIN_SYSTEM_F6402b823_FUN_00447A98(char *a);
extern void LVL_5_FELTZIN_SYSTEM_F6402b823_FUN_00447A98(char *a);
extern void LVL_5_FELTZIN_SYSTEM_F6402b823_FUN_00446E88(char *a, int b);
extern void LVL_5_FELTZIN_SYSTEM_F6402b823_FUN_00456290(char *a);
extern void LVL_5_FELTZIN_SYSTEM_F6402b823_FUN_004560B0(char *a);
extern void LVL_5_FELTZIN_SYSTEM_F6402b823_FUN_00455FC0(char *a);
extern void LVL_5_FELTZIN_SYSTEM_F6402b823_FUN_004561A0(char *a);
extern void LVL_5_FELTZIN_SYSTEM_F6402b823_FUN_00455960(char *a);
extern void LVL_5_FELTZIN_SYSTEM_F6402b823_FUN_00447340(char *a);

void LVL_5_FELTZIN_SYSTEM_FUN_00456380(char *obj)
{
    if (*(int *)(obj + 1080) != 0) {
        char *s0 = obj + 456;

        LVL_5_FELTZIN_SYSTEM_F6402b823_FUN_00447340(obj);
        LVL_5_FELTZIN_SYSTEM_F6402b823_FUN_00447340(obj + 76);
        LVL_5_FELTZIN_SYSTEM_F6402b823_FUN_00447340(obj + 152);
        LVL_5_FELTZIN_SYSTEM_F6402b823_FUN_00447340(obj + 228);
        LVL_5_FELTZIN_SYSTEM_F6402b823_FUN_00447A98(s0);
        LVL_5_FELTZIN_SYSTEM_F6402b823_FUN_00447A98(obj + 664);
        LVL_5_FELTZIN_SYSTEM_F6402b823_FUN_00447A98(s0);
        LVL_5_FELTZIN_SYSTEM_F6402b823_FUN_00446E88(obj + 528, 0);
        LVL_5_FELTZIN_SYSTEM_F6402b823_FUN_00456290(obj);
        LVL_5_FELTZIN_SYSTEM_F6402b823_FUN_004560B0(obj);
        LVL_5_FELTZIN_SYSTEM_F6402b823_FUN_00455FC0(obj);
        LVL_5_FELTZIN_SYSTEM_F6402b823_FUN_004561A0(obj);
        LVL_5_FELTZIN_SYSTEM_F6402b823_FUN_00455960(obj);
        LVL_5_FELTZIN_SYSTEM_F6402b823_FUN_00447340(obj + 380);
    }
}
extern void LVL_5_FELTZIN_SYSTEM_F36efd143_FUN_00446FE8(char *a);
extern void *LVL_5_FELTZIN_SYSTEM_F36efd143_FUN_00447E60(char *a);
extern void *LVL_5_FELTZIN_SYSTEM_F36efd143_FUN_00447DC8(int size, void *b);
extern void *LVL_5_FELTZIN_SYSTEM_F36efd143_FUN_00447E60(char *a);
extern void *LVL_5_FELTZIN_SYSTEM_F36efd143_FUN_00447DC8(int size, void *b);
void LVL_5_FELTZIN_SYSTEM_FUN_00447200(char *obj)
{
    int *p;
    int x;
    LVL_5_FELTZIN_SYSTEM_F36efd143_FUN_00446FE8(obj);
    if (*(int *)(obj + 44) != 0) {
        p = (int *)LVL_5_FELTZIN_SYSTEM_F36efd143_FUN_00447DC8(16, LVL_5_FELTZIN_SYSTEM_F36efd143_FUN_00447E60(*(int *)(obj + 44)));
        *(int *)(obj + 52) = (int)p;
        x = *(int *)(obj + 44);
        p[1] = 0; p[2] = 0; p[3] = 0; p[0] = 0;
        p = (int *)LVL_5_FELTZIN_SYSTEM_F36efd143_FUN_00447DC8(16, LVL_5_FELTZIN_SYSTEM_F36efd143_FUN_00447E60(x));
        *(int *)(obj + 56) = (int)p;
        {
            float *f = (float *)*(int *)(obj + 4);
            p[1] = 0;
            p[2] = 0;
            p[3] = 0;
            p[0] = 0;
            f[0] = 1.0f;
            *(float *)(*(int *)(obj + 4) + 4) = 1.0f;
            *(float *)(*(int *)(obj + 4) + 8) = 1.0f;
        }
    }
    *(int *)(obj + 68) = 0;
    *(int *)(obj + 72) = 0;
}
extern int LVL_5_FELTZIN_SYSTEM_F29eece9b_FUN_003716D8(char *p, int a1, char *a2, int a3, int a4);
extern char LVL_5_FELTZIN_SYSTEM_F29eece9b_D_00188660[];

int LVL_5_FELTZIN_SYSTEM_FUN_00371900(int index, int a1, char *a2)
{
    int v0;
    int v1;
    int r;
    char *p;

    if (a2 == 0)
        return -1;
    v0 = *(int *)(a2 + 36);
    if (v0 == 0)
        return -1;
    v1 = *(int *)(v0 + 40);
    if (v1 == 0)
        return -1;
    v0 = *(unsigned char *)(v0 + 13);
    if (index >= v0)
        return -1;
    r = LVL_5_FELTZIN_SYSTEM_F29eece9b_FUN_003716D8((char *)(v1 + index * 32), a1, a2, 0, 1024);
    if (r >= 0) {
        p = &LVL_5_FELTZIN_SYSTEM_F29eece9b_D_00188660[r * 112];
        *(int *)(p + 136) = (int)a2;
        *(short *)(p + 126) = (short)index;
    }
    return r;
}
extern void LVL_5_FELTZIN_SYSTEM_F081de6c9_FUN_00446FE8(char *s, int a1, char *a2);
extern int LVL_5_FELTZIN_SYSTEM_F081de6c9_FUN_00447E60(int x);
extern int *LVL_5_FELTZIN_SYSTEM_F081de6c9_FUN_00447DC8(int n, int x);

void LVL_5_FELTZIN_SYSTEM_FUN_00447730(char *s1, int a1, char *a2)
{
    LVL_5_FELTZIN_SYSTEM_F081de6c9_FUN_00446FE8(s1, a1, a2);
    if (a2 != 0) {
        int *v = LVL_5_FELTZIN_SYSTEM_F081de6c9_FUN_00447DC8(16, LVL_5_FELTZIN_SYSTEM_F081de6c9_FUN_00447E60(*(int *)(s1 + 44)));

        *(int **)(s1 + 52) = v;
        v[1] = 0;
        v[2] = 0;
        v[3] = 0;
        v[0] = 0;
    }
    ((int *)*(int **)(s1 + 52))[0] = 0;
    ((int *)*(int **)(s1 + 52))[1] = 0;
    *(float *)(*(char **)s1 + 0) = 100.0f;
    *(float *)(*(char **)s1 + 4) = 100.0f;
    *(float *)(*((char **)s1 + 1) + 0) = 64.0f;
    *(float *)(*((char **)s1 + 1) + 4) = 64.0f;
    *(int *)(s1 + 56) = 0;
}
extern void LVL_5_FELTZIN_SYSTEM_F15a8b7f0_FUN_003066A0(char *first, char *second, float blend);
extern void LVL_5_FELTZIN_SYSTEM_F15a8b7f0_FUN_00306630(char *first, char *second, char *third);
extern void LVL_5_FELTZIN_SYSTEM_F15a8b7f0_FUN_003423C8(char *object);

void LVL_5_FELTZIN_SYSTEM_FUN_0034C0F0(char *object)
{
    int count;
    int low;
    int high;

    LVL_5_FELTZIN_SYSTEM_F15a8b7f0_FUN_003066A0(object + 32, object + 32, 0.975f);
    LVL_5_FELTZIN_SYSTEM_F15a8b7f0_FUN_00306630(object + 16, object + 16, object + 32);
    *(float *)(object + 12) += 6300.0f;
    count = *(unsigned char *)(object + 4) - 4;
    if (count <= 0)
        LVL_5_FELTZIN_SYSTEM_F15a8b7f0_FUN_003423C8(object);
    else {
        low = (count << 8) | 0x60000000;
        high = (count << 16) | low;
        *(int *)(object + 4) = high | count;
    }
}
extern void LVL_5_FELTZIN_SYSTEM_F8b17817c_FUN_004471C8(char *block);
extern void LVL_5_FELTZIN_SYSTEM_F8b17817c_FUN_00447988(char *block);
extern void LVL_5_FELTZIN_SYSTEM_F8b17817c_FUN_004476F0(char *block);

char *LVL_5_FELTZIN_SYSTEM_FUN_0044C0E0(char *object)
{
    int index;
    char *block;

    LVL_5_FELTZIN_SYSTEM_F8b17817c_FUN_004471C8(object);
    LVL_5_FELTZIN_SYSTEM_F8b17817c_FUN_004471C8(object + 76);
    LVL_5_FELTZIN_SYSTEM_F8b17817c_FUN_004471C8(object + 152);
    block = object + 228;
    for (index = 2; index != -1; index--) {
        LVL_5_FELTZIN_SYSTEM_F8b17817c_FUN_004471C8(block);
        block += 76;
    }
    LVL_5_FELTZIN_SYSTEM_F8b17817c_FUN_00447988(object + 472);
    LVL_5_FELTZIN_SYSTEM_F8b17817c_FUN_00447988(object + 544);
    LVL_5_FELTZIN_SYSTEM_F8b17817c_FUN_00447988(object + 616);
    LVL_5_FELTZIN_SYSTEM_F8b17817c_FUN_004476F0(object + 688);
    LVL_5_FELTZIN_SYSTEM_F8b17817c_FUN_004476F0(object + 748);
    return object;
}
extern int LVL_5_FELTZIN_SYSTEM_Fbfc8418e_FUN_003062D0(char *handle);
extern void LVL_5_FELTZIN_SYSTEM_Fbfc8418e_FUN_00328870(char *object);

void LVL_5_FELTZIN_SYSTEM_FUN_004143F8(char *object)
{
    char *handle = *(char **)(object + 104);

    if (LVL_5_FELTZIN_SYSTEM_Fbfc8418e_FUN_003062D0(handle) == 0)
        LVL_5_FELTZIN_SYSTEM_Fbfc8418e_FUN_003062D0(handle + 4);
    else
        LVL_5_FELTZIN_SYSTEM_Fbfc8418e_FUN_00328870(object);
}
extern int LVL_5_FELTZIN_SYSTEM_Fbfc8418e_FUN_003062D0(char *handle);
extern void LVL_5_FELTZIN_SYSTEM_Fbfc8418e_FUN_00328870(char *object);

void LVL_5_FELTZIN_SYSTEM_FUN_004314D8(char *object)
{
    char *handle = *(char **)(object + 104);

    if (LVL_5_FELTZIN_SYSTEM_Fbfc8418e_FUN_003062D0(handle) == 0)
        LVL_5_FELTZIN_SYSTEM_Fbfc8418e_FUN_003062D0(handle + 4);
    else
        LVL_5_FELTZIN_SYSTEM_Fbfc8418e_FUN_00328870(object);
}
extern void LVL_5_FELTZIN_SYSTEM_Ff26f272a_FUN_002F2858(char *first, char *second, char *third);
extern float LVL_5_FELTZIN_SYSTEM_Ff26f272a_FUN_00307620(float value, float reference);
extern void LVL_5_FELTZIN_SYSTEM_Ff26f272a_FUN_00306E98(char *out, char *source);
extern void LVL_5_FELTZIN_SYSTEM_Ff26f272a_FUN_00307100(char *object, char *out);

void LVL_5_FELTZIN_SYSTEM_FUN_00440048(char *object)
{
    float local[16];
    char *child = *(char **)(object + 112);

    child += 176;
    LVL_5_FELTZIN_SYSTEM_Ff26f272a_FUN_002F2858(object + 48, object + 80, child);
    *(float *)(object + 80) = LVL_5_FELTZIN_SYSTEM_Ff26f272a_FUN_00307620(*(float *)(object + 80), *(float *)(child + 24));
    *(int *)(object + 64) = 0;
    *(float *)(object + 68) = LVL_5_FELTZIN_SYSTEM_Ff26f272a_FUN_00307620(*(float *)(object + 84), *(float *)(object + 92));
    *(float *)(object + 72) = LVL_5_FELTZIN_SYSTEM_Ff26f272a_FUN_00307620(3.14159265f, *(float *)(object + 80));
    *(float *)(object + 72) = LVL_5_FELTZIN_SYSTEM_Ff26f272a_FUN_00307620(*(float *)(object + 72), *(float *)(object + 96));
    *(int *)(object + 76) = 0;
    LVL_5_FELTZIN_SYSTEM_Ff26f272a_FUN_00306E98((char *)local, object + 64);
    LVL_5_FELTZIN_SYSTEM_Ff26f272a_FUN_00307100(object, (char *)local);
}
extern void LVL_5_FELTZIN_SYSTEM_F5a9e4f98_FUN_004471C8(char *p);
extern void LVL_5_FELTZIN_SYSTEM_F5a9e4f98_FUN_004471C8(char *p);
extern void LVL_5_FELTZIN_SYSTEM_F5a9e4f98_FUN_004471C8(char *p);
extern void LVL_5_FELTZIN_SYSTEM_F5a9e4f98_FUN_004471C8(char *p);
extern void LVL_5_FELTZIN_SYSTEM_F5a9e4f98_FUN_004471C8(char *p);
extern void LVL_5_FELTZIN_SYSTEM_F5a9e4f98_FUN_004471C8(char *p);
extern void LVL_5_FELTZIN_SYSTEM_F5a9e4f98_FUN_004473F0(char *p);
extern void LVL_5_FELTZIN_SYSTEM_F5a9e4f98_FUN_00447988(char *p);
extern void LVL_5_FELTZIN_SYSTEM_F5a9e4f98_FUN_00447988(char *p);
extern void LVL_5_FELTZIN_SYSTEM_F5a9e4f98_FUN_00447988(char *p);
extern void LVL_5_FELTZIN_SYSTEM_F5a9e4f98_FUN_00447988(char *p);
extern void LVL_5_FELTZIN_SYSTEM_F5a9e4f98_FUN_00447988(char *p);
extern void LVL_5_FELTZIN_SYSTEM_F5a9e4f98_FUN_004476F0(char *p);
extern void LVL_5_FELTZIN_SYSTEM_F5a9e4f98_FUN_004471C8(char *p);
extern void LVL_5_FELTZIN_SYSTEM_F5a9e4f98_FUN_004471C8(char *p);
extern void LVL_5_FELTZIN_SYSTEM_F5a9e4f98_FUN_004471C8(char *p);

void *LVL_5_FELTZIN_SYSTEM_FUN_00457698(char *p)
{
    LVL_5_FELTZIN_SYSTEM_F5a9e4f98_FUN_004471C8(p);
    LVL_5_FELTZIN_SYSTEM_F5a9e4f98_FUN_004471C8(p + 0x4c);
    LVL_5_FELTZIN_SYSTEM_F5a9e4f98_FUN_004471C8(p + 0x98);
    LVL_5_FELTZIN_SYSTEM_F5a9e4f98_FUN_004471C8(p + 0xe4);
    LVL_5_FELTZIN_SYSTEM_F5a9e4f98_FUN_004471C8(p + 0x130);
    LVL_5_FELTZIN_SYSTEM_F5a9e4f98_FUN_004471C8(p + 0x17c);
    LVL_5_FELTZIN_SYSTEM_F5a9e4f98_FUN_004473F0(p + 0x1c8);
    LVL_5_FELTZIN_SYSTEM_F5a9e4f98_FUN_00447988(p + 0x210);
    LVL_5_FELTZIN_SYSTEM_F5a9e4f98_FUN_00447988(p + 0x258);
    LVL_5_FELTZIN_SYSTEM_F5a9e4f98_FUN_00447988(p + 0x2a0);
    LVL_5_FELTZIN_SYSTEM_F5a9e4f98_FUN_00447988(p + 0x2e8);
    LVL_5_FELTZIN_SYSTEM_F5a9e4f98_FUN_00447988(p + 0x330);
    LVL_5_FELTZIN_SYSTEM_F5a9e4f98_FUN_004476F0(p + 0x378);
    LVL_5_FELTZIN_SYSTEM_F5a9e4f98_FUN_004471C8(p + 0x3b4);
    LVL_5_FELTZIN_SYSTEM_F5a9e4f98_FUN_004471C8(p + 0x400);
    LVL_5_FELTZIN_SYSTEM_F5a9e4f98_FUN_004471C8(p + 0x44c);

    return p;
}
extern void LVL_5_FELTZIN_SYSTEM_F72a1dff5_FUN_0045AAE0(char *p, int a);
extern void LVL_5_FELTZIN_SYSTEM_F72a1dff5_FUN_0045AAE0(char *p, int a);
extern void LVL_5_FELTZIN_SYSTEM_F72a1dff5_FUN_0045AAE0(char *p, int a);
extern void LVL_5_FELTZIN_SYSTEM_F72a1dff5_FUN_0045A658(char *p, int a);
extern void LVL_5_FELTZIN_SYSTEM_F72a1dff5_FUN_0045AAE0(char *p, int a);
extern void LVL_5_FELTZIN_SYSTEM_F72a1dff5_FUN_00447940(char *p, void *b, int c);
extern void LVL_5_FELTZIN_SYSTEM_F72a1dff5_FUN_00447940(char *p, void *b, int c);

void LVL_5_FELTZIN_SYSTEM_FUN_0045DB10(char *p, void *a1, int a2)
{
    *(int *)(p + 0x1564) = a2;
    if (*(int *)(p + 0x1568) != 0) {
        *(int *)(p + 0x1568) = 0;
        LVL_5_FELTZIN_SYSTEM_F72a1dff5_FUN_0045AAE0(p + 0xf1c, 0);
        LVL_5_FELTZIN_SYSTEM_F72a1dff5_FUN_0045AAE0(p + 0xfb0, 0);
        LVL_5_FELTZIN_SYSTEM_F72a1dff5_FUN_0045AAE0(p + 0x1044, 0);
        LVL_5_FELTZIN_SYSTEM_F72a1dff5_FUN_0045A658(p + 0x10d8, 1);
        LVL_5_FELTZIN_SYSTEM_F72a1dff5_FUN_0045AAE0(p + 0x1160, 0);
        LVL_5_FELTZIN_SYSTEM_F72a1dff5_FUN_00447940(p + 0x148, a1, 0);
    }
    if (*(int *)(p + 0x157c) != 0) {
        LVL_5_FELTZIN_SYSTEM_F72a1dff5_FUN_00447940(p + 0x148, a1, 0);
    }
}
extern void LVL_5_FELTZIN_SYSTEM_Fa03721e9_FUN_00306630(char *a, char *b, char *c);
extern void LVL_5_FELTZIN_SYSTEM_Fa03721e9_FUN_003423C8(char *p);

void LVL_5_FELTZIN_SYSTEM_FUN_0034D860(char *p)
{
    char *q = p + 32;

    LVL_5_FELTZIN_SYSTEM_Fa03721e9_FUN_00306630(p + 16, p + 16, q);
    *(float *)(p + 12) = *(float *)(p + 12) + *(float *)(q + 16);
    *(unsigned char *)(p + 8) = *(unsigned char *)(p + 8) + 1;
    if (--*(short *)(p + 10) == 0) {
        *(unsigned int *)(p + 4) = *(unsigned int *)(p + 4) + 0xff000000;
        *(short *)(p + 10) = 2;
    }
    if ((*(unsigned int *)(p + 4) & 0xff000000) == 0)
        LVL_5_FELTZIN_SYSTEM_Fa03721e9_FUN_003423C8(p);
}
extern char *LVL_5_FELTZIN_SYSTEM_F8622720f_D_001A904C __attribute__((sda));
extern char *LVL_5_FELTZIN_SYSTEM_F8622720f_D_001A904C __attribute__((sda));
extern char *LVL_5_FELTZIN_SYSTEM_F8622720f_D_001A904C __attribute__((sda));
extern char *LVL_5_FELTZIN_SYSTEM_F8622720f_D_001A904C __attribute__((sda));
extern char *LVL_5_FELTZIN_SYSTEM_F8622720f_D_001A904C __attribute__((sda));
extern void LVL_5_FELTZIN_SYSTEM_F8622720f_FUN_004473B0(char *dst, char *src, int value);

void LVL_5_FELTZIN_SYSTEM_FUN_004595A8(char *object, int *values)
{
    LVL_5_FELTZIN_SYSTEM_F8622720f_FUN_004473B0(object,       LVL_5_FELTZIN_SYSTEM_F8622720f_D_001A904C + 0x8710, values[0]);
    LVL_5_FELTZIN_SYSTEM_F8622720f_FUN_004473B0(object + 304, LVL_5_FELTZIN_SYSTEM_F8622720f_D_001A904C + 0x8710, values[2]);
    LVL_5_FELTZIN_SYSTEM_F8622720f_FUN_004473B0(object + 76,  LVL_5_FELTZIN_SYSTEM_F8622720f_D_001A904C + 0x8710, values[4]);
    LVL_5_FELTZIN_SYSTEM_F8622720f_FUN_004473B0(object + 152, LVL_5_FELTZIN_SYSTEM_F8622720f_D_001A904C + 0x8710, values[8]);
    LVL_5_FELTZIN_SYSTEM_F8622720f_FUN_004473B0(object + 228, LVL_5_FELTZIN_SYSTEM_F8622720f_D_001A904C + 0x8710, values[6]);
}
extern unsigned char LVL_5_FELTZIN_SYSTEM_F1f401dc9_D_00189E20[];
extern float LVL_5_FELTZIN_SYSTEM_F1f401dc9_FUN_00306790(char *object);
extern void LVL_5_FELTZIN_SYSTEM_F1f401dc9_FUN_00306E98(char *dst, char *src);
extern void LVL_5_FELTZIN_SYSTEM_F1f401dc9_FUN_00307120(char *dst, char *src);
extern void LVL_5_FELTZIN_SYSTEM_F1f401dc9_FUN_00306B00(char *dst, char *src, char *extra);

float LVL_5_FELTZIN_SYSTEM_FUN_002EC2D8(char *arg)
{
    char first[64];
    char second[64];
    char third[16];
    unsigned char *p = LVL_5_FELTZIN_SYSTEM_F1f401dc9_D_00189E20;
    int flag = p[8899];

    if (flag == 0)
        return LVL_5_FELTZIN_SYSTEM_F1f401dc9_FUN_00306790(arg);
    if (flag < 0)
        return 0.0f;
    if (flag >= 3)
        return 0.0f;
    LVL_5_FELTZIN_SYSTEM_F1f401dc9_FUN_00306E98(first, (char *)(*(int *)(p + 8848) + 240));
    LVL_5_FELTZIN_SYSTEM_F1f401dc9_FUN_00307120(second, first);
    LVL_5_FELTZIN_SYSTEM_F1f401dc9_FUN_00306B00(third, arg, second);
    return LVL_5_FELTZIN_SYSTEM_F1f401dc9_FUN_00306790(third);
}
extern void LVL_5_FELTZIN_SYSTEM_F280d7406_FUN_00306630(char *dst, char *left, char *right);
extern void LVL_5_FELTZIN_SYSTEM_F280d7406_FUN_00394B90(char *dst, char *src);
extern int LVL_5_FELTZIN_SYSTEM_F280d7406_FUN_00307778(float value);
extern void LVL_5_FELTZIN_SYSTEM_F280d7406_FUN_003423C8(char *object);

void LVL_5_FELTZIN_SYSTEM_FUN_00346860(char *a)
{
    char *p1 = a + 16;
    char *p2 = a + 32;
    char *p3 = a + 48;
    int v;

    LVL_5_FELTZIN_SYSTEM_F280d7406_FUN_00306630(p1, p1, p3);
    LVL_5_FELTZIN_SYSTEM_F280d7406_FUN_00306630(p2, p2, p3);
    LVL_5_FELTZIN_SYSTEM_F280d7406_FUN_00394B90(p1, p1);
    LVL_5_FELTZIN_SYSTEM_F280d7406_FUN_00394B90(p2, p2);
    v = *(int *)(a + 4) - (LVL_5_FELTZIN_SYSTEM_F280d7406_FUN_00307778(*(float *)(p3 + 12)) << 24);
    *(int *)(a + 4) = v;
    *(int *)(a + 12) = v;
    if (v < 0)
        LVL_5_FELTZIN_SYSTEM_F280d7406_FUN_003423C8(a);
}
extern void LVL_5_FELTZIN_SYSTEM_Fd1c2476b_FUN_00447340(char *p);
extern void LVL_5_FELTZIN_SYSTEM_Fd1c2476b_FUN_00447340(char *p);
extern void LVL_5_FELTZIN_SYSTEM_Fd1c2476b_FUN_00447340(char *p);
extern void LVL_5_FELTZIN_SYSTEM_Fd1c2476b_FUN_00447340(char *p);
extern void LVL_5_FELTZIN_SYSTEM_Fd1c2476b_FUN_00447A98(char *p);
extern void LVL_5_FELTZIN_SYSTEM_Fd1c2476b_FUN_004572D0(char *p);
extern void LVL_5_FELTZIN_SYSTEM_Fd1c2476b_FUN_004573F0(char *p);
extern void LVL_5_FELTZIN_SYSTEM_Fd1c2476b_FUN_004574F8(char *p);
extern void LVL_5_FELTZIN_SYSTEM_Fd1c2476b_FUN_00447340(char *p);
extern void LVL_5_FELTZIN_SYSTEM_Fd1c2476b_FUN_00447A98(char *p);
extern void LVL_5_FELTZIN_SYSTEM_Fd1c2476b_FUN_00447A98(char *p);
extern void LVL_5_FELTZIN_SYSTEM_Fd1c2476b_FUN_00447A98(char *p);
extern void LVL_5_FELTZIN_SYSTEM_Fd1c2476b_FUN_00447A98(char *p);
extern void LVL_5_FELTZIN_SYSTEM_Fd1c2476b_FUN_00447A98(char *p);

void LVL_5_FELTZIN_SYSTEM_FUN_004575F8(char *a0)
{
    if (*(int *)(a0 + 1160) == 0)
        return;
    LVL_5_FELTZIN_SYSTEM_Fd1c2476b_FUN_00447340(a0);
    LVL_5_FELTZIN_SYSTEM_Fd1c2476b_FUN_00447340(a0 + 76);
    LVL_5_FELTZIN_SYSTEM_Fd1c2476b_FUN_00447340(a0 + 152);
    LVL_5_FELTZIN_SYSTEM_Fd1c2476b_FUN_00447340(a0 + 228);
    LVL_5_FELTZIN_SYSTEM_Fd1c2476b_FUN_00447A98(a0 + 456);
    LVL_5_FELTZIN_SYSTEM_Fd1c2476b_FUN_004572D0(a0);
    LVL_5_FELTZIN_SYSTEM_Fd1c2476b_FUN_004573F0(a0);
    LVL_5_FELTZIN_SYSTEM_Fd1c2476b_FUN_004574F8(a0);
    LVL_5_FELTZIN_SYSTEM_Fd1c2476b_FUN_00447340(a0 + 380);
    LVL_5_FELTZIN_SYSTEM_Fd1c2476b_FUN_00447A98(a0 + 736);
    LVL_5_FELTZIN_SYSTEM_Fd1c2476b_FUN_00447A98(a0 + 664);
    LVL_5_FELTZIN_SYSTEM_Fd1c2476b_FUN_00447A98(a0 + 808);
    LVL_5_FELTZIN_SYSTEM_Fd1c2476b_FUN_00447A98(a0 + 880);
    LVL_5_FELTZIN_SYSTEM_Fd1c2476b_FUN_00447A98(a0 + 952);
}
extern int LVL_5_FELTZIN_SYSTEM_Fb77d67f1_FUN_003062A0(char *p);
extern void LVL_5_FELTZIN_SYSTEM_Fb77d67f1_FUN_003423C8(char *p);

void LVL_5_FELTZIN_SYSTEM_FUN_003449E0(char *a0)
{
    char *p = a0 + 32;

    if (LVL_5_FELTZIN_SYSTEM_Fb77d67f1_FUN_003062A0(p) != 0) {
        LVL_5_FELTZIN_SYSTEM_Fb77d67f1_FUN_003423C8(a0);
        return;
    }
    *(float *)(a0 + 12) = *(float *)(a0 + 12) + *(float *)(p + 4);
    if (*(int *)(a0 + 32) < 6)
        *(int *)(a0 + 4) = (*(int *)(a0 + 4) & 0xFFFFFF)
                         | ((*(int *)(a0 + 32) * 127 / 6) << 24);
}
extern void LVL_5_FELTZIN_SYSTEM_Faac80289_FUN_004471C8(char *p);
extern void LVL_5_FELTZIN_SYSTEM_Faac80289_FUN_004471C8(char *p);
extern void LVL_5_FELTZIN_SYSTEM_Faac80289_FUN_004471C8(char *p);
extern void LVL_5_FELTZIN_SYSTEM_Faac80289_FUN_004471C8(char *p);
extern void LVL_5_FELTZIN_SYSTEM_Faac80289_FUN_004471C8(char *p);
extern void LVL_5_FELTZIN_SYSTEM_Faac80289_FUN_004471C8(char *p);
extern void LVL_5_FELTZIN_SYSTEM_Faac80289_FUN_004471C8(char *p);
extern void LVL_5_FELTZIN_SYSTEM_Faac80289_FUN_00447988(char *p);

char *LVL_5_FELTZIN_SYSTEM_FUN_004594F0(char *a0)
{
    char *p = a0 + 536;
    int i;

    LVL_5_FELTZIN_SYSTEM_Faac80289_FUN_004471C8(a0);
    LVL_5_FELTZIN_SYSTEM_Faac80289_FUN_004471C8(a0 + 76);
    LVL_5_FELTZIN_SYSTEM_Faac80289_FUN_004471C8(a0 + 152);
    LVL_5_FELTZIN_SYSTEM_Faac80289_FUN_004471C8(a0 + 228);
    LVL_5_FELTZIN_SYSTEM_Faac80289_FUN_004471C8(a0 + 304);
    LVL_5_FELTZIN_SYSTEM_Faac80289_FUN_004471C8(a0 + 380);
    LVL_5_FELTZIN_SYSTEM_Faac80289_FUN_004471C8(a0 + 456);

    for (i = 6; i != -1; i--) {
        LVL_5_FELTZIN_SYSTEM_Faac80289_FUN_00447988(p);
        p += 72;
    }
    return a0;
}
extern int LVL_5_FELTZIN_SYSTEM_Ff67aa9df_D_001A7350 __attribute__((sda));
extern int LVL_5_FELTZIN_SYSTEM_Ff67aa9df_D_001A7354 __attribute__((sda));
extern void LVL_5_FELTZIN_SYSTEM_Ff67aa9df_FUN_00301380(void *v, void *x);

void LVL_5_FELTZIN_SYSTEM_FUN_00301440(int i0, int i1, int i2, int i3, int tag, void *x)
{
    long long v[4];

    v[0] = (((i0 << 4) + LVL_5_FELTZIN_SYSTEM_Ff67aa9df_D_001A7350) - 8)
         | ((long long)(((i1 << 4) + LVL_5_FELTZIN_SYSTEM_Ff67aa9df_D_001A7354) - 8) << 16)
         | ((long long)tag << 32);
    v[1] = (((i2 << 4) + LVL_5_FELTZIN_SYSTEM_Ff67aa9df_D_001A7350) - 8)
         | ((long long)(((i1 << 4) + LVL_5_FELTZIN_SYSTEM_Ff67aa9df_D_001A7354) - 8) << 16)
         | ((long long)tag << 32);
    v[2] = (((i0 << 4) + LVL_5_FELTZIN_SYSTEM_Ff67aa9df_D_001A7350) - 8)
         | ((long long)(((i3 << 4) + LVL_5_FELTZIN_SYSTEM_Ff67aa9df_D_001A7354) - 8) << 16)
         | ((long long)tag << 32);
    v[3] = (((i2 << 4) + LVL_5_FELTZIN_SYSTEM_Ff67aa9df_D_001A7350) - 8)
         | ((long long)(((i3 << 4) + LVL_5_FELTZIN_SYSTEM_Ff67aa9df_D_001A7354) - 8) << 16)
         | ((long long)tag << 32);
    LVL_5_FELTZIN_SYSTEM_Ff67aa9df_FUN_00301380(v, x);
}
extern void LVL_5_FELTZIN_SYSTEM_Fc558ca70_FUN_0044BE50(char *p);
extern void LVL_5_FELTZIN_SYSTEM_Fc558ca70_FUN_0044C040(char *p, float a, float b);
extern void LVL_5_FELTZIN_SYSTEM_Fc558ca70_FUN_00371A60(int a, int b, int c);

extern volatile unsigned char LVL_5_FELTZIN_SYSTEM_Fc558ca70_D_001A7B95 __attribute__((sda));
extern volatile unsigned char LVL_5_FELTZIN_SYSTEM_Fc558ca70_D_001A7B94 __attribute__((sda));

int LVL_5_FELTZIN_SYSTEM_FUN_0044DB40(char *a0, int a1)
{
    char *p = a0 + 8;
    float *q;
    int v;

    LVL_5_FELTZIN_SYSTEM_Fc558ca70_FUN_0044BE50(p);
    q = *(float **)(a0 + 684);
    LVL_5_FELTZIN_SYSTEM_Fc558ca70_FUN_0044C040(p, q[0], q[1]);
    if (a1 & 0x1000) {
        LVL_5_FELTZIN_SYSTEM_Fc558ca70_FUN_00371A60(3, 0, 0);
        v = *(int *)(a0 + 680);
        *(int *)(a0 + 680) = (v + 1) % 2;
    } else if (a1 & 0x4000) {
        LVL_5_FELTZIN_SYSTEM_Fc558ca70_FUN_00371A60(3, 0, 0);
        v = *(int *)(a0 + 680);
        *(int *)(a0 + 680) = (v + 1) % 2;
    } else if (a1 & 0x40) {
        LVL_5_FELTZIN_SYSTEM_Fc558ca70_FUN_00371A60(4, 0, 0);
        switch (*(int *)(a0 + 680)) {
        case 0:
            LVL_5_FELTZIN_SYSTEM_Fc558ca70_D_001A7B95 = LVL_5_FELTZIN_SYSTEM_Fc558ca70_D_001A7B95 == 0;
            break;
        case 1:
            LVL_5_FELTZIN_SYSTEM_Fc558ca70_D_001A7B94 = LVL_5_FELTZIN_SYSTEM_Fc558ca70_D_001A7B94 == 0;
            break;
        }
    }
    return (a1 >> 6) & 1;
}
extern void LVL_5_FELTZIN_SYSTEM_Fb7feb893_FUN_0044BE50(char *p);
extern void LVL_5_FELTZIN_SYSTEM_Fb7feb893_FUN_0044C040(char *p, float a, float b);
extern void LVL_5_FELTZIN_SYSTEM_Fb7feb893_FUN_00371A60(int a, int b, int c);

extern volatile unsigned char LVL_5_FELTZIN_SYSTEM_Fb7feb893_D_001A7BB2 __attribute__((sda));
extern volatile unsigned char LVL_5_FELTZIN_SYSTEM_Fb7feb893_D_001A7BB3 __attribute__((sda));

int LVL_5_FELTZIN_SYSTEM_FUN_0044E890(char *a0, int a1)
{
    char *p = a0 + 8;
    float *q;
    int v;

    LVL_5_FELTZIN_SYSTEM_Fb7feb893_FUN_0044BE50(p);
    q = *(float **)(a0 + 684);
    LVL_5_FELTZIN_SYSTEM_Fb7feb893_FUN_0044C040(p, q[0], q[1]);
    if (a1 & 0x1000) {
        LVL_5_FELTZIN_SYSTEM_Fb7feb893_FUN_00371A60(3, 0, 0);
        v = *(int *)(a0 + 680);
        *(int *)(a0 + 680) = (v + 1) % 2;
    } else if (a1 & 0x4000) {
        LVL_5_FELTZIN_SYSTEM_Fb7feb893_FUN_00371A60(3, 0, 0);
        v = *(int *)(a0 + 680);
        *(int *)(a0 + 680) = (v + 1) % 2;
    } else if (a1 & 0x40) {
        LVL_5_FELTZIN_SYSTEM_Fb7feb893_FUN_00371A60(4, 0, 0);
        switch (*(int *)(a0 + 680)) {
        case 0:
            LVL_5_FELTZIN_SYSTEM_Fb7feb893_D_001A7BB2 = LVL_5_FELTZIN_SYSTEM_Fb7feb893_D_001A7BB2 == 0;
            break;
        case 1:
            LVL_5_FELTZIN_SYSTEM_Fb7feb893_D_001A7BB3 = LVL_5_FELTZIN_SYSTEM_Fb7feb893_D_001A7BB3 == 0;
            break;
        }
    }
    return (a1 >> 6) & 1;
}
#ifndef RAC2_T_V4_F213135AA
#define RAC2_T_V4_F213135AA
typedef struct { float x, y, z, w; } V4_F213135aa;
#endif


extern float LVL_5_FELTZIN_SYSTEM_F213135aa_FUN_00332B50(float a, float b);
extern float LVL_5_FELTZIN_SYSTEM_F213135aa_FUN_00332B50(float a, float b);
extern void LVL_5_FELTZIN_SYSTEM_F213135aa_FUN_00306E78(char *a, char *b);
extern void LVL_5_FELTZIN_SYSTEM_F213135aa_FUN_003068F8(char *a, char *b, float f);
extern void LVL_5_FELTZIN_SYSTEM_F213135aa_FUN_00306660(char *a, char *b, char *c);
extern void LVL_5_FELTZIN_SYSTEM_F213135aa_FUN_00306748(char *a, char *b, char *c);
extern void LVL_5_FELTZIN_SYSTEM_F213135aa_FUN_003068F8(char *a, char *b, float f);
extern void LVL_5_FELTZIN_SYSTEM_F213135aa_FUN_00336928(char *a, char *b, float f);

int LVL_5_FELTZIN_SYSTEM_FUN_00396FC8(char *obj, char *obj2, float x, float y)
{
    V4_F213135aa m0, m1, m2;
    char *s1;
    char *s3;
    float f22;

    s1 = *(char **)(obj + 104);
    if (*(unsigned char *)(obj + 32) == 4)
        return 0;
    f22 = 0.0f;
    if (x == 0.0f)
        x = LVL_5_FELTZIN_SYSTEM_F213135aa_FUN_00332B50(-30.0f, 30.0f) * 1.7453294247388839721680e-02f;
    if (y == 0.0f)
        y = LVL_5_FELTZIN_SYSTEM_F213135aa_FUN_00332B50(f22, 30.0f) * 1.7453294247388839721680e-02f;
    s3 = s1 + 32;
    if (*(unsigned char *)(obj + 32) == 3) {
        LVL_5_FELTZIN_SYSTEM_F213135aa_FUN_00306E78((char *)&m0, s1 + 16);
        LVL_5_FELTZIN_SYSTEM_F213135aa_FUN_003068F8(s3, (char *)&m2, 1.3333334028720855712891e-01f);
    }
    *(float *)(s1 + 100) = f22;
    *(float *)(s1 + 76) = x;
    *(float *)(s1 + 72) = y;
    *(char **)(s1 + 96) = obj2;
    LVL_5_FELTZIN_SYSTEM_F213135aa_FUN_00306660((char *)&m1, obj2 + 16, obj + 16);
    s1 = s1 + 48;
    LVL_5_FELTZIN_SYSTEM_F213135aa_FUN_00306748((char *)&m0, s3, (char *)&m1);
    LVL_5_FELTZIN_SYSTEM_F213135aa_FUN_003068F8(s1, (char *)&m0, 1.0f);
    LVL_5_FELTZIN_SYSTEM_F213135aa_FUN_00336928(s1, s1, 2.0943954586982727050781e-01f);
    *(unsigned char *)(obj + 32) = 4;
    return 1;
}
extern void LVL_5_FELTZIN_SYSTEM_Fb1bbe20c_FUN_0044BE50(char *p);
extern void LVL_5_FELTZIN_SYSTEM_Fb1bbe20c_FUN_0044C040(char *p, float x, float y);
extern int LVL_5_FELTZIN_SYSTEM_Fb1bbe20c_FUN_00371A60(int a, int b, int c);
extern volatile unsigned char LVL_5_FELTZIN_SYSTEM_Fb1bbe20c_D_001A7BB2 __attribute__((sda));

int LVL_5_FELTZIN_SYSTEM_FUN_0044EC58(char *object, int flags)
{
    float *vec;

    LVL_5_FELTZIN_SYSTEM_Fb1bbe20c_FUN_0044BE50(object + 8);
    vec = *(float **)(object + 684);
    LVL_5_FELTZIN_SYSTEM_Fb1bbe20c_FUN_0044C040(object + 8, vec[0], vec[1]);

    if ((flags & 0x40) && *(int *)(object + 680) == 0) {
        int discarded = LVL_5_FELTZIN_SYSTEM_Fb1bbe20c_FUN_00371A60(4, 0, 0);
        (void)discarded;
        LVL_5_FELTZIN_SYSTEM_Fb1bbe20c_D_001A7BB2 = (LVL_5_FELTZIN_SYSTEM_Fb1bbe20c_D_001A7BB2 < 1);
    }

    return (flags >> 6) & 1;
}
extern void LVL_5_FELTZIN_SYSTEM_Fb1bbe20c_FUN_0044BE50(char *p);
extern void LVL_5_FELTZIN_SYSTEM_Fb1bbe20c_FUN_0044C040(char *p, float x, float y);
extern int LVL_5_FELTZIN_SYSTEM_Fb1bbe20c_FUN_00371A60(int a, int b, int c);
extern volatile unsigned char LVL_5_FELTZIN_SYSTEM_Fb1bbe20c_D_001A7BB2 __attribute__((sda));

int LVL_5_FELTZIN_SYSTEM_FUN_0044EF08(char *object, int flags)
{
    float *vec;

    LVL_5_FELTZIN_SYSTEM_Fb1bbe20c_FUN_0044BE50(object + 8);
    vec = *(float **)(object + 684);
    LVL_5_FELTZIN_SYSTEM_Fb1bbe20c_FUN_0044C040(object + 8, vec[0], vec[1]);

    if ((flags & 0x40) && *(int *)(object + 680) == 0) {
        int discarded = LVL_5_FELTZIN_SYSTEM_Fb1bbe20c_FUN_00371A60(4, 0, 0);
        (void)discarded;
        LVL_5_FELTZIN_SYSTEM_Fb1bbe20c_D_001A7BB2 = (LVL_5_FELTZIN_SYSTEM_Fb1bbe20c_D_001A7BB2 < 1);
    }

    return (flags >> 6) & 1;
}
extern void LVL_5_FELTZIN_SYSTEM_Fb1bbe20c_FUN_0044BE50(char *p);
extern void LVL_5_FELTZIN_SYSTEM_Fb1bbe20c_FUN_0044C040(char *p, float x, float y);
extern int LVL_5_FELTZIN_SYSTEM_Fb1bbe20c_FUN_00371A60(int a, int b, int c);
extern volatile unsigned char LVL_5_FELTZIN_SYSTEM_Fb1bbe20c_D_001A7BB2 __attribute__((sda));

int LVL_5_FELTZIN_SYSTEM_FUN_0044F100(char *object, int flags)
{
    float *vec;

    LVL_5_FELTZIN_SYSTEM_Fb1bbe20c_FUN_0044BE50(object + 8);
    vec = *(float **)(object + 684);
    LVL_5_FELTZIN_SYSTEM_Fb1bbe20c_FUN_0044C040(object + 8, vec[0], vec[1]);

    if ((flags & 0x40) && *(int *)(object + 680) == 0) {
        int discarded = LVL_5_FELTZIN_SYSTEM_Fb1bbe20c_FUN_00371A60(4, 0, 0);
        (void)discarded;
        LVL_5_FELTZIN_SYSTEM_Fb1bbe20c_D_001A7BB2 = (LVL_5_FELTZIN_SYSTEM_Fb1bbe20c_D_001A7BB2 < 1);
    }

    return (flags >> 6) & 1;
}
extern void LVL_5_FELTZIN_SYSTEM_Ff2d8e5ad_FUN_0032D928(unsigned char *a, int b, unsigned char *c);
extern void LVL_5_FELTZIN_SYSTEM_Ff2d8e5ad_FUN_00306B70(unsigned char *a, long long v);
extern void LVL_5_FELTZIN_SYSTEM_Ff2d8e5ad_FUN_00306B70(unsigned char *a, long long v);
extern void LVL_5_FELTZIN_SYSTEM_Ff2d8e5ad_FUN_00306B00(unsigned char *a, unsigned char *b, unsigned char *c);
extern void LVL_5_FELTZIN_SYSTEM_Ff2d8e5ad_FUN_00306B00(unsigned char *a, unsigned char *b, unsigned char *c);
extern void LVL_5_FELTZIN_SYSTEM_Ff2d8e5ad_FUN_003066A0(unsigned char *a, unsigned char *b, float f);
extern void LVL_5_FELTZIN_SYSTEM_Ff2d8e5ad_FUN_003066A0(unsigned char *a, unsigned char *b, float f);
extern void LVL_5_FELTZIN_SYSTEM_Ff2d8e5ad_FUN_00306AD8(unsigned char *a, unsigned char *b, unsigned char *c);
extern void LVL_5_FELTZIN_SYSTEM_Ff2d8e5ad_FUN_00306AD8(unsigned char *a, unsigned char *b, unsigned char *c);
extern void LVL_5_FELTZIN_SYSTEM_Ff2d8e5ad_FUN_00306630(unsigned char *a, unsigned char *b, unsigned char *c);
extern void LVL_5_FELTZIN_SYSTEM_Ff2d8e5ad_FUN_00306630(unsigned char *a, unsigned char *b, unsigned char *c);
extern void LVL_5_FELTZIN_SYSTEM_Ff2d8e5ad_FUN_00306630(unsigned char *a, unsigned char *b, unsigned char *c);
extern void LVL_5_FELTZIN_SYSTEM_Ff2d8e5ad_FUN_003066A0(unsigned char *a, unsigned char *b, float f);
extern float LVL_5_FELTZIN_SYSTEM_Ff2d8e5ad_FUN_003067D8(unsigned char *a, unsigned char *b);

void LVL_5_FELTZIN_SYSTEM_FUN_00328CE8(
    unsigned char *obj, unsigned int index, unsigned char *dest)
{
    unsigned char m0[16];
    unsigned char m1[16];
    unsigned char *base;
    unsigned char *p;
    short n;

    base = *(unsigned char **)(obj + 36);
    p = base + ((unsigned int)*(unsigned char *)(base + 44) << 4);
    p = p + ((index << 4) + 64u);
    n = *(short *)(p + 6);
    if (n < *(short *)(p + 14))
        n = *(short *)(p + 14);
    if (n >= 0)
        LVL_5_FELTZIN_SYSTEM_Ff2d8e5ad_FUN_0032D928(obj, n + 1, (unsigned char *)0x80000000u);
    LVL_5_FELTZIN_SYSTEM_Ff2d8e5ad_FUN_00306B70(m0, *(long long *)(p));
    LVL_5_FELTZIN_SYSTEM_Ff2d8e5ad_FUN_00306B70(m1, *(long long *)(p + 8));
    *(float *)(m0 + 12) = 1.0f;
    *(float *)(m1 + 12) = 1.0f;
    if (n >= 0) {
        LVL_5_FELTZIN_SYSTEM_Ff2d8e5ad_FUN_00306B00(m0, m0, (unsigned char *)
            (((unsigned int)*(short *)(p + 6) << 6) + 0x70000000u));
        LVL_5_FELTZIN_SYSTEM_Ff2d8e5ad_FUN_00306B00(m1, m1, (unsigned char *)
            (((unsigned int)*(short *)(p + 14) << 6) + 0x70000000u));
    }
    LVL_5_FELTZIN_SYSTEM_Ff2d8e5ad_FUN_003066A0(m0, m0, *(float *)(obj + 44) * 0.0009765625f);
    LVL_5_FELTZIN_SYSTEM_Ff2d8e5ad_FUN_003066A0(m1, m1, *(float *)(obj + 44) * 0.0009765625f);
    LVL_5_FELTZIN_SYSTEM_Ff2d8e5ad_FUN_00306AD8(m0, m0, obj + 192);
    LVL_5_FELTZIN_SYSTEM_Ff2d8e5ad_FUN_00306AD8(m1, m1, obj + 192);
    LVL_5_FELTZIN_SYSTEM_Ff2d8e5ad_FUN_00306630(m0, m0, obj + 16);
    LVL_5_FELTZIN_SYSTEM_Ff2d8e5ad_FUN_00306630(m1, m1, obj + 16);
    LVL_5_FELTZIN_SYSTEM_Ff2d8e5ad_FUN_00306630(dest, m0, m1);
    LVL_5_FELTZIN_SYSTEM_Ff2d8e5ad_FUN_003066A0(dest, dest, 0.5f);
    *(float *)(dest + 12) = LVL_5_FELTZIN_SYSTEM_Ff2d8e5ad_FUN_003067D8(dest, m0);
}
extern void LVL_5_FELTZIN_SYSTEM_F5a19df7a_FUN_003906F8(unsigned int a, unsigned long b);
extern void LVL_5_FELTZIN_SYSTEM_F5a19df7a_FUN_003DE740(char *p);
extern void LVL_5_FELTZIN_SYSTEM_F5a19df7a_FUN_003DEB18(char *p);
extern char *LVL_5_FELTZIN_SYSTEM_F5a19df7a_FUN_00332AF8(int a, int b);
extern float LVL_5_FELTZIN_SYSTEM_F5a19df7a_FUN_00332C18(void);
extern void LVL_5_FELTZIN_SYSTEM_F5a19df7a_FUN_003DF340(char *a, int b, float e, char *c, float f, int d, int g);

void LVL_5_FELTZIN_SYSTEM_FUN_003DF1A0(char *p)
{
    char *q;
    char *o;
    char *r;
    float v;
    float w;

    q = p + 16;
    o = *(char **)(p + 104);
    LVL_5_FELTZIN_SYSTEM_F5a19df7a_FUN_003906F8(0x47, 0x53001UL);
    LVL_5_FELTZIN_SYSTEM_F5a19df7a_FUN_003DE740(p);
    LVL_5_FELTZIN_SYSTEM_F5a19df7a_FUN_003DEB18(p);

    v = *(float *)(o + 24);
    v = v * 0.5f;
    r = LVL_5_FELTZIN_SYSTEM_F5a19df7a_FUN_00332AF8(80, 96);
    w = LVL_5_FELTZIN_SYSTEM_F5a19df7a_FUN_00332C18();
    LVL_5_FELTZIN_SYSTEM_F5a19df7a_FUN_003DF340(q, 0x103080, v, r, w, 49, 2);

    v = *(float *)(o + 24);
    v = v * 3.00000011920928955078125e-01f;
    r = LVL_5_FELTZIN_SYSTEM_F5a19df7a_FUN_00332AF8(80, 96);
    w = LVL_5_FELTZIN_SYSTEM_F5a19df7a_FUN_00332C18();
    LVL_5_FELTZIN_SYSTEM_F5a19df7a_FUN_003DF340(q, 0xFFFFFF, v, r, w, 49, 2);

    v = *(float *)(o + 24);
    v = v * 6.99999988079071044921875e-01f;
    r = LVL_5_FELTZIN_SYSTEM_F5a19df7a_FUN_00332AF8(8, 22);
    w = LVL_5_FELTZIN_SYSTEM_F5a19df7a_FUN_00332C18();
    LVL_5_FELTZIN_SYSTEM_F5a19df7a_FUN_003DF340(q, 0x803010, v, r, w, 11, 2);

    v = *(float *)(o + 24);
    v = v * 4.49999988079071044921875e-01f;
    r = LVL_5_FELTZIN_SYSTEM_F5a19df7a_FUN_00332AF8(32, 64);
    w = LVL_5_FELTZIN_SYSTEM_F5a19df7a_FUN_00332C18();
    LVL_5_FELTZIN_SYSTEM_F5a19df7a_FUN_003DF340(q, 0x803010, v, r, w, 11, 2);

    LVL_5_FELTZIN_SYSTEM_F5a19df7a_FUN_003906F8(0x47, 0x5360bUL);
}
extern float LVL_5_FELTZIN_SYSTEM_Fb1c9893c_FUN_00332C18(void);
extern float LVL_5_FELTZIN_SYSTEM_Fb1c9893c_FUN_00332B50(float, float);
extern float LVL_5_FELTZIN_SYSTEM_Fb1c9893c_FUN_00306C08(float);
extern float LVL_5_FELTZIN_SYSTEM_Fb1c9893c_FUN_00306C20(float);
extern void LVL_5_FELTZIN_SYSTEM_Fb1c9893c_FUN_00306AD8(float *dst, float *src, char *table);
extern void LVL_5_FELTZIN_SYSTEM_Fb1c9893c_FUN_00306630(float *dst, float *src, int arg);
extern int LVL_5_FELTZIN_SYSTEM_Fb1c9893c_D_001A8FF0 __attribute__((sda));
extern void LVL_5_FELTZIN_SYSTEM_Fb1c9893c_FUN_002F4188(char *self, int a1, int a2, int a3, char *p4, char *p5,
                    float *buf, int b3, float fa, float fb);

void LVL_5_FELTZIN_SYSTEM_FUN_0033CDB0(char *self, int mask, int arg2,
                                        unsigned char arg3,
                                        float f0, float f1, float f2, float f3)
{
    float buf[3];
    float v;
    float k;
    float fa;
    float fb;
    int i;

    for (i = 0; i < 15; i++) {
        if (((mask >> i) ^ 1) & 1)
            continue;
        v = LVL_5_FELTZIN_SYSTEM_Fb1c9893c_FUN_00332C18();
        k = LVL_5_FELTZIN_SYSTEM_Fb1c9893c_FUN_00332B50(f0, f1) * (1.0f / 60.0f);
        buf[0] = LVL_5_FELTZIN_SYSTEM_Fb1c9893c_FUN_00306C08(v) * k;
        buf[1] = LVL_5_FELTZIN_SYSTEM_Fb1c9893c_FUN_00306C20(v) * k;
        buf[2] = 0.0f;
        buf[2] = LVL_5_FELTZIN_SYSTEM_Fb1c9893c_FUN_00332B50(f2, f3) * (1.0f / 60.0f);
        if (LVL_5_FELTZIN_SYSTEM_Fb1c9893c_D_001A8FF0 != 0)
            LVL_5_FELTZIN_SYSTEM_Fb1c9893c_FUN_00306AD8(buf, buf, self + 192);
        LVL_5_FELTZIN_SYSTEM_Fb1c9893c_FUN_00306630(buf, buf, arg2);
        fa = LVL_5_FELTZIN_SYSTEM_Fb1c9893c_FUN_00332B50(90.0f, 270.0f);
        fb = LVL_5_FELTZIN_SYSTEM_Fb1c9893c_FUN_00332B50(10.0f, 20.0f);
        LVL_5_FELTZIN_SYSTEM_Fb1c9893c_FUN_002F4188(self, 2, *(short *)(self + 170), i, self + 16, self + 240,
                buf, arg3, fa, fb);
    }
}
extern int LVL_5_FELTZIN_SYSTEM_Fdd54ca5d_FUN_003062D0(char *p);
extern void LVL_5_FELTZIN_SYSTEM_Fdd54ca5d_FUN_003423C8(char *self);
extern float LVL_5_FELTZIN_SYSTEM_Fdd54ca5d_FUN_00307768(int v);
extern float LVL_5_FELTZIN_SYSTEM_Fdd54ca5d_FUN_00307768(int v);
extern int LVL_5_FELTZIN_SYSTEM_Fdd54ca5d_FUN_00307778(float f);
extern void LVL_5_FELTZIN_SYSTEM_Fdd54ca5d_FUN_00306630(char *dst, char *src, char *vec);
extern void LVL_5_FELTZIN_SYSTEM_Fdd54ca5d_FUN_00394B90(char *dst, char *src);
extern void LVL_5_FELTZIN_SYSTEM_Fdd54ca5d_FUN_003066A0(char *dst, char *table, float scale);
extern void LVL_5_FELTZIN_SYSTEM_Fdd54ca5d_FUN_00306630(char *dst, char *src, char *vec);
extern void LVL_5_FELTZIN_SYSTEM_Fdd54ca5d_FUN_003066A0(char *dst, char *table, float scale);
extern char LVL_5_FELTZIN_SYSTEM_Fdd54ca5d_D_0018A0E0[];

void LVL_5_FELTZIN_SYSTEM_FUN_0034AE50(char *self)
{
    float vec[4];
    float tmp[4];
    char *s1;
    char *p;
    float f20;
    float t;
    unsigned int v;

    if (LVL_5_FELTZIN_SYSTEM_Fdd54ca5d_FUN_003062D0(self + 10)) {
        LVL_5_FELTZIN_SYSTEM_Fdd54ca5d_FUN_003423C8(self);
        return;
    }
    s1 = self + 32;
    f20 = LVL_5_FELTZIN_SYSTEM_Fdd54ca5d_FUN_00307768(*(short *)(s1 + 30));
    t = LVL_5_FELTZIN_SYSTEM_Fdd54ca5d_FUN_00307768(*(short *)(s1 + 28));
    v = LVL_5_FELTZIN_SYSTEM_Fdd54ca5d_FUN_00307778(f20 * ((float)*(short *)(self + 10) / t));
    v = v << 24;
    v = v | (*(unsigned char *)(s1 + 19) << 16);
    v = v | (*(unsigned char *)(s1 + 18) << 8);
    v = v | *(unsigned char *)(s1 + 17);
    *(unsigned int *)(self + 4) = v;
    vec[3] = 0.0f;
    vec[0] = *(float *)(self + 32);
    vec[1] = *(float *)(s1 + 4);
    vec[2] = *(float *)(s1 + 8);
    LVL_5_FELTZIN_SYSTEM_Fdd54ca5d_FUN_00306630((char *)self + 16, (char *)self + 16, (char *)vec);
    if (*(float *)(self + 28) != 0.0f) {
        if (*(float *)(self + 28) == 2.0f)
            LVL_5_FELTZIN_SYSTEM_Fdd54ca5d_FUN_00394B90((char *)self + 16, (char *)self + 16);
        *(float *)(self + 28) = 2.0f;
    }
    p = (char *)tmp;
    LVL_5_FELTZIN_SYSTEM_Fdd54ca5d_FUN_003066A0(p, LVL_5_FELTZIN_SYSTEM_Fdd54ca5d_D_0018A0E0, *(float *)(s1 + 12));
    LVL_5_FELTZIN_SYSTEM_Fdd54ca5d_FUN_00306630((char *)vec, (char *)vec, p);
    LVL_5_FELTZIN_SYSTEM_Fdd54ca5d_FUN_003066A0((char *)vec, (char *)vec, *(float *)(s1 + 24));
    *(float *)s1 = vec[0];
    *(float *)(s1 + 4) = vec[1];
    *(float *)(s1 + 8) = vec[2];
    *(unsigned char *)(self + 8) = *(unsigned char *)(self + 8) + *(unsigned char *)(s1 + 16);
    *(float *)(self + 12) = *(float *)(self + 12) + *(float *)(s1 + 20);
}
extern float LVL_5_FELTZIN_SYSTEM_Fb5729173_FUN_003067D8(char *a, char *b);
extern float LVL_5_FELTZIN_SYSTEM_Fb5729173_FUN_00306CD0(float x, float y);
extern float LVL_5_FELTZIN_SYSTEM_Fb5729173_FUN_00307708(float x, float y);
extern float LVL_5_FELTZIN_SYSTEM_Fb5729173_FUN_00306810(char *a, char *b);
extern int LVL_5_FELTZIN_SYSTEM_Fb5729173_FUN_00336F78(char *a);

float LVL_5_FELTZIN_SYSTEM_FUN_0033B548(char *a0, char *a1, int *a2,
                                       float p1, float p2, float p3, float p4)
{
    float best = p4;
    float hi = p3;
    float radius;
    float reach = p2;
    float far;
    float near;
    float tmp;

    *a2 = 0;
    far = LVL_5_FELTZIN_SYSTEM_Fb5729173_FUN_003067D8(a0, a1 + 16);
    if (reach < far) {
        *a2 = 1;
    }

    reach = 0.0f;
    radius = LVL_5_FELTZIN_SYSTEM_Fb5729173_FUN_00307708(LVL_5_FELTZIN_SYSTEM_Fb5729173_FUN_00306CD0(((float *)(a1 + 16))[0] - ((float *)a0)[0],
                             ((float *)(a1 + 16))[1] - ((float *)a0)[1]), p1);
    near = LVL_5_FELTZIN_SYSTEM_Fb5729173_FUN_00306810(a0, a1 + 16);
    tmp = LVL_5_FELTZIN_SYSTEM_Fb5729173_FUN_00307708(LVL_5_FELTZIN_SYSTEM_Fb5729173_FUN_00306CD0(near, ((float *)(a1 + 16))[2] - ((float *)a0)[2]), 0.0f);

    if (reach < hi) {
        if (hi < radius) {
            *a2 = 1;
        }
    }
    if (0.0f < best) {
        if (best < tmp) {
            *a2 = 1;
        }
    }

    reach = far + radius * far;
    if (LVL_5_FELTZIN_SYSTEM_Fb5729173_FUN_00336F78(a1) != 0) {
        reach = reach + 8.0f;
    }
    return reach;
}
struct family_27f9_object {
    unsigned char reserved[248];
    float heading;
};

extern float LVL_5_FELTZIN_SYSTEM_F27f9be8e_FUN_00307668(float p, float x);
extern float LVL_5_FELTZIN_SYSTEM_F27f9be8e_FUN_003065A0(float t);
extern float LVL_5_FELTZIN_SYSTEM_F27f9be8e_FUN_003065A0(float t);
extern float LVL_5_FELTZIN_SYSTEM_F27f9be8e_FUN_003065A0(float t);
extern float LVL_5_FELTZIN_SYSTEM_F27f9be8e_FUN_003065A0(float t);
extern float LVL_5_FELTZIN_SYSTEM_F27f9be8e_FUN_00307620(float x, float y);

float LVL_5_FELTZIN_SYSTEM_FUN_00333190(struct family_27f9_object *a0,
                                         float *a1,
                                         float p1, float p2, float p3, float p4)
{
    float t;
    float v;
    float f3;
    float out;

    t = LVL_5_FELTZIN_SYSTEM_F27f9be8e_FUN_00307668(p1, a0->heading);
    v = t * 6.3661971092224121093750e+00f;
    if (v > 1.0f) {
        v = 1.0f;
    } else {
        if (v < -1.0f) {
            v = -1.0f;
        }
    }
    f3 = a1[0];
    a1[0] = f3 + (p2 * v - p3 * f3);
    if (p4 != 0.0f) {
        if (a1[0] > p4) {
            a1[0] = p4;
        } else {
            if (a1[0] < -p4) {
                a1[0] = -p4;
            }
        }
    }
    if (LVL_5_FELTZIN_SYSTEM_F27f9be8e_FUN_003065A0(t) < a1[0]) {
        a1[0] = LVL_5_FELTZIN_SYSTEM_F27f9be8e_FUN_003065A0(t);
    } else {
        if (a1[0] < -LVL_5_FELTZIN_SYSTEM_F27f9be8e_FUN_003065A0(t)) {
            a1[0] = -LVL_5_FELTZIN_SYSTEM_F27f9be8e_FUN_003065A0(t);
        }
    }
    out = LVL_5_FELTZIN_SYSTEM_F27f9be8e_FUN_00307620(a0->heading, a1[0]);
    a0->heading = out;
    return out;
}

#ifndef RAC2_T_S16_FC94396F4
#define RAC2_T_S16_FC94396F4
typedef signed short s16_Fc94396f4;
#endif




#ifndef RAC2_T_FAMILYC94396F4VECTOR_FC94396F4
#define RAC2_T_FAMILYC94396F4VECTOR_FC94396F4
typedef struct {
    f32 x;
    f32 y;
    f32 z;
} FamilyC94396F4Vector_Fc94396f4;
#endif


#ifndef RAC2_T_FAMILYC94396F4STATE_FC94396F4
#define RAC2_T_FAMILYC94396F4STATE_FC94396F4
typedef struct {
    u8 reserved0[846];
    s16_Fc94396f4 gate;
    u8 reserved1[8004];
    s32 state;
    u8 reserved2[43];
    u8 mode;
} FamilyC94396F4State_Fc94396f4;
#endif


extern FamilyC94396F4State_Fc94396f4 LVL_5_FELTZIN_SYSTEM_Fc94396f4_D_00189E20;
extern u8 LVL_5_FELTZIN_SYSTEM_Fc94396f4_D_0018A0E0[];

extern void LVL_5_FELTZIN_SYSTEM_Fc94396f4_FUN_003068F8(u8 *buffer, u8 *table, f32 parameter);
extern void LVL_5_FELTZIN_SYSTEM_Fc94396f4_FUN_002EC458(u8 *buffer, FamilyC94396F4Vector_Fc94396f4 *source, f32 zero);
extern void LVL_5_FELTZIN_SYSTEM_Fc94396f4_FUN_002EC3D8(FamilyC94396F4Vector_Fc94396f4 *destination,
                    FamilyC94396F4Vector_Fc94396f4 *source, f32 zero);
extern void LVL_5_FELTZIN_SYSTEM_Fc94396f4_FUN_00306630(FamilyC94396F4Vector_Fc94396f4 *destination,
                    FamilyC94396F4Vector_Fc94396f4 *source, u8 *buffer);
extern void LVL_5_FELTZIN_SYSTEM_Fc94396f4_FUN_00306630(FamilyC94396F4Vector_Fc94396f4 *destination,
                    FamilyC94396F4Vector_Fc94396f4 *source, u8 *buffer);
extern void LVL_5_FELTZIN_SYSTEM_Fc94396f4_FUN_003068F8(u8 *buffer, u8 *table, f32 parameter);
extern void LVL_5_FELTZIN_SYSTEM_Fc94396f4_FUN_003068F8(u8 *buffer, u8 *table, f32 parameter);
extern void LVL_5_FELTZIN_SYSTEM_Fc94396f4_FUN_002EC458(u8 *buffer, FamilyC94396F4Vector_Fc94396f4 *source, f32 zero);
extern void LVL_5_FELTZIN_SYSTEM_Fc94396f4_FUN_002EC3D8(FamilyC94396F4Vector_Fc94396f4 *destination,
                    FamilyC94396F4Vector_Fc94396f4 *source, f32 zero);
extern void LVL_5_FELTZIN_SYSTEM_Fc94396f4_FUN_00306630(FamilyC94396F4Vector_Fc94396f4 *destination,
                    FamilyC94396F4Vector_Fc94396f4 *source, u8 *buffer);
extern void LVL_5_FELTZIN_SYSTEM_Fc94396f4_FUN_00306630(FamilyC94396F4Vector_Fc94396f4 *destination,
                     FamilyC94396F4Vector_Fc94396f4 *source, u8 *buffer);

void LVL_5_FELTZIN_SYSTEM_FUN_002EBD40(FamilyC94396F4Vector_Fc94396f4 *destination,
                                      FamilyC94396F4Vector_Fc94396f4 *source,
                                      f32 parameter)
{
    u8 first[16];
    u8 second[16];

    switch (LVL_5_FELTZIN_SYSTEM_Fc94396f4_D_00189E20.mode) {
    case 0:
        destination->z = source->z - parameter;
        return;
    case 1:
        LVL_5_FELTZIN_SYSTEM_Fc94396f4_FUN_003068F8(first, (u8 *)&LVL_5_FELTZIN_SYSTEM_Fc94396f4_D_00189E20 + 672, -parameter);
        LVL_5_FELTZIN_SYSTEM_Fc94396f4_FUN_002EC458(second, source, 0.0f);
        LVL_5_FELTZIN_SYSTEM_Fc94396f4_FUN_002EC3D8(destination, destination, 0.0f);
        LVL_5_FELTZIN_SYSTEM_Fc94396f4_FUN_00306630(destination, destination, second);
        LVL_5_FELTZIN_SYSTEM_Fc94396f4_FUN_00306630(destination, destination, first);
        return;
    case 2:
        if (LVL_5_FELTZIN_SYSTEM_Fc94396f4_D_00189E20.state == 58 && LVL_5_FELTZIN_SYSTEM_Fc94396f4_D_00189E20.gate == 0) {
            LVL_5_FELTZIN_SYSTEM_Fc94396f4_FUN_003068F8(first, (u8 *)&LVL_5_FELTZIN_SYSTEM_Fc94396f4_D_00189E20 + 672, -parameter);
        } else {
            LVL_5_FELTZIN_SYSTEM_Fc94396f4_FUN_003068F8(first, LVL_5_FELTZIN_SYSTEM_Fc94396f4_D_0018A0E0, parameter);
        }
        LVL_5_FELTZIN_SYSTEM_Fc94396f4_FUN_002EC458(second, source, 0.0f);
        LVL_5_FELTZIN_SYSTEM_Fc94396f4_FUN_002EC3D8(destination, destination, 0.0f);
        LVL_5_FELTZIN_SYSTEM_Fc94396f4_FUN_00306630(destination, destination, second);
        LVL_5_FELTZIN_SYSTEM_Fc94396f4_FUN_00306630(destination, destination, first);
        return;
    default:
        return;
    }
}
extern int LVL_5_FELTZIN_SYSTEM_F3c007b59_FUN_003062D0(void *p);
extern void LVL_5_FELTZIN_SYSTEM_F3c007b59_FUN_003423C8(void *p);
extern unsigned int LVL_5_FELTZIN_SYSTEM_F3c007b59_FUN_00307778(float x);

#ifndef RAC2_T_OBJ_F3C007B59
#define RAC2_T_OBJ_F3C007B59
typedef struct {
    unsigned char pad0[4];
    unsigned int w04;
    unsigned char c08;
    unsigned char c09;
    unsigned char c10;
    unsigned char c11;
    float f12;
    unsigned char pad16[8];
    float f24;
    unsigned char pad28[4];
    float f36;
    float f40;
    float f44;
} OBJ_F3c007b59;
#endif


void LVL_5_FELTZIN_SYSTEM_FUN_003465E0(OBJ_F3c007b59 *o)
{
    float *p = (float *)((char *)o + 32);
    float f;
    float y;

    f = p[1] + p[3] * 1.3000000268220901489258e-02f;
    p[1] = f;
    if (f <= 0.0f || LVL_5_FELTZIN_SYSTEM_F3c007b59_FUN_003062D0(&o->c10) != 0) {
        LVL_5_FELTZIN_SYSTEM_F3c007b59_FUN_003423C8(o);
    } else {
        f = p[1];
        if (2.1999999880790710449219e-01f <= f) {
            y = p[3];
            y = -y;
            p[3] = y;
            p[1] = f + y * 1.3000000268220901489258e-02f;
        }
        o->f12 = o->f12 + 8.1900000000000000000000e+03f;
        o->w04 = (o->w04 & 0xFFFFFFu) |
                 (LVL_5_FELTZIN_SYSTEM_F3c007b59_FUN_00307778(p[1] * 2.5500000000000000000000e+02f) << 24);
        p[2] = p[2] + 1.2000000104308128356934e-02f;
        if (p[2] > 1.0f)
            p[2] = p[2] - 1.0f;
        o->c08 = (unsigned char)(p[2] * 2.5500000000000000000000e+02f);
        o->f24 = o->f24 - 1.9999999552965164184570e-02f;
    }
}
extern void LVL_5_FELTZIN_SYSTEM_F043c77a5_FUN_00433400(void *dst);
extern long long LVL_5_FELTZIN_SYSTEM_F043c77a5_FUN_002FEF40(int id);
extern float LVL_5_FELTZIN_SYSTEM_F043c77a5_FUN_00306CD0(float x, float y);
extern float LVL_5_FELTZIN_SYSTEM_F043c77a5_FUN_00306790(void *vec);
extern void LVL_5_FELTZIN_SYSTEM_F043c77a5_FUN_00306E98(void *dst, void *src);
extern void LVL_5_FELTZIN_SYSTEM_F043c77a5_FUN_003066A0(void *dst, void *src, float scale);
extern void LVL_5_FELTZIN_SYSTEM_F043c77a5_FUN_00303910(void *dst, void *src, int flag);

#ifndef RAC2_T_BLOCK_F043C77A5
#define RAC2_T_BLOCK_F043C77A5
typedef struct { int q[4]; } BLOCK_F043c77a5;
#endif


#ifndef RAC2_T_LOC_F043C77A5
#define RAC2_T_LOC_F043C77A5
typedef struct {
    BLOCK_F043c77a5 b0;
    BLOCK_F043c77a5 b1;
    BLOCK_F043c77a5 b2;
    BLOCK_F043c77a5 b3;
    int   k0, k1, k2, k3;
    int   z80, z84, z88;
    float f92, f96;
    int   z100;
    float f104, f108;
    long long v112;
    long long v120;
    long long v128;
    long long v136;
    float m00, m01, m02, m03;
    float m10, m11, m12, m13;
    float m20, m21, m22, m23;
    float v192, v196, v200, v204;
    float v208, f212, f216, v220;
} LOC_F043c77a5;
#endif


void LVL_5_FELTZIN_SYSTEM_FUN_00434668(void *unused, float *b, float *a, int k, float f)
{
    LOC_F043c77a5 local;
    float x;

    LVL_5_FELTZIN_SYSTEM_F043c77a5_FUN_00433400(&local);
    local.z80 = 0;
    local.f92 = 1.0f;
    local.f96 = 1.0f;
    local.f104 = 1.0f;
    local.f108 = 1.0f;
    local.z84 = 0;
    local.z88 = 0;
    local.z100 = 0;
    local.v120 = LVL_5_FELTZIN_SYSTEM_F043c77a5_FUN_002FEF40(11);
    local.v128 = 0xFF9000000260LL;
    local.v136 = 0x0000008000000048LL;
    local.k3 = k;
    local.k2 = k;
    local.k1 = k;
    local.k0 = k;
    local.v112 = 0;
    local.v220 = 0.0f;
    local.f216 = LVL_5_FELTZIN_SYSTEM_F043c77a5_FUN_00306CD0(a[0], a[1]);
    x = LVL_5_FELTZIN_SYSTEM_F043c77a5_FUN_00306CD0(LVL_5_FELTZIN_SYSTEM_F043c77a5_FUN_00306790(a), a[2]);
    local.f212 = -x;
    local.v208 = 0.0f;
    LVL_5_FELTZIN_SYSTEM_F043c77a5_FUN_00306E98(&local.m00, &local.v208);
    local.v192 = b[0];
    local.v196 = b[1];
    local.v200 = b[2];
    local.v204 = 1.0f;
    LVL_5_FELTZIN_SYSTEM_F043c77a5_FUN_003066A0(&local.b0, &local.b0, f);
    LVL_5_FELTZIN_SYSTEM_F043c77a5_FUN_003066A0(&local.b1, &local.b1, f);
    LVL_5_FELTZIN_SYSTEM_F043c77a5_FUN_003066A0(&local.b2, &local.b2, f);
    LVL_5_FELTZIN_SYSTEM_F043c77a5_FUN_003066A0(&local.b3, &local.b3, f);
    LVL_5_FELTZIN_SYSTEM_F043c77a5_FUN_00303910(&local, &local.m00, 0);
}
extern int LVL_5_FELTZIN_SYSTEM_F7cacd225_FUN_003062D0(short *p);
extern void LVL_5_FELTZIN_SYSTEM_F7cacd225_FUN_003423C8(char *o);
extern float LVL_5_FELTZIN_SYSTEM_F7cacd225_FUN_00307768(int n);
extern float LVL_5_FELTZIN_SYSTEM_F7cacd225_FUN_00307768(int n);
extern int LVL_5_FELTZIN_SYSTEM_F7cacd225_FUN_003077C0(int a, int b, float q);

#ifndef RAC2_T_OBJ_F7CACD225
#define RAC2_T_OBJ_F7CACD225
typedef struct {
    int pad0;
    int f4;
    short pad8;
    short s10;
    float f12;
    float f16;
    float f20;
    float f24;
    int pad28;
    int f32;
} Obj_F7cacd225;
#endif


void LVL_5_FELTZIN_SYSTEM_FUN_0034F290(Obj_F7cacd225 *o)
{
    int v;

    if (o->f16 < 2.0f || o->f16 > 1021.0f ||
        o->f20 < 2.0f || o->f20 > 1021.0f ||
        o->f24 < 2.0f || o->f24 > 1021.0f ||
        LVL_5_FELTZIN_SYSTEM_F7cacd225_FUN_003062D0(&o->s10) != 0) {
        LVL_5_FELTZIN_SYSTEM_F7cacd225_FUN_003423C8((char *)o);
        return;
    }
    v = o->f32;
    if (v != 0) {
        o->f12 = o->f12 * 0.99f;
        o->f4 = LVL_5_FELTZIN_SYSTEM_F7cacd225_FUN_003077C0(0x30FFFFFF, o->f4, LVL_5_FELTZIN_SYSTEM_F7cacd225_FUN_00307768(o->s10 - 1) / LVL_5_FELTZIN_SYSTEM_F7cacd225_FUN_00307768(o->s10));
    } else {
        o->f12 = o->f12 * 0.95f;
        o->f4 = LVL_5_FELTZIN_SYSTEM_F7cacd225_FUN_003077C0(0x603F1008, o->f4, LVL_5_FELTZIN_SYSTEM_F7cacd225_FUN_00307768(o->s10 - 1) / LVL_5_FELTZIN_SYSTEM_F7cacd225_FUN_00307768(o->s10));
    }
}
extern float LVL_5_FELTZIN_SYSTEM_Ff454dd77_FUN_003065A0(float a);
extern float LVL_5_FELTZIN_SYSTEM_Ff454dd77_FUN_003065A0(float a);
extern float LVL_5_FELTZIN_SYSTEM_Ff454dd77_FUN_003065A0(float a);
extern float LVL_5_FELTZIN_SYSTEM_Ff454dd77_FUN_003065A0(float a);
extern float LVL_5_FELTZIN_SYSTEM_Ff454dd77_FUN_003065A0(float a);
extern float LVL_5_FELTZIN_SYSTEM_Ff454dd77_FUN_003065A0(float a);
extern float LVL_5_FELTZIN_SYSTEM_Ff454dd77_FUN_003065A0(float a);
extern float LVL_5_FELTZIN_SYSTEM_Ff454dd77_FUN_003065A0(float a);

#ifndef RAC2_T_OBJ_FF454DD77
#define RAC2_T_OBJ_FF454DD77
typedef struct {
    float f0;
} Obj_Ff454dd77;
#endif


void LVL_5_FELTZIN_SYSTEM_FUN_003357F0(Obj_Ff454dd77 *o, float a, float b, float c, float d)
{
    if (LVL_5_FELTZIN_SYSTEM_Ff454dd77_FUN_003065A0(a) < o->f0)
        o->f0 = LVL_5_FELTZIN_SYSTEM_Ff454dd77_FUN_003065A0(a);
    else if (o->f0 < -LVL_5_FELTZIN_SYSTEM_Ff454dd77_FUN_003065A0(a))
        o->f0 = -LVL_5_FELTZIN_SYSTEM_Ff454dd77_FUN_003065A0(a);

    o->f0 = o->f0 + (b * a - c * o->f0);
    if (0.0f < d) {
        if (d < o->f0)
            o->f0 = d;
        else if (o->f0 < -d)
            o->f0 = -d;
    }

    if (LVL_5_FELTZIN_SYSTEM_Ff454dd77_FUN_003065A0(a) < o->f0)
        o->f0 = LVL_5_FELTZIN_SYSTEM_Ff454dd77_FUN_003065A0(a);
    else if (o->f0 < -LVL_5_FELTZIN_SYSTEM_Ff454dd77_FUN_003065A0(a))
        o->f0 = -LVL_5_FELTZIN_SYSTEM_Ff454dd77_FUN_003065A0(a);
}
#ifndef RAC2_T_V4_F5621621C
#define RAC2_T_V4_F5621621C
typedef int V4_F5621621c __attribute__((mode(TI)));
#endif


extern float LVL_5_FELTZIN_SYSTEM_F5621621c_FUN_00306CD0(float a, float b);
extern float LVL_5_FELTZIN_SYSTEM_F5621621c_FUN_00306C08(float a);
extern float LVL_5_FELTZIN_SYSTEM_F5621621c_FUN_00306C20(float a);
extern void LVL_5_FELTZIN_SYSTEM_F5621621c_FUN_00334368(int v, void *rec);

#ifndef RAC2_T_VEC16_F5621621C
#define RAC2_T_VEC16_F5621621C
typedef struct {
    float x;
    float y;
    float z;
    float w;
} Vec16_F5621621c;
#endif


#ifndef RAC2_T_NODE_F5621621C
#define RAC2_T_NODE_F5621621C
typedef struct {
    char pad[16];
    float f16;
    float f20;
} Node_F5621621c;
#endif


#ifndef RAC2_T_REC_F5621621C
#define RAC2_T_REC_F5621621C
typedef struct {
    float f0;
    float f4;
    float f8;
    float f12;
    int i16;
    int i20;
    signed char b24;
    signed char b25;
    unsigned short h26;
    float f28;
    int i32;
} Rec_F5621621c;
#endif


void LVL_5_FELTZIN_SYSTEM_FUN_00334D20(void *a0, Vec16_F5621621c *src, int *p, int n,
                                        int t0, int t1, int t2, int t3,
                                        float f1, float f2, float f3)
{
    Vec16_F5621621c vec;
    Vec16_F5621621c *vp = &vec;
    Rec_F5621621c rec;
    int i;
    int *q;

    *(V4_F5621621c *)&vec = *(V4_F5621621c *)src;
    if (n <= 0) return;
    for (q = p, i = n; i != 0; i--, q++) {
        Node_F5621621c *v = (Node_F5621621c *)*q;
        float t;
        if ((int)*q == t0) continue;
        rec.i16 = (int)a0;
        rec.h26 = *(unsigned short *)((char *)a0 + 170);
        rec.i20 = t1;
        rec.f28 = f1;
        rec.i32 = t1;
        rec.b24 = t2;
        rec.b25 = t3;
        t = LVL_5_FELTZIN_SYSTEM_F5621621c_FUN_00306CD0(v->f16 - vp->x, v->f20 - vp->y);
        rec.f0 = LVL_5_FELTZIN_SYSTEM_F5621621c_FUN_00306C08(t) * f2;
        rec.f4 = LVL_5_FELTZIN_SYSTEM_F5621621c_FUN_00306C20(t) * f2;
        rec.f8 = f3;
        rec.f12 = 5.6279248046875000000000e3f;
        LVL_5_FELTZIN_SYSTEM_F5621621c_FUN_00334368(*q, &rec);
    }
}
extern void LVL_5_FELTZIN_SYSTEM_F966dbf73_FUN_00332AB8(int a);
extern void LVL_5_FELTZIN_SYSTEM_F966dbf73_FUN_00332AB8(int a);
extern float LVL_5_FELTZIN_SYSTEM_F966dbf73_FUN_00332B50(float a, float b);
extern unsigned int LVL_5_FELTZIN_SYSTEM_F966dbf73_FUN_00332AF8(int a, int b);
extern void LVL_5_FELTZIN_SYSTEM_F966dbf73_FUN_00332CD8(char *p, float a, float b);
extern char *LVL_5_FELTZIN_SYSTEM_F966dbf73_FUN_00347040(float fa, float fb, float fc, float fd, char *p, int z,
                     char *local, unsigned int v, int one);

void LVL_5_FELTZIN_SYSTEM_FUN_003D6C30(char *unused, char *arg)
{
    char local[16];
    float f;
    int i;
    unsigned int v;
    unsigned int w;
    unsigned int x;
    char *r;

    i = 19;
    do {
        LVL_5_FELTZIN_SYSTEM_F966dbf73_FUN_00332AB8(2);
        i = i - 1;
        LVL_5_FELTZIN_SYSTEM_F966dbf73_FUN_00332AB8(2);
        f = LVL_5_FELTZIN_SYSTEM_F966dbf73_FUN_00332B50(70000.0f, 150000.0f);
        v = LVL_5_FELTZIN_SYSTEM_F966dbf73_FUN_00332AF8(10, 127);
        w = (v << 8) | 0x7f000000U;
        x = (v << 16) | w;
        v = x | v;
        LVL_5_FELTZIN_SYSTEM_F966dbf73_FUN_00332CD8(local, 1.6666668670950457453728e-05f,
                6.6666672937572002410889e-03f);
        r = LVL_5_FELTZIN_SYSTEM_F966dbf73_FUN_00347040(0.3f, 1.0f, 1.01f, f, arg, 0, local, v, 1);
        if (r != 0) {
            char *q = r + 32;

            *(short *)(r + 10) = 120;
            *(int *)(q + 4) = 2;
            *(char *)(q + 10) = 127;
            *(char *)(q + 11) = *(unsigned char *)(r + 10);
        }
    } while (i >= 0);
}
extern char LVL_5_FELTZIN_SYSTEM_F024e7577_D_00189E20[];
extern float LVL_5_FELTZIN_SYSTEM_F024e7577_FUN_00335940(float *p, float a, float b);

void LVL_5_FELTZIN_SYSTEM_FUN_002C25B8(float *a0, float *a1, float f12)
{
    char *base = LVL_5_FELTZIN_SYSTEM_F024e7577_D_00189E20;
    float v[2];

    v[0] = -*(float *)(base + 8112);
    v[1] = *(float *)(base + 8116);
    LVL_5_FELTZIN_SYSTEM_F024e7577_FUN_00335940(a1 + 2, v[0], f12);
    if (a1[2] > 1.0f) a1[2] = 1.0f;
    if (a1[2] < -1.0f) a1[2] = -1.0f;
    a0[0] = a1[2];
    LVL_5_FELTZIN_SYSTEM_F024e7577_FUN_00335940(a1 + 1, v[1], f12);
    if (a1[1] > 1.0f) a1[1] = 1.0f;
    if (a1[1] < -1.0f) a1[1] = -1.0f;
    a0[1] = a1[1];
}
extern float LVL_5_FELTZIN_SYSTEM_F229bff2f_FUN_003065A0(float t);

float LVL_5_FELTZIN_SYSTEM_FUN_002F0270(float *p, float a, float b, float c, float d, float lim)
{
    float t = b - a;
    float x = *p;
    float r;

    x += c * t - d * x;
    *p = x;
    if (lim != 0.0f) {
        if (x > lim) *p = lim;
        else if (x < -lim) *p = -lim;
    }
    r = LVL_5_FELTZIN_SYSTEM_F229bff2f_FUN_003065A0(t);
    if (r < *p) {
        *p = LVL_5_FELTZIN_SYSTEM_F229bff2f_FUN_003065A0(t);
    } else {
        float s = -LVL_5_FELTZIN_SYSTEM_F229bff2f_FUN_003065A0(t);
        if (*p < s) {
            *p = -LVL_5_FELTZIN_SYSTEM_F229bff2f_FUN_003065A0(t);
        }
    }
    return a + *p;
}
#ifndef RAC2_T_S_F49AFCBFE
#define RAC2_T_S_F49AFCBFE
typedef struct {
    float f0;
    float f4;
    float f8;
    float f12;
    float f16;
    int i20;
    float f24;
    int i28;
    int i32;
    int i36;
    int i40;
} S_F49afcbfe;
#endif


extern void LVL_5_FELTZIN_SYSTEM_F49afcbfe_FUN_0045AA98(S_F49afcbfe *x, int a, int b, float p, float q, float r, float s);

void LVL_5_FELTZIN_SYSTEM_FUN_0045A998(S_F49afcbfe *x)
{
    float z;

    x->f0 = 1.0f;
    x->f4 = 1.0f;
    x->f8 = 1.0f;
    x->f12 = 1.0f;
    x->f16 = 0.0f;
    x->f24 = 6.6665999591350555419922e-02f;
    x->i28 = 0;
    x->i32 = 0;
    x->i36 = 0;
    x->i40 = 0;
    z = x->f16;
    LVL_5_FELTZIN_SYSTEM_F49afcbfe_FUN_0045AA98(x, 0, 0, z, z, z, z);
    LVL_5_FELTZIN_SYSTEM_F49afcbfe_FUN_0045AA98(x, 0, 1, z, z, z, z);
    LVL_5_FELTZIN_SYSTEM_F49afcbfe_FUN_0045AA98(x, 1, 0, z, z, z, z);
    LVL_5_FELTZIN_SYSTEM_F49afcbfe_FUN_0045AA98(x, 1, 1, z, z, z, z);
}
extern void LVL_5_FELTZIN_SYSTEM_Fa6f6f46f_FUN_003070E0(char *a, char *b);
extern void LVL_5_FELTZIN_SYSTEM_Fa6f6f46f_FUN_0032E728(char *a, int b, int c, char *d);
extern void LVL_5_FELTZIN_SYSTEM_Fa6f6f46f_FUN_00307210(char *a, char *b, char *c);
extern void LVL_5_FELTZIN_SYSTEM_Fa6f6f46f_FUN_003066A0(char *a, char *b, float c);
extern void LVL_5_FELTZIN_SYSTEM_Fa6f6f46f_FUN_00306630(char *a, char *b, char *c);

void LVL_5_FELTZIN_SYSTEM_FUN_00329A88(char *a0, int n, int a2, char *a3)
{
    char buf[64];
    float f20;
    int i;

    f20 = *(float *)(a0 + 44) * 0.0009765625f;
    LVL_5_FELTZIN_SYSTEM_Fa6f6f46f_FUN_003070E0(buf, a0 + 192);
    LVL_5_FELTZIN_SYSTEM_Fa6f6f46f_FUN_0032E728(a0, n, a2, a3);
    for (i = 0; i < n; i++) {
        LVL_5_FELTZIN_SYSTEM_Fa6f6f46f_FUN_00307210(a3 + i * 64, buf, a3 + i * 64);
        LVL_5_FELTZIN_SYSTEM_Fa6f6f46f_FUN_003066A0(a3 + i * 64 + 48, a3 + i * 64 + 48, f20);
        LVL_5_FELTZIN_SYSTEM_Fa6f6f46f_FUN_00306630(a3 + i * 64 + 48, a3 + i * 64 + 48, a0 + 16);
    }
}
extern char LVL_5_FELTZIN_SYSTEM_F8a447ea5_D_001ABE10[];
extern void LVL_5_FELTZIN_SYSTEM_F8a447ea5_FUN_002FEC08(int a);
extern void LVL_5_FELTZIN_SYSTEM_F8a447ea5_FUN_00301E90(int a, int b, long long c, char *d, int e);
extern int LVL_5_FELTZIN_SYSTEM_F8a447ea5_FUN_003123B8(int a, int b);
extern int LVL_5_FELTZIN_SYSTEM_F8a447ea5_FUN_00312470(int a);
extern void LVL_5_FELTZIN_SYSTEM_F8a447ea5_FUN_00313240(float f12, float f13, float f14, float f15, float f16, int a, int b, int c);
extern void LVL_5_FELTZIN_SYSTEM_F8a447ea5_FUN_00301E90(int a, int b, long long c, char *d, int e);
extern int LVL_5_FELTZIN_SYSTEM_F8a447ea5_FUN_003123B8(int a, int b);
extern int LVL_5_FELTZIN_SYSTEM_F8a447ea5_FUN_00312470(int a);
extern void LVL_5_FELTZIN_SYSTEM_F8a447ea5_FUN_00313240(float f12, float f13, float f14, float f15, float f16, int a, int b, int c);
extern void LVL_5_FELTZIN_SYSTEM_F8a447ea5_FUN_002FED28(void);

struct Wave8a447eaPair { signed char a; signed char b; };

int LVL_5_FELTZIN_SYSTEM_FUN_00367A48(int *a0)
{
    char buf[16];
    float f20;
    int x;

    LVL_5_FELTZIN_SYSTEM_F8a447ea5_FUN_002FEC08(0);
    if (a0[14] != 0) {
        *(struct Wave8a447eaPair *)buf = *(struct Wave8a447eaPair *)LVL_5_FELTZIN_SYSTEM_F8a447ea5_D_001ABE10;
        LVL_5_FELTZIN_SYSTEM_F8a447ea5_FUN_00301E90(4, a0[9] / 2 - 8, 0x80FFA888LL, buf, -1);
        f20 = (float)(a0[9] << 3);
        x = LVL_5_FELTZIN_SYSTEM_F8a447ea5_FUN_003123B8(0xe99d, 6);
        x = LVL_5_FELTZIN_SYSTEM_F8a447ea5_FUN_00312470(x);
        LVL_5_FELTZIN_SYSTEM_F8a447ea5_FUN_00313240(640.0f, f20, 128.0f, 256.0f, 0.0f, 32, 16, x);
    } else {
        *(struct Wave8a447eaPair *)buf = *(struct Wave8a447eaPair *)(LVL_5_FELTZIN_SYSTEM_F8a447ea5_D_001ABE10 + 8);
        LVL_5_FELTZIN_SYSTEM_F8a447ea5_FUN_00301E90(a0[8] - 24, a0[9] / 2 - 8, 0x80FFA888LL, buf, -1);
        f20 = (float)(a0[9] << 3);
        x = LVL_5_FELTZIN_SYSTEM_F8a447ea5_FUN_003123B8(0xe99d, 6);
        x = LVL_5_FELTZIN_SYSTEM_F8a447ea5_FUN_00312470(x);
        LVL_5_FELTZIN_SYSTEM_F8a447ea5_FUN_00313240(192.0f, f20, 128.0f, 256.0f, 3.1415927f, 32, 16, x);
    }
    LVL_5_FELTZIN_SYSTEM_F8a447ea5_FUN_002FED28();
    return 2;
}
extern int LVL_5_FELTZIN_SYSTEM_F33c6e7a2_D_001A8FF0 __attribute__((sda));
extern int LVL_5_FELTZIN_SYSTEM_F33c6e7a2_D_001A8FF4 __attribute__((sda));
extern char LVL_5_FELTZIN_SYSTEM_F33c6e7a2_D_00189E20[];
extern void LVL_5_FELTZIN_SYSTEM_F33c6e7a2_FUN_00306608(char *a);
extern void LVL_5_FELTZIN_SYSTEM_F33c6e7a2_FUN_0033C380(char *a, char *b, int c);
extern void LVL_5_FELTZIN_SYSTEM_F33c6e7a2_FUN_00306660(char *a, char *b, char *c);
extern void LVL_5_FELTZIN_SYSTEM_F33c6e7a2_FUN_003068F8(char *a, char *b, float f12);
extern void LVL_5_FELTZIN_SYSTEM_F33c6e7a2_FUN_003066A0(char *a, char *b, float f12);

void LVL_5_FELTZIN_SYSTEM_FUN_0033C3F8(char *a0, char *a1, int a2)
{
    char *p;
    float f20;

    if (LVL_5_FELTZIN_SYSTEM_F33c6e7a2_D_001A8FF0 == 0) {
        LVL_5_FELTZIN_SYSTEM_F33c6e7a2_FUN_00306608(a1);
    } else if (LVL_5_FELTZIN_SYSTEM_F33c6e7a2_D_001A8FF4 != 0) {
        LVL_5_FELTZIN_SYSTEM_F33c6e7a2_FUN_0033C380(a0, a1, 1);
    } else {
        p = LVL_5_FELTZIN_SYSTEM_F33c6e7a2_D_00189E20;
        f20 = 1.0f;
        if (0.0f < *(float *)(p + 188))
            f20 = -1.0f;
        LVL_5_FELTZIN_SYSTEM_F33c6e7a2_FUN_00306660(a1, p + 176, a0);
        LVL_5_FELTZIN_SYSTEM_F33c6e7a2_FUN_003068F8(a1, a1, f20);
    }
    if (a2 == 0)
        LVL_5_FELTZIN_SYSTEM_F33c6e7a2_FUN_003066A0(a1, a1, -1.0f);
}
extern int LVL_5_FELTZIN_SYSTEM_F5ac03a17_FUN_003062D0(char *p);
extern void LVL_5_FELTZIN_SYSTEM_F5ac03a17_FUN_003423C8(char *p);
extern int LVL_5_FELTZIN_SYSTEM_F5ac03a17_FUN_00307778(float f);
extern int LVL_5_FELTZIN_SYSTEM_F5ac03a17_FUN_00307778(float f);
extern void LVL_5_FELTZIN_SYSTEM_F5ac03a17_FUN_00306630(char *a, char *b, char *c);
extern void LVL_5_FELTZIN_SYSTEM_F5ac03a17_FUN_003066A0(char *a, char *b, float f);

void LVL_5_FELTZIN_SYSTEM_FUN_00344DB8(char *p)
{
    char *q = p + 32;
    float v;
    int a, b;
    int h;

    v = *(float *)(q + 28) + (-0.04f);
    *(float *)(q + 28) = v;
    if (v <= 0.0f || LVL_5_FELTZIN_SYSTEM_F5ac03a17_FUN_003062D0(p + 10) != 0) {
        LVL_5_FELTZIN_SYSTEM_F5ac03a17_FUN_003423C8(p);
        return;
    }
    *(float *)(p + 12) = *(float *)(p + 12) + 12000.0f;
    if (*(float *)(q + 24) < 0.225f) {
        *(float *)(q + 24) = *(float *)(q + 24) + 0.0484f;
    }
    a = LVL_5_FELTZIN_SYSTEM_F5ac03a17_FUN_00307778(*(float *)(q + 24) * 255.0f) & 0xff;
    b = LVL_5_FELTZIN_SYSTEM_F5ac03a17_FUN_00307778(*(float *)(q + 28) * 255.0f);
    h = *(unsigned short *)(p + 4);
    *(int *)(p + 4) = h | (a << 16) | (b << 24);
    LVL_5_FELTZIN_SYSTEM_F5ac03a17_FUN_00306630(p + 16, p + 16, q);
    LVL_5_FELTZIN_SYSTEM_F5ac03a17_FUN_003066A0(q, q, 0.9f);
    *(char *)(p + 8) = *(unsigned char *)(p + 8) - 1;
}
extern void LVL_5_FELTZIN_SYSTEM_F1fd779a1_FUN_0032E728(char *p, int one, int *w, char *out);
extern void LVL_5_FELTZIN_SYSTEM_F1fd779a1_FUN_003066A0(char *a, char *out, float f);
extern void LVL_5_FELTZIN_SYSTEM_F1fd779a1_FUN_00306630(char *a, char *b, char *c);
extern void LVL_5_FELTZIN_SYSTEM_F1fd779a1_FUN_00306AD8(char *a, char *b, char *c);

void LVL_5_FELTZIN_SYSTEM_FUN_003B7F40(char *p, int v, char *a, char *b)
{
    char out0[48];
    char out48[16];
    int w;
    float f;

    f = *(float *)(p + 44) * 0.0009765625f;
    w = v;
    LVL_5_FELTZIN_SYSTEM_F1fd779a1_FUN_0032E728(p, 1, &w, out0);
    LVL_5_FELTZIN_SYSTEM_F1fd779a1_FUN_003066A0(a, out48, f);
    LVL_5_FELTZIN_SYSTEM_F1fd779a1_FUN_00306630(a, a, b);
    LVL_5_FELTZIN_SYSTEM_F1fd779a1_FUN_00306AD8(a, a, p + 192);
    LVL_5_FELTZIN_SYSTEM_F1fd779a1_FUN_00306630(a, a, p + 16);
}
extern void LVL_5_FELTZIN_SYSTEM_F1fd779a1_FUN_0032E728(char *p, int one, int *w, char *out);
extern void LVL_5_FELTZIN_SYSTEM_F1fd779a1_FUN_003066A0(char *a, char *out, float f);
extern void LVL_5_FELTZIN_SYSTEM_F1fd779a1_FUN_00306630(char *a, char *b, char *c);
extern void LVL_5_FELTZIN_SYSTEM_F1fd779a1_FUN_00306AD8(char *a, char *b, char *c);

void LVL_5_FELTZIN_SYSTEM_FUN_003F22B0(char *p, int v, char *a, char *b)
{
    char out0[48];
    char out48[16];
    int w;
    float f;

    f = *(float *)(p + 44) * 0.0009765625f;
    w = v;
    LVL_5_FELTZIN_SYSTEM_F1fd779a1_FUN_0032E728(p, 1, &w, out0);
    LVL_5_FELTZIN_SYSTEM_F1fd779a1_FUN_003066A0(a, out48, f);
    LVL_5_FELTZIN_SYSTEM_F1fd779a1_FUN_00306630(a, a, b);
    LVL_5_FELTZIN_SYSTEM_F1fd779a1_FUN_00306AD8(a, a, p + 192);
    LVL_5_FELTZIN_SYSTEM_F1fd779a1_FUN_00306630(a, a, p + 16);
}
extern float LVL_5_FELTZIN_SYSTEM_F4a600262_FUN_00307768(int a);
extern int LVL_5_FELTZIN_SYSTEM_F4a600262_FUN_00307778(float f);
extern int LVL_5_FELTZIN_SYSTEM_F4a600262_FUN_003077C0(int a, int b, float f);
extern float LVL_5_FELTZIN_SYSTEM_F4a600262_FUN_00332B50(float a, float b);
extern void LVL_5_FELTZIN_SYSTEM_F4a600262_FUN_00306630(char *a, char *b, char *c);
extern void LVL_5_FELTZIN_SYSTEM_F4a600262_FUN_003066A0(char *a, char *b, float f);
extern void LVL_5_FELTZIN_SYSTEM_F4a600262_FUN_00394B90(char *a, char *b);
extern void LVL_5_FELTZIN_SYSTEM_F4a600262_FUN_00394C48(char *a, char *b);
extern int LVL_5_FELTZIN_SYSTEM_F4a600262_FUN_003062D0(char *p);
extern void LVL_5_FELTZIN_SYSTEM_F4a600262_FUN_003423C8(char *p);

void LVL_5_FELTZIN_SYSTEM_FUN_00353E58(char *p)
{
    char *s0 = p + 32;
    char *s3 = p + 16;
    float r1, r2, r3, r4;
    int x, y;

    r1 = LVL_5_FELTZIN_SYSTEM_F4a600262_FUN_00307768(*(short *)(p + 10));
    r2 = LVL_5_FELTZIN_SYSTEM_F4a600262_FUN_00307768(*(int *)(s0 + 24));
    r1 = r1 / r2;
    r3 = LVL_5_FELTZIN_SYSTEM_F4a600262_FUN_00307768(*(int *)(s0 + 16));
    x = LVL_5_FELTZIN_SYSTEM_F4a600262_FUN_00307778(r3 * r1);
    y = LVL_5_FELTZIN_SYSTEM_F4a600262_FUN_003077C0(0, *(int *)(s0 + 20), r1 * 0.5f);
    *(char *)(p + 8) = *(unsigned char *)(p + 8) + 1;
    r4 = LVL_5_FELTZIN_SYSTEM_F4a600262_FUN_00332B50(0.004f, 0.012f);
    *(float *)(p + 12) = *(float *)(p + 12) + r4 * 210000.0f;
    LVL_5_FELTZIN_SYSTEM_F4a600262_FUN_00306630(s3, s3, s0);
    LVL_5_FELTZIN_SYSTEM_F4a600262_FUN_003066A0(s0, s0, 0.99f);
    LVL_5_FELTZIN_SYSTEM_F4a600262_FUN_00394B90(s3, s3);
    LVL_5_FELTZIN_SYSTEM_F4a600262_FUN_00394C48(s0, s0);
    *(int *)(p + 4) = y | (x << 24);
    if (LVL_5_FELTZIN_SYSTEM_F4a600262_FUN_003062D0(p + 10) != 0) {
        LVL_5_FELTZIN_SYSTEM_F4a600262_FUN_003423C8(p);
    }
}
extern void LVL_5_FELTZIN_SYSTEM_F0cbe9be2_FUN_002CC270(int arg0, float arg1);
extern float LVL_5_FELTZIN_SYSTEM_F0cbe9be2_FUN_002D23B8(char *arg0, int arg1);
extern float LVL_5_FELTZIN_SYSTEM_F0cbe9be2_FUN_00307668(float arg0, float arg1);
extern float LVL_5_FELTZIN_SYSTEM_F0cbe9be2_FUN_00307708(float arg0, float arg1);
extern char LVL_5_FELTZIN_SYSTEM_F0cbe9be2_D_00189E20[];

int LVL_5_FELTZIN_SYSTEM_FUN_002DC2F8(void)
{
    char *p = LVL_5_FELTZIN_SYSTEM_F0cbe9be2_D_00189E20;
    float value;
    int result;
    int state;

    result = 2;
    if (*(short *)(p + 5204) != 0) {
        state = *(unsigned char *)(p + 5207);
        if (state == 0)
            result = 0;
        else if (state == 3)
            result = 3;
        else if (state == 2)
            result = 2;
        else
            result = 1;
    } else {
        LVL_5_FELTZIN_SYSTEM_F0cbe9be2_FUN_002CC270(0, 1.0f);
        if (*(unsigned char *)(p + 8899) != 0)
            value = LVL_5_FELTZIN_SYSTEM_F0cbe9be2_FUN_002D23B8(p + 400, 0);
        else
            value = LVL_5_FELTZIN_SYSTEM_F0cbe9be2_FUN_00307668(*(float *)(p + 416), *(float *)(p + 152));
        if (LVL_5_FELTZIN_SYSTEM_F0cbe9be2_FUN_00307708(value, 3.1415929794311523437500e+00f) < 7.8539824485778808593750e-01f)
            result = 3;
        else if (LVL_5_FELTZIN_SYSTEM_F0cbe9be2_FUN_00307708(value, -1.5707964897155761718750e+00f) < 7.8539824485778808593750e-01f)
            result = 1;
        else if (LVL_5_FELTZIN_SYSTEM_F0cbe9be2_FUN_00307708(value, 1.5707964897155761718750e+00f) < 7.8539824485778808593750e-01f)
            result = 0;
    }
    return result;
}
extern void LVL_5_FELTZIN_SYSTEM_Ffea5082f_FUN_00306A68(void *a, void *b, void *c);
extern float LVL_5_FELTZIN_SYSTEM_Ffea5082f_FUN_00306760(void *a);
extern float LVL_5_FELTZIN_SYSTEM_Ffea5082f_FUN_00306720(void *a, void *b);
extern void LVL_5_FELTZIN_SYSTEM_Ffea5082f_FUN_00335940(float *p, float a, float b);
extern void LVL_5_FELTZIN_SYSTEM_Ffea5082f_FUN_003068F8(void *a, void *b, float f);

int LVL_5_FELTZIN_SYSTEM_FUN_002F5600(void *p, void *q, void *r, float f12, float f13)
{
    float saved;
    float t;
    float v;

    LVL_5_FELTZIN_SYSTEM_Ffea5082f_FUN_00306A68(p, p, q);
    saved = LVL_5_FELTZIN_SYSTEM_Ffea5082f_FUN_00306760(p);
    v = LVL_5_FELTZIN_SYSTEM_Ffea5082f_FUN_00306720(r, q);
    if (v > 0.7f) {
        t = saved * f12;
        if (t < f13) t = f13;
        LVL_5_FELTZIN_SYSTEM_Ffea5082f_FUN_00335940(&saved, 0.0f, t);
        LVL_5_FELTZIN_SYSTEM_Ffea5082f_FUN_003068F8(p, p, saved);
    }
    if (saved != 0.0f) return 1;
    return 0;
}
extern float LVL_5_FELTZIN_SYSTEM_F118c2370_FUN_00332C18(void);
extern float LVL_5_FELTZIN_SYSTEM_F118c2370_FUN_00332B50(float a, float b);
extern float LVL_5_FELTZIN_SYSTEM_F118c2370_FUN_00306C08(float a);
extern float LVL_5_FELTZIN_SYSTEM_F118c2370_FUN_00306C20(float a);
extern int LVL_5_FELTZIN_SYSTEM_F118c2370_FUN_00332AF8(int a, int b);
extern int LVL_5_FELTZIN_SYSTEM_F118c2370_FUN_00332AB8(int a);
extern void LVL_5_FELTZIN_SYSTEM_F118c2370_FUN_00349148(char *p, float *q, int a, int b);

void LVL_5_FELTZIN_SYSTEM_FUN_003EA598(char *a0)
{
    float v[3];
    float a;
    float b;
    int i;
    int m;
    int n;

    for (i = 47; i >= 0; i--) {
        a = LVL_5_FELTZIN_SYSTEM_F118c2370_FUN_00332C18();
        b = LVL_5_FELTZIN_SYSTEM_F118c2370_FUN_00332B50(0.0f, 0.050000004f);
        v[0] = LVL_5_FELTZIN_SYSTEM_F118c2370_FUN_00306C08(a) * b;
        v[1] = LVL_5_FELTZIN_SYSTEM_F118c2370_FUN_00306C20(a) * b;
        v[2] = LVL_5_FELTZIN_SYSTEM_F118c2370_FUN_00332B50(0.050000004f, 1.0833334177732467651367e-01f);
        m = LVL_5_FELTZIN_SYSTEM_F118c2370_FUN_00332AF8(90, 120);
        n = LVL_5_FELTZIN_SYSTEM_F118c2370_FUN_00332AB8(2);
        LVL_5_FELTZIN_SYSTEM_F118c2370_FUN_00349148(a0 + 16, v, n, m);
    }
}
extern float LVL_5_FELTZIN_SYSTEM_F63cf942f_FUN_00306C08(float x);
extern float LVL_5_FELTZIN_SYSTEM_F63cf942f_FUN_00307668(float a, float b);
extern float LVL_5_FELTZIN_SYSTEM_F63cf942f_FUN_00307620(float a, float b);

void LVL_5_FELTZIN_SYSTEM_FUN_003330D0(float *a0, float *a1, float *a2, float t)
{
    float k;

    k = (1.0f - LVL_5_FELTZIN_SYSTEM_F63cf942f_FUN_00306C08(t * 3.1415927f)) * 0.5f;
    a0[0] = LVL_5_FELTZIN_SYSTEM_F63cf942f_FUN_00307620(a1[0], LVL_5_FELTZIN_SYSTEM_F63cf942f_FUN_00307668(a2[0], a1[0]) * k);
    a0[1] = LVL_5_FELTZIN_SYSTEM_F63cf942f_FUN_00307620(a1[1], LVL_5_FELTZIN_SYSTEM_F63cf942f_FUN_00307668(a2[1], a1[1]) * k);
    a0[2] = LVL_5_FELTZIN_SYSTEM_F63cf942f_FUN_00307620(a1[2], LVL_5_FELTZIN_SYSTEM_F63cf942f_FUN_00307668(a2[2], a1[2]) * k);
}
extern float LVL_5_FELTZIN_SYSTEM_F846f1d58_FUN_002F0270(int *dst, float a, float b, float c, float d, float e);

void LVL_5_FELTZIN_SYSTEM_FUN_00439EE0(char *a0, float *a1, float *a2,
                                        float f12, float f13, float f14)
{
    int *p = *(int **)(a0 + 112);

    a1[0] = LVL_5_FELTZIN_SYSTEM_F846f1d58_FUN_002F0270(p + 64, a1[0], a2[0], f12, f13, f14);
    a1[1] = LVL_5_FELTZIN_SYSTEM_F846f1d58_FUN_002F0270(p + 65, a1[1], a2[1], f12, f13, f14);
    a1[2] = LVL_5_FELTZIN_SYSTEM_F846f1d58_FUN_002F0270(p + 66, a1[2], a2[2], f12, f13, f14);
}
extern char LVL_5_FELTZIN_SYSTEM_Fbfa3ff84_D_00189F80[];

extern float LVL_5_FELTZIN_SYSTEM_Fbfa3ff84_FUN_002EC2D8(void *p);
extern void LVL_5_FELTZIN_SYSTEM_Fbfa3ff84_FUN_002EC3D8(void *a, void *b, float f);
extern void LVL_5_FELTZIN_SYSTEM_Fbfa3ff84_FUN_002EC458(void *a, void *b, float f);
extern void LVL_5_FELTZIN_SYSTEM_Fbfa3ff84_FUN_00306630(void *a, void *b, void *c);
extern void LVL_5_FELTZIN_SYSTEM_Fbfa3ff84_FUN_003065F8(void *a);

void LVL_5_FELTZIN_SYSTEM_FUN_002D1D58(float a0)
{
    char *p = LVL_5_FELTZIN_SYSTEM_Fbfa3ff84_D_00189F80;
    float x = a0;
    float r = LVL_5_FELTZIN_SYSTEM_Fbfa3ff84_FUN_002EC2D8(p);
    float d;

    if (0.001f < r) {
        LVL_5_FELTZIN_SYSTEM_Fbfa3ff84_FUN_002EC3D8(p, p, 0.0f);
        d = r - x;
        if (d < 0.0f)
            d = 0.0f;
        LVL_5_FELTZIN_SYSTEM_Fbfa3ff84_FUN_002EC458(p, p, d);
        LVL_5_FELTZIN_SYSTEM_Fbfa3ff84_FUN_00306630(p - 112, p - 112, p);
    } else {
        LVL_5_FELTZIN_SYSTEM_Fbfa3ff84_FUN_003065F8(p);
    }
}
#ifndef RAC2_T_V4_FE23FE324
#define RAC2_T_V4_FE23FE324
typedef int V4_Fe23fe324 __attribute__((mode(TI)));
#endif


extern char LVL_5_FELTZIN_SYSTEM_Fe23fe324_D_00189E20[];
extern void LVL_5_FELTZIN_SYSTEM_Fe23fe324_FUN_003065F8();
extern void LVL_5_FELTZIN_SYSTEM_Fe23fe324_FUN_00306E98();
extern void LVL_5_FELTZIN_SYSTEM_Fe23fe324_FUN_00306B00();
extern void LVL_5_FELTZIN_SYSTEM_Fe23fe324_FUN_00306630();

void LVL_5_FELTZIN_SYSTEM_FUN_002EC120(V4_Fe23fe324 *a0, V4_Fe23fe324 *a1, float f)
{
    char *p = LVL_5_FELTZIN_SYSTEM_Fe23fe324_D_00189E20;
    unsigned char raw = p[8899];
    int state = raw;
    float m[4][4];
    float v[4];

    if (state == 0) {
        *a0 = *a1;
        ((float *)a0)[2] += f;
        return;
    }
    if (state < 0)
        return;
    if (state >= 3)
        return;
    LVL_5_FELTZIN_SYSTEM_Fe23fe324_FUN_003065F8(v);
    v[2] = f;
    LVL_5_FELTZIN_SYSTEM_Fe23fe324_FUN_00306E98(m, *(int *)(p + 8848) + 240);
    LVL_5_FELTZIN_SYSTEM_Fe23fe324_FUN_00306B00(v, v, m);
    LVL_5_FELTZIN_SYSTEM_Fe23fe324_FUN_00306630(a0, a1, v);
}
extern void LVL_5_FELTZIN_SYSTEM_F38a60c3d_FUN_0045A600(char *o, int n, float a, float b, float c, float d, float e);
extern void LVL_5_FELTZIN_SYSTEM_F38a60c3d_FUN_0045A638(char *o, int n, float a, float b);

void LVL_5_FELTZIN_SYSTEM_FUN_0045A4F8(char *o)
{
    float v;

    *(int *)(o + 24) = 0;
    *(float *)(o + 40) = 0.0f;
    v = *(float *)(o + 24);
    *(float *)(o + 44) = 0.0f;
    *(float *)(o + 128) = 0.0f;
    *(float *)(o + 36) = 0.005f;
    LVL_5_FELTZIN_SYSTEM_F38a60c3d_FUN_0045A600(o, 0, v, v, v, v, v);
    LVL_5_FELTZIN_SYSTEM_F38a60c3d_FUN_0045A600(o, 1, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);
    *(int *)(o + 132) = 2;
    LVL_5_FELTZIN_SYSTEM_F38a60c3d_FUN_0045A638(o, 0, v, v);
    *(int *)(o + 32) = 0;
    *(int *)(o + 28) = 1;
}
extern float LVL_5_FELTZIN_SYSTEM_Fb4148aec_FUN_00307668(float b, float a);
extern float LVL_5_FELTZIN_SYSTEM_Fb4148aec_FUN_003065A0(float t);
extern float LVL_5_FELTZIN_SYSTEM_Fb4148aec_FUN_003065A0(float t);
extern float LVL_5_FELTZIN_SYSTEM_Fb4148aec_FUN_003065A0(float t);
extern float LVL_5_FELTZIN_SYSTEM_Fb4148aec_FUN_003065A0(float t);
extern void LVL_5_FELTZIN_SYSTEM_Fb4148aec_FUN_00307620(float a, float c);

void LVL_5_FELTZIN_SYSTEM_FUN_00307A70(float a, float b, float c)
{
    float t = LVL_5_FELTZIN_SYSTEM_Fb4148aec_FUN_00307668(b, a);

    if (t <= 0.0f)
        c = -c;
    if (LVL_5_FELTZIN_SYSTEM_Fb4148aec_FUN_003065A0(t) < c)
        c = LVL_5_FELTZIN_SYSTEM_Fb4148aec_FUN_003065A0(t);
    else if (c < -LVL_5_FELTZIN_SYSTEM_Fb4148aec_FUN_003065A0(t))
        c = -LVL_5_FELTZIN_SYSTEM_Fb4148aec_FUN_003065A0(t);
    LVL_5_FELTZIN_SYSTEM_Fb4148aec_FUN_00307620(a, c);
}
extern float LVL_5_FELTZIN_SYSTEM_Fc8641365_FUN_00307620(float x);
extern float LVL_5_FELTZIN_SYSTEM_Fc8641365_FUN_00306C20(float x);
extern float LVL_5_FELTZIN_SYSTEM_Fc8641365_FUN_00307620(float x);
extern float LVL_5_FELTZIN_SYSTEM_Fc8641365_FUN_00306C20(float x);

void LVL_5_FELTZIN_SYSTEM_FUN_0033A6A0(float *a0, float *a1, float *a2,
                                        float b, float unused, float c)
{
    if (c > 0.0f) {
        float r = LVL_5_FELTZIN_SYSTEM_Fc8641365_FUN_00307620(*a1);

        *a1 = r;
        a0[6] = LVL_5_FELTZIN_SYSTEM_Fc8641365_FUN_00306C20(r) * b + c;
    } else {
        float r = LVL_5_FELTZIN_SYSTEM_Fc8641365_FUN_00307620(*a1);

        *a1 = r;
        a0[6] = a0[6] - *a2;
        *a2 = LVL_5_FELTZIN_SYSTEM_Fc8641365_FUN_00306C20(*a1) * b;
        a0[6] = a0[6] + *a2;
    }
}
extern int LVL_5_FELTZIN_SYSTEM_F6c3d1d31_FUN_00379CA0();
extern int LVL_5_FELTZIN_SYSTEM_F6c3d1d31_FUN_0037CDB0();
extern float LVL_5_FELTZIN_SYSTEM_F6c3d1d31_FUN_003067D8();
extern int LVL_5_FELTZIN_SYSTEM_F6c3d1d31_FUN_003062A0();

int LVL_5_FELTZIN_SYSTEM_FUN_0037D558(int *a0)
{
    int s2 = 0;
    int s1 = LVL_5_FELTZIN_SYSTEM_F6c3d1d31_FUN_00379CA0(a0);
    float f20 = 1.0f;

    if (LVL_5_FELTZIN_SYSTEM_F6c3d1d31_FUN_0037CDB0(a0) == 2)
        f20 = 8.0f;

    if (s1 != 0) {
        if (LVL_5_FELTZIN_SYSTEM_F6c3d1d31_FUN_003067D8((char *)a0 + 16, (char *)s1 + 96) < f20)
            s2 = LVL_5_FELTZIN_SYSTEM_F6c3d1d31_FUN_0037CDB0(a0) != 8;

        s2 = LVL_5_FELTZIN_SYSTEM_F6c3d1d31_FUN_003062A0((char *)s1 + 304) != 0 ? 1 : s2;
    }

    return s2;
}
extern int LVL_5_FELTZIN_SYSTEM_F0440d2f1_FUN_00306B00(float *, char *, char *);
extern float LVL_5_FELTZIN_SYSTEM_F0440d2f1_FUN_00306CD0(float, float);
extern float LVL_5_FELTZIN_SYSTEM_F0440d2f1_FUN_00335EF0(float *, char *, int, float, float, float, float);
extern void LVL_5_FELTZIN_SYSTEM_F0440d2f1_FUN_002CC640(float, float, float);
extern char LVL_5_FELTZIN_SYSTEM_F0440d2f1_D_00189FB0[];

void LVL_5_FELTZIN_SYSTEM_FUN_002CC6C0(int a0, float a1, float a2, float a3)
{
    float tmp[2];
    char *p = LVL_5_FELTZIN_SYSTEM_F0440d2f1_D_00189FB0;
    float out;
    float r;

    LVL_5_FELTZIN_SYSTEM_F0440d2f1_FUN_00306B00(tmp, p, p - 336);
    r = LVL_5_FELTZIN_SYSTEM_F0440d2f1_FUN_00306CD0(tmp[0], tmp[1]);
    out = 0.0f;
    *(float *)(p + 24) = LVL_5_FELTZIN_SYSTEM_F0440d2f1_FUN_00335EF0(&out, p + 20, a0, r, a1, a2, a3);
    LVL_5_FELTZIN_SYSTEM_F0440d2f1_FUN_002CC640(0.0f, 0.0f, out);
}
extern void LVL_5_FELTZIN_SYSTEM_F8cb0f4c0_FUN_003357F0(float *, float);
extern float LVL_5_FELTZIN_SYSTEM_F8cb0f4c0_FUN_003065A0(float);

float LVL_5_FELTZIN_SYSTEM_FUN_00335A00(float *a0, float *a1, float f1, float f2,
                                         float f3, float f4)
{
    float s = f1;
    float u = f4;
    float t;
    float r;

    LVL_5_FELTZIN_SYSTEM_F8cb0f4c0_FUN_003357F0(a1, s - a0[0]);
    t = s - (a0[0] + a1[0]);
    a0[0] = a0[0] + a1[0];
    r = LVL_5_FELTZIN_SYSTEM_F8cb0f4c0_FUN_003065A0(t);
    u = u * 0.01f;
    if (r < u) {
        a0[0] = s;
        a1[0] = 0.0f;
        return a1[0];
    }
    return t;
}
extern float LVL_5_FELTZIN_SYSTEM_Ffaf24891_FUN_00306C08(float x);
extern float LVL_5_FELTZIN_SYSTEM_Ffaf24891_FUN_00306C08(float x);
extern float LVL_5_FELTZIN_SYSTEM_Ffaf24891_FUN_00306C08(float x);
extern float LVL_5_FELTZIN_SYSTEM_Ffaf24891_FUN_00306C20(float x);
extern float LVL_5_FELTZIN_SYSTEM_Ffaf24891_FUN_00306C20(float x);
extern void LVL_5_FELTZIN_SYSTEM_Ffaf24891_FUN_00306630(float *out, float *in, void *q);

void LVL_5_FELTZIN_SYSTEM_FUN_002F2858(float *out, float *p, void *q)
{
    float t;

    t = LVL_5_FELTZIN_SYSTEM_Ffaf24891_FUN_00306C08(p[1]);
    out[0] = p[2] * t * LVL_5_FELTZIN_SYSTEM_Ffaf24891_FUN_00306C08(p[0]);
    t = LVL_5_FELTZIN_SYSTEM_Ffaf24891_FUN_00306C08(p[1]);
    out[1] = p[2] * t * LVL_5_FELTZIN_SYSTEM_Ffaf24891_FUN_00306C20(p[0]);
    out[2] = p[2] * LVL_5_FELTZIN_SYSTEM_Ffaf24891_FUN_00306C20(p[1]);
    out[3] = 0.0f;
    LVL_5_FELTZIN_SYSTEM_Ffaf24891_FUN_00306630(out, out, q);
}
extern float LVL_5_FELTZIN_SYSTEM_Fc3394786_FUN_00332B50(void);
extern float LVL_5_FELTZIN_SYSTEM_Fc3394786_FUN_00332C18(void);
extern float LVL_5_FELTZIN_SYSTEM_Fc3394786_FUN_00332C18(void);
extern float LVL_5_FELTZIN_SYSTEM_Fc3394786_FUN_00306C08(float);
extern float LVL_5_FELTZIN_SYSTEM_Fc3394786_FUN_00306C20(float);
extern float LVL_5_FELTZIN_SYSTEM_Fc3394786_FUN_00306C20(float);
extern float LVL_5_FELTZIN_SYSTEM_Fc3394786_FUN_00306C20(float);
extern float LVL_5_FELTZIN_SYSTEM_Fc3394786_FUN_00306C08(float);

void LVL_5_FELTZIN_SYSTEM_FUN_00332CD8(float *out)
{
    float back = LVL_5_FELTZIN_SYSTEM_Fc3394786_FUN_00332B50();
    float a = LVL_5_FELTZIN_SYSTEM_Fc3394786_FUN_00332C18();
    float b = LVL_5_FELTZIN_SYSTEM_Fc3394786_FUN_00332C18();
    float value;

    value = LVL_5_FELTZIN_SYSTEM_Fc3394786_FUN_00306C08(a) * LVL_5_FELTZIN_SYSTEM_Fc3394786_FUN_00306C20(b);
    value = value * back;
    out[0] = value;
    value = LVL_5_FELTZIN_SYSTEM_Fc3394786_FUN_00306C20(a) * LVL_5_FELTZIN_SYSTEM_Fc3394786_FUN_00306C20(b);
    value = value * back;
    out[1] = value;
    out[2] = LVL_5_FELTZIN_SYSTEM_Fc3394786_FUN_00306C08(b) * back;
}
extern unsigned int LVL_5_FELTZIN_SYSTEM_F95518630_FUN_00307778(float x);
extern unsigned int LVL_5_FELTZIN_SYSTEM_F95518630_FUN_00307778(float x);
extern unsigned int LVL_5_FELTZIN_SYSTEM_F95518630_FUN_00307778(float x);
extern unsigned int LVL_5_FELTZIN_SYSTEM_F95518630_FUN_00307778(float x);

int LVL_5_FELTZIN_SYSTEM_FUN_00336278(float r, float g, float b, float a)
{
    unsigned int cr = LVL_5_FELTZIN_SYSTEM_F95518630_FUN_00307778(r * 255.0f) & 0xff;
    unsigned int cg = LVL_5_FELTZIN_SYSTEM_F95518630_FUN_00307778(g * 255.0f) & 0xff;
    unsigned int cb = LVL_5_FELTZIN_SYSTEM_F95518630_FUN_00307778(b * 255.0f) & 0xff;
    unsigned int ca = LVL_5_FELTZIN_SYSTEM_F95518630_FUN_00307778(a * 255.0f) & 0xff;
    unsigned int packed = cr;

    packed |= cg << 8;
    packed |= cb << 16;
    packed |= ca << 24;
    return packed;
}
extern float LVL_5_FELTZIN_SYSTEM_F197ee8cc_FUN_00306C08(float v);
extern float LVL_5_FELTZIN_SYSTEM_F197ee8cc_FUN_00306C20(float v);
extern void LVL_5_FELTZIN_SYSTEM_F197ee8cc_FUN_00306B00(void *p, void *q, char *data);
extern void LVL_5_FELTZIN_SYSTEM_F197ee8cc_FUN_00306630(void *p, void *q, char *data);

extern char LVL_5_FELTZIN_SYSTEM_F197ee8cc_D_00189E20[];

void LVL_5_FELTZIN_SYSTEM_FUN_002EBEB8(float *p, int flag, float scale, float value, float height)
{
    p[0] = LVL_5_FELTZIN_SYSTEM_F197ee8cc_FUN_00306C08(value) * scale;
    p[1] = LVL_5_FELTZIN_SYSTEM_F197ee8cc_FUN_00306C20(value) * scale;
    p[2] = height;
    LVL_5_FELTZIN_SYSTEM_F197ee8cc_FUN_00306B00(p, p, LVL_5_FELTZIN_SYSTEM_F197ee8cc_D_00189E20);
    if (flag != 0)
        LVL_5_FELTZIN_SYSTEM_F197ee8cc_FUN_00306630(p, p, LVL_5_FELTZIN_SYSTEM_F197ee8cc_D_00189E20 + 128);
}
extern float LVL_5_FELTZIN_SYSTEM_F3392e4bc_FUN_003065A0(float d);

#ifndef RAC2_T_ROW_F3392E4BC
#define RAC2_T_ROW_F3392E4BC
typedef float Row_F3392e4bc[4];
#endif


float LVL_5_FELTZIN_SYSTEM_FUN_002C8D00(Row_F3392e4bc *a, Row_F3392e4bc *b)
{
    float sum = 0.0f;
    int i, j;

    for (i = 0; i < 3; i++)
        for (j = 0; j < 3; j++)
            sum += LVL_5_FELTZIN_SYSTEM_F3392e4bc_FUN_003065A0(a[i][j] - b[i][j]);
    return sum;
}
extern void LVL_5_FELTZIN_SYSTEM_F2b6b96d1_FUN_0032E728(char *, int, int *, char *);
extern void LVL_5_FELTZIN_SYSTEM_F2b6b96d1_FUN_003066A0(char *, char *, float);
extern void LVL_5_FELTZIN_SYSTEM_F2b6b96d1_FUN_003070E0(char *, char *);
extern void LVL_5_FELTZIN_SYSTEM_F2b6b96d1_FUN_00307210(char *, char *, char *);
extern void LVL_5_FELTZIN_SYSTEM_F2b6b96d1_FUN_00306630(char *, char *, char *);

void LVL_5_FELTZIN_SYSTEM_FUN_003298C0(char *p1, int p2, char *p3)
{
    int n;
    char buf[64];
    float f;

    n = p2;
    f = *(float *)(p1 + 44) * 0.0009765625f;
    LVL_5_FELTZIN_SYSTEM_F2b6b96d1_FUN_0032E728(p1, 1, &n, p3);
    LVL_5_FELTZIN_SYSTEM_F2b6b96d1_FUN_003066A0(p3 + 48, p3 + 48, f);
    LVL_5_FELTZIN_SYSTEM_F2b6b96d1_FUN_003070E0(buf, p1 + 192);
    LVL_5_FELTZIN_SYSTEM_F2b6b96d1_FUN_00307210(p3, buf, p3);
    LVL_5_FELTZIN_SYSTEM_F2b6b96d1_FUN_00306630(p3 + 48, p3 + 48, p1 + 16);
}
extern void LVL_5_FELTZIN_SYSTEM_F3258c258_FUN_0032E5D0(char *);
extern void LVL_5_FELTZIN_SYSTEM_F3258c258_FUN_003066A0(char *, char *, float);
extern void LVL_5_FELTZIN_SYSTEM_F3258c258_FUN_00306AD8(char *, char *, char *);
extern void LVL_5_FELTZIN_SYSTEM_F3258c258_FUN_00306630(char *, char *, char *);

void LVL_5_FELTZIN_SYSTEM_FUN_003299E8(char *p1, int n, char *p3, char *p4)
{
    float f = *(float *)(p1 + 44) * 0.0009765625f;

    LVL_5_FELTZIN_SYSTEM_F3258c258_FUN_0032E5D0(p1);
    if (n > 0) {
        do {
            LVL_5_FELTZIN_SYSTEM_F3258c258_FUN_003066A0(p4, p4, f);
            LVL_5_FELTZIN_SYSTEM_F3258c258_FUN_00306AD8(p4, p4, p1 + 192);
            LVL_5_FELTZIN_SYSTEM_F3258c258_FUN_00306630(p4, p4, p1 + 16);
            p4 += 16;
        } while (--n != 0);
    }
}
extern float LVL_5_FELTZIN_SYSTEM_F94baa797_FUN_00306C08(float);
extern float LVL_5_FELTZIN_SYSTEM_F94baa797_FUN_00306C08(float);
extern float LVL_5_FELTZIN_SYSTEM_F94baa797_FUN_00306C20(float);
extern float LVL_5_FELTZIN_SYSTEM_F94baa797_FUN_00306C08(float);
extern float LVL_5_FELTZIN_SYSTEM_F94baa797_FUN_00306C20(float);

void LVL_5_FELTZIN_SYSTEM_FUN_0033B330(float *p, float a, float b, float c)
{
    p[0] = LVL_5_FELTZIN_SYSTEM_F94baa797_FUN_00306C08(b) * a * LVL_5_FELTZIN_SYSTEM_F94baa797_FUN_00306C08(c);
    p[1] = LVL_5_FELTZIN_SYSTEM_F94baa797_FUN_00306C20(b) * a * LVL_5_FELTZIN_SYSTEM_F94baa797_FUN_00306C08(c);
    p[2] = LVL_5_FELTZIN_SYSTEM_F94baa797_FUN_00306C20(c) * a;
}
extern int LVL_5_FELTZIN_SYSTEM_Fcf85f2f4_FUN_003062D0(short *);
extern void LVL_5_FELTZIN_SYSTEM_Fcf85f2f4_FUN_003423C8(char *);
extern float LVL_5_FELTZIN_SYSTEM_Fcf85f2f4_FUN_00307768(int);
extern int LVL_5_FELTZIN_SYSTEM_Fcf85f2f4_FUN_003077C0(int, int, float);

struct T {
    float a;
    float b;
    int c;
    int d;
    float e;
};

void LVL_5_FELTZIN_SYSTEM_FUN_0034B968(char *p)
{
    if (LVL_5_FELTZIN_SYSTEM_Fcf85f2f4_FUN_003062D0((short *)(p + 10)) != 0) {
        LVL_5_FELTZIN_SYSTEM_Fcf85f2f4_FUN_003423C8(p);
    } else {
        struct T *t = (struct T *)(p + 32);
        float k = LVL_5_FELTZIN_SYSTEM_Fcf85f2f4_FUN_00307768(*(short *)(p + 10)) * t->e;

        *(int *)(p + 4) = LVL_5_FELTZIN_SYSTEM_Fcf85f2f4_FUN_003077C0(t->d, t->c, k);
        *(float *)(p + 12) = ((t->a - t->b) * k + t->b) * 210000.0f;
    }
}


extern f32 LVL_5_FELTZIN_SYSTEM_F3e5a3249_FUN_00306C08 (f32);

f32 LVL_5_FELTZIN_SYSTEM_FUN_00332ED8 (f32 a, f32 b, f32 t)
{
  f32 u;
  if (t == 0.0f)
    return a;
  if (t == 1.0f)
    return b;
  u = (1.0f - LVL_5_FELTZIN_SYSTEM_F3e5a3249_FUN_00306C08 (t * 3.1415927f)) * 0.5f;
  return a + (b - a) * u;
}


extern s32 LVL_5_FELTZIN_SYSTEM_F45041a5f_FUN_00369F08 (s32);
extern s32 LVL_5_FELTZIN_SYSTEM_F45041a5f_FUN_00369F08 (s32);
extern s32 LVL_5_FELTZIN_SYSTEM_F45041a5f_FUN_00369F08 (s32);
extern s32 LVL_5_FELTZIN_SYSTEM_F45041a5f_FUN_00369F08 (s32);

s32 LVL_5_FELTZIN_SYSTEM_FUN_00365BF0 (s32 self)
{
  *(s32 *) (self + 68) = 0;
  *(s32 *) (self + 72) = LVL_5_FELTZIN_SYSTEM_F45041a5f_FUN_00369F08 (*(s32 *) (self + 52) & 0x200);
  *(s32 *) (self + 76) = LVL_5_FELTZIN_SYSTEM_F45041a5f_FUN_00369F08 (*(s32 *) (self + 52) & 0x200);
  if ((*(s32 *) (self + 52) & 0x200) == 0)
    {
      if (*(s32 *) (self + 72) == 0)
        *(s32 *) (self + 72) = LVL_5_FELTZIN_SYSTEM_F45041a5f_FUN_00369F08 (1);
      if (*(s32 *) (self + 76) == 0)
        *(s32 *) (self + 76) = LVL_5_FELTZIN_SYSTEM_F45041a5f_FUN_00369F08 (1);
    }
  *(s32 *) (self + 92) = 0;
  *(s32 *) (self + 80) = -1;
  *(s32 *) (self + 84) = -1;
  return 0;
}
extern char *LVL_5_FELTZIN_SYSTEM_F5580c116_FUN_0033E430();
extern int *LVL_5_FELTZIN_SYSTEM_F5580c116_FUN_0033E460();

void LVL_5_FELTZIN_SYSTEM_FUN_003BD890(char *a0)
{
	int s1;
	int v1;
	int x;
	int i;
	int end;
	short *p;

	s1 = (int)LVL_5_FELTZIN_SYSTEM_F5580c116_FUN_0033E430(1483, a0);
	v1 = *LVL_5_FELTZIN_SYSTEM_F5580c116_FUN_0033E460(1483, a0);
	x = s1 + v1;
	p = (short *)(s1 + 8866);
	for (i = 79; i >= 0; i--) {
		*p = 0;
		p = p - 56;
	}
	s1 = x;
	end = s1 + 288;
	do {
		*(short *)(s1 + 80) = 0;
		*(int *)(s1 + 84) = 0;
		*(int *)(s1 + 88) = 0;
		s1 = s1 + 96;
	} while (s1 < end);
}



extern s32 LVL_5_FELTZIN_SYSTEM_F037efef1_FUN_003077C0(s32, s32, f32);

void LVL_5_FELTZIN_SYSTEM_FUN_00446BA0(s32 *unused, s32 *dst, s32 *left, s32 *right, f32 scale) {
    dst[0] = LVL_5_FELTZIN_SYSTEM_F037efef1_FUN_003077C0(left[0], right[0], scale);
    dst[1] = LVL_5_FELTZIN_SYSTEM_F037efef1_FUN_003077C0(left[1], right[1], scale);
    dst[2] = LVL_5_FELTZIN_SYSTEM_F037efef1_FUN_003077C0(left[2], right[2], scale);
    dst[3] = LVL_5_FELTZIN_SYSTEM_F037efef1_FUN_003077C0(left[3], right[3], scale);
}


extern void LVL_5_FELTZIN_SYSTEM_F2d77341b_FUN_00306630(void *, void *, void *);
extern s32 LVL_5_FELTZIN_SYSTEM_F2d77341b_FUN_003062A0(void *);
extern void LVL_5_FELTZIN_SYSTEM_F2d77341b_FUN_003423C8(void *);

void LVL_5_FELTZIN_SYSTEM_FUN_00347C80(s32 *self) {
    s32 *base = (s32 *)((char *)self + 32);
    s32 *state = (s32 *)((char *)self + 16);
    LVL_5_FELTZIN_SYSTEM_F2d77341b_FUN_00306630(state, state, base);
    self[1] = (self[1] & 0x00ffffff) + ((base[6] * base[4] / base[5]) << 24);
    if (LVL_5_FELTZIN_SYSTEM_F2d77341b_FUN_003062A0((s32 *)((char *)self + 48)) != 0) {
        LVL_5_FELTZIN_SYSTEM_F2d77341b_FUN_003423C8(self);
    }
}
extern void LVL_5_FELTZIN_SYSTEM_F252d542a_FUN_004471C8(char *object);
extern void LVL_5_FELTZIN_SYSTEM_F252d542a_FUN_004471C8(char *object);
extern void LVL_5_FELTZIN_SYSTEM_F252d542a_FUN_004471C8(char *object);
extern void LVL_5_FELTZIN_SYSTEM_F252d542a_FUN_004471C8(char *object);
extern void LVL_5_FELTZIN_SYSTEM_F252d542a_FUN_00447988(char *object);
extern void LVL_5_FELTZIN_SYSTEM_F252d542a_FUN_00447988(char *object);
extern void LVL_5_FELTZIN_SYSTEM_F252d542a_FUN_00447988(char *object);
extern void LVL_5_FELTZIN_SYSTEM_F252d542a_FUN_00447988(char *object);
extern void LVL_5_FELTZIN_SYSTEM_F252d542a_FUN_00447988(char *object);
extern void LVL_5_FELTZIN_SYSTEM_F252d542a_FUN_00447988(char *object);
extern void LVL_5_FELTZIN_SYSTEM_F252d542a_FUN_00447988(char *object);
extern void LVL_5_FELTZIN_SYSTEM_F252d542a_FUN_00447988(char *object);
extern void LVL_5_FELTZIN_SYSTEM_F252d542a_FUN_00447988(char *object);

char *LVL_5_FELTZIN_SYSTEM_FUN_0044AA60(char *object)
{
    LVL_5_FELTZIN_SYSTEM_F252d542a_FUN_004471C8(object + 8);
    LVL_5_FELTZIN_SYSTEM_F252d542a_FUN_004471C8(object + 84);
    LVL_5_FELTZIN_SYSTEM_F252d542a_FUN_004471C8(object + 160);
    LVL_5_FELTZIN_SYSTEM_F252d542a_FUN_004471C8(object + 236);
    LVL_5_FELTZIN_SYSTEM_F252d542a_FUN_00447988(object + 312);
    LVL_5_FELTZIN_SYSTEM_F252d542a_FUN_00447988(object + 384);
    LVL_5_FELTZIN_SYSTEM_F252d542a_FUN_00447988(object + 456);
    LVL_5_FELTZIN_SYSTEM_F252d542a_FUN_00447988(object + 528);
    LVL_5_FELTZIN_SYSTEM_F252d542a_FUN_00447988(object + 600);
    LVL_5_FELTZIN_SYSTEM_F252d542a_FUN_00447988(object + 672);
    LVL_5_FELTZIN_SYSTEM_F252d542a_FUN_00447988(object + 744);
    LVL_5_FELTZIN_SYSTEM_F252d542a_FUN_00447988(object + 816);
    LVL_5_FELTZIN_SYSTEM_F252d542a_FUN_00447988(object + 888);
    return object;
}
extern void LVL_5_FELTZIN_SYSTEM_Fb344bd8e_FUN_004473F0(void *p);
extern void LVL_5_FELTZIN_SYSTEM_Fb344bd8e_FUN_004473F0(void *p);
extern void LVL_5_FELTZIN_SYSTEM_Fb344bd8e_FUN_0045C098(void *p);
extern void LVL_5_FELTZIN_SYSTEM_Fb344bd8e_FUN_004476F0(void *p);
extern void LVL_5_FELTZIN_SYSTEM_Fb344bd8e_FUN_00448BF8(void *p);
extern void LVL_5_FELTZIN_SYSTEM_Fb344bd8e_FUN_00448BF8(void *p);

unsigned char *LVL_5_FELTZIN_SYSTEM_FUN_0045F018(unsigned char *a0)
{
    unsigned char *p;
    int i;

    for (i = 25, p = a0; i != -1; i--) {
        LVL_5_FELTZIN_SYSTEM_Fb344bd8e_FUN_004473F0(p);
        p += 72;
    }
    LVL_5_FELTZIN_SYSTEM_Fb344bd8e_FUN_004473F0(a0 + 1872);
    LVL_5_FELTZIN_SYSTEM_Fb344bd8e_FUN_0045C098(a0 + 1952);
    LVL_5_FELTZIN_SYSTEM_Fb344bd8e_FUN_004476F0(a0 + 7472);
    LVL_5_FELTZIN_SYSTEM_Fb344bd8e_FUN_00448BF8(a0 + 7532);
    LVL_5_FELTZIN_SYSTEM_Fb344bd8e_FUN_00448BF8(a0 + 8124);
    return a0;
}
#ifndef RAC2_T_V4_F61E33AD9
#define RAC2_T_V4_F61E33AD9
typedef int V4_F61e33ad9 __attribute__((mode(TI)));
#endif


extern float LVL_5_FELTZIN_SYSTEM_F61e33ad9_FUN_003065A0(float f);
extern void LVL_5_FELTZIN_SYSTEM_F61e33ad9_FUN_00306810(void *a, void *b);
extern void LVL_5_FELTZIN_SYSTEM_F61e33ad9_FUN_003067D8(void *a, void *b);

void LVL_5_FELTZIN_SYSTEM_FUN_00354288(void *a0, void *a1, float scale)
{
    V4_F61e33ad9 l0;
    V4_F61e33ad9 l1;
    float *p0;
    float *p1;
    float t;
    float u;

    l0 = *(V4_F61e33ad9 *)a0;
    l1 = *(V4_F61e33ad9 *)a1;
    p0 = (float *)&l0;
    p1 = (float *)&l1;
    if (0.0f < scale) {
        t = p0[2];
        u = p1[2];
        if (LVL_5_FELTZIN_SYSTEM_F61e33ad9_FUN_003065A0(t - u) < scale) {
            LVL_5_FELTZIN_SYSTEM_F61e33ad9_FUN_00306810(p0, p1);
            return;
        }
    }
    LVL_5_FELTZIN_SYSTEM_F61e33ad9_FUN_003067D8(p0, p1);
}
extern void *LVL_5_FELTZIN_SYSTEM_Fb8d1f7f1_FUN_002BD6C8(void *p);
extern void LVL_5_FELTZIN_SYSTEM_Fb8d1f7f1_FUN_002EA9E8(void *a, void *b, float f);

extern unsigned char LVL_5_FELTZIN_SYSTEM_Fb8d1f7f1_D_00189E20[];

void LVL_5_FELTZIN_SYSTEM_FUN_002C8050(void)
{
    if (LVL_5_FELTZIN_SYSTEM_Fb8d1f7f1_D_00189E20[8888] == 0)
        return;
    if (*(int *)(LVL_5_FELTZIN_SYSTEM_Fb8d1f7f1_D_00189E20 + 3736) != 0) {
        *(int *)(LVL_5_FELTZIN_SYSTEM_Fb8d1f7f1_D_00189E20 + 3748) = 1;
    } else if (*(int *)(LVL_5_FELTZIN_SYSTEM_Fb8d1f7f1_D_00189E20 + 8852) == 0) {
        if (*(unsigned char *)(*(int *)(LVL_5_FELTZIN_SYSTEM_Fb8d1f7f1_D_00189E20 + 8848) + 67) == *(int *)(LVL_5_FELTZIN_SYSTEM_Fb8d1f7f1_D_00189E20 + 9392)) {
            LVL_5_FELTZIN_SYSTEM_Fb8d1f7f1_FUN_002EA9E8(LVL_5_FELTZIN_SYSTEM_Fb8d1f7f1_FUN_002BD6C8(0), 0, -2.0f);
        }
    }
    LVL_5_FELTZIN_SYSTEM_Fb8d1f7f1_D_00189E20[8888] = 0;
    LVL_5_FELTZIN_SYSTEM_Fb8d1f7f1_D_00189E20[8890] = 0;
}
extern char LVL_5_FELTZIN_SYSTEM_Fd337d953_D_00189E20[];
extern void LVL_5_FELTZIN_SYSTEM_Fd337d953_FUN_00306B00(char *dst, char *src, char *extra);

#ifndef RAC2_T_V4_FD337D953
#define RAC2_T_V4_FD337D953
typedef int V4_Fd337d953 __attribute__((mode(TI)));
#endif


void LVL_5_FELTZIN_SYSTEM_FUN_002EC4E8(char *dst, char *src, float k)
{
    char *base = LVL_5_FELTZIN_SYSTEM_Fd337d953_D_00189E20;
    int flag = *(unsigned char *)(base + 8899);

    if (flag == 0) {
        *(V4_Fd337d953 *)dst = *(V4_Fd337d953 *)src;
        *(float *)(dst + 8) = *(float *)(dst + 8) * k;
        return;
    }
    if (flag < 0)
        return;
    if (flag >= 3)
        return;
    LVL_5_FELTZIN_SYSTEM_Fd337d953_FUN_00306B00(dst, src, base + 64);
    *(float *)(dst + 8) = *(float *)(dst + 8) * k;
    LVL_5_FELTZIN_SYSTEM_Fd337d953_FUN_00306B00(dst, dst, base);
}
extern void LVL_5_FELTZIN_SYSTEM_F1b9be9ff_FUN_0044BB78(void *);
extern void LVL_5_FELTZIN_SYSTEM_F1b9be9ff_FUN_004476F0(void *);
extern void LVL_5_FELTZIN_SYSTEM_F1b9be9ff_FUN_00447988(void *);
extern void LVL_5_FELTZIN_SYSTEM_F1b9be9ff_FUN_00447988(void *);
extern void LVL_5_FELTZIN_SYSTEM_F1b9be9ff_FUN_00447988(void *);
extern void LVL_5_FELTZIN_SYSTEM_F1b9be9ff_FUN_004471C8(void *);
extern void LVL_5_FELTZIN_SYSTEM_F1b9be9ff_FUN_00447988(void *);
extern void LVL_5_FELTZIN_SYSTEM_F1b9be9ff_FUN_00447988(void *);
extern void LVL_5_FELTZIN_SYSTEM_F1b9be9ff_FUN_00447988(void *);
extern void LVL_5_FELTZIN_SYSTEM_F1b9be9ff_FUN_00447988(void *);
extern void LVL_5_FELTZIN_SYSTEM_F1b9be9ff_FUN_00447988(void *);
extern void LVL_5_FELTZIN_SYSTEM_F1b9be9ff_FUN_00447988(void *);

char *LVL_5_FELTZIN_SYSTEM_FUN_0044F668(char *object)
{
    LVL_5_FELTZIN_SYSTEM_F1b9be9ff_FUN_0044BB78(object + 8);
    LVL_5_FELTZIN_SYSTEM_F1b9be9ff_FUN_004476F0(object + 684);
    LVL_5_FELTZIN_SYSTEM_F1b9be9ff_FUN_00447988(object + 744);
    LVL_5_FELTZIN_SYSTEM_F1b9be9ff_FUN_00447988(object + 816);
    LVL_5_FELTZIN_SYSTEM_F1b9be9ff_FUN_00447988(object + 888);
    LVL_5_FELTZIN_SYSTEM_F1b9be9ff_FUN_004471C8(object + 960);
    LVL_5_FELTZIN_SYSTEM_F1b9be9ff_FUN_00447988(object + 1040);
    LVL_5_FELTZIN_SYSTEM_F1b9be9ff_FUN_00447988(object + 1112);
    LVL_5_FELTZIN_SYSTEM_F1b9be9ff_FUN_00447988(object + 1184);
    LVL_5_FELTZIN_SYSTEM_F1b9be9ff_FUN_00447988(object + 1256);
    LVL_5_FELTZIN_SYSTEM_F1b9be9ff_FUN_00447988(object + 1328);
    LVL_5_FELTZIN_SYSTEM_F1b9be9ff_FUN_00447988(object + 1400);
    return object;
}
extern void *LVL_5_FELTZIN_SYSTEM_Fdd95b44d_FUN_0030CBA8(int);
extern void *LVL_5_FELTZIN_SYSTEM_Fdd95b44d_FUN_0030CBA8(int);
extern void *LVL_5_FELTZIN_SYSTEM_Fdd95b44d_FUN_0030CBA8(int);
extern void LVL_5_FELTZIN_SYSTEM_Fdd95b44d_FUN_0044C078(void *, void *, void *, void *);
extern void LVL_5_FELTZIN_SYSTEM_Fdd95b44d_FUN_0044C0D0(void *, float);

void LVL_5_FELTZIN_SYSTEM_FUN_0044A840(int *self)
{
    void *a;
    void *b;
    void *c;
    void *sub = (void *)(self + 2);

    a = LVL_5_FELTZIN_SYSTEM_Fdd95b44d_FUN_0030CBA8(11677);
    b = LVL_5_FELTZIN_SYSTEM_Fdd95b44d_FUN_0030CBA8(11676);
    c = LVL_5_FELTZIN_SYSTEM_Fdd95b44d_FUN_0030CBA8(11599);

    LVL_5_FELTZIN_SYSTEM_Fdd95b44d_FUN_0044C078(sub, a, b, c);
    LVL_5_FELTZIN_SYSTEM_Fdd95b44d_FUN_0044C0D0(sub, 0.0f);

    self[191] = 1;
}
extern void LVL_5_FELTZIN_SYSTEM_F62b44aca_FUN_003065F8(void *);
extern void LVL_5_FELTZIN_SYSTEM_F62b44aca_FUN_002C2868(void *, float, float, float);
extern unsigned char LVL_5_FELTZIN_SYSTEM_F62b44aca_D_0018C0D4[];

void LVL_5_FELTZIN_SYSTEM_FUN_002C2970(float a, float b, float c)
{
    float buf[4];

    LVL_5_FELTZIN_SYSTEM_F62b44aca_FUN_003065F8(buf);

    if (LVL_5_FELTZIN_SYSTEM_F62b44aca_D_0018C0D4[0] == 1)
        buf[2] = 0.35f;
    else
        buf[2] = 0.6f;

    LVL_5_FELTZIN_SYSTEM_F62b44aca_FUN_002C2868(buf, a, b, c);
}
extern int LVL_5_FELTZIN_SYSTEM_Ffe57d182_FUN_002EA620(int, void *, void *);
extern void LVL_5_FELTZIN_SYSTEM_Ffe57d182_FUN_00332708(void *, int, int, int);
extern void LVL_5_FELTZIN_SYSTEM_Ffe57d182_FUN_00332708(void *, int, int, int);
extern char LVL_5_FELTZIN_SYSTEM_Ffe57d182_D_00189E20[];

void LVL_5_FELTZIN_SYSTEM_FUN_002EA368(void)
{
    char *p = LVL_5_FELTZIN_SYSTEM_Ffe57d182_D_00189E20;
    void *s0;
    void *s1;
    int buf[2];

    s0 = *(void **)(p + 4880);
    s1 = *(void **)(p + 4884);

    if (s0 == 0)
        return;
    if (s1 == 0)
        return;

    if (*(unsigned char *)((char *)s0 + 67) != 1)
        return;

    if (LVL_5_FELTZIN_SYSTEM_Ffe57d182_FUN_002EA620(0, buf, buf + 1) == 0)
        return;

    LVL_5_FELTZIN_SYSTEM_Ffe57d182_FUN_00332708(s0, buf[0], 0, 7);
    LVL_5_FELTZIN_SYSTEM_Ffe57d182_FUN_00332708(s1, buf[1], 0, 7);
}
extern float LVL_5_FELTZIN_SYSTEM_F101cea20_FUN_00332B50(float, float);
extern float LVL_5_FELTZIN_SYSTEM_F101cea20_FUN_00332B50(float, float);
extern float LVL_5_FELTZIN_SYSTEM_F101cea20_FUN_00332B50(float, float);

void LVL_5_FELTZIN_SYSTEM_FUN_00337F58(float *vector, float scale)
{
    float negative = -scale;

    vector[0] = vector[0] + LVL_5_FELTZIN_SYSTEM_F101cea20_FUN_00332B50(negative, scale);
    vector[1] = vector[1] + LVL_5_FELTZIN_SYSTEM_F101cea20_FUN_00332B50(negative, scale);
    vector[2] = vector[2] + LVL_5_FELTZIN_SYSTEM_F101cea20_FUN_00332B50(negative, scale);
}
extern int LVL_5_FELTZIN_SYSTEM_F61cc5848_FUN_0030CBA8(int);
extern int LVL_5_FELTZIN_SYSTEM_F61cc5848_FUN_0030CBA8(int);
extern int LVL_5_FELTZIN_SYSTEM_F61cc5848_FUN_0030CBA8(int);
extern void LVL_5_FELTZIN_SYSTEM_F61cc5848_FUN_0044C078(char *, int, int, int);
extern void LVL_5_FELTZIN_SYSTEM_F61cc5848_FUN_0044C0D0(char *, float);

void LVL_5_FELTZIN_SYSTEM_FUN_0044A7C0(char *p)
{
    int first = LVL_5_FELTZIN_SYSTEM_F61cc5848_FUN_0030CBA8(11678);
    int second = LVL_5_FELTZIN_SYSTEM_F61cc5848_FUN_0030CBA8(11676);

    LVL_5_FELTZIN_SYSTEM_F61cc5848_FUN_0044C078(p + 8, first, second, LVL_5_FELTZIN_SYSTEM_F61cc5848_FUN_0030CBA8(11599));
    LVL_5_FELTZIN_SYSTEM_F61cc5848_FUN_0044C0D0(p + 8, 0.0f);
    *(int *)(p + 764) = 0;
}
extern int LVL_5_FELTZIN_SYSTEM_F32d48737_D_001A8FD8 __attribute__((sda));
extern int LVL_5_FELTZIN_SYSTEM_F32d48737_D_001A8FDC __attribute__((sda));
extern void LVL_5_FELTZIN_SYSTEM_F32d48737_FUN_0044BE48(int *p, int flag);
extern void LVL_5_FELTZIN_SYSTEM_F32d48737_FUN_0044BE48(int *p, int flag);
extern void LVL_5_FELTZIN_SYSTEM_F32d48737_FUN_0044BF70(int *p);
extern void LVL_5_FELTZIN_SYSTEM_F32d48737_FUN_00447340(int *p);

void LVL_5_FELTZIN_SYSTEM_FUN_0044A9D8(int *obj)
{
    if (LVL_5_FELTZIN_SYSTEM_F32d48737_D_001A8FD8 != 0 || LVL_5_FELTZIN_SYSTEM_F32d48737_D_001A8FDC != 0 || obj[192] != 0)
        LVL_5_FELTZIN_SYSTEM_F32d48737_FUN_0044BE48(obj + 2, 0);
    if (obj[191] == 1)
        LVL_5_FELTZIN_SYSTEM_F32d48737_FUN_0044BE48(obj + 2, 1);
    LVL_5_FELTZIN_SYSTEM_F32d48737_FUN_0044BF70(obj + 2);
    LVL_5_FELTZIN_SYSTEM_F32d48737_FUN_00447340(obj + 170);
}
extern int LVL_5_FELTZIN_SYSTEM_F455be788_D_001A904C __attribute__((sda));
extern int LVL_5_FELTZIN_SYSTEM_F455be788_FUN_00452580(int x);

int LVL_5_FELTZIN_SYSTEM_FUN_0035AB40(int *obj)
{
    if (LVL_5_FELTZIN_SYSTEM_F455be788_D_001A904C != 0)
        obj[13] = LVL_5_FELTZIN_SYSTEM_F455be788_FUN_00452580(LVL_5_FELTZIN_SYSTEM_F455be788_D_001A904C + 0x3BE08);
    return 0;
}
extern int LVL_5_FELTZIN_SYSTEM_F455be788_D_001A904C __attribute__((sda));
extern int LVL_5_FELTZIN_SYSTEM_F455be788_FUN_00452580(int x);

int LVL_5_FELTZIN_SYSTEM_FUN_00360C48(int *obj)
{
    if (LVL_5_FELTZIN_SYSTEM_F455be788_D_001A904C != 0)
        obj[13] = LVL_5_FELTZIN_SYSTEM_F455be788_FUN_00452580(LVL_5_FELTZIN_SYSTEM_F455be788_D_001A904C + 0x3BE08);
    return 0;
}
#ifndef RAC2_T_NODE16_F23626AD8
#define RAC2_T_NODE16_F23626AD8
typedef struct Node16_F23626ad8 Node16_F23626ad8;
#endif

#ifndef RAC2_T_NODE104_F23626AD8
#define RAC2_T_NODE104_F23626AD8
typedef struct Node104_F23626ad8 Node104_F23626ad8;
#endif

#ifndef RAC2_T_NODE24_F23626AD8
#define RAC2_T_NODE24_F23626AD8
typedef struct Node24_F23626ad8 Node24_F23626ad8;
#endif


struct Node16_F23626ad8 {
    short h0;
    unsigned char pad2[2];
    unsigned char b4;
    unsigned char b5;
    unsigned char b6;
};

struct Node104_F23626ad8 {
    unsigned char pad0[16];
    Node16_F23626ad8 *p16;
};

struct Node24_F23626ad8 {
    unsigned char pad0[52];
    unsigned short h52;
    unsigned char pad54[50];
    Node104_F23626ad8 *p104;
};

#ifndef RAC2_T_OBJ_F23626AD8
#define RAC2_T_OBJ_F23626AD8
typedef struct Obj_F23626ad8 {
    unsigned char pad0[4];
    union {
        int f4;
        struct {
            unsigned char b4;
            unsigned char b5;
            short h6;
        } b;
    } u;
    unsigned char pad8[16];
    Node24_F23626ad8 *f24;
} Obj_F23626ad8;
#endif


extern void LVL_5_FELTZIN_SYSTEM_F23626ad8_FUN_0032A498(Node24_F23626ad8 *a, unsigned char b, unsigned char c, unsigned char d);

void LVL_5_FELTZIN_SYSTEM_FUN_004229F0(Obj_F23626ad8 *p)
{
    Node24_F23626ad8 *s;
    Node16_F23626ad8 *d;
    int v;

    LVL_5_FELTZIN_SYSTEM_F23626ad8_FUN_0032A498(p->f24, p->u.b.b4, p->u.b.b5, p->u.b.h6);
    s = p->f24;
    if ((s->h52 & 0x20) == 0)
        return;
    d = ((Node104_F23626ad8 *)s->p104)->p16;
    if (d == 0)
        return;
    if (d->h0 == 0)
        return;
    d->b4 = p->u.b.b4;
    d->b5 = p->u.f4 >> 8;
    v = p->u.b.h6;
    d->b6 = v;
}
#ifndef RAC2_T_REC_F4EC78016
#define RAC2_T_REC_F4EC78016
typedef struct Rec_F4ec78016 {
    int f0;
    unsigned char pad4[6];
    short h10;
    unsigned char pad12[20];
    int f32;
} Rec_F4ec78016;
#endif


#ifndef RAC2_T_SLOT_F4EC78016
#define RAC2_T_SLOT_F4EC78016
typedef struct Slot_F4ec78016 {
    int f0;
    unsigned char pad4[108];
} Slot_F4ec78016;
#endif


#ifndef RAC2_T_GLOBALS_F4EC78016
#define RAC2_T_GLOBALS_F4EC78016
typedef struct Globals_F4ec78016 {
    unsigned char pad0[108];
    short h108;
    short h110;
    short h112;
    unsigned char pad114[18];
    int f132;
} Globals_F4ec78016;
#endif


extern Slot_F4ec78016 LVL_5_FELTZIN_SYSTEM_F4ec78016_D_00188660[];
extern Globals_F4ec78016 LVL_5_FELTZIN_SYSTEM_F4ec78016_D_001A63A8[];

extern void LVL_5_FELTZIN_SYSTEM_F4ec78016_FUN_0033FAF0(int a, int b, int c, int d);

void LVL_5_FELTZIN_SYSTEM_FUN_00340FC0(void *a0, long a1)
{
    Rec_F4ec78016 *n = (Rec_F4ec78016 *)a1;
    Slot_F4ec78016 *p;
    int i;

    if (n == 0)
        return;
    n->f0 = (int)a0;
    i = n->f32;
    if (i >= 0) {
        p = LVL_5_FELTZIN_SYSTEM_F4ec78016_D_00188660 + i;
        *(int *)((char *)p + 112) = (int)a0;
    }
    if (a0 != 0) {
        if (n->h10 == 1)
            n->h10 = 2;
    } else {
        LVL_5_FELTZIN_SYSTEM_F4ec78016_FUN_0033FAF0(LVL_5_FELTZIN_SYSTEM_F4ec78016_D_001A63A8->h108, LVL_5_FELTZIN_SYSTEM_F4ec78016_D_001A63A8->h112, LVL_5_FELTZIN_SYSTEM_F4ec78016_D_001A63A8->f132, LVL_5_FELTZIN_SYSTEM_F4ec78016_D_001A63A8->h110);
    }
}
#ifndef RAC2_T_V4_FA012328C
#define RAC2_T_V4_FA012328C
typedef int V4_Fa012328c __attribute__((mode(TI)));
#endif


extern char LVL_5_FELTZIN_SYSTEM_Fa012328c_D_00189F20[];
extern char LVL_5_FELTZIN_SYSTEM_Fa012328c_D_00189F30[] __attribute__((sda));

extern void LVL_5_FELTZIN_SYSTEM_Fa012328c_FUN_002CC258(void);
extern void LVL_5_FELTZIN_SYSTEM_Fa012328c_FUN_003065F8(void *p);
extern void LVL_5_FELTZIN_SYSTEM_Fa012328c_FUN_003065F8(void *p);
extern void LVL_5_FELTZIN_SYSTEM_Fa012328c_FUN_003065F8(void *p);
extern void LVL_5_FELTZIN_SYSTEM_Fa012328c_FUN_003065F8(void *p);
extern void LVL_5_FELTZIN_SYSTEM_Fa012328c_FUN_003065F8(void *p);
extern void LVL_5_FELTZIN_SYSTEM_Fa012328c_FUN_003065F8(void *p);
extern void LVL_5_FELTZIN_SYSTEM_Fa012328c_FUN_003065F8(void *p);
extern void LVL_5_FELTZIN_SYSTEM_Fa012328c_FUN_003416B0(void);

void LVL_5_FELTZIN_SYSTEM_FUN_002CB450(void)
{
    char *p;

    *(volatile V4_Fa012328c *)LVL_5_FELTZIN_SYSTEM_Fa012328c_D_00189F30 = 0;
    LVL_5_FELTZIN_SYSTEM_Fa012328c_FUN_002CC258();
    p = LVL_5_FELTZIN_SYSTEM_Fa012328c_D_00189F20;
    LVL_5_FELTZIN_SYSTEM_Fa012328c_FUN_003065F8(p);
    LVL_5_FELTZIN_SYSTEM_Fa012328c_FUN_003065F8(p - 16);
    LVL_5_FELTZIN_SYSTEM_Fa012328c_FUN_003065F8(p + 16);
    LVL_5_FELTZIN_SYSTEM_Fa012328c_FUN_003065F8(p + 32);
    LVL_5_FELTZIN_SYSTEM_Fa012328c_FUN_003065F8(p + 48);
    LVL_5_FELTZIN_SYSTEM_Fa012328c_FUN_003065F8(p + 96);
    LVL_5_FELTZIN_SYSTEM_Fa012328c_FUN_003065F8(p - 96);
    p = p - 256;
    *(int *)(p + 420) = 0;
    *(int *)(p + 376) = 0;
    *(int *)(p + 368) = 0;
    LVL_5_FELTZIN_SYSTEM_Fa012328c_FUN_003416B0();
}
#ifndef RAC2_T_NODE16_FE48725C6
#define RAC2_T_NODE16_FE48725C6
typedef struct Node16_Fe48725c6 Node16_Fe48725c6;
#endif

#ifndef RAC2_T_NODE104_FE48725C6
#define RAC2_T_NODE104_FE48725C6
typedef struct Node104_Fe48725c6 Node104_Fe48725c6;
#endif

#ifndef RAC2_T_NODE24_FE48725C6
#define RAC2_T_NODE24_FE48725C6
typedef struct Node24_Fe48725c6 Node24_Fe48725c6;
#endif


struct Node16_Fe48725c6 {
    short h0;
    unsigned char pad2[2];
    unsigned char b4;
    unsigned char b5;
    unsigned char b6;
};

struct Node104_Fe48725c6 {
    unsigned char pad0[16];
    Node16_Fe48725c6 *p16;
};

struct Node24_Fe48725c6 {
    unsigned char pad0[52];
    unsigned short h52;
    unsigned char pad54[50];
    Node104_Fe48725c6 *p104;
};

#ifndef RAC2_T_OBJ_FE48725C6
#define RAC2_T_OBJ_FE48725C6
typedef struct Obj_Fe48725c6 {
    unsigned char pad0[4];
    union {
        int f4;
        struct {
            unsigned char b4;
            unsigned char b5;
            short h6;
        } b;
    } u;
    unsigned char pad8[12];
    Node24_Fe48725c6 *f24;
} Obj_Fe48725c6;
#endif


extern void LVL_5_FELTZIN_SYSTEM_Fe48725c6_FUN_0032A498(Node24_Fe48725c6 *a, unsigned char b, unsigned char c, unsigned char d);

void LVL_5_FELTZIN_SYSTEM_FUN_003FFBC0(Obj_Fe48725c6 *p)
{
    Node24_Fe48725c6 *s;
    Node16_Fe48725c6 *d;
    int v;

    LVL_5_FELTZIN_SYSTEM_Fe48725c6_FUN_0032A498(p->f24, p->u.b.b4, p->u.b.b5, p->u.b.h6);
    s = p->f24;
    if ((s->h52 & 0x20) == 0)
        return;
    d = ((Node104_Fe48725c6 *)s->p104)->p16;
    if (d == 0)
        return;
    if (d->h0 == 0)
        return;
    d->b4 = p->u.b.b4;
    d->b5 = p->u.f4 >> 8;
    v = p->u.b.h6;
    d->b6 = v;
}
extern int LVL_5_FELTZIN_SYSTEM_F9032bf17_D_001A904C __attribute__((sda));
extern void LVL_5_FELTZIN_SYSTEM_F9032bf17_FUN_004490D8(int *p, int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9, int a10);

void LVL_5_FELTZIN_SYSTEM_FUN_00324D30(int a0, int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9)
{
    int value = LVL_5_FELTZIN_SYSTEM_F9032bf17_D_001A904C;

    if (value != 0)
        LVL_5_FELTZIN_SYSTEM_F9032bf17_FUN_004490D8((int *)(value + 0x36F28), a0, a1, a2, a3, a4, a5, a6, a7, a8, a9);
}
extern void LVL_5_FELTZIN_SYSTEM_F7a8d0dad_FUN_00449838(char *a0);
extern void LVL_5_FELTZIN_SYSTEM_F7a8d0dad_FUN_00449A80(char *a0);
extern void LVL_5_FELTZIN_SYSTEM_F7a8d0dad_FUN_00449830(char *a0);

void LVL_5_FELTZIN_SYSTEM_FUN_00449A88(char *a0)
{
    if (*(float *)(*(int *)(a0 + 4)) == 0.0f)
        return;

    switch (*(int *)(a0 + 456))
    {
    case 0:
        LVL_5_FELTZIN_SYSTEM_F7a8d0dad_FUN_00449838(a0);
        break;
    case 2:
        LVL_5_FELTZIN_SYSTEM_F7a8d0dad_FUN_00449A80(a0);
        break;
    }

    LVL_5_FELTZIN_SYSTEM_F7a8d0dad_FUN_00449830(a0);
}
extern void LVL_5_FELTZIN_SYSTEM_F8e0a750e_FUN_00306660(float *p);
extern float LVL_5_FELTZIN_SYSTEM_F8e0a750e_FUN_00306790(float *p);
extern float LVL_5_FELTZIN_SYSTEM_F8e0a750e_FUN_00306CD0(float a, float b);
extern float LVL_5_FELTZIN_SYSTEM_F8e0a750e_FUN_00306CD0(float a, float b);
extern void LVL_5_FELTZIN_SYSTEM_F8e0a750e_FUN_00307668(float a, float b);
extern float LVL_5_FELTZIN_SYSTEM_F8e0a750e_FUN_00306760(float *p);

int LVL_5_FELTZIN_SYSTEM_FUN_002F2908(float *a0)
{
    float local[3];
    float t;

    LVL_5_FELTZIN_SYSTEM_F8e0a750e_FUN_00306660(local);
    a0[1] = LVL_5_FELTZIN_SYSTEM_F8e0a750e_FUN_00306CD0(LVL_5_FELTZIN_SYSTEM_F8e0a750e_FUN_00306790(local), local[2]);

    t = LVL_5_FELTZIN_SYSTEM_F8e0a750e_FUN_00306CD0(local[0], local[1]);
    LVL_5_FELTZIN_SYSTEM_F8e0a750e_FUN_00307668(t, a0[0]);
    a0[0] = t;

    a0[2] = LVL_5_FELTZIN_SYSTEM_F8e0a750e_FUN_00306760(local);

    return 0;
}



extern f32 LVL_5_FELTZIN_SYSTEM_Fe985fe67_FUN_00332C18(void);
extern f32 LVL_5_FELTZIN_SYSTEM_Fe985fe67_FUN_00332B50(f32, f32);
extern void LVL_5_FELTZIN_SYSTEM_Fe985fe67_FUN_0033B330(s32, f32, f32, f32);

void LVL_5_FELTZIN_SYSTEM_FUN_00332C60(s32 a0, f32 a1, f32 a2) {
    f32 x = LVL_5_FELTZIN_SYSTEM_Fe985fe67_FUN_00332C18();
    f32 y = LVL_5_FELTZIN_SYSTEM_Fe985fe67_FUN_00332C18();
    f32 z = LVL_5_FELTZIN_SYSTEM_Fe985fe67_FUN_00332B50(a1, a2);
    LVL_5_FELTZIN_SYSTEM_Fe985fe67_FUN_0033B330(a0, z, x, y);
}



#ifndef RAC2_T_V4S_F31E44309
#define RAC2_T_V4S_F31E44309
typedef struct {
    f32 x, y, z, w;
} V4S_F31e44309;
#endif


extern V4S_F31e44309 LVL_5_FELTZIN_SYSTEM_F31e44309_D_00189E20[];

extern void LVL_5_FELTZIN_SYSTEM_F31e44309_FUN_003066A0(V4S_F31e44309 *, V4S_F31e44309 *, f32);

void LVL_5_FELTZIN_SYSTEM_FUN_002CE998(f32 a0) {
    V4S_F31e44309 *p = &LVL_5_FELTZIN_SYSTEM_F31e44309_D_00189E20[17];
    LVL_5_FELTZIN_SYSTEM_F31e44309_FUN_003066A0(p, p, a0);
    LVL_5_FELTZIN_SYSTEM_F31e44309_FUN_003066A0(p + 1, p + 1, a0);
    LVL_5_FELTZIN_SYSTEM_F31e44309_FUN_003066A0(p - 2, p - 2, a0);
    LVL_5_FELTZIN_SYSTEM_F31e44309_FUN_003066A0(p + 5, p + 5, a0);
    LVL_5_FELTZIN_SYSTEM_F31e44309_D_00189E20[27].y = LVL_5_FELTZIN_SYSTEM_F31e44309_D_00189E20[27].y * a0;
}



#ifndef RAC2_T_V4_F36D8A248
#define RAC2_T_V4_F36D8A248
typedef struct {
    f32 x, y, z, w;
} V4_F36d8a248;
#endif


#ifndef RAC2_T_M4_F36D8A248
#define RAC2_T_M4_F36D8A248
typedef struct {
    V4_F36d8a248 r[4];
} M4_F36d8a248;
#endif


extern void LVL_5_FELTZIN_SYSTEM_F36d8a248_FUN_00306E98(M4_F36d8a248 *, V4_F36d8a248 *);
extern void LVL_5_FELTZIN_SYSTEM_F36d8a248_FUN_00307210(M4_F36d8a248 *, M4_F36d8a248 *, V4_F36d8a248 *);
extern void LVL_5_FELTZIN_SYSTEM_F36d8a248_FUN_00336A90(M4_F36d8a248 *, V4_F36d8a248 *);

void LVL_5_FELTZIN_SYSTEM_FUN_00339F00(u8 *a0, f32 a1, f32 a2, f32 a3) {
    V4_F36d8a248 in;
    M4_F36d8a248 m1;
    M4_F36d8a248 m2;
    in.x = a1;
    in.y = a2;
    in.z = a3;
    LVL_5_FELTZIN_SYSTEM_F36d8a248_FUN_00306E98(&m1, &in);
    LVL_5_FELTZIN_SYSTEM_F36d8a248_FUN_00306E98(&m2, (V4_F36d8a248 *)(a0 + 240));
    LVL_5_FELTZIN_SYSTEM_F36d8a248_FUN_00307210(&m2, &m2, &m1);
    LVL_5_FELTZIN_SYSTEM_F36d8a248_FUN_00336A90(&m2, (V4_F36d8a248 *)(a0 + 240));
}



extern f32 LVL_5_FELTZIN_SYSTEM_F53c67c85_FUN_00306C20(f32);
extern f32 LVL_5_FELTZIN_SYSTEM_F53c67c85_FUN_00307620(f32, f32);
extern void LVL_5_FELTZIN_SYSTEM_F53c67c85_FUN_003077C0(s32, s32, f32);

void LVL_5_FELTZIN_SYSTEM_FUN_0033CC88(f32 *a0, s32 a1, s32 a2, f32 a3) {
    f32 v = LVL_5_FELTZIN_SYSTEM_F53c67c85_FUN_00306C20(a0[0]);
    f32 s = v * 0.5f + 0.5f;
    a0[0] = LVL_5_FELTZIN_SYSTEM_F53c67c85_FUN_00307620(a0[0], a3);
    LVL_5_FELTZIN_SYSTEM_F53c67c85_FUN_003077C0(a1, a2, s);
}



#ifndef RAC2_T_V4_F6B9E759F
#define RAC2_T_V4_F6B9E759F
typedef struct {
    f32 x, y, z, w;
} V4_F6b9e759f;
#endif


#ifndef RAC2_T_M4_F6B9E759F
#define RAC2_T_M4_F6B9E759F
typedef struct {
    V4_F6b9e759f r[4];
} M4_F6b9e759f;
#endif


extern V4_F6b9e759f LVL_5_FELTZIN_SYSTEM_F6b9e759f_D_00189EA0[];

extern void LVL_5_FELTZIN_SYSTEM_F6b9e759f_FUN_00306E98(M4_F6b9e759f *, V4_F6b9e759f *);
extern void LVL_5_FELTZIN_SYSTEM_F6b9e759f_FUN_00307210(M4_F6b9e759f *, M4_F6b9e759f *, V4_F6b9e759f *);
extern void LVL_5_FELTZIN_SYSTEM_F6b9e759f_FUN_00336A90(M4_F6b9e759f *, V4_F6b9e759f *);

void LVL_5_FELTZIN_SYSTEM_FUN_002CC640(f32 a1, f32 a2, f32 a3) {
    V4_F6b9e759f in;
    M4_F6b9e759f m1;
    M4_F6b9e759f m2;
    in.x = a1;
    in.y = a2;
    in.z = a3;
    LVL_5_FELTZIN_SYSTEM_F6b9e759f_FUN_00306E98(&m1, &in);
    LVL_5_FELTZIN_SYSTEM_F6b9e759f_FUN_00306E98(&m2, &LVL_5_FELTZIN_SYSTEM_F6b9e759f_D_00189EA0[1]);
    LVL_5_FELTZIN_SYSTEM_F6b9e759f_FUN_00307210(&m2, &m2, &m1);
    LVL_5_FELTZIN_SYSTEM_F6b9e759f_FUN_00336A90(&m2, &LVL_5_FELTZIN_SYSTEM_F6b9e759f_D_00189EA0[1]);
}
extern float LVL_5_FELTZIN_SYSTEM_F741d8ff0_FUN_00307668(float x, float y);
extern float LVL_5_FELTZIN_SYSTEM_F741d8ff0_FUN_00306C08(float x);
extern float LVL_5_FELTZIN_SYSTEM_F741d8ff0_FUN_00307620(float x, float y);

float LVL_5_FELTZIN_SYSTEM_FUN_00332F70(float a, float b, float c)
{
    float t;
    float u;

    t = LVL_5_FELTZIN_SYSTEM_F741d8ff0_FUN_00307668(b, a);
    u = LVL_5_FELTZIN_SYSTEM_F741d8ff0_FUN_00306C08(c * 3.1415927f);
    t = t * 0.5f;
    return LVL_5_FELTZIN_SYSTEM_F741d8ff0_FUN_00307620(a, t * (1.0f - u));
}
extern void LVL_5_FELTZIN_SYSTEM_Fd534a00c_FUN_0033C3F8(void *a, void *b, int c);
extern void LVL_5_FELTZIN_SYSTEM_Fd534a00c_FUN_003068F8(float f, void *a, void *b);
extern void LVL_5_FELTZIN_SYSTEM_Fd534a00c_FUN_00306630(char *target, char *first, char *local);

extern int LVL_5_FELTZIN_SYSTEM_Fd534a00c_D_001A8FF0 __attribute__((sda));

void LVL_5_FELTZIN_SYSTEM_FUN_0033C548(void *p, float *a1, float *a2, float f)
{
    float buf[4];

    if (LVL_5_FELTZIN_SYSTEM_Fd534a00c_D_001A8FF0 == 0) {
        a1[2] = a2[2] - f;
    } else {
        LVL_5_FELTZIN_SYSTEM_Fd534a00c_FUN_0033C3F8(p, buf, 0);
        LVL_5_FELTZIN_SYSTEM_Fd534a00c_FUN_003068F8(f, buf, buf);
        LVL_5_FELTZIN_SYSTEM_Fd534a00c_FUN_00306630((char *)a1, (char *)a2, (char *)buf);
    }
}
extern void LVL_5_FELTZIN_SYSTEM_F652b70cf_FUN_004471C8(void *);
extern void LVL_5_FELTZIN_SYSTEM_F652b70cf_FUN_004476F0(void *);
extern void LVL_5_FELTZIN_SYSTEM_F652b70cf_FUN_00447988(void *);

void *LVL_5_FELTZIN_SYSTEM_FUN_0044B4C8(char *p)
{
    int i;
    char *q = p + 4;

    for (i = 3; i != -1; i--) {
        LVL_5_FELTZIN_SYSTEM_F652b70cf_FUN_004471C8(q);
        q += 76;
    }
    LVL_5_FELTZIN_SYSTEM_F652b70cf_FUN_004476F0(p + 308);
    LVL_5_FELTZIN_SYSTEM_F652b70cf_FUN_00447988(p + 368);
    return p;
}
extern void LVL_5_FELTZIN_SYSTEM_F9e73b90d_FUN_0044BF70();
extern void LVL_5_FELTZIN_SYSTEM_F9e73b90d_FUN_00366920();
extern void LVL_5_FELTZIN_SYSTEM_F9e73b90d_FUN_00447A98();
extern void LVL_5_FELTZIN_SYSTEM_F9e73b90d_FUN_00447A98();
extern void LVL_5_FELTZIN_SYSTEM_F9e73b90d_FUN_00447A98();
extern void LVL_5_FELTZIN_SYSTEM_F9e73b90d_FUN_00447848();
extern void LVL_5_FELTZIN_SYSTEM_F9e73b90d_FUN_00447340();
extern void LVL_5_FELTZIN_SYSTEM_F9e73b90d_FUN_00447A98();
extern void LVL_5_FELTZIN_SYSTEM_F9e73b90d_FUN_00447A98();
extern void LVL_5_FELTZIN_SYSTEM_F9e73b90d_FUN_0044FDB0();

void LVL_5_FELTZIN_SYSTEM_FUN_00450058(char *p)
{
    LVL_5_FELTZIN_SYSTEM_F9e73b90d_FUN_0044BF70(p + 8);
    LVL_5_FELTZIN_SYSTEM_F9e73b90d_FUN_00366920(0);
    LVL_5_FELTZIN_SYSTEM_F9e73b90d_FUN_00447A98(p + 744);
    LVL_5_FELTZIN_SYSTEM_F9e73b90d_FUN_00447A98(p + 816);
    LVL_5_FELTZIN_SYSTEM_F9e73b90d_FUN_00447A98(p + 888);
    LVL_5_FELTZIN_SYSTEM_F9e73b90d_FUN_00447848(p + 684);
    LVL_5_FELTZIN_SYSTEM_F9e73b90d_FUN_00447340(p + 960);
    LVL_5_FELTZIN_SYSTEM_F9e73b90d_FUN_00447A98(p + 1400);
    LVL_5_FELTZIN_SYSTEM_F9e73b90d_FUN_00447A98(p + 1328);
    LVL_5_FELTZIN_SYSTEM_F9e73b90d_FUN_0044FDB0(p);
}
extern int LVL_5_FELTZIN_SYSTEM_Fc40b1162_FUN_003062D0();
extern void LVL_5_FELTZIN_SYSTEM_Fc40b1162_FUN_003423C8();

void LVL_5_FELTZIN_SYSTEM_FUN_00348D00(char *p)
{
    if (LVL_5_FELTZIN_SYSTEM_Fc40b1162_FUN_003062D0(p + 10)) {
        LVL_5_FELTZIN_SYSTEM_Fc40b1162_FUN_003423C8(p);
    }
}
extern int LVL_5_FELTZIN_SYSTEM_Fc40b1162_FUN_003062D0();
extern void LVL_5_FELTZIN_SYSTEM_Fc40b1162_FUN_003423C8();

void LVL_5_FELTZIN_SYSTEM_FUN_00352950(char *p)
{
    if (LVL_5_FELTZIN_SYSTEM_Fc40b1162_FUN_003062D0(p + 10)) {
        LVL_5_FELTZIN_SYSTEM_Fc40b1162_FUN_003423C8(p);
    }
}
extern char LVL_5_FELTZIN_SYSTEM_F2dbfd8df_D_00189E20[];
extern char LVL_5_FELTZIN_SYSTEM_F2dbfd8df_D_001A63A8[];
extern short LVL_5_FELTZIN_SYSTEM_F2dbfd8df_D_00152C2A;

extern void LVL_5_FELTZIN_SYSTEM_F2dbfd8df_FUN_00340480();
extern void LVL_5_FELTZIN_SYSTEM_F2dbfd8df_FUN_003706D0();
extern void LVL_5_FELTZIN_SYSTEM_F2dbfd8df_FUN_0030CA58();
extern void LVL_5_FELTZIN_SYSTEM_F2dbfd8df_FUN_00372F68();

void LVL_5_FELTZIN_SYSTEM_FUN_003731F8(void)
{
    char *p = LVL_5_FELTZIN_SYSTEM_F2dbfd8df_D_00189E20;
    char *q;
    unsigned short v;

    if (*(int *)(p + 9420) <= 0) {
        *(int *)(p + 9420) = 1;
    }
    LVL_5_FELTZIN_SYSTEM_F2dbfd8df_FUN_00340480(0);

    q = LVL_5_FELTZIN_SYSTEM_F2dbfd8df_D_001A63A8;
    v = *(unsigned short *)(q + 114);
    if ((unsigned short)(v - 6) >= 2) {
        *(unsigned short *)(q + 114) = 5;
    }
    LVL_5_FELTZIN_SYSTEM_F2dbfd8df_FUN_003706D0();
    LVL_5_FELTZIN_SYSTEM_F2dbfd8df_FUN_0030CA58();
    LVL_5_FELTZIN_SYSTEM_F2dbfd8df_FUN_00372F68(0);
    LVL_5_FELTZIN_SYSTEM_F2dbfd8df_D_00152C2A = 0;
}
extern char LVL_5_FELTZIN_SYSTEM_F0a1df9d9_D_001A8F20[] __attribute__((sda));
extern void LVL_5_FELTZIN_SYSTEM_F0a1df9d9_FUN_00329960(int a, int b, void *c);
extern int LVL_5_FELTZIN_SYSTEM_F0a1df9d9_FUN_003C0D48(int a, void *b, int c, char *d, float e, float f, float g, float h);
void LVL_5_FELTZIN_SYSTEM_FUN_003BA6F8(int a0)
{
    int buf[4];
    int s0;
    int v;

    s0 = *(int *)(a0 + 104);
    LVL_5_FELTZIN_SYSTEM_F0a1df9d9_FUN_00329960(a0, 0, buf);
    v = LVL_5_FELTZIN_SYSTEM_F0a1df9d9_FUN_003C0D48(a0, buf, *(int *)(s0 + 16), LVL_5_FELTZIN_SYSTEM_F0a1df9d9_D_001A8F20, *(float *)(s0 + 24), 2.0f, 5.0f, 0.6f);
    if (v != 0) {
        *(int *)(v + 184) = a0;
    }
}
#ifndef RAC2_T_V4_FB6552688
#define RAC2_T_V4_FB6552688
typedef int V4_Fb6552688 __attribute__((mode(TI)));
#endif


extern char *LVL_5_FELTZIN_SYSTEM_Fb6552688_FUN_00379CA0(char *);
extern void LVL_5_FELTZIN_SYSTEM_Fb6552688_FUN_003068F8(V4_Fb6552688 *, char *, float);
extern void LVL_5_FELTZIN_SYSTEM_Fb6552688_FUN_00306630(char *, V4_Fb6552688 *, char *);
extern void LVL_5_FELTZIN_SYSTEM_Fb6552688_FUN_0037D3E0(char *);

void LVL_5_FELTZIN_SYSTEM_FUN_0037D308(char *a0)
{
    V4_Fb6552688 buf;
    char *p;

    p = LVL_5_FELTZIN_SYSTEM_Fb6552688_FUN_00379CA0(a0);
    if (p == 0)
        return;
    LVL_5_FELTZIN_SYSTEM_Fb6552688_FUN_003068F8(&buf, a0 + 192, 8.0f);
    LVL_5_FELTZIN_SYSTEM_Fb6552688_FUN_00306630(p + 96, &buf, a0 + 16);
    LVL_5_FELTZIN_SYSTEM_Fb6552688_FUN_0037D3E0(a0);
    *(int *)(p + 304) = 300;
}
extern void LVL_5_FELTZIN_SYSTEM_Fe824cd8c_FUN_00447340(char *);
extern void LVL_5_FELTZIN_SYSTEM_Fe824cd8c_FUN_00447340(char *);
extern void LVL_5_FELTZIN_SYSTEM_Fe824cd8c_FUN_00447340(char *);
extern void LVL_5_FELTZIN_SYSTEM_Fe824cd8c_FUN_00447340(char *);
extern void LVL_5_FELTZIN_SYSTEM_Fe824cd8c_FUN_00447A98(char *);
extern void LVL_5_FELTZIN_SYSTEM_Fe824cd8c_FUN_00452A70(char *);
extern void LVL_5_FELTZIN_SYSTEM_Fe824cd8c_FUN_00452A90(char *);
extern void LVL_5_FELTZIN_SYSTEM_Fe824cd8c_FUN_00452AB0(char *);

void LVL_5_FELTZIN_SYSTEM_FUN_00452C48(char *a0)
{
    if (*(int *)(a0 + 544) == 0)
        return;
    LVL_5_FELTZIN_SYSTEM_Fe824cd8c_FUN_00447340(a0);
    LVL_5_FELTZIN_SYSTEM_Fe824cd8c_FUN_00447340(a0 + 152);
    LVL_5_FELTZIN_SYSTEM_Fe824cd8c_FUN_00447340(a0 + 76);
    LVL_5_FELTZIN_SYSTEM_Fe824cd8c_FUN_00447340(a0 + 228);
    LVL_5_FELTZIN_SYSTEM_Fe824cd8c_FUN_00447A98(a0 + 464);
    LVL_5_FELTZIN_SYSTEM_Fe824cd8c_FUN_00452A70(a0);
    LVL_5_FELTZIN_SYSTEM_Fe824cd8c_FUN_00452A90(a0);
    LVL_5_FELTZIN_SYSTEM_Fe824cd8c_FUN_00452AB0(a0);
}
extern int LVL_5_FELTZIN_SYSTEM_F18321eff_D_001A79F0 __attribute__((sda));
extern int LVL_5_FELTZIN_SYSTEM_F18321eff_FUN_002EEFE0(int);
int LVL_5_FELTZIN_SYSTEM_FUN_002BF880(void)
{
    int v = LVL_5_FELTZIN_SYSTEM_F18321eff_D_001A79F0;
    int r = 0;
    if (v >= 8) {
        if (v < 10 || v == 19) {
            if (LVL_5_FELTZIN_SYSTEM_F18321eff_FUN_002EEFE0(1) != 0 || LVL_5_FELTZIN_SYSTEM_F18321eff_FUN_002EEFE0(2) != 0)
                r = 1;
        }
    }
    return r;
}
extern void LVL_5_FELTZIN_SYSTEM_F20b0faf7_FUN_002EC578(int, int);
extern void LVL_5_FELTZIN_SYSTEM_F20b0faf7_FUN_002EC4E8(int, int, float);
extern void LVL_5_FELTZIN_SYSTEM_F20b0faf7_FUN_002EC458(int, int);
extern void LVL_5_FELTZIN_SYSTEM_F20b0faf7_FUN_002EC3D8(int, int, float);

void LVL_5_FELTZIN_SYSTEM_FUN_002CB4D8(int a, int b, float x, float y)
{
    if (b != 0) {
        LVL_5_FELTZIN_SYSTEM_F20b0faf7_FUN_002EC578(a, a);
        LVL_5_FELTZIN_SYSTEM_F20b0faf7_FUN_002EC4E8(a, a, y);
    } else {
        LVL_5_FELTZIN_SYSTEM_F20b0faf7_FUN_002EC458(a, a);
        LVL_5_FELTZIN_SYSTEM_F20b0faf7_FUN_002EC3D8(a, a, y);
    }
}
extern float LVL_5_FELTZIN_SYSTEM_F5ff747c4_FUN_00307768(int);

float LVL_5_FELTZIN_SYSTEM_FUN_0033CBC0(int a0, int a1)
{
    float r = LVL_5_FELTZIN_SYSTEM_F5ff747c4_FUN_00307768(a0 % a1);
    float s = LVL_5_FELTZIN_SYSTEM_F5ff747c4_FUN_00307768(a1);

    return 2.0f * r * 3.1415927f / s - 3.1415927f;
}
extern void LVL_5_FELTZIN_SYSTEM_Fac72d004_FUN_0045A658(char *, int);
extern void LVL_5_FELTZIN_SYSTEM_Fac72d004_FUN_0045A658(char *, int);
extern void LVL_5_FELTZIN_SYSTEM_Fac72d004_FUN_0045A658(char *, int);
extern void LVL_5_FELTZIN_SYSTEM_Fac72d004_FUN_0045A658(char *, int);

void LVL_5_FELTZIN_SYSTEM_FUN_0045C028(char *p, int a1)
{
    *(int *)(p + 1012) = a1;
    if (*(int *)(p + 1024) == 0)
        return;
    *(int *)(p + 1024) = 0;
    *(int *)(p + 12) = 1;
    LVL_5_FELTZIN_SYSTEM_Fac72d004_FUN_0045A658(p + 468, 1);
    LVL_5_FELTZIN_SYSTEM_Fac72d004_FUN_0045A658(p + 604, 1);
    LVL_5_FELTZIN_SYSTEM_Fac72d004_FUN_0045A658(p + 740, 1);
    LVL_5_FELTZIN_SYSTEM_Fac72d004_FUN_0045A658(p + 876, 1);
}
extern int LVL_5_FELTZIN_SYSTEM_Fd1d0f3f8_FUN_00301AD0(char *, int);

void LVL_5_FELTZIN_SYSTEM_FUN_00448E50(char *p, int a1, int a2, float f12, float f13)
{
    char *q = p + 168;

    *(float *)(*(int *)p) = f12;
    *(float *)(*(int *)p + 4) = f13;
    p[423] = 0;
    *(int *)(p + 440) = a2;
    *(int *)(p + 472) = (int)q;
    *(int *)(p + 468) = LVL_5_FELTZIN_SYSTEM_Fd1d0f3f8_FUN_00301AD0(q, -1);
    *(int *)(p + 432) = 1;
    *(float *)(*(int *)(p + 4)) = 1.0f;
}
extern void LVL_5_FELTZIN_SYSTEM_Fe2589056_FUN_0030F3A0(char *, int);

void LVL_5_FELTZIN_SYSTEM_FUN_0030F228(char *p)
{
    int fp;

    LVL_5_FELTZIN_SYSTEM_Fe2589056_FUN_0030F3A0(p, *(int *)(p + 32));
    fp = *(int *)(p + 48);
    *(int *)(p + 4) = *(int *)(p + 36);
    *(int *)(p + 20) = *(int *)(p + 52);
    *(int *)(p + 24) = *(int *)(p + 56);
    *(int *)(p + 12) = *(int *)(p + 44);
    *(int *)(p + 8) = *(int *)(p + 40);
    *(int *)(p + 16) = fp;
    if (fp != 0)
        ((void (*)(char *))fp)(p);
    *(int *)(p + 104) = 0;
}
extern int LVL_5_FELTZIN_SYSTEM_Fe8d026c6_FUN_00369D58(int);
extern int LVL_5_FELTZIN_SYSTEM_Fe8d026c6_FUN_00369F08(int);
extern int LVL_5_FELTZIN_SYSTEM_Fe8d026c6_FUN_00355418(void);
extern int LVL_5_FELTZIN_SYSTEM_Fe8d026c6_FUN_0030B9A0(void);
extern int LVL_5_FELTZIN_SYSTEM_Fe8d026c6_FUN_0044A788(int);
extern int LVL_5_FELTZIN_SYSTEM_Fe8d026c6_D_001A904C __attribute__((sda));

int LVL_5_FELTZIN_SYSTEM_FUN_00368470(char *a0)
{
    int v;

    LVL_5_FELTZIN_SYSTEM_Fe8d026c6_FUN_00369D58(1);
    v = LVL_5_FELTZIN_SYSTEM_Fe8d026c6_FUN_00369F08(0);
    *(int *)(a0 + 76) = 0;
    *(int *)(a0 + 72) = v;
    LVL_5_FELTZIN_SYSTEM_Fe8d026c6_FUN_00355418();
    LVL_5_FELTZIN_SYSTEM_Fe8d026c6_FUN_0030B9A0();
    v = *(int *)0x1A8FD8;
    if (v != 0) {
        v = LVL_5_FELTZIN_SYSTEM_Fe8d026c6_D_001A904C;
        if (v != 0) {
            LVL_5_FELTZIN_SYSTEM_Fe8d026c6_FUN_0044A788(v + 0x3CAA8);
        }
    }
    return 0;
}


extern int LVL_5_FELTZIN_SYSTEM_F1c1f8608_FUN_003066A0(void *, void *, float);
extern int LVL_5_FELTZIN_SYSTEM_F1c1f8608_FUN_00306630(void *, void *, void *);
extern int LVL_5_FELTZIN_SYSTEM_F1c1f8608_FUN_003423C8(void *);

void LVL_5_FELTZIN_SYSTEM_FUN_0034B5B0(char *a0)
{
    char *p = a0;
    char *q = p + 32;
    int v;

    LVL_5_FELTZIN_SYSTEM_F1c1f8608_FUN_003066A0(q, q, 0.975f);
    LVL_5_FELTZIN_SYSTEM_F1c1f8608_FUN_00306630(p + 16, p + 16, q);
    *(float *)(p + 12) = *(float *)(p + 12) + 14700.0f;
    *(u8 *)(p + 8) = *(u8 *)(p + 8) + *(u8 *)(q + 16);
    v = *(int *)(p + 4) + 0xFE000000;
    *(int *)(p + 4) = v;
    if (v < 0) {
        LVL_5_FELTZIN_SYSTEM_F1c1f8608_FUN_003423C8(p);
    }
}
#ifndef RAC2_T_V4_F876460D6
#define RAC2_T_V4_F876460D6
typedef int V4_F876460d6 __attribute__((mode(TI)));
#endif


extern void LVL_5_FELTZIN_SYSTEM_F876460d6_FUN_003065F8(char *p);
extern float LVL_5_FELTZIN_SYSTEM_F876460d6_FUN_00306CD0(float a, float b);
extern void LVL_5_FELTZIN_SYSTEM_F876460d6_FUN_00306E98(char *dst, char *src);
extern void LVL_5_FELTZIN_SYSTEM_F876460d6_FUN_00307210(char *a, char *b, char *c);
extern float LVL_5_FELTZIN_SYSTEM_F876460d6_FUN_00306CD0(float a, float b);
extern void LVL_5_FELTZIN_SYSTEM_F876460d6_FUN_00306EB8(char *dst, char *src);
extern void LVL_5_FELTZIN_SYSTEM_F876460d6_FUN_00307210(char *a, char *b, char *c);
extern float LVL_5_FELTZIN_SYSTEM_F876460d6_FUN_00306CD0(float a, float b);

void LVL_5_FELTZIN_SYSTEM_FUN_00336A90(float *src, float *out)
{
    V4_F876460d6 tmp[4];
    float m[16];
    float local[4];
    float a, b, c;

    *(V4_F876460d6 *)(m + 0) = *(V4_F876460d6 *)(src + 0);
    *(V4_F876460d6 *)(m + 4) = *(V4_F876460d6 *)(src + 4);
    *(V4_F876460d6 *)(m + 8) = *(V4_F876460d6 *)(src + 8);
    *(V4_F876460d6 *)(m + 12) = *(V4_F876460d6 *)(src + 12);
    LVL_5_FELTZIN_SYSTEM_F876460d6_FUN_003065F8((char *)(m + 12));
    m[15] = 1.0f;
    a = LVL_5_FELTZIN_SYSTEM_F876460d6_FUN_00306CD0(m[0], m[1]);
    local[0] = 0.0f;
    local[1] = 0.0f;
    local[2] = -a;
    LVL_5_FELTZIN_SYSTEM_F876460d6_FUN_00306E98((char *)tmp, (char *)local);
    LVL_5_FELTZIN_SYSTEM_F876460d6_FUN_00307210((char *)m, (char *)tmp, (char *)m);
    b = LVL_5_FELTZIN_SYSTEM_F876460d6_FUN_00306CD0(m[0], -m[2]);
    local[0] = 0.0f;
    local[2] = 0.0f;
    local[1] = -b;
    LVL_5_FELTZIN_SYSTEM_F876460d6_FUN_00306EB8((char *)tmp, (char *)local);
    LVL_5_FELTZIN_SYSTEM_F876460d6_FUN_00307210((char *)m, (char *)tmp, (char *)m);
    c = LVL_5_FELTZIN_SYSTEM_F876460d6_FUN_00306CD0(m[5], m[6]);
    out[2] = a;
    out[1] = b;
    out[0] = c;
    local[1] = 0.0f;
    local[0] = -c;
    local[2] = 0.0f;
}
extern int LVL_5_FELTZIN_SYSTEM_F9a4b4d8b_FUN_003062D0(char *);
extern void LVL_5_FELTZIN_SYSTEM_F9a4b4d8b_FUN_003423C8(char *);
extern void LVL_5_FELTZIN_SYSTEM_F9a4b4d8b_FUN_00306630(char *, char *, char *);
extern void LVL_5_FELTZIN_SYSTEM_F9a4b4d8b_FUN_00394B90(char *, char *);

#ifndef RAC2_T_VEC16_F9A4B4D8B
#define RAC2_T_VEC16_F9A4B4D8B
typedef struct {
    float f[4];
} Vec16_F9a4b4d8b;
#endif


void LVL_5_FELTZIN_SYSTEM_FUN_00350488(char *obj)
{
    Vec16_F9a4b4d8b local;
    char *s1;
    char *s2;
    int a;
    int v1;

    if (LVL_5_FELTZIN_SYSTEM_F9a4b4d8b_FUN_003062D0(obj + 10) != 0) {
        LVL_5_FELTZIN_SYSTEM_F9a4b4d8b_FUN_003423C8(obj);
        return;
    }

    a = *(int *)(obj + 4);
    s1 = obj + 32;
    *(int *)(obj + 4) = (a & 0x00ffffff) | (((a >> 24) + *(unsigned char *)(s1 + 20)) << 24);

    s2 = obj + 16;
    local.f[0] = *(float *)(obj + 32);
    local.f[1] = *(float *)(s1 + 4);
    local.f[2] = *(float *)(s1 + 8);
    local.f[3] = 0.0f;
    LVL_5_FELTZIN_SYSTEM_F9a4b4d8b_FUN_00306630(s2, s2, (char *)&local);

    *(float *)(s1 + 8) = *(float *)(s1 + 8) - *(float *)(s1 + 12);

    if (*(float *)(obj + 28) != 0.0f) {
        if (*(float *)(obj + 28) == 2.0f)
            LVL_5_FELTZIN_SYSTEM_F9a4b4d8b_FUN_00394B90(s2, s2);
        *(float *)(obj + 28) = 2.0f;
    }
    v1 = *(unsigned char *)(s1 + 21);

    *(unsigned char *)(obj + 8) = *(unsigned char *)(obj + 8) + v1;
    *(float *)(obj + 12) += *(float *)(s1 + 16);
}
extern void LVL_5_FELTZIN_SYSTEM_F187f348a_FUN_003068F8(char *, char *, float);
extern void LVL_5_FELTZIN_SYSTEM_F187f348a_FUN_00306748(char *, char *, char *);
extern void LVL_5_FELTZIN_SYSTEM_F187f348a_FUN_003068F8(char *, char *, float);
extern void LVL_5_FELTZIN_SYSTEM_F187f348a_FUN_00306748(char *, char *, char *);

void LVL_5_FELTZIN_SYSTEM_FUN_003BD3E8(char *obj, char *arg)
{
    char *base = obj + 192;
    char *other = obj + 208;
    float one = 1.0f;

    LVL_5_FELTZIN_SYSTEM_F187f348a_FUN_003068F8(base, (char *)(*(int *)(obj + 104)), one);
    LVL_5_FELTZIN_SYSTEM_F187f348a_FUN_00306748(other, base, arg);
    LVL_5_FELTZIN_SYSTEM_F187f348a_FUN_003068F8(other, other, one);
    LVL_5_FELTZIN_SYSTEM_F187f348a_FUN_00306748(obj + 224, other, base);
}
extern void LVL_5_FELTZIN_SYSTEM_F187f348a_FUN_003068F8(char *, char *, float);
extern void LVL_5_FELTZIN_SYSTEM_F187f348a_FUN_00306748(char *, char *, char *);
extern void LVL_5_FELTZIN_SYSTEM_F187f348a_FUN_003068F8(char *, char *, float);
extern void LVL_5_FELTZIN_SYSTEM_F187f348a_FUN_00306748(char *, char *, char *);

void LVL_5_FELTZIN_SYSTEM_FUN_003FC368(char *obj, char *arg)
{
    char *base = obj + 192;
    char *other = obj + 208;
    float one = 1.0f;

    LVL_5_FELTZIN_SYSTEM_F187f348a_FUN_003068F8(base, (char *)(*(int *)(obj + 104)), one);
    LVL_5_FELTZIN_SYSTEM_F187f348a_FUN_00306748(other, base, arg);
    LVL_5_FELTZIN_SYSTEM_F187f348a_FUN_003068F8(other, other, one);
    LVL_5_FELTZIN_SYSTEM_F187f348a_FUN_00306748(obj + 224, other, base);
}
extern float LVL_5_FELTZIN_SYSTEM_F6417c3cd_FUN_00307668(float, float);
extern float LVL_5_FELTZIN_SYSTEM_F6417c3cd_FUN_003065A0(float);
extern void LVL_5_FELTZIN_SYSTEM_F6417c3cd_FUN_00307620(float, float);

void LVL_5_FELTZIN_SYSTEM_FUN_002F0358(char *obj, float p1, float p2, float p3, float p4, float p5)
{
    float r;
    float t;
    float d;
    float neg;

    r = LVL_5_FELTZIN_SYSTEM_F6417c3cd_FUN_00307668(p2, p1);
    t = *(float *)obj;
    d = p3 * r - p4 * t;
    t = t + d;
    *(float *)obj = t;

    if (p5 != 0.0f) {
        if (t > p5) {
            *(float *)obj = p5;
        } else {
            neg = -p5;
            if (t < neg)
                *(float *)obj = neg;
        }
    }

    if (LVL_5_FELTZIN_SYSTEM_F6417c3cd_FUN_003065A0(r) < *(float *)obj) {
        *(float *)obj = LVL_5_FELTZIN_SYSTEM_F6417c3cd_FUN_003065A0(r);
    } else if (*(float *)obj < -LVL_5_FELTZIN_SYSTEM_F6417c3cd_FUN_003065A0(r)) {
        *(float *)obj = -LVL_5_FELTZIN_SYSTEM_F6417c3cd_FUN_003065A0(r);
    }

    LVL_5_FELTZIN_SYSTEM_F6417c3cd_FUN_00307620(p1, *(float *)obj);
}
#ifndef RAC2_T_SRC_F66766F2B
#define RAC2_T_SRC_F66766F2B
typedef struct {
    char pad0[35];        /* 0   */
    unsigned char f35;    /* 35  */
    char pad36[8];        /* 36  */
    float f44;            /* 44  */
    unsigned char f48;    /* 48  */
    unsigned char f49;    /* 49  */
    unsigned short f50;   /* 50  */
    unsigned short f52;   /* 52  */
    char pad54[2];        /* 54  */
    long long f56;        /* 56  */
    char pad64[34];       /* 64  */
    unsigned char f98;    /* 98  */
    char pad99[21];       /* 99  */
    int f120;             /* 120 */
    unsigned short f124;  /* 124 */
    char pad126[26];      /* 126 */
    int f152;             /* 152 */
    char pad156[14];      /* 156 */
    short f170;           /* 170 */
} Src_F66766f2b;
#endif


#ifndef RAC2_T_LIST_F66766F2B
#define RAC2_T_LIST_F66766F2B
typedef struct {
    char pad0[256];       /* 0   */
    int a[4];             /* 256 */
    int b[4];             /* 272 */
    Src_F66766f2b *c[4];            /* 288 */
    float d[4];           /* 304 */
    int pad320;           /* 320 */
    Src_F66766f2b *src;             /* 324 */
    int count;            /* 328 */
} List_F66766f2b;
#endif


extern Src_F66766f2b *LVL_5_FELTZIN_SYSTEM_F66766f2b_FUN_00328508(short);

void LVL_5_FELTZIN_SYSTEM_FUN_00339FA8(List_F66766f2b *obj, int a1, int a2, float v)
{
    Src_F66766f2b *q;
    short n;

    if (obj->count == 4)
        return;
    if (a2 >= 9)
        return;

    q = LVL_5_FELTZIN_SYSTEM_F66766f2b_FUN_00328508(obj->src->f170);
    if (q == 0)
        return;

    n = q->f170;
    q->f124 = obj->src->f124;
    q->f50 = obj->src->f50;
    q->f56 = obj->src->f56;
    q->f44 = obj->src->f44;
    q->f120 = obj->src->f120;
    q->f49 = 1;
    q->f52 = 2058;
    q->f48 = 0;
    q->f152 = 0;
    if (n == 0)
        q->f98 = 0;
    q->f35 = a1;

    obj->b[obj->count] = a2;
    obj->a[obj->count] = a1;
    obj->d[obj->count] = v;
    obj->c[obj->count] = q;
    obj->count = obj->count + 1;
}
extern int LVL_5_FELTZIN_SYSTEM_F7b0b4597_FUN_00332AF8(int, int);
extern float LVL_5_FELTZIN_SYSTEM_F7b0b4597_FUN_00332B50(float, float);
extern float LVL_5_FELTZIN_SYSTEM_F7b0b4597_FUN_00332C18(void);
extern void LVL_5_FELTZIN_SYSTEM_F7b0b4597_FUN_00305768(char *, int, int, int, float, float, float);

void LVL_5_FELTZIN_SYSTEM_FUN_003B7960(int p0, int p1, int p2, int p3, float v)
{
    int r;
    float s;
    float t;

    r = LVL_5_FELTZIN_SYSTEM_F7b0b4597_FUN_00332AF8(p3 >> 1, p3);
    p2 = p2 | (r << 24);
    s = LVL_5_FELTZIN_SYSTEM_F7b0b4597_FUN_00332B50(v * 0.75f, v);
    s = s + s;
    t = LVL_5_FELTZIN_SYSTEM_F7b0b4597_FUN_00332C18();
    LVL_5_FELTZIN_SYSTEM_F7b0b4597_FUN_00305768((char *)p1, 44, p2, 1, s, 0.08f, t);
}
extern int LVL_5_FELTZIN_SYSTEM_F7b0b4597_FUN_00332AF8(int, int);
extern float LVL_5_FELTZIN_SYSTEM_F7b0b4597_FUN_00332B50(float, float);
extern float LVL_5_FELTZIN_SYSTEM_F7b0b4597_FUN_00332C18(void);
extern void LVL_5_FELTZIN_SYSTEM_F7b0b4597_FUN_00305768(char *, int, int, int, float, float, float);

void LVL_5_FELTZIN_SYSTEM_FUN_003F1CD0(int p0, int p1, int p2, int p3, float v)
{
    int r;
    float s;
    float t;

    r = LVL_5_FELTZIN_SYSTEM_F7b0b4597_FUN_00332AF8(p3 >> 1, p3);
    p2 = p2 | (r << 24);
    s = LVL_5_FELTZIN_SYSTEM_F7b0b4597_FUN_00332B50(v * 0.75f, v);
    s = s + s;
    t = LVL_5_FELTZIN_SYSTEM_F7b0b4597_FUN_00332C18();
    LVL_5_FELTZIN_SYSTEM_F7b0b4597_FUN_00305768((char *)p1, 44, p2, 1, s, 0.08f, t);
}
#ifndef RAC2_T_V4_FC6BD459E
#define RAC2_T_V4_FC6BD459E
typedef int V4_Fc6bd459e __attribute__((mode(TI)));
#endif


extern void LVL_5_FELTZIN_SYSTEM_Fc6bd459e_FUN_00306660(float *local, void *a1, void *a0);
extern float LVL_5_FELTZIN_SYSTEM_Fc6bd459e_FUN_00306760(float *local);
extern void LVL_5_FELTZIN_SYSTEM_Fc6bd459e_FUN_003357F0(void *a2, float r, float f1, float f2, float f3);
extern void LVL_5_FELTZIN_SYSTEM_Fc6bd459e_FUN_003068F8(float *local, float *local2, float v);
extern void LVL_5_FELTZIN_SYSTEM_Fc6bd459e_FUN_00306630(void *a0, void *a0b, float *local);
extern float LVL_5_FELTZIN_SYSTEM_Fc6bd459e_FUN_003065A0(float t);

float LVL_5_FELTZIN_SYSTEM_FUN_00335AB0(void *a0, void *a1, void *a2, float f1, float f2, float f3)
{
    float local[4];
    float r;
    float u;

    LVL_5_FELTZIN_SYSTEM_Fc6bd459e_FUN_00306660(local, a1, a0);
    r = LVL_5_FELTZIN_SYSTEM_Fc6bd459e_FUN_00306760(local);
    LVL_5_FELTZIN_SYSTEM_Fc6bd459e_FUN_003357F0(a2, r, f1, f2, f3);
    LVL_5_FELTZIN_SYSTEM_Fc6bd459e_FUN_003068F8(local, local, *(float *)a2);
    LVL_5_FELTZIN_SYSTEM_Fc6bd459e_FUN_00306630(a0, a0, local);
    r = r - *(float *)a2;
    u = LVL_5_FELTZIN_SYSTEM_Fc6bd459e_FUN_003065A0(r);
    if (!(u < f3 * 0.01f))
        return r;
    *(V4_Fc6bd459e *)a0 = *(V4_Fc6bd459e *)a1;
    *(float *)a2 = 0.0f;
    return *(float *)a2;
}
extern void  LVL_5_FELTZIN_SYSTEM_F856af239_FUN_0033B330(char *p, float a, float b, float c);
extern void  LVL_5_FELTZIN_SYSTEM_F856af239_FUN_00306630(char *p, char *q, char *r);
extern int   LVL_5_FELTZIN_SYSTEM_F856af239_FUN_002F6C50(void *a, void *b, int c, int d, int e);
extern void  LVL_5_FELTZIN_SYSTEM_F856af239_FUN_002EBF60(void *p, int n, float a, float b, float c);
extern void  LVL_5_FELTZIN_SYSTEM_F856af239_FUN_00306660(void *dst, void *src, void *arg);
extern float LVL_5_FELTZIN_SYSTEM_F856af239_FUN_00306CD0(float a, float b);
extern float LVL_5_FELTZIN_SYSTEM_F856af239_FUN_00306790(void *p);
extern char  LVL_5_FELTZIN_SYSTEM_F856af239_D_001B9580[];
extern char  LVL_5_FELTZIN_SYSTEM_F856af239_D_001BFB20[];
extern char  LVL_5_FELTZIN_SYSTEM_F856af239_D_00189E20[];

int LVL_5_FELTZIN_SYSTEM_FUN_002D2C90(void)
{
    char buf[48];
    char *base = LVL_5_FELTZIN_SYSTEM_F856af239_D_001B9580;
    char *res;
    float v;

    LVL_5_FELTZIN_SYSTEM_F856af239_FUN_0033B330(buf, 10.0f, *(float *)(base + 344), -*(float *)(base + 340));
    LVL_5_FELTZIN_SYSTEM_F856af239_FUN_00306630(buf, buf, base + 320);
    res = LVL_5_FELTZIN_SYSTEM_F856af239_D_00189E20;
    if (LVL_5_FELTZIN_SYSTEM_F856af239_FUN_002F6C50(base + 320, buf, 4, *(int *)(res + 8848), 0)) {
        LVL_5_FELTZIN_SYSTEM_F856af239_FUN_002EBF60(buf + 16, 1, 0.5f, 0.0f, 0.5f);
        LVL_5_FELTZIN_SYSTEM_F856af239_FUN_00306660(buf + 32, LVL_5_FELTZIN_SYSTEM_F856af239_D_001BFB20, buf + 16);
        v = LVL_5_FELTZIN_SYSTEM_F856af239_FUN_00306CD0(*(float *)(buf + 32), *(float *)(buf + 36));
        *(float *)(res + 3076) = v;
        v = LVL_5_FELTZIN_SYSTEM_F856af239_FUN_00306790(buf + 32);
        *(float *)(res + 3080) = LVL_5_FELTZIN_SYSTEM_F856af239_FUN_00306CD0(v, *(float *)(buf + 40));
        return 1;
    }
    return 0;
}
#ifndef RAC2_T_V4_F0FBA48D3
#define RAC2_T_V4_F0FBA48D3
typedef int V4_F0fba48d3 __attribute__((mode(TI)));
#endif


extern void LVL_5_FELTZIN_SYSTEM_F0fba48d3_FUN_00306660(void *b, void *c, void *d);
extern void LVL_5_FELTZIN_SYSTEM_F0fba48d3_FUN_003068F8(void *dst, void *src, float x);
extern void LVL_5_FELTZIN_SYSTEM_F0fba48d3_FUN_00306630(void *c, void *c2, void *s);
extern void LVL_5_FELTZIN_SYSTEM_F0fba48d3_FUN_00306660(void *b, void *c, void *p);
extern void LVL_5_FELTZIN_SYSTEM_F0fba48d3_FUN_003068F8(void *dst, void *src, float y);
extern void LVL_5_FELTZIN_SYSTEM_F0fba48d3_FUN_00306630(void *b, void *p, void *s);
extern void LVL_5_FELTZIN_SYSTEM_F0fba48d3_FUN_00306660(void *b, void *s, void *e);

void LVL_5_FELTZIN_SYSTEM_FUN_0043C0C8(char *a0, void *a1, void *a2, void *a3,
                                      void *a4, float t0, float t1)
{
    V4_F0fba48d3 b0, b1, b2, b3;
    void *p = (void *)(*(int *)(a0 + 112));

    p = (void *)((int)p + 176);

    LVL_5_FELTZIN_SYSTEM_F0fba48d3_FUN_00306660(&b0, a2, a3);
    LVL_5_FELTZIN_SYSTEM_F0fba48d3_FUN_003068F8(&b1, &b0, t0);
    LVL_5_FELTZIN_SYSTEM_F0fba48d3_FUN_00306630(a2, a2, &b1);
    LVL_5_FELTZIN_SYSTEM_F0fba48d3_FUN_00306660(&b2, a2, p);
    LVL_5_FELTZIN_SYSTEM_F0fba48d3_FUN_003068F8(&b2, &b2, t1);
    LVL_5_FELTZIN_SYSTEM_F0fba48d3_FUN_00306630(&b3, p, &b2);
    LVL_5_FELTZIN_SYSTEM_F0fba48d3_FUN_00306660(a1, &b3, a4);
}
extern float LVL_5_FELTZIN_SYSTEM_F21bf1d75_D_001A8900 __attribute__((sda));

extern void LVL_5_FELTZIN_SYSTEM_F21bf1d75_FUN_00306660(float *out, char *a, char *b);
extern void LVL_5_FELTZIN_SYSTEM_F21bf1d75_FUN_00306678(float *out, char *a, char *b, float k);
extern float LVL_5_FELTZIN_SYSTEM_F21bf1d75_FUN_00306760(float *v);
extern void LVL_5_FELTZIN_SYSTEM_F21bf1d75_FUN_003068F8(float *out, float *in, float k);

void LVL_5_FELTZIN_SYSTEM_FUN_0043D998(char *obj)
{
    char *p = *(char **)(obj + 112);
    char *r = p + 496;
    char *q = p + 352;
    float buf[4];
    float a, b, c;

    if (*(short *)(p + 16) <= 0) return;
    LVL_5_FELTZIN_SYSTEM_F21bf1d75_FUN_00306660(buf, p, p + 176);
    LVL_5_FELTZIN_SYSTEM_F21bf1d75_FUN_00306678((float *)q, q, (char *)buf, LVL_5_FELTZIN_SYSTEM_F21bf1d75_D_001A8900);
    a = LVL_5_FELTZIN_SYSTEM_F21bf1d75_FUN_00306760((float *)q);
    b = *(float *)(q + 44);
    if (b < a) {
        a = b;
        LVL_5_FELTZIN_SYSTEM_F21bf1d75_FUN_003068F8((float *)q, (float *)q, a);
        c = *(float *)(q + 44);
    } else {
        float d = b - *(float *)(r + 48);
        if (a < d) {
            a = d;
            LVL_5_FELTZIN_SYSTEM_F21bf1d75_FUN_003068F8((float *)q, (float *)q, a);
        }
        c = *(float *)(q + 44);
    }
    *(float *)(r + 48) = c - a;
}
extern float LVL_5_FELTZIN_SYSTEM_F8629a204_FUN_00306C20(float x);
extern float LVL_5_FELTZIN_SYSTEM_F8629a204_FUN_00306C20(float x);
extern float LVL_5_FELTZIN_SYSTEM_F8629a204_FUN_00306C20(float x);
extern float LVL_5_FELTZIN_SYSTEM_F8629a204_FUN_00306C08(float x);
extern float LVL_5_FELTZIN_SYSTEM_F8629a204_FUN_00307620(float x, float y);
extern float LVL_5_FELTZIN_SYSTEM_F8629a204_FUN_00307620(float x, float y);

void LVL_5_FELTZIN_SYSTEM_FUN_0033A758(float *out, float *p, float *q,
                                        float k1, float k2, float k3)
{
    out[60] = k1 * LVL_5_FELTZIN_SYSTEM_F8629a204_FUN_00306C20(*p) * LVL_5_FELTZIN_SYSTEM_F8629a204_FUN_00306C20(*q);
    out[61] = k1 * LVL_5_FELTZIN_SYSTEM_F8629a204_FUN_00306C20(*p) * LVL_5_FELTZIN_SYSTEM_F8629a204_FUN_00306C08(*q);
    *p = LVL_5_FELTZIN_SYSTEM_F8629a204_FUN_00307620(*p, k2);
    *q = LVL_5_FELTZIN_SYSTEM_F8629a204_FUN_00307620(*q, k3);
}
extern char LVL_5_FELTZIN_SYSTEM_F822bf205_D_00189E20[];

extern float LVL_5_FELTZIN_SYSTEM_F822bf205_FUN_00332B50(float a0, float a1);
extern void LVL_5_FELTZIN_SYSTEM_F822bf205_FUN_0034AFE8(float *a0, float *a1, int a2, float a3, float a4);
extern int LVL_5_FELTZIN_SYSTEM_F822bf205_FUN_00332AB8(char *a0);

void LVL_5_FELTZIN_SYSTEM_FUN_002C2CF8(char *self, int arg1)
{
    float v[3];
    int n;
    char *p;
    float r;

    p = LVL_5_FELTZIN_SYSTEM_F822bf205_D_00189E20;
    n = *(unsigned short *)(p + 2628) + 1;
    *(unsigned short *)(p + 2628) = n;
    if (arg1 < (short)n) {
        v[0] = *(float *)(p + 128) + LVL_5_FELTZIN_SYSTEM_F822bf205_FUN_00332B50(-0.05f, 0.05f);
        v[1] = *(float *)(p + 132) + LVL_5_FELTZIN_SYSTEM_F822bf205_FUN_00332B50(-0.05f, 0.05f);
        v[2] = *(float *)(p + 816);
        r = LVL_5_FELTZIN_SYSTEM_F822bf205_FUN_00332B50(0.4f, 0.6f);
        LVL_5_FELTZIN_SYSTEM_F822bf205_FUN_0034AFE8(v, (float *)(p + 816), -1, r, 5250.0f);
        *(unsigned short *)(p + 2628) = LVL_5_FELTZIN_SYSTEM_F822bf205_FUN_00332AB8(self);
    }
}
extern char LVL_5_FELTZIN_SYSTEM_Fd653e601_D_00189E20[];

extern void LVL_5_FELTZIN_SYSTEM_Fd653e601_FUN_00306B00(void *a, void *b, void *c);
extern void LVL_5_FELTZIN_SYSTEM_Fd653e601_FUN_00306B00(void *a, void *b, void *c);

void LVL_5_FELTZIN_SYSTEM_FUN_002EC578(float *dst, void *src, float scale)
{
    char *d = LVL_5_FELTZIN_SYSTEM_Fd653e601_D_00189E20;
    int v = *(unsigned char *)(d + 8899);

    switch (v) {
    case 0:
        dst[0] = dst[0] * scale;
        dst[1] = dst[1] * scale;
        break;
    case 1:
    case 2:
        LVL_5_FELTZIN_SYSTEM_Fd653e601_FUN_00306B00(dst, src, d + 64);
        dst[0] = dst[0] * scale;
        dst[1] = dst[1] * scale;
        LVL_5_FELTZIN_SYSTEM_Fd653e601_FUN_00306B00(dst, dst, d);
        break;
    }

}
extern int LVL_5_FELTZIN_SYSTEM_F4aea17e5_FUN_0030CBA8 ();
extern void LVL_5_FELTZIN_SYSTEM_F4aea17e5_FUN_00301F10 (int v, int p7, long k, int r, int m1);
extern int LVL_5_FELTZIN_SYSTEM_F4aea17e5_FUN_0030CBA8 ();
extern void LVL_5_FELTZIN_SYSTEM_F4aea17e5_FUN_003023E0 (int v, int p7, long k, int r, int m1);

int LVL_5_FELTZIN_SYSTEM_FUN_00355540 (int *p)
{
  int a = p[6];
  int t = p[8] >> 1;
  int diff = a - t;
  int sum = a + t;
  int r;

  r = LVL_5_FELTZIN_SYSTEM_F4aea17e5_FUN_0030CBA8 (4412);
  LVL_5_FELTZIN_SYSTEM_F4aea17e5_FUN_00301F10 (diff, p[7], (long) 0x80f0f0f0, r, -1);
  r = LVL_5_FELTZIN_SYSTEM_F4aea17e5_FUN_0030CBA8 (4408);
  LVL_5_FELTZIN_SYSTEM_F4aea17e5_FUN_003023E0 (sum, p[7], (long) 0x80f0f0f0, r, -1);
  return 0;
}
extern void LVL_5_FELTZIN_SYSTEM_F5979c03f_FUN_0044BE50 (char *object);
extern void LVL_5_FELTZIN_SYSTEM_F5979c03f_FUN_0044C040 (char *object, float x, float y);
extern int LVL_5_FELTZIN_SYSTEM_F5979c03f_FUN_00371A60 (int a, int b, int c);

int LVL_5_FELTZIN_SYSTEM_FUN_0044E5C8 (char *object, int flags)
{
  volatile unsigned char *g = (volatile unsigned char *) 0x1A7B96;
  float *vec;
  int discarded;

  LVL_5_FELTZIN_SYSTEM_F5979c03f_FUN_0044BE50 (object + 8);
  vec = *(float **) (object + 684);
  LVL_5_FELTZIN_SYSTEM_F5979c03f_FUN_0044C040 (object + 8, vec[0], vec[1]);

  if ((flags & 0x40) && *(int *) (object + 680) == 0)
    {
      discarded = LVL_5_FELTZIN_SYSTEM_F5979c03f_FUN_00371A60 (4, 0, 0);
      (void) discarded;
      *g = (*g < 1);
    }

  return (flags >> 6) & 1;
}
extern void LVL_5_FELTZIN_SYSTEM_F9ebc9e57_FUN_003063B8 (char *node, int zero, int size);

void LVL_5_FELTZIN_SYSTEM_FUN_00329690 (char *list, char *node)
{
  char *cur;

  if (node == 0)
    return;

  if (*(char **) (list + 84) == node)
    {
      *(char **) (list + 84) = *(char **) (node + 8);
    }
  else if (*(char **) (list + 84) != 0)
    {
      cur = *(char **) (list + 84);
      while (*(char **) (cur + 8) != 0 && *(char **) (cur + 8) != node)
        cur = *(char **) (cur + 8);
      if (*(char **) (cur + 8) == node)
        *(char **) (cur + 8) = *(char **) (node + 8);
    }
  LVL_5_FELTZIN_SYSTEM_F9ebc9e57_FUN_003063B8 (node, 0, 64);
}
extern void LVL_5_FELTZIN_SYSTEM_Fac2822b7_FUN_00306E10 (float *local);
extern void LVL_5_FELTZIN_SYSTEM_Fac2822b7_FUN_003957C8 (char *object, float a, float b, int flags, float d, float *local);

void LVL_5_FELTZIN_SYSTEM_FUN_00395688 (char *object, int flags, float a, float b, float c, float d)
{
  float local[16];

  if (flags >> 24)
    {
      c = c * *(float *) (object + 12);
      LVL_5_FELTZIN_SYSTEM_Fac2822b7_FUN_00306E10 (local);
      local[0] = c;
      local[10] = c;
      LVL_5_FELTZIN_SYSTEM_Fac2822b7_FUN_003957C8 (object, a, b, flags, d, local);
    }
}
extern float LVL_5_FELTZIN_SYSTEM_Fff49167b_FUN_00335D90 (float x, int a1, float y);
extern float LVL_5_FELTZIN_SYSTEM_Fff49167b_FUN_00307620 (float x, float y);
extern float LVL_5_FELTZIN_SYSTEM_Fff49167b_FUN_00335D90 (float x, int a1, float y);

void LVL_5_FELTZIN_SYSTEM_FUN_00335E58 (float *p, int a1, float fx, float fl)
{
  float v;

  v = LVL_5_FELTZIN_SYSTEM_Fff49167b_FUN_00335D90 (fx, a1, p[0]);
  if (fl < v)
    v = fl;
  else if (v < -fl)
    v = -fl;
  v = LVL_5_FELTZIN_SYSTEM_Fff49167b_FUN_00307620 (p[0], v);
  p[0] = v;
  LVL_5_FELTZIN_SYSTEM_Fff49167b_FUN_00335D90 (fx, a1, v);
}
extern char LVL_5_FELTZIN_SYSTEM_F99e18b77_D_00189E20[];
extern int LVL_5_FELTZIN_SYSTEM_F99e18b77_FUN_00307778(float value);
extern float LVL_5_FELTZIN_SYSTEM_F99e18b77_FUN_00307750(float *buffer, float value);
float LVL_5_FELTZIN_SYSTEM_FUN_002C27B0(float *table, int count)
{
    char *base = LVL_5_FELTZIN_SYSTEM_F99e18b77_D_00189E20;
    float buffer[4];
    float t;
    int index;
    int last;
    int previous;
    index = LVL_5_FELTZIN_SYSTEM_F99e18b77_FUN_00307778(*(float *)(base + 3128));
    last = count - 1;
    previous = (index + last) % count;
    if (*(int *)(base + 3112) & 2)
        previous = last;
    t = LVL_5_FELTZIN_SYSTEM_F99e18b77_FUN_00307750(buffer, *(float *)(base + 3128));
    return t * table[index] + (*(float *)(base + 3132) - t) * table[previous];
}
extern void LVL_5_FELTZIN_SYSTEM_F981a31f4_FUN_0032E728(char *a, int b, char *c, char *d);
extern void LVL_5_FELTZIN_SYSTEM_F981a31f4_FUN_003066A0(char *a, char *b, float f);
extern void LVL_5_FELTZIN_SYSTEM_F981a31f4_FUN_00306AD8(char *a, char *b, char *c);
extern void LVL_5_FELTZIN_SYSTEM_F981a31f4_FUN_00306630(char *a, char *b, char *c);

void LVL_5_FELTZIN_SYSTEM_FUN_00329960(char *a0, int a1, char *a2)
{
    char buf[80];
    float x;

    x = *(float *)(a0 + 44);
    *(int *)(buf + 64) = a1;
    x = x * 0.0009765625f;
    LVL_5_FELTZIN_SYSTEM_F981a31f4_FUN_0032E728(a0, 1, buf + 64, buf);
    LVL_5_FELTZIN_SYSTEM_F981a31f4_FUN_003066A0(a2, buf + 48, x);
    LVL_5_FELTZIN_SYSTEM_F981a31f4_FUN_00306AD8(a2, a2, a0 + 192);
    LVL_5_FELTZIN_SYSTEM_F981a31f4_FUN_00306630(a2, a2, a0 + 16);
}
extern unsigned char LVL_5_FELTZIN_SYSTEM_F67dd0d3f_D_00189E20[];

extern void LVL_5_FELTZIN_SYSTEM_F67dd0d3f_FUN_00306948(char *a, int b, float f);
extern void LVL_5_FELTZIN_SYSTEM_F67dd0d3f_FUN_00306B00(char *a, char *b, char *c);

void LVL_5_FELTZIN_SYSTEM_FUN_002EC458(char *a0, int a1, float f12)
{
    unsigned char *d = LVL_5_FELTZIN_SYSTEM_F67dd0d3f_D_00189E20;
    float f20;
    int v;

    f20 = f12;
    v = d[8899];
    if (v == 0) {
        LVL_5_FELTZIN_SYSTEM_F67dd0d3f_FUN_00306948(a0, a1, f12);
        return;
    }
    if (v < 0)
        return;
    if (v >= 3)
        return;
    LVL_5_FELTZIN_SYSTEM_F67dd0d3f_FUN_00306B00(a0, a1, (char *)d + 64);
    LVL_5_FELTZIN_SYSTEM_F67dd0d3f_FUN_00306948(a0, a0, f20);
    LVL_5_FELTZIN_SYSTEM_F67dd0d3f_FUN_00306B00(a0, a0, (char *)d);
}
extern char LVL_5_FELTZIN_SYSTEM_F280ccf7a_D_00189E20[];

extern int LVL_5_FELTZIN_SYSTEM_F280ccf7a_FUN_002EA620(int, int *, int *);

void LVL_5_FELTZIN_SYSTEM_FUN_002EA758(void)
{
    char *d = LVL_5_FELTZIN_SYSTEM_F280ccf7a_D_00189E20;
    int a;
    int b;
    int *o;

    if (*(unsigned char *)(d + 8884) != 0)
        return;
    if (*(int *)(d + 4916) != 2)
        return;
    if (LVL_5_FELTZIN_SYSTEM_F280ccf7a_FUN_002EA620(*(unsigned char *)(*(int *)(d + 8848) + 67), &a, &b) == 0)
        return;
    o = (int *)*(int *)(d + 4880);
    if (o != 0)
        *(float *)((char *)o + 72) = *(float *)(d + 3104);
    o = (int *)*(int *)(d + 4884);
    if (o != 0)
        *(float *)((char *)o + 72) = *(float *)(d + 3104);
}
#ifndef RAC2_T_S36_F39E097FB
#define RAC2_T_S36_F39E097FB
typedef struct { int w[9]; } S36_F39e097fb;
#endif


extern int LVL_5_FELTZIN_SYSTEM_F39e097fb_D_0018C0B0;
extern char LVL_5_FELTZIN_SYSTEM_F39e097fb_D_0018AA70[];
extern S36_F39e097fb LVL_5_FELTZIN_SYSTEM_F39e097fb_D_001A7F68;

extern void LVL_5_FELTZIN_SYSTEM_F39e097fb_FUN_00329A88(int, int, S36_F39e097fb *, char *);

void LVL_5_FELTZIN_SYSTEM_FUN_002C29F8(int a0)
{
    S36_F39e097fb buf;

    if (a0 == 0)
        a0 = LVL_5_FELTZIN_SYSTEM_F39e097fb_D_0018C0B0;
    buf = LVL_5_FELTZIN_SYSTEM_F39e097fb_D_001A7F68;
    LVL_5_FELTZIN_SYSTEM_F39e097fb_FUN_00329A88(a0, 9, &buf, LVL_5_FELTZIN_SYSTEM_F39e097fb_D_0018AA70);
}
extern void LVL_5_FELTZIN_SYSTEM_F7d9c8805_FUN_004471C8(int);
extern void LVL_5_FELTZIN_SYSTEM_F7d9c8805_FUN_00447988(int);
extern void LVL_5_FELTZIN_SYSTEM_F7d9c8805_FUN_00447988(int);
extern void LVL_5_FELTZIN_SYSTEM_F7d9c8805_FUN_00447988(int);

int LVL_5_FELTZIN_SYSTEM_FUN_0044BB78(int a0)
{
	char *p = (char *)a0 + 12;
	int i;

	for (i = 4; i != -1; i--) {
		LVL_5_FELTZIN_SYSTEM_F7d9c8805_FUN_004471C8(p);
		p += 76;
	}
	LVL_5_FELTZIN_SYSTEM_F7d9c8805_FUN_00447988(a0 + 408);
	LVL_5_FELTZIN_SYSTEM_F7d9c8805_FUN_00447988(a0 + 480);
	LVL_5_FELTZIN_SYSTEM_F7d9c8805_FUN_00447988(a0 + 552);
	return a0;
}
extern void LVL_5_FELTZIN_SYSTEM_Fac6231ce_FUN_00306660(float *, int, int);
extern void LVL_5_FELTZIN_SYSTEM_Fac6231ce_FUN_00307120(float *, int);
extern void LVL_5_FELTZIN_SYSTEM_Fac6231ce_FUN_00306B00(float *, float *, float *);

float LVL_5_FELTZIN_SYSTEM_FUN_003364C8(int a0, int a1, int a2, int a3)
{
	float v[24];
	float *m = v + 4;

	LVL_5_FELTZIN_SYSTEM_Fac6231ce_FUN_00306660(v, a2, a0);
	LVL_5_FELTZIN_SYSTEM_Fac6231ce_FUN_00307120(v + 8, a1);
	LVL_5_FELTZIN_SYSTEM_Fac6231ce_FUN_00306B00(m, v, v + 8);
	return m[a3];
}
extern int LVL_5_FELTZIN_SYSTEM_F09d4d860_FUN_003416C8(int, int, int *);
extern int LVL_5_FELTZIN_SYSTEM_F09d4d860_FUN_00306588(int);

int LVL_5_FELTZIN_SYSTEM_FUN_00341768(int a0, int a1, int a2, int a3)
{
	int r = 0;
	int a;
	int b;

	if (LVL_5_FELTZIN_SYSTEM_F09d4d860_FUN_003416C8(a0, a2, &a)) {
		if (LVL_5_FELTZIN_SYSTEM_F09d4d860_FUN_003416C8(a1, a2, &b))
			r = LVL_5_FELTZIN_SYSTEM_F09d4d860_FUN_00306588(a - b) < a3;
	}
	return r;
}
extern char LVL_5_FELTZIN_SYSTEM_F79501aca_D_0014B540[];
extern short LVL_5_FELTZIN_SYSTEM_F79501aca_D_00152CE4[];
void LVL_5_FELTZIN_SYSTEM_F79501aca_FUN_0031D030(int, int, int, int);

void LVL_5_FELTZIN_SYSTEM_FUN_0031D958(int id, int arg)
{
    int i;
    int *p = (int *)LVL_5_FELTZIN_SYSTEM_F79501aca_D_0014B540;

    for (i = 0; i < 48; i++) {
        if (p[i * 5 + 4816] == id)
            break;
    }
    if (i != 48) {
        LVL_5_FELTZIN_SYSTEM_F79501aca_D_00152CE4[0] = (short)i;
        LVL_5_FELTZIN_SYSTEM_F79501aca_FUN_0031D030(i, -1, arg, 1);
    }
}
extern int LVL_5_FELTZIN_SYSTEM_F1bd62089_D_001A904C __attribute__((sda));
extern int LVL_5_FELTZIN_SYSTEM_F1bd62089_FUN_004528E8(int a, int b);

int LVL_5_FELTZIN_SYSTEM_FUN_003259F0(int a0)
{
    int v = LVL_5_FELTZIN_SYSTEM_F1bd62089_D_001A904C;

    if (v != 0) {
        return LVL_5_FELTZIN_SYSTEM_F1bd62089_FUN_004528E8(v + 0x3BE08, a0);
    }
    return 0;
}
extern int LVL_5_FELTZIN_SYSTEM_F1bd62089_D_001A904C __attribute__((sda));
extern int LVL_5_FELTZIN_SYSTEM_F1bd62089_FUN_004528E8(int a, int b);

int LVL_5_FELTZIN_SYSTEM_FUN_00325A60(int a0)
{
    int v = LVL_5_FELTZIN_SYSTEM_F1bd62089_D_001A904C;

    if (v != 0) {
        return LVL_5_FELTZIN_SYSTEM_F1bd62089_FUN_004528E8(v + 0x3BE08, a0);
    }
    return 0;
}
extern int LVL_5_FELTZIN_SYSTEM_Fbd51b1fa_D_001A904C __attribute__((sda));
extern int LVL_5_FELTZIN_SYSTEM_Fbd51b1fa_FUN_004497C8(int a, int b, int c);

int LVL_5_FELTZIN_SYSTEM_FUN_00326198(int a0, int a1)
{
    int v = LVL_5_FELTZIN_SYSTEM_Fbd51b1fa_D_001A904C;

    if (v == 0) return a0;
    return LVL_5_FELTZIN_SYSTEM_Fbd51b1fa_FUN_004497C8(v + 0x36F28, a0, a1);
}
extern int LVL_5_FELTZIN_SYSTEM_Fbd51b1fa_D_001A904C __attribute__((sda));
extern int LVL_5_FELTZIN_SYSTEM_Fbd51b1fa_FUN_00449060(int a, int b, int c);

int LVL_5_FELTZIN_SYSTEM_FUN_003261D8(int a0, int a1)
{
    int v = LVL_5_FELTZIN_SYSTEM_Fbd51b1fa_D_001A904C;

    if (v == 0) return a0;
    return LVL_5_FELTZIN_SYSTEM_Fbd51b1fa_FUN_00449060(v + 0x36F28, a0, a1);
}
extern void LVL_5_FELTZIN_SYSTEM_Ffee684c2_FUN_00390558(int);
extern void LVL_5_FELTZIN_SYSTEM_Ffee684c2_FUN_00307B40(void);
extern void LVL_5_FELTZIN_SYSTEM_Ffee684c2_FUN_00307DA8(int, int, int, int, int, int);
extern void LVL_5_FELTZIN_SYSTEM_Ffee684c2_FUN_00307DA8(int, int, int, int, int, int);

void LVL_5_FELTZIN_SYSTEM_FUN_003092D8(void)
{
    LVL_5_FELTZIN_SYSTEM_Ffee684c2_FUN_00390558(1);
    LVL_5_FELTZIN_SYSTEM_Ffee684c2_FUN_00307B40();
    if (*(int *)0x001A7BB8 != 0)
        LVL_5_FELTZIN_SYSTEM_Ffee684c2_FUN_00307DA8(512, 416, 640, 448, 0, 0);
    else
        LVL_5_FELTZIN_SYSTEM_Ffee684c2_FUN_00307DA8(512, 416, 512, 448, 0, 0);
}
extern char LVL_5_FELTZIN_SYSTEM_Fcc134e7e_D_00189E20[];
extern void LVL_5_FELTZIN_SYSTEM_Fcc134e7e_FUN_00328870(int);

struct S {
    char pad[52];
    unsigned short flags;
};

void LVL_5_FELTZIN_SYSTEM_FUN_002E2CF8(void)
{
    char *g = LVL_5_FELTZIN_SYSTEM_Fcc134e7e_D_00189E20;
    int v;
    struct S *p;
    struct S *q;

    v = *(int *)(g + 6228);
    if (v != 0) {
        LVL_5_FELTZIN_SYSTEM_Fcc134e7e_FUN_00328870(v);
        *(int *)(g + 6228) = 0;
    }
    p = *(struct S **)(g + 4880);
    if (p != 0)
        p->flags &= ~0x41;
    q = *(struct S **)(g + 4884);
    if (q != 0)
        q->flags &= ~0x41;
}
extern void LVL_5_FELTZIN_SYSTEM_F10bf3d29_FUN_00307120(char *a, char *b);
extern void LVL_5_FELTZIN_SYSTEM_F10bf3d29_FUN_00306AD8(char *a, char *b, char *c);
extern void LVL_5_FELTZIN_SYSTEM_F10bf3d29_FUN_00306AD8(char *a, char *b, char *c);

void LVL_5_FELTZIN_SYSTEM_FUN_0033C278(char *a0, char *a1, char *a2, char *a3)
{
    char buf[64];

    if (a3 == 0) {
        LVL_5_FELTZIN_SYSTEM_F10bf3d29_FUN_00307120(buf, a0 + 192);
        LVL_5_FELTZIN_SYSTEM_F10bf3d29_FUN_00306AD8(a1, a2, buf);
    } else {
        LVL_5_FELTZIN_SYSTEM_F10bf3d29_FUN_00306AD8(a1, a2, a3);
    }
}
extern void LVL_5_FELTZIN_SYSTEM_F3b16bab7_FUN_00447340(char *a);
extern void LVL_5_FELTZIN_SYSTEM_F3b16bab7_FUN_00447340(char *a);
extern void LVL_5_FELTZIN_SYSTEM_F3b16bab7_FUN_00447340(char *a);
extern void LVL_5_FELTZIN_SYSTEM_F3b16bab7_FUN_00447340(char *a);
extern void LVL_5_FELTZIN_SYSTEM_F3b16bab7_FUN_00447A98(char *a);
extern void LVL_5_FELTZIN_SYSTEM_F3b16bab7_FUN_00447A98(char *a);
extern void LVL_5_FELTZIN_SYSTEM_F3b16bab7_FUN_00447A98(char *a);

void LVL_5_FELTZIN_SYSTEM_FUN_0044A5B8(char *a0)
{
    if (*(int *)(a0 + 664) == 0)
        return;
    LVL_5_FELTZIN_SYSTEM_F3b16bab7_FUN_00447340(a0 + 8);
    LVL_5_FELTZIN_SYSTEM_F3b16bab7_FUN_00447340(a0 + 84);
    LVL_5_FELTZIN_SYSTEM_F3b16bab7_FUN_00447340(a0 + 160);
    LVL_5_FELTZIN_SYSTEM_F3b16bab7_FUN_00447340(a0 + 236);
    LVL_5_FELTZIN_SYSTEM_F3b16bab7_FUN_00447A98(a0 + 312);
    LVL_5_FELTZIN_SYSTEM_F3b16bab7_FUN_00447A98(a0 + 384);
    LVL_5_FELTZIN_SYSTEM_F3b16bab7_FUN_00447A98(a0 + 456);
}
extern int LVL_5_FELTZIN_SYSTEM_F489adc25_FUN_0030C1E8(int a, char *b);
extern void LVL_5_FELTZIN_SYSTEM_F489adc25_FUN_0030BF08(int a);

void LVL_5_FELTZIN_SYSTEM_FUN_00314938(char *a0)
{
    int i;

    for (i = 0; i < 56; i++) {
        if (LVL_5_FELTZIN_SYSTEM_F489adc25_FUN_0030C1E8(i, a0) == 0)
            continue;
        if (i != 0)
            LVL_5_FELTZIN_SYSTEM_F489adc25_FUN_0030BF08(i);
    }
}
extern int LVL_5_FELTZIN_SYSTEM_F4f96b231_FUN_0030CBA8(int a);
extern void LVL_5_FELTZIN_SYSTEM_F4f96b231_FUN_00447A58(char *a, int b);

void LVL_5_FELTZIN_SYSTEM_FUN_00459668(char *a0, int a1, int *a2)
{
    int i;

    *(int *)(a0 + 1092) = a1;
    for (i = 0; i < a1; i++)
        LVL_5_FELTZIN_SYSTEM_F4f96b231_FUN_00447A58(a0 + 536 + i * 72, LVL_5_FELTZIN_SYSTEM_F4f96b231_FUN_0030CBA8(a2[i]));
}
extern float LVL_5_FELTZIN_SYSTEM_F77438389_FUN_00306C20(float x);
extern void LVL_5_FELTZIN_SYSTEM_F77438389_FUN_003066A0(void *a0, int a1, float x);
extern float LVL_5_FELTZIN_SYSTEM_F77438389_FUN_00306C08(float x);

void LVL_5_FELTZIN_SYSTEM_FUN_00336928(void *a0, int a1, float x)
{
    float h = x * 0.5f;
    float t = LVL_5_FELTZIN_SYSTEM_F77438389_FUN_00306C20(h);

    LVL_5_FELTZIN_SYSTEM_F77438389_FUN_003066A0(a0, a1, t);
    *(float *)((char *)a0 + 12) = LVL_5_FELTZIN_SYSTEM_F77438389_FUN_00306C08(h);
}
extern int LVL_5_FELTZIN_SYSTEM_F8fdb4153_FUN_00462F60(void *a0);

int LVL_5_FELTZIN_SYSTEM_FUN_00462F70(volatile int *a0)
{
    int d, n;

    if (LVL_5_FELTZIN_SYSTEM_F8fdb4153_FUN_00462F60((void *)a0) != 0)
        return 0;
    d = a0[2] - a0[3];
    n = a0[4];
    d = d + n;
    return a0[1] + (d % n) * 0x138c0;
}
extern void LVL_5_FELTZIN_SYSTEM_Fabac7e02_FUN_004471C8(void *p);
extern void LVL_5_FELTZIN_SYSTEM_Fabac7e02_FUN_004471C8(void *p);
extern void LVL_5_FELTZIN_SYSTEM_Fabac7e02_FUN_004471C8(void *p);
extern void LVL_5_FELTZIN_SYSTEM_Fabac7e02_FUN_004471C8(void *p);
extern void LVL_5_FELTZIN_SYSTEM_Fabac7e02_FUN_00447988(void *p);
extern void LVL_5_FELTZIN_SYSTEM_Fabac7e02_FUN_00447988(void *p);
extern void LVL_5_FELTZIN_SYSTEM_Fabac7e02_FUN_00447988(void *p);
extern void LVL_5_FELTZIN_SYSTEM_Fabac7e02_FUN_00447988(void *p);

void *LVL_5_FELTZIN_SYSTEM_FUN_0044A030(char *a0)
{
    LVL_5_FELTZIN_SYSTEM_Fabac7e02_FUN_004471C8(a0 + 8);
    LVL_5_FELTZIN_SYSTEM_Fabac7e02_FUN_004471C8(a0 + 84);
    LVL_5_FELTZIN_SYSTEM_Fabac7e02_FUN_004471C8(a0 + 160);
    LVL_5_FELTZIN_SYSTEM_Fabac7e02_FUN_004471C8(a0 + 236);
    LVL_5_FELTZIN_SYSTEM_Fabac7e02_FUN_00447988(a0 + 312);
    LVL_5_FELTZIN_SYSTEM_Fabac7e02_FUN_00447988(a0 + 384);
    LVL_5_FELTZIN_SYSTEM_Fabac7e02_FUN_00447988(a0 + 456);
    LVL_5_FELTZIN_SYSTEM_Fabac7e02_FUN_00447988(a0 + 528);
    return a0;
}
extern void LVL_5_FELTZIN_SYSTEM_Fce0d9a7a_FUN_00447EF0(int a, int b);

void LVL_5_FELTZIN_SYSTEM_FUN_00446ED0(char *a0, int a1)
{
    if (a1 != *(int *)(a0 + 4)) {
        if (*(int *)(a0 + 44) != 0 && *(int *)(a0 + 24) == 0) {
            LVL_5_FELTZIN_SYSTEM_Fce0d9a7a_FUN_00447EF0(*(int *)(a0 + 44), *(int *)(a0 + 4));
            *(int *)(a0 + 24) = 1;
        }
        *(int *)(a0 + 4) = a1;
    }
}
extern int LVL_5_FELTZIN_SYSTEM_F0a35c0b5_FUN_002EEFC0(void);
extern int LVL_5_FELTZIN_SYSTEM_F0a35c0b5_D_0018C0B4;

int LVL_5_FELTZIN_SYSTEM_FUN_002EF0B8(void)
{
    int result = 0;
    int mode;
    if (LVL_5_FELTZIN_SYSTEM_F0a35c0b5_FUN_002EEFC0() != 0) goto out;
    if (LVL_5_FELTZIN_SYSTEM_F0a35c0b5_D_0018C0B4 != 49) goto out;
    mode = *(int *)0x001A79F0;
    if (mode != 4 && mode != 11) goto out;
    result = 1;
out:
    return result;
}
extern void LVL_5_FELTZIN_SYSTEM_Fc2cf0de2_FUN_0043E750(int);
extern void LVL_5_FELTZIN_SYSTEM_Fc2cf0de2_FUN_0043D998(int);
extern void LVL_5_FELTZIN_SYSTEM_Fc2cf0de2_FUN_0043D4A0(int, float *, float *);
extern void LVL_5_FELTZIN_SYSTEM_Fc2cf0de2_FUN_0043D620(int, float, float);
extern void LVL_5_FELTZIN_SYSTEM_Fc2cf0de2_FUN_0043C8C8(int);
extern void LVL_5_FELTZIN_SYSTEM_Fc2cf0de2_FUN_0043E1D8(int);
extern void LVL_5_FELTZIN_SYSTEM_Fc2cf0de2_FUN_0043DA68(int);

void LVL_5_FELTZIN_SYSTEM_FUN_0043E848(int object)
{
    float x;
    float y;

    LVL_5_FELTZIN_SYSTEM_Fc2cf0de2_FUN_0043E750(object);
    LVL_5_FELTZIN_SYSTEM_Fc2cf0de2_FUN_0043D998(object);
    LVL_5_FELTZIN_SYSTEM_Fc2cf0de2_FUN_0043D4A0(object, &x, &y);
    LVL_5_FELTZIN_SYSTEM_Fc2cf0de2_FUN_0043D620(object, x, y);
    LVL_5_FELTZIN_SYSTEM_Fc2cf0de2_FUN_0043C8C8(object);
    LVL_5_FELTZIN_SYSTEM_Fc2cf0de2_FUN_0043E1D8(object);
    LVL_5_FELTZIN_SYSTEM_Fc2cf0de2_FUN_0043DA68(object);
}
extern void LVL_5_FELTZIN_SYSTEM_Fd59cca7a_D_00115AC0(void *, int, int);
extern void LVL_5_FELTZIN_SYSTEM_Fd59cca7a_FUN_00448EB8(void *, int, int, float, float);

void LVL_5_FELTZIN_SYSTEM_FUN_004497C8(int object, int value, int count)
{
    int limit = (count == -1) ? 180 : count;
    int inner = object + 7532;

    LVL_5_FELTZIN_SYSTEM_Fd59cca7a_D_00115AC0((void *)(object + 7700), value, 254);
    LVL_5_FELTZIN_SYSTEM_Fd59cca7a_FUN_00448EB8((void *)inner, 1, limit, 255.0f, 123.0f);
}
extern void LVL_5_FELTZIN_SYSTEM_Fe68884be_D_00115AC0(void *, int, int);
extern void LVL_5_FELTZIN_SYSTEM_Fe68884be_FUN_00448EB8(void *, int, int, float, float);

void LVL_5_FELTZIN_SYSTEM_FUN_00449060(int object, int value, int count)
{
    int limit = (count == -1) ? 360 : count;
    int inner = object + 8124;

    LVL_5_FELTZIN_SYSTEM_Fe68884be_D_00115AC0((void *)(object + 8292), value, 255);
    LVL_5_FELTZIN_SYSTEM_Fe68884be_FUN_00448EB8((void *)inner, 1, limit, 255.0f, 80.0f);
}
extern void LVL_5_FELTZIN_SYSTEM_F076896f4_FUN_0045AAE0(void *, int);
extern void LVL_5_FELTZIN_SYSTEM_F076896f4_FUN_0045AAE0(void *, int);
extern void LVL_5_FELTZIN_SYSTEM_F076896f4_FUN_0045AAE0(void *, int);
extern void LVL_5_FELTZIN_SYSTEM_F076896f4_FUN_0045AAE0(void *, int);

void LVL_5_FELTZIN_SYSTEM_FUN_0045DE50(int *self, int value)
{
    self[1371] = value;
    if (self[1372] != 0) {
        self[1372] = 0;
        LVL_5_FELTZIN_SYSTEM_F076896f4_FUN_0045AAE0((char *)self + 4596, 0);
        LVL_5_FELTZIN_SYSTEM_F076896f4_FUN_0045AAE0((char *)self + 4744, 0);
        LVL_5_FELTZIN_SYSTEM_F076896f4_FUN_0045AAE0((char *)self + 4892, 0);
        LVL_5_FELTZIN_SYSTEM_F076896f4_FUN_0045AAE0((char *)self + 5040, 0);
    }
}


extern void LVL_5_FELTZIN_SYSTEM_F4c55616a_FUN_004471C8(u8 *);
extern void LVL_5_FELTZIN_SYSTEM_F4c55616a_FUN_004476F0(u8 *);
extern void LVL_5_FELTZIN_SYSTEM_F4c55616a_FUN_00447988(u8 *);
extern void LVL_5_FELTZIN_SYSTEM_F4c55616a_FUN_004537D8(u8 *);

u8 *LVL_5_FELTZIN_SYSTEM_FUN_00454228(u8 *a0) {
    LVL_5_FELTZIN_SYSTEM_F4c55616a_FUN_004471C8(a0);
    LVL_5_FELTZIN_SYSTEM_F4c55616a_FUN_004471C8(a0 + 76);
    LVL_5_FELTZIN_SYSTEM_F4c55616a_FUN_004471C8(a0 + 152);
    LVL_5_FELTZIN_SYSTEM_F4c55616a_FUN_004476F0(a0 + 228);
    LVL_5_FELTZIN_SYSTEM_F4c55616a_FUN_00447988(a0 + 432);
    LVL_5_FELTZIN_SYSTEM_F4c55616a_FUN_00447988(a0 + 504);
    LVL_5_FELTZIN_SYSTEM_F4c55616a_FUN_00447988(a0 + 576);
    LVL_5_FELTZIN_SYSTEM_F4c55616a_FUN_004537D8(a0 + 664);
    return a0;
}

#ifndef RAC2_T_S16_F570CFB4B
#define RAC2_T_S16_F570CFB4B
typedef short s16_F570cfb4b;
#endif



extern void LVL_5_FELTZIN_SYSTEM_F570cfb4b_FUN_003423C8(u8 *);

void LVL_5_FELTZIN_SYSTEM_FUN_0034E1D8(u8 *a0) {
    s16_F570cfb4b *p = (s16_F570cfb4b *)(a0 + 10);
    if (--*p == 0) {
        *(s32 *)(a0 + 4) += 0xff000000;
        *p = 2;
    }
    if ((*(s32 *)(a0 + 4) & 0xff000000) == 0) {
        LVL_5_FELTZIN_SYSTEM_F570cfb4b_FUN_003423C8(a0);
    }
}


extern void LVL_5_FELTZIN_SYSTEM_F65f0250b_FUN_004471C8(u8 *);
extern void LVL_5_FELTZIN_SYSTEM_F65f0250b_FUN_004476F0(u8 *);
extern void LVL_5_FELTZIN_SYSTEM_F65f0250b_FUN_00447988(u8 *);
extern void LVL_5_FELTZIN_SYSTEM_F65f0250b_FUN_00458EC8(u8 *);

u8 *LVL_5_FELTZIN_SYSTEM_FUN_004521E8(u8 *a0) {
    LVL_5_FELTZIN_SYSTEM_F65f0250b_FUN_004471C8(a0);
    LVL_5_FELTZIN_SYSTEM_F65f0250b_FUN_004471C8(a0 + 76);
    LVL_5_FELTZIN_SYSTEM_F65f0250b_FUN_004471C8(a0 + 152);
    LVL_5_FELTZIN_SYSTEM_F65f0250b_FUN_004471C8(a0 + 228);
    LVL_5_FELTZIN_SYSTEM_F65f0250b_FUN_004471C8(a0 + 304);
    LVL_5_FELTZIN_SYSTEM_F65f0250b_FUN_004476F0(a0 + 380);
    LVL_5_FELTZIN_SYSTEM_F65f0250b_FUN_00447988(a0 + 464);
    LVL_5_FELTZIN_SYSTEM_F65f0250b_FUN_00458EC8(a0 + 552);
    return a0;
}
extern void LVL_5_FELTZIN_SYSTEM_Fd179801d_FUN_00340E78(int);
extern int LVL_5_FELTZIN_SYSTEM_Fd179801d_FUN_00340CB0(char *, int, int);
extern void LVL_5_FELTZIN_SYSTEM_Fd179801d_FUN_00340E78(int);

int LVL_5_FELTZIN_SYSTEM_FUN_00340E18(char *p, int x, int y)
{
    int v;

    LVL_5_FELTZIN_SYSTEM_Fd179801d_FUN_00340E78(1);
    v = LVL_5_FELTZIN_SYSTEM_Fd179801d_FUN_00340CB0(p, x, y);
    LVL_5_FELTZIN_SYSTEM_Fd179801d_FUN_00340E78(1);
    return v;
}
extern int LVL_5_FELTZIN_SYSTEM_F1f748010_FUN_0033E408(int, int);
extern void LVL_5_FELTZIN_SYSTEM_F1f748010_FUN_00328870(char *);
extern void LVL_5_FELTZIN_SYSTEM_F1f748010_FUN_003FCCD8(char *);
extern void LVL_5_FELTZIN_SYSTEM_F1f748010_FUN_003FD4D0(char *);
extern void LVL_5_FELTZIN_SYSTEM_F1f748010_FUN_003FDCD8(char *);

void LVL_5_FELTZIN_SYSTEM_FUN_003FC8B8(char *p)
{
    if (LVL_5_FELTZIN_SYSTEM_F1f748010_FUN_0033E408(3076, *(short *)(*(int *)(p + 104) + 26)) == 0)
        LVL_5_FELTZIN_SYSTEM_F1f748010_FUN_00328870(p);
    else {
        LVL_5_FELTZIN_SYSTEM_F1f748010_FUN_003FCCD8(p);
        LVL_5_FELTZIN_SYSTEM_F1f748010_FUN_003FD4D0(p);
        LVL_5_FELTZIN_SYSTEM_F1f748010_FUN_003FDCD8(p);
    }
}
extern char *LVL_5_FELTZIN_SYSTEM_Fdc7ffbd9_FUN_00328508(int);

char *LVL_5_FELTZIN_SYSTEM_FUN_003A6EC8(char *p)
{
    char *o = LVL_5_FELTZIN_SYSTEM_Fdc7ffbd9_FUN_00328508(167);
    int *v;

    if (o != 0) {
        v = *(int **)(o + 104);
        v[1] = (int)p;
        v[0] = 0;
        v[2] = 0;
        v[3] = 0;
        *(unsigned char *)(o + 48) = 255;
        *(short *)(o + 50) = 126;
        o[49] = 0;
        o[32] = 0;
    }
    return o;
}
extern int LVL_5_FELTZIN_SYSTEM_F23db9810_FUN_00379CA0(char *);
extern int LVL_5_FELTZIN_SYSTEM_F23db9810_FUN_0037CEB8(char *);
extern void LVL_5_FELTZIN_SYSTEM_F23db9810_FUN_0037CD80(char *, int);
extern void LVL_5_FELTZIN_SYSTEM_F23db9810_FUN_0037CD80(char *, int);
extern int LVL_5_FELTZIN_SYSTEM_F23db9810_FUN_00332AF8(int, int);
extern int LVL_5_FELTZIN_SYSTEM_F23db9810_FUN_0037CEB8(char *);
extern void LVL_5_FELTZIN_SYSTEM_F23db9810_FUN_0037CD80(char *, int);
extern void LVL_5_FELTZIN_SYSTEM_F23db9810_FUN_0037CD80(char *, int);
extern int LVL_5_FELTZIN_SYSTEM_F23db9810_FUN_00332AF8(int, int);
extern int LVL_5_FELTZIN_SYSTEM_F23db9810_D_001163B0(void);
extern int LVL_5_FELTZIN_SYSTEM_F23db9810_D_00221D10[];

void LVL_5_FELTZIN_SYSTEM_FUN_0037B6D0(char *obj)
{
    char *s;

    s = (char *)LVL_5_FELTZIN_SYSTEM_F23db9810_FUN_00379CA0(obj);
    if (s == 0)
        return;
    if (*(int *)(s + 288) == 0)
        return;
    if (*(int *)(s + 284) != 0) {
        int *p = LVL_5_FELTZIN_SYSTEM_F23db9810_D_00221D10;
        int one = 1;

        *(int *)(s + 280) = one;
        p[3] += one;
        if (LVL_5_FELTZIN_SYSTEM_F23db9810_FUN_0037CEB8(obj) != 5) {
            LVL_5_FELTZIN_SYSTEM_F23db9810_FUN_0037CD80(obj, 4);
            *(float *)(s + 120) = (LVL_5_FELTZIN_SYSTEM_F23db9810_D_001163B0() & 1) ? -1.0f : 1.0f;
            if (LVL_5_FELTZIN_SYSTEM_F23db9810_D_001163B0() & 1)
                *(float *)(s + 116) = -1.0f;
            else
                *(float *)(s + 116) = 1.0f;
            *(int *)(s + 252) = one;
            *(int *)(s + 112) = 0;
            *(int *)(s + 124) = 0;
        } else {
            LVL_5_FELTZIN_SYSTEM_F23db9810_FUN_0037CD80(obj, 7);
        }
        *(int *)(s + 304) = LVL_5_FELTZIN_SYSTEM_F23db9810_FUN_00332AF8(120, 500);
    } else {
        int *p = LVL_5_FELTZIN_SYSTEM_F23db9810_D_00221D10;

        *(int *)(s + 280) = 1;
        p[3] += 1;
        if (LVL_5_FELTZIN_SYSTEM_F23db9810_FUN_0037CEB8(obj) != 5)
            LVL_5_FELTZIN_SYSTEM_F23db9810_FUN_0037CD80(obj, 4);
        else
            LVL_5_FELTZIN_SYSTEM_F23db9810_FUN_0037CD80(obj, 7);
        *(int *)(s + 304) = LVL_5_FELTZIN_SYSTEM_F23db9810_FUN_00332AF8(120, 500);
        *(int *)(s + 252) = 0;
    }
}
extern int LVL_5_FELTZIN_SYSTEM_F953b9ef6_FUN_00447A60(void *);
extern int LVL_5_FELTZIN_SYSTEM_F953b9ef6_FUN_002FEF40(int);
extern void LVL_5_FELTZIN_SYSTEM_F953b9ef6_FUN_00302010(float, float, float, int, int, int, int, int);

void LVL_5_FELTZIN_SYSTEM_FUN_00447A98(char *o)
{
    float f20;
    int s4;
    int r;
    int s2v;
    char *p0;
    char *p1;

    if (*(float *)(*(char **)(o + 16)) == 0.0f) {
        return;
    }
    if (*(int *)(o + 64) == 0) {
        return;
    }
    s4 = LVL_5_FELTZIN_SYSTEM_F953b9ef6_FUN_00447A60(o);
    f20 = *(float *)(*(char **)(o));
    switch (*(int *)(o + 68)) {
    case 0:
        break;
    case 1:
        f20 = f20 - (float)(s4 >> 1);
        break;
    case 2:
        f20 = f20 - (float)s4;
        break;
    }
    p0 = *(char **)(o);
    p1 = *(char **)(o + 4);
    s2v = *(int *)(*(char **)(o + 12));
    r = LVL_5_FELTZIN_SYSTEM_F953b9ef6_FUN_002FEF40(*(int *)(o + 56));
    LVL_5_FELTZIN_SYSTEM_F953b9ef6_FUN_00302010(f20, *(float *)(p0 + 4), *(float *)(p1), s2v, *(int *)(o + 64),
            s4, r, *(int *)(o + 52));
}
#ifndef RAC2_T_V4_F6A70B950
#define RAC2_T_V4_F6A70B950
typedef int V4_F6a70b950 __attribute__((mode(TI)));
#endif


extern char LVL_5_FELTZIN_SYSTEM_F6a70b950_D_00189E20[];
extern float LVL_5_FELTZIN_SYSTEM_F6a70b950_FUN_00306C08(float);
extern float LVL_5_FELTZIN_SYSTEM_F6a70b950_FUN_00306C20(float);
extern float LVL_5_FELTZIN_SYSTEM_F6a70b950_FUN_00306C08(float);
extern float LVL_5_FELTZIN_SYSTEM_F6a70b950_FUN_00306C20(float);
extern void LVL_5_FELTZIN_SYSTEM_F6a70b950_FUN_00306E98(float *m, char *src);
extern void LVL_5_FELTZIN_SYSTEM_F6a70b950_FUN_00306B00(float *dst, float *src, float *m);
extern void LVL_5_FELTZIN_SYSTEM_F6a70b950_FUN_00306630(V4_F6a70b950 *out, V4_F6a70b950 *in, float *v);

void LVL_5_FELTZIN_SYSTEM_FUN_002EC018(V4_F6a70b950 *out, V4_F6a70b950 *in, float scale)
{
    char *p = LVL_5_FELTZIN_SYSTEM_F6a70b950_D_00189E20;
    unsigned char mode;
    float z;

    mode = *(unsigned char *)(p + 8899);

    switch (mode) {
    case 0:
        *out = *in;
        *(float *)out += LVL_5_FELTZIN_SYSTEM_F6a70b950_FUN_00306C08(*(float *)(*(int *)(p + 8848) + 248)) * scale;
        *(float *)((char *)out + 4) += LVL_5_FELTZIN_SYSTEM_F6a70b950_FUN_00306C20(*(float *)(*(int *)(p + 8848) + 248)) * scale;
        break;
    case 1:
    case 2: {
        float m[16];
        float v[4];

        z = 0.0f;
        v[0] = LVL_5_FELTZIN_SYSTEM_F6a70b950_FUN_00306C08(z) * scale;
        v[1] = LVL_5_FELTZIN_SYSTEM_F6a70b950_FUN_00306C20(z) * scale;
        v[2] = z;
        LVL_5_FELTZIN_SYSTEM_F6a70b950_FUN_00306E98(m, (char *)*(int *)(p + 8848) + 240);
        LVL_5_FELTZIN_SYSTEM_F6a70b950_FUN_00306B00(v, v, m);
        LVL_5_FELTZIN_SYSTEM_F6a70b950_FUN_00306630(out, in, v);
        break;
    }
    }
}
#ifndef RAC2_T_V4_FBFDC087A
#define RAC2_T_V4_FBFDC087A
typedef int V4_Fbfdc087a __attribute__((mode(TI)));
#endif


extern char LVL_5_FELTZIN_SYSTEM_Fbfdc087a_D_00189EB0[];
extern void LVL_5_FELTZIN_SYSTEM_Fbfdc087a_FUN_00306E98(float *m, char *p);
extern void LVL_5_FELTZIN_SYSTEM_Fbfdc087a_FUN_00306B00(float *dst, float *src, float *m);
extern void LVL_5_FELTZIN_SYSTEM_Fbfdc087a_FUN_00306E98(float *m, char *p);
extern void LVL_5_FELTZIN_SYSTEM_Fbfdc087a_FUN_00307210(float *m, float *m2, float *e);
extern void LVL_5_FELTZIN_SYSTEM_Fbfdc087a_FUN_00306B00(float *dst, float *src, float *m);
extern void LVL_5_FELTZIN_SYSTEM_Fbfdc087a_FUN_00306660(float *c, float *a, float *b);
extern void LVL_5_FELTZIN_SYSTEM_Fbfdc087a_FUN_00306630(char *a, char *b, float *c);
extern void LVL_5_FELTZIN_SYSTEM_Fbfdc087a_FUN_00336A90(float *m, char *p);

void LVL_5_FELTZIN_SYSTEM_FUN_002C2868(V4_Fbfdc087a *src, float x, float y, float z)
{
    char *p = LVL_5_FELTZIN_SYSTEM_Fbfdc087a_D_00189EB0;
    float q[4];
    float a[4];
    float b[4];
    float c[4];
    float m[16];
    float e[16];
    float v[4];

    *(V4_Fbfdc087a *)q = *src;
    LVL_5_FELTZIN_SYSTEM_Fbfdc087a_FUN_00306E98(m, p);
    LVL_5_FELTZIN_SYSTEM_Fbfdc087a_FUN_00306B00(a, q, m);
    v[0] = x;
    v[1] = y;
    v[2] = z;
    LVL_5_FELTZIN_SYSTEM_Fbfdc087a_FUN_00306E98(e, v);
    LVL_5_FELTZIN_SYSTEM_Fbfdc087a_FUN_00307210(m, m, e);
    LVL_5_FELTZIN_SYSTEM_Fbfdc087a_FUN_00306B00(b, q, m);
    LVL_5_FELTZIN_SYSTEM_Fbfdc087a_FUN_00306660(c, a, b);
    LVL_5_FELTZIN_SYSTEM_Fbfdc087a_FUN_00306630(p - 16, p - 16, c);
    LVL_5_FELTZIN_SYSTEM_Fbfdc087a_FUN_00336A90(m, p);
}
extern float LVL_5_FELTZIN_SYSTEM_Fa580e594_FUN_00307768(int a);
extern float LVL_5_FELTZIN_SYSTEM_Fa580e594_FUN_00307768(int a);
extern float LVL_5_FELTZIN_SYSTEM_Fa580e594_FUN_00307768(int a);
extern float LVL_5_FELTZIN_SYSTEM_Fa580e594_FUN_00307768(int a);

float LVL_5_FELTZIN_SYSTEM_FUN_00328A68(char *s1)
{
    char *p;
    char *q;
    float t;

    if (*(unsigned char *)(s1 + 66) != 255)
        p = *(char **)(s1 + 88);
    else
        p = *(char **)(s1 + 92);

    if (*(float *)(s1 + 68) == 0.0f)
        return LVL_5_FELTZIN_SYSTEM_Fa580e594_FUN_00307768(*(short *)(p + 4)) * 0.0625f;

    if (*(unsigned char *)(s1 + 66) != *(unsigned char *)(s1 + 67) ||
        *(unsigned char *)(s1 + 64) > *(unsigned char *)(s1 + 65))
        return LVL_5_FELTZIN_SYSTEM_Fa580e594_FUN_00307768(*(short *)(p + 4)) * 0.0625f + *(float *)(s1 + 68);

    q = *(char **)(s1 + 92);
    t = LVL_5_FELTZIN_SYSTEM_Fa580e594_FUN_00307768(*(short *)(p + 4)) * (1.0f - *(float *)(s1 + 68));
    t = t + LVL_5_FELTZIN_SYSTEM_Fa580e594_FUN_00307768(*(short *)(q + 4)) * *(float *)(s1 + 68);
    return t * 0.0625f;
}
extern float LVL_5_FELTZIN_SYSTEM_Fd03b762f_FUN_00307768(int a0);
extern int LVL_5_FELTZIN_SYSTEM_Fd03b762f_FUN_00307778(float x);

int LVL_5_FELTZIN_SYSTEM_FUN_00379870(int a0, int *p0, int *p1, int *p2)
{
    float t;
    int a;
    int b;
    int c;
    int d;
    int e;

    t = LVL_5_FELTZIN_SYSTEM_Fd03b762f_FUN_00307768(a0);
    a = LVL_5_FELTZIN_SYSTEM_Fd03b762f_FUN_00307778(t * (1.0f / 3600.0f));
    *p0 = a;
    b = LVL_5_FELTZIN_SYSTEM_Fd03b762f_FUN_00307778((float)a * 3600.0f);
    t = t - (float)b;
    c = LVL_5_FELTZIN_SYSTEM_Fd03b762f_FUN_00307778(t * 0.01666667f);
    *p1 = c;
    d = LVL_5_FELTZIN_SYSTEM_Fd03b762f_FUN_00307778((float)c * 60.0f);
    t = t - (float)d;
    e = LVL_5_FELTZIN_SYSTEM_Fd03b762f_FUN_00307778(t * (5.0f / 3.0f));
    e = e > 99 ? 0 : e;
    *p2 = e;
    return e;
}
extern void LVL_5_FELTZIN_SYSTEM_Fc7a982c7_FUN_003329E8(char *arg, int mode, int value);
extern void LVL_5_FELTZIN_SYSTEM_Fc7a982c7_FUN_00406270(char *arg);
extern void LVL_5_FELTZIN_SYSTEM_Fc7a982c7_FUN_00406348(char *arg);
extern float LVL_5_FELTZIN_SYSTEM_Fc7a982c7_FUN_00306810(char *arg, char *table);
extern float LVL_5_FELTZIN_SYSTEM_Fc7a982c7_FUN_003065A0(float value);
extern void LVL_5_FELTZIN_SYSTEM_Fc7a982c7_FUN_0033CD60(int arg, int value);
extern void LVL_5_FELTZIN_SYSTEM_Fc7a982c7_FUN_0030BE28(int arg);
extern void LVL_5_FELTZIN_SYSTEM_Fc7a982c7_FUN_00338F58(int arg);
extern void LVL_5_FELTZIN_SYSTEM_Fc7a982c7_FUN_00328870(char *arg);
extern char LVL_5_FELTZIN_SYSTEM_Fc7a982c7_D_00189EA0[];
extern unsigned char LVL_5_FELTZIN_SYSTEM_Fc7a982c7_D_001A7B2E __attribute__((sda));
void LVL_5_FELTZIN_SYSTEM_FUN_00406528(char *arg)
{
    int *object = *(int **)(arg + 104);
    unsigned char state = *(unsigned char *)(arg + 32);

    switch (state) {
    case 0:
        *(unsigned char *)(arg + 48) = 255;
        if (LVL_5_FELTZIN_SYSTEM_Fc7a982c7_D_001A7B2E != 0 && object[17] != 0) {
            LVL_5_FELTZIN_SYSTEM_Fc7a982c7_FUN_00328870((char *)object[17]);
            LVL_5_FELTZIN_SYSTEM_Fc7a982c7_FUN_00328870(arg);
            return;
        } else {
            LVL_5_FELTZIN_SYSTEM_Fc7a982c7_FUN_003329E8(arg, 1, -1);
            LVL_5_FELTZIN_SYSTEM_Fc7a982c7_FUN_00406270(arg);
        }
        break;
    case 1:
        LVL_5_FELTZIN_SYSTEM_Fc7a982c7_FUN_00406348(arg);
        if (LVL_5_FELTZIN_SYSTEM_Fc7a982c7_FUN_00306810(arg + 16, LVL_5_FELTZIN_SYSTEM_Fc7a982c7_D_00189EA0) < 2.0f) {
            if (LVL_5_FELTZIN_SYSTEM_Fc7a982c7_FUN_003065A0(*(float *)(arg + 24) - *(float *)(LVL_5_FELTZIN_SYSTEM_Fc7a982c7_D_00189EA0 + 8)) < 2.0f) {
                LVL_5_FELTZIN_SYSTEM_Fc7a982c7_FUN_0033CD60(4658, -1);
                LVL_5_FELTZIN_SYSTEM_Fc7a982c7_FUN_0030BE28(54);
                LVL_5_FELTZIN_SYSTEM_Fc7a982c7_FUN_00338F58(54);
                if (object[17] != 0) {
                    LVL_5_FELTZIN_SYSTEM_Fc7a982c7_FUN_00328870((char *)object[17]);
                    LVL_5_FELTZIN_SYSTEM_Fc7a982c7_FUN_00328870(arg);
                    return;
                }
                object[16] = 120;
            }
        }
        break;
    }
}
