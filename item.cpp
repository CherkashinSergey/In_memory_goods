//#include "goods.h"
#include <string.h>
#include "item.h"
#include <iostream>

using namespace std;

/* Methods */
Item::Item(string vendor_code, string manufacturer, string name, unsigned int price)
{
	//this->value = (item_value *)malloc(sizeof (item_value));
	//this->value = new item_value();
	//auto temp = make_shared<item_value>(new item_value());
	//auto temp2 (new item_value());
	this->value = make_shared<item_value>(vendor_code, manufacturer, name, price);

/*
	this->value->vendor_code = vendor_code;
	this->value->manufacturer = manufacturer;
	this->value->name = name;
	this->value->price = price;
	this->value->in_storage = false;
*/
}

/*Item::Item(char *vendor_code, char *manufacturer, char *name, unsigned int price)
{
	//this->value = (item_value *)malloc(sizeof (item_value));
	this->value = new item_value();
	this->value->vendor_code = string(vendor_code);
	this->value->manufacturer = string(manufacturer);
	this->value->name = string(name);
	this->value->price = price;
	this->value->in_storage = false;
}*/

Item::Item(shared_ptr<item_value> value)
{
	//this->value = value;
	this->value = make_shared<item_value>(value->vendor_code, value->manufacturer, value->name, value->price);
}

/*Item::~Item()
{
	if (!this->value->in_storage)
		delete(this->value);
		//free(this->value);
	
}
*/

void Item::print(void) const
{
	cout << "vendor_code: " << this->value->vendor_code << ", "
		 << "manufacturer: " << this->value->manufacturer << ", "
		 << "name: " << this->value->name << ", "
		 << "price: " << this->value->price << endl;
}

string
Item::get_vendor_code(void)
{
	string value;
	//this->value->my_mutex.lock();
	value = this->value->vendor_code;
	//this->value->my_mutex.unlock();
	return value;
}

string
Item::get_manufacturer(void)
{
	string value;
	//this->value->my_mutex.lock();
	value = this->value->manufacturer;
	//this->value->my_mutex.unlock();
	return value;
}

string
Item::get_name(void)
{
	string value;
	//this->value->my_mutex.lock();
	value = this->value->name;
	//this->value->my_mutex.unlock();
	return value;
}

unsigned int
Item::get_price(void)
{
	unsigned int value;
	//this->value->my_mutex.lock();
	value = this->value->price;
	//this->value->my_mutex.unlock();
	return value;
}

void
Item::set_vendor_code(string value)
{
	//this->value->my_mutex.lock();
	this->value->vendor_code = value;
	//this->value->my_mutex.unlock();
}

void
Item::set_manufacturer(string value)
{
	//this->value->my_mutex.lock();
	this->value->manufacturer = value;
	//this->value->my_mutex.unlock();
}

void
Item::set_name(string value)
{
	//this->value->my_mutex.lock();
	this->value->name = value;
	//this->value->my_mutex.unlock();
}

void
Item::set_price(unsigned int value)
{
	//this->value->my_mutex.lock();
	this->value->price = value;
	//this->value->my_mutex.unlock();
}

item_value::item_value(string vendor_code, string manufacturer, string name, unsigned int price)
{
	this->vendor_code = vendor_code;
	this->manufacturer = manufacturer;
	this->name = name;
	this->price = price;
	cout << "item " << this->vendor_code << " created" << endl;
}

item_value::~item_value()
{
	cout << "item " << this->vendor_code << " destroyed" << endl;
}