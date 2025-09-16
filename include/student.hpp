#ifndef STUDENT_HPP
#define STUDENT_HPP

#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include "transaction.hpp"
#include "meal.hpp"
#include "user.hpp"
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

class User;
class Reservation;

class Student : public User
{
public:
    Student(int = 0, string = "", string = "", string = "", string = "", string = "4031226078", string = "", float = 0, bool = 0);

    void setStudentId(string);
    void setEmail(string);
    void setBalance(float);
    void setIsActive(bool);
    void setReservations(vector<Reservation*>);
    void setTransactions(const vector<Transaction>&);
    void addReservation(Reservation*);

    void print()const;
    void reserveMeal(Meal*);
    bool cancelReservation(Reservation*);
    bool isActive();
    void activate();
    void deactivate();
    string getType();
    bool operator==(Student);
    void addTransaction(const Transaction&);
    string trim(const string&);

    string getStudentId()const
    {
        return _student_id;
    }
    string getEmail()const
    {
        return _email;
    }
    float getBalance()const
    {
        return _balance;
    }
    bool getIsActive()const
    {
        return _is_active;
    }
    vector<Reservation*>& getReserves()
    {
        return _reservations;
    }
    const vector<Transaction>& getTransactions() const
    {
        return _transactions;
    }

private:
    string _student_id;
    string _email;
    float _balance;
    bool _is_active;
    vector<Reservation*>_reservations;
    vector<Transaction> _transactions;
};

namespace nlohmann
{
    template<>
    struct adl_serializer<Student>
    {
        static void to_json(json& j, const Student& s)
        {
                j = static_cast<const User&>(s);
                j["studentID"] = s.getStudentId();
                j["email"] = s.getEmail();
                j["balance"] = s.getBalance();
                // برای رزروها (Reservation*) بهتره فقط شناسه یا اسم ذخیره بشه
                // فعلا ردش می‌کنیم یا بعدا ID بذاریم
                // {"reservations", s.getReserves()},
                j["transactions"] = s.getTransactions();
                // 👆 شرطش اینه Transaction هم adl_serializer داشته باشه

        }
        static void from_json(const json& j, Student& s)
        {
            // اول داده‌های User رو بارگذاری کن
            User& u = s; // upcast
            u = j.get<User>();
            
            // بعد فیلدهای خودش رو
            s.setStudentId(j.at("studentID").get<string>());
            s.setEmail(j.at("email").get<string>());
            s.setBalance(j.at("balance").get<float>());
            s.setTransactions(j.at("transactions").get<vector<Transaction>>());
        }
    };
}


#endif