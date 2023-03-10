/*!
 * @file
 * @brief An implementation of different helpful functions.
 */

#include "utilities.h"

#include <assert.h>
#include <stdlib.h>




void print_n_chars (char ch, size_t n, FILE* output)
{
	assert (output);

	for (size_t i = 0; i < n; ++i)
		putc(ch, output);
}


char* read_string (FILE* input, size_t* size)
{
	assert (input);
	assert (size);

	const size_t CHUNK_SIZE = 10000;
	size_t len      = 0;
	size_t was_read = 0;
	char* str = (char*) calloc(CHUNK_SIZE, sizeof *str);
	if (!str)
	{
		*size = 0;
		return NULL;
	}

	while ((was_read = fread(str + len, 1, CHUNK_SIZE, input)) == CHUNK_SIZE)
	{
		len += CHUNK_SIZE;
		char* realloc_check = (char*) realloc(str, (len + CHUNK_SIZE)
		                                           * sizeof *str);
		
		if (!realloc_check)
		{
			if (fgetc(input) != EOF)
			{
				*size = 0;
				free(str);
				return NULL;
			}

			break;
		}

		str = realloc_check;
	}

	len   += was_read;
	*size  = len;

	return str;
}


void clear_buffer (FILE* stream)
{
	assert (stream);

	while (getc(stream) != '\n')
		continue;
}
