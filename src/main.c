/*!
 * @file
 * @brief This is the main file of Akinator program.
 */

#include "akinator.h"


int main (void)
{
	bool      exit_mode = false;
	bintree_t tree      = ak_get_tree();
	bintree_t obj1      = NULL;
	bintree_t obj2      = NULL;

	while (!exit_mode)
	{
		switch (ak_get_mode())
		{
			case AK_MODE_DEFINITION:
				obj1 = ak_get_object(tree);
				ak_define(obj1);
				break;

			case AK_MODE_COMPIRISON:
				obj1 = ak_get_object(tree);
				obj2 = ak_get_object(tree);
				ak_compare(tree, obj1, obj2);
				break;

			case AK_MODE_GUESSING:
				ak_guess(&tree);
				break;

			case AK_MODE_SAVE:
				ak_save_tree(tree);
				break;

			case AK_MODE_EXIT:
				exit_mode = true;
				break;

			default:
				fputs("CRITICAL ERROR: unknown Akinator mode...", stderr);
				exit_mode = true;
		}
	}

	ak_print("Спасибо за игру!");
	return 0;
}
