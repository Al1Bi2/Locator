#include <string>

class Cell{
private:

    unsigned long id=0;
    std::string name="";
    double x=0,y=0;
    double r=0;
public:
Cell(){};
Cell(unsigned long id, const std::string& name,double x,double y,double r){
    this->id=id;
    this->name=name;
    this->x=x;
    this->y=y;
    this->r=r;
}
bool empty(){
    return id==0;
}
unsigned long get_id(){
    return id;
}
std::string get_name(){
    return name;
}
double get_x(){
    return x;
}
double get_y(){
    return y;
}
double get_r(){
    return r;
}
};
