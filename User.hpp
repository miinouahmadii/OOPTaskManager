#ifndef __User_hpp__
#define __User_hpp__
#include<string>
#include<vector>
#include<iostream>
#include"Task.hpp"

class User
{
public:
    User(std::string name){ username=name;}
    std::string return_username(){return username;}
    void push_back_tasks(Task* assign_task){tasks_of_user.push_back(assign_task);}
    int number_of_tasks() {return tasks_of_user.size();}

    int return_sum_of_times()
    {
        int x=0;
        for(int i=0;i<tasks_of_user.size();i++)
        {
            x+=tasks_of_user[i]->return_estimatedTime();
        }
        return x;
    }

    int return_sum_of_remain_times()
    {
        int x=0;
        for(int i=0;i<tasks_of_user.size();i++)
        {  
            if(tasks_of_user[i]->compilit_status_tasks()!= true)
            {
            x+=tasks_of_user[i]->return_estimatedTime();
            }
        }
        return x;
    }
    int return_sum_of_tasks_time()
    {
        int x=0;
        for(int i=0;i<tasks_of_user.size();i++)
        {  
            x+=tasks_of_user[i]->return_estimatedTime();
        }
        return x;
    }
    
    std::vector<Task*> return_tasks_of_user(){return tasks_of_user;}
private:
    std::string username;
    std::vector<Task*>tasks_of_user;
};
#endif