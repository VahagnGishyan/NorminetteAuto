/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgishyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 23:32:56 by vgishyan          #+#    #+#             */
/*   Updated: 2021/06/03 23:33:00 by vgishyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void*		ft_calloc(size_t count, size_t size)
{
	void* array;
	size_t	required;

	required = count * size;
	array = (void*)malloc(required);
	ft_memset(array, 0, required);
	return (array);
}
