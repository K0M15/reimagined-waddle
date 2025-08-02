/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ll_add_node.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzarins <kzarins@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 14:03:09 by kzarins           #+#    #+#             */
/*   Updated: 2025/01/31 14:05:33 by kzarins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ll.h"
#include <stdlib.h>
#include <unistd.h>

t_node	*add_node(const int value)
{
	t_node	*new_head;

	new_head = (t_node *)malloc(sizeof(t_node));
	if (!new_head)
		return (NULL);
	new_head->value = value;
	new_head->next = NULL;
	return (new_head);
}

t_node	*add_ll_back_node(t_node *head, const int value)
{
	if (!head)
		return (0);
	while (head->next)
	{
		head = head->next;
	}
	head->next = (t_node *)malloc(sizeof(t_node));
	if (!head->next)
		return (NULL);
	head = head->next;
	head->value = value;
	head->next = NULL;
	return (head);
}

t_node	*add_ll_node_after(t_node *previous_node, const int value)
{
	t_node	*new_node;

	new_node = add_node(value);
	if (!new_node)
		return (NULL);
	new_node->next = previous_node->next;
	previous_node->next = new_node;
	return (new_node);
}

t_node	*add_ll_node_head(t_node *head, const int value)
{
	t_node	*new_head;

	new_head = add_node(value);
	if (!new_head)
		return (head);
	new_head->next = head;
	return (new_head);
}

t_node	*add_ll_middle_node(t_node *head, const int value)
{
	t_node	*fast_ptr;
	t_node	*previous_ptr;

	fast_ptr = head;
	if (!head)
		return (NULL);
	if (!head->next)
	{
		head->next = add_node(value);
		return (head->next);
	}
	while (fast_ptr && fast_ptr->next)
	{
		previous_ptr = head;
		head = head->next;
		fast_ptr = fast_ptr->next->next;
	}
	if (!fast_ptr)
		head = add_ll_node_after(previous_ptr, value);
	else
		head = add_ll_node_after(head, value);
	return (head);
}
