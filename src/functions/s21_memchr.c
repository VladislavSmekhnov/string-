#include "../s21_string.h"

/**
 * @brief Выполняет поиск первого вхождения символа c (беззнаковый тип) в первых
 * n байтах строки, на которую указывает аргумент str.
 *
 * @param str строка, в которой ищем первое вхождение c
 * @param c символ, первое вхождение которого ищем
 * @param n количество первых байт для поиска вхождения c в str
 * @return void*
 */
void *s21_memchr(const void *str, int c, s21_size_t n) {
  unsigned char *s = (unsigned char *)str;
  unsigned char *find = s21_NULL;
  while ((str != s21_NULL) && (n--)) {
    if (*s != (unsigned char)c) {
      s++;
    } else {
      find = s;
      break;
    }
  }
  return (void *)find;
}
