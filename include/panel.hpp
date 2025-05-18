#ifndef PANEL_H
#define PANEL_H
#include "../include/reservation.hpp"
#include "../include/student.hpp"
 class Panel
 {
 public:
     void Action(int);
     void showMenu();
     void showStudentInfo();
     void checkBalance(Student*);
     void viewReservation();
     void addToShoppingCart();
     void confirmShoppingCart();
     void removeShoppingCartItem();
     void increaseBalance(Student*, float);
     void viewRecentTransactions();
     void cancelReservation(int);
     void exit(bool b);
 };
 #endif

