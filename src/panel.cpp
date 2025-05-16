#include <iostream>
#include "panel.hpp"
#include "reservation.hpp"
using namespace std;
bool Panel::Action(int n)
{
    switch (n)
    {
    case 1:
        showStudentInfo();
        break;
    case 2:
        checkBalance();
         break;
    case 3:
         viewReservation();
        break;
    case 4:
        addToShoppingCart();
        break;
    case 5:
        confirmShoppingCart();
        break;
    case 6:
        removeShoppingCartItem();
        break;
    case 7:
        increaseBalance();
        break;
    case 8:
        viewRecentTransactions();
        break;
    case 9:
        cancelReservation();
        break;
    }
}
void Panel::showMenu()
{
     void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

    int hightMM, widthMM;
    int i,j,y_start;
    bool sw_MainMenu;
    char ch;

  //while(true)
  //{
    sw_MainMenu=false;
    hightMM=28;
    widthMM=28;
    y_start=3;

    //system("cls");
    gotoxy(5,y_start);
    for(i=0;i<=widthMM-1;i++)
    {
        if(i%2==0)
        {
            cout<<"* ";
        }
        else
        {
            cout <<"* ";
        }
    }
    for(i=1;i<hightMM-1;i++)
    {
        gotoxy(5,y_start+i);
        cout<<"* ";
        for(j=1;j<widthMM-1;j++)
            cout<<"  ";
        cout<<"*";
    }
    gotoxy(5,y_start+i);
    for(i=0;i<=widthMM-1;i++)
    {
        if(i%2==0)
        {
            cout <<"* ";
        }
        else
        {
            cout <<"* ";
        }
    }
    gotoxy(12,y_start+2);
    cout<<"Student Menu    ---  <<Feeding atuomation>>";
        gotoxy(12,y_start+5);
        cout<<"1 _ show StudentInfo";

        gotoxy(12,y_start+7);
        cout<<"2 _ check Balance";

        gotoxy(12,y_start+9);
        cout<<"3 _ view Reservation";

        gotoxy(12,y_start+11);
        cout<<"4 _ add To ShoppingCart";

        gotoxy(12,y_start+13);
        cout << "5 _ confirm ShoppingCart";

        gotoxy(12,y_start+15);
        cout << "6 _ remove ShoppingCartItem";

        gotoxy(12,y_start+17);
        cout << "7 _ increase Balance";

        gotoxy(12,y_start+19);
        cout << "8 _ view Recent Transactions";

        gotoxy(12,y_start+21);
        cout << "9 _ cancel Reservation";

        gotoxy(12,y_start+24);
        cout<<"Enter Keys : ( 1 to 9 ) ";


   /* while (!sw_MainMenu)
    {
      if (kbhit())
      {
          n = getch();
          if(n >= 1 && n <= 9)
            Action(n);
        else
            gotoxy(12,y_start+26);
            cout << "The number is not valid!";

      }
    }
  }*/
//}
return 0;
}    
void Panel::showStudentInfo()
{

}
void Panel::checkBalance()
{

}
void Panel::viewReservation()
{

}
void Panel::addviewReservation(Reservation)
{

}
void Panel::addToShoppingCart()
{

}
void Panel::confirmShoppingCart()
{

}
void Panel::removeShoppingCartItem()
{

}
void Panel::increaseBalance()
{

}
void Panel::viewRecentTransactions()
{

}
void Panel::cancelReservation(int)
{
    
}
void Panel::exit()
{
     system(cls);
    cout << "";
    exit(0);
}