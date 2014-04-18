#include "syntaxkeywords.h"
#include <string>

const char *SYNTAX_KEYWORDS = "add|and|area|binarize|blur|canny|centroid|dilate|enhance|erode|filter|find-connected|gamma-correct-gray|get|get-foreground-mask|invert|laplace|load|make-color|make-gray|mult|probe|remove-background|resize|save|scharr|set|sharpen|sobel|subtract|writeparams";

std::map<std::string, std::string> createKeywordMap()
{
	std::map<std::string, std::string> m;
	m["and"] = "";
	m["load"] = "";
	m["set"] = "";
	m["sobel"] = "";
	m["probe"] = "";
	m["writeparams"] = "";
	m["binarize"] = "";
	m["gamma-correct-gray"] = "";
	m["area"] = "";
	m["invert"] = "";
	m["remove-background"] = "";
	m["make-color"] = "";
	m["get-foreground-mask"] = "";
	m["add"] = "";
	m["centroid"] = "";
	m["resize"] = "";
	m["blur"] = "";
	m["sharpen"] = "";
	m["save"] = "";
	m["erode"] = "";
	m["get"] = "";
	m["find-connected"] = "";
	m["canny"] = "";
	m["subtract"] = "";
	m["mult"] = "";
	m["dilate"] = "";
	m["filter"] = "";
	m["scharr"] = "";
	m["make-gray"] = "";
	m["enhance"] = "";
	m["laplace"] = "";
	return m;
}

std::map<std::string, std::string> keywordMap = createKeywordMap();

