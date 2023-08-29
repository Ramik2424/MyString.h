#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "s21_sprintf.h"
#include "s21_string.h"

START_TEST(s21_memchr_test) {
  char test1[] = "123456";
  char test2 = '4';
  char test3 = '7';
  char test4[] = "hello/\0";
  char test5[] = "h";
  char test6 = 'h';
  char test7 = ' ';
  char test8 = '/';
  char test9 = '\0';
  ck_assert_uint_eq((unsigned long)s21_memchr(test1, test2, 6),
                    (unsigned long)memchr(test1, test2, 6));
  ck_assert_uint_eq((unsigned long)s21_memchr(test1, test3, 6),
                    (unsigned long)memchr(test1, test3, 6));
  ck_assert_uint_eq((unsigned long)s21_memchr(test4, test6, 6),
                    (unsigned long)memchr(test4, test6, 6));
  ck_assert_uint_eq((unsigned long)s21_memchr(test5, test7, 1),
                    (unsigned long)memchr(test5, test7, 1));
  ck_assert_uint_eq((unsigned long)s21_memchr(test4, test8, 6),
                    (unsigned long)memchr(test4, test8, 6));
  ck_assert_uint_eq((unsigned long)s21_memchr(test4, test9, 6),
                    (unsigned long)memchr(test4, test9, 6));
}
END_TEST

START_TEST(s21_memcmp_test) {
  char test1[] = "Apple Pay Money Day";
  char test2[] = "Apple with worm";
  char test3[] = "\0";
  char test4[] = "gud\0 job";
  char test5[] = "gud\0 job";
  ck_assert_uint_eq(s21_memcmp(test1, test2, 16) < 0,
                    memcmp(test1, test2, 16) < 0);
  ck_assert_uint_eq(s21_memcmp(test1, test3, 2) > 0,
                    memcmp(test1, test3, 2) > 0);
  ck_assert_uint_eq(s21_memcmp(test2, test3, 2) > 0,
                    memcmp(test2, test3, 2) > 0);
  ck_assert_uint_eq(s21_memcmp(test4, test1, 9) > 0,
                    memcmp(test4, test1, 9) > 0);
  ck_assert_uint_eq(s21_memcmp(test4, test5, 7) == 0,
                    memcmp(test4, test5, 7) == 0);
}
END_TEST

START_TEST(s21_strlen_test) {
  char test_1[] = "12345";
  char test_2[] = "Hello";
  char test_3[] = "1\0";
  char test_4[] = "   ";
  char test_5[] = "123\0456";
  char test_6[] = "hhh\0";
  ck_assert_int_eq(s21_strlen(test_1), strlen(test_1));
  ck_assert_int_eq(s21_strlen(test_2), strlen(test_2));
  ck_assert_int_eq(s21_strlen(test_3), strlen(test_3));
  ck_assert_int_eq(s21_strlen(test_4), strlen(test_4));
  ck_assert_int_eq(s21_strlen(test_5), strlen(test_5));
  ck_assert_int_eq(s21_strlen(test_6), strlen(test_6));
}
END_TEST

START_TEST(s21_memcpy_test) {
  char test_1[10] = "12345";
  char test_2[] = "  ";
  char test_3[20] = "///  ";
  char test_4[] = "   ///";
  char test_5[30] = "";
  char test_6[] = "4444";
  char test_7[] = "123\0123";

  ck_assert_str_eq(s21_memcpy(test_1, test_2, 2), memcpy(test_1, test_2, 2));
  ck_assert_str_eq(s21_memcpy(test_3, test_4, 6), memcpy(test_3, test_4, 6));
  ck_assert_str_eq(s21_memcpy(test_5, test_6, 4), memcpy(test_5, test_6, 4));
  ck_assert_str_eq(s21_memcpy(test_5, test_7, 6), memcpy(test_5, test_7, 6));
}
END_TEST

START_TEST(s21_strncat_test) {
  char test_2[4] = "<<<";
  char test_4[2] = "5";
  char test_44[2] = "5";
  char test_5[] = "";

  ck_assert_str_eq(s21_strncat(test_2, test_4, 1), "<<<5");
  ck_assert_str_eq(s21_strncat(test_44, test_5, 0), strncat(test_4, test_5, 0));
}
END_TEST

START_TEST(s21_strstr_test) {
  char test_1[] = "<<<5>>>";
  char test_2[] = "5";
  char test_3[] = "QwertyQwertyQwerty";
  char test_4[] = "Qwerty";
  char test_5[] = "abcd";
  char test_6[] = "";
  char test_7[] = "aaaaa123aaa1234aaa";
  char test_8[] = "1234";

  ck_assert_ptr_eq(s21_strstr(test_1, test_2), strstr(test_1, test_2));
  ck_assert_ptr_eq(s21_strstr(test_3, test_4), strstr(test_3, test_4));
  ck_assert_ptr_eq(s21_strstr(test_5, test_6), strstr(test_5, test_6));
  ck_assert_ptr_eq(s21_strstr(test_4, test_5), strstr(test_4, test_5));
  ck_assert_ptr_eq(s21_strstr(test_7, test_8), strstr(test_7, test_8));
}
END_TEST

START_TEST(s21_memset_test) {
  unsigned char test1[10] = "1234357890";
  unsigned char test2[10] = "hello";
  ck_assert_uint_eq((unsigned long)s21_memset(test1, '1', 10),
                    (unsigned long)memset(test1, '1', 10));
  ck_assert_uint_eq((unsigned long)s21_memchr(test1, '3', 10),
                    (unsigned long)memchr(test1, '3', 10));
  ck_assert_uint_eq((unsigned long)s21_memchr(test1, '/', 8),
                    (unsigned long)memchr(test1, '/', 8));
  ck_assert_uint_eq((unsigned long)s21_memchr(test1, '9', 0),
                    (unsigned long)memchr(test1, '9', 0));
  ck_assert_uint_eq((unsigned long)s21_memchr(test1, '0', 4),
                    (unsigned long)memchr(test1, '0', 4));
  ck_assert_uint_eq((unsigned long)s21_memchr(test2, '1', 3),
                    (unsigned long)memchr(test2, '1', 3));
}
END_TEST

START_TEST(s21_strcspn_test) {
  char test1[] = "0123456789";
  char test2[] = "9876";
  char test3[] = "LOST: 4-8-15-16-23-42";
  char test4[] = "1234567890";
  char test5[] = "0/";
  char test6[] = "%%\\#";
  char test7[] = " ";
  char test8[] = "1234567890";
  ck_assert_uint_eq(s21_strcspn(test1, test2), strcspn(test1, test2));
  ck_assert_uint_eq(s21_strcspn(test3, test4), strcspn(test3, test4));
  ck_assert_uint_eq(s21_strcspn(test3, test5), strcspn(test3, test5));
  ck_assert_uint_eq(s21_strcspn(test3, test6), strcspn(test3, test6));
  ck_assert_uint_eq(s21_strcspn(test3, test7), strcspn(test3, test7));
  ck_assert_uint_eq(s21_strcspn(test4, test8), strcspn(test4, test8));
  ck_assert_uint_eq(s21_strcspn(test2, test7), strcspn(test2, test7));
}
END_TEST

START_TEST(s21_strrchr_test) {
  char test1[] = "0163456769";
  char test2[] = ";;;;;;H//#HH";
  char test3[] = "     /";
  ck_assert_uint_eq((unsigned long)s21_strrchr(test1, '6'),
                    (unsigned long)strrchr(test1, '6'));
  ck_assert_uint_eq((unsigned long)s21_strrchr(test1, '4'),
                    (unsigned long)strrchr(test1, '4'));
  ck_assert_uint_eq((unsigned long)s21_strrchr(test1, '6'),
                    (unsigned long)strrchr(test1, '6'));
  ck_assert_uint_eq((unsigned long)s21_strrchr(test2, 'H'),
                    (unsigned long)strrchr(test2, 'H'));
  ck_assert_uint_eq((unsigned long)s21_strrchr(test2, ';'),
                    (unsigned long)strrchr(test2, ';'));
  ck_assert_uint_eq((unsigned long)s21_strrchr(test3, ' '),
                    (unsigned long)strrchr(test3, ' '));
  ck_assert_str_eq(s21_strrchr(test2, '\0'), strrchr(test2, '\0'));
}
END_TEST

START_TEST(s21_strerror_test) {
  char *str1 = s21_strerror(20);
  char *str2 = strerror(20);
  ck_assert_str_eq(str1, str2);

  char *str3 = s21_strerror(12);
  char *str4 = strerror(12);
  ck_assert_str_eq(str3, str4);

  char *str5 = s21_strerror(1337);
  char *str6 = strerror(1337);
  ck_assert_str_eq(str5, str6);

  char *str7 = s21_strerror(1);
  char *str8 = strerror(1);
  ck_assert_str_eq(str7, str8);

  char *str9 = s21_strerror(25);
  char *str10 = strerror(25);
  ck_assert_str_eq(str9, str10);
}
END_TEST

START_TEST(s21_strncmp_test) {
  char str1[] = "hellaa 1";
  char str2[] = "helloa 3";
  ck_assert_int_eq(s21_strncmp(str1, str2, 5) < 0, strncmp(str1, str2, 5) < 0);
  ck_assert_int_eq(s21_strncmp(str1, str2, 3) == 0,
                   strncmp(str1, str2, 3) == 0);
}
END_TEST

START_TEST(s21_insert_test) {
  char *my_str1 = "School-21 test";
  char *my_str2 = "insert ";
  char *my_str3 = "amogus";
  char *my_str4 = "is";
  char *my_str5 = "shrek";
  char *res1 = s21_insert(my_str1, " ", 3);
  char *res2 = s21_insert(my_str5, my_str3, 5);
  char *res3 = s21_insert(my_str3, my_str5, 0);
  char *res4 = s21_insert(my_str5, my_str4, 5);
  char *res5 = s21_insert(my_str2, my_str1, 4);

  ck_assert_str_eq(res1, "Sch ool-21 test");
  ck_assert_str_eq(res2, "shrekamogus");
  ck_assert_str_eq(res3, "shrekamogus");
  ck_assert_str_eq(res4, "shrekis");
  ck_assert_str_eq(res5, "inseSchool-21 testrt ");

  free(res1);
  free(res2);
  free(res3);
  free(res4);
  free(res5);
}
END_TEST

START_TEST(s21_to_upper_test) {
  char destination[] = "Here w0 are123";
  char *test01 = s21_to_upper(destination);
  ck_assert_str_eq(test01, "HERE W0 ARE123");
  free(test01);

  char destination2[] = "Here w0 are\n\0";
  char *test02 = s21_to_upper(destination2);
  ck_assert_str_eq(test02, "HERE W0 ARE\n");
  free(test02);

  char destination3[] = "a\n\0";
  char *test03 = s21_to_upper(destination3);
  ck_assert_str_eq(test03, "A\n");
  free(test03);

  char destination4[] = " \n\0";
  char *test04 = s21_to_upper(destination4);
  ck_assert_str_eq(test04, " \n");
  free(test04);

  char destination5[] = " \0";
  char *test05 = s21_to_upper(destination5);
  ck_assert_str_eq(test05, " ");
  free(test05);

  char destination6[] = "\n\0";
  char *test06 = s21_to_upper(destination6);
  ck_assert_str_eq(test06, "\n");
  free(test06);

  char destination7[] = "\0";
  char *test07 = s21_to_upper(destination7);
  ck_assert_str_eq(test07, "");
  free(test07);
}
END_TEST

