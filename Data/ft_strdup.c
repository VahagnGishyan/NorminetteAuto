/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgishyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 23:45:28 by vgishyan          #+#    #+#             */
/*   Updated: 2021/06/03 23:45:31 by vgishyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Libft.h"

char* ft_strdup(const char* string)
{
	size_t	length;
	char	*duplicate;

	length = ft_strlen(string);
	duplicate = (char*)(ft_calloc(length + 1, sizeof(char)));
	if (duplicate == NULL)
		return NULL;
	ft_memcpy(duplicate, string, length);
	duplicate[length] = '\0';
	return (duplicate);
}
