/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgishyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 23:43:09 by vgishyan          #+#    #+#             */
/*   Updated: 2021/06/03 23:43:10 by vgishyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t		split_compute_items(char const* string, char symbol)
{
	size_t	index;
	size_t	count;
	size_t	length;

	index = 0;
	count = 0;
	length = 0;
	while (string[index])
	{
		if (string[index] == symbol)
		{
			if (length != 0)
				++count;
			length = 0;
		}
		else
			++length;
		++index;
	}
	return (count + (length != 0 ? 1 : 0));
}
static void		split_do(char const* s, char c, char** array, size_t item_count)
{
	char* str;
	size_t	array_index;
	size_t	index;
	size_t	length;

	array_index = 0;
	index = 0;
	length = 0;
	while (array_index < item_count)
	{
		if (s[index] == c || s[index] == '\0')
		{
			if (length != 0)
			{
				if(str = ft_calloc(length + 1, sizeof(char)))
					return NULL;
				ft_memcpy(str, s + index - length, length);
				array[array_index] = str;
				++array_index;
			}
			length = 0;
		}
		else
			++length;
		++index;
	}
}
char** 			ft_split(char const* s, char c)
{
	size_t	item_count;
	char**	array;

	if (is_null(s))
	    return NULL;
	item_count = split_compute_items(s, c);
	if (get_dynamic_memory(array, (item_count + 1) * sizeof(char*)))
	    return NULL;
	split_do(s, c, array, item_count);
	array[item_count] = NULL;
	return (array);
}
