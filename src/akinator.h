/*!
 * @file
 * @brief An Akinator header file.
 */

#ifndef AKINATOR_H_
#define AKINATOR_H_

#include "bintree.h"




/*!
 * @brief Attempts to get correct answer from user.
 */
#define AK_ATTEMPTS_TO_GET_ANSWER ((size_t) 3)

/*!
 * @brief Max length of given object.
 */
#define MAX_OBJ_LENGTH ((size_t) 1024)

/*!
 * @brief List of Akinator modes.
 */
enum ak_mode
{
	AK_MODE_DEFINITION = 1,
	AK_MODE_COMPIRISON = 2,
	AK_MODE_GUESSING   = 3,
	AK_MODE_SAVE       = 4,
	AK_MODE_EXIT       = 5,
};




/*!
 * @brief Get Akinator tree.
 *
 * @return Akinator binary tree.
 */
bintree_t ak_get_tree (void);

/*!
 * @brief Get Akinator mode.
 *
 * @return Akinator mode.
 */
enum ak_mode ak_get_mode (void);

/*!
 * @brief Get object.
 *
 * @return An object or NULL if given object doesn't exist in Akinator tree.
 */
bintree_t ak_get_object
(
 	const bintree_t tree /*!< [in] Akinator tree.                            */
);

/*!
 * @brief Give definition of given object.
 */
void ak_define
(
	const bintree_t obj /*!< [in] given object.                              */
);

/*!
 * @brief Compare two objects.
 */
void ak_compare
(
 	const bintree_t tree, /*!< [in] Akinator tree.                           */
	const bintree_t obj1, /*!< [in] first object.                            */
	const bintree_t obj2  /*!< [in] second object.                           */
);

/*!
 * @brief Try to guess an object.
 *
 * If guessing failed ask to add new object.
 *
 * @return Success of this attempt.
 */
bool ak_guess
(
	bintree_t tree /*!< [in,out] Akinator tree.                              */
);

/*!
 * @brief Save Akinator tree.
 */
void ak_save_tree
(
	const bintree_t tree /*!< [in] Akinator tree.                            */
);

/*!
 * @brief Print message with '\n' at the end on console with speech.
 */
void ak_print
(
	const char* msg /*!< [in] message which will be printed.                 */
);

/*!
 * @brief Print message on console with speech.
 */
void ak_print_in_line
(
	const char* msg /*!< [in] message which will be printed.                 */
);

/*!
 * @brief Get a choice from user.
 *
 * @return Given choice.
 */
int ak_get_choice
(
	const char* invitation, /*!< [in] an invitation message.                 */
	size_t      n_choices,  /*!< [in] amount of choices.                     */
	                        /*!< [in] strings wich choice descriptions.      */
	...
);




#endif // Undefined AKINATOR_H_
