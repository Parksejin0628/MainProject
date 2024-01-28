#include<stdio.h>
#include<time.h>
#include<Windows.h>
#include<conio.h>
#include<stdlib.h>

#define BLOCK_CREATE_POS_X 5
#define BLOCK_CREATE_POS_Y 2
#define KEY_DOWN 0x8000
#define KEY_UP 0x0001
#define KEY_KEEP 0x8001
#define BOARD_POS_X 5

typedef short key;

typedef struct Block{
	int x;
	int y;
	int code;
}block;

void settingGame();														//���� ����� �ʱ� ���� 
void printBoard(int blockCode, double x, int y);						//blockCode���� ���� ������ ���ڸ� ����ϴ� �Լ� 
int updateGame();														//���������� ȣ��Ǵ� �Լ� 
void goto_xy(int x, int y);												//Ŀ����ġ�� �ű�� �Լ�  
void createBlock(int code);												//����� �����ϴ� �Լ� 
void settingTetromino();												//�̳� ����� ���� 
void fallingBlock();													//���� �ð����� ����� �����ϴ� ���� �����ϴ� �Լ�  
void softDrop();														//����Ʈ ����� �����ϴ� �Լ� 
int blockMoveSimulation(block blockQueue[4], int moveX, int moveY); 	//����� �����̴� ���� �ùķ��̼��ؼ� �Ұ����� ��� 0, ������ ��� 1�� �����ϰ� preloadBlockQueue�� ������Ʈ ���ִ� �Լ�  
void inputPreloadBlockQueue(int index, int code, int x, int y);			//preloadBlockQueue�� ������ �Է��ϴ� �Լ�
void reloadBlock();														//���� �������� ����� ��ǥ�� �ֽ�ȭ���ִ� �Լ� 
int blockRotationSimulation(block blockQueue[4], int rotDir);			//����� ȸ����Ű�� ���� �ùķ��̼����ִ� �Լ� 
void inputKey();														//Ű �Է��� �޴� �Լ� 
void landBlock(block blockQueue[4], int decreseY);						//����� ��ġ�ϴ� �Լ�
void checkLine(int line);												//y��° ���� ���� á���� Ȯ���ϴ� �Լ� 
void hardDrop();														//�ϵ� ����� �����ϴ� �Լ�
void printUI();															//UI�� ����ϴ� �Լ� 
void createBag();														//7bag�� �����ϴ� �Լ�
void hold();															//hold�� ������ �Լ� 
int importNext();														//next���� ���� ����� �����ϰ�, next�� �ֽ�ȭ �ϴ� �Լ� 
void setColor(unsigned short color);									//�ܼ� ������ ���� �����ϴ� �Լ� 
void searchHardDrop();													//��Ʈ�� ��ġ�� �ľ� �� ����ϱ� ���� �Լ� 
void reloadBoard();														//���� ��ü�� ���������� �����ϴ� �Լ� 
void settingWallkickData();												//SRS������ ��� �����͸� ����  

int board[24][12] = {0};												//���� ������ ���� 
int blockExistence = 0;													//���� �÷��̾ �����ϴ� ����� �����ϴ��� �Ǵ��ϴ� ���� 
block tetromino[8][4][4] = {0};											//��Ʈ������ �̳� ����� �����ϴ� ���� [����ڵ�][ȸ��][���] 
block blockQueue[4] = {0};												//���� �÷��̾ �����ϰ� �ִ� ����� ������ ���� ���� 
block preloadBlockQueue[4] = {0};										//����� �̵������� ��ǥ�� ������ ��� �ִ� ���� 
time_t gameStartTime = 0;												//������ ������ �ð��� �����ϴ� ���� 
time_t fallingCriteriaTime = 0;											//���� ������ ������ �Ǿ��ִ� ���� 
time_t moveCriteriaTime = 0;											//������� �������� ������ �Ǿ��ִ� ����  
time_t rotCriteriaTime = 0;												//���ȸ�� �������� ������ �Ǿ��ִ� ���� 
time_t nowTime = 0;														//����ð� ��, ���� ���� �� �󸶳� ���������� �����ϴ� ���� 
time_t fallingDelayTime = 1000;											//��ϳ��� ������ �ð�  
time_t moveDelayTime = 167;												//����̵� ������ �ð� 
time_t rotDelayTime = 100;												//���ȸ�� ������ �ð�  
time_t fallingDelayDecreaseTime = 5;									//��ϳ��� ������ ���ҷ�
time_t ARR = 33;
time_t DAS = 167;
int blockRot = 0;														//����� ȸ�� ���¸� �����ϴ� ����			
int playing = 1; 														//�÷��� ���� 
int clearLine = 0;														//������ ���� ��  
int targetLine = 40;													//��ǥ ���� �� 
int bag7[7] = {0};														//7bag���� �����ϴ� �Լ� 
int next[5] = {0};												//next���� �����ϴ� �Լ� 
int bagIndex = 5;														//7bag�� �ε��� 
int nextFrontIndex = 0;													//nextQueue�� frontIndex 
int nextRearIndex = 4;													//nextQueue�� reatIndex
int holdValue = 0; 														//hold�� �ִ� ��� ��  
block shadowPos[4] = {0};												//���� �׸��ڰ� �ִ� ��ǥ 
int preloadBoard[24][12] = {0};
key keydown_left = 0;
key keydown_right = 0;
key keydown_up = 0;
key keydown_down = 0;
key keydown_z = 0;
key keydown_x = 0;
key keydown_c = 0;
key keydown_space = 0;
block wallkickData_normal[4][5] = {0};
block wallkickData_I[8][5] = {0};

int main(void)
{
	settingGame();
	while(playing)
	{
		updateGame();
	}
	scanf("%d",&playing);
	
	return 0;
}

int updateGame()
{
	nowTime = clock();
	createBlock(0);
	fallingBlock();
	inputKey();
	printUI();
	reloadBoard();

	
	return 1;
}