START_TEST(s21_to_lower_test) {
  char destination[] = "HERE W0 ARE123\0";
  char *test01 = s21_to_lower(destination);
  ck_assert_str_eq(test01, "here w0 are123");
  free(test01);

  char destination2[] = "HERE W0 ARE\n\0";
  char *test02 = s21_to_lower(destination2);
  ck_assert_str_eq(test02, "here w0 are\n");
  free(test02);

  char destination3[] = "A\n\0";
  char *test03 = s21_to_lower(destination3);
  ck_assert_str_eq(test03, "a\n");
  free(test03);

  char destination4[] = " \n\0";
  char *test04 = s21_to_lower(destination4);
  ck_assert_str_eq(test04, " \n");
  free(test04);

  char destination5[] = " \0";
  char *test05 = s21_to_lower(destination5);
  ck_assert_str_eq(test05, " ");
  free(test05);

  char destination6[] = "\n\0";
  char *test06 = s21_to_lower(destination6);
  ck_assert_str_eq(test06, "\n");
  free(test06);

  char destination7[] = "\0";
  char *test07 = s21_to_lower(destination7);
  ck_assert_str_eq(test07, "");
  free(test07);
}
END_TEST
START_TEST(s21_test_trim_1) {
  char src[4] = "abc";
  char trim_chars[2] = "a";
  char res[3] = "bc";

  char *tmp = s21_trim(src, trim_chars);

  ck_assert_str_eq(tmp, res);

  free(tmp);
}
END_TEST

START_TEST(s21_test_trim_2) {
  char *src = "abcd";
  char *trim_chars = "ac";
  char *res = "bcd";

  char *tmp = s21_trim(
      src, trim_chars);  // Почему здесь приведение к char исправило ситуацию

  ck_assert_str_eq(tmp, res);

  free(tmp);
}
END_TEST

START_TEST(s21_test_trim_3) {
  char *src = "abcd";
  char *trim_chars = "dc";
  char *res = "ab";

  char *tmp = s21_trim(src, trim_chars);

  ck_assert_str_eq(tmp, res);

  free(tmp);
}
END_TEST

START_TEST(s21_test_trim_4) {
  char *src = "Hello World";
  char *trim_chars = "Hedl";
  char *res = "o Wor";

  char *tmp = s21_trim(src, trim_chars);

  ck_assert_str_eq(tmp, res);

  free(tmp);
}
END_TEST

START_TEST(s21_test_trim_5) {
  char *src = "";
  char *trim_chars = "dc";
  char *res = "";

  char *tmp = s21_trim(src, trim_chars);

  ck_assert_str_eq(tmp, res);

  free(tmp);
}
END_TEST

START_TEST(s21_test_strcmp) {
  char str1[11] = "hellowwwwaa";
  char str2[11] = "hellowwwwai";
  ck_assert_int_eq(strcmp(str1, str2), s21_strcmp(str1, str2));
}
END_TEST

START_TEST(s21_strchr_test) {
  char str1[] = "Abcdefg";
  int symbol1 = 'd';
  char *ach1 = s21_strchr(str1, symbol1);
  ck_assert_str_eq(ach1, "defg");

  char str2[] = "Abcdefg";
  int symbol2 = 'd';
  char *ach2 = strchr(str2, symbol2);
  ck_assert_str_eq(ach1, ach2);
  ck_assert_str_eq(str1, str2);

  char str3[] = "Abcdefg";
  int symbol3 = '\0';
  char *ach3 = s21_strchr(str3, symbol3);

  char str4[] = "Abcdefg";
  int symbol4 = '\0';
  char *ach4 = strchr(str4, symbol4);
  ck_assert_str_eq(ach3, ach4);
  ck_assert_str_eq(str3, str4);
}
END_TEST

START_TEST(s21_strncpy_test) {
  char str1[] = "test of string";
  char dest1[20] = "";

  char str2[] = "test\0";
  char dest2[15] = "";

  char str3[] = "test ";
  char dest3[] = "crushcrush";

  ck_assert_str_eq(strncpy(dest1, str1, 15), s21_strncpy(dest1, str1, 15));
  ck_assert_str_eq(strncpy(dest2, str2, 6), s21_strncpy(dest2, str2, 6));
  ck_assert_str_eq(strncpy(dest3, str3, 10), s21_strncpy(dest3, str3, 10));
}
END_TEST

START_TEST(s21_strpbrk_test) {
  char str_for_strpbrk[] = "Megalomania";
  char str_oneof[] = "yal";
  ck_assert_str_eq(s21_strpbrk(str_for_strpbrk, str_oneof), "alomania");
  ck_assert_str_eq(s21_strpbrk(str_for_strpbrk, str_oneof),
                   strpbrk(str_for_strpbrk, str_oneof));

  char *str = "Hello, world";
  char *empty = "";
  ck_assert(s21_strpbrk(str, empty) == NULL);
  ck_assert_uint_eq((unsigned long)s21_strpbrk(str, empty),
                    (unsigned long)strpbrk(str, empty));
}
END_TEST

START_TEST(s21_strtok_test_1) {
  char str_strtok1[] = "one/two/three(four)five";
  char delim1[] = "/()";

  char str_strtok2[] = "one/two/three(four)five";
  char delim2[] = "/()";
  char *my_strtok = s21_strtok(str_strtok1, delim1);
  char *origin_strtok = strtok(str_strtok2, delim2);
  while (my_strtok != NULL) {
    ck_assert_str_eq(my_strtok, origin_strtok);
    my_strtok = s21_strtok(NULL, delim1);
    origin_strtok = strtok(NULL, delim2);
  }
}
END_TEST

START_TEST(s21_strtok_test_2) {
  char str_strtok1[] = "one/two/three(four)five";
  char delim1[] = "():/ \0";

  char str_strtok2[] = "one/two/three(four)five";
  char delim2[] = "():/ \0";
  char *my_strtok = s21_strtok(str_strtok1, delim1);
  char *origin_strtok = strtok(str_strtok2, delim2);
  while (my_strtok != NULL) {
    ck_assert_str_eq(my_strtok, origin_strtok);
    my_strtok = s21_strtok(NULL, delim1);
    origin_strtok = strtok(NULL, delim2);
  }
}
END_TEST

START_TEST(s21_sprintf_prc_test) {
  char str[80];
  char str_orig[80];

  int res_1 = s21_sprintf(str, "%%");
  int res_1_orig = sprintf(str_orig, "%%");
  ck_assert_int_eq(res_1, res_1_orig);
  ck_assert_str_eq(str, str_orig);

  int res_2 = s21_sprintf(str, "%10%");

  ck_assert_int_eq(res_2, 10);
  ck_assert_str_eq(str, "         %");

  int a_prc = 14;
  int res_3 = s21_sprintf(str, "hhhh%0*%", a_prc);

  ck_assert_int_eq(res_3, 18);
  ck_assert_str_eq(str, "hhhh0000000000000%");

  int width_prc = 30;
  int res_4 = s21_sprintf(str, "%-*%12345", width_prc);

  ck_assert_int_eq(res_4, 35);
  ck_assert_str_eq(str, "%                             12345");

  int res_5 = s21_sprintf(str, "abc%%defg");
  int res_5_orig = sprintf(str_orig, "abc%%defg");

  ck_assert_int_eq(res_5, res_5_orig);
  ck_assert_str_eq(str, str_orig);
}
END_TEST

START_TEST(s21_sprintf_test) {
  char str[80];
  char str_origin[80];
  const char *format_str1 = "Hello";
  char c = 'X';
  int result1 = s21_sprintf(str, format_str1, c);
  int result_origin1 = sprintf(str_origin, format_str1, c);
  ck_assert_int_eq(result1, result_origin1);
  ck_assert_str_eq(str, str_origin);
}
END_TEST

START_TEST(s21_sprintf_c_test) {
  char str[80];
  char str1[80];
  char x = 'c';
  int res = s21_sprintf(str, "%-10c", x);
  int res1 = sprintf(str1, "%-10c", x);
  ck_assert_uint_eq((unsigned long)*str, (unsigned long)*str1);
  ck_assert_int_eq(res, res1);

  res = s21_sprintf(str, "%10c", x);
  res1 = sprintf(str1, "%10c", x);
  ck_assert_uint_eq((unsigned long)*str, (unsigned long)*str1);
  ck_assert_int_eq(res, res1);
}
END_TEST

START_TEST(s21_sprintf_s_test) {
  char str[80];
  char str1[80];
  char *x = "blablabla";
  int res = s21_sprintf(str, "%-11.10s", x);
  int res1 = sprintf(str1, "%-11.10s", x);
  ck_assert_uint_eq((unsigned long)*str, (unsigned long)*str1);
  ck_assert_int_eq(res, res1);

  res = s21_sprintf(str, "%11.8s", x);
  res1 = sprintf(str1, "%11.8s", x);
  ck_assert_uint_eq((unsigned long)*str, (unsigned long)*str1);
  ck_assert_int_eq(res, res1);
}
END_TEST

START_TEST(s21_sprintf_u_test) {
  char str[80];
  char str_orig[80];
  unsigned int a = 2345;

  int res_1 = s21_sprintf(str, "%10.5u", a);
  int res_1_orig = sprintf(str_orig, "%10.5u", a);

  ck_assert_int_eq(res_1, res_1_orig);
  ck_assert_str_eq(str, str_orig);

  int res_2 = s21_sprintf(str, "%10.5u", a);
  int res_2_orig = sprintf(str_orig, "%10.5u", a);

  ck_assert_int_eq(res_2, res_2_orig);
  ck_assert_str_eq(str, str_orig);

  int res_3 = s21_sprintf(str, "%3.5u", a);
  int res_3_orig = sprintf(str_orig, "%3.5u", a);

  ck_assert_int_eq(res_3, res_3_orig);
  ck_assert_str_eq(str, str_orig);

  int res_4 = s21_sprintf(str, "%0u", a);
  int res_4_orig = sprintf(str_orig, "%0u", a);

  ck_assert_int_eq(res_4, res_4_orig);
  ck_assert_str_eq(str, str_orig);

  int res_5 = s21_sprintf(str, "%-u", a);
  int res_5_orig = sprintf(str_orig, "%-u", a);

  ck_assert_int_eq(res_5, res_5_orig);
  ck_assert_str_eq(str, str_orig);

  int res_6 = s21_sprintf(str, "%u", a);
  int res_6_orig = sprintf(str_orig, "%u", a);

  ck_assert_int_eq(res_6, res_6_orig);
  ck_assert_str_eq(str, str_orig);

  int res_7 = s21_sprintf(str, "%5u", a);
  int res_7_orig = sprintf(str_orig, "%5u", a);

  ck_assert_int_eq(res_7, res_7_orig);
  ck_assert_str_eq(str, str_orig);

  int res_8 = s21_sprintf(str, "%05u", a);
  int res_8_orig = sprintf(str_orig, "%05u", a);

  ck_assert_int_eq(res_8, res_8_orig);
  ck_assert_str_eq(str, str_orig);

  int res_9 = s21_sprintf(str, "%-5u", a);
  int res_9_orig = sprintf(str_orig, "%-5u", a);

  ck_assert_int_eq(res_9, res_9_orig);
  ck_assert_str_eq(str, str_orig);

  int res_10 = s21_sprintf(str, "%.5u", a);
  int res_10_orig = sprintf(str_orig, "%.5u", a);

  ck_assert_int_eq(res_10, res_10_orig);
  ck_assert_str_eq(str, str_orig);

  int res_11 = s21_sprintf(str, "%.5u", a);
  int res_11_orig = sprintf(str_orig, "%.5u", a);

  ck_assert_int_eq(res_11, res_11_orig);
  ck_assert_str_eq(str, str_orig);

  int res_12 = s21_sprintf(str, "%-.5u", a);
  int res_12_orig = sprintf(str_orig, "%-.5u", a);

  ck_assert_int_eq(res_12, res_12_orig);
  ck_assert_str_eq(str, str_orig);

  int res_13 = s21_sprintf(str, "%-10.5u", a);
  int res_13_orig = sprintf(str_orig, "%-10.5u", a);

  ck_assert_int_eq(res_13, res_13_orig);
  ck_assert_str_eq(str, str_orig);

  int res_14 = s21_sprintf(str, "%3.5u", a);
  int res_14_orig = sprintf(str_orig, "%3.5u", a);

  ck_assert_int_eq(res_14, res_14_orig);
  ck_assert_str_eq(str, str_orig);

  int res_15 = s21_sprintf(str, "%-3.5u", a);
  int res_15_orig = sprintf(str_orig, "%-3.5u", a);

  ck_assert_int_eq(res_15, res_15_orig);
  ck_assert_str_eq(str, str_orig);

  int res_16 = s21_sprintf(str, "%6.2u", a);
  int res_16_orig = sprintf(str_orig, "%6.2u", a);

  ck_assert_int_eq(res_16, res_16_orig);
  ck_assert_str_eq(str, str_orig);

  int res_17 = s21_sprintf(str, "%3.2u", a);
  int res_17_orig = sprintf(str_orig, "%3.2u", a);

  ck_assert_int_eq(res_17, res_17_orig);
  ck_assert_str_eq(str, str_orig);

  int res_18 = s21_sprintf(str, "%01u", a);
  int res_18_orig = sprintf(str_orig, "%01u", a);

  ck_assert_int_eq(res_18, res_18_orig);
  ck_assert_str_eq(str, str_orig);

  int res_19 = s21_sprintf(str, "%hu", (unsigned short)a);
  int res_19_orig = sprintf(str_orig, "%hu", (unsigned short)a);

  ck_assert_int_eq(res_19, res_19_orig);
  ck_assert_str_eq(str, str_orig);

  int res_20 = s21_sprintf(str, "%lu", (unsigned long)a);
  int res_20_orig = sprintf(str_orig, "%lu", (unsigned long)a);

  ck_assert_int_eq(res_20, res_20_orig);
  ck_assert_str_eq(str, str_orig);
}
END_TEST

