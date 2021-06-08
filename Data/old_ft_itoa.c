/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgishyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 23:35:18 by vgishyan          #+#    #+#             */
/*   Updated: 2021/06/03 23:37:11 by vgishyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	itoa_compute_number_size(long number)
{
	size_t	size;

	size = (number < 0 ? 1 : 0);
	while (1)
	{
		number /= 10;
		size++;
		if (number == 0)
			break;
	}
	return (size);
}
char* 		ft_itoa(int n)
{
	long	number;
	char* array;
	size_t	size;

	number = n;
	size = itoa_compute_number_size(n);
	if (get_dynamic_memory(array, (size + 1) * sizeof(char)))
		return NULL;
	if (number < 0)
	{
		array[0] = '-';
		number *= -1;
	}
	array[size] = '\0';
	while (1)
	{
		array[size - 1] = (number % 10) + '0';
		number /= 10;
		--size;
		if (number == 0)
			break;
	}
	return (array);
}
