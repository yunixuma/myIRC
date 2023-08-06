class Rec {
public:
    Rec(int width, int height)
        : width(width), height(height) {}
	// Rec& operator=(const Rec& other)
    // Rec& operator=(const Rec& src) {
    //     if (this != &src) {
    //         width = src.width;
    //         height = src.height;
    //     }
        
    //     return *this;
    // }

	// Rec& operator=(const Rec& src)
	// {
	// 	// this は現在のオブジェクト（つまり、メソッドが呼び出されているオブジェクト）を指します
	// 	if(this != src)
	// 	{
	// 		width = src.width;
	// 		height = src.height;
	// 	}
	// 	return *this;
	// }

	Rec& operator=(const Rec& src)
	{
		if(this != &src)
		{
			width = src.width;
			height = src.height;
		}
		return *this;
	}

    int getWidth() const { return width; }
    int getHeight() const { return height; }

	if(this != src)
	{
		width = src.width;
		height = src.width;
	}
	return *this;


private:
    int width;
    int height;
};


#include <iostream>

int main() {
    Rec rect1(10, 20);  // 幅10、高さ20の長方形を作成
    Rec rect2(30, 40);  // 幅30、高さ40の長方形を作成

    std::cout << "Rect1: " << rect1.getWidth() << " x " << rect1.getHeight() << std::endl;
    std::cout << "Rect2: " << rect2.getWidth() << " x " << rect2.getHeight() << std::endl;

    rect1 = rect2;  // rect2の内容をrect1にコピー

    std::cout << "After assignment..." << std::endl;
    std::cout << "Rect1: " << rect1.getWidth() << " x " << rect1.getHeight() << std::endl;
    std::cout << "Rect2: " << rect2.getWidth() << " x " << rect2.getHeight() << std::endl;

    return 0;
}
