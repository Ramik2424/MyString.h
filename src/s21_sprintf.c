#include "s21_sprintf.h"

int s21_sprintf(char *str, const char *format, ...) {
  const char *pstr = str;
  va_list arguments;
  va_start(arguments, format);
  pr_spec spec = {0};
  while (*format) {
    if (spec.null_c) {
      *str++ = '\0';
      spec.null_c = 0;
    }
    if (*format != '%') {
      *str++ = *format++;
      continue;
    } else {
      format++;
      spec = parse_spec(&format, &arguments);
      check_spec(&spec, &str, arguments, pstr);
    }
  }
  *str = '\0';
  va_end(arguments);

  return str - pstr;
}

pr_spec parse_spec(const char **format, va_list *arguments) {
  pr_spec spec = {0};
  parse_flags(format, &spec);
  parse_wid_acc(format, &spec, arguments);
  parse_length(format, &spec);
  spec.spec_symb = **format;
  (*format)++;
  return spec;
}

void parse_flags(const char **format, pr_spec *spec) {
  while (**format == '0' || **format == ' ' || **format == '-' ||
         **format == '+' || **format == '#') {
    if (**format == '0')
      spec->flags.zero = 1;
    else if (**format == ' ')
      spec->flags.space = 1;
    else if (**format == '-')
      spec->flags.minus = 1;
    else if (**format == '+')
      spec->flags.plus = 1;
    else if (**format == '#')
      spec->flags.sharp = 1;
    (*format)++;
  }
}

void parse_wid_acc(const char **format, pr_spec *spec, va_list *arguments) {
  int size = 0;
  int minus = 0;
  if (**format == '*') {
    size = va_arg(*arguments, int);
    if (size < 0 && !spec->flags.dot) {
      size = -size;
      minus = 1;
    }
    (*format)++;
  } else if (**format > 47 && **format < 58) {
    while (**format > 47 && **format < 58) {
      size = size * 10 + (**format - 48);
      (*format)++;
    }
  }
  if (spec->flags.dot)
    spec->accuracy = size;
  else {
    spec->width = size;
    if (minus) spec->flags.minus = 1;
  }
  if (**format == '.') {
    spec->flags.dot = 1;
    (*format)++;
    parse_wid_acc(format, spec, arguments);
  }
}

void parse_length(const char **format, pr_spec *spec) {
  if (**format == 'h') {
    spec->length = h;
    (*format)++;
  } else if (**format == 'l') {
    spec->length = l;
    (*format)++;
  } else if (**format == 'L') {
    spec->length = L;
    (*format)++;
  }
}

void check_spec(pr_spec *spec, char **str, va_list arguments,
                const char *pstr) {
  char *buffer = (char *)calloc(256, sizeof(char));
  if (spec->spec_symb == 'c') {
    buffer[0] = va_arg(arguments, int);
    buffer[1] = '\0';
    if (buffer[0] == '\0') spec->null_c = 1;
    spec->accuracy = 0;
  } else if (spec->spec_symb == 'd' || spec->spec_symb == 'i')
    spec_d_i(spec, &buffer, arguments);
  else if (spec->spec_symb == 'e' || spec->spec_symb == 'E')
    spec_e_E(spec, &buffer, arguments);
  else if (spec->spec_symb == 'f')
    spec_f(spec, &buffer, arguments);
  else if (spec->spec_symb == 'g' || spec->spec_symb == 'G')
    spec_g_G(spec, &buffer, arguments);
  else if (spec->spec_symb == 'o' || spec->spec_symb == 'x' ||
           spec->spec_symb == 'X' || spec->spec_symb == 'u' ||
           spec->spec_symb == 'p')
    spec_o_u_x_X_p(spec, &buffer, arguments);
  else if (spec->spec_symb == 's')
    spec_s(spec, &buffer, arguments);
  else if (spec->spec_symb == 'n')
    *(va_arg(arguments, int *)) = *str - pstr;
  else if (spec->spec_symb == '%') {
    buffer[0] = '%';
    buffer[1] = '\0';
  }
  if (spec->null_c)
    **str = '\0';
  else {
    if (spec->flags.infnan) {
      spec->spec_symb = 's';
      spec->accuracy = 0;
      spec->flags.zero = spec->flags.plus = 0;
      spec->flags.sharp = spec->flags.space = 0;
    }
    if (spec->spec_symb != 'g' && spec->spec_symb != 'G')
      add_precision(spec, &buffer);
    add_flags(spec, &buffer);
    int i = 0;

    while (buffer[i] != '\0') {
      **str = buffer[i];
      (*str)++;
      i++;
    }
  }
  free(buffer);
}

