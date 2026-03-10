// ============================================================================
// ROLE-BASED ACCESS CONTROL (RBAC) SYSTEM
// B.Tech CSE 2025-29 | Semester II
// ============================================================================

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <ctime>

using namespace std;

// ============================================================================
// PERMISSION CLASS - Stores individual permission details
// ============================================================================
class Permission 
{
private:
    string permissionName;
    
public:
    // Default constructor
    Permission() 
    {
        permissionName = "";
    }
    
    // Parameterized constructor
    Permission(string name) 
    {
        permissionName = name;
    }
    
    // Getter
    string getName() 
    {
        return permissionName;
    }
    
    // Setter
    void setName(string name) 
    {
        permissionName = name;
    }
    
    // Display permission
    void display() 
    {
        cout << "  - " << permissionName << endl;
    }
};

// ============================================================================
// ROLE CLASS - Manages roles and their permissions
// ============================================================================
class Role 
{
private:
    string roleName;
    vector<Permission> permissions;
    
public:
    // Default constructor
    Role() 
    {
        roleName = "";
    }
    
    // Parameterized constructor
    Role(string name) 
    {
        roleName = name;
    }
    
    // Getter for role name
    string getName() 
    {
        return roleName;
    }
    
    // Add permission to role
    void addPermission(Permission perm) 
    {
        permissions.push_back(perm);
    }
    
    // Check if role has specific permission
    bool hasPermission(string permName) 
    {
        for (int i = 0; i < permissions.size(); i++) 
        {
            if (permissions[i].getName() == permName) 
            {
                return true;
            }
        }
        return false;
    }
    
    // Display role and its permissions
    void display() 
    {
        cout << "\nRole: " << roleName << endl;
        cout << "Permissions:" << endl;
        
        if (permissions.size() == 0) 
        {
            cout << "  (No permissions)" << endl;
        } 
        else 
        {
            for (int i = 0; i < permissions.size(); i++) 
            {
                permissions[i].display();
            }
        }
    }
};

// ============================================================================
// USER CLASS - Stores user information and assigned roles
// ============================================================================
class User 
{
private:
    string userID;
    string name;
    string password;
    vector<string> assignedRoles;
    
public:
    // Default constructor
    User() 
    {
        userID = "";
        name = "";
        password = "";
    }
    
    // Parameterized constructor
    User(string id, string userName, string pass) 
    {
        userID = id;
        name = userName;
        password = pass;
    }
    
    // Getters
    string getUserID() 
    {
        return userID;
    }
    
    string getName() 
    {
        return name;
    }
    
    string getPassword() 
    {
        return password;
    }
    
    // Get assigned roles
    vector<string> getRoles() 
    {
        return assignedRoles;
    }
    
    // Assign role to user
    void assignRole(string roleName) 
    {
        // Check if role already assigned
        for (int i = 0; i < assignedRoles.size(); i++) 
        {
            if (assignedRoles[i] == roleName) 
            {
                cout << "Role already assigned!" << endl;
                return;
            }
        }
        assignedRoles.push_back(roleName);
        cout << "Role assigned successfully!" << endl;
    }
    
    // Check password
    bool checkPassword(string pass) 
    {
        return (password == pass);
    }
    
    // Display user details
    void display() 
    {
        cout << "\nUser ID: " << userID << endl;
        cout << "Name: " << name << endl;
        cout << "Assigned Roles: ";
        
        if (assignedRoles.size() == 0) 
        {
            cout << "(None)";
        } 
        else 
        {
            for (int i = 0; i < assignedRoles.size(); i++) 
            {
                cout << assignedRoles[i];
                if (i < assignedRoles.size() - 1) 
                {
                    cout << ", ";
                }
            }
        }
        cout << endl;
    }
};

// ============================================================================
// LOGGER CLASS - Records all system activities
// ============================================================================
class Logger 
{
private:
    string logFile;
    
    // Get current timestamp
    string getTimestamp() 
    {
        time_t now = time(0);
        char buffer[100];
        strftime(buffer, 100, "%Y-%m-%d %H:%M:%S", localtime(&now));
        return string(buffer);
    }
    
public:
    // Constructor
    Logger() 
    {
        logFile = "access_logs.txt";
    }
    
