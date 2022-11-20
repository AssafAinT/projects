/****************************************************
* max_n_pnts                                        *
* Assaf Ainhoren                                    *
* Reviewer: Herscho the king                        *
* date: 11.09.2022                                  *
****************************************************/
/********************************libraries includes****************************/
#include <iostream>
enum 
{
    pnt = 2,
    size = 6
};
int Coline(int *a,int *b,int *c){ 
    if ((a[0]-c[0])*(b[1]-c[1]) == (a[1]-c[1])*(b[0]-c[0]))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
int MaxNPnt(int graph[size][pnt]) {
    int n = size;
    int max_pts = 0;
    for(int i = 0; i < n; ++i )
    {
        for(int j = i+1;  j < n; ++j)
        {
            if(graph[i][0]==graph[j][0] && graph[i][1]==graph[j][1]) 
            {
                continue;
            }
            int sum = 0;
            for(int k = 0; k < n; ++k)
            {
                sum += Coline(graph[i],graph[j],graph[k]);

            } 
            max_pts = std::max(max_pts,sum);
        }
    }
    if(max_pts==0)
    {
        return n;
    }
    else
    {
        return max_pts;
    }
}
int main(void)
{
    int points[size][pnt] = {{-1, 1}, {0, 0}, {1, 1}, 
                    {2, 2}, {3, 3}, {3, 4} };

    std::cout << "points: " << MaxNPnt(points) << std::endl;


    return (0);
}