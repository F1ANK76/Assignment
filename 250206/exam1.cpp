#include <iostream>
#include <unordered_map>
#include <map>
#include <vector>
#include <iomanip>
#include <algorithm>
using namespace std;

class Gradebook {
private:
    // 학생 ID -> (과목명 -> 점수) 맵
    map<int, map<string, int>> studentGrades;
    // 과목명 -> 점수 벡터 맵
    map<string, vector<int>> subjectScores;

public:
    // 학생 성적 추가
    void addGrade(int studentId, string subject, int score) {
        if (score < 0 || score > 100) {
            cout << "점수는 0 ~ 100 범위이어야 합니다." << endl;
            return;
        }

        // 학생의 성적 갱신
        studentGrades[studentId][subject] = score;
        // 과목별 점수 추가
        subjectScores[subject].push_back(score);
    }

    // 해당 학생의 전체 성적 조회
    void viewStudentGrades(int studentId) {
        if (studentGrades.find(studentId) == studentGrades.end()) {
            cout << "존재하지 않는 학생 ID입니다." << endl;
            return;
        }

        cout << "학생 ID " << studentId << "의 성적:" << endl;
        for (const auto& subject : studentGrades[studentId]) {
            cout << "- " << subject.first << ": " << subject.second << "점" << endl;
        }

        cout << endl;
    }

    // 전체 학생의 평균 점수 출력
    void printAverageScores() {
        cout << "전체 과목 평균 점수:" << endl;
        for (const auto& subject : subjectScores) {
            double sum = 0;
            for (int score : subject.second) {
                sum += score;
            }
            double average = sum / subject.second.size();

            // fixed << setprecision(2) 문법 이용하여 소수점 둘째자리까지 출력
            cout << "- " << subject.first << ": " << fixed << setprecision(2) << average << "점" << endl;
        }

        cout << endl;
    }

    // 해당 과목 최고 점수 학생 조회
    void findTopScorersForSubject(string subject) {
        if (subjectScores.find(subject) == subjectScores.end()) {
            cout << "존재하지 않는 과목입니다." << endl;
            return;
        }

        int maxScore = *max_element(subjectScores[subject].begin(), subjectScores[subject].end());
        vector<int> topScorers;

        // 최고 점수를 받은 학생을 찾아 리스트에 추가
        for (const auto& student : studentGrades) {
            // 해당 번호의 학생이 가진 map<string, int> 과목 정보에서 해당 과목이 있는지, 있다면 해당 점수가 최고점인지 판단
            if (student.second.find(subject) != student.second.end() && student.second.at(subject) == maxScore) {
                topScorers.push_back(student.first);
            }
        }

        sort(topScorers.begin(), topScorers.end()); // 동점자 대비 학생 ID 오름차순 정렬
        cout << subject << " 최고 점수: " << maxScore << "점" << endl;
        cout << "- 학생 ID: ";
        for (int i = 0; i < topScorers.size(); i++) {
            if (i != 0) cout << ", ";
            cout << topScorers[i];
        }

        cout << endl << endl;
    }
};

int main() {
    Gradebook gradebook;

    // 성적 추가
    gradebook.addGrade(1, "C++", 100);
    gradebook.addGrade(1, "알고리즘", 85);
    gradebook.addGrade(2, "C++", 100);
    gradebook.addGrade(2, "알고리즘", 100);
    gradebook.addGrade(3, "C++", 95);
    gradebook.addGrade(3, "알고리즘", 95);

    // 학생 성적 조회
    gradebook.viewStudentGrades(1);
    gradebook.viewStudentGrades(2);
    gradebook.viewStudentGrades(3);

    // 전체 학생 평균 점수 출력
    gradebook.printAverageScores();

    // 과목별 최고 점수 학생 조회
    gradebook.findTopScorersForSubject("C++");
    gradebook.findTopScorersForSubject("알고리즘");

    return 0;
}

