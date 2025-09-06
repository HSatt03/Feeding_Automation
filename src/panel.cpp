#include <iostream>
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
#include "logsystem.hpp"
#include "consoleMessageBox.hpp"

using namespace std;
using namespace StudentSession;

void gotoxy(int x, int y);

void drawBox(int x, int y, int width, int height);

LogSystem logger(ConfigPaths::instance().getStudentsLogFile().string());

void Panel::Action(int n, StudentSession::SessionManager *Student)
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
        cout << "Bye Bye!!!";
        break;
    }
}

bool Panel::showMenu(StudentSession::SessionManager *Student)
{
    auto& msgBox = ConsoleMessageBox::instance();
    msgBox.setPosition(7, 20, 100, 5);
    int hightMM = 34, widthMM = 36, y_start = 3;

    while (1)
    {
        system("cls"); // پاک کردن صفحه قبل از چاپ منو

        // رسم چارچوب منو
        gotoxy(5,y_start);
        for(int i=0 ; i<widthMM ; i++) cout<<"* ";
        for(int i=1 ; i<hightMM-1 ; i++)
        {
            gotoxy(5,y_start+i);
            cout<<"* ";
            for(int j=1 ; j<widthMM-1 ; j++) cout<<"  ";
            cout<<"*";
        }
        gotoxy(5, y_start + hightMM - 1);
        for(int i=0 ; i<widthMM ; i++) cout << "* ";

        // چاپ گزینه‌ها
        gotoxy(19,y_start+2);
        cout <<"Student Menu    ---  <<Feeding automation>>";
        gotoxy(12, y_start+5);  cout <<"1 _ Show StudentInfo";
        gotoxy(12, y_start+7);  cout <<"2 _ Check Balance";
        gotoxy(12, y_start+9);  cout <<"3 _ View Reservation";
        gotoxy(12, y_start+11); cout << "4 _ View ShappingCart";
        gotoxy(12, y_start+13); cout <<"5 _ Add To ShoppingCart";
        gotoxy(12, y_start+15); cout << "6 _ Confirm ShoppingCart";
        gotoxy(12, y_start+17); cout << "7 _ Remove ShoppingCartItem";
        gotoxy(12, y_start+19); cout << "8 _ Increase Balance";
        gotoxy(12, y_start+21); cout << "9 _ View Recent Transactions";
        gotoxy(12, y_start+23); cout << "10 _ Cancel Reservation";
        gotoxy(12, y_start+25); cout << "11 _ Sign out of the user account";

        gotoxy(12, y_start+28);
        cout<<"Choose your option (1-11): ";

        int n;
        cin >> n;

        if(n >= 1 && n <= 11)
        {

            system("cls");
            if(n == 11) 
            {
                return false;
            }
            else
            {
                // صبر تا کاربر Enter بزند قبل از چاپ دوباره منو
                Action(n, Student); // اجرای عملیات انتخاب شده
                drawBox(83, 22, 35, 3);
                gotoxy(85, 23);
                cout << "Press Enter to return to menu...";
                getch();
            }
        }
        else
        {
            gotoxy(12, y_start+31);
            cout << "Invalid option! Press Enter to try again...";
            getch();
        }
    }
}
   
void Panel::showStudentInfo(StudentSession::SessionManager& s)
{
    system("cls");
    drawBox(0, 0, 40, 15);
    gotoxy(10, 1);
    string studentID = s.currentStudent()->getStudentId();
    logger.addLog("Student " + studentID + " opened student info.", "INFO");
    cout << "Student information :" << endl;
    s.currentStudent()->print();

}

void Panel::checkBalance(StudentSession::SessionManager& s)
{
    system("cls");
    drawBox(0, 0, 35, 6);
    gotoxy(3, 3);
    string studentID = s.currentStudent()->getStudentId();
    logger.addLog("Student " + studentID + " checked balance.", "INFO");
    cout << "your balance : " << s.currentStudent()->getBalance() << " toman";
}

