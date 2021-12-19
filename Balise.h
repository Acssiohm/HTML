#pragma once
#include <iostream>
#include "KDColor.h"

class Balise {
public:

	const char* balises[100]{
		"html", "head", "body", "link", "meta", "script", "style", "title",
		"abbr", "blockquote", "cite", "q",
		"sup", "sub",
		"strong", "em", "mark",
		"h1", "h2", "h3", "h4", "h5", "h6",
		"img", "figure", "figcaption",
		"audio", "video", "source",
		"a",
		"br",
		"p",
		"hr",
		"address",
		"del",
		"ins",
		"dfn",
		"kbd",
		"pre",
		"progress",
		"ul",
		"ol",
		"li",
		"dl",
		"dt",
		"dd",
		"span",
		"div",
		"input",
		"unknown",
		"Text"
	};
	enum class Balises {
		html, head, body, link, meta, script, style, title,
		abbr, blockquote, cite, q,
		sup, sub,
		strong, em, mark,
		h1, h2, h3, h4, h5, h6,
		img, figure, figcaption,
		audio, video, source,
		a,
		br,
		p,
		hr,
		address,
		del,
		ins,
		dfn,
		kbd,
		pre,
		progress,
		ul,
		ol,
		li,
		dl,
		dt,
		dd,
		span,
		div,
		input,
		unknown,
		Text
	};
	Balise(Balises name) :m_name(name) {}
	Balise(char * str , size_t len) :m_name(str_to_balises(str, len)) {}
	Balise(const char* str) :m_name(str_to_balises(str, strlen(str))) {}
	bool isOrpheline();
	KDColor defaultColor();
	bool isUndisplayable();
	bool isDisplayable();
	bool isInline();
	bool isBlock();
	friend bool operator==(const Balise& b1, const Balise& b2);
	const char* text ()const;
private:
	Balises str_to_balises(const char* str, size_t len);
	Balises m_name;
};

std::ostream &operator<<(std::ostream& os, const Balise& b);

