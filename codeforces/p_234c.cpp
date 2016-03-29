#include <fstream>
#include <cmath>

#define N_MAX 100005

int main()
{
    int n;
    std::ifstream fin;
    fin.open("input.txt");
    fin >> n;

    int t[N_MAX];
    for (int i = 1; i <= n; i++)
        fin >> t[i];
    fin.close();

    int d_neg[N_MAX];
    d_neg[0] = 0;
    for (int i = 1; i <= n-1; i++)
        d_neg[i] = d_neg[i-1] + int(t[i] >= 0);

    int d_pos[N_MAX];
    d_pos[n+1] = 0;
    for (int i = n; i > 1; i--)
        d_pos[i] = d_pos[i+1] + int(t[i] <= 0);
    
    int min_num_changes = d_neg[1] + d_pos[2];
    for (int i = 2; i <= n-1; i++)
    {
        int num_changes = d_neg[i] + d_pos[i+1];
        if (num_changes < min_num_changes)
            min_num_changes = num_changes;
    }

    std::ofstream fout;
    fout.open("output.txt");
    fout << min_num_changes;
    fout.close();
    return 0;
}