void Panel::viewReservation(StudentSession::SessionManager& s)
{
    int i = 2;
    int j = 3;
    system("cls");
    drawBox(0, 0, 70, 100);
    gotoxy(22, 1);
    cout << "Definite reservation :" << endl;
    for (Reservation* R : s.currentStudent()->getReserves()) // روش for-each
    {
        string studentID = s.currentStudent()->getStudentId();
        logger.addLog("Student " + studentID + " viewed reservations.", "INFO");
        if (R) R->print(i, j); // چک کن null نباشه
        j+=8;
    }
}

void Panel::viewShappingCart(StudentSession::SessionManager& s)
{
    system("cls");
    drawBox(0, 0, 70, 100);
    gotoxy(22, 1);
    cout <<"Temporary reservation :" << endl;
    s.shoppingCart()->viewShoppingCartItems();
    string studentID = s.currentStudent()->getStudentId();
    logger.addLog("Student " + studentID + " viewed shopping cart.", "INFO");
}

void Panel::addToShoppingCart(StudentSession::SessionManager& s)
{
    auto& msgBox = ConsoleMessageBox::instance();
    msgBox.setPosition(7, 20, 100, 5);
    system("cls");
    string studentID = s.currentStudent()->getStudentId();
    drawBox(0, 0, 60, 110);

    // ---------- Read meals file ----------
    string mealsFile = ConfigPaths::instance().getMealsJson().string();
    ifstream mealStream(mealsFile);
    if (!mealStream.is_open()) 
    {
        msgBox.addMessage("Error opening meals file: " + mealsFile, MsgColor::RED);
        msgBox.showMessages();
        system("pause");
        msgBox.clear();
        logger.addLog("Student " + studentID + " failed to open meals file.", "ERROR");
        return;
    }

    nlohmann::json jMeals;
    mealStream >> jMeals;
    vector<Meal> meals = jMeals.get<vector<Meal>>();  // ✅ استفاده از سریالایزر

    // ---------- Select meal ----------
    int i, j;
    i = 3;
    j = 4;
    gotoxy(17, 2);
    cout << "Available meals:";
    for (auto& meal : meals) 
    {
        gotoxy(i, j);
        cout << "Meal ID: " << meal.getMeal_id();
        gotoxy(i, j+=1);
        cout << "Meal Name: " << meal.getName();
        gotoxy(i, j+=1);
        cout << "Meal Price: " << meal.getPrice() << " Toman";
        j+=2;
    }

    int mealChoice;
    gotoxy(i, j);
    cout << "Enter meal ID: ";
    cin >> mealChoice;

    auto mealIt = find_if(meals.begin(), meals.end(), [mealChoice](Meal& m)
    {
        return m.getMeal_id() == mealChoice;
    });
    if (mealIt == meals.end()) 
    {
        logger.addLog("Student " + studentID + " selected invalid meal ID.", "WARNING");
        msgBox.addMessage("Invalid meal selected!", MsgColor::RED);
        msgBox.showMessages();
        system("pause");
        msgBox.clear();
        return;
    }
    Meal* selectedMeal = new Meal(*mealIt);

    // ---------- Read dining halls file ----------
    string hallFile = ConfigPaths::instance().getDiningHallsJson().string();
    ifstream hallStream(hallFile);
    if (!hallStream.is_open()) 
    {
        logger.addLog("Student " + studentID + " failed to open dining halls file.", "ERROR");
        msgBox.addMessage("Error opening dining halls file: " + hallFile, MsgColor::RED);
        msgBox.showMessages();
        system("pause");
        msgBox.clear();
        return;
    }

    nlohmann::json jHalls;
    hallStream >> jHalls;
    vector<DiningHall> halls = jHalls.get<vector<DiningHall>>();  // ✅ سریالایزر

    // ---------- Select dining hall ----------
    gotoxy(14, j+=2);
    cout << "Available dining halls:";
    j+=2;
    for (auto& hall : halls) 
    {
        gotoxy(i, j);
        cout << "Hall ID: " << hall.getHallId();
        gotoxy(i, j+=1);
        cout << "Hall Name: " << hall.getName();
        gotoxy(i, j+=1);
        cout << "Hall Gender: "<< (hall.getGender() == Gender::MALE ? "Male" : "Female");
        j+=2;
    }

    int hallChoice;
    gotoxy(i, j);
    cout << "Enter dining hall ID: ";
    cin >> hallChoice;

    auto hallIt = find_if(halls.begin(), halls.end(), [hallChoice](DiningHall& h)
    {
        return h.getHallId() == hallChoice;
    });
    if (hallIt == halls.end()) 
    {
        logger.addLog("Student " + studentID + " selected invalid dining hall ID.", "WARNING");
        msgBox.addMessage("Invalid dining hall selected!", MsgColor::RED);
        msgBox.showMessages();
        system("pause");
        msgBox.clear();
        return;
    }
    DiningHall* selectedHall = new DiningHall(*hallIt);

    // ---------- Create reservation ----------
    static int count_reservation = 0;
    Reservation* reservation = new Reservation(selectedHall, selectedMeal, count_reservation, RStatus::PENDING);
    count_reservation += 1;

    // ---------- Add to shopping cart ----------
    auto& session = StudentSession::SessionManager::instance();
    if (session.shoppingCart()) 
    {
        session.shoppingCart()->addReservation(*reservation);
        logger.addLog("Student " + studentID + " added meal " + to_string(mealChoice) + " to shopping cart in dining hall: " + selectedHall->getName(),
    "INFO");
        msgBox.addMessage("Meal added to shopping cart!", MsgColor::GREEN);
        msgBox.showMessages();
        system("pause");
        msgBox.clear();
    } 
    else 
    {
        msgBox.addMessage("Error: Shopping cart not available!", MsgColor::RED);
        msgBox.showMessages();
        system("pause");
        msgBox.clear();
        logger.addLog("Student " + studentID + " shopping cart unavailable.", "ERROR");
        // Free heap memory since reservation was not stored:
        delete selectedHall;
        delete selectedMeal;
    }
}

