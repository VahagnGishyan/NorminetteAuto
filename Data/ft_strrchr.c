/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgishyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 23:48:32 by vgishyan          #+#    #+#             */
/*   Updated: 2021/06/03 23:48:35 by vgishyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Libft.h"

char*		ft_strrchr(const char* string, int symbol)
{
	char*	last_ptr;

	last_ptr = NULL;
	while (*string)
	{
		if (*string == symbol)
			last_ptr = (char*)(string);
		++string;
	}
	return (last_ptr);
}
