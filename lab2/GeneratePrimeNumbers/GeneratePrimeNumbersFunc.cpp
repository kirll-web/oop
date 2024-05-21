#include <set>
#include <vector>

std::set<int> GeneratePrimeNumbersSet(const int upperBound)
{
    std::set<int> numbers;
    std::vector<bool> startPos(upperBound + 1, true);
    for (int k = 2; k * k <= upperBound; k++)
    {
        if (startPos[k])
        {
            for (int l = k * k; l <= upperBound; l += k)
            {
                startPos[l] = false;
            }
        }
    }

    for (int k = 2; k <= upperBound; k++) 
    {
        if (startPos[k])
        {
            numbers.insert(k);
        }
    }

    return numbers;
}