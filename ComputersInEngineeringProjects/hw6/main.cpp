////////////////////////////////////////////////////////////////////////////////////
//// Programer: Rafael Rangel                                                   ////
//// Date: 04/04/2021                                                           ////
//// Project: hw6                                                               ////
//// Description: modified code from zybook figure 11.1.2 with added            ////
//// copy constructors, copy assignment operators, destructors and inheritance. ////
////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <string>

using namespace std;

class Business {
public:

    //constructor for the Business class with default values for all data members
    explicit Business(string c_name = "no name assigned", string c_address = "no address assigned", int c_maxOccupancy = -1):
    name(c_name),address(c_address){
        if (maxOccupancy == nullptr){
            maxOccupancy = new int;
            cout<<"The memory address is at"<<static_cast<void*>(maxOccupancy)<<endl; //line to check for memory leaks, for these must be in pairs one for the new and one for delete
                                                                                        //print the allocated memory address, check for corresponding memory address when deleted
            if (maxOccupancy!= nullptr){
                *maxOccupancy = c_maxOccupancy;
            }
        }
        else
        {
            *maxOccupancy = c_maxOccupancy;
        }
        cout << "constructor for business class called" << endl;
    }

    //destructor of the business class that frees the MaxOccupancy memory
    ~Business(){
        cout<<"The memory address is at"<<static_cast<void*>(maxOccupancy)<<endl; //line to check for memory leaks, deleted memory address
        delete maxOccupancy;
        cout << "Business destructor called " << endl;
    }

    //copy constructor for the business class
    Business(const Business& origBusiness){
        cout << "copy constructor for business called" << endl;
        name = origBusiness.name;
        address = origBusiness.address;
        maxOccupancy = new int;
        cout<<"The memory address is at"<<static_cast<void*>(maxOccupancy)<<endl; //line to check for memory leaks
        *maxOccupancy = *(origBusiness.maxOccupancy);
    }

    //copy assignment operator
    Business& operator=(const Business& businessObjToCopy){
        cout << "Business copy assignment operator called" << endl;
        if (this != &businessObjToCopy){
            name = businessObjToCopy.name;
            address = businessObjToCopy.address;
            cout<<"The memory address is at"<<static_cast<void*>(maxOccupancy)<<endl; //line to check for memory leaks
            delete maxOccupancy; //delete old maxOccupancy
            cout<<"The memory address is at"<<static_cast<void*>(maxOccupancy)<<endl; //line to check for memory leaks
            maxOccupancy = new int; //allocate new maxOccupancy
            *maxOccupancy = *(businessObjToCopy.maxOccupancy);
        }
        return *this;
    }

    //public method name: setName
    //Description: takes in a string from the user to assign to the name private data member
    //input: sting busName
    //output: none, its of type void
    void SetName(string busName) {
        name = busName;
    }

    //public method name: setAddress
    //Description: takes in a string from the user to assign it to the address private data member
    //input: sting busAddress
    //output: none, its of type void
    void SetAddress(string busAddress) {
        address = busAddress;
    }

    //public method SetMaxOccupancy
    //Descriptions: takes in an integer that will be the max occupancy value stored in the pointer memory address
    //input: integer
    //output: none, its of type void
    void SetMaxOccupancy(const int busMaxOccupancy)
    {
        if (maxOccupancy == nullptr){
            maxOccupancy = new int;
            cout<<"The memory address is at"<<static_cast<void*>(maxOccupancy)<<endl; //line to check for memory leaks
            if (maxOccupancy!= nullptr){
                *maxOccupancy = busMaxOccupancy;
            }
        }
        else {
            *maxOccupancy = busMaxOccupancy;
        }

    }

    //public method GetDescription
    //Description: when called it returns the string held in name and in address along with a set of --
    //input: none
    //output: string connotation of the strings contained in the private data members name and address, and a set of --
    string GetDescription() const {
        return name + " -- " + address;
    }

    //public method GetName
    //Description: method that returns the string assigned to the name member variable
    //input: none
    //Output: string assigned to the name private member
    string GetName()const
    {
        return name;
    }

    //public method GetAddress
    //Description: when called it returns the contained string in address member
    //input: none
    //Output: string private data member address
    string GetAddress()const
    {
        return address;
    }

    //public method GetMaxOccupancy
    //Description: when called it returns the data to which the maxOccupancy protected pointer member points
    //input: none
    //Output: int containing the data to which maxOccupancy points to
    int GetMaxOccupancy() const{
        return *maxOccupancy;
    }

    //public print method for the business class
    //Description: when called it displays to the screen the values of the member variables
    //input: none
    //output: void function, it doesn't return anything, it just prints to the screen
    void printBusiness() const{
        cout << "name: " << name << endl
            << "address: " << address << endl
            << "max occupancy: " << *maxOccupancy << endl;
    }

    //business class private data members - private means that only the business class can access these members directly
private:
    string name;
    string address;

protected:
    int* maxOccupancy = nullptr;
};

//Restaurant class is a derived class inheriting from the Business class
class Restaurant : public Business {
public:

    //Restaurant class constructor, it calls the business constructor
    explicit Restaurant(string r_name = "unknown restaurant",string r_address = "no address", int r_maxOccupancy = -1,int r_rating = 0):
    Business(r_name,r_address,r_maxOccupancy),rating(r_rating){cout << "Restaurant constructor called" << endl;};

