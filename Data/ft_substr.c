/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgishyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 23:49:18 by vgishyan          #+#    #+#             */
/*   Updated: 2021/06/03 23:49:19 by vgishyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char* ft_substr(char const* string, unsigned int start, size_t len)
{
    char* new_string;
    size_t	length;
    size_t	index;

    if (is_null(string))
	return NULL;
    length = ft_strlen(string);
    if (get_dynamic_memory(new_string, (len * sizeof(char)) + 1))
	return NULL;
    index = 0;
    while (index < len && index + start < length)
    {
	new_string[index] = string[start + index];
	index++;
    }
    new_string[index] = '\0';
    return (new_string);
}
