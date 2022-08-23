#ifndef __Task_hpp__
#define __Task_hpp__
#include<string>
#include<vector>
#include<iostream>

class Task
{
public: 
    Task(std::string keep_list_name,std::string keep_name , unsigned int keep_Time,unsigned int keep_priority, std::string keep_description)
    {
    name=keep_name;
    list=keep_list_name;
    estimatedTime=keep_Time;
    priority=keep_priority;
    description=keep_description;
    is_deleted=false;
    is_compilited=false;
    assigned_to = "Unassigned";
    }
    void change_list_name(std::string listname){list = listname;}
    std::string return_name_task(){return name;}
    std::string return_name_list(){return list;}
    unsigned int return_estimatedTime(){return estimatedTime;}
    unsigned int return_priority(){return priority;}
    void change_estimatedTime(unsigned int new_estimatedTime){estimatedTime=new_estimatedTime;}
    void change_priority(unsigned int new_priority){priority=new_priority;}
    void change_description(stringstd:: new_description){description=new_description;}
    std::string return_description(){return description;}
    void delete_task(){is_deleted=true;}
    bool delete_status_task(){return is_deleted;}
    void compilit_task(){is_compilited=true;}
    bool compilit_status_tasks(){return is_compilited;}
    void assign_to(string n){assigned_to = n;}
    std::string return_assigned_to(){return assigned_to;}

private:
    bool is_deleted;
    bool is_compilited;
    std::string name;
    std::string list;
    unsigned int estimatedTime;
    unsigned int priority;
    std::string description;
    std::string assigned_to;

};
#endif