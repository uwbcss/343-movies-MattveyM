#ifndef FACTORY_H
#define FACTORY_H

#include <map>
#include <string>
using namespace std;

class Movie;
class Command;

class MovieFactory {
public:
  static MovieFactory &getInstance();
  void registerMovie(char type, Movie *prototype);
  Movie *createMovie(char type) const;

private:
  map<char, Movie *> prototypes;
  MovieFactory() = default;
  ~MovieFactory();
};

class CommandFactory {
public:
  static CommandFactory &getInstance();
  void registerCommand(char type, Command *prototype);
  Command *createCommand(char type) const;

private:
  map<char, Command *> prototypes;
  CommandFactory() = default;
  ~CommandFactory();
};

#endif
