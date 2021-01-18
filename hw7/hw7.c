 /**
 * @file hw7.c
 * @author Shaotong Sun
 * @brief Command-line argument & expression parsing logic
 * @date 2020-03-xx
 */

// DO NOT MODIFY THE INCLUDE(s) LIST
#include <stdio.h>
#include "hw7.h"
#include "errcodes.h"

#define FALSE 0
#define TRUE 1

// One-time defined global array of expressions
struct expression arr[MAX_NUMBER_OF_EXPRESSIONS];

/**
 * @brief Convert a string containing ASCII characters (in decimal) to an int.
 * 
 * @param str A null-terminated C string
 * @return int the corresponding decimal value of the passed in str
 */
int decimalStringToInt(const char *str)
{
    int result = 0;
    for (unsigned int i = 0; i < my_strlen(str); i++) {
        result *= 10;
        if (47 < str[i] && str[i] < 58) {
            result += ((int)str[i] - 48);
        } else {
            return -1;
        }
    }
    return result;
}

/**
 * @brief Convert a string containing ASCII characters (in hex) to an int.
 * 
 * @param str A null-terminated C string
 * @return int the corresponding decimal value of the passed in hexadecimal str
 */
int hexStringToInt(const char *str)
{
        int result = 0;
        for (unsigned int i = 0; i < my_strlen(str); i++) {
            result = result << 4;
            if (47 < str[i] && str[i] < 58) {
                result += ((int)str[i] - 48);
            } else if (64 < str[i] && str[i] < 71) {
                result += ((int)str[i] - 55);
            } else {
            	return -1;
            }
        }
        return result;
}

/**
 * @brief Parser algorithm for determining the result of a basic math expression.
 * 
 * @param expression A null terminated expression retrieved as a command line arg
 * @param index Indicating the corresponding struct in the global struct array (for this expression) to be populated
 */
void parseExpression(char *expression, int index)
{
    if (my_strlen(expression) > MAX_EXPRESSION_LENGTH) {
        my_strncpy(arr[index].buffer, ERROR_MSG, my_strlen(ERROR_MSG));
        arr[index].result = FALSE;
        arr[index].errorCode = ERR_EXPRESSION_TOO_LONG;
    } else if (my_strlen(expression) < MIN_EXPRESSION_LENGTH) {
        my_strncpy(arr[index].buffer, ERROR_MSG, my_strlen(ERROR_MSG));
        arr[index].result = FALSE;
        arr[index].errorCode = ERR_EXPRESSION_TOO_SMALL;
    } else if (my_strncmp(expression, DEBUG_FLAG, my_strlen(DEBUG_FLAG)) == 0) {
        my_strncpy(arr[index].buffer, ERROR_MSG, my_strlen(ERROR_MSG));
        arr[index].result = FALSE;
        arr[index].errorCode = ERR_MALFORMED_HEX_FOUND;
    } else {
        int flag = 0;
        int flag_copy = 0;
        int result = 0;
        int e = 0;
        for (unsigned int i = 0; i < my_strlen(expression); i++) {
            if (expression[i] == 43 || expression[i] == 45) {
                char c[i - flag];
                c[i - flag] = '\0';
                my_strncpy(c, expression + flag, i - flag);
                flag_copy = flag;
                flag = i + 1;
                if (c[0] == 48 && c[1] == 120) {
                    char a[i - flag_copy - 2];
                    a[i - flag_copy - 2] = '\0';
                    my_strncpy(a, (c + 2), my_strlen(c) - 2);
                    if (hexStringToInt(a) == -1) {
                        e = 1;
                        my_strncpy(arr[index].buffer, ERROR_MSG, my_strlen(ERROR_MSG));
                        arr[index].result = FALSE;
                        arr[index].errorCode = ERR_MALFORMED_HEX_FOUND;
                        break;
                        return;
                    }
                    if (flag_copy == 0) {
                        result = hexStringToInt(a);
                    } else {
                        if (expression[flag_copy - 1] == 43) {
                            result += hexStringToInt(a);
                        } else {
                            result -= hexStringToInt(a);
                        }
                    }
                } else {
                    if (decimalStringToInt(c) == -1) {
                        e = 1;
                        my_strncpy(arr[index].buffer, ERROR_MSG, my_strlen(ERROR_MSG));
                        arr[index].result = FALSE;
                        arr[index].errorCode = ERR_MALFORMED_HEX_FOUND;
                        break;
                        return;
                    }
                    if (flag_copy == 0) {
                        result = decimalStringToInt(c);
                    } else {
                        if (expression[flag_copy - 1] == 43) {
                            result += decimalStringToInt(c);
                        } else {
                            result -= decimalStringToInt(c);
                        }
                    }
                }
                for (unsigned int x = 0; x < MAX_EXPRESSION_LENGTH; x++) {
                    c[x] = '\0';
                }
            }
        }
        //tail check
        char c[my_strlen(expression) - flag];
        c[my_strlen(expression) - flag] = '\0';
        for (unsigned int x = 0; x < MAX_EXPRESSION_LENGTH; x++) {
            c[x] = '\0';
        }
        my_strncpy(c, expression + flag, my_strlen(expression) - flag);
        if (c[0] == 48 && c[1] == 120) {
            int temp;
            char a[my_strlen(expression) - flag - 2];
            a[my_strlen(expression) - flag - 2] = '\0';
            my_strncpy(a, (c + 2), my_strlen(expression) - flag - 2);
            temp = hexStringToInt(a);
            if (temp == -1) {
                e = 1;
                my_strncpy(arr[index].buffer, ERROR_MSG, my_strlen(ERROR_MSG));
                arr[index].result = FALSE;
                arr[index].errorCode = ERR_MALFORMED_HEX_FOUND;
            } else {
                if (expression[flag - 1] == 43 || flag == 0){
                    result += temp;
                } else {
                    result -= temp;
                }
            }
        } else {
            if (decimalStringToInt(c) == -1) {
                e = 1;
                my_strncpy(arr[index].buffer, ERROR_MSG, my_strlen(ERROR_MSG));
                arr[index].result = FALSE;
                arr[index].errorCode = ERR_MALFORMED_HEX_FOUND;
                return;
            }
            if (expression[flag - 1] == 43 || flag == 0){
                result += decimalStringToInt(c);
            } else {
                result -= decimalStringToInt(c);
            }
        }
        if (e == 0) {
            my_strncpy(arr[index].buffer, expression, my_strlen(expression));
            arr[index].result = result;
            arr[index].errorCode = NO_ERROR;
        }
    }
}

