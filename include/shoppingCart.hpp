#ifndef SHOPPINGCART_HPP
#define SHOPPINGCART_HPP
#include <iostream>
#include <vector>
#include "reservation.hpp"
#include "transaction.hpp"
using namespace std;

class ShoppingCart
{
public:
    Transaction confirm();
    void addReservation(Reservation);
    void removeReservation(int ID);
    void viewShoppingCartItems();
    void clear();
    vector<Reservation> getReservations() const;
private:
    vector<Reservation> _reservations;
};

#endif 