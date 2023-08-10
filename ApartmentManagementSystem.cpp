#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>

using namespace std;

struct apartment {
    int number;
    float monthly_rent;
    int max_tenants;
    int num_tenants;
    string tenants[10];
};

void load(string fname, apartment apartments[], int &num) {
    ifstream inFS;
    int i;
    int j;
    inFS.open(fname);
    inFS >> num;
    for(i=0; i<num; i++) {
        inFS >> apartments[i].number;
        inFS >> apartments[i].monthly_rent;
        inFS >> apartments[i].max_tenants;
        inFS >> apartments[i].num_tenants;
        inFS.ignore();
        for(j=0; j<apartments[i].num_tenants; j++){
            getline(inFS, apartments[i].tenants[j]);
        }
    }
    inFS.close();
    for( i=0; i<num; i++) {
        for (j=0; j<num-1; j++){
            if(apartments[j].monthly_rent > apartments[j+1].monthly_rent) {
                apartment temp = apartments[j];
                apartments[j] = apartments[j+1];
                apartments[j+1] = temp;
            }
        }
    }
}


void save(string fname, apartment apartments[], int num) {
    ofstream outFS;
    outFS.open(fname);
    int i, j;
    outFS << num << endl;
    for(i=0; i<num; i++) {
        outFS << apartments[i].number << endl;
        outFS << apartments[i].monthly_rent << endl;
        outFS << apartments[i].max_tenants << endl;
        outFS << apartments[i].num_tenants << endl;
        for(j=0; j<apartments[i].num_tenants; j++) {
            outFS << apartments[i].tenants[j] << endl;
        }
    }
    outFS.close();
}

void list_all_apartments(apartment apartments[], int num) {
    int i, j;
    int available = 0;
    int occupied = 0;
    int totalRent = 0;
    for(i=0; i<num; i++) {
        cout << "Apartment #" << apartments[i].number << ":" << endl;
        cout << "Monthly Rent: $" << apartments[i].monthly_rent << endl;
        cout << "Max # of tenants: " << apartments[i].max_tenants << endl;
        cout << "Number of Tenants: " << apartments[i].num_tenants << endl;
        if(apartments[i].num_tenants == 0) {
            available += 1;
        }
        if(apartments[i].num_tenants != 0) {
            totalRent += apartments[i].monthly_rent;
            cout << "Tenants: ";
            for(j=0; j<apartments[i].num_tenants - 1; j++) {
                cout << apartments[i].tenants[j] << ", ";
            }
                cout << apartments[i].tenants[apartments[i].num_tenants - 1];
                cout << endl;
                occupied += 1;
        }
        cout << "---" << endl;
    }
    cout << "Total Monthly Rent Collected: $" << totalRent << endl;
    cout << "Number of occupied units: " << occupied << "/" << num << endl;
    cout << "---" << endl;

}

void list_available_apartments(apartment apartments[], int num) {
int i;
for(i=0; i<num; i++) {
    if(apartments[i].max_tenants > apartments[i].num_tenants) {
         cout << "Apartment #" << apartments[i].number << ":" << endl;
        cout << "Monthly Rent: $" << apartments[i].monthly_rent << endl;
        cout << "Max # of Tenants: " << apartments[i].max_tenants << endl;
        cout << "---" << endl;
        }
    }
}

void find_tenant(string tenant_name, apartment apartments[], int num) {
    int i;
    int j;
    int index;
    bool found = false;
    for(i=0; i<num; i++) {
        for(j=0; j<apartments[i].num_tenants; j++) {
            if(tenant_name == apartments[i].tenants[j] ) {
                found = true;
                index = i;
            }
        }

    }
    if(found) {
        cout << tenant_name << " is in apartment #" << apartments[index].number << "!" << endl;
    }
    else if(!found) {
        cout << "Error, tenant not found!" << endl;
    }
}

void move_in(string tenant_name, int apartment_num, apartment apartments[], int num_apartments) {
    int index = -1;
    for (int i = 0; i < num_apartments; i++) {
        if (apartments[i].number == apartment_num) {
            index = i;
        }
    }
    if (index == -1) {
        cout << "Error, the apartment cannot hold any more tenants!" << endl;
        }
    else if(apartments[index].max_tenants > apartments[index].num_tenants) {
        apartments[index].tenants[apartments[index].num_tenants] = tenant_name;
        apartments[index].num_tenants += 1;
        cout << "Successfully moved in!" << endl; 
    }
    else if(apartments[index].max_tenants == apartments[index].num_tenants){
        cout << "Error, the apartment cannot hold any more tenants!" << endl;
    }
}

void move_out(string tenant_name, apartment apartments[], int num_apartments) {
    int i;
    int j;
    int k;
    bool found = false;
    for(i=0; i<num_apartments; i++) {
        for(j=0; j<apartments[i].num_tenants; j++) {
            if(tenant_name == apartments[i].tenants[j] ) {
                found = true;
                if (j == apartments[i].num_tenants - 1) {
                    apartments[i].tenants[j] = "";
                }
                else{
                    for (k = j; k < apartments[i].num_tenants - 1; k++) {
                    apartments[i].tenants[k] = apartments[i].tenants[k + 1];
                    apartments[i].tenants[apartments[i].num_tenants - 1] = "";
                    }
                }
                apartments[i].num_tenants -= 1;
                break;
            }
        }

    }
    if(found) {
        cout << "Successfully moved out." << endl;
    }
    else if(!found) {
        cout << "Error, there are no tenants with that name!" << endl;
    }
}




int main() {
    string fname;
    cout << "Please enter the name of the file to load:" << endl;
    cin >> fname;
    apartment appts[10];
    int num = 0;
    load(fname, appts, num);
    list_all_apartments(appts, num);
    int option;
    while (cin >> option) {
        cout << "Main Menu" << endl;
        cout << "1- List All Apartments" << endl;
        cout << "2- List Available Apartments" << endl;
        cout << "3- Move In" << endl;
        cout << "4- Move Out" << endl;
        cout << "5- Find Tenant" << endl;
        cout << "6- Save" << endl;
        cout << "7- Load" << endl;
        cout << "8- Exit" << endl;
        cout << "Please enter your choice:" << endl;
    
        if (option == 1) {
            list_all_apartments(appts, num);
        }

        else if(option == 2){
            list_available_apartments(appts, num);
        }

        else if(option == 3){
            int apt_num;
            string tenant_name;
            cout << "Enter the apartment number to move in:" << endl;
            cout << "Enter the name of the tenant:" << endl;
            cin >> apt_num;
            cin.ignore();
            getline(cin, tenant_name);
            move_in(tenant_name, apt_num, appts, num);
        }

        else if(option == 4){
            string tenant_name;
            cout << "Enter the name of the tenant moving out:" << endl;
            cin.ignore();
            getline(cin, tenant_name);
            move_out(tenant_name, appts, num);
        }

        else if(option == 5){
            string tenant_name;
            cout << "Enter the name of the tenant to search for:" << endl;
            cin.ignore();
            getline(cin, tenant_name);
            find_tenant(tenant_name, appts, num);
        }

        else if(option == 6){
            string save_file;
            cout << "Enter the file name to save to: " << endl;
            cin >> save_file;
            save(save_file, appts, num);
        }

        else if(option == 7){
            string load_file;
            cout << "Enter the file name to load from: " << endl;
            cin >> load_file;
            num = 0;
            load(load_file, appts, num);
        }

        else if(option == 8){
            break;
        }

        else {
            cout << "Invalid option!" << endl;
        }
    }
    return 0;
}