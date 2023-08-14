#include<iostream>
#include<string>
#include <fstream>
using namespace std;

// To store the car Information in the system
class user{
    public:
    string cus_name;
    int days;
    int advance;
    int totalbill;
    int amountleft;
    string name;
    string model;
    string car_number;
    int rent_price;
    user(){
        cus_name="";
        days=0;
        advance=0;
        totalbill=0;
        amountleft=0;
        name="";
        model="";
        car_number="";
        rent_price=0;
    } void getuserdata(){
        cout<<"Enter the name of customer"<<endl;
        cin>>cus_name;
        cout<<endl;
        cout<<"Enter the no. of days"<<endl;
        cin>>days;
        cout<<endl;
        cout<<"Enter the amount paid in advanced"<<endl;
        cin>>advance;
        cout<<endl;
    }
    void viewuser(){
        cout<<cus_name<<"\t\t"<<name<<"\t\t"<<car_number<<"\t"<<model<<"\t"<<rent_price<<"\t\t"<<days<<"\t"<<totalbill<<"\t\t"<<advance<<"\t"<<amountleft<<endl;
    }
    int nocomp(string no){
        if(car_number==no){
            return 1;
        }
        return 0;
    }
    void copy(user *temp){
        (*temp).cus_name=cus_name;
        (*temp).days=days;
        (*temp).advance=advance;
        (*temp).totalbill=totalbill;
        (*temp).amountleft=amountleft;
        (*temp).name=name;
        (*temp).model=model;
        (*temp).car_number=car_number;
        (*temp).rent_price=rent_price;
    }
    void addusertofile();
    void userfromfile();
    int checkuser(string,user*);
    void syncuser(string);
};
void user::syncuser(string no){
      ifstream u1;
      ofstream u2;
      u1.open("userdata.dat",ios::in|ios::binary);
      u1.read((char*)this, sizeof(*this));
      u2.open("newuser.dat",ios::app|ios::binary);
      while(!u1.eof()){
        int x=nocomp(no);
        if(x==0){
          u2.write((char*)this, sizeof(*this));
        }
         u1.read((char*)this, sizeof(*this));
      }
      u1.close();
      u2.close();
      remove("userdata.dat");
      rename("newuser.dat","userdata.dat");
}
int user::checkuser(string no,user* temp){
    ifstream check;
    int flag=0;
    check.open("userdata.dat",ios::in|ios::binary);
    check.read((char*)this,sizeof(*this));
     while(!check.eof()){
        int ch=nocomp(no);
        if(ch==1){
            flag=1;
            copy(temp);
            break;
        }
        check.read((char*)this,sizeof(*this));
     }
     check.close();
     if(flag==0){
        cout<<"Type number carefully"<<endl;
        cout<<endl;
        return 0;
        }
    else return 1;
}
class Car{
   public:
    string name;
    string model;
    string car_number;
    int rent_price;
    Car(){
        name="";
        model="";
        car_number="";
        rent_price=0;
    }
    void getcardata(int *signal){
        cout<<"Enter the name of the car"<<endl;
        cin>>name;
        cout<<endl;
        cout<<"Enter car type"<<"\n"<<"{Press 1 for SUV and 0 for Sedan}"<<endl;
        int c;
        cin>>c;
        cout<<endl;
        if(c==1){
            model="SUV";
        }
        else if(c==0){
            model="Sedan";
        }
        else{
            *signal=0;
            cout<<"Wrong input try it again"<<endl;
            cout<<endl;
            return;
        }
        cout<<"Enter the car number"<<endl;
        cin>>car_number;
        cout<<endl;
        cout<<"Enter the rent price"<<endl;
        cin>>rent_price;
        cout<<endl;
    }
    void viewcar(){
        cout<<name<<"\t\t"<<model<<"\t\t"<<car_number<<"\t\t"<<rent_price<<endl;
    }
    int comapre(string n){
        //cout<<name;
        if(n==car_number){
            return 1;
        }
        else return 0;
    }
    void copy(user* t){
        (*t).name=name;
        (*t).car_number=car_number;
        (*t).model=model;
        (*t).rent_price=rent_price;
        (*t).totalbill=(rent_price)*(*t).days;
        (*t).amountleft=(*t).totalbill-(*t).advance;
    }
    int addcartofile();
    void viewcarfromfile();
    int car_check(string);
    int bookuser(string);
    void set_parentdata(string,user*);
    void syncrecord(string);
};
void Car::syncrecord(string no){
    ifstream car;
      ofstream car2;
      car.open("cardata.dat",ios::in|ios::binary);
      car.read((char*)this, sizeof(*this));
      car2.open("newfile.dat",ios::app|ios::binary);
      while(!car.eof()){
        int x=comapre(no);
        if(x==0){
          car2.write((char*)this, sizeof(*this));
        }
         car.read((char*)this, sizeof(*this));
      }
      car.close();
      car2.close();
      remove("cardata.dat");
      rename("newfile.dat","cardata.dat");
}
void Car::set_parentdata(string no,user* t){
        ifstream set;
        set.open("cardata.dat",ios::in|ios::binary);
        set.read((char*)this,sizeof(*this));
        while(!set.eof()){
            int cp=comapre(no);
            if(cp==1){
                copy(t);
                break;
            }
            set.read((char*)this,sizeof(*this));
        }
        set.close();
    }
