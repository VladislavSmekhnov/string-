#include "s21_sprintf.h"

/**
 * @brief Отправляет форматированный вывод в строку, на которую указывает str.
 *
 * @param str С-строка, которую функция обрабатывает в качестве источника для
 * извлечения данных
 * @param format  это С-строка, содержащая один или несколько следующих
 * элементов: пробельный символ, непробельный символ и спецификаторы формата
 * @param ...
 * @return int код ошибки
 */
int s21_sprintf(char *str, const char *format, ...) {
  va_list ap;            // pointer to the argument stach
  va_start(ap, format);  // initialization ap
  int res = 0;           // printed characters counter
  int N = 0;             // array argument index of format
  int error = 1;
  str[0] = 0;
  while (N < 4000 && format[N] != 0 && error > 0) {
    if (format[N] == '%') {
      char specifier_str[MAX_SPEC] = {0};
      int specifier_length = specifier_parsing(format + N, specifier_str);
      if (specifier_length > 0) {
        struct specifier spec = {0, {0}, 0, 0, 0, {0}};
        error = decomp_specif(specifier_str, &spec);
        // add formatted specifier text
        if (error >= 0) {
          N = N + specifier_length;
          // replaces * with the value of the argument
          if (spec.width == -1) {
            spec.width = va_arg(ap, int);
            if (spec.width < 0) spec.width = -spec.width;
          }
          if (spec.precision == -1) {
            spec.precision = va_arg(ap, int);
            if (spec.precision < 0) {
              spec.precision = 0;
              spec.point = 0;
            }
          }
          out_put(&spec, &res, str, ap);
        }
      } else {
        error = -1;
      }
      if (error < 0) {
        if (format[N + 1] != 0) {
          s21_strcat(str, "%");
          error = 1;
        }
        res++;
        N++;
        str[res] = 0;
      }
    } else {
      str[res] = format[N];
      N++;
      res++;
      str[res] = 0;
    }
  }
  str[res] = 0;
  va_end(ap);
  if (error < 0) res = error;
  return res;
}

// returns the number of characters in the specifier, -1 - error
int specifier_parsing(const char *format, char *specifier_str) {
  int res = 0;
  s21_size_t cspn = s21_strcspn(format + 1, "cdieEfgGosuxXpn%");
  if (cspn != s21_strlen(format)) {
    s21_memcpy(specifier_str, format, cspn + 2);
    specifier_str[cspn + 2] = 0;
    res = (int)cspn + 2;
  } else {
    res = -1;
  }
  return res;
}

int decomp_specif(char *specifier_str, struct specifier *spec) {
  int error = 1;  // -1 -error
  char decomp_str[DEC_STR] = {0};
  int offset = 1;
  s21_size_t decomp = 0;
  // flags
  decomp = decomp_parsing(specifier_str, "-+ #0", &offset, decomp_str);
  if (decomp > 0) {
    decomp_flags(decomp_str, spec);
  }
  // width
  decomp = decomp_parsing(specifier_str, "0123456789*", &offset, decomp_str);
  if (decomp > 0) {
    error = decomp_width_or_precifier(decomp_str, &spec->width);
  }
  // point
  if (specifier_str[offset] == '.' && error >= 0) {
    spec->point = '.';
    offset++;
  }
  // precision
  decomp = decomp_parsing(specifier_str, "0123456789*", &offset, decomp_str);
  if (decomp > 0 && error >= 0) {
    error = decomp_width_or_precifier(decomp_str, &spec->precision);
  }
  // length
  if ((specifier_str[offset] == 'h' || specifier_str[offset] == 'l' ||
       specifier_str[offset] == 'L') &&
      error >= 0) {
    if (specifier_str[offset] == 'h') spec->length[0] = 'h';
    if (specifier_str[offset] == 'l') spec->length[1] = 'l';
    if (specifier_str[offset] == 'L') spec->length[2] = 'L';
    offset++;
  }
  // name
  if (s21_strpbrk(specifier_str + offset, "cdieEfgGosuxXpn%") ==
          specifier_str + offset &&
      error >= 0) {
    spec->name = specifier_str[offset];
  } else {
    error = -1;
  }
  return error;
}

// copies text with search characters
s21_size_t decomp_parsing(char *specifier_str, char *str, int *offset,
                          char *decomp_str) {
  s21_size_t spn = 0;
  spn = s21_strspn(specifier_str + *offset, str);
  if (spn > 0) {
    s21_memcpy(decomp_str, specifier_str + *offset, spn);
    decomp_str[spn] = 0;
    *offset = *offset + (int)spn;
  }
  return spn;
}