    // Log access attempt
    void logAccess(string userID, string action, bool granted) 
    {
        ofstream file;
        file.open(logFile.c_str(), ios::app);
        
        if (file.is_open()) 
        {
            file << "[" << getTimestamp() << "] ";
            file << "User: " << userID << " | ";
            file << "Action: " << action << " | ";
            file << "Status: ";
            
            if (granted) 
            {
                file << "GRANTED";
            } 
            else 
            {
                file << "DENIED";
            }
            
            file << endl;
            file.close();
        }
    }
    
    // Log login attempt
    void logLogin(string userID, bool success) 
    {
        ofstream file;
        file.open(logFile.c_str(), ios::app);
        
        if (file.is_open()) 
        {
            file << "[" << getTimestamp() << "] ";
            file << "User: " << userID << " | ";
            file << "Login: ";
            
            if (success) 
            {
                file << "SUCCESS";
            } 
            else 
            {
                file << "FAILED";
            }
            
            file << endl;
            file.close();
        }
    }
    
    // Display all logs
    void displayLogs() 
    {
        ifstream file;
        file.open(logFile.c_str());
        
        cout << "\n========== ACCESS LOGS ==========" << endl;
        
        if (file.is_open()) 
        {
            string line;
            int count = 0;
            
            while (getline(file, line)) 
            {
                cout << line << endl;
                count++;
            }
            
            if (count == 0) 
            {
                cout << "No logs available." << endl;
            }
            
            file.close();
        } 
        else 
        {
            cout << "Cannot open log file." << endl;
        }
        
        cout << "=================================" << endl;
    }
};

// ============================================================================
// RBAC SYSTEM CLASS - Main system controller
// ============================================================================
class RBACSystem 
{
private:
    vector<User> users;
    vector<Role> roles;
    Logger logger;
    User* currentUser;
    int currentUserIndex;
    
    // Initialize default roles and permissions
    void initializeSystem() 
    {
        // Create permissions
        Permission readPerm("READ");
        Permission writePerm("WRITE");
        Permission updatePerm("UPDATE");
        Permission deletePerm("DELETE");
        Permission executePerm("EXECUTE");
        
        // Create Admin role with all permissions
        Role adminRole("Admin");
        adminRole.addPermission(readPerm);
        adminRole.addPermission(writePerm);
        adminRole.addPermission(updatePerm);
        adminRole.addPermission(deletePerm);
        adminRole.addPermission(executePerm);
        roles.push_back(adminRole);
        
        // Create Manager role
        Role managerRole("Manager");
        managerRole.addPermission(readPerm);
        managerRole.addPermission(writePerm);
        managerRole.addPermission(updatePerm);
        roles.push_back(managerRole);
        
        // Create Staff role
        Role staffRole("Staff");
        staffRole.addPermission(readPerm);
        staffRole.addPermission(writePerm);
        roles.push_back(staffRole);
        
        // Create Guest role
        Role guestRole("Guest");
        guestRole.addPermission(readPerm);
        roles.push_back(guestRole);
        
        cout << "System initialized with default roles." << endl;
    }
    
    // Find user by ID
    int findUser(string userID) 
    {
        for (int i = 0; i < users.size(); i++) 
        {
            if (users[i].getUserID() == userID) 
            {
                return i;
            }
        }
        return -1;
    }
    
    // Find role by name
    int findRole(string roleName) 
    {
        for (int i = 0; i < roles.size(); i++) 
        {
            if (roles[i].getName() == roleName) 
            {
                return i;
            }
        }
        return -1;
    }
    
    // Check if user has permission
    bool checkAccess(string permission) 
    {
        if (currentUser == NULL) 
        {
            return false;
        }
        
        vector<string> userRoles = currentUser->getRoles();
        
        // Check each role assigned to user
        for (int i = 0; i < userRoles.size(); i++) 
        {
            int roleIndex = findRole(userRoles[i]);
            
            if (roleIndex != -1) 
            {
                if (roles[roleIndex].hasPermission(permission)) 
                {
                    return true;
                }
            }
        }
        
        return false;
    }
    
public:
    // Constructor
    RBACSystem() 
    {
        currentUser = NULL;
        currentUserIndex = -1;
        initializeSystem();
    }
    
