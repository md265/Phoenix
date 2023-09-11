
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
static node_t* mask_table[MAX_MASK] = {NULL};

#include "add.c"
#include "check.c"
#include "del.c"

int main(void) {
  // prefix_t test_prefix = {.ip = 0xAABBCCDD, .mask = 10};

  // unsigned char bytes[4];
  // bytes[0] = test_prefix.ip & 0xFF;
  // bytes[1] = (test_prefix.ip >> 8) & 0xFF;
  // bytes[2] = (test_prefix.ip >> 16) & 0xFF;
  // bytes[3] = (test_prefix.ip >> 24) & 0xFF;
  // printf("%d.%d.%d.%d\n", bytes[3], bytes[2], bytes[1], bytes[0]);

  return 0;
}