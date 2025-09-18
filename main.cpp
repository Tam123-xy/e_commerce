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

vector<Product> loadProducts(const string &filename) {
    vector<Product> products;
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return products;
    }

    string line;
    bool firstLine = true;
    while (getline(file, line)) {
        if (line.empty()) continue;

        if(firstLine) { // Skip header line
            firstLine = false;
            if (line.rfind("ID,ProductName", 0) == 0) continue;
        }

        stringstream ss(line);
        Product p;
        string priceStr;

        getline(ss, p.ID, ',');
        getline(ss, p.ProductName, ',');
        getline(ss, p.SuitableAges, ',');
        getline(ss, p.SuitableGender, ',');
        getline(ss, p.Category, ',');
        getline(ss, priceStr, ',');
        getline(ss, p.SellerName, ',');
        getline(ss, p.ProductDescription, '\n');

        try {
            p.Price = stod(priceStr);
        } catch (...) {
            p.Price = 0.0;
        }

        products.push_back(p);
    }
    return products;
}

//Print Table Header
void printTableHeader() {
    cout << left
         << setw(41) << "\nProduct Name"
         << setw(10) << "Ages"
         << setw(8)  << "Gender"
         << setw(12) << "Category"
         << setw(10) << "Price"
         << setw(15) << "Seller"
         << endl;
    cout << string(100, '-') << endl;
}

// Browse by Keyword
void searchByKeyword(const vector<Product> &products, const string &keyword) {
    bool found = false;

    printTableHeader();
    for (const auto &p : products) {
        string lowerName = p.ProductName;
        string lowerDesc = p.ProductDescription;

        // Convert both to lowercase for case-insensitive search
        transform(lowerName.begin(), lowerName.end(), lowerName.begin(), ::tolower);
        transform(lowerDesc.begin(), lowerDesc.end(), lowerDesc.begin(), ::tolower);
        string lowerKey = keyword;
        transform(lowerKey.begin(), lowerKey.end(), lowerKey.begin(), ::tolower);

        if (lowerName.find(lowerKey) != string::npos || lowerDesc.find(lowerKey) != string::npos) {
            found = true;
            cout << left
                 << setw(40) << p.ProductName.substr(0,39)  // truncate long names
                 << setw(10) << p.SuitableAges
                 << setw(8)  << p.SuitableGender
                 << setw(12) << p.Category
                 << setw(10) << fixed << setprecision(2) << p.Price
                 << setw(15) << p.SellerName.substr(0,14)
                 << endl;
        }
    }

    if (!found) {
        cout << "No products found matching keyword: " << keyword << "\n";
    }
}
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
            searchByKeyword(products, keyword);
        }   else if (choice == 4) {
            cout << "Exiting system. Goodbye!\n";
        } else {
            cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 4);

    return 0;
}