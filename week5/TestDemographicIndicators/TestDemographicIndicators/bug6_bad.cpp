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
int ComputeMedianAge6(InputIt range_begin, InputIt range_end) {
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

int main6() {
	int person_count;
	cin >> person_count;
	vector<Person> persons;
	persons.reserve(person_count);
	for (int i = 0; i < person_count; ++i) {
		int age, gender, is_employed;
		cin >> age >> gender >> is_employed;
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
		<< ComputeMedianAge6(begin(persons), end(persons)) << endl
		<< "Median age for males = "
		<< ComputeMedianAge6(females_end, end(persons)) << endl
		<< "Median age for females = "
		<< ComputeMedianAge6(begin(persons), females_end) << endl
		<< "Median age for employed males = "
		<< ComputeMedianAge6(females_end, employed_males_end) << endl
		<< "Median age for unemployed males = "
		<< ComputeMedianAge6(employed_males_end, end(persons)) << endl
		<< "Median age for employed females = "
		<< ComputeMedianAge6(begin(persons), employed_females_end) << endl
		<< "Median age for unemployed females = "
		<< ComputeMedianAge6(employed_females_end, females_end) << endl;

	return 0;
}

