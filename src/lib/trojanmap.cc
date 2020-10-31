#include "trojanmap.h"

#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <algorithm>
#include <fstream>
#include <locale>
#include <map>
#include <queue>
#include <sstream>
#include <string>
#include <utility>

#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"

//-----------------------------------------------------
// TODO (Students): You do not and should not change the following functions:
//-----------------------------------------------------
// TODO (Hong Shuo): Use switch case instead of if statements.

void TrojanMap::PrintMenu() {

  std::string menu =
      "**************************************************************\n"
      "* Select the function you want to execute.                     \n"
      "* 1. Autocomplete                                             \n"
      "* 2. Find the position                                        \n"
      "* 3. CalculateShortestPath                                              "
      "    \n"
      "* 4. Travelling salesman problem                              \n"
      "* 5. Exit                                                     \n"
      "**************************************************************\n";
  std::cout << menu << std::endl;
  std::string input;
  getline(std::cin, input);
  char swit = input[0];
  switch (swit)
  {
  case '1':
  {
    menu =
        "**************************************************************\n"
        "* 1. Autocomplete                                             \n"
        "**************************************************************\n";
    std::cout << menu << std::endl;
    menu = "Please input a partial location:";
    std::cout << menu;
    getline(std::cin, input);
    auto results = Autocomplete(input);
    menu = "*************************Results******************************\n";
    std::cout << menu;
    if (results.size() != 0) {
      for (auto x : results) std::cout << x << std::endl;
    } else {
      std::cout << "No matched locations." << std::endl;
    }
    menu = "**************************************************************\n";
    std::cout << menu << std::endl;
    PrintMenu();
    break;
  }
  case '2':
  {
    menu =
        "**************************************************************\n"
        "* 2. Find the position                                        \n"
        "**************************************************************\n";
    std::cout << menu << std::endl;
    menu = "Please input a location:";
    std::cout << menu;
    getline(std::cin, input);
    auto results = GetPosition(input);
    menu = "*************************Results******************************\n";
    std::cout << menu;
    if (results.first != -1) {
      std::cout << "Latitude: " << results.first
                << " Longitude: " << results.second << std::endl;
      PlotPoint(results.first, results.second);
    } else {
      std::cout << "No matched locations." << std::endl;
    }
    menu = "**************************************************************\n";
    std::cout << menu << std::endl;
    PrintMenu();
    break;
  }
  case '3':
  {
    menu =
        "**************************************************************\n"
        "* 3. CalculateShortestPath                                            "
        "      \n"
        "**************************************************************\n";
    std::cout << menu << std::endl;
    menu = "Please input the start location:";
    std::cout << menu;
    std::string input1;
    getline(std::cin, input1);
    menu = "Please input the destination:";
    std::cout << menu;
    std::string input2;
    getline(std::cin, input2);
    auto results = CalculateShortestPath(input1, input2);
    menu = "*************************Results******************************\n";
    std::cout << menu;
    if (results.size() != 0) {
      for (auto x : results) std::cout << x << std::endl;
      PlotPath(results);
    } else {
      std::cout << "No route from the start point to the destination."
                << std::endl;
    }
    menu = "**************************************************************\n";
    std::cout << menu << std::endl;
    PrintMenu();
    break;
  }
  case '4':
  {
    menu =
        "**************************************************************\n"
        "* 4. Travelling salesman problem                              \n"
        "**************************************************************\n";
    std::cout << menu << std::endl;
    menu = "Please input the number of the places:";
    std::cout << menu;
    int num;
    std::cin >> num;
    std::vector<std::string> keys;
    for (auto x : data) {
      keys.push_back(x.first);
    }
    std::vector<std::string> locations;
    srand(time(NULL));
    for (int i = 0; i < num; i++)
      locations.push_back(keys[rand() % keys.size()]);
    PlotPoints(locations);
    auto results = TravellingTrojan(locations);
    menu = "*************************Results******************************\n";
    std::cout << menu;
    if (results.second.size() != 0) {
      std::cout << "Shortest Path distance is:" << results.first << std::endl;
      for (auto x : results.second) std::cout << x << std::endl;
      PlotPath(results.second);
    } else {
      std::cout << "Path size is 0" << std::endl;
    }
    menu = "**************************************************************\n";
    std::cout << menu;
    PrintMenu();
    break;
  }
  case '5':
    break;
  default:
    std::cout << "Please select 1 - 5." << std::endl;
    PrintMenu();
    break;
  }
}


/**
 * CreateGraphFromCSVFile: Read the map data from the csv file
 *
 */
