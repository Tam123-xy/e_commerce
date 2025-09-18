#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip> // for setw, left, etc.
#include <set>
using namespace std;

struct Product {
    string ID;
    string ProductName;
    string SuitableAges;
    string SuitableGender;
    string Category;
    double Price;
    string SellerName;
    string ProductDescription;
};

vector<Product> loadProducts(const string& filename) {
    vector<Product> products;
    ifstream file(filename);}
// Browse by Category

// Personalized Recommendation 

int main() {
    vector<Product> products = loadProducts("data.txt");
    if (products.empty()) {
        cout << "No products loaded. Exiting...\n";
        return 0;
    }

    int choice;
    do {
        cout << "\n=== Product Recommendation System ===\n";
        cout << "1. Browse by Keyword\n";
        //2. Browse by Category 
        //3. Personalized Recommendation 
        cout << "4. Exit\n";
        cout << "Enter choice: ";

        if (!(cin >> choice)) {
            cin.clear();
            string junk;
            getline(cin, junk);
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        getline(cin, *(new string));

        if (choice == 1) {
            string keyword;
            cout << "Enter keyword: ";
            getline(cin, keyword);
            //searchByKeyword(products, keyword);
        }   else if (choice == 4) {
            cout << "Exiting system. Goodbye!\n";
        } else {
            cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 4);

    return 0;
}