    // Add new user
    void addUser() 
    {
        string id, name, password;
        
        cout << "\n--- Add New User ---" << endl;
        cout << "Enter User ID: ";
        cin >> id;
        
        // Check if user already exists
        if (findUser(id) != -1) 
        {
            cout << "User ID already exists!" << endl;
            return;
        }
        
        cin.ignore();
        cout << "Enter Name: ";
        getline(cin, name);
        cout << "Enter Password: ";
        getline(cin, password);
        
        User newUser(id, name, password);
        users.push_back(newUser);
        
        cout << "User added successfully!" << endl;
    }
    
    // User login
    void login() 
    {
        string id, password;
        
        cout << "\n--- User Login ---" << endl;
        cout << "Enter User ID: ";
        cin >> id;
        cin.ignore();
        cout << "Enter Password: ";
        getline(cin, password);
        
        int userIndex = findUser(id);
        
        if (userIndex != -1) 
        {
            if (users[userIndex].checkPassword(password)) 
            {
                currentUser = &users[userIndex];
                currentUserIndex = userIndex;
                logger.logLogin(id, true);
                
                cout << "\nLogin successful!" << endl;
                cout << "Welcome, " << currentUser->getName() << endl;
                return;
            }
        }
        
        logger.logLogin(id, false);
        cout << "Invalid credentials!" << endl;
    }
    
    // User logout
    void logout() 
    {
        if (currentUser != NULL) 
        {
            cout << "User " << currentUser->getName() << " logged out." << endl;
            currentUser = NULL;
            currentUserIndex = -1;
        } 
        else 
        {
            cout << "No user is logged in." << endl;
        }
    }
    
    // Assign role to user
    void assignRole() 
    {
        if (users.size() == 0) 
        {
            cout << "No users in system." << endl;
            return;
        }
        
        string userID, roleName;
        
        cout << "\n--- Assign Role to User ---" << endl;
        cout << "Enter User ID: ";
        cin >> userID;
        
        int userIndex = findUser(userID);
        
        if (userIndex == -1) 
        {
            cout << "User not found!" << endl;
            return;
        }
        
        cout << "Enter Role Name: ";
        cin >> roleName;
        
        if (findRole(roleName) == -1) 
        {
            cout << "Role not found!" << endl;
            return;
        }
        
        users[userIndex].assignRole(roleName);
    }
    
    // Request access to perform action
    void requestAccess() 
    {
        if (currentUser == NULL) 
        {
            cout << "\nPlease login first!" << endl;
            return;
        }
        
        string permission;
        
        cout << "\n--- Request Access ---" << endl;
        cout << "Available permissions: READ, WRITE, UPDATE, DELETE, EXECUTE" << endl;
        cout << "Enter permission: ";
        cin >> permission;
        
        bool granted = checkAccess(permission);
        logger.logAccess(currentUser->getUserID(), permission, granted);
        
        if (granted) 
        {
            cout << "\n✓ ACCESS GRANTED" << endl;
            cout << "You can perform " << permission << " operation." << endl;
        } 
        else 
        {
            cout << "\n✗ ACCESS DENIED" << endl;
            cout << "You don't have permission for " << permission << " operation." << endl;
        }
    }
    
    // Create new role
    void createRole() 
    {
        string roleName;
        
        cout << "\n--- Create New Role ---" << endl;
        cout << "Enter Role Name: ";
        cin >> roleName;
        
        if (findRole(roleName) != -1) 
        {
            cout << "Role already exists!" << endl;
            return;
        }
        
        Role newRole(roleName);
        
        cout << "\nAdd permissions (enter 'done' to finish):" << endl;
        cout << "Options: READ, WRITE, UPDATE, DELETE, EXECUTE" << endl;
        
        while (true) 
        {
            string permName;
            cout << "Enter permission: ";
            cin >> permName;
            
            if (permName == "done" || permName == "DONE") 
            {
                break;
            }
            
            Permission perm(permName);
            newRole.addPermission(perm);
            cout << "Permission added." << endl;
        }
        
        roles.push_back(newRole);
        cout << "Role created successfully!" << endl;
    }
    
