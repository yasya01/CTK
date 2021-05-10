// Lab1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
#include<iomanip>
#include<regex>
#include <cctype> 
#include<Windows.h>
#include<WinUser.h>
#include <Lmcons.h>
#include <functional>
#include <Wincrypt.h> 
#include<vector>
#define MY_ENCODING_TYPE  (PKCS_7_ASN_ENCODING | X509_ASN_ENCODING)
using namespace std;
#define INFO_BUFFER_SIZE 32767
#define UNLEN 256
#define NULL 0
using namespace std;



string login()
{
    string name, password;

    cout << "Put your name" << endl;
    cin >> name;
    if (name == "ADMIN")
    {
        return name;
    }
    
    if (name != "ADMIN")
    {
        
        ifstream myfile;
        myfile.open("example.csv");
        static char c = '\0';
        std::string buf = "\0";
        while (myfile.peek() >= 0 && !myfile.eof())
        {
            myfile >> c; buf += c;
        }

        std::size_t pos = 0;
        if ((pos = buf.find(name, 0)) != std::string::npos)
        {
            return name;
        }
        else
        {
            return "no user";       
        }
        myfile.close();
    }
    
}

bool password_in(string nameIn)
{
    
    string password, passwordIn;
   cout << "Put your password"<<endl;
   cin >> passwordIn;
       std::fstream ip("example.csv");
       std::string line;
       while (std::getline(ip, line))
       {
           std::istringstream iss(line);
           std::string name, password;

           if (getline(iss, name, ',') && getline(iss, password, ','))
           {
               if (name == nameIn && password == passwordIn)
               {
                   cout << "YOU LOGIN"<<endl;
                   return true;
               }
               if (name == nameIn && password != passwordIn)
               {
                   cout << "Incorrect password"<<endl; 
                   return false;
               }
           }
       }
       ip.close();
}

bool is_user(string nameIn)
{
    std::ifstream ip("example.csv");
    std::string line, name;
    int k = 0;
    while (std::getline(ip, line))
    {
        std::istringstream iss(line);

        if (getline(iss, name, ','))
        {
            if (name == nameIn)
            {
               // cout << "USER exists" << endl;
                k = +1;
                return true;
            }

        }
    }
    ip.close();
    if (k != 1)
    {
        return false;
    }

}
void add_user()
{
    
    string nameIn;
    cout << "Put name of new user" << endl;
    cin >> nameIn;
    ofstream file;
    file.open("example.csv", std::ios::app);
    if (is_user(nameIn)==false)
    {
        file << nameIn << "," << ' ' << "," << ' ' << "," << ' ' << '\n';
        cout << "new user added" << endl;
    }
    if((is_user(nameIn) == true))
        cout << "user exists" << endl;
    file.close();

}

void watch_user()
{
    std::ifstream ip("example.csv");
    string line, name, passwd, bl, rs;
    char k;
    cout << "Do u want to see all users(Y) one by one(N)?"<< endl;
    cin >> k;
    if (k == 'Y' or k == 'y')
    {
        cout << "-------------------------------------------|" << endl;
        cout << setw(10) << left << "NAME" << right << setw(10) << fixed << setprecision(2) << " | " << "blocked" << "  |  " << "restriction" << endl;
        cout << "-------------------------------------------|" << endl;
        while (std::getline(ip, line))
        {
            std::istringstream iss(line);
            getline(iss, name, ',') && getline(iss, passwd, ',') && getline(iss, bl, ',') && getline(iss, rs);
            cout << setw(10) << left << name << right << setw(10) << fixed << setprecision(2) << " | " << bl << "       |      " << rs << endl;
            cout << "-------------------------------------------|" << endl;
        }

    }
    if (k == 'N' or k == 'n')
    {
        cout << "-------------------------------------------|" << endl;
        cout << setw(10) << left << "NAME" << right << setw(10) << fixed << setprecision(2) << " | " << "blocked" << "  |  " << "restriction" << endl;
        cout << "-------------------------------------------|" << endl;
        int i;
        while (std::getline(ip, line))
        {   
            std::istringstream iss(line);
            getline(iss, name, ',') && getline(iss, passwd, ',') && getline(iss, bl, ',') && getline(iss, rs);
            cout << setw(10) << left << name << right << setw(10) << fixed << setprecision(2) << " | " << bl << "       |      " << rs << endl;
            cout << "-------------------------------------------|" << endl;
            cout << "Next?(1-yes 0-no)" << endl;  
            cin >> i;
            if (i == 0)
            {
                break;
            }
            else
            {
                system("cls");
                continue;
            }                                        
        }
   }    
    else
        cout << "Put correct char" << endl;
}


