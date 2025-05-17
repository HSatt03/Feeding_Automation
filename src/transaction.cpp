#include <string.h>
#include <iostream>
#include :/include/transaction.hpp
using namespace std;

Transaction::Transaction(int transactionID, string trackingCode, float amount , TransactionType type, TransactionStatus status, time_t = createdAT)
{
    setTransactionID(createdAT);
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
    _trackingCode = (s.lenght() == 5) ? s : "00000";
}
void Transaction::setAmount(float f)
{
    _amount = (f > 0) ? f : 0.00;
}
void Transaction::setType(TransactionType t)
{
    if(t == TRANSFER || t == PAYMENT) 
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
    if(t == PENDING || t == COMPLETED || t == FIALED) 
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
