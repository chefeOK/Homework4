#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//성명
int** create_matrix(int row, int col);
void print_matrix(int** matrix, int row, int col);
int free_matrix(int** matrix, int row, int col);
int fill_data(int** matrix, int row, int col);
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col);
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col);
int transpose_matrix(int** matrix, int** matrix_t, int row, int col);
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col);

int main()
{
	char command;
	printf("[----- [CHEN YUXIANG]  [2020039089] -----]\n");

	int row, col;
	srand(time(NULL));//srand(time(NULL)) 을 먼저 호출하는 것은 현재 시간을 시드로 사용하고 프로그램이 실행될 때마다 다른 난수 시퀀스를 생성하는 것입니다.

	printf("Input row and col : ");
	scanf_s("%d %d", &row, &col);
	int** matrix_a = create_matrix(row, col);
	int** matrix_b = create_matrix(row, col);
	int** matrix_a_t = create_matrix(col, row);

	printf("Matrix Created.\n");

	if (matrix_a == NULL || matrix_b == NULL) { return -1; }

	do {
		printf("----------------------------------------------------------------\n");
		printf("                     Matrix Manipulation                        \n");//행렬 연산

		printf("----------------------------------------------------------------\n");
		printf(" Initialize Matrix   = z           Print Matrix        = p \n");//초기화 행렬    인쇄 매트릭스
		printf(" Add Matrix          = a           Subtract Matrix     = s \n");//행렬 추가      빼기 행렬
		printf(" Transpose matrix_a  = t           Multiply Matrix     = m \n");//전치 행렬     행렬 곱셈
		printf(" Quit                = q \n");//그만두 다
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf_s(" %c", &command);
                    // //스위치 명령
		switch (command) {
		case 'z': case 'Z':
			printf("Matrix Initialized\n");//행렬 초기화
			fill_data(matrix_a, row, col);//데이터 투입
			fill_data(matrix_b, row, col);
			break;
		case 'p': case 'P':
			printf("Print matrix\n");
			printf("matrix_a\n");
			print_matrix(matrix_a, row, col);
			printf("matrix_b\n");
			print_matrix(matrix_b, row, col);
			break;
		case 'a': case 'A':
			printf("Add two matrices\n");//두 개의 행렬 추가
			addition_matrix(matrix_a, matrix_b, row, col);
			break;
		case 's': case 'S':
			printf("Subtract two matrices \n");//두 행렬 빼기
			subtraction_matrix(matrix_a, matrix_b, row, col);
			break;
		case 't': case 'T':
			printf("Transpose matrix_a \n");//전치 행렬
			printf("matrix_a\n");
			transpose_matrix(matrix_a, matrix_a_t, col, row);
			print_matrix(matrix_a_t, col, row);
			break;
		case 'm': case 'M':
			printf("Multiply matrix_a with transposed matrix_a \n");//matrix_a와 전치된 matrix_a를 곱합니다.
			transpose_matrix(matrix_a, matrix_a_t, col, row);
			multiply_matrix(matrix_a, matrix_a_t, row, col);
			break;
		case 'q': case 'Q':
			printf("Free all matrices..\n");//모든 행렬 해제
			free_matrix(matrix_a_t, col, row);
			free_matrix(matrix_a, row, col);
			free_matrix(matrix_b, row, col);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');

	return 1;
}

//malloc()을 사용하여 행 x 열 크기의 2D 배열을 만듭니다.
int** create_matrix(int row, int col)
{
	//사전 조건 확인 
	if (row <= 0 || col <= 0) {
		printf("Check the size of row and col!\n");//행 및 열 크기 확인
		return NULL;
	}

	int** matrix = (int**)malloc(sizeof(int*) * row);
	for (int r = 0; r < row; r++) {
		matrix[r] = (int*)malloc(sizeof(int) * col);
	}

	//포스트 조건 확인 
	if (matrix == NULL) {
		printf("Memory Allocation Failed.\n");//메모리 할당 실패
		return NULL;
	}

	return matrix;
}

//크기가 행 x 열인 행렬 인쇄 
void print_matrix(int** matrix, int row, int col)
{
	//사전 조건 확인 
	if (row <= 0 || col <= 0) {
		printf("Check the size of row and col!\n");//행 및 열 크기 확인
		return;
	}
	for (int matrix_row = 0; matrix_row < row; matrix_row++) {
		for (int matrix_col = 0; matrix_col < col; matrix_col++)
			printf("%3d ", matrix[matrix_row][matrix_col]);
		printf("\n");
	}
	printf("\n");
	//포스트 조건 확인
	if (matrix == NULL) {
		printf("Memory Allocation Failed.\n");//메모리 할당 실패
		return;
	}


	return;
}


 //create_matrix()에 의해 할당된 여유 메모리 
int free_matrix(int** matrix, int row, int col)
{
	//사전 조건 확인 
	if (row <= 0 || col <= 0) {
		printf("Check the size of row and col!\n");//행 및 열 크기 확인
		return -1;
	}

	for (int matrix_row = 0; matrix_row < row; matrix_row++) {
		free(matrix[matrix_row]);
	}

	free(matrix);
	return 1;
}


//주어진 행렬에 임의의 값을 할당 
int fill_data(int** matrix, int row, int col)
{
	//사전 조건 확인 
	if (row <= 0 || col <= 0) {
		printf("Check the size of row and col!\n");//행 및 열 크기 확인
		return -1;
	}
	for (int matrix_row = 0; matrix_row < row; matrix_row++)
		for (int matrix_col = 0; matrix_col < col; matrix_col++)
			matrix[matrix_row][matrix_col] = rand() % 20;
	//포스트 조건 확인
	if (matrix == NULL) {
		printf("Memory Allocation Failed.\n");//메모리 할당 실패
		return -1;
	}
	return 1;
}

//mmatrix_sum = matrix_a + matrix_b 
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col)
{
	int** matrix_sum = create_matrix(row, col);
	//사전 조건 확인 
	if (row <= 0 || col <= 0) {
		printf("Check the size of row and col!\n");//행 및 열 크기 확인
		return -1;
	}
	for (int matrix_row = 0; matrix_row < row; matrix_row++) {
		for (int matrix_col = 0; matrix_col < col; matrix_col++)
			matrix_sum[matrix_row][matrix_col] = matrix_a[matrix_row][matrix_col] + matrix_b[matrix_row][matrix_col];
	}
	//포스트 조건 확인
	if (matrix_a == NULL || matrix_b == NULL || matrix_sum == NULL) {
		printf("Memory Allocation Failed.\n");
		return -1;
	}

	print_matrix(matrix_sum, row, col);
	free_matrix(matrix_sum, row, col);
	return 1;
}

//matrix_sub = matrix_a - matrix_b 
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col)
{
	int** matrix_sub = create_matrix(row, col);
	//사전 조건 확인 
	if (row <= 0 || col <= 0) {
		printf("Check the size of row and col!\n");//행 및 열 크기 확인
		return -1;
	}
	for (int matrix_row = 0; matrix_row < row; matrix_row++) {
		for (int matrix_col = 0; matrix_col < col; matrix_col++)
			matrix_sub[matrix_row][matrix_col] = matrix_a[matrix_row][matrix_col] - matrix_b[matrix_row][matrix_col];
	}
	//포스트 조건 확인
	if (matrix_a == NULL || matrix_b == NULL || matrix_sub == NULL) {
		printf("Memory Allocation Failed.\n");//메모리 할당 실패
		return -1;
	}
	print_matrix(matrix_sub, row, col);
	free_matrix(matrix_sub, row, col);

	return 1;
}

