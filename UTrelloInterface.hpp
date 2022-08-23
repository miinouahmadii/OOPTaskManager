#ifndef __UTrelloInterface_hpp__
#define __UTrelloInterface_hpp__
#include<string>
#include<vector>
#include<iostream>
#include"Task.hpp"
#include"List.hpp"
#include"User.hpp"


class UTrelloInterface
{
public:
	UTrelloInterface();

	std::string addUser(std::string username);
	std::string addTask(std::string list,std::string name, unsigned int estimatedTime, unsigned int priority, std::string description);
	std::string editTask(std::string task, unsigned int estimatedTime, unsigned int priority, std::string description);
	std::string deleteTask(std::string task);
	std::string assignTask(std::string task,std::string user);
	std::string moveTask(std::string task,std::string list);
	std::string completeTask(std::string task);
    std::string printTask(std::string task);
	std::string addList(std::string name);
	std::string deleteList(std::string list);
	std::string printList(std::string list);
	std::string printUserTasks(std::string user);
	std::string printUserUnfinishedTasks(std::string user);
	int printTotalEstimatedTime();
	int printTotalRemainingTime();
    int printUserWorkload(std::string user);
	std::string printUsersByWorkload();
	std::string printUsersByPerformance();
    std::string printAllLists();
    std::string printUnassignedTasksByPriority();
	std::string printAllUnfinishedTasksByPriority();
    void sort_tasks_by_priority();
    void sort_users_by_time();
    void sort_users_by_estimatedtime();
    bool is_in_tasks(vector<Task*>t,Task* t2);
    bool is_in_users(vector<User*>u,User* u2);
    private:
    vector<User*> Users;
    vector<User*> Sorted_Users;
    vector<User*> Sorted_Users_estimatedtime;
    vector<List*> Lists;
    vector<Task*> Tasks;
    vector<Task*> Sorted_Tasks;
    vector<Task*> tasks_of_user;
    vector<Task*> tasks_remain;
};
#endif