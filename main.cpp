/*
INT2215-24 Assignment ATM App
Author: Ngo Duc Hung
Student ID: 20020078
VNU email: 20020078@vnu.edu.vn
Academic honesty statement: I hereby confirm that this is my own work and I have
not violated any rule of lecturer.
Description: This is the source code for the ATM app. In implements the main
function that is the driver of the program.
*/

#include <iostream>
#include "bank_system.h"

int main(){
  bank ChingChongDingDong;
  std::cout << "Welcome to ChingChongDingDong ATM!" << '\n';
  while(1){
    int choice;
    starting();
    std::cin >> choice;
    if(choice < 2) ChingChongDingDong.sign_up();
    else{
      if(choice < 3){
        bool ok = 0, ch = 0;
        ChingChongDingDong.sign_in();
        while(!ok && !ch){
          int choice1;
          menu();
          std::cin >> choice1;
          switch(choice1){
            case 1:
              ChingChongDingDong.deposit();
              break;
            case 2:
              ChingChongDingDong.withdraw();
              break;
            case 3:
              ChingChongDingDong.balance_inquiry();
              break;
            case 4:
              ChingChongDingDong.transfer();
              break;
            case 5:
              ch = 1;
              break;
            case 6:
              ok = 1;
              break;
          }
        }
        if(ok) break;
      }
      else break;
    }
  }
  return 0;
}
