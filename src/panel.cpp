#include <iostream>
#include <windows.h>
#include <iomanip>
#include "../include/panel.hpp"
#include "../include/reservation.hpp"
#include "../include/student.hpp"

using namespace std;
void Panel::Action(int n)
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

void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void Panel::showMenu()
{
     
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
}    

void Panel::showStudentInfo()
{

}

void showBalanceBox(double balance)
{
    string title = " your balance ";
    string currency = " toman ";
    string balanceStr = to_string((int)balance) + currency;
    int width = 30;

    cout << "+" << string(width, '-') << "+" << endl;
    cout << "|" << setw((width + title.size()) / 2) << right << title;
    cout << setw(width - ((width + title.size()) / 2)) << left << "" << "|" << endl;
    cout << "+" << string(width, '-') << "+" << endl;
    cout << "|" << setw((width + balanceStr.size()) / 2) << right << balanceStr;
    cout << setw(width - ((width + balanceStr.size()) / 2)) << left << "" << "|" << endl;
    cout << "+" << string(width, '-') << "+" << endl;
}

void Panel::checkBalance(Student *s)
{
    double balance = s.getBalance();
    showBalanceBox(balance);
}

void Panel::viewReservation()
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

void Panel::increaseBalance(Student *s, float a)
{
    system("cls");
    
    if (a <= 0)
    {
        throw invalid_argument("Amount must be greater than zero.");
    }
    else
    {
        float balance = s->getBalance();
        s->setBalance(balance + a);
    }
}

void Panel::viewRecentTransactions()
{

}

void Panel::cancelReservation(int)
{
    
}

void Panel::exit(bool b)
{
     system("cls");
    cout << "";
    exit(0);
}