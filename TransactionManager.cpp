#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <string>
using namespace std;

class Transaction {
private:
	bool typeTransaction; // 1 for income 0 for expense
	string description;
	double amount;
	string date;
public:

	Transaction (){}

	Transaction(bool t, string d, double a, string dat) {
		typeTransaction = t;
		description = d;
		amount = a;
		date = dat;
	}

	bool getTypeTransaction() {
		return typeTransaction;
	}

	void setTypeTransaction(bool t){
		typeTransaction = t;
	}

	string getDescription() {
		return description;
	}

	void setDescription(string des) {
		description = des;
	}

	double getAmount() {
		return amount;
	}

	void setAmount(double am) {
		amount = am;
	}

	string getDate() {
		return date;
	}

	void setDate(string da) {
		date = da;
	}

	friend ifstream& operator>> (ifstream& fin, Transaction& T) {
		fin >> T.typeTransaction >> T.description >> T.amount >> T.date;
		return fin;
	}

	friend ofstream& operator<< (ofstream& fout, Transaction& T) {
		fout << T.typeTransaction << " " << T.description << " " << T.amount << " " << T.date;
		return fout;
	}

	friend istream& operator>> (istream& in, Transaction& T) {
		in >> T.typeTransaction >> T.description >> T.amount >> T.date;
		return in;
	}

	friend ostream& operator<< (ostream& out, Transaction& T) {
		out << T.typeTransaction << " " << T.description << " " << T.amount << "$ " << T.date;
		return out;
	}
};

bool comparebyDate(Transaction t1, Transaction t2)
{
	return (t1.getDate() < t2.getDate());
}

bool ExpenseFirst(Transaction t1, Transaction t2)
{
	return (t1.getTypeTransaction() > t2.getTypeTransaction());
}

bool IncomeFirst(Transaction t1, Transaction t2)
{
	return (t1.getTypeTransaction() < t2.getTypeTransaction());
}

class TransactionManager {
private:
	vector <Transaction> transactions;
	void sortByListing(){}
	void sortByExpense(){}
	void sortByIncome(){}
public:
	void clearTransactions(){
		transactions.clear();
	}
	void saveToFile(string fileName){
		ofstream out;
		out.open(fileName);
		if (out.is_open()) {
			for (auto i = 0; i < transactions.size(); i++) {
				out << transactions.at(i) << endl;
			}
		}
		else {
			cout << "Unable to open file\n";
		}
	}
	void loadFromFile(string fileName){
		ifstream in;
		in.open(fileName);
		if (in.is_open()) {
			while (!in.eof()) {
				Transaction T;
				in >> T;
				transactions.push_back(T);
			}
		}
		else {
			cout << "Unable to open file\n";
		}
	}
	void addMoney(){
		string desc; double amount; string date;
		cout << "Please enter transaction description: "; cin.ignore(); getline(cin, desc);
		cout << "Please enter amount: "; cin >> amount;
		cout << "Please enter date: (yyyy/mm/dd): "; cin >> date;
		Transaction T(1, desc, amount, date);
		transactions.push_back(T);
	}
	void spendMoney(){
		string desc; double amount; string date;
		cout << "Please enter transaction description: "; cin.ignore(); getline(cin, desc);
		cout << "Please enter amount: "; cin >> amount;
		cout << "Please enter date: (yyyy/mm/dd): "; cin >> date;
		Transaction T(0, desc, amount, date);
		transactions.push_back(T);
	}
	void printTransactions(){
		double sumIncome = 0, sumExpenses = 0;
		for (auto i = 0; i < transactions.size(); i++) {
			if (transactions.at(i).getTypeTransaction() == 0) {
				sumExpenses += transactions.at(i).getAmount();
				cout << transactions.at(i) << endl;
			}
			else {
				sumIncome += transactions.at(i).getAmount();
				cout << transactions.at(i) << endl;
			}
		}
		if (sumIncome >= sumExpenses) {
			cout << "Your balance is: " << sumIncome - sumExpenses << "$" << endl;
		}
		else {
			cout << "Your balance is: " << sumIncome - sumExpenses << "$ so, you are spending more than the income" << endl;
		}
		
	}
	void sortTransactions(){
		char opt = ' ';
		cout << "Enter choice: "; cin >> opt;
		if (opt == 'a') {
			sort(transactions.begin(), transactions.end(), comparebyDate);
		}
		else if (opt == 'b') {
			sort(transactions.begin(), transactions.end(), ExpenseFirst);
		}
		else if (opt == 'c') {
			sort(transactions.begin(), transactions.end(), IncomeFirst);
		}
		else {
			cout << "Invalid input\n";
		}
	}

};


void menu() {
	cout << "1. Clear all Transactions\n";
	cout << "2. Save financial records from file\n";
	cout << "3. Read financial records from file\n";
	cout << "4. Add money\n";
	cout << "5. Spend money\n";
	cout << "6. Print Report\n";
	cout << "7. Sort Transactions\n";
	cout << "8. Exit\n";
}


void subMenu() {
	cout << "a. Same Listing\n";
	cout << "b. Expense first\n";
	cout << "c. Income first\n";
}

int main() {


	TransactionManager tm; string fileName;
	int option = -1;
	while (option != 8) {
		menu();
		cout << "Enter choice: "; cin >> option;
		if (option == 1) {
			tm.clearTransactions();
		}
		else if (option == 2) {
			cout << "Enter file name: "; cin >> fileName;
			tm.saveToFile(fileName);
		}
		else if (option == 3) {
			cout << "Enter file name: "; cin >> fileName;
			tm.loadFromFile(fileName);
		}
		else if (option == 4) {
			tm.addMoney();
		}
		else if (option == 5) {
			tm.spendMoney();
		}
		else if (option == 6) {
			tm.printTransactions();
		}
		else if (option == 7) {
			subMenu();
			tm.sortTransactions();
		}
	}

	return 0;
}