void spec_f(pr_spec *spec, char **buff, va_list arguments) {
  long double value = 0;
  if (spec->length == L) {
    value = va_arg(arguments, long double);
  } else {
    value = va_arg(arguments, double);
  }
  if (!spec->flags.dot) {
    spec->accuracy = 6;
    spec->flags.dot = 1;
  }
  if (value != value) {
    s21_strcpy(*buff, "nan");
    spec->flags.infnan = 1;
  } else if (value == INFINITY) {
    s21_strcpy(*buff, "inf");
    spec->flags.infnan = 1;
  } else if (value == -INFINITY) {
    s21_strcpy(*buff, "-inf");
    spec->flags.infnan = 1;
  } else
    s21_ftoa(value, spec, *buff);
}

void spec_e_E(pr_spec *spec, char **buff, va_list arguments) {
  long double value = 0;
  if (spec->length == L) {
    value = va_arg(arguments, long double);
  } else {
    value = va_arg(arguments, double);
  }
  if (!spec->flags.dot) {
    spec->accuracy = 6;
    spec->flags.dot = 1;
  }
  if (value != value) {
    s21_strcpy(*buff, "nan");
    spec->flags.infnan = 1;
  } else if (value == INFINITY) {
    s21_strcpy(*buff, "inf");
    spec->flags.infnan = 1;
  } else if (value == -INFINITY) {
    s21_strcpy(*buff, "-inf");
    spec->flags.infnan = 1;
  } else
    sci_notation(value, spec, *buff);
  if (spec->spec_symb == 'E') s21_to_up(*buff);
}

void spec_g_G(pr_spec *spec, char **buff, va_list arguments) {
  long double value = 0;
  if (spec->length == L) {
    value = va_arg(arguments, long double);
  } else {
    value = va_arg(arguments, double);
  }
  if (!spec->flags.dot) {
    spec->accuracy = 6;
    spec->flags.dot = 1;
  }
  if (value != value) {
    s21_strcpy(*buff, "nan");
    spec->flags.infnan = 1;
  } else if (value == INFINITY) {
    s21_strcpy(*buff, "inf");
    spec->flags.infnan = 1;
  } else if (value == -INFINITY) {
    s21_strcpy(*buff, "-inf");
    spec->flags.infnan = 1;
  } else if (value == 0.0) {
    if (spec->flags.sharp) {
      if (spec->accuracy == 1) spec->accuracy = 0;
      spec->accuracy--;
      s21_ftoa(value, spec, *buff);
    } else
      s21_strcpy(*buff, "0");
  } else {
    long double tmp = fabsl(value);
    int tmp_prec = 0;
    while (tmp < 9.999999e-01) {
      tmp *= 10;
      tmp_prec++;
    }
    if (value < 9.999999e-01 && spec->flags.sharp) tmp_prec--;
    if (!spec->accuracy && fabsl(value) < 1) {
      spec->accuracy = tmp_prec;
    }
    if (fabsl(value) >= 9.999999e-05 &&
        fabsl(value) < pow(10., !spec->accuracy ? 1 : spec->accuracy)) {
      if (spec->flags.sharp) spec->accuracy += tmp_prec;
      s21_ftoa(value, spec, *buff);
      if (spec->accuracy) add_sciprecision(buff, spec);
      if (spec->flags.sharp) spec->accuracy -= tmp_prec;
      if (!spec->flags.sharp) remove_nulls(*buff);
    } else {
      if (!spec->flags.sharp) spec->accuracy--;
      sci_notation(value, spec, *buff);
    }
  }
  if (spec->spec_symb == 'G') s21_to_up(*buff);
}

