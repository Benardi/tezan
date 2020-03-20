#include <check.h>
#include <dll.h>
#include <malloc.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

Register* reg;
DoublyLinkedList** head;

void setup(void);
void teardown(void);
Suite* make_test_suite(void);

void setup(void)
{
  reg = malloc(sizeof(Register));
  head = malloc(sizeof(DoublyLinkedList*));
}

void teardown(void)
{
  free(reg);
  free(head);
}

START_TEST(test_dll_insert_1)
{
  DoublyLinkedList* node1;

  *head = NULL;
  reg->key = -150;
  node1 = dll_insert(head, *reg);

  ck_assert_int_eq(node1->data.key, -150);
  ck_assert_int_eq(node1 == NULL, false);
  ck_assert_int_eq(node1->prev == NULL, true);
  ck_assert_int_eq(node1->next == NULL, true);

  ck_assert_int_eq((*head)->data.key, -150);
  ck_assert_int_eq((*head) == NULL, false);
  ck_assert_int_eq((*head)->prev == NULL, true);
  ck_assert_int_eq((*head)->next == NULL, true);

  free(node1);
}
END_TEST

START_TEST(test_dll_insert_2)
{
  DoublyLinkedList* node1;
  DoublyLinkedList* node2;

  *head = NULL;
  reg->key = 10;
  node1 = dll_insert(head, *reg);
  reg->key = 30;
  node2 = dll_insert(head, *reg);

  /* Test collateral effect */
  ck_assert_int_eq((*head)->data.key, 30);
  ck_assert_int_eq((*head)->prev == NULL, true);
  ck_assert_int_eq((*head)->next == NULL, false);

  ck_assert_int_eq((*head)->next->data.key, 10);
  ck_assert_int_eq((*head)->next->next == NULL, true);
  ck_assert_int_eq((*head)->next->prev == NULL, false);
  ck_assert_int_eq((*head)->next->prev->data.key, 30);

  /* Test function return */
  ck_assert_int_eq(node1 == NULL, false);
  ck_assert_int_eq(node1->next == NULL, true);
  ck_assert_int_eq(node1->prev == NULL, false);
  ck_assert_int_eq(node1->data.key, 10);
  ck_assert_int_eq(node1->prev->next->data.key, 10);

  ck_assert_int_eq(node2 == NULL, false);
  ck_assert_int_eq(node2->prev == NULL, true);
  ck_assert_int_eq(node2->next == NULL, false);
  ck_assert_int_eq(node2->data.key, 30);
  ck_assert_int_eq(node2->next->prev->data.key, 30);

  free(node2);
  free(node1);
}
END_TEST

START_TEST(test_dll_insert_3)
{
  DoublyLinkedList* node1;
  DoublyLinkedList* node2;
  DoublyLinkedList* node3;
  DoublyLinkedList* node4;

  *head = NULL;
  reg->key = -67;
  node1 = dll_insert(head, *reg);
  reg->key = 30;
  node2 = dll_insert(head, *reg);
  reg->key = -12;
  node3 = dll_insert(head, *reg);
  reg->key = 0;
  node4 = dll_insert(head, *reg);

  /* Test collateral effect */
  ck_assert_int_eq((*head)->data.key, 0);
  ck_assert_int_eq((*head)->prev == NULL, true);
  ck_assert_int_eq((*head)->next == NULL, false);

  ck_assert_int_eq((*head)->next->data.key, -12);
  ck_assert_int_eq((*head)->next->next == NULL, false);
  ck_assert_int_eq((*head)->next->prev == NULL, false);
  ck_assert_int_eq((*head)->next->prev->data.key, 0);

  ck_assert_int_eq((*head)->next->next->data.key, 30);
  ck_assert_int_eq((*head)->next->next->next == NULL, false);
  ck_assert_int_eq((*head)->next->next->prev == NULL, false);
  ck_assert_int_eq((*head)->next->next->prev->data.key, -12);

  ck_assert_int_eq((*head)->next->next->next->data.key, -67);
  ck_assert_int_eq((*head)->next->next->next->next == NULL, true);
  ck_assert_int_eq((*head)->next->next->next->prev == NULL, false);
  ck_assert_int_eq((*head)->next->next->next->prev->data.key, 30);

  /* Test function return */
  ck_assert_int_eq(node1->data.key, -67);
  ck_assert_int_eq(node1->next == NULL, true);
  ck_assert_int_eq(node1->prev == NULL, false);
  ck_assert_int_eq(node1->prev->data.key, 30);

  ck_assert_int_eq(node2->data.key, 30);
  ck_assert_int_eq(node2->next == NULL, false);
  ck_assert_int_eq(node2->prev == NULL, false);
  ck_assert_int_eq(node2->prev->data.key, -12);

  ck_assert_int_eq(node3->data.key, -12);
  ck_assert_int_eq(node3->next == NULL, false);
  ck_assert_int_eq(node3->prev == NULL, false);
  ck_assert_int_eq(node3->prev->data.key, 0);

  ck_assert_int_eq(node4->data.key, 0);
  ck_assert_int_eq(node4->prev == NULL, true);
  ck_assert_int_eq(node4->next == NULL, false);
  ck_assert_int_eq(node4->next->data.key, -12);

  free(node4);
  free(node3);
  free(node2);
  free(node1);
}
END_TEST

