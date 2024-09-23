#include <iostream>
#include <string>
#include <unordered_set>

bool isDigitExist(std::string str) {
  for (int i = 0; i < str.size(); i++) {
    if (isdigit(str[i])) {
      return true;
    }
  }
  return false;
}

bool isAlphaNumeric(std::string str) {
  for (int i = 0; i < str.size(); i++) {
    if (isalnum(str[i]) == 0) {
      return false;
    }
  }
  return true;
}

bool characterGroupMatch(const std::string &input_line,
                         const std::string &pattern) {
  std::unordered_set<char> pattern_set;
  for (int i = 1; i < pattern.size() - 1; i++) {
    pattern_set.insert(pattern[i]);
  }

  for (int i = 0; i < input_line.size(); i++) {
    if (pattern_set.find(input_line[i]) != pattern_set.end()) {
      return true;
    }
  }
  return false;
}

bool match_pattern(const std::string &input_line, const std::string &pattern) {
  if (pattern.length() >= 3 && pattern[0] == '[' &&
      pattern[pattern.length() - 1] == ']') {
    return characterGroupMatch(input_line, pattern);
  }
  if (pattern == "\\w") {
    return isAlphaNumeric(input_line);
  } else if (pattern == "\\d") {
    return isDigitExist(input_line);
  } else if (pattern.length() == 1) {
    return input_line.find(pattern) != std::string::npos;
  } else {
    throw std::runtime_error("Unhandled pattern " + pattern);
  }
}

int main(int argc, char *argv[]) {
  // Flush after every std::cout / std::cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

  // You can use print statements as follows for debugging, they'll be visible
  // when running tests.
  std::cout << "Logs from your program will appear here" << std::endl;

  if (argc != 3) {
    std::cerr << "Expected two arguments" << std::endl;
    return 1;
  }

  std::string flag = argv[1];
  std::string pattern = argv[2];

  if (flag != "-E") {
    std::cerr << "Expected first argument to be '-E'" << std::endl;
    return 1;
  }

  std::string input_line;
  std::getline(std::cin, input_line);

  try {
    if (match_pattern(input_line, pattern)) {
      return 0;
    } else {
      return 1;
    }
  } catch (const std::runtime_error &e) {
    std::cerr << e.what() << std::endl;
    return 1;
  }
}
