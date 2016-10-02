#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <iterator>
#include <algorithm>

using namespace std;

class Solution {
 public:
  struct Token {
    enum Type { NUMBER = 0, PLUS, MINUS, LEFT_PAR, RIGHT_PAR };
    Type type_;
    // Only make sense when type is number
    int val_;
    Token(): type_(NUMBER), val_(0) {}
  };

  class Tokenizer {
   public:
    Tokenizer(const string& s):
        s_(s), i_(0),
        hasNext_(false),
        nextToken_(Token())
    {
      skipSpace();
      advance();
    }

    bool hasNext() const {
      return hasNext_;
    }

    void next(Token& token) {
      token = nextToken_;
      advance();
    }

   private:
    const string& s_;
    int i_;
    bool hasNext_;
    Token nextToken_;

    void skipSpace() {
      int n = s_.size();
      while (i_ < n && s_[i_] == ' ') ++i_;
    }

    void advance() {
      int n = s_.size();
      if (i_ == n) {
        hasNext_ = false;
        return;
      }

      char c = s_[i_];
      Token token;
      switch (c) {
        case '(': token.type_ = Token::LEFT_PAR; ++i_; break;
        case ')': token.type_ = Token::RIGHT_PAR; ++i_; break;
        case '+': token.type_ = Token::PLUS; ++i_; break;
        case '-': token.type_ = Token::MINUS; ++i_; break;
        default:
          if (c >= '0' && c <= '9') {
            // Number:
            int start = i_;
            while (i_ < n && c >= '0' && c <= '9') c = s_[++i_];
            token.type_ = Token::NUMBER;
            token.val_ = atoi(s_.substr(start, i_ - start).c_str());
          } else {
            throw runtime_error("Unexpected token " + string(1, c));
          }
      }
      nextToken_ = token;
      hasNext_ = true;
      skipSpace();
    }
  };

  int calculate(string s) {
    Tokenizer tokenizer(s);
    Token token;
    // vector<string> types = { "NUMBER", "PLUS", "MINUS", "LEFT_PAR", "RIGHT_PAR" };

    int result = 0;
    int sign = 1;
    vector<pair<int, int> > stack;
    while (tokenizer.hasNext()) {
      tokenizer.next(token);
      // cout << "token: type=" << types[token.type_] << " val=" << token.val_ << "\n";
      switch (token.type_) {
        case Token::NUMBER: result += sign * token.val_; break;
        case Token::PLUS: sign = 1; break;
        case Token::MINUS: sign = -1; break;
        case Token::LEFT_PAR: stack.push_back(make_pair(result, sign)); result = 0; sign = 1; break;
        case Token::RIGHT_PAR: {
          const pair<int, int>& top = stack.back();
          result = result * top.second + top.first;
          stack.pop_back();
          break;
        }
        default: break;
      }
    }

    return result;
  }
};

void test(const string& input, int expected) {
  Solution sol;
  cout << "input: \"" << input << "\"\n";
  cout << "result: " << sol.calculate(input) << "\n";
  cout << "expected: " << expected << "\n\n";
}

int main(int argc, char* argv[]) {
  test("1 + 1", 2);
  test(" 2-1 + 2 ", 3);
  test("(1+(4+5+2)-3)+(6+8)", 23);
  return 0;
}
