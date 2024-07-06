#include <bits/stdc++.h>
using namespace std;

constexpr int MODULO_VALUE = 1e4 + 7;

int number_of_rows, number_of_columns;
string board_layout[10];
map<string, int> memoization_cache[10][10];

struct Converter {
private:
	string ConvertType0(const string& current_string) {
		string converted_string = current_string;
		converted_string.erase(converted_string.begin()); 
        converted_string.pop_back();
		converted_string.push_back('0');
        converted_string.push_back('0');
		return converted_string;
	}
	string ConvertType1(const string& current_string) {
		string converted_string = current_string;
		converted_string.erase(converted_string.begin()); 
        converted_string.pop_back();
		converted_string.push_back('0');
        converted_string.push_back(current_string.back());
		return converted_string;
	}
	string ConvertType2(const string& current_string) {
		string converted_string = current_string;
		converted_string.erase(converted_string.begin()); 
        converted_string.pop_back();
		for (auto& character : converted_string) {
            if (character == current_string.back()) {
                character = current_string[0];
            }
        }
		converted_string.push_back('0');
        converted_string.push_back('0');
		return converted_string;
	}
	string ConvertType3(const string& current_string) {
		string converted_string = current_string;
		converted_string.erase(converted_string.begin()); 
        converted_string.pop_back();
		converted_string.push_back('0');
        converted_string.push_back(current_string[0]);
		return converted_string;
	}
	string ConvertType4(const string& current_string) {
		string converted_string = current_string;
		converted_string.erase(converted_string.begin()); 
        converted_string.pop_back();
		converted_string.push_back(current_string[0]);
        converted_string.push_back('0');
		return converted_string;
	}
	string ConvertType5(const string& current_string) {
		string converted_string = current_string;
		converted_string.erase(converted_string.begin()); 
        converted_string.pop_back();
		converted_string.push_back(current_string.back());
        converted_string.push_back('0');
		return converted_string;
	}
	string ConvertType6(const string& current_string) {
		string converted_string = current_string;
		converted_string.erase(converted_string.begin()); 
        converted_string.pop_back();
		converted_string.push_back('9');
        converted_string.push_back('9');
		return Normalize(converted_string);
	}
public:
	string Normalize(const string& current_string) {
		char normalization_check[10]{};
		for (int index = 0, type_index = 1; index < current_string.size(); index++) {
			if (current_string[index] == '0' || normalization_check[current_string[index] & 15]) continue;
			normalization_check[current_string[index] & 15] = type_index++ | 48;
		}
		string normalized_string(current_string.size(), '0');
		for (int index = 0; index < current_string.size(); index++) {
			if (current_string[index] == '0') continue;
			normalized_string[index] = normalization_check[current_string[index] & 15];
		}
		return normalized_string;
	}
	string operator() (int conversion_type, const string& current_string) {
		switch (conversion_type) {
		case 0: return ConvertType0(current_string);
		case 1: return ConvertType1(current_string);
		case 2: return ConvertType2(current_string);
		case 3: return ConvertType3(current_string);
		case 4: return ConvertType4(current_string);
		case 5: return ConvertType5(current_string);
		case 6: return ConvertType6(current_string);
		}
	}
} ConverterInstance;

bool IsEndConditionMet(const string& current_string) {
	for (int index = 0; index < current_string.size(); index++) {
		if (index + 2 != current_string.size() ^ current_string[index] != '1') return false;
	}
	return true;
}

int DepthFirstSearch(int row_index, int column_index, string current_state) {
	current_state = ConverterInstance.Normalize(current_state);
	if (row_index == number_of_rows) return IsEndConditionMet(current_state);
	if (memoization_cache[row_index][column_index].count(current_state)) return memoization_cache[row_index][column_index][current_state];

	int& result_value = memoization_cache[row_index][column_index][current_state];
	int next_row_index = row_index, next_column_index = column_index + 1;
	if (next_column_index >= number_of_columns) next_row_index++, next_column_index = 0;

	if ((current_state[0] > '0' || current_state.back() > '0') && board_layout[row_index][column_index] == '#' || current_state.back() > '0' && column_index == 0);
	else if (current_state[0] > '0' && current_state.back() > '0') {
		if (current_state[0] == current_state.back());
		else result_value = DepthFirstSearch(next_row_index, next_column_index, ConverterInstance(2, current_state));
	}
	else if (current_state[0] > '0') {
		result_value += DepthFirstSearch(next_row_index, next_column_index, ConverterInstance(3, current_state));
		result_value += DepthFirstSearch(next_row_index, next_column_index, ConverterInstance(4, current_state));
	}
	else if (current_state.back() > '0') {
		result_value += DepthFirstSearch(next_row_index, next_column_index, ConverterInstance(1, current_state));
		result_value += DepthFirstSearch(next_row_index, next_column_index, ConverterInstance(5, current_state));
	}
	else {
		if (board_layout[row_index][column_index] != '#') result_value += DepthFirstSearch(next_row_index, next_column_index, ConverterInstance(6, current_state));
		result_value += DepthFirstSearch(next_row_index, next_column_index, ConverterInstance(0, current_state));
	}

	return result_value %= MODULO_VALUE;
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	cin >> number_of_rows >> number_of_columns;
	for (int row_index = 0; row_index < number_of_rows; row_index++) cin >> board_layout[row_index];
	string initial_state(number_of_columns + 1, '0'); 
    initial_state[0] = '1';
	cout << DepthFirstSearch(0, 0, initial_state) << '\n';
}
