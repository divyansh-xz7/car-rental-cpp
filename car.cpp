#include <iostream>
#include <fstream>
#include <string>
#include <ctime>//to get time
#include <direct.h>//to use _fullpath function
#include <algorithm>//to use transform function
#include <windows.h>//to use system("CLS")
#include <conio.h>//to use getch

//list of cars in carlist.txt (1.carno 2.busy 3.Time and Date 4.travel time 56)
//details of car in cardetail.txt (1.carno 2.seat 3.model 4.mileage 56)
//travel details in travel.txt (1.id 2.name 3.age 4.gender 5.address 6.pincode 7.phone 8.aadhar 9.location 10.loc_pin  11.distance 12.amount 13.carno 14.ttime)
//password in info.txt
//extra in extra.txt (1.id_present_or_not 2.tid 3.petrol 4.profit 5.revenue)

using namespace std;

char path1[_MAX_PATH],path2[_MAX_PATH];//character array to store path of files
double petrol,profit;//store value for petrol price and profit per km

void del_all(int n);

string show_time(int i=0)//function to return date or time
{
    int hour,min,sec,year,month,day;
    time_t now=time(0);
    tm *ltm=localtime(&now);//function localtime returns pointer of type tm
    //getting current time and date 
    hour=ltm->tm_hour;
    min=ltm->tm_min;
    sec=ltm->tm_sec;
    year=1900+ltm->tm_year;
    month=1+ltm->tm_mon;
    day=ltm->tm_mday;
    //generating a string for time and date respectively
    string T,D;
    T.append(to_string(hour));
    T.append(":");
    T.append(to_string(min));
    T.append(":");
    T.append(to_string(sec));
    T.append(".");

    D.append(to_string(day));
    D.append("/");
    D.append(to_string(month));
    D.append("/");
    D.append(to_string(year));
    D.append(".");

    if(i==0)
    return T;//the function returns time by default
    else
    return D;//if a value is passed as parameter then date is returned

}


int compare_time(string TD,long long int ttime)//to return true if ttime(variable name) minutes have passed since TD(time+date)
{
    int hr,min,sec,day,mon,yr;//data for car
    int chr,cmin,csec,cday,cmon,cyr;//for cuurent date and time
    string CTD=show_time();
    CTD.append(" ");
    CTD.append(show_time(1));

    hr=stoi(TD.substr(0,TD.find(':')));
    TD=TD.substr(TD.find(':')+1);

    min=stoi(TD.substr(0,TD.find(':')));
    TD=TD.substr(TD.find(':')+1);

    sec=stoi(TD.substr(0,TD.find('.')));
    TD=TD.substr(TD.find(' ')+1);

    day=stoi(TD.substr(0,TD.find('/')));
    TD=TD.substr(TD.find('/')+1);

    mon=stoi(TD.substr(0,TD.find('/')));
    TD=TD.substr(TD.find('/')+1);

    yr=stoi(TD.substr(0,TD.find('.')));
    TD=TD.substr(TD.find(':')+1);
///
    chr=stoi(CTD.substr(0,CTD.find(':')));
    CTD=CTD.substr(CTD.find(':')+1);

    cmin=stoi(CTD.substr(0,CTD.find(':')));
    CTD=CTD.substr(CTD.find(':')+1);

    csec=stoi(CTD.substr(0,CTD.find('.')));
    CTD=CTD.substr(CTD.find(' ')+1);

    cday=stoi(CTD.substr(0,CTD.find('/')));
    CTD=CTD.substr(CTD.find('/')+1);

    cmon=stoi(CTD.substr(0,CTD.find('/')));
    CTD=CTD.substr(CTD.find('/')+1);

    cyr=stoi(CTD.substr(0,CTD.find('.')));
    CTD=CTD.substr(CTD.find(':')+1);

    long long int tcount=0;

    if(cmin-min>=0)
    {
        tcount+=cmin-min;
    }
    else
    {
        chr--;
        min=60-min;
        if(chr==-1)
        {
            chr=23;
            cday--;
            if(cday==0)
            {
                cmon--;
                if(cmon==0)
                {
                    cmon=12;
                    cyr--;
                }
                if(cmon==1 || cmon==3 || cmon==5 || cmon==7 || cmon==8 || cmon==10 || cmon==12)
                cday=31;
                else if(cmon==4 || cmon==6 || cmon==9 || cmon==11)
                cday=30;
                if(cmon==2)
                {
                    if((cyr%4==0 && cyr%100!=0) || cyr%400==0)
                    cday=29;
                    else
                    cday=28;
                }
            }
        }
        
        tcount+=60-(min-cmin);
    }

    if(chr-hr>=0)
    {
        tcount+=(chr-hr)*60;
    }
    else
    {
        cday--;
        tcount+=(24+chr-hr)*60;
        if(cday==0)
        {
            cmon--;
            if(cmon==0)
            {
                cmon=12;
                cyr--;
            }
            if(cmon==1 || cmon==3 || cmon==5 || cmon==7 || cmon==8 || cmon==10 || cmon==12)
            cday=31+cday;
            else if(cmon==4 || cmon==6 || cmon==9 || cmon==11)
            cday=30+cday;
            if(cmon==2)
            {
                if((cyr%4==0 && cyr%100!=0) || cyr%400==0)
                cday=29+cday;
                else
                cday=28+cday;
            }
        }
    }

    if(cday-day>=0)
    {
        tcount+=(cday-day)*24*60;
    }
    else
    {
        cmon--;
        if(cmon==0)
        {
            cmon=12;
            cyr--;
        }
        if(cmon==1 || cmon==3 || cmon==5 || cmon==7 || cmon==8 || cmon==10 || cmon==12)
        cday=31+cday;
        else if(cmon==4 || cmon==6 || cmon==9 || cmon==11)
        cday=30+cday;
        if(cmon==2)
        {
            if((cyr%4==0 && cyr%100!=0) || cyr%400==0)
            cday=29+cday;
            else
            cday=28+cday;
        }

        tcount+=(cday-day)*24*60;

    }

    if(cmon-mon>=0)
    {
        int temp=mon;
        while(temp<cmon)
        {
            if(temp==1 || temp==3 || temp==5 || temp==7 || temp==8 || temp==10 || temp==12)
            tcount+=31*24*60;
            if(temp==4 || temp==6 || temp==9 || temp==11)
            tcount+=30*24*60;
            if(temp==2)
            {
                if((cyr%4==0 && cyr%100!=0) || cyr%400==0)
                tcount+=29*24*60;
                else
                tcount+=28*24*60;
            }
            temp++;
        }
    }
    else
    {
        cyr--;
        int temp=mon;
        while(temp!=cmon)
        {
            if(temp==cmon)
            break;

            if(temp==1 || temp==3 || temp==5 || temp==7 || temp==8 || temp==10 || temp==12)
            tcount+=31*24*60;
            if(temp==4 || temp==6 || temp==9 || temp==11)
            tcount+=30*24*60;
            if(temp==2)
            {
                if((cyr%4==0 && cyr%100!=0) || cyr%400==0)
                tcount+=29*24*60;
                else
                tcount+=28*24*60;
            }
            temp++;
            if(temp==13)
            temp=1;
        }
    }
    if(cyr-yr>0)
    {
        tcount+=(cyr-yr)*365*24*60;
    }

    //result

    if(tcount>=ttime)
    return 1;
    else
    return 0;
    

}


