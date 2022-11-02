#include "SteckMachine.h"
#include <vector>

int SteckMachine::peek()
{
	return container.top();
}

void SteckMachine::dup()
{
	container.push(container.top());
}

void SteckMachine::add()
{
	int sum = container.top();
	container.pop();
	sum += container.top();
	container.pop();
	container.push(sum);
}

void SteckMachine::sub()
{	
	int a = container.top();
	container.pop();
	int b = container.top();
	container.pop();
	container.push(b - a);
}

void SteckMachine::div()
{
	int a = container.top();
	container.pop();
	int b = container.top();
	container.pop();
	container.push(b / a);
}

void SteckMachine::mul()
{
	int multi = container.top();
	container.pop();
	multi *= container.top();
	container.pop();
	container.push(multi);
}
