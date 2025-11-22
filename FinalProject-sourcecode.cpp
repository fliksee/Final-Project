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
int getPolicyNumber(){ 
  return PolicyNumber; 
}
const char* getCustomerName() { 
  return customername; 
}
};
class MotorInsurance: public Insurance {//derived class 
private :
  char vehicleType[15];;
  double engineCapacity;
  int accidentHistory;
  char coverageType[15];
public: 
      MotorInsurance(int pn, const char* cname, int pv, float mp, string ed, const char* s,
                   const char* vType, double engine, int accidents, const char* coverage): Insurance(pn, cname, pv, mp, ed, s) {
        strcpy(vehicleType, vType);
        engineCapacity = engine;
        accidentHistory = accidents;
        strcpy(coverageType, coverage);
      }
double calculatePremium() override {
        double premium = policyvalue * 0.02; // base 2%
        if (strcmp(coverageType, "full") == 0)
            premium *= 1.5;
        premium += accidentHistory * 50; // $50 per accident
        monthlyPayment = premium / 12;
        return monthlyPayment;
}
void displayPolicyInfo() override {//overriding method found in base class
        Insurance::displayPolicyInfo();
        cout << "Vehicle Type: " << vehicleType << endl;
        cout << "Engine Capacity: " << engineCapacity << " cc\n";
        cout << "Accident History: " << accidentHistory << endl;
        cout << "Coverage Type: " << coverageType << endl;
}
void renewPolicy() override {//overriding method found in base class
        if (strcmp(status, "Expired") == 0)
            monthlyPayment += 20; // late fee
        strcpy(status, "Active");
        cout << "Motor policy renewed.\n";
}
};


