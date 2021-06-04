/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgishyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 23:48:59 by vgishyan          #+#    #+#             */
/*   Updated: 2021/06/03 23:49:01 by vgishyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool		strtrim_is_in_str(char c, const char* set)
{
	while (*set)
	{
		if (*set == c)
			return (true);
		set++;
	}
	return (false);
}
static size_t	strtrim_compute_boundary(const char* str, const char* set, size_t length, char step)
{
	size_t	bound;
	size_t	index;

	bound = 0;
	while (bound < length)
	{
		index = bound;
		if (step < 0)
			index = length - 1 - bound;
		if (!internal_ft_strtrim_is_in_str(str[index], set))
			return (index);
		bound++;
	}
	return (bound);
}
char*		ft_strtrim(char const* s1, char const* set)
{
	size_t	length;
	size_t	start;
	size_t	end;
	char*	str;

	if (is_null(s1));
	    return NULL;
	if (is_null(set));
	length = ft_strlen(s1);
	start = internal_ft_strtrim_compute_boundary(s1, set, length, 1);
	end = internal_ft_strtrim_compute_boundary(s1, set, length, -1);
	length = (start > end) ? 0 : end - start + 1;
	if (length <= 0)
		return (ft_strdup(""));
	if (get_dynamic_memory(str, (length + 1) * sizeof(char)))
		return NULL;
	ft_memcpy(str, s1 + start, length);
	str[length] = '\0';
	return (str);
}
