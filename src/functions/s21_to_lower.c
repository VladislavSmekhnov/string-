#include "../s21_string.h"

/**
 * @brief Возвращает копию строки (str), преобразованной в нижний регистр. В
 * случае какой-либо ошибки следует вернуть значение s21_NULL
 *
 * @param str строка, которую преобразовываем в нижний регистр
 * @return void* новая строка src, преобразованная в нижний регистр
 */
void *s21_to_lower(const char *str) {
  char *lower_str;
  s21_size_t str_length = s21_strlen(str);
  if (str == s21_NULL) {
    lower_str = s21_NULL;
  } else {
    lower_str = calloc(str_length + 1, sizeof(char));
    if (lower_str) {
      for (s21_size_t i = 0; i < str_length; ++i)
        lower_str[i] = (str[i] >= 'A' && str[i] <= 'Z') ? str[i] + 32 : str[i];

      lower_str[str_length] = '\0';
    }
  }
  return (void *)lower_str;
}
