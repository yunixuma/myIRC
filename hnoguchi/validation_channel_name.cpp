/*
   ・channel nameが正しいか調べる。
   ・50文字以内
   ・prefixは、&, #, !, または、なし
   ・space, Ctrl+G(ascii code 7), comma, colon, は、含めてはならない。
*/

#include <iostream>

// if (name[0] != '&' && name[0] != '#' && name[0] != '+' && name[0] != '!') {
// 	return (false);
// }

bool	isChannelName(const std::string& name)
{
	if (50 < name.size()) {
		return (false);
	}
	if (name.find(" ") != std::string::npos \
			|| name.find(",") != std::string::npos \
			|| name.find(":") != std::string::npos) {
		return (false);
	}
	return (true);
}

int	main(void) {

	if (isChannelName("#channel")) {
		std::cout << "T" << std::endl;
	}
	else {
		std::cout << "F" << std::endl;
	}
	return (0);
}