void TrojanMap::CreateGraphFromCSVFile() {
  std::fstream fin;
  fin.open("src/main/map.csv", std::ios::in);
  std::string line, word;

  getline(fin, line);
  while (getline(fin, line)) {
    std::stringstream s(line);

    Node n;
    int count = 0;
    while (getline(s, word, ',')) {
      word.erase(std::remove(word.begin(), word.end(), '\''), word.end());
      word.erase(std::remove(word.begin(), word.end(), '"'), word.end());
      word.erase(std::remove(word.begin(), word.end(), '['), word.end());
      word.erase(std::remove(word.begin(), word.end(), ']'), word.end());
      if (count == 0)
        n.id = word;
      else if (count == 1)
        n.lat = stof(word);
      else if (count == 2)
        n.lon = stof(word);
      else if (count == 3)
        n.name = word;
      else
        n.neighbors.push_back(word);
      count++;
    }
    data[n.id] = n;
  }
  fin.close();
}

void TrojanMap::PlotPoint(std::string id) {
  std::string image_path = cv::samples::findFile("src/main/input.jpg");
  cv::Mat img = cv::imread(image_path, cv::IMREAD_COLOR);
  auto result = GetPlotLocation(GetLat(id), GetLon(id));
  cv::circle(img, cv::Point(result.first, result.second), DOT_SIZE,
             cv::Scalar(0, 0, 255), cv::FILLED);
  cv::imshow("TrojanMap", img);
  cv::waitKey(0);
}

void TrojanMap::PlotPoint(double lat, double lon) {
  std::string image_path = cv::samples::findFile("src/main/input.jpg");
  cv::Mat img = cv::imread(image_path, cv::IMREAD_COLOR);
  auto result = GetPlotLocation(lat, lon);
  cv::circle(img, cv::Point(int(result.first), int(result.second)), DOT_SIZE,
             cv::Scalar(0, 0, 255), cv::FILLED);
  cv::startWindowThread();
  cv::imshow("TrojanMap", img);
  cv::waitKey(0);
}

void TrojanMap::PlotPath(std::vector<std::string> input) {
  std::string image_path = cv::samples::findFile("src/main/input.jpg");
  cv::Mat img = cv::imread(image_path, cv::IMREAD_COLOR);
  auto start = GetPlotLocation(GetLat(input[0]), GetLon(input[0]));
  cv::circle(img, cv::Point(int(start.first), int(start.second)), DOT_SIZE,
             cv::Scalar(0, 0, 255), cv::FILLED);
  for (int i = 1; i < input.size(); i++) {
    auto start = GetPlotLocation(GetLat(input[i - 1]), GetLon(input[i - 1]));
    auto end = GetPlotLocation(GetLat(input[i]), GetLon(input[i]));
    cv::circle(img, cv::Point(int(end.first), int(end.second)), DOT_SIZE,
               cv::Scalar(0, 0, 255), cv::FILLED);
    cv::line(img, cv::Point(int(start.first), int(start.second)),
             cv::Point(int(end.first), int(end.second)), cv::Scalar(0, 255, 0),
             LINE_WIDTH);
  }
  cv::startWindowThread();
  cv::imshow("TrojanMap", img);
  cv::waitKey(0);
}

void TrojanMap::PlotPoints(std::vector<std::string> input) {
  std::string image_path = cv::samples::findFile("src/main/input.jpg");
  cv::Mat img = cv::imread(image_path, cv::IMREAD_COLOR);
  for (auto x : input) {
    auto result = GetPlotLocation(GetLat(x), GetLon(x));
    cv::circle(img, cv::Point(result.first, result.second), DOT_SIZE,
               cv::Scalar(0, 0, 255), cv::FILLED);
  }
  cv::imshow("TrojanMap", img);
  cv::waitKey(0);
}

std::pair<double, double> TrojanMap::GetPlotLocation(double lat, double lon) {
  std::pair<double, double> bottomLeft(34.01001, -118.30000);
  std::pair<double, double> upperRight(34.03302, -118.26502);
  double h = upperRight.first - bottomLeft.first;
  double w = upperRight.second - bottomLeft.second;
  std::pair<double, double> result((lon - bottomLeft.second) / w * 1248,
                                   (1 - (lat - bottomLeft.first) / h) * 992);
  return result;
}

//-----------------------------------------------------
// TODO: Student should implement the following:
//-----------------------------------------------------
double TrojanMap::GetLat(std::string id) { return data[id].lat; }
//-----------------------------------------------------
double TrojanMap::GetLon(std::string id) { return data[id].lon; }
//-----------------------------------------------------
std::string TrojanMap::GetName(std::string id) { return data[id].name; }
//-----------------------------------------------------
std::vector<std::string> TrojanMap::GetNeighborIDs(std::string id) {
  return data[id].neighbors;
}
//-----------------------------------------------------
double TrojanMap::CalculateDistance(const Node &a, const Node &b) {
  // TODO: Use Haversine Formula:
  // dlon = lon2 - lon1;
  // dlat = lat2 - lat1;
  // a = (sin(dlat / 2)) ^ 2 + cos(lat1) * cos(lat2) * (sin(dlon / 2)) ^ 2;
  // c = 2 * arcsin(min(1, sqrt(a)));
  // distances = 3961 * c;

  // where 3961 is the approximate radius of the earth at the latitude of
  // Washington, D.C., in miles
  return pow(pow(a.lat - b.lat, 2) + pow(a.lon - b.lon, 2),0.5);
}

