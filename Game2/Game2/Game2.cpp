#include <iostream>
#include <cstdlib>

using namespace std;

enum enQuestionLevels{ Easy = 1, Medium = 2, Hard = 3, MixLevels = 4 };
enum enOperationTypes{ Addition = 1, Subtraction = 2, Multiplication = 3, Division = 4, MixOperations = 5 };

string QuestionLevelText(enQuestionLevels Level) {

	switch (Level)
	{
	case Easy: return "Easy";
		break;
	case Medium: return "Medium";
		break;
	case Hard: return "Hard";
		break;
	case MixLevels: return "Mix Levels";
		break;
	}

}

string OperationSymbol(enOperationTypes Type) {

	switch (Type)
	{
	case Addition: return "+";
		break;
	case Subtraction: return "-";
		break;
	case Multiplication: return "*";
		break;
	case Division: return "/";
		break;
	case MixOperations: return "Mix Operations";
		break;
	}

}

int ReadNumberOfQuestions() {

	int Number = 0;

	do {

		cout << "How many question do you want : 1 - 100 ? ";
		cin >> Number;

	} while (Number < 1 || Number > 100);

	return Number;

}

int GetRandomNumber(int From, int To) {

	int RandomNum = rand() % (To - From + 1) + From;

	return RandomNum;

}

enQuestionLevels ReadQuestionLevel() {
	
	int Level = 0;

	do {

		cout << "Whice question level do you want : [1]:Easy, [2]:Medium, [3]:Hard, [4]Mix Levels ? ";
		cin >> Level;

	} while (Level < 1 || Level > 4);

	return (enQuestionLevels)Level;

}

enOperationTypes ReadOperationType() {

	int Type = 0;

	do {

		cout << "Whice operation Type do you want : [1]:Addition, [2]:Subtraction, [3]:Multiplication, [4]:Division, [5]Mix Operations ? ";
		cin >> Type;

	} while (Type < 1 || Type > 5);

	return (enOperationTypes)Type;

}

enQuestionLevels GetMixedLevel() {
	
	return (enQuestionLevels) GetRandomNumber(1, 3);

}

enOperationTypes GetMixedType() {

	return (enOperationTypes) GetRandomNumber(1, 4);

}

struct stQuestion {

	int FirstNumber = 0;
	int SecondNumber = 0;
	enQuestionLevels QuestionLevel;
	enOperationTypes OperationType;
	int Answer = 0;
	int QuestionAnswer = 0;
	bool AnswerResult = false;

};

struct stExam {

	stQuestion Questions[100];
	int NumberOfQuestions = 0;
	enQuestionLevels QuestionLevel;
	enOperationTypes OperationType;
	int NumberOfRightAnsewrs = 0;
	int NumberOfWrongAnswers = 0;
	bool ExamResult = false;

};

int SimpleCalculater(int FirstNumber, int SecondNumber, enOperationTypes Type) {

	switch (Type)
	{
	
	case Addition: return FirstNumber + SecondNumber;
		break;
	
	case Subtraction: return FirstNumber - SecondNumber;
		break;
	
	case Multiplication: return FirstNumber * SecondNumber;
		break;
	
	case Division: return FirstNumber / SecondNumber;
		break;

	default: return FirstNumber + SecondNumber;
		break;

	}
}

stQuestion GenerateQuestion(enQuestionLevels Level, enOperationTypes Type) {

	stQuestion Question;

	if (Level == enQuestionLevels::MixLevels) {
		Level = GetMixedLevel();
	}

	if (Type == enOperationTypes::MixOperations) {
		Type = GetMixedType();
	}

	Question.OperationType = Type;

	switch (Level)
	{

	case Easy:

		Question.FirstNumber = GetRandomNumber(1, 10);
		Question.SecondNumber = GetRandomNumber(1, 10);

		Question.QuestionAnswer = SimpleCalculater(Question.FirstNumber, Question.SecondNumber, Question.OperationType);
		Question.QuestionLevel = Level;

		return Question;

		break;

	case Medium:

		Question.FirstNumber = GetRandomNumber(10, 50);
		Question.SecondNumber = GetRandomNumber(10, 50);

		Question.QuestionAnswer = SimpleCalculater(Question.FirstNumber, Question.SecondNumber, Question.OperationType);
		Question.QuestionLevel = Level;

		return Question;

		break;

	case Hard:
		
		Question.FirstNumber = GetRandomNumber(50, 100);
		Question.SecondNumber = GetRandomNumber(50, 100);

		Question.QuestionAnswer = SimpleCalculater(Question.FirstNumber, Question.SecondNumber, Question.OperationType);
		Question.QuestionLevel = Level;

		return Question;

		break;

	}
}

