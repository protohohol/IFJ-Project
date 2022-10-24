/**
 * @brief string interface
 * 
 */

#ifndef STR_H
#define STR_H

#include <stdbool.h>

typedef struct
{
  char* str;		// variable for string with '\0' in the end
  unsigned length;		// length of string
  unsigned allocSize;	// size of allocated memory in bytes
} string;

/**
 * @brief string initializator
 * 
 * @param s pointer to string
 * @return true if initialization was successful
 * @return false initialization was not successful
 */
bool str_init(string* s);

/**
 * @brief frees allocated memory
 * 
 * @param s pointer to string
 */
void str_free(string* s);

/**
 * @brief clears content of string
 * 
 * @param s pointer to string
 */
void str_clear(string* s);

/**
 * @brief adds char to the end of string
 * 
 * @param s pointer to string
 * @param c char to be added
 * @return true if adding was successful
 * @return false adding was not successful
 */
bool str_add_char(string* s, char c);

/**
 * @brief copies content of source string to target string
 * 
 * @param target pointer to target string
 * @param source pointer to source string
 * @return true if copying was successful
 * @return false if copying was not successful
 */
bool str_copy_string(string* target, string* source);

/**
 * @brief compares two strings
 * 
 * @param s1 pointer to first string
 * @param s2 pointer to second string
 * @return 0 if strings are equal
 * @return >0 if the first non-matching character in s1 is greater (in ASCII) than that of s2
 * @return <0 if the first non-matching character in str1 is lower (in ASCII) than that of str2
 */
int str_cmp_string(string* s1, string* s2);

/**
 * @brief compares string with const string
 * 
 * @param s1 pointer to string
 * @param s2 pointer to const string
 * @return 0 if strings are equal
 * @return >0 if the first non-matching character in s1 is greater (in ASCII) than that of s2
 * @return <0 if the first non-matching character in str1 is lower (in ASCII) than that of str2
 */
int str_cmp_const_str(string* s1, char* s2);

#endif // !STR_H