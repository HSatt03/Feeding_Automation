#ifndef PANEL_H
#define PANEL_H

#include <iostream>
#include "reservation.hpp"
#include "shoppingCart.hpp"
#include "sessionManager.hpp"

using namespace std;
using namespace StudentSession;

 class Panel
 {
 public:
     void Action(int, StudentSession::SessionManager*);
     bool showMenu(StudentSession::SessionManager*);
     void showStudentInfo(StudentSession::SessionManager&);
     void checkBalance(StudentSession::SessionManager&);
     void viewReservation(StudentSession::SessionManager&);
     void viewShappingCart(StudentSession::SessionManager&);
     void addToShoppingCart(StudentSession::SessionManager&);
     void confirmShoppingCart(StudentSession::SessionManager&);
     void removeShoppingCartItem(StudentSession::SessionManager&);
     void increaseBalance(StudentSession::SessionManager&);
     void viewRecentTransactions(StudentSession::SessionManager&);
     void cancelReservation(StudentSession::SessionManager&);
     void exit(StudentSession::SessionManager&);
 };
 
 #endif

