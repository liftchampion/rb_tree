#include <stdlib.h>
#include "ft_map.h"
#include "libft.h"
#include <stdio.h>

#define WHITE_BACK "\x1B[107m\x1B[30m\x1B[7m"
#define WHITE_FRONT "\x1B[0m\x1B[97m"
#define WHITE "\x1B[0m"

#define WHITE_BACK_RED "\x1B[0m\x1B[1m\x1B[31m\x1B[40m"
#define WHITE_BACK_BLACK "\x1B[0m\x1B[1m\x1B[97m\x1B[40m"

void		rb_tree_level_count_helper(t_rb_tree *root, int this_deep, int *max_deep, t_rb_tree *nil)
{
	if (root == nil || root == 0)
	{
		if (this_deep > *max_deep)
			*max_deep = this_deep;
		return ;
	}
	this_deep++;
	rb_tree_level_count_helper(root->left, this_deep, max_deep, nil);
	rb_tree_level_count_helper(root->right, this_deep, max_deep, nil);
}

int			rb_tree_level_count(t_rb_tree *root, t_rb_tree *nil)
{
	int deep;

	deep = 0;
	rb_tree_level_count_helper(root, 0, &deep, nil);
	return (deep);
}

typedef struct
{
	char* item;
	int level;
	t_color color;
}		t_item_info;

int ft_count_empty_nodes(int curr_deep, int max_deep)
{
	int res;

	res = 0;
	while (curr_deep <= max_deep)
	{
		res += ft_pow(2, max_deep - curr_deep);
		curr_deep++;
	}
	return (res);
}

typedef struct
{
	char *first;
	char *next;
}	t_nulls;

void ft_AHUENNO(t_rb_tree *root, int max_deep, int curr_deep, int apply_deep, int *coord, t_item_info *items, t_nulls empty)
{
	int i;
	int l;
	int j;

	if (root == 0)
	{
		i = *coord;
		l = curr_deep;
		*coord += ft_count_empty_nodes(curr_deep, max_deep);
		while (l <= max_deep)
		{
			j = 0;
			while (j < ft_pow(2, l - curr_deep))
			{
				items[i] = (t_item_info){l == curr_deep ? empty.first : empty.next, l, RB_BLACK};
				i++;
				j++;
			}
			l++;
		}
		return ;
	}							//ft_itoa((int)root->key)
	items[*coord] = (t_item_info){ft_itoa((int)root->key), curr_deep, root->color};
	if (!items[*coord].item)
		return ;
	(*coord)++;
	ft_AHUENNO(root->left, max_deep, curr_deep + 1, apply_deep, coord, items, empty);
	ft_AHUENNO(root->right, max_deep, curr_deep + 1, apply_deep, coord, items, empty);
}

void ft_print_tree_items_arr(t_item_info *items, int tree_depth, int max_size)
{
	int tree_width;
	int item_width;
	int deep;
	char *spaces;
	int j;

	int max_width = 0;
	int curr_width = 0;
	int max_int_width = 0;
	int k = 0;
	while (k < max_size)
	{
		if (items[k].level == tree_depth - 1)
			max_width += ft_strlen(items[k].item) + 1;
		k++;
	}

	item_width = 1;
	tree_width = ft_pow(2, tree_depth) * (item_width + 1);
	spaces = (char*)malloc(tree_width + 1);
	if (!spaces)
		return ;
	deep = 0;
	ft_strset(spaces, ' ', tree_width - 1);
	int offset = ft_strlen(spaces);
	while (deep <= tree_depth)
	{
		curr_width = 0;
		size_t c = ft_strlen(spaces) / 2;
		spaces[c] = 0;
		printf(WHITE_BACK "%s", spaces);
		curr_width += ft_strlen(spaces);
		spaces[c] = ' ';
		j = 0;
		while (j < max_size)
		{
			if (items[j].level == deep)
			{
				curr_width += ft_strlen(items[j].item);
				if (items[j].color == RB_RED)
					printf(WHITE_BACK_RED "%s", items[j].item);
				if (items[j].color == RB_BLACK)
					printf(WHITE_BACK_BLACK "%s", items[j].item);

				for (int l = ft_strlen(items[j].item) - 1; l < ft_strlen(spaces); l++)
				{
					printf(WHITE_BACK " ");
					curr_width++;
				}


				//size_t z = ft_strlen(spaces) - (ft_strlen(items[j].item) - 1);
				//spaces[z] = 0;
				//spaces[c] = 0;
				//printf(WHITE_BACK "%s", spaces);
				//curr_width += ft_strlen(spaces);
				//spaces[z] = ' ';
				//spaces[c] = ' ';
			}
			j++;
		}
		for (int l = curr_width; l < max_width; l++)
		{
			printf(WHITE_BACK " ");
		}
		//for (int t = curr_width; t < max_width; t++)
		//	printf(WHITE_BACK " ");
		spaces[c] = 0;
		printf(WHITE "\n");

		int e = 0;
		int g;
		curr_width = 0;
		while (e < c / 2)
		{
			g = 0;
			while(g < tree_width + ft_pow(2, deep))
			{
				if (g % (offset + 1) == c - 1 - e && g < tree_width)
					printf(WHITE_BACK "/");
				else if (g % (offset + 1) == c + 1 + e && g < tree_width)
					printf(WHITE_BACK "\\");
				else
				printf(WHITE_BACK " ");
				g++;
				curr_width++;
			}
			for (int t = curr_width; t < max_width; t++)
				printf(WHITE_BACK " ");
			printf(WHITE "\n");
			e++;
		}
		offset = c;
		deep++;
	}
}

void ft_PIZDATO(t_rb_tree *root, t_rb_tree *nil)
{
	int max_deep;
	int curr_deep;
	int coord;
	t_item_info *items;
	t_nulls nulls;

	if (!root)
	{
		printf(WHITE_BACK "EMPTY TREE");
		printf(WHITE "\n");
		return ;
	}
	nulls = (t_nulls){"#", " "};
	curr_deep = 0;
	max_deep = rb_tree_level_count(root, nil);
	items = (t_item_info*)malloc(sizeof(t_item_info) * ft_count_empty_nodes(0, max_deep));
	if (!items)
		return ;
	ft_bzero(items, sizeof(t_item_info) * ft_count_empty_nodes(0, max_deep));

	while (curr_deep < max_deep)
	{
		coord = 0;
		curr_deep++;
		ft_AHUENNO(root, max_deep, 0, curr_deep, &coord, items, nulls);
	}
	ft_print_tree_items_arr(items, max_deep, ft_count_empty_nodes(0, max_deep));
}