#include <iostream>
#include <vector>
#include <climits>
#include <map>
#include <unordered_map>
#include <string>
#include <queue>
#include <algorithm>

using namespace std;


class Pipeline

{
public:

    int length; // in meters
    int diameter; // in inches
    string material; // Steel, PVC, etc.
    double flow_rate; // in liters per second
    double pressure; // in Pascals or PSI
    string status; // Active, Inactive, Under Maintenance
    string maintenance_schedule;
    double cost; // Cost of the pipeline in currency
    string leak_detection_type; // Leak detection type (Ultrasonic or Pressure Differential)


    Pipeline(int l, int d, string m, double fr, double p, string s, string ms, double c, string ldt)
        : length(l),
        diameter(d),
        material(m),
        flow_rate(fr),
        pressure(p),
        status(s),
        maintenance_schedule(ms),
        cost(c),
          leak_detection_type(ldt) {}



    void display()
    {
        cout << "\nPipeline details: Length = " << length << " meters, Diameter = " << diameter
             << " inches, Material = " << material << ", Flow Rate = " << flow_rate
             << " L/s, Pressure = " << pressure << " PSI, Status = " << status
             << ", Maintenance Schedule = " << maintenance_schedule << ", Cost = " << cost
             << ", Leak Detection Type = " << leak_detection_type << endl;
    }


    void updateMaintenanceSchedule(string newSchedule)
    {
        maintenance_schedule = newSchedule;
        cout << "Maintenance schedule updated to: " << newSchedule << endl;

    }


};

class Customer

{
public:

    string name;
    string address;
    string customer_id;
    string location; // Customer's location to calculate distance
    string supply_type; // Regular, Emergency
    string billing_cycle; // Monthly, Quarterly, Weekly
    double total_usage; // Total water usage during billing cycle
    double total_amount; // Total amount to be paid
    vector<Pipeline> pipelines; // A customer may have multiple pipelines
    vector<string> usage_history; // History of water usage and billing information


    // Default constructor
    Customer()
        : name(""),
        address(""),
        customer_id(""),
        location(""),
          supply_type("Regular"),
          billing_cycle("Monthly"),
          total_usage(0),
          total_amount(0) {}


    // Parameterized constructor
    Customer(string n, string addr, string id, string loc, string supply, string cycle, double usage, double amount)
        : name(n),
        address(addr),
        customer_id(id),
        location(loc),
        supply_type(supply),
        billing_cycle(cycle),
          total_usage(usage),
          total_amount(amount) {}


    void display()
    {
        cout << "\nCustomer Details: \nName: " << name << "\nAddress: " << address
             << "\nCustomer ID: " << customer_id << "\nLocation: " << location
             << "\nSupply Type: " << supply_type << "\nBilling Cycle: " << billing_cycle
             << "\nTotal Water Usage: " << total_usage << "\nTotal Amount: " << total_amount << endl;

        cout << "\nPipeline Details: " << endl;
        for (auto &pipe : pipelines)
        {
            pipe.display();
        }

        cout << "\nUsage History: " << endl;
        for (const string &record : usage_history)
        {
            cout << record << endl;
        }
    }



    void addPipeline(Pipeline p)
    {
        pipelines.push_back(p);
        cout << "New pipeline added for " << name << endl;
    }



    void addUsageRecord(string record)
    {
        usage_history.push_back(record);
        cout << "Usage record added: " << record << endl;
    }


};

class Graph

{
public:

    map<string, vector<pair<string, int>>> adj;

    void addEdge(string u, string v, int distance)
    {
        adj[u].push_back(make_pair(v, distance));
        adj[v].push_back(make_pair(u, distance));
    }


    map<string, int> dijkstra(string source)
    {
        map<string, int> dist;
        for (auto &node : adj)
        {
            dist[node.first] = INT_MAX;
        }
        dist[source] = 0;

        priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> pq;
        pq.push(make_pair(0, source));


        while (!pq.empty())
        {
            int u_dist = pq.top().first;
            string u = pq.top().second;
            pq.pop();

            if (u_dist > dist[u])
                continue;

            for (auto &neighbor : adj[u])
            {
                string v = neighbor.first;
                int weight = neighbor.second;

                if (dist[u] + weight < dist[v])
                {
                    dist[v] = dist[u] + weight;
                    pq.push(make_pair(dist[v], v));
                }
            }
        }
        return dist;
    }



    int getShortestDistanceToPumpStation(string customerLocation)
    {
        map<string, int> distances = dijkstra(customerLocation);

        int minDistance = INT_MAX;

        for (auto &d : distances)
        {
            if (d.first != customerLocation && d.second < minDistance)
            {
                minDistance = d.second;
            }
        }
        return (minDistance == INT_MAX) ? -1 : minDistance;
    }


};

void displayMenu()

{
    cout << "\n\nWelcome to the Belagavi City Water Corporation\n";
    cout << "Please choose an option:\n";
    cout << "0. Create New Customer\n";
    cout << "1. Choose Material Type of Pipe\n";
    cout << "2. Choose Billing Type\n";
    cout << "3. Choose Leak Detection Type\n";
    cout << "4. Choose Supply Type\n";
    cout << "5. View Pipeline Details\n";
    cout << "6. View Customer Details\n";
    cout << "7. Finalize Selections\n";
    cout << "8. View Total Installation Cost\n";
    cout << "9. Update Maintenance Schedule\n";
    cout << "10. Add New Pipeline\n";
    cout << "11. Customer Details (Already Installed Pipeline)\n";
    cout << "12. Disconnect Pipeline (Already Installed Pipeline)\n";
    cout << "13. Exit\n";


}

// Structure to represent the AreaDetails with distance and cost
struct AreaDetails {
    string area_name;
    int distance; // distance from selected area (in meters)
    int cost;     // cost in Rs
};

// Structure to represent the Sub-division gas pipeline Office
struct Sub_division_gas_pipeline_office {
    vector<AreaDetails> areas;  // List of areas in the sub-division
};

// Function to implement the functionality of displaying areas based on the selected zone
void displayAreas(const string& selected_zone, const unordered_map<string, vector<string>>& zone_areas)
{
    cout << selected_zone << " contains the following areas:\n";
    const vector<string>& areas = zone_areas.at(selected_zone);  // Get areas for selected zone
    for (size_t i = 0; i < areas.size(); ++i) {
        cout << i + 1 << ". " << areas[i] << endl;  // Display area number and name
    }
}

// Function to display the sub-division office and area details based on the selected area
void displaySubDivisionDetails(const string& selected_area, const unordered_map<string, Sub_division_gas_pipeline_office>& area_details) {
    auto it = area_details.find(selected_area);  // Find the selected area in the area details map
    if (it != area_details.end()) {
        // Correctly displaying the area name dynamically
        cout << "gas pipeline office " << selected_area << ":\n";
        for (size_t i = 0; i < it->second.areas.size(); ++i) {
            const AreaDetails& area = it->second.areas[i];
            cout << i + 1 << ". " << area.area_name << " - " << area.distance << " meters, cost - " << area.cost << " rs\n";
        }
    } else {
        cout << "Area not found in this sub-division.\n";
    }
}

// Function to find the area with the shortest distance
string findShortestDistanceArea(const vector<AreaDetails>& areas) {
    // Find the area with the minimum distance
    auto min_it = min_element(areas.begin(), areas.end(), [](const AreaDetails& a, const AreaDetails& b) {
        return a.distance < b.distance;
    });
    return min_it->area_name;
}

// Function to calculate the volume of a cylindrical pipe
double calculatePipeVolume(double length, double outerDiameter, double thickness)
{
    const double PI = 3.14159265359;
    double innerDiameter = outerDiameter - 2 * thickness;
    double outerRadius = outerDiameter / 2.0;
    double innerRadius = innerDiameter / 2.0;

    double outerVolume = PI * outerRadius * outerRadius * length;
    double innerVolume = PI * innerRadius * innerRadius * length;

    return outerVolume - innerVolume; // Material volume
}
// Function to calculate the surface area of a cylindrical pipe
double calculateSurfaceArea(double length, double outerDiameter)
{
    const double PI = 3.14159265359;
    double radius = outerDiameter / 2.0;
    return 2 * PI * radius * length; // Surface area of the cylindrical surface
}

// Function to categorize pressure
string categorizePressure(double pressure)
 {
    if (pressure > 100)
    {
        return "High Pressure";
    } else if (pressure >= 40 && pressure <= 100)
    {
        return "Medium Pressure";
    } else
    {
        return "Low Pressure";
    }
}



int main()

