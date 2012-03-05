# Dempster-Shafer Library for Evidence-Theory
# Thilo Michael, Jeffrey Jedele
# 2012

lab_exercise : main.cpp dempstershafer.cpp
	g++ -o lab_exercise main.cpp dempstershafer.cpp

test_exam_1 : test_wbs_exam.cpp dempstershafer.cpp
	g++ -o test_exam_1 test_wbs_exam.cpp dempstershafer.cpp

csv_test : csvtest.cpp csvreader.cpp
	g++ -g -o csv_test csvtest.cpp csvreader.cpp

all : lab_exercise test_exam_1 csv_test

clean :
	rm -f lab_exercise test_exam_1 csv_test