bool check_passwd(string passwordIn)
{
    smatch result;
    regex regular("[a-zA-Z]");
    regex regular1("[а-яёА-ЯЁ]");
    if ((regex_search(passwordIn, result, regular)) && (regex_search(passwordIn, result, regular1)))
    {
        cout << "Correct password" << endl;
        return true;
    }
    else
    {
        cout << "Incorrect password. Try again"<<endl;
        return false;
    }

}

bool check_bl(string nameIn)
{

    std::ifstream ip("example.csv");
    std::string line, name, passwd, bl;

    while (std::getline(ip, line))
    {
        std::istringstream iss(line);

        if (getline(iss, name, ','))
        {
            if (name == nameIn)
            {
                getline(iss, passwd, ','); getline(iss, bl, ',');
                if (bl == "y")
                {
                    //cout << "user is blocked" << endl;
                    return true;
                }
                if (bl == "n")
                {
                   // cout << "user isn`t blocked" << endl;
                    return false;
                }
                else
                    cout << "error in block"<<endl;
            }
        }
    }
    ip.close();
}

bool is_passwd(string nameIn)
{
    std::ifstream ip("example.csv");
    std::string line, name, passwd, bl;
    while (std::getline(ip, line))
    {
        std::istringstream iss(line);

        if (getline(iss, name, ','))
        {
            if (name == nameIn)
            {
                getline(iss, passwd, ',');
                if (passwd.length()!= NULL)
                {
                    return true;
                }
                if (passwd.length() == NULL)
                {
                    return false;
                }
                else
                    cout << "error  put passwd" << endl;
            }
        }
    }
    ip.close();
}

bool check_r(string nameIn)
{
    std::ifstream ip("example.csv");
    std::string line, name, passwd, bl, restr;

    while (std::getline(ip, line))
    {
        std::istringstream iss(line);

        if (getline(iss, name, ','))
        {
            if (name == nameIn)
            {
                getline(iss, passwd, ','); getline(iss, bl, ','); getline(iss, restr, ',');
                //cout << "restr - " << restr << endl;
                if (restr == "y")
                {
                   // cout << "user has restriction" << endl;
                    return true;
                }
                if (restr == "n")
                {
                   // cout << "user hasn`t restriction" << endl;
                    return false;
                }
                else
                    cout << "error" << endl;
            }
        }
    }
    ip.close();
}


void put_bl(string nameIn)
{
    if (check_bl(nameIn) == false)
    {

        string name, passwd, bl, restr;
        std::ifstream ip("example.csv");
        ofstream temp;
        temp.open("temp.csv");
        std::string line;
        while (getline(ip, line))
        {
            std::istringstream iss(line);
            std::string name;

            if (getline(iss, name, ','))
            {
                getline(iss, passwd, ','); getline(iss, bl, ','); getline(iss, restr, ',');

                if (name == nameIn)
                {                  
                    temp << name << "," << passwd << "," << "y" << "," << restr << endl;                 
                }
                else
                {
                    temp << name << "," << passwd << "," << bl << "," << restr << endl;;
                }
            }
            else
            {
                cout << "ERROR" << endl;
            }
        }
        ip.close();
        temp.close();

        remove("example.csv");
        char oldname[] = "temp.csv";
        char newname[] = "example.csv";

        //	Deletes the file if exists 
        if (rename(oldname, newname) != 0)
            perror("Error renaming file");
       // else
          //  cout << "File renamed successfully";
    }
    if (check_bl(nameIn) == true)
    {
        cout << "user is blocked" << endl;
    }
}

