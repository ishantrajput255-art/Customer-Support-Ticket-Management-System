#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

class Customer {
public:
    int customerID;
    string name;
    string email;

    void inputCustomer() {
        cout << "Enter Customer ID: ";
        cin >> customerID;

        cout << "Enter Customer Name: ";
        cin.ignore();
        getline(cin, name);

        cout << "Enter Customer Email: ";
        getline(cin, email);
    }
};


class Ticket {
public:
    int ticketID;
    int customerID;
    string issue;
    string status;

    void createTicket() {
        cout << "Enter Ticket ID: ";
        cin >> ticketID;

        cout << "Enter Customer ID: ";
        cin >> customerID;

        cout << "Enter Issue: ";
        cin.ignore();
        getline(cin, issue);

        status = "Open";
    }

    void displayTicket() {
        cout << "\n------------------------";
        cout << "\nTicket ID: " << ticketID;
        cout << "\nCustomer ID: " << customerID;
        cout << "\nIssue: " << issue;
        cout << "\nStatus: " << status;
        cout << "\n------------------------\n";
    }
};


vector<Ticket> tickets;


void saveTickets() {
    ofstream file("tickets.txt");

    for(auto &t : tickets) {
        file << t.ticketID << endl;
        file << t.customerID << endl;
        file << t.issue << endl;
        file << t.status << endl;
    }

    file.close();
}


void loadTickets() {
    ifstream file("tickets.txt");

    Ticket t;

    while(file >> t.ticketID) {
        file >> t.customerID;
        file.ignore();

        getline(file, t.issue);
        getline(file, t.status);

        tickets.push_back(t);
    }

    file.close();
}


void addTicket() {
    Ticket t;
    t.createTicket();

    tickets.push_back(t);

    saveTickets();

    cout << "\nTicket Created Successfully!\n";
}


void viewTickets() {

    if(tickets.empty()) {
        cout << "\nNo Tickets Available\n";
        return;
    }

    for(auto &t : tickets) {
        t.displayTicket();
    }
}


void searchTicket() {

    int id;
    cout << "Enter Ticket ID: ";
    cin >> id;

    for(auto &t : tickets) {

        if(t.ticketID == id) {
            t.displayTicket();
            return;
        }
    }

    cout << "Ticket Not Found\n";
}


void updateTicket() {

    int id;
    cout << "Enter Ticket ID: ";
    cin >> id;

    for(auto &t : tickets) {

        if(t.ticketID == id) {

            cout << "Enter New Status (Open/In Progress/Resolved): ";
            cin.ignore();
            getline(cin,t.status);

            saveTickets();

            cout << "Status Updated Successfully\n";
            return;
        }
    }

    cout<<"Ticket Not Found\n";
}


void deleteTicket() {

    int id;

    cout<<"Enter Ticket ID: ";
    cin>>id;


    for(int i=0;i<tickets.size();i++) {

        if(tickets[i].ticketID==id) {

            tickets.erase(tickets.begin()+i);

            saveTickets();

            cout<<"Ticket Deleted Successfully\n";
            return;
        }
    }

    cout<<"Ticket Not Found\n";
}



bool login() {

    string username,password;

    cout<<"Username: ";
    cin>>username;

    cout<<"Password: ";
    cin>>password;


    if(username=="Ishant" && password=="122534") {

        cout<<"\nLogin Successful\n";
        return true;
    }

    cout<<"\nInvalid Login\n";
    return false;
}



int main() {

    loadTickets();


    cout<<"===== Customer Support Ticket Management System =====\n";


    if(!login()) {
        return 0;
    }


    int choice;


    do {

        cout<<"\n\n1. Create Ticket";
        cout<<"\n2. View All Tickets";
        cout<<"\n3. Search Ticket";
        cout<<"\n4. Update Ticket Status";
        cout<<"\n5. Delete Ticket";
        cout<<"\n6. Exit";

        cout<<"\nEnter Choice: ";
        cin>>choice;


        switch(choice) {

            case 1:
                addTicket();
                break;

            case 2:
                viewTickets();
                break;

            case 3:
                searchTicket();
                break;

            case 4:
                updateTicket();
                break;

            case 5:
                deleteTicket();
                break;

            case 6:
                cout<<"Thank You!";
                break;

            default:
                cout<<"Invalid Choice";
        }


    }while(choice!=6);


    return 0;
}
