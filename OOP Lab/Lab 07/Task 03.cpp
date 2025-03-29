#include <iostream>
#include <string>
using namespace std;

class Ticket {
protected:
    int ticketID;
    string passengerName;
    double price;
    string date;
    string destination;
public:
    Ticket(int id, string name, double p, string d, string dest)
        : ticketID(id), passengerName(name), price(p), date(d), destination(dest) {}

    virtual void reserve() {
        cout << "Ticket reserved for " << passengerName << "\n";
    }
    
    virtual void cancel() {
        cout << "Ticket cancelled for " << passengerName << "\n";
    }
    
    virtual void displayTicketInfo() const {
        cout << "Ticket ID: " << ticketID << "\nPassenger: " << passengerName
             << "\nPrice: $" << price << "\nDate: " << date << "\nDestination: " << destination << endl;
    }
};

class FlightTicket : public Ticket {
    string airlineName;
    string flightNumber;
    string seatClass;
public:
    FlightTicket(int id, string name, double p, string d, string dest, string airline, string fnum, string sclass)
        : Ticket(id, name, p, d, dest), airlineName(airline), flightNumber(fnum), seatClass(sclass) {}
    
    void displayTicketInfo() const override {
        Ticket::displayTicketInfo();
        cout << "Airline: " << airlineName << "\nFlight Number: " << flightNumber << "\nSeat Class: " << seatClass << "\n";
    }
};

class TrainTicket : public Ticket {
    string trainNumber;
    string coachType;
    string departureTime;
public:
    TrainTicket(int id, string name, double p, string d, string dest, string tnum, string ctype, string dtime)
        : Ticket(id, name, p, d, dest), trainNumber(tnum), coachType(ctype), departureTime(dtime) {}
    
    void reserve() override {
        cout << "Train ticket reserved for " << passengerName << " with auto-assigned seat.\n";
    }
};

class BusTicket : public Ticket {
    string busCompany;
    int seatNumber;
public:
    BusTicket(int id, string name, double p, string d, string dest, string company, int seat)
        : Ticket(id, name, p, d, dest), busCompany(company), seatNumber(seat) {}
    
    void cancel() override {
        cout << "Bus ticket cancelled for " << passengerName << " with full refund.\n";
    }
};

class ConcertTicket : public Ticket {
    string artistName;
    string venue;
    string seatType;
public:
    ConcertTicket(int id, string name, double p, string d, string dest, string artist, string v, string stype)
        : Ticket(id, name, p, d, dest), artistName(artist), venue(v), seatType(stype) {}
    
    void displayTicketInfo() const override {
        Ticket::displayTicketInfo();
        cout << "Artist: " << artistName << "\nVenue: " << venue << "\nSeat Type: " << seatType << "\n";
    }
};

int main() {
    FlightTicket flight(1, "Huzaif", 500.0, "2025-06-10", "New York", "Delta", "DL123", "Economy");
    TrainTicket train(2, "Ali", 100.0, "2025-06-15", "Los Angeles", "T456", "Sleeper", "08:00 AM");
    BusTicket bus(3, "Kazim", 50.0, "2025-06-20", "San Francisco", "Greyhound", 12);
    ConcertTicket concert(4, "Hardeep", 75.0, "2025-07-01", "Chicago", "Coldplay", "Stadium Arena", "VIP");
    
    flight.reserve();
    train.reserve();
    bus.cancel();
    concert.displayTicketInfo();
    
    return 0;
}
