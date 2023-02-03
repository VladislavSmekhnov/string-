#include "../s21_string.h"

/**
 * @brief Добавляет строку, на которую указывает src, в конец строки, на которую
 * указывает dest, длиной до n символов.
 *
 * @param dest строка, к которой добавляем
 * @param src строка, которую добавляем
 * @param n максимальное количество символов из строки src
 * @return char* строку dest с добавленной к ней n символов из src
 */
char *s21_strncat(char *dest, const char *src, size_t n) {
  s21_size_t i, j;

  for (i = 0; dest[i] != '\0'; ++i) {
  }
  for (j = 0; src[j] != '\0' && j <= n; ++j) dest[i + j] = src[j];
  dest[i + j] = '\0';

  return dest;
}
