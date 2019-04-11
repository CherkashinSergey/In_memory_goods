//#include <iostream>
#include <thread>
using namespace std;

#include "goods.h"
#define ITEM_COUNT 10
#define THREAD_COUNT 2

//Storage storage;

void run_test(void func(Storage *, int), Storage *storage, const int thread_count)
{
	thread threads[thread_count];
	for (int i = 0; i < thread_count; i++)
	{
		threads[i] = thread(func, storage,i);
	}

	for (int i = 0; i < thread_count; i++)
	{
		threads[i].join();
	}
}

void test_insert(Storage *storage, int thread_num)
//void test_insert(int thread_num)
{
	for (int i=0; i < ITEM_COUNT; i++)
	{
		string num = to_string(i);
		//string vendor_code = "i" + to_string(i);
		//Item item ("item0" + num, "manufacturer " + num, "some stuff " + num, 1000 + i);
		//if (storage.insert_item(item))
		if (storage->insert_item("item0" + num, "manufacturer " + num, "some stuff " + num, 1000 + i))
			cout << "Thread " << thread_num << " added item " << i << endl;
	}
}
void test_find(Storage *storage, int thread_num)
{
	for (int i=0; i < ITEM_COUNT; i++)
	{
		string vendor_code = "i" + to_string(i);
		if (!storage->get_item(vendor_code))
			cout << "Thread " << thread_num << " could not get item " << vendor_code << endl;
	}
}

void test_find_by_manufacturer(Storage *storage, int thread_num)
{
	int res = (storage->get_items_by_manufacturer("manufacturer")).size();
	cout << "Search by manufacturer in " << thread_num << " is "
		 << (res == ITEM_COUNT ? "" : "NOT ") << "successfull" << endl;
}

void test_remove(Storage *storage, int thread_num)
{
	for (int i=0; i < ITEM_COUNT; i++)
	{
		//string num = to_string(i);
		//Item item ("item0" + num, "manufacturer " + num, "some stuff " + num, 1000 + i); //seg fault
		//if (storage.remove_item(item))
		//	cout << "Thread " << thread_num << " removed item " << i << endl;
		
		string vendor_code = "i" + to_string(i);
		if (storage->remove_item(vendor_code))
			cout << "Thread " << thread_num << " removed item " << i << endl;
	}
}

/*
void test_single_remove(void)
{
	string vc = string("i100");
	Item i0 ("i100", "manufacturer 0", "some stuff 0", 1000);
	Storage _storage;
	_storage.insert_item(i0);
	_storage.get_item(vc);
	_storage.remove_item(i0);
}
*/
int main()
{
	cout << "Hello world!\n";

	Storage storage;

/*
	Item i0 ("i0", "manufacturer 0", "some stuff 0", 1000);
	Item i1 ("i1", "manufacturer 1", "some stuff 1", 1001);
	Item i2 ("i2", "manufacturer 2", "some stuff 2", 1002);
	Item i3 ("i3", "manufacturer 3", "some stuff 3", 1003);
	Item i4 ("i4", "manufacturer 4", "some stuff 4", 1004);
	Item m41 ("m41", "manufacturer 4", "some stuff 4", 1004);
	Item m42 ("m42", "manufacturer 4", "some stuff 4", 1004);
	Item m43 ("m43", "manufacturer 4", "some stuff 4", 1004);


	storage.insert_item(i0);
	storage.insert_item(i1);
	storage.insert_item(i2);
	storage.insert_item(i3);
	storage.insert_item(i4);
	storage.insert_item(m41);
	storage.insert_item(m42);
	storage.insert_item(m43);
	//storage.insert_item("i3", "manufacturer 3", "some stuff 3", 1003);
	//storage.insert_item("i4", "manufacturer 4", "some stuff 4", 1004);
	//storage.insert_item("i5", "manufacturer 5", "some stuff 5", 1005);

	for (int i=0; i < 10; i++)
	{
		string vendor_code = "i" + to_string(i);
		Item *item = storage.get_item(vendor_code);
		if (item)
		{
			item->print();
			//cout << endl;
		}
	}

	string item_to_remove = "i3";
	storage.remove_item(i3);
	storage.remove_item(item_to_remove);

	cout << "Look for manufacturer 4:" << endl;
	for (Item item : storage.get_items_by_manufacturer("manufacturer 4"))
	{
		item.print();
	}
*/

	//thread t1(test_insert, storage, 1);
	//thread t2(test_insert, storage, 2);

	//test_single_remove();
	//cout << "Continue" << endl;

/*
	thread t1(test_insert, 1);
	thread t2(test_insert, 2);
	t1.join();
	t2.join();
	
	t1 = thread(test_find, 1);
	t2 = thread(test_find, 2);
	t1.join();
	t2.join();

	for (int i=0; i < ITEM_COUNT; i++)
	{
		string num = to_string(i);
		Item item ("item1" + num, "manufacturer", "some stuff " + num, 1000 + i);
		storage.insert_item(item);
	}
	t1 = thread(test_find_by_manufacturer, 1);
	t2 = thread(test_find_by_manufacturer, 2);
	t1.join();
	t2.join();
	
	t1 = thread(test_remove, 1);
	t2 = thread(test_remove, 2);
	t1.join();
	t2.join();
*/
/*
	thread threads[THREAD_COUNT];
	for (int i = 0; i < THREAD_COUNT; i++)
	{
		threads[i] = thread(test_insert, &storage,i);
	}

	for (int i = 0; i < THREAD_COUNT; i++)
	{
		threads[i].join();
	}
*/
	run_test(test_insert, &storage, THREAD_COUNT);
	run_test(test_find, &storage, THREAD_COUNT);
	run_test(test_find_by_manufacturer, &storage, THREAD_COUNT);
	run_test(test_remove, &storage, THREAD_COUNT);
	return 0;
}
