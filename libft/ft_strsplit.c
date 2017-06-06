/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narajaon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 09:22:12 by narajaon          #+#    #+#             */
/*   Updated: 2017/04/14 11:17:37 by narajaon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		nb_word(char const *s, char c)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (s[i] == c)
		i++;
	while (s[i])
	{
		if (s[i] != c)
			count++;
		while ((s[i] != c) && s[i])
			i++;
		if (!s[i])
			break ;
		i++;
	}
	return (count);
}

static int		word_len(char const *str, char c)
{
	int len;

	len = 0;
	while (str[len] != c && str[len])
		len++;
	return (len);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**tab;
	int		i;
	int		j;
	int		jc;
	int		word;

	i = 0;
	j = 0;
	word = nb_word(s, c);
	if (!(tab = (char **)malloc(sizeof(char *) * (word + 1))))
		return (NULL);
	while (word)
	{
		jc = 0;
		while (s[i] == c)
			i++;
		tab[j] = (char *)malloc(sizeof(char *) * (word_len(s + i, c) + 1));
		while ((s[i] != c) && s[i])
			tab[j][jc++] = s[i++];
		tab[j][jc] = '\0';
		j++;
		word--;
	}
	tab[j] = 0;
	return (tab);
}
