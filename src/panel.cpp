#include <iostream>
#include <windows.h>
#include <conio.h>
#include <ctime>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "panel.hpp"
#include "reservation.hpp"
#include "shoppingCart.hpp"
#include "sessionManager.hpp"
#include "transaction.hpp"
#include "student.hpp"
#include "meal.hpp"
#include "diningHall.hpp"
#include "configPaths.hpp"
#include "utils.hpp"

using namespace std;
using namespace StudentSession;

void gotoxy(int x, int y);

void drawBox(int x, int y, int width, int height);

bool Panel::Action(int n, StudentSession::SessionManager *Student)
{
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
        viewShappingCart(*Student);
        break;
    case 5:
        addToShoppingCart(*Student);
        break;
    case 6:
        confirmShoppingCart(*Student);
        break;
    case 7:
        removeShoppingCartItem(*Student);
        break;
    case 8:
        increaseBalance(*Student);
        break;
    case 9:
        viewRecentTransactions(*Student);
        break;
    case 10:
        cancelReservation(*Student);
        break;
    case 11:
        exit();
    }
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
    for (Reservation* R : s.currentStudent()->getReserves()) // روش for-each
    {
        if (R) R->print(); // چک کن null نباشه
    }
}

void Panel::viewShappingCart(StudentSession::SessionManager& s)
{
    system("cls");
    drawBox(0, 0, 40, 15);
    gotoxy(20, 17);
    cout <<"Temporary reservation :" << endl;
    for (auto add = s.shoppingCart()->getReservations().begin(); add != s.shoppingCart()->getReservations().end(); add++)
    {
        add->print();
    }
}

void Panel::addToShoppingCart(StudentSession::SessionManager& s)
{
    system("cls");
    drawBox(0, 0, 50, 20);
    // ---------- Read meals file ----------
    string mealsFile = ConfigPaths::instance().getMealsJson().string();
    ifstream mealStream(mealsFile);
    if (!mealStream.is_open()) {
        cerr << "Error opening meals file: " << mealsFile << "\n";
        // delete selectedHall;
        return;
    }

    std::vector<Meal> meals;
    string line;
    // Skip header
    getline(mealStream, line);

    while (getline(mealStream, line)) {
        stringstream ss(line);
        string idStr, name, priceStr, mealTypeStr, dayStr;

        getline(ss, idStr, ',');
        getline(ss, name, ',');
        getline(ss, priceStr, ',');
        getline(ss, mealTypeStr, ',');
        getline(ss, dayStr, ',');

        int id = stoi(idStr);
        float price = stof(priceStr);
        MealType mealType = Meal::stringToMealType(mealTypeStr);
        ReserveDay day = Meal::stringToReserveDay(dayStr);

        meals.emplace_back(id, name, price, mealType, day, true);
    }

    // ---------- Select meal ----------
    std::cout << "\nAvailable meals:\n";
    for (auto& meal : meals) {
        cout << meal.getMeal_id() << " - " << meal.getName()
                  << " (" << meal.getPrice() << " Toman)\n";
    }

    int mealChoice;
    std::cout << "Enter meal ID: ";
    std::cin >> mealChoice;

    auto mealIt = std::find_if(meals.begin(), meals.end(), [mealChoice](Meal& m){
        return m.getMeal_id() == mealChoice;
    });
    if (mealIt == meals.end()) {
        std::cout << "Invalid meal selected!\n";
        // delete selectedHall();
        return;
    }
    Meal* selectedMeal = new Meal(*mealIt);

    // ---------- Read dining halls file ----------
    std::string hallFile = ConfigPaths::instance().getDiningHallsJson().string();
    std::ifstream hallStream(hallFile);
    if (!hallStream.is_open()) {
        std::cerr << "Error opening dining halls file: " << hallFile << "\n";
        return;
    }

    std::vector<DiningHall> halls;
    std::string line;

    // Skip header
    std::getline(hallStream, line);

    while (std::getline(hallStream, line)) {
        std::stringstream ss(line);
        std::string idStr, name, genderStr, address, capStr;

        std::getline(ss, idStr, ',');
        std::getline(ss, name, ',');
        std::getline(ss, genderStr, ',');
        std::getline(ss, address, ',');
        std::getline(ss, capStr, ',');

        int id = std::stoi(idStr);
        int cap = std::stoi(capStr);
        Gender g = DiningHall::stringToGender(genderStr);

        halls.emplace_back(id, name, address, cap);
        halls.back().setGender(g);
    }

    // ---------- Select dining hall ----------
    std::cout << "\nAvailable dining halls:\n";
    for (auto& hall : halls) {
        std::cout << hall.getHallId() << " - " << hall.getName()
                  << " (" << (hall.getGender() == Gender::MALE ? "Male" : "Female") << ")\n";
    }

    int hallChoice;
    std::cout << "Enter dining hall ID: ";
    std::cin >> hallChoice;

    auto hallIt = std::find_if(halls.begin(), halls.end(), [hallChoice](DiningHall& h){
        return h.getHallId() == hallChoice;
    });
    if (hallIt == halls.end()) {
        std::cout << "Invalid dining hall selected!\n";
        return;
    }
    DiningHall* selectedHall = new DiningHall(*hallIt);

    // ---------- Create reservation ----------
    Reservation reservation(selectedHall, selectedMeal, std::rand(), RStatus::PENDING);

    // ---------- Add to shopping cart ----------
    auto& session = StudentSession::SessionManager::instance();
    if (session.shoppingCart()) {
        session.shoppingCart()->addReservation(reservation);
        std::cout << "✅ Meal added to shopping cart!\n";
    } else {
        std::cout << "❌ Error: Shopping cart not available!\n";
        // Free heap memory since reservation was not stored:
        delete selectedHall;
        delete selectedMeal;
    }
}

