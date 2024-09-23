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
      return true;
    }
  }
  return false;
}

bool characterGroupMatch(const std::string &input_line,
                         const std::string &pattern, int start, int end) {

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

bool negativeCharacterGroupMatch(const std::string &input_line,
                                 const std::string &pattern, int start,
                                 int end) {
  std::unordered_set<char> pattern_set;
  for (int i = 2; i < pattern.size() - 1; i++) {
    pattern_set.insert(pattern[i]);
  }
  for (int i = 0; i < input_line.size(); i++) {
    if (pattern_set.find(input_line[i]) != pattern_set.end()) {
      return false;
    }
  }
  return true;
}

bool match(const std::string &input_line, const std::string &pattern) {
  int i = 0;
  while (i < input_line.size()) {
    int j = 0;
    int temp = i;
    while (j < pattern.size() && temp < input_line.size()) {
      if (pattern[j] == '\\') {
        j++;
        if (j < pattern.size()) {
          if (pattern[j] == 'd') {
            if (!isdigit(input_line[temp])) {
              break;
            } else
              temp++;
          } else if (pattern[j] == 'w') {
            if (!isalnum(input_line[temp])) {
              break;
            } else
              temp++;
          } else if (pattern[j] == '[') {
            int start = j;
            while (j < pattern.size()) {
              if (pattern[j] != ']')
                j++;
            }
            if (pattern[j] == '^') {
              return negativeCharacterGroupMatch(input_line, pattern, start,
                                                 j + 1);
            } else {
              return characterGroupMatch(input_line, pattern, start, j + 1);
            }
          }
        } else {
          break;
        }
      } else {
        if (input_line[temp] != pattern[j]) {
          break;
        } else
          temp++;
      }
      j++;
    }
    if (j == pattern.size())
      return true;
    i++;
  }

  return false;
}

bool stringAnchorMatch(const std::string &input_line,
                       const std::string &pattern) {
  if (pattern[0] == '^') {
    return input_line.find(pattern.substr(1)) == 0;
  } else if (pattern[pattern.size() - 1] == '$') {
    return input_line.find(pattern.substr(0, pattern.size() - 1)) ==
           input_line.size() - pattern.size() + 1;
  }
  return false;
}

bool match_pattern(const std::string &input_line, const std::string &pattern) {
  if (pattern.length() >= 3 && pattern[0] == '[' &&
      pattern[pattern.length() - 1] == ']') {
    if (pattern[1] == '^')
      return negativeCharacterGroupMatch(input_line, pattern);
    else
      return characterGroupMatch(input_line, pattern);
  }
  if (pattern == "\\w") {
    return !isAlphaNumeric(input_line);
  } else if (pattern == "\\d") {
    return !isDigitExist(input_line);
  } else if (pattern.length() == 1) {
    return input_line.find(pattern) != std::string::npos;
  } else if (pattern.length() > 3) {
    return match(input_line, pattern);
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
