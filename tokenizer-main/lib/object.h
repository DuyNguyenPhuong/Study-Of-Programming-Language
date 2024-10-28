#ifndef _VALUE
#define _VALUE

typedef enum {
    INT_TYPE, DOUBLE_TYPE, STR_TYPE, CONS_TYPE, NULL_TYPE, PTR_TYPE,
    OPEN_TYPE, CLOSE_TYPE, BOOL_TYPE, SYMBOL_TYPE, CLOSEBRACE_TYPE
} objectType;

typedef struct Object {
    objectType type;
} Object;

typedef struct Integer {
    objectType type;
    int value;
} Integer;

typedef struct Double {
    objectType type;
    double value;
} Double;

typedef struct String {
    objectType type;
    char *value;
} String;

typedef struct Pointer {
    objectType type;
    void *value;
} Pointer;

typedef struct ConsCell {
    objectType type;
    Object *car;
    Object *cdr;
} ConsCell;

// Store a 1 for a true, a 0 for a false
typedef struct Boolean {
    objectType type;
    int value;
} Boolean;

typedef struct Symbol {
    objectType type;
    char *value;
} Symbol;

#endif
