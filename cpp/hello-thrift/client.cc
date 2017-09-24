#include <iostream>
#include <memory>

#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TTransportUtils.h>

#include "Scoring.h"

using namespace std;
using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;

int main() {
  boost::shared_ptr<TTransport> socket(new TSocket("127.0.0.1", 9090));
  boost::shared_ptr<TTransport> transport(new TBufferedTransport(socket));
  boost::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));
  ScoringClient client(protocol);

  // cout << "opening transport...\n";
  try {
    transport->open();
  }
  catch (TException& tx) {
    cout << "ERROR: " << tx.what() << endl;
  }

  ScoringRequest req;
  ScoringResponse res;

  req.globalFeatures.indices = { 1, 2 };

  req.demandFeatures.resize(3);

  req.demandFeatures[0].creativeId = 1;
  req.demandFeatures[0].indices = { 4, 5 };

  req.demandFeatures[1].creativeId = 2;
  req.demandFeatures[1].indices = { 7 };

  req.demandFeatures[2].creativeId = 3;
  req.demandFeatures[2].indices = { 8, 9, 10 };

  try {
    client.score(res, req);
    cout << "pctr: [";
    for (auto x : res.pctrScores) cout << " " << x;
    cout << " ]\n";

    cout << "pcvr: [";
    for (auto x : res.pcvrScores) cout << " " << x;
    cout << " ]\n";
  }
  catch(...) {
    cout << "score failed: \n";
  }
}
