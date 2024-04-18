def main():
    t = int(input())
    for _ in range(t):
        n, m = map(int, input().split())
        ans = 0
        v = [0] + list(map(int, input().split()))
        dp = [-1] * (2 * n + 1)

        for i in range(1, n + 1):
            if v[i] + i == m:
                dp[i] = 1
            else:
                dp[i] = 0

        for i in range(n, 0, -1):
            if i + v[i] <= n:
                dp[i] = max(dp[i], dp[i + v[i]] + dp[i])

        for i in range(1, n + 1):
            ans += dp[i]

        print(ans)

if __name__ == "__main__":
    main()