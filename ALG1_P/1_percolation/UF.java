abstract class UF
{
    protected int[] id;

    public UF(int N)
    {
         id = new int[N];
         for (int i = 0; i < N; i++)
            id[i] = i;
    }

    abstract public boolean connected(int p, int q);

	abstract public void union(int p, int q);

    public void printUF()
    {
         for (int x: id )
               System.out.print(x+" ");
         System.out.println(" ");
    }

}
