#include "../s21_string.h"

/**
 * @brief Проверяет наличие символов для удаления в концах строки.
 *
 * @param src строка, в которой удаляем (вырезаем)
 * @param trim_chars список символов, подлежащих удалению (вырезке)
 * @param index номер элемента в строке src
 * @return int статус:
 * 0 - в концах строк нет символов для удаления (вырезки);
 * 1 - в концах строк есть символы для удаления (вырезки);
 */
int has_line_edges(const char *src, const char *trim_chars, int index) {
  int state = 0;
  int trim_length = s21_strlen(trim_chars);

  for (int i = 0; i < trim_length; i++)
    state = src[index] == trim_chars[i] ? 1 : state;

  return state;
}

/**
 * @brief Возвращает новую строку, в которой удаляются все начальные и конечные
 * вхождения набора заданных символов (trim_chars) из данной строки (src). В
 * случае какой-либо ошибки следует вернуть значение s21_NULL
 *
 * @param src строка, в которой удаляем (вырезаем)
 * @param trim_chars набор заданных символов, подлежащих удалению в строке src
 * @return void* новую изменённую строку
 */
void *s21_trim(const char *src, const char *trim_chars) {
  char *trimmed_str = s21_NULL;

  if (src) {
    if (trim_chars && trim_chars[0]) {
      trimmed_str = calloc(s21_strlen(src) + 1, sizeof(char));
      if (trimmed_str) {
        int start = 0;
        int end = s21_strlen(src);
        for (; has_line_edges(src, trim_chars, start); start++) {
        };
        if (start != end) {
          for (; has_line_edges(src, trim_chars, end - 1); end--) {
          };
          for (int i = 0; start < end; ++i) {
            trimmed_str[i] = src[start];
            start++;
          }
        } else {
          trimmed_str[0] = '\0';
        }
      }
    } else {
      trimmed_str = s21_trim(src, "\t\n ");
    }
  }

  return (void *)trimmed_str;
}
