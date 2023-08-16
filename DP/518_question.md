**Problem: Coin Change II**

You are provided with an array called `coins` containing various coin denominations and an integer `amount` representing a total amount of money. Your task is to determine the number of combinations that can be used to make up the given amount using the provided coins. If it is not possible to make up the amount using any combination of the coins, return 0.

Assumptions:
- You have an infinite supply of each type of coin.
- The answer will be within the range of a signed 32-bit integer.

Example 1:
- Input: `amount = 5`, `coins = [1, 2, 5]`
- Output: 4
- Explanation: There are four ways to make up the amount 5:
  1. 5 = 5
  2. 5 = 2 + 2 + 1
  3. 5 = 2 + 1 + 1 + 1
  4. 5 = 1 + 1 + 1 + 1 + 1

Example 2:
- Input: `amount = 3`, `coins = [2]`
- Output: 0
- Explanation: It's not possible to make up the amount 3 using only coins of denomination 2.

Example 3:
- Input: `amount = 10`, `coins = [10]`
- Output: 1
- Explanation: There is one way to make up the amount 10, using a single coin of denomination 10.

Constraints:
- 1 <= `coins.length` <= 300
- 1 <= `coins[i]` <= 5000
- All values in `coins` are unique.
- 0 <= `amount` <= 5000