START_TEST(s21_sprintf_d_test) {
  char str[80];
  char str_orig[80];
  int a = 2345;

  int res_1 = s21_sprintf(str, "%10.5d", a);
  int res_1_orig = sprintf(str_orig, "%10.5d", a);

  ck_assert_int_eq(res_1, res_1_orig);
  ck_assert_str_eq(str, str_orig);

  int res_2 = s21_sprintf(str, "% 10.5d", a);
  int res_2_orig = sprintf(str_orig, "% 10.5d", a);

  ck_assert_int_eq(res_2, res_2_orig);
  ck_assert_str_eq(str, str_orig);

  int res_3 = s21_sprintf(str, "%3.5d", a);
  int res_3_orig = sprintf(str_orig, "%3.5d", a);

  ck_assert_int_eq(res_3, res_3_orig);
  ck_assert_str_eq(str, str_orig);

  int res_4 = s21_sprintf(str, "%d", a);
  int res_4_orig = sprintf(str_orig, "%d", a);

  ck_assert_int_eq(res_4, res_4_orig);
  ck_assert_str_eq(str, str_orig);

  int res_5 = s21_sprintf(str, "%0d", a);
  int res_5_orig = sprintf(str_orig, "%0d", a);

  ck_assert_int_eq(res_5, res_5_orig);
  ck_assert_str_eq(str, str_orig);

  int res_6 = s21_sprintf(str, "%-d", a);
  int res_6_orig = sprintf(str_orig, "%-d", a);

  ck_assert_int_eq(res_6, res_6_orig);
  ck_assert_str_eq(str, str_orig);

  int res_7 = s21_sprintf(str, "%+d", a);
  int res_7_orig = sprintf(str_orig, "%+d", a);

  ck_assert_int_eq(res_7, res_7_orig);
  ck_assert_str_eq(str, str_orig);

  int res_8 = s21_sprintf(str, "% d", a);
  int res_8_orig = sprintf(str_orig, "% d", a);

  ck_assert_int_eq(res_8, res_8_orig);
  ck_assert_str_eq(str, str_orig);

  int res_9 = s21_sprintf(str, "%5d", a);
  int res_9_orig = sprintf(str_orig, "%5d", a);

  ck_assert_int_eq(res_9, res_9_orig);
  ck_assert_str_eq(str, str_orig);

  int res_10 = s21_sprintf(str, "%05d", a);
  int res_10_orig = sprintf(str_orig, "%05d", a);

  ck_assert_int_eq(res_10, res_10_orig);
  ck_assert_str_eq(str, str_orig);

  int res_11 = s21_sprintf(str, "%-5d", a);
  int res_11_orig = sprintf(str_orig, "%-5d", a);

  ck_assert_int_eq(res_11, res_11_orig);
  ck_assert_str_eq(str, str_orig);

  int res_12 = s21_sprintf(str, "%+5d", a);
  int res_12_orig = sprintf(str_orig, "%+5d", a);

  ck_assert_int_eq(res_12, res_12_orig);
  ck_assert_str_eq(str, str_orig);

  int res_13 = s21_sprintf(str, "% 5d", a);
  int res_13_orig = sprintf(str_orig, "% 5d", a);

  ck_assert_int_eq(res_13, res_13_orig);
  ck_assert_str_eq(str, str_orig);

  int res_14 = s21_sprintf(str, "%.5d", a);
  int res_14_orig = sprintf(str_orig, "%.5d", a);

  ck_assert_int_eq(res_14, res_14_orig);
  ck_assert_str_eq(str, str_orig);

  int res_15 = s21_sprintf(str, "%05d", a);
  int res_15_orig = sprintf(str_orig, "%.5d", a);

  ck_assert_int_eq(res_15, res_15_orig);
  ck_assert_str_eq(str, str_orig);

  int res_16 = s21_sprintf(str, "% .5d", a);
  int res_16_orig = sprintf(str_orig, "% .5d", a);

  ck_assert_int_eq(res_16, res_16_orig);
  ck_assert_str_eq(str, str_orig);

  int res_17 = s21_sprintf(str, "%+.5d", a);
  int res_17_orig = sprintf(str_orig, "%+.5d", a);

  ck_assert_int_eq(res_17, res_17_orig);
  ck_assert_str_eq(str, str_orig);

  int res_18 = s21_sprintf(str, "%-.5d", a);
  int res_18_orig = sprintf(str_orig, "%-.5d", a);

  ck_assert_int_eq(res_18, res_18_orig);
  ck_assert_str_eq(str, str_orig);

  int res_19 = s21_sprintf(str, "%10.5d", a);
  int res_19_orig = sprintf(str_orig, "%10.5d", a);

  ck_assert_int_eq(res_19, res_19_orig);
  ck_assert_str_eq(str, str_orig);

  int res_20 = s21_sprintf(str, "%+10.5d", a);
  int res_20_orig = sprintf(str_orig, "%+10.5d", a);

  ck_assert_int_eq(res_20, res_20_orig);
  ck_assert_str_eq(str, str_orig);

  int res_21 = s21_sprintf(str, "%-10.5d", a);
  int res_21_orig = sprintf(str_orig, "%-10.5d", a);

  ck_assert_int_eq(res_21, res_21_orig);
  ck_assert_str_eq(str, str_orig);

  int res_22 = s21_sprintf(str, "%3.5d", a);
  int res_22_orig = sprintf(str_orig, "%3.5d", a);

  ck_assert_int_eq(res_22, res_22_orig);
  ck_assert_str_eq(str, str_orig);

  int res_23 = s21_sprintf(str, "% 3.5d", a);
  int res_23_orig = sprintf(str_orig, "% 3.5d", a);

  ck_assert_int_eq(res_23, res_23_orig);
  ck_assert_str_eq(str, str_orig);

  int res_24 = s21_sprintf(str, "%+3.5d", a);
  int res_24_orig = sprintf(str_orig, "%+3.5d", a);

  ck_assert_int_eq(res_24, res_24_orig);
  ck_assert_str_eq(str, str_orig);

  int res_25 = s21_sprintf(str, "%-3.5d", a);
  int res_25_orig = sprintf(str_orig, "%-3.5d", a);

  ck_assert_int_eq(res_25, res_25_orig);
  ck_assert_str_eq(str, str_orig);

  int res_26 = s21_sprintf(str, "%hd", (unsigned short)a);
  int res_26_orig = sprintf(str_orig, "%hd", (unsigned short)a);

  ck_assert_int_eq(res_26, res_26_orig);
  ck_assert_str_eq(str, str_orig);

  int res_27 = s21_sprintf(str, "%ld", (unsigned long)a);
  int res_27_orig = sprintf(str_orig, "%ld", (unsigned long)a);

  ck_assert_int_eq(res_27, res_27_orig);
  ck_assert_str_eq(str, str_orig);
}
END_TEST

START_TEST(s21_sprintf_d_test_2) {
  char str[80];
  char str_orig[80];
  int a = -23454546;

  int res_2 = s21_sprintf(str, "% 10.5d", a);
  int res_2_orig = sprintf(str_orig, "% 10.5d", a);

  ck_assert_int_eq(res_2, res_2_orig);
  ck_assert_str_eq(str, str_orig);

  int res_3 = s21_sprintf(str, "%3.5d", a);
  int res_3_orig = sprintf(str_orig, "%3.5d", a);

  ck_assert_int_eq(res_3, res_3_orig);
  ck_assert_str_eq(str, str_orig);

  int res_4 = s21_sprintf(str, "%d", a);
  int res_4_orig = sprintf(str_orig, "%d", a);

  ck_assert_int_eq(res_4, res_4_orig);
  ck_assert_str_eq(str, str_orig);

  int res_5 = s21_sprintf(str, "%0d", a);
  int res_5_orig = sprintf(str_orig, "%0d", a);

  ck_assert_int_eq(res_5, res_5_orig);
  ck_assert_str_eq(str, str_orig);

  int res_6 = s21_sprintf(str, "%-d", a);
  int res_6_orig = sprintf(str_orig, "%-d", a);

  ck_assert_int_eq(res_6, res_6_orig);
  ck_assert_str_eq(str, str_orig);

  int res_7 = s21_sprintf(str, "%+d", a);
  int res_7_orig = sprintf(str_orig, "%+d", a);

  ck_assert_int_eq(res_7, res_7_orig);
  ck_assert_str_eq(str, str_orig);

  int res_8 = s21_sprintf(str, "% d", a);
  int res_8_orig = sprintf(str_orig, "% d", a);

  ck_assert_int_eq(res_8, res_8_orig);
  ck_assert_str_eq(str, str_orig);

  int res_9 = s21_sprintf(str, "%5d", a);
  int res_9_orig = sprintf(str_orig, "%5d", a);

  ck_assert_int_eq(res_9, res_9_orig);
  ck_assert_str_eq(str, str_orig);

  int res_11 = s21_sprintf(str, "%-5d", a);
  int res_11_orig = sprintf(str_orig, "%-5d", a);

  ck_assert_int_eq(res_11, res_11_orig);
  ck_assert_str_eq(str, str_orig);

  int res_12 = s21_sprintf(str, "%+5d", a);
  int res_12_orig = sprintf(str_orig, "%+5d", a);

  ck_assert_int_eq(res_12, res_12_orig);
  ck_assert_str_eq(str, str_orig);

  int res_13 = s21_sprintf(str, "% 5d", a);
  int res_13_orig = sprintf(str_orig, "% 5d", a);

  ck_assert_int_eq(res_13, res_13_orig);
  ck_assert_str_eq(str, str_orig);

  int res_14 = s21_sprintf(str, "%.5d", a);
  int res_14_orig = sprintf(str_orig, "%.5d", a);

  ck_assert_int_eq(res_14, res_14_orig);
  ck_assert_str_eq(str, str_orig);

  int res_15 = s21_sprintf(str, "%.5d", a);
  int res_15_orig = sprintf(str_orig, "%.5d", a);

  ck_assert_int_eq(res_15, res_15_orig);
  ck_assert_str_eq(str, str_orig);

  int res_16 = s21_sprintf(str, "% .5d", a);
  int res_16_orig = sprintf(str_orig, "% .5d", a);

  ck_assert_int_eq(res_16, res_16_orig);
  ck_assert_str_eq(str, str_orig);

  int res_17 = s21_sprintf(str, "%+.5d", a);
  int res_17_orig = sprintf(str_orig, "%+.5d", a);

  ck_assert_int_eq(res_17, res_17_orig);
  ck_assert_str_eq(str, str_orig);

  int res_18 = s21_sprintf(str, "%-.5d", a);
  int res_18_orig = sprintf(str_orig, "%-.5d", a);

  ck_assert_int_eq(res_18, res_18_orig);
  ck_assert_str_eq(str, str_orig);

  int res_19 = s21_sprintf(str, "%10.5d", a);
  int res_19_orig = sprintf(str_orig, "%10.5d", a);

  ck_assert_int_eq(res_19, res_19_orig);
  ck_assert_str_eq(str, str_orig);

  int res_20 = s21_sprintf(str, "%+10.5d", a);
  int res_20_orig = sprintf(str_orig, "%+10.5d", a);

  ck_assert_int_eq(res_20, res_20_orig);
  ck_assert_str_eq(str, str_orig);

  int res_21 = s21_sprintf(str, "%-10.5d", a);
  int res_21_orig = sprintf(str_orig, "%-10.5d", a);

  ck_assert_int_eq(res_21, res_21_orig);
  ck_assert_str_eq(str, str_orig);

  int res_22 = s21_sprintf(str, "%3.5d", a);
  int res_22_orig = sprintf(str_orig, "%3.5d", a);

  ck_assert_int_eq(res_22, res_22_orig);
  ck_assert_str_eq(str, str_orig);

  int res_23 = s21_sprintf(str, "% 3.5d", a);
  int res_23_orig = sprintf(str_orig, "% 3.5d", a);

  ck_assert_int_eq(res_23, res_23_orig);
  ck_assert_str_eq(str, str_orig);

  int res_24 = s21_sprintf(str, "%+3.5d", a);
  int res_24_orig = sprintf(str_orig, "%+3.5d", a);

  ck_assert_int_eq(res_24, res_24_orig);
  ck_assert_str_eq(str, str_orig);

  int res_25 = s21_sprintf(str, "%-3.5d", a);
  int res_25_orig = sprintf(str_orig, "%-3.5d", a);

  ck_assert_int_eq(res_25, res_25_orig);
  ck_assert_str_eq(str, str_orig);
}
END_TEST