{
    map<string, Customer> customerDatabase;

    customerDatabase["C0101"] = Customer("John Doe", "123 Main St", "C0101", "Shaniwar Khoot", "Regular", "Monthly", 100, 2500);

    customerDatabase["C0102"] = Customer("Jane Smith", "456 Elm St", "C0102", "Khade Bazar", "Emergency", "Weekly", 200, 6000);

    customerDatabase["C0103"] = Customer("Alice Brown", "789 Pine St", "C0103", "Green Taj", "Regular", "Weekly", 150.0, 8000.0);

    customerDatabase["C0104"] = Customer("Emily Davis", "101 Oak St", "C0104", "Budhwar Peth", "Regular", "Monthly", 50.0, 20000.0);

    customerDatabase["C0105"] = Customer("Michael Brown", "202 Maple St", "C0105", "Angol", "Standard", "Quarterly", 75.0, 28000.0);

    customerDatabase["C0106"] = Customer("Sophia White", "303 Cedar St", "C0106", "Ramdev", "Premium", "Monthly", 0.0, 35000.0);

    customerDatabase["C0107"] = Customer("William Green", "404 Birch St", "C0107", "Mangalwar Peth", "Regular", "Quarterly", 50.0, 27000.0);

    customerDatabase["C0108"] = Customer("Olivia Black", "505 Ash St", "C0108", "Udyambag", "Premium", "Monthly", 100.0, 25000.0);

    customerDatabase["C0109"] = Customer("Ethan Harris", "606 Willow St", "C0109", "Tilakwadi", "Standard", "Monthly", 200.0, 35000.0);

    customerDatabase["C0110"] = Customer("Ava Martinez", "707 Cherry St", "C0110", "Bhagya Nagar", "Regular", "Quarterly", 150.0, 3300.0);

    customerDatabase["C0111"] = Customer("Carlos Lee", "808 Rose St", "C0111", "Tilakwadi", "Regular", "Monthly", 90.0, 2700.0);

    customerDatabase["C0112"] = Customer("Mia Williams", "909 Lily St", "C0112", "Udyambag", "Premium", "Monthly", 0.0, 3800.0);

    customerDatabase["C0113"] = Customer("David Brown", "1001 Maple Ave", "C0113", "Udyambag", "Standard", "Quarterly", 50.0, 2500.0);

    customerDatabase["C0114"] = Customer("Isabella Clark", "1202 Elm St", "C0114", "Tilakwadi", "Regular", "Monthly", 100.0, 2300.0);

    customerDatabase["C0115"] = Customer("Ethan Thomas", "1303 Cedar St", "C0115", "Udyambag", "Premium", "Monthly", 0.0, 3900.0);

    customerDatabase["C0116"] = Customer("Oliver Anderson", "1404 Pine St", "C0116", "Udyambag", "Regular", "Quarterly", 100.0, 3100.0);

    customerDatabase["C0117"] = Customer("Ava Moore", "1505 Oak St", "C0117", "Udyambag", "Premium", "Monthly", 0.0, 3800.0);

    customerDatabase["C0118"] = Customer("Lucas Harris", "1606 Birch St", "C0118", "Udyambag", "Regular", "Quarterly", 50.0, 2900.0);

    customerDatabase["C0119"] = Customer("Charlotte Lee", "1707 Willow St", "C0119", "Udyambag", "Premium", "Monthly", 0.0, 3600.0);

    customerDatabase["C0120"] = Customer("James Davis", "1808 Cherry St", "C0120", "Tilakwadi", "Regular", "Monthly", 90.0, 2800.0);


    //The location distances to pump stations

    Graph g;
    g.addEdge("Shaniwar Khoot", "Khanjar Galli", 500);

    g.addEdge("Shaniwar Khoot", "Green Taj", 700);

    g.addEdge("Khade Bazar", "Kaktives Road", 300);

    g.addEdge("Topi Galli", "Bhavye Chowk", 1000);

    g.addEdge("Shivaji Nagar", "Sadashiv Nagar", 800);

    g.addEdge("Tilakwadi", "Maratha Colony", 1600);

    g.addEdge("Tilakwadi", "Mangalwar Peth", 1300);

    g.addEdge("Tilakwadi", "Guruwar Peth", 1200);

    g.addEdge("Tilakwadi", "Khanapu Road", 1000);

    g.addEdge("Tilakwadi", "Hindu Nagar", 850);

    g.addEdge("Tilakwadi", "Budhawar Peth", 1400);

    g.addEdge("Tilakwadi", "Deshmukh Road", 1300);

    g.addEdge("Tilakwadi", "Somawar Peth", 1300);

    g.addEdge("Tilakwadi", "Shukrawar Peth", 1700);

    g.addEdge("Udyambag", "Angol Industrial Estate", 1300);

    g.addEdge("Udyambag", "Parvati Nagar", 1200);

    g.addEdge("Udyambag", "Kle college road", 1400);

    g.addEdge("Udyambag", "Panjim-Belagavi Road", 800);

    g.addEdge("Udyambag", "Subhas Chandra Nagar", 1700);

    g.addEdge("Udyambag", "Kalameshwar Housing Colony", 1200);

    g.addEdge("Udyambag", "Angol", 1500);

    g.addEdge("Udyambag", "Sbi colony", 1400);

    g.addEdge("Angol", "Bhagya Nagar", 1000);

    g.addEdge("Angol", "Hindwadi", 700);

    g.addEdge("Angol", "Omkar Nagar", 900);

    g.addEdge("Angol", "Adarsh Nagar", 1200);

    g.addEdge("Angol", "Anand Nagar", 1300);

    g.addEdge("Angol", "Ambedkar Nagar", 1100);

    g.addEdge("Chenamma Circle", "Neharu Nagar", 750);

    g.addEdge("Chenamma Circle", "Ashok Nagar", 600);

    g.addEdge("Chenamma Circle", "Shivabasav Nagar", 1200);

    g.addEdge("Chenamma Circle", "Ayodhya Nagar", 1050);

    g.addEdge("Chenamma Circle", "Ramdev", 900);

    g.addEdge("Chenamma Circle", "RLS", 500);

    g.addEdge("Mahantesh Nagar", "Revenue Colony", 1000);

    g.addEdge("Mahantesh Nagar", "Shivatirtha Colony", 900);

    g.addEdge("Mahantesh Nagar", "Rukmini Nagar", 650);

    g.addEdge("Mahantesh Nagar", "Shree Nagar Garden", 800);

    g.addEdge("Mahantesh Nagar", "Malini Nagar", 1200);

    g.addEdge("Mahantesh Nagar", "Ramtirtha Nagar", 1500);

    g.addEdge("Shahu Nagar", "Vaibhav Nagar", 1600);

    g.addEdge("Shahu Nagar", "Basav Colony", 1300);

    g.addEdge("Shahu Nagar", "Sai Colony", 500);

    g.addEdge("Shahu Nagar", "Bauxite Road", 700);

    g.addEdge("Shahu Nagar", "Vandan Colony", 1200);

    g.addEdge("Shahu Nagar", "Kalmeshwar Nagar", 1000);

    g.addEdge("Shahu Nagar", "Kangrali", 900);

    g.addEdge("Raviwar Peth", "Motilal Circle", 600);

    g.addEdge("Raviwar Peth", "Samadevi Galli", 800);

    g.addEdge("Tilakwadi", "Nanawadi", 500);

    g.addEdge("Tilakwadi", "Shahapur", 1000);

    g.addEdge("Udayambag", "Majagaon", 1400);

    g.addEdge("Khade Bazar", "Gandhi Nagar", 1500);

    g.addEdge("Neharu Nagar", "Mahantesh Nagar", 1300);

    g.addEdge("Mahantesh nagar", "Gandhi Nagar", 800);

    g.addEdge("Udayambag", "Piranwadi", 1800);

    g.addEdge("Mahantesh Nagar", "Kanabargi", 900);

    g.addEdge("Hanuman Nagar", "Sadashiv Nagar", 750);

    g.addEdge("Sahyadri Nagar", "Hanuman Nagar", 900);

    g.addEdge("Mahantesh Nagar", "Anjaneya Nagar", 600);

    g.addEdge("Tilakwadi", "RPD", 550);

    g.addEdge("Gandhi Nagar", "Pai Hotel", 600);

    g.addEdge("Hanuman Nagar", "Anjaneya Nagar", 1200);

    g.addEdge("Anjaneya Nagar", "Kanabargi", 750);

    g.addEdge("Shahapur", "Udayambag", 900);

    g.addEdge("Kakar Galli", "Tilak Chowk", 1400);

    g.addEdge("Sardar High School", "Topi Galli", 1300);

    g.addEdge("Azad Galli", "Samadevi Galli", 850);

    g.addEdge("Vidyagiri", "Motilal Circle", 650);

    g.addEdge("Kanakdas Circle", "Shani Mandir", 1000);

    g.addEdge("Rayanna Circle", "Sambhaji Circle", 300);

    g.addEdge("Shivaji Nagar", "Ganpat Galli", 500);

    g.addEdge("Govt. Hospital", "Court Compound", 200);

    g.addEdge("Tilakwadi", "Deshmukh Road", 1000);

    // Declare variables

    string name, address, customerID, location;
    string pipeMaterial;
    string billingCycle;
    string leakDetectionType;
    string supplyType;

    bool materialSelected = false;
    bool billingSelected = false;
    bool leakDetectionSelected = false;
    bool supplyTypeSelected = false;
    Pipeline pipeline(0, 0, "", 0.0, 0.0, "", "", 0.0, "");
     // Initialize pipeline object
    Customer customer;
    // Initialize customer object

    map<string, string> leakDetectionOptions = {{"1", "Ultrasonic"}, {"2", "Pressure Differential"}};

    map<string, double> materialRates = {{"Steel", 900.0}, {"PVC", 400.0}, {"Concrete", 650.0}};

    map<string, map<string, double>> supplyPricing =
    {
        {"Regular", {{"Monthly", 100.0}, {"Quarterly", 250.0}, {"Weekly", 25.0}}},

        {"Emergency", {{"Monthly", 200.0}, {"Quarterly", 500.0}, {"Weekly", 50.0}}}
    };

    bool exitMenu = false;

    while (!exitMenu)
        {
        displayMenu();
        int choice;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {

            case 0:
                {
                cout << "Enter Customer Name: ";
                cin.ignore();
                getline(cin, name);

                cout << "Enter Customer Address: ";
                getline(cin, address);

                cout << "Enter Customer ID: ";
                cin >> customerID;

                cout << "Enter Customer Location: ";
                cin.ignore();
                getline(cin, location);

                customer = Customer(name, address, customerID, location, "Regular", "Monthly", 0, 0);
                cout << "\nCustomer Created Successfully!\n";

                int shortestDistance = g.getShortestDistanceToPumpStation(customer.location);
                cout << "\nCalculating shortest distance from your location to the nearest pump station...\n";

                if (shortestDistance != -1)
                    {
                    cout << "The shortest distance to the nearest pump station is: " << shortestDistance << " meters." << endl;
                }

                else
                    {
                    cout << "No pump station found or no path exists from your location." << endl;
                }
                 // Now create the Pipeline object with the calculated shortestDistance
                Pipeline pipeline(shortestDistance, 12, "Steel", 20.5, 250, "Active", "Monthly", 0.0, "");

                break;
            }

            case 1:
                {
                cout << "\nChoose Material Type for Pipe (1. Steel, 2. PVC, 3. Concrete): ";
                int materialChoice;
                cin >> materialChoice;

                if (materialChoice == 1)
                    {
                    pipeMaterial = "Steel";
                    pipeline.material = "Steel";
                }

                else if (materialChoice == 2)
                    {
                    pipeMaterial = "PVC";
                    pipeline.material = "PVC";
                }

                else if (materialChoice == 3)
                    {
                    pipeMaterial = "Concrete";
                    pipeline.material = "Concrete";
                }

                else
                    {
                    cout << "Invalid choice." << endl;
                    continue;
                }
                materialSelected = true;
                cout << "You selected " << pipeMaterial << " as the material." << endl;

                break;
            }

            case 2:
                {
                cout << "\nChoose Billing Type (1. Monthly, 2. Quarterly, 3. Weekly): ";
                int billingChoice;
                cin >> billingChoice;

                if (billingChoice == 1)
                    {
                    billingCycle = "Monthly";
                    customer.billing_cycle = "Monthly";
                }

                else if (billingChoice == 2)
                    {
                    billingCycle = "Quarterly";
                    customer.billing_cycle = "Quarterly";
                }

                else if (billingChoice == 3)
                    {
                    billingCycle = "Weekly";
                    customer.billing_cycle = "Weekly";
                }

                else
                {
                    cout << "Invalid choice." << endl;
                    continue;
                }
                billingSelected = true;
                cout << "You selected " << billingCycle << " billing." << endl;
                break;
            }
            case 3: {
                cout << "\nChoose Leak Detection Type (1. Ultrasonic, 2. Pressure Differential): ";
                string leakChoice;
                cin >> leakChoice;
                if (leakDetectionOptions.count(leakChoice))
                    {
                    leakDetectionType = leakDetectionOptions[leakChoice];
                    pipeline.leak_detection_type = leakDetectionType;
                    leakDetectionSelected = true;
                    cout << "You selected " << leakDetectionType << " for leak detection." << endl;
                }

                else
                    {
                    cout << "Invalid choice." << endl;
                }
                break;
            }
            case 4: {
                cout << "\nChoose Supply Type (1. Regular, 2. Emergency): ";
                string supplyChoice;
                cin >> supplyChoice;

                if (supplyChoice == "1")
                    {
                    supplyType = "Regular";
                    customer.supply_type = "Regular";
                }

                else if (supplyChoice == "2")
                {
                    supplyType = "Emergency";
                    customer.supply_type = "Emergency";
                }

                else
                {
                    cout << "Invalid choice." << endl;
                    continue;
                }
                supplyTypeSelected = true;
                if (supplyPricing.count(supplyType) && supplyPricing[supplyType].count(billingCycle))
                    {
                    double supplyCost = supplyPricing[supplyType][billingCycle];
                    cout << "You selected " << supplyType << " as the supply type." << endl;
                    cout << "The cost for " << supplyType << " supply with " << billingCycle << " billing is: " << supplyCost << " currency." << endl;
                    break;
            }
            }
            case 5: {
                      // View Pipeline Details
                    if (pipeline.material != "") { // Check if pipeline is initialized
                    pipeline.display();
                    } else {
                       cout << "No pipeline has been set yet. Please create or select a pipeline first." << endl;
                  }
              break;
            }

            case 6:
                {
                    // View Customer Details

                customer.display();

                break;
            }

            case 7:
                {
                    // Finalize Selections

                if (billingSelected && materialSelected && leakDetectionSelected && supplyTypeSelected)
                    {
                    double materialCost = materialRates[pipeMaterial];
                    double supplyCost = supplyPricing[supplyType][billingCycle];
                    double totalInstallCost = materialCost * pipeline.length + supplyCost;
                    customer.total_amount = totalInstallCost;
                    cout << "\nCustomer Final Selections:\n";
                    customer.display();
                    pipeline.display();
                }

                else
                    {
                    cout << "Please make all necessary selections before finalizing." << endl;
                }

                break;
            }


            case 8:
                {
                    // View Total Installation Cost

                if (customer.total_amount > 0)
                    {
                    cout << "The total installation cost is: " << customer.total_amount << endl;
                }

                else
                    {
                    cout << "Installation cost has not been calculated yet.\n";
                }

                break;
            }


            case 9:
                {
                    // Update Maintenance Schedule

                cout << "Enter new maintenance schedule: ";
                string newSchedule;
                cin >> newSchedule;
                pipeline.updateMaintenanceSchedule(newSchedule);

                break;
            }


            case 10:
                {
                    // Add New Pipeline

                cout << "\nEnter details for new pipeline:\n";
                cout << "Length (meters): ";
                int length;
                cin >> length;

                cout << "Diameter (inches): ";
                int diameter;
                cin >> diameter;

                cout << "Material (Steel, PVC, Concrete): ";
                string material;
                cin >> material;

                cout << "Flow Rate (L/s): ";
                double flowRate;
                cin >> flowRate;

                cout << "Pressure (PSI): ";
                double pressure;
                cin >> pressure;

                cout << "Maintenance Schedule: ";
                string maintSchedule;
                cin >> maintSchedule;

                Pipeline newPipe(length, diameter, material, flowRate, pressure, "Active", maintSchedule, 0.0, "Ultrasonic");
                customer.addPipeline(newPipe);

                break;
            }

        case 11:
        {
            cout << "Enter Customer ID to get Details: ";
            string id;
            cin >> id;

            if (customerDatabase.find(id) != customerDatabase.end())
            {
                customerDatabase[id].display();
            }

            else
            {
                cout << "Customer not found." << endl;
            }
            break;
        }

        case 12:
        {
            cout << "Enter Customer ID: ";
            string id;
            cin >> id;
            if (customerDatabase.find(id) != customerDatabase.end())
            {
                cout << "Reason for Pipeline Disconnection: ";
                string reason;
                cin.ignore();
                getline(cin, reason);
                cout << "Pipeline for customer ID " << id << " has been disconnected. Reason: " << reason << endl;
                customerDatabase.erase(id);
            }

            else
            {
                cout << "Customer not found." << endl;
            }
            break;
        }

        case 13:

            exitMenu = true;
            cout << "Exiting the program..!" << endl;

            break;

        default:
            cout << "Invalid choice. Please try again." << endl;

            break;
        }
    }
    // User interface for input
    cout << "The Belagavi city gas pipeline " << endl;
    cout << "Enter the Zones (1. East zone, 2. West zone, 3. North zone, 4. South zone): ";
    int zone_choice;
    cin >> zone_choice;

    string selected_zone;
    unordered_map<int, string> zone_map =
     {
        {1, "East Zone"},
        {2, "West Zone"},
        {3, "North Zone"},
        {4, "South Zone"}
    };

    if (zone_map.find(zone_choice) == zone_map.end())
    {
        cout << "Invalid Zone" << endl;
        return 1;
    }

    selected_zone = zone_map[zone_choice];
    cout << "The selected zone is: " << selected_zone << endl;

    // Define the list of areas for each zone
    unordered_map<string, vector<string>> zone_areas =
    {
        {"East Zone", {"Shaniwar Khoot",
                       "Khanjar Galli",
                       "Green Taj",
                       "Khanjar Galli Cross",
                       "Khanjar Galli Urdu School",
                       "Darbar Galli Cross",
                       "Bagwan Galli Cross",
                       "Kotwal Galli Double Road",
                       "Kakar Galli",
                       "Khade Bazar",
                       "Tenginkeri Galli Junction",
                       "Govt. Hospital",
                       "Mesni Galli",
                       "Kaktives",
                       "Chandu Galli",
                       "Ghee Galli - Jalgar Galli",
                       "Mali Galli",
                       "MBS No. 4 Azad Galli",
                       "Joshi Bazar",
                       "Joshi Bazar Road",
                       "Karnatak Chowk",
                       "Kalmath Road",
                       "Bhavye Chowk",
                       "Ananshyana Galli",
                       "Konwal Galli",
                       "Tilak Chowk",
                       "Raghvendra Math",
                       "SamsunG Showroom",
                       "Corporation Bank",
                       "Sardar High School",
                       "Court Compound",
                       "Topi Galli",
                       "Darbar Galli Cross",
                       "Chavat Galli to PB Road",
                       "Shetti Galli PB Road Cross",
                       "Kotwal Galli Double Road",
                       "Kaktives Road",
                       "Sardar High School Ground",
                       "Konwal Galli Guest House",
                       "Azad Galli", "Hospital Road",
                       "Tenginkeri Sheetal Hotel Cross",
                       "Pai Hotel",
                       "Old PB Road South Peripheral"}},
        {"West Zone", {"Raviwar Peth Main Road",
                       "Motilal Circle",
                       "Hira Talkies",
                       "Ganpat Galli upto Hira Talkies",
                       "Kirloskar Road",
                       "Bata Showroom",
                       "Ramdev Galli",
                       "Adarsh Dress Circle",
                       "SamsunG Showroom",
                       "Samadevi Galli",
                       "Gondhalli Galli",
                       "Gavli Galli",
                       "Narvekar Gali",
                       "Risaldar Galli",
                       "Khade Bazar Police Station",
                       "Shaniwar Khoot - Ganpat Galli",
                       "Hira Talkies Backside",
                       "Kalkundrikar Road",
                       "Kalkundrikar",
                       "Ganga Prabaha Hotel",
                       "Kirloskar Road",
                       "Bata Showroom"}},
        {"North Zone", {"Moksahi Galli",
                        "Bauxite Road",
                        "Bank of Maharashtra",
                        "Nayaya Marg",
                        "Vidyagiri",
                        "Basav Colony",
                        "Shivbasav Nagar",
                        "Bauxite Road",
                        "Kanakdas Circle",
                        "Shankam Hotel Cross",
                        "Gandhi Nagar",
                        "Shivterth Colony",
                        "KLE Compound",
                        "Jadhav Nagar",
                        "Shivaji Garden",
                        "Vandan Colony",
                        "Vidyagiri"}},
        {"South Zone", {"Chennamma Circle",
                        "Rayanna Circle",
                        "Keerti Hotel",
                        "Shetti Galli",
                        "Old PB Road",
                        "SamsunG Showroom",
                        "Raviwar Peth Main Road",
                        "Shani Mandir",
                        "Shivaji Nagar",
                        "Sambhaji Circle",
                        "Shivbasav Nagar",
                        "Ram Nagar",
                        "NCC Arts",
                        "Bharat Motor School",
                        "Jadhav Nagar",
                        "Sadashiv Nagar",
                        "Vengurla Road",
                        "DC Bungalow Cross",
                        "Ambedkar Road",
                        "Chennamma Circle - College Road",
                        "Vengurla Road - DC Bungalow",
                        "Rail Nagar South Cross",
                        "TB Ward - Ambedkar Road",
                        "APMC Road",
                        "Ambedkar Road",
                        "Veerbhadra Nagar"}}



};

    // Define the sub-division office and area details
    unordered_map<string, Sub_division_gas_pipeline_office> area_details = {
        {"Green Taj", {
            {{"Green Taj", 800, 3000},
            {"Khanjar Galli", 500, 2500},
            {"Shaniwar Khoot", 300, 2000},
             {"Khanjar Galli Cross", 1000, 3300},
             {"Khanjar Galli Urdu School", 900, 3200}}}
        },
        {"Shaniwar Khoot",{
         {{"Shaniwar Khoot", 300, 2000},
         {"Khanjar Galli", 500, 2500},
        {"Green Taj", 800, 3000},
        {"Khanjar Galli Cross", 1000, 3300},
        {"Khanjar Galli Urdu School", 900, 3200},
        {"Darbar Galli Cross", 1200, 3500},
        {"Bagwan Galli Cross", 300, 2000}}}
        },
        {"Khanjar Galli",{
         {{"Shaniwar Khoot", 300, 2000},
         {"Khanjar Galli", 500, 2500},
        {"Green Taj", 800, 3000},
        {"Khanjar Galli Cross", 1000, 3300},
        {"Khanjar Galli Urdu School", 900, 3200},
        {"Darbar Galli Cross", 1200, 3500},
        {"Bagwan Galli Cross", 300, 2000}}}
        },
        {"Darbar Galli Cross",{
         {{"Shaniwar Khoot", 300, 2000},
         {"Khanjar Galli", 500, 2500},
        {"Green Taj", 800, 3000},
        {"Khanjar Galli Cross", 1000, 3300},
        {"Khanjar Galli Urdu School", 900, 3200},
        {"Darbar Galli Cross", 1200, 3500},
        {"Bagwan Galli Cross", 300, 2000}}}
        },
        {"Bagwan Galli Cross",{
         {{"Shaniwar Khoot", 300, 2000},
         {"Khanjar Galli", 500, 2500},
        {"Green Taj", 800, 3000},
        {"Khanjar Galli Cross", 1000, 3300},
        {"Khanjar Galli Urdu School", 900, 3200},
        {"Darbar Galli Cross", 1200, 3500},
        {"Bagwan Galli Cross", 300, 2000}}}
        },
        {"Khanjar Galli Cross", {
            {{"Green Taj", 800, 3000},
            {"Khanjar Galli", 500, 2500},
            {"Shaniwar Khoot", 300, 2000},
             {"Khanjar Galli Cross", 1000, 3300},
             {"Khanjar Galli Urdu School", 900, 3200}}}
        },
        {"Khanjar Galli Urdu School", {
            {{"Green Taj", 800, 3000},
            {"Khanjar Galli", 500, 2500},
            {"Shaniwar Khoot", 300, 2000},
             {"Khanjar Galli Cross", 1000, 3300},
             {"Khanjar Galli Urdu School", 900, 3200}}}
        },
        {"Khade Bazar",{
        {{"Kotwal Galli Double Road", 2000, 5500},
        {"Kakar Galli", 1600, 4800},
        {"Khade Bazar", 300, 2000},
        {"Tenginkeri Galli Junction", 900, 3200},
        {"Govt. Hospital", 1000, 3300},
        {"Green Taj", 500, 2500}}}
        },
        {"Kotwal Galli Double Road",{
        {{"Kotwal Galli Double Road", 2000, 5500},
        {"Kakar Galli", 1600, 4800},
        {"Khade Bazar", 300, 2000},
        {"Tenginkeri Galli Junction", 900, 3200},
        {"Govt. Hospital", 1000, 3300},
        {"Green Taj", 500, 2500}}}
        },
        {"Kakar Galli",{
        {{"Kotwal Galli Double Road", 2000, 5500},
        {"Kakar Galli", 1600, 4800},
        {"Khade Bazar", 300, 2000},
        {"Tenginkeri Galli Junction", 900, 3200},
        {"Govt. Hospital", 1000, 3300},
        {"Green Taj", 500, 2500}}}
        },
        {"Tenginkeri Galli Junction",{
        {{"Kotwal Galli Double Road", 2000, 5500},
        {"Kakar Galli", 1600, 4800},
        {"Khade Bazar", 300, 2000},
        {"Tenginkeri Galli Junction", 900, 3200},
        {"Govt. Hospital", 1000, 3300},
        {"Green Taj", 500, 2500}}}
        },
        {"Govt. Hospital",{
        {{"Kotwal Galli Double Road", 2000, 5500},
        {"Kakar Galli", 1600, 4800},
        {"Khade Bazar", 300, 2000},
        {"Tenginkeri Galli Junction", 900, 3200},
        {"Govt. Hospital", 1000, 3300},
        {"Green Taj", 500, 2500}}}
        },
        {"Kaktives",{
        {{"Govt. Hospital", 1000, 3300},
        {"Green Taj", 500, 2500},
        {"Mesni Galli", 500, 2500},
        {"Kaktives", 1600, 4800},
        {"Chandu Galli", 2000, 5500},
        {"Khanjar Galli Cross", 800, 3000},
        {"Ghee Galli - Jalgar Galli", 2500, 6500}}
        }
        },
        {"Mesni Galli",{
        {{"Govt. Hospital", 1000, 3300},
        {"Green Taj", 500, 2500},
        {"Mesni Galli", 500, 2500},
        {"Kaktives", 1600, 4800},
        {"Chandu Galli", 2000, 5500},
        {"Khanjar Galli Cross", 800, 3000},
        {"Ghee Galli - Jalgar Galli", 2500, 6500}}
        }
        },
        {"Chandu Galli",{
        {{"Govt. Hospital", 1000, 3300},
        {"Green Taj", 500, 2500},
        {"Mesni Galli", 500, 2500},
        {"Kaktives", 1600, 4800},
        {"Chandu Galli", 2000, 5500},
        {"Khanjar Galli Cross", 800, 3000},
        {"Ghee Galli - Jalgar Galli", 2500, 6500}}
        }
        },
        {"Ghee Galli - Jalgar Galli",{
        {{"Govt. Hospital", 1000, 3300},
        {"Green Taj", 500, 2500},
        {"Mesni Galli", 500, 2500},
        {"Kaktives", 1600, 4800},
        {"Chandu Galli", 2000, 5500},
        {"Khanjar Galli Cross", 800, 3000},
        {"Ghee Galli - Jalgar Galli", 2500, 6500}}
        }
        },
        {"Topi Galli",{
        {{"Mali Galli", 500, 2500},
        {"MBS No. 4 Azad Galli", 1200, 3500},
        {"Joshi Bazar", 800, 3000},
        {"Joshi Bazar Road", 900, 3200},
        {"Karnatak Chowk", 1600, 4800},
        {"Kalmath Road", 3500, 8000},
        {"Khade Bazar", 1000, 3000},
        {"Topi Galli", 200, 1800},
        {"Ananshyana Galli", 800, 3000}}}
        },
        {"Joshi Bazar",{
        {{"Mali Galli", 500, 2500},
        {"MBS No. 4 Azad Galli", 1200, 3500},
        {"Joshi Bazar", 800, 3000},
        {"Joshi Bazar Road", 900, 3200},
        {"Karnatak Chowk", 1600, 4800},
        {"Kalmath Road", 3500, 8000},
        {"Khade Bazar", 1000, 3000},
        {"Topi Galli", 200, 1800},
        {"Ananshyana Galli", 800, 3000}}}
        },
        {"Karnatak Chowk",{
        {{"Mali Galli", 500, 2500},
        {"MBS No. 4 Azad Galli", 1200, 3500},
        {"Joshi Bazar", 800, 3000},
        {"Joshi Bazar Road", 900, 3200},
        {"Karnatak Chowk", 1600, 4800},
        {"Kalmath Road", 3500, 8000},
        {"Khade Bazar", 1000, 3000},
        {"Topi Galli", 200, 1800},
        {"Ananshyana Galli", 800, 3000}}}
        },
        {"Ananshyana Galli",{
        {{"Mali Galli", 500, 2500},
        {"MBS No. 4 Azad Galli", 1200, 3500},
        {"Joshi Bazar", 800, 3000},
        {"Joshi Bazar Road", 900, 3200},
        {"Karnatak Chowk", 1600, 4800},
        {"Kalmath Road", 3500, 8000},
        {"Khade Bazar", 1000, 3000},
        {"Topi Galli", 200, 1800},
        {"Ananshyana Galli", 800, 3000}}}
        },
        {"Kalmath Road",{
        {{"Mali Galli", 500, 2500},
        {"MBS No. 4 Azad Galli", 1200, 3500},
        {"Joshi Bazar", 800, 3000},
        {"Joshi Bazar Road", 900, 3200},
        {"Karnatak Chowk", 1600, 4800},
        {"Kalmath Road", 3500, 8000},
        {"Khade Bazar", 1000, 3000},
        {"Topi Galli", 200, 1800},
        {"Ananshyana Galli", 800, 3000}}}
        },
        {"Tilak Chowk",{
        {{"Konwal Galli", 500, 2500},
        {"Tilak Chowk", 1200, 3500},
        {"Raghvendra Math", 1600, 4800},
        {"SamsunG Showroom", 300, 2000},
        {"Corporation Bank", 3500, 8000},
        {"Sardar High School", 2000, 5500},
        {"Court Compound", 1000, 3300}}}
        },
        {"Konwal Galli",{
        {{"Konwal Galli", 500, 2500},
        {"Tilak Chowk", 1200, 3500},
        {"Raghvendra Math", 1600, 4800},
        {"SamsunG Showroom", 300, 2000},
        {"Corporation Bank", 3500, 8000},
        {"Sardar High School", 2000, 5500},
        {"Court Compound", 1000, 3300}}}
        },
        {"Raghvendra Math",{
        {{"Konwal Galli", 500, 2500},
        {"Tilak Chowk", 1200, 3500},
        {"Raghvendra Math", 1600, 4800},
        {"SamsunG Showroom", 300, 2000},
        {"Corporation Bank", 3500, 8000},
        {"Sardar High School", 2000, 5500},
        {"Court Compound", 1000, 3300}}}
        },
        {"Court Compound",{
        {{"Konwal Galli", 500, 2500},
        {"Tilak Chowk", 1200, 3500},
        {"Raghvendra Math", 1600, 4800},
        {"SamsunG Showroom", 300, 2000},
        {"Corporation Bank", 3500, 8000},
        {"Sardar High School", 2000, 5500},
        {"Court Compound", 1000, 3300}}}
        },
        {"Bhavye Chowk",{
        {{"Bhavye Chowk",200, 1800},
        {"Darbar Galli Cross",2500, 6500},
        {"SamsunG Showroom", 500, 2500},
        {"Chavat Galli to PB Road",4000, 9000},
        {"Shetti Galli PB Road Cross",3000, 8500},
        {"Kotwal Galli Double Road",2000, 5500}}}
        },
        {"Bhavye Chowk",{
        {{"Bhavye Chowk",200, 1800},
        {"Darbar Galli Cross",2500, 6500},
        {"SamsunG Showroom", 500, 2500},
        {"Chavat Galli to PB Road",4000, 9000},
        {"Shetti Galli PB Road Cross",3000, 8500},
        {"Kotwal Galli Double Road",2000, 5500}}}
        },
        {"Darbar Galli Cross",{
        {{"Bhavye Chowk",200, 1800},
        {"Darbar Galli Cross",2500, 6500},
        {"SamsunG Showroom", 500, 2500},
        {"Chavat Galli to PB Road",4000, 9000},
        {"Shetti Galli PB Road Cross",3000, 8500},
        {"Kotwal Galli Double Road",2000, 5500}}}
        },
        {"Chavat Galli to PB Road",{
        {{"Bhavye Chowk",200, 1800},
        {"Darbar Galli Cross",2500, 6500},
        {"SamsunG Showroom", 500, 2500},
        {"Chavat Galli to PB Road",4000, 9000},
        {"Shetti Galli PB Road Cross",3000, 8500},
        {"Kotwal Galli Double Road",2000, 5500}}}
        },
        {"Shetti Galli PB Road Cross",{
        {{"Bhavye Chowk",200, 1800},
        {"Darbar Galli Cross",2500, 6500},
        {"SamsunG Showroom", 500, 2500},
        {"Chavat Galli to PB Road",4000, 9000},
        {"Shetti Galli PB Road Cross",3000, 8500},
        {"Kotwal Galli Double Road",2000, 5500}}}
        },

        {"Kaktives Road", {
        {{"Kaktives Road",300, 2000},
        {"Sardar High School Ground",1200, 3500},
        {"Konwal Galli Guest House",3500, 8000},
        {"Azad Galli",2000, 5500},
        {"Hospital Road",800, 3000},
        {"Tenginkeri Sheetal Hotel Cross",1600, 3300},
        {"Pai Hotel",1000, 3300},
        {"Old PB Road South Peripheral",3000, 8500}}}
        },
        {"Old PB Road South Peripheral", {
        {{"Kaktives Road",300, 2000},
        {"Sardar High School Ground",1200, 3500},
        {"Konwal Galli Guest House",3500, 8000},
        {"Azad Galli",2000, 5500},
        {"Hospital Road",800, 3000},
        {"Tenginkeri Sheetal Hotel Cross",1600, 3300},
        {"Pai Hotel",1000, 3300},
        {"Old PB Road South Peripheral",3000, 8500}}}
        },
        {"Azad Galli", {
        {{"Kaktives Road",300, 2000},
        {"Sardar High School Ground",1200, 3500},
        {"Konwal Galli Guest House",3500, 8000},
        {"Azad Galli",2000, 5500},
        {"Hospital Road",800, 3000},
        {"Tenginkeri Sheetal Hotel Cross",1600, 3300},
        {"Pai Hotel",1000, 3300},
        {"Old PB Road South Peripheral",3000, 8500}}}
        },
        {"Pai Hotel", {
        {{"Kaktives Road",300, 2000},
        {"Sardar High School Ground",1200, 3500},
        {"Konwal Galli Guest House",3500, 8000},
        {"Azad Galli",2000, 5500},
        {"Hospital Road",800, 3000},
        {"Tenginkeri Sheetal Hotel Cross",1600, 3300},
        {"Pai Hotel",1000, 3300},
        {"Old PB Road South Peripheral",3000, 8500}}}
        },
        {"Konwal Galli Guest House", {
        {{"Kaktives Road",300, 2000},
        {"Sardar High School Ground",1200, 3500},
        {"Konwal Galli Guest House",3500, 8000},
        {"Azad Galli",2000, 5500},
        {"Hospital Road",800, 3000},
        {"Tenginkeri Sheetal Hotel Cross",1600, 3300},
        {"Pai Hotel",1000, 3300},
        {"Old PB Road South Peripheral",3000, 8500}}}
        },
        {"Hospital Road", {
        {{"Kaktives Road",300, 2000},
        {"Sardar High School Ground",1200, 3500},
        {"Konwal Galli Guest House",3500, 8000},
        {"Azad Galli",2000, 5500},
        {"Hospital Road",800, 3000},
        {"Tenginkeri Sheetal Hotel Cross",1600, 3300},
        {"Pai Hotel",1000, 3300},
        {"Old PB Road South Peripheral",3000, 8500}}}
        },
        {"Motilal Circle",{
        {{"Motilal Circle", 300, 2000},
        {"Raviwar Peth Main Road", 1200, 3500},
        {"Hira Talkies", 3500, 8000},
        {"Ganpat Galli upto Hira Talkies", 1000, 3300},
        {"Kirloskar Road", 2000, 5500},
        {"Bata Showroom", 1200, 3500}}}
        },
        {"Raviwar Peth Main Road",{
        {{"Motilal Circle", 300, 2000},
        {"Raviwar Peth Main Road", 1200, 3500},
        {"Hira Talkies", 3500, 8000},
        {"Ganpat Galli upto Hira Talkies", 1000, 3300},
        {"Kirloskar Road", 2000, 5500},
        {"Bata Showroom", 1200, 3500}}}
        },
        {"Hira Talkies",{
        {{"Motilal Circle", 300, 2000},
        {"Raviwar Peth Main Road", 1200, 3500},
        {"Hira Talkies", 3500, 8000},
        {"Ganpat Galli upto Hira Talkies", 1000, 3300},
        {"Kirloskar Road", 2000, 5500},
        {"Bata Showroom", 1200, 3500}}}
        },
        {"Kirloskar Road",{
        {{"Motilal Circle", 300, 2000},
        {"Raviwar Peth Main Road", 1200, 3500},
        {"Hira Talkies", 3500, 8000},
        {"Ganpat Galli upto Hira Talkies", 1000, 3300},
        {"Kirloskar Road", 2000, 5500},
        {"Bata Showroom", 1200, 3500}}}
        },
        {"Adarsh Dress Circle",{
        {{"Ramdev Galli", 200, 1800},
        {"Adarsh Dress Circle", 500, 2500},
        {"SamsunG Showroom", 3000, 8500},
        {"Samadevi Galli", 1000, 3300},
        {"Gondhalli Galli", 1600, 4800},
        {"Gavli Galli", 800, 3000},
        {"Narvekar Gali", 2000, 5500}}}
        },
        {"Ramdev Galli",{
        {{"Ramdev Galli", 200, 1800},
        {"Adarsh Dress Circle", 500, 2500},
        {"SamsunG Showroom", 3000, 8500},
        {"Samadevi Galli", 1000, 3300},
        {"Gondhalli Galli", 1600, 4800},
        {"Gavli Galli", 800, 3000},
        {"Narvekar Gali", 2000, 5500}}}
        },
        {"Samadevi Galli",{
        {{"Ramdev Galli", 200, 1800},
        {"Adarsh Dress Circle", 500, 2500},
        {"SamsunG Showroom", 3000, 8500},
        {"Samadevi Galli", 1000, 3300},
        {"Gondhalli Galli", 1600, 4800},
        {"Gavli Galli", 800, 3000},
        {"Narvekar Gali", 2000, 5500}}}
        },
        {"Gondhalli Galli",{
        {{"Ramdev Galli", 200, 1800},
        {"Adarsh Dress Circle", 500, 2500},
        {"SamsunG Showroom", 3000, 8500},
        {"Samadevi Galli", 1000, 3300},
        {"Gondhalli Galli", 1600, 4800},
        {"Gavli Galli", 800, 3000},
        {"Narvekar Gali", 2000, 5500}}}
        },
        {"Gavli Galli",{
        {{"Ramdev Galli", 200, 1800},
        {"Adarsh Dress Circle", 500, 2500},
        {"SamsunG Showroom", 3000, 8500},
        {"Samadevi Galli", 1000, 3300},
        {"Gondhalli Galli", 1600, 4800},
        {"Gavli Galli", 800, 3000},
        {"Narvekar Gali", 2000, 5500}}}
        },
        {"Risaldar Galli",{
        {{"Risaldar Galli", 1200, 3500},
        {"Kalkundrikar Road", 500, 2500},
        {"Ganga Prabaha Hotel", 1200, 3500},
        {"Kirloskar Road", 1600, 4800},
        {"Bata Showroom", 800, 3000},
        {"Khade Bazar Police Station", 900, 3200},
        {"Shaniwar Khoot - Ganpat Galli", 2500, 6500},
        {"Hira Talkies Backside", 3000, 8500}}}
        },
        {"Kalkundrikar Road",{
        {{"Risaldar Galli", 1200, 3500},
        {"Kalkundrikar Road", 500, 2500},
        {"Ganga Prabaha Hotel", 1200, 3500},
        {"Kirloskar Road", 1600, 4800},
        {"Bata Showroom", 800, 3000},
        {"Khade Bazar Police Station", 900, 3200},
        {"Shaniwar Khoot - Ganpat Galli", 2500, 6500},
        {"Hira Talkies Backside", 3000, 8500}}}
        },
        {"Bata Showroom",{
        {{"Risaldar Galli", 1200, 3500},
        {"Kalkundrikar Road", 500, 2500},
        {"Ganga Prabaha Hotel", 1200, 3500},
        {"Kirloskar Road", 1600, 4800},
        {"Bata Showroom", 800, 3000},
        {"Khade Bazar Police Station", 900, 3200},
        {"Shaniwar Khoot - Ganpat Galli", 2500, 6500},
        {"Hira Talkies Backside", 3000, 8500}}}
        },
        {"Ganga Prabaha Hotel",{
        {{"Risaldar Galli", 1200, 3500},
        {"Kalkundrikar Road", 500, 2500},
        {"Ganga Prabaha Hotel", 1200, 3500},
        {"Kirloskar Road", 1600, 4800},
        {"Bata Showroom", 800, 3000},
        {"Khade Bazar Police Station", 900, 3200},
        {"Shaniwar Khoot - Ganpat Galli", 2500, 6500},
        {"Hira Talkies Backside", 3000, 8500}}}
        },
        {"Shaniwar Khoot - Ganpat Galli",{
        {{"Risaldar Galli", 1200, 3500},
        {"Kalkundrikar Road", 500, 2500},
        {"Ganga Prabaha Hotel", 1200, 3500},
        {"Kirloskar Road", 1600, 4800},
        {"Bata Showroom", 800, 3000},
        {"Khade Bazar Police Station", 900, 3200},
        {"Shaniwar Khoot - Ganpat Galli", 2500, 6500},
        {"Hira Talkies Backside", 3000, 8500}}}
        },
        {"Moksahi Galli",{
        {{"Moksahi Galli", 500, 2500},
        {"Bauxite Road", 3000, 8500},
        {"Bank of Maharashtra", 900, 3200},
        {"Nayaya Marg", 500, 2500},
        {"Vidyagiri", 800, 3000},
        {"Basav Colony", 1600, 4800},
        {"Shivbasav Nagar", 1200, 3500}}}
        },
        {"Bauxite Road",{
        {{"Moksahi Galli", 500, 2500},
        {"Bauxite Road", 3000, 8500},
        {"Bank of Maharashtra", 900, 3200},
        {"Nayaya Marg", 500, 2500},
        {"Vidyagiri", 800, 3000},
        {"Basav Colony", 1600, 4800},
        {"Shivbasav Nagar", 1200, 3500}}}
        },
        {"Bank of Maharashtra",{
        {{"Bauxite Road", 3000, 8500},
        {"Bank of Maharashtra", 900, 3200},
        {"Nayaya Marg", 500, 2500},
        {"Vidyagiri", 800, 3000},
        {"Basav Colony", 1600, 4800},
        {"Shivbasav Nagar", 1200, 3500}}}
        },
        {"Nayaya Marg",{
        {{"Moksahi Galli", 500, 2500},
        {"Bauxite Road", 3000, 8500},
        {"Bank of Maharashtra", 900, 3200},
        {"Nayaya Marg", 500, 2500},
        {"Vidyagiri", 800, 3000},
        {"Basav Colony", 1600, 4800},
        {"Shivbasav Nagar", 1200, 3500}}}
        },
        {"Vidyagiri",{
        {{"Bauxite Road", 3000, 8500},
        {"Bank of Maharashtra", 900, 3200},
        {"Nayaya Marg", 500, 2500},
        {"Vidyagiri", 800, 3000},
        {"Basav Colony", 1600, 4800},
        {"Shivbasav Nagar", 1200, 3500}}}
        },
        {"Basav Colony",{
        {{"Bauxite Road", 3000, 8500},
        {"Bank of Maharashtra", 900, 3200},
        {"Nayaya Marg", 500, 2500},
        {"Vidyagiri", 800, 3000},
        {"Basav Colony", 1600, 4800},
        {"Shivbasav Nagar", 1200, 3500}}}
        },
        {"Shivbasav Nagar",{
        {{"Bauxite Road", 3000, 8500},
        {"Bank of Maharashtra", 900, 3200},
        {"Nayaya Marg", 500, 2500},
        {"Vidyagiri", 800, 3000},
        {"Basav Colony", 1600, 4800},
        {"Shivbasav Nagar", 1200, 3500}}}
        },
        {"Kanakdas Circle",{
        {{"Bauxite Road", 200, 1800},
        {"Kanakdas Circle", 900, 3200},
        {"Shankam Hotel Cross", 800, 3000},
        {"Gandhi Nagar", 500, 2500},
        {"Shivterth Colony", 1000, 3300},
        {"Kanakdas Circle", 1200, 3500},
        {"KLE Compound", 3000, 8500},
        {"Jadhav Nagar", 1600, 4800}}}
        },
        {"Shankam Hotel Cross",{
        {{"Kanakdas Circle", 900, 3200},
        {"Shankam Hotel Cross", 800, 3000},
        {"Gandhi Nagar", 500, 2500},
        {"Shivterth Colony", 1000, 3300},
        {"Kanakdas Circle", 1200, 3500},
        {"KLE Compound", 3000, 8500},
        {"Jadhav Nagar", 1600, 4800}}}
        },
        {"Gandhi Nagar",{
        {{"Kanakdas Circle", 900, 3200},
        {"Shankam Hotel Cross", 800, 3000},
        {"Gandhi Nagar", 500, 2500},
        {"Shivterth Colony", 1000, 3300},
        {"Kanakdas Circle", 1200, 3500},
        {"Jadhav Nagar", 1600, 4800}}}
        },
        {"Shivterth Colony",{
        {{"Bauxite Road", 200, 1800},
        {"Kanakdas Circle", 900, 3200},
        {"Shankam Hotel Cross", 800, 3000},
        {"Gandhi Nagar", 500, 2500},
        {"Shivterth Colony", 1000, 3300},
        {"Kanakdas Circle", 1200, 3500},
        {"KLE Compound", 3000, 8500},
        {"Jadhav Nagar", 1600, 4800}}}
        },
        {"KLE Compound",{
        {{"Kanakdas Circle", 900, 3200},
        {"Shankam Hotel Cross", 800, 3000},
        {"Gandhi Nagar", 500, 2500},
        {"Shivterth Colony", 1000, 3300},
        {"Kanakdas Circle", 1200, 3500},
        {"KLE Compound", 3000, 8500},
        {"Jadhav Nagar", 1600, 4800}}}
        },
        {"Jadhav Nagar",{
        {{"Kanakdas Circle", 900, 3200},
        {"Shankam Hotel Cross", 800, 3000},
        {"Gandhi Nagar", 500, 2500},
        {"Shivterth Colony", 1000, 3300},
        {"Kanakdas Circle", 1200, 3500},
        {"KLE Compound", 3000, 8500},
        {"Jadhav Nagar", 1600, 4800}}}
        },

        {"Shivaji Garden",{
        {{"Shivaji Garden",500, 2500},
        {"Vandan Colony", 900, 3200},
        {"Vidyagiri", 1000, 3300},
        {"Bauxite Road", 800, 3000},
        {"Gandhinagar", 1200, 3500}}}
        },

        {"Vidyagiri",{
        {{"Vandan Colony", 900, 3200},
        {"Vidyagiri", 1000, 3300},
        {"Bauxite Road", 800, 3000},
        {"Gandhinagar", 1200, 3500}}}
        },

        {"Vandan Colony",{
        {{"Shivaji Garden",500, 2500},
        {"Vandan Colony", 900, 3200},
        {"Vidyagiri", 1000, 3300},
        {"Bauxite Road", 800, 3000},
        {"Gandhinagar", 1200, 3500}}}
        },

        {"Chennamma Circle",{
        {{"Chennamma Circle", 200, 1800},
        {"Rayanna Circle", 900, 3200},
        {"Keerti Hotel", 2000, 5500},
        {"Shetti Galli", 1200, 3500},
        {"Old PB Road", 3000, 8500},
        {"SamsunG Showroom", 800, 3000},
        {"Raviwar Peth Main Road", 1600, 4800}}}
        },

        {"Rayanna Circle",{
        {{"Rayanna Circle", 900, 3200},
        {"Keerti Hotel", 2000, 5500},
        {"Shetti Galli", 1200, 3500},
        {"Old PB Road", 3000, 8500},
        {"SamsunG Showroom", 800, 3000},
        {"Raviwar Peth Main Road", 1600, 4800},
        {"Shani Mandir", 500, 2500}}}
        },

        {"Keerti Hotel",{
        {{"Rayanna Circle", 900, 3200},
        {"Keerti Hotel", 2000, 5500},
        {"Shetti Galli", 1200, 3500},
        {"Old PB Road", 3000, 8500},
        {"Raviwar Peth Main Road", 1600, 4800}}}
        },

        {"Shetti Galli",{
        {{"Rayanna Circle", 900, 3200},
        {"Keerti Hotel", 2000, 5500},
        {"Shetti Galli", 1200, 3500},
        {"Old PB Road", 3000, 8500},
        {"SamsunG Showroom", 800, 3000},
        {"Raviwar Peth Main Road", 1600, 4800},
        {"Shani Mandir", 500, 2500}}}
        },

        {"Old PB Road",{
        {{"Rayanna Circle", 900, 3200},
        {"Keerti Hotel", 2000, 5500},
        {"Shetti Galli", 1200, 3500},
        {"Old PB Road", 3000, 8500},
        {"SamsunG Showroom", 800, 3000},
        {"Raviwar Peth Main Road", 1600, 4800}}}
        },

        {"SamsunG Showroom",{
        {{"Rayanna Circle", 900, 3200},
        {"Keerti Hotel", 2000, 5500},
        {"Shetti Galli", 1200, 3500},
        {"Old PB Road", 3000, 8500},
        {"SamsunG Showroom", 800, 3000},
        {"Raviwar Peth Main Road", 1600, 4800}}}
        },

        {"Raviwar Peth Main Road",{
        {{"Keerti Hotel", 2000, 5500},
        {"Shetti Galli", 1200, 3500},
        {"Old PB Road", 3000, 8500},
        {"Raviwar Peth Main Road", 1600, 4800}}}
        },

        {"Shivaji Nagar",{
        {{"Shivaji Nagar", 500, 2500},
        {"Sambhaji Circle", 900, 3200},
        {"Shivbasav Nagar", 1200, 3500},
        {"Ram Nagar", 2000, 5500},
        {"NCC Arts", 1000, 3300},
        {"Bharat Motor School", 3000, 8500},
        {"Jadhav Nagar", 1600, 4800}}}
        },

        {"Sambhaji Circle",{
        {{"Shivaji Nagar", 500, 2500},
        {"Sambhaji Circle", 900, 3200},
        {"Shivbasav Nagar", 1200, 3500},
        {"Ram Nagar", 2000, 5500},
        {"NCC Arts", 1000, 3300},
        {"Bharat Motor School", 3000, 8500},
        {"Jadhav Nagar", 1600, 4800}}}
        },

        {"Shivbasav Nagar",{
        {{"Shivbasav Nagar", 1200, 3500},
        {"Ram Nagar", 2000, 5500},
        {"NCC Arts", 1000, 3300},
        {"Bharat Motor School", 3000, 8500},
        {"Jadhav Nagar", 1600, 4800}}}
        },

        {"Ram Nagar",{
        {{"Sambhaji Circle", 900, 3200},
        {"Shivbasav Nagar", 1200, 3500},
        {"Ram Nagar", 2000, 5500},
        {"NCC Arts", 1000, 3300},
        {"Bharat Motor School", 3000, 8500},
        {"Jadhav Nagar", 1600, 4800}}}
        },

        {"NCC Arts",{
        {{"Shivbasav Nagar", 1200, 3500},
        {"Ram Nagar", 2000, 5500},
        {"Bharat Motor School", 3000, 8500},
        {"Jadhav Nagar", 1600, 4800}}}
        },

        {"Bharat Motor School",{
        {{"Sambhaji Circle", 900, 3200},
        {"Shivbasav Nagar", 1200, 3500},
        {"Ram Nagar", 2000, 5500},
        {"NCC Arts", 1000, 3300},
        {"Bharat Motor School", 3000, 8500},
        {"Jadhav Nagar", 1600, 4800}}}
        },

        {"Jadhav Nagar",{
        {{"Sambhaji Circle", 900, 3200},
        {"Shivbasav Nagar", 1200, 3500},
        {"Ram Nagar", 2000, 5500},
        {"NCC Arts", 1000, 3300},
        {"Bharat Motor School", 3000, 8500},
        {"Jadhav Nagar", 1600, 4800}}}
        },

        {"Sadashiv Nagar",{
        {{"Vengurla Road", 500, 2500},
        {"DC Bungalow Cross", 2000, 5500},
        {"Ambedkar Road", 900, 3200},
        {"Chennamma Circle - College Road", 1200, 3500},
        {"Vengurla Road - DC Bungalow", 1000, 3300},
        {"Rail Nagar South Cross", 3000, 8500}}}
        },

        {"Vengurla Road",{
        {{"Sadashiv Nagar", 200, 1800},
        {"Vengurla Road", 500, 2500},
        {"DC Bungalow Cross", 2000, 5500},
        {"Ambedkar Road", 900, 3200},
        {"Chennamma Circle - College Road", 1200, 3500},
        {"Vengurla Road - DC Bungalow", 1000, 3300},
        {"Rail Nagar South Cross", 3000, 8500}}}
        },

        {"DC Bungalow Cross",{
        {{"DC Bungalow Cross", 2000, 5500},
        {"Ambedkar Road", 900, 3200},
        {"Chennamma Circle - College Road", 1200, 3500},
        {"Vengurla Road - DC Bungalow", 1000, 3300},
        {"Rail Nagar South Cross", 3000, 8500}}}
        },

        {"Ambedkar Road",{
        {{"Sadashiv Nagar", 200, 1800},
        {"Vengurla Road", 500, 2500},
        {"DC Bungalow Cross", 2000, 5500},
        {"Ambedkar Road", 900, 3200},
        {"Chennamma Circle - College Road", 1200, 3500},
        {"Vengurla Road - DC Bungalow", 1000, 3300},
        {"Rail Nagar South Cross", 3000, 8500}}}
        },

        {"Chennamma Circle - College Road",{
        {{"DC Bungalow Cross", 2000, 5500},
        {"Ambedkar Road", 900, 3200},
        {"Chennamma Circle - College Road", 1200, 3500},
        {"Vengurla Road - DC Bungalow", 1000, 3300},
        {"Rail Nagar South Cross", 3000, 8500}}}
        },

        {"Vengurla Road - DC Bungalow",{
        {{"Vengurla Road", 500, 2500},
        {"DC Bungalow Cross", 2000, 5500},
        {"Ambedkar Road", 900, 3200},
        {"Chennamma Circle - College Road", 1200, 3500},
        {"Vengurla Road - DC Bungalow", 1000, 3300},
        {"Rail Nagar South Cross", 3000, 8500}}}
        },

        {"Rail Nagar South Cross",{
        {{"Vengurla Road", 500, 2500},
        {"DC Bungalow Cross", 2000, 5500},
        {"Ambedkar Road", 900, 3200},
        {"Chennamma Circle - College Road", 1200, 3500},
        {"Vengurla Road - DC Bungalow", 1000, 3300},
        {"Rail Nagar South Cross", 3000, 8500}}}
        }




        // You can define other areas similarly
    };

    // Display the areas in the selected zone
    displayAreas(selected_zone, zone_areas);

    // Ask the user to select an area
    cout << "\nEnter your choice (area number): ";
    int area_choice;
    cin >> area_choice;

    if (area_choice < 1 || area_choice > zone_areas[selected_zone].size()) {
        cout << "Invalid area choice" << endl;
        return 1;
    }

    // Get the name of the selected area
    string selected_area = zone_areas[selected_zone][area_choice - 1];
    cout << "You have selected " << selected_area << " as your area.\n";

    // Display the sub-division office and area details for the selected area
    displaySubDivisionDetails(selected_area, area_details);

    // Ask the user for their choice to find the nearest area
    cout << "\nEnter the Choice that you have selected for shortest distance: ";
    int user_choice;
    cin >> user_choice;

    string shortest_area = findShortestDistanceArea(area_details[selected_area].areas);
    cout << "You have selected " << shortest_area << " which is near to your location.\n";
    double outerDiameter, thickness;
    int segmentCount;
    string material;
    double density;

    // Select material
    cout << "Select material (polythene or steel): ";
    cin >> material;

    // Assign density based on material
    if (material == "polythene" || material == "Polythene") {
        density = 950; // kg/m^3 for polyethylene
    } else if (material == "steel" || material == "Steel") {
        density = 7850; // kg/m^3 for steel
    } else {
        cout << "Invalid material selected. Please choose 'polythene' or 'steel'." << endl;
        return 1;
    }

    // Input pipe specifications
    cout << "Enter the outer diameter of the pipe (in meters): ";
    cin >> outerDiameter;
    cout << "Enter the pipe wall thickness (in meters): ";
    cin >> thickness;

    // Input number of segments
    cout << "Enter the number of pipeline segments: ";
    cin >> segmentCount;

    vector<double> segmentLengths(segmentCount);
    double totalLength = 0.0;

    // Input lengths of each segment
    cout << "Enter the length of each segment (in meters):" << endl;
    for (int i = 0; i < segmentCount; i++) {
        cout << "Segment " << i + 1 << ": ";
        cin >> segmentLengths[i];
        totalLength += segmentLengths[i];
    }

    // Calculate total material volume and weight
    double totalVolume = 0.0;
    for (double length : segmentLengths) {
        totalVolume += calculatePipeVolume(length, outerDiameter, thickness);
    }
    double totalWeight = totalVolume * density;

    // Output results
    cout << "\nPipeline Material Usage Summary:" << endl;
    cout << "Material: " << material << endl;
    cout << "Total Length of Pipeline: " << totalLength << " meters" << endl;
    cout << "Total Material Volume: " << totalVolume << " cubic meters" << endl;
    cout << "Total Material Weight: " << totalWeight << " kilograms" << endl;
    string coatingType;


    double coatingThickness, coatingDensity;

    // Select coating type
    cout << "Select coating type (epoxy, polythene, plastic): ";
    cin >> coatingType;

    // Assign properties based on coating type
    if (coatingType == "epoxy") {
        coatingDensity = 1200; // kg/m³
        coatingThickness = 0.005; // 5 mm
    } else if (coatingType == "polythene") {
        coatingDensity = 950; // kg/m³
        coatingThickness = 0.01; // 10 mm
    } else if (coatingType == "plastic") {
        coatingDensity = 1050; // kg/m³
        coatingThickness = 0.008; // 8 mm
    } else {
        cout << "Invalid coating type. Please choose 'epoxy', 'polythene', or 'plastic'." << endl;
        return 1;
    }

    // Input pipe specifications
    cout << "Enter the outer diameter of the pipe (in meters): ";
    cin >> outerDiameter;

    // Input number of pipeline segments
    cout << "Enter the number of pipeline segments: ";
    cin >> segmentCount;



    // Input lengths of each segment
    cout << "Enter the length of each segment (in meters):" << endl;
    for (int i = 0; i < segmentCount; i++) {
        cout << "Segment " << i + 1 << ": ";
        cin >> segmentLengths[i];
        totalLength += segmentLengths[i];
    }

    // Calculate total coating area and weight
    double totalSurfaceArea = 0.0;
    for (double length : segmentLengths) {
        totalSurfaceArea += calculateSurfaceArea(length, outerDiameter);
    }
    double coatingVolume = totalSurfaceArea * coatingThickness;
    double coatingWeight = coatingVolume * coatingDensity;

    // Output results
    cout << "\nCoating Material Usage Summary:" << endl;
    cout << "Coating Type: " << coatingType << endl;
    cout << "Total Length of Pipeline: " << totalLength << " meters" << endl;
    cout << "Total Surface Area: " << totalSurfaceArea << " square meters" << endl;
    cout << "Total Coating Volume: " << coatingVolume << " cubic meters" << endl;
    cout << "Total Coating Weight: " << coatingWeight << " kilograms" << endl;
    double pressure; // Variable to store the pressure in the pipeline

    // Input the pressure value
    cout << "Enter the pressure in the pipeline (in PSI): ";
    cin >> pressure;

    // Validate input
    if (pressure < 0)
    {
        cout << "Pressure cannot be negative. Please enter a valid value." << endl;
        return 1;
    }

    // Determine and display the pressure category
    string category = categorizePressure(pressure);
    cout << "The pipeline pressure is categorized as: " << category << endl;

 // Define safety thresholds
    const float pressureThreshold = 100.0;   // Pressure threshold in bar
    const float temperatureThreshold = 60.0; // Temperature threshold in °C
    const float leakThreshold = 5.0;         // Sensor reading threshold for leak detection

    // Input parameters
    float  temperature, sensorReading;

    // Gather input from the user
    cout << "Enter pipeline pressure (in bar): ";
    cin >> pressure;

    cout << "Enter pipeline temperature (in °C): ";
    cin >> temperature;

    cout << "Enter gas sensor reading: ";
    cin >> sensorReading;

    // Check pipeline safety
    bool isSafe = true;

    if (pressure > pressureThreshold) {
        cout << "Warning: Pressure exceeds safe limit! Current pressure: " << pressure << " bar" << endl;
        isSafe = false;
    }

    if (temperature > temperatureThreshold) {
        cout << "Warning: Temperature exceeds safe limit! Current temperature: " << temperature << " °C" << endl;
        isSafe = false;
    }

    // Leak detection
    if (sensorReading > leakThreshold) {
        cout << "Warning: Gas leak detected! Sensor reading: " << sensorReading << endl;
        isSafe = false;
    }

    // Final safety status
    if (isSafe) {
        cout << "The pipeline is operating within safe limits." << endl;
    } else {
        cout << "Pipeline safety compromised! Take immediate action!" << endl;
    }

     // Variables to hold user inputs
    float unitsUsed, ratePerUnit;

    // Gather input from the user
    cout << "Enter the number of gas units used: ";
    cin >> unitsUsed;

    cout << "Enter the rate per unit (in rupees): ";
    cin >> ratePerUnit;

    // Calculate bills
    float monthlyBill = unitsUsed * ratePerUnit;
    float quarterlyBill = monthlyBill * 3; // Quarterly means 3 months
    float yearlyBill = monthlyBill * 12;  // Yearly means 12 months

    // Display the results
    cout << "Monthly bill: " << monthlyBill << " rupees" << endl;
    cout << "Quarterly bill: " << quarterlyBill << " rupees" << endl;
    cout << "Yearly bill: " << yearlyBill << " rupees" << endl;



// Variables to hold user inputs
    float gasBill, taxRate, totalBill;
    string dueDate, paymentStatus;

    // Gather input from the user
    cout << "Enter the gas bill amount (in rupees): ";
    cin >> gasBill;

    cout << "Enter the tax rate (in percentage): ";
    cin >> taxRate;

    cout << "Enter the due date (e.g., 10-Jan-2025): ";
    cin >> dueDate;

    cout << "Has the bill been paid? (yes/no): ";
    cin >> paymentStatus;

    // Calculate total bill with tax
    float taxAmount = (gasBill * taxRate) / 100;
    totalBill = gasBill + taxAmount;

    // Display the total bill
    cout << "Base gas bill: " << gasBill << " rupees" << endl;
    cout << "Tax (" << taxRate << "%): " << taxAmount << " rupees" << endl;
    cout << "Total bill amount: " << totalBill << " rupees" << endl;

    // Check payment status
    if (paymentStatus == "yes") {
        cout << "Thank you! The bill has been paid on time." << endl;
    } else {
        cout << "The bill has not been paid. Due date was: " << dueDate << endl;
        cout << "Please pay the bill immediately to avoid penalties." << endl;
    }
    int eastHomes, westHomes, northHomes, southHomes;
    int eastUsage, westUsage, northUsage, southUsage;
    long long eastTotal, westTotal, northTotal, southTotal, grandTotal;

    // Input for the East zone
    cout << "Enter the number of homes in the East zone: ";
    cin >> eastHomes;
    cout << "Enter the average gas usage per home in the East zone (in units): ";
    cin >> eastUsage;

    // Input for the West zone
    cout << "Enter the number of homes in the West zone: ";
    cin >> westHomes;
    cout << "Enter the average gas usage per home in the West zone (in units): ";
    cin >> westUsage;

    // Input for the North zone
    cout << "Enter the number of homes in the North zone: ";
    cin >> northHomes;
    cout << "Enter the average gas usage per home in the North zone (in units): ";
    cin >> northUsage;

    // Input for the South zone
    cout << "Enter the number of homes in the South zone: ";
    cin >> southHomes;
    cout << "Enter the average gas usage per home in the South zone (in units): ";
    cin >> southUsage;

    // Calculate total usage for each zone
    eastTotal = static_cast<long long>(eastHomes) * eastUsage;
    westTotal = static_cast<long long>(westHomes) * westUsage;
    northTotal = static_cast<long long>(northHomes) * northUsage;
    southTotal = static_cast<long long>(southHomes) * southUsage;

    // Calculate the grand total
    grandTotal = eastTotal + westTotal + northTotal + southTotal;

    // Display the results
    cout << "\nTotal gas usage by zones:";
    cout << "\nEast zone: " << eastTotal << " units";
    cout << "\nWest zone: " << westTotal << " units";
    cout << "\nNorth zone: " << northTotal << " units";
    cout << "\nSouth zone: " << southTotal << " units";
    cout << "\n\nGrand Total gas usage across all zones: " << grandTotal << " units" << endl;

     // Variables for leak detection system parameters
    double monitoredPressure, maop, distanceFromStructures;
    string leakDetectionMethod, emergencyValveStatus;

    // Input parameters for leak detection system
    cout << "Enter the monitored pressure of the pipeline (in bar): ";
    cin >> monitoredPressure;
    cout << "Enter the Maximum Allowable Operating Pressure (MAOP) (in bar): ";
    cin >> maop;
    cout << "Enter the distance from other structures (in meters): ";
    cin >> distanceFromStructures;
    cout << "Enter the leak detection method used (e.g., Pressure Monitoring, Acoustic Sensors, Odorants): ";
    cin.ignore(); // Clear input buffer
    getline(cin, leakDetectionMethod);
    cout << "Is the emergency shutoff valve functional? (Yes/No): ";
    getline(cin, emergencyValveStatus);

    // Display the entered parameters
    cout << "\nGas Pipeline Leak Detection System Parameters:" << endl;
    cout << "-----------------------------------------------" << endl;
    cout << "Monitored Pressure: " << monitoredPressure << " bar" << endl;
    cout << "Maximum Allowable Operating Pressure (MAOP): " << maop << " bar" << endl;
    cout << "Distance from Other Structures: " << distanceFromStructures << " meters" << endl;
    cout << "Leak Detection Method: " << leakDetectionMethod << endl;
    cout << "Emergency Shutoff Valve Functional: " << emergencyValveStatus << endl;

    // Warning for exceeding MAOP
    if (monitoredPressure > maop) {
        cout << "\nWARNING: Monitored pressure exceeds MAOP! Immediate action required." << endl;
    }

    // Variables for geotechnical parameters
    string soilType, seismicActivityZone, terrainType;
    double waterTableLevel;

    // Input parameters
    cout << "Enter the soil type (e.g., Sandy, Clay, Rocky): ";
    getline(cin, soilType);
    cout << "Enter the seismic activity zone (e.g., Low, Moderate, High): ";
    getline(cin, seismicActivityZone);
    cout << "Enter the water table level (in meters): ";
    cin >> waterTableLevel;
    cin.ignore(); // Clear input buffer
    cout << "Enter the terrain type (e.g., Flat, Hilly, Mountainous): ";
    getline(cin, terrainType);

    // Display the entered parameters
    cout << "\nGeotechnical Parameters for Gas Pipeline System:" << endl;
    cout << "-----------------------------------------------" << endl;
    cout << "Soil Type: " << soilType << endl;
    cout << "Seismic Activity Zone: " << seismicActivityZone << endl;
    cout << "Water Table Level: " << waterTableLevel << " meters" << endl;
    cout << "Terrain Type: " << terrainType << endl;

    // Additional considerations based on inputs
    if (waterTableLevel < 1.5) {
        cout << "\nNOTE: High water table level detected. Additional corrosion protection may be required." << endl;
    }

    if (seismicActivityZone == "High")
    {
        cout << "WARNING: High seismic activity zone. Flexible pipeline design recommended." << endl;
    }

    if (terrainType == "Mountainous")
    {
        cout << "CAUTION: Mountainous terrain detected. Advanced stabilization methods may be necessary." << endl;
    }

     // Variables for environmental parameters
    double tempFluctuation, rainfall, snowDepth;
    string proximityToWaterBodies, landUse;

    // Input parameters
    cout << "Enter the temperature fluctuation (in degrees Celsius): ";
    cin >> tempFluctuation;
    cout << "Enter the annual rainfall (in mm): ";
    cin >> rainfall;
    cout << "Enter the snow depth during winter (in cm): ";
    cin >> snowDepth;
    cin.ignore(); // Clear input buffer
    cout << "Enter the proximity to water bodies (e.g., Close, Moderate, Far): ";
    getline(cin, proximityToWaterBodies);
    cout << "Enter the type of land use (e.g., Agricultural, Urban, Industrial): ";
    getline(cin, landUse);


    // Display the entered parameters
    cout << "\nEnvironmental Parameters for Gas Pipeline System:" << endl;
    cout << "-------------------------------------------------" << endl;
    cout << "Temperature Fluctuation: " << tempFluctuation << " °C" << endl;
    cout << "Annual Rainfall: " << rainfall << " mm" << endl;
    cout << "Snow Depth: " << snowDepth << " cm" << endl;
    cout << "Proximity to Water Bodies: " << proximityToWaterBodies << endl;
    cout << "Land Use: " << landUse << endl;


    // Additional considerations based on inputs
    if (tempFluctuation > 30)
    {
        cout << "\nNOTE: High temperature fluctuations detected. Consider thermal expansion measures." << endl;
    }

    if (proximityToWaterBodies == "Close")
    {
        cout << "CAUTION: Close proximity to water bodies. Ensure measures to prevent contamination." << endl;
    }

    if (landUse == "Agricultural")
    {
        cout << "ADVICE: Agricultural land detected. Take precautions to avoid disrupting farming activities." << endl;
    }
 // Variables for maintenance and inspection parameters
    string inspectionFrequency, repairMethods;
    int lifespan;

    // Input parameters
    cout << "Enter the inspection frequency (e.g., Monthly, Quarterly, Annually): ";
    getline(cin, inspectionFrequency);
    cout << "Enter the repair methods used (e.g., Welding, Clamp Repairs, Section Replacement): ";
    getline(cin, repairMethods);
    cout << "Enter the expected lifespan of the pipeline (in years): ";
    cin >> lifespan;

     // Display the entered parameters
    cout << "\nMaintenance and Inspection Parameters for Gas Pipeline System:" << endl;
    cout << "-------------------------------------------------------------" << endl;
    cout << "Inspection Frequency: " << inspectionFrequency << endl;
    cout << "Repair Methods: " << repairMethods << endl;
    cout << "Expected Lifespan: " << lifespan << " years" << endl;

    // Additional suggestions based on inputs
    if (inspectionFrequency == "Annually")
    {
        cout << "\nNOTE: Annual inspections may not be sufficient for high-risk areas. Consider more frequent checks." << endl;
    }

    if (lifespan < 20)
    {
        cout << "ADVICE: Short lifespan detected. Ensure regular maintenance and timely rehabilitation planning." << endl;
    }

    // Variables for regulatory and compliance parameters
    string standards, permits, odorization;

    // Input parameters
    cout << "Enter the standards and codes followed (e.g., ASME B31.8, ISO 9001): ";
    getline(cin, standards);
    cout << "Enter the status of permits and approvals (e.g., Approved, Pending): ";
    getline(cin, permits);
    cout << "Is odorization required? (Yes/No): ";
    getline(cin, odorization);

    // Display the entered parameters
    cout << "\nRegulatory and Compliance Parameters for Gas Pipeline System:" << endl;
    cout << "------------------------------------------------------------" << endl;
    cout << "Standards and Codes: " << standards << endl;
    cout << "Permits and Approvals: " << permits << endl;
    cout << "Odorization Requirement: " << odorization << endl;


    // Additional compliance checks
    if (permits == "Pending")
    {
        cout << "\nWARNING: Permits and approvals are pending. Ensure compliance before operation." << endl;
    }

    if (odorization == "No")
    {
        cout << "NOTE: Odorization is not enabled. Ensure alternative leak detection methods are in place." << endl;
    }
    // Variables for operational parameters
    string controlSystem, pressureRegulatingStation, meteringStation;

    // Input parameters
    cout << "Enter the control system used (e.g., SCADA, DCS): ";
    getline(cin, controlSystem);
    cout << "Enter the pressure regulating station details (e.g., Located at key points, Automated, Manual): ";
    getline(cin, pressureRegulatingStation);
    cout << "Enter the metering station details (e.g., Flow meters, Usage meters, Installed at intervals): ";
    getline(cin, meteringStation);

    // Display the entered parameters
    cout << "\nOperational Parameters for Gas Pipeline System:" << endl;
    cout << "-------------------------------------------------" << endl;
    cout << "Control System: " << controlSystem << endl;
    cout << "Pressure Regulating Station: " << pressureRegulatingStation << endl;
    cout << "Metering Station: " << meteringStation << endl;

    // Additional suggestions or checks based on inputs
    if (controlSystem == "SCADA")
    {
        cout << "\nNOTE: SCADA system detected. Ensure proper cybersecurity measures are in place for remote monitoring." << endl;
    }

    if (pressureRegulatingStation == "Manual")
    {
        cout << "WARNING: Manual pressure regulation detected. Consider automation for better control and efficiency." << endl;
    }

    if (meteringStation == "Installed at intervals")
    {
        cout << "ADVICE: Ensure metering stations are installed at regular intervals to maintain accurate usage data." << endl;
    }

    // Variables for risk assessment parameters
    string risks, hazardZone, integrityProgram;

    // Input parameters
    cout << "Enter potential risks (e.g., Leaks, Explosions, External Interference): ";
    getline(cin, risks);
    cout << "Enter the hazard zones (e.g., High Risk Areas, Earthquake-Prone Zones, Flood Zones): ";
    getline(cin, hazardZone);
    cout << "Enter the pipeline integrity management program (e.g., Regular Inspections, Cathodic Protection): ";
    getline(cin, integrityProgram);

     // Display the entered parameters
    cout << "\nRisk Assessment for Gas Pipeline System:" << endl;
    cout << "-----------------------------------------" << endl;
    cout << "Potential Risks: " << risks << endl;
    cout << "Hazard Zones: " << hazardZone << endl;
    cout << "Pipeline Integrity Management Program: " << integrityProgram << endl;


      // Additional risk management suggestions based on input
    if (risks.find("Leaks") != string::npos)
    {
        cout << "\nNOTE: Ensure effective leak detection systems are in place (e.g., sensors, pressure monitoring)." << endl;
    }

    if (hazardZone.find("Earthquake-Prone Zones") != string::npos)
    {
        cout << "ADVICE: Consider flexible pipeline designs and additional seismic protection measures." << endl;
    }

    if (integrityProgram.find("Cathodic Protection") != string::npos)
    {
        cout << "ADVICE: Ensure regular maintenance and checks of cathodic protection systems to prevent corrosion." << endl;
    }



    return 0;
}