START_TEST(test_dll_search_1)
{
  DoublyLinkedList* retrieved;
  DoublyLinkedList* node1;
  DoublyLinkedList* node2;
  DoublyLinkedList* node3;
  DoublyLinkedList* node4;

  *head = NULL;
  reg->key = -67;
  node1 = dll_insert(head, *reg);
  reg->key = 30;
  node2 = dll_insert(head, *reg);
  reg->key = -12;
  node3 = dll_insert(head, *reg);
  reg->key = 0;
  node4 = dll_insert(head, *reg);
  retrieved = dll_search(head, 30);

  ck_assert_int_eq(retrieved == NULL, false);
  ck_assert_int_eq(retrieved->data.key, 30);
  ck_assert_int_eq(retrieved->next == NULL, false);
  ck_assert_int_eq(retrieved->prev == NULL, false);
  ck_assert_int_eq(retrieved->next->data.key, -67);
  ck_assert_int_eq(retrieved->prev->data.key, -12);
  ck_assert_int_eq(retrieved->prev->prev->data.key, 0);

  free(node4);
  free(node3);
  free(node2);
  free(node1);
}
END_TEST

START_TEST(test_dll_search_2)
{
  DoublyLinkedList* retrieved;
  DoublyLinkedList* node1;
  DoublyLinkedList* node2;
  DoublyLinkedList* node3;
  DoublyLinkedList* node4;

  *head = NULL;
  reg->key = 23;
  node1 = dll_insert(head, *reg);
  reg->key = 5;
  node2 = dll_insert(head, *reg);
  reg->key = -17;
  node3 = dll_insert(head, *reg);
  reg->key = -10;
  node4 = dll_insert(head, *reg);
  retrieved = dll_search(head, 25);

  ck_assert_int_eq(retrieved == NULL, true);

  free(node4);
  free(node3);
  free(node2);
  free(node1);
}
END_TEST

START_TEST(test_dll_search_3)
{
  DoublyLinkedList* retrieved;
  DoublyLinkedList* node1;
  DoublyLinkedList* node2;
  DoublyLinkedList* node3;
  DoublyLinkedList* node4;
  DoublyLinkedList* node5;
  DoublyLinkedList* node6;

  *head = NULL;
  reg->key = -67;
  node1 = dll_insert(head, *reg);
  reg->key = 30;
  node2 = dll_insert(head, *reg);
  reg->key = -12;
  node3 = dll_insert(head, *reg);
  reg->key = 0;
  node4 = dll_insert(head, *reg);
  reg->key = 20;
  node5 = dll_insert(head, *reg);
  reg->key = -189;
  node6 = dll_insert(head, *reg);
  retrieved = dll_search(head, -67);

  ck_assert_int_eq(retrieved == NULL, false);
  ck_assert_int_eq(retrieved->data.key, -67);
  ck_assert_int_eq(retrieved->next == NULL, true);
  ck_assert_int_eq(retrieved->prev == NULL, false);
  ck_assert_int_eq(retrieved->prev->data.key, 30);
  ck_assert_int_eq(retrieved->prev->prev->data.key, -12);
  ck_assert_int_eq(retrieved->prev->prev->prev->data.key, 0);
  ck_assert_int_eq(retrieved->prev->prev->prev->prev->data.key, 20);
  ck_assert_int_eq(retrieved->prev->prev->prev->prev->prev->data.key, -189);

  free(node6);
  free(node5);
  free(node4);
  free(node3);
  free(node2);
  free(node1);
}
END_TEST

