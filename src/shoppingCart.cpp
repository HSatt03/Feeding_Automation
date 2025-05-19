#include <iostream>
#include <vector>
#include "../include/shoppingCart.hpp"
#include "reservation.hpp"
#include "../include/transactiohn.hpp"
Transaction ShoppingCart::confirm()
{

}
ShoppingCart::addReservation(Reservation reservation)
{
    reservation.setStatus(RStatus::NOT_PAID);
    Stime = time(0);
    _reservations.push_back(reservation);
}
void ShoppingCart::removeReservation(int ID)
{
    for(auto add = _reservations.begin(); add != _reservations.end(); add++)
    {
        if((*add)._reservation_id == ID)
        {
            _reservations.erase(add);
            break;
        }
    }
}
void ShoppingCart::viewShoppingCartItems()
{
    
}