// Pipeline class extended to include more details and additional methods
class ElectricityLine
{
public:
    int length; // in meters
    int capacity; // in kilowatts
    string material; // Copper, Aluminum, etc.
    double voltage; // in volts
    double current; // in amperes
    string status; // Active, Inactive, Under Maintenance
    string maintenance_schedule;
    double cost; // Cost of the electricity line in currency
    string fault_detection_type; // Fault detection type (Thermal Imaging or Electrical Testing)

    ElectricityLine(int l, int c, string m, double v, double cur, string s, string ms, double cost, string fdt)
        : length(l),
          capacity(c),
          material(m),
          voltage(v),
          current(cur),
          status(s),
          maintenance_schedule(ms),
          cost(cost),
          fault_detection_type(fdt) {}

    void display()
    {
        cout << "\nElectricity Line Details: Length = " << length << " meters, Capacity = " << capacity
             << " kW, Material = " << material << ", Voltage = " << voltage
             << " V, Current = " << current << " A, Status = " << status
             << ", Maintenance Schedule = " << maintenance_schedule << ", Cost = " << cost
             << ", Fault Detection Type = " << fault_detection_type << endl;
    }

    void updateMaintenanceSchedule(string newSchedule)
    {
        maintenance_schedule = newSchedule;
        cout << "Maintenance schedule updated to: " << newSchedule << endl;
    }
};