START_TEST(test_dll_search_4)
{
  DoublyLinkedList* retrieved;
  DoublyLinkedList* node1;
  DoublyLinkedList* node2;
  DoublyLinkedList* node3;
  DoublyLinkedList* node4;
  DoublyLinkedList* node5;
  DoublyLinkedList* node6;

  *head = NULL;
  reg->key = -67;
  node1 = dll_insert(head, *reg);
  reg->key = 30;
  node2 = dll_insert(head, *reg);
  reg->key = -12;
  node3 = dll_insert(head, *reg);
  reg->key = 0;
  node4 = dll_insert(head, *reg);
  reg->key = 20;
  node5 = dll_insert(head, *reg);
  reg->key = -189;
  node6 = dll_insert(head, *reg);
  retrieved = dll_search(head, -189);

  ck_assert_int_eq(retrieved == NULL, false);
  ck_assert_int_eq(retrieved->data.key, -189);
  ck_assert_int_eq(retrieved->next == NULL, false);
  ck_assert_int_eq(retrieved->prev == NULL, true);
  ck_assert_int_eq(retrieved->next->data.key, 20);
  ck_assert_int_eq(retrieved->next->next->data.key, 0);
  ck_assert_int_eq(retrieved->next->next->next->data.key, -12);
  ck_assert_int_eq(retrieved->next->next->next->next->data.key, 30);
  ck_assert_int_eq(retrieved->next->next->next->next->next->data.key, -67);

  free(node6);
  free(node5);
  free(node4);
  free(node3);
  free(node2);
  free(node1);
}
END_TEST

START_TEST(test_dll_delete_1)
{
  DoublyLinkedList* node1;
  DoublyLinkedList* node2;

  *head = NULL;
  reg->key = -67;
  node1 = dll_insert(head, *reg);
  reg->key = 30;
  node2 = dll_insert(head, *reg);

  ck_assert_int_eq(node1->data.key, -67);
  ck_assert_int_eq(node1 == NULL, false);
  ck_assert_int_eq(node1->next == NULL, true);
  ck_assert_int_eq(node1->prev == NULL, false);
  ck_assert_int_eq(node1->prev->next->data.key, -67);

  ck_assert_int_eq(node2->data.key, 30);
  ck_assert_int_eq(node2 == NULL, false);
  ck_assert_int_eq(node2->next == NULL, false);
  ck_assert_int_eq(node2->prev == NULL, true);
  ck_assert_int_eq(node2->next->prev->data.key, 30);

  ck_assert_int_eq((*head) == NULL, false);
  ck_assert_int_eq((*head)->next == NULL, false);
  ck_assert_int_eq((*head)->prev == NULL, true);
  ck_assert_int_eq((*head)->data.key, 30);
  ck_assert_int_eq((*head)->next->data.key, -67);
  ck_assert_int_eq((*head)->next->prev->data.key, 30);

  dll_delete(head, node1);

  ck_assert_int_eq((*head)->data.key, 30);
  ck_assert_int_eq((*head)->next == NULL, true);
  ck_assert_int_eq((*head)->prev == NULL, true);

  free(node2);
  free(node1);
}
END_TEST

