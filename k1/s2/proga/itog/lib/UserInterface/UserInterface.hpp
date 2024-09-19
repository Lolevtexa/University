#include "../List/List.hpp"
#include "../String/String.hpp"

int inputNumber(int, int);

Number inputNumber();
Number inputNumber(List &);

void inputNumber(List &, Number &, Number &);


void saveNumberInList(List &, const Number &);


void saveListInFile(List &);
void loadListFromFile(List &);


void printList(List &);


void additionIntoAColumn(const Number &, const Number &, List &);
void subtractionIntoAColumn(const Number &, const Number &, List &);
void multiplicationIntoAColumn(const Number &, const Number &, List &);
void divisionIntoAColumn(const Number &, const Number &, List &);
void remainderIntoAColumn(const Number &, const Number &, List &);
