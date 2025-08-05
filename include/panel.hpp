#ifndef PANEL_H
#define PANEL_H
#include <iostream>
#include "../include/reservation.hpp"
#include "../include/shoppingCart.hpp"
#include "../include/sessionManager.hpp"
using namespace std;
using namespace StudentSession;

 class Panel
 {
 public:
     bool Action(int, StudentSession::SessionManager*);
     void showMenu();
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
     void exit();
 };
 
 #endif

