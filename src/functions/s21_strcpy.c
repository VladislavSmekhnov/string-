#include "../s21_string.h"

/**
 * @brief Копирует строку, на которую указывает src, в dest.
 *
 * @param dest строка, куда копируем строку src
 * @param src строка, которую копируем в dest
 * @return char*
 */
char *s21_strcpy(char *dest, const char *src) {
  char *p = dest;
  while (*src != '\0') {
    *p = *src;
    p++;
    src++;
  }
  *p = '\0';
  return dest;
}
