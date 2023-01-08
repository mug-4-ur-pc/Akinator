/*!
 * @file
 * @brief An Akinator implementation.
 */

#include "akinator.h"
#include "bintree.h"
#include "utilities.h"

#include <assert.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <linux/limits.h>
#include <festival/festival.h>




/*!
 * @brief Ask user about guessed object and add it.
 */
static void ak_ask_to_add
(
	bintree_t* tree, /*!< [in,out] Akinator tree.                            */
	bintree_t  node  /*!< [in]     an object which was given by Akinator.    */
)
{
	ak_print("Ладно. Я проиграл");
	puts(" :((");
	ak_print_in_line("А что же это было? ");
	char obj_name[AK_MAX_OBJ_LENGTH + 1] = {0};
	if (!fgets(obj_name, AK_MAX_OBJ_LENGTH, stdin))
	{
		ak_print("Не могу прочитать твой ответ. Пора заканчивать.");
		return;
	}

	obj_name[strlen(obj_name) - 1] = '\0';
	ak_print_in_line("Помоги мне узнать, что такое ");
	ak_print(obj_name);
	ak_print("Дополни предложение.");
	ak_print_in_line(obj_name);
	ak_print_in_line(", в отличие от ");
	ak_print_in_line(node->value);
	fputs(", не", stdout);
	
	char prop_name[AK_MAX_OBJ_LENGTH] = {0};
	if (!fgets(prop_name, AK_MAX_OBJ_LENGTH, stdin))
	{
		ak_print("Не могу прочитать твой ответ. Пора заканчивать.");
		return;
	}

	prop_name[strlen(prop_name) - 1] = '\0';
	bintree_t prop = bintree_create(prop_name);
	bintree_add_left(prop, obj_name);
	bintree_insert_right(tree, node, prop);
	ak_print("Отлично! Я запомнил.");
}

/*!
 * @brief Ask user if given property correct and get next direction.
 *
 * @return Direction.
 */
static bintree_direction_t ak_get_direction
(
	const bintree_t prop /*!< [in] an object.                                 */
)
{
	for (size_t i = 0; i < AK_ATTEMPTS_TO_GET_ANSWER; ++i)
	{
		ak_print_in_line("Загаданный обхект ");
		ak_print_in_line(prop->value);
		puts("?");
		int choice = ak_get_choice(NULL, 3, "Да", "Нет", "Выход");

		switch (choice)
		{
			case 1:  return BINTREE_RIGHT;
			case 2:  return BINTREE_LEFT;
			case 3:  return BINTREE_STAY;
			default: break;
		}
		
		if (i + 1 < AK_ATTEMPTS_TO_GET_ANSWER)
			ak_print("Ты ввёл какую-то фигню. Даваф ещё раз.");
	}

	ak_print("Ну всё! Ты мне надоел. Я заканчиваю.");
	return BINTREE_STAY;
}

/*!
 * @brief Print info about object recursively.
 */
static void ak_define_recursive_print
(
	const bintree_t prop, /*!< [in] object's property.                       */
	bool            last  /*!< [in] is it the last property.                 */
)
{
	if (!prop->parent)
		return;

	ak_define_recursive_print(prop->parent, false);

	if (prop->parent->left == prop)
		ak_print_in_line("не");
	ak_print_in_line(prop->parent->value);
	fputs((last) ? ".\n" : ", ", stdout);
}

/*!
 * @brief Print general properties of two objects.
 */
static void ak_compare_print_general
(
	const bintree_t            tree,   /*!< [in] Akinator tree.              */
	const bintree_t            obj1,   /*!< [in] first object.               */
	const bintree_t            obj2,   /*!< [in] second object.              */
	const bintree_direction_t* way1,   /*!< [in] way from root to
	                                             first object.               */
	size_t                     depth1, /*!< [in] depth of first object
	                                             in tree.                    */
	const bintree_direction_t* way2,   /*!< [in] way from root to
	                                             second object.              */
	size_t                     depth2  /*!< [in] depth of second object
	                                             in tree.                    */
)
{
	ak_print_in_line(obj1->value);
	ak_print_in_line(" и ");
	ak_print_in_line(obj2->value);

	if (way1[0] != way2[0])
	{
		ak_print(" ничем не похожи друг на друга.");
		return;
	}
	else
		ak_print_in_line(" похожи тем, что они оба ");

	size_t min_depth = (depth1 < depth2) ? depth1 : depth2;

	bintree_t property = tree;
	size_t i = 0;
	while (true)
	{
		if (way1[i] == BINTREE_LEFT)
			ak_print_in_line("не");
		ak_print_in_line(property->value);
		++i;
		if (way1[i] != way2[i] || i >= min_depth)
			break;

		fputs(", ", stdout);
		property = bintree_next(property, way1[i]);
	}
	puts(".");
}

