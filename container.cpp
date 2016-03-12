//
//  hw1.cpp
//  sikoraAssignment1
//
//  Created by Administrator on 2/8/16.
//  Copyright © 2016 Administrator. All rights reserved.
//

#include <iostream>
#include <cmath>
#include <cassert>
#include <string>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

//DOCUMENTATION for PrepaidAccount class:
//
//ATTRIBUTES:
//string phoneNumber: 10 character String (i.e. 718-260-0000)
//float availableBalance: dollar value as a floating point number
//
//CONSTRUCTOR for the PrepaidAccount class:
//PrepaidAccount(string phoneNumber, float availableBalance)
//    Post-condition: The account has been initialized with given phone number. The balance has been initialized to zero.
//
//MODIFICATION MEMBER FUNCTIONS:
//void AddBalance(double howMuch)
//  Post-Condition: The amount howMuch dollars has been added to the available balance.
//double PayForCall(int callDuration, double tariff)
//  Pre-condition: The call cost must be greater than available balance.
//  Post-condition: The appropriate amount of dollars (callDuration in seconds, divided by 60 seconds/minute, times tariff in dollars/minute) has been deducted from availableBalance. The charges deducted from the balance have been returned, unless the balance was too low.
//CONSTANT MEMBER FUNCTIONS:
//string getPhone() const
//  Post-condition: phoneNumber has been returned.
//int getBal()
//  Post-condition: availableBalance has been returned.
//NON-MEMBER FUNCTIONS:
//int stringToInt(string s1);
//  Post-condition: string s1 has been converted to and int and returned.
//int compareAccounts(const PrepaidAccount a1, const PrepaidAccount a2)
//  Post-condition: Function  has returned -1 if a1’s phone number is smaller than a2’s phone number, 0 if a1’s phone number is equal to a2’s phone number, or 1 if a1’s phone number is larger than a2’s phone number.

class PrepaidAccount
{
public:
    //CONSTRUCTOR:
    PrepaidAccount();
    PrepaidAccount(string phoneNumber, float availableBalance=0.0);
    
    //MODIFICATION MEMBER FUNCTIONS:
    void AddBalance(double howMuch);
    double PayForCall(int callDuration, double tariff);
    
    //CONSTANT MEMBER FUNCTIONS:
    string getPhone() const {return phoneNumber;}
    float getBal() {return availableBalance;}
private:
    string phoneNumber;
    float availableBalance;
}; //End of Class Definition

//NON-MEMBER FUNCTIONS for PrepaidAccount class:
int compareAccounts(const PrepaidAccount& a1, const PrepaidAccount& a2);
//string randAcct();

//IMPLEMENTATION:
//
//DEFAULT CONSTRUCTOR
PrepaidAccount::PrepaidAccount()
{
    phoneNumber.assign("");
    availableBalance=NULL;
}
//CLASS IMPLEMENTED: PrepaidAccount
PrepaidAccount::PrepaidAccount(string phone, float Balance)
{
    phoneNumber=phone;
    availableBalance=Balance;
}
//MEMBER FUNCTIONS:
void PrepaidAccount::AddBalance(double howMuch)
{
    availableBalance+=howMuch;
}
double PrepaidAccount::PayForCall(int callDuration, double tariff)
{
    //Calculate cost of call by converting call duration into minutes and multiplying by tariff.
    double callCost, callTime;
    callTime = (double) callDuration / 60; //minutes
    callCost = callTime * tariff; // minutes times dollars/minute
    //Pre-condition:
    assert(callCost<=availableBalance);
    //Adjust balance.
    availableBalance-= callCost;
    //Return the charges deducted.
    return callCost;
}
//NON-MEMBER FUNCTIONS:

int compareAccounts(const PrepaidAccount& a1, const PrepaidAccount& a2)
{
    string phone1, phone2;
    phone1=a1.getPhone();
    phone2=a2.getPhone();
    if (phone1.compare(phone2)<0)
        return -1;
    else if (phone1.compare(phone2)==0)
        return 0;
    else
        return 1;
}

//Trying to generate random numbers and write them to a string for phone numbers. Can't seem to recast them successfully.
/*string randAcct(){
    string num;
    int dum;
    char intStr[];
    string str;
    for (int i=0; i<10; i++){
        dum= (int) rand()%10;
        itoa(dum,intStr,10);
        str = string(intStr);
        num+= str;
    }
    return num;
}*/


