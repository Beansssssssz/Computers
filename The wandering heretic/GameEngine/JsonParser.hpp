#pragma once

#include <SDL.h>
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

#include "Square.hpp"
#include "Enemy.hpp"

using json = nlohmann::json;

///returns the name of the inputed var
#define GETVARNAME(x) #x

namespace jsonParser {

  /// <summary>
  /// Cleans the file then writes to it the
  /// param data
  /// TODO
  /// there is overflow?
  /// dont know
  /// doesnt really work
  /// </summary>
  /// <param name="path"> the file path</param>
  /// <param name="data">a json object</param>
  /// <returns></returns>
  inline void WriteToFile(const char* path, json* data) {
    std::ofstream file(path);
    if (!file.is_open()) {
      std::cerr << "Error opening JSON file.\n";
      return;
    }


    int width = (*data)["width"];
    int height = (*data)["height"];
    json arr = (*data)["data"];
    std::cout << arr << std::endl;

    // Write the JSON data to a file
    try {
      file << "{\n";

      long long loc = 0;
      file << "    \"data\": [\n    ";
      for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
          loc = (long long)x * (long long)y;

          file << arr[loc];
          if (x < (long long)width - 1)
            file << ", ";
        }

        if (y < (long long)height - 1)
          file << ",\n    ";
      }
      file << "],\n";

      file << "    \"width\": " << width << ",\n";
      file << "    \"height\": " << height << "\n";
      file << "}";
      file.close();

      std::cerr << "JSON file updated successfully.\n";
    }
    catch (const std::exception& e) {
      std::cerr << "Error writing to JSON file: " << e.what() << "\n";
    }

    file.close();
  }

  inline json ReadFromFile(const char* path) {
    std::ifstream file(path);
    if (!file.is_open()) {
      std::cerr << "Error opening JSON file.\n";
      return 1;
    }

    json data;
    file >> data;
    std::cout << path << std::endl;;


    file.close();
    return data;
  }

  /// <summary>
  /// deletes the given element from the json param
  /// </summary>
  /// <param name="data">the json data to delete element from</param>
  /// <param name="element">the json element name</param>
  /// <returns> 0 if no errors occured other wise returns 1
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
  /// turns a SDL_Rect into a json
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
  inline json CreateJsonFromData(SDL_Rect dst, std::string path) {
    json data;
    data["dst"] = FromRectToJson(dst);
    data["path"] = path;

    return data;
  }

  /// <summary>
  /// froms a json param it create a button obj
  /// </summary>
  /// <param name="data"></param>
  /// <returns></returns>
  inline Square* FromJsonToSquare(json data, bool destoryTex = true) {
    SDL_Rect dst = FromJsonToRect(data["dst"]),
      src = { 0,0,64,64 };//a fixed size and loc

    std::string path = data["path"];
    if (path == "")//failsafe
      path = "Assets\\Blocks\\image_0.png";


    return new Square(path.c_str(), src, dst, destoryTex);
  };

  /// <summary>
  /// froms a Button param it create a json
  /// </summary>
  /// <param name="btn"></param>
  /// <returns></returns>
  inline json FromSquareToJson(Square* sqr) {
    json data;

    return CreateJsonFromData(*sqr->GetDstRect(), sqr->GetPath());
  };

  /// <summary>
  /// a function that converts the vector into a 1d int array with a
  /// fixed width and height for the block
  /// </summary>
  /// <typeparam name="T">(is a pointer type) an Square object or an object with the
  /// GetDstRect function and type</typeparam>
  /// <param name="vec"></param>
  /// <returns>a json type object</returns>
  template<typename T>
  inline json FromVectorToJson(std::vector<T> vec) {
    json data;

    //finding the width and size of the 1d array
    int width = 0;
    int height = 0;

    for (T obj : vec) {
      SDL_Rect rect = *obj->GetDstRect();
      rect.y /= 64;
      rect.x /= 64;

      if (rect.y > height)
        height = rect.y;

      if (rect.x > width)
        width = rect.x;
    }

    /*
      the actuall width and height needs to be bigger in 1
      because an array with only location 0 has a size of 1
    */
    width++;
    height++;

    //creating the 2d array
    std::vector<int> arr(height * width); //the vector witch the correct size
    std::string path; //the path of the current block
    SDL_Rect rect; //the rect of the current block

    long long loc; //the current loc in the array
    for (int i = 0; i < height; i++)
      for (int j = 0; j < width; j++)
      {
        loc = i * j;
        if ((long long)vec.size() <= loc)
          continue;

        rect = *vec[loc]->GetDstRect();
        path = vec[loc]->GetPath();

        int x = rect.x / 64;
        int y = rect.y / 64;
        loc = x * y;

        if (path == "")
          arr[loc] = 1;
        else
          arr[loc] = (int)(path[path.size() - 5] - '0');
      }


    data["data"] = arr;
    data["width"] = width;
    data["height"] = height;

    return data;
  }

  /// <summary>
  /// from the json data it returns an array of Entity
  /// also an out variable of the enemy Vector
  /// and an out Finishline
  /// </summary>
  /// <typeparam name="T">a square type</typeparam>
  /// <param name="data">a json data</param>
  /// <returns>a vector with all the objects</returns>
  template<typename T>
  inline std::vector<T*> FromJsonToVector(json data, std::vector<Enemy*>* outEnemyVec, SDL_Rect* OutFinishLine) {
    SDL_Rect src = { 0, 0, 64, 64 };
    SDL_Rect dst = { 0, 0, 64, 64 };

    std::vector<int> arr = data["data"];
    int width = data["width"];
    int height = data["height"];

    std::string path = "Assets/Blocks/image_0.png";
    SDL_Texture* tex;

    RenderWindow* win = RenderWindow::GetRenderWindowInstance();

    std::vector<T*> vec;
    for (int i = 0; i < height; i++)
      for (int j = 0; j < width; j++)
      {
        int loc = i * width + j;
        if (arr[loc] == 0)
          continue;
         
        dst.y = i * 64;
        dst.x = j * 64;

        /* enemy */
        if (arr[loc] == 9) {
          SDL_Rect enemySrc = SDL_Rect{ 0, 0, 50, 54 };
          SDL_Rect enemyDst = SDL_Rect{ dst.x, dst.y, 53 * 2, 55 * 2 };

          GIF* enemyGifIdle = new GIF("Assets\\Character\\Bringer_Of_Death\\Walk\\bringer_",
            8, enemySrc, enemyDst, 150);

          GIF* enemyGifAttack = new GIF("Assets\\Character\\Bringer_Of_Death\\Attack\\bringer_",
            10, enemySrc, enemyDst, 120);

          outEnemyVec->push_back(new Enemy({ enemyGifIdle, enemyGifAttack }, enemySrc, enemyDst));
          continue;
        }

        /* finish line */
        if (arr[loc] == 8) {
          
          continue;
        }

        //if its a single digit number u can cahnge it into a char by adding a '0'
        path[path.size() - 5] = (char)(arr[loc] + '0'); 

        tex = win->LoadTexture(path.c_str());
        vec.push_back(new T(tex, src, dst));
      }

    return vec;
  }
}



#undef GETVARNAME
