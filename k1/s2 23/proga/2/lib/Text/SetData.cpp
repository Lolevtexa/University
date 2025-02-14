#include "Text.h"

void Text::SetData(Text &end)
{
    for (int i1 = 0; i1 < size; i1++)
    {
        for (int j1 = 0, j = 0; j1 < data[i1].size;)
        {
            if (!IsLetter(data[i1].data[j1]))
            {
                end.data[i1].data[j] = data[i1].data[j1];
                j1++, j++;
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
                        flag = false;
                        f1 = true;
                        break;
                    }
                    j2 += word2.size - 1;
                }
                if (!flag)
                    break;
            }

            if (!f1)
                for (int k = 0; k < word1.size; k++)
                    end.data[i1].data[j++] = data[i1].data[j1 + k];
            else
            {
                end.data[i1].data[j++] = data[i1].data[j1];

                end.data[i1].data[j++] = '(';

                String number(counter);
                
                for (int k = 0; k < number.size; k++)
                    end.data[i1].data[j++] = number.data[k];

                end.data[i1].data[j++] = ')';
            }    

            j1 += word1.size;
        }
    }
}