void update()//to update availability of cars according to current time and date
{
    ifstream carlist;
    ofstream newlist;
    _fullpath(path1,"car_list.txt",_MAX_PATH);//to get full path of text file
    _fullpath(path2,"new_list.txt",_MAX_PATH);
    carlist.open(path1);
    newlist.open(path2);

    string line,T,D;
    int i=0,j=0,k=0;
    float t;
    int erase;
    T=show_time();
    D=show_time(1);
    string carno,busy,TD,ttime;

    while(getline(carlist,line))//to read carlist file and create a new one with updated details
    {
        if(line!="")//to skip blank lines
        {
            j=0;
            //reading from old file
            if(i==0)
            carno=line;
            else if(i==1)
            busy=line;
            else if(i==2)
            TD=line;
            else if(i==3)
            {
                k=1;
                ttime=line;
                i=0;
            }
            i++;
            if(k==1)//writing in new file
            {
                k=0;
                i=0;
                j=2;
                if(busy=="0")
                {
                    newlist<<carno<<endl<<0<<endl<<0<<endl<<0<<endl<<endl<<endl;
                }
                else//if car is not free according to file then check and update according to current time and date
                {
                    erase=compare_time(TD,stoll(ttime));//to check if the given amount of time has passed or not

                    if(erase==0)//if update is not required then write as it is
                    {
                        newlist<<carno<<endl<<busy<<endl<<TD<<endl<<ttime<<endl<<endl<<endl;
                    }
                    else//if time is passed then make car available in list
                    {
                        newlist<<carno<<endl<<0<<endl<<0<<endl<<0<<endl<<endl<<endl;
                    }
                }
            }
        }
        else
        {
            j++;
            if(j<3)
            newlist<<endl;
        }
    }
    carlist.close();
    newlist.close();
    remove(path1);//deleting old file
    rename(path2,path1);//renaming newfile back to original name

}


string decrypt()//to decrypt the password stored in info.txt file
{
    ifstream file;
    _fullpath(path1,"info.txt",_MAX_PATH);//getting fullpath of text file
    file.open(path1);
    string pass,code;
    code.resize(500);
    getline(file,code);//getting the encrypted code from file

    unsigned char o;
    int s,a;
    s=code.length();
    //decrypting the code back to original password according to the way it was encrypted (by changing ascii code and adding dummy characters in between)
    for (int i=0;i<s;i=i+a+1)
    {
        o=code[i];
        a=o;
        while(a>9)
        a=a%10;
        if(o<53)
        {
            o-=32;
            o+=127;
            o-=21;
        }
        else
        o-=21;
        if(i<s)
        pass.append(1,o);//appending the original char to string password

    }
    file.close();
    return pass;//returning original password

}