void spec_s(pr_spec *spec, char **buff, va_list arguments) {
  char *temp = S21_NULL;
  temp = va_arg(arguments, char *);
  if (temp == S21_NULL)
    s21_strcpy(*buff, "(null)");
  else {
    size_t len_of_s = s21_strlen(temp) + 1;
    if (len_of_s > 255) {
      temp = (char *)realloc(*buff, (len_of_s * sizeof(char)));
      if (temp == S21_NULL) {
        free(temp);
        spec->error = -1;
      } else if (temp == *buff) {
        free(temp);
      } else {
        *buff = temp;
        temp = S21_NULL;
      }
    }
    if (spec->error != -1)
      s21_strncpy(*buff, temp,
                  spec->flags.dot ? (size_t)spec->accuracy
                                  : s21_strlen(temp));  // s21_s21_strcpy
  }
  spec->accuracy = 0;
  spec->flags.zero = spec->flags.plus = 0;
  spec->flags.sharp = spec->flags.space = 0;
}

void spec_d_i(pr_spec *spec, char **buff, va_list arguments) {
  int64_t value = va_arg(arguments, int64_t);
  if (spec->length == h) {
    value = (int16_t)value;
  } else if (spec->length == zero) {
    value = (int32_t)value;
  }
  if (value == 0 && spec->flags.dot && spec->accuracy == 0) {
    **buff = '\0';
  } else {
    s21_itoa((int64_t)value, 10, *buff);
  }
}

void spec_o_u_x_X_p(pr_spec *spec, char **buff, va_list arguments) {
  uint64_t value = va_arg(arguments, uint64_t);
  char *temp = (char *)calloc(252, sizeof(char));
  if (spec->spec_symb == 'p') {
    if (value == 0)
      s21_strcpy(*buff, "(nil)");
    else {
      s21_uitoa((uint64_t)value, 16, temp);
      s21_strcpy(*buff, "0x");
      s21_strcat(*buff, temp);
    }
  } else if (spec->length == h) {
    value = (uint16_t)value;
  } else if (spec->length == zero) {
    value = (uint32_t)value;
  }
  if (value == 0 && spec->flags.dot && spec->accuracy == 0) {
    **buff = '\0';
  } else {
    if (spec->spec_symb == 'o') {
      s21_uitoa((uint64_t)value, 8, temp);
      s21_strcpy(*buff, spec->flags.sharp ? !value ? "" : "0" : "");
      s21_strcat(*buff, temp);
    } else if (spec->spec_symb == 'x' || spec->spec_symb == 'X') {
      s21_uitoa((uint64_t)value, 16, temp);
      s21_strcpy(*buff, spec->flags.sharp ? !value ? "" : "0x" : "");
      s21_strcat(*buff, temp);
      if (spec->spec_symb == 'X') s21_to_up(*buff);
    } else if (spec->spec_symb == 'u') {
      s21_uitoa((uint64_t)value, 10, temp);
      s21_strcpy(*buff, spec->flags.sharp ? !value ? "" : "0" : "");
      s21_strcat(*buff, temp);
    }
  }
  free(temp);
}

void s21_itoa(int64_t n, int type, char s[]) {
  int64_t sign = n;
  if (n == INT64_MIN)
    s21_strcpy(s, "-9223372036854775808");
  else {
    int64_t it = 0;
    if (sign < 0) n = -n;
    do {
      s[it++] = n % type + ((n % type) <= 9 ? '0' : 'W');
    } while ((n /= type) > 0);
    if (sign < 0) s[it++] = '-';
    s[it] = '\0';
    for (int i = 0, j = it - 1; i < j; i++, j--) {
      char c = s[i];
      s[i] = s[j];
      s[j] = c;
    }
  }
}

