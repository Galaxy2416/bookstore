#include <iostream>
#include <list>

using namespace std;
struct Employee
{
	int happy;
	list<Employee> ems;
	
	Employee(int h) : happy(h) {}
};

pair<int, int> process(const Employee& e)
{
	int yes = e.happy;
	int no = 0;
	for (const auto& i : e.ems)
	{
		auto [y, n] = process(i);
		yes += n;
		no += max(y, n);
	}
	return {yes, no};
}

int getMaxHappy(const Employee& e)
{
	auto [y, n] = process(e);
	return max(y, n);
}

int main()
{	
	Employee boss{10};
	Employee mgr1{4}, mgr2{21}, mgr3{6};
	Employee u1{2}, u2{6}, u3{1}, u4{4}, u5{3}, u6{10}, u7{4};
	mgr1.ems.push_back(u1); 
	mgr1.ems.push_back(u2); 
	mgr1.ems.push_back(u3); 

	mgr2.ems.push_back(u4);
	mgr2.ems.push_back(u5);

	mgr3.ems.push_back(u6);
	mgr3.ems.push_back(u7);

	boss.ems.push_back(mgr1);
	boss.ems.push_back(mgr2);
	boss.ems.push_back(mgr3);

	cout << getMaxHappy(boss) << endl;
}

