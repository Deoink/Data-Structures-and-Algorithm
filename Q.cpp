#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <thread>
#include <set>

using namespace std;

class Person {
	public:
    string name;
    string tketNum;

    Person(string n, string t) : name(n), tketNum(t) {}
};

class Queue {
	private:
    vector<Person> qList; 
    int tketCounter;
    set<string> recvdTickets;

	public:
    Queue() : tketCounter(1) {}

    void enqueue(const string& name) {
        string ticketNum = formatNumber(tketCounter++);
        qList.emplace_back(name, ticketNum);
        cout << name << " added to the queue with Ticket #" << ticketNum << endl;
    }

    void autoDequeue() {
        if (!qList.empty()) {
            Person front = qList.front();
            qList.erase(qList.begin()); 
            cout << "\nAfter 1 minute...\n";
            cout << "Dequeue: " << front.name << " received a ticket (Ticket #" << front.tketNum << ")" << endl;
            recvdTickets.insert(front.tketNum);
        } else {
            cout << "Queue is empty." << endl;
        }
    }

    bool isEmpty() {
        return qList.empty();
    }

    int size() {
        return qList.size();
    }

    string peek() {
        if (!qList.empty()) {
            return qList.front().name + " (Ticket #" + qList.front().tketNum + ")";
        }
        return "No one in line.";
    }

    int position(const string& nameOrticket) {
        for (int i = 0; i < qList.size(); ++i) {
            if (qList[i].name == nameOrticket || qList[i].tketNum == nameOrticket) {
                return i + 1; 
            }
        }
        return -1; 
    }

    bool hasRecvedTicket(const string& nameOrticket) {
        return recvdTickets.find(nameOrticket) != recvdTickets.end();
    }

	private:
    string formatNumber(int num) {
        return (num < 10 ? "00" : (num < 100 ? "0" : "")) + to_string(num);
    }
};

	int main() {
    Queue ticketQ;
    int choice;
    bool menuDisplayed = false;

    cout << "Welcome to Olivia Rodrigo's Concert Ticketing System!" << endl;

    auto lastDequeueTime = chrono::steady_clock::now();

    while (true) {
        auto currentTime = chrono::steady_clock::now();
        if (chrono::duration_cast<chrono::minutes>(currentTime - lastDequeueTime).count() >= 1) {
            ticketQ.autoDequeue();
            lastDequeueTime = currentTime;
            cout << "Queue size: " << ticketQ.size() << endl;
            cout << "Next in line: " << ticketQ.peek() << endl;
        }

        if (!menuDisplayed) {
            cout << "\n\t1. Enqueue a person\n\t2. Check your position in the Queue\n\t3. Exit\n";
            menuDisplayed = true;
        }

        cout << "\nChoose an option: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string name;
                cout << "Enter the name: ";
                cin >> name; 
                ticketQ.enqueue(name);
                cout << "Queue size: " << ticketQ.size() << endl;
                break;
            }
            case 2: {
                string nameOrticket;
                cout << "Enter your name or ticket number: ";
                cin >> nameOrticket;

                if (ticketQ.hasRecvedTicket(nameOrticket)) {
                    cout << nameOrticket << " has already received a ticket." << endl;
                } else {
                    int pos = ticketQ.position(nameOrticket);
                    if (pos != -1) {
                        cout << nameOrticket << " is currently at position " << pos << " in the queue.\n" << endl;
                    } else {
                        cout << nameOrticket << " is not in the queue.\n" << endl;
                    }
                }
                break;
            }
            case 3: {
                cout << "Exiting the system. Thank you!" << endl;
                return 0;
            }
            default: {
                cout << "Invalid option. Please try again." << endl;
                break;
            }
        }

        this_thread::sleep_for(chrono::seconds(1));
    }

    return 0;
}