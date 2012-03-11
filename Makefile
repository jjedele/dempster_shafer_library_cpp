# Dempster-Shafer Library for Evidence-Theory
# Thilo Michael, Jeffrey Jedele
# 2012

lab_exercise : main.cpp dempstershafer.cpp csvreader.cpp learningclassificator.cpp
	g++ -o lab_exercise main.cpp dempstershafer.cpp csvreader.cpp learningclassificator.cpp

tests : test_dempstershafer.cpp test_csvreader.cpp test_learningclassificator.cpp dempstershafer.cpp csvreader.cpp learningclassificator.cpp
	g++ -o test_dempstershafer test_dempstershafer.cpp dempstershafer.cpp
	g++ -g -o test_csvreader test_csvreader.cpp csvreader.cpp
	g++ -o test_learningclassificator test_learningclassificator.cpp learningclassificator.cpp

all : lab_exercise tests

clean :
	rm -f lab_exercise test_dempstershafer test_csvreader test_learningclassificator
