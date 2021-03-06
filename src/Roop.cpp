#define VERBOSE_INTERACTIVE 1
#include "RoopCommon.h"
#include <fstream>
#include <string>
#include <iterator>
#include <readline/readline.h>
#include <readline/history.h>
#include <regex>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/lexical_cast.hpp>
#include <unistd.h>

using namespace cv;

bool isCommentOrWhitespace(char *lineData) {
  std::string line = lineData;
  bool allWhitespace = true;
  for (std::string::iterator ss = line.begin(); ss != line.end(); ss++) {
    if (*ss == ';') {
      return true; //is comment
    }
    else if (*ss != ' ') {
      allWhitespace = false;
      break;
    }
  }
  return allWhitespace;
}

bool isSkippableLine(char *lineData) {
  return isCommentOrWhitespace(lineData); 
}

bool processLine(char* _command, EvalResult &commandResult,
		 std::string &lastCommand, int &line_number,
		 bool &shouldDisplay, std::string &persistFilename) 
{

  if (!isSkippableLine(_command)) {
    if (isDisplayCommand(_command)) {
      imshow(lastCommand.c_str(), commandResult.resultMat);
      shouldDisplay = true;
    } 
    else if (isExitCommand(_command)) {
      std::cout << "Exit found" << std::endl;
      return true;
    }
    else if (boost::starts_with(_command, "(persist")) {
      std::vector<std::string> splitElements;
      boost::split(splitElements, _command, boost::is_any_of(" "));
      boost::replace_last(splitElements[1], ")", "");
      persistFilename = splitElements[1];
    }
    else {
     RoopList result = evaluate(_command);
      if (result.size() > 0) {
	commandResult = result[0];
	lastCommand = _command;
      }
    }
  }    
  return false;
}

char* dupstr(const char *text) {
  char *newString = (char*)malloc(strlen(text)+1);
  if (newString) {
    strcpy(newString, text);
  }
  return newString;
}

char* command_generator (const char *text, int state)
{
  static int list_index = 0;
  static int len;
  const char *name;

  if (!state)
    {
      list_index = 0;
      len = strlen (text);
    }

  /* Return the next name which partially matches from the
     command list. */
  while (name = getCommandList()[list_index].c_str())
    {    
      list_index++;
      if (list_index > getCommandList().size()) {
	break;
      }

      if (strncmp (name, text, len) == 0) {
        return (dupstr(name));
      }
    }

  /* If no names matched, then return NULL. */
  return (char *) NULL;
}

char **command_completion(const char *text, int start, int end)
{
  char **matches = (char **)NULL;
  
  int numchars = strlen(text);
  if (numchars > 0) {
    char first_preceder = ' ';
    for (int i=start-1; i>=0; i--) {
      if (rl_line_buffer[i] != ' ') {
	first_preceder = rl_line_buffer[i];
	break;
      }
    }
    if (first_preceder == '(') {
      matches = rl_completion_matches(text, command_generator);
    }
  }

  return matches;
}

void initialize_readline() 
{
  rl_attempted_completion_function = command_completion;
}

int main( int argc, char** argv )
{
  initRoop();

  char* initScriptFilename;
  char* cValue = NULL;
  int c;
  bool printCommands = false;

  opterr = 0;
  while ((c = getopt(argc, argv, "p")) != -1) {
    switch (c) {
    case 'p':
      printCommands = true;
      break;
    }
  }

  if (printCommands) {
    std::vector<std::string> commands = getCommandList();
    for (int i =0; i<commands.size(); i++) {
      std::cout << commands[i] << std::endl;
    }

    
    return 0;
  }


  cv::destroyWindow("win");
  char _command[256];
  sexp_t* command;
  EvalResult cResult;
  std::string lastCommand;
  bool shouldDisplay = false;
  std::string persistFilename = "";
    
  if (argc > 1) {
    char *initScriptFilename = argv[1];
    std::cout << "Received initializer file: " << initScriptFilename << std::endl;
    // Load initializer commands
    std::ifstream inputFile(initScriptFilename);
    int line_number = 0;
    while (inputFile.getline(_command, 256)) {
      if (processLine(_command, cResult, lastCommand, 
		      line_number, shouldDisplay, persistFilename)) {
	return 0;
      }
      add_history(_command);
      line_number ++;
      if (persistFilename != "") {
	std::cout << "Persisting to " << persistFilename << std::endl;
	cv::imwrite(persistFilename, cResult.resultMat);
	persistFilename = "";
      }
    }
    if (shouldDisplay) {
      waitKey(0);
    }
  }
 
  initialize_readline();

  while(true) {
    char *line = readline("Enter command: \t");
    add_history(line);
    shouldDisplay = false;
    int lnum = 0;
    if (processLine(line, cResult, lastCommand, lnum, shouldDisplay, persistFilename)) {
      return 0;
    }
    if (persistFilename != "") {
      std::cout << "Persisting to " << persistFilename << std::endl;
      cv::imwrite(persistFilename, cResult.resultMat);
      persistFilename = "";
    }
 
    if (shouldDisplay) {
      waitKey(0);
    }
    if (line) {
      free(line);
    }
   }

  return 0;
}
