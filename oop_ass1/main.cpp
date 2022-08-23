/**
Name:Monica Saeed Habib  ID:20200567
Name:Mirette Shenouda Maher  ID:20200575
*/

#include <iostream>
#include <windows.h>

using namespace std;

class ColoredBox{
private:
    char **b;        /// 2 diminsional array of character
    int length, width, color;   ///to store the length , width and color that construct the box
    char character;    ///to store the character that construct the box
    static int MaxArea;  /// variable to check area and store max
public:
    ColoredBox();
    void allocate();
    ColoredBox(int len, int wid);
    ColoredBox(int len, int wid,int col,char cha);

    void setCharacter(int cha);
    void setColor(int col);
    int getColor();
    int getCharacter();

    void display();
    void displayTransposed();
    void displayWider();
    void displayChess(int col2);

    int getArea();
    static int getMaxArea();

    void SetColor(int ForgC);

    ~ColoredBox();
};

int ColoredBox::MaxArea=0; ///set initial value to MaxArea

ColoredBox::ColoredBox()
{
    length = 0;
    width = 0;
}
void ColoredBox::allocate()        ///to allocate (dynamic allocation) the box and it will be called twice in both constructors
{
    b = new char *[length];
    for (int i = 0; i < length; i++){
        b[i] = new char[width];
    }
    for(int i=0;i<length;i++){
        for(int j=0;j<width;j++){
            b[i][j]=character;
        }
    }
    if(MaxArea<(length*width)) MaxArea=length*width;  ///to check MaxArea (compare area of new box with max area and store maximum between them)
}

ColoredBox::ColoredBox(int len, int wid)  ///constructor #1 if object has two parameters length and  width
{
    length = len;
    width = wid;
    character='#';
    color=15;
    allocate();
}
ColoredBox::ColoredBox(int len, int wid,int col,char cha)   ///constructor #2 if object has four parameters length ,  width , color @ character
{
  length = len;
    width = wid;
    character = cha;
    color = col;
    allocate();
}
void ColoredBox::setCharacter(int cha)   ///character setter
{
     for(int i=0;i<length;i++){
        for(int j=0;j<width;j++){
            b[i][j]=cha;
        }
    }
}
void ColoredBox::setColor(int col)      ///color setter
{
    color=col;
}
int ColoredBox::getColor()     ///color getter
{
    return color;
}
int ColoredBox::getCharacter()    ///character getter
{
    return character;
}
void ColoredBox::display()    ///function display that has the original matrix
{
    for(int i=0;i<length;i++){
        for(int j=0;j<width;j++){
            SetColor(color);
            cout<<b[i][j];
        }
        cout<<endl;
    }
    SetColor(15);      ///to return console color
}
void ColoredBox::displayTransposed()      ///function that converts rows and columns and set it to the new color
{
    for(int j=0;j<width;j++){
        for(int i=0;i<length;i++){
            SetColor(color);
            cout<<b[i][j];
        }
        cout<<endl;
        }
        SetColor(15);      ///to return console color
}
void ColoredBox::displayWider()  ///display wider function
{
    for(int i=0;i<length;i++){
        for(int j=0;j<width;j++){
            SetColor(color);
            cout<<b[i][j]<<" ";
        }
        cout<<endl;
    }
    SetColor(15);         ///to return console color
}
void ColoredBox::displayChess(int col2)
{
    for(int i=0; i<length;i++)
    {
        for(int j=0;j<width;j++)
        {
            if((i+j)%2==0){
                SetColor(color);
                cout<<b[i][j];
            }
            else{
                SetColor(col2);
                cout<<b[i][j];
            }
        }cout<<endl;
    }
}
int ColoredBox::getArea()   ///get the area of the box
{
    return length*width;
}
int ColoredBox::getMaxArea()    ///get the max area
{
    return MaxArea;
}
void ColoredBox::SetColor(int ForgC)
{
    WORD wColor;
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    //We use csbi for the wAttributes word.
    if(GetConsoleScreenBufferInfo(hStdOut, &csbi)){
        //Mask out all but the background attribute, and add in the forgournd color
        wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
        SetConsoleTextAttribute(hStdOut, wColor);
    }
    return;
}
ColoredBox::~ColoredBox()     ///destructor to clear the memory
{
    for(int i=0; i<length; i++){
        delete[] b[i];
    }
    delete[] b;
}

int main()
{
    int len,wid,col,col2;
    char boxChar;
    cout<<"Enter length and width of the box separated by a space: ";
    cin>>len>>wid;
    ColoredBox* cb1;                                ///object 1
    cb1 = new ColoredBox(len,wid);
    cb1->display();
    cout<<"Set the box to another color: ";
    cin>>col;
    cb1->setColor(col);
    cout<<"Displaying Transposed: "<<endl;
    cb1->displayTransposed();
    cout<<"Displaying Wider: "<<endl;
    cb1->displayWider();
    cout<<"Displaying Chess, enter the other color: "<<endl;
    cin>>col2;
    cb1->displayChess(col2);
    cout<<endl<<"Area="<<cb1->getArea();
    cout<<endl<<"Max Area="<<cb1->getMaxArea();
    delete cb1;

    cout<<"Enter length,width,color,character of the box separated by spaces: ";
    cin>>len>>wid>>col>>boxChar;
    ColoredBox* cb2;                            ///object 2
    cb2 = new ColoredBox(len,wid,col,boxChar);
    cb2->display();
    cout<<"Displaying Transposed: "<<endl;
    cb2->displayTransposed();
    cout<<"Displaying Wider: "<<endl;
    cb2->displayWider();
    cout<<"Displaying Chess, enter the other color: "<<endl;
    cin>>col2;
    cb2->displayChess(col2);
    cout<<"Displaying original again:"<<endl;
    cb2->display();
    cout<<endl<<"Area="<<cb2->getArea();
    cout<<endl<<"Max Area="<<cb2->getMaxArea();
    delete cb2;
    return 0;
}