    //destructor of the Restaurant class, since the base class constructor already frees up the maxOccupancy pointer, no delete statement is needed
    ~Restaurant(){
        cout << "Restaurant destructor called" << endl;
    }

    //copy constructor for the Restaurant class
    Restaurant(const Restaurant& origRestaurant):Business(origRestaurant.GetName(),origRestaurant.GetAddress(),origRestaurant.GetMaxOccupancy()){
        cout << "Restaurant copy constructor called" << endl;
        rating = origRestaurant.GetRating();
    }

    //copy assignment operator
    Restaurant& operator=(const Restaurant& restaurantObjectToCopy){
        cout << "Restaurant copy assignment operator called " << endl;
        if (this != &restaurantObjectToCopy){
           Business::operator=(restaurantObjectToCopy);
            rating = restaurantObjectToCopy.rating;
        }
        return *this;
    }

    //public method SetRating
    //Description: takes in an integer and assigns it to the rating member variable
    //input: int userRating
    //output: none, its a void function
    void SetRating(int userRating) {
        rating = userRating;
    }

    //public method GetRating
    //Description: when called it returns the value of the rating private data member
    int GetRating() const {
        return rating;
    }

    //public print method for the Restaurant class which calls a business method
    //Description: when called it displays to the screen the values of the member variables of the object
    //input: none
    //output: void function, it doesn't return anything, it just prints to the screen
    void printRestaurant() const{
        printBusiness(); //call printBusiness method, possible because it is a public method of the base class
        cout << "rating: " << rating << endl;
    }

    //private data member accesible directly to the Restaurant class only
private:
    int rating;
};

int main() {
    Business someBusiness; //create business object
    Restaurant favoritePlace; //create restaurant object

    //Use setters of the Business class to set the private data members of the someBusiness Business object
    someBusiness.SetName("ACME");
    someBusiness.SetAddress("4 Main St");

    //Set private data members of the favorite place Restaurant object
    favoritePlace.SetName("Friends Cafe"); // inherited name setter from the base class to set the also inherited name data member
    favoritePlace.SetAddress("500 W 2nd Ave"); // inherited address setter from the base class to set the also inherited name data member address
    favoritePlace.SetRating(5); //setter from the Restaurant class

    //Print the data member values of the objects ussing the Business class getter and the Restaurant class getter
    cout << someBusiness.GetDescription() << endl;
    cout << favoritePlace.GetDescription() << endl; //usage of inherited getter from the Bussiness class to print the data members of the someBusiness object
    cout << "  Rating: " << favoritePlace.GetRating() << endl;

    //test my added code
    cout << "----------------------------------------------------------------" << endl;
    cout << "Added code to test " << endl;

    //Business constructor test
    cout << "----------------------------------------------------------------" << endl;
    Business firstBusiness("Batman gear","Gotham city ", 20);
    //print Business method test
    firstBusiness.printBusiness();

    cout << "----------------------------------------------------------------" << endl;
    //test setters and getters for the Business class
    firstBusiness.SetName("Nightwing gear");
    firstBusiness.SetAddress("chicago");
    firstBusiness.SetMaxOccupancy(10);
    cout << firstBusiness.GetName() << endl;
    cout << firstBusiness.GetAddress() << endl;
    cout << firstBusiness.GetMaxOccupancy() << endl;

    cout << "----------------------------------------------------------------" << endl;
    //Restaurant constructor test
    Restaurant firstRestaurant("Heroes dining","1415 Tecno Ave",44,4);
    //print Restaurant Method function
    firstRestaurant.printRestaurant();

    cout << "----------------------------------------------------------------" << endl;
    Restaurant secondRestaurant;
    secondRestaurant.printRestaurant(); //further test constructor

    cout << "----------------------------------------------------------------" << endl;
    //setters and getters test on derived class Restaurant
    secondRestaurant.SetName("Villains dining");
    secondRestaurant.SetAddress("1010 bad Ave");
    secondRestaurant.SetMaxOccupancy(22);
    secondRestaurant.SetRating(4);
    cout << secondRestaurant.GetName() << endl;
    cout << secondRestaurant.GetAddress() << endl;
    cout << secondRestaurant.GetMaxOccupancy() << endl;
    cout << secondRestaurant.GetRating() << endl;

    cout << "----------------------------------------------------------------" << endl;
    Business secondBusiness(firstBusiness); //business copy constructor test
    secondBusiness.printBusiness(); //should print out nightwing business, because it was changed using the seters and getters

    cout << "----------------------------------------------------------------" << endl;
    Restaurant thirdRestaurant(firstRestaurant);//restaurant copy constructor test
    thirdRestaurant.printRestaurant(); //should print out heroes dining restaurant

    cout << "----------------------------------------------------------------" << endl;
    firstBusiness = someBusiness; //business copy assignment operator test
    firstBusiness.printBusiness(); //should print out the acme business with max occupancy = -1 because this was not set for this business

    cout << "----------------------------------------------------------------" << endl;
    firstRestaurant = favoritePlace; //restaurant copy assignment operator test
    firstRestaurant.printRestaurant(); //should print out the Friends cafe restaurant with max occupancy = -1 because this was not set for this restaurant


    cout << "----------------------------------------------------------------" << endl;
    cout << "all tests passed" << endl;
    cout << "below check that all memory addresses were cleared" << endl;
    return 0;
}

