/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_file.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 17:04:33 by gsmith            #+#    #+#             */
/*   Updated: 2020/01/10 18:04:57 by gsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_FILE_H
# define UTILS_FILE_H

unsigned int	read_file(const char **output, const char *filename);
unsigned int	next_line(const char *data);
char			*get_word(const char *data, unsigned int *read_head);

#endif
