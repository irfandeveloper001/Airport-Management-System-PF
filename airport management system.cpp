#include <iostream>
#include <string>
#include <conio>
#include <fstream>
using namespace std;

using namespace std;

struct Flight 
{
    string flightID;
    string airlineName;
    string source;
    string destination;
    string departureTime;
    string arrivalTime;
    int totalSeats;
    int availableSeats;
};

struct Ticket
 {
    string ticketID;
    string passengerName;
    string flightID;
    string seatNumber;
    double price;
};

struct AirportStaff 
{
    string username;
    string password;
};



bool adminLogin() 
{
    string correctUsername = "admin";  // Hardcoded admin username
    string correctPassword = "password123";  // Hardcoded admin password

    string enteredUsername, enteredPassword;
    cout << "Enter Admin Username: ";
    cin >> enteredUsername;
    cout << "Enter Admin Password: ";
    cin >> enteredPassword;

    if (enteredUsername == correctUsername && enteredPassword == correctPassword) 
    {
        cout << "Login successful!" << endl;
        return true;
    } 
    else 
    {
        cout << "Invalid username or password!" << endl;
        return false;
    }
}




bool validateFlightID(const string& flightID) 
{
	
    int length = 0;
    
    for (int i = 0; flightID[i] != '\0'; i++) 
	{
        length++;
    }
    
    if (length < 3 || length > 6) 
	{
        cout << "Invalid Flight ID! It should be between 3 and 6 characters long." << endl;
        return false;
    }
    
    for (int i = 0; i < length; i++) 
	{
        char ch = flightID[i];
        
        if (!(ch >= 'A' && ch <= 'Z') && !(ch >= 'a' && ch <= 'z') && !(ch >= '0' && ch <= '9')) 
		{
            cout << "Invalid Flight ID! It should only contain alphanumeric characters." << endl;
            return false;
        }
    }
    
    return true;
}


void addFlight() 
{
    Flight newFlight;
    
    cout << "Enter Flight ID: ";
    cin >> newFlight.flightID;
    
    while (!validateFlightID(newFlight.flightID)) 
	{
        cout << "Enter a valid Flight ID: ";
        cin >> newFlight.flightID;
    }
    
    cout << "Enter Airline Name: ";
    cin >> newFlight.airlineName;
    
    cout << "Enter Source: ";
    cin >> newFlight.source;
    
    cout << "Enter Destination: ";
    cin >> newFlight.destination;
    
    cout << "Enter Departure Time: ";
    cin >> newFlight.departureTime;
    
    cout << "Enter Arrival Time: ";
    cin >> newFlight.arrivalTime;
    
    cout << "Enter Total Seats: ";
    cin >> newFlight.totalSeats;
    
    newFlight.availableSeats = newFlight.totalSeats;
    
    ofstream outFile("flights.txt", ios::app);
    
    if (outFile.is_open()) 
	{
        outFile << newFlight.flightID << "\n"
                << newFlight.airlineName << "\n"
                << newFlight.source << "\n"
                << newFlight.destination << "\n"
                << newFlight.departureTime << "\n"
                << newFlight.arrivalTime << "\n"
                << newFlight.totalSeats << "\n"
                << newFlight.availableSeats << "\n";
        outFile.close();
        cout << "Flight added successfully!" << endl;
    }
	 else 
	 {
        cout << "Unable to open file!" << endl;
    }
}


void displayFlights() 
{
    ifstream inFile("flights.txt");
    
    if (!inFile) 
	{
        cout << "Error opening file!" << endl;
        return;
    }
    
    Flight flight;
    cout << "Flight ID | Airline | Source | Destination | Departure Time | Arrival Time | Total Seats | Available Seats" << endl;
    cout << "---------------------------------------------------------------------------------------------" << endl;
    
    while (inFile >> flight.flightID) 
	{
        inFile.ignore();
        getline(inFile, flight.airlineName);
        getline(inFile, flight.source);
        getline(inFile, flight.destination);
        getline(inFile, flight.departureTime);
        getline(inFile, flight.arrivalTime);
        inFile >> flight.totalSeats;
        inFile >> flight.availableSeats;
        
        cout << flight.flightID << " | "
             << flight.airlineName << " | "
             << flight.source << " | "
             << flight.destination << " | "
             << flight.departureTime << " | "
             << flight.arrivalTime << " | "
             << flight.totalSeats << " | "
             << flight.availableSeats << endl;
    }
    
    inFile.close();
}



