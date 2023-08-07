/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykosaka <ykosaka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:04:04 by ykosaka           #+#    #+#             */
/*   Updated: 2023/08/06 20:01:47 by ykosaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

# include <iostream>

class Client
{
private:
	int							fd_;
	std::string					userName_;
	std::string					nickname_;
	int							role_;
	std::vector<std::string>	joinedChannel_;
public:
	Client(const int fd, const std::string& userName, const std::string& nickname, const int role);
	Client(const Client& src);
	Client&			operator=(const Client& rhs);
	~Client();
	const int		getId(void) const;
	std::string&	getUserName(void) const;
	std::string&	getNickname(void) const;
	int				getRole(void) const;
	void			setUserName(const std::string& userName);
	void			setNickname(const std::string& nickname);
	void			setRole(const int role);
};

#endif
