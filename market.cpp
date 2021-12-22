#include<iostream>          // input output
#include<iomanip>           // output manipulators
#include<fstream>           // to perform file handling
#include<stdlib.h>          // to use clear screen function
#include <chrono>           // to input delay while displaying the outputs      
#include <thread>           // to input delay while displaying the outputs
using namespace std;
using namespace std::chrono; // nanoseconds, system_clock, seconds
using namespace std::this_thread; // sleep_for, sleep_until
class User
{  
    //  User class which cannot be accessed from outside while declaring its objects
    private:
        ofstream write;              //  This data type represents the output file stream and is used to create files and to write information to files.
        ifstream read;
        string manager,cashier;
        string manager_pass,cashier_pass;
    protected:
        void set_id_pass()              // the default id and password for owner manager and cashier
        {        
            read.open("password.txt");    
            read>>manager;
            read>>manager_pass;
            read>>cashier;
            read>>cashier_pass;
            read.close();
        } 
        void set_manager(string manager,string manager_pass)    // setter for setting the values for Manager
        {
            write.open("password.txt");
            this->manager=manager;
            write<<manager<<" ";
            this->manager_pass=manager_pass;
            write<<manager_pass<<endl;
            write<<this->cashier<<" ";
            write<<this->cashier_pass;
            write.close();
        }
        void set_cashier(string cashier,string cashier_pass)    // setter for setting the values for Cashier
        {
            write.open("password.txt");
            this->cashier=cashier;
            write<<this->manager<<" ";
            write<<this->manager_pass<<endl;
            write<<cashier<<" ";
            this->cashier_pass=cashier_pass;
            write<<cashier_pass;
            write.close();
        }
        // 
        void display()                                          // to display the details of Owner,Manager & Cashier
        {
            cout<<"Manager's details\n"<<manager<<"  "<<manager_pass<<endl;
            cout<<"Cashier's details\n"<<cashier<<"  "<<cashier_pass<<endl;
        }
        bool check_manager(string id,string pass)       // to be continued to check if the user already exist and if you want to overwrite the user
        {
            if(id==manager && pass==manager_pass)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        int check_pass(string id,string pass)       // to be continued to check if the user already exist and if you want to overwrite the user
        {
            if(id==manager && pass==manager_pass )
            {
                return 1;
            }
            else if (id==cashier && pass==cashier_pass)
            {
                return 2;
            }
            else
            {
                return 0;
            }
        }
        void items_stocks()
        {
                system("clear");
                string item,item1,search;
                int stock,stock1,price,price1,n,num;
                cout<<"Enter the item which you want to update : ";
                cin>>search;
                read.open("items.txt");
                while(!read.eof())
                {
                    read>>item;
                    read>>stock;
                    read>>price;
                
                    if(item==search)
                    {
                        
                        cout<<"Enter"<<endl; 
                        cout<<"1- To change the stock."<<endl;
                        cout<<"2- To change the price of item."<<endl;
                        cout<<"3- To Exit."<<endl;
                        cout<<"Enter your choice : ";
                        cin>>n;
                        if(n==1)
                        {                            
                            cout<<"Enter the number of items newly arrived : ";
                            cin>>num;
                            stock+=num;
                            system("clear");
                            break;
                        }
                        else if(n==2)
                        {
                            cout<<"Enter the new price of the item : ";
                            cin>>price;
                            system("clear");
                            break;
                        }
                        else if(n==3)
                        {
                            break;
                        }
                        else
                        {
                            cout<<"wrong choice"<<endl;                            
                        }
                    }   
                }
                read.close();

                read.open("items.txt");                             // to write the updated items into file      
                
                write.open("new.txt");                              // to write the updated items into file                          
                while(!read.eof())
                {
                    read>>item1;
                    read>>stock1;
                    read>>price1;
                    if(item1==item)
                    {
                        write<<item<<" ";
                        write<<stock<<" ";
                        write<<price<<endl;
                    }
                    else
                    {
                        write<<item1<<" ";
                        write<<stock1<<" ";
                        write<<price1<<endl;
                    }   
                }
                read.close();
                remove("items.txt");
                rename("new.txt","items.txt");


        }
};
// Login using inherited properties of the Parent class User
class login:public User
{  
    public:
        bool manager_check()
        {
            string id,pass;
            fflush(stdin);
            cout<<"Enter the Manager's id : ";
            getline(cin,id);
            fflush(stdin);
            cout<<"Enter the Manager's password : ";
            getline(cin,pass);
            return check_manager(id,pass);
        }
        int pass_check()
        {
            system("clear");
            string id,pass;
            fflush(stdin);
            cout<<"Enter the id : ";
            getline(cin,id);
            fflush(stdin);
            cout<<"Enter the password : ";
            getline(cin,pass);
            return check_pass(id,pass);
        }
        void set_id_password()  // to set the id - password & call setter from the parent class
        {
            set_id_pass();
        }
        void sign_up()        //to set the id - password for Owner ,Manager & Cashier
        {   
            int n;
            string id,pass;
            do
            {
                cout<<"Enter :"<<endl;
                cout<<"1-To Sign up as Manager."<<endl;
                cout<<"2-To Sign up as Cashier."<<endl; 
                cout<<"3-To exit."<<endl;
                cout<<"Enter your choice : ";    
                cin>>n; 
                if(n==1)
                {                  
                    cout<<"Enter the username for the Manager :";
                    fflush(stdin);
                    getline(cin,id);
                    cout<<endl<<"Enter the password for the Manager :";
                    fflush(stdin);
                    getline(cin,pass);
                    set_manager(id,pass);             
                }
                else if(n==2)        
                {
                    cout<<"Enter the username for the Cashier :";
                    fflush(stdin);
                    getline(cin,id);
                    cout<<endl<<"Enter the password for the Cashier :";
                    fflush(stdin);
                    getline(cin,pass);
                    set_cashier(id,pass);                   
                }
                else if(n>3)
                {
                    cout<<"Wrong choice! Please, choose a valid option to proceed further."<<endl;
                }
            }while(n!=4);
        }
        void manager()
        {
            int n;
            do
            {
                system("clear");
                cout<<"Welcome Manager : "<<endl<<endl;
                cout<<"Enter what you want to do : "<<endl;
                cout<<"1- To manage the stock of items or change the price of the item ."<<endl;
                cout<<"2- To add new items in the list ."<<endl;
                cout<<"3- To Exit ."<<endl;
                cout<<"Enter your choice : ";
                cin>>n;
                switch(n)
                {
                    case 1:
                        items_stocks();

                }
            } while (n!=3);
            
            
        }   
};
/*float Bill_calc()
{
    
}*/
int main()
{

    login a;       //Object for accessing the data members of the class User
    a.set_id_password();    
    int choice;
    
    // Menu for displaying the login page
    do
    {
        system("clear");
        cout<<setfill('*')<<setw(70)<<"*"<<endl;        
        cout<<"---------------------BIG BAZAAR SUPERMARKET--------------------------"<<endl<<endl;
        cout<<"                     Welcome to login page                               "<<endl<<endl;
        cout<<"*******************           MENU          *************************"<<endl<<endl;
        cout<<"1.LOGIN"<<endl;
        cout<<"2.REGISTER"<<endl;
        //cout<<"3.FORGOT PASSWORD (or) USERNAME"<<endl;
        cout<<"4.Exit"<<endl;
        cout<<"\nEnter your choice :";
        cin>>choice;
        cout<<endl;
        switch(choice)
        {
            case 1:
                if(a.pass_check()==1 )//for manager
                {                    
                    system("clear");
                    cout<<endl<<"Access Granted"<<endl<<endl;
                    sleep_for(nanoseconds(10));
                    sleep_until(system_clock::now()+seconds(2));
                    a.manager();    // Access the signup member function of class login
                }
                else
                {
                    system("clear");
                    cout<<endl<<"Access Denied"<<endl<<endl;
                    sleep_for(nanoseconds(10));
                    sleep_until(system_clock::now()+seconds(2));               
                }
                break;
            case 2:
                if(a.manager_check())
                {
                    system("clear");
                    cout<<endl<<"Access Granted"<<endl<<endl;
                    sleep_for(nanoseconds(10));
                    sleep_until(system_clock::now()+seconds(2));
                    a.sign_up();    // Access the signup member function of class login
                }
                else
                {
                    system("clear");
                    cout<<endl<<"Access Denied"<<endl<<endl;
                    sleep_for(nanoseconds(10));
                    sleep_until(system_clock::now()+seconds(2));
                }
                break;
            case 3:
                system("clear");
                //forgot();
                sleep_for(nanoseconds(10));
                sleep_until(system_clock::now()+seconds(2));
                break;
            case 4:
                system("clear");
                cout<<"Thanks for using this program.\n\n";
                sleep_for(nanoseconds(10));
                sleep_until(system_clock::now()+seconds(2));
                break;
            default:
                //system("cls");
                system("clear");
                cout<<"You've made a mistake , give it a try again\n"<<endl; 
                main();
        }
    } while (choice!=4);
    return 0;
}
