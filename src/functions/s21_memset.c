#include "../s21_string.h"

/**
 * @brief Копирует символ c (беззнаковый тип) в первые n символов строки, на
 * которую указывает аргумент str.
 *
 * @param str откуда копируем
 * @param c копируемый символ
 * @param n количество символов для копирования
 * @return void*
 */
void *s21_memset(void *str, int c, s21_size_t n) {
  unsigned char *p = (unsigned char *)str;

  for (s21_size_t i = 0; i < n; i++) p[i] = (unsigned char)c;

  return str;
}