void take_bl(string nameIn)
{
    if (check_bl(nameIn) == true)
    {

        string name, passwd, bl, restr;
        std::ifstream ip("example.csv");
        ofstream temp;
        temp.open("temp.csv");
        std::string line;
        while (getline(ip, line))
        {
            std::istringstream iss(line);
            std::string name;

            if (getline(iss, name, ','))
            {
                getline(iss, passwd, ','); getline(iss, bl, ','); getline(iss, restr, ',');

                if (name == nameIn)
                {
                    temp << name << "," << passwd << "," << "n" << "," << restr << endl;
                }
                else
                {
                    temp << name << "," << passwd << "," << bl << "," << restr << endl;;
                }
            }
            else
            {
                cout << "ERROR" << endl;
            }
        }
        ip.close();
        temp.close();

        remove("example.csv");
        char oldname[] = "temp.csv";
        char newname[] = "example.csv";

        //	Deletes the file if exists 
        if (rename(oldname, newname) != 0)
            perror("Error renaming file");
      //  else
        //    cout << "File renamed successfully";
    }
    if (check_bl(nameIn) == false)
    {
        cout << "user isn`t blocked" << endl;
    }
}

void put_restr(string nameIn)
{
    if (check_r(nameIn) == false)
    {

        string name, passwd, bl, restr;
        std::ifstream ip("example.csv");
        ofstream temp;
        temp.open("temp.csv");
        std::string line;
        while (getline(ip, line))
        {
            std::istringstream iss(line);
            std::string name;

            if (getline(iss, name, ','))
            {
                getline(iss, passwd, ','); getline(iss, bl, ','); getline(iss, restr, ',');

                if (name == nameIn)
                {
                    temp << name << "," << passwd << "," << bl << "," << "y" << endl;
                    cout << "Password restriction puted" << endl;
                }
                else
                {
                    temp << name << "," << passwd << "," << bl << "," << restr << endl;;
                }
            }
            else
            {
                cout << "ERROR" << endl;
            }
        }
        ip.close();
        temp.close();

        remove("example.csv");
        char oldname[] = "temp.csv";
        char newname[] = "example.csv";

        //	Deletes the file if exists 
        if (rename(oldname, newname) != 0)
            perror("Error renaming file");
        //else
          //  cout << "File renamed successfully";
    }
    if (check_bl(nameIn) == true)
    {
        cout << "user has restriction" << endl;
    }
}

void take_restr(string nameIn)
{
    if (check_r(nameIn) == true)
    {

        string name, passwd, bl, restr;
        std::ifstream ip("example.csv");
        ofstream temp;
        temp.open("temp.csv");
        std::string line;
        while (getline(ip, line))
        {
            std::istringstream iss(line);
            std::string name;

            if (getline(iss, name, ','))
            {
                getline(iss, passwd, ','); getline(iss, bl, ','); getline(iss, restr, ',');

                if (name == nameIn)
                {
                    temp << name << "," << passwd << "," << bl << "," << "n" << endl;
                    cout << "Password restriction taked" << endl;
                }
                else
                {
                    temp << name << "," << passwd << "," << bl << "," << restr << endl;;
                }
            }
            else
            {
                cout << "ERROR" << endl;
            }
        }
        ip.close();
        temp.close();

        remove("example.csv");
        char oldname[] = "temp.csv";
        char newname[] = "example.csv";

        //	Deletes the file if exists 
        if (rename(oldname, newname) != 0)
            perror("Error renaming file");
       // else
        //    cout << "File renamed successfully";
    }
    if (check_bl(nameIn) == false)
    {
        cout << "user hasn`t restriction" << endl;
    }
}

