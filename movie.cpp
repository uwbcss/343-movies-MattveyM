#include "movie.h"
#include <algorithm>
#include <sstream>

Movie::Movie(char type, int stock, const string &director, const string &title)
    : type(type), stock(stock), director(director), title(title) {}

bool Movie::borrowMovie() {
  if (stock > 0) {
    stock--;
    return true;
  }
  return false;
}

bool Movie::returnMovie() {
  stock++;
  return true;
}

// Comedy Implementation
Comedy::Comedy() : Movie('F', 0, "", ""), year(0) {}

Comedy::Comedy(int stock, const string &director, const string &title, int year)
    : Movie('F', stock, director, title), year(year) {}

bool Comedy::operator<(const Movie &other) const {
  const Comedy *otherComedy = dynamic_cast<const Comedy *>(&other);
  if (otherComedy == nullptr) {
    return false;
  }

  if (title != otherComedy->title) {
    return title < otherComedy->title;
  }
  return year < otherComedy->year;
}

bool Comedy::operator==(const Movie &other) const {
  const Comedy *otherComedy = dynamic_cast<const Comedy *>(&other);
  if (otherComedy == nullptr) {
    return false;
  }

  return title == otherComedy->title && year == otherComedy->year;
}

string Comedy::toString() const {
  return title + ", " + to_string(year) + ", " + director + " (" +
         to_string(stock) + ") - Comedy";
}

Movie *Comedy::create() const { return new Comedy(); }

bool Comedy::setData(const string &line) {
  stringstream ss(line);
  string token;

  // Skip type and get stock
  getline(ss, token, ',');
  getline(ss, token, ',');
  stock = stoi(token);

  // Get director
  getline(ss, director, ',');
  director.erase(0, director.find_first_not_of(" "));
  director.erase(director.find_last_not_of(" ") + 1);

  // Get title
  getline(ss, title, ',');
  title.erase(0, title.find_first_not_of(" "));
  title.erase(title.find_last_not_of(" ") + 1);

  // Get year
  getline(ss, token);
  token.erase(0, token.find_first_not_of(" "));
  year = stoi(token);

  return true;
}

bool Comedy::matchesSearchCriteria(const string &criteria) const {
  stringstream ss(criteria);
  string searchTitle;
  string yearStr;

  getline(ss, searchTitle, ',');
  searchTitle.erase(0, searchTitle.find_first_not_of(" "));
  searchTitle.erase(searchTitle.find_last_not_of(" ") + 1);

  getline(ss, yearStr);
  yearStr.erase(0, yearStr.find_first_not_of(" "));

  return title == searchTitle && year == stoi(yearStr);
}

// Drama Implementation
Drama::Drama() : Movie('D', 0, "", ""), year(0) {}

Drama::Drama(int stock, const string &director, const string &title, int year)
    : Movie('D', stock, director, title), year(year) {}

bool Drama::operator<(const Movie &other) const {
  const Drama *otherDrama = dynamic_cast<const Drama *>(&other);
  if (otherDrama == nullptr) {
    return false;
  }

  if (director != otherDrama->director) {
    return director < otherDrama->director;
  }
  return title < otherDrama->title;
}

bool Drama::operator==(const Movie &other) const {
  const Drama *otherDrama = dynamic_cast<const Drama *>(&other);
  if (otherDrama == nullptr) {
    return false;
  }

  return director == otherDrama->director && title == otherDrama->title;
}

string Drama::toString() const {
  return director + ", " + title + ", " + to_string(year) + " (" +
         to_string(stock) + ") - Drama";
}

Movie *Drama::create() const { return new Drama(); }

bool Drama::setData(const string &line) {
  stringstream ss(line);
  string token;

  // Skip type and get stock
  getline(ss, token, ',');
  getline(ss, token, ',');
  stock = stoi(token);

  // Get director
  getline(ss, director, ',');
  director.erase(0, director.find_first_not_of(" "));
  director.erase(director.find_last_not_of(" ") + 1);

  // Get title
  getline(ss, title, ',');
  title.erase(0, title.find_first_not_of(" "));
  title.erase(title.find_last_not_of(" ") + 1);

  // Get year
  getline(ss, token);
  token.erase(0, token.find_first_not_of(" "));
  year = stoi(token);

  return true;
}

bool Drama::matchesSearchCriteria(const string &criteria) const {
  stringstream ss(criteria);
  string searchDirector;
  string searchTitle;

  getline(ss, searchDirector, ',');
  searchDirector.erase(0, searchDirector.find_first_not_of(" "));
  searchDirector.erase(searchDirector.find_last_not_of(" ") + 1);

  getline(ss, searchTitle);
  searchTitle.erase(0, searchTitle.find_first_not_of(" "));
  searchTitle.erase(searchTitle.find_last_not_of(" ") + 1);

  return director == searchDirector && title == searchTitle;
}

// Classic Implementation
Classic::Classic() : Movie('C', 0, "", ""), month(0), year(0) {}

Classic::Classic(int stock, const string &director, const string &title,
                 const string &actor, int month, int year)
    : Movie('C', stock, director, title), actor(actor), month(month),
      year(year) {}

bool Classic::operator<(const Movie &other) const {
  const Classic *otherClassic = dynamic_cast<const Classic *>(&other);
  if (otherClassic == nullptr) {
    return false;
  }

  if (year != otherClassic->year) {
    return year < otherClassic->year;
  }
  if (month != otherClassic->month) {
    return month < otherClassic->month;
  }
  return actor < otherClassic->actor;
}

bool Classic::operator==(const Movie &other) const {
  const Classic *otherClassic = dynamic_cast<const Classic *>(&other);
  if (otherClassic == nullptr) {
    return false;
  }

  return year == otherClassic->year && month == otherClassic->month &&
         actor == otherClassic->actor;
}

string Classic::toString() const {
  return to_string(year) + " " + to_string(month) + ", " + actor + ", " +
         director + ", " + title + " (" + to_string(stock) + ") - Classics";
}

Movie *Classic::create() const { return new Classic(); }

bool Classic::setData(const string &line) {
  stringstream ss(line);
  string token;

  // Skip type and get stock
  getline(ss, token, ',');
  getline(ss, token, ',');
  stock = stoi(token);

  // Get director
  getline(ss, director, ',');
  director.erase(0, director.find_first_not_of(" "));
  director.erase(director.find_last_not_of(" ") + 1);

  // Get title
  getline(ss, title, ',');
  title.erase(0, title.find_first_not_of(" "));
  title.erase(title.find_last_not_of(" ") + 1);

  // Get remaining part (actor month year)
  string remaining;
  getline(ss, remaining);
  remaining.erase(0, remaining.find_first_not_of(" "));

  // Parse actor month year
  stringstream remainingStream(remaining);
  string firstName;
  string lastName;
  string monthStr;
  string yearStr;
  remainingStream >> firstName >> lastName >> monthStr >> yearStr;

  actor = firstName + " " + lastName;
  month = stoi(monthStr);
  year = stoi(yearStr);

  return true;
}

bool Classic::matchesSearchCriteria(const string &criteria) const {
  stringstream ss(criteria);
  string monthStr;
  string yearStr;
  string searchActor;

  ss >> monthStr >> yearStr;
  getline(ss, searchActor);
  searchActor.erase(0, searchActor.find_first_not_of(" "));

  return month == stoi(monthStr) && year == stoi(yearStr) &&
         actor == searchActor;
}