void searchFlightByID(string flightID) 
{
    ifstream inFile("flights.txt");

    if (!inFile) 
	{
        cout << "Error opening file!" << endl;
        return;
    }

    Flight flight;
    bool found = false;

    while (inFile >> flight.flightID) 
	{
        inFile.ignore();
        getline(inFile, flight.airlineName);
        getline(inFile, flight.source);
        getline(inFile, flight.destination);
        getline(inFile, flight.departureTime);
        getline(inFile, flight.arrivalTime);
        inFile >> flight.totalSeats;
        inFile >> flight.availableSeats;

        if (flight.flightID == flightID) 
		{
            found = true;
            cout << "Flight ID: " << flight.flightID << endl;
            cout << "Airline: " << flight.airlineName << endl;
            cout << "Source: " << flight.source << endl;
            cout << "Destination: " << flight.destination << endl;
            cout << "Departure Time: " << flight.departureTime << endl;
            cout << "Arrival Time: " << flight.arrivalTime << endl;
            cout << "Total Seats: " << flight.totalSeats << endl;
            cout << "Available Seats: " << flight.availableSeats << endl;
            break;
        }
    }

    if (!found) 
	{
        cout << "Flight with ID " << flightID << " not found!" << endl;
    }

    inFile.close();
}







void bookTicket() 
{
    string flightID;
    string passengerName;
    string seatNumber;
    double price;
    string ticketID;
    
    cout << "Enter Flight ID to book: ";
    cin >> flightID;

    ifstream flightFile("flights.txt");
    if (!flightFile) 
	{
        cout << "Error opening flight file!" << endl;
        return;
    }

    Flight flight;
    bool flightFound = false;

    while (flightFile >> flight.flightID) 
	{
        flightFile.ignore();
        getline(flightFile, flight.airlineName);
        getline(flightFile, flight.source);
        getline(flightFile, flight.destination);
        getline(flightFile, flight.departureTime);
        getline(flightFile, flight.arrivalTime);
        flightFile >> flight.totalSeats;
        flightFile >> flight.availableSeats;

        if (flight.flightID == flightID) 
		{
            flightFound = true;
            cout << "Flight found!" << endl;
            cout << "Available Seats: " << flight.availableSeats << endl;

            if (flight.availableSeats > 0) 
			{
                cout << "Enter Passenger Name: ";
                cin.ignore();
                getline(cin, passengerName);

                cout << "Enter Seat Number: ";
                cin >> seatNumber;

                cout << "Enter Ticket Price: ";
                cin >> price;

                ticketID = "T" + flightID + seatNumber;

                Ticket ticket;
                ticket.ticketID = ticketID;
                ticket.passengerName = passengerName;
                ticket.flightID = flightID;
                ticket.seatNumber = seatNumber;
                ticket.price = price;

                flight.availableSeats--;

                ofstream flightFileOut("flights.txt", ios::in | ios::out);
                if (!flightFileOut) 
				{
                    cout << "Error opening file to update available seats!" << endl;
                    return;
                }

                string tempFile = "flights_temp.txt";
                ofstream tempOut(tempFile);

                flightFile.seekg(0, ios::beg);
                while (flightFile >> flight.flightID) 
				{
                    flightFile.ignore();
                    getline(flightFile, flight.airlineName);
                    getline(flightFile, flight.source);
                    getline(flightFile, flight.destination);
                    getline(flightFile, flight.departureTime);
                    getline(flightFile, flight.arrivalTime);
                    flightFile >> flight.totalSeats;
                    flightFile >> flight.availableSeats;

                    if (flight.flightID == flightID) 
					{
                        tempOut << flight.flightID << endl;
                        tempOut << flight.airlineName << endl;
                        tempOut << flight.source << endl;
                        tempOut << flight.destination << endl;
                        tempOut << flight.departureTime << endl;
                        tempOut << flight.arrivalTime << endl;
                        tempOut << flight.totalSeats << endl;
                        tempOut << flight.availableSeats << endl;
                    }
					 else 
					 {
                        tempOut << flight.flightID << endl;
                        tempOut << flight.airlineName << endl;
                        tempOut << flight.source << endl;
                        tempOut << flight.destination << endl;
                        tempOut << flight.departureTime << endl;
                        tempOut << flight.arrivalTime << endl;
                        tempOut << flight.totalSeats << endl;
                        tempOut << flight.availableSeats << endl;
                    }
                }

                flightFile.close();
                tempOut.close();

                remove("flights.txt");
                rename(tempFile.c_str(), "flights.txt");

                ofstream ticketFile("tickets.txt", ios::app);
                if (!ticketFile) 
				{
                    cout << "Error opening ticket file!" << endl;
                    return;
                }

                ticketFile << ticket.ticketID << endl;
                ticketFile << ticket.passengerName << endl;
                ticketFile << ticket.flightID << endl;
                ticketFile << ticket.seatNumber << endl;
                ticketFile << ticket.price << endl;
                ticketFile.close();

                cout << "Ticket booked successfully!" << endl;
                cout << "Ticket ID: " << ticket.ticketID << endl;
                cout << "Passenger Name: " << ticket.passengerName << endl;
                cout << "Seat Number: " << ticket.seatNumber << endl;
                cout << "Price: " << ticket.price << endl;
            }
			 else 
			 {
                cout << "No available seats for this flight." << endl;
            }
            break;
        }
    }

    if (!flightFound) 
	{
        cout << "Flight with ID " << flightID << " not found!" << endl;
    }

    flightFile.close();
}