//DOCUMENTATION for AccountStore container class:
//AccountStore holds at most 100 objects of class PrepaidAccount, sorted with respect to their phone numbers.
//TYPEDEF and MEMBER CONSTANTS for the AccountStore class:
//   typedef: PrepaidAccount
//
//CONSTRUCTOR for the AccountStore class:
//   int size=0 gives how many items are in a bag.
//   static const size CAPACITY = 100
//     AccountStore::CAPACITY is the maximum number of items that a AccountStore can hold.
//     Postcondition: The AccountStore has been initialized as an empty container with capacity 100.
//
//MODIFICATION MEMBER FUNCTIONS:
//void removeAccount(string phoneNumber)
//  Pre-condition: An account with the given phoneNumber exists in the container.
//  Post-condition: -1 has been returned if account is not found. If the account has been found, it has been removed from the container class, and the subsequent accounts have all been moved up on place. The size has been decreased by 1.
//void insertAccount(PrepaidAccount a)
//  Post-condition: The given account has been added to the appropriate position in the container. The subsequent accounts have been moved to the right by one place. The size has been increased by 1.
//
//CONSTANT MEMBER FUNCTIONS:
//int getSize()
//  Post-condition: Number of accounts currently being stored has been returned.
//PrepaidAccount getAccount(int i)
//  Post-condition: The account with i^th smallest phone number has been returned.
//
//CLASS DEFINITION: AccountStore
class AccountStore
{
public:
    //TYPEDEF:
    static const int CAPACITY = 100;
    //CONSTRUCTOR:
    AccountStore();
    //MODIFICATION MEMBER FUNCTIONS:
    void removeAccount(string phoneNumber);
    void insertAccount(PrepaidAccount a);
    //CONSTANT MEMBER FUNCTIONS:
    int getSize() const {return used;}
    PrepaidAccount getAccount(int i) {return data[i];}
private:
    PrepaidAccount data[CAPACITY];
    int used;
};
//IMPLEMENTATION:
//
//CLASS IMPLEMENTED: AccountStore
AccountStore::AccountStore()
{
    used=0;
}
//MEMBER FUNCTIONS:
void AccountStore::removeAccount(string phoneNumber)
{
    bool remove=false;
    //bool found=false;
    for (int i=0; i<used; i++){
        if (remove==false){
            if (data[i].getPhone().compare(phoneNumber)==0){
                for (int j=i;j<used;j++) {
                    data[j]=data[j+1];
                }
                remove=true;
                used--;
            }
        }
    }
    /*if (found==false)
     return -1;*/ //The instructions said to include a return statement, but it doesn't make sense because I made this a void function.
}
void AccountStore::insertAccount(PrepaidAccount a)
{
    bool insert=false;
    int place=0;
    if (data[0].getPhone()==""){
        data[0]=a;
        insert=true;
        used++;
    }
    for (int i=0; i<=used; i++){
        if (insert==false){
            place = compareAccounts(a, data[i]);
            if (place <= 0){
                for (int j=used-1;j>=i;j--) {
                    data[j+1]=data[j];
                }
                data[i]=a;
                used++;
                insert=true;
            } else if (data[i].getPhone()==""){
                data[i]=a;
                used++;
                insert=true;
            }
        }
    }
    
}

//Test the code here:
int main() {
    
    AccountStore myStore;
    
    float howMuch;
    int callTime;
    float tar;
    
    PrepaidAccount A("1729476940",0);
    PrepaidAccount B("8462935073",0);
    PrepaidAccount C("9475600367",0);
    PrepaidAccount D("4739604882",0);
    PrepaidAccount E("2748694002",0);
    
    howMuch = rand()%50 +50;
    callTime = (int) rand()%190 +10;
    tar= (rand()%4 + 1)*0.1;
    A.AddBalance(howMuch);
    A.PayForCall(callTime,tar);
    myStore.insertAccount(A);
    
    howMuch = rand()%50 +50;
    callTime = (int) rand()%190 +10;
    tar= (rand()%4+1)*0.1;
    B.AddBalance(howMuch);
    B.PayForCall(callTime,tar);
    myStore.insertAccount(B);
    
    howMuch = rand()%50 +50;
    callTime = (int) rand()%190 +10;
    tar= (rand()%4+1)*0.1;
    C.AddBalance(howMuch);
    C.PayForCall(callTime,tar);
    myStore.insertAccount(C);
    
    howMuch = rand()%50 +50;
    callTime = (int) rand()%190 +10;
    tar= (rand()%4+1)*0.1;
    D.AddBalance(howMuch);
    D.PayForCall(callTime,tar);
    myStore.insertAccount(D);
    
    howMuch = rand()%50 +50;
    callTime = (int) rand()%190 +10;
    tar= (rand()%4+1)*0.1;
    E.AddBalance(howMuch);
    E.PayForCall(callTime,tar);
    myStore.insertAccount(E);
    
    //myStore.removeAccount("4739604882");
    
    for (int j=0;j<5;j++){
        cout<<myStore.getAccount(j).getPhone()<<endl;
        cout<<myStore.getAccount(j).getBal()<<endl;
    }
    
    return 0;
}
