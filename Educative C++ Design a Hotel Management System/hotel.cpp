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
//////////////////////////
class Hotel {
    public:
    string name;
    Hotel(string n):name(n){};
    map<string,Room*> emptyRooms;
    map<string,Admin*> admins;
    map<string,Guest*> guests;
    void addAdmin(string id);
    void addGuest(string id);
};
class Room {
    public:
    string roomName;
    Room(string n):roomName(n) {};
};

class Standard:public Room {

};
class Deluxe:public Room {

};

class Account {
    public:
    string id;
    Hotel* hotel;
    Account(Hotel* hotel,string id):hotel(hotel),id(id) {};
};

class Guest:public Account {
    public:
    vector<Booking*> bookings;

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
};

class Admin:public Account {
    public:
    Admin(Hotel* hotel,string id):Account(hotel,id){};
    void addRoom(string n) {
        Room* temp = new Room(n);
        hotel->emptyRooms[n] = temp;
    }
};

class Booking {
    public:
    int checkinTime;
    int checkoutTime;
    vector<Room*> bookedRooms;
    Booking(int in,int out,vector<Room*> r):checkinTime(in),checkoutTime(out), bookedRooms(r) {};
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
    Booking* temp = new Booking(in,out,r);
    bookings.push_back(temp);
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

}