void encrypt(string pass)//to encrypt the password and store it in file
{
    ofstream file;
    _fullpath(path1,"info.txt",_MAX_PATH);//getting path
    file.open(path1);//opening file
    int s=pass.length();
    
    int x,r,z;
    unsigned char c,o;
    //encrypting password by ascii code and adding dummy characters
    for (int i=0;i<s;i++)
    {
        c=pass[i];
        x=c+21;
        if(x>126)
        {
            r=x-127;
            x=32+r;
            
        }
        o=x;
        file<<o;//coded char
        z=o;
        while(z>9)
        z=z%10;
        //adding dummy char
        for(int j=0;j<z;j++)
        {
            x=c+(i+1)*j+11;
            while(x>126)
            {
                r=x-127;
                x=32+r;
            }
            o=x;
            file<<o;

        }


    }
    file.close();
    
}


void login()//to login or create new account
{
    ifstream extra;
    _fullpath(path1,"extra.txt",_MAX_PATH);
    extra.open(path1,ios::app);
    string temp;
    getline(extra,temp);//here temp tells if thr exists a account or program is running first time
    int t;
    int t2;
    string pass,original;
    if(temp=="1")
    {
        A:
        cout<<"\n!!Enter any natural number to login or 0 to create new id!!\n";
        fflush(stdin);
        cin>>temp;
        if(temp=="0")//if user selects to create new id
        {
            cout<<"\n!!Are you sure you want to delete all data and create a new id!!\n";
            cout<<"!!Press 0 for yes and any other number for no!!\n";
            cin>>t2;
            if(t2==0)
            {
                
                extra.close();
                del_all(1);//if user wants to create a new account then all old data is deleted

                cout<<"\n!!Create a new Password!!\n";
                cout<<"\n!!The password can contain alphabets, numerics, special characters and spaces!!\n";
                fflush(stdin);
                string pass;
                getline(cin,pass);
                encrypt(pass);
                cout<<"\n!!Password encrypted and saved successfully!!\n";
                ofstream extr;
                _fullpath(path1,"extra.txt",_MAX_PATH);
                extr.open(path1);
                extr<<1<<endl<<1<<endl;

                cout<<"\n !Enter Petrol Price!\n (This will used for calculating fare , you can update it later also)\n :";
                cin>>petrol;
                cout<<"\n !Enter Profit per km!\n (This will used for calculating fare , you can update it later also)\n :";
                cin>>profit;
                extr<<petrol<<endl<<profit<<endl;
                extr.close();
                
            }
            else
            goto A;

        }
        else//is users wants to login
        {
            B:
            cout<<"\n!!!Enter Password to Login!!!\n";
            fflush(stdin);
            getline(cin,pass);
            original=decrypt();
            if(original==pass)
            {
                cout<<"\n!!Accesss Granted!!\n";
            }
            else
            {
                cout<<"\n!!Wrong Password...Try Again!!\n";
                goto B;
            }

            update();

            ifstream extraa;
            _fullpath(path1,"extra.txt",_MAX_PATH);
            extraa.open(path1,ios::app);
            string p;
            getline(extraa,p);
            getline(extraa,p);
            getline(extraa,p);
            petrol=stod(p);
            getline(extraa,p);
            profit=stod(p);
            extraa.close();
        }

    }
    else//if no accounts exixts 
    {
        cout<<"\n! Welcome New User !\n";
        cout<<"!Create a Password for your Account!\n";
        fflush(stdin);
        string pass;
        getline(cin,pass);
        encrypt(pass);
        ofstream extraa;
        _fullpath(path1,"extra.txt",_MAX_PATH);
        extraa.open(path1);
        extraa<<1<<endl<<1<<endl;
        cout<<"\n !Enter Petrol Price!\n (This will used for calculating fare , you can update it later also)\n :";
        cin>>petrol;
        cout<<"\n !Enter your Profit per km!\n (This will used for calculating fare , you can update it later also)\n :";
        cin>>profit;
        extraa<<petrol<<endl<<profit<<endl;
        extraa.close();
        

    }
}


int carno_check(string str)//to check if entered car number is in correct format
{
    int size=str.length(),f=0;
    if(size != 10)
    return 0;
    if((str[0]>90 || str[0]<65)||(str[1]>90 || str[1]<65))
    return 0;
    if((str[2]!=' ')||(str[5]!=' '))
    return 0;
    for(int i=3;i<10;i++)
    {
        if(i==5)
        continue;
        if(str[i]<48 || str[i]>57)
        return 0;
    }
    return 1;
}


