#include "../s21_string.h"

/**
 * @brief Еще одна функция для копирования n символов из src в dest.
 *
 * @param dest куда копируем
 * @param src откуда копируем
 * @param n количество символов для копирования
 * @return void*
 */
void *s21_memmove(void *dest, const void *src, s21_size_t n) {
  char *d = (char *)dest;
  const char *s = (const char *)src;

  if (!d || !s) {
    s = s21_NULL;
  } else {
    if (s < d) {
      for (d = d + n, s = s + n; n--;) *(--d) = *(--s);
    } else {
      while (n--) {
        *(d++) = *(s++);
      }
    }
  }
  return dest;
}
