/*!
 * @file
 * @bruef A header file which includes different helpful functions.
 */

#ifndef UTILITIES_H_
#define UTILITIES_H_


#include <stdio.h>
#include <stdbool.h>




/*!
 * @brief Print character n times.
 */
void print_n_chars
(
	char   ch,    /*!< [in]     printed character.                           */
	size_t n,     /*!< [in]     amount of printed char.                      */
	FILE*  output /*!< [in,out] output stream.                               */
);

/*!
 * @brief Read string with allocating memory for it.
 *
 * @note Don't forget to free memory.
 *
 * @return String or NULL if an error occurred.
 */
char* read_string
(
	FILE*   input, /*!< [in]  input stream.                                  */
	size_t* size   /*!< [out] pointer to variable where the read string length
	                          will be placed.                                */
);

/*!
 * @brief Clear buffer by reading 
 * until '\n' will be encountered.
 */
void clear_buffer
(
	FILE* stream /*!< [in,out] input stream.                                 */
);




#endif // Undefined UTILITIES_H_
