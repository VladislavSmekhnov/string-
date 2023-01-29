#include "../s21_string.h"

/**
 * @brief Находит последний разделитель.
 *
 * @param str строка, в которой находим последний разделитель
 * @param delim разделитель, который находим
 * @return char* указатель на символ строки src после разделителя
 */
char* find_last_separator(char* str, const char* delim) {
  int flag = 0;
  char* res = str;
  char* str1 = str;
  for (long unsigned int i = 0; i < s21_strlen(str1) && flag == 0; i++) {
    int next = 0;
    for (long unsigned int j = 0;
         j < s21_strlen(delim) && flag == 0 && next == 0; j++) {
      if (str[i] == delim[j]) {
        str[i] = '\0';
        str1 = &str[i + 1];
        next = 1;
      } else if (j == s21_strlen(delim) - 1) {
        flag = 1;
        res = &str[i];
      }
    }
  }
  if (flag == 0) res = 0;

  return res;
}

/**
 * @brief Разбивает строку str на ряд токенов, разделенных delim.
 *
 * @param str строка, которую разбиваем
 * @param delim набор разделителей
 * @return char* токен до первого разделителя
 */
char* s21_strtok(char* str, const char* delim) {
  static char* start = 0;
  if (str != 0) start = str;

  int flag = 0;
  char* search = start;
  s21_size_t start_length = s21_strlen(start);
  s21_size_t delim_length = s21_strlen(delim);

  if (start != 0 && start_length > 0) {
    for (long unsigned int i = 0; i < start_length && flag == 0; i++)
      for (long unsigned int j = 0; j < delim_length && flag == 0; j++)
        if (start[i] == delim[j]) {
          start[i] = '\0';
          start = find_last_separator(start + i + 1, delim);
          flag = 1;
        }
  }
  if (flag == 0) search = 0;

  return search;
}
