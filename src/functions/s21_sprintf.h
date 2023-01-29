#ifndef SRC_FUNCTIONS_S21_SPRINTF_H_
#define SRC_FUNCTIONS_S21_SPRINTF_H_

#include <math.h>
#include <stdarg.h>

#include "../s21_string.h"

#define MAX_SPEC 4000
#define DEC_STR 4000

struct specifier {
  char name;
  char flags[6];  // -+( )#0
  int width;
  char point;
  int precision;
  char length[4];
};

int s21_sprintf(char *str, const char *format, ...);
int specifier_parsing(const char *format, char *specifier_str);
int decomp_specif(char *specifier_str, struct specifier *spec);
s21_size_t decomp_parsing(char *specifier_str, char *str, int *offset,
                          char *decomp_str);
void decomp_flags(const char *decomp_str, struct specifier *spec);
int decomp_width_or_precifier(char *decomp_str, int *spec);
int string_to_number(char *str);
void out_put(struct specifier *spec, int *res, char *str, va_list ap);
void out_spec_c(struct specifier *spec, int *res, char *str, va_list ap);
void fit_in_width(struct specifier *spec, char *extra_line);
void out_spec_int(struct specifier *spec, char sign, int denominator, int *res,
                  char *str, va_list ap);
int determine_first_char(struct specifier *spec, char sign, long double va,
                         char *extra_line);
void del_err_flags(struct specifier *spec, struct specifier *reference_spec);
void int_num_to_str(struct specifier *spec, char sign, long long int va,
                    char *extra_line, int denominator);
void num_to_str(int i, char type_num, struct specifier *spec, int denominator,
                unsigned long long int va, char *extra_line);
void out_spec_double(struct specifier *spec, int *res, char *str, va_list ap);
void double_num_to_str(struct specifier *spec, char sign, va_list ap,
                       char *extra_line);
void remove_last_spaces(char *extra_line);
int number_of_digits(long double I);
long double s21_frexpl(long double L_va, int *exp);
void determ_output(int ii, struct specifier *spec);
void output_exp(struct specifier *spec, int exp, char *extra_line);
void out_spec_s(struct specifier *spec, int *res, char *str, va_list ap);
void out_spec_n(int res, va_list ap);
void out_spec_percent(int *res, char *str, struct specifier *spec);

#endif  // SRC_FUNCTIONS_S21_SPRINTF_H_
