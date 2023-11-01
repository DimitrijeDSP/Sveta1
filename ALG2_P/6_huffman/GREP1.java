public class GREP1 {
    public static void main(String[] args) {
        String regexp = args[0];
        NFA nfa = new NFA(regexp);
        if (nfa.recognizes(args[1])) 
            StdOut.println("true");
        else
            StdOut.println("false");
    }
}