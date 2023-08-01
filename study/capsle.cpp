#include<iostream>

class BankAccount {
    private:
        int balance; // private変数によりカプセル化（隠蔽）されています。

    public:
        BankAccount() { // constructor
            balance = 0;
        }

        void deposit(int amount) {
            if (amount > 0) {
                balance += amount;
            } else {
                std::cout << "Deposit amount must be positive!" << std::endl;
            }
        }

        void withdraw(int amount) {
            if (amount > 0) {
                if (amount <= balance) {
                    balance -= amount;
                } else {
                    std::cout << "Insufficient balance!" << std::endl;
                }
            } else {
                std::cout << "Withdraw amount must be positive!" << std::endl;
            }
        }

        int getBalance() const {
            return balance;
        }
};

int main() {
    BankAccount myAccount; 
    myAccount.deposit(500);
    std::cout << "Balance after deposit: " << myAccount.getBalance() << std::endl;
    myAccount.withdraw(200);
    std::cout << "Balance after withdrawal: " << myAccount.getBalance() << std::endl;
    return 0;
}
