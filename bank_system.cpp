#include <iostream>
#include <fstream>
#include "bank_system.h"

static const int base_list[8]={500000, 200000, 100000, 50000, 20000, 5000, 2000, 1000};

bank::bank(){
  current_id = "";
  number_user = 0;
  bank_balance = 0;
  denomination = base_list;
  number_per_denomitation[500001] = {0};
}

void starting(){
  std::cout << "<<1. Sign up." << '\n';
  std::cout << "<<2. Sign in." << '\n';
  std::cout << "<<3. Exit." << '\n';
  std::cout << '\n';
}

void exiting(){
  std::cout << "Thank you and see you soon!" << '\n';
  std::cout << '\n';
}

void menu(){
  std::cout << "List menu:" << '\n';
  std::cout << "<<1. Deposit." << '\n';
  std::cout << "<<2. Withdraw." << '\n';
  std::cout << "<<3. Balance inquiry." << '\n';
  std::cout << "<<4. Transfer." << '\n';
  std::cout << "<<5. Sign out." << '\n';
  std::cout << "<<6. Exit." <<'\n';
  std::cout << '\n';
}

std::string create_password(){
  std::string old_pass,new_pass;
  std::cout << "Please enter your password." << '\n';
  std::cin >> old_pass;
  std::cout << "Please enter your password again!" << '\n';
  std::cin >> new_pass;
  if(old_pass != new_pass){
    std::cout << "Those passwords didn't match. Try again!" << '\n';
    return create_password();
  }
  else{
    std::cout << "You have successfully created a password. ";
    std::cout << "Please do not reveal your password to anyone!" << '\n';
    return new_pass;
  }
  std::string temp = "";
  return temp;
}

void bank::save_history(const std::string id_user, const std::string content, const int balance){
  std::string file_name = "history_" + id_user + ".txt";
  std::ofstream file(file_name, std::ios::app);
  file << "Content: " << content << '\n';
  if(balance){
    file << "Bank balance: ";
    if(balance > 0) file << '+';
    file << balance << "VND" << '\n';
  }
  file << '\n';
  file.close();
}

std::string bank::enter_id(){
  std::cout << "Please enter your ID user!" << '\n';
  std::string id_user;
  std::cin >> id_user;
  if(check[id_user]) return id_user;
  else{
    if(check[id_user] == 0){
      std::cout << "You have enter wrong ID. Try again!" << '\n';
      return enter_id();
    }
    else{
      std::cout<< "Your bank account has been locked! Try again!" << '\n';
      return enter_id();
    }
  }
}

std::string bank::enter_password(int number){
  if(number > 5){
    std::cout << "You have enter wrong ID 5 times. ";
    std::cout << "Your login access is locked temporarily because you either entered the wrong password for more than 5 times!" << '\n';
    save_history(current_id, "Bank account is locked since logging in over 5 times", 0);
    std::string temp = "";
    return temp;
  }
  std::cout << "Please enter your password!" << '\n';
  std::string pass;
  std::cin >> pass;
  if(pass != list_user[check[current_id] - 1].password){
    std::cout << "You have enter wrong password. Try again!" << '\n';
    return enter_password(number + 1);
  }
  else{
    std::cout << "You have successfully accessed your account!" << '\n';
    return pass;
  }
}

void bank::sign_up(){
  ++number_user;
  std::string id = std::to_string(number_user);
  while(id.size() < 4) id = '0' + id;
  check[id] = number_user;
  std::string pass = create_password();
  std::cout << "Your account ID is " << id << '\n';
  save_history(id, "Create account successfully", 0);
  user temp;
  temp.id = id;
  temp.money = 0;
  temp.password = pass;
  list_user.push_back(temp);
}

void bank::sign_in(){
  current_id = enter_id();
  std::string pass = enter_password(0);
  std::string temp = "";
  if(pass == temp){
    check[current_id] = -1;
    sign_in();
  }
}

void bank::deposit(){
  std::cout << "Please enter the number you deposit corresponding to the denomination! ";
  std::cout << '\n' << "Denomination first, number per denomination second." << '\n';
  std::cout << "If you want to finish depositing, please enter money that is -1." << '\n';
  int number, money, sum = 0;
  while(1){
    std::cin >> money;
    if(money < 0) break;
    std::cin >> number;
    sum += money * number;
    number_per_denomitation[money] += number;
    bank_balance += money * number;
    list_user[check[current_id] - 1].money += money * number;
  }
  save_history(current_id, "Deposit", sum);
  std::cout << "Successful transaction!" << '\n';
}

bool bank::check_money(int money){
  if(money % 1000 || money < 50000 || money > list_user[check[current_id] - 1].money || money > bank_balance) return 0;
  int temp = money;
  for(int i = 0; i < 8; ++i) temp -= std::min(temp / base_list[i], number_per_denomitation[base_list[i]]) * base_list[i];
  if(temp) return 0;
  return 1;
}

void bank::withdraw(){
  int money;
  while(1){
    std::cout << "The amount that can be withdrawn is at least 50000VND and is a multiple of 1000VND." << '\n';
    std::cout << "Enter the amount to withdraw." << '\n';
    std::cin >> money;
    if(check_money(money)) break;
    else std::cout << "You have entered an invalid amount." << '\n';
  }
  bank_balance -= money;
  list_user[check[current_id] - 1].money -= money;
  save_history(current_id, "Withdraw", -money);
  for(int i = 0; i < 8; ++i){
    int temp = std::min(money / base_list[i], number_per_denomitation[base_list[i]]);
    money -= temp * base_list[i];
    number_per_denomitation[base_list[i]] -= temp;
  }
}

void bank::balance_inquiry(){
  std::cout << "Your account balance is " << list_user[check[current_id] - 1].money << "VND." << '\n';
}

void bank::transfer(){
  std::cout << "Please enter the ID that you want to send money." << '\n';
  std::string other_id;
  while(1){
    std::cin >> other_id;
    if(!check[other_id]) std::cout << "You have enter wrong ID. Try again!" << '\n';
    else break;
  }
  std::cout << "Please enter amount money that you want to send!" << '\n';
  int money;
  std::cin >> money;
  if(money > list_user[check[current_id] - 1].money){
    std::cout << "Your account balance is not enough to send." << '\n';
    return;
  }
  list_user[check[current_id] - 1].money -= money;
  list_user[check[other_id]].money += money;
  save_history(current_id, "Transfer", -money);
  save_history(other_id, "Receive", money);
}