void Panel::confirmShoppingCart(StudentSession::SessionManager& s)
{
    system("cls");
    drawBox(0, 0, 40, 15);
    gotoxy(20, 17);
    vector<Transaction> transactions;  // استفاده از وکتور به پیشنهاد چت جی پی تی برای دخیره تراکنش ها
    try 
    {
        Transaction t = s.shoppingCart()->confirm();
        transactions.push_back(t);
        cout << "Shopping cart confirmed successfully.\n";
        t.print(); // نمایش جزئیات تراکنش
    } 
    catch (const exception& e) 
    {
        cout << "Error: " << e.what() << endl;
    }
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
    Transaction t;
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
    
    t.setTransactionID(t.getTransactionID()+1);
    t.setTrackingCode(to_string(rand() % 90000 + 10000));
    t.setAmount(amount);
    t.setType(TransactionType::TRANSFER);
    t.setStatus(TransactionStatus::COMPLETED);
    t.setCreatedAT(time(0));
    t.print();

    Student* student = StudentSession::SessionManager::instance().currentStudent();
    if (student)
    {
        student->addTransaction(t);  // دخیره کردن در کلاس student
    }             
}

void Panel::viewRecentTransactions(StudentSession::SessionManager& s)
{
    system("cls"); // پاک کردن صفحه
    drawBox(0, 0, 80, 20);
    gotoxy(2, 1);
    cout << "Recent Transactions:\n";

    const vector<Transaction>& transactions = s.currentStudent()->getTransactions();
    if (transactions.empty())
    {
        gotoxy(2, 3);
        cout << "No transactions found.\n";
        return;
    }

    int line = 3;
    for (const auto& t : transactions)
    {
        gotoxy(2, line++);
        cout << "ID: " << t.getTransactionID()
             << " Code: " << t.getTrackingCode()
             << " Amount: " << t.getAmount()
             << " Type: " << (t.getType() == TransactionType::TRANSFER ? "Transfer" : "Payment")
             << " Status: " << (t.getStatus() == TransactionStatus::COMPLETED ? "Completed" :
                                t.getStatus() == TransactionStatus::PENDING ? "Pending" : "Failed");
            time_t createdAt = t.getCreatedAT();       // مقدار رو بگیر
            cout << " Time: " << ctime(&createdAt);    // آدرس بده به ctime
                    
        line++;
        if (line > 18) break; // محدود به تعداد خط
    }

    //gotoxy(2, 19);
    //system("pause");
}

void Panel::cancelReservation(StudentSession::SessionManager& s)
{
    int id;
    system("cls");
    drawBox(0, 0, 40, 15);
    gotoxy(20, 17);
    cout << "Enter reservation ID to cancel: ";
    cin >> id;

    vector<Reservation*>& reservations = s.currentStudent()->getReserves();
    for (auto it = reservations.begin(); it != reservations.end(); ++it)
    {
        if ((*it)->getReservation_id() == id)
        {
            if ((*it)->cancel())
            {
                // برگردوندن پول به دانشجو
                float price = (*it)->getMeal().getPrice();
                s.currentStudent()->setBalance(s.currentStudent()->getBalance()+ price);

                // حذف رزرو از لیست
                delete *it; // اگه با new ساخته شده
                reservations.erase(it);

                gotoxy(20, 19);
                cout << "Reservation cancelled successfully and amount refunded.\n";
                return;
            }
            else
            {
                gotoxy(20, 19);
                cout << "This reservation is already cancelled!\n";
                return;
            }
        }
    }

    gotoxy(20, 19);
    cout << "Reservation ID not found!\n";
}

void Panel::exit()
{
     system("cls");
    cout << "";
    std::exit(0);
}