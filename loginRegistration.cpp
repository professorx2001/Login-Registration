#include <iostream>
#include <fstream>

using namespace std;
//To check if username is unique
bool checkUniqueUsrname(string username)
{
    ifstream read;
    read.open("masterUsername.txt");
    string dummyLine;
    while (!read.eof())
    {
        getline(read, dummyLine);
        if (username == dummyLine)
            return false;
    }
    read.close();
    return true;
}
//Updating master file everytime a new username drops
void writeInFile(string username)
{
    vector<string> v;
    string dummyLine;
    ifstream read;
    read.open("masterUsername.txt");

    while (!read.eof())
    {
        getline(read, dummyLine);
        v.push_back(dummyLine);
    }
    read.close();

    v[v.size() - 1] = username;

    ofstream write("masterUsername.txt");
    for (int i = 0; i < v.size(); i++)
    {
        write << v[i] << endl;
    }
    write.close();
}

// Creating unique file and storing password in it.
void signUp()
{
    string username;
    string password;

    cout << "Enter your username:" << endl;
    cin >> username;
    bool uniq = checkUniqueUsrname(username);

    if (uniq == false)
    {
        while (uniq != true)
        {
            cout << "Enter a unique username" << endl;
            cin >> username;
            uniq = checkUniqueUsrname(username);
        }
    }
    if (uniq == true)
    {
        cout << "Enter your password:" << endl;
        cin >> password;

        string fileName = username + ".txt";
        ofstream write;
        write.open(fileName);

        write << password;
        writeInFile(username);
        write.close();
        cout << "Sign Up successful. Account created." << endl;
    }
}

// Authenticating user credentials.
void login()
{
    string username;
    string password;

    cout << "Enter your username:" << endl;
    cin >> username;
    cout << "Enter your password:" << endl;
    cin >> password;
    ifstream read;
    string fileName = username + ".txt";
    read.open(fileName);

    // checking if file exists
    if (!read)
    {
        cout << "Invalid credentials" << endl;
        return;
    }

    string passLine;
    getline(read, passLine);
    read.close();
    if (passLine == password)
    {
        cout << "Login successful" << endl;
        return;
    }
    cout << "Invalid credentials" << endl;
}

//Rewriting password
void forgotPassword()
{
    string username;
    cout << "Enter your username:" << endl;
    cin >> username;

    ifstream read;
    string fileName = username + ".txt";
    read.open(fileName);

    if (!read)
    {
        cout << "Inavalid username" << endl;
    }
    else
    {
        // Take otp when username confirmed using number
        //currently out of scope of this project
        // if(otp == ----){below lines}

        string newPassword;
        cout << "Enter your new password" << endl;
        cin >> newPassword;

        ofstream write;
        write.open(fileName);
        write << newPassword;
        write.close();
        cout<<"Your password has been changed go to login screen."<<endl;
    }
}


int main()
{
    char c;
    // UI
    cout << "[L]ogin" << endl;
    cout << "[S]ign Up" << endl;
    cout << "[F]orgot Password" << endl;
    cout << endl;
    cout << "Enter your choice:" << endl;
    cin >> c;

    if (c == 's' || c == 'S')
        signUp();

    else if (c == 'l' || c == 'L')
        login();

    else if (c == 'f' || c == 'F')
        forgotPassword();

    else
        cout << "Please enter a correct option" << endl;

    return 0;
}
