#include "cell.hpp"
#include "subscriber.hpp"
#include "trigger.hpp"

#include <vector>
#include <map>
#include <cmath>
#include <fstream>
#include <iostream>

#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"
#include <nlohmann/json.hpp>
using json = nlohmann::json;

class Locator : public AbstractObject{
private:
std::map<unsigned long,Cell> cells;
std::map<std::string,Subscriber> subs;

std::shared_ptr<spdlog::logger> log;
public:
void loadJSON(std::string);
void setSubscriberLocation(std::string id, double x,double y);
Subscriber getSubscriber(std::string id);

std::vector<Subscriber>  getSubsciberInZone(unsigned long id);

void addCell(unsigned long id, const std::string& name,double x,double y,double r);
Cell getCell(unsigned long id);

Locator(){
     std::shared_ptr<spdlog::logger> log = spdlog::get("log");
          if (not log) {
              log =  std::make_shared<spdlog::logger>("log", std::make_shared<spdlog::sinks::basic_file_sink_mt>("logs/log.txt"));
               spdlog::register_logger(log);
        spdlog::set_default_logger(log);

           }
        }       




};
class proximityTrigger: public AbstractTrigger{
   friend class Locator;
private:
    unsigned long id=0;
    std::string subscriber1_id="";
    std::string subscriber2_id="";
    double distance;

    enum border{OUT,IN};
    border state;
public:
   proximityTrigger() : AbstractTrigger(){};
   proximityTrigger(unsigned long id, std::string subscriber1_id, std::string subscriber2_id, double distance) : AbstractTrigger(){
        this->id=id;
        this->subscriber1_id=subscriber1_id;
        this->subscriber2_id=subscriber2_id;
        this->distance=distance;

    }

    void update(){
 
      Locator* locatorPtr = static_cast<Locator*>(object);

      if(locatorPtr==0){return;}
      border new_state;
      Subscriber sub1=locatorPtr->getSubscriber(subscriber1_id);
      Subscriber sub2=locatorPtr->getSubscriber(subscriber2_id);
      if( sub2.empty() or sub1.empty()){return;}

      double x_1=sub1.get_x();
      double y_1=sub1.get_y();
      double x_2=sub2.get_x();
      double y_2=sub2.get_y();
      if(pow(x_1-x_2,2)+pow(y_2-y_2,2)<distance*distance){
         spdlog::info("S:{0} is near S:{1}",subscriber1_id,subscriber2_id);
      }
     
    }
};

class borderTrigger: public AbstractTrigger{
   friend class Locator;
private:
    unsigned long id=0;
    std::string subscriber_id="";
    unsigned long cell_id=0;
    char event=0;

    enum border{OUT,IN};
    border state;
public:
   borderTrigger() : AbstractTrigger(){};
   borderTrigger(unsigned long id, std::string subscriber_id, unsigned long cell_id, char event) : AbstractTrigger(){
        this->id=id;
        this->subscriber_id=subscriber_id;
        this->cell_id=cell_id;
        this->event=event;

    }

    void update(){
 
      Locator* locatorPtr = static_cast<Locator*>(object);

      if(locatorPtr==0){return;}
      border new_state;
      Cell cell = locatorPtr->getCell(cell_id);
      Subscriber sub=locatorPtr->getSubscriber(subscriber_id);
      if( cell.empty() or sub.empty()){return;}
      double x_cell=cell.get_x();
      double y_cell=cell.get_y();
      double r=cell.get_r();
      double x_sub=sub.get_x();
      double y_sub=sub.get_y();
      new_state=border(pow(x_cell-x_sub,2)+pow(y_cell-y_sub,2)<r*r);

      switch (event)
      {
      case 0://IN
         if(state-new_state==-1){
            spdlog::info("S:{0} entered cell {1}",subscriber_id,cell_id);
         }
         break;
      case 1://OUT
         if(state-new_state==1){
            spdlog::info("S:{0} exited cell {1}",subscriber_id,cell_id);
         }
         break;
      case 2://IN|OUT
         if(abs(state-new_state)==1){
            spdlog::info("S:{0} crossed border cell {1}",subscriber_id,cell_id);
         }
         break;
      default:
         break;
      }

    }
};
