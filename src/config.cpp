using std::istream;
using std::ostream;
using std::string;

Config()
{
	ifstream ifs(FILE, in);
	
	if(!ifs.good())
		exit(error("ifstream config file", 1));

	string line;

	for(;!ifs.eof();)
	{
		getline(ifs, line);
		stringstream	ss(line);
		string			key;		
		string			val;

		getline(ss, key, SEP);
		getline(ss, val, '\n');
				
		this -> map_[key] = val;
	}

	ifs.close();

	string portNumber = this -> map_["port"];
}



~Config()
{}

    Config& operator=(const Config& src)
	{
		if(this != &src)
		{
			map_ = src;
		}
		return (*this);
	}
	
std::ostream& operator<<(std::ostream& o, const Config& src) {
    std::map<std::string, std::string>::const_iterator i;
    for(i = src.get_map().begin(); i != src.get_map().end(); ++i) {
        o << "\t\t\t" << i->first << "=" << i->second << std::endl;
    }
    return o;
}
