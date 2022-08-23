/*
author:
Name:Monica Saeed Habib
ID:20200567
Mirette Shenouda Maher
ID:20200575

*/
/**
Online shopping system
in this program we are trying to facilitate online shopping so we have infromation about the seller such as
his name, email and the maximum number of items he can stor
 we can create more than one seller and store (name ,email & items of seller with max capacity ) &
what he have items (id ,name ,price,quantity) can create more than item
and then we allow the user to enter some details about any product he wants to buy or sell
such as name, price, quantity if this product is already found within the seller so we increment it's quantity
if not and there is a space for it we add it with a new id
if we want to sell an item we just enter it's name and the quantity we want and if it's not available we will have a message
with the amount left from this item
if we want to access a certain item and know if it's available or not we enter it's id
and all details will appear such as quantity, name, id and price
we can also print the seller's info and the products he have in store
*/
#include <iostream>
using namespace std;
//class item is made to let the user enter the items he has in his store
class Item
{
private:
    static int IDCounter;   //static counter to count ID's items
    int ID;              //set an id to each item in store, once the item is entered by the seller the ID is given to it starting from 1
    string name;
    double quantity, price;    //quantity is the number of pieces the seller has for each item, price: is the price per unit for the item
    friend class Seller;        // friend class seller: class item can have access to the variables of of class item
public:
    Item();                        //default constructor created to give initial values to the attributes if the user didn't enter any
    Item(string n,double q,double p);    //parametrized constructor to give values for the name, quantity and price attributes
    Item(const Item& obj);              // copy constructor to copy all attribute (except ID count new) from obj to new item
    friend ostream & operator<<(ostream& os, const Item& I);   //header of insertion operator to be overloaded
    friend istream & operator>>(istream& is,Item& I);           //header of extraction operator to be overloaded
    void operator+=(Item & I);                               //overloading += operator
    void operator-=(const double num);                             //overloading -=operator
    bool operator==(const Item & I);                       //overloading == operator
    //setters and getters of the name,ID,price,quantity attributes
    void setName(string name);
    void setID(int ID);
    void setprice(double price);
    void setQuantity(double quantity);

    string getName();
    int getID();
    double getprice();
    double getQuantity();

};
int Item::IDCounter=0;        //initialization of the static member variable IDCounter

Item::Item()             //default constructor
{
    IDCounter +=1;        //increment ID by one once the default constructor is called
    ID=IDCounter;
    name = "not found";
    quantity = 0;
    price = 0;
}
Item::Item(string n,double q,double p)        //parametrized constructor
{
    IDCounter +=1;
    ID=IDCounter;
    name = n;
    quantity = q;
    price = p;
}
Item::Item(const Item& obj)    //copy constructor
{
    IDCounter +=1;
    ID = IDCounter;  //count new ID
    name = obj.name;
    quantity = obj.quantity;
    price = obj.price;
}
//setters and getters of the name,ID,price,quantity attributes
void Item::setName(string name)
{
    this->name=name;
}
void Item::setID(int ID)
{
    this->ID=ID;
}
void Item::setprice(double price)
{
    this->price=price;
}
void Item::setQuantity(double quantity)
{
    this->quantity=quantity;
}

string Item::getName()
{
    return name;
}
int Item::getID()
{
    return ID;
}
double Item::getprice()
{
    return price;
}
double Item::getQuantity()
{
    return quantity;
}

void Item::operator+=(Item & I)
 /* If the item already exists in the seller's items you will increase the item's
quantity by the quantity of the parameter item*/
{
    quantity+=I.quantity;
    double x=quantity;     //x variable store new quantity to set it in item's quantity
    setQuantity(x);
    I.setQuantity(0);
}
void Item::operator-=(const double num)
 /*-= operator used when the user asks for a certain amount of an item
If the quantity he wants is <= item’s quantity you will decrease it from item*/
{
    quantity-=num;
}
bool Item::operator==(const Item & I)    //compares the the item's name that we wants to add with the item's name that the seller already have
{
    if(name==I.name) return true;
    else return false;
}
/* class seller has a dynamic array of objects of type item with the maximum size that the seller can store it stores the items that the seller has and increments their quantity if their is addition by using += operator
 and decrement their quantity if he sold some of them by using -= operator , and by using == we compare the name of the item added or the item he wants to sell
with the items he already has */

