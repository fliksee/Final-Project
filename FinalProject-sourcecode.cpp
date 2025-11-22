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
    Insurance(int pn, const char* cname, int pv, float mp, string ed, const char* s){//Insurance constructor with parameters
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
   cout << "Policy cancelled. \n";
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
double applyAccidentSurcharge() { return accidentHistory * 500.0; }
};

class HomeInsurance : public Insurance {
private:
    char propertyType[30], locationRiskFactor[30];
    bool securitySystemInstalled, claimsMadeLastTerm;
public:
 HomeInsurance(int pn, const char* cn, int pv, float mp, string ed, const char* s, const char* pt, const char* lrf, bool ssi)
        : Insurance(pn, cn, pv, mp, ed, s), securitySystemInstalled(ssi), claimsMadeLastTerm(false) {
        strcpy(propertyType, pt);
        strcpy(locationRiskFactor, lrf);
        monthlyPayment = calculatePremium() / 12.0;
    }
  double calculatePremium() override {
        double p = policyvalue * 0.005;
        if (strcmp(locationRiskFactor, "medium") == 0) p *= 1.25;
        else if (strcmp(locationRiskFactor, "high") == 0) p *= 1.5;
        if (securitySystemInstalled) p *= 0.85;
        if (strcmp(propertyType, "commercial") == 0) p *= 1.15;
        return p;
    }
void renewPolicy() override {
        Insurance::renewPolicy();
        if (!claimsMadeLastTerm) {
            double newPrem = calculatePremium() * 0.95;
            monthlyPayment = newPrem / 12.0;
            cout << "Discount applied.\n";
        }
claimsMadeLastTerm = false;
    }
 void displayPolicyInfo() override {
        Insurance::displayPolicyInfo();
        cout << "--- Home ---\nType: " << propertyType << " | Risk: " << locationRiskFactor << "\nSecurity: " << (securitySystemInstalled ? "Yes" : "No") << "\n";
    }
};
