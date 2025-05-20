#include <iostream>
#include <windows.h>
#include <conio.h>
#include "../include/panel.hpp"
#include "../include/reservation.hpp"
#include "../include/shoppingCart.hpp"
#include "../include/sessionManager.hpp"
using namespace std;
using namespace StudentSession;

void drawBox(int x, int y, int width, int height)
{
    // گوشه‌ها
    gotoxy(x, y); cout << "+";
    gotoxy(x + width, y); cout << "+";
    gotoxy(x, y + height); cout << "+";
    gotoxy(x + width, y + height); cout << "+";

    // خطوط افقی
    for (int i = 1; i < width; ++i) {
        gotoxy(x + i, y); cout << "-";
        gotoxy(x + i, y + height); cout << "-";
    }

    // خطوط عمودی
    for (int i = 1; i < height; ++i) {
        gotoxy(x, y + i); cout << "|";
        gotoxy(x + width, y + i); cout << "|";
    }
}

bool Panel::Action(int n)
{
    StudentSession::SessionManager *Student;
    switch (n)
    {
    case 1:
        showStudentInfo(*Student);
        break;
    case 2:
        checkBalance(*Student);
         break;
    case 3:
         viewReservation(*Student);
        break;
    case 4:
        viewShappingCart(Student->shoppingCart());
        break;
    case 5:
        addToShoppingCart();
        break;
    case 6:
        confirmShoppingCart();
        break;
    case 7:
        removeShoppingCartItem(*Student);
        break;
    case 8:
        increaseBalance(*Student);
        break;
    case 9:
        viewRecentTransactions();
        break;
    case 10:
        cancelReservation();
        break;
    case 11:
        exit();
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
    sw_MainMenu = false;
    hightMM = 33;
    widthMM = 28;
    y_start = 3;

    //system("cls");
    gotoxy(5,y_start);
    for(int i=0 ; i<=widthMM-1 ; i++)
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
    for(int i=1 ; i<hightMM-1 ; i++)
    {
        gotoxy(5,y_start+i);
        cout<<"* ";
        for(int j=1 ; j<widthMM-1 ; j++)
            cout<<"  ";
        cout<<"*";
    }
    gotoxy(5,y_start+i);
    for(int i=0 ; i<=widthMM-1 ; i++)
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
    cout <<"Student Menu    ---  <<Feeding atuomation>>";
    gotoxy(12, y_start+5);
    cout <<"1 _ show StudentInfo";

    gotoxy(12, y_start+7);
    cout <<"2 _ check Balance";

    gotoxy(12, y_start+9);
    cout <<"3 _ view Reservation";

    gotoxy(12, y_start+11);
    cout << "4 _ view ShappingCast";

    gotoxy(12, y_start+13);
    cout <<"5 _ add To ShoppingCart";

    gotoxy(12, y_start+15);
    cout << "6 _ confirm ShoppingCart";

    gotoxy(12, y_start+17);
    cout << "7 _ remove ShoppingCartItem";

    gotoxy(12, y_start+19);
    cout << "8 _ increase Balance";

    gotoxy(12, y_start+21);
    cout << "9 _ view Recent Transactions";

    gotoxy(12, y_start+23);
    cout << "10 _ cancel Reservation";

    gotoxy(12, y_start+26);
    cout << "11 _ exit";

    gotoxy(12, y_start+29);
    cout<<"Enter Keys : ( 1 to 9 ) ";


   /* while (!sw_MainMenu)
    {
      if (kbhit())
      {
          n = getch();
          if(n >= 1 && n <= 9)
            Action(n);
        else
            gotoxy(12,y_start+31);
            cout << "The number is not valid!";

      }
    }
  }*/
//
}
   
void Panel::showStudentInfo(StudentSession::SessionManager& s)
{
    system("cls");
    drawBox(0, 0, 40, 15);
    gotoxy(20, 17);
    cout << "Student information :" << endl;
    s.currentStudent()->print();


}

void Panel::checkBalance(StudentSession::SessionManager& s)
{
    system("cls");
    drawBox(0, 0, 40, 15);
    gotoxy(20, 17);
    cout << "your balance : " << s.currentStudent()->getBalance() << "toman";
}

void Panel::viewReservation(StudentSession::SessionManager& s)
{
    system("cls");
    drawBox(0, 0, 40, 15);
    gotoxy(20, 17);
    cout << "Definite reservation :";
    s.currentStudent()->getReserves().print();
}

void Panel::viewShappingCart(ShoppingCart *s)
{
    system("cls");
    drawBox(0, 0, 40, 15);
    gotoxy(20, 17);
    cout <<"Temporary reservation :" << endl;
    for (auto add = s->getReservations().begin(); add != s->getReservations().end(); add++)
    {
        add->print();
    }
}

void Panel::addToShoppingCart()
{

}

void Panel::confirmShoppingCart()
{

}

void Panel::removeShoppingCartItem(StudentSession::SessionManager& s)
{
    int ID;
    system("cls");
    drawBox(0, 0, 40, 15);
    gotoxy(20, 17);
    cout << "Enter the reservationID you want to remove.";
    cin >> ID;
    s.shoppingCart()->removeReservation(ID);

}

void Panel::increaseBalance(StudentSession::SessionManager& s)
{
    float amount;
    system("cls");
    drawBox(0, 0, 40, 15);
    gotoxy(20, 17);
    cout << "Enter the amount.";
    cin >> amount;
    if (amount <= 0) 
    {
        throw invalid_argument("Amount must be greater than zero.");
    }
    else
    {
        float f = s.currentStudent()->getBalance();
        f += amount;
        s.currentStudent()->setBalance(f);
    }
}

void Panel::viewRecentTransactions()
{

}

void Panel::cancelReservation(int)
{
    
}

void Panel::exit()
{
     system("cls");
    cout << "";
    std::exit(0);
}