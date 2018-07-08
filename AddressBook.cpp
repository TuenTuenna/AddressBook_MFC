//AddressBook.cpp
#include "AddressBook.h"

AddressBook::AddressBook(Long capacity)
	:personals(capacity) {
	this->capacity = capacity;
	this->length = 0;
}

AddressBook::AddressBook(const AddressBook& source)
	: personals(source.personals) {
	this->capacity = source.capacity;
	this->length = source.length;
}

AddressBook::~AddressBook() {
}

Long AddressBook::Record(string name, string address, string telephoneNumber, string emailAddress)
{
	Personal personal(name, address, telephoneNumber, emailAddress);
	Long index;
	if (this->length < this->capacity){
	index = this->personals.Store(this->length, personal);
	}
	else 
	{
		index = this->personals.AppendFromRear(personal);
		this->capacity++;
	}
	this->length++;
	return index;
}
void AddressBook::Find(string name, Long*(*indexes), Long *count)
{
	this->personals.LinearSearchDuplicate(&name, indexes, count, CompareKeys);
}
Long AddressBook::Correct(Long index, string address, string telephoneNumber, string emailAddress)
{
	Personal personal(this->personals.GetAt(index).GetName(), address, telephoneNumber, emailAddress);
	index = this->personals.Modify(index, personal);
	return index;
}
Long AddressBook::Erase(Long index)
{
	index = this->personals.Delete(index);
	this->capacity--;
	this->length--;
	return index;
}
void AddressBook::Arrange()
{
	this->personals.InsertionSort(CompareNames);
}
Personal& AddressBook::GetAt(Long index)
{
	return this->personals.GetAt(index);
}
AddressBook& AddressBook::operator = (const AddressBook& source)
{
	this->personals = source.personals;
	this->capacity = source.capacity;
	this->length = source.length;
	return *this;
}
Personal& AddressBook::operator[](Long index)
{
	return this->personals.GetAt(index);
}

int CompareNames(void *one, void*other)
{
	return static_cast<Personal*>(one)->GetName().compare(static_cast<Personal*>(other)->GetName());
}

int CompareKeys(void *one, void *other)
{
	return (static_cast<Personal*>(one))->GetName().compare(*static_cast<string*>(other));
}

#include <iostream>
using namespace std;
int main(int argc, char *argv[]) {
	Long(*indexes);
	Long count;

	AddressBook addressBook(2);
	Long index = addressBook.Record("고길동", "경기도", "031", "aa@");
	Personal personal = addressBook.GetAt(index);
	cout << personal.GetName() << "," << personal.GetAddress() << "," << personal.GetTelephoneNumber() << "," << personal.GetEmailAddress() << endl;
	index = addressBook.Record("홍길동", "부산", "051", "bb@");
	personal = addressBook.GetAt(index);
	cout << personal.GetName() << "," << personal.GetAddress() << "," << personal.GetTelephoneNumber() << "," << personal.GetEmailAddress() << endl;

	index = addressBook.Record("김길동", "울산", "052", "cc@");
	personal = addressBook.GetAt(index);
	cout << personal.GetName() << "," << personal.GetAddress() << "," << personal.GetTelephoneNumber() << "," << personal.GetEmailAddress() << endl;

	addressBook.Find("홍길동", &indexes, &count);
	Long i = 0;
	while (i < count) {
		personal = addressBook.GetAt(indexes[i]);
		cout << personal.GetName() << "," << personal.GetAddress() << "," << personal.GetTelephoneNumber() << "," << personal.GetEmailAddress() << endl;
		i++;
	}
	if (indexes != 0) {
		delete[] indexes;
	}
	index = addressBook.Correct(2, "서울", "02", "dd@");
	personal = addressBook.GetAt(index);
	cout << personal.GetName() << "," << personal.GetAddress() << "," << personal.GetTelephoneNumber() << "," << personal.GetEmailAddress() << endl;

	index = addressBook.Erase(2);

	if (index == -1){
		cout << "지워졌습니다" << endl;
	}

	addressBook.Arrange();
	i = 0;
	while (i < addressBook.GetLength()) {
		personal = addressBook.GetAt(i);
		cout << personal.GetName() << "," << personal.GetAddress() << "," << personal.GetTelephoneNumber() << "," << personal.GetEmailAddress() << endl;
		i++;
	}

	return 0;

}