// this project was made by Allyn Novelo and Lizzy Vasquez
#include <iostream>
#include <cstring>
using namespace std;

class Insurance{
  protected:
    int PolicyNumber;
    char customername [15];
    int policyvalue;
    float monthlyPayment;
    string expiryDate;
    char status[15];
public:
    Insurance(int pn, char* cname, int pv, float mp, string ed, char* s){
        PolicyNumber = pn;
        strcpy(customername, cname);
        policyvalue = pv;
        monthlyPayment = mp;
        expiryDate = ed;
        strcpy(status, s);
    }
virtual void displayPolicyInfo(){
    cout << "~~~~ Policy Info ~~~~\n";
    cout << "Number: "<< PolicyNumber << " | Name: " << customername << "\n"; 
}
    
    
    
};
