
#define MAX_Input_val 11        //максимальна к-сть вхідних значень
#define MAX_Result_val 11       //максимальна к-сть вихідних значень
#define MAX_States_cnt 4        //макс к-сть станів
#define MAX_Enable_val 4        //макс к-сть можливих вхідних значень (алфавіт)
#define MAX_States_val 3        //макс значення стану автомата

//Вхідний алфавіт
int EnableVal[] = {8, 12, 17, 107};

int moves [] = {12, 12, 107, 8, 107, 17, 8, 12, 12, 8, 107};

int result [] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

//Визначаємо операції
enum States
{
	State_No = -1,
	State_0,
	State_1,
	State_2,
	State_3,
};

//Визначаємо стани
enum Operation
{
	Push,
	Pop,
	Continue,
	Repeat,
	Break
};

//Масив операцій
int operationType[MAX_Enable_val][MAX_States_cnt]	=	{	{12, Continue, 13, Break},
															{0, Continue, 14, Pop},
															{Pop, Continue, Pop, 15},
															{18, Continue, 16, Repeat}
														};

//Масив станів(задає новий стан)
int newState[MAX_Enable_val][MAX_States_cnt]		=	{	{State_1, State_1, State_2, State_No},
															{State_No, State_2, State_3, State_2},
															{State_3, State_3, State_0, State_1},
															{State_0, State_0, State_2, State_1}
														};


int FindEnableVal(int currentVal, int enableVal[], int MaxEnableVal)
{
	int i;
	for(i = 0; i < MaxEnableVal; i++)
	{
		if(currentVal == enableVal[i])
			return i;
	}
	return (-1);
}


void ClearResultArray(int res[], int resLen)
{
	int i;

	for(i = 0; i < resLen; i++)
	{
		res[i] = 0;
	}
}


int CalcResult(int res[], int resLen)
{
	int i, iCnt;

	iCnt = 0;

	for(i = 0; i < resLen; i++)
	{
		if(res[i] != 0)
			iCnt++;
	}
	return(iCnt);
}

void PrintResult(int res[], int resLen, int inputLen, int moves[])
{
	int i;
	printf("Input: ");
	printf("{");
    for(i = 0; i < inputLen; i++)
    {
        printf("%d, ", moves[i]);
    }
    printf("}");
    printf("\nCount: ");
	printf("%d\nResult: ", CalcResult(res, resLen));
	printf("{");
	for(i = 0; i < resLen; i++)
	{
		printf("%d, ", res[i]);
	}
	puts("}\n");

}


//Головна функція
int run(int moves[], int movesLen, int res[], int resLen)
{
	int i;
	int currentVal = 0;					//поточне вхідне значення
	int currentState = 0;				//поточний стан
	int currentOperat = Push;			//поточна операція
	int cntElem = 0;					//к-сть заповнених елементів на даних момент
	int Y;								//номер стовпчика

	for(i = 0; i < movesLen; i++)
	{
		//Визначаємо значення
		if(currentOperat != Repeat)
			currentVal = moves[i];

		//Перевіряємо, чи підходить воно (входить до алфавіту)
		Y = FindEnableVal(currentVal, EnableVal, MAX_Enable_val);
		if(Y == -1)
		{
			//Очишуємо масив і закінчуємо роботу
			ClearResultArray(res, resLen);

			return 0;
		}

		//Знаходимо поточну операцію
		currentOperat =  operationType[currentState][Y];

		//Присвоюємо поточному стану новий стан
		currentState = newState[currentState][Y];

		//Дивимось тип операції
		switch(currentOperat)
		{

		case Pop:

			if(cntElem == 0)
				return 0;

			res[cntElem - 1] = 0;
			cntElem--;
			break;


		case Continue:
			break;


		case Repeat:
			break;


		case Break:

			return (CalcResult(res, resLen));

			 //Push будь-яке число
		default:
			//Записуємо число у вихідний масив
			res[cntElem] = currentOperat;
			cntElem++;
			//Якщо весь масив заповнений
			if(cntElem == resLen)
				return (CalcResult(res, resLen));
			break;

		}
	}
	return (CalcResult(res, resLen));
}

void main()
{
	run(moves, MAX_Input_val, result, MAX_Result_val);
	PrintResult(result, MAX_Result_val, MAX_Input_val, moves);
	return;
}