START_TEST(s21_sprintf_d_test_3) {
  char str[80];
  char str_orig[80];
  int a = 234;

  int res_1 = s21_sprintf(str, "%10.5d", a);
  int res_1_orig = sprintf(str_orig, "%10.5d", a);

  ck_assert_int_eq(res_1, res_1_orig);
  ck_assert_str_eq(str, str_orig);

  int res_2 = s21_sprintf(str, "% 10.5d", a);
  int res_2_orig = sprintf(str_orig, "% 10.5d", a);

  ck_assert_int_eq(res_2, res_2_orig);
  ck_assert_str_eq(str, str_orig);

  int res_3 = s21_sprintf(str, "%3.5d", a);
  int res_3_orig = sprintf(str_orig, "%3.5d", a);

  ck_assert_int_eq(res_3, res_3_orig);
  ck_assert_str_eq(str, str_orig);

  int res_4 = s21_sprintf(str, "%d", a);
  int res_4_orig = sprintf(str_orig, "%d", a);

  ck_assert_int_eq(res_4, res_4_orig);
  ck_assert_str_eq(str, str_orig);

  int res_5 = s21_sprintf(str, "%0d", a);
  int res_5_orig = sprintf(str_orig, "%0d", a);

  ck_assert_int_eq(res_5, res_5_orig);
  ck_assert_str_eq(str, str_orig);

  int res_6 = s21_sprintf(str, "%-d", a);
  int res_6_orig = sprintf(str_orig, "%-d", a);

  ck_assert_int_eq(res_6, res_6_orig);
  ck_assert_str_eq(str, str_orig);

  int res_7 = s21_sprintf(str, "%+d", a);
  int res_7_orig = sprintf(str_orig, "%+d", a);

  ck_assert_int_eq(res_7, res_7_orig);
  ck_assert_str_eq(str, str_orig);

  int res_8 = s21_sprintf(str, "% d", a);
  int res_8_orig = sprintf(str_orig, "% d", a);

  ck_assert_int_eq(res_8, res_8_orig);
  ck_assert_str_eq(str, str_orig);

  int res_9 = s21_sprintf(str, "%5d", a);
  int res_9_orig = sprintf(str_orig, "%5d", a);

  ck_assert_int_eq(res_9, res_9_orig);
  ck_assert_str_eq(str, str_orig);

  int res_10 = s21_sprintf(str, "%05d", a);
  int res_10_orig = sprintf(str_orig, "%05d", a);

  ck_assert_int_eq(res_10, res_10_orig);
  ck_assert_str_eq(str, str_orig);

  int res_11 = s21_sprintf(str, "%-5d", a);
  int res_11_orig = sprintf(str_orig, "%-5d", a);

  ck_assert_int_eq(res_11, res_11_orig);
  ck_assert_str_eq(str, str_orig);

  int res_12 = s21_sprintf(str, "%+5d", a);
  int res_12_orig = sprintf(str_orig, "%+5d", a);

  ck_assert_int_eq(res_12, res_12_orig);
  ck_assert_str_eq(str, str_orig);

  int res_13 = s21_sprintf(str, "% 5d", a);
  int res_13_orig = sprintf(str_orig, "% 5d", a);

  ck_assert_int_eq(res_13, res_13_orig);
  ck_assert_str_eq(str, str_orig);

  int res_14 = s21_sprintf(str, "%.5d", a);
  int res_14_orig = sprintf(str_orig, "%.5d", a);

  ck_assert_int_eq(res_14, res_14_orig);
  ck_assert_str_eq(str, str_orig);

  int res_15 = s21_sprintf(str, "%.5d", a);
  int res_15_orig = sprintf(str_orig, "%.5d", a);

  ck_assert_int_eq(res_15, res_15_orig);
  ck_assert_str_eq(str, str_orig);

  int res_16 = s21_sprintf(str, "% .5d", a);
  int res_16_orig = sprintf(str_orig, "% .5d", a);

  ck_assert_int_eq(res_16, res_16_orig);
  ck_assert_str_eq(str, str_orig);

  int res_17 = s21_sprintf(str, "%+.5d", a);
  int res_17_orig = sprintf(str_orig, "%+.5d", a);

  ck_assert_int_eq(res_17, res_17_orig);
  ck_assert_str_eq(str, str_orig);

  int res_18 = s21_sprintf(str, "%-.5d", a);
  int res_18_orig = sprintf(str_orig, "%-.5d", a);

  ck_assert_int_eq(res_18, res_18_orig);
  ck_assert_str_eq(str, str_orig);

  int res_19 = s21_sprintf(str, "%10.5d", a);
  int res_19_orig = sprintf(str_orig, "%10.5d", a);

  ck_assert_int_eq(res_19, res_19_orig);
  ck_assert_str_eq(str, str_orig);

  int res_20 = s21_sprintf(str, "%+10.5d", a);
  int res_20_orig = sprintf(str_orig, "%+10.5d", a);

  ck_assert_int_eq(res_20, res_20_orig);
  ck_assert_str_eq(str, str_orig);

  int res_21 = s21_sprintf(str, "%-10.5d", a);
  int res_21_orig = sprintf(str_orig, "%-10.5d", a);

  ck_assert_int_eq(res_21, res_21_orig);
  ck_assert_str_eq(str, str_orig);

  int res_22 = s21_sprintf(str, "%3.5d", a);
  int res_22_orig = sprintf(str_orig, "%3.5d", a);

  ck_assert_int_eq(res_22, res_22_orig);
  ck_assert_str_eq(str, str_orig);

  int res_23 = s21_sprintf(str, "% 3.5d", a);
  int res_23_orig = sprintf(str_orig, "% 3.5d", a);

  ck_assert_int_eq(res_23, res_23_orig);
  ck_assert_str_eq(str, str_orig);

  int res_24 = s21_sprintf(str, "%+3.5d", a);
  int res_24_orig = sprintf(str_orig, "%+3.5d", a);

  ck_assert_int_eq(res_24, res_24_orig);
  ck_assert_str_eq(str, str_orig);

  int res_25 = s21_sprintf(str, "%-3.5d", a);
  int res_25_orig = sprintf(str_orig, "%-3.5d", a);

  ck_assert_int_eq(res_25, res_25_orig);
  ck_assert_str_eq(str, str_orig);

  int res_26 = s21_sprintf(str, "%+6.2d", a);
  int res_26_orig = sprintf(str_orig, "%+6.2d", a);

  ck_assert_int_eq(res_26, res_26_orig);
  ck_assert_str_eq(str, str_orig);

  int res_27 = s21_sprintf(str, "%+6.3d", a);
  int res_27_orig = sprintf(str_orig, "%+6.3d", a);

  ck_assert_int_eq(res_27, res_27_orig);
  ck_assert_str_eq(str, str_orig);

  int res_28 = s21_sprintf(str, "%+6.4d", a);
  int res_28_orig = sprintf(str_orig, "%+6.4d", a);

  ck_assert_int_eq(res_28, res_28_orig);
  ck_assert_str_eq(str, str_orig);

  int res_29 = s21_sprintf(str, "%-6.2d", -a);
  int res_29_orig = sprintf(str_orig, "%-6.2d", -a);

  ck_assert_int_eq(res_29, res_29_orig);
  ck_assert_str_eq(str, str_orig);

  int res_30 = s21_sprintf(str, "%+05d", a);
  int res_30_orig = sprintf(str_orig, "%+05d", a);

  ck_assert_int_eq(res_30, res_30_orig);
  ck_assert_str_eq(str, str_orig);
}
END_TEST

