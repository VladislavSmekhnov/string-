#include "../s21_string.h"

/**
 * @brief Возвращает копию строки (str), преобразованной в верхний регистр. В
 * случае какой-либо ошибки следует вернуть значение s21_NULL
 *
 * @param str строка, которую преобразовываем в верхний регистр
 * @return void* новая строка src, преобразованная в верхний регистр
 */
void *s21_to_upper(const char *str) {
  char *upper_str;
  s21_size_t str_length = s21_strlen(str);
  if (str == s21_NULL) {
    upper_str = s21_NULL;
  } else {
    upper_str = calloc(str_length + 1, sizeof(char));
    if (upper_str) {
      for (s21_size_t i = 0; i < str_length; ++i)
        upper_str[i] = (str[i] >= 'a' && str[i] <= 'z') ? str[i] - 32 : str[i];

      upper_str[str_length] = '\0';
    }
  }
  return (void *)upper_str;
}
