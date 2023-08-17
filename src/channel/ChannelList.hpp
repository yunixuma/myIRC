#ifndef CHANNELLIST_HPP
# define CHANNELLIST_HPP

#include <iostream>
#include <vector>
#include "Channel.hpp"

class Channel;

class ChannelList {
	private:
		std::vector<Channel *> list_;
	public:
		std::vector<Channel *>	getList(void) const;
		void					setList(std::vector<Channel *> const &list);
};

#endif