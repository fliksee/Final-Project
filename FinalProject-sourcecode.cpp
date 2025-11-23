// this project was made by Allyn Novelo and Lizzy Vasquez
#include <iostream>
#include <cstring>
#include <string>
using namespace std;

class Insurance {//Base Class
protected:
    char PolicyNumber[15];
    char customername[15];
    double policyvalue;
    float monthlyPayment;
    string expiryDate;
    char status[15];
public:
    Insurance() {//default Insurance constructor
        strcpy(PolicyNumber, "0");
        strcpy(customername, "Unknown");
        policyvalue = 0.0;
        monthlyPayment = 0.0;
        expiryDate = "N/A";
        strcpy(status, "Active");
    }
    Insurance(const char* pn, const char* cname, double pv, float mp, string ed, const char* s) {//Insurance constructor with parameters
        strcpy(PolicyNumber, pn);
        strcpy(customername, cname);
        policyvalue = pv;
        monthlyPayment = mp;
        expiryDate = ed;
        strcpy(status, s);
    }
    virtual void displayPolicyInfo() {
        cout << "~~~~ Policy Info ~~~~\n";
        cout << "Number: " << PolicyNumber << " | Name: " << customername << "\n";
    }
    virtual double calculatePremium() = 0; //pure virtual that forces override in subclasses
    virtual void renewPolicy() {
        strcpy(status, "Active");
        cout << "Policy renewed. \n";
    }
    void cancelPolicy() {
        strcpy(status, "Cancelled");
        cout << "Policy cancelled. \n";
    }
    const char* getPolicyNumber() {
        return PolicyNumber;
    }
    const char* getCustomerName() {
        return customername;
    }
    const char* getStatus() {
        return status;
    }
    const string& getExpiryDate() {
        return expiryDate;
    }
};

