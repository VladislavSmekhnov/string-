#include "../s21_string.h"

/**
 * @brief Выполняет поиск первого вхождения символа c (беззнаковый тип) в
 * строке, на которую указывает аргумент str.
 *
 * @param str строка, в которой ищем символ c
 * @param c символ, вхождение которого ищем
 * @return char* указатель на символ c в строке str
 */
char *s21_strchr(const char *str, int c) {
  const char *s = str;
  while (*s != (char)c) {
    if (!*s++) {
      return s21_NULL;
    }
  }
  return (char *)s;
}
