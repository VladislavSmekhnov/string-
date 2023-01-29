#include "../s21_string.h"

/**
 * @brief Вычисляет длину строки str, не включая завершающий нулевой символ.
 *
 * @param str строка, для которой вычисляем длину
 * @return s21_size_t длина строки str
 */
s21_size_t s21_strlen(const char *str) {
  s21_size_t len = 0;
  for (; str[len]; len++)
    ;
  return len;
}