void put_first_passwd(string nameIn)
{

    if (check_r(nameIn) == true)
    {
        string passwordIn, password, password_new, passwd_rep, bl, restr;
        std::ifstream ip("example.csv");
        ofstream temp;
        temp.open("temp.csv");
        std::string line;
        while (getline(ip, line))
        {
            std::istringstream iss(line);
            std::string name;

            if (getline(iss, name, ','))
            {
                getline(iss, password, ','); getline(iss, bl, ','); getline(iss, restr, ',');

                if (name == nameIn)
                {
                    cout << "Put your password. Include kirilic and latin letter" << endl;
                                 
                    for (int i = 0; i < 2; i++)
                    {
                      
                        cin >> password_new;
                        if (check_passwd(password_new) == true)
                        {
                            cout << "Repeat your new password" << endl;
                            cin >> passwd_rep;
                            if (password_new == passwd_rep)
                            {
                                cout << "Your password changed " << password << endl;
                                temp << name << "," << password_new << "," << bl << "," << restr << endl;
                            }
                            else
                            {
                                cout << "not equal" << endl;
                            }
                        }
                        else
                            cout << "Put your password.Include kirilic and latin letter" << endl;
                    }
                  
                }
            
                else
                {
                    temp << name << "," << password << "," << bl << "," << restr << endl;
                }
            }
            else
            {
                cout << "ERROR" << endl;
            }
        }
        ip.close();
        temp.close();

        remove("example.csv");
        char oldname[] = "temp.csv";
        char newname[] = "example.csv";

        //	Deletes the file if exists 
        if (rename(oldname, newname) != 0)
            perror("Error renaming file");
      //  else
        //    cout << "File renamed successfully";
    }


    if (check_r(nameIn) == false)
    {
        string passwordIn, password, password_new, passwd_rep, bl, restr;
        std::ifstream ip("example.csv");
        ofstream temp;
        temp.open("temp.csv");
        std::string line;
        while (getline(ip, line))
        {
            std::istringstream iss(line);
            std::string name;

            if (getline(iss, name, ','))
            {
                getline(iss, password, ','); getline(iss, bl, ','); getline(iss, restr, ',');

                if (name == nameIn)
                {

                    cout << "Put your password" << endl;
                    cin >> password_new;
                        cout << "Repeat your new password" << endl;
                        cin >> passwd_rep;
                        if (password_new == passwd_rep)
                        {
                            cout << "Your password changed " << password << endl;
                            temp << name << "," << password_new << "," << bl << "," << restr << endl;
                        }
                        else
                        {
                            cout << "not equal" << endl;
                        }
                    

                }
                else
                {
                    temp << name << "," << password << "," << bl << "," << restr << endl;
                }
            }
            else
            {
                cout << "ERROR" << endl;
            }
        }
        ip.close();
        temp.close();

        remove("example.csv");
        char oldname[] = "temp.csv";
        char newname[] = "example.csv";

        //	Deletes the file if exists 
        if (rename(oldname, newname) != 0)
            perror("Error renaming file");
       // else
        //    cout << "File renamed successfully";
    }
}


void password_change(string nameIn)
{   

    if (check_r(nameIn) == true)
    {
        string passwordIn, password, password_new, passwd_rep, bl, restr;
        //string name = login();
        std::ifstream ip("example.csv");
        ofstream temp;
        temp.open("temp.csv");
        std::string line;
        cout << "Put your password" << endl;
        cin >> passwordIn;
        while (getline(ip, line))
        {
            std::istringstream iss(line);
            std::string name;

            if (getline(iss, name, ','))
            {
                getline(iss, password, ','); getline(iss, bl, ','); getline(iss, restr, ',');

                if (name == nameIn && password != passwordIn)
                {
                    cout << "Incorrect password";
                }

                if (name == nameIn && password == passwordIn)
                {
                    cout << "Put your password. Include kirilic and latin letter" << endl;
                    cin >> password_new;
                    if (check_passwd(password_new) == true)
                    {
                        cout << "Repeat your new password" << endl;
                        cin >> passwd_rep;
                        if (password_new == passwd_rep)
                        {
                            cout << "Your password changed " << password << endl;
                            temp << name << "," << password_new << "," << bl << "," << restr << endl;
                        }
                        else
                        {
                            cout << "not equal" << endl;
                        }
                    }
                    else
                        cout << "Put your password.Include kirilic and latin letter" << endl;

                }
                else
                {
                    temp << name << "," << password << "," << bl << "," << restr << endl;
                }
            }
            else
            {
                cout << "ERROR" << endl;
            }
        }
        ip.close();
        temp.close();

        remove("example.csv");
        char oldname[] = "temp.csv";
        char newname[] = "example.csv";

        //	Deletes the file if exists 
        if (rename(oldname, newname) != 0)
            perror("Error renaming file");
    }
    if (check_r(nameIn) == false)
    {
        string passwordIn, password, password_new, passwd_rep, bl, restr;
        //string name = login();
        std::ifstream ip("example.csv");
        ofstream temp;
        temp.open("temp.csv");
        std::string line;
        cout << "Put your password" << endl;
        cin >> passwordIn;
        while (getline(ip, line))
        {
            std::istringstream iss(line);
            std::string name;

            if (getline(iss, name, ','))
            {
                getline(iss, password, ','); getline(iss, bl, ','); getline(iss, restr, ',');

                if (name == nameIn && password != passwordIn)
                {
                    cout << "Incorrect password";
                }

                if (name == nameIn && password == passwordIn)
                {
                    cout << "Put your new password:" << endl;
                    cin >> password_new;
                    
                        cout << "Repeat your new password: " << endl;
                        cin >> passwd_rep;
                        if (password_new == passwd_rep)
                        {
                            cout << "Your password changed " << password << endl;
                            temp << name << "," << password_new << "," << bl << "," << restr << endl;
                        }
                        else
                        {
                            cout << "not equal" << endl;
                        }
                    
                    

                }
                else
                {
                    temp << name << "," << password << "," << bl << "," << restr << endl;
                }
            }
            else
            {
                cout << "ERROR" << endl;
            }
        }
        ip.close();
        temp.close();

        remove("example.csv");
        char oldname[] = "temp.csv";
        char newname[] = "example.csv";

        //	Deletes the file if exists 
        if (rename(oldname, newname) != 0)
            perror("Error renaming file");
    }


}





