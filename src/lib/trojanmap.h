#ifndef TROJAN_MAP_H
#define TROJAN_MAP_H
#define DOT_SIZE 5
#define LINE_WIDTH 3

#include <iostream>
#include <map>
#include <vector>

// A Node is the location of one point in the map.
class Node {
  // TODO: Add a constructor and a copy constructor.
  std::string id;    // A unique id assign to each point
  double lat;        // Latitude
  double lon;        // Longitude
  std::string name;  // Name of the location. E.g. "Bank of America".
  std::vector<std::string>
      neighbors;  // List of the ids of all neighbor points.
};

class TrojanMap {
 public:
  //-----------------------------------------------------
  // TODO: You do not and should not change the following functions:
  // TODO (Hong Shuo): Add clear comment for each of these functionss
  // Create the menu.
  void PrintMenu();
  // Read in the data
  void CreateGraphFromCSVFile();

  // Visualization
  void PlotPoint(std::string id);
  void PlotPoint(double lat, double lon);

  // Given a vector of location ids draws the path (connects the points
  // together)
  void PlotPath(std::vector<std::string> input);

  // Given a vector of location ids draws the points on the map (no path).
  void PlotPoints(std::vector<std::string> input);
  std::pair<double, double> GetPlotLocation(double lat, double lon);
  //-----------------------------------------------------
  // TODO: Implement these functions:

  // Get the Latitude of a Node given its id.
  double GetLat(std::string id);

  // Get the Longitude of a Node given its id.
  double GetLon(std::string id);

  // Get the name of a Node given its id.
  std::string GetName(std::string id);

  // Get the neighbor ids of a Node.
  std::vector<std::string> GetNeighborIDs(std::string id);

  // Get the distance between 2 nodes.
  double CalculateDistance(const struct Node &a, const struct Node &b);

  // Calculates the total path length for the locations inside the vector.
  float CalculatePathLength(const std::vector<std::string> &path);

  // Returns a vector of names given a partial name.
  std::vector<std::string> Autocomplete(std::string name);

  // Returns lat and long of the given the name.
  std::pair<double, double> GetPosition(std::string name);

  // Given the name of two locations, it should return the **ids** of the nodes
  // on the shortest path.
  std::vector<std::string> CalculateShortestPath(std::string location1_name,
                                                 std::string location2_name);

  // Given a vector of location ids, it should reorder them such that the path
  // that covers all these points has the minimum length.
  // The return value is a pair where the first member is the total_path,
  // and the second member is the reordered vector of points.
  // (Notice that we don't find the optimal answer. You can return an estimated
  // path.)
  std::pair<double, std::vector<std::string>> TravellingTrojan(
      std::vector<std::string> &location_ids);

  //-----------------------------------------------------

 private:
  // A map of ids to Nodes.
  std::map<std::string, Node> data;
};

#endif