// define an array of flags
void decomp_flags(const char *decomp_str, struct specifier *spec) {
  int i = 0;
  const char flag_str[6] = "-+ #0";
  while (i < 4000 && decomp_str[i] != 0) {
    for (int n = 0; n < 5; n++) {
      if (decomp_str[i] == flag_str[n]) {
        spec->flags[n] = decomp_str[i];
        break;
      }
    }
    i++;
  }
}

int decomp_width_or_precifier(char *decomp_str, int *spec) {
  int error = 1;  // -1 -error
  char *c = s21_strchr(decomp_str, '*');
  if (c == decomp_str && decomp_str[1] == 0) {
    *spec = -1;  // -1 => *
  }
  if (s21_NULL == c) {
    *spec = string_to_number(decomp_str);
  }
  if (s21_NULL != c && decomp_str[1] != 0) {
    error = -1;
  }
  return error;
}

int string_to_number(char *str) {
  int sum = 0;
  int multiplier = 1;
  int N = (int)s21_strlen(str) - 1;
  while (N >= 0) {
    sum = sum + ((int)str[N] - 48) * multiplier;
    multiplier = multiplier * 10;
    N--;
  }
  return sum;
}

void out_put(struct specifier *spec, int *res, char *str, va_list ap) {
  switch (spec->name) {
    case 'c':
      out_spec_c(spec, res, str, ap);
      break;
    case 'd':
      out_spec_int(spec, 's', 10, res, str, ap);
      break;
    case 'i':
      out_spec_int(spec, 's', 10, res, str, ap);
      break;
    case 'e':
      out_spec_double(spec, res, str, ap);
      break;
    case 'E':
      out_spec_double(spec, res, str, ap);
      break;
    case 'f':
      out_spec_double(spec, res, str, ap);
      break;
    case 'g':
      out_spec_double(spec, res, str, ap);
      break;
    case 'G':
      out_spec_double(spec, res, str, ap);
      break;
    case 'o':
      out_spec_int(spec, 'u', 8, res, str, ap);
      break;
    case 's':
      out_spec_s(spec, res, str, ap);
      break;
    case 'u':
      out_spec_int(spec, 'u', 10, res, str, ap);
      break;
    case 'x':
      out_spec_int(spec, 'u', 16, res, str, ap);
      break;
    case 'X':
      out_spec_int(spec, 'u', 16, res, str, ap);
      break;
    case 'p':
      out_spec_int(spec, 'u', 16, res, str, ap);
      break;
    case 'n':
      out_spec_n(*res, ap);
      break;
    case '%':
      out_spec_percent(res, str, spec);
  }
}

void out_spec_c(struct specifier *spec, int *res, char *str, va_list ap) {
  struct specifier reference_spec = {0, {1, 0, 0, 0, 0, 0}, 1, 0,
                                     0, {0, 1, 0, 0}};
  del_err_flags(spec, &reference_spec);

  char extra_line[DEC_STR] = {0};
  if (spec->length[1] == 'l') {
    extra_line[0] = va_arg(ap, wchar_t);
  } else {
    extra_line[0] = (char)va_arg(ap, int);
  }

  fit_in_width(spec, extra_line);
  s21_strcat(str, extra_line);
  *res = *res + (int)s21_strlen(extra_line);
}

void fit_in_width(struct specifier *spec, char *extra_line) {
  int len = (int)s21_strlen(extra_line);
  char c = 0;
  char r[3] = {0};
  if (spec->flags[4] == '0' && extra_line[0] != '(') {
    c = '0';
    if (extra_line[0] == '+' || extra_line[0] == ' ' || extra_line[0] == '-' ||
        extra_line[0] == '0')
      r[0] = extra_line[0];
    if (extra_line[1] == 'x' || extra_line[1] == 'X' || extra_line[1] == '0')
      r[1] = extra_line[1];
    if (extra_line[2] == 'x' || extra_line[2] == 'X') r[2] = extra_line[2];
  } else {
    c = ' ';
  }
  if (len < spec->width) {
    int i = 0;
    if (spec->flags[0] == '-') {
      for (i = len; i < spec->width; i++) {
        extra_line[i] = c;
      }
      extra_line[i] = 0;
    } else {
      extra_line[spec->width] = 0;
      len = len - 1;
      for (i = spec->width - 1; i >= 0; i--) {
        if (len > 2) {
          extra_line[i] = extra_line[len];
          len = len - 1;
        } else if (len >= 0) {
          for (int m = 2; m >= 0; m--) {
            if (len == m) {
              if (r[m] == 0)
                extra_line[i] = extra_line[len];
              else
                extra_line[i] = c;
            }
          }
          len = len - 1;
        } else {
          extra_line[i] = c;
        }
      }
      for (int m = 0; m <= 2; m++) {
        if (r[m] != 0) extra_line[m] = r[m];
      }
    }
  }
}