void add_car()//to add new car to list
{
    string car_no;
    int seat,check;
    string model;
    float mileage;

    A:
    cout<<"\n!!Enter Car number in format AB 00 1234!!\n";
    fflush(stdin);
    getline(cin,car_no);
    fflush(stdin);
    check=carno_check(car_no);//checking if car number is in correct format
    if(check==0)
    {
        cout<<"\n!!Invalid Car no\n";
        goto A;
    }
    //getting details of car
    cout<<"\n!!Enter number of seats!!\n";
    cin>>seat;
    cout<<"\n!!Enter model name of car!!\n";
    fflush(stdin);
    getline(cin,model);
    fflush(stdin);
    cout<<"\n!!Enter mileage of car!!\n";
    cin>>mileage;
    
    //adding cardetails to cardetail.txt file
    ofstream cardetail;
    _fullpath(path1,"car_detail.txt",_MAX_PATH);
    cardetail.open(path1,ios::app);
    cardetail<<car_no<<endl<<seat<<endl<<model<<endl<<mileage<<endl<<endl<<endl;
    cardetail.close();
    //adding car in carlist text file
    ofstream carlist;
    _fullpath(path1,"car_list.txt",_MAX_PATH);
    carlist.open(path1,ios::app);
    carlist<<car_no<<endl<<0<<endl<<0<<endl<<0<<endl<<endl<<endl;
    cout<<"Car added in list successfully\n";
    carlist.close();

}


void show_car_details(int n=0,string s=" ")//to show details of car
{
    int t,i=0,check;
    string line,carno;
    ifstream cardetail;
    _fullpath(path1,"car_detail.txt",_MAX_PATH);
    cardetail.open(path1);
    if(n==0)
    {
        cout<<"!!Press 0 to get status of all cars, 1 for particular car and press 2 to cancel the task.!!"<<endl;
        cin>>t;
    }
    else
    t=1;
    
    //using switch statement to get user choice
    switch(t)
    {
        case 0://if details of all cars is requested
            while (getline(cardetail, line)) 
            { 
                cout << line << endl; 
            }  
            break;

        case 1://if details of specific car is requested
            A:
            if(n==0)
            {
                cout<<"!!Enter number( AB 00 1234 ) of the car which u want to search!!\n";
                fflush(stdin);
                getline(cin,carno);
            }
            else
            carno=s;
            check=carno_check(carno);//to check if carnumber is in correct format
            if(check==0)
            {
                cout<<"\n!!Invalid car number!!";
                goto A;
            }
            while(getline(cardetail, line))
            {
                if (line==carno || (i>0 && i<5))
                {
                    i++;
                    if(i==1)
                    cout<<"Car Number is : "<<line<<endl;
                    if(i==2)
                    cout<<"Seats in Car : "<<line<<endl;
                    if(i==3)
                    cout<<"Car Model : "<<line<<endl;
                    if(i==4)
                    cout<<"Mileage : "<<line<<endl;

                }
                if (i==5)
                break;

            }
            
            break;

    }

}


void car_status()//to show status of cars [if they are free or not]
{
    cout<<"!!Press 0 to get status of all cars, 1 for particular car and press 2 to cancel the task.!!"<<endl;
    
    int t,i=0,check;
    cin>>t;
    string line,carno;

    ifstream carlist;
    _fullpath(path1,"car_list.txt",_MAX_PATH);
    carlist.open(path1);

    switch(t)
    {
        case 0://if data of all cars is requested
            while (carlist) 
            { 
                getline(carlist, line); 
                cout << line << endl; 
            }  
            
            cout<<"!!Here 0 means free and 1 means travelling!!\n\n";
            break;

        case 1://for specific car
            A:
            cout<<"!!Enter number( AB 00 1234 ) of the car which u want to search!!\n";
            fflush(stdin);
            getline(cin,carno);
            check=carno_check(carno);
            if(check==0)
            {
                cout<<"\n!!Invalid car number!!";
                goto A;
            }
            while(carlist)
            {
                getline(carlist, line);
                if (line==carno || i!=0)
                {
                    cout<<line<<endl;
                    i++;
                }
                if (i==4)
                break;

            }
            break;

    }
    carlist.close();
}


void del_car()//to delete a specific car from list
{
    string carno,line;
    int check,i=0;

    ifstream carlist;
    _fullpath(path1,"car_list.txt",_MAX_PATH);
    ofstream newlist;//creating a new updated list
    _fullpath(path2,"new_list.txt",_MAX_PATH);

    A:
    cout<<"\n!!Enter the number of the car which is to be deleted from list!!\n";
    fflush(stdin);
    getline(cin,carno);
    check=carno_check(carno);
    if(check==0)
    {
        cout<<"\n!!Invalid car number!!\n";
        goto A;
    }
    carlist.open(path1,ios::app);
    newlist.open(path2,ofstream::out);
    int j=0;
    while(getline(carlist,line))//loop to read from old file and write updated details on carlist newfile
    {
        if(line!="")
        {
            j=0;
            if(i!=0)
            i++;
            if(line==carno)
            {
                i++;
            }
            else if(i==0)
            {
                newlist<<line<<endl;
            }
            if(i==4)
            {
                i=0;
                j=2;
            }
        }
        else
        {
            j++;
            if(j<3)
            newlist<<endl;
        }
        
        
    }
    carlist.close();
    newlist.close();
    remove(path1);
    rename(path2,path1);

    //for car_detail list

    ifstream old;
    _fullpath(path1,"car_detail.txt",_MAX_PATH);
    ofstream newlist2;
    _fullpath(path2,"new_list.txt",_MAX_PATH);

    old.open(path1,ios::app);
    newlist2.open(path2,ios::app);
    i=0;

    while(getline(old,line))//loop to write updated details on new cardetails text file
    {
        if(line!="")
        {
            j=0;
            if(i!=0)
            i++;
            if(line==carno)
            {
                i++;
            }
            else if(i==0)
            {
                newlist2<<line<<endl;
            }
            if(i==4)
            {
                i=0;
                j=2;
            }
        }
        else
        {
            j++;
            if(j<3)
            newlist2<<endl;
        }
        
        
    }
    old.close();
    newlist2.close();

    remove(path1);
    rename(path2,path1);

}