void settingGame()
{
//�ʱ� ���� ���� 
	//board���� �ʱ� ���� 
	for(int row=0; row<=23; row++)
	{
		board[row][0] = -1;
		board[row][11] = -1;
	}
	for(int column=0; column<=11; column++)
	{
		//board[0][column] = -1;
		board[23][column] = -1;
	}
	//���� �õ尪 ���� 
	srand((unsigned int)time(NULL));
	
	//��Ʈ�ι̳� ���� ���� 
	settingTetromino();
	//��ű ������ ���� 
	settingWallkickData();
	
	//�ʱ� �ð����� ���� 
	gameStartTime = clock();
	fallingCriteriaTime = clock();
	rotCriteriaTime = clock();
	
	//�ʱ� next�� ���� 
	createBag();
	for(int i=0; i<5; i++)
	{
		next[i] = bag7[i];
	}
	
	
	
//�ʱ� ȭ����� ���� 
	//������ ���� 
	for(int row=3; row<=23; row++)
	{
		for(int column=0; column<=11; column++)
		{
			printBoard(board[row][column], column + BOARD_POS_X, row);
		}
		printf("\n");
	}
	
	//holdĭ ���� 
	goto_xy(0, 3);
	setColor(8); //ȸ�� 
	printf("���hold��\n");
	printf("��\n");
	printf("��\n");
	printf("������\n");
	
	//nextĭ ���� 
	for(int i=3; i<=18; i++)
	{
		setColor(8); //ȸ�� 
		goto_xy(34, i);
		if(i == 3)
		{
			printf("��next���");
		}
		else if(i==18)
		{
			printf("������");
		}
		else if((i-3)%3 == 0)
		{
			printf("--------��");
		}
		else
		{
			printBoard(-1, 21, i);
		}
	}
	
	//preloadBoard�� board���� �����ϱ�
	for(int row = 0; row < 23; row++)
	{
		for(int column = 0; column < 12; column++)
		{
			preloadBoard[row][column] = board[row][column];
		}
	 } 
	
	
	return;
}

void printBoard(int blockCode, double x, int y)
{
	x*=2;
	goto_xy(x, y); 
	
	//��� �ڵ忡 ���� ��� 
	if(blockCode == -1)
	{
		setColor(8);
		printf("��");
	}
	else if(blockCode == 0)
	{
		printf("  ");
	}
	else
	{
		if(blockCode == 1 || blockCode == 8)
		{
			setColor(4); //���� 
		}
		else if(blockCode == 2 || blockCode == 9)
		{
			setColor(7); //�Ͼ� 
		}
		else if(blockCode == 3 || blockCode == 10)
		{
			setColor(6); //���  
		}
		else if(blockCode == 4 || blockCode == 11)
		{
			setColor(2); //�ʷ� 
		}
		else if(blockCode == 5 || blockCode == 12)
		{
			setColor(1); //�Ķ� 
		}
		else if(blockCode == 6 || blockCode == 13)
		{
			setColor(5); //���� 
		}
		else if(blockCode == 7 || blockCode == 14)
		{
			setColor(3); //û�ϻ� 
		}
		else if(blockCode == 15)
		{
			setColor(12); //���� ���� 
		}
		else if(blockCode == 16)
		{
			setColor(8); //���� �Ͼ� 
		}
		else if(blockCode == 17)
		{
			setColor(14); //���� ��� 
		}
		else if(blockCode == 18)
		{
			setColor(10); //���� �ʷ� 
		}
		else if(blockCode == 19)
		{
			setColor(9); //���� �Ķ� 
		}
		else if(blockCode == 20)
		{
			setColor(13); //���� ����  
		}
		else if(blockCode == 21)
		{
			setColor(11); //���� û�� 
		}
		printf("��");
	}
	setColor(7); 
	
	return;
}


void createBlock(int code)
{
	//�������� ����� ���� ��� ����� �������� �ʴ´�. 
	if(blockExistence == 1)
	{
		return;
	}
	
	int blockCode = 0;
	int X = 0;
	int Y = 0;
	
	//���ο� ����� �����ϴ� ��� 
	if(code == 0) 
	{
		blockCode = importNext();
	}
	//������ ��� (�ַ� hold�� �ִ� ���)�� �����ϴ� ��� 
	else
	{
		blockCode = code;
	}
	// ���ο� ����� ��ǥ ���� �� ��� ��� 
	for(int i=0; i<=3; i++)
	{
		X = BLOCK_CREATE_POS_X + tetromino[blockCode][0][i].x;
		Y = BLOCK_CREATE_POS_Y + tetromino[blockCode][0][i].y;
		board[Y][X] = blockCode;
		blockQueue[i].x = X;
		blockQueue[i].y = Y;
		blockQueue[i].code = blockCode;
		
		//inputPreloadBlockQueue(i, blockCode, X, Y); 
	}
	
	/*for(int i=0; i<=3; i++)
	{
		shadowPos[i].x = 0;
		shadowPos[i].y = 0;
	}*/
	searchHardDrop();
	blockExistence = 1;
	blockRot = 0; 
	
	return;
}

void fallingBlock()
{
	if(blockExistence == 0)
	{
		return;
	}
	if(nowTime - fallingCriteriaTime >= fallingDelayTime)
	{
		fallingCriteriaTime = clock();
		softDrop();
	} 
	
	return;
}

void softDrop()
{
	
	int X = 0;
	int Y = 0;
	int CODE = blockQueue[0].code;
	int temp = blockMoveSimulation(blockQueue, 0, 1);
	if(temp == 0)
	{
		landBlock(blockQueue, 0);
		
		return;
	}
	else
	{
		reloadBlock();
	}
} 

int blockMoveSimulation(block blockQueue[4], int moveX, int moveY)
{
	int X = 0;
	int Y = 0;
	int CODE = blockQueue[0].code;;
	
	if(moveX != 0)
	{
		for(int i=0; i<=3; i++)
		{
			X = blockQueue[i].x;
			Y = blockQueue[i].y;
			
			if(board[Y][X + moveX] != 0 && board[Y][X + moveX] != CODE)
			{
				return 0;
			}
			inputPreloadBlockQueue(i, CODE, X + moveX, Y);
		}
		
	}
	else if(moveY != 0)
	{
		for(int i=0; i<=3; i++)
		{
			X = blockQueue[i].x;
			Y = blockQueue[i].y;
			
			if(board[Y + moveY][X] != 0 && board[Y + moveY][X] != CODE)
			{
				return 0;
			}
			inputPreloadBlockQueue(i, CODE, X, Y + moveY);
		}
	}
	
	return 1;
}