/*!
 * @brief Print properties from given to the last one.
 */
static void ak_print_props_from
(
	const bintree_t            prop,  /*!< [in] given property.              */
	size_t                     index, /*!< [in] number of given property.    */
	const bintree_direction_t* way,   /*!< [in] array which contains way
	                                            to object.                   */
	size_t                     depth  /*!< [in] size of way.                 */
)
{
	bintree_t curr_prop = prop;
	for (size_t i = index; i < depth; ++i)
	{
		if (way[i] == BINTREE_LEFT)
			ak_print_in_line("не");

		ak_print_in_line(curr_prop->value);
		fputs((i + 1 < depth) ? ", " : ".\n", stdout);
		curr_prop = bintree_next(curr_prop, way[i]);
	}
}

/*!
* @brief Print different properties of two objects.
*/
static void ak_compare_print_different
(
	const bintree_t            tree,   /*!< [in] Akinator tree.              */
	const bintree_direction_t* way1,   /*!< [in] way from root to
	                                             first object.               */
	size_t                     depth1, /*!< [in] depth of first object
	                                             in tree.                    */
	const bintree_direction_t* way2,   /*!< [in] way from root to
	                                             second object.              */
	size_t                     depth2  /*!< [in] depth of second object
	                                             in tree.                    */
)
{
	size_t    index = 0;
	bintree_t prop  = tree;
	while (way1[index] == way2[index])
		prop = bintree_next(prop, way1[index++]);

	ak_print_in_line("Перыый объект, в отличие от второго, ");
	ak_print_props_from(prop, index, way1, depth1);
	ak_print_in_line("Второй же, в свою очередь ");
	ak_print_props_from(prop, index, way2, depth2);

}




bintree_t ak_get_tree (void)
{
	ak_print("Привет, мой сладкий козлик) Я - Акинатор! Давай начнём.\n\n");

	bool create_new_tree = false;
	for (size_t i = 0; i < AK_ATTEMPTS_TO_GET_ANSWER; ++i)
	{
		int choice = ak_get_choice("Выбери нужный вариант", 2,
				"Создать новую базу", "Открыть существующую базу");

		char fname[PATH_MAX] = {0};
		switch (choice)
		{
			case 1:
				create_new_tree = true;
				break;

			case 2:
				ak_print_in_line("Введи имя файла с базой: ");
				scanf("%[^\n]", fname);
				FILE* fp = fopen(fname, "r");
				if (fp)
				{
					ak_print("Читаю таблицу из файла...\n");
					bintree_t tree = bintree_read(fp);
					fclose(fp);
					if (tree)
						return tree;

					ak_print("Файл имеет неверный формат.");
				}
				else
				{
					ak_print("Не могу открыть файл с базой."
						"Может его и нет вовсе?");
				}
				break;
		}

		if (create_new_tree)
			break;

		if (i != AK_ATTEMPTS_TO_GET_ANSWER - 1)
			ak_print("Ничего страшного. Попробуй снова...\n");
	}

	ak_print("Создаю пустую таблицу...\n");
	return bintree_create("неизвестный объект");
}


int ak_get_choice (const char* invitation, size_t n_choices, ...)
{
	if (invitation)
	{
		ak_print(invitation);
		putchar(':');
	}

	va_list va;
	va_start(va, n_choices);
	for (size_t i = 1; i <= n_choices; ++i)
	{
		printf("\t%zd) ", i);
		ak_print_in_line(va_arg(va, const char*));
		fputs(";\n", stdout);
	}

	va_end(va);
	ak_print_in_line("\nВведи число: ");
	
	int  num    = -1;
	char tmp_ch = '\0';
	scanf("%d%c", &num, &tmp_ch);
	if (tmp_ch != '\n')
		clear_buffer(stdin);

	return num;
}


void ak_print (const char* msg)
{
	assert (msg);

	ak_print_in_line(msg);
	putchar('\n');
}


void ak_print_in_line (const char* msg)
{
	assert (msg);

	static bool need_init = true;
	if (need_init)
	{
		need_init = false;
		festival_initialize(1, FESTIVAL_HEAP_SIZE);
		festival_init_lang("russian");
	}

	fputs(msg, stdout);
	fflush(stdout);
	
	while (*msg && (ispunct(*msg) || isspace(*msg))) ++msg;
	if (*msg)
		festival_say_text(msg);
}


