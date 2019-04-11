#ifndef STORAGE_H
#define STORAGE_H

#include <unordered_map>
//#include <mutex>
#include <shared_mutex>
#include <string>
#include <list>
#include <vector>
//#include "goods.h"
#include "item.h"


using namespace std;

class Storage
{
	private:
		//unordered_map<string, Item> map;
		unordered_map<string, /* Item::item_value **/ shared_ptr<item_value>> vendor_index;
		//unordered_map<string, list<Item *>> manufacturer_index;
		unordered_multimap<string, /* Item::item_value **/ shared_ptr<item_value>> manufacturer_index;
		mutable shared_mutex my_mutex;
	/* Methods */
	public:
		//Storage();
		bool insert_item(Item &item);
		bool insert_item(string vendor_code, string manufacturer, string name, unsigned int price);
		bool remove_item(Item &item);
		bool remove_item(string &vendor_code);
		//bool remove_item(char *vendor_code);
		Item *get_item(string &name);
		vector<Item> get_items_by_manufacturer(string manufacturer);


		/* Перегрузить конструкторы, чтобы создание и копирование было потокобезопасным */
		~Storage();
};

#endif /* STORAGE_H */