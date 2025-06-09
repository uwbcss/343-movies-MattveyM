#ifndef MOVIE_H
#define MOVIE_H

#include <iostream>
#include <string>
using namespace std;

class Movie {
public:
  Movie(char type, int stock, const string &director, const string &title);
  virtual ~Movie() = default;

  virtual bool operator<(const Movie &other) const = 0;
  virtual bool operator==(const Movie &other) const = 0;
  virtual string toString() const = 0;
  virtual Movie *create() const = 0;
  virtual bool setData(const string &line) = 0;
  virtual bool matchesSearchCriteria(const string &criteria) const = 0;

  char getType() const { return type; }
  int getStock() const { return stock; }
  void setStock(int newStock) { stock = newStock; }
  string getDirector() const { return director; }
  string getTitle() const { return title; }

  bool borrowMovie();
  bool returnMovie();

protected:
  char type;
  int stock;
  string director;
  string title;
};

class Comedy : public Movie {
public:
  Comedy();
  Comedy(int stock, const string &director, const string &title, int year);

  bool operator<(const Movie &other) const override;
  bool operator==(const Movie &other) const override;
  string toString() const override;
  Movie *create() const override;
  bool setData(const string &line) override;
  bool matchesSearchCriteria(const string &criteria) const override;

  int getYear() const { return year; }

private:
  int year;
};

class Drama : public Movie {
public:
  Drama();
  Drama(int stock, const string &director, const string &title, int year);

  bool operator<(const Movie &other) const override;
  bool operator==(const Movie &other) const override;
  string toString() const override;
  Movie *create() const override;
  bool setData(const string &line) override;
  bool matchesSearchCriteria(const string &criteria) const override;

  int getYear() const { return year; }

private:
  int year;
};

class Classic : public Movie {
public:
  Classic();
  Classic(int stock, const string &director, const string &title,
          const string &actor, int month, int year);

  bool operator<(const Movie &other) const override;
  bool operator==(const Movie &other) const override;
  string toString() const override;
  Movie *create() const override;
  bool setData(const string &line) override;
  bool matchesSearchCriteria(const string &criteria) const override;

  string getActor() const { return actor; }
  int getMonth() const { return month; }
  int getYear() const { return year; }

private:
  string actor;
  int month;
  int year;
};

#endif