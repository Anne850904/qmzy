#include<iostream>
using namespace std;
void Backtracking(int);

/*全局变量定义*/
static int num;				
static int limit_num;		
static double* value;		
static int* load;		
static int* limit;			
static double* curreen_limit;	
static double* r_limit;		
static double** characteristic;		
static double current_value = 0;	
static double surplus_value = 0;	
static double best_value = 0;		

int main() {
	cin >> num >> limit_num;
	value = new double[num + 1];	
	load = new int[num + 1];		
	
	characteristic = new double* [limit_num + 1];
	for (int i = 0; i <= limit_num + 1; i++)
		characteristic[i] = new double[num + 1];
	limit = new int[limit_num + 1];				
	r_limit = new double[limit_num + 1];			
	curreen_limit = new double[limit_num + 1];		

	/*初始化，如果没有初始化，最大价值直接为剩余价值*/
	for (int i = 0; i < limit_num + 1; i++) {
		r_limit[i] = 0;
		curreen_limit[i] = 0;
	}

	for (int i = 1; i <= num; i++) {
		cin >> value[i];
		surplus_value += value[i];
	}
	for (int j = 1; j <= limit_num; j++)
		for (int i = 1; i <= num; i++)
			cin >> characteristic[j][i];
	for (int i = 1; i <= limit_num; i++)
		cin >> limit[i];

	
	for (int i = 1; i <= limit_num; i++)
		for (int j = 1; j <= num; j++)
			r_limit[i] += characteristic[i][j];

	Backtracking(0);	

	/*输出*/
	cout << "\n最大价值为：" << best_value << endl;
}


/*回溯法*/
void Backtracking(int m) {

	/*当m > num 时，说明已经到达边界，进行边界处理。否则，进行计算最大价值		注意：这是递归结束的条件*/
	if (m > num) {	

	
		if (current_value > best_value)
			best_value = current_value;

	} else {

		/*----将物品m预装入背包---*/

		/*	  首先假设物品m装入背包，然后通过循环计算物品m装入背包后是否超过上界，
		 *如果超过上界，则将物品m退出背包，恢复装入物品m之前的现场，并且结束循环。
		*/
		load[m] = 1;	
		for (int j = 0; j < limit_num; j++) {
			if (curreen_limit[j] + characteristic[j][m] > limit[j]) {
				load[m] = 0;	
				break;
			}
		}

		/*----这里才是真正判断是否将物品装入背包，如果装入了执行if语句，在if语句里面递归搜索，否则在if外部递归搜索---*/

		if (load[m] == 1) {		
			
			
			for (int i = 1; i < limit_num + 1; i++)
				r_limit[i] -= characteristic[i][m];
			surplus_value -= value[m];

			/*----将物品m实际装入背包，计算当前占用的约束条件空间以及当前价值---*/
			if (load[m] == 1) {
				for (int i = 1; i < limit_num + 1; i++)
					curreen_limit[i] += characteristic[i][m];
				current_value += value[m];
			}

			Backtracking(m + 1);			

			/*向上层回溯*/
			for (int i = 1; i < limit_num + 1; i++)
				r_limit[i] += characteristic[i][m];
			surplus_value += value[m];
			
			/*当物品装入了背包时，还原当前占用的约束条件空间以及当前价值，上面加了就要减去*/
			if (load[m] == 1) {		
				for (int i = 1; i < limit_num + 1; i++)
					curreen_limit[i] -= characteristic[i][m];
				current_value -= value[m];
			}
		}

		Backtracking(m + 1);		
	}
}
