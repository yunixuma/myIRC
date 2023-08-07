
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykosaka <ykosaka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:04:04 by ykosaka           #+#    #+#             */
/*   Updated: 2023/08/06 19:00:05 by ykosaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

Client(int fd, const std::string& userName, const std::string& nickname, int role) \
	: fd_(fd), userName_(userName), nickname_(nickname), role_(role) {
	std::clog << "\033[36;2;3m[" << this \
		<< "]<Client> Constructor called (" << this->name_ << ")\033[m" << std::endl;
	for (int i = 0; i < 4; i++)
		this->slot_[i] = NULL;
}

Client::Client(const Client& src) {
	std::clog << "\033[36;2;3m[" << this << "<-" << &src \
		<< "]<Client> Copy constructor called (" << this->name_ << ")\033[m" << std::endl;
	this->name_ = src.name_;
	for (int i = 0; i < 4; i++)
	{
		if (src.slot_[i])
			this->slot_[i] = src.slot_[i]->clone();
		else
			this->slot_[i] = NULL;
	}
}

Client&	Client::operator=(const Client& rhs) {
	std::clog << "\033[35;2;3m[" << this << "<-" << &rhs \
		<< "]<Client> Copy assignment operator called (" \
		<< rhs.name_ << " -> " << this->name_ << ")\033[m" << std::endl;
	this->name_ = rhs.name_;
	for (int i = 0; i < 4; i++)
	{
		if (this->slot_[i])
			delete this->slot_[i];
		if (rhs.slot_[i])
			this->slot_[i] = rhs.slot_[i]->clone();
		else
			this->slot_[i] = NULL;
	}
	return (*this);
}

Client::~Client(void) {
	std::clog << "\033[31;2;3m[" << this \
		<< "]<Client> Destructor called (" << this->name_ << ")\033[m" << std::endl;
	for (int i = 0; i < 4; i++)
	{
		if (this->slot_[i])
		{
			delete this->slot_[i];
			this->slot_[i] = NULL;
		}
	}
}

const std::string&	Client::getName(void) const {
	return (this->name_);
}

void	Client::equip(AMateria* m) {
	std::clog << "\033[2;3m[" << this \
		<< "]<Client> equip(" << m \
		<< ") called (" << this->name_ << ")\033[m" << std::endl;
	if (!m)
	{
		std::cerr << "\033[35;3mNo new Materia equipped\033[m" << std::endl;
		return ;
	}
	for (int i = 0; i < 4; i++)
	{
		if (!this->slot_[i])
		{
			this->slot_[i] = m;
			return ;
		}
	}
	std::cerr << "\033[35;3mSlot is full\033[m" << std::endl;
	delete m;
}

void	Client::unequip(int idx) {
	std::clog << "\033[2;3m[" << this \
		<< "]<Client> unequip(" << idx \
		<< ") called (" << this->name_ << ")\033[m" << std::endl;
	if (0 > idx || idx > 4)
	{
		std::cerr << "\033[35;3mSlot number " << idx << " is out of range\033[m" << std::endl;
		return ;
	}
	if (!this->slot_[idx])
	{
		std::cerr << "\033[35;3mSlot " << idx << " is already empty\033[m" << std::endl;
		return;
	}
	delete this->slot_[idx];
	this->slot_[idx] = NULL;
}

void	Client::use(int idx, IClient& target) {
	std::clog << "\033[2;3m[" << this \
		<< "]<Client> use(" << idx << ", " << &target \
		<< ") called (" << this->name_ << ")\033[m" << std::endl;
	if (0 > idx || idx > 4)
	{
		std::cerr << "\033[35;3mSlot number " << idx << " is out of range\033[m" << std::endl;
		return ;
	}
	AMateria*	m = this->slot_[idx];
	if (!m)
	{
		std::cerr << "\033[35;3mSlot " << idx << " is empty\033[m" << std::endl;
		return;
	}
	m->use(target);
}

void	Client::showMateria(void) const {
	std::clog << "\033[33;2;3m[" << this << "] " << this->name_ << "\033[m" << std::endl;
	for (int i = 0; i < 4; i++)
	{
		if (this->slot_[i])
			std::clog << "\033[33;2;3m" << i << " [" << this->slot_[i] << "] " \
				<< this->slot_[i]->getType() << "\033[m" << std::endl;
		else
			std::clog << "\033[33;2;3m" << i << " [" << this->slot_[i] << "] " \
				<< "\033[m" << std::endl;
	}
}
