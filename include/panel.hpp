#ifndef PANEL_H
#define PANEL_H
#include <iostream>
#include "reservation.hpp"
using namespace std;

 class Panel
 {
 public:
     bool Action(int);
     void showMenu();
     void showStudentInfo();
     void checkBalance();
     void viewReservation();
     void addviewReservation(Reservation);
     void addToShoppingCart();
     void confirmShoppingCart();
     void removeShoppingCartItem();
     void increaseBalance();
     void viewRecentTransactions();
     void cancelReservation(int);
     void exit();
 };
 
 #endif

