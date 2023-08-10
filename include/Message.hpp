/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Yoshihiro Kosaka <ykosaka@student.42tok    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:04:04 by ykosaka           #+#    #+#             */
/*   Updated: 2023/08/01 15:42:20 by Yoshihiro K      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESSAGE_HPP
# define MESSAGE_HPP

# include <iostream>

class Message
{
private:
	const int		id_;
	const int		sender_;
	const time_t	timestamp_;
	std::string		body_;
public:
	Message(const int id, const int sender, const time_t timestamp, const std::string& body);
	Message(const Message& src);
	Message&			operator=(const Message& rhs);
	~Message();
	const int			getId(void) const;
	const int			getSender(void) const;
	const time_t		getTimestamp(void) const;
	std::string&		getBody(void) const;
};

#endif
