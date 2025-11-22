// this project was made by Allyn Novelo and Lizzy Vasquez
#include <iostream>
#include <cstring>
using namespace std;

class Insurance{//Base Class
  protected:
    int PolicyNumber;
    char customername [15];
    int policyvalue;
    float monthlyPayment;
    string expiryDate;
    char status[15];
public:
    Insurance(){//default Insurance constructor
      PolicyNumber=0;
      strcpy(customername, "Unknown");
      policyvalue = 0;
      monthlyPayment = 0.0;
      expiryDate = "N/A";
      strcpy(status, "Active");
    }
    Insurance(int pn, char* cname, int pv, float mp, string ed, char* s){//Insurance constructor with parameters
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
virtual double calculatePremium() = 0; //pure virtual that forces overrride in subclasses 
virtual void renewPolicy(){
    strcpy(status, "Active");
    cout << "Policy renewed. \n";
}
void cancelPolicy(){
   strcpy(status, "Cancelled");
   cout << "Policy cancelled. \n;
}
bool isExpired(){
    return strcmp(status, "Expired") == 0;
    cout << "This policy has expired.\n";
}
int getPolicyNumber() { return PolicyNumber; }
const char* getCustomerName() { return customername; }
};


