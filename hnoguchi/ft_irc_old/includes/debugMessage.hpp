/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debugMessage.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 17:09:31 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/05/26 18:09:03 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUGMESSAGE_HPP
# define DEBUGMESSAGE_HPP

#include <iostream>

# define DEFAULT_CONSTRUCT_MESSAGE "Default constructor called"
# define HAS_ARGS_CONSTRUCT_MESSAGE "Has args constructor called"
# define COPY_CONSTRUCT_MESSAGE "Copy constructor called"
# define COPY_OPERATOR_MESSAGE "Copy assignment operator called"
# define DESTRUCT_MESSAGE "Destructor called"

typedef enum eMessageType {
	DEFAULT_CONSTRUCT,
	HAS_ARGS_CONSTRUCT,
	COPY_CONSTRUCT,
	COPY_OPERATOR,
	DESTRUCT,
	NOT_MESSAGE
}	tMessageType;

void	debugMessage(const std::string &className, tMessageType type);

#endif