void inputPreloadBlockQueue(int index, int code, int x, int y)
{
	preloadBlockQueue[index].code = code;
	preloadBlockQueue[index].x = x;
	preloadBlockQueue[index].y = y;
}

void reloadBlock()
{
	int X = 0;
	int Y = 0;
	int CODE = blockQueue[0].code;
	
	for(int i=0; i<=3; i++)
	{
		X = blockQueue[i].x;
		Y = blockQueue[i].y;
		
		board[Y][X] = 0;
	}
	
	CODE = preloadBlockQueue[0].code;
	for(int i=0; i<=3; i++)
	{
		X = preloadBlockQueue[i].x;
		Y = preloadBlockQueue[i].y;
		
		board[Y][X] = CODE;
		blockQueue[i] = preloadBlockQueue[i];
	}
	if(blockExistence == 1)	searchHardDrop();
	
	return; 
}

void goto_xy(int x, int y)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(handle, pos);
}

void inputKey()
{
	if(blockExistence == 0)
	{
		return;
	}
	
	
	int temp = 0;
	int X = 0;
	int Y = 0;
	int CODE = 0;
	int keycode_z = 0X5a;
	int keycode_x = 0x58;
	int keycode_c = 0x43;
	if(GetAsyncKeyState(VK_LEFT))
	{
		if(keydown_left == 1 && (nowTime - moveCriteriaTime) > moveDelayTime)
		{
			keydown_left = 0;
			moveDelayTime = ARR;
		} 
		if(keydown_left == 0)
		{
			moveCriteriaTime = clock();
			keydown_left = 1;
			temp = blockMoveSimulation(blockQueue, -1, 0);
			if(temp != 0)
			{
				reloadBlock();
			}
		}
		
	}
	else if(!GetAsyncKeyState(VK_LEFT) && keydown_left == 1)	
	{
		keydown_left = 0;
		moveDelayTime = DAS;
	}
	
	if(GetAsyncKeyState(VK_RIGHT))
	{
		if(keydown_right == 1 && (nowTime - moveCriteriaTime) > moveDelayTime)
		{
			keydown_right = 0;
			moveDelayTime = ARR;
		} 
		if(keydown_right == 0)
		{
			moveCriteriaTime = clock();
			keydown_right = 1;
			temp = blockMoveSimulation(blockQueue, 1, 0);
			if(temp != 0)
			{
				reloadBlock();
			}
		}
		
	}
	else if(!GetAsyncKeyState(VK_RIGHT) && keydown_right == 1)	
	{
		keydown_right = 0;
		moveDelayTime = DAS;
	}
	
	if(GetAsyncKeyState(VK_DOWN))
	{
		if(keydown_down == 1 && (nowTime - moveCriteriaTime) > moveDelayTime)
		{
			keydown_down = 0;
		} 
		if(keydown_down == 0)
		{
			moveCriteriaTime = clock();
			moveDelayTime = ARR*2;
			keydown_down = 1;
			softDrop();
		}
	}
		
	else if(!GetAsyncKeyState(VK_DOWN) && keydown_down == 1)	
	{
		keydown_down = 0;
		moveDelayTime = DAS;
	}
	
	/*if(GetAsyncKeyState(VK_DOWN) && keydown_down == 0)
	{
		/*if(nowTime - moveCriteriaTime < moveDelayTime)
		{
			return;
		} 
		keydown_down = 1;
		moveCriteriaTime = clock();
		softDrop();
	}
	else if(!GetAsyncKeyState(VK_DOWN))	keydown_down = 0;*/
	
	if(GetAsyncKeyState(keycode_z) && keydown_z == 0)
	{
		/*if(nowTime - rotCriteriaTime < rotDelayTime)
		{
			return;
		} */
		keydown_z = 1;
		rotCriteriaTime = clock();
		temp = blockRotationSimulation(blockQueue, -1);
		if(temp != 0)
		{
			reloadBlock();
		}
	}
	else if(!GetAsyncKeyState(keycode_z))	keydown_z = 0;
	
	if(GetAsyncKeyState(keycode_x) && keydown_x == 0)
	{
		/*if(nowTime - rotCriteriaTime < rotDelayTime)
		{
			return;
		} */
		keydown_x = 1;
		rotCriteriaTime = clock();
		temp = blockRotationSimulation(blockQueue, 1);
		if(temp != 0)
		{
			reloadBlock();
		}
	}
	else if(!GetAsyncKeyState(keycode_x))	keydown_x = 0;
	
	if(GetAsyncKeyState(VK_SPACE) && keydown_space == 0)
	{
		/*if(nowTime - moveCriteriaTime < moveDelayTime)
		{
			return;
		} */
		keydown_space = 1;
		moveCriteriaTime = clock();
		hardDrop();
	}
	else if(!GetAsyncKeyState(VK_SPACE))	keydown_space = 0;
	
	if(GetAsyncKeyState(keycode_c) && keydown_c == 0)
	{
		/*if(nowTime - moveCriteriaTime < moveDelayTime)
		{
			return;
		} */
		keydown_c = 1;
		moveCriteriaTime = clock();
		hold();
	}
	else if(!GetAsyncKeyState(keycode_c))	keydown_c = 0;
}

