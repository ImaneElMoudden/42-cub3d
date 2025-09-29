/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamachi <klamachi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 13:14:52 by klamachi          #+#    #+#             */
/*   Updated: 2025/09/29 13:14:53 by klamachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static t_malloc	*create_node(void *ptr, size_t size)
{
	t_malloc	*node;

	node = malloc(sizeof(t_malloc));
	if (!node)
		clean(NULL);
	node->ptr = ptr;
	node->size = size;
	node->next = NULL;
	return (node);
}

static void	add_node(t_malloc *node)
{
	t_malloc	*tmp;

	if (!game_data()->mallc)
	{
		game_data()->mallc = node;
		return ;
	}
	tmp = game_data()->mallc;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = node;
}

void	*safe_malloc(size_t size)
{
	void		*ptr;
	t_malloc	*node;

	ptr = malloc(size);
	if (!ptr)
		clean(NULL);
	node = create_node(ptr, size);
	add_node(node);
	return (ptr);
}

void	safe_free(void)
{
	t_malloc	*curr;
	t_malloc	*next;

	curr = game_data()->mallc;
	while (curr)
	{
		next = curr->next;
		free(curr->ptr);
		free(curr);
		curr = next;
	}
	game_data()->mallc = NULL;
}
