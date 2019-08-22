#include <iostream>
#include <stdlib.h>

#define MAX 30000

using namespace std;
//---------------------------------------user ------------------------------------

typedef struct _node
{
    int m[4][4];
    struct _node *next;
} Node;

void init();
int hashFunc(int module[][4]); // 이렇게 하는게 맞나?? 배열을 인수로 넣는 방법 탐구하기
int makeBlock(int module[][4][4]);

Node nodeArr[MAX];
int nodeArrIdx;

class Linkedlist
{
public:
    Node *head;
    Node *target;
    Node *itr;
    Linkedlist()
    {
        head = NULL;
    }
    void add(int module[][4])
    {
        Node *tmp = &nodeArr[nodeArrIdx];
        nodeArrIdx++;
        if (nodeArrIdx > MAX)
            throw "error";
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                tmp->m[i][j] = module[i][j];
            }
        }
        tmp->next = NULL;
        if (head == NULL)
        {
            head = tmp;
        }
        else
        {
            tmp->next = head;
            head = tmp;
        }
    }
    int makeBlock(int h);
    int compare()
    {
        int tmpSum = 0;
        int prevSum = 0;
        bool flag = true;
        for (int k = 0; k < 4; k++)
        { // clock wise로 돌리면서 총 4번 검사
            flag = true;
            tmpSum = 0;
            prevSum = 0;
            for (int i = 0; i < 4; i++)
            {
                for (int j = 0; j < 4; j++)
                {
                    switch (k)
                    {
                    case 0:
                        tmpSum = itr->m[i][j] + target->m[i][3 - j];
                        break;
                    case 1:
                        tmpSum = itr->m[i][j] + target->m[3 - j][3 - i];
                        break;
                    case 2:
                        tmpSum = itr->m[i][j] + target->m[3 - i][j];
                        break;
                    case 3:
                        tmpSum = itr->m[i][j] + target->m[j][i];
                        break;
                    default:
                        break;
                    }
                    if (prevSum == 0) // 처음 계산했을 때
                        prevSum = tmpSum;
                    else if (prevSum != tmpSum)
                    {
                        flag = false;
                        break;
                    }
                }
                if (!flag)
                    break;
            }
            if (flag)
                return tmpSum;
        }
        return -1;
    }
    void clear()
    {
        head = NULL;
    }
};

Linkedlist hashtable[16];

int Linkedlist::makeBlock(int h)
{
    int sum = 0;
    int maxRet = 0;
    itr = head;
    while (itr != NULL)
    {
        maxRet = 0;

        if (h == 0 || h == 8)
            target = itr->next; // 본인들끼리 짝짝꿍해야한다.
        else
            target = hashtable[16 - h].head; // h 랑 16-h랑 짝짝꿍 해야한다.
        while (target != NULL)
        {
            int ret = compare();
            if (ret != -1)
            { // 맞는블럭
                if (maxRet < ret)
                    maxRet = ret;
            }
            target = target->next;
        }
        itr = itr->next;
        sum += maxRet;
    }
    return sum;
}

//---------------------------------------------------------------------------

int main(void)
{
    static int module[MAX][4][4];

    srand(3); // 3 will be changed

    for (int tc = 1; tc <= 10; tc++)
    {
        for (int c = 0; c < MAX; c++)
        {
            int base = 1 + (rand() % 6);
            for (int y = 0; y < 4; y++)
            {
                for (int x = 0; x < 4; x++)
                {
                    module[c][y][x] = base + (rand() % 3);
                }
            }
        }
        cout << "#" << tc << " " << makeBlock(module) << endl;
    }

    return 0;
}
//---------------------------------------user ------------------------------------
int makeBlock(int module[][4][4])
{
    init();
    int ret = 0;
    for (int i = 0; i < MAX; i++)
    {
        int h = hashFunc(module[i]);
        hashtable[h].add(module[i]);
    }
    for (int i = 0; i <= 8; i++)
    {
        ret += hashtable[i].makeBlock(i);
    }
    return ret;
}
int hashFunc(int module[4][4])
{
    int h = 0;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            h += module[i][j];
        }
    }

    h %= 16;
    return h;
}
void init()
{
    nodeArrIdx = 0;
    for (int i = 0; i < 16; i++)
    {
        hashtable[i].clear();
    }
}
//---------------------------------------user ------------------------------------