int blockRotationSimulation(block blockQueue[4], int rotDir)
{
	int X = 0;
	int Y = 0;
	int CODE = blockQueue[0].code;
	block kick; 
	int poss = 0;
	int IData = 0;
	
	for(int test=0; test<5; test++)
	{
		if(CODE != 7)
		{
			for(int i=0; i<=3; i++)
			{
				X = tetromino[CODE][(blockRot + 4 + rotDir) % 4][i].x - tetromino[CODE][blockRot][i].x;
				Y = tetromino[CODE][(blockRot + 4 + rotDir) % 4][i].y - tetromino[CODE][blockRot][i].y;
				kick.x = wallkickData_normal[blockRot][test].x - wallkickData_normal[(blockRot + 4 + rotDir) % 4][test].x;
				kick.y = wallkickData_normal[blockRot][test].y - wallkickData_normal[(blockRot + 4 + rotDir) % 4][test].y;
				kick.y *= -1; //(y��ǥ�� Ŀ������ ������ �������� ������ -1�� �����ش�.)
				goto_xy(0, 27);
				printf("kick.x : %d , kick.y : %d            ", kick.x, kick.y);
			
				if(board[blockQueue[i].y + Y + kick.y][blockQueue[i].x + X + kick.x] != 0 && board[blockQueue[i].y + Y + kick.y][blockQueue[i].x + X + kick.x] != CODE)
				{
					break;
				}
				inputPreloadBlockQueue(i, CODE, blockQueue[i].x + X + kick.x, blockQueue[i].y + Y + kick.y);
				if(i==3)	poss = 1;
			}
		}
		else if(CODE == 7)
		{
			for(int i=0; i<=3; i++)
			{
				X = tetromino[CODE][(blockRot + 4 + rotDir) % 4][i].x - tetromino[CODE][blockRot][i].x;
				Y = tetromino[CODE][(blockRot + 4 + rotDir) % 4][i].y - tetromino[CODE][blockRot][i].y;
				if(blockRot == 0)
				{
					if(rotDir == 1)
					{
						IData = 0;
					}
					else
					{
						IData = 5;
					}
				}
				else if(blockRot == 1)
				{
					if(rotDir == 1)
					{
						IData = 1;
					}
					else
					{
						IData = 8;
					}
				}
				else if(blockRot == 2)
				{
					if(rotDir == 1)
					{
						IData = 2;
					}
					else
					{
						IData = 7;
					}
				}
				else
				{
					if(rotDir == 1)
					{
						IData = 3;
					}
					else
					{
						IData = 6;
					}
				}
				kick.x = wallkickData_I[IData][test].x;
				kick.y = wallkickData_I[IData][test].y;
				kick.y *= -1; //(y��ǥ�� Ŀ������ ������ �������� ������ -1�� �����ش�.)
			
				if(board[blockQueue[i].y + Y + kick.y][blockQueue[i].x + X + kick.x] != 0 && board[blockQueue[i].y + Y + kick.y] [blockQueue[i].x + X + kick.x] != CODE)
				{
					break;
				}
				inputPreloadBlockQueue(i, CODE, blockQueue[i].x + X + kick.x, blockQueue[i].y + Y + kick.y);
				if(i==3)	poss = 1;
			}
		}
		if(poss == 1)
		{
			blockRot = (blockRot + 4 + rotDir) % 4;
			return 1;
		}
	}
	
	
	return 0;
} 

void landBlock(block blockQueue[4], int decreaseY)
{
	int X = 0;
	int Y = 0;
	int CODE = blockQueue[0].code;
	int line[24] = {0};
	for(int i=0; i<=3; i++)
	{
		X = blockQueue[i].x;
		Y = blockQueue[i].y;
		inputPreloadBlockQueue(i,CODE + 7, X, Y + decreaseY);
		line[Y + decreaseY] = 1;
	}
	blockExistence = 0;
	reloadBlock();
	for(int i=0; i<24; i++)
	{
		if(line[i] != 0)
		{
			checkLine(i);
		}
	}
	if(fallingDelayTime >= 50)
	{
		fallingDelayTime -= fallingDelayDecreaseTime;
	}
	searchHardDrop();
		
	return;
}

void checkLine(int line)
{
	if(line <=1)
	{
		playing = 0;
		return;
	}
	for(int x=1; x<=10; x++)
	{
		if(board[line][x] == 0)
		{
			return;
		}
	}
	for(int x=1; x<=10; x++)
	{
		board[line][x] = 0;
	}
	for(int y = line - 1; y>=0; y--)
	{
		for(int x = 1; x<=10; x++)
		{
			board[y+1][x] = board[y][x];
			board[y][x] = 0;
		}
	}
	clearLine++; 
	
	return;
}

void hardDrop()
{
	int temp = 0;
	
	for(int i=1; i<=30; i++)
	{
		temp = blockMoveSimulation(blockQueue, 0, i);
		if(temp == 0)
		{
			landBlock(blockQueue, i-1);
			
			return;
		}
	}
	
	return;
}

void printUI()
{
	goto_xy(0, 28);
	printf("���� �ð� | %d:%d.%d         ", nowTime / 60000, (nowTime / 1000)%60, nowTime % 1000);
	goto_xy(0, 29);
	printf("line : %d / %d        ", clearLine, targetLine);
	/*goto_xy(0, 30);
	printf("blockCode : %d             ", blockQueue[0].code);*/
	if(clearLine >= targetLine)
	{
		goto_xy (0, 30);
		printf("clear!                 \n");
		playing = 0;
	}
	
	return;
}

void createBag()
{
	int randomValue = 0;
	int temp = 0;
	
	for(int i=0; i<7; i++)
	{
		bag7[i] = i+1;
	}
	for(int i=0; i<7; i++)
	{
		randomValue = rand() % 7;
		temp = bag7[i];
		bag7[i] = bag7[randomValue];
		bag7[randomValue] = temp;
	}
	
	return;
} 

void hold()
{
	int originValue = holdValue;
	int X = 0;
	int Y = 0;
	
	holdValue = blockQueue[0].code;
	for(int i=0; i<=3; i++)
	{
		printBoard(0, 1+i, 4);
		printBoard(0, 1+i, 5);
	}
	for(int i=0; i<=3; i++)
	{
		X = blockQueue[i].x;
		Y = blockQueue[i].y;
		
		inputPreloadBlockQueue(i, 0, X, Y);
		
		X = tetromino[holdValue][0][i].x;
		Y = tetromino[holdValue][0][i].y;
		if(holdValue == 3)
		{
			printBoard(holdValue, 2 + X, 5 + Y);
		}
		else if(holdValue == 7)
		{
			printBoard(holdValue, 2 + X, 5 + Y);
		}
		else
		{
			printBoard(holdValue, 2.5 + X, 5 + Y);
		}
		
	}
	blockExistence = 0;
	reloadBlock();
	for(int i=0; i<=3; i++)		//���� �׸��� ����� 
	{
		printBoard(0, shadowPos[i].x, shadowPos[i].y);
	}
	createBlock(originValue);
	
	
	return;
}

