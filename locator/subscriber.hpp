#include <string>

class Subscriber {
private:
    std::string id;
    double x;
    double y;
public:
Subscriber():id(""),x(0),y(0){};
Subscriber(const std::string &id,double x,double y){
    this->id=id;
    this->x=x;
    this->y=y;
}
std::string get_id(){
    return id;
}
double get_x(){
    return x;
}
double get_y(){
    return y;
}
bool empty(){
    return id=="";
}
};