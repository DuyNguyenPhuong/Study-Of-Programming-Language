// Tester for linked list.

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "linkedlist.h"
#include "object.h"

void testForward(Object *head, int correctLength, bool exemplary) {
  Object *object = head;
  assert(CONS_TYPE == object->type);
  assert(DOUBLE_TYPE == car(object)->type);
  assert(1 == ((Double*)car(object))->value);

  if (exemplary) {
    object = cdr(object);
    assert(CONS_TYPE == object->type);
    assert(STR_TYPE == car(object)->type);
    assert(!strcmp("2.0s", ((String*)car(object))->value));

    object = cdr(object);
    assert(CONS_TYPE == object->type);
    assert(STR_TYPE == car(object)->type);
    assert(!strcmp("3.0s", ((String*)car(object))->value));
  }

  object = cdr(object);
  assert(CONS_TYPE == object->type);
  assert(DOUBLE_TYPE == car(object)->type);
  assert(4 == ((Double*)car(object))->value);

  if (exemplary) {
    object = cdr(object);
    assert(CONS_TYPE == object->type);
    assert(STR_TYPE == car(object)->type);
    assert(!strcmp("5.0s", ((String*)car(object))->value));
  }

  object = cdr(object);
  assert(CONS_TYPE == object->type);
  assert(DOUBLE_TYPE == car(object)->type);
  assert(6 == ((Double*)car(object))->value);

  object = cdr(object);
  assert(CONS_TYPE == object->type);
  assert(INT_TYPE == car(object)->type);
  assert(7 == ((Integer*)car(object))->value);

  object = cdr(object);
  assert(NULL_TYPE == object->type);

  assert(correctLength == length(head));
  assert(!isNull(head));
}

void testBackward(Object *head, int correctLength, bool exemplary) {
  Object *value = head;

  assert(CONS_TYPE == value->type);
  assert(INT_TYPE == car(value)->type);
  assert(7 == ((Integer*)car(value))->value);

  value = cdr(value);
  assert(CONS_TYPE == value->type);
  assert(DOUBLE_TYPE == car(value)->type);
  assert(6 == ((Double*)car(value))->value);

  if (exemplary) {
    value = cdr(value);
    assert(CONS_TYPE == value->type);
    assert(STR_TYPE == car(value)->type);
    assert(!strcmp("5.0s", ((String*)car(value))->value));
  }

  value = cdr(value);
  assert(CONS_TYPE == value->type);
  assert(DOUBLE_TYPE == car(value)->type);
  assert(4 == ((Double*)car(value))->value);

  if (exemplary) {
    value = cdr(value);
    assert(CONS_TYPE == value->type);
    assert(STR_TYPE == car(value)->type);
    assert(!strcmp("3.0s", ((String*)car(value))->value));

    value = cdr(value);
    assert(CONS_TYPE == value->type);
    assert(STR_TYPE == car(value)->type);
    assert(!strcmp("2.0s", ((String*)car(value))->value));
  }

  value = cdr(value);
  assert(CONS_TYPE == value->type);
  assert(DOUBLE_TYPE == car(value)->type);
  assert(1 == ((Double*)car(value))->value);

  value = cdr(value);
  assert(NULL_TYPE == value->type);

  assert(correctLength == length(head));
  assert(!isNull(head));
}


int main(int argc, char **argv) {

  bool exemplary = false;
  if (argc == 2 && !strcmp(argv[1], "E")) {
    exemplary = true;
  }

  Object *head = makeNull();
  int correctLength = 0;
  assert(length(head) == correctLength);

  Object *reverseLengthZero = reverse(head);
  assert(length(reverseLengthZero) == correctLength);
  cleanup(reverseLengthZero);

  Integer *val1 = malloc(sizeof(Integer));
  val1->type = INT_TYPE;
  val1->value = 7;
  head = cons((Object*)val1,head);
  correctLength++;
  assert(length(head) == correctLength);

  Object *reverseLengthOne = reverse(head);
  assert(length(reverseLengthOne) == correctLength);
  cleanup(reverseLengthOne);

  Double *val2 = malloc(sizeof(Double));
  val2->type = DOUBLE_TYPE;
  val2->value = 6.00;
  head = cons((Object*)val2,head);
  correctLength++;
  assert(length(head) == correctLength);

  if (exemplary) {
    String *val3 = malloc(sizeof(String));
    val3->type = STR_TYPE;
    char *text = "5.0s";
    val3->value = malloc(sizeof(char)*(strlen(text) + 1));
    strcpy(val3->value,text);
    head = cons((Object*)val3,head);
    correctLength++;
    assert(length(head) == correctLength);
  }

  Double *val4 = malloc(sizeof(Double));
  val4->type = DOUBLE_TYPE;
  val4->value = 4.00000;
  head = cons((Object*)val4,head);
  correctLength++;
  assert(length(head) == correctLength);

  if (exemplary) {
    String *val5 = malloc(sizeof(String));
    val5->type = STR_TYPE;
    char *text = "3.0s";
    val5->value = malloc(sizeof(char)*(strlen(text) + 1));
    strcpy(val5->value,text);
    head = cons((Object*)val5,head);
    correctLength++;
    assert(length(head) == correctLength);

    String *val6 = malloc(sizeof(String));
    val6->type = STR_TYPE;
    text = "2.0s";
    val6->value = malloc(sizeof(char)*(strlen(text) + 1));
    strcpy(val6->value,text);
    head = cons((Object*)val6,head);
    correctLength++;
    assert(length(head) == correctLength);

  }

  Double *val7 = malloc(sizeof(Double));
  val7->type = DOUBLE_TYPE;
  val7->value = 1.0;
  head = cons((Object*)val7,head);
  correctLength++;
  assert(length(head) == correctLength);


  display(head);
  testForward(head, correctLength, exemplary);

  Object *rev = reverse(head);
  display(rev);

  testBackward(rev, correctLength, exemplary);

  cleanup(head);
  cleanup(rev);

  head = NULL;
  rev = NULL;
}
