#ifndef MAIN_H
#define MAIN_H

/// @brief Maximal value of mask
#define MAX_MASK 32

/// @brief Maximal value of IP
#define MAX_IP 0xFFFFFFFF

/// @brief Node tree structure
typedef struct node {
  unsigned long int ip;     /*!< IP address */
  struct node* parent;      /*!< Pointer to the parent node */
  struct node* right_child; /*!< Pointer to the right child node */
  struct node* left_child;  /*!< Pointer to the left child node */
} node_t;

/// @brief An array of the tree roots for each mask (CIDR). Index is shifted by
/// 1 - i.e. table index 15 corresponds to mask "/16".
node_t* mask_table[MAX_MASK];

#endif /* MAIN_H */