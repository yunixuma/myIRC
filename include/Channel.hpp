/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykosaka <ykosaka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:04:04 by ykosaka           #+#    #+#             */
/*   Updated: 2023/08/01 20:01:45 by ykosaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <iostream>

class Channel
{
private:
	int					id_;
	std::string			name_;
	std::string			topic_;
	// std::vector<Message>	messages_;
	std::vector<User>	usersInvited_;
	std::vector<User>	usersJoined_;
	std::vector<User>	usersKicked_;
public:
	Channel(const int id, const std::string& name, const std::string& topic);
	Channel(const Channel& src);
	Channel&				operator=(const Channel& rhs);
	~Channel();
	const int			getId(void) const;
	std::string&		getName(void) const;
	std::string&		getTopic(void) const;
};

#endif
