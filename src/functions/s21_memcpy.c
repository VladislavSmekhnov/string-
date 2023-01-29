#include "../s21_string.h"

/**
 * @brief Копирует n символов из src в dest.
 *
 * @param dest куда копируем
 * @param src откуда копируем
 * @param n количество символов для копирования
 * @return void*
 */
void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  char *pd = (char *)dest;
  const char *ps = (const char *)src;

  size_t i = 0;

  while (i < n) {
    *pd = *ps;

    pd++;
    ps++;

    i++;
  }

  return dest;
}
