#include <string>
#include <iostream>
#include "transaction.hpp"
#include "utils.hpp"

using namespace std;

// int Transaction::_transactionID = 0; 
Transaction::Transaction(int transactionID, string trackingCode, float amount , TransactionType type, TransactionStatus status, time_t createdAT)
{
    setTransactionID(transactionID);
    setTrackingCode(trackingCode);
    setAmount(amount);
    setType(type);
    setStatus(status);
    setCreatedAT(createdAT);
}
void Transaction::setTransactionID(int i)
{
    _transactionID = (i > 0) ? i : 0;
}
void Transaction::setTrackingCode(string s)
{
    _trackingCode = (s.length() == 5) ? s : "00000";
}
void Transaction::setAmount(float f)
{
    _amount = (f > 0) ? f : 0.00;
}
void Transaction::setType(TransactionType t)
{
    if(t == TransactionType::TRANSFER || t == TransactionType::PAYMENT) 
    {
        _type = t;
    }
    else
    {
        throw invalid_argument("Incorrect value for TransactionType!!!");
    }
}
void Transaction::setStatus(TransactionStatus t)
{
    if(t == TransactionStatus::PENDING || t == TransactionStatus::COMPLETED || t == TransactionStatus::FIALED) 
    {
        _status = t;
    }
    else
    {
        throw invalid_argument("Incorrect value for TransactionStatus!!!");
    }
}
void Transaction::setCreatedAT(time_t t)
{
    if(t > 0)
    {
        _createdAT = t;
    }
    else
    {
        throw invalid_argument("Incorrect value for time!!!");
    }
}

ostream& operator<<(ostream& os, const TransactionType& num)
{
    switch(num)
    {
        case TransactionType::TRANSFER:
            os << "TRANSFER";
            break;
        case TransactionType::PAYMENT:
            os << "PAYMENT";
            break;
        default:
            os << "Unknown!!!";
    }
    return os;
}

ostream& operator<<(ostream& os, const TransactionStatus& num)
{
    switch(num)
    {
        case TransactionStatus::PENDING:
            os << "PENDING";
            break;
        case TransactionStatus::COMPLETED:
            os << "COMPLETED";
            break;
        case TransactionStatus::FIALED:
            os << "FIALED";
            break;
        default:
            os << "Unknown!!!";
    }
    return os;
}


void Transaction::print()
{
    gotoxy(2, 3);
    cout << "TransactionID : " << getTransactionID();
    gotoxy(2, 5);
    cout << "\nTrackingCode : " << getTrackingCode();
    gotoxy(2, 7);
    cout << "\nAmount : " << getAmount();
    gotoxy(2, 9);
    cout << "\nType : " << getType();
    gotoxy(2, 11);
    cout << "\nStatus : " << getStatus();
    gotoxy(2, 13);
    cout << "\ncreaded at : ";
    tm* localTime = localtime(&_createdAT);
    char buffer1[80];
    char buffer2[80];
    strftime(buffer1, sizeof(buffer1), "%H:%M" , localTime);
    strftime(buffer2, sizeof(buffer2), "%Y-%m-%d" , localTime);
    cout << buffer1 <<" " << buffer2 << endl;
}

string Transaction::transactionTypeToString(TransactionType type)
{
    switch(type)
    {
        case TransactionType::TRANSFER: 
            return "TRANSFER";
        case TransactionType::PAYMENT:  
            return "PAYMENT";
        default: 
            return "UNKNOWN";
    }
}

TransactionType Transaction::stringToTransactionType(const string& str)
{
    if (str == "TRANSFER")
    {
        return TransactionType::TRANSFER;
    }
    if (str == "PAYMENT")
    {
        return TransactionType::PAYMENT;
    }
    throw invalid_argument("Invalid TransactionType string: " + str);
}

string Transaction::transactionStatusToString(TransactionStatus status)
{
    switch(status)
    {
        case TransactionStatus::PENDING:
            return "PENDING";
        case TransactionStatus::COMPLETED:
            return "COMPLETED";
        case TransactionStatus::FIALED:    
            return "FIALED";
        default: 
            return "UNKNOWN";
    }
}

TransactionStatus Transaction::stringToTransactionStatus(const string& str)
{
    if (str == "PENDING")
    {   
        return TransactionStatus::PENDING;
    }
    if (str == "COMPLETED")
    {
        return TransactionStatus::COMPLETED;
    }
    if (str == "FIALED")
    {    
        return TransactionStatus::FIALED;
    }
    throw invalid_argument("Invalid TransactionStatus string: " + str);
}