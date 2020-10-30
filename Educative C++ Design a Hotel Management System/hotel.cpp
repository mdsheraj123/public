/* author: Mohammad Sheraj */
/* email: mdsheraj123@gmail.com */
/* Clang++17 */
// freopen("input.txt", "r", stdin);
// freopen("output.txt", "w", stdout);
// Use long long instead of long for answer too
// ios_base::sync_with_stdio(0);
// cin.tie(0);
// cout.tie(0);
//////////////
// printf("%.2lf",double_value); // cout.precision(17);
// cout<<"Case #"<<test_case<<": "<<answer<<endl;
///////////////////////////////////////////////////////////////
// #include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <string>
#include <tuple>
#include <stack>
#include <queue> //includes priority_queue <int, vector<int>, greater<int> > pq
#include <deque>
#include <unordered_set>
#include <unordered_map>
#include <set> //sorts by value
#include <map> //sorts by key
#include <algorithm> //max/min //lower_bound/upper_bound //binary_search //reverse //next_permutation
#include <math.h> //ceil/floor
#include <climits> //INT_MIN
// #include <fstream>
// #include <numeric> //gcd //there will be sqiggly red line but no compilation error
// #include <time.h> //clock_t clock() //CLOCKS_PER_SEC
// #include <chrono> //time
// #include <thread> // std::thread
// #include <mutex> // std::mutex
using namespace std;
///////////////////////////////////////////////////////////////////////////make private later

class Room;
class Admin;
class Guest;
class Booking;
class Payment;
class Notification;
//////////////////////////
class Hotel {//all bookings here for notifications
    public:
    string name;
    Hotel(string n):name(n){};
    map<string,Room*> emptyRooms;
    map<string,Room*> bookedRooms;
    map<string,Admin*> admins;
    map<string,Guest*> guests;

    map<int,vector<Booking*>> checkinBookings;
    map<int,vector<Booking*>> checkoutBookings;

    void addAdmin(string id);
    void addGuest(string id);
    void checkAndSendNotifications();
};
class Room {
    public:
    string roomName;
    string user;
    Room(string n):roomName(n) {};
};

class Standard:public Room {

};
class Deluxe:public Room {

};

class Account {
    public:
    string userid;
    Hotel* hotel;
    Account(Hotel* hotel,string id):hotel(hotel),userid(id) {};
};

class Guest:public Account {
    public:
    Booking* booking;
    vector<Notification*> notifications;

    Guest(Hotel* hotel,string id):Account(hotel,id){};

    vector<Room*> searchEmptyRooms() {
        vector<Room*> temp;
        for(auto i:hotel->emptyRooms) {
            temp.push_back(i.second);
            cout<<i.second->roomName<<endl;
        }
        return temp;
    }

    void addBooking(int in, int out,vector<Room*> r);
    void cancelBooking();
};

class Admin:public Account {
    public:
    Admin(Hotel* hotel,string id):Account(hotel,id){};
    void addRoom(string n) {
        Room* temp = new Room(n);
        hotel->emptyRooms[n] = temp;
    }
};


class Notification {
    public:
    Notification(string m,Account* a):message(m),account(a){};
    string message;
    Account* account;
    virtual void send() = 0;
};

class SMS:public Notification {
    public:
    SMS(string m,Account* a):Notification(m,a){};
    void send() {
        cout<<"SMS sent to "<<account->userid<<endl;
    }
};

class Email:public Notification {
    public:
    Email(string m,Account* a):Notification(m,a){};
    void send() {
        cout<<"Email sent to "<<account->userid<<endl;
    }
};

class Booking {
    public:
    int checkinTime;
    int checkoutTime;
    vector<Room*> bookedRooms;
    Hotel* hotel;
    Guest* guest;
    Payment* paymentused;
    Booking(Hotel* h,Guest* guest,int in,int out,vector<Room*> r);
    ~Booking();
};


class Payment {
    public:
    bool paid;
    double amount;
    Payment(int a):paid(false),amount(a){};
    void refund() {
        amount = 0;
        paid = false;
    }
};

