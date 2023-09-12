/* Sprawdzenie czy adres ip zawiera się w zbiorze prefiksów. Zwraca maskę
   najmniejszego prefiksu (o największej wartości maski) w zbiorze, który
   zawiera wskazany adres.
   Jeżeli ip nie zawiera się w zbiorze prefiksów zwraca -1. */

/// @brief Subnet masks related to the CIDR values. Array index is shifted by 1
/// - i.e. table index 15 corresponds to mask "/16".
static const unsigned long int mask_table[MAX_MASK] = {
    0xFFFFFFFE, 0xFFFFFFFC, 0xFFFFFFF8, 0xFFFFFFF0, 0xFFFFFFE0, 0xFFFFFFC0,
    0xFFFFFF80, 0xFFFFFF00, 0xFFFFFE00, 0xFFFFFC00, 0xFFFFF800, 0xFFFFF000,
    0xFFFFE000, 0xFFFFC000, 0xFFFF8000, 0xFFFF0000, 0xFFFE0000, 0xFFFC0000,
    0xFFF80000, 0xFFF00000, 0xFFE00000, 0xFFC00000, 0xFF800000, 0xFF000000,
    0xFE000000, 0xFC000000, 0xF8000000, 0xF0000000, 0xE0000000, 0xC0000000,
    0x80000000, 0x00000000};

/// @brief Find given IP address in prefix database.
/// @param ip - value of the IP address to find in range of 1 to MAX_IP.
/// @return Result of the delete operation: largest mask found when succesfull
/// or -1 if ip does not exist.
char check(const unsigned long int ip) {
  char result = -1;

  if ((0UL < ip) && (MAX_IP >= ip)) {
    /* Search in every mask tree in descending order */
    for (int index = (MAX_MASK - 1); index >= 0; index--) {
      node_t* root = prefix_table[index];

      /* Network IP calculating */
      const unsigned long int network_ip = ip & mask_table[index];

      /* Searching in the specified tree */
      while (NULL != root) {
        if (network_ip > root->ip) {
          root = root->right_child;
        } else if (network_ip < root->ip) {
          root = root->left_child;
        } else {
          /* Array index is shifted by 1 - it should be increased by one to get
           * the value of the netmask */
          result = index + 1;
          break;
        }
      }

      /* Only the first occurrence (with the highest value mask) is returned */
      if (result > -1) {
        break;
      }
    }
  }

  return result;
}
