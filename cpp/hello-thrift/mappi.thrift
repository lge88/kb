
enum FeatureType {
  GLOBAL = 1,
  DEMAND = 2
}

struct FeatureVector {
  1:list<i64> indices,
  2:FeatureType type = FeatureType.GLOBAL,
  3:i64 creativeId = 0
}

struct ScoringRequest {
  1:FeatureVector globalFeatures,
  2:list<FeatureVector> demandFeatures
}

struct ScoringResponse {
  1:list<double> pctrScores,
  2:list<double> pcvrScores
}

service Scoring {
  ScoringResponse score(1:ScoringRequest request)
}