// transpose the matrix to matrix_t 
int transpose_matrix(int** matrix, int** matrix_t, int row, int col)
{
	//사전 조건 확인 
	if (row <= 0 || col <= 0) {
		printf("Check the size of row and col!\n");//행 및 열 크기 확인
		return -1;
	}
	for (int matrix_row = 0; matrix_row < row; matrix_row++) {
		for (int matrix_col = 0; matrix_col < col; matrix_col++)
			matrix_t[matrix_row][matrix_col] = matrix[matrix_col][matrix_row];
	}
	//포스트 조건 확인
	if (matrix == NULL || matrix_t == NULL) {
		printf("Memory Allocation Failed.\n");//메모리 할당 실패
		return -1;
	}

	return 1;
}

/* matrix_axt - matrix_a x matrix_t */
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col)
{
	int** matrix_axt = create_matrix(row, row);
	//사전 조건 확인 
	if (row <= 0 || col <= 0) {
		printf("Check the size of row and col!\n");//행 및 열 크기 확인
		return -1;
	}
	for (int matrix_a_row = 0; matrix_a_row < row; matrix_a_row++) {
		for (int matrix_t_row = 0; matrix_t_row < row; matrix_t_row++) {
			int temp = 0;
			for (int matrix_col = 0; matrix_col < col; matrix_col++)
				temp += matrix_a[matrix_a_row][matrix_col] * matrix_t[matrix_col][matrix_t_row];
			matrix_axt[matrix_a_row][matrix_t_row] = temp;
		}
	}
	//포스트 조건 확인
	if (matrix_t == NULL || matrix_axt == NULL) {
		printf("Memory Allocation Failed.\n");//메모리 할당 실패
		return -1;
	}
	print_matrix(matrix_axt, row, row);
	free_matrix(matrix_axt, row, col);
	return 1;
}
