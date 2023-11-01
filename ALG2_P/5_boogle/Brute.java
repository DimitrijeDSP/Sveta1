public class Brute {
    public static int search1(String pat, String txt) {
        int M = pat.length();
        int N = txt.length();
        for (int i = 0; i < N - M; i++) {
            int j;
            for (j = 0; j < M; j++)
                if (txt.charAt(i+j) != pat.charAt(j))
                    break;
            if (j == M) return i;    // found
        }
        return N;  // not found 
    }

    public static int search2(String pat, String txt) {
        int i, M = pat.length();
        int j, N = txt.length();
        for (i = 0, j = 0; i < N && j < M; i++) {
            if (txt.charAt(i+j) == pat.charAt(j)) j++;
            else {
                i -= j;
                j = 0;
            }
        }
        if (j == M) 
            return i - M;    // found
        else 
            return N;  // not found 
    }

}