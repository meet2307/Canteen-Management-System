//Some Header files.
#include<iostream>
#include<fstream>
#include<string.h>
#include<string>
#include<stdlib.h>
#include<dos.h>
#include<windows.h>
#include<time.h>
#include<conio.h>
#include<iomanip>
#include<stdio.h>
#include<cstdlib>

using namespace std;

//Class Declaration
class login;
class employee;
class store;
class order;

//Global Function Declaration.
void empjump();
void loginjump();
void SetColor(int);
void date_time();
void loading();
void Today();


//Function Declaration
void gotoxy(int ,int );

COORD coord={0,0};
void gotoxy(int x,int y)
{
    coord.X=x;
    coord.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

//Class Declaration
class login;
class employee;
class store;
class customer;

//Structure of Dish Details
struct dish_detail{
    char name[50];
    int key,quantity;
    float price;
}dd;

//Temp Structure For Billing
struct temp{
char d[50];
float p,amount;
int qty;
}tp;


//Class Store
class store
{
    public:
        char y;
        string item;
        string name;
        int amt;
        int choice;
        int rate;
        int quantity=0;
        void storepage()
        {
            system("CLS");
            gotoxy(40,1);cout<<"CAN101";
            gotoxy(40,2);cout<<"--------"<<endl<<endl;
            cout<<"     1. VIEW INVENTORY"<<endl;
            cout<<"     2. ADD DISH"<<endl;
            cout<<"     3. SEARCH DISH"<<endl;
            cout<<"     4. UPDATE DISH"<<endl;
            cout<<"     5. DELETE DISH"<<endl;
            cout<<"     6. GO BACK"<<endl;
            cout<<"     7. EXIT"<<endl<<endl;
            cout<<"     ENTER CHOICE"<<endl;
            cout<<"     ";
            cin>>choice;
            while(1)
                {
                    switch(choice)
                    {
                        case 1:
                            view_inventory();
                            storepage();
                            break;
                        case 2:
                            add_dish();
                            storepage();
                            break;
                        case 3:
                            search_dish();
                            storepage();
                            break;
                        case 4:
                            update_dish();
                            storepage();
                            break;
                        case 5:
                            delete_dish();
                            storepage();
                            break;
                        case 6:
                            empjump();
                        case 7:
                            exit(0);
                        default:
                            cout<<endl<<"     INVALID CHOICE"<<endl<<endl;
                            cout<<"     ENTER CHOICE"<<endl<<endl;
                            cout<<"     ";
                            cin>>choice;
                    }
                }
        }
        void view_inventory()
        {
            int c=0;
            fstream view;
            view.open("DISH.txt",ios::in);
            cout<<"\n     ||| Key  | DISH NAME         | PRICE  | QUANTITY |||"<<endl;
            cout<<"     ---------------------------------------------------"<<endl;
            while(view>>dd.key>>dd.name>>dd.price>>dd.quantity)
            {
                cout<<"     ||| "<<setw(4)<<std::left<<dd.key<<" | "<<setw(17)<<std::left<<dd.name<<" | "<<setw(6)<<std::left<<dd.price<<" | "<<setw(8)<<std::left<<dd.quantity<<" |||"<<endl ;
                c++;
            }
            cout<<"     ---------------------------------------------------"<<endl;
            if(c==0)
            {
                cout<<"list is empty"<<endl;
            }
            view.close();
            cout<<endl<<"     PRESS ANY KEY TO GO BACK "<<endl;
            cout<<"     ";getch();
        }
        void add_dish()
        {
            char a;
            int k;
            fstream add;
            top:
            while(a!='n')
                {
                    add.open("DISH.txt",ios::in);
                    cout<<"enter the dish key:";
                    cin>>k;
                     while(add>>dd.key>>dd.name>>dd.price>>dd.quantity)
                        {
                            if(dd.key==k)
                            {
                                cout<<"key is already exist"<<endl;
                                add.close();
                            goto top;
                            }
                        }
                    add.close();
                    add.open("DISH.txt",ios::app);
                    dd.key=k;
                    cin.ignore();
                    cout<<"ENTER THE DISH NAME:";
                    gets(dd.name);
                    cout<<"ENTER THE DISH PRICE:";
                    cin>>dd.price;
                    cout<<"ENTER THE DISH QUANTITY:";
                    cin>>dd.quantity;
                    add<<dd.key<<' '<<dd.name<<' '<<dd.price<<' '<<dd.quantity<<endl;
                    cout<<"do you want to add an other [y/n]:";
                    cin>>a;
                    add.close();
                }
        }
        void search_dish()
        {
            int a,c=0;
            fstream searchkey;
            searchkey.open("DISH.txt",ios::in);
            cout<<"enter the dish key:";
            cin>>a;
            cout<<"\tKey\t\tDISH NAME\t\tPRICE\t\tQUANTITY"<<endl;
            while(searchkey>>dd.key>>dd.name>>dd.price>>dd.quantity)
            {
                if(dd.key==a)
                {
                    cout<<"\t"<<dd.key<<"\t\t"<<dd.name<<"\t\t\t"<<dd.price<<"\t\t\t"<<dd.quantity<<endl;
                    c++;
                }
            }
            if(c==0)
            {
                cout<<"Dish not found"<<endl;
            }
            searchkey.close();
            cout<<endl<<"     PRESS ANY KEY TO GO BACK "<<endl;
            cout<<"     ";getch();
        }
        void update_dish()
        {
            int a,p,c=0;
            fstream update;
            update.open("DISH.txt",ios::in|ios::out);
            ofstream update1("TEMP_DISH.txt");
            cout<<"enter the dish key:";
            cin>>a;
            update.seekg(0);
            while(update>>dd.key>>dd.name>>dd.price>>dd.quantity)
            {
                if(dd.key==a)
                {
                    cout<<"destinatio record:"<<endl;
                    cout<<"\t"<<dd.key<<"\t\t"<<dd.name<<"\t\t\t"<<dd.price<<"\t\t\t"<<dd.quantity<<endl;
                    cout<<"ENTER NEW DISH KEY:";
                    cin>>dd.key;
                    cin.ignore();
                    cout<<"ENTER NEW DISH NAME:";
                    gets(dd.name);
                    cout<<"ENTER NEW DISH PRICE:";
                    cin>>dd.price;
                    cout<<"ENTER NEW DISH QUANTITY:";
                    cin>>dd.quantity;
                    update1<<dd.key<<' '<<dd.name<<' '<<dd.price<<' '<<dd.quantity<<endl;
                    c++;
                }
                else
                {
                    update1<<dd.key<<' '<<dd.name<<' '<<dd.price<<' '<<dd.quantity<<endl;
                }

            }
            if(c==0)
            {
                cout<<"not found"<<endl;
            }
            update.close();
            update1.close();
            remove("DISH.txt");
            rename("TEMP_DISH.txt","DISH.txt");
            cout<<endl<<"     PRESS ANY KEY TO GO BACK "<<endl;
            cout<<"     ";getch();
        }
        void delete_dish()
        {
            int a,c;
            fstream dlt,dlt1;
            dlt.open("DISH.txt",ios::in);
            dlt1.open("TEMP_DELETE.txt",ios::app);
            cout<<"enter the dish key:";
            cin>>a;
            cout<<"\n\tKey\t\tDISH NAME\t\tPRICE\t\tQUANTITY"<<endl;
            while(dlt>>dd.key>>dd.name>>dd.price>>dd.quantity)
            {
                if(dd.key==a)
                {
                    c++;
                    cout<<dd.key<<' '<<dd.name<<' '<<dd.price<<' '<<dd.quantity<<endl;
                    cout<<"destination record is deleted"<<endl;
                }
                if(dd.key!=a)
                {
                    dlt1<<dd.key<<' '<<dd.name<<' '<<dd.price<<' '<<dd.quantity<<endl;
                }
            }
            dlt.close();
            dlt1.close();
            if(c==0)
            {
                cout<<"not found"<<endl;
            }
            remove("DISH.txt");
            rename("TEMP_DELETE.txt","DISH.txt");
            cout<<endl<<"     PRESS ANY KEY TO GO BACK "<<endl;
            cout<<"     ";getch();
        }
};//Store Class Ended

//Customer Class Strat
class customer
{
    public:
        int choice;
        char cname[20];
        void customerpage()
        {
            system("CLS");
            cout<<"     1. VIEW INVENTORY & Take Order"<<endl;
            cout<<"     2. GO BACK TO LOGIN PAGE"<<endl;
            cout<<"     3. EXIT"<<endl<<endl;
            cout<<"     ENTER CHOICE"<<endl;
            cout<<"     ";
            cin>>choice;
            while(1)
                {
                    switch(choice)
                    {
                        case 1:
                            take_order();
                            customerpage();
                            break;
                        case 2:
                            loginjump();
                            break;
                        case 3:
                            exit(0);
                        default:
                            cout<<endl<<"     INVALID CHOICE"<<endl<<endl;
                            cout<<"     ENTER CHOICE"<<endl<<endl;
                            cout<<"     ";
                            cin>>choice;
                    }
                }
        }
        void take_order()
        {
            int c=0,empty_list=1;
            fstream view;
            view.open("DISH.txt",ios::in);
            cout<<"\n     ||| Key  | DISH NAME         | PRICE  | QUANTITY |||"<<endl;
            cout<<"     ---------------------------------------------------"<<endl;
            while(view>>dd.key>>dd.name>>dd.price>>dd.quantity)
            {
                cout<<"     ||| "<<setw(4)<<std::left<<dd.key<<" | "<<setw(17)<<std::left<<dd.name<<" | "<<setw(6)<<std::left<<dd.price<<" | "<<setw(8)<<std::left<<dd.quantity<<" |||"<<endl ;
                c++;
            }
            cout<<"     ---------------------------------------------------"<<endl;
            if(c==0)
            {
                empty_list=0;
            }
            view.close();
            if(empty_list==1)
            {
                int a,c=0;
                char pay;
                char ch;
                float total=0;
                fstream b,o,on;
                b.open("BILL.txt",ios::out);
                cin.ignore();
                do{
                    cout<<"     ENTER JUST NAME OF CUSTOMER"<<endl;
                    cout<<"     ";
                    gets(cname);

                }while(!strcmp(cname,""));
                cout<<endl;
                while(ch!='n')
                    {
                        o.open("DISH.txt",ios::in);
                        on.open("temp_DISH.txt",ios::out);
                        cout<<"enter the dish key:";
                        cin>>a;
                        o.seekg(0);
                        while(o>>dd.key>>dd.name>>dd.price>>dd.quantity)
                        {
                            if(dd.key==a)
                            {
                                c++;
                                cout<<"enter the quantity:";
                                cin>>tp.qty;
                                if(dd.quantity>=tp.qty)
                                {
                                    dd.quantity -= tp.qty;
                                    on<<dd.key<<' '<<dd.name<<' '<<dd.price<<' '<<dd.quantity<<endl;
                                    tp.amount=tp.qty*dd.price;
                                    cout<<"\t"<<dd.name<<"\t\t"<<dd.price<<"*"<<tp.qty<<"\t\t"<<tp.amount<<endl;
                                    strcpy(tp.d,dd.name);
                                    tp.p=dd.price;
                                    b<<tp.d<<' '<<tp.p<<' '<<tp.qty<<' '<<tp.amount<<endl;
                                    total=total+tp.amount;
                                }
                                else
                                {
                                    cout<< "    QUANTITY OF DISH IS NOT AVAILABLE   "<<endl;
                                    on<<dd.key<<' '<<dd.name<<' '<<dd.price<<' '<<dd.quantity<<endl;
                                }
                            }
                            else
                            {
                                on<<dd.key<<' '<<dd.name<<' '<<dd.price<<' '<<dd.quantity<<endl;
                            }
                        }
                        if(c==0)
                        {
                            cout<<"not found"<<endl;
                        }
                        cout<<"do you want to order more [y/n]";
                        cin>>ch;
                        o.close();
                        on.close();
                        remove("DISH.txt");
                        rename("temp_DISH.txt","DISH.txt");
                    }
                b.close();
                cout<<"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"<<endl;
                cout<<"|||||||||||||||||||||||||||||||||||||||||||||||| BILL  |||||||||||||||||||||||||||||||||||||||||||||||||||||||"<<endl;
                cout<<"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"<<endl;
                showbill();
                cout<<"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"<<endl;
                cout<<"|||\t\t\t\t\t\t\t   TOTAL="<<total<<"\t\t\t\t\t   |||"<<endl;
                cout<<"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"<<endl;
                fstream salerecord("SALESRECORD.txt",ios::app);
                salerecord<<cname<<' '<<total<<endl;
                salerecord.close();
                cout<<endl<<"     ::: PAY THE BILL :::";
                cout<<endl<<"     PRESS ANY KEY TO GO BACK "<<endl;
                cout<<"     ";getch();
            }
            else
            {
                cout<<"List Is Empty So You Can Not Order Anything ";
                cout<<endl<<"     PRESS ANY KEY TO GO BACK "<<endl;
                cout<<"     ";getch();
            }

        }
        void showbill()
        {
            fstream obj;
            obj.open("BILL.txt",ios::in);
            cout<<"     \nHELLO "<<cname<<endl;
            cout<<"\tDISH NAME\t\tPRICE\t\tQTY\t\tAMOUNT"<<endl;
            while(obj>>tp.d>>tp.p>>tp.qty>>tp.amount)
            {

                    cout<<"\t"<<tp.d<<"\t\t\t"<<tp.p<<"\t\t"<<tp.qty<<"\t\t"<<tp.amount<<endl;


            }
            obj.close();
        }
};

//Class Sales
class sales
{
    public:
        string name;
        int amt;
        char dec;
        void viewstat()
        {
            system("CLS");
            gotoxy(0,0);Today();
            gotoxy(78,2);cout<<">-----------------<"<<endl;
            gotoxy(78,3);cout<<">     CAN 101     <"<<endl;
            gotoxy(78,4);cout<<">-----------------<"<<endl;
            ifstream viewsr("SALESRECORD.txt");
            gotoxy(80,6);cout<<"SALES RECORDS :> ";
            gotoxy(71,8);cout<<"---------------------------------";
            gotoxy(71,9);cout<<"||| NAME         | AMOUNT     |||";
            gotoxy(71,10);cout<<"---------------------------------";
            int i=11;
            while (viewsr>>name>>amt)
            {
                gotoxy(71,i);cout<<"||| "<<setw(12)<<std::left<<name<<" | "<<"$"<<setw(10)<<std::left<<amt<<"|||"<<endl;
                i++;
            }
            gotoxy(71,i);cout<<"---------------------------------"<<endl;
            viewsr.close();

            cout<<endl<<"     PRESS ANY KEY TO GO BACK "<<endl;
            cout<<"     ";getch();
        }
        void clearstat()
        {

            system("CLS");
            gotoxy(0,0);Today();
            gotoxy(78,2);cout<<">-----------------<"<<endl;
            gotoxy(78,3);cout<<">     CAN 101     <"<<endl;
            gotoxy(78,4);cout<<">-----------------<"<<endl;
            gotoxy(5,7);cout<<"CLEAR SALES RECORD [Y/N] :> ";cin>>dec;
            if(dec=='Y')
            {
                remove("SALESRECORD.txt");
                gotoxy(78,9);cout<<"SALES RECORD CLEARED";
                cout<<endl<<"     PRESS ANY KEY TO GO BACK ";getch();
                remove("SALESRECORD.txt");
                ifstream newsr("SALESRECORD.txt");
                newsr.close();
            }
            else
            {
                gotoxy(73,9);cout<<"SALES RECORD ARE NOT CLEARED"<<endl;
                cout<<endl<<"     PRESS ANY KEY TO GO BACK ";getch();
            }
        }
};//Class Bill Ended.


//Employee Class
class employee
{
    public:
        int choice,age,tp;
        char fname[50],sname[50],email[50],id[10],phn[11];
        long int salary;
        void employeepage()
        {
            system("CLS");
            gotoxy(0,0);Today();
            gotoxy(78,2);cout<<">-----------------<"<<endl;
            gotoxy(78,3);cout<<">     CAN 101     <"<<endl;
            gotoxy(78,4);cout<<">-----------------<"<<endl;
            gotoxy(69,6);cout<<"| 1.  DISPLAY ALL EMPLOYEE DETAILS |";
            gotoxy(69,7);cout<<"| 2.  ADD NEW EMPLOYEE DETAILS     |";
            gotoxy(69,8);cout<<"| 3.  SEARCH EMPLOYEE DETAIL BY ID |";
            gotoxy(69,9);cout<<"| 4.  EDIT EMPLOYEE DETAILS        |";
            gotoxy(69,10);cout<<"| 5.  REMOVE OLD EMPLOYEE DETAILS  |";
            gotoxy(69,11);cout<<"| 6.  VIEW SALES RECORD            |";
            gotoxy(69,12);cout<<"| 7.  CLEAR SALES RECORD           |";
            gotoxy(69,13);cout<<"| 8.  STOREPAGE                    |";
            gotoxy(69,14);cout<<"| 9.  GO BACK TO LOGIN PAGE        |";
            gotoxy(69,15);cout<<"| 10. EXIT                         |";
            gotoxy(69,16);cout<<"|__________________________________|";
            gotoxy(5,18);cout<<"WHAT WOULD YOU LIKE TO DO, SIR ??"<<endl;
            gotoxy(5,19);cout<<"ENTER CHOICE :> ";cin>>choice;
            while(1)
                {
                    switch(choice)
                    {
                        case 1:
                            displayemployee();
                            employeepage();
                            break;
                        case 2:
                            addemployee();
                            employeepage();
                            break;
                        case 3:
                            searchemployee();
                            employeepage();
                            break;
                        case 4:
                            editemployee();
                            employeepage();
                            break;
                        case 5:
                            removeemployee();
                            employeepage();
                            break;
                        case 6:
                            {
                                sales s1;
                                s1.viewstat();
                            }
                            employeepage();
                            break;
                        case 7:
                            {
                                sales s2;
                                s2.clearstat();
                            }
                            employeepage();
                        case 8:
                            {
                                store s;
                                s.storepage();
                            }
                            employeepage();
                            break;
                        case 9:
                            loginjump();
                            break;
                        case 10:
                            exit(0);
                            break;
                        default:
                            cout<<endl<<"     INVALID CHOICE"<<endl;
                            cout<<"     ENTER CHOICE"<<endl;
                            cout<<"     ";cin>>choice;
                    }
                }
        }
        void displayemployee()
        {
            system("CLS");
            gotoxy(0,0);Today();
            gotoxy(78,2);cout<<">-----------------<"<<endl;
            gotoxy(78,3);cout<<">     CAN 101     <"<<endl;
            gotoxy(78,4);cout<<">-----------------<\n\n"<<endl;
            ifstream employee("EMPLOYEE.txt");
            cout<<"\t\t\t\t  ------------------------------------------------------------------------------------------------------"<<endl;
            cout<<"\t\t\t\t  ||| ID          | NAME                 | AGE | SALARY     | PHONE       | E-MAIL                   |||"<<endl;
            cout<<"\t\t\t\t  ------------------------------------------------------------------------------------------------------"<<endl;
            while (employee>>id>>sname>>fname>>age>>salary>>phn>>email)
            {
                tp=20 - strlen(sname);
                cout<<"\t\t\t\t  ||| "<<setw(11)<<std::left<<id<<" | "<<sname<<" "<<setw(tp)<<std::left<<fname<<"| "<<setw(3)<<std::left<<age<<" | "<<setw(10)<<std::left<<salary<<" | "<<setw(11)<<std::left<<phn<<" | "<<setw(25)<<std::left<<email<<"|||"<<endl ;
            }
            cout<<"\t\t\t\t  ------------------------------------------------------------------------------------------------------"<<endl;
            employee.close();
            cout<<endl<<"     PRESS ANY KEY TO GO BACK ";getch();
            cout<<endl;
        }
        void addemployee()
        {
            system("CLS");
            gotoxy(0,0);Today();
            gotoxy(78,2);cout<<">-----------------<"<<endl;
            gotoxy(78,3);cout<<">     CAN 101     <"<<endl;
            gotoxy(78,4);cout<<">-----------------<\n\n"<<endl;
            char tid[10];
            fstream tnewemployee;
            gotoxy(5,5);cout<<"ENTER DETAILS OF EMPLOYEE\n"<<endl;
            top1:
                tnewemployee.open("EMPLOYEE.txt",ios::in);
                cout<<"     ENTER ID OF EMPLOYEE"<<endl;
                cout<<"     ";cin>>tid;
                while(tnewemployee>>id>>sname>>fname>>age>>salary>>phn>>email)
                {
                    if(strcmp(tid,id)==0)
                    {
                        cout<<"\nEMPLOYEE ID IS ALREADY EXITS\n"<<endl;
                        tnewemployee.close();
                        goto top1;
                    }
                    else{
                        continue;
                    }
                }
                tnewemployee.close();
            ofstream newemployee("EMPLOYEE.txt",ios::app);
            cout<<"     ENTER SURNAME OF EMPLOYEE"<<endl;
            cout<<"     ";cin>>sname;
            cin.sync();
            cout<<"     ENTER NAME OF EMPLOYEE"<<endl;
            cout<<"     ";cin>>fname;
            cin.sync();
            cout<<"     ENTER AGE OF EMPLOYEE"<<endl;
            cout<<"     ";cin>>age;
            cin.sync();
            cout<<"     ENTER SALARY OF EMPLOYEE"<<endl;
            cout<<"     ";cin>>salary;
            cin.sync();
            cout<<"     ENTER PHONE NUMBER OF EMPLOYEE"<<endl;
            cout<<"     ";cin>>phn;
            cin.sync();
            cout<<"     ENTER E-MAIL OF EMPLOYEE"<<endl;
            cout<<"     ";cin>>email;
            cin.sync();
            newemployee<<tid<<' '<<sname<<' '<<fname<<' '<<age<<' '<<salary<<' '<<phn<<' '<<email<<endl;
            newemployee.close();
            cout<<endl<<"EMPLOYEE RECORDE ADDED"<<endl;
            cout<<endl<<"     PRESS ANY KEY TO GO BACK ";getch();
        }
        void searchemployee()
        {
            system("CLS");
            gotoxy(0,0);Today();
            gotoxy(78,2);cout<<">-----------------<"<<endl;
            gotoxy(78,3);cout<<">     CAN 101     <"<<endl;
            gotoxy(78,4);cout<<">-----------------<\n\n"<<endl;
            int c=0;
            char tid[10];
            fstream searchemp;
            searchemp.open("EMPLOYEE.txt",ios::in|ios::out);
            gotoxy(5,8);cout<<"ENTER ID OF EMPLOYEE :> ";
            cin>>tid;
            searchemp.seekg(0);
            while(searchemp>>id>>sname>>fname>>age>>salary>>phn>>email)
            {
                if(strcmp(tid,id)==0)
                {
                    gotoxy(78,10);cout<<"DESTINATION RECORD :>"<<endl;
                    gotoxy(78,12);cout<<"ID        : "<<id;
                    gotoxy(78,13);cout<<"NAME      : "<<sname<<" "<<fname;
                    gotoxy(78,14);cout<<"AGE       : "<<age;
                    gotoxy(78,15);cout<<"SALARY    : "<<salary;
                    gotoxy(78,16);cout<<"PHONE NO. : "<<phn;
                    gotoxy(78,17);cout<<"E-MAIL    : "<<email<<endl;
                    c++;
                }
            }
            if(c==0)
            {
                gotoxy(75,10);cout<<">> EMPLOYEE NOT FOUND <<"<<endl;
            }
            searchemp.close();
            cout<<"\n\n     PRESS ANY KEY TO GO BACK "<<endl;
            cout<<"     ";getch();
        }
        void editemployee()
        {
            system("CLS");
            gotoxy(0,0);Today();
            gotoxy(78,2);cout<<">-----------------<"<<endl;
            gotoxy(78,3);cout<<">     CAN 101     <"<<endl;
            gotoxy(78,4);cout<<">-----------------<\n\n"<<endl;
            char tid[50],nfname[50],nsname[50],nemail[50],nid[10],nphn[12];
            int nage,c=0;
            long int nsalary;
            fstream edit;
            edit.open("EMPLOYEE.txt",ios::in|ios::out);
            ofstream edit1("TEMP_EMPLOYEE.txt");
            cout<<"     ENTER ID OF EMPLOYEE : ";
            cin>>tid;
            edit.seekg(0);
            while(edit>>id>>sname>>fname>>age>>salary>>phn>>email)
            {
                if(strcmp(tid,id)==0)
                {
                    gotoxy(78,10);cout<<"DESTINATION RECORD :>"<<endl;
                    gotoxy(78,12);cout<<"ID        : "<<id;
                    gotoxy(78,13);cout<<"NAME      : "<<sname<<" "<<fname;
                    gotoxy(78,14);cout<<"AGE       : "<<age;
                    gotoxy(78,15);cout<<"SALARY    : "<<salary;
                    gotoxy(78,16);cout<<"PHONE NO. : "<<phn;
                    gotoxy(78,17);cout<<"E-MAIL    : "<<email<<endl;
                    gotoxy(5,19);cout<<"ENTER NEW DETAILS OF EMPLOYEE";
                    gotoxy(5,21);cout<<"ENTER ID OF EMPLOYEE           :> ";cin>>nid;
                    cin.sync();
                    gotoxy(5,22);cout<<"ENTER SURNAME OF EMPLOYEE      :> ";cin>>nsname;
                    cin.sync();
                    gotoxy(5,23);cout<<"ENTER NAME OF EMPLOYEE         :> ";cin>>nfname;
                    cin.sync();
                    gotoxy(5,24);cout<<"ENTER AGE OF EMPLOYEE          :> ";cin>>nage;
                    cin.sync();
                    gotoxy(5,25);cout<<"ENTER SALARY OF EMPLOYEE       :> ";cin>>nsalary;
                    cin.sync();
                    gotoxy(5,26);cout<<"ENTER PHONE NUMBER OF EMPLOYEE :> ";cin>>nphn;
                    cin.sync();
                    gotoxy(5,27);cout<<"ENTER E-MAIL OF EMPLOYEE       :> ";cin>>nemail;
                    cin.sync();
                    c++;
                    edit1<<nid<<' '<<nsname<<' '<<nfname<<' '<<nage<<' '<<nsalary<<' '<<nphn<<' '<<nemail<<endl;
                }
                else
                {
                    edit1<<id<<' '<<sname<<' '<<fname<<' '<<age<<' '<<salary<<' '<<phn<<' '<<email<<endl;
                }

            }
            if(c==0)
            {
                gotoxy(75,10);cout<<">> EMPLOYEE NOT FOUND <<"<<endl;
            }
            edit.close();
            edit1.close();
            remove("EMPLOYEE.txt");
            rename("TEMP_EMPLOYEE.txt","EMPLOYEE.txt");
            cout<<endl<<"     RECORDS ARE UPDATED SUCCESSFULLY "<<endl;
            cout<<endl<<"     PRESS ANY KEY TO GO BACK ";getch();
            cout<<endl;
        }
        void removeemployee()
        {
            system("CLS");
            gotoxy(0,0);Today();
            gotoxy(78,2);cout<<">-----------------<"<<endl;
            gotoxy(78,3);cout<<">     CAN 101     <"<<endl;
            gotoxy(78,4);cout<<">-----------------<\n\n"<<endl;
            char tid[50];
            int c=0;
            ifstream emp1("EMPLOYEE.txt");
            ofstream emp2("temp.txt");
            gotoxy(5,8);cout<<"ENTER ID OF EMPLOYEE YOU WISH TO REMOVE :> ";cin>>tid;
            while(emp1>>id>>sname>>fname>>age>>salary>>phn>>email)
            {
                if(strcmp(id,tid)==0)
                {
                    gotoxy(78,10);cout<<"DESTINATION RECORD :>"<<endl;
                    gotoxy(78,12);cout<<"ID        : "<<id;
                    gotoxy(78,13);cout<<"NAME      : "<<sname<<" "<<fname;
                    gotoxy(78,14);cout<<"AGE       : "<<age;
                    gotoxy(78,15);cout<<"SALARY    : "<<salary;
                    gotoxy(78,16);cout<<"PHONE NO. : "<<phn;
                    gotoxy(78,17);cout<<"E-MAIL    : "<<email<<endl;
                    c++;
                }
                else
                {
                    emp2<<id<<' '<<sname<<' '<<fname<<' '<<age<<' '<<salary<<' '<<phn<<' '<<' '<<email<<endl;
                }
            }
            emp1.close();
            emp2.close();
            if(c==0)
            {
                gotoxy(75,10);cout<<">> EMPLOYEE NOT FOUND <<"<<endl;
            }
            remove("EMPLOYEE.txt");
            rename("temp.txt","EMPLOYEE.txt");
            cout<<endl<<"     EMPLOYEE REMOVED SUCCESSFULLY"<<endl;
            cout<<endl<<"     PRESS ANY KEY TO GO BACK ";getch();
        }


};//Employee Clss Ended


//Login Class
class login
{
  public:
      string password="";
      int choice;
      char c;
      void homepage()
      {
          /*system("CLS");
          SetColor(11);
          date_time();
          SetColor(12);
          cout<<"\n\n\t\t\t\t\t\t    ***********************************************************\n";
          cout<<endl;
          SetColor(9);
          cout<<"\t\t\t\t\t             ********        **        *      *  ****     *******    ****           "<<endl;
          cout<<"\t\t\t\t\t            *               *  *       * *    *     *    *       *      *           "<<endl;
          cout<<"\t\t\t\t\t            *              *    *      *   *  *     *    *       *      *           "<<endl;
          cout<<"\t\t\t\t\t            *             ********     *    * *     *    *       *      *           "<<endl;
          cout<<"\t\t\t\t\t            *            *        *    *     **     *    *       *      *           "<<endl;
          cout<<"\t\t\t\t\t             ********   *          *   *      *   *****   *******     *****           "<<endl<<endl;
          SetColor(12);
          cout<<"\t\t\t\t\t\t    ***********************************************************\n\n\n";
          SetColor(15);
          cout<<endl;
          cout<<"   *****                       *****\n";
          SetColor(11);
          cout<<"   ~";
          SetColor(9);
          cout<<"     MADE BY ::";
          SetColor(11);
          cout<<"\t\t   ~\n";
          cout<<"   ~\t       Mahir Shekh ";
          cout<<"\t   ~\n";
          cout<<"   ~\t       Meet Thakkar";
          cout<<"\t   ~\n";
          cout<<"   ~";
          SetColor(9);
          cout<<"     ID NO. ::";
          SetColor(11);
          cout<<"\t\t   ~";
          cout<<endl;
          cout<<"   ~\t        19IT135";
          cout<<"\t\t   ~\n";
          cout<<"   ~\t        19IT146";
          cout<<"\t\t   ~\n";
          SetColor(15);
          cout<<"   *****                       *****\n\n\n";
          SetColor(14);
          cout<<"   PRESS ANY KEY TO CONTINUE "<<endl;
          getch();
          loading();*/
          system("cls");
          loginpage();
      }
      void loginpage()
      {
          system("CLS");
          gotoxy(0,0);Today();
          gotoxy(78,2);cout<<">-------------------<"<<endl;
          gotoxy(78,3);cout<<">      CAN 101      <"<<endl;
          gotoxy(78,4);cout<<">-------------------<"<<endl<<endl;
          gotoxy(78,7);cout<<"| 1. OWNER LOGIN    |"<<endl;
          gotoxy(78,8);cout<<"| 2. EMPLOYEE LOGIN |"<<endl;
          gotoxy(78,9);cout<<"| 3. CUSTMER LOGIN  |"<<endl;
          gotoxy(78,10);cout<<"| 4. EXIT           |"<<endl;
          gotoxy(78,11);cout<<"|___________________|"<<endl<<endl;
          gotoxy(5,13);cout<<"HOW WOULD YOU LIKE TO LOGIN ??"<<endl;
          gotoxy(5,14);cout<<"ENTER YOUR CHOICE :> ";cin>>choice;
          while(1)
            {
                switch(choice)
                {
                    case 1:
                        ownerlogin();
                        break;
                    case 2:
                        employeelogin();
                        break;
                    case 3:
                        customerlogin();
                        break;
                    case 4:
                        exit(0);
                        break;
                    default:
                        cout<<endl<<"     INVALID CHOICE"<<endl;
                        cout<<"     RE-ENTER CHOICE"<<endl;
                        cout<<"     ";
                        cin>>choice;
                }
            }
        }
        void ownerlogin()
        {
            while(1)
                {
                    password="";
                    cout<<endl<<"     ENTER OWNER PASSWORD"<<endl;
                    cout<<"     ";
                    c=_getch();
                    while(c!=13)
                    {
                        password.push_back(c);
                        cout<<"*";
                        c=getch();
                    }
                    if(password=="mahir")
                    {
                        cout<<endl<<"     ACCESS GRANTED"<<endl;
                        cout<<endl<<"     PRESS ANY KEY TO CONTINUE"<<endl;
                        cout<<"     ";
                        getch();
                        ownermenu();
                    }
                    else
                    {
                        cout<<endl<<"     INVALID PASSWORD"<<endl;
                    }
                }
        }
        void employeelogin()
        {
            while(1)
            {
                password="";
                cout<<"     ENTER EMPLOYEE PASSWORD"<<endl;
                cout<<"     ";
                c=_getch();
                while(c!=13)
                {
                    password.push_back(c);
                    cout<<"*";
                    c=getch();
                }
                if(password=="employee")
                {
                    cout<<endl<<"     EMPLOYEE ACCESS GRANTED"<<endl;
                    cout<<endl<<"     PRESS ANY KEY TO CONTINUE"<<endl;
                    cout<<"     ";
                    getch();
                    employeemenu();
                }
                else
                {
                    cout<<endl<<"     INVALID PASSSWORD"<<endl;
                }
            }
        }
        void customerlogin()
        {
            customermenu();
        }


        void ownermenu()
        {
            employee e;
            e.employeepage();
        }
        void employeemenu()
        {
            store emps;
            system("CLS");
            gotoxy(40,1);cout<<"CAN101";
            gotoxy(40,2);cout<<"--------"<<endl<<endl;
            cout<<"     1. VIEW INVENTORY"<<endl;
            cout<<"     2. ADD DISH"<<endl;
            cout<<"     3. SEARCH DISH"<<endl;
            cout<<"     4. UPDATE DISH"<<endl;
            cout<<"     5. DELETE DISH"<<endl;
            cout<<"     6. GO BACK TO LOGIN PAGE"<<endl;
            cout<<"     7. EXIT"<<endl<<endl;
            cout<<"     ENTER CHOICE"<<endl;
            cout<<"     ";
            cin>>choice;
            while(1)
                {
                    switch(choice)
                    {
                        case 1:
                            emps.view_inventory();
                            employeemenu();
                            break;
                        case 2:
                            emps.add_dish();
                            employeemenu();
                            break;
                        case 3:
                            emps.search_dish();
                            employeemenu();
                            break;
                        case 4:
                            emps.update_dish();
                            employeemenu();
                            break;
                        case 5:
                            emps.delete_dish();
                            employeemenu();
                            break;
                        case 6:
                            loginjump();
                            break;
                        case 7:
                            exit(0);
                        default:
                            cout<<endl<<"     INVALID CHOICE"<<endl<<endl;
                            cout<<"     ENTER CHOICE"<<endl<<endl;
                            cout<<"     ";
                            cin>>choice;
                    }
                }
        }
        void customermenu()
        {
            customer c;
            c.customerpage();
        }
};//Login Class Ended


//Global Function Definition.

void empjump()
{
    employee e;
    e.employeepage();
}
void loginjump()
{
    login l;
    l.loginpage();
}

//Main Function Ended
void SetColor(int ForgC)
{
    WORD wColor;
    //This handle is needed to get the current background attribute

    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    //csbi is used for wAttributes word

    if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
    {
        //To mask out all but the background attribute, and to add the color
        wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
        SetConsoleTextAttribute(hStdOut, wColor);
    }
    return;
}

//Function Definition.
void date_time()
{
    // variables to store date and time components
    int hours, minutes, seconds, day, month, year;

    // time_t is arithmetic time type
    time_t now;

    // Obtain current time
    // time() returns the current time of the system as a time_t value
    time(&now);

    // Convert to local time format and print to stdout
    //printf("Today is %s", ctime(&now));

    // localtime converts a time_t value to calendar time and
    // returns a pointer to a tm structure with its members
    // filled with the corresponding values
    struct tm *local = localtime(&now);

    hours = local->tm_hour;          // get hours since midnight (0-23)
    minutes = local->tm_min;         // get minutes passed after the hour (0-59)
    seconds = local->tm_sec;         // get seconds passed after minute (0-59)

    day = local->tm_mday;            // get day of month (1 to 31)
    month = local->tm_mon + 1;       // get month of year (0 to 11)
    year = local->tm_year + 1900;    // get year since 1900

    // print local time

    if (hours < 12)    // before midday
        printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t  Time is : %02d:%02d:%02d AM\n", hours, minutes, seconds);

    else    // after midday
        printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t  Time is : %02d:%02d:%02d PM\n", hours - 12, minutes, seconds);

    // print current date
    printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t  Date is : %02d/%02d/%d\n\n\n", day, month, year);
}

void Today()
{
    // time_t is arithmetic time type
    time_t now;

    // Obtain current time
    // time() returns the current time of the system as a time_t value
    time(&now);

    // Convert to local time format and print to stdout
    printf("Today is %s", ctime(&now));
}

void loading()
{
    cout<<"\n   WAIT ";
    for(int i=0; i<5; i++)
    {
        Sleep(400);
        cout<<".";
    }
    cout<<endl;
}


//Main Function
int main()
{
    login l;
    l.homepage();
    return 0;
}//Main Function Ended
