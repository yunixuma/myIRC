/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoo-lee <yoo-lee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 13:31:54 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/08/04 12:09:17 by yoo-lee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

Channel::Channel(std::string &name) :
	name_(name), normal_clients_(NULL), operator_clients_(NULL)
{
	
}

void	Channel::setName(std::string &name)
{
	this->name_ = name;
}

std::string &Channel::getName(void)
{
	return (this->name_);
}

Channel::~Channel()
{
}