void del_all(int n=0)//to delete all records
{
    A:
    string pass,saved;
    if(n==0)//here n=0 means it is done internally
    {
        cout<<"\n!!Enter Password to delete!!\n";
        fflush(stdin);
        getline(cin,pass);
        fflush(stdin);
        saved=decrypt();
    }
    if (saved==pass || n==1)//n=1 means user has requested data deletion
    {
        //removing all text files
        _fullpath(path1,"car_detail.txt",_MAX_PATH);
        remove(path1);
        _fullpath(path1,"car_list.txt",_MAX_PATH);
        remove(path1);
        _fullpath(path1,"travel.txt",_MAX_PATH);
        remove(path1);
        _fullpath(path1,"info.txt",_MAX_PATH);
        remove(path1);
        _fullpath(path1,"extra.txt",_MAX_PATH);
        remove(path1);
    }
    else
    {
        cout<<"\n!Wrong Password!\n";
        goto A;
    }
}


int check_personal_details(string name,string address,long int pincode,char gender,int age,long long int phone,long long int aadhar)//to check personal details are in correct format or not
{
    int check=1;

    for(int i=0;name[i]!='\0';i++)//name check
    {
        if((name[i]<65 || name[i]>90) && name[i]!=' ')
        check=0;
    }
    if(pincode<0 || pincode>999999)//pincode check
    check=0;
    if(gender!='M' && gender!='F' && gender!='T')//gender check
    check=0;
    if(age<10 || age>140)//age check
    check=0;
    if(phone>9999999999 || phone<1000000000)
    check=0;
    if(aadhar<100000000000 || aadhar>999999999999)
    check=0;

    return check;
}


int book_car(string name,string address,long int pincode,char gender ,int age,long long int phone,long long int aadhar,string location,long int loc_pincode,int distance,int amount,string car_no,long double &tim)//function to write and update details on text files
{
    ofstream travel;
    _fullpath(path1,"travel.txt",_MAX_PATH);
    travel.open(path1,ios::app);

    ifstream extra;
    _fullpath(path2,"extra.txt",_MAX_PATH);
    extra.open(path2,ios::app);

    int id;
    string q1,w,q2;

    getline(extra,q1);
    getline(extra,q2);
    id=stoi(q2);
    q2=to_string(++id);

    extra.close();
    ofstream extra2;
    extra2.open(path2);
    extra2<<q1<<endl<<q2<<endl<<petrol<<endl<<profit<<endl;
    extra2.close();

    string T,D;
    T=show_time();
    D=show_time(1);
    //writing travel details on travel.txt
    travel<<--id<<" travel id"<<endl<<name<<endl<<age<<" Age"<<endl<<gender<<endl<<address<<endl<<pincode<<endl<<phone<<" phone"<<endl<<aadhar<<" aadhar"<<endl<<location<<endl<<loc_pincode<<" location pincode"<<endl<<car_no<<endl<<distance<<" distance"<<endl<<amount<<" amount in rupees"<<endl<<T<<" "<<D<<endl<<"Expected time :"<<tim<<endl<<endl<<endl;
    travel.close();

    ifstream carlist;
    _fullpath(path1,"car_list.txt",_MAX_PATH);
    carlist.open(path1,ios::app);

    ofstream newlist;
    _fullpath(path2,"new_list.txt",_MAX_PATH);
    newlist.open(path2);

    int i=0;
    while(getline(carlist,q1))//loop to update carlist.txt
    {
        if(car_no==q1)
        {
            i++;
            newlist<<car_no<<endl;   
        }
        else if(i>0 && i<5)
        {
            if(i==2)
            newlist<<1<<endl;
            if(i==3)
            newlist<<T<<" "<<D<<endl;
            if(i==4)
            newlist<<tim<<endl;
            i++;
        }
        if(i==5)
        i=0;
        if(i==0 && car_no!=q1)
        {
            newlist<<q1<<endl;
        }
    }
    newlist.close();
    carlist.close();
    remove(path1);
    rename(path2,path1);
    
    return id;

}


