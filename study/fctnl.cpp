#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    int fd;
    
    // ファイルを開く
    fd = open("test.txt", O_RDONLY);
    if (fd < 0) {
        perror("Failed to open file");
        return 1;
    }
    
    // 現在のフラグを取得
    int flags = fcntl(fd, F_GETFL, 0);
    if (flags < 0) {
        perror("Failed to get flags");
        return 1;
    }
    
    // フラグを設定して非ブロッキングにする
    if (fcntl(fd, F_SETFL, flags | O_NONBLOCK) < 0) {
        perror("Failed to set non-blocking");
        return 1;
    }
	

    // ...
    // ファイル操作はここに書く
    // ...

    // ファイルを閉じる
    close(fd);
    
    return 0;
}
