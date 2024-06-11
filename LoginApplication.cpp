#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

class Users {
private:
    string login;
    string password;
public:
    string getLogin() {
        return login;
    }
    void setLogin(string login) {
        this->login = login;
    }
    string getPassword() {
        return password;
    }
    void setPassword(string password) {
        this->password = password;
    }

};

void addUserInDB(const string& filename, const vector<string>& lines) {
    ofstream file(filename, ios::app); // открываем файл в режиме добавления
    if (file.is_open()) {
        for (const auto& line : lines) {
            file << line << endl; // добавляем каждую строку в файл
        }
        file.close(); // закрываем файл
    }
}

void logIn(string file, string login, string password) {
    while (true) {
        cout << "Account login:" << endl;
        cout << "Login: ";
        cin >> login;
        cout << "Password: ";
        cin >> password;

        ifstream out(file);
        string searchText_1 = login;
        string searchText_2 = password;
        string line;
        bool found = false;

        while (getline(out, line)) {
            if (line.find(searchText_1) != string::npos && line.find(searchText_2) != string::npos) {
                found = true;
                break;
            }
        }

        if (found) {
            cout << endl;
            cout << "Hello, you have successfully logged in!" << endl;
            break;
        }
        else {
            cout << endl;
            cout << "An error occurred, try again later..." << endl;
            cout << endl;
        }

        out.close();
    }
}

bool validation_check(string login,string password) { 

	bool valid = false;

	if((login.size() < 20 && login.size() > 5) && (password.size() < 30 && password.size() > 7)) {
        valid = true;
    }
    else {
        valid = false;
    }

    return valid;
}

void regestration(string file,string login, string password) {
reg:
    cout << "Create an account" << endl;
    cout << "Login: ";
    cin >> login;
    cout << "Password: ";
    cin >> password;

    ifstream out(file);
    string searchText_1 = login;
    string searchText_2 = password;
    string log_pas = login + " " + password;
    vector<string> lines = { log_pas };
    string line;
    bool found = false;

    while (getline(out, line)) {
        if (line.find(searchText_1) != string::npos && line.find(searchText_2) != string::npos) {
            found = true;
            break;
        }
    }

    if (validation_check(login, password)) {
        goto func;
    }
    else {
        cout << endl;
        cout << "You have entered too few or too many characters in your login or password";
        cout << endl;
        goto reg;
    }
func:
    if (found && validation_check(login,password)) {
        system("CLS");
        cout << "You are already registered, log in!" << endl;
        for (int i = 0; i < 2; i++) {
            cout << endl;
        }
        logIn(file,login,password);
    }
    else {
        cout << "Thank you for registering!" << endl;
        addUserInDB(file, lines);
        for (int i = 0; i <= 3; i++) {
            cout << "........." << endl;
        }
        cout << endl;
        cout << "Log in to your account :" << endl;
        logIn(file, login, password);
    }

    out.close();
}


int main() {
    setlocale(0, "");
    string pass;
    string login;

    Users user1;
    user1.setLogin(login);
    user1.setPassword(pass);

    string database = "UserData.txt";

    regestration(database, login, pass);

    return 0;
}
    