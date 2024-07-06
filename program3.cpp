#include <iostream>
 
using namespace std;

class Box{
     private:
      double length;
      double breadth;
      double height;
      
     public:
      
      static int Count;
      
      // Constructor definition
      Box(double l=5, double b=6, double h=7) {
        cout <<"Constructor called." << endl;
        if(l<=0 || b<=0 || h<=0){
            length=0;
            breadth=0;
            height=0;
            cout<<"input invalid, enter a positive number"<<endl;
        }
        else{
         length = l;
         breadth = b;
         height = h;
         
         Count++;
        }
      }
      double boxVolume(){
         return length*breadth*height;
      }
      double boxarea(){
        return 2*(length*breadth+breadth*height+height*length);
      }
};

// Initialize static member of class Box
int Box::Count;

int main(void) {
   class Box a(3, 2, 5);
   class Box b(6, -3, 3);


   cout<<"volume of box a : "<<a.boxVolume()<<endl;
   cout<<"Area of box a : "<<a.boxarea()<<endl;
   cout<<"volume of box b : "<<b.boxVolume()<<endl;
   cout<<"Area of box b : "<<b.boxarea()<<endl;

   // Print total number of objects.
   cout << "Total objects: "<<Box::Count<<endl;

   return 0;
}