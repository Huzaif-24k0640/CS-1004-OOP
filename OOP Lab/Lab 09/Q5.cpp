#include <iostream>
using namespace std;

class Shipment {
    string trackingNumber;
    double weight;
public:
    Shipment (string t, double w): trackingNumber (t), weight (w) {}
    
    string getTrackingNumber () { return trackingNumber; }
    double getWeight () { return weight; }
    
    virtual void estimatedDeliveryTime () = 0;
    virtual void showDetails () = 0;
};

class AirFreight: public Shipment {
public:
    AirFreight (string t, double w): Shipment (t, w) {}
    
    void estimatedDeliveryTime () { 
        if (getWeight () > 50) { 
            cout << "Estimated delivery time: 5 days\n";  
        } else {
            cout << "Estimated delivery time: 3 days\n";
        }
    }
    void showDetails () {
        cout << "\n--- Shipment type: By Air ---\nTracking Number: " << getTrackingNumber () << "\nWeight: " << getWeight () << " kg\n";
        estimatedDeliveryTime ();
    }
};

class GroundShipment: public Shipment {
public:
    GroundShipment (string t, double w): Shipment (t, w) {}
    
    void estimatedDeliveryTime () { 
        if (getWeight () > 200) { 
            cout << "Estimated delivery time: 7 days\n";  
        } else {
            cout << "Estimated delivery time: 5 days\n";
        }
    }
    void showDetails () {
        cout << "\n--- Shipment type: By Land ---\nTracking Number: " << getTrackingNumber () << "\nWeight: " << getWeight () << " kg\n";
        estimatedDeliveryTime ();
    }
};

int main () {
    AirFreight af ("12345", 50.5);
    GroundShipment gs ("98765", 1000);
    
    af.showDetails ();
    gs.showDetails ();
    
    return 0;
}