int importNext()
{
	int nextBlock = next[(nextFrontIndex) % 5];
	int X = 0;
	int Y = 0;
	
	nextFrontIndex ++;
	nextRearIndex ++;
	next[(nextRearIndex)%5] = bag7[bagIndex];
	bagIndex++;
	if(bagIndex >= 7)
	{
		createBag();
		bagIndex = 0;
	}
	for(int y=4; y<=17; y++)
	{
		if((y-3) % 3 != 0)
		{
			printBoard(0, 17, y);
			printBoard(0, 18, y);
			printBoard(0, 19, y);
			printBoard(0, 20, y);
		}
	}
		for(int i=nextFrontIndex; i<=nextRearIndex ; i++)
		{
			for(int j=0; j<=3; j++)
			{
				X = tetromino[next[i%5]][0][j].x;
				Y = tetromino[next[i%5]][0][j].y;
				if(next[i%5] == 3)
				{
					printBoard(next[i%5], 18 + X, 5 + (3*(i-nextFrontIndex)) + Y);
				}
				else if(next[i%5] == 7)
				{
					printBoard(next[i%5], 18 + X, 5 + (3*(i-nextFrontIndex)) + Y);
				}
				else
				{
					printBoard(next[i%5], 18.5 + X, 5 + (3*(i-nextFrontIndex)) + Y);
				}
			}
		}
		
		return nextBlock;
} 
//0 : ������ / 1 : �Ķ��� / 2 : ��� / 3 : û�ϻ� / 4 : ������ / 5 : ���ֻ� / 6 : ����� / 7 : ��� / 8~ : 0~7�� ������ 
void setColor(unsigned short color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
	
	return;
}

void searchHardDrop()
{
	int temp = 0;
	int X = 0;
	int Y = 0;
	int decreaseY = 0;
	int CODE = blockQueue[0].code;
	int search = 0;
	
	if(CODE > 7)	CODE -= 7;
	for(int i=0; i<=3; i++)
	{
		printBoard(0, shadowPos[i].x, shadowPos[i].y);
		shadowPos[i].x = 0;
		shadowPos[i].y = 0;
	}
	
	for(int y=1; y<=30; y++)
	{
		for(int i=0; i<=3; i++)
		{
			X = blockQueue[i].x;
			Y = blockQueue[i].y;
			
			if(board[Y + y][X] != 0 && board[Y + y][X] != CODE)
			{
				decreaseY = y;
				search = 1;
			}
		}
		if(search == 1)
		{
			break;
		}
	}
	for(int i=0; i<=3; i++)
	{
		X = blockQueue[i].x;
		Y = blockQueue[i].y;
		if(board[Y + decreaseY -1][X] == 0)
		{
			printBoard(CODE + 14, X + BOARD_POS_X ,Y + decreaseY -1);
			shadowPos[i].x = X + BOARD_POS_X;
			shadowPos[i].y = Y + decreaseY -1;
		}
	}

	
	return;
}

void reloadBoard()
{
	for(int row = 0; row < 24; row++)
	{
		for(int column = 0; column < 12; column++)
		{
			if(board[row][column] != preloadBoard[row][column])
			{
				preloadBoard[row][column] = board[row][column];
				printBoard(board[row][column], column + BOARD_POS_X, row);
			}
		}
	}
	return;
}

