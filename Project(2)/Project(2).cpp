#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

enum enQuestionsLevel { Easy = 1, Med = 2, Hard = 3, Mix = 4 };

enum enOperationType { Add = 1, Sub = 2, Mult = 3, Div = 4, MixOp = 5 };

int RandomNum(int from, int To)
{
	int randNum = rand() % (To - from + 1) + from;

	return randNum;
}

string GetOpType(enOperationType OpType)
{
	switch (OpType)
	{
	case enOperationType::Add:
		return "+";
	case enOperationType::Sub:
		return "-";
	case enOperationType::Mult:
		return "*";
	case enOperationType::Div:
		return "/";
	default:
		return "Mix";

	}
}

enOperationType GetOperationRandom()
{
	return (enOperationType)RandomNum(1, 4);
}

short ReadHowmanyQuestion()
{

	short NumberOfQuestion;

	do
	{

		cout << "How Many Questions do You want to answer?";
		cin >> NumberOfQuestion;

	} while (NumberOfQuestion < 1 || NumberOfQuestion > 10);

	return NumberOfQuestion;
}

enQuestionsLevel ReadQuestionsLevel()
{

	short QuestionLevel = 0;

	do
	{
		cout << "Enter Question Level [1] Easy, [2] Med, [3] Hard, [4]Mix ?";
		cin >> QuestionLevel;

	} while (QuestionLevel < 1 || QuestionLevel > 4);
	
	return(enQuestionsLevel)QuestionLevel;
}

enOperationType ReadOpType()
{
	short OpType;
	 
	do
	{
		cout << "Enter Operation Type [1] Add, [2] Sub, [3] Mul, [4] Div, [5] Mix ?";
		cin >> OpType;

	} while (OpType < 1 || OpType > 5);

	return (enOperationType)OpType;
}

string GetQuestionLevel(enQuestionsLevel QuestionLevel)
{

	string arrQuestionLevel[4] = { "Easy", "Medium", "Hard",  "Mixed" };
	return arrQuestionLevel[QuestionLevel - 1];

}

void SetScreenColor(bool Right)
{
	if (Right)

		system("color 2F");
	else
	{
		system("color 4F");
		cout << "\a";
	}

}

int SimpleCalc(int Number1, int Number2, enOperationType OpType)
{
	switch (OpType)
	{
	case enOperationType::Add:
		return Number1 + Number2;

	case enOperationType::Sub:
		return Number1 - Number2;

	case enOperationType::Div:
		return (Number2 != 0) ? (Number1 / Number2) : 0;

	case enOperationType::Mult:
		return Number1 * Number2;

	default:
		return Number1 + Number2;

	}

}

struct stQuestion
{
	int Number1 = 0;
	int Number2 = 0;
	enOperationType OperationType;
	enQuestionsLevel QuestionsLevel;
	int CorrectAnswer = 0;
	int PlayerAnswer = 0;
	bool AnswerResult = false;

};

struct stQuiz
{
	stQuestion QuestionList[100];
	short NumberOfQuestions;
	enQuestionsLevel QuestionsLevel;
	enOperationType OpType;
	short NumberOfWrongAnswers = 0;
	short NumberOfRightAnswers = 0;
	bool isPass = false;


};

stQuestion GenerateQuestion(enQuestionsLevel QuestionLevel, enOperationType OpType)
{

	stQuestion Question;

	if (QuestionLevel == enQuestionsLevel::Mix)
		QuestionLevel = (enQuestionsLevel)RandomNum(1, 3);

	Question.OperationType = OpType;

	switch (QuestionLevel)
	{

	case enQuestionsLevel::Easy:
		Question.Number1 = RandomNum(1, 10);
		Question.Number2 = RandomNum(1, 10);
		break;

	case enQuestionsLevel::Med:
		Question.Number1 = RandomNum(10, 50);
		Question.Number2 = RandomNum(10, 50);
		break;

	case enQuestionsLevel::Hard:
		Question.Number1 = RandomNum(50, 100);
		Question.Number2 = RandomNum(50, 100);
		break;

	}

	Question.CorrectAnswer = SimpleCalc(Question.Number1, Question.Number2, Question.OperationType);
	Question.QuestionsLevel = QuestionLevel;

	return Question;
}

void AskAndCorrectQuestionListAnswers(stQuiz& Quiz)
{
	for (short QuestionNumber = 0; QuestionNumber < Quiz.NumberOfQuestions; QuestionNumber++)
	{
		cout << "\nQuestion [" << QuestionNumber + 1 << "/" << Quiz.NumberOfQuestions << "]\n";
		cout << Quiz.QuestionList[QuestionNumber].Number1 << " "
			<< GetOpType(Quiz.QuestionList[QuestionNumber].OperationType) << " "
			<< Quiz.QuestionList[QuestionNumber].Number2 << " = ";

		cin >> Quiz.QuestionList[QuestionNumber].PlayerAnswer;

		if (Quiz.QuestionList[QuestionNumber].PlayerAnswer == Quiz.QuestionList[QuestionNumber].CorrectAnswer)
		{
			cout << "Correct!\n";
			Quiz.NumberOfRightAnswers++;
		}
		else
		{
			cout << "Wrong! Correct Answer: " << Quiz.QuestionList[QuestionNumber].CorrectAnswer << endl;
			Quiz.NumberOfWrongAnswers++;
		}
	}

	Quiz.isPass = (Quiz.NumberOfRightAnswers >= Quiz.NumberOfWrongAnswers);
}

void PlayMathGame()
{

	stQuiz Quiz;
	Quiz.NumberOfQuestions = 5;
	Quiz.QuestionsLevel = enQuestionsLevel::Easy;
	Quiz.OpType = enOperationType::MixOp;

	for (short QuestionNumber = 0; QuestionNumber < Quiz.NumberOfQuestions; QuestionNumber++)
	{
		Quiz.QuestionList[QuestionNumber] = GenerateQuestion(Quiz.QuestionsLevel, Quiz.OpType);
	}

	AskAndCorrectQuestionListAnswers(Quiz);

	cout << "\nQuiz Completed! Right Answers: " << Quiz.NumberOfRightAnswers <<
		", Wrong Answers: " << Quiz.NumberOfWrongAnswers << "\n";

	cout << (Quiz.isPass ? "You Passed the Quiz!\n" : "You Failed the Quiz!\n");

}

int main()
{
	srand((unsigned)time(NULL));
	
	ReadHowmanyQuestion();
	ReadQuestionsLevel();
	ReadOpType();


	PlayMathGame();

	return 0;
}