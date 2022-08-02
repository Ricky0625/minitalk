/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 11:31:07 by wricky-t          #+#    #+#             */
/*   Updated: 2022/06/08 17:27:44 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// s1: the string to be trimmed
// set: the reference set of characters to trim (it's a set of char not string)

// check from start first, then check from back (pincer movement)

#include "libft.h"

// if found then 1, not found 0
static int	is_in_set(char c, char const *set)
{
	int	i;

	i = 0;
	while (*(set + i))
	{
		if (*(set + i) == c)
			return (1);
		i++;
	}
	return (0);
}

// pass in the start index and end index after trimmed
// if end index - start index less than 0, meaning there is no occurrence of
// set in the string, then just return 0. bcos no char to be copied
// if end index - start index more than or equal zero, meaning the string
// has been trimmed, then just return total + 1
// why plus 1: we are using index to calculate, index starts from 0
// so in order to get the length of the string, we need to plus 1 afterward

static int	get_size(int s_index, int e_index)
{
	int	total;

	total = e_index - s_index;
	if (total < 0)
		return (0);
	return (total + 1);
}

// loop condition: while s1 not null, and the current character is still in set
// the loop stops when it encounters the character that is not in the set
// trimmed len + 1, the 1 is for null
char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	len;
	int		s_i;
	int		e_i;
	int		trimmed_len;
	char	*out;

	if (!s1 || !set)
		return (NULL);
	len = ft_strlen(s1);
	s_i = 0;
	while (*(s1 + s_i) && is_in_set(*(s1 + s_i), set) == 1)
		s_i++;
	e_i = len - 1;
	while (*(s1 + e_i) && is_in_set(*(s1 + e_i), set) == 1)
		e_i--;
	trimmed_len = get_size(s_i, e_i);
	out = ft_substr(s1, s_i, trimmed_len);
	return (out);
}
