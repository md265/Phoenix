#ifndef TREE_H
#define TREE_H

/// @brief Node tree structure
typedef struct node {
  unsigned long int ip;     /*!< IP address */
  struct node* right_child; /*!< Pointer to the right child node */
  struct node* left_child;  /*!< Pointer to the left child node */
} node_t;

#endif /* TREE_H */