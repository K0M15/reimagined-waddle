/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ll.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzarins <kzarins@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 13:33:21 by kzarins           #+#    #+#             */
/*   Updated: 2025/01/31 13:48:42 by kzarins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LL_H
# define FT_LL_H

//TODO: Redo the whole lib so that the first node changes
//	the value of the head node argument.
typedef struct node
{
	struct node	*next;
	void		*value;
}				t_node;

/*ft_ll_add_node.c*/
// Returns a new node
t_node			*add_node(void *value);
// Return: the last nodes pointer
t_node			*add_ll_back_node(t_node **head, void *value);
// Adds node in the middle or middle + 1
// Return: the node that was inserted
t_node			*add_ll_middle_node(t_node *head, void *value);
// Inserts a new head node
// Return: new head node or the head node if malloc fails!
t_node			*add_ll_node_head(t_node *head, void *value);

/*ft_ll_delete_node.c*/
void			delete_inbetween_node(t_node *previous_node);
void			delete_ll_last_node(t_node *head);
void			delete_ll_middle_node(t_node *head);
// Return: the new head
t_node			*delete_ll_node_head(t_node *head);
void			delete_ll_all(t_node **head);

#endif
