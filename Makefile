# Dempster-Shafer Library for Evidence-Theory
# Thilo Michael, Jeffrey Jedele
# 2012

lab_exercise : main.cpp dempstershafer.cpp
	g++ -o lab_exercise main.cpp dempstershafer.cpp

test_exam_1 : test_wbs_exam.cpp dempstershafer.cpp
	g++ -o test_exam_1 test_wbs_exam.cpp dempstershafer.cpp

all : lab_exercise test_exam_1

clean :
	rm -f lab_exercise test_exam_1
