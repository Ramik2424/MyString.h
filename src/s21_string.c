#include "s21_string.h"

void *s21_memchr(const void *str, int c, s21_size_t n) {
  char *out = S21_NULL;
  char *prog = (char *)str;
  for (s21_size_t i = 0; prog == S21_NULL || i < n; prog++, i++) {
    if (prog[0] == c) {
      out = prog;
      break;
    }
  }
  return out;
}

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  int out = 0;
  const char *one = (char *)str1;
  const char *two = (char *)str2;
  for (s21_size_t i = 0; i < n && one != S21_NULL && two != S21_NULL && !out;
       i++, one++, two++) {
    if (*one != *two) {
      out = one[0] - two[0];
    }
  }
  return out;
}

void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  char *res = (char *)dest;
  char *tmp = (char *)src;
  for (s21_size_t i = 0; i < n; i++) *(char *)(res + i) = *(char *)(tmp + i);
  return dest;
}

void *s21_memset(void *str, int c, s21_size_t n) {
  char *tmp = (char *)str;

  for (s21_size_t i = 0; i < n; i++) tmp[i] = c;

  str = tmp;
  return str != S21_NULL ? (char *)str : S21_NULL;
}

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  s21_size_t num = s21_strlen(dest);
  s21_size_t i = num;

  for (; i < num + n; i++) dest[i] = src[i - num];
  dest[i] = '\0';

  return dest;
}

char *s21_strchr(const char *str, int c) {
  char *newstr = S21_NULL;

  for (int i = 0; str[i] == c || str[i] != '\0'; i++)
    if ((int)str[i] == c) {
      newstr = (char *)(str + i);
      break;
    }

  return newstr;
}

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  const unsigned char *p1 = (const unsigned char *)str1;
  const unsigned char *p2 = (const unsigned char *)str2;
  int res = 0;
  while (n--) {
    if (*p1 != *p2) {
      res = *p1 - *p2;
    } else {
      ++p1, ++p2;
    }
  }
  return res;
}

char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  for (s21_size_t i = 0; i < n; i++) dest[i] = src[i];

  return dest;
}

s21_size_t s21_strcspn(const char *str1, const char *str2) {
  s21_size_t len = s21_strlen(str1);
  s21_size_t len2 = s21_strlen(str2);
  s21_size_t i = 0;
  for (; i < len; i++) {
    for (s21_size_t j = 0; j < len2; j++) {
      if (str1[i] == str2[j]) return i;
    }
  }
  return i;
}

s21_size_t s21_strlen(const char *str) {
  s21_size_t len = 0;

  while (*str) {
    len++;
    str++;
  }

  return len;
}

char *s21_strpbrk(const char *str1, const char *str2) {
  while (*str1 != '\0') {
    int i = 0;
    while (str2[i] != '\0') {
      if (*str1 == str2[i]) return (char *)str1;
      i++;
    }
    str1++;
  }

  return S21_NULL;
}

char *s21_strrchr(const char *str, int c) {
  char *newstr = S21_NULL;

  for (int i = s21_strlen(str); i >= 0; i--)
    if ((int)str[i] == c) {
      newstr = (char *)(str + i);
      break;
    }

  return newstr;
}

char *s21_strstr(const char *haystack, const char *needle) {
  while (*haystack != '\0') {
    if (s21_memcmp(haystack, needle, s21_strlen(needle)) == 0) {
      return (char *)(haystack);
    }
    haystack++;
  }
  return S21_NULL;
}

char *s21_strtok(char *str, const char *delim) {
  static char *result = S21_NULL;
  if (str) {
    result = str;
    while (*result && s21_strchr(delim, *result)) *result++ = '\0';
  }
  if (result != NULL) {
    if (*result != '\0') {
      str = result;
      while (*result && !s21_strchr(delim, *result)) ++result;
      while (*result && s21_strchr(delim, *result)) *result++ = '\0';
    } else {
      str = S21_NULL;
    }
  } else {
    str = S21_NULL;
  }
  return str;
}

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  char *res = S21_NULL;
  if (src && str && s21_strlen(src) >= start_index) {
    s21_size_t src_l = s21_strlen(src);
    s21_size_t str_l = s21_strlen(str);
    s21_size_t res_l = src_l + str_l + 1;
    res = (char *)malloc(sizeof(char) * res_l);
    if (res) {
      s21_strncpy(res, src, start_index);
      res[start_index] = '\0';
      s21_size_t i = start_index, j = 0;
      while (str[j] != '\0') {
        res[i] = str[j];
        i++, j++;
      }
      res[i] = '\0';

      while (src[start_index] != '\0') {
        res[i] = src[start_index];
        i++, start_index++;
      }
      res[i] = '\0';
    }
  }
  return res;
}

void *s21_to_upper(const char *str) {
  char *res = S21_NULL;
  if (str) {
    res = (char *)calloc((s21_strlen(str) + 1), sizeof(char));
    if (res) {
      s21_strncpy(res, str, s21_strlen(str) + 1);
      for (char *tmp = res; *tmp; tmp++)
        if (*tmp >= 'a' && *tmp <= 'z') *tmp -= 32;
    }
  }
  return res;
}
void *s21_to_lower(const char *str) {
  char *res = S21_NULL;
  if (str) {
    res = (char *)calloc((s21_strlen(str) + 1), sizeof(char));
    if (res) {
      s21_strncpy(res, str, s21_strlen(str) + 1);
      for (char *tmp = res; *tmp; tmp++)
        if (*tmp >= 'A' && *tmp <= 'Z') *tmp += 32;
    }
  }
  return res;
}

void *s21_trim(const char *src, const char *trim_chars) {
  char *res = S21_NULL;

  if (src && trim_chars) {
    char *start = (char *)src;
    char *end = (char *)(src + s21_strlen(src) - 1);
    while (*start && s21_strchr(trim_chars, *start)) start++;
    while (end > start && s21_strchr(trim_chars, *end)) end--;

    s21_size_t trim_l = end - start + 1;

    res = (char *)malloc(sizeof(char) * (trim_l + 1));
    if (res) {
      s21_strncpy(res, start, trim_l);
      res[trim_l] = '\0';
    }
  }
  return res;
}

void s21_strcpy(char *dest, const char *src) {
  while (*src != '\0') *dest++ = *src++;
}

char *s21_strcat(char *dest, const char *src) {
  s21_size_t len_dest = s21_strlen(dest);
  s21_size_t i = len_dest;
  s21_size_t len_src = s21_strlen(src);

  for (; i < len_dest + len_src; i++) dest[i] = src[i - len_dest];
  dest[i] = '\0';

  return dest;
}

int s21_strcmp(const char *str1, const char *str2) {
  int res = 0;
  s21_size_t i = 0;
  s21_size_t len_str1 = s21_strlen(str1);
  s21_size_t len_str2 = s21_strlen(str2);

  for (; i < len_str1 && i < len_str2; i++)
    if (str1[i] != str2[i]) {
      res = str1[i] - str2[i];
      break;
    }
  return res;
}
