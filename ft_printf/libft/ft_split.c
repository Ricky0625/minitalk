/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 11:58:48 by wricky-t          #+#    #+#             */
/*   Updated: 2022/06/08 17:19:35 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// allocates and returns an array of strings obtained by splitting 's' using
// the character 'c' as a delimiter.
// the array must end with a NULL pointer.

#include "libft.h"

// count how many substrings in a string
// logic:
// traversing thru the str while it's not \0
// if the current character is not the delimeter, detected set as 1, meaning
// it detected the start of a string. continue to loop until encounter
// delimeter, if detected is set to 1, count++ & reset detected to 0
// there are some cases where the current char is delimeter and detected is 0
// for example, the delimeter appears at the start of the string
// if the next character of the current character is \0. meaning we are at
// the end of the string, hence, count++ as well (while stops at \0)
static int	count_string(char const *str, char c)
{
	int	detected;
	int	count;

	detected = 0;
	count = 0;
	while (*str)
	{
		if (*str != c)
			detected = 1;
		if (*str == c || *(str + 1) == '\0')
		{
			if (detected)
			{
				count++;
				detected = 0;
			}
		}
		str++;
	}
	return (count);
}

// **tab = a pointer to an array of string(an array of char)
// traversing thru s while it's not \0
// if the current char is not delimeter, \0 and len not 0, increment S's address
// ++len will always be true, it's used to count the len of the substr
// once the inner loop encounter delimeter, \0, loop stops
// at nth index of tab, set it's value to result of ft_substr
// reset len to 0 afterward, so that we can count the length of the next substr
// the last element of tab should be NULL
char	**ft_split(char const *s, char c)
{
	int		len;
	int		index;
	char	**tab;

	if (!s)
		return (NULL);
	len = 0;
	index = 0;
	tab = malloc(sizeof(char *) * (count_string(s, c) + 1));
	if (tab == NULL)
		return (NULL);
	while (*s)
	{
		if (*s != c)
		{
			while (*s != c && *s && ++len)
				s++;
			tab[index++] = ft_substr((s - len), 0, len);
			len = 0;
		}
		else
			s++;
	}
	tab[index] = NULL;
	return (tab);
}