void settingWallkickData()
{
	wallkickData_normal[0][0].x = 0;
	wallkickData_normal[0][0].y = 0;
	wallkickData_normal[0][1].x = 0;
	wallkickData_normal[0][1].y = 0;
	wallkickData_normal[0][2].x = 0;
	wallkickData_normal[0][2].y = 0;
	wallkickData_normal[0][3].x = 0;
	wallkickData_normal[0][3].y = 0;
	wallkickData_normal[0][4].x = 0;
	wallkickData_normal[0][4].y = 0;
	
	wallkickData_normal[1][0].x = 0;
	wallkickData_normal[1][0].y = 0;
	wallkickData_normal[1][1].x = 1;
	wallkickData_normal[1][1].y = 0;
	wallkickData_normal[1][2].x = 1;
	wallkickData_normal[1][2].y = -1;
	wallkickData_normal[1][3].x = 0;
	wallkickData_normal[1][3].y = 2;
	wallkickData_normal[1][4].x = 1;
	wallkickData_normal[1][4].y = 2;
	
	wallkickData_normal[2][0].x = 0;
	wallkickData_normal[2][0].y = 0;
	wallkickData_normal[2][1].x = 0;
	wallkickData_normal[2][1].y = 0;
	wallkickData_normal[2][2].x = 0;
	wallkickData_normal[2][2].y = 0;
	wallkickData_normal[2][3].x = 0;
	wallkickData_normal[2][3].y = 0;
	wallkickData_normal[2][4].x = 0;
	wallkickData_normal[2][4].y = 0;
	
	wallkickData_normal[3][0].x = 0;
	wallkickData_normal[3][0].y = 0;
	wallkickData_normal[3][1].x = -1;
	wallkickData_normal[3][1].y = 0;
	wallkickData_normal[3][2].x = -1;
	wallkickData_normal[3][2].y = -1;
	wallkickData_normal[3][3].x = 0;
	wallkickData_normal[3][3].y = 2;
	wallkickData_normal[3][4].x = -1;
	wallkickData_normal[3][4].y = 2;
	
	wallkickData_I[0][0].x = 0;
	wallkickData_I[0][0].y = 0;
	wallkickData_I[0][1].x = -2;
	wallkickData_I[0][1].y = 0;
	wallkickData_I[0][2].x = 1;
	wallkickData_I[0][2].y = 1;
	wallkickData_I[0][3].x = 1;
	wallkickData_I[0][3].y = 2;
	wallkickData_I[0][4].x = -2;
	wallkickData_I[0][4].y = -1;
	
	wallkickData_I[1][0].x = 0;
	wallkickData_I[1][0].y = 0;
	wallkickData_I[1][1].x = -1;
	wallkickData_I[1][1].y = 0;
	wallkickData_I[1][2].x = 2;
	wallkickData_I[1][2].y = 0;
	wallkickData_I[1][3].x = -1;
	wallkickData_I[1][3].y = 2;
	wallkickData_I[1][4].x = 2;
	wallkickData_I[1][4].y = -1;
	
	wallkickData_I[2][0].x = 0;
	wallkickData_I[2][0].y = 0;
	wallkickData_I[2][1].x = 2;
	wallkickData_I[2][1].y = 0;
	wallkickData_I[2][2].x = -1;
	wallkickData_I[2][2].y = 0;
	wallkickData_I[2][3].x = 2;
	wallkickData_I[2][3].y = 1;
	wallkickData_I[2][4].x = -1;
	wallkickData_I[2][4].y = -1;

	wallkickData_I[3][0].x = 0;
	wallkickData_I[3][0].y = 0;
	wallkickData_I[3][1].x = -2;
	wallkickData_I[3][1].y = 0;
	wallkickData_I[3][2].x = 1;
	wallkickData_I[3][2].y = 0;
	wallkickData_I[3][3].x = -2;
	wallkickData_I[3][3].y = -1;
	wallkickData_I[3][4].x = 1;
	wallkickData_I[3][4].y = -2;
	
	wallkickData_I[4][0].x = 0;
	wallkickData_I[4][0].y = 0;
	wallkickData_I[4][1].x = 2;
	wallkickData_I[4][1].y = 0;
	wallkickData_I[4][2].x = -1;
	wallkickData_I[4][2].y = 0;
	wallkickData_I[4][3].x = -1;
	wallkickData_I[4][3].y = 2;
	wallkickData_I[4][4].x = 2;
	wallkickData_I[4][4].y = -1;
	
	wallkickData_I[5][0].x = 0;
	wallkickData_I[5][0].y = 0;
	wallkickData_I[5][1].x = 1;
	wallkickData_I[5][1].y = 0;
	wallkickData_I[5][2].x = -2;
	wallkickData_I[5][2].y = 0;
	wallkickData_I[5][3].x = 1;
	wallkickData_I[5][3].y = 2;
	wallkickData_I[5][4].x = -2;
	wallkickData_I[5][4].y = -1;
	
	wallkickData_I[6][0].x = 0;
	wallkickData_I[6][0].y = 0;
	wallkickData_I[6][1].x = -2;
	wallkickData_I[6][1].y = 0;
	wallkickData_I[6][2].x = 1;
	wallkickData_I[6][2].y = 0;
	wallkickData_I[6][3].x = -2;
	wallkickData_I[6][3].y = 1;
	wallkickData_I[6][4].x = 1;
	wallkickData_I[6][4].y = -1;

	wallkickData_I[7][0].x = 0;
	wallkickData_I[7][0].y = 0;
	wallkickData_I[7][1].x = 2;
	wallkickData_I[7][1].y = 0;
	wallkickData_I[7][2].x = -1;
	wallkickData_I[7][2].y = 0;
	wallkickData_I[7][3].x = 2;
	wallkickData_I[7][3].y = 1;
	wallkickData_I[7][4].x = -1;
	wallkickData_I[7][4].y = -2;
}

