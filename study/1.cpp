#include "Config.h"
#include <cstdio>

Config::Config()
{
    map_["1"] = "a";
    map_["2"] = "b";
    map_["3"] = "c";
}

Config::~Config()
{
}

Config &Config::operator=(const Config &src)
{
    if (this == &src)
        return *this;
    
    map_ = src.map_;

    return *this;
}

std::ostream& operator<<(std::ostream& os, const Config& config)
{
    for (std::map<std::string, std::string>::const_iterator it = config.map_.begin(); it != config.map_.end(); ++it)
    {
        os << it->first << "=" << it->second << std::endl;
    }
    return os;
}

int main()
{
    Config a;
    Config b;
    a = b;
    std::cout << a << std::endl;
}