string select_car(int n=0)//function to select most efficient car for travel
{
    ifstream carlist,cardetail;
    _fullpath(path1,"car_list.txt",_MAX_PATH);
    _fullpath(path2,"car_detail.txt",_MAX_PATH);
    carlist.open(path1,ios::app);
    cardetail.open(path2,ios::app);

    double mileages[200];//creating array for storing mileage values to select highest one
    int i=0,j=0,busy,m=0;//i for detail,j for array count,m for max location in array
    string line_d,line_l;
    
    while(getline(cardetail,line_d))
    {
        getline(carlist,line_l);
        if(line_d.length()!=0)
        {
            i++;
            if(i%4==0)
            {
                busy=stoi(line_l);
                if(busy==0)
                mileages[j]=stod(line_d);
                else
                mileages[j]=0;
                j++;
            }
        }
    }
    int a=0;
    double max=0.0;
    j--;
    if(n>j)
    n=j;
    int t=0;
    for (int h=0;h<n;h++)//to remove cars if next is requested
    {
        max=0;
        for (t=0;t<=j;t++)
        {
            if(mileages[t]>max)
            {
                max=mileages[t];
                a=t;
            }           
        }
        mileages[a]=0;
    }
    max=0;
    for (t=0;t<=j;t++)//to find max of mileages
    {
        if(mileages[t]>max)
        {
            max=mileages[t];
            m=t;
        }
    }
    
    int z=6*m+1;
    i=0;
    string to_return;
    
    cardetail.close();
    carlist.close();

    ifstream carlistt;
    carlistt.open(path1);

    while(getline(carlistt,line_l))//loop to get car number of selected car from text file
    {
        i++;
        if(i==z)
        {
            to_return=line_l;
            break;
        }
    }
    carlistt.close();
    return to_return;
}


int amount_calculate(int distance,string car_no,long double &tim)//to calculate fare amount
{
    float mileage;
    ifstream file;
    int i=0,amount;
    _fullpath(path1,"car_detail.txt",_MAX_PATH);
    file.open(path1);
    string line;
    while(getline(file,line))
    {
        if(line==car_no)
        i++;
        if(i==4)
        {
            mileage=stof(line);
            amount=int(distance/mileage)*petrol+distance*profit;
            file.close();
            break;
        }
        if(i>0)
        {
            i++;
            continue;
        }
    }
    file.close();
    tim=60.0*(double)distance/50.0;
    return amount;

}


void hire()//to get details of traveler and allot a car
{
    //personal details
    string name,address;
    int age;
    char gender;
    long long int phone;
    long int pincode;
    long long int aadhar;

    int check;

    //Travel details
    string location;
    long int loc_pincode;
    double distance;

    int amount;
    char pay;
    int travel_id;
    string car_no;
    long double tim;

    int n=0;//for select_car

    //getting details
    A:
    cout<<"\n!!Enter Personal Details!!\n";
    cout<<"!!Enter Your Name!!\n";
    fflush(stdin);
    getline(cin,name);
    cout<<"!!Enter Your address!!\n";
    fflush(stdin);
    getline(cin,address);
    cout<<"!!Enter pincode of your area!!\n";
    cin>>pincode;
    cout<<"!!Enter your gender!!\n";
    fflush(stdin);
    cin>>gender;
    toupper(gender);
    cout<<"!!Enter your age!!\n";
    cin>>age;
    cout<<"!!Enter your phone number!!\n";
    cin>>phone;
    cout<<"!!Enter your Aadhar Card number!!\n";
    cin>>aadhar;
    
    transform(name.begin(), name.end(), name.begin(),::toupper);//changing all letters to uppercase

    //check personal details
    check=check_personal_details(name,address,pincode,gender,age,phone,aadhar);
    if(check==0)
    {
        cout<<"\n!!The data you entered is not valid...please check again!!\n!!Make sure that \nname contains no number or special characters!!\npincode is positive and is of 6 digits!!\ninput for gender is given as M or F or T!!\nAge is more than 10 and less than 140!!\nPhone number is positive and is of 10 digits!!\nAadhar number is positive and is of 12 digits!!!\n";
        goto A;
    }

    cout<<"\n!!Enter Travel Details!!\n";
    cout<<"!!Enter the location where you want to go!!\n";
    fflush(stdin);
    getline(cin,location);
    cout<<"!!Enter pincode of location!!\n";
    cin>>loc_pincode;
    cout<<"!!Enter approximate distance!!\n";
    cin>>distance;

    cout<<"!!Press P to confirm booking and any other key to cancel booking!!\n";
    cin>>pay;

    if(pay=='P' || pay=='p')
    {
        cout<<"\n!!Booking your Car!!\n!!Booking Completed!!\n!!Happy Travelling!!\n";
        B:
        car_no=select_car(n);
        show_car_details(1,car_no);
        int a;
        cout<<"\n!!Press 0 to see next car and any other number to choose this!!\n!!Most Efficient and budget Friendly Cars are shown First!!\n";
        cin>>a;
        if(a==0)
        {
            n++;
            goto B;
        }
        amount=amount_calculate(distance,car_no, tim);
        travel_id=book_car(name,address,pincode,gender,age,phone,aadhar,location,loc_pincode,distance,amount,car_no,tim);
        cout<<"\n!!Your travelling id is "<<travel_id<<endl;
        cout<<"\n!!Car "<<car_no<<" is booked for you!!\n!!Thankyou for choosing our services!!\n";
    }

}