void displayAllTickets() 
{
    ifstream ticketFile("tickets.txt");
    if (!ticketFile) 
	{
        cout << "Error opening ticket file!" << endl;
        return;
    }

    Ticket ticket;
    cout << "Displaying All Tickets: " << endl;
    cout << "---------------------------------" << endl;

    while (ticketFile >> ticket.ticketID) 
	{
        ticketFile.ignore();
        getline(ticketFile, ticket.passengerName);
        getline(ticketFile, ticket.flightID);
        getline(ticketFile, ticket.seatNumber);
        ticketFile >> ticket.price;
        ticketFile.ignore();

        cout << "Ticket ID: " << ticket.ticketID << endl;
        cout << "Passenger Name: " << ticket.passengerName << endl;
        cout << "Flight ID: " << ticket.flightID << endl;
        cout << "Seat Number: " << ticket.seatNumber << endl;
        cout << "Price: " << ticket.price << endl;
        cout << "---------------------------------" << endl;
    }

    ticketFile.close();
}




void saveFlightDataToFile(Flight flight) 
{
    ofstream flightFile("flights.txt", ios::app);
    if (!flightFile) 
	{
        cout << "Error opening flight file!" << endl;
        return;
    }

    flightFile << flight.flightID << endl;
    flightFile << flight.airlineName << endl;
    flightFile << flight.source << endl;
    flightFile << flight.destination << endl;
    flightFile << flight.departureTime << endl;
    flightFile << flight.arrivalTime << endl;
    flightFile << flight.totalSeats << endl;
    flightFile << flight.availableSeats << endl;
    
    flightFile.close();
    cout << "Flight data saved successfully!" << endl;
}



void saveTicketDataToFile(Ticket ticket) 
{
    ofstream ticketFile("tickets.txt", ios::app);
    if (!ticketFile) 
	{
        cout << "Error opening ticket file!" << endl;
        return;
    }

    ticketFile << ticket.ticketID << endl;
    ticketFile << ticket.passengerName << endl;
    ticketFile << ticket.flightID << endl;
    ticketFile << ticket.seatNumber << endl;
    ticketFile << ticket.price << endl;

    ticketFile.close();
    cout << "Ticket data saved successfully!" << endl;
}




void displayMenu() 
{
    cout << "\nAirport Management System\n";
    cout << "1. Admin Login\n";
    cout << "2. Add Flight\n";
    cout << "3. Display All Flights\n";
    cout << "4. Search Flight by ID\n";
    cout << "5. Book Ticket\n";
    cout << "6. Display All Tickets\n";
    cout << "7. Exit\n";
    cout << "Enter your choice: ";
}

int main() 
{
    
    if (adminLogin()) 
	{
        cout << "Admin login successful!" << endl;
    }
	else 
	{
        cout << "Admin login failed!" << endl;
    }
    
    
    int choice;
    bool loggedIn = false;

    while (true) 
	{
        displayMenu();
        cin >> choice;

        switch (choice) 
		{
            case 1:
                loggedIn = adminLogin();
                if (loggedIn) 
				{
                    cout << "Admin Logged In!\n";
                }
                break;

            case 2:
                if (loggedIn) 
				{
                    addFlight();
                }
				else 
				{
                    cout << "Please log in as admin first.\n";
                }
                break;

            case 3:
                displayFlights();
                break;

            case 4: {
                string flightID;
                cout << "Enter Flight ID to search: ";
                cin >> flightID;
                searchFlightByID(flightID);
                break;
            }

            case 5:
                bookTicket();
                break;

            case 6:
                displayAllTickets();
                break;

            case 7:
                cout << "Exiting the system.\n";
                return 0;

            default:
                cout << "Invalid choice, please try again.\n";
        }
    }
}
