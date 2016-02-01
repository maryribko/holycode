#include <iostream>
#include <vector>
#include <queue>

struct Cell
{
    typedef std::pair<bool, int> Edge;

    int color;
    int num_active_edges;
    std::vector<Edge> edges;
};

void fillBoard (int n, int m, std::vector<Cell> & board)
{
    board.resize(n*m);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
        {
            char c;
            std::cin >> c;

            int cell_idx = i * m + j;

            board[cell_idx].color = c - 'A';

            // Add neighbours
            if (j != 0)
            {
                int cell_left_idx = cell_idx - 1;

                if (board[cell_idx].color == board[cell_left_idx].color)
                {
                    board[cell_idx].num_active_edges++;
                    board[cell_idx].edges.emplace_back(true, cell_left_idx);

                    board[cell_left_idx].num_active_edges++;
                    board[cell_left_idx].edges.emplace_back(true, cell_idx);
                }
            }

            if (i != 0)
            {
                int cell_up_idx = cell_idx - m;

                if (board[cell_idx].color == board[cell_up_idx].color)
                {
                    board[cell_idx].num_active_edges++;
                    board[cell_idx].edges.emplace_back(true, cell_up_idx);

                    board[cell_up_idx].num_active_edges++;
                    board[cell_up_idx].edges.emplace_back(true, cell_idx);
                }
            }
        }
}

bool cycleCheck (std::vector<Cell> & board)
{
    std::queue<int> next2process;

    // Init
    for (int cell_idx = 0; cell_idx < board.size(); cell_idx++)
        if (board[cell_idx].num_active_edges == 1)
            next2process.push(cell_idx);

    // Process
    while (!next2process.empty())
    {
        int cell_idx = next2process.front();
        next2process.pop();

        board[cell_idx].num_active_edges--;

        for (Cell::Edge & edge: board[cell_idx].edges)
        {
            if (edge.first)
            {
                edge.first = false;

                int neib_idx = edge.second;
                board[neib_idx].num_active_edges--;

                for (Cell::Edge & rev_edge: board[neib_idx].edges)
                    if (rev_edge.second == cell_idx)
                        rev_edge.first = false;

                if (board[neib_idx].num_active_edges == 1)
                    next2process.push(neib_idx);
            }
        }
    }

    // Check if there is cycle
    for (Cell & cell: board)
        if (cell.num_active_edges > 1)
            return true;

    return false;
}

int main()
{
    int n,m;
	std::cin >> n >> m;
	
    std::vector<Cell> board;
    fillBoard (n, m, board);

    if (cycleCheck (board))
        std::cout << "Yes";
    else
        std::cout << "No";

	return 0;
}
