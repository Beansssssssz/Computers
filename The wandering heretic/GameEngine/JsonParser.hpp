#pragma once

#include <SDL.h>
#include <nlohmann/json.hpp>
#include <iostream>

using json = nlohmann::json;

///returns the name of the inputed var
#define GETVARNAME(x) #x

namespace jsonParser {

  /// <summary>
/// Cleans the file then writes to it the
/// param data
/// </summary>
/// <param name="path"> the file path</param>
/// <param name="data">a json object</param>
/// <returns></returns>
  inline int WriteToFile(const char* path, json data) {
    std::ofstream file(path);
    if (!file.is_open()) {
      std::cerr << "Error opening JSON file.\n";
      return 1;
    }

    file << std::setw(4) << data << std::endl;
    file.close();

    std::cout << "JSON file updated successfully.\n";

    return 0;
  }

  /// <summary>
  /// deletes the given element from the json param
  /// </summary>
  /// <param name="data">the json data to delete element from</param>
  /// <param name="element">the json element name</param>
  /// <returns> 0 if no erros occured other wise returns 1
  /// error code is found in stderr </returns>
  inline int DeleteElement(json* data, const char* element) {
    if (data->find(element) == data->end()) {
      std::cerr << "No element was found.\n";
      return 1;
    }
    data->erase(element);
    return 0;
  }

  /// <summary>
  /// turns a SDL_REct into a json
  /// the json param exmple: data["rect.x"] / data["rect.w"] 
  /// </summary>
  /// <param name="rect"></param>
  /// <returns></returns>
  inline json FromRectToJson(SDL_Rect rect) {
    json data;
    data[GETVARNAME(rect.h)] = rect.h;
    data[GETVARNAME(rect.w)] = rect.w;
    data[GETVARNAME(rect.y)] = rect.y;
    data[GETVARNAME(rect.x)] = rect.x;

    return data;
  };

  /// <summary>
  /// turns a json into an SDL_Rect struct
  /// exmple of json: data["rect.x"] / data["rect.w"]
  /// otherwise will not work
  /// </summary>
  /// <param name="data"></param>
  /// <returns></returns>
  inline SDL_Rect FromJsonToRect(json data) {
    SDL_Rect rect;
    rect.x = data[GETVARNAME(rect.x)];
    rect.y = data[GETVARNAME(rect.y)];
    rect.w = data[GETVARNAME(rect.w)];
    rect.h = data[GETVARNAME(rect.h)];

    return rect;
  }

  /// <summary>
  /// creates a json data from a normal sqaure class data
  /// </summary>
  /// <param name="dst"></param>
  /// <param name="src"></param>
  /// <param name="path"></param>
  /// <returns></returns>
  inline json CreateJsonFromData(SDL_Rect dst, SDL_Rect src, const char* path) {
    json data;
    data["src"] = FromRectToJson(src);
    data["dst"] = FromRectToJson(dst);
    data["path"] = path;

    return data;
  }
}

//no hagging macros
//only leads to bad code design
#undef GETVARNAME