void admin_menu()
{
    while (1)
    {
        int opt;

        cout << endl << "----------------------------" << endl;
        cout << endl << "      Admin Menu   " << endl;
        cout << endl << "----------------------------" << endl;
        cout << "1. Change password" << endl;
        cout << "2. Show list of users" << endl;
        cout << "3. Put new user" << endl;
        cout << "4. Block user" << endl;
        cout << "5. Put password restriction" << endl;
        cout << "6. Take password restriction" << endl;
        cout << "7. Exit" << endl;
           
        cin >> opt;
        cout << "\n" << endl;

        switch (opt)
        {
        case 1:
            password_change("ADMIN");
            break;
        case 2:
            watch_user();
            break;
        case 3:
            add_user();
            break;
        case 4:
        {
            string nameIn;
            cout << "Please put username" << endl;
            cin >> nameIn;
            if (is_user(nameIn))
            {
                put_bl(nameIn);

            }
            else
                cout << "no user with this name" << endl;
            break;
        }
        case 5:
        {
            string nameIn;
            cout << "Please put username" << endl;
            cin >> nameIn;
            if (is_user(nameIn))
            {
                put_restr(nameIn);
            }
            else
                cout << "no user with this name" << endl;
            break;
        }
        case 6:
        {
            string nameIn;
            cout << "Please put username" << endl;
            cin >> nameIn;
            if (is_user(nameIn))
            {
                take_restr(nameIn);
            }
            else
                cout << "no user with this name" << endl;
            break;
        }
        case 7:
            exit(1);
        default:
            break;
        }

    }
}


void user_menu(string nameIn)
{
    while (1)
    {
        int opt;

        cout << endl << "----------------------------" << endl;
        cout << endl << "      User Menu   " << endl;
        cout << endl << "----------------------------" << endl;
        cout << "1. Change password" << endl;
        cout << "2. Exit" << endl;

        cin >> opt;
        cout << "\n" << endl;

        switch (opt)
        {
        case 1:
            password_change(nameIn);
            break;
        case 2:
            exit(1);
        default:
            break;
        }

    }
}

void read_file()
{
    ifstream file("Info.txt");
    string line;
    if (file.is_open())
    {   
        cout << "Info" << endl;
        while (getline(file, line))
        {
            std::cout << line << std::endl;
        }
    }
    file.close();
}
void computerInfo()
{
    TCHAR username[UNLEN + 1];
    DWORD size = UNLEN + 1;
    if (GetUserName((TCHAR*)username, &size))
        wcout << L"User name: " << username << L"\n";
    wstring name = username;
    hash <wstring> h;
    h(name);
    TCHAR  infoBuf[INFO_BUFFER_SIZE];
    DWORD  bufCharCount = INFO_BUFFER_SIZE;
    if (GetComputerName(infoBuf, &bufCharCount))
        wcout << L"Computer name: " << infoBuf << endl;
    wstring cname = infoBuf;
    h(cname);
    wchar_t path[MAX_PATH];
    GetWindowsDirectory(path, MAX_PATH);
    wstring path1 = path;
    GetSystemDirectory(path, MAX_PATH);
    wstring path2 = path;
    int keyboard_type = GetKeyboardType(0);
    int keyboard_buttons = GetKeyboardType(2);
    int keyboard_subtype = GetKeyboardType(1); 
    int nIndex = SM_CXSCREEN;
    hash <int> h1;
    MEMORYSTATUS stat;
    stat.dwLength = sizeof(stat);
    GlobalMemoryStatus(&stat);
    DWORD nsc, nbs, nfc, ncu;
    DWORD64 nf1;
    double nf;
    GetDiskFreeSpace(L"c:\\", &nsc, &nbs, &nfc, &ncu);
    nf1 = (DWORD64)nfc * (DWORD64)nsc * (DWORD64)nbs;
    nf = (double)nfc * (double)nsc * (double)nbs;
    nf = nf / 1024.0 / 1024;
    ofstream file;
    file.open("data.txt");
    file << h(name) << h(cname) << h(path1) << h(path2) << h1(keyboard_type) << h1(keyboard_subtype) << h1(GetSystemMetrics(nIndex)) << h1((size_t)stat.dwTotalPhys) << h1(nf1) << h1(nf);

}

