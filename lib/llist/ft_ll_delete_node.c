/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ll_delete_node.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzarins <kzarins@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 14:03:31 by kzarins           #+#    #+#             */
/*   Updated: 2025/01/31 14:04:59 by kzarins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ll.h"
#include <stdlib.h>

void	delete_inbetween_node(t_node *previous_node)
{
	t_node	*temp;

	temp = previous_node->next->next;
	free(previous_node->next);
	previous_node->next = temp;
}

void	delete_ll_last_node(t_node *head)
{
	t_node	*previous;

	if (!head)
		return ;
	while (head->next)
	{
		previous = head;
		head = head->next;
	}
	free(head);
	previous->next = NULL;
}

void	delete_ll_middle_node(t_node *head)
{
	t_node	*fast_ptr;
	t_node	*previous_ptr;

	fast_ptr = head;
	if (!head)
		return ;
	while (fast_ptr && fast_ptr->next)
	{
		previous_ptr = head;
		head = head->next;
		fast_ptr = fast_ptr->next->next;
	}
	delete_inbetween_node(previous_ptr);
}

t_node	*delete_ll_node_head(t_node *head)
{
	t_node	*new_head;

	new_head = head->next;
	free(head);
	return (new_head);
}

void	delete_ll_all(t_node **head)
{
	t_node	*previous;

	while ((*head)->next)
	{
		previous = *head;
		*head = (*head)->next;
		free(previous);
	}
	free(*head);
	*head = NULL;
}