void search_travel()//to access travel records
{
    cout<<"\n!Search by :-";
    cout<<"\n 1. Travel Id\n 2. Name\n 3. Address\n 4. Phone\n 5. Age\n 6. Aadhar Number\n 7. Car Number\n 8. Home Pincode\n 9. Destination Pincode\n";
    int t,a=0,i=0,flag=0,j=0;
    cout<<"\nEnter Your Choice\n";
    cin>>t;
    string input,line;
    int arr[500]={0};

    switch(t)
    {
        case 1:
        a=1;
        cout<<"\nEnter Travel Id :";
        break;

        case 2:
        a=2;
        cout<<"\nEnter Traveler's Name :";
        break;

        case 3:
        a=5;
        cout<<"\nEnter Traveler's Address :";
        break;

        case 4:
        a=7;
        cout<<"\nEnter Traveler's phone number :";
        break;

        case 5:
        a=3;
        cout<<"\nEnter Traveler's Age :";
        break;

        case 6:
        a=8;
        cout<<"\nEnter Traveler's Aadhar Number :";
        break;

        case 7:
        a=11;
        cout<<"\nEnter Car Number (AB 00 1111) :";
        break;

        case 8:
        a=6;
        cout<<"\nEnter Traveler's Address Pincode :";
        break;

        case 9:
        a=10;
        cout<<"\nEnter Destination Pincode :";
        break;

        default:
        cout<<"\nInvalid Choice....Search Cancelled\n";
    }

    fflush(stdin);
    getline(cin,input);

    ifstream travel;
    _fullpath(path1,"travel.txt",_MAX_PATH);
    travel.open(path1);

    while(getline(travel,line))//reading travel.txt and selecting which record is to be shown
    {
        if(line.length()!=0)
        {
            i++;
            if(i==a)
            {
                if(a==1)
                {
                    int id=stoi(line);
                    if(input==to_string(id))
                    {
                        arr[j]=1;
                        flag=1;
                    }
                    else
                    arr[j]=-1;
                }
                if(a==2)
                {
                    transform(input.begin(), input.end(), input.begin(),::toupper);
                    if(input==line)
                    {
                        arr[j]=1;
                        flag=1;
                    }
                    else
                    arr[j]=-1;
                }
                if(a==3)
                {
                    int age=stoi(line);
                    if(input==to_string(age))
                    {
                        arr[j]=1;
                        flag=1;
                    }
                    else
                    arr[j]=-1;
                }
                if(a==5)
                {
                    transform(input.begin(), input.end(), input.begin(),::toupper);
                    transform(line.begin(), line.end(), line.begin(),::toupper);
                    if(input==line)
                    {
                        arr[j]=1;
                        flag=1;
                    }
                    else
                    arr[j]=-1;
                }
                if(a==6)
                {
                    if(input==line)
                    {
                        arr[j]=1;
                        flag=1;
                    }
                    else
                    arr[j]=-1;
                }
                if(a==7)
                {
                    long long int phone=stoll(line);
                    if(input==to_string(phone))
                    {
                        arr[j]=1;
                        flag=1;
                    }
                    else
                    arr[j]=-1;
                }
                if(a==8)
                {
                    unsigned long long int aadhar=stoull(line);
                    if(input==to_string(aadhar))
                    {
                        arr[j]=1;
                        flag=1;
                    }
                    else
                    arr[j]=-1;
                }
                if(a==10)
                {
                    long int pincode=stol(line);
                    if(input==to_string(pincode))
                    {
                        arr[j]=1;
                        flag=1;
                    }
                    else
                    arr[j]=-1;
                }
                if(a==11)
                {
                    if(input==line)
                    {
                        arr[j]=1;
                        flag=1;
                    }
                    else
                    arr[j]=-1;
                }

            }

            if(i==15)
            {
                i=0;
                j++;
            }
            
        }
    }
    travel.close();
    if(flag==1)
    {
        ifstream travel2;
        _fullpath(path1,"travel.txt",_MAX_PATH);
        travel2.open(path1);
        i=0;
        int line_no,h;
        for(int k=0;arr[k]!=0 && k<500;k++)//to show specific records from list which satisfy search condition
        {
            if(arr[k]==1)
            {
                line_no=17*k+1;//to get line number on which record is placed on text file
                cout<<endl;
                flag=0;
                h=0;
                while(getline(travel2,line))
                {
                    i++;
                    if(i==line_no)
                    flag=1;
                    if(flag==1 && h<15)
                    {
                        cout<<line<<endl;
                        h++;
                    }
                    if(h==15)
                    break;
                }
            }
        }
        travel2.close();
    }
    else
    {
        cout<<"\n!!No Record!!\n";
    }

}


void update_profit()//func to upfdate profit per km
{
    cout<<"\n!!Enter New value for Profit(per km) in rupees!!\n";
    cin>>profit;
    cout<<"\n!!Petrol Price Updated...New Price is "<<profit<<" rupees!!\n";
    ifstream extra_old;
    _fullpath(path1,"extra.txt",_MAX_PATH);
    extra_old.open(path1,ios::app);
    string s1,s2,s3;
    getline(extra_old,s1);
    getline(extra_old,s2);
    getline(extra_old,s3);
    extra_old.close();

    ofstream extra;
    extra.open(path1);
    extra<<s1<<endl<<s2<<endl<<s3<<endl<<profit<<endl;
    extra.close();
}


