#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <cstdlib>
#include <ctime>
using namespace std;

int N, W;
vector<int> weights;
vector<int> profits;

int tabuSize = 10, MaxIteration = 1000;
queue<string> tabuQueue;       // queue負責順序 (FIFO控制tabuSize)
unordered_set<string> tabuSet; // set負責快速查詢 (判斷是不是tabu)

void input() // 讀取物品數量(N)、背包限重(W)、物品重量(weights)及價值(profits)
{
    cin >> N >> W;
    weights.resize(N);
    profits.resize(N);

    for (int i = 0; i < N; i++)
    {
        cin >> weights[i] >> profits[i];
    }
}

int cmptWeight(const vector<int> &solution) // 計算背包重量
{
    int totalWeight = 0;
    for (int i = 0; i < N; i++)
    {
        if (solution[i] == 1)
        {
            totalWeight += weights[i];
        }
    }
    return totalWeight;
}

int cmptProfit(const vector<int> &solution) // 計算背包價值
{
    int totalProfit = 0;
    for (int i = 0; i < N; i++)
    {
        if (solution[i] == 1)
        {
            totalProfit += profits[i];
        }
    }
    return totalProfit;
}

vector<int> generate_Init_Sol() // Tabu的隨機初始解
{
    vector<int> solution(N, 0);
    int currentWeight = 0;

    for (int i = 0; i < N; i++)
    {
        int pick = rand() % 2;

        if (pick == 1 && currentWeight + weights[i] <= W)
        {
            solution[i] = 1;
            currentWeight += weights[i];
        }
    }

    return solution;
}

vector<int> tweak(const vector<int> &solution) // 產生鄰居解：隨機選一個 bit 並進行 flip（0→1 或 1→0）
{
    vector<int> newSolution = solution;
    int index = rand() % N;
    newSolution[index] = 1 - newSolution[index]; // flip bit

    return newSolution;
}

// 將 vector<int> 轉成 string
// 讓Solution方便存進 unordered_set 中，快速查找是否為tabu
// 解決hash不支援vector的問題
string SolutionToString(const vector<int> &solution)
{
    string s = "";
    for (int i = 0; i < N; i++)
    {
        s += to_string(solution[i]);
    }

    return s;
}

int main()
{
    srand(time(0));
    input();

    vector<int> currSolution = generate_Init_Sol();
    vector<int> BestSolution = currSolution;

    string currSolutionStr = SolutionToString(currSolution);
    tabuQueue.push(currSolutionStr);
    tabuSet.insert(currSolutionStr);

    for (int iter = 0; iter < MaxIteration; iter++) // 迭代 1000 次，持續尋找更好的解
    {
        vector<int> candidateSol;
        int candidateProfit = -1;

        for (int i = 0; i < N; i++)
        {
            vector<int> neighbor = tweak(currSolution);
            string neighborStr = SolutionToString(neighbor);

            // 尋找一個不是tabu的合法鄰居解
            // 或者即使是tabu，但是它的profit比當前最佳解還高且重量合法，則可以考慮(Aspiration)
            if ((tabuSet.count(neighborStr) == 0 || cmptProfit(neighbor) > cmptProfit(BestSolution)) && cmptWeight(neighbor) <= W)
            {
                int neighborProfit = cmptProfit(neighbor);

                if (neighborProfit > candidateProfit) // 如果鄰居profit比當前candidate更高，就更新candidate
                {
                    candidateProfit = neighborProfit;
                    candidateSol = neighbor;
                }
            }
        }

        // 更新當前解為選定的最佳鄰居解（無論其是否優於原解），並同步更新 Tabu List
        // 允許局部下降，有助於跳脫局部最佳解的陷阱
        if (!candidateSol.empty())
        {
            currSolution = candidateSol;

            currSolutionStr = SolutionToString(currSolution);
            tabuQueue.push(currSolutionStr);
            tabuSet.insert(currSolutionStr);

            if (tabuQueue.size() > tabuSize) // 如果tabuQueue超過大小限制，則刪除最舊的元素
            {
                string oldest = tabuQueue.front();
                tabuQueue.pop();
                tabuSet.erase(oldest);
            }
        }

        if (cmptProfit(currSolution) > cmptProfit(BestSolution)) // 更新當前最佳解
        {
            BestSolution = currSolution;
        }
    }

    // cout << "Initial Solution: ";
    // for (int x : currSolution)
    //     cout << x;
    // cout << endl;
    // cout << "Weight: " << cmptWeight(currSolution) << endl;
    // cout << "Profit: " << cmptProfit(currSolution) << endl;

    // 輸出最終最佳解的總價值與選擇組合
    cout << "max profit:" << cmptProfit(BestSolution) << endl;
    cout << "solution:";
    for (int x : BestSolution)
    {
        cout << x;
    }
    cout << endl;

    return 0;
}