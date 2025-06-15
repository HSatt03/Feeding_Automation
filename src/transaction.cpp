#include <string.h>
#include <iostream>
#include "../include/transaction.hpp"
using namespace std;

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
    _transactionID = (i > 0) ? : 0;
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

void Transaction::print()
{
    cout << "TransactionID : " << getTransactionID();
    cout << "\nTrackingCode : " << getTrackingCode();
    cout << "\nAmount : " << getAmount();
    cout << "\nType : " << getType();
    cout << "\nStatus : " << getStatus();
    cout << "\nCreatedAT : " << getCreatedAT();
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
