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

void Student::print()const
{
    cout << "Name: " << _name << 
                            "\nUser Id: " << _user_id << 
                                                    "\nStudent Id: " << _student_id << 
                                                                                    "\nEmail: " << _email <<
                                                                                                    "\nBalance: " << _balance << endl;
}

void Student::reserveMeal(Meal meal)
{
    Reservation reserve;
    reserve.Meal(meal);
    _reservations.push_back(reserve);
}

bool Student::cancelReservation(Reservation reserve)
{
    bool success = false;
    for(auto add = _reservations.begin(); add != _reservations.end(); add++)
    {
        if(*add == reserve)
        {
            _reservations.erase(add);
            success = true;
        }
    }
    if(success)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Student::operator==(Student ob)
{
    return(_user_id == ob._user_id
          && _student_id == ob._student_id
          && _name == ob._name
          && _email == ob._email
          && _balance == ob._balance
          && _is_active == ob._is_active);
}
////////////////////////////////////
enum Enum2
{
    FAILED,
    CANCELLED,
    SUCCESSFULL,
};

class Reservation
{
public:
    Reservation(int = 0, Enum2 = FAILED, time_t = time(0)); 

    void setReservation_id(int);
    void setStudent(Student);
    void setDhall(DiningHall);
    void setMeal(Meal);
    void setStatus(Enum2);
    void setTime(time_t);

    int getReservation_id()const
    {
        return _reservation_id;
    }
    Student getStudent()const
    {
        return _student;
    }
    DiningHall getDhall()const
    {
        return _dHall;
    }
    Meal getMeal()const
    {
        return _meal;
    }
    Enum getStatus()const
    {
        return _status;
    }
    time_t getTime()const
    {
        return _created_at;
    }

    void print()const;
    bool cancel();
    bool operator==(Reservation);
    friend ostream& operator<<(ostream& ,const Enum2&);

private:
    int _reservation_id;
    Student _student;
    DiningHall _dHall;
    Meal _meal;
    Enum2 _status;
    time_t _created_at;
};
Reservation::Reservation(int r, Student S, DiningHall d, Meal m, Enum2 s, time_t c)
{
    setReservation_id(r);
    setStudent(S);
    setDhall(d);
    setMeal(m);
    setStatus(s);
    setTime(c);
}

void Reservation::setReservation_id(int r)
{
    if(r > 0)
    {
        reservation_id = r;
    }
    else
    {
        throw invalid_argument("Incorrect value for reservations");
    }
}

void Reservation::setStudent(Student s)
{
    s.setUserId(s.getUserId());
    s.setStudentId(s.getStudentId());
    s.setName(s.getName());
    s.setEmail(s.getEmail());
    s.setBalance(s.getBalance());
    s.setIsActive(s.getIsActive());
}

void Reservation::setDhall(DiningHall d)
{
    d.setHallId(d.getHallId());
    d.setName(d.getName());
    d.setAddress(d.getAddress());
    d.setCapacity(d.getCapacity());
}

void Reservation::setMeal(Meal m)
{
    m.setMeal_id(m.getMeal_id());
    m.setName(m.getName());
    m.setPrice(m.getPrice());
    m.setMeal_type(m.getMeal_type());
}

void Reservation::setStatus(Enum2 s)
{
    _status = s; //بپرسم
}

void Reservation::setTime(time_t t)
{
    if(t > 0)
    {
        _created_at = t;
    }
    else
    {
        throw invalid_argument("Incorrect value for time!!!");
    }
}