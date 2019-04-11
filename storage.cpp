#include <iostream>
#include <mutex>
#include <cassert>
using namespace std;

#include "storage.h"
//#include "goods.h"


//Storage::Storage(void)
//{
//	this->map = new unordered_map;
//}

Storage::~Storage()
{
	//this->manufacturer_index.erase(this->manufacturer_index.begin(), manufacturer_index.end());
	//this->vendor_index.erase(vendor_index.begin(), vendor_index.end());
	for (auto iter : this->manufacturer_index)
		iter.second.~shared_ptr();
	for (auto iter : this->vendor_index)
		iter.second.~shared_ptr();
	this->manufacturer_index.clear();
	this->vendor_index.clear();
	cout << "Storage removed" << endl;
}

bool Storage::insert_item(Item &item)
{
	//this->my_mutex.lock();
	unique_lock lock(this->my_mutex);
	/* Should we? */
	//item.value->my_mutex.lock();
	string vc = item.get_vendor_code();
	auto res = this->vendor_index.emplace(vc, item.value);
	//auto res = this->vendor_index.insert(vc, item.value);
	if (res.second)
		this->manufacturer_index.emplace(item.get_manufacturer(), item.value);
	//this->my_mutex.unlock();
	return res.second;
}

bool Storage::insert_item(string vendor_code, string manufacturer, string name, unsigned int price)
{
	Item item = Item(vendor_code, manufacturer, name, price);
	//Item item = Item(vendor_code.c_str(), manufacturer.c_str(), name.c_str(), price);
	//this->my_mutex.lock();
	unique_lock lock(my_mutex);
	//auto res = this->map.emplace(vendor_code, Item(vendor_code, manufacturer, name, price));
	
	auto res = this->vendor_index.emplace(vendor_code, item.value);
	if (res.second)
		this->manufacturer_index.emplace(item.get_manufacturer(), item.value);
	//this->my_mutex.unlock();
	return res.second;
	//return false;
}

bool Storage::remove_item(Item &item)
{
	//item.value->my_mutex.lock();
	//unique_lock lock(item.value->my_mutex);
	//this->my_mutex.lock();
	unique_lock lock(my_mutex);
	string vc = item.get_vendor_code();
	//auto res = this->vendor_index.erase(vc);
	auto res = this->vendor_index.find(item.get_vendor_code());
	if (res != this->vendor_index.end())
	{
		auto _pair = this->manufacturer_index.equal_range(item.get_manufacturer());
		for (; _pair.first != _pair.second; ++_pair.first)
		{
			if (_pair.first->second == item.value)
			{
				_pair.first->second.~shared_ptr();
				this->manufacturer_index.erase(_pair.first);
				break;
			}
		}
		this->vendor_index.erase(res->first);
		res->second.~shared_ptr();
		return true;
	}
	return false;
	//auto res_v = this->vendor_index.erase(item.get_vendor_code());
	//if (res_v > 0)
	//{
	//	if (res_v != res_m)
	//	{
	//		string error_msg = string("Removed from vendor_index: ") + 
	//						   to_string(res_v) + ", " +
	//						   "removed from manufacturer_index: " +
	//						   to_string(res_m) + ".";
	//		throw error_msg;
	//	}
	//}
	//return res_v > 0;
}

bool Storage::remove_item(string &vendor_code)
{
	
	//unique_lock lock(my_mutex);
	//auto res = this->vendor_index.erase(vendor_code);
	//return res > 0;
	Item *item = get_item(vendor_code);
	if (item)
		return remove_item(*item);
	else
		return false;
}

Item *Storage::get_item(string &vendor_code)
{
	//this->my_mutex.lock_shared();
	shared_lock lock(my_mutex);
	auto res = this->vendor_index.find(vendor_code);
	//this->my_mutex.unlock();

	if (res != this->vendor_index.end())
	{
		Item *item = new Item(res->second);
		return item;
	}
	else
		return NULL;
}

/* Since C++11 it is safe to return vector, constructed inside function */
vector<Item> Storage::get_items_by_manufacturer(string manufacturer)
{
	shared_lock lock(my_mutex);
	vector<Item> _vector;

	auto _pair = this->manufacturer_index.equal_range(manufacturer);
	
	for (; _pair.first != _pair.second; ++_pair.first)
	{
		_vector.emplace_back(Item(_pair.first->second));
	}
	return _vector;
}
