class A {
  const int val_;

 public:
  A(int x, int y) : val_(x + y) {
  // This does not work
  // A(int x, int y) {
  //   val_ = x + y;
  }
};

int main() {
  A a(1, 2);
}
