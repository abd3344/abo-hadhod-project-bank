
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include<iomanip>

using namespace std;
const string ClientsFileName = "Clients.txt";

enum enmylist
{
	Showcilent = 1, addnewcilent = 2, deletecilent = 3, updetecilent = 4, findcilent = 5, exitprogram = 6
};

struct sClient
{
	string PinCode;
	string AccountNumber;
	string Name;
	string Phone;
	double AccountBalance;
	bool MarkForDelete = false;
};
sClient ReadNewClient() {
	sClient Client;
	cout << "Enter Account Number? ";
	// Usage of std::ws will extract allthe whitespace character 
	getline(cin >> ws, Client.AccountNumber);
	cout << "Enter PinCode? ";
	getline(cin, Client.PinCode);
	cout << "Enter Name? ";
	getline(cin, Client.Name);
	cout << "Enter Phone? ";
	getline(cin, Client.Phone);
	cout << "Enter AccountBalance? ";
	cin >> Client.AccountBalance;
	return Client;
}







string ConvertRecordToLine(sClient Client, string Seperator = "#//#") {
	string stClientRecord = "";
	stClientRecord += Client.AccountNumber + Seperator;
	stClientRecord += Client.PinCode + Seperator;
	stClientRecord += Client.Name + Seperator;
	stClientRecord += Client.Phone + Seperator;
	stClientRecord += to_string(Client.AccountBalance);
	return stClientRecord;
}
void AddDataLineToFile(string FileName, string stDataLine) {
	fstream myfail;
	myfail.open(FileName, ios::out | ios::app);
	if (myfail.is_open()) {
		myfail << "\n" << stDataLine;
		myfail.close();
	}

}
void AddNewClient() {
	sClient Client;
	Client = ReadNewClient();
	AddDataLineToFile(ClientsFileName, ConvertRecordToLine(Client));
}
void AddClients() {
	char AddMore = 'Y';
	do {
		system("cls");
		cout << "Adding New Client:\n\n";
		AddNewClient();
		cout << "\nClient Added Successfully, do you want to add more clients? Y/N? ";
		cin >> AddMore;
	} while (toupper(AddMore) == 'Y');

}
vector <string>  SplitString(string S1, string delim) {
	short pos = 0;
	string sWord;// define a string variabl
	vector <string> vstring;
	// use find() function to get the position of the delimiters
	while ((pos = S1.find(delim)) != std::string::npos)
	{
		sWord = S1.substr(0, pos);
		if (sWord != "")
		{
			vstring.push_back(sWord);//خزن الكلمة store the word
		}
		/*احزف يلي بقلب  المتغير erase() until positon and move to next word. */
		S1.erase(0, pos + delim.length());
	}


	if (S1 != "") {
		vstring.push_back(S1);// it counts the last word of the string.   
	}
	return vstring;
}

sClient ConvertLinetoRecord(string line, string spectitor = "#//#") {
	sClient Client;
	vector <string>  SplitStrin = SplitString(line, spectitor);
	Client.AccountNumber = SplitStrin[0];
	Client.PinCode = SplitStrin[1];
	Client.Name = SplitStrin[2];
	Client.Phone = SplitStrin[3];
	Client.AccountBalance = stod(SplitStrin[4]);
	return Client;

}

vector < sClient> LoadCleintsDataFromFile(string FileName) {
	fstream myfail;
	vector <sClient> vcilent;
	myfail.open(FileName, ios::in);
	if (myfail.is_open()) {
		sClient cilent;
		string line;
		while (getline(myfail, line))
		{
			cilent = ConvertLinetoRecord(line);
			vcilent.push_back(cilent);
		}
		myfail.close();
	}
	return vcilent;
}
void PrintClientRecord(sClient Client) {
	cout << "| " << setw(15) << left << Client.AccountNumber;
	cout << "| " << setw(10) << left << Client.PinCode;
	cout << "| " << setw(40) << left << Client.Name;
	cout << "| " << setw(12) << left << Client.Phone;
	cout << "| " << setw(12) << left << Client.AccountBalance;

}
void PrintAllClientsData(vector <sClient> vClients) {
	cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).";
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	cout << "| " << left << setw(15) << "Accout Number";
	cout << "| " << left << setw(10) << "Pin Code";
	cout << "| " << left << setw(40) << "Client Name";
	cout << "| " << left << setw(12) << "Phone";
	cout << "| " << left << setw(12) << "Balance";
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	for (sClient Client : vClients) {
		PrintClientRecord(Client);
		cout << endl;
	}     cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
}

bool FindClientByAccountNumber(string accountnum, sClient& Client) {
	vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
	for (sClient c : vClients)
	{
		if (c.AccountNumber == accountnum)
		{
			Client = c;
			return true;
		}
	}
	return false;


}

bool MarkClientForDeleteByAccountNumber(string AccountNumber, vector <sClient>& vClients) {
	for (sClient& C : vClients) {

		if (C.AccountNumber == AccountNumber) {

			C.MarkForDelete = true;
			return true;
		}
	}
	return false;
}
bool FindClientByAccountNumber(string accountnum, vector<sClient> vClients, sClient& Client) {
	for (sClient c : vClients)
	{
		if (c.AccountNumber == accountnum)
		{
			Client = c;
			return true;
		}
	}
	return false;
}

