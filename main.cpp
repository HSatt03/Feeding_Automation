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
void Reservation::print()const
{
    cout << "reservation id : " << _reservation_id;
    cout << endl;
    _student.print();
    cout << endl;
    _dHall.print();
    cout << "endl";
    _meal.print();
    cout << "\nstatus : " << _status;
    cout << "\ncreaded at : ";
    tm* localTime = localtime(&_created_at);
    char buffer1[80];
    char buffer2[80];
    strftime(buffer1, sizeof(buffer1), "%H:%M" , localTime);
    strftime(buffer2, sizeof(buffer2), "%Y-%m-%d" , localTime);
    cout << buffer1 <<" " << buffer2 << endl;
}

bool Reservation::cancel()
{
    if(_status == CANCELLED)
    return true;
    else
    return false;
}

bool Reservation::operator==(Reservation ob)
{
    return(_reservation_id == ob._reservation_id
           && _student == ob._student
           && _dHall == ob._dHall
           && _meal == ob._meal
           && _status == ob._status
           && _created_at == ob._created_at);
}
ostream& operator<<(ostream& os, const Enum2& num)
{
    switch(num)
    {
        case FAILED:
            os << "FAILED";
            break;
        case CANCELLED:
            os << "CANCELLED";
            break;
        case SUCCESSFULL:
            os << "SUCCESSFULL";
            break;
        default:
            os << "Unkown!!!";
    }
    return os;
}
enum Enum1
{
    FIRST_GROUP,
    SECOND_GROUP,
    THRID_GROUP,
};

class Meal
{
public:
    Meal(int = 0, string = "NAME", float = 0.0, Enum1 = FIRST_GROUP);

    void setMeal_id(int);
    void setName(string);
    void setPrice(float);
    void setMeal_type(Enum1);
    void setSide_item(vector<string>);

    void print();
    void update_price(float);
    void add_side_item(string);
    bool operator==(Meal);
    friend ostream& operator<<(ostream&, const Enum1&);

    int getMeal_id()const 
    {
        return _meal_id;
    }
    string getName()const 
    {
        return _name;
    }
    float getPrice()const
    {
        return _price;
    }
    Enum1 getMeal_type()const
    {
        return _meal_type;
    }
    vector<string> getSide_item()const
    {
        return _side_item;
    }

private:
    int _meal_id;
    string _name;
    float _price;
    Enum1 _meal_type;
    vector<string> _side_item;
};
Meal::Meal(int m, string n, float p, Enum1 mt)
{
    setMeal_id(m);
    setName(n);
    setPrice(p);
    setMeal_type(mt);
}

void Meal::setMeal_id(int m) 
{
    if(m > 0)
    {
        _meal_id = m;
    }
    else
    {
        throw invalid_argument("Incorrect value for meal_id!!!");
    }
}

void Meal::setName(string name)
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

void Meal::setPrice(float p)
{
    if(p > 0.0)
    {
        _price = p;
    }
    else
    {
        throw invalid_argument("Incorrect value for price!!!");
    }
}

void Meal::setMeal_type(Enum1 e)
{ 
    if(e == FIRST_GROUP || e == SECOND_GROUP || e == THRID_GROUP)
    {
        _meal_type = e;
    }
    else
    {
        throw invalid_argument("Incorrect value for meal_type!!!");
    }
}

void Meal::setSide_item(vector<string> si)
{
    _side_item = si;
}
void Meal::print()
{
    cout << "meal id : " << _meal_id;
    cout << "\nmeal name : " << _name;
    cout << "\nmeal price : " << _price;
    cout << "\nmeal type : " << _meal_type;
    cout << "\nside item : ";
    for (int i=0 ; i < _side_item.size() ; ++i)
    {
            cout << _side_item[i] << " , ";
    } 
}

void Meal::update_price(float new_price)
{
    setPrice(new_price);
}

void Meal::add_side_item(string item)
{
    _side_item.push_back(item);
}

bool Meal::operator==(Meal ob)
{
    return(_meal_id == ob._meal_id
            && _name == ob._name
            && _price == ob._price
            && _meal_type == ob._meal_type
            && _side_item == ob._side_item);
}
ostream& operator<<(ostream& os, const Enum1& num)
{
    switch(num)
    {
        case FIRST_GROUP:
            os << "FIRST_GROUP";
            break;
        case SECOND_GROUP:
            os << "SECOND_GROUP";
            break;
        case THRID_GROUP:
            os << "THRID_GROUP";
            break;
        default:
            os << "Unknown!!!";
    }
    return os;
}

class DiningHall
{
public:
    DiningHall(int, string, string, int);
    void setHallId(int);
    void setName(string);
    void setAddress(string);
    void setCapacity(int);
    void print()const;
    bool operator==(DiningHall);
    int getHallId()const
    {
        return _hall_id;
    }
    string getName()const
    {
        return _name;
    }
    string getAddress()const
    {
        return _address;
    }
    int getCapacity()const
    {
        return _capacity;
    }

private:
    int _hall_id;
    string _name;
    string _address;
    int _capacity;
};

DiningHall::DiningHall(int hall_id = 2, string name = "Sadaf", string address = "Next to the Central Library", int capacity = 100)
{
    _hall_id = hall_id;
    _name = name;
    _address = address;
    _capacity = capacity;
}
void DiningHall::setHallId(int hall_id)
{
    if(hall_id == 1 && hall_id == 2)
    {
        _hall_id = hall_id;
    }
    else 
    {
        throw invalid_argument("Incorect value for hall_id!!!");
    }
}
void DiningHall::setName(string name)
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
void DiningHall::setAddress(string address)
{
    _address = address;
}
void DiningHall::setCapacity(int capacity)
{
    if(capacity > 0)
    {
        _capacity = capacity;
    }
}

void DiningHall::print()const
{
    cout << "Name: " << _name << 
                            "\nHall Id: " << _hall_id << 
                                                    "\nAddress: " << _address << 
                                                                            "\nCapacity: " << _capacity << endl;            
}