// Customer class with multiple electricity lines and usage history

class Customer
{
public:
    string name;
    string address;
    string customer_id;
    string location; // Customer's location to calculate distance
    string connection_type; // Residential, Commercial
    string billing_cycle; // Monthly, Quarterly, Weekly
    double total_usage; // Total electricity usage during billing cycle
    double total_amount; // Total amount to be paid
    vector<ElectricityLine> electricity_lines; // A customer may have multiple electricity lines
    vector<string> usage_history; // History of electricity usage and billing information

    Customer(string n, string addr, string id, string loc, string conn, string cycle, double usage, double amount)
        : name(n),
          address(addr),
          customer_id(id),
          location(loc),
          connection_type(conn),
          billing_cycle(cycle),
          total_usage(usage),
          total_amount(amount) {}

    void display()
    {
        cout << "\nCustomer Details: \nName: " << name << "\nAddress: " << address
             << "\nCustomer ID: " << customer_id << "\nLocation: " << location
             << "\nConnection Type: " << connection_type << "\nBilling Cycle: " << billing_cycle
             << "\nTotal Electricity Usage: " << total_usage << "\nTotal Amount: " << total_amount << endl;

        cout << "\nElectricity Line Details: " << endl;
        for (auto &line : electricity_lines)
        {
            line.display();
        }

        cout << "\nUsage History: " << endl;
        for (const string &record : usage_history)
        {
            cout << record << endl;
        }
    }

