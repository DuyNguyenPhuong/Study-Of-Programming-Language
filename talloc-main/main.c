// Tester for linked list.

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "linkedlist.h"
#include "object.h"
#include "talloc.h"

void testForward(Object *head, int correctLength, bool exemplary) {
  Object *value = head;
  assert(CONS_TYPE == value->type);
  assert(DOUBLE_TYPE == car(value)->type);
  assert(1 == ((Double*)car(value))->value);

  if (exemplary) {
    value = cdr(value);
    assert(CONS_TYPE == value->type);
    assert(STR_TYPE == car(value)->type);
    assert(!strcmp("2.0s", ((String*)car(value))->value));

    value = cdr(value);
    assert(CONS_TYPE == value->type);
    assert(STR_TYPE == car(value)->type);
    assert(!strcmp("3.0s", ((String*)car(value))->value));
  }

  value = cdr(value);
  assert(CONS_TYPE == value->type);
  assert(DOUBLE_TYPE == car(value)->type);
  assert(4 == ((Double*)car(value))->value);

  if (exemplary) {
    value = cdr(value);
    assert(CONS_TYPE == value->type);
    assert(STR_TYPE == car(value)->type);
    assert(!strcmp("5.0s", ((String*)car(value))->value));
  }

  value = cdr(value);
  assert(CONS_TYPE == value->type);
  assert(DOUBLE_TYPE == car(value)->type);
  assert(6 == ((Double*)car(value))->value);

  value = cdr(value);
  assert(CONS_TYPE == value->type);
  assert(INT_TYPE == car(value)->type);
  assert(7 == ((Integer*)car(value))->value);

  value = cdr(value);
  assert(NULL_TYPE == value->type);

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

  Integer *val1 = talloc(sizeof(Integer));
  val1->type = INT_TYPE;
  val1->value = 7;
  head = cons((Object*)val1,head);
  correctLength++;

  Double *val2 = talloc(sizeof(Double));
  val2->type = DOUBLE_TYPE;
  val2->value = 6.00;
  head = cons((Object*)val2,head);
  correctLength++;

  if (exemplary) {
    String *val3 = talloc(sizeof(String));
    val3->type = STR_TYPE;
    char *text = "5.0s";
    val3->value = talloc(sizeof(char)*(strlen(text) + 1));
    strcpy(val3->value,text);
    head = cons((Object*)val3,head);
    correctLength++;
  }

  Double *val4 = talloc(sizeof(Double));
  val4->type = DOUBLE_TYPE;
  val4->value = 4.00000;
  head = cons((Object*)val4,head);
  correctLength++;

  if (exemplary) {
    String *val5 = talloc(sizeof(String));
    val5->type = STR_TYPE;
    char *text = "3.0s";
    val5->value = talloc(sizeof(char)*(strlen(text) + 1));
    strcpy(val5->value,text);
    head = cons((Object*)val5,head);
    correctLength++;

    String *val6 = talloc(sizeof(String));
    val6->type = STR_TYPE;
    text = "2.0s";
    val6->value = talloc(sizeof(char)*(strlen(text) + 1));
    strcpy(val6->value,text);
    head = cons((Object*)val6,head);
    correctLength++;
  }

  Double *val7 = talloc(sizeof(Double));
  val7->type = DOUBLE_TYPE;
  val7->value = 1.0;
  head = cons((Object*)val7,head);
  correctLength++;
    
  display(head);
  testForward(head, correctLength, exemplary);

  Object *rev = reverse(head);
  display(rev);

  testBackward(rev, correctLength, exemplary);

  // Verify that neither of the lists share identical cons cells
  Object *headcur = head;
  while (headcur->type != NULL_TYPE) {
    Object *revcur = rev;
    while (revcur->type != NULL_TYPE) {
      assert(headcur != revcur);
      revcur = ((ConsCell*)revcur)->cdr;
    }
    headcur = ((ConsCell*)headcur)->cdr;
  }

  if (exemplary) {
    printf(" -=- EMPTY LIST -=- \n");
    Object *emptyList = makeNull();
    assert(0 == length(emptyList));
    assert(isNull(emptyList));

    printf(" -=- REVERSE EMPTY LIST -=- \n");
    Object *reverseEmpty = reverse(emptyList);
    assert(0 == length(reverseEmpty));
    assert(isNull(reverseEmpty));

    Object *justOneByte = talloc(1);
  }

  tfree();

  Object *justOneByte = talloc(1);
  texit(0);
}