void Panel::confirmShoppingCart(StudentSession::SessionManager& s)
{
    system("cls");
    drawBox(0, 0, 60, 20);
    gotoxy(2, 1);
        if (!s.shoppingCart() || s.shoppingCart()->getReservations().empty())
    {
        cout << "Shopping cart is empty!" << endl;
        return;
    }

    vector<Transaction> transactions;  // استفاده از وکتور به پیشنهاد چت جی پی تی برای دخیره تراکنش ها
    try 
    {
        Transaction t = s.shoppingCart()->confirm();
        transactions.push_back(t);
        //logger.addLog("Student " + studentID + " confirmed shopping cart: " , "INFO");
        t.print(); // نمایش جزئیات تراکنش
    } 
    catch (const exception& e) 
    {
        //logger.addLog("Student " + studentID + " failed to confirm shopping cart: " + string(e.what()), "ERROR");
        cout << "Error: " << e.what() << endl;
    }
}

void Panel::removeShoppingCartItem(StudentSession::SessionManager& s)
{
    int ID;
    system("cls");
    drawBox(0, 0, 50, 8);
    gotoxy(2, 1);
    string studentID = s.currentStudent()->getStudentId();
    cout << "Enter the reservationID you want to remove:";
    cin >> ID;
    if(s.shoppingCart()->removeReservation(ID))
    { 
        string studentID = s.currentStudent()->getStudentId();
        logger.addLog("Student " + studentID + " removed reservation ID " + to_string(ID) + " from shopping cart.", "INFO");
        gotoxy(2, 3);
        cout << "Reservation removed successfully.";
    }
    else
    {
        gotoxy(2, 3);
        cout << "ReservationID not found.";
    }
}

