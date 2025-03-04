#include <vector>
#include <algorithm>
#include <iostream>

class ATM {
    public:
        ATM() :
        banknotesCount_(5, 0)
        {    
        }
        
        void deposit(std::vector<int> banknotesCount) {
            std::transform(banknotesCount_.begin(), banknotesCount_.end(), 
            banknotesCount.begin(), banknotesCount_.begin(), 
            [](int a, int b) { return a + b; });
        }
        
        std::vector<int> withdraw(int amount) {
            std::vector<int> diff(banknotesCount_.size(), 0);
            std::vector<int> pre_calc = banknotesCount_;

            for (int i = pre_calc.size() - 1; i >= 0; i--) {
                if (amount <= 0) {
                    break;
                }

                int cnt =  std::min(pre_calc[i], amount / banknotesNominal_[i]);
                amount -= cnt*banknotesNominal_[i];
                pre_calc[i] -= cnt;
            }
            if (amount == 0) {
                std::transform(banknotesCount_.begin(), banknotesCount_.end(),
                    pre_calc.begin(), diff.begin(), 
                    [](int a, int b) { return a - b; });
                banknotesCount_ = pre_calc;
                return diff;
            } else {
                return std::vector<int>(1, -1);
            }
        }
        
    private:
        std::vector<int> banknotesCount_;
        std::vector<int> banknotesNominal_ = {20, 50, 100, 200, 500};
};

int main()
{
    ATM atm = ATM();
    atm.deposit({0,0,1,2,1});
    atm.withdraw(600); // Returns [0,0,1,0,1]. The machine uses 1 $100 banknote
                        // and 1 $500 banknote. The banknotes left over in the
                        // machine are [0,0,0,2,0].
    atm.deposit({0,1,0,1,1}); // Deposits 1 $50, $200, and $500 banknote.
                            // The banknotes in the machine are now [0,1,0,3,1].
    atm.withdraw(600);        // Returns [-1]. The machine will try to use a $500 banknote
                            // and then be unable to complete the remaining $100,
                    // so the withdraw request will be rejected.
                            // Since the request is rejected, the number of banknotes
                            // in the machine is not modified.
        // Returns [0,1,0,0,1]. The machine uses 1 $50 banknote
                            // and 1 $500 banknote.
    for (const auto& at : atm.withdraw(550)) {
        std::cout << at << " ";
    }
    return 0;
}