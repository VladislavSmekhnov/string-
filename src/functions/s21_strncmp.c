#include "../s21_string.h"

/**
 * @brief Сравнивает не более первых n байтов str1 и str2.
 *
 * @param str1 строка для сравнения 1
 * @param str2 строка для сравнения 2
 * @param n количество первый байт для сравнения
 * @return int
 */
int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  int b = 0;
  unsigned char *b1 = (unsigned char *)str1;
  unsigned char *b2 = (unsigned char *)str2;

  for (s21_size_t i = 0; i < n; i++) {
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