class Seller
{
private:
    string name, email;
    Item *items;
    int maxItems;
    int Count=0; //count the added items
public:
    Seller(string name,string email,int maxItems);
    friend ostream & operator<<(ostream& os, const Seller& s);
    bool AddItem(Item& obj);
    bool SellItem(string n,double q);
    void printItem();
    Item* FindItem(int ID);
    ~Seller();

};
Seller::Seller(string name,string email,int maxItems)
{
    this->name=name;
    this->email=email;
    this->maxItems=maxItems;
    items=new Item[maxItems];
    items->IDCounter-=maxItems;
}
/*additem has a return type boolean that indicates the successful
addition of item, which will succeed if there is a place in the array and fail
otherwise.*/
bool Seller::AddItem(Item& obj)
{
    bool check=false;
    for(int i=0; i<Count; i++)
    {
        if(obj.name==items[i].name)
        {
            items[i].quantity+=obj.quantity;
            items[i].IDCounter--;
            check=true;
            break;
        }
    }
// if check = false which means this object isn't already found in the array so we added the item in it
    if(check==false)
    {
        items[Count].name=obj.name;
        items[Count].ID=obj.getID();
        items[Count].quantity=obj.quantity;
        items[Count].price=obj.price;
        Count+=1;
    }
    return check;
}
/*SellItem will take an item name and a quantity as parameters
- If the quantity is <= item’s quantity you will decrease it from item Using
the (-=) in Item class.
- Else we will print him a message with the only left quantity.
- The member function should return a boolean which is true if the item was
found, false otherwise.*/
bool Seller::SellItem(string n,double q)
{
    bool check = false;       //boolean equal true only inside the if statement
    for(int i=0; i<Count; i++)
    {
        if(items[i].name==n)
        {
            if(items[i].quantity>=q)
            {
                items[i].quantity -= q;
                break;
            }
            else
            {
                cout<<"There is only "<<items[i].quantity<<" left for "<<items[i].name<<endl;
            }
            check = true;
        }
    }
    if(check==true)
    {
        return check;
    }
    else
    {
        cout<< "the item does not exist"<<endl;
        return check;
    }

}
/*This will print all the item information for the seller.
You by using the (<<) operator.*/
void Seller::printItem()
{
    for(int i=0; i<Count; i++)
    {
        cout<<items[i];
    }
    cout<<endl;
}
/*This returns an Item object with the specified ID if
there is an item with such ID.*/
Item* Seller::FindItem(int ID)
{
    for(int i=0; i<Count; i++)
    {
        if(items[i].ID==ID)
        {
            return &items[i];
        }
    }
    cout<<"Not found"<<endl;
}
Seller::~Seller()    //destructor that frees the memory
{
    delete [] items;
}
/*overloading the insertion operator to print details about the items */
ostream & operator<<(ostream& os, const Item& I)
{
    os<<"Product name: "<<I.name<<endl;
    os<<"ID: "<<I.ID<<endl;
    os<<"Quantity = "<<I.quantity<<endl;
    os<<"Price = "<<I.price<<endl;
    os<<endl;
    return os;
}
/*overloading extraction operator to let the user enter details of the item object  */
istream & operator>>(istream& is,Item& I)
{
    cout<<"Enter item's name: ";
    is>>I.name;
    cout<<"Enter quantity = ";
    is>>I.quantity;
    cout<<"Enter price = ";
    is>>I.price;
    cout<<endl;
    return is;
}
//used to print the details about the seller such as his name, email and maximum number of items he can store/
ostream & operator<<(ostream& os, const Seller& s)
{
    os<<"Seller's name: "<<s.name<<endl;
    os<<"Seller's email: "<<s.email<<endl;
    os<<"Maximum number of items: "<<s.maxItems<<endl;
    os<<s.items;
    os<<endl;
}


int main()
{
    string Seller_Name, Seller_email;
    int maxITEMS;
    cout<<"Please enter your name and your email"<<endl;
    cin>> Seller_Name;
    cin>>Seller_email;
    cout<<"Store capacity (maxNumberOfItems)"<<endl;
    cin>>maxITEMS;
    Seller s1(Seller_Name,Seller_email,maxITEMS);
    //menu to show available options in this application for users
    cout<<"Choose a number from 1 to 6 according to the option you want"<<endl;
    cout<<"1.Print my info"<<endl;
    cout<<"2.Add An Item"<<endl;
    cout<<"3.Sell An Item"<<endl;
    cout<<"4.Print Items"<<endl;
    cout<<"5.Find an Item by ID"<<endl;
    cout<<"6.Exit"<<endl;
    cout<<endl;
    int x;                          //the number that the user will choose
    cout<<"Enter the number you've chosen: ";

    //do while loop is formed so the user can choose more than 1 option and it will only terminate if the user chooses to exit the program/
    do
    {
        cin>>x;
        if(x==1)        //when the user enters 1 the seller's details will be printed by using insertion operator
                cout<<s1;
            else if (x==2)         //if he chooses 2 this will let him add objects to the items array
            {
                Item I1;
                cin>>I1;
                s1.AddItem(I1);
            }
            else if (x==3)       // if he chooses 3 it will let him sell items by the amount of quantity he ask for
            {
                string ProductNeeded;     //he will enter the name and the amount he wants of a certain product
                double ProductQuantity;
                cout<<"What do you want to buy ? and how much?"<<endl;
                cin>>ProductNeeded>>ProductQuantity;
                s1.SellItem(ProductNeeded, ProductQuantity);
            }
            else if (x==4)   //it will print the items inside the array
            {
                s1.printItem();
            }
            else if (x==5)  // the user will enter the ID of the item object he wants to know it's details
            {
                int id;
                cout<<"Enter the ID of the product needed"<<endl;
                cin>>id;
                cout<<*s1.FindItem(id);
            }
            else if(x==6)  // exit the program if he's done
            {
                cout<<"Thank you for using our online shopping application"<<endl;
                exit(1);
            }
            cout<<"Enter another number : ";

        }while(x!=6);

    return 0;
}
