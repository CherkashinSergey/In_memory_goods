#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <mutex>
#include <memory>
using namespace std;

class Storage;

class item_value
{
	public:
	string			vendor_code; /* UNIQUE */
	string			manufacturer;
	string			name;
	unsigned int	price;
	//mutex			my_mutex;

	item_value(string vendor_code, string manufacturer, string name, unsigned int price);
	~item_value();
};

class Item
{

	friend class Storage;
	/* Choose wisely... */

	private:
		//struct item_value
		//{
		//	string			vendor_code; /* UNIQUE */
		//	string			manufacturer;
		//	string			name;
		//	unsigned int	price;
		//	mutex			my_mutex;
		//	//bool			in_storage;
		//};
		
		shared_ptr<item_value> value;

		//Item(item_value *value);
		Item(shared_ptr<item_value> value);
	/* Methods */
	public:
		Item(string vendor_code, string manufacturer, string name,
			 unsigned int price);
		//Item(char *vendor_code, char *manufacturer, char *name,
		//	 unsigned int price);
		~Item() = default;

		string get_vendor_code(void);
		string get_manufacturer(void);
		string get_name(void);
		unsigned int get_price(void);
		
		void set_vendor_code(string value);
		void set_manufacturer(string value);
		void set_name(string value);
		void set_price(unsigned int value);
		void print(void) const;
};

#endif /* ITEM_H */