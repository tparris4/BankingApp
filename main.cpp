#include <iostream>
#include <memory>
#include "Account.h"
#include "Checking_Account.h"
#include "Savings_Account.h"
#include "Trust_Account.h"
#include "Account_Util.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <limits>
#include <algorithm>

using namespace std;

bool checkAccountExists(std::vector<std::unique_ptr<Account>> accounts, std::unique_ptr<Account> &acc)
{
    if(std::find(accounts.begin(), accounts.end(), acc) != accounts.end()){
        std::cout << "You do not have an account of this type" << std::endl;
        return false;
        //test 
}

    else{
        return true;
    }
}

void withdrawal(std::unique_ptr<Account> &acc){
    double amnt;
    std::cout << "Enter the amount you'd like to withdraw " << std::endl;
    std::cin >> amnt;
    try {
    acc->withdraw(amnt);
    } 
catch (const InsufficientFundsException &ex)
  {
    std::cerr << "Withdrawal error" << ex.what() << std::endl;
  }       
}

void display(const std::vector<std::unique_ptr<Account>> &vec) {
    std::cout << "\nDisplaying account info" << std::endl;
    std::cout << "=======================" << std::endl;
    for (const auto &ptr: vec) 
        std::cout << ptr->print << std::endl;
   
    std::cout << "=======================" << std::endl;
}

