#include <vector>
#include <map>

#ifndef bank_system
#define bank_system

// struct that save the information of user
struct user{
  std::string id;
  std::string password;
  int money;
};

class bank{

// private variables used inside class
  std::string current_id;
  std::vector<user> list_user;
  int number_user;
  int bank_balance;
  const int *denomination;
  int number_per_denomitation[500001];
  std::map<std::string,int> check;

// public variables
public:
  // construct a bank system
  bank();

  // a function that saves the history of all operations
  void save_history(const std::string id_user, const std::string content, const int balance);

  // a function that signs up to ATM app to check user is registered or not
  void sign_up();

  // a function that enters id user
  std::string enter_id();

  // a function that enters password user
  std::string enter_password(int number);

  // a function that signs in to ATM app
  void sign_in();

  // a function that deposits to ATM app
  void deposit();

  // a function that checks invalid money to withdraw
  bool check_money(int money);

  // a function that withdraws to ATM app
  void withdraw();

  // a function that checks the account balance
  void balance_inquiry();

  // a function that transfers money to an other account
  void transfer();
};

// welcome screen of ATM app
void starting();

// screen before exiting ATM app
void exiting();

// menu screen of ATM app
void menu();

// a function that creates a new password for new user
std::string create_password();

#endif // bank_system