vector <sClient> SaveCleintsDataToFile(string FileName, vector<sClient> vClients)
{
	fstream MyFile;
	MyFile.open(FileName, ios::out);
	//overwrite
	string DataLine;

	if (MyFile.is_open()) {

		for (sClient C : vClients) {

			if (C.MarkForDelete == false)
			{ //we only write records that are not marked for delete. 
				DataLine = ConvertRecordToLine(C);
				MyFile << DataLine << endl;
			}


		}         MyFile.close();
	} return vClients;
}
void PrintClientCard(sClient Client) {
	cout << "\nThe following are the client details:\n";
	cout << "\nAccout Number: " << Client.AccountNumber;
	cout << "\nPin Code     : " << Client.PinCode;
	cout << "\nName         : " << Client.Name;

	cout << "\nPhone        : " << Client.Phone;
	cout << "\nAccount Balance: " << Client.AccountBalance;

}

bool DeleteClientByAccountNumber(string AccountNumber, vector<sClient>& vClients) {

	sClient Client;
	char Answer = 'n';
	if (FindClientByAccountNumber(AccountNumber, vClients, Client)) {

		PrintClientCard(Client);
		cout << "\n\nAre you sure you want delete this client? y/n ? ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y') {

			MarkClientForDeleteByAccountNumber(AccountNumber, vClients);
			SaveCleintsDataToFile(ClientsFileName, vClients);

			//Refresh Clients
			vClients = LoadCleintsDataFromFile(ClientsFileName);
			cout << "\n\nClient Deleted Successfully.";
			return true;
		}
	}
	else
	{
		cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";
		return false;
	}
}
sClient ChangeClientRecord(string AccountNumber) {
	sClient Client;
	Client.AccountNumber = AccountNumber;
	cout << "Enter PinCode? ";
	getline(cin >> ws, Client.PinCode);
	cout << "Enter Name? ";
	getline(cin, Client.Name);
	cout << "Enter Phone? ";
	getline(cin, Client.Phone);
	cout << "Enter AccountBalance? ";
	cin >> Client.AccountBalance;
	return Client;
}

bool UpdeteClientByAccountNumber(string AccountNumber, vector<sClient>& vClients) {

	sClient Client;
	char Answer = 'n';
	if (FindClientByAccountNumber(AccountNumber, vClients, Client)) {

		PrintClientCard(Client);
		cout << "\n\nAre you sure you want updete this client? y/n ? ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y') {



			for (sClient& C : vClients) {
				if (C.AccountNumber == AccountNumber) {
					C = ChangeClientRecord(AccountNumber);
					break;
				}
			}



			SaveCleintsDataToFile(ClientsFileName, vClients);

			vClients = LoadCleintsDataFromFile(ClientsFileName);
			cout << "\n\nClient updeted Successfully.";
			return true;
		}
	}
	else
	{
		cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";
		return false;
	}
}

string ReadClientAccountNumber() {
	string AccountNumber = "";
	cout << "\nPlease enter AccountNumber? ";
	cin >> AccountNumber;
	return AccountNumber;
}




void ShowMainMenue();


void theprogramend() {
	system("cls");

	cout << "\n-------------------------------\n";
	cout << " Program ends !!\n";
	cout << "\n-------------------------------\n";


}

void GoBackToMainMenue() {
	cout << "\n\nPress any key to go back to Main Menue...";
	system("pause>0");
	ShowMainMenue();
}
enmylist readthelist() {
	int num;
	enmylist number;
	do
	{
		cout << "\npls insrt num from the list \n";
		cin >> num;

	} while (num > 6 || num < 0);
	return (enmylist)num;
}
void chosefromthelist(enmylist thelist) {

	vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
	sClient Clients;

	switch (thelist)

	{
	case enmylist::Showcilent:
		system("cls");
		PrintAllClientsData(vClients);
		GoBackToMainMenue();
		return;
	case enmylist::addnewcilent:
		system("cls");
		AddClients();
		GoBackToMainMenue();
		return;

	case enmylist::deletecilent:
		system("cls");
		DeleteClientByAccountNumber(ReadClientAccountNumber(), vClients);
		GoBackToMainMenue();
		return;


	case enmylist::updetecilent:
		system("cls");
		UpdeteClientByAccountNumber(ReadClientAccountNumber(), vClients);
		GoBackToMainMenue();
		return;

	case enmylist::findcilent:
		system("cls");
		if (FindClientByAccountNumber(ReadClientAccountNumber(), Clients))
			PrintClientRecord(Clients);
		else
			cout << "\nnot defined!!\n";
		GoBackToMainMenue();


	case enmylist::exitprogram:
		system("cls");
		theprogramend();
		return;

	}






}
void ShowMainMenue() {

	system("cls");

	cout << "==========================\n";
	cout << "Show menue screen\n";
	cout << "==========================\n";
	cout << "[1] show Cilent list \n";
	cout << "[2]Add new Cilent\n";
	cout << "[3]delete Cilent\n";
	cout << "[4]updete Cilent info\n";
	cout << "[5]find Cilent \n";
	cout << "[6]Exit \n";
	chosefromthelist(readthelist());

}
int main()
{
	ShowMainMenue();
}