START_TEST(s21_sprintf_d_test_4) {
  char str[80];
  char str_orig[80];
  int a = -23;

  int res_1 = s21_sprintf(str, "%10.5d", a);
  int res_1_orig = sprintf(str_orig, "%10.5d", a);

  ck_assert_int_eq(res_1, res_1_orig);
  ck_assert_str_eq(str, str_orig);

  int res_2 = s21_sprintf(str, "% 10.5d", a);
  int res_2_orig = sprintf(str_orig, "% 10.5d", a);

  ck_assert_int_eq(res_2, res_2_orig);
  ck_assert_str_eq(str, str_orig);

  int res_3 = s21_sprintf(str, "%3.5d", a);
  int res_3_orig = sprintf(str_orig, "%3.5d", a);

  ck_assert_int_eq(res_3, res_3_orig);
  ck_assert_str_eq(str, str_orig);

  int res_4 = s21_sprintf(str, "%d", a);
  int res_4_orig = sprintf(str_orig, "%d", a);

  ck_assert_int_eq(res_4, res_4_orig);
  ck_assert_str_eq(str, str_orig);

  int res_5 = s21_sprintf(str, "%0d", a);
  int res_5_orig = sprintf(str_orig, "%0d", a);

  ck_assert_int_eq(res_5, res_5_orig);
  ck_assert_str_eq(str, str_orig);

  int res_6 = s21_sprintf(str, "%-d", a);
  int res_6_orig = sprintf(str_orig, "%-d", a);

  ck_assert_int_eq(res_6, res_6_orig);
  ck_assert_str_eq(str, str_orig);

  int res_7 = s21_sprintf(str, "%+d", a);
  int res_7_orig = sprintf(str_orig, "%+d", a);

  ck_assert_int_eq(res_7, res_7_orig);
  ck_assert_str_eq(str, str_orig);

  int res_8 = s21_sprintf(str, "% d", a);
  int res_8_orig = sprintf(str_orig, "% d", a);

  ck_assert_int_eq(res_8, res_8_orig);
  ck_assert_str_eq(str, str_orig);

  int res_9 = s21_sprintf(str, "%5d", a);
  int res_9_orig = sprintf(str_orig, "%5d", a);

  ck_assert_int_eq(res_9, res_9_orig);
  ck_assert_str_eq(str, str_orig);

  int res_10 = s21_sprintf(str, "%05d", a);
  int res_10_orig = sprintf(str_orig, "%05d", a);

  ck_assert_int_eq(res_10, res_10_orig);
  ck_assert_str_eq(str, str_orig);

  int res_11 = s21_sprintf(str, "%-5d", a);
  int res_11_orig = sprintf(str_orig, "%-5d", a);

  ck_assert_int_eq(res_11, res_11_orig);
  ck_assert_str_eq(str, str_orig);

  int res_12 = s21_sprintf(str, "%+5d", a);
  int res_12_orig = sprintf(str_orig, "%+5d", a);

  ck_assert_int_eq(res_12, res_12_orig);
  ck_assert_str_eq(str, str_orig);

  int res_13 = s21_sprintf(str, "% 5d", a);
  int res_13_orig = sprintf(str_orig, "% 5d", a);

  ck_assert_int_eq(res_13, res_13_orig);
  ck_assert_str_eq(str, str_orig);

  int res_14 = s21_sprintf(str, "%.5d", a);
  int res_14_orig = sprintf(str_orig, "%.5d", a);

  ck_assert_int_eq(res_14, res_14_orig);
  ck_assert_str_eq(str, str_orig);

  int res_15 = s21_sprintf(str, "%.5d", a);
  int res_15_orig = sprintf(str_orig, "%.5d", a);

  ck_assert_int_eq(res_15, res_15_orig);
  ck_assert_str_eq(str, str_orig);

  int res_16 = s21_sprintf(str, "% .5d", a);
  int res_16_orig = sprintf(str_orig, "% .5d", a);

  ck_assert_int_eq(res_16, res_16_orig);
  ck_assert_str_eq(str, str_orig);

  int res_17 = s21_sprintf(str, "%+.5d", a);
  int res_17_orig = sprintf(str_orig, "%+.5d", a);

  ck_assert_int_eq(res_17, res_17_orig);
  ck_assert_str_eq(str, str_orig);

  int res_18 = s21_sprintf(str, "%-.5d", a);
  int res_18_orig = sprintf(str_orig, "%-.5d", a);

  ck_assert_int_eq(res_18, res_18_orig);
  ck_assert_str_eq(str, str_orig);

  int res_19 = s21_sprintf(str, "%10.5d", a);
  int res_19_orig = sprintf(str_orig, "%10.5d", a);

  ck_assert_int_eq(res_19, res_19_orig);
  ck_assert_str_eq(str, str_orig);

  int res_20 = s21_sprintf(str, "%+10.5d", a);
  int res_20_orig = sprintf(str_orig, "%+10.5d", a);

  ck_assert_int_eq(res_20, res_20_orig);
  ck_assert_str_eq(str, str_orig);

  int res_21 = s21_sprintf(str, "%-10.5d", a);
  int res_21_orig = sprintf(str_orig, "%-10.5d", a);

  ck_assert_int_eq(res_21, res_21_orig);
  ck_assert_str_eq(str, str_orig);

  int res_22 = s21_sprintf(str, "%3.5d", a);
  int res_22_orig = sprintf(str_orig, "%3.5d", a);

  ck_assert_int_eq(res_22, res_22_orig);
  ck_assert_str_eq(str, str_orig);

  int res_23 = s21_sprintf(str, "% 3.5d", a);
  int res_23_orig = sprintf(str_orig, "% 3.5d", a);

  ck_assert_int_eq(res_23, res_23_orig);
  ck_assert_str_eq(str, str_orig);

  int res_24 = s21_sprintf(str, "%+3.5d", a);
  int res_24_orig = sprintf(str_orig, "%+3.5d", a);

  ck_assert_int_eq(res_24, res_24_orig);
  ck_assert_str_eq(str, str_orig);

  int res_25 = s21_sprintf(str, "%-3.5d", a);
  int res_25_orig = sprintf(str_orig, "%-3.5d", a);

  ck_assert_int_eq(res_25, res_25_orig);
  ck_assert_str_eq(str, str_orig);

  int res_26 = s21_sprintf(str, "%+05d", a);
  int res_26_orig = sprintf(str_orig, "%+05d", a);

  ck_assert_int_eq(res_26, res_26_orig);
  ck_assert_str_eq(str, str_orig);
}
END_TEST

START_TEST(s21_sprintf_d_test_5) {
  char str[80];
  char str_orig[80];
  int a = -2344;

  int res_2 = s21_sprintf(str, "% 10.5d", a);
  int res_2_orig = sprintf(str_orig, "% 10.5d", a);

  ck_assert_int_eq(res_2, res_2_orig);
  ck_assert_str_eq(str, str_orig);

  int res_3 = s21_sprintf(str, "%3.5d", a);
  int res_3_orig = sprintf(str_orig, "%3.5d", a);

  ck_assert_int_eq(res_3, res_3_orig);
  ck_assert_str_eq(str, str_orig);

  int res_4 = s21_sprintf(str, "%d", a);
  int res_4_orig = sprintf(str_orig, "%d", a);

  ck_assert_int_eq(res_4, res_4_orig);
  ck_assert_str_eq(str, str_orig);

  int res_5 = s21_sprintf(str, "%0d", a);
  int res_5_orig = sprintf(str_orig, "%0d", a);

  ck_assert_int_eq(res_5, res_5_orig);
  ck_assert_str_eq(str, str_orig);

  int res_6 = s21_sprintf(str, "%-d", a);
  int res_6_orig = sprintf(str_orig, "%-d", a);

  ck_assert_int_eq(res_6, res_6_orig);
  ck_assert_str_eq(str, str_orig);

  int res_7 = s21_sprintf(str, "%+d", a);
  int res_7_orig = sprintf(str_orig, "%+d", a);

  ck_assert_int_eq(res_7, res_7_orig);
  ck_assert_str_eq(str, str_orig);

  int res_8 = s21_sprintf(str, "% d", a);
  int res_8_orig = sprintf(str_orig, "% d", a);

  ck_assert_int_eq(res_8, res_8_orig);
  ck_assert_str_eq(str, str_orig);

  int res_9 = s21_sprintf(str, "%5d", a);
  int res_9_orig = sprintf(str_orig, "%5d", a);

  ck_assert_int_eq(res_9, res_9_orig);
  ck_assert_str_eq(str, str_orig);

  int res_10 = s21_sprintf(str, "%05d", a);
  int res_10_orig = sprintf(str_orig, "%05d", a);

  ck_assert_int_eq(res_10, res_10_orig);
  ck_assert_str_eq(str, str_orig);

  int res_11 = s21_sprintf(str, "%-5d", a);
  int res_11_orig = sprintf(str_orig, "%-5d", a);

  ck_assert_int_eq(res_11, res_11_orig);
  ck_assert_str_eq(str, str_orig);

  int res_12 = s21_sprintf(str, "%+5d", a);
  int res_12_orig = sprintf(str_orig, "%+5d", a);

  ck_assert_int_eq(res_12, res_12_orig);
  ck_assert_str_eq(str, str_orig);

  int res_13 = s21_sprintf(str, "% 5d", a);
  int res_13_orig = sprintf(str_orig, "% 5d", a);

  ck_assert_int_eq(res_13, res_13_orig);
  ck_assert_str_eq(str, str_orig);

  int res_14 = s21_sprintf(str, "%.5d", a);
  int res_14_orig = sprintf(str_orig, "%.5d", a);

  ck_assert_int_eq(res_14, res_14_orig);
  ck_assert_str_eq(str, str_orig);

  int res_15 = s21_sprintf(str, "%.5d", a);
  int res_15_orig = sprintf(str_orig, "%.5d", a);

  ck_assert_int_eq(res_15, res_15_orig);
  ck_assert_str_eq(str, str_orig);

  int res_16 = s21_sprintf(str, "% .5d", a);
  int res_16_orig = sprintf(str_orig, "% .5d", a);

  ck_assert_int_eq(res_16, res_16_orig);
  ck_assert_str_eq(str, str_orig);

  int res_17 = s21_sprintf(str, "%+.5d", a);
  int res_17_orig = sprintf(str_orig, "%+.5d", a);

  ck_assert_int_eq(res_17, res_17_orig);
  ck_assert_str_eq(str, str_orig);

  int res_18 = s21_sprintf(str, "%-.5d", a);
  int res_18_orig = sprintf(str_orig, "%-.5d", a);

  ck_assert_int_eq(res_18, res_18_orig);
  ck_assert_str_eq(str, str_orig);

  int res_19 = s21_sprintf(str, "%10.5d", a);
  int res_19_orig = sprintf(str_orig, "%10.5d", a);

  ck_assert_int_eq(res_19, res_19_orig);
  ck_assert_str_eq(str, str_orig);

  int res_20 = s21_sprintf(str, "%+10.5d", a);
  int res_20_orig = sprintf(str_orig, "%+10.5d", a);

  ck_assert_int_eq(res_20, res_20_orig);
  ck_assert_str_eq(str, str_orig);

  int res_21 = s21_sprintf(str, "%-10.5d", a);
  int res_21_orig = sprintf(str_orig, "%-10.5d", a);

  ck_assert_int_eq(res_21, res_21_orig);
  ck_assert_str_eq(str, str_orig);

  int res_22 = s21_sprintf(str, "%3.5d", a);
  int res_22_orig = sprintf(str_orig, "%3.5d", a);

  ck_assert_int_eq(res_22, res_22_orig);
  ck_assert_str_eq(str, str_orig);

  int res_23 = s21_sprintf(str, "% 3.5d", a);
  int res_23_orig = sprintf(str_orig, "% 3.5d", a);

  ck_assert_int_eq(res_23, res_23_orig);
  ck_assert_str_eq(str, str_orig);

  int res_24 = s21_sprintf(str, "%+3.5d", a);
  int res_24_orig = sprintf(str_orig, "%+3.5d", a);

  ck_assert_int_eq(res_24, res_24_orig);
  ck_assert_str_eq(str, str_orig);

  int res_25 = s21_sprintf(str, "%-3.5d", a);
  int res_25_orig = sprintf(str_orig, "%-3.5d", a);

  ck_assert_int_eq(res_25, res_25_orig);
  ck_assert_str_eq(str, str_orig);

  int res_26 = s21_sprintf(str, "%+05d", a);
  int res_26_orig = sprintf(str_orig, "%+05d", a);

  ck_assert_int_eq(res_26, res_26_orig);
  ck_assert_str_eq(str, str_orig);
}
END_TEST

