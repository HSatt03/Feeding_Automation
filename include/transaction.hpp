#ifndef TRANSACTION_HPP
#define TRANSACTION_HPP
#include <iostream>
using namespace std;

enum class TransactionType
{
    TRANSFER,
    PAYMENT
};

enum class TransactionStatus
{
    PENDING,
    COMPLETED,
    FIALED
};

class Transaction
{
public:
    Transaction(int = 0, string = "00000", float = 0.00, TransactionType = TransactionType::TRANSFER, TransactionStatus = TransactionStatus::PENDING, time_t = time(0));
    void setTransactionID(int);
    void setTrackingCode(string);
    void setAmount(float);
    void setType(TransactionType);
    void setStatus(TransactionStatus);
    void setCreatedAT(time_t);
    void print();

    int getTransactionID()const
    {
        return _transactionID;
    }
    string getTrackingCode()const
    {
        return _trackingCode;
    }
    float getAmount()const
    {
        return _amount;
    }
    TransactionType getType()const
    {
        return _type;
    }
    TransactionStatus getStatus()const
    {
        return _status;
    }
    time_t getCreatedAT()const
    {
        return _createdAT;
    }
    private:
    static int _transactionID;
    string _trackingCode;
    float _amount;
    TransactionType _type;
    TransactionStatus _status;
    time_t _createdAT;
};

#endif