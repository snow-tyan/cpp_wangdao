#include <iostream>
#include <algorithm>
using std::cout;
using std::endl;

template <typename T>
class HeapSort
{
public:
	HeapSort(T *p, int length) :_p(p), _length(length) {}

	void sort()
	{
		for (int i = _length / 2 - 1; i >= 0; i--) //利用了二叉树的性质n0=n2+1
		{                                   //第N/2-1个结点恰好是最后一个有孩子结点的父节点
			adjustHeapMax(i, _length);         //自下向上调整
		}
		std::swap(_p[0], _p[_length - 1]); //交换堆顶元素和末尾元素
		for (int i = _length - 1; i > 1; i--)
		{
			adjustHeapMax(0, i); //剩余元素自上向下调成大顶堆
			std::swap(_p[0], _p[i - 1]);
		}
	}

private:
	void adjustHeapMax(int adjustPos, int arrLength)
	{
		int dad = adjustPos;   //父节点
		int son = 2 * dad + 1; //son取左子结点
		while (son < arrLength)
		{
			if (son + 1 < arrLength && _p[son] < _p[son + 1])
			{ //短路操作，下标是安全的
				//如果父节点有右孩子 且 右孩子大于左孩子
				son++; //son取右孩子
			}

			if(_p[dad] < _p[son])
			{
				std::swap(_p[dad], _p[son]);
				dad = son;
				son = 2 * dad + 1;
			}
            else
            {
                break;
            }
		}
	}

private:
	T * _p;
	int _length;
};

int main()
{
	int arr[] = { 5, 2, 3, 7, 9, 5, 6, 4, 1, 2, 3, 0, 10 };

	HeapSort<int> hSort(arr, sizeof(arr) / sizeof(int));
	hSort.sort();
	for (auto &elem : arr)
	{
		cout << elem << " ";
	}
	cout << endl;


	return 0;
}