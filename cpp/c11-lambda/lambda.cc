#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Event {
  int timestamp;
  double gain;
};

int main(int argc, char* argv[]) {

  vector<Event> events = {
    { 9, +1.0 },
    { 2, -1.0 },
    { 4, +3.0 },
    { 5, -2.0 },
    { 1, +5.0 },
  };

  auto printEvents = [](const vector<Event>& events) {
    for (auto event : events) {
      cout << event.timestamp << "\t" << event.gain << "\n";
    }
  };

  cout << "input:\n";
  printEvents(events);

  auto byTs = [](const Event& a, const Event& b) -> bool {
    return a.timestamp < b.timestamp;
  };
  sort(events.begin(), events.end(), byTs);

  cout << "\nsorted by timestamp:\n";
  printEvents(events);

  sort(events.begin(), events.end(), [](const Event& a, const Event& b) -> bool {
      return a.gain < b.gain;
    });

  cout << "\nsorted by gain:\n";
  printEvents(events);

  return 0;
}
