


#ifndef _OBJECT
#define _OBJECT

/* Define a new data type called 'objectType'. A variable of this type has value 
INT_TYPE, or DOUBLE_TYPE, or .... Right now there are only five possible values. 
Later there will be more. */
typedef enum {INT_TYPE, DOUBLE_TYPE, STR_TYPE, CONS_TYPE, NULL_TYPE} objectType;
/* (By the way, objectType is an integer type in disguise. INT_TYPE is actually 
0, DOUBLE_TYPE is actually 1, etc. You can see these integer values, if you 
print them out. In your code, always use the names defined above, because they 
are more meaningful than 0, 1, ....) */

/* The simplest kind of object has a type and no other members. Right now it can 
only have NULL_TYPE, but that will change later. We represent Scheme's empty 
list () as an Object with type NULL_TYPE. */
typedef struct Object {
    objectType type;
} Object;

/* An Integer should have INT_TYPE. */
typedef struct Integer {
    objectType type;
    int value;
} Integer;

/* A Double should have DOUBLE_TYPE. */
typedef struct Double {
    objectType type;
    double value;
} Double;

/* A String should have STR_TYPE. */
typedef struct String {
    objectType type;
    char *value;
} String;

/* A ConsCell should have CONS_TYPE. */
typedef struct ConsCell {
    objectType type;
    Object *car;
    Object *cdr;
} ConsCell;

#endif


