#include "../s21_string.h"

/**
 * @brief Сравнивает строку, на которую указывает str1, со строкой, на которую
 * указывает str2.
 *
 * @param str1 строка для сравнения 1
 * @param str2 строка для сравнения 2
 * @return int
 */
int s21_strcmp(const char *str1, const char *str2) {
  int b = 0;
  s21_size_t i = 0;
  char *b1 = (char *)str1;
  char *b2 = (char *)str2;

  while (1) {
    if (b1[i] > b2[i]) {
      b = 1;
      break;
    }
    if (b1[i] < b2[i]) {
      b = -1;
      break;
    }
    if (b1[i] == b2[i] && b1[i] == '\0') {
      b = 0;
      break;
    }
    i++;
  }

  return b;
}