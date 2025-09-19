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
vector<string>getCategories(const vector<Product> &products){
    set<string> catset;
    for (const auto &p : products){
        if (!p.Category.empty()) catset.insert(p.Category);
    }
    return vector<string>(catset.begin(), catset.end());
}

void searchByCategory(const vector<Product> &products){
    auto categories = getCategories(products);
    if (categories.empty()){
        cout << "No categories available.\n";
        return;
    }

    cout << "Available Categories:\n";
    for (size_t i = 0; i < categories.size(); ++i){
        cout << " " << (i + 1) << ". " << categories[i] << "\n";
    }

    cout << endl << "Select a category by typing name OR entering its number: ";
    string input;
    getline(cin >> ws, input);

    int num = -1;
    try {
        num = stoi(input);
    } catch (...) {
        
    }

    string chooseCategory;
    if (num >= 1 && static_cast<size_t>(num) <= categories.size()){
        chooseCategory = categories[num - 1];
    } else {
        string wanted = input;
        transform(wanted.begin(), wanted.end(), wanted.begin(), ::tolower);

        for (const auto &category : categories){
            string c = category;
            transform(c.begin(), c.end(), c.begin(), ::tolower);
            if (c == wanted){
                chooseCategory = category;
                break;
            }
        }

        if(chooseCategory.empty()){
            cout << endl <<"Category not found.\n";
            return;
        }
    }

    bool found = false;
    cout << endl << "Products in category: " << chooseCategory << "\n";
    printTableHeader();
    for (const auto &p: products){
        string lowerCategory= p.Category;
        string choose = chooseCategory;
        transform(lowerCategory.begin(), lowerCategory.end(), lowerCategory.begin(), ::tolower);
        transform(choose.begin(), choose.end(), choose.begin(), ::tolower); 

        if (lowerCategory == choose){
            found = true;
            cout << left
                 << setw(40) << p.ProductName.substr(0,39) 
                 << setw(10) << p.SuitableAges
                 << setw(8)  << p.SuitableGender
                 << setw(12) << p.Category
                 << setw(10) << fixed << setprecision(2) << p.Price
                 << setw(15) << p.SellerName.substr(0,14)
                 << endl;
        }
    }

    if (!found){
        cout << "No products found in this category.\n";
    }
}

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
        cout << "2. Browse by Category\n";
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
        }   else if (choice == 2) {
            searchByCategory(products);
        }   else if (choice == 4) {
            cout << "Exiting system. Goodbye!\n";
        } else {
            cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 4);

    return 0;
}