#include <boost/functional/hash.hpp>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;
void getOuterCoordonates(int x, int y, int dist, unordered_set<pair<int, int>, boost::hash<pair<int, int>>> &resultSet);
void getAllCoordonates(int x, int y, int dist, unordered_set<pair<int, int>, boost::hash<pair<int, int>>> &resultSet);
void getAllCoordonatesOfBuilding(int x, int y, int dist, const vector<pair<int, int>> &buildingScheme, unordered_set<pair<int, int>, boost::hash<pair<int, int>>> &resultSet);
int calculateScoreFromSet(const unordered_set<pair<int, int>, boost::hash<pair<int, int>>> &set, const vector<vector<int>> &map);