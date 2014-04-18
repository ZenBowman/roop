import sys

if __name__ == "__main__":
    f = open(sys.argv[1])
    cmap = {}
    pattern = ""
    for line in f.readlines():
        pattern += line.strip()
        cmap[line.strip()] = ""
        pattern += "|"
    f.close()
    pattern = pattern.strip("|")
    print '#include "syntaxkeywords.h"'
    print "#include <string>"
    print ""
    print 'const char *SYNTAX_KEYWORDS = "%s";' % pattern
    print ""
    
    print "std::map<std::string, std::string> createKeywordMap()"
    print "{"
    print "\tstd::map<std::string, std::string> m;"
    for k in cmap:
        print '\tm["%s"] = "%s";' % (k, cmap[k])
    print "\treturn m;"
    print "}"