void GenerateExamQuestions(stExam &Exam) {

	for (int Question = 0; Question < Exam.NumberOfQuestions; Question++) {

		Exam.Questions[Question] = GenerateQuestion(Exam.QuestionLevel, Exam.OperationType);

	}
}

int ReadQustionAnswer() {
	
	int Answer = 0;
	
	cin >> Answer;

	return Answer;

}

void PrintQuestion(stExam Exam, int QuestionNumber) {

	cout << "Question[" << QuestionNumber + 1 << " / " << Exam.NumberOfQuestions << "]\n\n";
	cout << Exam.Questions[QuestionNumber].FirstNumber << "\n";
	cout << Exam.Questions[QuestionNumber].SecondNumber << " ";
	cout << OperationSymbol(Exam.Questions[QuestionNumber].OperationType) << "\n";
	cout << "____________\n";

}

void SetScreenColor(bool Answer) {

	if (Answer) {
		system("color 2F");
	}
	else {
		system("color 4F");
		cout << "\a";
	}

}

void CorrectQuestionAnswer(stExam &Exam, int QuestionNumber) {

	if (Exam.Questions[QuestionNumber].Answer != Exam.Questions[QuestionNumber].QuestionAnswer) {
		
		Exam.NumberOfWrongAnswers++;
		Exam.Questions[QuestionNumber].AnswerResult = false;
		cout << "\nWrong Answer :-(\n";
		cout << "The right answer is ";
		cout << Exam.Questions[QuestionNumber].QuestionAnswer;
		cout << "\n";


	}
	else {

		Exam.NumberOfRightAnsewrs++;
		Exam.Questions[QuestionNumber].AnswerResult = true;
		cout << "\nRight Answer :-)\n";
		
	}

	cout << endl;
	
	SetScreenColor(Exam.Questions[QuestionNumber].AnswerResult);
}

void AskQuestionAndCorrectIt(stExam &Exam) {

	for (int Question = 0; Question < Exam.NumberOfQuestions; Question++) {
		
		PrintQuestion(Exam, Question);
		Exam.Questions[Question].Answer = ReadQustionAnswer();
		CorrectQuestionAnswer(Exam, Question);
	}

	Exam.ExamResult = (Exam.NumberOfRightAnsewrs >= Exam.NumberOfWrongAnswers);

}

string PrintExamResult(bool Result) {

	if (Result) 
		return "PASS :-)";
	
	else 
		return "FAIL :-(";


} 

void PrintFinalResult(stExam Exam) {

	cout << "____________________________\n\n";
	cout << "The final result is " << PrintExamResult(Exam.ExamResult) << "\n";
	cout << "____________________________\n\n";

	cout << "Number of questions : " << Exam.NumberOfQuestions << "\n";
	cout << "Question level : " << QuestionLevelText(Exam.QuestionLevel) << "\n";
	cout << "Operation type : " << OperationSymbol(Exam.OperationType) << "\n";
	cout << "Number of right answers : " << Exam.NumberOfRightAnsewrs << "\n";
	cout << "Number of wrong answers : " << Exam.NumberOfWrongAnswers << "\n";
	cout << "________________________________\n";

	SetScreenColor(Exam.ExamResult);


}

void PlayMathGame() {

	stExam Exam;

	Exam.NumberOfQuestions = ReadNumberOfQuestions();
	Exam.QuestionLevel = ReadQuestionLevel();
	Exam.OperationType = ReadOperationType();

	GenerateExamQuestions(Exam);
	AskQuestionAndCorrectIt(Exam);

	PrintFinalResult(Exam);
}

void ResetScreen() {

	system("cls");
	system("color 0F");

}

void StartGame() {

	char PlayAgian = 'Y';

	do
	{
		ResetScreen();
		PlayMathGame();

		cout << "\n Do you want to play again : Y/N ? ";
		cin >> PlayAgian;

	} while (PlayAgian == 'Y' || PlayAgian == 'y');

}








int main()
{
	srand((unsigned)time(NULL));

	StartGame();

	return 0;
}