bool check_sign()
{
    HCRYPTPROV hProv;
    BYTE* pbBuffer = (BYTE*)"28274873903423424879226167186315368679591827780651268118805352621397116624417771527245903808446037";// data.txt
    DWORD dwBufferLen = strlen((char*)pbBuffer) + 1;
    HCRYPTHASH hHash;
    HCRYPTKEY hKey;
    HCRYPTKEY hPubKey;
    BYTE* pbKeyBlob;
    BYTE* pbSignature;
    DWORD dwSigLen;
    DWORD dwBlobLen;


    if (CryptImportKey(hProv, pbKeyBlob, dwBlobLen, 0, 0, &hPubKey))
    {
        printf("The key has been imported.\n");
    }

    if (CryptCreateHash(hProv, CALG_MD5, 0, 0, &hHash))
    {
        printf("The hash object has been recreated. \n");
    }


    if (CryptHashData(hHash, pbBuffer, dwBufferLen, 0))
    {
        cout << "The new hash has been created.\n";
    }
    else
        if (CryptVerifySignature(hHash, pbSignature, dwSigLen, hPubKey, NULL, 0))
        {
            cout << "The signature has been verified.\n";
            return true;
        }
        else
        {
            cout << "Signature not validated!\n";
            return false;
        }

}





int main()
{
   
    ofstream file("example.csv");
    char k[] = " ";
    file << "ADMIN"<<","<<","<<"n"<<","<<"n";
    file.close();
    if (check_sign())
    {
        while (1)
        {
            int opt;

            cout << "----------------------------|" << endl;
            cout << "     Menu   " << endl;
            cout << "----------------------------|" << endl;
            cout << "1. LogIn as ADMIN" << endl;
            cout << "----------------------------|" << endl;
            cout << "2. LogIn as USER" << endl;
            cout << "----------------------------|" << endl;
            cout << "3. Program info " << endl;
            cout << "----------------------------|" << endl;
            cout << "4. Exit" << endl;
            cout << "----------------------------|" << endl;

            cin >> opt;
            cout << "\n" << endl;

            switch (opt)
            {
            case 1:
            {
                string nameIn = login();

                if (nameIn == "ADMIN")
                {
                    if (is_passwd(nameIn))
                    {
                        //cout << "is passwd";
                        if (password_in(nameIn) == true)
                        {
                            admin_menu();
                        }
                    }
                    else
                    {
                        cout << "no passwd" << endl;
                        put_first_passwd(nameIn);
                        admin_menu();

                    }
                }
                break;
            }
            case 2:
            {
                string nameIn = login();
                if (nameIn != "ADMIN")
                {
                    if (is_user(nameIn))
                    {
                        if (check_bl(nameIn) == true)
                            cout << "you are blocked" << endl;
                        if (check_bl(nameIn) == false)
                        {
                            if (is_passwd(nameIn))
                            {
                                for (int i = 0; i < 3; i++)
                                {
                                    if (password_in(nameIn) == true)
                                    {
                                        user_menu(nameIn);
                                        break;
                                    }
                                }

                            }
                            else
                            {
                                // cout << "FIRST" << endl;
                                put_first_passwd(nameIn);
                                user_menu(nameIn);

                            }
                        }
                    }
                    else
                        cout << "no user with this name in database" << endl;
                }
                break;
            }
            case 3:
            {
                read_file();
                break;
            }
            case 4:
                exit(1);
            default:
                break;
            }

        }
    }
    else
        exit(1);
    return 0;
}

