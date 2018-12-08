#include<utility>
#include<unordered_set>
#include<vector>
#include<boost/functional/hash.hpp>

using namespace std;
void getOuterCoordonates(int x, int y, int dist, unordered_set<pair<int,int>, boost::hash<pair<int,int>>> &resultSet);
void getAllCoordonates(int x, int y, int dist, unordered_set<pair<int, int>,  boost::hash<pair<int,int>>> &resultSet);
void getAllCoordonatesOfBuilding(int x, int y, int dist, const vector<pair<int, int>> &buildingScheme, unordered_set<pair<int, int>, boost::hash<pair<int,int>>> &resultSet );
int calculateScoreFromSet(const unordered_set<pair<int,int>, boost::hash<pair<int,int>>> &set,const vector<vector<int>> &map);

    template <class T>
    inline void hash_combine(std::size_t & seed, const T & v)
    {
      std::hash<T> hasher;
      seed ^= hasher(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    }
     
    namespace std
    {
      template<typename S, typename T> struct hash<pair<S, T>>
      {
        inline size_t operator()(const pair<S, T> & v) const
        {
          size_t seed = 0;
          ::hash_combine(seed, v.first);
          ::hash_combine(seed, v.second);
          return seed;
        }
      };
    }