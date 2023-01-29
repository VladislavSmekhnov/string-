#include "../s21_string.h"

/**
 * @brief Сравнивает первые n байтов str1 и str2.
 *
 * @param str1 строка для сравнения 1
 * @param str2 строка для сравнения 2
 * @param n количество первый байтов для сравнения
 * @return int
 */
int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  int b = 0;
  char *b1 = (char *)str1;
  char *b2 = (char *)str2;

  for (s21_size_t i = 0; i < n; ++i) {
    if (b1[i] > b2[i]) {
      b = 1;
      break;
    }
    if (b1[i] < b2[i]) {
      b = -1;
      break;
    }
  }

  return b;
}
