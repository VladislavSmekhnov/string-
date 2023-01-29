#include "../s21_string.h"

/**
 * @brief Копирует до n символов из строки, на которую указывает src, в dest.
 *
 * @param dest строка куда копируем n символов
 * @param src строка откуда копируем n символов
 * @param n количество символов для копирования
 * @return char*
 */
char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  char *p = dest;

  size_t i = 0;

  while (*src != '\0' && i < n) {
    *p = *src;

    p++;
    src++;

    i++;
  }

  while (i < n) {
    *p = '\0';
    p++;
    i++;
  }

  return dest;
}