class MotorInsurance : public Insurance {//derived class
private:
    char vehicleType[15];
    double engineCapacity;
    int accidentHistory;
    char coverageType[15];
public:
    MotorInsurance(const char* pn, const char* cname, double pv, float mp, string ed, const char* s,
                   const char* vType, double engine, int accidents, const char* coverage) : Insurance(pn, cname, pv, mp, ed, s) {
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
    HomeInsurance(const char* pn, const char* cn, double pv, float mp, string ed, const char* s, const char* pt, const char* lrf, bool ssi)
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

// Global variables
const int MAX_POLICIES = 50;
Insurance* policies[MAX_POLICIES];
int policyCount = 0;

// Add motor
void addMotorPolicy() {
    if (policyCount >= MAX_POLICIES) { cout << "Full.\n"; return; }
    char pn[50], cn[50], vt[50], ct[50];
    double pv;
    int d, m, y, ec, ah;
    cout << "Policy No: ";
    cin >> pn;
    cout << "Name: ";
    cin.ignore();
    cin.getline(cn, 50);
    cout << "Value: ";
    cin >> pv;
    cout << "Expiry D M Y: ";
    cin >> d >> m >> y;
    string ed = to_string(d) + "/" + to_string(m) + "/" + to_string(y);
    cout << "Vehicle Type: ";
    cin >> vt;
    cout << "Engine CC: ";
    cin >> ec;
    cout << "Accidents: ";
    cin >> ah;
    cout << "Coverage: ";
    cin >> ct;
    policies[policyCount] = new MotorInsurance(pn, cn, pv, 0.0, ed, "Active", vt, ec, ah, ct);
    policyCount++;
    cout << "Added.\n";
}

// Add home
void addHomePolicy() {
    if (policyCount >= MAX_POLICIES) { cout << "Full.\n"; return; }
    char pn[50], cn[50], pt[50], lrf[50];
    double pv;
    int d, m, y, ssi;
    cout << "Policy No: ";
    cin >> pn;
    cout << "Name: ";
    cin.ignore();
    cin.getline(cn, 50);
    cout << "Value: ";
    cin >> pv;
    cout << "Expiry D M Y: ";
    cin >> d >> m >> y;
    string ed = to_string(d) + "/" + to_string(m) + "/" + to_string(y);
    cout << "Property Type: ";
    cin >> pt;
    cout << "Risk: ";
    cin >> lrf;
    cout << "Security (1/0): ";
    cin >> ssi;
    policies[policyCount] = new HomeInsurance(pn, cn, pv, 0.0, ed, "Active", pt, lrf, ssi == 1);
    policyCount++;
    cout << "Added.\n";
}

// Menu for adding
void addNewPolicyMenu() {
    int choice;
    do {
        cout << "\n::::: SELECT INSURANCE TYPE :::::\n1. Motor\n2. Home\n3. Life (N/A)\n4. Exit\nChoice: ";
        cin >> choice;
        if (choice == 1) addMotorPolicy();
        else if (choice == 2) addHomePolicy();
        else if (choice == 3) cout << "Not implemented.\n";
        else if (choice != 4) cout << "Invalid.\n";
    } while (choice != 4);
}

// Print list
void printPolicyList() {
    cout << "\n=================================================================\n";
    cout << "POLICY NO.      CUSTOMER NAME                 STATUS    EXPIRY DATE\n";
    cout << "-----------------------------------------------------------------\n";
    if (policyCount == 0) { cout << "None.\n"; return; }
    for (int i = 0; i < policyCount; ++i) {
        if (policies[i]) {
            cout << policies[i]->getPolicyNumber() << "          " << policies[i]->getCustomerName() << "                 " << policies[i]->getStatus() << "    " << policies[i]->getExpiryDate() << "\n";
        }
    }
    cout << "-----------------------------------------------------------------\n";
}

// Find policy
Insurance* findPolicyByNumber() {
    if (policyCount == 0) { cout << "None.\n"; return NULL; }
    printPolicyList();
    cout << "\nPolicy Number: ";
    char search_term[50];
    cin >> search_term;
    for (int i = 0; i < policyCount; ++i) {
        if (policies[i] && strcmp(policies[i]->getPolicyNumber(), search_term) == 0) return policies[i];
    }
    cout << "Not found.\n";
    return NULL;
}

// View details
void viewPolicyDetails() {
    Insurance* policy = findPolicyByNumber();
    if (policy) {
        cout << "\n<<< DETAILS >>>\n";
        policy->displayPolicyInfo();
    }
}

// Renew or cancel
void renewOrCancelPolicy() {
    Insurance* policy = findPolicyByNumber();
    if (!policy) return;
    int choice;
    cout << "\n1. Renew\n2. Cancel\n3. Back\nChoice: ";
    cin >> choice;
    if (choice == 1) policy->renewPolicy();
    else if (choice == 2) policy->cancelPolicy();
    else if (choice == 3) cout << "Back.\n";
    else cout << "Invalid.\n";
}

// Main menu
void mainMenu() {
    int choice;
    do {
        cout << "\n=================================================================\n::::: BELIZEAN INSURANCE LTD :::::\n=================================================================\n::::: SELECT MENU OPTION :::::\n\n1. Add New Insurance Policy\n2. View Policy Details\n3. Renew or Cancel Policy\n4. Exit Program\n\nChoice: ";
        cin >> choice;
        switch (choice) {
            case 1: addNewPolicyMenu(); break;
            case 2: viewPolicyDetails(); break;
            case 3: renewOrCancelPolicy(); break;
            case 4: cout << "\nGoodbye!\n"; break;
            default: cout << "Invalid.\n";
        }
    } while (choice != 4);
}

// Main
int main() {
    // Dummy data
    policies[policyCount++] = new MotorInsurance("M-121", "Allyn Novelo", 50600.0, 20.0, "30/12/2025", "Active", "car", 1800, 1, "full");
    policies[policyCount++] = new HomeInsurance("H-122", "Lizzy Vasquez", 250000.0, 30.0, "26/11/2026", "Active", "house", "low", true);
    policies[policyCount++] = new MotorInsurance("M-123", "Test Expired", 10000.0, 25.0, "10/1/2025", "Expired", "motorcycle", 250, 0, "third party");
    
    mainMenu();
    
    // Clean up memory
    for (int i = 0; i < policyCount; ++i) {
        delete policies[i];
    }
    
    return 0;
}

