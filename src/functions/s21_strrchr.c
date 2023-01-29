#include "../s21_string.h"

/**
 * @brief Выполняет поиск последнего вхождения символа c (беззнаковый тип) в
 * строке, на которую указывает аргумент str.
 *
 * @param str строка, где ищем
 * @param c символ, который ищем
 * @return char*
 */
char *s21_strrchr(const char *str, int c) {
  char *ptr = s21_NULL;
  while (*str != '\0') {
    if (*str == c) {
      ptr = (char *)str;
    }
    str++;
  }
  if (*str == c) ptr = (char *)str;
  return ptr;
}