bool accountVecCheck(std::vector<std::unique_ptr<Account>> &acc){
            if(acc.empty()){
                std::cout << "There are no accounts found " << std::endl;
                return false;
            }    
            return true;
}
int main() {
    // test your code here
    std::cout << "Welcome to the Banking Application, please choose from one of the following options" << std::endl;
    int flag = 1;
    std::unique_ptr<Account> checking_accounts;
    std::unique_ptr<Account> savings_accounts;
    std::unique_ptr<Account> trust_accounts;
    std::vector<std::unique_ptr<Account>> accounts;
    do{
        std::string option{};
        int value{};
        std::cout << std::setw(10) << "1) Create an account " << std::endl;
        std::cout << std::setw(10) << "2) Deposit money to account " << std::endl;
        std::cout << std::setw(10) << "3) Withdraw money from account " << std::endl;
        std::cout << std::setw(10) << "4) Display all types of accounts " << std::endl;
        std::cout << std::setw(10) << "5) Quit " << std::endl;
        std:: cout << "Please use the number when choosing an option" << std::endl;
        std::cin >> option;
        std::istringstream valid {option};
        if (valid >> value)
        {
            value = std::stoi (option);
            switch(value){
            case 1:
            {
                int acc{};
                std::string name;
                double amount;
                int flag2{0};
                std::cout << "You have chosen to create an account " << std::endl;
                do {
                std::cout << "Which account would you like? We have 3 types of accounts available\n"
                << "1) Checking, 2) Savings, 3) Trust. The Trust account gives you a $50 bonus when depositing\n" <<
                "amounts of $5000 or more but you can only withdrawal up to 3 times per year" << std::endl;
                std::cin >> acc;
            switch(acc){
                case 1:
                {
                    std::cout << "Please enter your name followed by the amount you are initially depositing" << std::endl;
                    try {
                    std::cin >> name >> amount;
                    checking_accounts = std::make_unique<Checking_Account>(name, amount);
                    if(checking_accounts)
                        std::cout << "Successfully created account" << std::endl;
                    accounts.push_back(checking_accounts);
                        }
                    catch (const IllegalBalanceException &ex)
                        {
                    std::cerr << "Couldn't create account - negative balance" << std::endl;
                        }
                    flag2 = 1;
                    break;
                    
                }
                
                case 2:
                {
                    std::cout << "Please enter your name followed by the amount you are initially depositing" << std::endl;
                    try {
                    std::cin >> name >> amount;
                    savings_accounts = std::make_unique<Savings_Account>(name, amount);
                    if(savings_accounts)
                        std::cout << "Successfully created account" << std::endl;
                    accounts.push_back(savings_accounts);
                        }
                    catch (const IllegalBalanceException &ex)
                    {
                    std::cerr << "Couldn't create account - negative balance" << std::endl;
                    }
                    flag2 = 1;
                    break;
                    
                }
                    
                case 3:
                {
                    std::cout << "Please enter your name followed by the amount you are initially depositing" << std::endl;
                    try {
                    std::cin >> name >> amount;
                    trust_accounts = std::make_unique<Trust_Account>(name, amount);
                    if(trust_accounts)
                        std::cout << "Successfully created account" << std::endl;
                    accounts.push_back(trust_accounts);
                        }
                    catch (const IllegalBalanceException &ex)
                    {
                    std::cerr << "Couldn't create account - negative balance" << std::endl;
                    }
                    flag2 = 1;
                    break;   

                default:
                    std::cout << "That is not an option" << std::endl;
            } 
            }
        } while (!flag2);
            }
        case 2:
        {
            std::cout << "You have chosen to deposit an amount " << std::endl;
            if(accounts.empty()){
                std::cout << "There are no accounts found " << std::endl;
                break;
            }
            int nameAcc;
            double deposit;
            std::cout << "Please enter which account you'd like to deposit to: 1 for Checking, 2 for Savings, 3 for Trust" << std::endl;
            cin >> nameAcc;
            switch(nameAcc){
                case 1:
                {
                if(std::find(accounts.begin(), accounts.end(), checking_accounts) != accounts.end()){
                    std::cout << "You do not have an account of this type" << std::endl;
                    break;
                }
                std::cout << "Enter the amount you'd like to deposit" << std::endl;
                checking_accounts->deposit(deposit);
                break;
                
                }
                
                case 2:
                {
                if(std::find(accounts.begin(), accounts.end(), savings_accounts) != accounts.end()){
                    std::cout << "You do not have an account of this type" << std::endl;
                    break;
                }
                std::cout << "Enter the amount you'd like to deposit" << std::endl;
                savings_accounts->deposit(deposit);
                break;    
                
                }    

                case 3:
                {
                if(std::find(accounts.begin(), accounts.end(), savings_accounts) != accounts.end()){
                    std::cout << "You do not have an account of this type" << std::endl;
                    break;
                }
                std::cout << "Enter the amount you'd like to deposit" << std::endl;
                savings_accounts->deposit(deposit);
                break; 
                
                }     
                
                default:
                    std::cout << "Please enter a valid input" << std::endl;
            }
            break;
            
        case 3:
        {
            std::cout << "You have chosen to withdraw from an account " << std::endl;
            if(accounts.empty()){
                std::cout << "There are no accounts found " << std::endl;
                break;
            }
            int nameAcc2;
            double withdraw;
            std::cout << "Please enter which account you'd like to withdraw from: 1 for Checking, 2 for Savings, 3 for Trust" << std::endl;
            cin >> nameAcc2;
            switch(nameAcc2){
            case 1:
            {
                if(!checkAccountExists(accounts, checking_accounts)){
                    break;
                }
                else {
                    withdrawal(checking_accounts);
                    break;
                }
                
            }
            
            case 2:
            {
                if(!checkAccountExists(accounts, savings_accounts)){
                    break;
                }
                else {
                    withdrawal(savings_accounts);
                    break;
                }  
                
            }
                
            case 3:
            {
                if(!checkAccountExists(accounts, trust_accounts)){
                    break;
                }
                else {
                    withdrawal(trust_accounts);
                    break;
                }
                
            }
            default:
                    std::cout << "Please enter a valid input" << std::endl;
        }
        break;
        
        }
        
        case 4:
        {
        if(accountVecCheck(accounts)){
            std::cout << "Here is the account information: " << std::endl;
            display(accounts);
            break;
            }
        break;
        
        }
            
        case 5:
        {
        std::cout << "Thank you for using this application " <<std::endl;
        flag = 1;
        break;
        
        }
        
        default:
        std::cout << "That is not an option" << std::endl;
    }
            }
            
            
            
            
            // exit conditions
        }else{
            std::cout << "That is not an integer input, try again " << std::endl;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        }
}while(!flag);
    
    
//    try {
//            std::unique_ptr<Account> moes_account = std::make_unique<Checking_Account>("Moe", -10.0);
//        std::cout << *moes_account << std::endl;
//    }
//    catch (const IllegalBalanceException &ex)
//    {
//        std::cerr << "Couldn't create account - negative balance" << std::endl;
//    }
//    catch (const InsufficientFundsException &ex)
//    {
//        std::cerr << "Withdrawal error" << ex.what() << std::endl;
//    }
//    std::cout << "Program completed successfully" << std::endl;
//    return 0;
//}

    
    
}