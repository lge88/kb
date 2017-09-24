#include <memory>
#include <iostream>

#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>

#include "Scoring.h"

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

using boost::shared_ptr;

class ScoringHandler : virtual public ScoringIf {
 public:
  ScoringHandler() {
    // Your initialization goes here
    std::cout << "Init ScoringHandler...\n";
    std::cout << "Load scoring models..\n";
  }

  double lookupWeight(int globalFeatureIndex) {
    return globalFeatureIndex;
  }

  double lookupWeight(int creativeId, int demandFeatureIndex) {
    return demandFeatureIndex;
  }

  void score(ScoringResponse& res, const ScoringRequest& req) {
    // Your implementation goes here
    int numAds = req.demandFeatures.size();
    double baseScore = 0.0;
    for (auto i : req.globalFeatures.indices) {
      baseScore += lookupWeight(i);
    }

    res.pctrScores.resize(numAds, baseScore);
    res.pcvrScores.resize(numAds, baseScore);

    for (auto demandFeatureVector : req.demandFeatures) {
      auto creativeId = demandFeatureVector.creativeId;
      for (int i = 0; i < numAds; ++i) {
        auto index = demandFeatureVector.indices[i];
        res.pctrScores[i] += lookupWeight(creativeId, index);
      }
    }

    std::cerr << "pctr: [";
    for (auto x : res.pctrScores) std::cerr << " " << x;
    std::cerr << " ]\n";

    std::cerr << "pcvr: [";
    for (auto x : res.pcvrScores) std::cerr << " " << x;
    std::cerr << " ]\n";;
  }

};

int main(int argc, char **argv) {
  int port = 9090;
  shared_ptr<ScoringHandler> handler(new ScoringHandler());
  shared_ptr<TProcessor> processor(new ScoringProcessor(handler));
  shared_ptr<TServerTransport> serverTransport(new TServerSocket(port));
  shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
  shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());

  TSimpleServer server(processor, serverTransport, transportFactory, protocolFactory);
  server.serve();
  return 0;
}
