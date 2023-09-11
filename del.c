/* Usunięcie prefiksu ze zbioru. Zwraca 0 lub -1 dla błędnych argumentów
wywołania. */

/// @brief Removing the prefix from the database.
/// @param base - value of the IP address to delete in range of 1 to MAX_IP.
/// @param mask - value of the IP subnet mask (CIDR) to delete in range of 1 to
/// @return Result of the delete operation: 0 when succesfull or -1 if not.
int del(const unsigned long int base, const char mask) {
  int result = -1;

  if ((MAX_MASK >= mask) && (0 <= mask) && (0UL < base) && (MAX_IP >= base)) {
    if (NULL != prefix_table[mask - 1]) {
      node_t* current_node_ptr = prefix_table[mask - 1];
      node_t* previous_node_ptr = NULL;

      /* Looking for a ip value in the tree */
      while ((NULL != current_node_ptr) && (base != current_node_ptr->ip)) {
        previous_node_ptr = current_node_ptr;
        if (base < current_node_ptr->ip) {
          current_node_ptr = current_node_ptr->left_child;
        } else {
          current_node_ptr = current_node_ptr->right_child;
        }
      }

      /* Found node has only one child */
      if ((NULL == current_node_ptr->left_child) ||
          (NULL == current_node_ptr->right_child)) {
        node_t* new_current_ptr = NULL;

        if (NULL == current_node_ptr->left_child) {
          new_current_ptr = current_node_ptr->right_child;
        } else {
          new_current_ptr = current_node_ptr->left_child;
        }

        /* Node to delete is a root */
        if (NULL == previous_node_ptr) {
          prefix_table[mask - 1] = new_current_ptr;
        } else {
          if (current_node_ptr == previous_node_ptr->left_child) {
            previous_node_ptr->left_child = new_current_ptr;
          } else {
            previous_node_ptr->right_child = new_current_ptr;
          }
        }

        free(current_node_ptr);
      }
      /* Found node has two children */
      else {
        node_t* parent_node = NULL;

        // Compute the inorder successor
        node_t* temporary_node_ptr = current_node_ptr->right_child;

        while (NULL != temporary_node_ptr->left_child) {
          parent_node = temporary_node_ptr;
          temporary_node_ptr = temporary_node_ptr->left_child;
        }

        if (NULL != parent_node) {
          parent_node->left_child = temporary_node_ptr->right_child;
        } else {
          current_node_ptr->right_child = temporary_node_ptr->right_child;
        }

        current_node_ptr->ip = temporary_node_ptr->ip;
        free(temporary_node_ptr);
      }

      result = 0;
    }
  }

  return result;
}