void out_spec_int(struct specifier *spec, char sign, int denominator, int *res,
                  char *str, va_list ap) {
  struct specifier reference_spec_s = {0, {1, 1, 1, 0, 1, 0}, 1, 1,
                                       1, {1, 1, 1, 0}};
  struct specifier reference_spec_u = {0, {1, 0, 0, 1, 1, 0}, 1, 1,
                                       1, {1, 1, 1, 0}};
  struct specifier reference_spec_p = {0, {1, 1, 1, 1, 1, 0}, 1, 0,
                                       0, {0, 0, 0, 0}};
  if (sign == 's')
    del_err_flags(spec, &reference_spec_s);
  else {
    if (spec->name == 'p')
      del_err_flags(spec, &reference_spec_p);
    else
      del_err_flags(spec, &reference_spec_u);
  }

  char extra_line[DEC_STR] = {0};
  long long int va;
  if (spec->name == 'p') {
    va = (long long int)va_arg(ap, void *);
    spec->flags[3] = '#';
    spec->length[1] = 'l';
  } else
    va = va_arg(ap, long long int);

  // remove conflict flags
  if (spec->flags[1] != 0) spec->flags[2] = 0;  // ' ' ignored with +
  if (spec->flags[0] != 0) spec->flags[4] = 0;  // 0 ignored with -
  if (spec->precision != 0 || spec->point != 0)
    spec->flags[4] = 0;  // 0 ignored with prec

  int_num_to_str(spec, sign, va, extra_line, denominator);

  fit_in_width(spec, extra_line);
  s21_strcat(str, extra_line);
  *res = *res + (int)s21_strlen(extra_line);
}

// looks for the absence of invalid parameters
void del_err_flags(struct specifier *spec, struct specifier *reference_spec) {
  if (reference_spec->flags[0] == 0) spec->flags[0] = 0;
  if (reference_spec->flags[1] == 0) spec->flags[1] = 0;
  if (reference_spec->flags[2] == 0) spec->flags[2] = 0;
  if (reference_spec->flags[3] == 0) spec->flags[3] = 0;
  if (reference_spec->flags[4] == 0) spec->flags[4] = 0;

  if (reference_spec->width == 0) spec->width = 0;
  if (reference_spec->point == 0) spec->point = 0;
  if (reference_spec->precision == 0) spec->precision = 0;

  if (reference_spec->length[0] == 0) spec->length[0] = 0;
  if (reference_spec->length[1] == 0) spec->length[1] = 0;
  if (reference_spec->length[2] == 0) spec->length[2] = 0;
}

void int_num_to_str(struct specifier *spec, char sign, long long int va,
                    char *extra_line, int denominator) {
  if (spec->length[0] == 'h') {
    if (sign == 's')
      va = (short int)va;
    else
      va = (unsigned short)va;
  } else if (spec->length[1] == 'l') {
    if (sign == 's')
      va = (long int)va;
    else
      va = (unsigned long int)va;
  } else if (spec->length[2] == 'L') {
    if (sign == 's')
      va = (long long int)va;
    else
      va = (unsigned long long int)va;
  } else {
    if (sign == 's')
      va = (int)va;
    else
      va = (unsigned int)va;
  }

  int i = determine_first_char(spec, sign, (long double)va, extra_line);
  if (va < 0) va = -va;

  num_to_str(i, 'i', spec, denominator, va, extra_line);
}

