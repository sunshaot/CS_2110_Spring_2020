
/**
 * @file my_string.c
 * @author Shaotong Sun
 * @brief Your implementation of these famous 3 string.h libraries!
 * 
 * NOTE: NO ARRAY NOTATION IS ALLOWED IN THIS FILE
 * 
 * @date 2020-03-xx
 */

// DO NOT MODIFY THE INCLUDE(s) LIST
#include <stddef.h>
#include "hw7.h"

/**
 * @brief Calculate the length of a string
 * 
 * @param s a constant C string
 * @return size_t the number of characters in the passed in string
 */
size_t my_strlen(const char *s)
{
    int count = 0;
    while (*s != '\0') {
        count++;
        s++;
    }
    return count;
}

/**
 * @brief Compare two strings
 * 
 * @param s1 First string to be compared
 * @param s2 Second string to be compared
 * @param n First (at most) n bytes to be compared
 * @return int "less than, equal to, or greater than zero if s1 (or the first n bytes thereof) is found, respectively, to be less than, to match, or be greater than s2"
 */
int my_strncmp(const char *s1, const char *s2, size_t n)
{
    unsigned int count = 0;
    while (*s1 == *s2 && *s1 && *s2 && count < n) {
        s1++;
        s2++;
        count++;
    }
    if (*s1 < *s2) {
        return -1;
    } else if (*s1 == *s2) {
        return 0;
    } else {
        return 1;
    }
}

/**
 * @brief Copy a string
 * 
 * @param dest The destination buffer
 * @param src The source to copy from
 * @param n maximum number of bytes to copy
 * @return char* a pointer same as dest
 */
char *my_strncpy(char *dest, const char *src, size_t n)
{
    char *p;
    p = dest;
    for (; n > 0 && *src != '\0'; n--) {
        *p++ = *src++;
    }
    for (; n > 0; n--) {
        *p++ = '\0';
    }
    return dest;
}
