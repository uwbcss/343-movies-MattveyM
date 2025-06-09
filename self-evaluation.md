# Self-Evaluation

## Name(s): 

Out of 25 points. Use output.txt created using 
`./create-output.sh > output.txt 2>&1` for guidance.

Complete all questions with "Q:"

Q: Does the program compile and run to completion: Yes

- If the program does not compile or gives a segmentation error when run, 
the maximum possible grade is 50%. No need to continue with the rest of self-evaluation

Q: All public functions have been implemented: ENTER_NUMBER 25

- -2 for each functionality not implemented

For each command, state Full, Partial or None to indicate 
if it has been fully, partially or not implemented at all.
Explain any partial implementations.

Inventory: TODO(student) Full
History: TODO(student) Full
Borrow: TODO(student) Full
Return: TODO(student) Full


Q: -1 for each compilation warning, min -3: ENTER_NUMBER 0

- Check under *1. Compiles without warnings*
- If the warning message is addressed in README.md, including how the programmer tried to address it, no deductions

Q: -1 for each clang-tidy warning, min -3: ENTER_NUMBER 0

- Check under *3. clang-tidy warnings*
- If the warning message is addressed in README.md, including how the programmer tried to address it, no deductions

Q: -1 for each clang-format warning, min -3: ENTER_NUMBER 0

- Check under *4. clang-format does not find any formatting issues*


Q: -2 for any detected memory leak: ENTER_NUMBER 0

- Check under *5. No memory leaks using g++*
- Check under *6. No memory leaks using valgrind*

Q: Do the tests sufficiently test the code: ENTER_NUMBER 0

- -1 for each large block of code not executed
- -2 for each function that is never called when testing
- Check under *7. Tests have full code coverage* paying attention to *The lines below were never executed*

Q: Are all functions in .h and .cpp file documents (min -3): ENTER_NUMBER 0

- -1 for each function not documented

## Location of error message or functionality

State the file and function where the information can be found

invalid command code: TODO(student)
command.cpp in CommandFactory::createCommand() and store.cpp in processCommands()

invalid movie type: TODO(student)
movie.cpp in MovieFactory::createMovie() and store.cpp in loadMovies()

invalid customer ID: TODO(student)
store.cpp in borrowMovie() and returnMovie() functions
 
invalid movie: TODO(student)
store.cpp in findMovie() function

factory classes: TODO(student)
factory.h and factory.cpp - MovieFactory and CommandFactory classes

hashtable: TODO(student) (explain what the hashtable is used for)
 hashtable.h - Custom hash table template used for O(1) customer lookup by ID

container used for comedy movies: TODO(student)
store.h - std::set<Movie*, MovieCompare> with custom comparator

function for sorting comedy movies: TODO(student)
movie.cpp - Comedy::operator< function (sorts by title, then year)

function where comedy movies are sorted: TODO(student)
store.cpp - movies set automatically maintains sorted order

functions called when retrieving a comedy movie based on title and year: TODO(student)
store.cpp findMovie() and movie.cpp Comedy::matchesSearchCriteria()

functions called for retrieving and printing customer history: TODO(student)
store.cpp displayCustomerHistory() and customer.cpp displayHistory()

container used for customer history: TODO(student)
customer.h - std::vector<Transaction*> history

functions called when borrowing a movie: TODO(student)
store.cpp borrowMovie(), transaction.cpp BorrowTransaction::execute(), movie.cpp borrowMovie()

explain borrowing a movie that does not exist: TODO(student)
store.cpp findMovie() returns nullptr, error message printed in borrowMovie()

explain borrowing a movie that has 0 stock: TODO(student)
transaction.cpp BorrowTransaction::execute() checks stock, prints out-of-stock message

explain returning a movie that customer has not checked out: TODO(student)
System allows any valid return - no explicit tracking of what customer borrowed

any static_cast or dynamic_cast used: TODO(student)
movie.cpp in operator< and operator== methods for downcasting between movie types

## Bonus +5

Are there multiple files, of the form runit-without-XXX, where the same set of files will compile and run excluding some of the commands or genres? TODO(student)
No




Q: Total points: ADD_ALL_POINTS (max 25 (+ 5 Bonus)) 25