START_TEST(s21_sprintf_d_test_6) {
  char str[80];
  char str_orig[80];
  int a = 23;

  int res_1 = s21_sprintf(str, "%+10.5d", a);
  int res_1_orig = sprintf(str_orig, "%+10.5d", a);

  ck_assert_int_eq(res_1, res_1_orig);
  ck_assert_str_eq(str, str_orig);

  int res_3 = s21_sprintf(str, "%+3.5d", a);
  int res_3_orig = sprintf(str_orig, "%+3.5d", a);

  ck_assert_int_eq(res_3, res_3_orig);
  ck_assert_str_eq(str, str_orig);

  int res_4 = s21_sprintf(str, "%+d", a);
  int res_4_orig = sprintf(str_orig, "%+d", a);

  ck_assert_int_eq(res_4, res_4_orig);
  ck_assert_str_eq(str, str_orig);

  int res_5 = s21_sprintf(str, "%+0d", a);
  int res_5_orig = sprintf(str_orig, "%+0d", a);

  ck_assert_int_eq(res_5, res_5_orig);
  ck_assert_str_eq(str, str_orig);

  int res_6 = s21_sprintf(str, "%-+d", a);
  int res_6_orig = sprintf(str_orig, "%-+d", a);

  ck_assert_int_eq(res_6, res_6_orig);
  ck_assert_str_eq(str, str_orig);

  int res_7 = s21_sprintf(str, "%+d", a);
  int res_7_orig = sprintf(str_orig, "%+d", a);

  ck_assert_int_eq(res_7, res_7_orig);
  ck_assert_str_eq(str, str_orig);

  int res_9 = s21_sprintf(str, "%+5d", a);
  int res_9_orig = sprintf(str_orig, "%+5d", a);

  ck_assert_int_eq(res_9, res_9_orig);
  ck_assert_str_eq(str, str_orig);

  int res_11 = s21_sprintf(str, "%-+5d", a);
  int res_11_orig = sprintf(str_orig, "%-+5d", a);

  ck_assert_int_eq(res_11, res_11_orig);
  ck_assert_str_eq(str, str_orig);

  int res_12 = s21_sprintf(str, "%+5d", a);
  int res_12_orig = sprintf(str_orig, "%+5d", a);

  ck_assert_int_eq(res_12, res_12_orig);
  ck_assert_str_eq(str, str_orig);

  int res_14 = s21_sprintf(str, "%+.5d", a);
  int res_14_orig = sprintf(str_orig, "%+.5d", a);

  ck_assert_int_eq(res_14, res_14_orig);
  ck_assert_str_eq(str, str_orig);

  int res_15 = s21_sprintf(str, "%+.5d", a);
  int res_15_orig = sprintf(str_orig, "%+.5d", a);

  ck_assert_int_eq(res_15, res_15_orig);
  ck_assert_str_eq(str, str_orig);

  int res_16 = s21_sprintf(str, "% .5d", a);
  int res_16_orig = sprintf(str_orig, "% .5d", a);

  ck_assert_int_eq(res_16, res_16_orig);
  ck_assert_str_eq(str, str_orig);

  int res_18 = s21_sprintf(str, "%-+.5d", a);
  int res_18_orig = sprintf(str_orig, "%-+.5d", a);

  ck_assert_int_eq(res_18, res_18_orig);
  ck_assert_str_eq(str, str_orig);

  int res_20 = s21_sprintf(str, "%+10.5d", a);
  int res_20_orig = sprintf(str_orig, "%+10.5d", a);

  ck_assert_int_eq(res_20, res_20_orig);
  ck_assert_str_eq(str, str_orig);

  int res_21 = s21_sprintf(str, "%-+10.5d", a);
  int res_21_orig = sprintf(str_orig, "%-+10.5d", a);

  ck_assert_int_eq(res_21, res_21_orig);
  ck_assert_str_eq(str, str_orig);

  int res_22 = s21_sprintf(str, "%+3.5d", a);
  int res_22_orig = sprintf(str_orig, "%+3.5d", a);

  ck_assert_int_eq(res_22, res_22_orig);
  ck_assert_str_eq(str, str_orig);

  int res_23 = s21_sprintf(str, "% 3.5d", a);
  int res_23_orig = sprintf(str_orig, "% 3.5d", a);

  ck_assert_int_eq(res_23, res_23_orig);
  ck_assert_str_eq(str, str_orig);

  int res_25 = s21_sprintf(str, "%-+3.5d", a);
  int res_25_orig = sprintf(str_orig, "%-+3.5d", a);

  ck_assert_int_eq(res_25, res_25_orig);
  ck_assert_str_eq(str, str_orig);

  int res_26 = s21_sprintf(str, "%+05d", a);
  int res_26_orig = sprintf(str_orig, "%+05d", a);

  ck_assert_int_eq(res_26, res_26_orig);
  ck_assert_str_eq(str, str_orig);
}
END_TEST

START_TEST(s21_sprintf_d_test_0) {
  char str[80];
  char str_orig[80];
  int a = 0;

  int res_1 = s21_sprintf(str, "%+10.5d", a);
  int res_1_orig = sprintf(str_orig, "%+10.5d", a);

  ck_assert_int_eq(res_1, res_1_orig);
  ck_assert_str_eq(str, str_orig);

  int res_3 = s21_sprintf(str, "%+3.5d", a);
  int res_3_orig = sprintf(str_orig, "%+3.5d", a);

  ck_assert_int_eq(res_3, res_3_orig);
  ck_assert_str_eq(str, str_orig);

  int res_4 = s21_sprintf(str, "%+d", a);
  int res_4_orig = sprintf(str_orig, "%+d", a);

  ck_assert_int_eq(res_4, res_4_orig);
  ck_assert_str_eq(str, str_orig);

  int res_5 = s21_sprintf(str, "%05d", a);
  int res_5_orig = sprintf(str_orig, "%05d", a);

  ck_assert_int_eq(res_5, res_5_orig);
  ck_assert_str_eq(str, str_orig);

  int res_7 = s21_sprintf(str, "%+d", a);
  int res_7_orig = sprintf(str_orig, "%+d", a);

  ck_assert_int_eq(res_7, res_7_orig);
  ck_assert_str_eq(str, str_orig);

  int res_9 = s21_sprintf(str, "%+5d", a);
  int res_9_orig = sprintf(str_orig, "%+5d", a);

  ck_assert_int_eq(res_9, res_9_orig);
  ck_assert_str_eq(str, str_orig);

  int res_12 = s21_sprintf(str, "%+5d", a);
  int res_12_orig = sprintf(str_orig, "%+5d", a);

  ck_assert_int_eq(res_12, res_12_orig);
  ck_assert_str_eq(str, str_orig);

  int res_14 = s21_sprintf(str, "%+.5d", a);
  int res_14_orig = sprintf(str_orig, "%+.5d", a);

  ck_assert_int_eq(res_14, res_14_orig);
  ck_assert_str_eq(str, str_orig);

  int res_15 = s21_sprintf(str, "%+.5d", a);
  int res_15_orig = sprintf(str_orig, "%+.5d", a);

  ck_assert_int_eq(res_15, res_15_orig);
  ck_assert_str_eq(str, str_orig);

  int res_20 = s21_sprintf(str, "%+10.5d", a);
  int res_20_orig = sprintf(str_orig, "%+10.5d", a);

  ck_assert_int_eq(res_20, res_20_orig);
  ck_assert_str_eq(str, str_orig);

  int res_22 = s21_sprintf(str, "%+3.5d", a);
  int res_22_orig = sprintf(str_orig, "%+3.5d", a);

  ck_assert_int_eq(res_22, res_22_orig);
  ck_assert_str_eq(str, str_orig);

  int res_26 = s21_sprintf(str, "%+05d", a);
  int res_26_orig = sprintf(str_orig, "%+05d", a);

  ck_assert_int_eq(res_26, res_26_orig);
  ck_assert_str_eq(str, str_orig);
}
END_TEST

