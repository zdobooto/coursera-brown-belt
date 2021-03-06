#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

enum class Gender {
	FEMALE,
	MALE
};

struct Person {
	int age;
	Gender gender;
	bool is_employed;
};

template <typename InputIt>
int ComputeMedianAge3(InputIt range_begin, InputIt range_end) {
	if (range_begin == range_end) {
		return 0;
	}
	vector<typename iterator_traits<InputIt>::value_type> range_copy(
		range_begin,
		range_end
	);
	auto middle = begin(range_copy) + range_copy.size() / 2;
	nth_element(
		begin(range_copy), middle, end(range_copy),
		[](const Person& lhs, const Person& rhs) {
			return lhs.age < rhs.age;
		}
	);
	return middle->age;
}

int main3() {
	int person_count;
	cin >> person_count;
	vector<Person> persons;
	persons.reserve(person_count);
	for (int i = 0; i < person_count; ++i) {
		int age, is_employed, gender;
		cin >> age >> is_employed >> gender;
		Person person{
			age,
			static_cast<Gender>(gender),
			is_employed == 1
		};
		persons.push_back(person);
	}

	auto females_end = partition(
		begin(persons), end(persons),
		[](const Person& p) {
			return p.gender == Gender::FEMALE;
		}
	);
	auto employed_females_end = partition(
		begin(persons), females_end,
		[](const Person& p) {
			return p.is_employed;
		}
	);
	auto employed_males_end = partition(
		females_end, end(persons),
		[](const Person& p) {
			return p.is_employed;
		}
	);

	cout << "Median age = "
		<< ComputeMedianAge3(begin(persons), end(persons)) << endl
		<< "Median age for females = "
		<< ComputeMedianAge3(begin(persons), females_end) << endl
		<< "Median age for males = "
		<< ComputeMedianAge3(females_end, end(persons)) << endl
		<< "Median age for employed females = "
		<< ComputeMedianAge3(begin(persons), employed_females_end) << endl
		<< "Median age for unemployed females = "
		<< ComputeMedianAge3(employed_females_end, females_end) << endl
		<< "Median age for employed males = "
		<< ComputeMedianAge3(females_end, employed_males_end) << endl
		<< "Median age for unemployed males = "
		<< ComputeMedianAge3(employed_males_end, end(persons)) << endl;

	return 0;
}

