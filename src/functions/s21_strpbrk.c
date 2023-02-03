#include "../s21_string.h"

/**
 * @brief Находит первый символ в строке str1, который соответствует любому
 * символу, указанному в str2.
 *
 * @param str1 строка, в которой ищем
 * @param str2 строка, с которой сравниваем
 * @return char*
 */
char *s21_strpbrk(const char *str1, const char *str2) {
  if ((str1 == NULL) || (str2 == NULL)) return NULL;
  while (*str1) {
    if (s21_strchr(str2, *str1)) {
      return (char *)str1;
    } else {
      str1++;
    }
  }
  return s21_NULL;
}
