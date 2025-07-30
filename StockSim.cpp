#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <ctime>
#include <sstream>
#include <cstdlib>
#include <iomanip>

using namespace std;

tm* getLocalTime() {
    time_t now = time(nullptr);
    return localtime(&now);
}

string getCurrentDate() {
    ostringstream oss;
    oss << put_time(getLocalTime(), "%Y-%m-%d");
    return oss.str();
}

void logTransaction(const string& entry) {
    ofstream logFile("transaction_log.txt", ios::app);
    if (logFile.is_open()) {
        logFile << getCurrentDate() << " | " << entry << endl;
        logFile.close();
    }
}

// Function to view transaction log
void viewTransactionLog() {
    ifstream logFile("transaction_log.txt");
    if (!logFile.is_open()) {
        cout << "No transaction log found.\n";
        return;
    }
    string line;
    cout << "\nTransaction Log:\n";
    while (getline(logFile, line)) {
        cout << line << endl;
    }
    logFile.close();
}

// Base class
class Asset {
public:
    virtual void display() const = 0;
    virtual ~Asset() {}
};

// Stock class derived from Asset
class Stock : public Asset {
protected:
    string name;
    double price;

public:
    Stock(string n = "", double p = 0.0) : name(n), price(p) {}

    string getName() const { return name; }
    double getPrice() const { return price; }

    void fluctuatePrice() {
        double percent = (rand() % 1001 - 500) / 10000.0; // -5% to +5%
        price += price * percent;
        if (price < 1) price = 1;
    }

    void display() const override {
        cout << name << " - $" << fixed << setprecision(2) << price << endl;
    }
};

// Trader class
class Trader {
    map<string, pair<int, double>> portfolio;

public:
    void buyStock(Stock& stock, int quantity) {
        stock.fluctuatePrice();
        double totalCost = quantity * stock.getPrice();
        string name = stock.getName();

        if (portfolio.count(name)) {
            portfolio[name].first += quantity;
            portfolio[name].second = stock.getPrice();
        } else {
            portfolio[name] = {quantity, stock.getPrice()};
        }

        cout << quantity << " shares of \"" << name << "\" at $" << stock.getPrice() << " each bought successfully. ✅" << endl;
        cout << "Total cost: $" << fixed << setprecision(2) << totalCost << endl;

        logTransaction("BOUGHT: " + to_string(quantity) + " shares of \"" + name +
                       "\" at $" + to_string(stock.getPrice()) + " each. Total: $" + to_string(totalCost));
    }

    void sellStock(Stock& stock, int quantity) {
        string name = stock.getName();
        if (!portfolio.count(name) || portfolio[name].first < quantity) {
            cout << " You do not have enough shares to sell." << endl;
            return;
        }

        double buyPrice = portfolio[name].second;
        stock.fluctuatePrice();
        double sellPrice = stock.getPrice();
        double totalSell = quantity * sellPrice;
        double profitLoss = (sellPrice - buyPrice) * quantity;

        portfolio[name].first -= quantity;
        if (portfolio[name].first == 0) {
            portfolio.erase(name);
        }

        cout << quantity << " shares of \"" << name << "\" sold at $" << sellPrice << " each. " << endl;
        cout << "Total sale: $" << fixed << setprecision(2) << totalSell << endl;
        if (profitLoss >= 0) {
            cout << "Profit: $" << fixed << setprecision(2) << profitLoss << endl;
        } else {
            cout << "Loss: $" << fixed << setprecision(2) << -profitLoss << endl;
        }

        logTransaction("SOLD: " + to_string(quantity) + " shares of \"" + name +
                       "\" at $" + to_string(sellPrice) + " each. Total: $" + to_string(totalSell) +
                       ". Profit/Loss: $" + to_string(profitLoss));
    }

    void viewPortfolio() const {
        if (portfolio.empty()) {
            cout << "📭 Your portfolio is empty." << endl;
            return;
        }

        cout << "Your Portfolio:\n";
        for (const auto& entry : portfolio) {
            cout << entry.first << " - " << entry.second.first << " shares at $" << fixed << setprecision(2) << entry.second.second << " each" << endl;
        }
    }
};

// View available stocks
void viewAvailableStocks(Stock stocks[], int size) {
    cout << "\nAvailable Stocks:\n";
    for (int i = 0; i < size; ++i) {
        cout << i + 1 << ". ";
        stocks[i].display();
    }
}

int main() {
    srand(time(0));

    Trader trader;

    Stock stocks[] = {
        Stock("Apple", 150.00),
        Stock("Tesla", 280.00),
        Stock("Microsoft", 310.00),
        Stock("Google", 2700.00),
        Stock("Amazon", 3300.00)
    };

    const int stockCount = sizeof(stocks) / sizeof(stocks[0]);

    int choice;
    do {
        cout << "\n=== Stock Market Simulator ===\n";
        cout << "1. View Available Stocks\n";
        cout << "2. Buy Stock\n";
        cout << "3. Sell Stock\n";
        cout << "4. View Portfolio\n";
        cout << "5. View Transaction Log\n";
        cout << "6. Exit\n";
        cout << "Select an option: ";
        cin >> choice;

        switch (choice) {
            case 1:
                viewAvailableStocks(stocks, stockCount);
                break;

            case 2: {
                viewAvailableStocks(stocks, stockCount);
                int index, quantity;
                cout << "Enter stock number to buy: ";
                cin >> index;
                if (index < 1 || index > stockCount) {
                    cout << "Invalid stock choice.\n";
                    break;
                }
                cout << "Enter quantity: ";
                cin >> quantity;
                trader.buyStock(stocks[index - 1], quantity);
                break;
            }

            case 3: {
                viewAvailableStocks(stocks, stockCount);
                int index, quantity;
                cout << "Enter stock number to sell: ";
                cin >> index;
                if (index < 1 || index > stockCount) {
                    cout << "Invalid stock choice.\n";
                    break;
                }
                cout << "Enter quantity: ";
                cin >> quantity;
                trader.sellStock(stocks[index - 1], quantity);
                break;
            }

            case 4:
                trader.viewPortfolio();
                break;

            case 5:
                viewTransactionLog();
                break;

            case 6:
                cout << "---------------------------------\n \n";
                cout << "EXITING SIMULATOR\n THANK YOU!\n";
                break;

            default:
                cout << "Invalid option. Try again.\n";
        }
    } while (choice != 7);

    return 0;
}
