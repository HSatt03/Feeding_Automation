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
#include "logsystem.hpp"
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
        exit(*Student);
        break;
    }
}

void Panel::showMenu(StudentSession::SessionManager *Student)
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


    while (!sw_MainMenu)
    {
      if (kbhit())
      {
          int n = getch();
          if(n >= 1 && n <= 9)
            Action(n, Student);
        else
            gotoxy(12,y_start+31);
            cout << "The number is not valid!";

      }
    }
  }
   
void Panel::showStudentInfo(StudentSession::SessionManager& s)
{
    system("cls");
    drawBox(0, 0, 40, 15);
    gotoxy(20, 17);
    string studentID = s.currentStudent()->getStudentId();
    logger.addLog("Student " + studentID + " opened student info.", "INFO");
    cout << "Student information :" << endl;
    s.currentStudent()->print();
}

void Panel::checkBalance(StudentSession::SessionManager& s)
{
    system("cls");
    drawBox(0, 0, 40, 15);
    gotoxy(20, 17);
    string studentID = s.currentStudent()->getStudentId();
    logger.addLog("Student " + studentID + " checked balance.", "INFO");
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
        string studentID = s.currentStudent()->getStudentId();
        logger.addLog("Student " + studentID + " viewed reservations.", "INFO");
        if (R) R->print(); // چک کن null نباشه
    }
}

void Panel::viewShappingCart(StudentSession::SessionManager& s)
{
    system("cls");
    drawBox(0, 0, 40, 15);
    gotoxy(20, 17);
    cout <<"Temporary reservation :" << endl;
    for (auto& r : s.shoppingCart()->getReservations()) 
    {
        string studentID = s.currentStudent()->getStudentId();
        logger.addLog("Student " + studentID + " viewed shopping cart.", "INFO");
        r.print();
    }
}

void Panel::addToShoppingCart(StudentSession::SessionManager& s)
{
    system("cls");
    drawBox(0, 0, 50, 20);
    string studentID = s.currentStudent()->getStudentId();
    // ---------- Read meals file ----------
    string mealsFile = ConfigPaths::instance().getMealsJson().string();
    ifstream mealStream(mealsFile);
    if (!mealStream.is_open()) {
        cerr << "Error opening meals file: " << mealsFile << "\n";
        logger.addLog("Student " + studentID + " failed to open meals file.", "ERROR");
        // delete selectedHall;
        return;
    }

    vector<Meal> meals;
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
    cout << "\nAvailable meals:\n";
    for (auto& meal : meals) {
        cout << meal.getMeal_id() << " - " << meal.getName()
                  << " (" << meal.getPrice() << " Toman)\n";
    }

    int mealChoice;
    cout << "Enter meal ID: ";
    cin >> mealChoice;

    auto mealIt = find_if(meals.begin(), meals.end(), [mealChoice](Meal& m){
        return m.getMeal_id() == mealChoice;
    });
    if (mealIt == meals.end()) 
    {
        logger.addLog("Student " + studentID + " selected invalid meal ID.", "WARNING");
        cout << "Invalid meal selected!\n";
        // delete selectedHall();
        return;
    }
    Meal* selectedMeal = new Meal(*mealIt);

    // ---------- Read dining halls file ----------
    string hallFile = ConfigPaths::instance().getDiningHallsJson().string();
    ifstream hallStream(hallFile);
    if (!hallStream.is_open()) 
    {
        logger.addLog("Student " + studentID + " failed to open dining halls file.", "ERROR");
        cerr << "Error opening dining halls file: " << hallFile << "\n";
        return;
    }

    vector<DiningHall> halls;
    //string line;

    // Skip header
    getline(hallStream, line);

    while (getline(hallStream, line)) 
    {
        stringstream ss(line);
        string idStr, name, genderStr, address, capStr;

        getline(ss, idStr, ',');
        getline(ss, name, ',');
        getline(ss, genderStr, ',');
        getline(ss, address, ',');
        getline(ss, capStr, ',');

        int id = std::stoi(idStr);
        int cap = std::stoi(capStr);
        Gender g = DiningHall::stringToGender(genderStr);

        halls.emplace_back(id, name, address, cap);
        halls.back().setGender(g);
    }

    // ---------- Select dining hall ----------
    cout << "\nAvailable dining halls:\n";
    for (auto& hall : halls) {
        cout << hall.getHallId() << " - " << hall.getName()
                  << " (" << (hall.getGender() == Gender::MALE ? "Male" : "Female") << ")\n";
    }

    int hallChoice;
    cout << "Enter dining hall ID: ";
    cin >> hallChoice;

    auto hallIt = find_if(halls.begin(), halls.end(), [hallChoice](DiningHall& h)
    {
        return h.getHallId() == hallChoice;
    });
    if (hallIt == halls.end()) 
    {
        logger.addLog("Student " + studentID + " selected invalid dining hall ID.", "WARNING");
        cout << "Invalid dining hall selected!\n";
        return;
    }
    DiningHall* selectedHall = new DiningHall(*hallIt);

    // ---------- Create reservation ----------
    Reservation reservation(selectedHall, selectedMeal, std::rand(), RStatus::PENDING);

    // ---------- Add to shopping cart ----------
    auto& session = StudentSession::SessionManager::instance();
    if (session.shoppingCart()) {
        session.shoppingCart()->addReservation(reservation);
        logger.addLog("Student " + studentID + " added meal " + to_string(mealChoice) + " to shopping cart in dining hall: " + selectedHall->getName(),
    "INFO");
        cout << "✅ Meal added to shopping cart!\n";
    } else {
        cout << "❌ Error: Shopping cart not available!\n";
        logger.addLog("Student " + studentID + " shopping cart unavailable.", "ERROR");
        // Free heap memory since reservation was not stored:
        delete selectedHall;
        delete selectedMeal;
    }
}

