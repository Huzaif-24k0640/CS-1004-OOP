#include <iostream>
#include <string>
using namespace std;

class Product {
protected:
    int productID;
    string productName;
    double price;
    int stockQuantity;
public:
    Product(int id, string name, double p, int stock = 0) 
        : productID(id), productName(name), price(p), stockQuantity(stock) {}

    virtual double calculateTotalPrice(int quantity) {
        return price * quantity;
    }
    
    virtual void applyDiscount(double percentage) {
        price -= price * (percentage / 100.0);
    }
    
    virtual void displayProductInfo() const {
        cout << "Product ID: " << productID << "\nName: " << productName
             << "\nPrice: $" << price << "\nStock: " << stockQuantity << endl;
    }
    
    friend ostream& operator<<(ostream& os, const Product& p) {
        p.displayProductInfo();
        return os;
    }
    
    Product operator+(const Product& other) {
        return Product(0, "Bulk Purchase", this->price + other.price);
    }
};

class Electronics : public Product {
    int warrantyPeriod;
    string brand;
public:
    Electronics(int id, string name, double p, int stock, int warranty, string br)
        : Product(id, name, p, stock), warrantyPeriod(warranty), brand(br) {}
    
    void displayProductInfo() const override {
        Product::displayProductInfo();
        cout << "Brand: " << brand << "\nWarranty: " << warrantyPeriod << " years\n";
    }
};

class Clothing : public Product {
    string size, color, fabricMaterial;
public:
    Clothing(int id, string name, double p, int stock, string s, string c, string fabric)
        : Product(id, name, p, stock), size(s), color(c), fabricMaterial(fabric) {}
    
    void applyDiscount(double percentage) override {
        if (percentage > 20) percentage = 20;
        Product::applyDiscount(percentage);
    }
};

class FoodItem : public Product {
    string expirationDate;
    int calories;
public:
    FoodItem(int id, string name, double p, int stock, string exp, int cal)
        : Product(id, name, p, stock), expirationDate(exp), calories(cal) {}
    
    double calculateTotalPrice(int quantity) override {
        return (quantity >= 5) ? price * quantity * 0.9 : price * quantity;
    }
};

class Book : public Product {
    string author, genre;
public:
    Book(int id, string name, double p, int stock, string auth, string gen)
        : Product(id, name, p, stock), author(auth), genre(gen) {}
    
    void displayProductInfo() const override {
        Product::displayProductInfo();
        cout << "Author: " << author << "\nGenre: " << genre << "\n";
    }
};

int main() {
    Electronics laptop(1, "Laptop", 1200.0, 10, 2, "Dell");
    Clothing tshirt(2, "T-Shirt", 25.0, 50, "L", "Red", "Cotton");
    FoodItem apple(3, "Apple", 2.0, 100, "2025-01-01", 52);
    Book novel(4, "Art of War", 15.0, 30, "Sun Tzu", "Military Treatise");
    
    laptop.applyDiscount(10);
    tshirt.applyDiscount(30);
    
    cout << laptop << endl;
    cout << tshirt << endl;
    cout << apple << endl;
    cout << novel << endl;
    
    cout << "Total price for 6 apples: $" << apple.calculateTotalPrice(6) << endl;
    
    Product bulkPurchase = laptop + novel;
    cout << "Bulk Purchase Price: $" << bulkPurchase.calculateTotalPrice(1) << endl;
    
    return 0;
}
