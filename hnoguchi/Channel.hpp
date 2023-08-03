/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 13:31:54 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/08/03 13:57:23 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

enum ChannelMode
{
	INVITE_ONLY,				//+i
	TOPIC_BY_CHANNEL_OPERATOR,	//+t
	PASSWORD_KEY,				//+k
	OPERATOR,					//+o
	USER_LIMIT					//+l
};

enum ClientMode
{
	REGULAR_USERS,	// regular users
	OPERATOR		// operator
};

class Channel
{
	private:
		std::string	name_;
	public:
		std::vector<int *> normal_clients_;
		std::vector<int *> operator_clients_;

	public:
		// CONSTRUCTER
		Channel(std::string &name);

		// Setters
		void	setName(std::string &name);

		// Getter
		std::string &getName(void);
}

#endif
