#include <iostream>
#include <string>
#include <vector>
#include <iterator>

class NaiveMatcher {
 public:
  class const_iterator {
   public:
    typedef const_iterator self_type;
    typedef int value_type;
    typedef int& reference;
    typedef int* pointer;
    typedef int difference_type;
    typedef std::forward_iterator_tag iterator_category;

    const_iterator(const std::string& pattern, const std::string& input, int index = 0) :
        pattern_(pattern),
        input_(input),
        index_(index)
    {
      index_ = search(index_);
    }

    self_type& operator++() {
      ++index_;
      index_ = search(index_);
      return *this;
    }

    // Why?
    // warning: 'const' qualifier on reference type 'reference' (aka 'int &') has no effect
    //       [-Wignored-qualifiers]
    // const reference operator*() {
    value_type operator*() const {
      return index_;
    }

    bool operator==(const self_type& other) const {
      if (index_ == -1 && other.index_ == -1) return true;

      return pattern_ == other.pattern_ &&
          input_ == other.input_ &&
          index_ == other.index_;
    }

    bool operator!=(const self_type& other) const {
      return !(*this == other);
    }

   private:
    const std::string& pattern_;
    const std::string& input_;
    int index_;

    int search(int startIndex) {
      if (startIndex == -1) return -1;
      int i = startIndex, m = pattern_.size(), n = input_.size();
      for (; i + m <= n; ++i) {
        if (input_.substr(i, m) == pattern_) return i;
      }
      return -1;
    }
  };

  NaiveMatcher(const std::string& pattern) :
      pattern_(pattern)
  {}

  const_iterator begin(const std::string& input) const {
    return const_iterator(pattern_, input, 0);
  }

  const_iterator end() const {
    return const_iterator("", "", -1);
  }

 private:
  const std::string& pattern_;

};

class KMPMatcher {
 public:
  class const_iterator {
   public:
    typedef const_iterator self_type;
    typedef int value_type;
    typedef int& reference;
    typedef int* pointer;
    typedef int difference_type;
    typedef std::forward_iterator_tag iterator_category;

    const_iterator(const std::string& pattern, const std::string& input, int index = 0) :
        pattern_(pattern),
        input_(input),
        index_(index),
        border_(0)
    {
      if (index_ != -1) {
        buildPrefix();
        index_ = search(0);
      }
    }

    self_type& operator++() {
      index_ = search(index_ + pattern_.size());
      return *this;
    }

    value_type operator*() const {
      return index_;
    }

    bool operator==(const self_type& other) const {
      if (index_ == -1 && other.index_ == -1) return true;

      return pattern_ == other.pattern_ &&
          input_ == other.input_ &&
          index_ == other.index_;
    }

    bool operator!=(const self_type& other) const {
      return !(*this == other);
    }

   private:
    const std::string& pattern_;
    const std::string& input_;
    int index_;
    int border_;

    // Prefix function
    std::vector<int> s_;

    void buildPrefix() {
      s_.resize(pattern_.size());
      s_[0] = 0;
      int border = 0;
      for (int i = 1, m = s_.size(); i < m; ++i) {
        while (border > 0 && pattern_[border] != pattern_[i]) {
          border = s_[border - 1];
        }
        if (pattern_[border] == pattern_[i]) {
          border += 1;
        }
        s_[i] = border;
      }
      // std::cout << "s_: ";
      // for (size_t i = 0; i < s_.size(); ++i) std::cout << (i > 0 ? ", " : "") << s_[i];
      // std::cout << "\n";
    }

    int search(int startIndex) {
      if (startIndex == -1) return -1;
      int i = startIndex, m = pattern_.size(), n = input_.size();
      for (; i < n; ++i) {
        while (border_ > 0 && pattern_[border_] != input_[i]) {
          border_ = s_[border_ - 1];
        }

        if (pattern_[border_] == input_[i]) {
          border_ += 1;
        }

        if (border_ == m) {
          border_ = s_[border_ - 1];
          return i - m + 1;
        }

      }
      return -1;
    }
  };

  KMPMatcher(const std::string& pattern) :
      pattern_(pattern)
  {}

  const_iterator begin(const std::string& input) const {
    return const_iterator(pattern_, input, 0);
  }

  const_iterator end() const {
    return const_iterator("", "", -1);
  }

 private:
  const std::string& pattern_;

};

template <typename Matcher>
void testMatcher(const std::string& pattern, const std::string& input) {
  std::cout << "input: " << input << "\n";
  std::cout << "pattern: " << pattern << "\n";
  Matcher m(pattern);
  std::cout << "occurrences: [ ";
  for (typename Matcher::const_iterator beg = m.begin(input), end = m.end(), it = beg;
       it != end;
       ++it) {
    std::cout << (it == beg ? "" : " ")  << *it;
  }
  std::cout << " ]\n";
}

int main(int argc, char* argv[]) {
  {
    std::string input = "hello world hello world";
    std::string pattern = "world";
    testMatcher<NaiveMatcher>(pattern, input);
    testMatcher<KMPMatcher>(pattern, input);
  }
  {
    std::string input = "aaaaaaaaaaa";
    std::string pattern = "aaa";
    testMatcher<NaiveMatcher>(pattern, input);
    testMatcher<KMPMatcher>(pattern, input);
  }
  {
    std::string input = "abcdfabcdgabcdx";
    std::string pattern = "abcde";
    testMatcher<NaiveMatcher>(pattern, input);
    testMatcher<KMPMatcher>(pattern, input);
  }
  {
    std::string input = "abababacababababaababacabacababacabab";
    std::string pattern = "ababacabab";
    testMatcher<NaiveMatcher>(pattern, input);
    testMatcher<KMPMatcher>(pattern, input);
  }
  return 0;
}
