/*!
 * @file
 * @brief File with binary tree configuration.
 *
 * Change it to configure your own binary tree.
 */


/*!
 * @brief Type of binary tree element.
 */
#define BINTREE_VALUE_T char*

/*!
 * @brief Copy function for binary tree elements.
 */
#define BINTREE_VALUE_COPY(NODE_VALUE_, VALUE_) \
do \
{ \
	size_t len = strlen(VALUE_) + 1; \
	NODE_VALUE_ = (BINTREE_VALUE_T)  calloc(1, len); \
	if (NODE_VALUE_) \
		strcpy(NODE_VALUE_, VALUE_); \
} \
while (false)

/*!
 *
 */
#define BINTREE_VALUE_DESTROY(VALUE_) free(VALUE_)

/*!
 * @brief Function which prints a tree element.
 */
#define BINTREE_VALUE_PRINT(VALUE_, STREAM_) \
do \
{ \
	fputs(VALUE_, STREAM_); \
} \
while (false)

/*!
 * @brief Function which parses value from input string.
 */
#define BINTREE_VALUE_PARSE(VALUE_, STR_, STRLEN_) \
do \
{ \
	VALUE_ = (BINTREE_VALUE_T) calloc(STRLEN_ + 1, sizeof *VALUE_); \
	if (VALUE_) \
		strcpy(VALUE_, STR_); \
} \
while (false)

/*!
 * @brief Function which returns true if elements are equal else false.
 */
#define BINTREE_VALUE_EQUAL(NODE_VALUE_, VALUE_) \
	(strcmp(NODE_VALUE_, VALUE_) == 0)

/*!
 * @brief Max file name of binary tree dump.
 */
#define BINTREE_MAX_FNAME ((size_t) 8192)
