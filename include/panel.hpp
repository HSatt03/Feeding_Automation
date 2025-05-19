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
     bool Action(int);
     void showMenu();
     void showStudentInfo(StudentSession::SessionManager&);
     void checkBalance(StudentSession::SessionManager&);
     void viewReservation(StudentSession::SessionManager&);
     void viewShappingCart(ShoppingCart*);
     void addToShoppingCart();
     void confirmShoppingCart();
     void removeShoppingCartItem(StudentSession::SessionManager&);
     void increaseBalance(StudentSession::SessionManager&);
     void viewRecentTransactions();
     void cancelReservation(int);
     void exit();
 };
 
 #endif

