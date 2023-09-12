
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "tree.h"

/* Constants */
/// @brief Maximal value of mask
#define MAX_MASK 32

/// @brief Maximal value of IP
#define MAX_IP 0xFFFFFFFF

/* Data structure init */
/// @brief An array of the tree roots for each mask (CIDR). Index is shifted by
/// 1 - i.e. table index 15 corresponds to mask "/16".
static node_t* prefix_table[MAX_MASK] = {NULL};

#include "add.c"
#include "check.c"
#include "del.c"

int main(void) {
  int result;

  result = add(0X0A000000, 16);
  printf("Adding 10.0.0.0/16 : result = %d\n", result);
  assert(0 == result);

  result = add(0x0A140000, 16);
  printf("Adding 10.20.0.0/16 : result = %d\n", result);
  assert(0 == result);

  result = add(0x0A000000, 8);
  printf("Adding 10.0.0.0/8 : result = %d\n", result);
  assert(0 == result);

  printf("\n");

  result = check(0x0A14FFFF);
  printf("Checking 10.20.255.255 : result = %d\n", result);
  assert(16 == result);

  result = check(0x0A150000);
  printf("Checking 10.21.0.0 : result = %d\n", result);
  assert(-1 == result);

  printf("\n");

  result = add(0X0A000000, 16);
  printf("Adding 10.0.0.0/16 again: result = %d\n", result);
  assert(-1 == result);

  printf("\n");

  result = add(0X020408000, 16);
  printf("Adding 32.64.128.0/16 : result = %d\n", result);
  assert(0 == result);

  printf("\n");

  result = del(0X0A000000, 16);
  printf("Deleting 10.0.0.0/16 : result = %d\n", result);
  assert(0 == result);

  result = del(0x0A000000, 8);
  printf("Deleting 10.0.0.0/8 : result = %d\n", result);
  assert(0 == result);

  printf("\n");

  return 0;
}
