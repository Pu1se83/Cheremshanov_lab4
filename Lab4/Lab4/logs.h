#pragma once

#include <iostream>
#include <string>
#include <limits>

#define INPUT_LINE(in, str) getline(in>>ws, str); \
						cerr << str << endl

#define PRINT_PARAM(out, x) out<< #x << "=" << x << endl

using namespace std;

class redirect_output_wrapper
{
    ostream& stream;
    streambuf* const old_buf;
public:
    redirect_output_wrapper(ostream& src)
        :old_buf(src.rdbuf()), stream(src)
    {
    }

    ~redirect_output_wrapper() {
        stream.rdbuf(old_buf);
    }
    void redirect(ostream& dest)
    {
        stream.rdbuf(dest.rdbuf());
    }
};

template <typename T>
T read_input(const string& prompt, const T min_value = numeric_limits<T>::lowest(), const T max_value = numeric_limits<T>::max()) {
    T value;
    while (true) {
        cout << prompt;

        if constexpr (is_integral_v<T> || is_floating_point_v<T>) {
            if (cin >> value && cin.peek() == '\n' && value >= min_value && value <= max_value) {
                cerr << value << endl;  // Логирование введенного значения
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                return value;
            }
            else {
                cout << "Invalid input. Please enter a valid number between " << min_value << " and " << max_value << ".\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
        else if constexpr (is_same_v<T, string>) {
            getline(cin >> ws, value);
            if (!value.empty()) {
                cerr << value << endl;  // Логирование введенного значения
                return value;
            }
            else {
                cout << "Invalid input. Please enter a non-empty string.\n";
            }
        }
    }
}