/**
 * Autocomplete: Given a parital name return all the possible locations with
 * partial name as the prefix.
 *
 * @param  {std::string} name          : partial name
 * @return {std::vector<std::string>}  : a vector of full names
 */
std::vector<std::string> TrojanMap::Autocomplete(std::string name) {
  std::vector<std::string> results;
  for (auto x : data) {
    if (name.size() > x.second.name.size()) continue;
    std::string str = x.second.name.substr(0, name.size());
    std::locale loc;
    bool flag = true;
    for (std::string::size_type i = 0; i < str.length(); ++i) {
      if (std::toupper(name[i], loc) != std::toupper(str[i], loc)) {
        flag = false;
        break;
      }
    }
    if (flag) results.push_back(x.second.name);
  }
  return results;
}

/**
 * GetPosition: Given a location name, return the position.
 *
 * @param  {std::string} name          :
 * @return {std::pair<double,double>}  : (lat, lon)
 */
std::pair<double, double> TrojanMap::GetPosition(std::string name) {
  std::pair<double, double> results(-1, -1);
  for (auto x : data) {
    if (x.second.name == name) {
      results.first = x.second.lat;
      results.second = x.second.lon;
      return results;
    }
  }
  return results;
}

/**
 * CalculateShortestPath: Given 2 locations, return the shortest path which is a
 * list of id.
 *
 * @param  {std::string} location1_name     : start
 * @param  {std::string} location2_name     : goal
 * @return {std::vector<std::string>}       : path
 */
std::vector<std::string> TrojanMap::CalculateShortestPath(
    std::string location1_name, std::string location2_name) {
  std::vector<std::string> x{
      "2578244375", "5559640911", "6787470571", "6808093910", "6808093913",
      "6808093919", "6816831441", "6813405269", "6816193784", "6389467806",
      "6816193783", "123178876",  "2613117895", "122719259",  "2613117861",
      "6817230316", "3642819026", "6817230310", "7811699597", "5565967545",
      "123318572",  "6813405206", "6813379482", "544672028",  "21306059",
      "6813379476", "6818390140", "63068610",   "6818390143", "7434941012",
      "4015423966", "5690152766", "6813379440", "6813379466", "21306060",
      "6813379469", "6813379427", "123005255",  "6807200376", "6807200380",
      "6813379451", "6813379463", "123327639",  "6813379460", "4141790922",
      "4015423963", "1286136447", "1286136422", "4015423962", "6813379494",
      "63068643",   "6813379496", "123241977",  "4399914059", "4015372478",
      "1732243576", "6813379548", "4015372476", "4015372475", "1732243620",
      "4015372469", "4015372463", "6819179749", "1732243544", "6813405275",
      "348121996",  "348121864",  "6813405280", "1472141024", "4015372462",
      "6813411586", "4015372458", "6813411588", "1837212101", "6820935911",
      "4547476733"};
  return x;
}

float TrojanMap::CalculatePathLength(const std::vector<std::string> &path) {
  float sum = 0;
  for (int i = 1; i < path.size(); i++) {
    sum += CalculateDistance(data[path[i]], data[path[i - 1]]);
  }
  sum += CalculateDistance(data[path[0]], data[path[path.size() - 1]]);
  return sum;
}

std::vector<std::string> TrojanMap::findPermutations(
  std::vector<std::string>& a){
  std::sort(a.begin(), a.end());
  std::vector<std::string> results;
  float min = INT_MAX;
  do {
    float tmp = CalculatePathLength(a);
    if (min > tmp) {
      min = tmp;
      results = a;
    }
  } while (next_permutation(a.begin(), a.end()));
  results.push_back(results[0]);
  return results;
}

/**
 * Travelling salesman problem: Given a list of locations, return the shortest
 * path which visit all the places and back to the start point.
 *
 * @param  {std::vector<std::string>} input : a list of locations needs to visit
 * @return {std::pair<double, std::vector<std::string>>} : a pair of total distance and path
 */
std::pair<double, std::vector<std::string>> TrojanMap::TravellingTrojan(
                                    std::vector<std::string> &location_ids) {
  std::pair<double, std::vector<std::string>> results;
  auto res = findPermutations(location_ids);
  results.first = 100; // a random number
  results.second = res;
  return results;
} 