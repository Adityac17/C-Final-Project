# Role-Based Access Control (RBAC) System 🔐

### B.Tech CSE Semester II | ITM Skills University

**Case Study: Secure Access Management System**

---

## 📌 Project Overview

This project is a high-level simulation of a **Role-Based Access Control (RBAC)** engine. It demonstrates how modern applications (like AWS, WordPress, or Banking Portals) manage user permissions by decoupling users from specific actions and linking them through "Roles."

The system features a **two-layer security architecture**:

1. **Authentication:** Verification of User Identity via ID and Password.
2. **Authorization:** Restricting high-level system functions (Admin Controls) to specific roles like 'Admin' or 'Manager'.

---

## 🛠️ Technical Features

* **Hierarchical Menu System:** A clean UI that hides administrative tools in a restricted submenu.
* **Audit Logging:** Every login and access request (granted or denied) is recorded in `access_logs.txt` with a high-resolution timestamp.
* **Persistent Data:** Uses C++ File I/O (`fstream`) to ensure logs are saved even after the program terminates.
* **OOP Principles Applied:**
* **Encapsulation:** Private data members for security.
* **Composition:** Roles contain vectors of Permission objects.
* **Abstraction:** Complex security logic hidden behind simple user-facing menus.



---

## 📂 File Structure

* `rbac_system.cpp`: The main source code containing all classes and logic.
* `access_logs.txt`: (Auto-generated) Stores the time-stamped security audit trail.
* `README.md`: Project documentation.

---

## 🚀 Getting Started

### 1. Prerequisites

You need a C++ compiler (like G++, MinGW, or Clang) installed on your system.

### 2. Compilation

Open your terminal/command prompt and run:

```bash
g++ rbac_system.cpp -o rbac_system

```

### 3. Execution

Run the compiled executable:

```bash
./rbac_system          # Linux/macOS
rbac_system.exe        # Windows

```

---

## 🔐 System Logic & Workflow

The system follows a strict **Gatekeeper Pattern**:

1. **User Login:** The system sets a `currentUser` pointer.
2. **Access Check:** - User requests an action (e.g., "DELETE").
* System loops: `User` ➔ `Roles` ➔ `Permissions`.
* Result is displayed and logged to `access_logs.txt`.


3. **Admin Controls:** - A specific helper function `isAdminOrManager()` checks if the user has elevated privileges before displaying the Management Submenu.

---

## 📊 Access Control Matrix (Default)

| Role | READ | WRITE | UPDATE | DELETE | EXECUTE | Admin Menu |
| --- | --- | --- | --- | --- | --- | --- |
| **Admin** | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ |
| **Manager** | ✅ | ✅ | ✅ | ❌ | ❌ | ✅ |
| **Staff** | ✅ | ✅ | ❌ | ❌ | ❌ | ❌ |
| **Guest** | ✅ | ❌ | ❌ | ❌ | ❌ | ❌ |

---

## 📈 Future Enhancements

* [ ] **Password Hashing:** Integrate MD5 or SHA-256 for secure password storage.
* [ ] **Database Integration:** Connect to MySQL/SQLite instead of text files.
* [ ] **GUI Layer:** Build a visual dashboard using Qt or WinForms.
* [ ] **Multi-Factor Authentication (MFA):** Add a second layer of verification.

---

## 👤 Author

* **Aditya Sunil Chouksey**
* **Roll Number: 150096725070** 
* ** B.Tech CSE (2025-2029)**
* ** ITM Skills University**

---

*This project was developed as a part of the Semester II C++ Curriculum.*
