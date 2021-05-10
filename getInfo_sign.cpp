#include<iostream>
#include<Windows.h>
#include<WinUser.h>
#include <fstream> 
#include<string>
#include <Lmcons.h>
#include <functional>
#include <Wincrypt.h>
#include <sstream> 
#include<vector>
#define MY_ENCODING_TYPE  (PKCS_7_ASN_ENCODING | X509_ASN_ENCODING)
using namespace std;
#define INFO_BUFFER_SIZE 32767
#define UNLEN 256

void computerInfo()
{
    TCHAR username[UNLEN + 1];
    DWORD size = UNLEN + 1;
    if (GetUserName((TCHAR*)username, &size))
    wcout << L"User name: " << username << L"\n";
    wstring name = username;
    hash <wstring> h;
    h(name);
    //wcout << L"hash user name: " << h(name) << endl;


    TCHAR  infoBuf[INFO_BUFFER_SIZE];
    DWORD  bufCharCount = INFO_BUFFER_SIZE;
    if (GetComputerName(infoBuf, &bufCharCount))
       wcout << L"Computer name: " << infoBuf << endl;
    wstring cname = infoBuf;
    h(cname);
    //wcout << L"hash computer name: " << h(cname) << endl;




    wchar_t path[MAX_PATH];
    GetWindowsDirectory(path, MAX_PATH);
   // wcout << L"Windows directory is " << path << L'\n';
    wstring path1 = path;
   // cout << "hash windows directory is " << h(path1);

    GetSystemDirectory(path, MAX_PATH);
   // wcout << L"System directory is " << path << L'\n';
    wstring path2 = path;
  //  cout << "hash system directory is " << h(path2);



    int keyboard_type = GetKeyboardType(0);
    int keyboard_buttons = GetKeyboardType(2);
    int keyboard_subtype = GetKeyboardType(1);
   /* cout << "Type:" << keyboard_type << "\n";
    cout << "Subtype: " << keyboard_subtype << "\n";
    cout << "Buttons:" << keyboard_buttons << "\n";
    */


    int nIndex = SM_CXSCREEN;
   // cout << "Width of screen: " << GetSystemMetrics(nIndex);

    hash <int> h1;
   /* cout << "hash keyboard type: " << h1(keyboard_type) << endl;
    cout << "hash keyboard subtype: " << h1(keyboard_subtype) << endl;
    cout << "hash width of screen: " << h1(GetSystemMetrics(nIndex)) << endl;


    */


    MEMORYSTATUS stat;
    stat.dwLength = sizeof(stat);
    GlobalMemoryStatus(&stat);
   // cout << "Total bytes of physical memory: " << (size_t)stat.dwTotalPhys;


    DWORD nsc, nbs, nfc, ncu;
    DWORD64 nf1;
    double nf;
    GetDiskFreeSpace(L"c:\\", &nsc, &nbs, &nfc, &ncu);

    nf1 = (DWORD64)nfc * (DWORD64)nsc * (DWORD64)nbs;

   // cout << "Total Number Of Free Bytes: " << nf1 << endl;
    nf = (double)nfc * (double)nsc * (double)nbs;
    nf = nf / 1024.0 / 1024;
   
    /*cout << "Accessible number of mb: " << nf << endl;

    cout << "hash total bytes of physical memory: " << h1((size_t)stat.dwTotalPhys) << endl;
    cout << "hash Total Number Of Free Bytes: " << h1(nf1) << endl;
    cout << "hash accessible number of mb: " << h1(nf) << endl;
    */
    ofstream file;
    file.open("data.txt");
    file << h(name) << h(cname) << h(path1) << h(path2) << h1(keyboard_type) << h1(keyboard_subtype) << h1(GetSystemMetrics(nIndex)) << h1((size_t)stat.dwTotalPhys) << h1(nf1) << h1(nf);

}

void sign()
{

    std::ifstream f("data.txt");
    std::stringstream ss;
    ss << f.rdbuf();
    string a = ss.str();

    HCRYPTPROV hProv;
    BYTE* pbBuffer = (BYTE*)(a);// data.txt
    DWORD dwBufferLen = strlen((char*)pbBuffer) + 1;
    HCRYPTHASH hHash;
    HCRYPTKEY hKey;
    HCRYPTKEY hPubKey;
    BYTE* pbKeyBlob;
    BYTE* pbSignature = (BYTE*)"Bondarchuk";
    DWORD dwSigLen;
    DWORD dwBlobLen;


    if (CryptAcquireContext(&hProv, NULL, NULL, PROV_RSA_FULL, 0))
    {
        cout << "CSP context acquired.\n";
    }
    if (CryptGetUserKey(hProv, AT_SIGNATURE, &hKey))
    {
        cout << "The signature key has been acquired. \n";
    }

    if (CryptExportKey(hKey, NULL, PUBLICKEYBLOB, 0, NULL, &dwBlobLen))
    {
        cout << "Size of the BLOB for the public key determined. \n";
    }
    else
    {
        cout << "Error computing BLOB length.";
    }
    if (pbKeyBlob = (BYTE*)malloc(dwBlobLen))
    {
        cout << "Memory has been allocated for the BLOB. \n";
    }
    else
    {
        cout << "Out of memory. \n";
    }

    if (CryptExportKey(hKey, NULL, PUBLICKEYBLOB, 0, pbKeyBlob, &dwBlobLen))
    {
        cout << "Contents have been written to the BLOB. \n";
    }
    else
    {
        cout << "Error during CryptExportKey.";
    }
    if (CryptCreateHash(hProv, CALG_MD5, 0, 0, &hHash))
    {
        cout << "Hash object created. \n";
    }
    else
    {
        cout << "Error during CryptCreateHash.";
    }

    if (CryptHashData(hHash, pbBuffer, dwBufferLen, 0))
    {
        cout << "The data buffer has been hashed.\n";
    }
    else
    {
        cout << "Error during CryptHashData.";
    }
    dwSigLen = 0;
    if (CryptSignHash(hHash, AT_SIGNATURE, NULL, 0, NULL, &dwSigLen))
    {
        printf("Signature length %d found.\n", dwSigLen);
    }
    if (pbSignature = (BYTE*)malloc(dwSigLen))
    {
        printf("Memory allocated for the signature.\n");
    }
    if (CryptSignHash(
        hHash,
        AT_SIGNATURE,
        NULL,
        0,
        pbSignature,
        &dwSigLen))
    {
        printf("pbSignature is the hash signature.\n");
    }

}


int main()
{
    computerInfo();
    sign();
}
