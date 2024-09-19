#include "Text.h"

void Text::SetSizes(Text &end)
{
    end.size = size;
    end.data = new String[size];

    for (int i1 = 0; i1 < size; i1++)
    {
        for (int j1 = 0; j1 < data[i1].size; j1++)
        {
            if (!IsLetter(data[i1].data[j1]))
            {
                end.data[i1].size++;
                continue;
            }

            String word1 = GetWord(i1, j1);

            int counter = 0;
            bool f1 = false;
            for (int i2 = 0; i2 <= i1; i2++)
            {
                bool flag = true;
                for (int j2 = 0; (i2 != i1 && j2 < data[i2].size) || (i2 == i1 && j2 < j1); j2++)
                {
                    if (!IsLetter(data[i2].data[j2]))
                        continue;
            
                    String word2 = GetWord(i2, j2);
                    counter++;
                    if (word1 == word2)
                    {
                        f1 = true;
                        flag = false;
                        break;
                    }
                    j2 += word2.size - 1;
                }
                if (!flag)
                    break;
            }

            end.data[i1].size += !f1 ? word1.size :  3 + String(counter).size;
            j1 += word1.size - 1;
        }
        end.data[i1].data = new char[end.data[i1].size];
    }
}