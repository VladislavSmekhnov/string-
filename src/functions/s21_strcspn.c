#include "../s21_string.h"

/**
 * @brief Вычисляет длину начального сегмента str1, который полностью состоит из
 * символов, не входящих в str2.
 *
 * @param str1 строка, в которой вычисляем
 * @param str2 строка, с которой стравниваем
 * @return s21_size_t длина сегмента
 */
s21_size_t s21_strcspn(const char* str1, const char* str2) {
  const char* p;
  const char* a;
  int count = 0;
  for (p = str1; *p != '\0'; ++p) {
    for (a = str2; *a != '\0'; ++a) {
      if (*p == *a) {
        return count;
      }
      if (*(a + 1) == '\0') count++;
    }
  }
  return count;
}
