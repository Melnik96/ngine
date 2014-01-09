/*
 * <one line to give the program's name and a brief idea of what it does.>
 * Copyright (C) 2013  <copyright holder> <email>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef LIST_H
#define LIST_H
#include <serialize.h>

struct list {
  struct list *prev;
  struct list *next;
};

void list_init(struct list *list);
void list_insert(struct list *list, struct list *elm);
void list_remove(struct list *elm);
int list_length(const struct list *list);
int list_empty(const struct list *list);
void list_insert_list(struct list *list, struct list *other);

#ifdef __GNUC__
#define container_of(ptr, sample, member)				\
	(__typeof__(sample))((char *)(ptr)	-			\
		 ((char *)&(sample)->member - (char *)(sample)))
#else
#define container_of(ptr, sample, member)				\
	(void *)((char *)(ptr)	-				        \
		 ((char *)&(sample)->member - (char *)(sample)))
#endif

#define list_for_each(pos, head, member)				\
	for (pos = 0, pos = container_of((head)->next, pos, member);	\
	     &pos->member != (head);					\
	     pos = container_of(pos->member.next, pos, member))

#define list_for_each_safe(pos, tmp, head, member)			\
	for (pos = 0, tmp = 0, 						\
	     pos = container_of((head)->next, pos, member),		\
	     tmp = container_of((pos)->member.next, tmp, member);	\
	     &pos->member != (head);					\
	     pos = tmp,							\
	     tmp = container_of(pos->member.next, tmp, member))

#define list_for_each_reverse(pos, head, member)			\
	for (pos = 0, pos = container_of((head)->prev, pos, member);	\
	     &pos->member != (head);					\
	     pos = container_of(pos->member.prev, pos, member))

#define list_for_each_reverse_safe(pos, tmp, head, member)		\
	for (pos = 0, tmp = 0, 						\
	     pos = container_of((head)->prev, pos, member),	\
	     tmp = container_of((pos)->member.prev, tmp, member);	\
	     &pos->member != (head);					\
	     pos = tmp,							\
	     tmp = container_of(pos->member.prev, tmp, member))

#endif // LIST_H
