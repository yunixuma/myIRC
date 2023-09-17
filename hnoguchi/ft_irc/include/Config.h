#ifndef CONFIG_H
# define CONFIG_H

#define SEP	'='
#define FILE "config/default.conf"

#include <iostream>
#include <map>

using std::map;
using std::string;
class Config
{
	public:
	config();
	~config();

	const map<string,string> map_;
	
	Config &operator=(const Config &src);
	Config &operator<<(const Config &src);
}

#endif

