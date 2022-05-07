#pragma once

#include <map>
#include <string>
#include <iostream>

class Style
{
public:

	Style(char* css, size_t len, Style * parent = nullptr, Style * default_style = nullptr ): m_parent(parent), m_default(default_style)
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
	}

	Style(Style* parent = nullptr, Style* default_style = nullptr) : m_parent(parent), m_default(default_style){}

	KDColor color() {
		KDColor result;
		std::string result_string = getValueOf("color");
		if (color_from_string(result_string, result)) {
			return result;
		}
		return KDColorBlack;
	}

	KDColor background_color() {
		KDColor result;
		std::string result_string = getValueOf("background-color");
		if (color_from_string(result_string, result)) {
			return result;
		}
		return KDColorBlack;
	}
	std::string getValueOf(std::string name) {
		try {
			return attrs.at(name);
		}
		catch (std::out_of_range) {
			return "";
		}
		
	}
private:
	int hex_to_int(char c) {
		if ('0' <= c && c <= '9')
			return int(c) - int('0');
		if ('A' <= c && c <= 'F')
			return 10 + int(c) - int('A');
		if ('a' <= c && c <= 'f')
			return 10 + int(c) - int('a');
		return -1;
	}
	bool color_from_string(std::string color_string, KDColor & result) {
		if (color_string.size() != 4 && color_string.size() != 7) {
			return false;
		}
		if (color_string[0] != '#') {
			return false;
		}
		
		int r = hex_to_int(color_string[1]) << 4;
		if (color_string.size() == 7) {
			r += hex_to_int(color_string[2]);
		}
		int g = hex_to_int(color_string[ (color_string.size() == 4 ? 2 : 3) ] ) << 4;
		if (color_string.size() == 7) {
			g += hex_to_int(color_string[4]);
		}
		int b = hex_to_int(color_string[ (color_string.size() == 4 ? 3 : 5) ] ) << 4;
		if (color_string.size() == 7) {
			r += hex_to_int(color_string[6]);
		}

		result = KDColor::RGB888( r , g , b );
		return true;
	}
	std::map<std::string, std::string> attrs;
	Style* m_parent;
	Style* m_default;
};