void s21_ftoa(long double n, pr_spec *spec, char s[]) {
  long double sign = n;
  char *buffm = (char *)calloc(253, sizeof(char));
  char *buffe = (char *)calloc(spec->accuracy + 2, sizeof(char));
  if (sign < 0) n = -n;
  long double tempm = 0, temp = modfl(n, &tempm);
  temp = spec->accuracy ? temp : 0;
  uint64_t mantissa = spec->accuracy ? tempm : roundl(n);

  int i = 0;
  while (i < spec->accuracy) {
    temp *= 10.;
    int digit = 0;
    digit = (int)temp;
    buffe[i++] = digit + '0';
    temp -= digit;
  }
  buffe[i] = '\0';

  int lastDigit = temp *= 10.;
  if (lastDigit >= 5) {
    int carry = 1;
    for (int j = spec->accuracy - 1; j >= 0; j--) {
      int digit = buffe[j] - '0' + carry;
      carry = digit / 10;
      digit %= 10;
      buffe[j] = digit + '0';
    }
    if (carry) mantissa++;
  }

  s21_uitoa(mantissa, 10, buffm);
  if (sign < 0) {
    s21_strcpy(s, "-");
    s21_strcat(s, buffm);
  } else
    s21_strcpy(s, buffm);
  if (spec->accuracy != 0) s21_strcat(s, ".");
  s21_strcat(s, buffe);
  free(buffm);
  free(buffe);
}

void s21_uitoa(uint64_t n, int type, char s[]) {
  uint64_t it = 0;
  do {
    s[it++] = n % type + ((n % type) <= 9 ? '0' : 'W');
  } while ((n /= type) > 0);
  s[it] = '\0';
  for (int i = 0, j = it - 1; i < j; i++, j--) {
    char c = s[i];
    s[i] = s[j];
    s[j] = c;
  }
}

void s21_to_up(char str[]) {
  int i = 0;
  while (str[i] != '\0') {
    if (str[i] > 96 && str[i] < 123) str[i] -= 32;
    i++;
  }
}

void sci_notation(long double number, pr_spec *spec, char *buffscinot) {
  char *buffexp = (char *)calloc(12, sizeof(char));
  char *numexp = (char *)calloc(10, sizeof(char));
  int exponent = 0;

  if (fabsl(number) != 0.0) {
    while (fabsl(number) < 1.0 || fabsl(number) >= 10.0) {
      if (fabsl(number) >= 10.0) {
        number /= 10.0;
        exponent++;
      }
      if (fabsl(number) < 1.0) {
        number *= 10.0;
        exponent--;
      }
    }
  }
  if (fabsl(number) - floorl(fabsl(number)) >= 0.999) {
    number /= 10.0;
    exponent++;
  }
  if (exponent < 0) {
    s21_strcpy(buffexp, "e-");
    exponent = -exponent;
  } else
    s21_strcpy(buffexp, "e+");
  s21_ftoa(number, spec, buffscinot);
  if (!s21_strcmp(buffscinot, "10") || !s21_strcmp(buffscinot, "-10")) {
    exponent++;
    number /= 10.0;
    s21_ftoa(number, spec, buffscinot);
  }
  s21_itoa((int64_t)exponent, 10, numexp);
  if (s21_strlen(numexp) < 2) s21_strcat(buffexp, "0");
  s21_strcat(buffexp, numexp);

  if (spec->spec_symb == 'g' || spec->spec_symb == 'G') {
    add_sciprecision(&buffscinot, spec);
    if (!spec->flags.sharp) remove_nulls(buffscinot);
  }

  s21_strcat(buffscinot, buffexp);
  buffscinot[s21_strlen(buffscinot)] = '\0';
  free(buffexp);
  free(numexp);
}

void remove_nulls(char *buff) {
  if (s21_strchr(buff, '.') != S21_NULL) {
    int i = s21_strlen(buff) - 1;
    while (buff[i] == '0' || buff[i] == '.') {
      if (buff[i] == '.') {
        buff[i--] = '\0';
        break;
      }
      buff[i--] = '\0';
    }
  }
}

