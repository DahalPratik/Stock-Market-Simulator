# 💹 Stock Market Simulator (C++ OOP Project)

A console-based Stock Market Simulator built using Object-Oriented Programming principles in C++. Users can simulate buying and selling stocks, track their portfolio, and observe fluctuating stock prices — all while maintaining transaction history through file handling.

---

## 🚀 Features

- Buy and sell stocks with real-time price updates.
- Simulate market fluctuations manually.
- Transaction history logging to file.
- Persistent portfolio storage across sessions.
- Clear and user-friendly menu interface.

---

## 📦 Classes Used

- **`Asset`** *(Base Class)*: Abstract representation of any tradable financial asset.
- **`Stock`** *(Derived Class)*: Defines each stock's properties and price behavior.
- **`Trader`**: Handles user actions like buying, selling, viewing portfolio, and logging transactions.

---

## ⚙️ Key Functions

- **`BuyStock()`**: Buy a stock and store in portfolio.
- **`SellStock()`**: Sell stock (if available) and calculate profit/loss.
- **`SimulateMarket()`**: Randomly adjust all stock prices.
- **`LogTransaction()`**: Log each transaction to a file with timestamp.
- **`ViewPortfolio()`**: Display current holdings with prices.
- **`LoadPortfolio()` / `SavePortfolio()`**: Read/write portfolio from/to file.

---

## 📚 Header Files Used

| Header         | Purpose |
|----------------|---------|
| `<iostream>`   | Console input/output |
| `<fstream>`    | File handling (logs and portfolio) |
| `<string>`     | String manipulation |
| `<map>`        | Store stock holdings |
| `<iomanip>`    | Output formatting |
| `<ctime>`      | Date and time for logs |
| `<cstdlib>`    | Random number generation |
| `<cmath>`      | Mathematical operations |

---

## 🛠 How to Run

1. **Compile:**
   ```bash
   g++ -o stock_simulator main.cpp
Run:

bash
Copy
Edit
./stock_simulator
📌 You can also compile and run this program in Code::Blocks, Dev C++, or any C++ IDE.

📁 Files
main.cpp – Main program source code.

portfolio.txt – Portfolio saved between sessions.

transactions.txt – Log of all buy/sell actions with date and price.

🧠 Concepts Demonstrated
Object-Oriented Programming (OOP)

Inheritance

Polymorphism

Encapsulation

File I/O

Console-based user interaction

Randomized simulation

