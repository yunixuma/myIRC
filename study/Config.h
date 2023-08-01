#ifndef CONFIG_H
#define CONFIG_H

#include <map>
#include <string>
#include <iostream>

#define SEP   '='
#define FILE  "config/default.conf"

class Config
{
public:
    Config();
    ~Config();

    const std::map<std::string, std::string> map_;
    Config& operator=(const Config& src);

	std::ostream& operator<<(std::ostream& os, Config& config);
	
};

#endif
