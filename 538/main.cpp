#include <iostream>
#include <vector>

using namespace std;

vector<char> stack;

int main() {

	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	stack.push_back('x');

	while (true) {
		char c = cin.get();
		if (cin.eof()) break;
		if (c == '(') stack.push_back(c);
		else if (!isalpha(c) && c != ')' && c != ' ') stack.push_back(c);
		else if (c == ')' && stack[stack.size() - 1] == '(') stack[stack.size() - 1] = 'x';
		else if (c == ')' && stack[stack.size() - 1] != '(') stack.push_back(c);
	}

	int count = 0;

	for (int i = 0; i < stack.size(); ++i) if (stack[i] == '(' || stack[i] == ')') ++count;

	printf("%d\n", count);

	return 0;
}