START_TEST(test_dll_delete_2)
{
  DoublyLinkedList* node1;
  DoublyLinkedList* node2;

  *head = NULL;
  reg->key = -67;
  node1 = dll_insert(head, *reg);
  reg->key = 30;
  node2 = dll_insert(head, *reg);

  ck_assert_int_eq(node1->data.key, -67);
  ck_assert_int_eq(node1 == NULL, false);
  ck_assert_int_eq(node1->next == NULL, true);
  ck_assert_int_eq(node1->prev == NULL, false);
  ck_assert_int_eq(node1->prev->next->data.key, -67);

  ck_assert_int_eq(node2->data.key, 30);
  ck_assert_int_eq(node2 == NULL, false);
  ck_assert_int_eq(node2->next == NULL, false);
  ck_assert_int_eq(node2->prev == NULL, true);
  ck_assert_int_eq(node2->next->prev->data.key, 30);

  ck_assert_int_eq((*head) == NULL, false);
  ck_assert_int_eq((*head)->next == NULL, false);
  ck_assert_int_eq((*head)->prev == NULL, true);
  ck_assert_int_eq((*head)->data.key, 30);
  ck_assert_int_eq((*head)->next->data.key, -67);
  ck_assert_int_eq((*head)->next->prev->data.key, 30);

  dll_delete(head, node2);

  ck_assert_int_eq((*head)->data.key, -67);
  ck_assert_int_eq((*head)->next == NULL, true);
  ck_assert_int_eq((*head)->prev == NULL, true);

  free(node2);
  free(node1);
}
END_TEST

START_TEST(test_dll_delete_3)
{
  DoublyLinkedList* node1;

  *head = NULL;
  reg->key = -67;
  node1 = dll_insert(head, *reg);

  ck_assert_int_eq((*head)->data.key, -67);

  ck_assert_int_eq(node1->data.key, -67);
  ck_assert_int_eq(node1 == NULL, false);
  ck_assert_int_eq(node1->next == NULL, true);
  ck_assert_int_eq(node1->prev == NULL, true);

  ck_assert_int_eq((*head)->data.key, -67);
  ck_assert_int_eq((*head) == NULL, false);
  ck_assert_int_eq((*head)->next == NULL, true);
  ck_assert_int_eq((*head)->prev == NULL, true);

  dll_delete(head, node1);

  ck_assert_int_eq((*head) == NULL, true);

  free(node1);
}
END_TEST

START_TEST(test_dll_delete_4)
{
  DoublyLinkedList* node1;
  DoublyLinkedList* node2;
  DoublyLinkedList* node3;

  *head = NULL;
  reg->key = 25;
  node1 = dll_insert(head, *reg);
  reg->key = 75;
  node2 = dll_insert(head, *reg);
  reg->key = 150;
  node3 = dll_insert(head, *reg);

  ck_assert_int_eq((*head)->data.key, 150);
  ck_assert_int_eq((*head)->prev == NULL, true);
  ck_assert_int_eq((*head)->next == NULL, false);
  ck_assert_int_eq((*head)->next->data.key, 75);
  ck_assert_int_eq((*head)->next->next->data.key, 25);

  ck_assert_int_eq(node3->data.key, 150);
  ck_assert_int_eq(node3->prev == NULL, true);
  ck_assert_int_eq(node3->next == NULL, false);
  ck_assert_int_eq(node3->next->data.key, 75);
  ck_assert_int_eq(node3->next->next->data.key, 25);

  ck_assert_int_eq(node2->data.key, 75);
  ck_assert_int_eq(node2->prev == NULL, false);
  ck_assert_int_eq(node2->next == NULL, false);
  ck_assert_int_eq(node2->prev->data.key, 150);
  ck_assert_int_eq(node2->next->data.key, 25);

  ck_assert_int_eq(node1->data.key, 25);
  ck_assert_int_eq(node1->prev == NULL, false);
  ck_assert_int_eq(node1->next == NULL, true);
  ck_assert_int_eq(node1->prev->data.key, 75);
  ck_assert_int_eq(node1->prev->prev->data.key, 150);

  dll_delete(head, node2);

  ck_assert_int_eq((*head)->data.key, 150);
  ck_assert_int_eq((*head)->prev == NULL, true);
  ck_assert_int_eq((*head)->next == NULL, false);
  ck_assert_int_eq((*head)->next->data.key, 25);

  ck_assert_int_eq(node3->data.key, 150);
  ck_assert_int_eq(node3->prev == NULL, true);
  ck_assert_int_eq(node3->next == NULL, false);
  ck_assert_int_eq(node3->next->data.key, 25);

  ck_assert_int_eq(node1->data.key, 25);
  ck_assert_int_eq(node1->prev == NULL, false);
  ck_assert_int_eq(node1->next == NULL, true);
  ck_assert_int_eq(node1->prev->data.key, 150);

  free(node3);
  free(node2);
  free(node1);
}
END_TEST

