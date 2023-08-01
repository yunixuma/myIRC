/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Yoshihiro Kosaka <ykosaka@student.42tok    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:04:04 by ykosaka           #+#    #+#             */
/*   Updated: 2023/08/01 15:35:09 by Yoshihiro K      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USER_HPP
# define USER_HPP

# include <iostream>

class User
{
private:
	const int	id_;
	std::string	userName_;
	std::string	nickname_;
	int			role_;
public:
	User(const int id, const std::string& userName, const std::string& nickname, const int role);
	User(const User& src);
	User&			operator=(const User& rhs);
	~User();
	const int		getId(void) const;
	std::string&	getUserName(void) const;
	std::string&	getNickname(void) const;
	int				getRole(void) const;
	void			setUserName(const std::string& userName);
	void			setNickname(const std::string& nickname);
	void			setRole(const int role);
};

#endif