int determine_first_char(struct specifier *spec, char sign, long double va,
                         char *extra_line) {
  int i = 0;
  if (sign == 's') {
    if (1 / va < 0) {
      extra_line[i] = '-';
      i++;
    } else {
      if (spec->flags[1] == '+') {
        extra_line[i] = '+';
        i++;
      }
      if (spec->flags[2] == ' ') {
        extra_line[i] = ' ';
        i++;
      }
    }
  } else {
    if (spec->flags[3] == '#') {
      if (spec->name == 'o' &&
          (va != 0 || (spec->point == '.' && spec->precision == 0))) {
        extra_line[i] = '0';
        i++;
      }
      if ((spec->name == 'x' || spec->name == 'X') && va != 0) {
        extra_line[i] = '0';
        extra_line[i + 1] = spec->name;
        i = i + 2;
      }
      if (spec->name == 'p' && va != 0) {
        if (spec->flags[1] == '+') {
          extra_line[i] = '+';
          i++;
        }
        if (spec->flags[2] == ' ') {
          extra_line[i] = ' ';
          i++;
        }
        extra_line[i] = '0';
        extra_line[i + 1] = 'x';
        i = i + 2;
      }
    }
  }
  extra_line[i] = 0;
  return i;
}

void num_to_str(int i, char type_num, struct specifier *spec, int denominator,
                unsigned long long int va, char *extra_line) {
  char num[17] = "0123456789abcdef";
  if (spec->name == 'X') {
    s21_strcpy(num + 10, "ABCDEF");
  }
  int n = DEC_STR - 1;
  int modulo = 0;  // remainder of the division
  if (va == 0 && type_num == 'i') {
    if (spec->point == '.' && spec->precision == 0)
      extra_line[n] = 0;
    else if (spec->name == 'p') {
      s21_strcpy(extra_line + n - 2, "0x0");
      n = n - 2;
    } else
      extra_line[n] = '0';
    n--;
  }
  if (va == 0 && type_num == 'd') {
    extra_line[n] = '0';
    n--;
  }
  while (va > 0 && n >= 0) {
    modulo = va % denominator;
    extra_line[n] = num[modulo];
    va = va / denominator;
    n--;
  }
  int M = 0;  // %o
  if (i > 0 && extra_line[i - 1] == '0') M = 1;
  if (type_num == 'i') {
    while (DEC_STR - 1 - n + M < spec->precision) {
      extra_line[n] = '0';
      n--;
    }
  }
  n++;
  while (n <= DEC_STR - 1) {
    extra_line[i] = extra_line[n];
    ++i;
    n++;
  }
  extra_line[i] = 0;
}

void out_spec_double(struct specifier *spec, int *res, char *str, va_list ap) {
  // remove conflict flags
  if (spec->flags[1] != 0) spec->flags[2] = 0;  // ' ' ignored with +
  if (spec->flags[0] != 0) spec->flags[4] = 0;  // 0 ignored with -

  char extra_line[DEC_STR] = {0};

  double_num_to_str(spec, 's', ap, extra_line);

  fit_in_width(spec, extra_line);
  s21_strcat(str, extra_line);
  *res = *res + (int)s21_strlen(extra_line);
}

void double_num_to_str(struct specifier *spec, char sign, va_list ap,
                       char *extra_line) {
  int i = 0;
  long double va = 0;
  unsigned long long int va_int = 0;
  unsigned long long int va_fraction = 0;
  int exp = 0;
  int ii;
  int del_flag = 0;
  if ((spec->name == 'G' || spec->name == 'g') && spec->flags[3] != '#')
    del_flag = 1;

  if (spec->point == 0) spec->precision = 6;

  if (spec->length[2] == 'L')
    va = va_arg(ap, long double);
  else
    va = (long double)va_arg(ap, double);

  if (isnan(va) == 0) {
    if (isinf(va) == 0) {
      i = determine_first_char(spec, sign, (long double)va, extra_line);
      va = fabsl(va);

      if (spec->name == 'g' || spec->name == 'G') {  // %g, %G
        ii = number_of_digits((long double)va);
        determ_output(ii, spec);
      }
      if (spec->name == 'e' || spec->name == 'E') va = s21_frexpl(va, &exp);

      if (spec->precision == 0) {
        va_int = (unsigned long long int)roundl(va);
        va_fraction = 0;
      } else {
        long double d_va_int = 0;
        long double d_va_fraction = 0;
        d_va_fraction = modfl(va, &d_va_int);

        va_fraction = (unsigned long long int)roundl(d_va_fraction *
                                                     powl(10, spec->precision));
        va_int = (unsigned long long int)d_va_int;
      }

      unsigned long long int I = va_fraction / powl(10, spec->precision);
      if (I > 0) {
        va_int = va_int + I;
        va_fraction = va_fraction - I * powl(10, spec->precision);
      }
      num_to_str(i, 'd', spec, 10, va_int, extra_line);
      i = (int)s21_strlen(extra_line);
      if (spec->precision != 0 || spec->flags[3] == '#') {
        extra_line[i] = '.';
        i++;
      }
      if (spec->precision != 0) {
        num_to_str(i, 'i', spec, 10, va_fraction, extra_line);
      }
      if (del_flag == 1) remove_last_spaces(extra_line);
      if (spec->name == 'e' || spec->name == 'E') {
        output_exp(spec, exp, extra_line);
      }
    } else {
      if (va > 0)
        s21_strcpy(extra_line, "inf");
      else
        s21_strcpy(extra_line, "-inf");
    }
  } else {
    if (va == NAN) {
      s21_strcpy(extra_line, "nan");
    } else {
      s21_strcpy(extra_line, "-nan");
    }
  }
}