/**
 * @brief Helper method for printing out the global array struct info
 * DO NOT MODIFY THIS METHOD AS IT IS USED FOR THE LAST STEP (PIPE).
 */
void printArrayDebug(void)
{
    // Safety check
    if (sizeof(arr) / sizeof(arr[0]) != MAX_NUMBER_OF_EXPRESSIONS)
    {
        printf("ERROR: MISMATCH ARRAY LENGTH WITH MACRO: MAX_NUMBER_OF_EXPRESSIONS.\n");
        return;
    }

    for (int i = 0; i < MAX_NUMBER_OF_EXPRESSIONS; i++)
    {
        printf("\nStruct info at index %d:\n", i);
        printf("Expression: %s\n", arr[i].buffer);
        printf("Result: %d\n", arr[i].result);
        printf("ErrorCode: %u\n", arr[i].errorCode);
        printf("---------------------\n");
    }
}

/**
 * @brief Main method, responsible for parsing command line argument and populating expression structs in the global arr
 * 
 * @param argc argument count
 * @param argv argument vector (it's an array of strings)
 * @return int status code of the program termination
 */
int my_main(int argc, char const *argv[])
{
    // Initial check: We need at least 1 math expression passed in
    // ( Yes argc can possibly be zero! But we don't worry about that too much in this hw :) )
    if (argc < 2)
    {
        printf("USAGE:   ./hw7 [-d] \"basic math expressions separated by quotation marks\"\n");
        printf("EXAMPLE: ./hw7 \"3+0x40-7+5\" \"0xA6+5000-45\"\n");
        printf("EXAMPLE FOR PRINTING OUT DEBUG INFO: ./hw7 -d \"3+0x40-7+5\" \"0xA6+5000-45\"\n");
        return 1; // Exit failure (value is implementation defined)
    } else if (argc == 2 && my_strncmp(argv[1], DEBUG_FLAG, my_strlen(DEBUG_FLAG)) == 0) {
        printf("PROGRAM ERROR: No expression specified!\n");
        return 1;
    } else if (argc - 1 > MAX_NUMBER_OF_EXPRESSIONS && my_strncmp(argv[1], DEBUG_FLAG, my_strlen(DEBUG_FLAG)) != 0) {
        printf("PROGRAM ERROR: Too many expressions specified!\n");
        return 1;
    } else if (argc - 2 > MAX_NUMBER_OF_EXPRESSIONS && my_strncmp(argv[1], DEBUG_FLAG, my_strlen(DEBUG_FLAG)) == 0) {
        printf("PROGRAM ERROR: Too many expressions specified!\n");
        return 1;
    } else {
        int i;
        if (my_strncmp(argv[1], DEBUG_FLAG, my_strlen(DEBUG_FLAG)) == 0) {
            for (i = 2; i < argc; i++) {
                char temp[my_strlen(argv[i])];
                temp[my_strlen(argv[i])] = '\0';
                my_strncpy(temp, argv[i], my_strlen(argv[i]));
                parseExpression(temp, i - 2);
            }
            printArrayDebug();
        } else {
            for (i = 1; i < argc; i++) {
                char temp[my_strlen(argv[i])];
                temp[my_strlen(argv[i])] = '\0';
                my_strncpy(temp, argv[i], my_strlen(argv[i]));
                parseExpression(temp, i - 1);
            }
        }
    }
    // Note 1: If debug flag is presented in any other location besides argv[1], it should be treated as a bad HEX value

    // Note 2: In order to protect our struct array from overflow and undefined behavior,
    // we need to make sure we don't pass in more command-line arguments than necessary.
    // Later on in the course you will learn how to dynamically allocate space for situations like this!

    return 0; // EXIT_SUCCESS
}
