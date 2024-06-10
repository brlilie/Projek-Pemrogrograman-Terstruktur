#include<iostream>
#include<fstream>
#include<string.h>
using namespace std;

int main();

void login()
{
    int count;
    string userId, password, id, pass;
    system("cls");
    cout<<"\t\t\t Mohon masukan username dan password: "<<endl;
    cout<<"\t\t\t USERNAME: ";
    cin>>userId;
    cout<<"\t\t\t PASSWORD: ";
    cin>>password;

    ifstream input("records.txt");

    while(input>>id>>pass)
    {
        if(id==userId && pass==password){
            count=1;
            system("cls");
        }
    }input.close();

    if(count=1)
    {
        cout<<userId<<"\n Kamu berhasil Login! ";
        main();
    }
    else{
        cout<<"Kamu belum registrasi, silahkan registrasi terlebih dahulu ";
        main();
    }

}

void registrasi()
{
    string ruserid, rpassword, rid, rpass;
    system("cls");
    cout<<"\t\t\t Masukan username: ";
    cin>>ruserid;
    cout<<"\t\t\t Masukan password: ";
    cin>>rpassword;


    //write inside the file
    ofstream f1("records.txt", ios::app);
    f1<<ruserid<<' '<<rpassword<<endl;
    system("cls");
    cout<<"\n\t\t\t Registrasi berhasil! ";
    main();
}

void forgot()
{
    int option;
    system("cls");
    cout<<"\t\t\t Kamu lupa password? Jangan khawatir \n";
    cout<<"Tekan 1 untuk mencari id kamu dengan username "<<endl;
    cout<<"Tekan 2 untuk kembali ke menu utama "<<endl;
    cout<<"\t\t\t Masukan pilihan kamu: ";  
    cin>>option;

    switch (option)
    {
    case 1 :
    {
        int count = 0;
        string suserId, sId, spass;
        cout<<"\n\t\t\tMasukan username yang kamu ingat: ";
        cin>>suserId;

        ifstream f2("records.txt");
        while(f2>>sId>>spass)
        {
            if(sId==suserId){
                count=1;
            }f2.close();
            if(count==1){
                cout<<"Username kamu ditemukan, passwordnya yaitu: "<<spass;
                main();
            }else{
                cout<<"Username kamu tidak ditemukan. ";
                main();
            }
        }
        break;
    }

    case 2 :
    {
        main();
    }

    default:
        cout<<"\t\t\t Pilihan kamu salah! silahkan coba lagi. "<<endl;
        forgot();
    } 
}

int main(){
int c;
cout<<"\t\t\t__________________________________________________\n\n\n";
cout<<"\t\t\t         Selamat datang di halaman login:)        \n\n\n";
cout<<"\t\t\t______________    MENU   ___________________________\n\n";
cout<<"                                                          \n\n";
cout<<"\t| Tekan 1 untuk LOGIN            |"<<endl;
cout<<"\t| Tekan 2 untuk REGISTER AKUN    |"<<endl;
cout<<"\t|Tekan 3 jika kamu LUPA PASSWORD |"<<endl;
cout<<"\t|Tekan 3 untuk KELUAR            |"<<endl;
cout<<"\n\t\t\t Masukan pilihan anda : ";
cin>>c;
cout<<endl;

switch(c)
{
    case 1:
         login();
         break;
    case 2:
         registrasi();
         break;
    case 3:
        forgot();
        break;
    case 4:
       cout<<"\t\t\t Terimakasih \n\n";
    default:
        system("cls");
        cout<<"Mohon pilih angka yang tertera pada pilihan di atas. "<<endl;
        main();
        
}
}