void Panel::increaseBalance(StudentSession::SessionManager& s)
{
    string studentID = s.currentStudent()->getStudentId();
    float amount;
    Transaction t;
    system("cls");
    drawBox(0, 0, 40, 15);
    gotoxy(2, 1);
    cout << "Enter the amount:";
    cin >> amount;
    if (amount <= 0) 
    {
        logger.addLog("Student " + studentID + " attempted to increase balance with invalid amount: " + to_string(amount), "WARNING");
        throw invalid_argument("Amount must be greater than zero.");
    }
    else
    {
        float f = s.currentStudent()->getBalance();
        f += amount;
        s.currentStudent()->setBalance(f);
    }
    
    t.setTransactionID(t.getTransactionID());
    t.setTrackingCode(to_string(rand() % 90000 + 10000));
    t.setAmount(amount);
    t.setType(TransactionType::TRANSFER);
    t.setStatus(TransactionStatus::COMPLETED);
    t.setCreatedAT(time(0));
    t.print();
    logger.addLog("Student " + studentID + " increased balance by " + to_string(amount) + ". Transaction ID: " + to_string(t.getTransactionID()), "INFO");

    Student* student = StudentSession::SessionManager::instance().currentStudent();
    if (student)
    {
        student->addTransaction(t);  // دخیره کردن در کلاس student
    }             
}

void Panel::viewRecentTransactions(StudentSession::SessionManager& s)
{
    string studentID = s.currentStudent()->getStudentId();
    system("cls"); // پاک کردن صفحه
    drawBox(0, 0, 110, 20);
    gotoxy(2, 1);
    cout << "Recent Transactions:\n";

    const vector<Transaction>& transactions = s.currentStudent()->getTransactions();
    if (transactions.empty())
    {
        gotoxy(2, 3);
        logger.addLog("Student " + studentID + " viewed recent transactions: none found.", "INFO");
        cout << "No transactions found.\n";
        return;
    }

    int line = 3;
    for (const auto& t : transactions)
    {
        gotoxy(2, line++);
        cout << "ID: " << t.getTransactionID() << ","
             << " Code: " << t.getTrackingCode() << ","
             << " Amount: " << t.getAmount() << ","
             << " Type: " << (t.getType() == TransactionType::TRANSFER ? "Transfer" : "Payment") << ","
             << " Status: " << (t.getStatus() == TransactionStatus::COMPLETED ? "Completed" :
                                t.getStatus() == TransactionStatus::PENDING ? "Pending" : "Failed") << ",";
            time_t createdAt = t.getCreatedAT();       // مقدار رو بگیر
            cout << " Time: " << ctime(&createdAt);    // آدرس بده به ctime
                    
        line++;
        if (line > 18) 
        break; // محدود به تعداد خط
        logger.addLog("Student " + studentID + " viewed recent transactions.", "INFO");


    }
}

void Panel::cancelReservation(StudentSession::SessionManager& s)
{
    string studentID = s.currentStudent()->getStudentId();
    int id;
    system("cls");
    drawBox(0, 0, 60, 8);
    gotoxy(2, 1);
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

                gotoxy(2, 3);
                logger.addLog("Student " + studentID + " cancelled reservation ID " + to_string(id) + " and refunded " + to_string(price), "INFO");
                cout << "Reservation cancelled successfully and amount refunded.\n";
                return;
            }
            else
            {
                gotoxy(2, 3);
                logger.addLog("Student " + studentID + " attempted to cancel already cancelled reservation ID " + to_string(id), "WARNING");
                cout << "This reservation is already cancelled!\n";
                return;
            }
        }
    }

    gotoxy(2, 3);
    logger.addLog("Student " + studentID + " attempted to cancel non-existent reservation ID " + to_string(id), "WARNING");
    cout << "Reservation ID not found!\n";
}

void Panel::exit(StudentSession::SessionManager& s)
{
    system("cls");
    string studentID = s.currentStudent()->getStudentId();
    logger.addLog("Student " + studentID + " exited panel.", "INFO");
    cout << "Bye Bye!!!  ";
    std::exit(0);
}