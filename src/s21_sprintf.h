#ifndef S21_SPRINTF_H
#define S21_SPRINTF_H

#include <math.h>
#include <stdlib.h>

#include "s21_string.h"

typedef enum { zero, h, l, L } length_t;

typedef struct {
  int minus;
  int plus;
  int space;
  int sharp;
  int zero;
  int dot;
  int infnan;
} pr_flags;

typedef struct {
  pr_flags flags;
  char spec_symb;
  length_t length;
  int width;
  int accuracy;
  int error;
  int null_c;
} pr_spec;

int s21_sprintf(char *str, const char *format, ...);
pr_spec parse_spec(const char **format, va_list *arguments);
void parse_flags(const char **format, pr_spec *spec);
void parse_wid_acc(const char **format, pr_spec *spec, va_list *arguments);
void parse_length(const char **format, pr_spec *spec);
void check_spec(pr_spec *spec, char **str, va_list arguments, const char *pstr);
void spec_s(pr_spec *spec, char **buff, va_list arguments);
void spec_d_i(pr_spec *spec, char **buff, va_list arguments);
void spec_o_u_x_X_p(pr_spec *spec, char **buff, va_list arguments);
void spec_f(pr_spec *spec, char **buff, va_list arguments);
void spec_e_E(pr_spec *spec, char **buff, va_list arguments);
void spec_g_G(pr_spec *spec, char **buff, va_list arguments);
void s21_to_up(char str[]);
void s21_itoa(int64_t n, int type, char s[]);
void s21_uitoa(uint64_t n, int type, char s[]);
void s21_ftoa(long double n, pr_spec *spec, char s[]);
void sci_notation(long double number, pr_spec *spec, char *buffscinot);
void remove_nulls(char *buff);
void add_flags(pr_spec *spec, char **buff);
void add_precision(pr_spec *spec, char **buff);
void add_sciprecision(char **buff, pr_spec *spec);

#endif  // S21_SPRINTF_H