void user::addusertofile(){
    ofstream userout;
    userout.open("userdata.dat",ios::binary|ios::app);
    userout.write((char*)this,sizeof(*this));
    userout.close();
}
void user::userfromfile(){
    ifstream uin;
    uin.open("userdata.dat",ios::in|ios::binary);
    if(!uin){
        cout<<"File not found"<<endl;
        cout<<endl;
    }
    else{
        uin.read((char*)this,sizeof(*this));
        cout<<"Customer Name"<<"\t"<<"Car Name"<<"\t"<<"Car Number"<<"\t"<<"Type"<<"\t"<<"Rent/Day"<<"\t"<<"Days"<<"\t"<<"Total bill"<<"\t"<<"Advance"<<"\t"<<"Amount left"<<endl;
        while(!uin.eof()){
            viewuser();
            uin.read((char*)this,sizeof(*this));
        }
        uin.close();
    }
}
int Car::bookuser(string no){
    ifstream book;
    int flag=0;
     book.open("cardata.dat",ios::in|ios::binary);
     book.read((char*)this,sizeof(*this));
     while(!book.eof()){
        if(this->car_number==no){
            flag=1;
            break;
        }
        book.read((char*)this,sizeof(*this));
     }
     book.close();
     if(flag==0){
        cout<<"Enter the number correctly.Choose again from main menue"<<endl;
        cout<<endl;
        return 0;
     }
     else{
      return 1;
     }
}
int Car::addcartofile(){
    if(rent_price==0 && name==""){
        cout<<"Car not added"<<endl;
        cout<<endl;
        return 0;
    }
    else{
        ofstream fout;
        fout.open("cardata.dat",ios::binary|ios::app);
        fout.write((char*)this,sizeof(*this));
        fout.close();
        return 1;
    }
}
void Car::viewcarfromfile(){
    ifstream fin;
    fin.open("cardata.dat",ios::in|ios::binary);
    if(!fin){
        cout<<"File not found"<<endl;
        cout<<endl;
    }
    else{
        fin.read((char*)this,sizeof(*this));
        cout<<"Car Name"<<"\t"<<"Model"<<"\t\t"<<"Car Number"<<"\t\t"<<"Rent/Day"<<endl;
        while(!fin.eof()){
            viewcar();
            fin.read((char*)this,sizeof(*this));
        }
        fin.close();
    }

}
int Car::car_check(string type){
      ifstream check;
      int flag=0;
     check.open("cardata.dat",ios::in|ios::binary);
     check.read((char*)this,sizeof(*this));
     cout<<endl;
     cout<<"Car Name"<<"\t"<<"Model"<<"\t\t"<<"Car Number"<<"\t\t"<<"Rent/Day"<<endl;
     while(!check.eof()){
        if(this->model==type){
            flag=1;
            viewcar();
        }
        check.read((char*)this,sizeof(*this));
     }
     check.close();
     if(flag==0){
        cout<<"No car availabe of this type"<<endl;
        cout<<endl;
        return 0;
     }
     else return 1;
}
int main(){
    int choice;
    while(true){
        Car c;
        user u;
        cout<<"Press [1] for add car"<<endl;
        cout<<"Press [2] for see which cars are available"<<endl;
        cout<<"Press [3] to Book a Car "<<endl;
        cout<<"Press [4] to see rented cars"<<endl;
        cout<<"Press [5] for returning car"<<endl;
        cout<<"Press [-1] to exit the software"<<endl;
        cin>>choice;
        if(choice==1){
            cout<<endl;
            int flag=0;
            while(true){
                int s=1;
                c.getcardata(&s);
                if(s==1){
                flag=c.addcartofile();
                }
                if(flag==0){
                    cout<<"Choose again from main menu"<<endl;
                    cout<<endl;
                    break;
                }
                else{
                char c; 
                    cout<<"Do you to add more[y/n]"<<endl;
                    cin>>c;
                    cout<<endl;
                    if(c=='y'||c=='Y'){
                        continue;
                    }
                    else if(c=='n'||c=='N') {
                        break;
                    }
                    else{
                        cout<<"Choose correct option"<<endl;
                        cout<<endl;
                        break;
                    } 
                }
            }
        }
        else if(choice==2){
          cout<<endl;
          c.viewcarfromfile();
          cout<<endl;          
        }
        else if(choice==3){
            char ch;
            int flag=0;
            cout<<endl;
            cout<<"Press [x] for SUV"<<endl;
            cout<<"Press [y] for Sedan"<<endl;
            cin>>ch;
            if(ch=='x'||ch=='X'){
                flag=c.car_check("SUV");
                if(flag==1){
                    cout<<endl;
                    string no;
                    cout<<endl;
                    cout<<"Enter the number of car from above you want to rent"<<endl;
                    cin>>no;
                    cout<<endl;
                    cout<<endl;
                    int check=c.bookuser(no);
                    if(check==1){
                        u.getuserdata();
                        c.set_parentdata(no,&u);
                        u.addusertofile();
                        c.syncrecord(no);
                        cout<<"Car rented successfully"<<endl;
                        cout<<endl;
                    }
                    else {
                        continue;
                    } 
                }
                else{
                    continue;
                }
            }
            else if(ch=='y'||ch=='Y'){
                flag=c.car_check("Sedan");
                if(flag==1){
                    string no;
                    cout<<endl;
                    cout<<"Enter the number of car from above you want to rent"<<endl;
                    cin>>no;
                    cout<<endl;
                    int check=c.bookuser(no);
                    if(check==1){
                        u.getuserdata();
                        c.set_parentdata(no,&u);
                        u.addusertofile();
                        c.syncrecord(no);
                        cout<<"Car rented successfully"<<endl;
                        cout<<endl;
                    }
                    else {
                        continue;
                    } 
                }
            }
            else{
                cout<<endl;
                cout<<"Enter correct option"<<endl;
                cout<<endl;
                continue;
            }
        }
        else if(choice==4){
            cout<<endl;
            u.userfromfile();
            cout<<endl;
        }
        else if(choice==5){
            cout<<endl;
            u.userfromfile();
            cout<<endl;
            cout<<"Choose the number of car and enter the number"<<endl;
            string no;
            cin>>no;
            cout<<endl;
            user temp;
            int ch=u.checkuser(no,&temp);
            if(ch==1){
                c.car_number=temp.car_number;
                c.name=temp.name;
                c.model=temp.model;
                c.rent_price=temp.rent_price;
                int ft=c.addcartofile();
                u.syncuser(no);
                cout<<"Car Returned Successfully"<<endl;
                cout<<endl;
            }
            else{
                continue;
            }
        }
        else if(choice==-1){
            break;
        }
        else{
            cout<<"Choose right option"<<endl;
            cout<<endl;
        }
    }
    return 0;
}