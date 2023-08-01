/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Yoshihiro Kosaka <ykosaka@student.42tok    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:04:04 by ykosaka           #+#    #+#             */
/*   Updated: 2023/08/01 15:39:00 by Yoshihiro K      ###   ########.fr       */
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
	std::vector<int>	messages_;
	std::vector<int>	usersInvited_;
	std::vector<int>	usersJoined_;
	std::vector<int>	usersKicked_;
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
