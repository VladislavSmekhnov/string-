#include "../s21_string.h"

/**
 * @brief Возвращает новую строку, в которой указанная строка (str) вставлена в
 * указанную позицию (start_index) в строке (src). В случае какой-либо ошибки
 * следует вернуть значение s21_NULL
 *
 * @param src строка, которую меняем
 * @param str строка, которую вставляем
 * @param start_index позиция в строке (src) куда надо вставить строку (str)
 * @return void* строку (src) со вставленной (str) в неё
 */
void* s21_insert(const char* src, const char* str, s21_size_t start_index) {
  char* result;

  if (src == s21_NULL || str == s21_NULL || start_index > s21_strlen(src)) {
    result = s21_NULL;
  } else {
    s21_size_t i, j;
    result = calloc(s21_strlen(src) + s21_strlen(str) + 1, sizeof(char));
    if (result) {
      for (i = 0; i < start_index; i++) result[i] = src[i];
      for (j = 0; j < s21_strlen(str); j++, i++) result[i] = str[j];
      for (j = start_index; src[j]; j++, i++) result[i] = src[j];
      result[i] = '\0';
    }
  }

  return (void*)result;
}
