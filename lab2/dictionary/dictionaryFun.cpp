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
        //посмотреть что делает token compress и при следующей сдаче рассказать преподавателю
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
    std::cout << "Неизвестное слово " << wordEng << ". Введите перевод или пустую строку для отказа." << std::endl;
    getline(inputStream, wordRus);

    if (wordEng[wordEng.length() - 1] == '\x1a')
    {
        std::cout << "Введён некорректный символ." << std::endl;
        return false;
    }

    if (wordRus == END_OF_STRING)
    {
        return false;
    }
    //проверять неправильные вхождения параметров выше основных действий функции
    if (wordEng.length() == 0)
    {
        std::cout << "Строка со словом на английском пустая.";
        return false;
    }

    if (wordRus.length() == 0)
    {
        std::cout << "Cлово " << wordEng << " было проигнорировано." << std::endl;
        return true;
    }


    dictionary[wordEng].push_back(wordRus);
    std::cout << "Для слова " << wordEng << " записан перевод " << wordRus << std::endl;
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
            //называть переменные правильно
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
        std::cout << "Передан пустой словарь." << std::endl;
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

bool DictionaryWasСhanged(std::string const& dictionaryFileName, std::map<std::string, std::vector<std::string>> const& dictionary)
{
    std::string answer;
    std::cout << "В словарь были внесены изменения. Введите Y или y для сохранения перед выходом." << std::endl;
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

    std::cout << "Введите слово для перевода" << std::endl;

    getline(inputStream, wordEng);

    //конец строки не завершает работу программы

    if (wordEng == END_OF_STRING)
    {
        return false;
    }

    if (wordEng[wordEng.length()-1] == '\x1a')
    {
        std::cout << "Введён некорректный символ." << std::endl;
        return false;
    }

    return true;
}