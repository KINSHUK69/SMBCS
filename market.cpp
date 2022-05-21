#include<iostream>          
#include<iomanip>           // output manipulators
#include<fstream>           // to perform file handling
#include<stdlib.h>          // to use CLS screen function
#include<vector>  
#include<sstream>
#include<algorithm>
#include<ctime>
#include<unistd.h>       //loding animation

using namespace std;
 
class User
{  
    //  User class which cannot be accessed from outside while declaring its objects
    private:
        ofstream write;              //  This data type represents the output file stream and is used to create files and to write information to files.
        ifstream read;
        string manager,cashier,customer;
        int order_no;
        float gst;
        string manager_pass,cashier_pass;
        vector<pair <string,int> > itm_q;           // itm_s for item and it's quantity
        vector<pair <int,float> > pr_t;              // price and total
        float Grand_total;
    
    protected:
        void initially()
        {
            Grand_total=0;
            gst=0;
        }
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
            else if(id==cashier && pass==cashier_pass)
            {
                return 2;
            }
            else
            {
                return 0;
            }
        }

    public :
        void items(string search)
        {
            string item,item1;
            int stock,stock1,price,price1,n,num,count=0;
            
            read.open("items.txt");
            while(read>>item)
            {
                read>>stock;
                read>>price;
    
                if(item==search)
                {   
                    count=1;
                    do
                    {
                        system("CLS");
                        cout<<"Item : "<<item<<endl;                
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
                            system("CLS");
                        }
                        else if(n==2)
                        {
                            cout<<"Enter the new price of the item : ";
                            cin>>price;
                            system("CLS");
                        }
                        else if(n==3)
                        {
                            break;
                        }
                        else
                        {
                            cout<<"wrong choice"<<endl;                            
                        }
                    }while(n!=3);
                    break;
                }  
            }
            read.close();
            read.open("items.txt");                             // to write the updated items into file      
                
            write.open("new.txt");                              // to write the updated items into file                          
            while(read>>item1)
            {
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
            write.close();
            remove("items.txt");
            rename("new.txt","items.txt");
            if(count==0)
            {
                cout<<"Item doesn't exist in the stock please fist of all add the item to the stock.."<<endl;
                cout<<"Press Any Key to continue. ";
                fflush(stdin);
                getchar();
            }
        }
        float Cashier_items(string search)
        {
            string item,item1;
            int stock,stock1,price,price1,n,num,count=0;
            float total=0;
            read.open("items.txt");
            while(read>>item)
            {
                read>>stock;
                read>>price;
                if(item==search)
                {   
                    count=1;                     
                    cout<<"Enter how many "<<item<<" you want to buy :"; 
                    cin>>stock1;
                    itm_q.push_back(make_pair(item,stock1));  //vect.push_back( make_pair(string,quantity );
                    total=stock1*price;
                    pr_t.push_back(make_pair(price,total));
                    stock-=stock1;
                    break;                  
                }
            }
            read.close();
            if(count==0)
            {
                cout<<"Sorry but this item is not in our stock"<<endl;
            }
            read.open("items.txt");                             // to write the updated items into file      
                
            write.open("new.txt");                              // to write the updated items into file                          
            while(read>>item1)
            {
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
            write.close();
            remove("items.txt");
            rename("new.txt","items.txt");
            
            return total;
        }
        void items_stocks()
        {
            system("CLS");
            string search;
            cout<<"Enter the item which you want to update : ";
            cin>>search;
            items(search);                
        }

        void add_item()
        {
            write.open("items.txt",ios::app);
            string item,item1;
            int stock,stock1,price,price1,count,n=0;
            do
            {
                count=0;
                cout<<"Enter the item which you want to add in the stock : ";
                cin>>item;
            
                read.open("items.txt");
                while(read>>item1)                                              // if the item already exist in the file
                {
                    read>>stock1;
                    read>>price1;
                    if(item1==item)
                    {
                        count=1;
                        cout<<"Item already exist in the stocks."<<endl;
                        cout<<"Please select the Right menu to update the existing item "<<endl;
                        fflush(stdin);
                        cout<<"Enter any key to continue.";
                        getchar();
                        system("CLS");
                        count=1;
                        read.close();
                        break;
                    }
                }
                if(count==0)                                        // if the item is not in the file
                {
                    cout<<"Enter the stock of "<<item<<" :";
                    cin>>stock;
                    cout<<"Enter the price of "<<item<<" :";
                    cin>>price;
                    write<<item<<" ";
                    write<<stock<<" ";
                    write<<price<<endl; 
                }
                system("CLS");
                cout<<"Press"<<endl<<"0-To add more items to the stock "<<endl;
                cout<<"1-To Exit."<<endl;
                cout<<"Enter your choice : ";
                cin>>n;
                read.close();
            }while(n!=1);
        }
        
        void Bill_generate()
        {
            system("CLS");
            float total;
            int i=1;
            cout<<"Enter 0 when you are done ."<<endl;
            cout<<"Enter the items :"<<endl; 
            string s;
            do
            {
                fflush(stdin);
                cout<<i<<" ";
                i++;
                getline(cin,s);                
                total=Cashier_items(s);
                Grand_total+=total;
            }while (s!="0");
            Bill_printing();
        }
        void load()
        {
            int i = 0; 
 	        char load[9]; 
 	        while(i < 8) 
 	        { 
 		        system("CLS"); 
 		        load[i++] = '.'; 
 		        load[i] = '\0'; 
		        printf("\n\nLOADING %-8s", load); 
 		        usleep(199900); 
 	        } 
            system("CLS"); 
            printf("\n"); 
        }
        void Bill_printing()
        {
            unsigned long long int receipt_number,order_number;
            read.open("order.txt");
            read>>receipt_number>>order_no;
            receipt_number++;
            order_no++;
            read.close();
            write.open("order.txt");
            write<<receipt_number<<endl<<order_no;
            write.close();

            gst=(.18*Grand_total);
            time_t now = time(NULL);            
            string t=ctime(&now);
            system("CLS");
            cout<<"Enter customer's name :";
            getline(cin,customer);
            system("CLS");
            load();
            
            system("CLS"); 
            cout<<setfill('*')<<setw(67)<<"*"<<endl<<endl; 
            cout<<"------------------------ GEHU SUPERMARKET -------------------------"<<endl<<endl;
            cout<<"                      CLEMENTOWN , DEHRADUN                   "<<endl;
            cout<<"                            PIN - 248007                          "<<endl<<endl;
            cout<<"                     FSSAI REG. NO. :- 60000069                   "<<endl;
            cout<<"                        TAX NO. - H09E35L6P8                "<<endl;
            cout<<"  ------------------------------------------------------------------ "<<endl;
            cout<<"  Reciept Number : "<<receipt_number<<endl;
            cout<<"  "<<t<<endl;
            cout<<"  Manager :  "<<manager<<endl;
            cout<<"  Cashier :  "<<cashier<<endl;
            cout<<"  Customer : "<<customer<<endl;
            cout<<"  Order Number : "<<order_no<<endl;
            cout<<"  ------------------------------------------------------------------ "<<endl;
            cout<<"  No Item \tQuantity\t\tRate\t\tNet Amt"<<endl;
            for(int i=0;i<itm_q.size();i++)
            {
                cout<<"  "<<i+1<<". "<<itm_q[i].first<<"\t   "<<itm_q[i].second<<"\t\tx\tRs. "<<pr_t[i].first<<"\t=\tRs. "<<pr_t[i].second<<endl; 
            }
            cout<<"  ------------------------------------------------------------------ "<<endl<<endl;
            cout<<"  Total quantity of items purachsed : "<<itm_q.size()<<endl<<endl;
            cout<<"  ------------------------------------------------------------------ "<<endl<<endl;
            cout<<"  Subtotal :                                                Rs. "<<Grand_total<<endl;
            cout<<"  GST 18%  :                                                Rs. "<<gst<<endl<<endl;
            cout<<"  ------------------------------------------------------------------ "<<endl<<endl;
            cout<<"  \e[1mTOTAL\e[1m                                                    Rs. "<<Grand_total+gst<<endl<<endl;
            cout<<"  \e[0m\e[0m------------------------------------------------------------------ "<<endl<<endl;
            cout<<"  Thank You ! "<<customer<<" for shopping with us."<<endl<<endl;
            cout<<"  ------------------------------------------------------------------ "<<endl;
            cout<<"                  HAVE A GREAT DAY   "<<customer<<endl;
            cout<<"  ------------------------------------------------------------------ "<<endl;
        
            getchar();
            system("CLS");
        }
};
// Login using inherited properties of the Parent class User
class login:public User
{  
    public:
        login()
        {
            initially();
        }
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
            system("CLS");
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
            }while(n!=3);
        }
        void manager()
        {
            int n;
            do
            {
                system("CLS");
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
                        break;
                    case 2:
                        add_item();
                        break;
                    default:
                        cout<<"Wrong choice"<<endl;                        
                }
            } while (n!=3);
        }
        void cashier()
        {
            int n;
            do
            {
                system("CLS");
                cout<<"Welcome Cashier : "<<endl<<endl;
                cout<<"Enter what you want to do : "<<endl;
                cout<<"1- To Generate the Bill."<<endl;
                cout<<"2- To Exit ."<<endl;
                cout<<"Enter your choice : ";
                cin>>n;
                switch(n)
                {
                    case 1:
                        Bill_generate();
                        break;
                    case 2:
                        break;
                    default:cout<<"You entered the wrong choice."<<endl;
                }
            } while(n!=2);
            
        }
};
int main()
{

    login a;       //Object for accessing the data members of the class User
    a.set_id_password();    
    int choice;
    int c;
    // Menu for displaying the login page
    do
    {
        system("CLS");
        cout<<setfill('*')<<setw(70)<<"*"<<endl<<endl;        
        cout<<"------------------------ GEHU SUPERMARKET ----------------------------"<<endl<<endl;
        cout<<"                            LOGIN PAGE                              "<<endl<<endl;
        cout<<"*********************      USER MENU          ***********************"<<endl<<endl;
        cout<<"1.LOGIN"<<endl;
        cout<<"2.REGISTER"<<endl;
        cout<<"2.Exit"<<endl;
        cout<<"\nEnter your choice :\n 1 for Login\n 2 for regestering into a new account \n 3 for exiting out of the program\n";
        cin>>choice;
        cout<<endl;
        switch(choice)
        {
            case 1:
                c=a.pass_check();
                if(c==1)//for manager
                {                    
                    system("CLS");
                    cout<<endl<<"\nAccess Granted"<<endl<<endl; 
                    cout<<"\n\nPress Enter Key to continue\n\n";
                    getchar();                                     
                    
                    a.manager();    // Access the signup member function of class login
                }
                else if(c==2)//for cashier
                {
                    system("CLS");
                    cout<<endl<<"\nAccess Granted"<<endl<<endl;
                    cout<<"\n\nPress Enter Key to continue\n\n";
                    getchar();
                    
                    a.cashier();
                }
                else
                {
                    system("CLS");
                    cout<<endl<<"\nAccess Denied"<<endl<<endl;
                    cout<<"\n\nPress Enter Key to continue\n\n";
                    getchar();
                             
                }
                break;
            case 2:
                {
                system("CLS");
                a.sign_up();                
                getchar();
                break;                
                }
                break;  
            case 3:
                {
                system("CLS");                
                cout<<"\n\nThanks For Using This Application\n\n\n\n"<<endl;
                getchar();
                break;                
                }
                break;           
            default:
                system("CLS");
                cout<<"You've made a mistake , give it a try again\n"<<endl; 
                main();
        }
    } while(choice!=3);
    return 0;
}