enum ak_mode ak_get_mode (void)
{
	putchar('\n');
	for (size_t i = 0; i < AK_ATTEMPTS_TO_GET_ANSWER; ++i)
	{
		int choice = ak_get_choice("Выбери режим", 5,
			"Режим определений", "Режим сравнения", "Угадать объект",
			"Сохранить базу", "Выйти");

		switch (choice)
		{
			case 1: return AK_MODE_DEFINITION;
			case 2: return AK_MODE_COMPIRISON;
			case 3: return AK_MODE_GUESSING;
			case 4: return AK_MODE_SAVE;
			case 5: return AK_MODE_EXIT;
		}

		if (i != AK_ATTEMPTS_TO_GET_ANSWER - 1)
			ak_print("Такого режима нет. Попробуй ещё.");
	}

	ak_print("Ты так и не смог выбрать режим. Я завершаю работу.");
	return AK_MODE_EXIT;
}


bintree_t ak_get_object (const bintree_t tree)
{
	assert (tree);

	char str[AK_MAX_OBJ_LENGTH + 1] = {0};
	ak_print_in_line("Введи имя объекта: ");
	if (!fgets(str, AK_MAX_OBJ_LENGTH, stdin))
	{
		ak_print("Не могу прочитать имя объекта.");
		return NULL;
	}

	str[strlen(str) - 1] = '\0';

	bintree_t obj = bintree_find(tree, str);

	// Object must be a leaf.
	return (obj && obj->left) ? NULL : obj;
}


void ak_define (const bintree_t obj)
{
	if (obj && obj->parent)
	{
		ak_print_in_line("Вот что известно про ");
		ak_print_in_line(obj->value);
		puts(".");
		ak_print_in_line("Это ");
		ak_define_recursive_print(obj, true);
	}
	else
	{
		ak_print_in_line("Про ");
		ak_print_in_line((obj) ? obj->value : "этот объект");
		ak_print(" ничего не известно.\n");
	}
}


void ak_compare (const bintree_t tree,
                 const bintree_t obj1, const bintree_t obj2)
{
	putchar('\n');
	if (obj1 == obj2)
	{
		if (!obj1)
		{
			ak_print("Про оба объекта ничего не известно.");
			return;
		}

		ak_print_in_line(obj1->value);
		ak_print_in_line(" и ");
		ak_print_in_line(obj2->value);
		ak_print_in_line("один и тот же объект. ");
		return;
	}
	
	if (!obj1)
	{
		ak_print("Про первый объект ничего не известно.");
		ak_define(obj2);
		return;
	}

	if (!obj2)
	{
		ak_define(obj1);
		ak_print("Про второй объект ничего не известно.");
		return;
	}

	size_t depth1 = 0;
	size_t depth2 = 0;

	bintree_direction_t* way1 = bintree_get_way(obj1, &depth1);
	bintree_direction_t* way2 = bintree_get_way(obj2, &depth2);

	if (!way1 || !way2)
	{
		ak_print("Ошибка выделения памяти. Продолжение работы невозможно.");
		free(way1);
		free(way2);
		return;
	}

	ak_compare_print_general(tree, obj1, obj2, way1, depth1, way2, depth2);
	ak_compare_print_different(tree, way1, depth1, way2, depth2);
	putchar('\n');

	free(way1);
	free(way2);
}


bool ak_guess (bintree_t* tree)
{
	assert (tree);

	putchar('\n');
	bintree_t           node = *tree;
	bintree_direction_t dir  = BINTREE_STAY;
	while (true)
	{
		if (!node->left)
		{
			bintree_direction_t guessed = ak_get_direction(node);
			if (guessed == BINTREE_LEFT)
				ak_ask_to_add(tree, node);
			else if (guessed == BINTREE_RIGHT)
				ak_print("Я сразу знал, что я выиграю))");

			return guessed == BINTREE_RIGHT;
		}

		if ((dir = ak_get_direction(node)) == BINTREE_STAY)
			return false;

		node = bintree_next(node, dir);
	}
}


void ak_save_tree (const bintree_t tree)
{
	assert (tree);

	ak_print_in_line("Введи имя файла, куда сохранится база: ");
	char fname[PATH_MAX] = {0};
	fgets(fname, PATH_MAX - 1, stdin);
	fname[strlen(fname) - 1] = '\0';

	FILE* fp = fopen(fname, "w");
	bintree_print(tree, fp);
	fclose(fp);
}