void Panel::confirmShoppingCart(StudentSession::SessionManager& s)
{
    string studentID = s.currentStudent()->getStudentId();
    system("cls");
    drawBox(0, 0, 40, 15);
    gotoxy(20, 17);
    vector<Transaction> transactions;  // استفاده از وکتور به پیشنهاد چت جی پی تی برای دخیره تراکنش ها
    try 
    {
        Transaction t = s.shoppingCart()->confirm();
        transactions.push_back(t);
        logger.addLog("Student " + studentID + " confirmed shopping cart: " , "INFO");
        cout << "Shopping cart confirmed successfully.\n";
        t.print(); // نمایش جزئیات تراکنش
    } 
    catch (const exception& e) 
    {
        logger.addLog("Student " + studentID + " failed to confirm shopping cart: " + string(e.what()), "ERROR");
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
    string studentID = s.currentStudent()->getStudentId();
    logger.addLog("Student " + studentID + " removed reservation ID " + to_string(ID) + " from shopping cart.", "INFO");
}

void Panel::increaseBalance(StudentSession::SessionManager& s)
{
    string studentID = s.currentStudent()->getStudentId();
    float amount;
    Transaction t;
    system("cls");
    drawBox(0, 0, 40, 15);
    gotoxy(20, 17);
    cout << "Enter the amount.";
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
    
    t.setTransactionID(t.getTransactionID()+1);
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
    drawBox(0, 0, 80, 20);
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
        cout << "ID: " << t.getTransactionID()
             << " Code: " << t.getTrackingCode()
             << " Amount: " << t.getAmount()
             << " Type: " << (t.getType() == TransactionType::TRANSFER ? "Transfer" : "Payment")
             << " Status: " << (t.getStatus() == TransactionStatus::COMPLETED ? "Completed" :
                                t.getStatus() == TransactionStatus::PENDING ? "Pending" : "Failed");
            time_t createdAt = t.getCreatedAT();       // مقدار رو بگیر
            cout << " Time: " << ctime(&createdAt);    // آدرس بده به ctime
                    
        line++;
        if (line > 18) 
        break; // محدود به تعداد خط
        logger.addLog("Student " + studentID + " viewed recent transactions.", "INFO");


    }

    //gotoxy(2, 19);
    //system("pause");
}

void Panel::cancelReservation(StudentSession::SessionManager& s)
{
    string studentID = s.currentStudent()->getStudentId();
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
                logger.addLog("Student " + studentID + " cancelled reservation ID " + to_string(id) + " and refunded " + to_string(price), "INFO");
                cout << "Reservation cancelled successfully and amount refunded.\n";
                return;
            }
            else
            {
                gotoxy(20, 19);
                logger.addLog("Student " + studentID + " attempted to cancel already cancelled reservation ID " + to_string(id), "WARNING");
                cout << "This reservation is already cancelled!\n";
                return;
            }
        }
    }

    gotoxy(20, 19);
    logger.addLog("Student " + studentID + " attempted to cancel non-existent reservation ID " + to_string(id), "WARNING");
    cout << "Reservation ID not found!\n";
}

void Panel::exit(StudentSession::SessionManager& s)
{
    system("cls");
    string studentID = s.currentStudent()->getStudentId();
    logger.addLog("Student " + studentID + " exited panel.", "INFO");
    cout << "";
    std::exit(0);
}