START_TEST(s21_sprintf_test1) {
  char array1[100];
  char array2[100];
  int a = sprintf(array1, "|%5d|", 888);
  int b = s21_sprintf(array2, "|%5d|", 888);
  ck_assert_str_eq(array1, array2);
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(s21_sprintf_test2) {
  char array1[100];
  char array2[100];
  int a = sprintf(array1, "|%5d|", -888);
  int b = s21_sprintf(array2, "|%5d|", -888);
  ck_assert_str_eq(array1, array2);
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(s21_sprintf_test3) {
  char array1[100];
  char array2[100];
  int a = sprintf(array1, "|%-5d|", 888);
  int b = s21_sprintf(array2, "|%-5d|", 888);
  ck_assert_str_eq(array1, array2);
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(s21_sprintf_test4) {
  char array1[100];
  char array2[100];
  int a = sprintf(array1, "|%-5d|", -888);
  int b = s21_sprintf(array2, "|%-5d|", -888);
  ck_assert_str_eq(array1, array2);
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(s21_sprintf_test5) {
  char array1[100];
  char array2[100];
  int a = sprintf(array1, "|%+5d|", -888);
  int b = s21_sprintf(array2, "|%+5d|", -888);
  ck_assert_str_eq(array1, array2);
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(s21_sprintf_test6) {
  char array1[100];
  char array2[100];
  int a = sprintf(array1, "|%+5d|", +888);
  int b = s21_sprintf(array2, "|%+5d|", +888);
  ck_assert_str_eq(array1, array2);
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(s21_sprintf_test7) {
  char array1[100];
  char array2[100];
  int a = sprintf(array1, "|%*d|", 4, -888);
  int b = s21_sprintf(array2, "|%*d|", 4, -888);
  ck_assert_str_eq(array1, array2);
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(s21_sprintf_test8) {
  char array1[100];
  char array2[100];
  int a = sprintf(array1, "|%+5d|", -888);
  int b = s21_sprintf(array2, "|%+5d|", -888);
  ck_assert_str_eq(array1, array2);
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(s21_sprintf_test9) {
  char array1[100];
  char array2[100];
  int a = sprintf(array1, "|% d|", 888);
  int b = s21_sprintf(array2, "|% d|", 888);
  ck_assert_str_eq(array1, array2);
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(s21_sprintf_test10) {
  char array1[100];
  char array2[100];
  int a = sprintf(array1, "|% d|", -888);
  int b = s21_sprintf(array2, "|% d|", -888);
  ck_assert_str_eq(array1, array2);
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(s21_sprintf_test11) {
  char array1[100];
  char array2[100];
  int a = sprintf(array1, "|% -d|", 888);
  int b = s21_sprintf(array2, "|% -d|", 888);
  ck_assert_str_eq(array1, array2);
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(s21_sprintf_test12) {
  char array1[100];
  char array2[100];
  int a = sprintf(array1, "|% -d|", -888);
  int b = s21_sprintf(array2, "|% -d|", -888);
  ck_assert_str_eq(array1, array2);
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(s21_sprintf_test13) {
  char array1[100];
  char array2[100];
  int a = sprintf(array1, "|%04d|", 88);
  int b = s21_sprintf(array2, "|%04d|", 88);
  ck_assert_str_eq(array1, array2);
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(s21_sprintf_test14) {
  char array1[100];
  char array2[100];
  int a = sprintf(array1, "|%05d|", -88);
  int b = s21_sprintf(array2, "|%05d|", -88);
  ck_assert_str_eq(array1, array2);
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(s21_sprintf_test15) {
  char array1[100];
  char array2[100];
  int a = sprintf(array1, "|%05d|", -88);
  int b = s21_sprintf(array2, "|%05d|", -88);
  ck_assert_str_eq(array1, array2);
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(s21_sprintf_test16) {
  char array1[100];
  char array2[100];
  int a = sprintf(array1, "|%+05d|", -88);
  int b = s21_sprintf(array2, "|%+05d|", -88);
  ck_assert_str_eq(array1, array2);
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(s21_sprintf_test17) {
  char array1[100];
  char array2[100];
  int a = sprintf(array1, "|%.3d|", 88);
  int b = s21_sprintf(array2, "|%.3d|", 88);
  ck_assert_str_eq(array1, array2);
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(s21_sprintf_test18) {
  char array1[100];
  char array2[100];
  int a = sprintf(array1, "|%.03d|", 88);
  int b = s21_sprintf(array2, "|%.03d|", 88);
  ck_assert_str_eq(array1, array2);
  ck_assert_int_eq(a, b);
}
END_TEST

// Спецификатор %i
START_TEST(s21_sprintf_test20) {
  char array1[100];
  char array2[100];
  int a = sprintf(array1, "|%-5i|", 12345);
  int b = s21_sprintf(array2, "|%-5d|", 12345);
  ck_assert_str_eq(array1, array2);
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(s21_sprintf_test21) {
  char array1[100];
  char array2[100];
  int a = sprintf(array1, "|%-5i|", -12345);
  int b = s21_sprintf(array2, "|%-5i|", -12345);
  ck_assert_str_eq(array1, array2);
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(s21_sprintf_test22) {
  char array1[100];
  char array2[100];
  int a = sprintf(array1, "|%+5i|", -12345);
  int b = s21_sprintf(array2, "|%+5i|", -12345);
  ck_assert_str_eq(array1, array2);
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(s21_sprintf_test23) {
  char array1[100];
  char array2[100];
  int a = sprintf(array1, "|%+5i|", +12345);
  int b = s21_sprintf(array2, "|%+5i|", +12345);
  ck_assert_str_eq(array1, array2);
  ck_assert_int_eq(a, b);
}
END_TEST

// Cпецификатор %с

START_TEST(s21_sprintf_test24) {
  char data[100];
  char data1[100];
  int a = s21_sprintf(data, "|%c|", 'a');
  int b = sprintf(data1, "|%c|", 'a');
  ck_assert_str_eq(data, data1);
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(s21_sprintf_test25) {
  char data[100];
  char data1[100];
  int a = s21_sprintf(data, "|%5c|", 'R');
  int b = sprintf(data1, "|%5c|", 'R');
  ck_assert_str_eq(data, data1);
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(s21_sprintf_test26) {
  char data[100];
  char data1[100];
  int a = s21_sprintf(data, "|%-5c|", 'R');
  int b = sprintf(data1, "|%-5c|", 'R');
  ck_assert_str_eq(data, data1);
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(s21_sprintf_test27) {
  char data[100];
  char data1[100];
  int a = s21_sprintf(data, "|%c|", '\0');
  int b = sprintf(data1, "|%c|", '\0');
  ck_assert_str_eq(data, data1);
  ck_assert_int_eq(a, b);
}
END_TEST

// Спецификатор %e

START_TEST(s21_sprintf_test28) {
  char data[100];
  char data1[100];
  int a = s21_sprintf(data, "|%e|", 3.141592);
  int b = sprintf(data1, "|%e|", 3.141592);
  ck_assert_str_eq(data, data1);
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(s21_sprintf_test29) {
  char data[100];
  char data1[100];
  int a = s21_sprintf(data, "|%e|", 314.1592);
  int b = sprintf(data1, "|%e|", 314.1592);
  ck_assert_str_eq(data, data1);
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(s21_sprintf_test30) {
  char data[100];
  char data1[100];
  int a = s21_sprintf(data, "|%E|", 314.1592);
  int b = sprintf(data1, "|%E|", 314.1592);
  ck_assert_str_eq(data, data1);
  ck_assert_int_eq(a, b);
}
END_TEST

// Спецификатор %f

START_TEST(s21_sprintf_test31) {
  char array1[100];
  char array2[100];
  int a = sprintf(array1, "|%.3f|", 8.8888);
  int b = s21_sprintf(array2, "|%.3f|", 8.8888);
  ck_assert_str_eq(array1, array2);
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(s21_sprintf_test32) {
  char array1[100];
  char array2[100];
  int a = sprintf(array1, "|%.03f|", 8.88);
  int b = s21_sprintf(array2, "|%.03f|", 8.88);
  ck_assert_str_eq(array1, array2);
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(s21_sprintf_test33) {
  char array1[100];
  char array2[100];
  int a = sprintf(array1, "|%0.3f|", 8.88);
  int b = s21_sprintf(array2, "|%0.3f|", 8.88);
  ck_assert_str_eq(array1, array2);
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(s21_sprintf_test34) {
  char array1[100];
  char array2[100];
  int a = sprintf(array1, "|%*.*f|", 8, 3, 8.8888);
  int b = s21_sprintf(array2, "|%*.*f|", 8, 3, 8.8888);
  ck_assert_str_eq(array1, array2);
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(s21_sprintf_test35) {
  char array1[100];
  char array2[100];
  int a = sprintf(array1, "|%-*.*f|", 8, 3, 8.8888);
  int b = s21_sprintf(array2, "|%-*.*f|", 8, 3, 8.8888);
  ck_assert_str_eq(array1, array2);
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(s21_sprintf_test36) {
  char array1[100];
  char array2[100];
  int a = sprintf(array1, "|%0*.*f|", 8, 3, 8.8888);
  int b = s21_sprintf(array2, "|%0*.*f|", 8, 3, 8.8888);
  ck_assert_str_eq(array1, array2);
  ck_assert_int_eq(a, b);
}
END_TEST

// Спецификатор %g и G

START_TEST(s21_sprintf_test37) {
  char array1[100];
  char array2[100];
  int a = sprintf(array1, "|%g|", 8.88000);
  int b = s21_sprintf(array2, "|%g|", 8.88000);
  ck_assert_str_eq(array1, array2);
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(s21_sprintf_test38) {
  char array1[100];
  char array2[100];
  int a = sprintf(array1, "|%.0g|", 8.88000);
  int b = s21_sprintf(array2, "|%.0g|", 8.88000);
  ck_assert_str_eq(array1, array2);
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(s21_sprintf_test39) {
  char array1[100];
  char array2[100];
  int a = sprintf(array1, "|%.1g|", 8.88000);
  int b = s21_sprintf(array2, "|%.1g|", 8.88000);
  ck_assert_str_eq(array1, array2);
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(s21_sprintf_test40) {
  char array1[100];
  char array2[100];
  int a = sprintf(array1, "|%.2g|", 8.88000);
  int b = s21_sprintf(array2, "|%.2g|", 8.88000);
  ck_assert_str_eq(array1, array2);
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(s21_sprintf_test41) {
  char array1[100];
  char array2[100];
  int a = sprintf(array1, "|%.2G|", 8.88000);
  int b = s21_sprintf(array2, "|%.2G|", 8.88000);
  ck_assert_str_eq(array1, array2);
  ck_assert_int_eq(a, b);
}
END_TEST

// Спецификатор %o

START_TEST(s21_sprintf_test42) {
  char array1[100];
  char array2[100];
  int a = sprintf(array1, "|%o|", 888);
  int b = s21_sprintf(array2, "|%o|", 888);
  ck_assert_str_eq(array1, array2);
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(s21_sprintf_test43) {
  char array1[100];
  char array2[100];
  int a = sprintf(array1, "|%#o|", 888);
  int b = s21_sprintf(array2, "|%#o|", 888);
  ck_assert_str_eq(array1, array2);
  ck_assert_int_eq(a, b);
}
END_TEST

// Спецификатор %x и X

START_TEST(s21_sprintf_test44) {
  char array1[100];
  char array2[100];
  int a = sprintf(array1, "|%x|", 888);
  int b = s21_sprintf(array2, "|%x|", 888);
  ck_assert_str_eq(array1, array2);
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(s21_sprintf_test45) {
  char array1[100];
  char array2[100];
  int a = sprintf(array1, "|%#x|", 888);
  int b = s21_sprintf(array2, "|%#x|", 888);
  ck_assert_str_eq(array1, array2);
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(s21_sprintf_test46) {
  char array1[100];
  char array2[100];
  int a = sprintf(array1, "|%X|", 888);
  int b = s21_sprintf(array2, "|%X|", 888);
  ck_assert_str_eq(array1, array2);
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(s21_sprintf_test47) {
  char array1[100];
  char array2[100];
  int a = sprintf(array1, "|%#X|", 888);
  int b = s21_sprintf(array2, "|%#X|", 888);
  ck_assert_str_eq(array1, array2);
  ck_assert_int_eq(a, b);
}
END_TEST

// Спецификатор %s

START_TEST(s21_sprintf_test48) {
  char data[100];
  char data1[100];
  int a = s21_sprintf(data, "|%.3s| love |%20s|", "IIII", "you");
  int b = sprintf(data1, "|%.3s| love |%20s|", "IIII", "you");
  ck_assert_str_eq(data, data1);
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(s21_sprintf_test69) {
  char data[100];
  char data1[100];
  int a = s21_sprintf(data, "|test %-12i et %24s !|", 0, "zero");
  int b = sprintf(data1, "|test %-12i et %24s !|", 0, "zero");
  ck_assert_str_eq(data, data1);
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(s21_sprintf_test49) {
  char data[100];
  char data1[100];
  int a = s21_sprintf(data, "|%.15s|", "21school");
  int b = sprintf(data1, "|%.15s|", "21school");
  ck_assert_str_eq(data, data1);
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(s21_sprintf_test50) {
  char data[100];
  char data1[100];
  int a = s21_sprintf(data, "|%.0s|", "21school");
  int b = sprintf(data1, "|%.0s|", "21school");
  ck_assert_str_eq(data, data1);
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(s21_sprintf_test51) {
  char data[100];
  char data1[100];
  int a = s21_sprintf(data, "|%s|", "\0ab");
  int b = sprintf(data1, "|%s|", "\0ab");
  ck_assert_str_eq(data, data1);
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(s21_sprintf_test52) {
  char data[100];
  char data1[100];
  int a = s21_sprintf(data, "|%s|", "");
  int b = sprintf(data1, "|%s|", "");
  ck_assert_str_eq(data, data1);
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(s21_sprintf_test53) {
  char data[100];
  char data1[100];
  int a = s21_sprintf(data, "|%10.8s|", "yandex");
  int b = sprintf(data1, "|%10.8s|", "yandex");
  ck_assert_str_eq(data, data1);
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(s21_sprintf_test54) {
  char data[100];
  char data1[100];
  int a = s21_sprintf(data, "|%-10.2s|", "21school21");
  int b = sprintf(data1, "|%-10.2s|", "21school21");
  ck_assert_str_eq(data, data1);
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(s21_sprintf_test70) {
  char data[100];
  char data1[100];
  int a = s21_sprintf(data, "|%25s|", "1fg*#&h");
  int b = sprintf(data1, "|%25s|", "1fg*#&h");
  ck_assert_str_eq(data, data1);
  ck_assert_int_eq(a, b);
}
END_TEST

// Спецификатор %u

START_TEST(s21_sprintf_test55) {
  char data[100];
  char data1[100];
  int c = s21_sprintf(data, "|%-2.8u|", (unsigned)-345);
  int d = sprintf(data1, "|%-2.8u|", (unsigned)-345);
  ck_assert_str_eq(data, data1);
  ck_assert_int_eq(c, d);
}
END_TEST

START_TEST(s21_sprintf_test56) {
  char data[100];
  char data1[100];
  int a = s21_sprintf(data, "|%u|", (unsigned)34);
  int b = sprintf(data1, "|%u|", (unsigned)34);
  ck_assert_str_eq(data, data1);
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(s21_sprintf_test57) {
  char data[100];
  char data1[100];
  int a = s21_sprintf(data, "|%-u|", (unsigned)50);
  int b = sprintf(data1, "|%-u|", (unsigned)50);
  ck_assert_str_eq(data, data1);
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(s21_sprintf_test58) {
  char data[100];
  char data1[100];
  int a = s21_sprintf(data, "|%15.20u|", (unsigned)-100000);
  int b = sprintf(data1, "|%15.20u|", (unsigned)-100000);
  ck_assert_str_eq(data, data1);
  ck_assert_int_eq(a, b);
}
END_TEST

// Спецификтор %p

START_TEST(s21_sprintf_test59) {
  char data[100];
  char data1[100];
  int c = 3;
  int a = s21_sprintf(data, "|%p|", &c);
  int b = sprintf(data1, "|%p|", &c);
  ck_assert_str_eq(data, data1);
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(s21_sprintf_test60) {
  char data[100];
  char data1[100];
  int a = s21_sprintf(data, "|%p|", (void *)0x2123);
  int b = sprintf(data1, "|%p|", (void *)0x2123);
  ck_assert_str_eq(data, data1);
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(s21_sprintf_test68) {
  char data[100];
  char data1[100];
  int a = s21_sprintf(data, "|%p|", (void *)0x2123);
  int b = sprintf(data1, "|%p|", (void *)0x2123);
  ck_assert_str_eq(data, data1);
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(s21_sprintf_test61) {
  char data[100];
  char data1[100];
  int a = s21_sprintf(data, "|%12p|", (void *)12345678);
  int b = sprintf(data1, "|%12p|", (void *)12345678);
  ck_assert_str_eq(data, data1);
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(s21_sprintf_test62) {
  char data[100];
  char data1[100];
  int a = s21_sprintf(data, "|%p|", (void *)0xaB123);
  int b = sprintf(data1, "|%p|", (void *)0xaB123);
  ck_assert_str_eq(data, data1);
  ck_assert_int_eq(a, b);
}
END_TEST

// Спецификатор %n

START_TEST(s21_sprintf_test64) {  // Вот тут правильно или нет, 3 сравнения
  char data[100];
  char data1[100];
  int num = 0;
  int s21_num = 0;
  int a = s21_sprintf(data, "|%d%n|", 6525365, &s21_num);
  int b = sprintf(data1, "|%d%n|", 6525365, &num);
  ck_assert_str_eq(data, data1);
  ck_assert_int_eq(s21_num, num);
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(s21_sprintf_test65) {
  char data[100];
  char data1[100];
  int num = 0;
  int s21_num = 0;
  int a = s21_sprintf(data, "|%d%s%n|", 6525365, "fight", &s21_num);
  int b = sprintf(data1, "|%d%s%n|", 6525365, "fight", &num);
  ck_assert_str_eq(data, data1);
  ck_assert_int_eq(s21_num, num);
  ck_assert_int_eq(a, b);
}
END_TEST

// Спецификатор %%

START_TEST(s21_sprintf_test66) {
  char array1[100];
  char array2[100];
  int a = sprintf(array1, "|%%|");
  int b = s21_sprintf(array2, "|%%|");
  ck_assert_str_eq(array1, array2);
  ck_assert_int_eq(a, b);
}
END_TEST

// сборный

START_TEST(s21_sprintf_test67) {
  char str[100];
  char str1[100];
  int a = sprintf(str,
                  "Chislo:|%-5s|kust and |%9c|. This sum is |%i|. This is "
                  "|%%|. And now unsigned: |%u|",
                  "abra", 'e', 56, (unsigned)-43);
  int b = s21_sprintf(str1,
                      "Chislo:|%-5s|kust and |%9c|. This sum is |%i|. This is "
                      "|%%|. And now unsigned: |%u|",
                      "abra", 'e', 56, (unsigned)-43);
  ck_assert_str_eq(str, str1);
  ck_assert_int_eq(a, b);
}
END_TEST

// inf nan spec e f g

START_TEST(s21_sprintf_test71) {
  char data[100];
  char data1[100];
  int a = s21_sprintf(data, "|%E|", INFINITY);
  int b = sprintf(data1, "|%E|", INFINITY);
  ck_assert_str_eq(data, data1);
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(s21_sprintf_test72) {
  char data[100];
  char data1[100];
  int a = s21_sprintf(data, "|%e|", -INFINITY);
  int b = sprintf(data1, "|%e|", -INFINITY);
  ck_assert_str_eq(data, data1);
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(s21_sprintf_test73) {
  char data[100];
  char data1[100];
  int a = s21_sprintf(data, "|%E|", NAN);
  int b = sprintf(data1, "|%E|", NAN);
  ck_assert_str_eq(data, data1);
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(s21_sprintf_test74) {
  char data[100];
  char data1[100];
  int a = s21_sprintf(data, "|%g|", INFINITY);
  int b = sprintf(data1, "|%g|", INFINITY);
  ck_assert_str_eq(data, data1);
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(s21_sprintf_test75) {
  char data[100];
  char data1[100];
  int a = s21_sprintf(data, "|%g|", -INFINITY);
  int b = sprintf(data1, "|%g|", -INFINITY);
  ck_assert_str_eq(data, data1);
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(s21_sprintf_test76) {
  char data[100];
  char data1[100];
  int a = s21_sprintf(data, "|%G|", NAN);
  int b = sprintf(data1, "|%G|", NAN);
  ck_assert_str_eq(data, data1);
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(s21_sprintf_test77) {
  char data[100];
  char data1[100];
  int a = s21_sprintf(data, "|%f|", INFINITY);
  int b = sprintf(data1, "|%f|", INFINITY);
  ck_assert_str_eq(data, data1);
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(s21_sprintf_test78) {
  char data[100];
  char data1[100];
  int a = s21_sprintf(data, "|%f|", -INFINITY);
  int b = sprintf(data1, "|%f|", -INFINITY);
  ck_assert_str_eq(data, data1);
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(s21_sprintf_test79) {
  char data[100];
  char data1[100];
  int a = s21_sprintf(data, "|%f|", NAN);
  int b = sprintf(data1, "|%f|", NAN);
  ck_assert_str_eq(data, data1);
  ck_assert_int_eq(a, b);
}
END_TEST

int main(void) {
  Suite *suite = suite_create("s21_string");
  TCase *tc1_1 = tcase_create("s21_string");
  SRunner *runner = srunner_create(suite);
  int counted_errors;
  suite_add_tcase(suite, tc1_1);

  tcase_add_test(tc1_1, s21_memchr_test);
  tcase_add_test(tc1_1, s21_memcmp_test);
  tcase_add_test(tc1_1, s21_strlen_test);
  tcase_add_test(tc1_1, s21_memcpy_test);
  tcase_add_test(tc1_1, s21_strncat_test);
  tcase_add_test(tc1_1, s21_memset_test);
  tcase_add_test(tc1_1, s21_strcspn_test);
  tcase_add_test(tc1_1, s21_strrchr_test);
  tcase_add_test(tc1_1, s21_strerror_test);
  tcase_add_test(tc1_1, s21_strchr_test);
  tcase_add_test(tc1_1, s21_strstr_test);
  tcase_add_test(tc1_1, s21_strncpy_test);
  tcase_add_test(tc1_1, s21_strpbrk_test);
  tcase_add_test(tc1_1, s21_strncmp_test);
  tcase_add_test(tc1_1, s21_insert_test);
  tcase_add_test(tc1_1, s21_to_upper_test);
  tcase_add_test(tc1_1, s21_to_lower_test);
  tcase_add_test(tc1_1, s21_test_trim_1);
  tcase_add_test(tc1_1, s21_test_trim_2);
  tcase_add_test(tc1_1, s21_test_trim_3);
  tcase_add_test(tc1_1, s21_test_trim_4);
  tcase_add_test(tc1_1, s21_test_trim_5);
  tcase_add_test(tc1_1, s21_test_strcmp);
  tcase_add_test(tc1_1, s21_strtok_test_1);
  tcase_add_test(tc1_1, s21_strtok_test_2);

  tcase_add_test(tc1_1, s21_sprintf_prc_test);
  tcase_add_test(tc1_1, s21_sprintf_test);
  tcase_add_test(tc1_1, s21_sprintf_c_test);
  tcase_add_test(tc1_1, s21_sprintf_s_test);
  tcase_add_test(tc1_1, s21_sprintf_u_test);
  tcase_add_test(tc1_1, s21_sprintf_d_test);
  tcase_add_test(tc1_1, s21_sprintf_d_test_2);
  tcase_add_test(tc1_1, s21_sprintf_d_test_3);
  tcase_add_test(tc1_1, s21_sprintf_d_test_4);
  tcase_add_test(tc1_1, s21_sprintf_d_test_5);
  tcase_add_test(tc1_1, s21_sprintf_d_test_6);
  tcase_add_test(tc1_1, s21_sprintf_d_test_0);

  tcase_add_test(tc1_1, s21_sprintf_test1);
  tcase_add_test(tc1_1, s21_sprintf_test2);
  tcase_add_test(tc1_1, s21_sprintf_test3);
  tcase_add_test(tc1_1, s21_sprintf_test4);
  tcase_add_test(tc1_1, s21_sprintf_test5);
  tcase_add_test(tc1_1, s21_sprintf_test6);
  tcase_add_test(tc1_1, s21_sprintf_test7);
  tcase_add_test(tc1_1, s21_sprintf_test1);
  tcase_add_test(tc1_1, s21_sprintf_test8);
  tcase_add_test(tc1_1, s21_sprintf_test9);
  tcase_add_test(tc1_1, s21_sprintf_test10);
  tcase_add_test(tc1_1, s21_sprintf_test11);
  tcase_add_test(tc1_1, s21_sprintf_test12);
  tcase_add_test(tc1_1, s21_sprintf_test13);
  tcase_add_test(tc1_1, s21_sprintf_test14);
  tcase_add_test(tc1_1, s21_sprintf_test15);
  tcase_add_test(tc1_1, s21_sprintf_test16);
  tcase_add_test(tc1_1, s21_sprintf_test17);
  tcase_add_test(tc1_1, s21_sprintf_test18);
  tcase_add_test(tc1_1, s21_sprintf_test20);
  tcase_add_test(tc1_1, s21_sprintf_test21);
  tcase_add_test(tc1_1, s21_sprintf_test22);
  tcase_add_test(tc1_1, s21_sprintf_test23);
  tcase_add_test(tc1_1, s21_sprintf_test24);
  tcase_add_test(tc1_1, s21_sprintf_test25);
  tcase_add_test(tc1_1, s21_sprintf_test26);
  tcase_add_test(tc1_1, s21_sprintf_test27);
  tcase_add_test(tc1_1, s21_sprintf_test28);
  tcase_add_test(tc1_1, s21_sprintf_test29);
  tcase_add_test(tc1_1, s21_sprintf_test30);
  tcase_add_test(tc1_1, s21_sprintf_test31);
  tcase_add_test(tc1_1, s21_sprintf_test32);
  tcase_add_test(tc1_1, s21_sprintf_test33);
  tcase_add_test(tc1_1, s21_sprintf_test34);
  tcase_add_test(tc1_1, s21_sprintf_test35);
  tcase_add_test(tc1_1, s21_sprintf_test36);
  tcase_add_test(tc1_1, s21_sprintf_test37);
  tcase_add_test(tc1_1, s21_sprintf_test38);
  tcase_add_test(tc1_1, s21_sprintf_test39);
  tcase_add_test(tc1_1, s21_sprintf_test40);
  tcase_add_test(tc1_1, s21_sprintf_test41);
  tcase_add_test(tc1_1, s21_sprintf_test42);
  tcase_add_test(tc1_1, s21_sprintf_test43);
  tcase_add_test(tc1_1, s21_sprintf_test44);
  tcase_add_test(tc1_1, s21_sprintf_test45);
  tcase_add_test(tc1_1, s21_sprintf_test46);
  tcase_add_test(tc1_1, s21_sprintf_test47);
  tcase_add_test(tc1_1, s21_sprintf_test48);
  tcase_add_test(tc1_1, s21_sprintf_test49);
  tcase_add_test(tc1_1, s21_sprintf_test50);
  tcase_add_test(tc1_1, s21_sprintf_test51);
  tcase_add_test(tc1_1, s21_sprintf_test52);
  tcase_add_test(tc1_1, s21_sprintf_test53);
  tcase_add_test(tc1_1, s21_sprintf_test54);
  tcase_add_test(tc1_1, s21_sprintf_test55);
  tcase_add_test(tc1_1, s21_sprintf_test56);
  tcase_add_test(tc1_1, s21_sprintf_test57);
  tcase_add_test(tc1_1, s21_sprintf_test58);
  tcase_add_test(tc1_1, s21_sprintf_test59);
  tcase_add_test(tc1_1, s21_sprintf_test60);
  tcase_add_test(tc1_1, s21_sprintf_test61);
  tcase_add_test(tc1_1, s21_sprintf_test62);
  tcase_add_test(tc1_1, s21_sprintf_test64);
  tcase_add_test(tc1_1, s21_sprintf_test65);
  tcase_add_test(tc1_1, s21_sprintf_test66);
  tcase_add_test(tc1_1, s21_sprintf_test67);
  tcase_add_test(tc1_1, s21_sprintf_test68);
  tcase_add_test(tc1_1, s21_sprintf_test69);
  tcase_add_test(tc1_1, s21_sprintf_test70);
  tcase_add_test(tc1_1, s21_sprintf_test71);
  tcase_add_test(tc1_1, s21_sprintf_test72);
  tcase_add_test(tc1_1, s21_sprintf_test73);
  tcase_add_test(tc1_1, s21_sprintf_test74);
  tcase_add_test(tc1_1, s21_sprintf_test75);
  tcase_add_test(tc1_1, s21_sprintf_test76);
  tcase_add_test(tc1_1, s21_sprintf_test77);
  tcase_add_test(tc1_1, s21_sprintf_test78);
  tcase_add_test(tc1_1, s21_sprintf_test79);

  srunner_set_fork_status(runner, CK_NOFORK);
  srunner_run_all(runner, CK_ENV);
  counted_errors = srunner_ntests_failed(runner);
  srunner_free(runner);
  return counted_errors == 0 ? 0 : 1;
}
