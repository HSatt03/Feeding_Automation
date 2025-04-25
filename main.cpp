#include <iostream>
#include <string>
#include <vector>
class Student
{
public:
    Student(int user_id = 12, string student_id = "4022559082", string name = "name", string email = "name20002001@gmail.com", float balance = 100000, bool is_active = false);

    void setUserId(int);
    void setStudentId(string);
    void setName(string);
    void setEmail(string);
    void setBalance(float);
    void setIsActive(bool);
    void setReservations(vector<Reservation>);

    void print()const;
    void reserveMeal(Meal);
    bool cancelReservation(Reservation);
    bool operator==(Student);
    int getUserId()const
    {
        return _user_id;
    }
    string getStudentId()const
    {
        return _student_id;
    }
    string getName()const
    {
        return _name;
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
    const vector<string>& getReservations()const
    {
        return _reservations;
    }

private:
    int _user_id;
    string _student_id;
    string _name;
    string _email;
    float _balance;
    bool _is_active;
    vector<Reservation*>_reservations;
};
////////////////////////////////////////
Student::Student(int user_id, string student_id, string name, string email, float balance, bool is_active)
{
    setUserId(user_id);  
    setStudentId(student_id);
    setName(name);
    setEmail(email);
    setBalance(balance);
    setIsActive(is_active);
}

void Student::setUserId(int user_id)
{
    if(user_id > 0)
    {
        _user_id = user_id;
    }
}

void Student::setStudentId(string student_id)
{
    if(student_id.length() == 10)
    {
        _student_id = student_id;
    }
    else
    {
        throw invalid_argument("Incorrect value for strudent_id!!!");
    }
}

void Student::setName(string name)
{
    int value = name.length();
    for(int i = 0; i < value; i++)
    {
        if(!isalpha(name[i]))
        {
            throw invalid_argument("Incorrect name!!!");
        }
    }
    _name = name;
}

void Student::setEmail(string email)
{
    bool flag;
    string s1;
    int value = email.length();
    for(int i = 0; i < value; i++)
    {
        if(email[i] == '@')
        {
            flag = true;
            s1 = email.substr(i, 10);
            if(s1 == "@gmail.com")
            {
                _email = email;
            } 
            else
            {
                throw invalid_argument("Incorrect email!!!");
            }
        }
        else if(flag == false && i == value - 1)
        {
            throw invalid_argument("Incorrect email!!!");
        }
    }
}

void Student::setBalance(float balance)
{
    if(balance >= 0)
    {
        _balance = balance;
    }
    else 
    {
        throw invalid_argument("Incorrect value for balance!!!");
    }
}

void Student::setIsActive(bool is_active)
{
    _is_active = is_active;
}

void Student::setReservations(vector<Reservation>reserve)
{
    _reservations = reserve;
}