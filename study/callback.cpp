#include <iostream>
#include <functional>
#include <thread>
#include <chrono>

// 非同期処理を模倣する関数
void simulateAsyncOperation(const std::function<void(int)>& callback) {
    std::this_thread::sleep_for(std::chrono::seconds(2)); // 2秒間の遅延をシミュレート
    int result = 42;
    callback(result); // 非同期処理完了時にコールバックを呼び出す
}

int main() {
    // コールバック関数を定義
    auto asyncCallback = [](int result) {
        std::cout << "Async operation completed with result: " << result << std::endl;
    };

    std::cout << "Starting async operation..." << std::endl;

    // 非同期処理を実行
    simulateAsyncOperation(asyncCallback);

    std::cout << "Async operation started, waiting for completion..." << std::endl;

    // ここで他の処理を行う（非同期処理の完了を待たずに進行）

    std::this_thread::sleep_for(std::chrono::seconds(3)); // 3秒間の遅延をシミュレート

    return 0;
}
