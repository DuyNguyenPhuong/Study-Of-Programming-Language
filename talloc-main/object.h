#ifndef _VALUE
#define _VALUE

typedef enum {INT_TYPE,DOUBLE_TYPE,STR_TYPE,CONS_TYPE,NULL_TYPE,
              PTR_TYPE} objectType;

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

#endif