void change_password()//func to change password and save it after encrypting
{
    A:
    cout<<"\n!Enter old Password!\n";
    string pass,original;
    original=decrypt();
    fflush(stdin);
    getline(cin,pass);
    if(pass==original)
    {
        cout<<"\n!Enter new Password!\n";
        fflush(stdin);
        getline(cin,pass);
        encrypt(pass);
        cout<<"\n!Password encrypted and saved successfully!\n";
    }
    else
    {
        cout<<"\n!Wrong Password....Try again or create new id [Data will be Lost] !\n";
        goto A;
    }
}


void update_petrol()//func to update petrol price
{
    cout<<"\n!!Enter New Petrol Price in rupees!!\n";
    cin>>petrol;
    cout<<"\n!!Petrol Price Updated...New Price is "<<petrol<<" rupees!!\n";
    ifstream extra_old;
    _fullpath(path1,"extra.txt",_MAX_PATH);
    extra_old.open(path1,ios::app);
    string s1,s2,s4;
    getline(extra_old,s1);
    getline(extra_old,s2);
    getline(extra_old,s4);
    getline(extra_old,s4);
    extra_old.close();

    ofstream extra;
    extra.open(path1);
    extra<<s1<<endl<<s2<<endl<<petrol<<endl<<s4<<endl;
    extra.close();

}


void features()//to print features of program
{
    cout<<"\n!Features of this program!\n";
    cout<<"\n 1. You can add cars with details like Car Number, Model, Number of seats and Mileage.";
    cout<<"\n 2. Data is not lost even if you close the program.";
    cout<<"\n 3. You can check details and status of cars that if they are busy or free.";
    cout<<"\n 4. Every Travel Details are stored and you can also search it.";
    cout<<"\n 5. Password is saved after encrypting it.";
    cout<<"\n 6. You can change petrol price and Profit per km.";
    cout<<"\n 7. This program works on real time which means that if a car is busy for 1 hr then the list will be automatically updated after 1 hr.";
    cout<<"\n 8. You can change password without losing data.\n";
}


void menu()//to show a menu and then calling appropriate func as per user choice
{
    A:
    cout<<"\n !! Menu !!\n";
    //menu
    cout<<"\n 1. Book Car !\n 2. Add Car !\n 3. Car Details !\n 4. Car Status !\n 5. Remove a Car !\n 6. Search Travel Details !\n 7. Update Petrol Price !\n";
    cout<<" 8. Update Profit per km !\n 9. Change Password !\n 10. Remove All Records !\n 11. View Features !\n !!Any other number to exit!!\n";
    int t;
    cout<<"\n !Enter your choice!\n :";
    cin>>t;

    switch(t)
    {
        case 1:
            update();
            hire();
            cout<<"\n\n!!Enter any character to return to menu!!\n";
            getch();
            system("CLS");
            goto A;

        case 2:
            update();
            add_car();
            cout<<"\n\n!!Enter any character to return to menu!!\n";
            getch();
            system("CLS");
            goto A;

        case 3:
            update();
            show_car_details();
            cout<<"\n\n!!Enter any character to return to menu!!\n";
            getch();
            system("CLS");
            goto A;

        case 4:
            update();
            car_status();
            cout<<"\n\n!!Enter any character to return to menu!!\n";
            getch();
            system("CLS");
            goto A;

        case 5:
            update();
            del_car();
            cout<<"\n\n!!Enter any character to return to menu!!\n";
            getch();
            system("CLS");
            goto A;

        case 6:
            update();
            search_travel();
            cout<<"\n\n!!Enter any character to return to menu!!\n";
            getch();
            system("CLS");
            goto A;

        case 7:
            update();
            update_petrol();
            cout<<"\n\n!!Enter any character to return to menu!!\n";
            getch();
            system("CLS");
            goto A;

        case 8:
            update();
            update_profit();
            cout<<"\n\n!!Enter any character to return to menu!!\n";
            getch();
            system("CLS");
            goto A;

        case 9:
            update();
            change_password();
            cout<<"\n\n!!Enter any character to return to menu!!\n";
            getch();
            system("CLS");
            goto A;

        case 10:
            update();
            del_all();
            cout<<"\n\n!!Enter any character to return to menu!!\n";
            getch();
            system("CLS");
            goto A;

        case 11:
            update();
            features();
            cout<<"\n\n!!Enter any character to return to menu!!\n";
            getch();
            system("CLS");
            goto A;


    }
}


int main()
{
    cout<<"!!!! A Project made by Divyansh !!!!\n";
    login();
    menu();
    cout<<"\n\n!Hey User!\n!You can read Features of this Program before leaving! :)\n!Enter any char to exit!\n";
    features();
    fflush(stdin);
    getchar();
}