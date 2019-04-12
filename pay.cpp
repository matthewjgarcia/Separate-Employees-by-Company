// pay .cpp

#include <iostream>
#include <string>
#include <iomanip>
#include "person.cpp"
#include <fstream>
#include <vector>

using namespace std;

void readData(vector <Person> &employees)
{
  string firstName;
  string lastName;
  int employeeID;
  string companyName;
  float hoursWorked;
  float payRate;
  // all of these need to be initialized to allow us to use the varaibles

  ifstream input;
  input.open("input.txt");
  while (input >> firstName >> lastName >> employeeID >> companyName >> hoursWorked >> payRate)
  {
    //this part is to add the parts of the input txt file into the vector employees
    Person p;
    p.setFirstName(firstName);
    p.setLastName(lastName);
    p.setEmployeeId(employeeID);
    p.setCompanyName(companyName);
    p.setHoursWorked(hoursWorked);
    p.setPayRate(payRate);
    employees.push_back(p);
  }

  input.close();
}

void getCompanies(vector <Person> &employees, vector <string> &companyName)
{
  for (int i = 0; i < employees.size(); i++){

    int j = 0;
    if (companyName.empty())
    {
      companyName.push_back(employees.at(i).getCompanyName());
    }

    for (int k = 0; k < companyName.size(); k++)
    {
      if (employees.at(i).getCompanyName() == companyName.at(k))
      {
      j++;
      }
    }
  if(j == 0)
  {
    companyName.push_back(employees.at(i).getCompanyName());
  }

  }
}

void printHighestPaid(vector <Person> &employees){
  int count;
  float temp; // this is needed to compare the values
  int i = 0;
  while(i < employees.size()){
    if (temp < employees.at(i).totalPay()){
      temp= employees.at(i).totalPay();
      count = i;
    }
    i++;
  }
  cout << "Highest Paid: " << employees.at(count).fullName() << endl;
  cout << "Employee ID: " << employees.at(count).getEmployeeId()<< endl;
  cout << "Employer: " << employees.at(count).getCompanyName() << endl;
  cout << "Total pay: " << fixed << setprecision(2) << employees.at(count).totalPay() << endl;
  }



void separateAndSave(vector <Person> &employees, vector <string> &companyName){
  ofstream output;
  for (int i = 0; i < companyName.size(); i++)
  {
    float amount = 0;
    output.open(companyName.at(i)+".txt");
    for (int j = 0; j < employees.size(); j++)
    {
      if (companyName.at(i) == employees.at(j).getCompanyName())
      {
        output << setw(12) << left << employees.at(j).getFirstName();
        output << setw(12) << left << employees.at(j).getLastName();
        output << setw(12) << left << employees.at(j).getEmployeeId();
        output << setw(12) << left << employees.at(j).getCompanyName();
        output << "$" << setw(12) << left << fixed << setprecision(2) <<employees.at(j).totalPay() << " \n";
        amount = amount + employees.at(j).totalPay();
      }
    }
    output << "Total amount: $" << fixed << setprecision(2) << amount;
    output.close();
  }
}





int main()
{
vector <Person> employees;
vector <string> companyName;
readData(employees);
getCompanies(employees, companyName);
printHighestPaid(employees);
separateAndSave(employees, companyName);

  return 0;
}
