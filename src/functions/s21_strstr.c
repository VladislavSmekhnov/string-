#include "../s21_string.h"

/**
 * @brief Находит первое вхождение всей строки needle (не включая завершающий
 * нулевой символ), которая появляется в строке haystack.
 *
 * @param haystack строка, в которой ищем вхождение needle
 * @param needle строка, которую ищем
 * @return char*
 */
char *s21_strstr(const char *haystack, const char *needle) {
  char *position = s21_NULL;
  int err = 0;
  char *chaystack = (char *)haystack;
  if (s21_strlen(needle) == 0) {
    position = chaystack;
  } else {
    for (s21_size_t i = 0; i < s21_strlen(chaystack); ++i) {
      if (chaystack[i] == needle[0]) {
        position = &chaystack[i];
        for (s21_size_t j = i, k = 0; j < s21_strlen(needle) + i; ++j, k++) {
          if (chaystack[j] != needle[k]) {
            err = 1;
          }
        }
        if (err == 0) {
          break;
        } else {
          position = s21_NULL;
          err = 0;
          continue;
        }
      }
    }
  }
  return position;
}