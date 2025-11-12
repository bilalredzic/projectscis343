#include "Car.h"
#include "ServiceRecord.h"
#include <iostream>

void findInInventory(std::vector<Car>::iterator it, std::vector<Car> inventory, int id){
	while(it != inventory.end()){
		if(it->getId() == id){
			break;
		}
		++it;
	}
}

void makeTrade(std::vector<Car>& inventory, Car& tradein, Car& tradeout){
	ServiceRecord outInspection("Sale inspection.", 0.0);
	tradeout.addRecord(outInspection);

	ServiceRecord inInspection("Presale inspection.", 19.95);
	tradein.addRecord(inInspection);

	auto it=inventory.begin();
	findInInventory(it, inventory, tradeout.getId());
	if(it != inventory.end()){
		inventory.erase(it);
	}
	inventory.push_back(tradein);
}

int main(int argc, char** argv){
	Car a(1985, "Toyota Hilux");
	ServiceRecord first("Oil change.", 9.95f);
	a.addRecord(first);

	Car b(1985, "Toyota Hilux");
	first = ServiceRecord("Radiator flush.", 19.95);
	b.addRecord(first);

	std::vector<Car> inventory;
	inventory.push_back(a);
	inventory.push_back(b);

	Car c(1985, "Toyota Hilux");
	c.setModel("Ford F150");

	std::cout << "Customer wants to trade in " << c << std::endl;
	std::cout << "They want to get " << a << std::endl;

	std::cout << "Before makeTrade:\n";
	for (auto& car : inventory)
    	std::cout << car;
	makeTrade(inventory, c, a);
	std::cout << "After makeTrade:\n";
	for (auto& car : inventory)
    	std::cout << car;

	std::cout << "After trade, inventory is: " << std::endl;
	std::cout << "===========================" << std::endl;
	for(auto it = inventory.begin(); it != inventory.end(); ++it){
		std::cout << *it << std::endl;
	}
	std::cout << "A ID: " << a.getId() << std::endl;
std::cout << "B ID: " << b.getId() << std::endl;
std::cout << "C ID: " << c.getId() << "\n\n\n\n\n\n\n" << std::endl;



Car honda(2010, "Honda Civic");
honda.addRecord(ServiceRecord("Oil Change", 30.0));
honda.addRecord(ServiceRecord("Brakes", 150.0));

Car toyota(2015, "Toyota Corolla");
toyota.addRecord(ServiceRecord("Tire Rotation", 50.0));

Car ford(2018, "Ford F150");
ford.addRecord(ServiceRecord("Engine Repair", 500.0));

Car bmw(2020, "BMW 330i");
bmw.addRecord(ServiceRecord("Oil Change", 60.0));
bmw.addRecord(ServiceRecord("Brake Pads", 200.0));

Car tesla(2023, "Tesla Model 3");
tesla.addRecord(ServiceRecord("Software Update", 0.0));

std::vector<Car> cars = {honda, toyota, ford, bmw, tesla};

std::sort(cars.begin(), cars.end());

std::cout << "\nCars sorted by total service cost:\n";
for (auto& car : cars)
    std::cout << car;
}