START_TEST(test_dll_delete_5)
{
  DoublyLinkedList* node;
  DoublyLinkedList* node1;
  DoublyLinkedList* node3;

  *head = NULL;
  reg->key = 25;
  node1 = dll_insert(head, *reg);
  reg->key = 75;
  dll_insert(head, *reg);
  reg->key = 150;
  node3 = dll_insert(head, *reg);

  node = dll_search(head, 75);

  ck_assert_int_eq((*head)->data.key, 150);
  ck_assert_int_eq((*head)->prev == NULL, true);
  ck_assert_int_eq((*head)->next == NULL, false);
  ck_assert_int_eq((*head)->next->data.key, 75);
  ck_assert_int_eq((*head)->next->next->data.key, 25);

  dll_delete(head, node);

  ck_assert_int_eq((*head)->data.key, 150);
  ck_assert_int_eq((*head)->prev == NULL, true);
  ck_assert_int_eq((*head)->next == NULL, false);
  ck_assert_int_eq((*head)->next->data.key, 25);

  free(node);
  free(node1);
  free(node3);
}
END_TEST

START_TEST(test_dll_delete_6)
{
  DoublyLinkedList* node1;
  DoublyLinkedList* node2;
  DoublyLinkedList* node3;

  *head = NULL;
  reg->key = 25;
  dll_insert(head, *reg);
  reg->key = 75;
  node3 = dll_insert(head, *reg);
  reg->key = 150;
  dll_insert(head, *reg);

  node1 = dll_search(head, 150);
  dll_delete(head, node1);
  node2 = dll_search(head, 25);
  dll_delete(head, node2);

  ck_assert_int_eq((*head)->data.key, 75);
  ck_assert_int_eq((*head)->prev == NULL, true);
  ck_assert_int_eq((*head)->next == NULL, true);

  free(node3);
  free(node2);
  free(node1);
}
END_TEST

Suite* make_test_suite(void)
{
  Suite* s;
  TCase* tc_core;

  s = suite_create("DoublyLinkedList Test Suite");

  /* Creation test case */
  tc_core = tcase_create("Test Cases with Setup and Teardown");

  tcase_add_checked_fixture(tc_core, setup, teardown);

  tcase_add_test(tc_core, test_dll_insert_1);
  tcase_add_test(tc_core, test_dll_insert_2);
  tcase_add_test(tc_core, test_dll_insert_3);

  tcase_add_test(tc_core, test_dll_search_1);
  tcase_add_test(tc_core, test_dll_search_2);
  tcase_add_test(tc_core, test_dll_search_3);
  tcase_add_test(tc_core, test_dll_search_4);

  tcase_add_test(tc_core, test_dll_delete_1);
  tcase_add_test(tc_core, test_dll_delete_2);
  tcase_add_test(tc_core, test_dll_delete_3);
  tcase_add_test(tc_core, test_dll_delete_4);
  tcase_add_test(tc_core, test_dll_delete_5);
  tcase_add_test(tc_core, test_dll_delete_6);

  suite_add_tcase(s, tc_core);

  return s;
}

int main(void)
{
  int number_failed;
  SRunner* sr;

  sr = srunner_create(make_test_suite());
  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_set_log(sr, "test.log");
  srunner_set_xml(sr, "test.xml");
  srunner_run_all(sr, CK_VERBOSE);

  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
