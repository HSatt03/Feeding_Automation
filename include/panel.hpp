#ifndef PANEL.H
#define PANEL.H
#include "reservation.hpp"
 class Panel
 {
 public:
     bool Action(bool);
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
     void exit(bool);
 };
 #endif

