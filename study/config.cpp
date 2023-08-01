
#include "Config.h"
#include <cstdio>

// Configクラスのコンストラクタ
Config::Config()
{
	map_["1"] = "a";
	map_["2"] = "b";
	map_["3"] = "c";
    // コンストラクタの実装
}

// Configクラスのデストラクタ
Config::~Config()
{
    // デストラクタの実装
}

// Configクラスの代入演算子オーバーロード
Config &Config::operator=(const Config &src)
{
    // 代入演算子の実装
    if (this == &src) // 自己代入をチェック
        return *this;
	map_ = src.map_;
    // ここにメンバ変数の代入処理を実装

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

int main ()
{
	using std::cout;
	using std::endl;
	Config a;
	Config b;
	a = b;
	cout << a << endl;
}