void settingTetromino()
{
	//Z�̳�
	tetromino[1][0][0].x = -1;
	tetromino[1][0][0].y = -1;
	tetromino[1][0][0].code = 1;
	tetromino[1][0][1].x = 0;
	tetromino[1][0][1].y = -1;
	tetromino[1][0][1].code = 1;
	tetromino[1][0][2].x = 0;
	tetromino[1][0][2].y = 0;
	tetromino[1][0][2].code = 1;
	tetromino[1][0][3].x = 1;
	tetromino[1][0][3].y = 0;
	tetromino[1][0][3].code = 1;
	
	tetromino[1][1][0].x = 1;
	tetromino[1][1][0].y = -1;
	tetromino[1][1][0].code = 1;
	tetromino[1][1][1].x = 1;
	tetromino[1][1][1].y = 0;
	tetromino[1][1][1].code = 1;
	tetromino[1][1][2].x = 0;
	tetromino[1][1][2].y = 0;
	tetromino[1][1][2].code = 1;
	tetromino[1][1][3].x = 0;
	tetromino[1][1][3].y = 1;
	tetromino[1][1][3].code = 1;
	
	tetromino[1][2][0].x = 1;
	tetromino[1][2][0].y = 1;
	tetromino[1][2][0].code = 1;
	tetromino[1][2][1].x = 0;
	tetromino[1][2][1].y = 1;
	tetromino[1][2][1].code = 1;
	tetromino[1][2][2].x = 0;
	tetromino[1][2][2].y = 0;
	tetromino[1][2][2].code = 1;
	tetromino[1][2][3].x = -1;
	tetromino[1][2][3].y = 0;
	tetromino[1][2][3].code = 1;
	
	tetromino[1][3][0].x = -1;
	tetromino[1][3][0].y = 1;
	tetromino[1][3][0].code = 1;
	tetromino[1][3][1].x = -1;
	tetromino[1][3][1].y = 0;
	tetromino[1][3][1].code = 1;
	tetromino[1][3][2].x = 0;
	tetromino[1][3][2].y = 0;
	tetromino[1][3][2].code = 1;
	tetromino[1][3][3].x = 0;
	tetromino[1][3][3].y = -1;
	tetromino[1][3][3].code = 1;
	
	//L�̳�
	
	tetromino[2][0][0].x = -1;
	tetromino[2][0][0].y = 0;
	tetromino[2][0][0].code = 2; 
	tetromino[2][0][1].x = 0;
	tetromino[2][0][1].y = 0;
	tetromino[2][0][1].code = 2; 
	tetromino[2][0][2].x = 1;
	tetromino[2][0][2].y = 0;
	tetromino[2][0][2].code = 2; 
	tetromino[2][0][3].x = 1;
	tetromino[2][0][3].y = -1;
	tetromino[2][0][3].code = 2; 
	
	tetromino[2][1][0].x = 0;
	tetromino[2][1][0].y = -1;
	tetromino[2][1][0].code = 2;
	tetromino[2][1][1].x = 0;
	tetromino[2][1][1].y = 0;
	tetromino[2][1][1].code = 2;
	tetromino[2][1][2].x = 0;
	tetromino[2][1][2].y = 1;
	tetromino[2][1][2].code = 2;
	tetromino[2][1][3].x = 1;
	tetromino[2][1][3].y = 1;
	tetromino[2][1][3].code = 2; 
	
	tetromino[2][2][0].x = 1;
	tetromino[2][2][0].y = 0;
	tetromino[2][2][0].code = 2;
	tetromino[2][2][1].x = 0;
	tetromino[2][2][1].y = 0;
	tetromino[2][2][1].code = 2;
	tetromino[2][2][2].x = -1;
	tetromino[2][2][2].y = 0;
	tetromino[2][2][2].code = 2;
	tetromino[2][2][3].x = -1;
	tetromino[2][2][3].y = 1;
	tetromino[2][2][3].code = 2;

	tetromino[2][3][0].x = 0;
	tetromino[2][3][0].y = 1;
	tetromino[2][3][0].code = 2;
	tetromino[2][3][1].x = 0;
	tetromino[2][3][1].y = 0;
	tetromino[2][3][1].code = 2;
	tetromino[2][3][2].x = 0;
	tetromino[2][3][2].y = -1;
	tetromino[2][3][2].code = 2;
	tetromino[2][3][3].x = -1;
	tetromino[2][3][3].y = -1;
	tetromino[2][3][3].code = 2;

	//O�̳�  
	
	tetromino[3][0][0].x = 0;
	tetromino[3][0][0].y = -1;
	tetromino[3][0][0].code = 3;
	tetromino[3][0][1].x = 0;
	tetromino[3][0][1].y = 0;
	tetromino[3][0][1].code = 3;
	tetromino[3][0][2].x = 1;
	tetromino[3][0][2].y = 0;
	tetromino[3][0][2].code = 3;
	tetromino[3][0][3].x = 1;
	tetromino[3][0][3].y = -1;
	tetromino[3][0][3].code = 3;
	
	tetromino[3][1][0].x = 0;
	tetromino[3][1][0].y = -1;
	tetromino[3][1][0].code = 3;
	tetromino[3][1][1].x = 0;
	tetromino[3][1][1].y = 0;
	tetromino[3][1][1].code = 3;
	tetromino[3][1][2].x = 1;
	tetromino[3][1][2].y = 0;
	tetromino[3][1][2].code = 3;
	tetromino[3][1][3].x = 1;
	tetromino[3][1][3].y = -1;
	tetromino[3][1][3].code = 3;
	
	tetromino[3][2][0].x = 0;
	tetromino[3][2][0].y = -1;
	tetromino[3][2][0].code = 3;
	tetromino[3][2][1].x = 0;
	tetromino[3][2][1].y = 0;
	tetromino[3][2][1].code = 3;
	tetromino[3][2][2].x = 1;
	tetromino[3][2][2].y = 0;
	tetromino[3][2][2].code = 3;
	tetromino[3][2][3].x = 1;
	tetromino[3][2][3].y = -1;
	tetromino[3][2][3].code = 3;
	
	tetromino[3][3][0].x = 0;
	tetromino[3][3][0].y = -1;
	tetromino[3][3][0].code = 3;
	tetromino[3][3][1].x = 0;
	tetromino[3][3][1].y = 0;
	tetromino[3][3][1].code = 3;
	tetromino[3][3][2].x = 1;
	tetromino[3][3][2].y = 0;
	tetromino[3][3][2].code = 3;
	tetromino[3][3][3].x = 1;
	tetromino[3][3][3].y = -1;
	tetromino[3][3][3].code = 3;

	//S�̳�
	
	tetromino[4][0][0].x = 1;
	tetromino[4][0][0].y = -1;
	tetromino[4][0][0].code = 4;
	tetromino[4][0][1].x = 0;
	tetromino[4][0][1].y = -1;
	tetromino[4][0][1].code = 4;
	tetromino[4][0][2].x = 0;
	tetromino[4][0][2].y = 0;
	tetromino[4][0][2].code = 4;
	tetromino[4][0][3].x = -1;
	tetromino[4][0][3].y = 0;
	tetromino[4][0][3].code = 4;
	
	tetromino[4][1][0].x = 1;
	tetromino[4][1][0].y = 1;
	tetromino[4][1][0].code = 4;
	tetromino[4][1][1].x = 1;
	tetromino[4][1][1].y = 0;
	tetromino[4][1][1].code = 4;
	tetromino[4][1][2].x = 0;
	tetromino[4][1][2].y = 0;
	tetromino[4][1][2].code = 4;
	tetromino[4][1][3].x = 0;
	tetromino[4][1][3].y = -1;
	tetromino[4][1][3].code = 4;
	
	tetromino[4][2][0].x = -1;
	tetromino[4][2][0].y = 1;
	tetromino[4][2][0].code = 4;
	tetromino[4][2][1].x = 0;
	tetromino[4][2][1].y = 1;
	tetromino[4][2][1].code = 4;
	tetromino[4][2][2].x = 0;
	tetromino[4][2][2].y = 0;
	tetromino[4][2][2].code = 4;
	tetromino[4][2][3].x = 1;
	tetromino[4][2][3].y = 0;
	tetromino[4][2][3].code = 4;
	
	tetromino[4][3][0].x = -1;
	tetromino[4][3][0].y = -1;
	tetromino[4][3][0].code = 4;
	tetromino[4][3][1].x = -1;
	tetromino[4][3][1].y = 0;
	tetromino[4][3][1].code = 4;
	tetromino[4][3][2].x = 0;
	tetromino[4][3][2].y = 0;
	tetromino[4][3][2].code = 4;
	tetromino[4][3][3].x = 0;
	tetromino[4][3][3].y = 1;
	tetromino[4][3][3].code = 4;

	//J�̳�
	
	tetromino[5][0][0].x = 1;
	tetromino[5][0][0].y = 0;
	tetromino[5][0][0].code = 5;
	tetromino[5][0][1].x = 0;
	tetromino[5][0][1].y = 0;
	tetromino[5][0][1].code = 5;
	tetromino[5][0][2].x = -1;
	tetromino[5][0][2].y = 0;
	tetromino[5][0][2].code = 5;
	tetromino[5][0][3].x = -1;
	tetromino[5][0][3].y = -1;
	tetromino[5][0][3].code = 5; 

	tetromino[5][1][0].x = 0;
	tetromino[5][1][0].y = 1;
	tetromino[5][1][0].code = 5;
	tetromino[5][1][1].x = 0;
	tetromino[5][1][1].y = 0;
	tetromino[5][1][1].code = 5;
	tetromino[5][1][2].x = 0;
	tetromino[5][1][2].y = -1;
	tetromino[5][1][2].code = 5;
	tetromino[5][1][3].x = 1;
	tetromino[5][1][3].y = -1;
	tetromino[5][1][3].code = 5;

	tetromino[5][2][0].x = -1;
	tetromino[5][2][0].y = 0;
	tetromino[5][2][0].code = 5;
	tetromino[5][2][1].x = 0;
	tetromino[5][2][1].y = 0;
	tetromino[5][2][1].code = 5;
	tetromino[5][2][2].x = 1;
	tetromino[5][2][2].y = 0;
	tetromino[5][2][2].code = 5;
	tetromino[5][2][3].x = 1;
	tetromino[5][2][3].y = 1;
	tetromino[5][2][3].code = 5;
	
	tetromino[5][3][0].x = 0;
	tetromino[5][3][0].y = -1;
	tetromino[5][3][0].code = 5;
	tetromino[5][3][1].x = 0;
	tetromino[5][3][1].y = 0;
	tetromino[5][3][1].code = 5;
	tetromino[5][3][2].x = 0;
	tetromino[5][3][2].y = 1;
	tetromino[5][3][2].code = 5;
	tetromino[5][3][3].x = -1;
	tetromino[5][3][3].y = 1;
	tetromino[5][3][3].code = 5;
	
	//T�̳� 
	
	tetromino[6][0][0].x = 1;
	tetromino[6][0][0].y = 0;
	tetromino[6][0][0].code = 6;
	tetromino[6][0][1].x = 0;
	tetromino[6][0][1].y = 0;
	tetromino[6][0][1].code = 6;
	tetromino[6][0][2].x = -1;
	tetromino[6][0][2].y = 0;
	tetromino[6][0][2].code = 6;
	tetromino[6][0][3].x = 0;
	tetromino[6][0][3].y = -1;
	tetromino[6][0][3].code = 6;
	
	tetromino[6][1][0].x = 0;
	tetromino[6][1][0].y = 1;
	tetromino[6][1][0].code = 6;
	tetromino[6][1][1].x = 0;
	tetromino[6][1][1].y = 0;
	tetromino[6][1][1].code = 6;
	tetromino[6][1][2].x = 0;
	tetromino[6][1][2].y = -1;
	tetromino[6][1][2].code = 6;
	tetromino[6][1][3].x = 1;
	tetromino[6][1][3].y = 0;
	tetromino[6][1][3].code = 6;
	
	tetromino[6][2][0].x = 1;
	tetromino[6][2][0].y = 0;
	tetromino[6][2][0].code = 6;
	tetromino[6][2][1].x = 0;
	tetromino[6][2][1].y = 0;
	tetromino[6][2][1].code = 6;
	tetromino[6][2][2].x = -1;
	tetromino[6][2][2].y = 0;
	tetromino[6][2][2].code = 6;
	tetromino[6][2][3].x = 0;
	tetromino[6][2][3].y = 1;
	tetromino[6][2][3].code = 6;
	
	tetromino[6][3][0].x = 0;
	tetromino[6][3][0].y = 1;
	tetromino[6][3][0].code = 6;
	tetromino[6][3][1].x = 0;
	tetromino[6][3][1].y = 0;
	tetromino[6][3][1].code = 6;
	tetromino[6][3][2].x = 0;
	tetromino[6][3][2].y = -1;
	tetromino[6][3][2].code = 6;
	tetromino[6][3][3].x = -1;
	tetromino[6][3][3].y = 0;
	tetromino[6][3][3].code = 6;
	
	//I�̳�
	
	tetromino[7][0][0].x = -1;
	tetromino[7][0][0].y = 0;
	tetromino[7][0][0].code = 7;
	tetromino[7][0][1].x = 0;
	tetromino[7][0][1].y = 0;
	tetromino[7][0][1].code = 7;
	tetromino[7][0][2].x = 1;
	tetromino[7][0][2].y = 0;
	tetromino[7][0][2].code = 7;
	tetromino[7][0][3].x = 2;
	tetromino[7][0][3].y = 0;
	tetromino[7][0][3].code = 7; 
	
	tetromino[7][1][0].x = 1;
	tetromino[7][1][0].y = -1;
	tetromino[7][1][0].code = 7;
	tetromino[7][1][1].x = 1;
	tetromino[7][1][1].y = 0;
	tetromino[7][1][1].code = 7;
	tetromino[7][1][2].x = 1;
	tetromino[7][1][2].y = 1;
	tetromino[7][1][2].code = 7;
	tetromino[7][1][3].x = 1;
	tetromino[7][1][3].y = 2;
	tetromino[7][1][3].code = 7;
	
	tetromino[7][2][0].x = -1;
	tetromino[7][2][0].y = 1;
	tetromino[7][2][0].code = 7;
	tetromino[7][2][1].x = 0;
	tetromino[7][2][1].y = 1;
	tetromino[7][2][1].code = 7;
	tetromino[7][2][2].x = 1;
	tetromino[7][2][2].y = 1;
	tetromino[7][2][2].code = 7;
	tetromino[7][2][3].x = 2;
	tetromino[7][2][3].y = 1;
	tetromino[7][2][3].code = 7;
	
	tetromino[7][3][0].x = 0;
	tetromino[7][3][0].y = -1;
	tetromino[7][3][0].code = 7;
	tetromino[7][3][1].x = 0;
	tetromino[7][3][1].y = 0;
	tetromino[7][3][1].code = 7;
	tetromino[7][3][2].x = 0;
	tetromino[7][3][2].y = 1;
	tetromino[7][3][2].code = 7;
	tetromino[7][3][3].x = 0;
	tetromino[7][3][3].y = 2;
	tetromino[7][3][3].code = 7;
}

