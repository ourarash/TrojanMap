#include <iostream>
#include "src/lib/trojanmap.h"

int main() {

  TrojanMap x;
  x.CreateGraphFromCSVFile();
  x.PrintMenu();

  // std::cout << x.GetName("4547476733") << " " << x.GetLat("4547476733") << " " << x.GetLon("4547476733") << std::endl;

  // for (auto y : x.GetNeighbors("4547476733"))
  //   std::cout << y << std::endl;

  // x.PlotPoint("4547476733");
  
  // std::string input;
  // while (std::cin >> input){
  //   auto out = x.Autocomplete(input);
  //   for(auto name: out){
  //     std::cout << name << std::endl;
  //   }
  //   std::cout << "----------------------------" << std::endl;
  // }
  
  // std::string image_path = samples::findFile("src/main/input.jpg");
  // Mat img = imread(image_path, IMREAD_COLOR);
  // imshow("Name", img);
  // waitKey(0);
  return 0;
}