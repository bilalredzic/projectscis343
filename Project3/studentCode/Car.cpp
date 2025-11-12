#include "Car.h"
#include <iostream>

int Car::current_id = 0;

Car::Car(int year, std::string model){
	this->id = Car::current_id++;
	std::cout << "Constructor called for ID " << this->id << std::endl;

	this->year = year;
	this->model = model;
	
}

int Car::getId() const {
	return this->id;
}

void Car::setYear(int year){
	this->year = year;
}

int Car::getYear() const {
	return year;
}

void Car::setModel(std::string model){
	this->model = model;
}

std::string Car::getModel() const {
	return model;
}

std::vector<ServiceRecord> Car::getRecords() const {
	return records;
}

void Car::addRecord(ServiceRecord record){
	records.push_back(record);
}

std::ostream& operator<<(std::ostream& os, const Car& car){
	os << car.id << ":" << car.year << " " << car.model << std::endl;
	os << "=========================" << std::endl;
	for(auto it=car.records.begin(); it != car.records.end(); ++it){
		os << "\t" << it->getCost() << ": " << it->getNotes() << std::endl;
	}
	return os;
}
bool Car::operator<(const Car& other) const {
    double total = 0, otherTotal = 0;
    for (auto& r : records) 
		total += r.getCost();
    for (auto& r : other.records) 
		otherTotal += r.getCost();
    return total < otherTotal;
}

