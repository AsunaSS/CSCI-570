import os
import sys
import time
import tracemalloc

class Efficient():
    def __init__(self, scores, keys):
        self.scores = scores
        self.keys = keys

    def score_dict(self):
        score_matrix = {}
        l = len(self.keys)
        for i in range(l):
            c1 = self.keys[i]
            if c1 == '_':
                score_matrix['_'] = {k: str1 for (k, str1) in zip(self.keys, [self.scores['gap'] for _ in range(l)])}
                continue
            score_matrix[c1] = {}
            for j in range(l):
                c2 = self.keys[j]
                if c2 == '_':
                    score_matrix[c1][c2] = self.scores['gap']
                elif i == j:
                    score_matrix[c1][c2] = self.scores['match']
                else:
                    score_matrix[c1][c2] = self.scores['mismatch'][c1 + c2]
        return score_matrix

    @staticmethod
    def prei(str1, str2, score_matrix):
        n, m = len(str1), len(str2)
        dp = [[0 for _ in range(m + 1)] for _ in range(n + 1)]
        for j in range(1, m + 1):
            dp[0][j] = dp[0][j - 1] + 30
        for i in range(1, n + 1):
            dp[i][0] = dp[i - 1][0] + 30
        for i in range(1, n + 1):
            for j in range(1, m + 1):
                dp[i][j] = min(dp[i][j - 1] + 30,
                              dp[i - 1][j] + 30,
                              dp[i - 1][j - 1] + score_matrix[str1[i - 1]][str2[j - 1]])
            if i != 0:
                dp[i - 1] = []
        return dp[n]

    @staticmethod
    def baci(str1, str2, score_matrix):
        n, m = len(str1), len(str2)
        dp = [[0 for _ in range(m + 1)] for _ in range(n + 1)]
        for j in range(1, m + 1):
            dp[0][j] = dp[0][j - 1] + 30
        for i in range(1, n + 1):
            dp[i][0] = dp[i - 1][0] + 30
        for i in range(1, n + 1):
            for j in range(1, m + 1):
                dp[i][j] = min(dp[i][j - 1] + 30,
                              dp[i - 1][j] + 30,
                              dp[i - 1][j - 1] + score_matrix[str1[n - i]][str2[m - j]])
            if i != 0:
                dp[i - 1] = []
        return dp[n]

    @staticmethod
    def traceback(str1, str2, dp_tb):
        i, j = len(str1), len(str2)
        str1_ali = []
        str2_ali = []
        while (j > 0) or (i > 0):
            if dp_tb[i][j] == '-':
                str1_ali.append('_')
                str2_ali.append(str2[j - 1])
                j -= 1
            elif dp_tb[i][j] == '|':
                str1_ali.append(str1[i - 1])
                str2_ali.append('_')
                i -= 1
            elif dp_tb[i][j] == '\\':
                str1_ali.append(str1[i - 1])
                str2_ali.append(str2[j - 1])
                i -= 1
                j -= 1
        return ''.join(str1_ali[::-1]), ''.join(str2_ali[::-1])

    def basic_dp(self, str1, str2, score_matrix):
        dp = [[0 for _ in range(len(str2) + 1)] for _ in range(len(str1) + 1)]
        dp_tb = [['' for _ in range(len(str2) + 1)] for _ in range(len(str1) + 1)]
        for j in range(1, len(str2) + 1):
            dp[0][j] = dp[0][j - 1] + 30
            dp_tb[0][j] = '-'
        for i in range(1, len(str1) + 1):
            dp[i][0] = dp[i - 1][0] + 30
            dp_tb[i][0] = '|'
        for i in range(1, len(str1) + 1):
            for j in range(1, len(str2) + 1):
                Dig = dp[i - 1][j - 1] + score_matrix[str1[i - 1]][str2[j - 1]]
                Left = dp[i][j - 1] + 30
                Up = dp[i - 1][j] + 30
                if (Dig <= Up) and (Dig <= Left):
                    dp[i][j] = Dig
                    dp_tb[i][j] = '\\'
                elif Up < Left:
                    dp[i][j] = Up
                    dp_tb[i][j] = '|'
                else:
                    dp[i][j] = Left
                    dp_tb[i][j] = '-'
            if i != 0:
                dp[i-1] = []
        score = dp[len(str1)][len(str2)]
        alignment_v, alignment_w = self.traceback(str1, str2, dp_tb)
        return score, alignment_v, alignment_w

    def divide_conquer(self, str1, str2, score_matrix):
        n, m = len(str1), len(str2)
        if n <= 1 or m <= 1:
            return self.basic_dp(str1, str2, score_matrix)
        else:
            prei = self.prei(str1[:n//2], str2, score_matrix)
            baci = self.baci(str1[n//2:], str2, score_matrix)
            index = [prei[i] + baci[m - i] for i in range(m + 1)]
            index = index.index(min(index))
            prei = self.divide_conquer(str1[:n//2], str2[:index], score_matrix)
            baci = self.divide_conquer(str1[n//2:], str2[index:], score_matrix)
            score = prei[0] + baci[0]
            alignment_v = prei[1] + baci[1]
            alignment_w = prei[2] + baci[2]
            return score, alignment_v, alignment_w

    def align(self, str1, str2):
        score_matrix = self.score_dict()
        score, alignment_v, alignment_w = self.divide_conquer(str1, str2, score_matrix)
        return score, alignment_v, alignment_w

if __name__ == '__main__':
    tracemalloc.start()
    start_time = time.time()
    path = './'
    #input_file = sys.argv[1]
    file_name = '10_H.txt'
    alignment1 = ''
    alignment2 = ''
    with open("10.txt", 'r') as file:
        lines = file.readlines()
        line = lines[0]
        tmp = line.split('\n')
        alignment1 = tmp[0]
        i = 1
        for line in lines[1:]:
            if line[0].isalpha():
                tmp = line.split('\n')
                line = tmp[0]
                alignment2 = line
                i += 1
                break
            else:
                alignment1_list = list(alignment1)
                alignment1_list.insert(int(line) + 1, alignment1)
                alignment1 = ''.join(alignment1_list)
                i += 1
        for line in lines[i:]:
            alignment2_list = list(alignment2)
            alignment2_list.insert(int(line) + 1, alignment2)
            alignment2 = ''.join(alignment2_list)
    #print(alignment1)
    #print(alignment2)
    keys = ['A', 'C', 'T', 'G', '_']
    scores = {'match': 0,
              'mismatch': {'AC': 110, 'AG': 48, 'AT': 94,
                           'CA': 110, 'CG':118, 'CT': 48,
                           'GA': 48,  'GC':118, 'GT':110,
                           'TA': 94,  'TC': 48, 'TG':110},
              'gap': 30}
    hs = Efficient(scores, keys)
    score, alignment1, alignment2 = hs.align(alignment1, alignment2)
    _, peak = tracemalloc.get_traced_memory()
    end_time = time.time()
    tracemalloc.stop()
    elapsed_time = end_time - start_time
    with open(os.path.join(path, file_name), 'w+') as f:
        f.write(alignment1[:50] + ' ' + alignment1[-50:] + '\n')
        f.write(alignment2[:50] + ' ' + alignment2[-50:] + '\n')
        f.write("%.1f\n" % float(score))
        f.write("%.4f\n" % elapsed_time)
        f.write("%.3f\n" % (peak / (10 ** 3)))