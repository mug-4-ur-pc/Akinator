/*!
 * @file
 * @brief This is a header file with binary tree.
 */


#ifndef BINTREE_H_
#define BINTREE_H_

#include <stdio.h>
#include <stdbool.h>

#include "bintree.config.h"




/*!
 * @brief Node of a binary tree.
 */
typedef struct bintree_node
{
	struct bintree_node* left;   /*!< left child.                            */
	struct bintree_node* right;  /*!< right child.                           */
	struct bintree_node* parent; /*!< parent node.                           */
	BINTREE_VALUE_T      value; /*!< value of node.                          */
}
*bintree_t;




/*!
 * @brief Create new node.
 *
 * @note Don't forget to free memory using bintree_destroy() function.
 *
 * @return Created node. If error occurred it returns NULL.
 */
bintree_t bintree_create
(
	BINTREE_VALUE_T val
);

/*!
 * @brief Destroy bintree.
 *
 * @return NULL.
 */
bintree_t bintree_destroy
(
	bintree_t head /*!< [in,out] Head of binary tree.                        */
);

/*!
 * @brief Create and set the left child to new node.
 *
 * @node If node already has child node it will be freed.
 *
 * @return Child node. If an error occurred it returns NULL.
 */
bintree_t bintree_add_left
(
	bintree_t       node, /*!< [in,out] node of binary tree.                 */
	BINTREE_VALUE_T value /*!< [in]     value of added node.                 */
);

/*!
 * @brief Hook node as left child.
 *
 * @node If node already has child node it will be destroyed.
 *
 * @return Child node. If an error occurred it returns NULL.
 */
bintree_t bintree_hook_left
(
	bintree_t node,       /*!< [in,out] node of binary tree.                 */
	bintree_t for_hooking /*!< [in]     node for hooking.                    */
);

/*!
 * @brief Unhook left child.
 *
 * @return Pointer to unhooked node.
 */
bintree_t bintree_unhook_left
(
	bintree_t  node /*!< [in,out] node of binary tree.                       */
);

/*!
 * @brief Create and set the right child to new node.
 *
 * @node If node already has child node it will be freed.
 *
 * @return Child node. If an error occurred it returns NULL.
 */
bintree_t bintree_add_right
(
	bintree_t       node, /*!< [in,out] node of binary tree.                 */
	BINTREE_VALUE_T value /*!< [in]     value of added node.                 */
);

/*!
 * @brief Hook node as right child.
 *
 * @node If node already has child node it will be destroyed.
 *
 * @return Child node. If an error occurred it returns NULL.
 */
bintree_t bintree_hook_right
(
	bintree_t node,       /*!< [in,out] node of binary tree.                 */
	bintree_t for_hooking /*!< [in]     node for hooking.                    */
);

/*!
 * @brief Unhook right child.
 *
 * @return Pointer to unhooked node.
 */
bintree_t bintree_unhook_right
(
	bintree_t  node /*!< [in,out] node of binary tree.                       */
);

/*!
 * @brief Print binary tree.
 */
void bintree_print
(
 	const bintree_t head,  /*!< [in]     binary tree.                        */
	FILE*           output /*!< [in,out] output stream.                      */
);

/*!
 * @brief Dump binary tree to .dot file and create .png file using GraphViz.
 */
#define bintree_dump(BINTREE_)                                                \
	bintree_dump_func_((BINTREE_), #BINTREE_, __LINE__, __func__, __FILE__)

/*!
 * @brief Dump binary tree to .dot file and create .png file using GraphViz.
 */
void bintree_dump_func_
(
 	const bintree_t head,      /*!< [in] binary tree.                        */
	const char*     tree_name, /*!< [in] name of the binary tree,            */
	size_t          line,      /*!< [in] line where dump function was called.*/
	const char*     func,      /*!< [in] function where the dump function
	                                      was called.                        */
	const char*     file       /*!< [in] file where dump function was called.*/
);

/*!
 * @brief Read binary tree.
 *
 * @return Binary tree. IF an error occurred it returns NULL.
 */
bintree_t bintree_read
(
	FILE*  input /*!< [in] input stream.                                     */
);

/*!
 * @brief Recursively deserialize binary tree from string.
 *
 * @return Binary tree. IF an error occurred it returns NULL.
 */
bintree_t bintree_deserialize
(
	const char* buff /*!< [in] input string.                                 */
);

/*!
 * @brief Find an element in binary tree.
 *
 * @return Node with given element
 * or NULL if tree doesn't contain given element.
 */
bintree_t bintree_find
(
	const bintree_t head, /*!< [in] binary tree.                             */
	BINTREE_VALUE_T elem  /*!< [in] given element.                           */
);
/*!
 * @brief Get way to the particular node.
 *
 * In returned array false means that the way goes to left child.
 *
 * @note Don't forget to free returned array.
 *
 * @return array with directions.
 */
bool* bintree_get_way
(
	const bintree_t node, /*!< [in]  binary tree node.                       */
	size_t*         len   /*!< [out] variable in which length of the way will
	                                 assigned.                               */
);

/*!
 * @brief Get height of binary subtree 
 * where given node is a leaf.
 *
 * @return Height of subtree.
 */
size_t bintree_get_height
(
	const bintree_t node /*!< [in] given node.                               */
);




#endif // undefined BINTREE_H_
