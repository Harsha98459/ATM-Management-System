# 🏧 ATM Management System (Trilingual)

A high-tech ATM simulation built using **C** that runs in a web browser via **CGI**. It features a modern dark-mode interface and supports three languages.

## 🚀 Key Features
* [cite_start]**Three Languages**: Full support for **English, Kannada, and Hindi**.
* [cite_start]**Modern Web UI**: Custom CSS3 styling with a "Money Rain" animation effect.
* **Core Banking**:
    * [cite_start]Secure Login (Default PIN: `9876`).
    * [cite_start]Balance Inquiry.
    * [cite_start]Cash Withdrawal (Multiples of ₹100).
    * [cite_start]Cash Deposit.
* [cite_start]**Data Persistence**: Automatically saves your balance to `balance.txt` and logs transactions to `history.txt`.

## 🛠️ How to Run (XAMPP Setup)
1.  **Place Files**: Put `atm.c` in `C:\xampp\htdocs\atm\`.
2.  **Configure Apache**:
    * Open `httpd.conf` in XAMPP.
    * Add `.exe` to the `AddHandler cgi-script` line.
    * Change `Options` to include `ExecCGI`.
3.  **Compile**: 
    ```bash
    gcc atm.c -o atm.exe
    ```
4.  **Launch**: Open your browser and go to `http://localhost/atm/atm.exe`.

## 💻 Tech Stack
* **Language**: C
* [cite_start]**Frontend**: HTML5 / CSS3 / JavaScript (Embedded in C).
* [cite_start]**Server Interface**: CGI (Common Gateway Interface).
