

/*!
 *  \brief     Add prefix function.
 *  \author    Maciej Domosud
 *  \details   Dodanie prefiksu do zbioru. Zwraca 0 lub -1 dla błędnych
 *             argumentów wywołania.
 */

/// @brief Adding new prefix to the database.
/// @param base - value of the IP address to store in range of 1 to MAX_IP.
/// @param mask - value of the IP subnet mask (CIDR) to store in range of 1 to
/// MAX_MASK.
/// @return Result of the addition operation: 0 when succesfull or -1 if not.
int add(const unsigned long int base, const char mask) {
  int result = -1;

  if ((MAX_MASK >= mask) && (0 <= mask) && (0UL < base) && (MAX_IP >= base)) {
    node_t* new_node_ptr;
    new_node_ptr = malloc(sizeof(node_t));

    if (NULL != new_node_ptr) {
      new_node_ptr->ip = base;
      new_node_ptr->left_child = NULL;
      new_node_ptr->right_child = NULL;

      /* Tree is empty */
      if (NULL == prefix_table[mask - 1]) {
        prefix_table[mask - 1] = new_node_ptr;
        result = 0;
      } else {
        node_t* next_node_ptr = prefix_table[mask - 1];
        node_t* current_node_ptr = NULL;

        /* Looking for a position for a new node in the tree */
        while (NULL != next_node_ptr) {
          current_node_ptr = next_node_ptr;
          if (base < next_node_ptr->ip) {
            next_node_ptr = next_node_ptr->left_child;
          } else if (base > next_node_ptr->ip) {
            next_node_ptr = next_node_ptr->right_child;
          } else {
            break; /* Duplicated value */
          }
        }

        if (base < current_node_ptr->ip) {
          current_node_ptr->left_child = new_node_ptr;
          result = 0;
        } else if (base > current_node_ptr->ip) {
          current_node_ptr->right_child = new_node_ptr;
          result = 0;
        } else {
          free(new_node_ptr); /* Duplicated value */
        }
      }

    } else {
      result = -1; /* No enough memory to create new node */
    }
  }

  return result;
}
