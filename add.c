

/* Dodanie prefiksu do zbioru.
   Zwraca 0 lub -1 dla błędnych argumentów wywołania. */
/// @brief
/// @param base -
/// @param mask -
/// @return
int add(const unsigned long int base, const char mask) {
  int result = -1;

  if ((MAX_MASK >= mask) && (0 <= mask) && (0UL < base) && (MAX_IP >= base)) {
    result = 0;
  }

  return result;
}