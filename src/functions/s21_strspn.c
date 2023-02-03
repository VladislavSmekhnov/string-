#include "../s21_string.h"

/**
 * @brief Вычисляет длину начального сегмента str1, который полностью состоит из
 * символов str2.
 *
 * @param str1 строка, в которой вычисляем длину сегмента
 * @param str2 строка, с которой сравниваем
 * @return s21_size_t длина сегмента
 */
s21_size_t s21_strspn(const char *str1, const char *str2) {
  int b = 0;
  int i = 0;
  while (str2[i]) {
    b = 0;
    for (int j = 0; str2[j]; j++) {
      if (str2[j] == str1[i]) b = 1;
    }
    if (b == 0) break;
    i++;
    if (b == 0 && i >= (int)sizeof(str2)) exit(1);
  }
  b = i;
  return b;
}
