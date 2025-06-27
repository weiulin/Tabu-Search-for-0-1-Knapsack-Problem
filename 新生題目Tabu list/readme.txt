========================================
0/1 Knapsack Problem - Tabu Search Solver
========================================

作業目的：
---------
使用 Tabu Search 方法解決 0/1 Knapsack 問題，透過局部搜尋與Tabu List管理，嘗試找最佳近似解的物品選擇組合，以獲得背包最大總價值
演算法包含 Aspiration Criterion，可在特定情況下破例接受 tabu 解，以跳脫局部最佳

使用方式：
---------
1. 編譯程式
   g++ -o knapsack tabu_search.cpp

2. 執行程式
   ./knapsack

3. 輸入格式
   - 第一行輸入兩個整數：物品數量 N 與背包最大重量 W
   - 接下來 N 行，每行輸入兩個整數：分別是該物品的重量與價值

4. 輸出格式
   - 搜尋到的最佳總價值
   - 對應的物品選擇組合（01編碼）

測試截圖：
---------
請參見附檔：test_output.png

此圖顯示本程式在測資 N = 10, W = 165, profit = {92,57,49,68,60,43,67,84,87,72}, weight = {23,31,29,44,53,38,63,85,89,82} 的情況下，
成功輸出 max profit: 309 以及 solution: 1111010000


自訂測資：
---------
測資 1：背包容量太小，無法放入任何物品 
--------------------------------------
輸入：
3 2
3 10
4 20
5 30

結果：
max profit: 0  
solution: 000

截圖請參見附檔：custom_test_case1.png

---

測資 2：全部物品剛好可以放滿
----------------------------
輸入：
4 10
2 10
3 20
1 5
4 25

結果：
max profit: 60  
solution: 1111

截圖請參見附檔：custom_test_case2.png

補充說明：
---------
本次實作以標準 Tabu Search（Algorithm 14）為基礎，並搭配 Aspiration Criterion 強化Tabu Search的搜索能力。
過程中亦有參考 Essentials-metaheuristic-algorithm 中 Feature-based Tabu Search（Algorithm 15）的原理。
我認為本次實作的重點在於掌握 Tabu Search 的基本流程與效果，且在有限時間內以正確實作、功能完備為優先考量，因此最終選擇維持完整且穩定的 Algorithm 14 版本。
未來若進行更大規模或更複雜問題的優化，Feature-based Tabu Search 將是值得進一步嘗試的方向。