    void addElectricityLine(ElectricityLine e)
    {
        electricity_lines.push_back(e);
        cout << "New electricity line added for " << name << endl;
    }

    void addUsageRecord(string record)
    {
        usage_history.push_back(record);
        cout << "Usage record added: " << record << endl;
    }
};

// ** Start of Pseudocode Section **

// 1. Initialize necessary variables for the program
//    - Variables for storing user input, results, and temporary calculations
//    - Example: int num1, num2, result;

// 2. Display a menu or options to the user
//    - Prompt the user to choose between different actions (e.g., addition, subtraction, exit)
//    - Example: cout << "Enter 1 for addition, 2 for subtraction, 3 to exit";

// 3. Read the user's input
//    - Accept the user’s choice from the menu (e.g., which operation to perform)
//    - Example: cin >> choice;

// 4. Use a decision structure (e.g., switch or if-else) to handle the user's choice
//    - If the user chooses an option, execute the corresponding block of code
//    - Example:
//      switch(choice) {
//          case 1:
//              // Perform addition
//              break;
//          case 2:
//              // Perform subtraction
//              break;
//          default:
//              // Handle invalid input
//              break;
//      }

// 5. For each case or action, do the following:
//    - Collect additional inputs as needed (e.g., numbers for operations)
//    - Perform the requested operation
//    - Output the result to the user
//    - Example:
//        cout << "Enter two numbers:";
//        cin >> num1 >> num2;
//        result = num1 + num2;
//        cout << "Result: " << result;





// Graph to store the network of pump stations and areas

class Graph
{
public:
    map<string, vector<pair<string, int>>> adj; // stores the adjacency list, with distances as weights

    void addEdge(string u, string v, int distance)
    {
        adj[u].push_back(make_pair(v, distance));
        adj[v].push_back(make_pair(u, distance)); // Assuming it's undirected
    }

    map<string, int> dijkstra(string source)
    {
        map<string, int> dist;
        for (auto &node : adj)
        {
            dist[node.first] = INT_MAX;
        }
        dist[source] = 0;

        priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> pq;
        pq.push(make_pair(0, source));

        while (!pq.empty())
        {
            int u_dist = pq.top().first;
            string u = pq.top().second;
            pq.pop();

            if (u_dist > dist[u])
                continue;

            for (auto &neighbor : adj[u])
            {
                string v = neighbor.first;
                int weight = neighbor.second;

                if (dist[u] + weight < dist[v])
                {
                    dist[v] = dist[u] + weight;
                    pq.push(make_pair(dist[v], v));
                }
            }
        }
        return dist;
    }

    int getShortestDistanceToSubstation(string customerLocation)
    {
        map<string, int> distances = dijkstra(customerLocation);

        int minDistance = INT_MAX;

        // 6. Optionally handle edge cases
//    - Example: If the user inputs an invalid choice or wrong data types, display an error message
//    - Example:
//        if (choice < 1 || choice > 3) {
//            cout << "Invalid option. Please try again.";
//        }

// 7. Repeat the process until the user chooses to exit the program
//    - Example: Use a loop (e.g., while or do-while) to allow the user to perform multiple operations until they select exit

// 8. Exit the program gracefully after the user finishes
//    - Example: cout << "Exiting program..."; return 0;

// ** End of Pseudocode Section **
        for (auto &d : distances)
        {
            if (d.first != customerLocation && d.second < minDistance)
            {
                minDistance = d.second;
            }
        }
        return (minDistance == INT_MAX) ? -1 : minDistance;
    }
};


// Display menu with expanded options

void displayMenu()
{
    cout << "\n\nWelcome to the City Electricity Corporation\n";
    cout << "Please choose an option: \n";
    cout << "1. Choose Material Type of Line\n";
    cout << "2. Choose Billing Type\n";
    cout << "3. Choose Fault Detection Type\n";
    cout << "4. Choose Connection Type\n";
    cout << "5. View Electricity Line Details\n";
    cout << "6. View Customer Details\n";
    cout << "7. Finalize Selections\n";
    cout << "8. View Total Installation Cost\n";
    cout << "9. Update Maintenance Schedule\n";
    cout << "10. Add New Electricity Line\n";
    cout << "11. Exit\n";
}
int main() {
    string name, address, customerID, location, connectionType, material, billingCycle, faultDetectionType;
    double totalUsage = 0.0, totalAmount = 0.0;

    // Material rates (cost per meter)
    map<string, double> materialRates = {
        {"Copper", 150.0},   // Copper costs 150 currency per meter
        {"Aluminum", 100.0} // Aluminum costs 100 currency per meter
    };

    // Fault detection options
    map<string, string> faultDetectionOptions = {
        {"1", "Thermal Imaging"},
        {"2", "Electrical Testing"}
    };

    // Connection types and pricing
    map<string, map<string, double>> connectionPricing = {
        {"Residential", {{"Monthly", 1000}, {"Quarterly", 2500}, {"Weekly", 400}}},
        {"Commercial", {{"Monthly", 3000}, {"Quarterly", 7500}, {"Weekly", 1200}}}
    };

    // Customer information
    cout << "Enter Customer Name: ";
    getline(cin, name);

    cout << "Enter Customer Address: ";
    getline(cin, address);

    cout << "Enter Customer ID: ";
    getline(cin, customerID);

    cout << "Enter Customer Location: ";
    getline(cin, location);

    Customer customer(name, address, customerID, location, "", "", 0.0, 0.0);

    // 4. Use a decision structure (e.g., switch or if-else) to handle the user's choice
//    - If the user chooses an option, execute the corresponding block of code
//    - Example:
//      switch(choice) {
//          case 1:
//              // Perform addition
//              break;
//          case 2:
//              // Perform subtraction
//              break;
//          default:
//              // Handle invalid input
//              break;
//      }

// 5. For each case or action, do the following:
//    - Collect additional inputs as needed (e.g., numbers for operations)
//    - Perform the requested operation
//    - Output the result to the user
//    - Example:
//        cout << "Enter two numbers:";
//        cin >> num1 >> num2;
//        result = num1 + num2;
//        cout << "Result: " << result;

// 6. Optionally handle edge cases
//    - Example: If the user inputs an invalid choice or wrong data types, display an error message
//    - Example:
//        if (choice < 1 || choice > 3) {
//            cout << "Invalid option. Please try again.";
//        }
    // Creating the graph (network of pump stations)

    Graph g;

    g.addEdge("Shaniwar Khoot", "Khanjar Galli", 500);
    g.addEdge("Shaniwar Khoot", "Green Taj", 700);
    g.addEdge("Khade Bazar", "Kaktives Road", 300);
    g.addEdge("Topi Galli", "Bhavye Chowk", 1000);
    g.addEdge("Shivaji Nagar", "Sadashiv Nagar", 800);
    g.addEdge("Tilakwadi", "Maratha Colony", 1600);
    g.addEdge("Tilakwadi", "Mangalwar Peth", 1300);
    g.addEdge("Tilakwadi", "Guruwar Peth", 1200);
    g.addEdge("Tilakwadi", "Khanapu Road", 1000);
    g.addEdge("Tilakwadi", "Hindu Nagar", 850);
    g.addEdge("Tilakwadi", "Budhawar Peth", 1400);
    g.addEdge("Tilakwadi", "Deshmukh Road", 1300);
    g.addEdge("Tilakwadi", "Somawar Peth", 1300);
    g.addEdge("Tilakwadi", "Shukrawar Peth", 1700);
    g.addEdge("Udyambag", "Angol Industrial Estate", 1300);
    g.addEdge("Udyambag", "Parvati Nagar", 1200);
    g.addEdge("Udyambag", "Kle college road", 1400);
    g.addEdge("Udyambag", "Panjim-Belagavi Road", 800);
    g.addEdge("Udyambag", "Subhas Chandra Nagar", 1700);
    g.addEdge("Udyambag", "Kalameshwar Housing Colony", 1200);
    g.addEdge("Udyambag", "Angol", 1500);
    g.addEdge("Udyambag", "Sbi colony", 1400);
    g.addEdge("Angol", "Bhagya Nagar", 1000);
    g.addEdge("Angol", "Hindwadi", 700);
    g.addEdge("Angol", "Omkar Nagar", 900);
    g.addEdge("Angol", "Adarsh Nagar", 1200);
    g.addEdge("Angol", "Anand Nagar", 1300);
    g.addEdge("Angol", "Ambedkar Nagar", 1100);
    g.addEdge("Chenamma Circle", "Neharu Nagar", 750);
    g.addEdge("Chenamma Circle", "Ashok Nagar", 600);
    g.addEdge("Chenamma Circle", "Shivabasav Nagar", 1200);
    g.addEdge("Chenamma Circle", "Ayodhya Nagar", 1050);
    g.addEdge("Chenamma Circle", "Ramdev", 900);
    g.addEdge("Chenamma Circle", "RLS", 500);
    g.addEdge("Mahantesh Nagar", "Revenue Colony", 1000);
    g.addEdge("Mahantesh Nagar", "Shivatirtha Colony", 900);
    g.addEdge("Mahantesh Nagar", "Rukmini Nagar", 650);
    g.addEdge("Mahantesh Nagar", "Shree Nagar Garden", 800);
    g.addEdge("Mahantesh Nagar", "Malini Nagar", 1200);
    g.addEdge("Mahantesh Nagar", "Ramtirtha Nagar", 1500);
    g.addEdge("Shahu Nagar", "Vaibhav Nagar", 1600);
    g.addEdge("Shahu Nagar", "Basav Colony", 1300);
    g.addEdge("Shahu Nagar", "Sai Colony", 500);
    g.addEdge("Shahu Nagar", "Bauxite Road", 700);
    g.addEdge("Shahu Nagar", "Vandan Colony", 1200);
    g.addEdge("Shahu Nagar", "Kalmeshwar Nagar", 1000);
    g.addEdge("Shahu Nagar", "Kangrali", 900);
    g.addEdge("Raviwar Peth", "Motilal Circle", 600);
    g.addEdge("Raviwar Peth", "Samadevi Galli", 800);
    g.addEdge("Tilakwadi", "Nanawadi", 500);
    g.addEdge("Tilakwadi", "Shahapur", 1000);
    g.addEdge("Udayambag", "Majagaon", 1400);
    g.addEdge("Khade Bazar", "Gandhi Nagar", 1500);
    g.addEdge("Neharu Nagar", "Mahantesh Nagar", 1300);
    g.addEdge("Mahantesh nagar", "Gandhi Nagar", 800);
    g.addEdge("Udayambag", "Piranwadi", 1800);
    g.addEdge("Mahantesh Nagar", "Kanabargi", 900);
    g.addEdge("Hanuman Nagar", "Sadashiv Nagar", 750);
    g.addEdge("Sahyadri Nagar", "Hanuman Nagar", 900);
    g.addEdge("Mahantesh Nagar", "Anjaneya Nagar", 600);
    g.addEdge("Tilakwadi", "RPD", 550);
    g.addEdge("Gandhi Nagar", "Pai Hotel", 600);
    g.addEdge("Hanuman Nagar", "Anjaneya Nagar", 1200);
    g.addEdge("Anjaneya Nagar", "Kanabargi", 750);
    g.addEdge("Shahapur", "Udayambag", 900);
    g.addEdge("Kakar Galli", "Tilak Chowk", 1400);
    g.addEdge("Sardar High School", "Topi Galli", 1300);
    g.addEdge("Azad Galli", "Samadevi Galli", 850);
    g.addEdge("Vidyagiri", "Motilal Circle", 650);
    g.addEdge("Kanakdas Circle", "Shani Mandir", 1000);
    g.addEdge("Rayanna Circle", "Sambhaji Circle", 300);
    g.addEdge("Shivaji Nagar", "Ganpat Galli", 500);
    g.addEdge("Govt. Hospital", "Court Compound", 200);



    // Additional edges omitted for brevity...

    cout << "\nCalculating shortest distance from your location to the nearest substation...\n";
    int shortestDistance = g.getShortestDistanceToSubstation(location);

    if (shortestDistance == INT_MAX) {
        cout << "No substation found near your location.\n";
        return 1;
    } else {
        cout << "The shortest distance to the nearest substation is: " << shortestDistance << " meters.\n";
    }

    ElectricityLine electricityLine(shortestDistance, 50, "Copper", 220.0, 10.0, "Active", "Monthly", 0.0, "");

    int choice;
    bool exitMenu = false, materialSelected = false, billingSelected = false, faultDetectionSelected = false, connectionTypeSelected = false;

    while (!exitMenu) {
        cout << "\nMenu:\n1. Choose Material Type\n2. Choose Billing Cycle\n3. Choose Fault Detection Type\n4. Choose Connection Type\n5. View Electricity Line Details\n6. View Customer Details\n7. Finalize Selections\n8. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                cout << "\nChoose Material Type (1. Copper, 2. Aluminum): ";
                int materialChoice;
                cin >> materialChoice;

                if (materialChoice == 1) {
                    material = "Copper";
                    electricityLine.material = "Copper";
                } else if (materialChoice == 2) {
                    material = "Aluminum";
                    electricityLine.material = "Aluminum";
                } else {
                    cout << "Invalid choice.\n";
                    continue;
                }
                materialSelected = true;
                cout << "You selected " << material << " as the material.\n";
                break;
            }

            case 2: {
                cout << "\nChoose Billing Cycle (1. Monthly, 2. Quarterly, 3. Weekly): ";
                int billingChoice;
                cin >> billingChoice;

                if (billingChoice == 1) {
                    billingCycle = "Monthly";
                } else if (billingChoice == 2) {
                    billingCycle = "Quarterly";
                } else if (billingChoice == 3) {
                    billingCycle = "Weekly";
                } else {
                    cout << "Invalid choice.\n";
                    continue;
                }
                billingSelected = true;
                cout << "You selected " << billingCycle << " billing.\n";
                break;
            }

            case 3: {
                cout << "\nChoose Fault Detection Type (1. Thermal Imaging, 2. Electrical Testing): ";
                string faultChoice;
                cin >> faultChoice;

                if (faultDetectionOptions.find(faultChoice) != faultDetectionOptions.end()) {
                    faultDetectionType = faultDetectionOptions[faultChoice];
                    electricityLine.fault_detection_type = faultDetectionType;
                    faultDetectionSelected = true;
                    cout << "You selected " << faultDetectionType << " for fault detection.\n";
                } else {
                    cout << "Invalid choice.\n";
                }
                break;
            }

            case 4: {
                cout << "\nChoose Connection Type (1. Residential, 2. Commercial): ";
                int connectionChoice;
                cin >> connectionChoice;

                if (connectionChoice == 1) {
                    connectionType = "Residential";
                } else if (connectionChoice == 2) {
                    connectionType = "Commercial";
                } else {
                    cout << "Invalid choice.\n";
                    continue;
                }
                connectionTypeSelected = true;
                cout << "You selected " << connectionType << " as the connection type.\n";
                break;
            }

            case 5: {
                electricityLine.display();
                break;
            }

            case 6: {
                customer.display();
                break;
            }

            case 7: {
                if (materialSelected && billingSelected && faultDetectionSelected && connectionTypeSelected) {
                    double materialCost = materialRates[material];
                    double connectionCost = connectionPricing[connectionType][billingCycle];
                    double totalCost = materialCost * electricityLine.length + connectionCost;
                    customer.total_amount = totalCost;

                    cout << "\nFinal Customer Details:\n";
                    customer.display();
                } else {
                    cout << "Please complete all selections before finalizing.\n";
                }
                break;
            }

            case 8: {
                exitMenu = true;
                cout << "Exiting the program. Goodbye!\n";
                break;
            }

            default: {
                cout << "Invalid choice. Please try again.\n";
                break;
            }
        }
    }
    return 0;
}

// Structure to store customer details
struct Customer {
    string name;
    string customerID;
    string address;
    string contactInfo;
};

// Structure to store pipeline details
struct Pipeline {
    string material;
    double length;
    double diameter;
    string routing;
    string location;
    double capacity;
    string installationType;
    double installationCost; // Cost based on installation type
};

// Structure to store subscription and billing details
struct Billing {
    string billingType;
    string subscriptionPlan;
    double serviceFee;
    double activationFee;
};

// Function to calculate installation type-specific cost
double calculateInstallationTypeCost(const string& installationType) {
    if (installationType == "underground") {
        return 2000; // Underground installation cost
    } else if (installationType == "aerial") {
        return 4000; // Aerial installation cost
    } else if (installationType == "combination") {
        return 8000; // Combination installation cost
    }
    return 0; // Default if installation type is unknown
}

// Function to display customer details
void displayCustomerDetails(const Customer& customer) {
    cout << "\nCustomer Details:\n";
    cout << "Name: " << customer.name << endl;
    cout << "Customer ID: " << customer.customerID << endl;
    cout << "Address: " << customer.address << endl;
    cout << "Contact Information: " << customer.contactInfo << endl;
}

// Function to display pipeline details
void displayPipelineDetails(const Pipeline& pipeline) {
    cout << "\nPipeline Details:\n";
    cout << "Material: " << pipeline.material << endl;
    cout << "Length: " << pipeline.length << " meters" << endl;
    cout << "Diameter: " << pipeline.diameter << " mm" << endl;
    cout << "Routing: " << pipeline.routing << endl;
    cout << "Location: " << pipeline.location << endl;
    cout << "Capacity: " << pipeline.capacity << " Gbps" << endl;
    cout << "Installation Type: " << pipeline.installationType << endl;
    cout << "Installation Cost: " << pipeline.installationCost << " units" << endl; // Display installation cost
}

// Function to display billing details
void displayBillingDetails(const Billing& billing) {
    cout << "\nBilling Details:\n";
    cout << "Billing Type: " << billing.billingType << endl;
    cout << "Subscription Plan: " << billing.subscriptionPlan << endl;
    cout << "Service Fee: " << billing.serviceFee << " units" << endl;
    cout << "Activation Fee: " << billing.activationFee << " units" << endl;
}

