/*authors:
Name: Mirette Shenouda Maher   ID:20200575
      Monica Saeed Habib          20200567
lab: S25
*/

#include <iostream>
#include <fstream>

using namespace std;

class FloatArray      ///class FloatArray allocates the memory to store the input array from the file the user choose
{
private:
    float *arr;
    int sz;
    int counter;        //to count the number of elements inside the array and set another element * starting from zero element
public:
    FloatArray(int sz){         //parametrized constructor that takes the array size
        this->sz=sz;
        arr=new float[sz];
        counter=0;          //to set the counter by zero when a new object is created
    }
    //write to file and to read from file
    friend ofstream& operator<<(ofstream& os, const FloatArray& F);
    friend ifstream& operator>>(ifstream& is, const FloatArray& F);

    virtual void add(float elem){          //function add which adds the elements from the file in the array
        arr[counter]=elem;
        counter++;
    }
    //get and set array element
    float getArrElement(int index){
        return arr[index];
    }
    void setArrElement(int index,float x){
        arr[index]=x;
    }

    void setSZ(int sz){           //size setter
        this->sz=sz;
    }

    virtual ~FloatArray(){     //destructor to delete the array and free the memory
        delete [] arr;
    }
};
class SortedArray:public FloatArray        ///class SortedArray reads the array that wants to be sorted from the input file
{
private:
    int sz2;
    int counter;  //to sort after adding a new element
public:
    SortedArray(int sz2):FloatArray(sz2){     //parametrized constructor that takes the array size
        this->sz2=sz2;
        counter=0;
    }
    void setSZ2(int sz2){
        this->sz2=sz2;
    }
     virtual void add(float elem){      ///it swaps the values until it is finally arranged ascendingly
        counter++;
        FloatArray::add(elem);
        for(int i=0; i<counter; i++){
            for(int j=0; j<i; j++){
                if(getArrElement(i) < getArrElement(j)){
                    ///swap arr[i] with arr[j]
                    float temp=getArrElement(i);
                    setArrElement(i,getArrElement(j));
                    setArrElement(j,temp);
                }
            }
        }
    }
};
class FrontArray:public FloatArray  /// class FrontArray to set element by element from right to left
{
private:
    int sz3;
    int counter;          //to get the final index from the array
public:
    FrontArray(int sz3):FloatArray(sz3){    //parametrized constructor that takes the array size
        this->sz3=sz3;
        counter=sz3-1;
    }
    void add(float elem){           ///An add method that adds a float at the front of the array.
        setArrElement(counter,elem);
        counter--;
    }
};
class PositiveArray:public SortedArray        ///class positive array that ony keeps the positive values in the given array,sort and set the size from size these values
{
private:
    int sz4;
    int counter;   //to count the number of positive values
public:
    PositiveArray(int sz4):SortedArray(sz4){         //parametrized constructor that takes the array size
        this->sz4=sz4;
        counter=0;
    }
    void add(float elem){               /*An add method that adds a float to the array only if it’s a positive number.
                                         It then uses the add method of SortedArray*/
        if(elem>0){
            SortedArray::add(elem);
            counter++;
        }
        sz4=counter;
        setSZ(counter);
        setSZ2(counter);
    }

};
class NegativeArray:public SortedArray  ///class negative array that ony keeps the negative values in the given array,sort and set the size from size these values
{
private:
    int sz5;
    int counter;      //to count the number of negative values
public:
    NegativeArray(int sz5):SortedArray(sz5){         //parametrized constructor that takes the array size
    this->sz5=sz5;
    counter=0;
    }
    void add(float elem){                               /*An add method that adds a float to the array only if it’s a
                                                        negative number. It then uses the add method of SortedArray.*/
        if(elem<0){
            SortedArray::add(elem);
            counter++;
        }
        sz5=counter;
        setSZ(counter);
        setSZ2(counter);
    }
};
ofstream& operator<<(ofstream& out, const FloatArray& F)     //overloading of the insertion operator << to write the array to a file (ofstream)
{
    if(out){
        out<<F.sz<<"|"<<"   ";
        for(int i=0;i<F.sz;i++){
            out<<F.arr[i]<<"    ";
        }
        out<<endl;
    }
    return out;
}
ifstream& operator>>(ifstream& in, const FloatArray& F)    //Overloading for the extraction operator >> to read the array
                                                           // elements from the file (ifstream) and add them to the array.
{
    while(in){
        in>>F.sz;
        for(int i=0;i<F.sz;i++){
            in>>F.arr[i];
        }
    }
    return in;
}
int main()
{
    cout<<"Enter the name of the input file:"<<endl;   //let the user enter the name of the input file
    string name1,name2;
    cin>>name1;
    ifstream file(name1.c_str());
    while(!file){         //if the file is not found exit the program
        cout<<"file not found"<<endl;
        return 0;
    }
    cout<<"Enter the name of the output file:"<<endl;      //let the user write the name of the output file
    cin>>name2;
    ofstream fileOut(name2.c_str());

    FloatArray* Array[10];         //polymorphism
    FloatArray* ptr;              //pointer to an object
    for(int j=0;j<10;j++)
    {
        string type;        //this string is used to know which class we should use
        int SIZE;           //and the SIZE variable reads the number written beside each string that express the number of elements in each array
        file>>type;
        file>>SIZE;
        if(type=="Array"){                // create new object of class FloatArray and adds elements to it
            ptr= new FloatArray(SIZE);
            for(int i=0;i<SIZE ;i++){
                float element ;
                file>>element;
                ptr->add(element);
            }
            fileOut<<*ptr;
        }
        else if(type=="Sorted"){    // create new object of class SortedArray and adds elements to it and also sort them
            ptr= new SortedArray(SIZE);
            for(int i=0;i<SIZE ;i++){
                float element ;
                file>>element;
                ptr->add(element);
            }
            fileOut<<*ptr;
        }
        else if(type=="Front"){      // create new object of class FrontArray and adds elements to it but from left handside (front) i.e. last element become the first element
            ptr= new FrontArray(SIZE);
            for(int i=0;i<SIZE ;i++){
                float element ;
                file>>element;
                ptr->add(element);
            }
            fileOut<<*ptr;
        }
        else if(type=="Positive"){       // create new object of class PositiveArray and adds only the positive elements to it without zero
            ptr= new PositiveArray(SIZE);
            for(int i=0;i<SIZE ;i++){
                float element ;
                file>>element;
                ptr->add(element);
            }
            fileOut<<*ptr;
        }
        else{
            ptr= new NegativeArray(SIZE);   // create new object of class NegativeArray and adds elements to it which are negative elements
            for(int i=0;i<SIZE ;i++){
                float element ;
                file>>element;
                ptr->add(element);
            }
            fileOut<<*ptr;
        }
    }
    for(int i=0 ;i<10 ;i++){
        ptr= Array[i];
    }
    //to delete dynamic Array
    for(int i=0 ;i<10 ;i++){
        delete Array[i];
    }

    return 0;
}