void add_precision(pr_spec *spec, char **buff) {
  char *temp = calloc(254, sizeof(char));
  int neg = 0;
  size_t size = s21_strlen(*buff);
  if ((*buff)[0] == '-') {
    temp[0] = '-';
    neg = 1;
    size--;
  }
  if (spec->accuracy > (int)size) {
    int ptr = neg;
    while (ptr < (int)(spec->accuracy - size + neg)) {
      temp[ptr] = '0';
      ptr++;
    }
    for (int i = neg; (*buff)[i]; i++, ptr++) {
      temp[ptr] = (*buff)[i];
    }
    s21_strcpy(*buff, temp);
  }
  free(temp);
}

void add_flags(pr_spec *spec, char **buff) {
  char *temp = calloc(256, sizeof(char));
  int sign = ((*buff)[0] == '-') ? 1 : 0;
  if ((spec->flags.plus && spec->spec_symb != 'u' && spec->spec_symb != 'o' &&
       spec->spec_symb != 'x' && spec->spec_symb != 'X' &&
       spec->spec_symb != 'o')) {
    temp[0] = sign ? '-' : '+';
    s21_strcpy(temp + 1, sign ? (*buff) + 1 : *buff);
    s21_strcpy(*buff, temp);
    sign = 1;
  } else if ((spec->flags.space && (*buff)[0] != '-' &&
              spec->spec_symb != 'u' && spec->spec_symb != 'o' &&
              spec->spec_symb != 'x' && spec->spec_symb != 'X' &&
              spec->spec_symb != 'o')) {
    temp[0] = ' ';
    s21_strcpy(temp + 1, *buff);
    s21_strcpy(*buff, temp);
    sign = 1;
  } else {
    s21_strcpy(temp, *buff);
  }
  size_t size = s21_strlen(*buff);
  if (spec->width > (int)size) {
    int diff = spec->width - size;
    if (spec->flags.minus) {
      s21_strcpy(temp, *buff);
      s21_memset(temp + s21_strlen(temp), ' ', diff);
    } else {
      int nulls = spec->flags.zero;
      if (sign && temp[0] != '+' && temp[0] != ' ') {
        temp[0] = '-';
      };
      s21_memset(nulls ? sign ? temp + 1 : temp : temp, nulls ? '0' : ' ',
                 diff);
      s21_strcpy(nulls ? sign ? temp + diff + 1 : temp + diff : temp + diff,
                 nulls ? sign ? (*buff) + 1 : *buff : *buff);
    }
  }
  if (s21_strlen(temp) != 0) {
    s21_strcpy((*buff), temp);
  }
  free(temp);
}
void add_sciprecision(char **buff, pr_spec *spec) {
  int digits = 0;
  size_t len = s21_strlen(*buff);
  int nullNotFound = 0;
  for (size_t i = 0; i < s21_strlen(*buff); i++) {
    if (((*buff)[i] == '0' && !nullNotFound) || (*buff)[i] == '.' ||
        (*buff)[i] == '-')
      continue;
    else
      nullNotFound = 1;
    if ((*buff)[i] >= '0' && (*buff)[i] <= '9' && nullNotFound) {
      digits++;
    }
    if (digits == spec->accuracy && i + 1 < len) {
      int next = (*buff)[i + 1] == '.' ? 2 : 1;
      if ((*buff)[i + next] - '0' >= 5) {
        if ((*buff)[i] >= '9') {
          (*buff)[i] = '0';
          (*buff)[i - 1] = (char)(*buff)[i - 1] + 1;
        } else {
          (*buff)[i] = (char)(*buff)[i] + 1;
        }
      }
      if ((*buff)[i + 1] == '.' && spec->flags.sharp)
        (*buff)[i + 2] = '\0';
      else
        (*buff)[i + 1] = '\0';
      break;
    }
  }
  size_t newsize = s21_strlen(*buff) - 1;
  while (newsize > 0 && (*buff)[newsize - 1] != '-') {
    int prev = (*buff)[newsize - 1] == '.' ? 2 : 1;
    if ((*buff)[newsize] == ':') {
      (*buff)[newsize - prev] += 1;
      (*buff)[newsize] = '0';
    }
    newsize -= prev;
  }
}
