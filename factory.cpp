#include "factory.h"
#include "command.h"
#include "movie.h"

// MovieFactory
MovieFactory &MovieFactory::getInstance() {
  static MovieFactory instance;
  return instance;
}

MovieFactory::~MovieFactory() {
  for (auto &pair : prototypes) {
    delete pair.second;
  }
}

void MovieFactory::registerMovie(char type, Movie *prototype) {
  prototypes[type] = prototype;
}

Movie *MovieFactory::createMovie(char type) const {
  auto it = prototypes.find(type);
  if (it != prototypes.end()) {
    return it->second->create();
  }
  return nullptr;
}

// CommandFactory
CommandFactory &CommandFactory::getInstance() {
  static CommandFactory instance;
  return instance;
}

CommandFactory::~CommandFactory() {
  for (auto &pair : prototypes) {
    delete pair.second;
  }
}

void CommandFactory::registerCommand(char type, Command *prototype) {
  prototypes[type] = prototype;
}

Command *CommandFactory::createCommand(char type) const {
  auto it = prototypes.find(type);
  if (it != prototypes.end()) {
    return it->second->create();
  }
  return nullptr;
}