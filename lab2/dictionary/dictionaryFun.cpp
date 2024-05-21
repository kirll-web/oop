#include "dictionaryFun.h"
const std::string DEL_TRANSLATED_WORDS = ",";
const std::string END_OF_STRING = "...";

bool InitDictionary(std::istream& inputStream, std::map<std::string, std::vector<std::string>>& dictionary)
{
    while (!inputStream.eof())
    {
        std::string wordEng;
        getline(inputStream, wordEng);

        if (wordEng == "")
        {
            break;
        }

        std::string translateLine;
        getline(inputStream, translateLine);

        std::vector<std::string> wordsRus;
        //���������� ��� ������ token compress � ��� ��������� ����� ���������� �������������
        boost::split(wordsRus, translateLine, boost::is_any_of(DEL_TRANSLATED_WORDS), boost::token_compress_on);

        for (std::string word : wordsRus) 
        {
            if (word.length() > 0)
            {
                dictionary[wordEng].push_back(word);
            }
        }
    }

    if (inputStream.bad())
    {
        return false;
    }

    return true;
}

std::vector<std::string> TranslateWord(std::string const& wordEng, std::map<std::string,  std::vector<std::string>> & dictionary)
{
    if (dictionary.count(wordEng))
    {
        return dictionary[wordEng];
    }

    return {};
}

bool AddNewWordToDictionary(std::string const& wordEng, std::string & wordRus,  std::map<std::string, std::vector<std::string>>& dictionary, std::istream& inputStream)
{
    std::cout << "����������� ����� " << wordEng << ". ������� ������� ��� ������ ������ ��� ������." << std::endl;
    getline(inputStream, wordRus);

    if (wordEng[wordEng.length() - 1] == '\x1a')
    {
        std::cout << "����� ������������ ������." << std::endl;
        return false;
    }

    if (wordRus == END_OF_STRING)
    {
        return false;
    }
    //��������� ������������ ��������� ���������� ���� �������� �������� �������
    if (wordEng.length() == 0)
    {
        std::cout << "������ �� ������ �� ���������� ������.";
        return false;
    }

    if (wordRus.length() == 0)
    {
        std::cout << "C���� " << wordEng << " ���� ���������������." << std::endl;
        return true;
    }


    dictionary[wordEng].push_back(wordRus);
    std::cout << "��� ����� " << wordEng << " ������� ������� " << wordRus << std::endl;
    return true;
}


bool SavedChangesInFile(std::string const & dictionaryFileName, std::map<std::string, std::vector<std::string>> const& dictionary)
{
    std::string wordRus;
    std::ofstream dictionaryFile(dictionaryFileName);

    if (dictionary.size() > 0)
    {
        for (auto & pairWords : dictionary) 
        {
            //�������� ���������� ���������
            dictionaryFile << pairWords.first << std::endl;

            for (auto & word : pairWords.second)
            {
                dictionaryFile << word << ",";
            }
            dictionaryFile << std::endl;
        }
    }
    else 
    {
        std::cout << "������� ������ �������." << std::endl;
        return false;
    }

    if (!dictionaryFile.flush())
    {
        std::cout << "Filed to write data to outputFile." << std::endl;
        dictionaryFile.close();
        return false;
    }

    dictionaryFile.close();

    return true;
}

bool DictionaryWas�hanged(std::string const& dictionaryFileName, std::map<std::string, std::vector<std::string>> const& dictionary)
{
    std::string answer;
    std::cout << "� ������� ���� ������� ���������. ������� Y ��� y ��� ���������� ����� �������." << std::endl;
    getline(std::cin, answer);

    if (answer == "y" || answer == "Y")
    {
        return SavedChangesInFile(dictionaryFileName, dictionary);
    }
}

bool GetWordEng(std::istream& inputStream, std::string& wordEng)
{
    wordEng = "";
    if (inputStream.bad())
    {
        return false;
    }

    std::cout << "������� ����� ��� ��������" << std::endl;

    getline(inputStream, wordEng);

    //����� ������ �� ��������� ������ ���������

    if (wordEng == END_OF_STRING)
    {
        return false;
    }

    if (wordEng[wordEng.length()-1] == '\x1a')
    {
        std::cout << "����� ������������ ������." << std::endl;
        return false;
    }

    return true;
}