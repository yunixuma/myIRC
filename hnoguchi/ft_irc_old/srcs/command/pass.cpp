#include "config.hpp"

bool		check_password(Client &user, Channel &channel, Message &message)
{
	// ユーザーが登録されているか否か
	if(!user.is_registrated())
		std::cerr << ("\tuser is not registrated\t(")
	
	// コンフィグであらかじめ決めらたパスワードと一致するか、の確認。
	if (message(parameter[0] == config.pass))
		std::cerr << ("CMD", "PASS:\twrong password\t")
}
