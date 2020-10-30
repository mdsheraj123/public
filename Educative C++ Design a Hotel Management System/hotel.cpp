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
/////////////////////////////////////////////////////////////////////////
class RoomBooking;
class RoomKey;
class Room;
class RoomCharge;
class RoomHouseKeeping;
////////////////////////////////
enum RoomStyle {
  STANDARD, DELUXE, FAMILY_SUITE, BUSINESS_SUITE
};

enum RoomStatus {
  AVAILABLE, RESERVED, OCCUPIED, NOT_AVAILABLE, BEING_SERVICED, OTHER
};

enum BookingStatus {
  REQUESTED, PENDING, CONFIRMED, CHECKED_IN, CHECKED_OUT, CANCELLED, ABANDONED
};

enum AccountStatus {
  ACTIVE, CLOSED, CANCELED, BLACKLISTED, BLOCKED
};

enum AccountType {
  MEMBER, GUEST, MANAGER, RECEPTIONIST
};

enum PaymentStatus {
  UNPAID, PPENDING, COMPLETED, FILLED, DECLINED, PCANCELLED, PABANDONED, SETTLING, SETTLED, REFUNDED
};

enum Date {
    FIRST,SECOND,THIRD
};

class Address {
    private:
    string streetAddress;
    string city;
    string state;
    string zipCode;
    string country;
};
/////////////////////////////////////////////////////
class Account {
    private:
    string id;
    string password;
    AccountStatus status;
    public:
    bool resetPassword();
};

class Person {
    private:
    string name;
    Address address;
    string email;
    string phone;
    Account account;
};
class Member:public Person {
    private:
    int totalRoomsCheckedIn;
    public:
    vector<RoomBooking> getBookings();
};

class Guest:public Person {
    private:
    int totalRoomsCheckedIn;
    public:
    vector<RoomBooking> getBookings();
};

class Receptionist:public Person {
    public:
    vector<Member> searchMember(string name);
    bool createBooking();
};

class Server:public Person {
    public:
    bool addRoomCharge(Room room, RoomCharge roomCharge);
};
class HouseKeeper:public Person {
    public:
    bool assignToRoom(Room room);
};
///////////////////////////////////////////////
class HotelLocation {
    private:
    string name;
    Address location;
    public:
    Address getRooms();
};

class Hotel {
    private:
    string name;
    vector<HotelLocation> locations;
    public:
    bool addLocation(HotelLocation location);
};
/////////////////////////////////////////////////
class Search {
    public:
    static vector<Room> search(RoomStyle style, Date startDate, int duration);
};

class Room:public Search {
    private:
    string roomNumber;
    RoomStyle style;
    RoomStatus status;
    double bookingPrice;
    bool isSmoking;

    vector<RoomKey> keys;
    vector<RoomHouseKeeping> houseKeepingLog;
    public:
    bool isRoomAvailable();
    bool checkIn();
    bool checkOut();

    static vector<Room> search(RoomStyle style, Date startDate, int duration) {
    // return all rooms with the given style and availability
  }
};

class RoomKey {
    private:
    string keyId;
    string barcode;
    Date issuedAt;
    bool active;
    bool isMaster;
    public:
    bool assignRoom(Room room);
    bool isActive();
};

class RoomHouseKeeping {
    private:
    string description;
    Date startDatetime;
    int duration;
    HouseKeeper houseKeeper;
    public:
    bool addHouseKeeping(Room room);
};
//////////////////////////////////////////////
class RoomBooking {
    private:
    string reservationNumber;
    Date startDate;
    int durationInDays;
    BookingStatus status;
    Date checkin;
    Date checkout;

    int guestID;
    Room room;
    Invoice invoice;
    vector<Notification> notifications;
    public:
    static RoomBooking fectchDetails(string reservationNumber);
};

class RoomCharge {
    public:
    Date issueAt;
    bool addInvoiceItem(Invoice invoice);
};

class Amenity:public RoomCharge {
    public:
    string name;
    string description;
};

class RoomService:public RoomCharge {
    public:
    bool isChargeable;
    Date requestTime;
};

class KitchenService:public RoomCharge {
    public:
    string description;
};
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


}