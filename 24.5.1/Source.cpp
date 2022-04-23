#include <iostream>
#include <ctime>
#include <iomanip>
#include <string>
#include <fstream>

#define BEGIN  "begin"
#define END    "end"
#define STATUS "status"
#define EXIT   "exit"

std::string spentTime(std::time_t time)
{
    double h;
    h = (double)time / 3600;
    std::string spentTime = std::to_string(h) + "h";
    return spentTime;
}

void endTask(std::string& fileName, const std::string& taskActiveName, std::time_t startTime)
{
    system("cls");
    std::time_t spentTime = std::time(nullptr) - startTime;
    std::ofstream file(fileName, std::ios::app);
    file << taskActiveName << ' ' << spentTime << std::endl;
    file.close();
    std::cout << "Task " << taskActiveName << " completed" << std::endl << std::endl;
}

bool isCorrectCommand(const std::string* actions, std::string& action)
{
    for (int i = 0; i < actions->size(); ++i)
    {
        if (action == actions[i])
        {
            return true;
        }
    }
    return false;
}

int main()
{
	std::string commands[]{ BEGIN, END, STATUS, EXIT };
	std::string taskActiveName = "";
    std::string taskCompletedName = "";
	std::string command;
	bool activeTask = false;
	std::time_t startTime = std::time(nullptr);
	std::string fileName{ "Tasks.txt" };
	std::ofstream file(fileName);

    do
    {
        std::cout << "Enter one of command below: " << std::endl;
        std::cout << "1.\"" << BEGIN  << "\"  FOR START NEW TASK" << std::endl;
        std::cout << "2.\"" << END    << "\"    FOR FINISH TASK" << std::endl;
        std::cout << "3.\"" << STATUS << "\" SHOW ALL FINISHED TASK" << std::endl;
        std::cout << "4.\"" << EXIT   << "\"   EXIT FROM PROGRAM" << std::endl;
        do
        {
            std::cin >> command;
        }   
        while (!isCorrectCommand(commands, command));

        if (command == BEGIN)
        {
            system("cls");
            if (activeTask)
            {
                endTask(fileName, taskActiveName, startTime);
                activeTask = false;
                taskCompletedName = taskActiveName;
            }

            std::cout << "Enter the name of the task: ";
            std::cin >> taskActiveName;
            startTime = time(nullptr);
            activeTask = true;
            system("cls");
            std::cout << "Task " << taskActiveName << " started" << std::endl << std::endl;
        }
        else
            if (command == END && activeTask)
            {   
                endTask(fileName, taskActiveName, startTime);
                activeTask = false;
                taskCompletedName = taskActiveName;
            }
            else
                if (command == STATUS)
                {
                    system("cls");
                    if (activeTask)
                    {
                        std::cout << "Active task " << taskActiveName << std::endl;
                    }
                    std::cout << "All completed tasks" << std::endl;
                    std::ifstream file(fileName);
                    std::time_t st;
                    while (file >> taskCompletedName >> st)
                    {
                        std::cout << taskCompletedName << ' ' << spentTime(st) << std::endl;
                    }
                    std::cout << std::endl << std::endl;
                }
    } while (command != commands[3]);
}