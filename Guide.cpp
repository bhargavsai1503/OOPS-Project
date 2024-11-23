#include <iostream>
#include <string>
#include <map>
using namespace std;

// 1. Data Abstraction and Encapsulation
class Exhibit {
private:
    string name;
    string description;

public:
    // Constructor
    Exhibit(const string& name, const string& description): name(name), description(description) {}

    // Destructor
    ~Exhibit() {
        //std::cout << "Exhibit " << name << " is being destroyed.\n";
    }

    // Getter method for name
    const string& getName() const {
        return name;
    }

    // 2. Operator Overloading for easy printing of Exhibit
    friend ostream& operator<<(ostream& os, const Exhibit& exhibit);

    // 3. Data encapsulation through display method
    void display() const {
        cout << "Exhibit: " << name << "\nDescription: " << description << "\n";
    }

    // 4. Friend Function to access private members (for specific use cases)
    friend void printExhibitDetails(const Exhibit& exhibit);
};

// 4. Friend Function that can access private members of the class
void printExhibitDetails(const Exhibit& exhibit) {
    cout << "Detailed Exhibit Info: " << exhibit.name << " - " << exhibit.description << "\n";
}

// Overloading the << operator to easily print the Exhibit
ostream& operator<<(ostream& os, const Exhibit& exhibit) {
    os << "Exhibit: " << exhibit.name << ", Description: " << exhibit.description;
    return os;
}
//class composition
class SalargamMuseum {
private:
    map<string, Exhibit> exhibits;
    map<string, string> directions;

public:
    // Constructor
    SalargamMuseum() {
        // Initialize exhibits with locations
        exhibits.emplace("centre-left", Exhibit("Antique Sword", "A rare sword from the Mughal era"));
        exhibits.emplace("right", Exhibit("Royal Painting", "A painting of the Nizam of Hyderabad"));
        exhibits.emplace("straight", Exhibit("Jade Collection", "A collection of ancient jade artifacts"));
        exhibits.emplace("centre2", Exhibit("Miniature Paintings", "Exquisite miniature paintings from different eras"));
        //exhibits.emplace("top-left", Exhibit("Marble Sculpture", "A marble sculpture from the 17th century"));
        exhibits.emplace("st-right", Exhibit("Ivory Throne", "An ivory throne used by royal families"));
        exhibits.emplace("left", Exhibit("Old Manuscripts", "Ancient manuscripts with historical significance"));
        exhibits.emplace("centre-right", Exhibit("Precious Jewelry", "A collection of royal jewelry and gemstones"));
        exhibits.emplace("centre1", Exhibit("Big Clock", "An antique clock symbolizing the passage of time through history"));

        // Initialize directions for user guidance
        directions["entrance"] = "left";
        directions["left"] = "right";
        directions["right"] = "centre-right";
        directions["centre-right"] = "centre2";
        directions["centre2"] = "centre1";
        directions["centre1"] = "centre-left";
        directions["centre-left"] = "straight";
        directions["straight"] = "st-right";
        directions["st-right"] = "exit";
    }

    // 5. Method to display the museum layout
    void displayMuseumLayout() const {
        cout << R"(
               +---------------------------------+
               |                                 |
               |  Jade Collection     Ivory        (exit)
               |  (straight)          Throne     |
               |                    (st-right)   |
       +-------+---+    +------    ----------+   -+-------+
       |                                                  |
       | Antique   |   Big      | Miniature | Precious    |
       | Sword     | Clock      | Paintings | Jewelry     |
       |(centre-   | (center1)  | (centre2) | (centre-    |
       |  (left)  +----    ----------    ---+   right)    |
       |                                                  |
       +-----------------            ---------------------+
               |                               |
               | Old Manuscripts      Royal    |
               | (left)              Painting  |
               |                      (right)  |
               +-------------|  |-----------------+
                    Salargam Museum Entrance 
        )" << "\n";
    }

    // 5. Method to guide the user through the museum (uses this pointer)
    void guideUser(const string& location) const {
        auto next_direction = directions.find(location);
        if (next_direction != directions.end()) {
            cout << "\nGuide: You are currently at the " << location 
                      << ". Head " << next_direction->second << " to explore the next exhibit.\n";
            navigate(next_direction->second);
        } else {
            cout << "\nGuide: Thank you for visiting all exhibits! Feel free to exit or explore again.\n";
        }
    }

    // 6. Navigating to the next exhibit
    void navigate(const std::string& direction) const {
        auto it = exhibits.find(direction);
        if (it != exhibits.end()) {
            cout << "\nYou walk to exhibit " << direction << " and see:\n";
            it->second.display();
        } else if (direction == "exit"||it== exhibits.end()) {
            cout << "Thank you for visiting the Salargam Museum. Goodbye!\n";
        } else {
            cout << "\nInvalid direction! Try a valid location.\n";
        }
    }

    // Method to retrieve the next location
    std::string getNextLocation(const std::string& current_location) const {
        auto it = directions.find(current_location);
        return (it != directions.end()) ? it->second : "exit";
    }
};

int main() {
    SalargamMuseum museum;
    museum.displayMuseumLayout();  // Display initial map layout

    std::string current_location = "entrance";
    std::string command;

    std::cout << "\nWelcome to the Salargam Museum Guided Tour!\n";

    while (true) {
        museum.guideUser(current_location);

        std::cout << "\nType '1' to proceed to the suggested exhibit or '0' to leave: ";
        std::cin >> command;

        if (command == "0") {
            std::cout << "Thank you for visiting the Salargam Museum. Goodbye!\n";
            break;
        } else if (command == "1") {
            current_location = museum.getNextLocation(current_location);
        } else {
            std::cout << "\nInvalid command. Please type '1' or '0'.\n";
        }
    }

    return 0;
}
