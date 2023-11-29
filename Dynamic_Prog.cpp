#include <iostream>
#include <string>
#include <vector>

using namespace std;

void FindingInTriangle(int, int&, vector<int>& , vector<vector<int>>);
void FindingInTriangle1();
void FindingInQuadrilateral(int, int&, vector<int>&, vector<vector<int>>);
void FindingInQuadrilateral1();
void ExponenNumber(int, int&);
void ExponenNumber1();
void MaxMatchingChain(string, string, int, int, string&);
void MaxMatchingChain1();
void BackpackProblem(int, int, vector<int>, vector<int>, vector<bool>&, int&);
void BackpackProblem1();

void main()
{
	FindingInTriangle1();
	FindingInQuadrilateral1();
	ExponenNumber1();
	MaxMatchingChain1();
	BackpackProblem1();
}

void FindingInTriangle(int n, int& res, vector<int>& way, vector<vector<int>> matrix_triangle)
{
	vector<vector<int>> res_triangle(n);
	way.resize(n);
	for (int i = 0; i < n; i++)
		res_triangle[i].resize(n + 1);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n + 1; j++)
			res_triangle[i][j] = matrix_triangle[i][j];
	}
	for (int i = 1; i < n; i++)
	{
		for (int j = 1; j < n + 1; j++)
			res_triangle[i][j] = max(res_triangle[i - 1][j - 1] + res_triangle[i][j],
				res_triangle[i - 1][j] + res_triangle[i][j]);
	}
	int maxIndex = 1;
	for (int i = 2; i < n + 1; i++)
	{
		if (res_triangle[n - 1][maxIndex] < res_triangle[4][i])
			maxIndex = i;
	}
	res = res_triangle[n - 1][maxIndex];
	way[n - 1] = maxIndex;
	for (int i = n - 1; i > 0; i--)
	{
		if (res_triangle[i][way[i]] - res_triangle[i - 1][way[i]] == matrix_triangle[i][way[i]])
			way[i - 1] = way[i];
		else if (res_triangle[i][way[i]] - res_triangle[i - 1][way[i] - 1] == matrix_triangle[i][way[i]])
			way[i - 1] = way[i] - 1;
	}
	for (int i = 0; i < n; i++)
		way[i] = matrix_triangle[i][way[i]];
}
void FindingInTriangle1()
{
	int n = 5, res; vector<int> way;
	vector<vector<int>> matrix_triangle = {
		{ 0, 9, 0, 0, 0, 0 },
		{ 0, 5, 5, 0, 0, 0 },
		{ 0, 4, 1, 9, 0, 0 },
		{ 0, 7, 7, 9, 3, 0 },
		{ 0, 3, 2, 1, 7, 4 }
	};
	cout << "FindingInTriangle" << endl;
	FindingInTriangle(n, res, way, matrix_triangle);
	cout << "Triangle:" << endl;
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n + 1; j++)
			cout << matrix_triangle[i][j] << "  ";
		cout << endl;
	}
	cout << "Sum max: " << res << endl;
	cout << "Optimal way: ";
	for (auto i = way.begin(); i != way.end(); i++)
		cout << *i << "  ";
	cout << endl<< endl;
}
void FindingInQuadrilateral(int n, int& result, vector<int>& way, vector<vector<int>> quadrilateral)
{
	int inf = 99,n1 = 0, n2 = n - 1;
	vector<bool> a(n); vector<int> b = quadrilateral[n1]; vector<int> c(n);
	for (auto i = c.begin(); i != c.end(); i++)
		*i = -1;
	for (int i = 0; i < n; i++)
	{
		int min_element = inf, min_index = 0;
		for (int j = 0; j < n; j++)
		{
			if (!a[j] && min_element > b[j])
			{
				min_element = b[j];
				min_index = j;
			}
		}
		a[min_index] = true;
		for (int j = 0; j < n; j++)
		{
			if (!a[j])
			{
				b[j] = min(b[j], min_element + quadrilateral[min_index][j]);
				c[j] = min_index;
			}
		}
	}
	result = b[n2];
	for (int i = n2; i != -1; i = c[i])
		way.push_back(i);
	reverse(way.begin(), way.end());
}
void FindingInQuadrilateral1()
{
	int n = 4, res;
	vector<int> way;
	vector<vector<int>> quadrilateral = {
		{ 0, 8, 4, 5 },
		{ 3, 0, 9, 4 },
		{ 3, 23, 0, 99 },
		{ 1, 4, 2, 0 }
	};
	cout << "FindingInQuadrilateral" << endl;
	FindingInQuadrilateral(n, res, way, quadrilateral);
	cout << "Quadrilateral:" << endl;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			cout << quadrilateral[i][j] << "  ";
		cout << endl;
	}
	cout << "Path length: " << res << endl;
	cout << "Optimal way: ";
	for (auto i = way.begin(); i != way.end(); i++)
		cout << *i << "  ";
	cout << endl << endl;
}
void ExponenNumber(int exp, int& res)
{
	vector<int> oper(exp + 1);
	for (int i = 2; i <= exp; i++)
	{
		oper[i] = oper[i - 1] + 1;
		for (int j = 2; j <= i - 1; j++)
		{
			oper[i] = min(oper[i], oper[j] + oper[i - j] + 1);
			if (i % j == 0)
				oper[i] = min(oper[i], static_cast<int>(oper[i / j] + j - 1));
		}
	}
	res = oper[exp];
}
void ExponenNumber1()
{
	int exp = 7, res = 0;
	cout << "ExponenOfNumber " << endl;
	ExponenNumber(exp, res);
	cout << "Exponent: " << exp << endl;
	cout << "Minimum number: " << res << endl;
	cout << endl;
}
void MaxMatchingChain(string word_1, string word_2, int count_1, int count_2, string& res)
{
	vector<vector<int>> colors, values;
	colors.resize(count_1);
	values.resize(count_1);
	for (int i = 0; i < count_1; i++)
	{
		colors[i].resize(count_2);
		values[i].resize(count_2);
	}
	bool row = false, col = false;
	for (int i = 0; i < count_1; i++)
	{
		for (int j = 0; j < count_2; j++)
		{
			colors[i][j] = word_1[i] == word_2[j] ? true : false;
			if (colors[0][j]) col = true;
			if (i == 0) values[0][j] = col ? 1 : 0;
		}
		if (colors[i][0]) row = true;
		values[i][0] = row ? 1 : 0;
	}
	for (int i = 1; i < count_1; i++)
	{
		for (int j = 1; j < count_2; j++)
			values[i][j] = colors[i][j] ? values[i - 1][j - 1] + 1 : max(values[i - 1][j], values[i][j - 1]);
	}
	res.reserve(max(count_1, count_2));
	int counter = values[count_1 - 1][count_2 - 1];
	for (int i = count_1 - 1; i >= 0; i--)
	{
		for (int j = count_2 - 1; j >= 0; j--)
		{
			if (colors[i][j] && values[i][j] == counter)
			{
				res.push_back(word_1[i]);
				--counter;
			}
		}
	}
	reverse(res.begin(), res.end());
}
void MaxMatchingChain1()
{
	string word_1 = "ggcatgatctagcc";
	string word_2 = "acatagtctac";
	string res;
	int count_1 = word_1.length();
	int count_2 = word_2.length();
	cout << "MaxMatchingChain" << endl;
	MaxMatchingChain(word_1, word_2, count_1, count_2, res);
	cout << "First word: " << word_1 << endl;
	cout << "Second word: " << word_2 << endl;
	cout << "Maximum chain: " << res << endl;
	cout << endl;
}
void BackpackProblem(int weight, int count, vector<int> weights, vector<int> prices, vector<bool>& incl, int& result)
{
	vector<vector<int>> table;
	table.resize(count + 1);
	for (int i = 0; i < count + 1; i++)
		table[i].resize(weight + 1);
	for (int i = 1; i < count + 1; i++)
	{
		for (int j = 0; j <= weight; j++)
		{
			if (j - weights[i - 1] >= 0)
				table[i][j] = max(table[i - 1][j], table[i - 1][j - weights[i - 1]] + prices[i - 1]);
			else
				table[i][j] = table[i - 1][j];
		}
	}
	result = table[count][weight];
	int j = weight;
	for (int i = count; i > 0; i--)
	{
		if (table[i][j] > table[i - 1][j])
		{
			incl[i - 1] = true;
			j -= weights[i - 1];
		}
		else
			incl[i - 1] = false;
	}
}
void BackpackProblem1()
{
	int weight = 12, count = 5;
	vector<int> weights = { 1, 7, 2, 4, 8 };
	vector<int> prices = { 2, 6, 3, 1, 9 };
	int result = 0;
	vector<bool> incl = { 0, 0, 0, 0, 0 };
	cout << "BackpackProblem " << endl;
	BackpackProblem(weight, count, weights, prices, incl, result);
	cout << "Weight: ";
	for (int i = 0; i < count; i++)
		cout << weights[i] << "  ";
	cout << endl;
	cout << "Price: ";
	for (int i = 0; i < count; i++)
		cout << prices[i] << "  ";
	cout << endl;
	cout << "Maximum price: " << result << std::endl;
	cout << "Subject: ";
	for (size_t i = 0; i < count; i++)
		incl[i] ? cout << i + 1 << "  " : cout;
	cout << endl << endl;
}
