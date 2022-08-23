#ifndef __List_hpp__
#define __List_hpp__
#include"Task.hpp"
#include<string>
#include<vector>
#include<iostream>

class List
{
public:

    List(std::string keep_name)
    {
        name=keep_name;
        is_deleted = false;
    }
    std::string return_name_list(){return name;}
    void delete_list(){is_deleted=true;}
    bool delete_status(){return is_deleted;}
    void add_task_list(Task* new_task){tasks_of_list.push_back(new_task);}

    void delete_task_list(std::string task_name)
    {
        for(int i=0;i<tasks_of_list.size();i++)
        {
            if(tasks_of_list[i]->return_name_task()==task_name)
                tasks_of_list[i]->delete_task();
        }
    }

    bool delete_status_task(){return is_deleted_task;}
    std::vector<Task*>return_tasks_of_list(){return tasks_of_list;}
    
private:
    bool is_deleted;
    bool is_deleted_task;
    std::string name;
    std::vector<Task*>tasks_of_list;

};
#endif