// Main function to input and manage Wi-Fi pipeline details
int main() {
    srand(time(0)); // Seed the random number generator to ensure randomness
    Customer customer;
    Pipeline pipeline;
    Billing billing;
    int choice;

    // Main menu-driven interface
    while (true) {
        cout << "\nWi-Fi Pipeline Connection Management System\n";
        cout << "Please choose an option:\n";
        cout << "1. Enter Customer Details\n";
        cout << "2. Enter Pipeline Details\n";
        cout << "3. Enter Billing and Subscription Details\n";
        cout << "4. View Customer Details\n";
        cout << "5. View Pipeline Details\n";
        cout << "6. View Billing Details\n";
        cout << "7. Exit\n";
        cout << "Enter your choice (1-7): ";
        cin >> choice;
        cin.ignore(); // To clear the newline character left by cin

        switch (choice) {
            case 1:
                // Input customer details
                cout << "\nEnter Customer Name: ";
                getline(cin, customer.name);
                cout << "Enter Customer ID: ";
                getline(cin, customer.customerID);
                cout << "Enter Customer Address: ";
                getline(cin, customer.address);
                cout << "Enter Customer Contact Information (Phone/Email): ";
                getline(cin, customer.contactInfo);
                break;

            case 2:
                // Input pipeline details
                cout << "\nEnter Pipeline Material (Fiber Optic, Coaxial Cable, Ethernet Cable): ";
                getline(cin, pipeline.material);
                cout << "Enter Pipeline Length (in meters): ";
                cin >> pipeline.length;
                cout << "Enter Pipeline Diameter (in mm): ";
                cin >> pipeline.diameter;
                cin.ignore(); // To clear the newline character left by cin
                cout << "Enter Pipeline Routing (e.g., underground, overhead): ";
                getline(cin, pipeline.routing);
                cout << "Enter Pipeline Location (e.g., street name, city): ";
                getline(cin, pipeline.location);
                cout << "Enter Pipeline Capacity (in Gbps): ";
                cin >> pipeline.capacity;
                cin.ignore(); // To clear the newline character left by cin
                cout << "Enter Installation Type (underground, aerial, combination): ";
                getline(cin, pipeline.installationType);

                // Set installation cost
                pipeline.installationCost = calculateInstallationTypeCost(pipeline.installationType);
                break;

            case 3:
                // Input billing details
                cout << "\nEnter Billing Type (Monthly, Quarterly, Annually): ";
                getline(cin, billing.billingType);
                cout << "Enter Subscription Plan (Basic, Premium, Business): ";
                getline(cin, billing.subscriptionPlan);
                cout << "Enter Service Fee (in units): ";
                cin >> billing.serviceFee;
                cout << "Enter Activation Fee (in units): ";
                cin >> billing.activationFee;
                break;

            case 4:
                // Display customer details
                if (customer.name.empty()) {
                    cout << "Customer details not entered yet.\n";
                } else {
                    displayCustomerDetails(customer);
                }
                break;

            case 5:
                // Display pipeline details
                if (pipeline.material.empty()) {
                    cout << "Pipeline details not entered yet.\n";
                } else {
                    displayPipelineDetails(pipeline);
                }
                break;

            case 6:
                // Display billing details
                if (billing.billingType.empty()) {
                    cout << "Billing details not entered yet.\n";
                } else {
                    displayBillingDetails(billing);
                }
                break;

            case 7:
                // Exit the program
                cout << "Exiting the Wi-Fi Pipeline Management System...\n";
                return 0;

            default:
                cout << "Invalid choice. Please enter a valid option (1-7).\n";
        }
    }
    return 0;


// Structure to represent the AreaDetails with distance and cost
struct AreaDetails {
    string area_name;
    int distance; // distance from selected area (in meters)
    int cost;     // cost in Rs
};

// Structure to represent the Sub-division gas pipeline Office
struct Sub_division_gas_pipeline_office {
    vector<AreaDetails> areas;  // List of areas in the sub-division
};

// Function to implement the functionality of displaying areas based on the selected zone
void displayAreas(const string& selected_zone, const unordered_map<string, vector<string>>& zone_areas) {
    cout << selected_zone << " contains the following areas:\n";
    const vector<string>& areas = zone_areas.at(selected_zone);  // Get areas for selected zone
    for (size_t i = 0; i < areas.size(); ++i) {
        cout << i + 1 << ". " << areas[i] << endl;  // Display area number and name
    }
}

// Function to display the sub-division office and area details based on the selected area
void displaySubDivisionDetails(const string& selected_area, const unordered_map<string, Sub_division_gas_pipeline_office>& area_details) {
    auto it = area_details.find(selected_area);  // Find the selected area in the area details map
    if (it != area_details.end()) {
        // Correctly displaying the area name dynamically
        cout << "gas pipeline office " << selected_area << ":\n";
        for (size_t i = 0; i < it->second.areas.size(); ++i) {
            const AreaDetails& area = it->second.areas[i];
            cout << i + 1 << ". " << area.area_name << " - " << area.distance << " meters, cost - " << area.cost << " rs\n";
        }
    } else {
        cout << "Area not found in this sub-division.\n";
    }
}

// Function to find the area with the shortest distance
string findShortestDistanceArea(const vector<AreaDetails>& areas) {
    // Find the area with the minimum distance
    auto min_it = min_element(areas.begin(), areas.end(), [](const AreaDetails& a, const AreaDetails& b) {
        return a.distance < b.distance;
    });
    return min_it->area_name;
}

// Function to calculate the volume of a cylindrical pipe
double calculatePipeVolume(double length, double outerDiameter, double thickness)
{
    const double PI = 3.14159265359;
    double innerDiameter = outerDiameter - 2 * thickness;
    double outerRadius = outerDiameter / 2.0;
    double innerRadius = innerDiameter / 2.0;

    double outerVolume = PI * outerRadius * outerRadius * length;
    double innerVolume = PI * innerRadius * innerRadius * length;

    return outerVolume - innerVolume; // Material volume
}
// Function to calculate the surface area of a cylindrical pipe
double calculateSurfaceArea(double length, double outerDiameter)
{
    const double PI = 3.14159265359;
    double radius = outerDiameter / 2.0;
    return 2 * PI * radius * length; // Surface area of the cylindrical surface
}

// Function to categorize pressure
string categorizePressure(double pressure)
 {
    if (pressure > 100)
    {
        return "High Pressure";
    } else if (pressure >= 40 && pressure <= 100)
    {
        return "Medium Pressure";
    } else
    {
        return "Low Pressure";
    }
}




int main()
{
    // User interface for input
    cout << "The Belagavi city gas pipeline " << endl;
    cout << "Enter the Zones (1. East zone, 2. West zone, 3. North zone, 4. South zone): ";
    int zone_choice;
    cin >> zone_choice;

    string selected_zone;
    unordered_map<int, string> zone_map =
     {
        {1, "East Zone"},
        {2, "West Zone"},
        {3, "North Zone"},
        {4, "South Zone"}
    };

    if (zone_map.find(zone_choice) == zone_map.end())
    {
        cout << "Invalid Zone" << endl;
        return 1;
    }

    selected_zone = zone_map[zone_choice];
    cout << "The selected zone is: " << selected_zone << endl;

    // Define the list of areas for each zone
    unordered_map<string, vector<string>> zone_areas =
    {
        {"East Zone", {"Shaniwar Khoot",
                       "Khanjar Galli",
                       "Green Taj",
                       "Khanjar Galli Cross",
                       "Khanjar Galli Urdu School",
                       "Darbar Galli Cross",
                       "Bagwan Galli Cross",
                       "Kotwal Galli Double Road",
                       "Kakar Galli",
                       "Khade Bazar",
                       "Tenginkeri Galli Junction",
                       "Govt. Hospital",
                       "Mesni Galli",
                       "Kaktives",
                       "Chandu Galli",
                       "Ghee Galli - Jalgar Galli",
                       "Mali Galli",
                       "MBS No. 4 Azad Galli",
                       "Joshi Bazar",
                       "Joshi Bazar Road",
                       "Karnatak Chowk",
                       "Kalmath Road",
                       "Bhavye Chowk",
                       "Ananshyana Galli",
                       "Konwal Galli",
                       "Tilak Chowk",
                       "Raghvendra Math",
                       "SamsunG Showroom",
                       "Corporation Bank",
                       "Sardar High School",
                       "Court Compound",
                       "Topi Galli",
                       "Darbar Galli Cross",
                       "Chavat Galli to PB Road",
                       "Shetti Galli PB Road Cross",
                       "Kotwal Galli Double Road",
                       "Kaktives Road",
                       "Sardar High School Ground",
                       "Konwal Galli Guest House",
                       "Azad Galli", "Hospital Road",
                       "Tenginkeri Sheetal Hotel Cross",
                       "Pai Hotel",
                       "Old PB Road South Peripheral"}},
        {"West Zone", {"Raviwar Peth Main Road",
                       "Motilal Circle",
                       "Hira Talkies",
                       "Ganpat Galli upto Hira Talkies",
                       "Kirloskar Road",
                       "Bata Showroom",
                       "Ramdev Galli",
                       "Adarsh Dress Circle",
                       "SamsunG Showroom",
                       "Samadevi Galli",
                       "Gondhalli Galli",
                       "Gavli Galli",
                       "Narvekar Gali",
                       "Risaldar Galli",
                       "Khade Bazar Police Station",
                       "Shaniwar Khoot - Ganpat Galli",
                       "Hira Talkies Backside",
                       "Kalkundrikar Road",
                       "Kalkundrikar",
                       "Ganga Prabaha Hotel",
                       "Kirloskar Road",
                       "Bata Showroom"}},
        {"North Zone", {"Moksahi Galli",
                        "Bauxite Road",
                        "Bank of Maharashtra",
                        "Nayaya Marg",
                        "Vidyagiri",
                        "Basav Colony",
                        "Shivbasav Nagar",
                        "Bauxite Road",
                        "Kanakdas Circle",
                        "Shankam Hotel Cross",
                        "Gandhi Nagar",
                        "Shivterth Colony",
                        "KLE Compound",
                        "Jadhav Nagar",
                        "Shivaji Garden",
                        "Vandan Colony",
                        "Vidyagiri"}},
        {"South Zone", {"Chennamma Circle",
                        "Rayanna Circle",
                        "Keerti Hotel",
                        "Shetti Galli",
                        "Old PB Road",
                        "SamsunG Showroom",
                        "Raviwar Peth Main Road",
                        "Shani Mandir",
                        "Shivaji Nagar",
                        "Sambhaji Circle",
                        "Shivbasav Nagar",
                        "Ram Nagar",
                        "NCC Arts",
                        "Bharat Motor School",
                        "Jadhav Nagar",
                        "Sadashiv Nagar",
                        "Vengurla Road",
                        "DC Bungalow Cross",
                        "Ambedkar Road",
                        "Chennamma Circle - College Road",
                        "Vengurla Road - DC Bungalow",
                        "Rail Nagar South Cross",
                        "TB Ward - Ambedkar Road",
                        "APMC Road",
                        "Ambedkar Road",
                        "Veerbhadra Nagar"}}



};

    // Define the sub-division office and area details
    unordered_map<string, Sub_division_gas_pipeline_office> area_details = {
        {"Green Taj", {
            {{"Green Taj", 800, 3000},
            {"Khanjar Galli", 500, 2500},
            {"Shaniwar Khoot", 300, 2000},
             {"Khanjar Galli Cross", 1000, 3300},
             {"Khanjar Galli Urdu School", 900, 3200}}}
        },
        {"Shaniwar Khoot",{
         {{"Shaniwar Khoot", 300, 2000},
         {"Khanjar Galli", 500, 2500},
        {"Green Taj", 800, 3000},
        {"Khanjar Galli Cross", 1000, 3300},
        {"Khanjar Galli Urdu School", 900, 3200},
        {"Darbar Galli Cross", 1200, 3500},
        {"Bagwan Galli Cross", 300, 2000}}}
        },
        {"Khanjar Galli",{
         {{"Shaniwar Khoot", 300, 2000},
         {"Khanjar Galli", 500, 2500},
        {"Green Taj", 800, 3000},
        {"Khanjar Galli Cross", 1000, 3300},
        {"Khanjar Galli Urdu School", 900, 3200},
        {"Darbar Galli Cross", 1200, 3500},
        {"Bagwan Galli Cross", 300, 2000}}}
        },
        {"Darbar Galli Cross",{
         {{"Shaniwar Khoot", 300, 2000},
         {"Khanjar Galli", 500, 2500},
        {"Green Taj", 800, 3000},
        {"Khanjar Galli Cross", 1000, 3300},
        {"Khanjar Galli Urdu School", 900, 3200},
        {"Darbar Galli Cross", 1200, 3500},
        {"Bagwan Galli Cross", 300, 2000}}}
        },
        {"Bagwan Galli Cross",{
         {{"Shaniwar Khoot", 300, 2000},
         {"Khanjar Galli", 500, 2500},
        {"Green Taj", 800, 3000},
        {"Khanjar Galli Cross", 1000, 3300},
        {"Khanjar Galli Urdu School", 900, 3200},
        {"Darbar Galli Cross", 1200, 3500},
        {"Bagwan Galli Cross", 300, 2000}}}
        },
        {"Khanjar Galli Cross", {
            {{"Green Taj", 800, 3000},
            {"Khanjar Galli", 500, 2500},
            {"Shaniwar Khoot", 300, 2000},
             {"Khanjar Galli Cross", 1000, 3300},
             {"Khanjar Galli Urdu School", 900, 3200}}}
        },
        {"Khanjar Galli Urdu School", {
            {{"Green Taj", 800, 3000},
            {"Khanjar Galli", 500, 2500},
            {"Shaniwar Khoot", 300, 2000},
             {"Khanjar Galli Cross", 1000, 3300},
             {"Khanjar Galli Urdu School", 900, 3200}}}
        },
        {"Khade Bazar",{
        {{"Kotwal Galli Double Road", 2000, 5500},
        {"Kakar Galli", 1600, 4800},
        {"Khade Bazar", 300, 2000},
        {"Tenginkeri Galli Junction", 900, 3200},
        {"Govt. Hospital", 1000, 3300},
        {"Green Taj", 500, 2500}}}
        },
        {"Kotwal Galli Double Road",{
        {{"Kotwal Galli Double Road", 2000, 5500},
        {"Kakar Galli", 1600, 4800},
        {"Khade Bazar", 300, 2000},
        {"Tenginkeri Galli Junction", 900, 3200},
        {"Govt. Hospital", 1000, 3300},
        {"Green Taj", 500, 2500}}}
        },
        {"Kakar Galli",{
        {{"Kotwal Galli Double Road", 2000, 5500},
        {"Kakar Galli", 1600, 4800},
        {"Khade Bazar", 300, 2000},
        {"Tenginkeri Galli Junction", 900, 3200},
        {"Govt. Hospital", 1000, 3300},
        {"Green Taj", 500, 2500}}}
        },
        {"Tenginkeri Galli Junction",{
        {{"Kotwal Galli Double Road", 2000, 5500},
        {"Kakar Galli", 1600, 4800},
        {"Khade Bazar", 300, 2000},
        {"Tenginkeri Galli Junction", 900, 3200},
        {"Govt. Hospital", 1000, 3300},
        {"Green Taj", 500, 2500}}}
        },
        {"Govt. Hospital",{
        {{"Kotwal Galli Double Road", 2000, 5500},
        {"Kakar Galli", 1600, 4800},
        {"Khade Bazar", 300, 2000},
        {"Tenginkeri Galli Junction", 900, 3200},
        {"Govt. Hospital", 1000, 3300},
        {"Green Taj", 500, 2500}}}
        },
        {"Kaktives",{
        {{"Govt. Hospital", 1000, 3300},
        {"Green Taj", 500, 2500},
        {"Mesni Galli", 500, 2500},
        {"Kaktives", 1600, 4800},
        {"Chandu Galli", 2000, 5500},
        {"Khanjar Galli Cross", 800, 3000},
        {"Ghee Galli - Jalgar Galli", 2500, 6500}}
        }
        },
        {"Mesni Galli",{
        {{"Govt. Hospital", 1000, 3300},
        {"Green Taj", 500, 2500},
        {"Mesni Galli", 500, 2500},
        {"Kaktives", 1600, 4800},
        {"Chandu Galli", 2000, 5500},
        {"Khanjar Galli Cross", 800, 3000},
        {"Ghee Galli - Jalgar Galli", 2500, 6500}}
        }
        },
        {"Chandu Galli",{
        {{"Govt. Hospital", 1000, 3300},
        {"Green Taj", 500, 2500},
        {"Mesni Galli", 500, 2500},
        {"Kaktives", 1600, 4800},
        {"Chandu Galli", 2000, 5500},
        {"Khanjar Galli Cross", 800, 3000},
        {"Ghee Galli - Jalgar Galli", 2500, 6500}}
        }
        },
        {"Ghee Galli - Jalgar Galli",{
        {{"Govt. Hospital", 1000, 3300},
        {"Green Taj", 500, 2500},
        {"Mesni Galli", 500, 2500},
        {"Kaktives", 1600, 4800},
        {"Chandu Galli", 2000, 5500},
        {"Khanjar Galli Cross", 800, 3000},
        {"Ghee Galli - Jalgar Galli", 2500, 6500}}
        }
        },
        {"Topi Galli",{
        {{"Mali Galli", 500, 2500},
        {"MBS No. 4 Azad Galli", 1200, 3500},
        {"Joshi Bazar", 800, 3000},
        {"Joshi Bazar Road", 900, 3200},
        {"Karnatak Chowk", 1600, 4800},
        {"Kalmath Road", 3500, 8000},
        {"Khade Bazar", 1000, 3000},
        {"Topi Galli", 200, 1800},
        {"Ananshyana Galli", 800, 3000}}}
        },
        {"Joshi Bazar",{
        {{"Mali Galli", 500, 2500},
        {"MBS No. 4 Azad Galli", 1200, 3500},
        {"Joshi Bazar", 800, 3000},
        {"Joshi Bazar Road", 900, 3200},
        {"Karnatak Chowk", 1600, 4800},
        {"Kalmath Road", 3500, 8000},
        {"Khade Bazar", 1000, 3000},
        {"Topi Galli", 200, 1800},
        {"Ananshyana Galli", 800, 3000}}}
        },
        {"Karnatak Chowk",{
        {{"Mali Galli", 500, 2500},
        {"MBS No. 4 Azad Galli", 1200, 3500},
        {"Joshi Bazar", 800, 3000},
        {"Joshi Bazar Road", 900, 3200},
        {"Karnatak Chowk", 1600, 4800},
        {"Kalmath Road", 3500, 8000},
        {"Khade Bazar", 1000, 3000},
        {"Topi Galli", 200, 1800},
        {"Ananshyana Galli", 800, 3000}}}
        },
        {"Ananshyana Galli",{
        {{"Mali Galli", 500, 2500},
        {"MBS No. 4 Azad Galli", 1200, 3500},
        {"Joshi Bazar", 800, 3000},
        {"Joshi Bazar Road", 900, 3200},
        {"Karnatak Chowk", 1600, 4800},
        {"Kalmath Road", 3500, 8000},
        {"Khade Bazar", 1000, 3000},
        {"Topi Galli", 200, 1800},
        {"Ananshyana Galli", 800, 3000}}}
        },
        {"Kalmath Road",{
        {{"Mali Galli", 500, 2500},
        {"MBS No. 4 Azad Galli", 1200, 3500},
        {"Joshi Bazar", 800, 3000},
        {"Joshi Bazar Road", 900, 3200},
        {"Karnatak Chowk", 1600, 4800},
        {"Kalmath Road", 3500, 8000},
        {"Khade Bazar", 1000, 3000},
        {"Topi Galli", 200, 1800},
        {"Ananshyana Galli", 800, 3000}}}
        },
        {"Tilak Chowk",{
        {{"Konwal Galli", 500, 2500},
        {"Tilak Chowk", 1200, 3500},
        {"Raghvendra Math", 1600, 4800},
        {"SamsunG Showroom", 300, 2000},
        {"Corporation Bank", 3500, 8000},
        {"Sardar High School", 2000, 5500},
        {"Court Compound", 1000, 3300}}}
        },
        {"Konwal Galli",{
        {{"Konwal Galli", 500, 2500},
        {"Tilak Chowk", 1200, 3500},
        {"Raghvendra Math", 1600, 4800},
        {"SamsunG Showroom", 300, 2000},
        {"Corporation Bank", 3500, 8000},
        {"Sardar High School", 2000, 5500},
        {"Court Compound", 1000, 3300}}}
        },
        {"Raghvendra Math",{
        {{"Konwal Galli", 500, 2500},
        {"Tilak Chowk", 1200, 3500},
        {"Raghvendra Math", 1600, 4800},
        {"SamsunG Showroom", 300, 2000},
        {"Corporation Bank", 3500, 8000},
        {"Sardar High School", 2000, 5500},
        {"Court Compound", 1000, 3300}}}
        },
        {"Court Compound",{
        {{"Konwal Galli", 500, 2500},
        {"Tilak Chowk", 1200, 3500},
        {"Raghvendra Math", 1600, 4800},
        {"SamsunG Showroom", 300, 2000},
        {"Corporation Bank", 3500, 8000},
        {"Sardar High School", 2000, 5500},
        {"Court Compound", 1000, 3300}}}
        },
        {"Bhavye Chowk",{
        {{"Bhavye Chowk",200, 1800},
        {"Darbar Galli Cross",2500, 6500},
        {"SamsunG Showroom", 500, 2500},
        {"Chavat Galli to PB Road",4000, 9000},
        {"Shetti Galli PB Road Cross",3000, 8500},
        {"Kotwal Galli Double Road",2000, 5500}}}
        },
        {"Bhavye Chowk",{
        {{"Bhavye Chowk",200, 1800},
        {"Darbar Galli Cross",2500, 6500},
        {"SamsunG Showroom", 500, 2500},
        {"Chavat Galli to PB Road",4000, 9000},
        {"Shetti Galli PB Road Cross",3000, 8500},
        {"Kotwal Galli Double Road",2000, 5500}}}
        },
        {"Darbar Galli Cross",{
        {{"Bhavye Chowk",200, 1800},
        {"Darbar Galli Cross",2500, 6500},
        {"SamsunG Showroom", 500, 2500},
        {"Chavat Galli to PB Road",4000, 9000},
        {"Shetti Galli PB Road Cross",3000, 8500},
        {"Kotwal Galli Double Road",2000, 5500}}}
        },
        {"Chavat Galli to PB Road",{
        {{"Bhavye Chowk",200, 1800},
        {"Darbar Galli Cross",2500, 6500},
        {"SamsunG Showroom", 500, 2500},
        {"Chavat Galli to PB Road",4000, 9000},
        {"Shetti Galli PB Road Cross",3000, 8500},
        {"Kotwal Galli Double Road",2000, 5500}}}
        },
        {"Shetti Galli PB Road Cross",{
        {{"Bhavye Chowk",200, 1800},
        {"Darbar Galli Cross",2500, 6500},
        {"SamsunG Showroom", 500, 2500},
        {"Chavat Galli to PB Road",4000, 9000},
        {"Shetti Galli PB Road Cross",3000, 8500},
        {"Kotwal Galli Double Road",2000, 5500}}}
        },

        {"Kaktives Road", {
        {{"Kaktives Road",300, 2000},
        {"Sardar High School Ground",1200, 3500},
        {"Konwal Galli Guest House",3500, 8000},
        {"Azad Galli",2000, 5500},
        {"Hospital Road",800, 3000},
        {"Tenginkeri Sheetal Hotel Cross",1600, 3300},
        {"Pai Hotel",1000, 3300},
        {"Old PB Road South Peripheral",3000, 8500}}}
        },
        {"Old PB Road South Peripheral", {
        {{"Kaktives Road",300, 2000},
        {"Sardar High School Ground",1200, 3500},
        {"Konwal Galli Guest House",3500, 8000},
        {"Azad Galli",2000, 5500},
        {"Hospital Road",800, 3000},
        {"Tenginkeri Sheetal Hotel Cross",1600, 3300},
        {"Pai Hotel",1000, 3300},
        {"Old PB Road South Peripheral",3000, 8500}}}
        },
        {"Azad Galli", {
        {{"Kaktives Road",300, 2000},
        {"Sardar High School Ground",1200, 3500},
        {"Konwal Galli Guest House",3500, 8000},
        {"Azad Galli",2000, 5500},
        {"Hospital Road",800, 3000},
        {"Tenginkeri Sheetal Hotel Cross",1600, 3300},
        {"Pai Hotel",1000, 3300},
        {"Old PB Road South Peripheral",3000, 8500}}}
        },
        {"Pai Hotel", {
        {{"Kaktives Road",300, 2000},
        {"Sardar High School Ground",1200, 3500},
        {"Konwal Galli Guest House",3500, 8000},
        {"Azad Galli",2000, 5500},
        {"Hospital Road",800, 3000},
        {"Tenginkeri Sheetal Hotel Cross",1600, 3300},
        {"Pai Hotel",1000, 3300},
        {"Old PB Road South Peripheral",3000, 8500}}}
        },
        {"Konwal Galli Guest House", {
        {{"Kaktives Road",300, 2000},
        {"Sardar High School Ground",1200, 3500},
        {"Konwal Galli Guest House",3500, 8000},
        {"Azad Galli",2000, 5500},
        {"Hospital Road",800, 3000},
        {"Tenginkeri Sheetal Hotel Cross",1600, 3300},
        {"Pai Hotel",1000, 3300},
        {"Old PB Road South Peripheral",3000, 8500}}}
        },
        {"Hospital Road", {
        {{"Kaktives Road",300, 2000},
        {"Sardar High School Ground",1200, 3500},
        {"Konwal Galli Guest House",3500, 8000},
        {"Azad Galli",2000, 5500},
        {"Hospital Road",800, 3000},
        {"Tenginkeri Sheetal Hotel Cross",1600, 3300},
        {"Pai Hotel",1000, 3300},
        {"Old PB Road South Peripheral",3000, 8500}}}
        },
        {"Motilal Circle",{
        {{"Motilal Circle", 300, 2000},
        {"Raviwar Peth Main Road", 1200, 3500},
        {"Hira Talkies", 3500, 8000},
        {"Ganpat Galli upto Hira Talkies", 1000, 3300},
        {"Kirloskar Road", 2000, 5500},
        {"Bata Showroom", 1200, 3500}}}
        },
        {"Raviwar Peth Main Road",{
        {{"Motilal Circle", 300, 2000},
        {"Raviwar Peth Main Road", 1200, 3500},
        {"Hira Talkies", 3500, 8000},
        {"Ganpat Galli upto Hira Talkies", 1000, 3300},
        {"Kirloskar Road", 2000, 5500},
        {"Bata Showroom", 1200, 3500}}}
        },
        {"Hira Talkies",{
        {{"Motilal Circle", 300, 2000},
        {"Raviwar Peth Main Road", 1200, 3500},
        {"Hira Talkies", 3500, 8000},
        {"Ganpat Galli upto Hira Talkies", 1000, 3300},
        {"Kirloskar Road", 2000, 5500},
        {"Bata Showroom", 1200, 3500}}}
        },
        {"Kirloskar Road",{
        {{"Motilal Circle", 300, 2000},
        {"Raviwar Peth Main Road", 1200, 3500},
        {"Hira Talkies", 3500, 8000},
        {"Ganpat Galli upto Hira Talkies", 1000, 3300},
        {"Kirloskar Road", 2000, 5500},
        {"Bata Showroom", 1200, 3500}}}
        },
        {"Adarsh Dress Circle",{
        {{"Ramdev Galli", 200, 1800},
        {"Adarsh Dress Circle", 500, 2500},
        {"SamsunG Showroom", 3000, 8500},
        {"Samadevi Galli", 1000, 3300},
        {"Gondhalli Galli", 1600, 4800},
        {"Gavli Galli", 800, 3000},
        {"Narvekar Gali", 2000, 5500}}}
        },
        {"Ramdev Galli",{
        {{"Ramdev Galli", 200, 1800},
        {"Adarsh Dress Circle", 500, 2500},
        {"SamsunG Showroom", 3000, 8500},
        {"Samadevi Galli", 1000, 3300},
        {"Gondhalli Galli", 1600, 4800},
        {"Gavli Galli", 800, 3000},
        {"Narvekar Gali", 2000, 5500}}}
        },
        {"Samadevi Galli",{
        {{"Ramdev Galli", 200, 1800},
        {"Adarsh Dress Circle", 500, 2500},
        {"SamsunG Showroom", 3000, 8500},
        {"Samadevi Galli", 1000, 3300},
        {"Gondhalli Galli", 1600, 4800},
        {"Gavli Galli", 800, 3000},
        {"Narvekar Gali", 2000, 5500}}}
        },
        {"Gondhalli Galli",{
        {{"Ramdev Galli", 200, 1800},
        {"Adarsh Dress Circle", 500, 2500},
        {"SamsunG Showroom", 3000, 8500},
        {"Samadevi Galli", 1000, 3300},
        {"Gondhalli Galli", 1600, 4800},
        {"Gavli Galli", 800, 3000},
        {"Narvekar Gali", 2000, 5500}}}
        },
        {"Gavli Galli",{
        {{"Ramdev Galli", 200, 1800},
        {"Adarsh Dress Circle", 500, 2500},
        {"SamsunG Showroom", 3000, 8500},
        {"Samadevi Galli", 1000, 3300},
        {"Gondhalli Galli", 1600, 4800},
        {"Gavli Galli", 800, 3000},
        {"Narvekar Gali", 2000, 5500}}}
        },
        {"Risaldar Galli",{
        {{"Risaldar Galli", 1200, 3500},
        {"Kalkundrikar Road", 500, 2500},
        {"Ganga Prabaha Hotel", 1200, 3500},
        {"Kirloskar Road", 1600, 4800},
        {"Bata Showroom", 800, 3000},
        {"Khade Bazar Police Station", 900, 3200},
        {"Shaniwar Khoot - Ganpat Galli", 2500, 6500},
        {"Hira Talkies Backside", 3000, 8500}}}
        },
        {"Kalkundrikar Road",{
        {{"Risaldar Galli", 1200, 3500},
        {"Kalkundrikar Road", 500, 2500},
        {"Ganga Prabaha Hotel", 1200, 3500},
        {"Kirloskar Road", 1600, 4800},
        {"Bata Showroom", 800, 3000},
        {"Khade Bazar Police Station", 900, 3200},
        {"Shaniwar Khoot - Ganpat Galli", 2500, 6500},
        {"Hira Talkies Backside", 3000, 8500}}}
        },
        {"Bata Showroom",{
        {{"Risaldar Galli", 1200, 3500},
        {"Kalkundrikar Road", 500, 2500},
        {"Ganga Prabaha Hotel", 1200, 3500},
        {"Kirloskar Road", 1600, 4800},
        {"Bata Showroom", 800, 3000},
        {"Khade Bazar Police Station", 900, 3200},
        {"Shaniwar Khoot - Ganpat Galli", 2500, 6500},
        {"Hira Talkies Backside", 3000, 8500}}}
        },
        {"Ganga Prabaha Hotel",{
        {{"Risaldar Galli", 1200, 3500},
        {"Kalkundrikar Road", 500, 2500},
        {"Ganga Prabaha Hotel", 1200, 3500},
        {"Kirloskar Road", 1600, 4800},
        {"Bata Showroom", 800, 3000},
        {"Khade Bazar Police Station", 900, 3200},
        {"Shaniwar Khoot - Ganpat Galli", 2500, 6500},
        {"Hira Talkies Backside", 3000, 8500}}}
        },
        {"Shaniwar Khoot - Ganpat Galli",{
        {{"Risaldar Galli", 1200, 3500},
        {"Kalkundrikar Road", 500, 2500},
        {"Ganga Prabaha Hotel", 1200, 3500},
        {"Kirloskar Road", 1600, 4800},
        {"Bata Showroom", 800, 3000},
        {"Khade Bazar Police Station", 900, 3200},
        {"Shaniwar Khoot - Ganpat Galli", 2500, 6500},
        {"Hira Talkies Backside", 3000, 8500}}}
        },
        {"Moksahi Galli",{
        {{"Moksahi Galli", 500, 2500},
        {"Bauxite Road", 3000, 8500},
        {"Bank of Maharashtra", 900, 3200},
        {"Nayaya Marg", 500, 2500},
        {"Vidyagiri", 800, 3000},
        {"Basav Colony", 1600, 4800},
        {"Shivbasav Nagar", 1200, 3500}}}
        },
        {"Bauxite Road",{
        {{"Moksahi Galli", 500, 2500},
        {"Bauxite Road", 3000, 8500},
        {"Bank of Maharashtra", 900, 3200},
        {"Nayaya Marg", 500, 2500},
        {"Vidyagiri", 800, 3000},
        {"Basav Colony", 1600, 4800},
        {"Shivbasav Nagar", 1200, 3500}}}
        },
        {"Bank of Maharashtra",{
        {{"Bauxite Road", 3000, 8500},
        {"Bank of Maharashtra", 900, 3200},
        {"Nayaya Marg", 500, 2500},
        {"Vidyagiri", 800, 3000},
        {"Basav Colony", 1600, 4800},
        {"Shivbasav Nagar", 1200, 3500}}}
        },
        {"Nayaya Marg",{
        {{"Moksahi Galli", 500, 2500},
        {"Bauxite Road", 3000, 8500},
        {"Bank of Maharashtra", 900, 3200},
        {"Nayaya Marg", 500, 2500},
        {"Vidyagiri", 800, 3000},
        {"Basav Colony", 1600, 4800},
        {"Shivbasav Nagar", 1200, 3500}}}
        },
        {"Vidyagiri",{
        {{"Bauxite Road", 3000, 8500},
        {"Bank of Maharashtra", 900, 3200},
        {"Nayaya Marg", 500, 2500},
        {"Vidyagiri", 800, 3000},
        {"Basav Colony", 1600, 4800},
        {"Shivbasav Nagar", 1200, 3500}}}
        },
        {"Basav Colony",{
        {{"Bauxite Road", 3000, 8500},
        {"Bank of Maharashtra", 900, 3200},
        {"Nayaya Marg", 500, 2500},
        {"Vidyagiri", 800, 3000},
        {"Basav Colony", 1600, 4800},
        {"Shivbasav Nagar", 1200, 3500}}}
        },
        {"Shivbasav Nagar",{
        {{"Bauxite Road", 3000, 8500},
        {"Bank of Maharashtra", 900, 3200},
        {"Nayaya Marg", 500, 2500},
        {"Vidyagiri", 800, 3000},
        {"Basav Colony", 1600, 4800},
        {"Shivbasav Nagar", 1200, 3500}}}
        },
        {"Kanakdas Circle",{
        {{"Bauxite Road", 200, 1800},
        {"Kanakdas Circle", 900, 3200},
        {"Shankam Hotel Cross", 800, 3000},
        {"Gandhi Nagar", 500, 2500},
        {"Shivterth Colony", 1000, 3300},
        {"Kanakdas Circle", 1200, 3500},
        {"KLE Compound", 3000, 8500},
        {"Jadhav Nagar", 1600, 4800}}}
        },
        {"Shankam Hotel Cross",{
        {{"Kanakdas Circle", 900, 3200},
        {"Shankam Hotel Cross", 800, 3000},
        {"Gandhi Nagar", 500, 2500},
        {"Shivterth Colony", 1000, 3300},
        {"Kanakdas Circle", 1200, 3500},
        {"KLE Compound", 3000, 8500},
        {"Jadhav Nagar", 1600, 4800}}}
        },
        {"Gandhi Nagar",{
        {{"Kanakdas Circle", 900, 3200},
        {"Shankam Hotel Cross", 800, 3000},
        {"Gandhi Nagar", 500, 2500},
        {"Shivterth Colony", 1000, 3300},
        {"Kanakdas Circle", 1200, 3500},
        {"Jadhav Nagar", 1600, 4800}}}
        },
        {"Shivterth Colony",{
        {{"Bauxite Road", 200, 1800},
        {"Kanakdas Circle", 900, 3200},
        {"Shankam Hotel Cross", 800, 3000},
        {"Gandhi Nagar", 500, 2500},
        {"Shivterth Colony", 1000, 3300},
        {"Kanakdas Circle", 1200, 3500},
        {"KLE Compound", 3000, 8500},
        {"Jadhav Nagar", 1600, 4800}}}
        },
        {"KLE Compound",{
        {{"Kanakdas Circle", 900, 3200},
        {"Shankam Hotel Cross", 800, 3000},
        {"Gandhi Nagar", 500, 2500},
        {"Shivterth Colony", 1000, 3300},
        {"Kanakdas Circle", 1200, 3500},
        {"KLE Compound", 3000, 8500},
        {"Jadhav Nagar", 1600, 4800}}}
        },
        {"Jadhav Nagar",{
        {{"Kanakdas Circle", 900, 3200},
        {"Shankam Hotel Cross", 800, 3000},
        {"Gandhi Nagar", 500, 2500},
        {"Shivterth Colony", 1000, 3300},
        {"Kanakdas Circle", 1200, 3500},
        {"KLE Compound", 3000, 8500},
        {"Jadhav Nagar", 1600, 4800}}}
        },

        {"Shivaji Garden",{
        {{"Shivaji Garden",500, 2500},
        {"Vandan Colony", 900, 3200},
        {"Vidyagiri", 1000, 3300},
        {"Bauxite Road", 800, 3000},
        {"Gandhinagar", 1200, 3500}}}
        },

        {"Vidyagiri",{
        {{"Vandan Colony", 900, 3200},
        {"Vidyagiri", 1000, 3300},
        {"Bauxite Road", 800, 3000},
        {"Gandhinagar", 1200, 3500}}}
        },

        {"Vandan Colony",{
        {{"Shivaji Garden",500, 2500},
        {"Vandan Colony", 900, 3200},
        {"Vidyagiri", 1000, 3300},
        {"Bauxite Road", 800, 3000},
        {"Gandhinagar", 1200, 3500}}}
        },

        {"Chennamma Circle",{
        {{"Chennamma Circle", 200, 1800},
        {"Rayanna Circle", 900, 3200},
        {"Keerti Hotel", 2000, 5500},
        {"Shetti Galli", 1200, 3500},
        {"Old PB Road", 3000, 8500},
        {"SamsunG Showroom", 800, 3000},
        {"Raviwar Peth Main Road", 1600, 4800}}}
        },

        {"Rayanna Circle",{
        {{"Rayanna Circle", 900, 3200},
        {"Keerti Hotel", 2000, 5500},
        {"Shetti Galli", 1200, 3500},
        {"Old PB Road", 3000, 8500},
        {"SamsunG Showroom", 800, 3000},
        {"Raviwar Peth Main Road", 1600, 4800},
        {"Shani Mandir", 500, 2500}}}
        },

        {"Keerti Hotel",{
        {{"Rayanna Circle", 900, 3200},
        {"Keerti Hotel", 2000, 5500},
        {"Shetti Galli", 1200, 3500},
        {"Old PB Road", 3000, 8500},
        {"Raviwar Peth Main Road", 1600, 4800}}}
        },

        {"Shetti Galli",{
        {{"Rayanna Circle", 900, 3200},
        {"Keerti Hotel", 2000, 5500},
        {"Shetti Galli", 1200, 3500},
        {"Old PB Road", 3000, 8500},
        {"SamsunG Showroom", 800, 3000},
        {"Raviwar Peth Main Road", 1600, 4800},
        {"Shani Mandir", 500, 2500}}}
        },

        {"Old PB Road",{
        {{"Rayanna Circle", 900, 3200},
        {"Keerti Hotel", 2000, 5500},
        {"Shetti Galli", 1200, 3500},
        {"Old PB Road", 3000, 8500},
        {"SamsunG Showroom", 800, 3000},
        {"Raviwar Peth Main Road", 1600, 4800}}}
        },

        {"SamsunG Showroom",{
        {{"Rayanna Circle", 900, 3200},
        {"Keerti Hotel", 2000, 5500},
        {"Shetti Galli", 1200, 3500},
        {"Old PB Road", 3000, 8500},
        {"SamsunG Showroom", 800, 3000},
        {"Raviwar Peth Main Road", 1600, 4800}}}
        },

        {"Raviwar Peth Main Road",{
        {{"Keerti Hotel", 2000, 5500},
        {"Shetti Galli", 1200, 3500},
        {"Old PB Road", 3000, 8500},
        {"Raviwar Peth Main Road", 1600, 4800}}}
        },

        {"Shivaji Nagar",{
        {{"Shivaji Nagar", 500, 2500},
        {"Sambhaji Circle", 900, 3200},
        {"Shivbasav Nagar", 1200, 3500},
        {"Ram Nagar", 2000, 5500},
        {"NCC Arts", 1000, 3300},
        {"Bharat Motor School", 3000, 8500},
        {"Jadhav Nagar", 1600, 4800}}}
        },

        {"Sambhaji Circle",{
        {{"Shivaji Nagar", 500, 2500},
        {"Sambhaji Circle", 900, 3200},
        {"Shivbasav Nagar", 1200, 3500},
        {"Ram Nagar", 2000, 5500},
        {"NCC Arts", 1000, 3300},
        {"Bharat Motor School", 3000, 8500},
        {"Jadhav Nagar", 1600, 4800}}}
        },

        {"Shivbasav Nagar",{
        {{"Shivbasav Nagar", 1200, 3500},
        {"Ram Nagar", 2000, 5500},
        {"NCC Arts", 1000, 3300},
        {"Bharat Motor School", 3000, 8500},
        {"Jadhav Nagar", 1600, 4800}}}
        },

        {"Ram Nagar",{
        {{"Sambhaji Circle", 900, 3200},
        {"Shivbasav Nagar", 1200, 3500},
        {"Ram Nagar", 2000, 5500},
        {"NCC Arts", 1000, 3300},
        {"Bharat Motor School", 3000, 8500},
        {"Jadhav Nagar", 1600, 4800}}}
        },

        {"NCC Arts",{
        {{"Shivbasav Nagar", 1200, 3500},
        {"Ram Nagar", 2000, 5500},
        {"Bharat Motor School", 3000, 8500},
        {"Jadhav Nagar", 1600, 4800}}}
        },

        {"Bharat Motor School",{
        {{"Sambhaji Circle", 900, 3200},
        {"Shivbasav Nagar", 1200, 3500},
        {"Ram Nagar", 2000, 5500},
        {"NCC Arts", 1000, 3300},
        {"Bharat Motor School", 3000, 8500},
        {"Jadhav Nagar", 1600, 4800}}}
        },

        {"Jadhav Nagar",{
        {{"Sambhaji Circle", 900, 3200},
        {"Shivbasav Nagar", 1200, 3500},
        {"Ram Nagar", 2000, 5500},
        {"NCC Arts", 1000, 3300},
        {"Bharat Motor School", 3000, 8500},
        {"Jadhav Nagar", 1600, 4800}}}
        },

        {"Sadashiv Nagar",{
        {{"Vengurla Road", 500, 2500},
        {"DC Bungalow Cross", 2000, 5500},
        {"Ambedkar Road", 900, 3200},
        {"Chennamma Circle - College Road", 1200, 3500},
        {"Vengurla Road - DC Bungalow", 1000, 3300},
        {"Rail Nagar South Cross", 3000, 8500}}}
        },

        {"Vengurla Road",{
        {{"Sadashiv Nagar", 200, 1800},
        {"Vengurla Road", 500, 2500},
        {"DC Bungalow Cross", 2000, 5500},
        {"Ambedkar Road", 900, 3200},
        {"Chennamma Circle - College Road", 1200, 3500},
        {"Vengurla Road - DC Bungalow", 1000, 3300},
        {"Rail Nagar South Cross", 3000, 8500}}}
        },

        {"DC Bungalow Cross",{
        {{"DC Bungalow Cross", 2000, 5500},
        {"Ambedkar Road", 900, 3200},
        {"Chennamma Circle - College Road", 1200, 3500},
        {"Vengurla Road - DC Bungalow", 1000, 3300},
        {"Rail Nagar South Cross", 3000, 8500}}}
        },

        {"Ambedkar Road",{
        {{"Sadashiv Nagar", 200, 1800},
        {"Vengurla Road", 500, 2500},
        {"DC Bungalow Cross", 2000, 5500},
        {"Ambedkar Road", 900, 3200},
        {"Chennamma Circle - College Road", 1200, 3500},
        {"Vengurla Road - DC Bungalow", 1000, 3300},
        {"Rail Nagar South Cross", 3000, 8500}}}
        },

        {"Chennamma Circle - College Road",{
        {{"DC Bungalow Cross", 2000, 5500},
        {"Ambedkar Road", 900, 3200},
        {"Chennamma Circle - College Road", 1200, 3500},
        {"Vengurla Road - DC Bungalow", 1000, 3300},
        {"Rail Nagar South Cross", 3000, 8500}}}
        },

        {"Vengurla Road - DC Bungalow",{
        {{"Vengurla Road", 500, 2500},
        {"DC Bungalow Cross", 2000, 5500},
        {"Ambedkar Road", 900, 3200},
        {"Chennamma Circle - College Road", 1200, 3500},
        {"Vengurla Road - DC Bungalow", 1000, 3300},
        {"Rail Nagar South Cross", 3000, 8500}}}
        },

        {"Rail Nagar South Cross",{
        {{"Vengurla Road", 500, 2500},
        {"DC Bungalow Cross", 2000, 5500},
        {"Ambedkar Road", 900, 3200},
        {"Chennamma Circle - College Road", 1200, 3500},
        {"Vengurla Road - DC Bungalow", 1000, 3300},
        {"Rail Nagar South Cross", 3000, 8500}}}
        }




        // You can define other areas similarly
    };

    // Display the areas in the selected zone
    displayAreas(selected_zone, zone_areas);

    // Ask the user to select an area
    cout << "\nEnter your choice (area number): ";
    int area_choice;
    cin >> area_choice;

    if (area_choice < 1 || area_choice > zone_areas[selected_zone].size()) {
        cout << "Invalid area choice" << endl;
        return 1;
    }

    // Get the name of the selected area
    string selected_area = zone_areas[selected_zone][area_choice - 1];
    cout << "You have selected " << selected_area << " as your area.\n";

    // Display the sub-division office and area details for the selected area
    displaySubDivisionDetails(selected_area, area_details);

    // Ask the user for their choice to find the nearest area
    cout << "\nEnter the Choice that you have selected for shortest distance: ";
    int user_choice;
    cin >> user_choice;

    string shortest_area = findShortestDistanceArea(area_details[selected_area].areas);
    cout << "You have selected " << shortest_area << " which is near to your location.\n";
    double outerDiameter, thickness;
    int segmentCount;
    string material;
    double density;

    // Select material
    cout << "Select material (polythene or steel): ";
    cin >> material;

    // Assign density based on material
    if (material == "polythene" || material == "Polythene") {
        density = 950; // kg/m^3 for polyethylene
    } else if (material == "steel" || material == "Steel") {
        density = 7850; // kg/m^3 for steel
    } else {
        cout << "Invalid material selected. Please choose 'polythene' or 'steel'." << endl;
        return 1;
    }

    // Input pipe specifications
    cout << "Enter the outer diameter of the pipe (in meters): ";
    cin >> outerDiameter;
    cout << "Enter the pipe wall thickness (in meters): ";
    cin >> thickness;

    // Input number of segments
    cout << "Enter the number of pipeline segments: ";
    cin >> segmentCount;

    vector<double> segmentLengths(segmentCount);
    double totalLength = 0.0;

    // Input lengths of each segment
    cout << "Enter the length of each segment (in meters):" << endl;
    for (int i = 0; i < segmentCount; i++) {
        cout << "Segment " << i + 1 << ": ";
        cin >> segmentLengths[i];
        totalLength += segmentLengths[i];
    }

    // Calculate total material volume and weight
    double totalVolume = 0.0;
    for (double length : segmentLengths) {
        totalVolume += calculatePipeVolume(length, outerDiameter, thickness);
    }
    double totalWeight = totalVolume * density;

    // Output results
    cout << "\nPipeline Material Usage Summary:" << endl;
    cout << "Material: " << material << endl;
    cout << "Total Length of Pipeline: " << totalLength << " meters" << endl;
    cout << "Total Material Volume: " << totalVolume << " cubic meters" << endl;
    cout << "Total Material Weight: " << totalWeight << " kilograms" << endl;
    string coatingType;


    double coatingThickness, coatingDensity;

    // Select coating type
    cout << "Select coating type (epoxy, polythene, plastic): ";
    cin >> coatingType;

    // Assign properties based on coating type
    if (coatingType == "epoxy") {
        coatingDensity = 1200; // kg/m
        coatingThickness = 0.005; // 5 mm
    } else if (coatingType == "polythene") {
        coatingDensity = 950; // kg/m
        coatingThickness = 0.01; // 10 mm
    } else if (coatingType == "plastic") {
        coatingDensity = 1050; // kg/m
        coatingThickness = 0.008; // 8 mm
    } else {
        cout << "Invalid coating type. Please choose 'epoxy', 'polythene', or 'plastic'." << endl;
        return 1;
    }

    // Input pipe specifications
    cout << "Enter the outer diameter of the pipe (in meters): ";
    cin >> outerDiameter;

    // Input number of pipeline segments
    cout << "Enter the number of pipeline segments: ";
    cin >> segmentCount;



    // Input lengths of each segment
    cout << "Enter the length of each segment (in meters):" << endl;
    for (int i = 0; i < segmentCount; i++) {
        cout << "Segment " << i + 1 << ": ";
        cin >> segmentLengths[i];
        totalLength += segmentLengths[i];
    }

    // Calculate total coating area and weight
    double totalSurfaceArea = 0.0;
    for (double length : segmentLengths) {
        totalSurfaceArea += calculateSurfaceArea(length, outerDiameter);
    }
    double coatingVolume = totalSurfaceArea * coatingThickness;
    double coatingWeight = coatingVolume * coatingDensity;

    // Output results
    cout << "\nCoating Material Usage Summary:" << endl;
    cout << "Coating Type: " << coatingType << endl;
    cout << "Total Length of Pipeline: " << totalLength << " meters" << endl;
    cout << "Total Surface Area: " << totalSurfaceArea << " square meters" << endl;
    cout << "Total Coating Volume: " << coatingVolume << " cubic meters" << endl;
    cout << "Total Coating Weight: " << coatingWeight << " kilograms" << endl;
    double pressure; // Variable to store the pressure in the pipeline

    // Input the pressure value
    cout << "Enter the pressure in the pipeline (in PSI): ";
    cin >> pressure;

    // Validate input
    if (pressure < 0)
    {
        cout << "Pressure cannot be negative. Please enter a valid value." << endl;
        return 1;
    }

    // Determine and display the pressure category
    string category = categorizePressure(pressure);
    cout << "The pipeline pressure is categorized as: " << category << endl;

 // Define safety thresholds
    const float pressureThreshold = 100.0;   // Pressure threshold in bar
    const float temperatureThreshold = 60.0; // Temperature threshold in  C
    const float leakThreshold = 5.0;         // Sensor reading threshold for leak detection

    // Input parameters
    float  temperature, sensorReading;

    // Gather input from the user
    cout << "Enter pipeline pressure (in bar): ";
    cin >> pressure;

    cout << "Enter pipeline temperature (in  C): ";
    cin >> temperature;

    cout << "Enter gas sensor reading: ";
    cin >> sensorReading;

    // Check pipeline safety
    bool isSafe = true;

    if (pressure > pressureThreshold) {
        cout << "Warning: Pressure exceeds safe limit! Current pressure: " << pressure << " bar" << endl;
        isSafe = false;
    }

    if (temperature > temperatureThreshold) {
        cout << "Warning: Temperature exceeds safe limit! Current temperature: " << temperature << "  C" << endl;
        isSafe = false;
    }

    // Leak detection
    if (sensorReading > leakThreshold) {
        cout << "Warning: Gas leak detected! Sensor reading: " << sensorReading << endl;
        isSafe = false;
    }

    // Final safety status
    if (isSafe) {
        cout << "The pipeline is operating within safe limits." << endl;
    } else {
        cout << "Pipeline safety compromised! Take immediate action!" << endl;
    }

     // Variables to hold user inputs
    float unitsUsed, ratePerUnit;

    // Gather input from the user
    cout << "Enter the number of gas units used: ";
    cin >> unitsUsed;

    cout << "Enter the rate per unit (in rupees): ";
    cin >> ratePerUnit;

    // Calculate bills
    float monthlyBill = unitsUsed * ratePerUnit;
    float quarterlyBill = monthlyBill * 3; // Quarterly means 3 months
    float yearlyBill = monthlyBill * 12;  // Yearly means 12 months

    // Display the results
    cout << "Monthly bill: " << monthlyBill << " rupees" << endl;
    cout << "Quarterly bill: " << quarterlyBill << " rupees" << endl;
    cout << "Yearly bill: " << yearlyBill << " rupees" << endl;



// Variables to hold user inputs
    float gasBill, taxRate, totalBill;
    string dueDate, paymentStatus;

    // Gather input from the user
    cout << "Enter the gas bill amount (in rupees): ";
    cin >> gasBill;

    cout << "Enter the tax rate (in percentage): ";
    cin >> taxRate;

    cout << "Enter the due date (e.g., 10-Jan-2025): ";
    cin >> dueDate;

    cout << "Has the bill been paid? (yes/no): ";
    cin >> paymentStatus;

    // Calculate total bill with tax
    float taxAmount = (gasBill * taxRate) / 100;
    totalBill = gasBill + taxAmount;

    // Display the total bill
    cout << "Base gas bill: " << gasBill << " rupees" << endl;
    cout << "Tax (" << taxRate << "%): " << taxAmount << " rupees" << endl;
    cout << "Total bill amount: " << totalBill << " rupees" << endl;

    // Check payment status
    if (paymentStatus == "yes") {
        cout << "Thank you! The bill has been paid on time." << endl;
    } else {
        cout << "The bill has not been paid. Due date was: " << dueDate << endl;
        cout << "Please pay the bill immediately to avoid penalties." << endl;
    }
    int eastHomes, westHomes, northHomes, southHomes;
    int eastUsage, westUsage, northUsage, southUsage;
    long long eastTotal, westTotal, northTotal, southTotal, grandTotal;

    // Input for the East zone
    cout << "Enter the number of homes in the East zone: ";
    cin >> eastHomes;
    cout << "Enter the average gas usage per home in the East zone (in units): ";
    cin >> eastUsage;

    // Input for the West zone
    cout << "Enter the number of homes in the West zone: ";
    cin >> westHomes;
    cout << "Enter the average gas usage per home in the West zone (in units): ";
    cin >> westUsage;

    // Input for the North zone
    cout << "Enter the number of homes in the North zone: ";
    cin >> northHomes;
    cout << "Enter the average gas usage per home in the North zone (in units): ";
    cin >> northUsage;

    // Input for the South zone
    cout << "Enter the number of homes in the South zone: ";
    cin >> southHomes;
    cout << "Enter the average gas usage per home in the South zone (in units): ";
    cin >> southUsage;

    // Calculate total usage for each zone
    eastTotal = static_cast<long long>(eastHomes) * eastUsage;
    westTotal = static_cast<long long>(westHomes) * westUsage;
    northTotal = static_cast<long long>(northHomes) * northUsage;
    southTotal = static_cast<long long>(southHomes) * southUsage;

    // Calculate the grand total
    grandTotal = eastTotal + westTotal + northTotal + southTotal;

    // Display the results
    cout << "\nTotal gas usage by zones:";
    cout << "\nEast zone: " << eastTotal << " units";
    cout << "\nWest zone: " << westTotal << " units";
    cout << "\nNorth zone: " << northTotal << " units";
    cout << "\nSouth zone: " << southTotal << " units";
    cout << "\n\nGrand Total gas usage across all zones: " << grandTotal << " units" << endl;

     // Variables for leak detection system parameters
    double monitoredPressure, maop, distanceFromStructures;
    string leakDetectionMethod, emergencyValveStatus;

    // Input parameters for leak detection system
    cout << "Enter the monitored pressure of the pipeline (in bar): ";
    cin >> monitoredPressure;
    cout << "Enter the Maximum Allowable Operating Pressure (MAOP) (in bar): ";
    cin >> maop;
    cout << "Enter the distance from other structures (in meters): ";
    cin >> distanceFromStructures;
    cout << "Enter the leak detection method used (e.g., Pressure Monitoring, Acoustic Sensors, Odorants): ";
    cin.ignore(); // Clear input buffer
    getline(cin, leakDetectionMethod);
    cout << "Is the emergency shutoff valve functional? (Yes/No): ";
    getline(cin, emergencyValveStatus);

    // Display the entered parameters
    cout << "\nGas Pipeline Leak Detection System Parameters:" << endl;
    cout << "-----------------------------------------------" << endl;
    cout << "Monitored Pressure: " << monitoredPressure << " bar" << endl;
    cout << "Maximum Allowable Operating Pressure (MAOP): " << maop << " bar" << endl;
    cout << "Distance from Other Structures: " << distanceFromStructures << " meters" << endl;
    cout << "Leak Detection Method: " << leakDetectionMethod << endl;
    cout << "Emergency Shutoff Valve Functional: " << emergencyValveStatus << endl;

    // Warning for exceeding MAOP
    if (monitoredPressure > maop) {
        cout << "\nWARNING: Monitored pressure exceeds MAOP! Immediate action required." << endl;
    }

    // Variables for geotechnical parameters
    string soilType, seismicActivityZone, terrainType;
    double waterTableLevel;

    // Input parameters
    cout << "Enter the soil type (e.g., Sandy, Clay, Rocky): ";
    getline(cin, soilType);
    cout << "Enter the seismic activity zone (e.g., Low, Moderate, High): ";
    getline(cin, seismicActivityZone);
    cout << "Enter the water table level (in meters): ";
    cin >> waterTableLevel;
    cin.ignore(); // Clear input buffer
    cout << "Enter the terrain type (e.g., Flat, Hilly, Mountainous): ";
    getline(cin, terrainType);

    // Display the entered parameters
    cout << "\nGeotechnical Parameters for Gas Pipeline System:" << endl;
    cout << "-----------------------------------------------" << endl;
    cout << "Soil Type: " << soilType << endl;
    cout << "Seismic Activity Zone: " << seismicActivityZone << endl;
    cout << "Water Table Level: " << waterTableLevel << " meters" << endl;
    cout << "Terrain Type: " << terrainType << endl;

    // Additional considerations based on inputs
    if (waterTableLevel < 1.5) {
        cout << "\nNOTE: High water table level detected. Additional corrosion protection may be required." << endl;
    }

    if (seismicActivityZone == "High")
    {
        cout << "WARNING: High seismic activity zone. Flexible pipeline design recommended." << endl;
    }

    if (terrainType == "Mountainous")
    {
        cout << "CAUTION: Mountainous terrain detected. Advanced stabilization methods may be necessary." << endl;
    }

     // Variables for environmental parameters
    double tempFluctuation, rainfall, snowDepth;
    string proximityToWaterBodies, landUse;

    // Input parameters
    cout << "Enter the temperature fluctuation (in degrees Celsius): ";
    cin >> tempFluctuation;
    cout << "Enter the annual rainfall (in mm): ";
    cin >> rainfall;
    cout << "Enter the snow depth during winter (in cm): ";
    cin >> snowDepth;
    cin.ignore(); // Clear input buffer
    cout << "Enter the proximity to water bodies (e.g., Close, Moderate, Far): ";
    getline(cin, proximityToWaterBodies);
    cout << "Enter the type of land use (e.g., Agricultural, Urban, Industrial): ";
    getline(cin, landUse);


    // Display the entered parameters
    cout << "\nEnvironmental Parameters for Gas Pipeline System:" << endl;
    cout << "-------------------------------------------------" << endl;
    cout << "Temperature Fluctuation: " << tempFluctuation << "  C" << endl;
    cout << "Annual Rainfall: " << rainfall << " mm" << endl;
    cout << "Snow Depth: " << snowDepth << " cm" << endl;
    cout << "Proximity to Water Bodies: " << proximityToWaterBodies << endl;
    cout << "Land Use: " << landUse << endl;


    // Additional considerations based on inputs
    if (tempFluctuation > 30)
    {
        cout << "\nNOTE: High temperature fluctuations detected. Consider thermal expansion measures." << endl;
    }

    if (proximityToWaterBodies == "Close")
    {
        cout << "CAUTION: Close proximity to water bodies. Ensure measures to prevent contamination." << endl;
    }

    if (landUse == "Agricultural")
    {
        cout << "ADVICE: Agricultural land detected. Take precautions to avoid disrupting farming activities." << endl;
    }
 // Variables for maintenance and inspection parameters
    string inspectionFrequency, repairMethods;
    int lifespan;

    // Input parameters
    cout << "Enter the inspection frequency (e.g., Monthly, Quarterly, Annually): ";
    getline(cin, inspectionFrequency);
    cout << "Enter the repair methods used (e.g., Welding, Clamp Repairs, Section Replacement): ";
    getline(cin, repairMethods);
    cout << "Enter the expected lifespan of the pipeline (in years): ";
    cin >> lifespan;

     // Display the entered parameters
    cout << "\nMaintenance and Inspection Parameters for Gas Pipeline System:" << endl;
    cout << "-------------------------------------------------------------" << endl;
    cout << "Inspection Frequency: " << inspectionFrequency << endl;
    cout << "Repair Methods: " << repairMethods << endl;
    cout << "Expected Lifespan: " << lifespan << " years" << endl;

    // Additional suggestions based on inputs
    if (inspectionFrequency == "Annually")
    {
        cout << "\nNOTE: Annual inspections may not be sufficient for high-risk areas. Consider more frequent checks." << endl;
    }

    if (lifespan < 20)
    {
        cout << "ADVICE: Short lifespan detected. Ensure regular maintenance and timely rehabilitation planning." << endl;
    }

    // Variables for regulatory and compliance parameters
    string standards, permits, odorization;

    // Input parameters
    cout << "Enter the standards and codes followed (e.g., ASME B31.8, ISO 9001): ";
    getline(cin, standards);
    cout << "Enter the status of permits and approvals (e.g., Approved, Pending): ";
    getline(cin, permits);
    cout << "Is odorization required? (Yes/No): ";
    getline(cin, odorization);

    // Display the entered parameters
    cout << "\nRegulatory and Compliance Parameters for Gas Pipeline System:" << endl;
    cout << "------------------------------------------------------------" << endl;
    cout << "Standards and Codes: " << standards << endl;
    cout << "Permits and Approvals: " << permits << endl;
    cout << "Odorization Requirement: " << odorization << endl;


    // Additional compliance checks
    if (permits == "Pending")
    {
        cout << "\nWARNING: Permits and approvals are pending. Ensure compliance before operation." << endl;
    }

    if (odorization == "No")
    {
        cout << "NOTE: Odorization is not enabled. Ensure alternative leak detection methods are in place." << endl;
    }
    // Variables for operational parameters
    string controlSystem, pressureRegulatingStation, meteringStation;

    // Input parameters
    cout << "Enter the control system used (e.g., SCADA, DCS): ";
    getline(cin, controlSystem);
    cout << "Enter the pressure regulating station details (e.g., Located at key points, Automated, Manual): ";
    getline(cin, pressureRegulatingStation);
    cout << "Enter the metering station details (e.g., Flow meters, Usage meters, Installed at intervals): ";
    getline(cin, meteringStation);

    // Display the entered parameters
    cout << "\nOperational Parameters for Gas Pipeline System:" << endl;
    cout << "-------------------------------------------------" << endl;
    cout << "Control System: " << controlSystem << endl;
    cout << "Pressure Regulating Station: " << pressureRegulatingStation << endl;
    cout << "Metering Station: " << meteringStation << endl;

    // Additional suggestions or checks based on inputs
    if (controlSystem == "SCADA")
    {
        cout << "\nNOTE: SCADA system detected. Ensure proper cybersecurity measures are in place for remote monitoring." << endl;
    }

    if (pressureRegulatingStation == "Manual")
    {
        cout << "WARNING: Manual pressure regulation detected. Consider automation for better control and efficiency." << endl;
    }

    if (meteringStation == "Installed at intervals")
    {
        cout << "ADVICE: Ensure metering stations are installed at regular intervals to maintain accurate usage data." << endl;
    }

    // Variables for risk assessment parameters
    string risks, hazardZone, integrityProgram;

    // Input parameters
    cout << "Enter potential risks (e.g., Leaks, Explosions, External Interference): ";
    getline(cin, risks);
    cout << "Enter the hazard zones (e.g., High Risk Areas, Earthquake-Prone Zones, Flood Zones): ";
    getline(cin, hazardZone);
    cout << "Enter the pipeline integrity management program (e.g., Regular Inspections, Cathodic Protection): ";
    getline(cin, integrityProgram);

     // Display the entered parameters
    cout << "\nRisk Assessment for Gas Pipeline System:" << endl;
    cout << "-----------------------------------------" << endl;
    cout << "Potential Risks: " << risks << endl;
    cout << "Hazard Zones: " << hazardZone << endl;
    cout << "Pipeline Integrity Management Program: " << integrityProgram << endl;


      // Additional risk management suggestions based on input
    if (risks.find("Leaks") != string::npos)
    {
        cout << "\nNOTE: Ensure effective leak detection systems are in place (e.g., sensors, pressure monitoring)." << endl;
    }

    if (hazardZone.find("Earthquake-Prone Zones") != string::npos)
    {
        cout << "ADVICE: Consider flexible pipeline designs and additional seismic protection measures." << endl;
    }

    if (integrityProgram.find("Cathodic Protection") != string::npos)
    {
        cout << "ADVICE: Ensure regular maintenance and checks of cathodic protection systems to prevent corrosion." << endl;
    }

    return 0;
}


