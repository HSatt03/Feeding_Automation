#ifndef TRANSACTION_HPP
#define TRANSACTION_HPP

#include <iostream>
#include <ctime>      
#include <iomanip>    
#include <sstream>    
#include <string>
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

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
    friend ostream& operator<<(ostream&, const TransactionStatus&);
    friend ostream& operator<<(ostream&, const TransactionType&);

    static TransactionType stringToTransactionType(const string&);
    static string transactionTypeToString(TransactionType);
    static TransactionStatus stringToTransactionStatus(const string& str);
    static string transactionStatusToString(TransactionStatus status);

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
    // static int _transactionID;
    int _transactionID;
    string _trackingCode;
    float _amount;
    TransactionType _type;
    TransactionStatus _status;
    time_t _createdAT;
};

namespace nlohmann
{
    template<>
    struct adl_serializer<Transaction>
    {
        static void to_json(json& j, const Transaction& t)
        {
            time_t created = t.getCreatedAT();
            tm* tm_ptr = std::localtime(&created);
            char buffer[20];
            strftime(buffer, sizeof(buffer), "%Y-%m-%dT%H:%M:%S", tm_ptr);

            j = json{
                {"transactionID", t.getTransactionID()},      // فرض: متد getID داری
                {"trackingcode", t.getTrackingCode()},
                {"amount", t.getAmount()},
                {"type", Transaction::transactionTypeToString(t.getType())},
                {"status", Transaction::transactionStatusToString(t.getStatus())},
                {"createdAT", string(buffer)}
            };
        }

        static void from_json(const json& j, Transaction& t)
        {
            t.setTransactionID(j.at("transactionID").get<int>()); 
            t.setTrackingCode(j.at("trackingcode").get<string>());    
            t.setAmount(j.at("amount").get<float>());
            t.setType(Transaction::stringToTransactionType((j.at("type").get<string>())));
            t.setStatus(Transaction::stringToTransactionStatus(j.at("status").get<string>()));
            std::tm tm = {};
            istringstream ss(j.at("createdAT").get<string>());
            ss >> get_time(&tm, "%Y-%m-%dT%H:%M:%S");
            t.setCreatedAT(mktime(&tm));
        }
    };
}

#endif