class Card:public Payment {
    public:
    int cardNumber;
    Card(int cn,int a):cardNumber(cn),Payment(a) {};
    void pay() {
        paid = true;
    }
};

class Cash:public Payment {
    public:
    Cash(int a):Payment(a) {};
    void pay() {
        paid = true;
    }
};



///////////////////////////////////////////////
void Hotel::addAdmin(string id) {
    Admin* temp  =new Admin(this,id);
    admins[id] = temp;
}
void Hotel::addGuest(string id) {
    Guest* temp  =new Guest(this,id);
    guests[id] = temp;
}
void Guest::addBooking(int in, int out,vector<Room*> r) {
    Booking* temp = new Booking(hotel,this,in,out,r);
    booking = temp;
}

void Guest::cancelBooking() {
    delete booking;
}
Booking::Booking(Hotel* h,Guest* guest,int in,int out,vector<Room*> r):hotel(h),guest(guest),checkinTime(in),checkoutTime(out), bookedRooms(r) {
    for(auto i:r) {
        paymentused = new Cash(r.size());
        ((Cash*)paymentused)->pay();
        i->user = guest->userid;
        h->bookedRooms[i->roomName] = i;
        h->emptyRooms.erase(i->roomName);

        hotel->checkinBookings[in].push_back(this);
        hotel->checkoutBookings[out].push_back(this);
    }
};
Booking::~Booking() {
    for(auto i:bookedRooms) {
        i->user.clear();
        hotel->emptyRooms[i->roomName] = i;
        hotel->bookedRooms.erase(i->roomName);
        int today = 0;
        if(today<checkinTime) {
            paymentused->refund();
        }
        for(int i=0;i<hotel->checkinBookings[checkinTime].size();i++) {
            if(hotel->checkinBookings[checkinTime][i]==this) {
                hotel->checkinBookings[checkinTime].erase(hotel->checkinBookings[checkinTime].begin()+i);
                break;
            }
        }
        for(int i=0;i<hotel->checkoutBookings[checkoutTime].size();i++) {
            if(hotel->checkoutBookings[checkoutTime][i]==this) {
                hotel->checkoutBookings[checkoutTime].erase(hotel->checkoutBookings[checkoutTime].begin()+i);
                break;
            }
        }
    }
}


void Hotel::checkAndSendNotifications() {
    int currentdate = 0;
    for(auto i:checkinBookings) {
        if(i.first>=currentdate) {
            for(int j=0;j<i.second.size();j++) {
                Notification* temp = new Email("Checkin time is near",(i.second[j])->guest);
                ((i.second[j])->guest)->notifications.push_back(temp);
                temp->send();
                Notification* temp2 = new SMS("Checkin time is near",(i.second[j])->guest);
                ((i.second[j])->guest)->notifications.push_back(temp2);
                temp2->send();
            }
        }
    }

    for(auto i:checkoutBookings) {
        if(i.first>=currentdate) {
            for(int j=0;j<i.second.size();j++) {
                Notification* temp = new Email("Checkin time is near",(i.second[j])->guest);
                ((i.second[j])->guest)->notifications.push_back(temp);
                temp->send();
                Notification* temp2 = new SMS("Checkin time is near",(i.second[j])->guest);
                ((i.second[j])->guest)->notifications.push_back(temp2);
                temp2->send();
            }
        }
    }
}
//////////////////////////////////////////////
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    #ifdef SHERAJ
        freopen("input.txt"  , "r", stdin);
    #endif
    // int T;
    // cin>>T;
    // for(int test_case = 1;test_case<=T;test_case++) {
    // }
    Hotel h("Grande");
    h.addAdmin("Boss");

    h.admins["Boss"]->addRoom("A1");
    h.admins["Boss"]->addRoom("B2");
    h.admins["Boss"]->addRoom("C3");

    h.addGuest("Russian");

    h.guests["Russian"]->addBooking(10,11,h.guests["Russian"]->searchEmptyRooms());
    h.guests["Russian"]->searchEmptyRooms();
    // h.guests["Russian"]->cancelBooking();
    // h.guests["Russian"]->searchEmptyRooms();
    h.checkAndSendNotifications();

}