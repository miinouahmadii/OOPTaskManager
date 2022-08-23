#include<string>
#include<vector>
#include<iostream>
#include"Task.hpp"
#include"List.hpp"
#include"User.hpp"
#include"UTrelloInterface.hpp"

int main()
{
	UTrelloInterface interface;

	std::cout << interface.addUser("Zhivar") <<std::endl;

	std::cout << interface.addUser("Amir") <<std::endl;

	std::cout << interface.addUser("Bardia") <<std::endl;

	std::cout << interface.addList("Code") <<std::endl;

	std::cout << interface.addList("Description") << std::endl;

	std::cout << interface.addList("Misc") << std::endl;

    std::cout << interface.addTask("Code", "Do Everything", 12, 1, "Write the whole code") <<std::endl;

    std::cout << interface.editTask("Do Everything", 12, 10, "Write the whole code") <<std::endl;

    std::cout << interface.assignTask("Do Everything", "Bardia") <<std::endl;

    std::cout << interface.printTask("Do Everything") <<std::endl;

    std::cout << interface.addTask("Code", "Destroy code formatting", 1, 2, "Rewrite the whole code in a worse format") <<std::endl;

	std::cout << interface.assignTask("Destroy code formatting", "Zhivar") <<std::endl;

	std::cout << interface.addTask("Description", "Write Description", 3, 1, "Write the damn description") <<std::endl;

	std::cout << interface.assignTask("Write Description", "Amir") <<std::endl;

	std::cout << interface.addTask("Misc", "Upload Assignment", 1, 1, "Upload it") <<std::endl;

	std::cout << interface.completeTask("Do Everything") <<std::endl;

	std::cout << interface.deleteTask("Upload Assignment") <<std::endl;

    std::cout << interface.printUserWorkload("Amir")<<std::endl;

	std::cout << interface.addTask("Misc", "Have fun", 10, 2, "Just do it")<<std::endl;

	std::cout << interface.moveTask("Have fun", "Code")<<std::endl;

    std::cout << interface.printTotalEstimatedTime()<<std::endl;

    std::cout << interface.printTotalRemainingTime()<<std::endl;

	std::cout << interface.printTask("Have fun")<<std::endl;

    std::cout << interface.printList("Code")<<std::endl;

    std::cout << interface.printAllLists() <<std::endl;

    std::cout << interface.printUserTasks("Amir")<<std::endl;

    std::cout << interface.printUserUnfinishedTasks("Amir")<<std::endl;

    std::cout << interface.printUnassignedTasksByPriority()<<std::endl;
	
    std::cout << interface.printAllUnfinishedTasksByPriority()<<std::endl;

    std::cout << interface.printUsersByWorkload()<<std::endl;

	std::cout << interface.printUsersByPerformance()<<std::endl;

    return 0;
}