void remove_last_spaces(char *extra_line) {
  if (s21_strchr(extra_line, '.')) {
    int i = (int)s21_strlen(extra_line) - 1;
    for (; i > 0; i--) {
      if (extra_line[i] == '0') {
        extra_line[i] = 0;
      } else if (extra_line[i] == '.') {
        extra_line[i] = 0;
        i = 0;
      } else {
        i = 0;
      }
    }
  }
}

int number_of_digits(long double I) {
  int i = 0;
  long double II = I;
  while (I >= 10 && i < 100) {
    I = I / 10;
    i++;
  }
  if (i == 0 && II > 0) {
    while (II < 1 && i > -100) {
      II = II * 10;
      i--;
    }
  }
  return i;
}

long double s21_frexpl(long double L_va, int *exp) {
  int flag = 1;
  int i = 0;
  *exp = 0;
  long double va = L_va;
  if (L_va < 1 && L_va > 0) {
    while (flag == 1 && i < 1000) {
      if (L_va + 1e-15 >= 1) {
        flag = 0;
      } else {
        L_va = L_va * 10;
        --*exp;
      }
      i++;
    }
  }
  if (L_va >= 1 && flag == 1) {
    while (flag == 1 && i < 1000) {
      if (L_va + 1e-15 < 10) {
        flag = 0;
      } else {
        L_va = L_va / 10;
        ++*exp;
      }
      i++;
    }
  }
  va = va / pow(10, *exp);
  return va;
}

void determ_output(int ii, struct specifier *spec) {
  if (spec->precision == 0) spec->precision = 1;

  if (spec->precision > ii && ii >= -4) {
    spec->name = 'f';
    spec->precision = spec->precision - ii - 1;
  } else {
    if (spec->name == 'g') spec->name = 'e';
    if (spec->name == 'G') spec->name = 'E';
    spec->precision--;
  }
}

void output_exp(struct specifier *spec, int exp, char *extra_line) {
  int i = (int)s21_strlen(extra_line);
  if (exp != 0 || spec->precision != 0) {
    extra_line[i] = spec->name;
    i++;
    if (exp < 0) {
      extra_line[i] = '-';
      exp = -exp;
    } else {
      extra_line[i] = '+';
    }
    const char num_str[11] = "0123456789";
    extra_line[i + 2] = num_str[exp % 10];
    exp = exp / 10;
    extra_line[i + 1] = num_str[exp % 10];
    extra_line[i + 3] = 0;
  }
}

void out_spec_s(struct specifier *spec, int *res, char *str, va_list ap) {
  struct specifier reference_spec = {0, {1, 0, 0, 0, 0, 0}, 1, 1,
                                     1, {0, 1, 0, 0}};
  del_err_flags(spec, &reference_spec);

  char extra_line[DEC_STR] = {0};

  if (spec->length[1] == 'l') {
    wchar_t *l_va = va_arg(ap, wchar_t *);
    s21_strcpy(extra_line, (char *)l_va);
  } else {
    char *va = va_arg(ap, char *);
    s21_strcpy(extra_line, va);
  }

  if (spec->point != 0) {
    extra_line[spec->precision] = 0;
  }
  fit_in_width(spec, extra_line);
  s21_strcat(str, extra_line);
  *res = *res + (int)s21_strlen(extra_line);
}

void out_spec_n(int res, va_list ap) {
  int *va = va_arg(ap, int *);
  *va = res;
}

void out_spec_percent(int *res, char *str, struct specifier *spec) {
  struct specifier reference_spec = {0, {1, 0, 1, 0, 1, 0}, 1, 0,
                                     0, {0, 0, 0, 0}};
  del_err_flags(spec, &reference_spec);

  char extra_line[DEC_STR] = {0};

  extra_line[0] = '%';

  fit_in_width(spec, extra_line);
  s21_strcat(str, extra_line);
  *res = *res + (int)s21_strlen(extra_line);
}
