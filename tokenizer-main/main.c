#include <stdio.h>
#include "tokenizer.h"
#include "object.h"
#include "linkedlist.h"
#include "talloc.h"

int main() {
    Object *list = tokenize();
    displayTokens(list);
    tfree();
}
