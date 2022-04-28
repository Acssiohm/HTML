#pragma once

#include <map>
#include <string>
#include <iostream>

class Style
{
public:

	Style(char* css, size_t len)
	{
		unsigned int pos = 0;
		while (pos < len) {
			while (isspace(css[pos]) && pos < len) {
				pos++;
			}
			int name_start = pos;
			while (!isspace(css[pos]) && css[pos] != ':' && pos < len) {
				pos++;
			}
			int name_end = pos;
			while (css[pos] != ':' && pos < len) {
				pos++;
			}
			pos++;
			while (isspace(css[pos]) && pos < len) {
				pos++;
			}
			int value_start = pos;
			while (!isspace(css[pos]) && css[pos] != ';' && pos < len) {
				pos++;
			}
			int value_end = pos;
			while (css[pos] != ';' && pos < len) {
				pos++;
			}
			pos++;
			std::string name(&css[name_start], name_end - name_start);
			std::string value(&css[value_start], value_end - value_start);
			if (name.size() && value.size()) {
				attrs[name] = value;
			}
		}
		for (std::pair<std::string, std::string> p : attrs) {
			std::cout << "name = '" << p.first << "'  value = '" << p.second << "' ;\n";
		}
	}
	Style(){}
	std::string getValueOf(std::string name) {
		return attrs[name];
	}
private:
	std::map<std::string, std::string> attrs;
};

