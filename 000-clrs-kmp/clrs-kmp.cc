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
    value_type operator*() {
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

// class KMPMatcher {
//  public:
//   class iterator {

//   }
// };

template <typename Matcher>
void test(const std::string& pattern, const std::string& input) {
  std::cout << "input: " << input << "\n";
  std::cout << "pattern: " << pattern << "\n";
  Matcher m(pattern);
  typename Matcher::const_iterator it = m.begin(input), end = m.end();
  for (; it != end; ++it) {
    std::cout << "index: " << *it << "\n";
  }
}

int main(int argc, char* argv[]) {
  {
    std::string input = "hello world hello world";
    std::string pattern = "world";
    test<NaiveMatcher>(pattern, input);
  }
  {
    std::string input = "aaaaaaaaaaa";
    std::string pattern = "aaa";
    test<NaiveMatcher>(pattern, input);
  }
  return 0;
}