    // Display all users
    void displayAllUsers() 
    {
        cout << "\n========== ALL USERS ==========" << endl;
        
        if (users.size() == 0) 
        {
            cout << "No users in system." << endl;
        } 
        else 
        {
            for (int i = 0; i < users.size(); i++) 
            {
                users[i].display();
            }
        }
        
        cout << "===============================" << endl;
    }
    
    // Display all roles
    void displayAllRoles() 
    {
        cout << "\n========== ALL ROLES ==========" << endl;
        
        if (roles.size() == 0) 
        {
            cout << "No roles in system." << endl;
        } 
        else 
        {
            for (int i = 0; i < roles.size(); i++) 
            {
                roles[i].display();
            }
        }
        
        cout << "===============================" << endl;
    }
    
    // Display current logged-in user
    void displayCurrentUser() 
    {
        if (currentUser != NULL) 
        {
            cout << "\n--- Current User ---" << endl;
            currentUser->display();
        } 
        else 
        {
            cout << "\nNo user is logged in." << endl;
        }
    }
    
    // Display access logs
    void displayLogs() 
    {
        logger.displayLogs();
    }
    
    // Generate system report
    void generateReport() 
    {
        cout << "\n========== SYSTEM REPORT ==========" << endl;
        
        cout << "\n1. USERS AND ROLES:" << endl;
        cout << "-------------------" << endl;
        for (int i = 0; i < users.size(); i++) 
        {
            users[i].display();
        }
        
        cout << "\n2. ROLES AND PERMISSIONS:" << endl;
        cout << "-------------------------" << endl;
        for (int i = 0; i < roles.size(); i++) 
        {
            roles[i].display();
        }
        
        cout << "\n3. ACCESS HISTORY:" << endl;
        cout << "------------------" << endl;
        logger.displayLogs();
        
        cout << "===================================" << endl;
    }
    
    // Main menu
    void showMenu() 
    {
        int choice;
        
        do 
        {
            cout << "\n========================================" << endl;
            cout << "   RBAC SYSTEM - MAIN MENU" << endl;
            cout << "========================================" << endl;
            cout << "1.  Add User" << endl;
            cout << "2.  Login" << endl;
            cout << "3.  Logout" << endl;
            cout << "4.  Assign Role to User" << endl;
            cout << "5.  Create New Role" << endl;
            cout << "6.  Request Access" << endl;
            cout << "7.  Display All Users" << endl;
            cout << "8.  Display All Roles" << endl;
            cout << "9.  Display Current User" << endl;
            cout << "10. Display Access Logs" << endl;
            cout << "11. Generate Report" << endl;
            cout << "0.  Exit" << endl;
            cout << "========================================" << endl;
            cout << "Enter choice: ";
            cin >> choice;
            
            switch (choice) 
            {
                case 1:
                    addUser();
                    break;
                    
                case 2:
                    login();
                    break;
                    
                case 3:
                    logout();
                    break;
                    
                case 4:
                    assignRole();
                    break;
                    
                case 5:
                    createRole();
                    break;
                    
                case 6:
                    requestAccess();
                    break;
                    
                case 7:
                    displayAllUsers();
                    break;
                    
                case 8:
                    displayAllRoles();
                    break;
                    
                case 9:
                    displayCurrentUser();
                    break;
                    
                case 10:
                    displayLogs();
                    break;
                    
                case 11:
                    generateReport();
                    break;
                    
                case 0:
                    cout << "\nThank you for using RBAC System!" << endl;
                    break;
                    
                default:
                    cout << "Invalid choice! Try again." << endl;
            }
            
        } while (choice != 0);
    }
};

// ============================================================================
// MAIN FUNCTION
// ============================================================================
int main() 
{
    cout << "========================================" << endl;
    cout << "  ROLE-BASED ACCESS CONTROL SYSTEM" << endl;
    cout << "  B.Tech CSE 2025-29 | Semester II" << endl;
    cout << "========================================" << endl;
    cout << "\nInitializing system...\n" << endl;
    
    RBACSystem system;
    
    cout << "\nDefault Roles:" << endl;
    cout << "  - Admin: Full access" << endl;
    cout << "  - Manager: READ, WRITE, UPDATE" << endl;
    cout << "  - Staff: READ, WRITE" << endl;
    cout << "  - Guest: READ only" << endl;
    
    system.showMenu();
    
    return 0;
}
