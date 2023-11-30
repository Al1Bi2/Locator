#include "locator.hpp"

Subscriber Locator::getSubscriber(std::string id){
    std::vector<Subscriber> out;

    out.push_back(subs[id]);
    spdlog::trace("subscriber returned");
    return subs[id];
    
}

void Locator::addCell(unsigned long id, const std::string& name,double x,double y,double r){
    cells[id]=Cell(id,name,x,y,r);
    spdlog::info("cell added");
}
Cell Locator::getCell(unsigned long id){
     spdlog::trace("cell returned");
    return cells[id];
}

void Locator::setSubscriberLocation(std::string id, double x,double y){
   subs[id]=Subscriber(id,x,y);
   notify();
   spdlog::info("subscriber location set");
}

std::vector<Subscriber> Locator::getSubsciberInZone(unsigned long id){
    std::vector<Subscriber> result;
    Cell cell = cells[id];
    double x_cell=cell.get_x();
    double y_cell=cell.get_y();
    double r=cell.get_r();
    for(auto const& x :subs){
        Subscriber sub=x.second;
        double x_sub=sub.get_x();
        double y_sub=sub.get_y();
        if(pow(x_cell-x_sub,2)+pow(y_cell-y_sub,2)<r*r){
            result.push_back(sub);
        }
    }
    spdlog::info("in cell {0} found {1} subs",id,result.size());
    return result;
}

void Locator::loadJSON(std::string filename){
    std::ifstream f(filename);
    json data = json::parse(f);

    for(auto const& x :data["zones"]){
        cells[x["id"]]=Cell(x["id"],x["name"],x["x"],x["y"],x["radius"]);

    }
    spdlog::warn(cells.size());

    /*switch(data["log_level"]){
        case "off" :
        spdlog::set_level(spdlog::level::off);
        break;
        case "trace":
        spdlog::set_level(spdlog::level::trace);
        break;
        case "debug":
        spdlog::set_level(spdlog::level::debug);
        break;
    }*/
}